#pragma once

#include "header.h"

//---КОНСТАНТЫ------------------------

enum class diraction
{
    UP, DOWN, RIGHT, LEFT,
};

enum class event
{
    eat_rabbit,
    kill_snake,
    nothing
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
    int name;

    std::list<part_body> body;

    diraction course;

    int score;

    bool operator==(const snake& snake_1)
    {
        auto tail = (snake_1.body).begin();
        return (tail->coord.x == body.begin()->coord.x) and (tail->coord.y == body.begin()->coord.y); 
    }

};

struct wall
{
    std::list<pos> part;

    pos start_;                // крайние положение стены
    pos end_;

    diraction course;

    pos last_delete;
};

struct change
{
    snake snake_;
    event event_;

    bool operator==(const change& change_1)
    {
        return snake_ == change_1.snake_;
    }
};

struct winsize; 

// --------------------------------------

class model 
{
    protected: // ПОЛЯ класса -----------------------

        pos center;
        winsize win_size;

    public:
        FILE * fd_log;

        part_body last_delete_part;

        std::list<rabbit> rabbits; 
        std::list<snake> snakes;
        std::list<change> changes;
        //std::list<bot> bots;
        std::list<wall> walls;

        int finish; // 0 - игра продолжается 1 - конец игры

    //-----------------------------------------------

    protected: // МЕТОДЫ класса --------------------

        int check_rabbit( rabbit); // проверяет существует ли такой же кроллик уже

        void crawl_snake( snake&, event); // Перемещение змейки

        void move_wall( wall&);

    public:

        void set_fd( FILE *);

        int get_ws_col();
        int get_ws_row();

        model();

        void create_snake( int , diraction, pos); 
        void create_bot( int, diraction, pos, bool);
        void create_wall( int, diraction, pos, int); 
    
        rabbit new_rabbit();

        void update();

        void change_course( std::list<snake>::iterator,  diraction);

        pos get_forward_block( snake&); // получаем следующий блок перед головой смейки

        int check_block_for_finish( pos ); // Проверяет закончилась игра если змейка пойдет в следующий блок

        std::list<rabbit>::iterator  check_block_for_z( pos); // проверяет сьела ли змейка зайча если пойдет в следующщий блок

};

// class bot:
// {
//     public:
//         snake& snake_;

//         std::vector<diraction> choices;

//         bool smart; // тупой или умный  бот

// };