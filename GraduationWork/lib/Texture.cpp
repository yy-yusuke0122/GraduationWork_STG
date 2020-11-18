#include "Texture.h"
#include "MeshRendererInfo.h"

void Texture::Set()
{
    MV1SetTextureAddressMode(info->handle, no, modeU, modeV);
    MV1SetTextureSampleFilterMode(info->handle, no, sample);
    MV1SetTextureGraphHandle(info->handle, no, handle, TRUE);
}

std::string Texture::GetName() const
{
    return info->textures[no].name;
}

bool Texture::SetMode(int _u, int _v)
{
    if (_u < 0 || _v < 0)return false;

    if (_u < DX_TEXADDRESS_NUM || _v < DX_TEXADDRESS_NUM)
    {
        if (_u == DEFAULT)modeU = info->textures[no].modeU;
        else modeU = _u;

        if (_v == DEFAULT)modeV = info->textures[no].modeV;
        else modeV = _v;

        return true;
    }
    return false;
}

void Texture::GetMode(int& _u, int& _v)
{
    _u = modeU;
    _v = modeV;
}

bool Texture::SetSample(int _sample)
{
    if (_sample < 0 || _sample >= DX_DRAWMODE_NUM)return false;

    sample = _sample;
    return true;
}
