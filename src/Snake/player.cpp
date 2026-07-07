#include "Snake/player.h"
#include "Snake/constants.h"
#include "Snake/fruit.h"

using namespace configsnake;


// #define BODY_BOTTOMLEFT_COLOR   al_map_rgb(255, 0, 0)      // rouge
// #define BODY_BOTTOMRIGHT_COLOR  al_map_rgb(0, 255, 0)      // vert
// #define BODY_HORIZONTAL_COLOR   al_map_rgb(0, 0, 255)      // bleu
// #define BODY_TOPLEFT_COLOR      al_map_rgb(255, 255, 0)    // jaune
// #define BODY_TOPRIGHT_COLOR     al_map_rgb(255, 0, 255)    // magenta
// #define BODY_VERTICAL_COLOR     al_map_rgb(0, 255, 255)    // cyan


// #define HEAD_DOWN_COLOR         al_map_rgb(255, 128, 0)    // orange
// #define HEAD_LEFT_COLOR         al_map_rgb(128, 0, 255)    // violet
// #define HEAD_RIGHT_COLOR        al_map_rgb(0, 128, 255)    // bleu clair
// #define HEAD_UP_COLOR           al_map_rgb(0, 255, 128)    // vert clair


// #define TAIL_DOWN_COLOR         al_map_rgb(160, 82, 45)    // brun
// #define TAIL_LEFT_COLOR         al_map_rgb(255, 105, 180)  // rose
// #define TAIL_RIGHT_COLOR        al_map_rgb(75, 0, 130)     // indigo
// #define TAIL_UP_COLOR           al_map_rgb(128, 128, 128)  // gris


void Snake_Player::draw(std::vector<ALLEGRO_BITMAP*> Headpic, std::vector<ALLEGRO_BITMAP*> Tailpic, std::vector<ALLEGRO_BITMAP*> Middlepic) const {
    
    drawHead(Headpic, getHeadStatut());
    
    for(int i = 1; i < body.size() - 1; ++i) {
        drawMiddle(Middlepic, i, getMiddleStatut(i));
    }
    
    drawTail(Tailpic, getTailStatut());
}

bool Snake_Player::updateHead(Snake_Fruit& fruit){
    
    if (vx == 0 && vy == 0) return true;
    
    body[0].first += vx;
    body[0].second += vy;

    if (body[0].first + size/2 > configsnake::SIZE ) body[0].first =   configsnake::SIZE -size/2;
    if (body[0].first - size/2 < 0 ) body[0].first = size/2;
    if (body[0].second + size/2 > configsnake::SIZE ) body[0].second =  configsnake::SIZE -size/2;
    if (body[0].second + size/2 - size < 0) body[0].second = size/2;

    if (isDead()) return false;

    if (isTouchingFruit(fruit)) grow();
    return true;
}

void Snake_Player::turn(int direction){

    if (!directionAllowed(direction)) return;

    switch (direction){

    case configsnake::UP:
        vx = 0;
        vy = -size;
        break;

    case configsnake::LEFT:
        vx = -size;
        vy = 0;
        break;

    case configsnake::DOWN: 
        vx = 0;
        vy = size;
        break;

    case configsnake::RIGHT:
        vx = size;
        vy = 0;
        break;

    default:
        break;
    }
}

void Snake_Player::grow(){

    std::pair<int, int> newtail{INT_MIN, INT_MIN};
    body.push_back(newtail);
    
}

void Snake_Player::updateBody(){

    for(int i = body.size() - 1; i >= 1; --i) {
        auto& currentBodyPart = body[i];     
        auto& nextBodyPart = body[i-1];      
    
        currentBodyPart.first = nextBodyPart.first;
        currentBodyPart.second = nextBodyPart.second;
        
    }
}

bool Snake_Player::isTouchingFruit(Snake_Fruit& fruit){

    bool istouchingFruit = (fruit.isHere() &&( fruit.getX() == body[0].first && fruit.getY() == body[0].second));

    if (istouchingFruit) fruit.toggleVisible();
    return istouchingFruit;
}

bool Snake_Player::isDead(){
    if (body[0].first - size/2 < 0 || body[0].first + size/2 > configsnake::SIZE) {
        return true;
    }
    if (body[0].second - size/2 < 0 || body[0].second + size/2 > configsnake::SIZE) {
        return true;
    }
    
    for(int i = 1; i < body.size() ; i++){
        if (body[0].first == body[i].first && body[0].second == body[i].second){
            return true;
        }
    }
    return false;
}

int Snake_Player::getHeadStatut() const {
    
    if (body[0].first == body[1].first && body[0].second > body[1].second )
        return HEADOWN;
    
    if (body[0].first == body[1].first && body[0].second < body[1].second )
        return HEADUP;
    
    if (body[0].first < body[1].first && body[0].second == body[1].second )
        return HEADLEFT;
    
    if (body[0].first > body[1].first && body[0].second == body[1].second )
        return HEADRIGHT;

    return HEADUP;
}

void Snake_Player::drawHead(std::vector<ALLEGRO_BITMAP*> Headpic, int status) const {
    float x1 = body[0].first - size/2;
    float y1 = body[0].second - size/2;
    float x2 = body[0].first + size/2;
    float y2 = body[0].second + size/2;

    al_draw_scaled_bitmap(Headpic[status], 0, 0, al_get_bitmap_width(Headpic[status]), al_get_bitmap_height(Headpic[status]), x1, y1, size, size, 0);

}

int Snake_Player::getTailStatut() const {
    int tail = body.size() - 1;
    int beforetail = body.size() - 2;

    if (body[tail].first == body[beforetail].first && body[tail].second > body[beforetail].second )
        return TAILDOWN;
    
    if (body[tail].first == body[beforetail].first && body[tail].second < body[beforetail].second )
        return TAILUP;
    
    if (body[tail].first < body[beforetail].first && body[tail].second == body[beforetail].second )
        return TAILLEFT;
    
    if (body[tail].first > body[beforetail].first && body[tail].second == body[beforetail].second )
        return TAILRIGHT;

    return TAILDOWN;
}

void Snake_Player::drawTail(std::vector<ALLEGRO_BITMAP*> Tailpic, int status) const {
    float x1 = body[body.size() - 1].first - size/2;
    float y1 = body[body.size() - 1].second - size/2;

    al_draw_scaled_bitmap(Tailpic[status],0, 0, al_get_bitmap_width(Tailpic[status]), al_get_bitmap_height(Tailpic[status]), x1, y1, size, size, 0);

}

int Snake_Player::getMiddleStatut(int currentpart) const {
    int prev = currentpart - 1;
    int next = currentpart + 1;
    
    int prevX = body[prev].first;
    int prevY = body[prev].second;
    int currX = body[currentpart].first;
    int currY = body[currentpart].second;
    int nextX = body[next].first;
    int nextY = body[next].second;
    
    if (prevY == currY && currY == nextY) return BODYHORIZONTAL;
    
    if (prevX == currX && currX == nextX) return BODYVERTICAL;
    

    if ((prevX < currX && nextY < currY) || (prevY < currY && nextX < currX)) 
        return BODYTOPLEFT;
    
    if ((prevX > currX && nextY < currY) || (prevY < currY && nextX > currX)) 
        return BODYTOPRIGHT;
    
    if ((prevX < currX && nextY > currY) || (prevY > currY && nextX < currX)) 
        return BODYBOTTOMLEFT;
    
    if ((prevX > currX && nextY > currY) || (prevY > currY && nextX > currX)) 
        return BODYBOTTOMRIGHT;
    
    return BODYHORIZONTAL;
}

void Snake_Player::drawMiddle(std::vector<ALLEGRO_BITMAP*> Middlepic, int currentpart, int status) const {
    float x1 = body[currentpart].first - size/2;
    float y1 = body[currentpart].second - size/2;

    al_draw_scaled_bitmap(Middlepic[status], 0, 0, al_get_bitmap_width(Middlepic[status]), al_get_bitmap_height(Middlepic[status]), x1, y1, size, size, 0);

}

bool Snake_Player::directionAllowed(int direction) const {

    if (!isMoving() && (direction != configsnake::DOWN)) return true;
    
    switch (direction) {
        case configsnake::UP:
            return vy != size;  
        
        case configsnake::DOWN:
            return vy != -size; 
        
        case configsnake::LEFT:
            return vx != size;  
        
        case configsnake::RIGHT:
            return vx != -size; 
        
        default:
            return true;
    }
}