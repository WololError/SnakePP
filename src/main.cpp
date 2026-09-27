#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "Snake/snake.h"

#include <filesystem>
namespace fs = std::filesystem;

int main() {
    fs::current_path(fs::canonical("/proc/self/exe").parent_path().parent_path());
    while (true) {
        Snake snake;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        snake.run();
        if (snake.quitRequested())
            break;
    }
    return 0;
}