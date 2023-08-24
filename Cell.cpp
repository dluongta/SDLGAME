#include "Cell.h"
Cell::Cell()
{
    rect_.x = 0;
    rect_.y = 0;
    val_ = 0;
    watered = 0;
    g_click = Mix_LoadWAV("audio/sound_mouse_click.wav");
}

Cell::~Cell()
{
    if (p_object != NULL)
    {
        SDL_FreeSurface(p_object);
    }
}

bool Cell::LoadImg(const char* file_name)
{
    p_object = SDLCommonFunc::LoadImage(file_name);
    if (p_object == NULL)
        return false;
    return true;
}

void Cell::Show(SDL_Surface* des)
{
    if (p_object != NULL)
    {
        rect_ = SDLCommonFunc::ApplySurface(p_object, des, rect_.x, rect_.y, rect_.w, rect_.h);
    }
}
void Cell::HandleInputAction(SDL_Event events)
{   
    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
       
        if (events.button.button == SDL_BUTTON_LEFT || events.button.button == SDL_BUTTON_RIGHT)
        {
            val_++;
            val_ %= 18;
            if (val_ < 14 && val_ % 4 == 0) val_ = val_ - 4;
            if (val_ == 14) val_ = 12;
            if (val_ == 18) val_ = 14;
            Mix_PlayChannel(-1, g_click, 0);
        }
    }
}
void Cell::update() 
{
    if (watered && val_ < 14) {
        val_ += 18;
    }
    if (!watered)
        val_ %= 18;
}