#include "UI.h"
#include "UpdateButton.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Start()
{
}

Text::Text() :
	text(""), handle(-1)
{
	SetNewFont(NULL, -1, -1, -1);
	color = GetColor(255, 255, 255);
}

Text::~Text()
{
	if (handle != -1) {
		DeleteFontToHandle(handle);
	}
}

int Text::SetNewFont(char* FontName, int Size, int Thick, int FontType)
{
	int ret = CreateFontToHandle(FontName, Size, Thick, FontType);
	if (ret > 0) {
		handle = ret;
		fontName = FontName;
		size = Size;
		thick = Thick;
		fontType = FontType;
	}
	return ret;
}

int Text::Draw(VECTOR2 _position)
{
	int ret;

	if (handle != -1) {
		ret = DrawStringToHandle(
			static_cast<int>(_position.x),
			static_cast<int>(_position.y),
			text.c_str(),
			color,
			handle
		);
	}

	return ret;
}

int Text::SetFontSize(int _size)
{
	int tmp = handle;
	if (SetNewFont(fontName, _size, thick, fontType) != -1) {
		DeleteFontToHandle(tmp);
		return 0;
	}
	return -1;
}

int Text::SetFontThick(int _thick)
{
	int tmp = handle;
	if (SetNewFont(fontName, size, _thick, fontType) != -1) {
		DeleteFontToHandle(tmp);
		return 0;
	}
	return -1;
}

int Text::SetFontType(int _type)
{
	int tmp = handle;
	if (SetNewFont(fontName, size, thick, _type) != -1) {
		DeleteFontToHandle(tmp);
		return 0;
	}
	return -1;
}

void Text::SetColor(unsigned int _color)
{
	color = _color;
}

Button::Button()
{
}

Button::~Button()
{
}

void Button::Start()
{
	textObj = Instantiate<Text>();
	textObj->SetParent(this);

	image = AddComponent<ImageRenderer>();
	image->isUseScroll = false;

	updater = AddComponent<UpdateButton>();
}
