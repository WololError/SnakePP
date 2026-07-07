#ifndef PLAYER_H
#define PLAYER_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <iostream>
#include <climits>
#include <string.h>

#include "Snake/constants.h"
class Snake_Fruit;

class Snake_Player{
    public:

    Snake_Player() { 
        body.push_back({configsnake::SNAKEX, configsnake::SNAKEY});                          
        body.push_back({configsnake::SNAKEX, configsnake::SNAKEY + configsnake::SNAKESIZE});     
        body.push_back({configsnake::SNAKEX, configsnake::SNAKEY + configsnake::SNAKESIZE * 2});  
        bodyDirections.resize(body.size(), {0, size});
        vx = 0;  
        vy = 0;

    }
    bool updateHead(Snake_Fruit& fruit);
    void updateBody();

    void draw(std::vector<ALLEGRO_BITMAP*> Headpic,std::vector<ALLEGRO_BITMAP*> Tailpic,std::vector<ALLEGRO_BITMAP*> Middlepic) const;
    void turn(int direction); // 0 = UP, 1 = LEFT, 2 = DOWN, 3 = RIGHT
    bool isMoving() const { return vx != 0 || vy != 0; }

    std::string getscore() { return std::to_string(body.size() - 3);}
    const std::vector<std::pair<int,int>>& getBody() const { return body;}

    private:

    void grow();
    std::vector<std::pair<int, int>> bodyDirections;

    float size = configsnake::SNAKESIZE;
    std::vector<std::pair<int,int>> body;

    float vx; 
    float vy; 

    bool directionAllowed(int direction) const;
    bool isTouchingFruit(Snake_Fruit& fruit);
    bool isDead();
    
    void drawHead(std::vector<ALLEGRO_BITMAP*> Headpic, int status) const;
    int getHeadStatut()const;

    void drawMiddle(std::vector<ALLEGRO_BITMAP*> Middlepic,int currentpart, int status)const;
    int getMiddleStatut(int currentpart)const;

    void drawTail(std::vector<ALLEGRO_BITMAP*> Tailpic,int status)const;
    int getTailStatut()const;
};

#endif

