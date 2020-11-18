#include "Material.h"
#include "MeshRendererInfo.h"
#include "MeshRenderer.h"
#include "Function.h"

namespace
{
    void ClampColor(COLOR_F& _color)
    {
        Clamp(_color.r, 0.f, 1.f);
        Clamp(_color.g, 0.f, 1.f);
        Clamp(_color.b, 0.f, 1.f);
        Clamp(_color.a, 0.f, 1.f);
    }
}


void Material::Set()
{
    ClampColor(diffuse);
    ClampColor(specular);
    ClampColor(ambient);
    ClampColor(emissive);
    ClampColor(toonColor);
    Clamp(blendParam, 0, 255);

    MV1SetMaterialDifColor(info->handle, no, diffuse);
    MV1SetMaterialSpcColor(info->handle, no, specular);
    MV1SetMaterialEmiColor(info->handle, no, emissive);
    MV1SetMaterialAmbColor(info->handle, no, ambient);
    MV1SetMaterialSpcPower(info->handle, no, specularPow);

    MV1SetMaterialDrawBlendMode(info->handle, no, blendMode);
    MV1SetMaterialDrawBlendParam(info->handle, no, blendParam);

    if (isToonDot)
    {
        MV1SetMaterialOutLineWidth(info->handle, no, 0.f);
        MV1SetMaterialOutLineDotWidth(info->handle, no, toonSize);
    }
    else
    {
        MV1SetMaterialOutLineWidth(info->handle, no, toonSize);
        MV1SetMaterialOutLineDotWidth(info->handle, no, 0.f);
    }

    MV1SetMaterialOutLineColor(info->handle, no, toonColor);
}

std::string Material::GetName() const
{
    return info->materials[no].name;
}

Texture* Material::GetDiffuseMap() const
{
    return renderer->GetTexture(info->materials[no].diffuseTex);
}

Texture* Material::GetSpecularMap() const
{
    return renderer->GetTexture(info->materials[no].specularTex);
}

Texture* Material::GetNormalMap() const
{
    return renderer->GetTexture(info->materials[no].normalTex);
}

bool Material::SetBlendMode(int _mode)
{
    switch (_mode)
    {
    case Material::NONE:
    case Material::ALPHA:
    case Material::ADD:
    case Material::SUB:
    case Material::MUL:
    case Material::INVSRC: break;
    default:return false;
    }

    blendMode = _mode;
    return true;
}
