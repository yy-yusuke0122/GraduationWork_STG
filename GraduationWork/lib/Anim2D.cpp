#include "Anim2D.h"
#include "UrLib.h"

Anim2D::Anim2D(ImageRenderer* _renderer) :
	renderer(_renderer), loopFlag(true),
	filePass(""), xdiv(1), ydiv(1), allnum(1),
	start(0), end(0), currentNum(0), speed(1.0f), time(0.0f)
{
}

Anim2D::~Anim2D()
{
}

void Anim2D::Start()
{
	currentNum = start;
	time = 0.0f;

	ActiveImage();
}

void Anim2D::Update()
{
	bool isEnd = IsEndAnim();

	// ループ無しで終了していたら無視する
	if (!loopFlag && isEnd)
		return;

	// カウントアップ
	time += Time::DeltaTime() * speed;
	if (time > 1.0f) {
		int addNum = static_cast<int>(time);
		LoopClamp(time, 0.0f, 1.0f);

		if (IsPlayBack()) {
			currentNum -= addNum;
			if (currentNum < end) {
				if (loopFlag) LoopClamp(currentNum, end, start - 1);
				else currentNum = end;
			}
		}
		else {
			currentNum += addNum;
			if (currentNum > end) {
				if (loopFlag) LoopClamp(currentNum, start, end + 1);
				else currentNum = end;
			}
		}

		renderer->SetImageNumber(currentNum);
	}
	printfDx("画像番号 : %d\n", currentNum);
}

bool Anim2D::ActiveImage()
{
	renderer->SetImageDiv(filePass, xdiv, ydiv, allnum);

	return renderer->SetImageNumber(start);
}

bool Anim2D::SetUsedImage(const std::string& _filePass, unsigned int _xdiv, unsigned int _ydiv, unsigned int _allnum)
{
	bool okayPass = _filePass != "";
	bool okayDiv = _xdiv > 0 && _ydiv > 0;
	bool okayAllnum = (_xdiv * _ydiv) <= _allnum;
	if (okayPass && okayDiv && okayAllnum) {
		filePass = _filePass;
		xdiv = _xdiv;
		ydiv = _ydiv;
		allnum = _allnum;
		return true;
	}

		return false;
}

bool Anim2D::SetPlayNum(unsigned int _start, unsigned int _end)
{
	bool okayStart = _start >= 0 && _start < allnum;
	bool okayEnd = _end >= 0 && _end < allnum;
	if (okayStart && okayEnd) {
		start = static_cast<int>(_start);
		end = static_cast<int>(_end);
		return true;
	}
	return false;
}

bool Anim2D::SetPlaySpeed(float _speed)
{
	if (_speed < 0.0f)
		return false;

	speed = _speed;
	return true;
}

bool Anim2D::SetCurrentNum(unsigned int _num)
{
	int num = static_cast<int>(_num);
	if (IsPlayBack()) {
		if (start >= num && end <= num) {
			currentNum = num;
			return true;
		}
	}
	else {
		if (start <= num && end >= num) {
			currentNum = num;
			return true;
		}
	}

	return false;
}

void Anim2D::Reverse()
{
	ReplaceValue(start, end);
}

bool Anim2D::IsEndAnim() const
{
	if (IsPlayBack()) {
		return currentNum <= end;
	}
	else {
		return currentNum >= end;
	}
}

bool Anim2D::IsPlayBack() const
{
	return start > end;
}
