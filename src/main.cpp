#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "Snake/snake.h"

#include <filesystem>

int main() {
    
    while (true) {
        Snake snake;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        snake.run();
        if (snake.quitRequested())
            break;
    }
    return 0;
}