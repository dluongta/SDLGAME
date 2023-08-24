#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "CommonFunction.h"

#define WIDTH_CELL 120
#define HEIGHT_CELL 120

class Cell
{
public:
   
    Cell();
    ~Cell();
    void Show(SDL_Surface* des);
    bool LoadImg(const char* file_name);
    void HandleInputAction(SDL_Event events);
    void SetRect(const int& x, const int& y, const int& w, const int& h) { rect_.x = x, rect_.y = y; rect_.w = w; rect_.h = h; }
    SDL_Rect GetRect() const { return rect_; }
    void set_val(const int& val) { val_ = val; }
    int get_val() const { return  val_; }
    bool get_watered() const { return watered; }
    void set_watered(const bool& water) { watered = water; }
    void update();
private:
    int val_;
    SDL_Rect rect_;
    SDL_Surface* p_object;
    bool watered;
};


#endif