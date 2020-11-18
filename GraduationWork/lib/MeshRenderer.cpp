#include "MeshRenderer.h"
#include "Function.h"
#include "MeshRendererInfo.h"
#include "Mesh.h"

namespace
{
    constexpr COLOR_F defColor{ 1.f, 1.f, 1.f, 1.f };

    void ClampColor(COLOR_F& _color)
    {
        Clamp(_color.r, 0.f, 1.f);
        Clamp(_color.g, 0.f, 1.f);
        Clamp(_color.b, 0.f, 1.f);
        Clamp(_color.a, 0.f, 1.f);
    }
}

std::unordered_map<std::string, MeshRendererInfo> MeshRenderer::meshInfo;

MeshRenderer::MeshRenderer() :
    alpha(1.f), diffuse(defColor), specular(defColor), ambient(defColor), emissive(defColor),
    info(nullptr), isLighting(true), isShadow(true)
{
}

MeshRenderer::~MeshRenderer()
{
    Release();
}

void MeshRenderer::Draw()
{
    if (info == nullptr)return;

    for (size_t i = 0ull, size = materials.size(); i < size; ++i)
        materials[i].Set();

    for (size_t i = 0ull, size = textures.size(); i < size; ++i)
        textures[i].Set();

    for (size_t i = 0ull, size = bones.size(); i < size; ++i)
        bones[i].Set();

    ClampColor(diffuse);
    ClampColor(specular);
    ClampColor(emissive);
    ClampColor(ambient);
    Clamp(alpha, 0.f, 1.f);

    MV1SetDifColorScale(info->handle, diffuse);
    MV1SetSpcColorScale(info->handle, specular);
    MV1SetEmiColorScale(info->handle, emissive);
    MV1SetAmbColorScale(info->handle, ambient);
    MV1SetOpacityRate(info->handle, alpha);

    VECTOR3 scale;
    scale.x = transform->scale.x * renderTransform.scale.x;
    scale.y = transform->scale.y * renderTransform.scale.y;
    scale.z = transform->scale.z * renderTransform.scale.z;

    MATRIX m = MGetScale(scale);

    m *= transform->GetFowardQuaternion().GetMatrix();

    m *= MGetTranslate(transform->position + renderTransform.position);

    m.m[0][0] = m.m[1][1] = 1.f;//TODO : Quaternionの行列変換バグ

    MV1SetMatrix(info->handle, m);

    SetUseLighting((isLighting) ? TRUE : FALSE);

    MV1DrawModel(info->handle);

}

bool MeshRenderer::Load(const std::string& _path)
{
    if (path == _path)return true;

    int h = -1;

    std::unordered_map<std::string, MeshRendererInfo>::iterator it = meshInfo.find(_path);
    if (it == meshInfo.end())
    {
        h = MV1LoadModel(_path.c_str());

        if (h == -1)return false;

        info = &meshInfo[_path];
        info->handle = h;
        info->isAsync = true;

        if (GetUseASyncLoadFlag())
            AddRendererToScene();
        else
            Initialize();
    }
    else
    {
        h = it->second.handle;
        ++it->second.count;

        info = &it->second;
    }

    if (info->isAsync)
        info->asyncList.emplace_back(this);
    else
        InitializeParam();

    path = _path;

    return true;
}

void MeshRenderer::Release()
{
    if (info == nullptr)return;

    --info->count;
    if (info->count <= 0)
    {
        MV1DeleteModel(info->handle);
        meshInfo.erase(path);
    }
    else
    {
        if (info->isAsync)
        {
            for (std::list<MeshRenderer*>::iterator it = info->asyncList.begin(),
                end = info->asyncList.end(); it != end; ++it)
            {
                if ((*it) == this)
                {
                    info->asyncList.erase(it);
                    break;
                }
            }
        }
    }

    info = nullptr;
    path.clear();
}

int MeshRenderer::GetHandle() const
{
    if (info != nullptr)
        return info->handle;
    return -1;
}

Material* MeshRenderer::GetMaterial(unsigned _count)
{
    if (_count < materials.size())
        return &materials[_count];
    return nullptr;
}

Texture* MeshRenderer::GetTexture(unsigned _count)
{
    if (_count < textures.size())
        return &textures[_count];
    return nullptr;
}

Bone* MeshRenderer::GetBone(unsigned _count)
{
    if (_count < bones.size())
        return &bones[_count];
    return nullptr;
}

Material* MeshRenderer::GetMaterial(const std::string& _name)
{
    for (size_t i = 0ull, size = materials.size(); i < size; ++i)
    {
        if (info->materials[i].name == _name)
            return &materials[i];
    }
    return nullptr;
}

Texture* MeshRenderer::GetTexture(const std::string& _name)
{
    for (size_t i = 0ull, size = textures.size(); i < size; ++i)
    {
        if (info->textures[i].name == _name)
            return &textures[i];
    }
    return nullptr;
}

Bone* MeshRenderer::GetBone(const std::string& _name)
{
    for (size_t i = 0ull, size = bones.size(); i < size; ++i)
    {
        if (info->bones[i].name == _name)
            return &bones[i];
    }
    return nullptr;
}

int MeshRenderer::CheckAsyncLoading() 
{
    if (info == nullptr)
        return 0;
    return CheckHandleASyncLoad(info->handle);
}

void MeshRenderer::DestroyParam()
{
    if (info == nullptr)return;

    meshInfo.erase(path);
    info = nullptr;
    path.clear();
}

void MeshRenderer::Initialize()
{
    if (info == nullptr)return;

    info->isAsync = false;

    int h = info->handle;

    //マテリアル生成
    info->materials.resize(MV1GetMaterialNum(h));
    for (int i = 0, size = static_cast<int>(info->materials.size()); i < size; ++i)
    {
        MeshRendererInfo::MaterialInfo& m = info->materials[i];
        m.name = MV1GetMaterialName(h, i);
        m.diffuse = MV1GetMaterialDifColor(h, i);
        m.specular = MV1GetMaterialSpcColor(h, i);
        m.emissive = MV1GetMaterialEmiColor(h, i);
        m.ambient = MV1GetMaterialAmbColor(h, i);
        m.specularPow = MV1GetMaterialSpcPower(h, i);
        m.diffuseTex = MV1GetMaterialDifMapTexture(h, i);
        m.specularTex = MV1GetMaterialSpcMapTexture(h, i);
        m.normalTex = MV1GetMaterialNormalMapTexture(h, i);
        m.blendMode = MV1GetMaterialDrawBlendMode(h, i);
        m.blendParam = MV1GetMaterialDrawBlendParam(h, i);
        m.toonSize = MV1GetMaterialOutLineWidth(h, i);
        m.toonColor = MV1GetMaterialOutLineColor(h, i);
    }

    //テクスチャ生成
    info->textures.resize(MV1GetTextureNum(h));
    for (int i = 0, size = static_cast<int>(info->textures.size()); i < size; ++i)
    {
        MeshRendererInfo::TextureInfo& t = info->textures[i];
        t.name = MV1GetTextureName(h, i);
        t.handle = MV1GetTextureGraphHandle(h, i);
        t.modeU = MV1GetTextureAddressModeU(h, i);
        t.modeV = MV1GetTextureAddressModeV(h, i);
        t.sample = MV1GetTextureSampleFilterMode(h, i);
    }

    //ボーン生成
    info->bones.resize(MV1GetFrameNum(h));
    for (int i = 0, size = static_cast<int>(info->bones.size()); i < size; ++i)
    {
        MeshRendererInfo::BoneInfo& b = info->bones[i];
        b.name = MV1GetFrameName(h, i);
        int count = MV1GetFrameParent(h, i);
        if (count >= 0)
            b.parent = count;
        else
            b.parent = -1;

        count = MV1GetFrameChildNum(h, i);
        if (count > 0)
            b.children.resize(count);

        b.isDisp = MV1GetFrameVisible(h, i);
        b.isSemiTrans = MV1GetFrameSemiTransState(h, i);

        b.meshes.resize(MV1GetFrameMeshNum(h, i));
        for (int j = 0, end = static_cast<int>(b.meshes.size()); j < end; ++j)
            b.meshes[j] = MV1GetFrameMesh(h, i, j);
    }

    //メッシュ生成
    info->meshes.resize(MV1GetMeshNum(h));
    for (int i = 0, size = static_cast<int>(info->meshes.size()); i < size; ++i)
    {
        MeshRendererInfo::MeshInfo& m = info->meshes[i];
        m.materialNo = MV1GetMeshMaterial(h, i);
        m.isDisp = MV1GetMeshVisible(h, i);
        m.blendMode = MV1GetMeshDrawBlendMode(h, i);
        m.blendParam = MV1GetMeshDrawBlendParam(h, i);
        m.isSemiTrans = MV1GetMeshSemiTransState(h, i);
    }

    //初期パラメータ
    for (std::list<MeshRenderer*>::iterator it = info->asyncList.begin(), end = info->asyncList.end(); it != end;)
    {
        (*it)->InitializeParam();
        it = info->asyncList.erase(it);
    }

}

void MeshRenderer::InitializeParam()
{
    //初期設定

    //マテリアル生成
    materials.resize(info->materials.size());
    for (int i = 0, size = static_cast<int>(materials.size()); i < size; ++i)
    {
        materials[i].no = i;
        materials[i].renderer = this;
        materials[i].info = info;

        materials[i].diffuse = info->materials[i].diffuse;
        materials[i].specular = info->materials[i].specular;
        materials[i].emissive = info->materials[i].emissive;
        materials[i].ambient = info->materials[i].ambient;

        materials[i].blendMode = info->materials[i].blendMode;
        materials[i].blendParam = info->materials[i].blendParam;
        materials[i].specularPow = info->materials[i].specularPow;

        materials[i].toonColor = info->materials[i].toonColor;
        materials[i].toonSize = info->materials[i].toonSize;
    }

    //テクスチャ生成
    textures.resize(info->textures.size());
    for (int i = 0, size = static_cast<int>(textures.size()); i < size; ++i)
    {
        textures[i].no = i;
        textures[i].info = info;

        textures[i].modeU = static_cast<Texture::ADDRESS_MODE>(info->textures[i].modeU);
        textures[i].modeV = static_cast<Texture::ADDRESS_MODE>(info->textures[i].modeV);
        textures[i].sample = static_cast<Texture::SAMPLE>(info->textures[i].sample);
        textures[i].handle = info->textures[i].handle;
    }

    //ボーン生成
    bones.resize(info->bones.size());
    for (int i = 0, size = static_cast<int>(bones.size()); i < size; ++i)
    {
        bones[i].no = i;
        bones[i].info = info;
        bones[i].renderer = this;

        bones[i].isDisp = info->bones[i].isDisp;

        //メッシュ生成
        bones[i].meshes.resize(info->bones[i].meshes.size());
        for (int j = 0, end = static_cast<int>(bones[i].meshes.size()); j < end; ++j)
        {
            Mesh& m = bones[i].meshes[j];
            m.no = info->bones[i].meshes[j];
            m.info = info;
            m.renderer = this;

            m.isDisp = info->meshes[j].isDisp;
            m.blendMode = info->meshes[j].blendMode;
            m.blendParam = info->meshes[j].blendParam;
        }
    }
}
