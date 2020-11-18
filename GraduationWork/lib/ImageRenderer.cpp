#include "ImageRenderer.h"
#include "UrLib.h"

ImageRenderer::ImageRenderer() :
    position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), alpha(1.0f),
    transFlag(TRUE), turnFlag(FALSE), order(0), drawNum(0u), image(this)
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

    int x = static_cast<int>(transform->position.x + position.x);
    int y = static_cast<int>(transform->position.y + position.y);
    int cx = sizex / 2;
    int cy = sizey / 2;
    float Angle = ToRadian(rotation);

    DrawRotaGraph3(x, y, cx, cy, scale.x, scale.y, Angle, image.imageInfo->handles[drawNum], transFlag, turnFlag);
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

void ImageRenderer::Initialize()
{
    if (image.imageInfo != nullptr)
        image.Initialize(image.imageInfo);
}
