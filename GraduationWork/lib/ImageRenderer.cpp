#include "UrLib.h"

ImageRenderer::ImageRenderer() :
    position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), alpha(1.0f),
    transFlag(TRUE), turnXFlag(false), turnYFlag(false), order(0), drawNum(0u), image(this)
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

    DrawRotaGraph3(x, y, cx, cy, scale.x, scale.y, Angle, image.imageInfo->handles[drawNum],
        transFlag, (turnXFlag) ? TRUE : FALSE, (turnYFlag) ? TRUE : FALSE);
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
