#include "Snake/fruit.h"
#include <random>

void Snake_Fruit::draw(ALLEGRO_BITMAP *image) const{
    if (visible){
        int w = al_get_bitmap_width(image);
        int h = al_get_bitmap_height(image);

        float scale = 0.35f;
        float scaled_width = w * scale;
        float scaled_height = h * scale;

        float draw_x = position.first - scaled_width / 2.0f;
        float draw_y = position.second - scaled_height / 2.0f;

        al_draw_scaled_bitmap(image,0, 0,w, h,draw_x,draw_y,scaled_width,scaled_height,0);
    }
}

void Snake_Fruit::parsePotentialLocation(){

    int Potential_location_size = configsnake::SIZE / configsnake::SNAKESIZE;

    potentialLocation.resize(Potential_location_size);   

    for (int i = 0; i < Potential_location_size; ++i) {
        potentialLocation[i].resize(Potential_location_size);  
    }
    std::vector<int> xlocation(Potential_location_size);
    std::vector<int> ylocation(Potential_location_size);

    int locx = configsnake::SNAKESIZE/2;
    for(int i = 0 ; i < Potential_location_size; ++i){
        xlocation[i] = locx;
        locx += configsnake::SNAKESIZE;
    }

    int locy = configsnake::SNAKESIZE/2;
    for(int i = 0 ; i < Potential_location_size; ++i){
        ylocation[i] = locy;
        locy += configsnake::SNAKESIZE;
    }

    for(int i = 0; i < Potential_location_size ; ++i){
        for(int j = 0; j < Potential_location_size ; ++j){
            potentialLocation[i][j].first  = xlocation[j];
            potentialLocation[i][j].second = ylocation[i];
        }
    }
}

void Snake_Fruit::generatePosition(Snake_Player& player){

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distrib(0, potentialLocation.size() - 1);  

    int i, j;
    do {
        i = distrib(gen);
        j = distrib(gen);
        position.first  = potentialLocation[i][j].first;   
        position.second = potentialLocation[i][j].second;  
    } while (!positionAllowed(player));
}

bool Snake_Fruit::positionAllowed(Snake_Player& player) const {
    for(auto& BodyPart : player.getBody()){
        if (position == BodyPart){
            return false;
        }
    }
    return true;
}

void Snake_Fruit::update(Snake_Player& player){
    if(canspawn){
        generatePosition(player);
        visible = true;      
        canspawn = false;    
    }
}
