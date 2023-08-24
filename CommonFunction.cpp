#include "CommonFunction.h"
#include "TextObject.h"


SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
    SDL_Surface* load_image = NULL;
    SDL_Surface* optimize_image = NULL;
    load_image = IMG_Load(file_path.c_str());
    if (load_image != NULL)
    {
        optimize_image = SDL_DisplayFormat(load_image);
        SDL_FreeSurface(load_image);
    }
    return optimize_image;
}


SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y, int w, int h)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    offset.w = w;
    offset.h = h;
    SDL_BlitSurface(src, NULL, des, &offset);
    return offset;
}





void SDLCommonFunc::CleanUp()
{
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_bkground);
    SDL_FreeSurface(g_menu);
    Mix_FreeChunk(g_click);
}
bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x > rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}
int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
    g_menu = LoadImage("image/background2d.png");
    if (g_menu == NULL)
    {
        return 1;
    }
    const int MenuItemNum = 3;
    SDL_Rect pos_arr[MenuItemNum];
    pos_arr[0].x = SCREEN_WIDTH/2-60;
    pos_arr[0].y = SCREEN_HEIGHT/2-60;
    pos_arr[1].x = SCREEN_WIDTH / 2-60;
    pos_arr[1].y = SCREEN_HEIGHT / 2-30 ;
    pos_arr[2].x = SCREEN_WIDTH / 2 - 60;
    pos_arr[2].y = SCREEN_HEIGHT / 2 ;
    TextObject text_menu[MenuItemNum];
    text_menu[0].SetText("Play Mode 4x4");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);
    text_menu[1].SetText("Play Mode 5x5");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);
    text_menu[2].SetText("Exit");
    text_menu[2].SetColor(TextObject::WHITE_TEXT);
    text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);
    bool selected[MenuItemNum] = { 0,0,0 };
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while (true)
    {
        SDLCommonFunc::ApplySurface(g_menu, des, 0, 0,SCREEN_WIDTH,SCREEN_HEIGHT);
        for (int i = 0; i < MenuItemNum; i++)
        {
            text_menu[i].CreatFontText(font, des);

        }
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 2;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < MenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                    {
                        if (selected[i] == 0)
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == 1)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }
            }

            break;
            case  SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < MenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                    {
                        return i;
                    }

                }

            }
            break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    exit(2);
                }

            default:
                break;

            }
        }
        SDL_Flip(des);
    }

    return 1;

}