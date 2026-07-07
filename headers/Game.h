#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class Game {
protected:
    ALLEGRO_DISPLAY*      display = nullptr;
    ALLEGRO_EVENT_QUEUE*  queue   = nullptr;
    ALLEGRO_FONT*         font    = nullptr;
    ALLEGRO_TIMER*        timer   = nullptr;

    ALLEGRO_EVENT event;   

    bool running = true;
    bool redraw  = false;
    bool quit    = false;   
    

public:
    virtual ~Game();

    void run();

    virtual bool init() = 0;
    virtual void handleEvent() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    bool quitRequested() const { return quit; }

protected:
    bool initAllegro();
    void shutdownAllegro();
    virtual void handleKeyboardInput(int key) = 0;
    virtual void handleKeyUp(int key) = 0;
};
