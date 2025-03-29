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

    finish = 0;

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
    new_snake.score = 0;

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
            fprintf( fd_log, "rabbit: x = %d. y = %d\n", new_rabbit.coord.x, new_rabbit.coord.y);
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

void model::crawl_snake( snake& snake_1, event event)
{
    part_body body_1;
    auto head_snake = snake_1.body.begin();
    std::advance(head_snake, snake_1.body.size() - 1);

    switch (snake_1.course)
    {
    case diraction::UP:
        body_1.coord.x = head_snake->coord.x ;
        body_1.coord.y = head_snake->coord.y - 1; 

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        if( event == event::nothing)
        {
            snake_1.body.erase(snake_1.body.begin());
        }
        break;

    case diraction::DOWN:
        body_1.coord.x = head_snake->coord.x ;
        body_1.coord.y = head_snake->coord.y + 1;     

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        if( event == event::nothing)
        {
            snake_1.body.erase(snake_1.body.begin());
        }
        break;

    case diraction::LEFT:
        body_1.coord.x = head_snake->coord.x - 1;
        body_1.coord.y = head_snake->coord.y; 

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        if( event == event::nothing)
        {
            snake_1.body.erase(snake_1.body.begin());
        }
        break;

    case diraction::RIGHT:
        body_1.coord.x = head_snake->coord.x +1 ;
        body_1.coord.y = head_snake->coord.y; 

        snake_1.body.push_back(body_1);

        last_delete_part.coord.x = snake_1.body.begin()->coord.x;
        last_delete_part.coord.y = snake_1.body.begin()->coord.y;

        if( event == event::nothing)
        {
            snake_1.body.erase(snake_1.body.begin());
        }
        // for( auto& gouda: snake_1.body)
        // fprintf(fd , "svo : x = %d, y = %d\n", gouda.coord.x, gouda.coord.y);
        break;
    }
}

void model::update()
{
    for( auto& snake: snakes )
    {
        pos next_block = get_forward_block( snake);
        
        if( check_block_for_finish( next_block))
        {
            finish = 1; //конец игры 
            return;
        }

        if( check_block_for_z( next_block))
        {
            snake.score++;
            change new_change;
            new_change.event_ = event::eat_rabbit;
            new_change.snake_ = snake;

            changes.push_back(new_change);
            crawl_snake( snake, event::eat_rabbit);
        }

        crawl_snake( snake, event::nothing);

    }

}

int model::check_block_for_finish( pos block)
{
    if( (block.x == win_size.ws_col) or (block.x == 1) or (block.y == win_size.ws_row) or (block.y == 1))
    {
        return 1;
    }

    int flag = 0;
    
    for (snake snake1 : snakes)
    {
        flag = 0;

        for ( auto& part: snake1.body)
        {
            if( part.coord.x == block.x and part.coord.y == block.y)
            {
                flag = 1;
                break;
            }
        }    

        if (flag)
        {
            break;
        }
    }

    if(flag)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int model::check_block_for_z( pos block)
{
    rabbit if_rabbit;
    if_rabbit.coord.x = block.x;
    if_rabbit.coord.y = block.y;
    
    if( find( rabbits.begin(), rabbits.end(), if_rabbit) != rabbits.end())
    {
        return 1;
    }

    return 0;

}

void model::change_course( std::list<snake>::iterator snk, diraction new_course)
{
    

    switch ( new_course)
    {
    case diraction::UP:
        if (snk->course == diraction::DOWN)
        {
            return;
        }
        break;

    case diraction::DOWN:
        if (snk->course == diraction::UP)
        {
            return;
        }
        break;

    case diraction::LEFT:
        if (snk->course == diraction::RIGHT)
        {
            return;
        }
        break;

    case diraction::RIGHT:
        if (snk->course == diraction::LEFT)
        {
            return;
        }
        break;    

    default:
        break;
    }

    snk->course = new_course;
}


pos model::get_forward_block( snake& snk)
{
    pos next_block;
    auto head_snake = snk.body.begin();
    std::advance(head_snake, snk.body.size() - 1);

    switch ( snk.course)
    {
        case diraction::UP:
            next_block.x = head_snake->coord.x;
            next_block.y = head_snake->coord.y - 1;
            break;

        case diraction::DOWN:
            next_block.x = head_snake->coord.x;
            next_block.y = head_snake->coord.y + 1;
            break;

        case diraction::LEFT:
            next_block.x = head_snake->coord.x - 1;
            next_block.y = head_snake->coord.y;
            break;

        case diraction::RIGHT:
            next_block.x = head_snake->coord.x + 1;
            next_block.y = head_snake->coord.y;
            break;

    }  
    
    return next_block;
}

void model::set_fd( FILE * fd )
{
    fd_log = fd;
}