#ifndef SNAKE_FRUIT_H
#define SNAKE_FRUIT_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <iostream>
#include <random>

#include "Snake/constants.h"
#include "Snake/player.h"

class Snake_Fruit{
    public:

    Snake_Fruit() { parsePotentialLocation(); color = al_map_rgb(255, 0, 255); position.first = 0; position.second = 0;}

    void update(Snake_Player& player);
    void draw(ALLEGRO_BITMAP *image) const;

    int getX() { return position.first; }
    int getY() { return position.second; }

    bool isHere() {return visible;}
    void toggleCanSpawn() { canspawn = !canspawn;}
    void toggleVisible() { visible = !visible;}

    private:

    int radius = configsnake::FRUITSIZE;
    std::pair<int,int> position;
    ALLEGRO_COLOR color;
    std::vector<std::vector<std::pair<int,int>>> potentialLocation;

    bool visible = false;
    bool canspawn = true;

    void parsePotentialLocation();
    void generatePosition(Snake_Player& p);
    bool positionAllowed(Snake_Player& p)const;

};





#endif