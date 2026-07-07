#pragma once

namespace configsnake {

    //display
    constexpr int SIZE = 900;
    constexpr int EXTRA = 1;
    constexpr double SFPS = 60.0;

    //snake
    constexpr int PROP = 15;
    constexpr int DRAW_SNAKE = 7.0;
    constexpr int SNAKESIZE = SIZE / PROP;
    constexpr int SNAKEX = SIZE / 2;
    constexpr int SNAKEY = SIZE / 2;
    

    constexpr int UP    = 0;
    constexpr int LEFT  = 1;
    constexpr int DOWN  = 2;
    constexpr int RIGHT = 3;
    
    //fruit
    constexpr int FRUITSIZE = SNAKESIZE/4.0;
    constexpr int TIMEFRUIT = 1;

    //player drawing
    constexpr int BODYHORIZONTAL  = 0;
    constexpr int BODYVERTICAL    = 1;
    constexpr int BODYTOPLEFT     = 4;        
    constexpr int BODYTOPRIGHT    = 5;       
    constexpr int BODYBOTTOMLEFT  = 2;     
    constexpr int BODYBOTTOMRIGHT = 3;    

    constexpr int HEADOWN      = 0;
    constexpr int HEADLEFT     = 1;
    constexpr int HEADRIGHT    = 2;
    constexpr int HEADUP       = 3;

    constexpr int TAILDOWN     = 0;
    constexpr int TAILLEFT     = 1;
    constexpr int TAILRIGHT    = 2;
    constexpr int TAILUP       = 3;
}
