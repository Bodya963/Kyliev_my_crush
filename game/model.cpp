#include "model.h"


// Конструктор ------------------------------

model::model()
{
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &win_size); // получаю размер окна терминала

    center = { win_size.ws_col/2, win_size.ws_row/2};

   // win_size.ws_col--;
   // win_size.ws_row--;
    
    diraction course = diraction::RIGHT;
    snakes.push_back( create_snake( 5, course, center));

    fd = fopen("log", "w");
    srand( time(0));
}

int model::get_ws_col()
{
    return win_size.ws_col;
}

int model::get_ws_row()
{
    return win_size.ws_row;
}
//-------------------------------------------

snake model::create_snake( int size, diraction course, pos start_pos) // создает змейку размера size с напралениеи course 
{                                                                      // и с начально точкой start_pos
    snake new_snake;

    new_snake.course = course;

    for( int i = 0; i < size; i++)
    {
        part_body small_body;
        small_body.coord.x = start_pos.x - i;           // последний элемент это голова змеи
        small_body.coord.y = start_pos.y ;

        new_snake.body.push_front( small_body);
    }

    return new_snake;
}

rabbit model::new_rabbit()
{
    rabbit new_rabbit;
    
    while(true)
    {
        new_rabbit.coord.x = 2 + (rand() % (win_size.ws_col - 1 - 2 + 1));
        new_rabbit.coord.y = 2 + (rand() % (win_size.ws_row - 1 - 2 + 1));
        
        if( check_rabbit( new_rabbit))
        {
            fprintf( fd, "rabbit: x = %d. y = %d\n", new_rabbit.coord.x, new_rabbit.coord.y);
            rabbits.push_back(new_rabbit);
            return new_rabbit;
        }
    }
}

int model::check_rabbit( rabbit rabbit_1)
{
    if( std::find(begin(rabbits), end(rabbits), rabbit_1 ) == end(rabbits))
    {
        return true;
    }
    return false;
}

void model::crawl_snake( snake& snake_1)
{
    part_body body_1;
    auto head_snake = snake_1.body.begin();
    std::advance(head_snake, snake_1.body.size() - 1);

    switch (snake_1.course)
    {
    case diraction::UP:
        body_1.coord.x = head_snake->coord.x ;
        body_1.coord.y = head_snake->coord.y + 1; 

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        snake_1.body.erase(snake_1.body.begin());
        break;

    case diraction::DOWN:
        body_1.coord.x = head_snake->coord.x ;
        body_1.coord.y = head_snake->coord.y - 1;     

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        snake_1.body.erase(snake_1.body.begin());
        break;

    case diraction::LEFT:
        body_1.coord.x = head_snake->coord.x - 1;
        body_1.coord.y = head_snake->coord.y; 

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        snake_1.body.erase(snake_1.body.begin());
        break;

    case diraction::RIGHT:
        body_1.coord.x = head_snake->coord.x +1 ;
        body_1.coord.y = head_snake->coord.y; 

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        snake_1.body.erase(snake_1.body.begin());

        // for( auto& gouda: snake_1.body)
        // fprintf(fd , "svo : x = %d, y = %d\n", gouda.coord.x, gouda.coord.y);
        break;
    }
}

void model::update()
{
    for( auto& snake: snakes )
    {
        crawl_snake( snake);
    }

}