#pragma once

#include "header.h"

//---КОНСТАНТЫ------------------------

enum class diraction
{
    UP, DOWN, RIGHT, LEFT,
};

//-- СТРУКТУРЫ ------------------------

struct pos
{
    int x;
    int y;
};

struct rabbit
{
    pos coord;

    bool operator==(const rabbit& rabbit_1)
    {
        return rabbit_1.coord.x == coord.x && rabbit_1.coord.y == coord.y;
    }
};

struct part_body
{
    pos coord;
};

struct snake
{
    std::list<part_body> body;

    diraction course;

};

struct winsize; 

// --------------------------------------

class model 
{
    protected: // ПОЛЯ класса -----------------------

        pos center;
        winsize win_size;

    public:
        FILE * fd; // для логов

        part_body last_delete_part;

        std::list<rabbit> rabbits; 
        std::list<snake> snakes;

    //-----------------------------------------------

    protected: // МЕТОДЫ класса --------------------

        int check_rabbit( rabbit); // проверяет существует ли такой же кроллик уже

        void crawl_snake( snake&); // Перемещение змейки

    public:

        int get_ws_col();
        int get_ws_row();

        model();

        snake create_snake( int , diraction, pos); 
    
        rabbit new_rabbit();

        void update();

};