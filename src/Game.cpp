#include "Game.h"

Game::~Game() {
    shutdownAllegro();
}

void Game::run() {
    if (!initAllegro())
        return;

    if (!init())
        return;

    while (running) {
        al_wait_for_event(queue, &event);

        handleEvent();

        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            render();
            al_flip_display();
        }
    }
}

bool Game::initAllegro() {
    if (!al_init())
        return false;

    return true;
}

void Game::shutdownAllegro() {
    if (timer)   al_destroy_timer(timer);
    if (queue)   al_destroy_event_queue(queue);
    if (font)    al_destroy_font(font);
    if (display) al_destroy_display(display);

    timer   = nullptr;
    queue   = nullptr;
    font    = nullptr;
    display = nullptr;
}
