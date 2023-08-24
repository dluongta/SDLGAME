#include "CommonFunction.h"
#include "Board.h"
#include "Board5x5.h"
#include"TextObject.h"
#include"Extension.h"
#include<ctime>

#undef main
TTF_Font* g_font_text = NULL;
std::string highscore;
bool is_quit = false;
//Make text
TextObject time_game;
TextObject score_game;
TextObject high_score;

bool Init()
{
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {   
        return false;
    }

    g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Pipe Water", NULL);

    if (g_screen == NULL)
        return false;
    if (TTF_Init() == -1) {
        return false;
    }
    resetHighScore("high_score.txt");
    g_font_text = TTF_OpenFont("font/Raleway-Medium.ttf", 20);
    if (g_font_text == NULL )
    {
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        return false;
    }
    g_click = Mix_LoadWAV("audio/sound_mouse_click.wav");
    if (g_click == NULL)
        return false;
    return true;
    
}
bool PlayMode1()
{
    
    //Make Board
    Board board;
    board.Show_Board(g_screen);
    Uint32 start_time = SDL_GetTicks();

    SDL_Flip(g_screen);
    while (!is_quit)
    {
        SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
        while (SDL_PollEvent(&g_even))
        {
            if (g_even.type == SDL_QUIT)
            {
                is_quit = true;
                return true;
            }
            if (g_even.type == SDL_KEYDOWN)
            {
                if (g_even.key.keysym.sym == SDLK_ESCAPE)
                {
                    return true;
                }
            }
        }

        board.HandleInputAction(g_even);
        board.convert();
        board.Show_Board(g_screen);
        //Show time for game

        std::string str_time = "Time: ";
        Uint32 time_val = TIME_PLAYING - (SDL_GetTicks() - start_time)/ 1000;
        std::string str_val = std::to_string(time_val);
        str_time += str_val;
        time_game.SetText(str_time);
        time_game.SetRect(WIDTH_BACKGROUND - 120, 10);
        time_game.CreatFontText(g_font_text, g_screen);
        //Show score
        std::string str_score = "Filled: ";
        Uint32 score_val = board.score();
        updateHighScore("high_score.txt", score_val, highscore);
        std::string str_score_val = std::to_string(score_val);
        str_score += str_score_val;
        str_score += "/16";
        score_game.SetText(str_score);
        score_game.SetRect(WIDTH_BACKGROUND - 120, 30);
        score_game.CreatFontText(g_font_text, g_screen);
        //Show highscore
        std::string str_highscore = "High Score: ";
        str_highscore += highscore;
        high_score.SetText(str_highscore);
        high_score.SetRect(WIDTH_BACKGROUND - 140, 50);
        high_score.CreatFontText(g_font_text, g_screen);
        if (SDL_Flip(g_screen) == -1)
            return true ;


        if (board.CheckBoard())
        {
            if (SDL_Flip(g_screen) == -1)
                return true ;
            if (MessageBox(NULL, L"You Win!", L"Infomation", MB_ICONINFORMATION) == IDOK)
            {
                break;
            }
        }

        if (time_val == 0)
        {
            if (MessageBox(NULL, L"GameOver!", L"Infomation", MB_ICONINFORMATION) == IDOK)
            {
                break;
            }
        }



        SDL_Delay(70);
    }
    return false;
}
bool PlayMode2()
{

    //Make Board
    Board5x5 board; 
    board.Show_Board(g_screen);
    Uint32 start_time = SDL_GetTicks();
    SDL_Flip(g_screen);
    while (!is_quit)
    {
        SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
        while (SDL_PollEvent(&g_even))
        {
            if (g_even.type == SDL_QUIT)
            {
                is_quit = true;
                return true;
            }
            if (g_even.type == SDL_KEYDOWN)
            {
                if (g_even.key.keysym.sym == SDLK_ESCAPE)
                {
                    return true;
                }
            }
        }

        board.HandleInputAction(g_even);
        board.convert();
        board.Show_Board(g_screen);

        //Show time for game
        std::string str_time = "Time: ";
        Uint32 time_val = TIME_PLAYING - (SDL_GetTicks() - start_time) / 1000;
        std::string str_val = std::to_string(time_val);
        str_time += str_val;
        time_game.SetText(str_time);
        time_game.SetRect(WIDTH_BACKGROUND - 120, 10);
        time_game.CreatFontText(g_font_text, g_screen);

        //Show score
        std::string str_score = "Filled: ";
        Uint32 score_val = board.score();
        updateHighScore("high_score.txt", score_val, highscore);
        std::string str_score_val = std::to_string(score_val);
        str_score += str_score_val;
        str_score += "/25";
        score_game.SetText(str_score);
        score_game.SetRect(WIDTH_BACKGROUND - 120, 30);
        score_game.CreatFontText(g_font_text, g_screen);
        //Show highscore
        std::string str_highscore = "High Score: ";
        str_highscore += highscore;
        high_score.SetText(str_highscore);
        high_score.SetRect(WIDTH_BACKGROUND - 140, 50);
        high_score.CreatFontText(g_font_text, g_screen);
        if (SDL_Flip(g_screen) == -1)
            return true;
       

        if (board.CheckBoard())
        {
            if (SDL_Flip(g_screen) == -1)
                return true;
            if (MessageBox(NULL, L"You Win!", L"Infomation", MB_ICONINFORMATION) == IDOK)
            {
                break;
            }
        }

        if (time_val == 0)
        {
            if (MessageBox(NULL, L"GameOver!", L"Infomation", MB_ICONINFORMATION) == IDOK)
            {
                break;
            }
        }
        SDL_Delay(70);
    }
    return false;
}




int main(int argc, char* argv[])
{
    
    if (Init() == false)
        return 0;
    // Apply Background
    g_bkground = SDLCommonFunc::LoadImage("image/background.png");
    if (g_bkground == NULL)
    {
        return 0;
    }
    
    while (true)
    {
        highscore = GetHighScoreFromFile("high_score.txt");
        //Menu
        int num_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);
        if (num_menu == 2)
        {
            break;      
        }
        bool is_done = false;
        if (num_menu == 0)
            is_done |= PlayMode1();
        else if (num_menu == 1)
            is_done |= PlayMode2();
        if (is_done)
        {
            break;
        }
    }

  
    SDLCommonFunc::CleanUp();
    SDL_Quit();

    return 1;
}
