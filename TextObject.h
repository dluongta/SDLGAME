#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include <string>
#include<SDL_ttf.h>
#include"CommonFunction.h"
class TextObject 
{
public:
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,

	};
	TextObject();
	~TextObject();
	void SetText(const std::string& text) { str_val_ = text; }
	void SetColor(const int& type);
	void CreatFontText(TTF_Font* font, SDL_Surface* des);
	void Show(SDL_Surface* des);
	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }

private:
	std::string str_val_;
	SDL_Color text_color_;
	SDL_Surface* p_object_;
	SDL_Rect rect_;
};

#endif

