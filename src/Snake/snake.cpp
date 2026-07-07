#include "Snake/snake.h"
#include <iostream>

bool Snake::init(){
        if (!al_install_keyboard()) {
        std::cout << "Couldn't install_keyboard" << std::endl;
        return false;
    }

    al_init_font_addon();
    al_init_primitives_addon();
    al_init_image_addon();       

    display = al_create_display(configsnake::SIZE + 2 * configsnake::EXTRA * configsnake::SNAKESIZE, configsnake::SIZE + 2 * configsnake::EXTRA * configsnake::SNAKESIZE);

    if (!display) {
        std::cout << "Couldn't create display" << std::endl;
        return false;
    }

    queue = al_create_event_queue();
    if (!queue) {
        std::cout << "Couldn't create event queue" << std::endl;
        return false;
    }


    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());

    font = al_create_builtin_font();
    if (!font) {
        std::cout << "Couldn't initiate font" << std::endl;
        return false;
    }

    timer = al_create_timer(1.0 / configsnake::SFPS);
    if (!timer) {
        std::cout << "Couldn't create timer" << std::endl;
        return false;
    }
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    timerdrawsnake = al_create_timer(1.0 / configsnake::DRAW_SNAKE);
    if (!timerdrawsnake) {
        std::cout << "Couldn't create timerdrawsnake" << std::endl;
        return false;
    }

    al_register_event_source(queue, al_get_timer_event_source(timerdrawsnake));
    al_start_timer(timerdrawsnake);

    timerspawnfruit = al_create_timer(configsnake::TIMEFRUIT);
    if (!timerspawnfruit) {
        std::cout << "Couldn't create timerspawnfruit" << std::endl;
        return false;
    }

    al_register_event_source(queue, al_get_timer_event_source(timerspawnfruit));
    al_start_timer(timerspawnfruit);

    running = true;
    redraw  = false;

    ensureFileExists("headers/Snake/bestScore.txt");
    this->readfile.open("headers/Snake/bestScore.txt", std::ios::in | std::ios::out);
    std::getline(readfile, bestScore);
    readfile.close();
    
    initiatePic();

    return true;
}

void Snake::update(){
    if (p.isMoving()) {
        p.updateBody();        
    }       
    if(!p.updateHead(f)){
        updateBestScore();
        running = false;
    } 
    f.update(p);           
}

void Snake::render() {

    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    
    al_translate_transform(&trans, configsnake::EXTRA * configsnake::SNAKESIZE, configsnake::EXTRA * configsnake::SNAKESIZE);
    al_use_transform(&trans);
    
    drawbackground();
    p.draw(Headpic, Tailpic, Middlepic);
    f.draw(fruitpic);
    
    al_identity_transform(&trans);
    al_use_transform(&trans);
    
    drawScore();
}

void Snake::handleEvent() {
    switch (event.type) {

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        quit = true;
        running = false;
        break;

    case ALLEGRO_EVENT_TIMER:
        if (event.timer.source == timerdrawsnake){
            update();
        }
        if (event.timer.source == timerspawnfruit && !f.isHere()){
            f.toggleCanSpawn();
        }
        if (event.timer.source == timer){
            redraw = true;
        }
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        handleKeyboardInput(event.keyboard.keycode);
        break;

    case ALLEGRO_EVENT_KEY_UP:
        handleKeyUp(event.keyboard.keycode);
        break;

    default:
        break;
    }
}

void Snake::handleKeyboardInput(int key) {
    switch (key) {

    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_Z:
        p.turn(configsnake::UP);
        break;
    

    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_Q:
        p.turn(configsnake::LEFT);
        break;

    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
        p.turn(configsnake::DOWN);
        break;
    
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        p.turn(configsnake::RIGHT);
        break;

    default:
        break;
    }
}

void Snake::handleKeyUp(int key) {
}

void Snake::updateBestScore(){
    writefile.open("headers/Snake/bestScore.txt", std::ios::in | std::ios::out);
    currentScore = p.getscore();
    writefile << (std::stoi(currentScore) >= std::stoi(bestScore) ? currentScore : bestScore);
    writefile.close();
}

void Snake::drawbackground(){
    al_clear_to_color(al_map_rgb(20,20,20));
    
    ALLEGRO_COLOR gridColor = al_map_rgb(0,0,0);
    
    for(int x = 0; x < configsnake::SIZE + 1; x += configsnake::SNAKESIZE){
        al_draw_line(x, 0, x, configsnake::SIZE, gridColor, 1);
    }
    
    for(int y = 0; y < configsnake::SIZE + 1; y += configsnake::SNAKESIZE){
        al_draw_line(0, y, configsnake::SIZE, y, gridColor, 1);
    }
}



void Snake::initiatePic() {

    fruitpic = al_load_bitmap("assets/Snake/fruit.png");

    for (int i = 0; i < 4; i++) {
    std::string filename = "assets/Snake/head/" + std::to_string(i) + ".png";
    Headpic[i] = al_load_bitmap(filename.c_str());
    
    if (!Headpic[i]) {
        std::cerr << "Couldn't load Head's picture" << filename << std::endl;
        exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 4; i++) {
    std::string filename = "assets/Snake/tail/" + std::to_string(i) + ".png";
    Tailpic[i] = al_load_bitmap(filename.c_str());
    
    if (!Tailpic[i]) {
        std::cerr << "Couldn't load Tail's picture" << filename << std::endl;
        exit(EXIT_FAILURE);
        }
    }   

    for (int i = 0; i < 6; i++) {
    std::string filename = "assets/Snake/body/" + std::to_string(i) + ".png";
    Middlepic[i] = al_load_bitmap(filename.c_str());
    
    if (!Middlepic[i]) {
        std::cerr << "Couldn't load Body's picture" << filename << std::endl;
        exit(EXIT_FAILURE);
        }
    }
}

void Snake::ensureFileExists(std::string filename){
    std::ifstream check(filename);
    if (!check.good()){
        std::ofstream create(filename);
        create << "0";
    }
}

void Snake::drawScore() {

    currentScore = p.getscore();

    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    
    al_scale_transform(&trans, 2.0, 2.0);
    al_use_transform(&trans);
    
    int scoreX = (2 * configsnake::SNAKESIZE + 1 * configsnake::SNAKESIZE) / 2; 
    int bestScoreX = (2 * configsnake::SNAKESIZE + 8 * configsnake::SNAKESIZE) / 2; 
    
    al_draw_text(font, al_map_rgb(255, 255, 255), scoreX, 15, ALLEGRO_ALIGN_LEFT, ("Score: " + currentScore).c_str());
    al_draw_text(font, al_map_rgb(255, 255, 255), bestScoreX, 15, ALLEGRO_ALIGN_LEFT, ("Best Score: " + (std::stoi(currentScore) >= std::stoi(bestScore) ? currentScore : bestScore)).c_str());
    
    al_identity_transform(&trans);
    al_use_transform(&trans);
}