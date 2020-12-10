#include "UrLib.h"

ImageRenderer::ImageRenderer() :
    position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f),
    alpha(255), add(-1), sub(-1), mul(-1), inv(-1),
    transFlag(TRUE), turnXFlag(false), turnYFlag(false), order(0), drawNum(0u), image(this),
    red(255), green(255), blue(255)
{
}

ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::Draw()
{
    if (image.imageInfo == nullptr)return;

    LoopClamp(rotation, 0.0f, 360.0f);

    int sizex = static_cast<int>(static_cast<float>(image.imageInfo->sizeX) * transform->scale.x);
    int sizey = static_cast<int>(static_cast<float>(image.imageInfo->sizeY) * transform->scale.y);

    const VECTOR2& scroll = Scroll::GetValue();

    int x = static_cast<int>(transform->position.x + position.x - scroll.x);
    int y = static_cast<int>(transform->position.y + position.y - scroll.y);
    int cx = sizex / 2;
    int cy = sizey / 2;
    float Angle = ToRadian(rotation);

    auto clamp = [](int& _pal) {Clamp(_pal, 0, 255); };

    clamp(red);
    clamp(green);
    clamp(blue);
    
    clamp(alpha);

    auto blend = [clamp](int _mode, int& _pal)
    {
        if (_pal != -1)
        {
            clamp(_pal);
            SetDrawBlendMode(_mode, _pal);
        }
    };

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    blend(DX_BLENDMODE_ADD, add);
    blend(DX_BLENDMODE_SUB, sub);
    blend(DX_BLENDMODE_MULA, mul);
    blend(DX_BLENDMODE_INVSRC, inv);

    SetDrawBright(red, green, blue);

    DrawRotaGraph3(x, y, cx, cy, scale.x, scale.y, Angle, image.imageInfo->handles[drawNum],
        transFlag, (turnXFlag) ? TRUE : FALSE, (turnYFlag) ? TRUE : FALSE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool ImageRenderer::SetImage(const std::string& _filePass)
{
    if (image.Load(_filePass))
    {
        drawNum = 0u;
        return true;
    }
    return false;
}

bool ImageRenderer::SetImageDiv(const std::string& _filePass, unsigned _xdiv, unsigned _ydiv, unsigned _allnum)
{
    if (image.LoadDiv(_filePass, _xdiv, _ydiv, _allnum))
    {
        drawNum = 0u;
        return true;
    }
    return false;
}

bool ImageRenderer::SetImageNumber(unsigned _num)
{
    if (image.imageInfo == nullptr)return false;

    if (static_cast<size_t>(_num) < image.imageInfo->handles.size())
    {
        drawNum = _num;
        return true;
    }
    return false;
}

unsigned ImageRenderer::GetDrawMaxNumber() const
{
    return (image.imageInfo == nullptr) ? 0u : static_cast<unsigned>(image.imageInfo->handles.size());
}

int ImageRenderer::CheckAsyncLoading() 
{
    if (image.imageInfo == nullptr)
        return 0;
    return CheckHandleASyncLoad(image.imageInfo->handles[0]);
}

void ImageRenderer::DestroyParam()
{
    image.DestroyParam();
    drawNum = 0u;
}

int ImageRenderer::GetSizeX() const
{
    return (image.imageInfo == nullptr) ? -1 : image.imageInfo->sizeX;
}

int ImageRenderer::GetSizeY() const
{
    return (image.imageInfo == nullptr) ? -1 : image.imageInfo->sizeY;
}

void ImageRenderer::Initialize()
{
    if (image.imageInfo != nullptr)
        image.Initialize(image.imageInfo);
}
