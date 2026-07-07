#pragma once

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/joystick.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Snake/player.h"
#include "Snake/fruit.h"
#include "Game.h"
#include "Snake/constants.h"


class Snake : public Game {
public:
    Snake() = default;
    ~Snake() override = default;

private:

    bool init() override;
    void handleEvent() override;
    void update() override;
    void render() override;
    Snake_Player p;
    Snake_Fruit f;

    void handleKeyboardInput(int key) override;
    void handleKeyUp(int key);
    void updateBestScore();
    void drawbackground();
    void drawScore();


    ALLEGRO_TIMER*        timerdrawsnake   = nullptr;
    ALLEGRO_TIMER*        timerspawnfruit   = nullptr;

    std::fstream readfile;
    std::fstream writefile;
    std::string bestScore = "0";
    std::string currentScore = "0";

    void initiatePic();
    ALLEGRO_BITMAP *fruitpic;

    std::vector<ALLEGRO_BITMAP*> Headpic{4};
    std::vector<ALLEGRO_BITMAP*> Tailpic{4};
    std::vector<ALLEGRO_BITMAP*> Middlepic{6};

    void ensureFileExists(std::string filename);
};
