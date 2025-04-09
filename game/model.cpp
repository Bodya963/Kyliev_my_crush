#include "model.h"


// Конструктор ------------------------------

model::model()
{
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &win_size); // получаю размер окна терминала

    center = { win_size.ws_col/2, win_size.ws_row/2};

   // win_size.ws_col--;
   // win_size.ws_row--;
    
    create_snake( 2, diraction::RIGHT, center);
    
    pos start_wall;
    start_wall.x = 10;
    start_wall.y = 20;
    create_wall( 3, diraction::RIGHT, start_wall, 20 );

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

void model::create_snake( int size, diraction course, pos start_pos) // создает змейку размера size с напралениеи course 
{                                                                      // и с начально точкой start_pos

    snake new_snake;

    new_snake.course = course;
    new_snake.score = 0;
    new_snake.name = snakes.size() + 1;

    for( int i = 0; i < size; i++)
    {
        part_body small_body;
        small_body.coord.x = start_pos.x - i;           // последний элемент это голова змеи
        small_body.coord.y = start_pos.y ;

        new_snake.body.push_front( small_body);
    }

    snakes.push_back( new_snake);

}

// void model::create_bot( int size, diraction course, pos start_pos, bool smart)
// {
//     snake new_snake = 7create_snake( size, course, start_pos);

//     snakes.push_back( new_snake);


// }

void model::create_wall( int size, diraction course, pos start_pos, int size_move)
{

    wall new_wall;

    new_wall.start_.x = start_pos.x;
    new_wall.start_.y = start_pos.y;

    auto last_part = new_wall.part.begin();

    switch( course)
    {
        case diraction::UP:
            
            for( int i = 0; i < size; i++)
            {
                pos part;
                part.x = start_pos.x;
                part.y = start_pos.y - i;

                new_wall.part.push_back( part);
            }

            last_part = --new_wall.part.end();
            new_wall.end_.y = last_part->y - size_move;
            new_wall.end_.x = last_part->x;

            new_wall.course = diraction::DOWN;

            break;

        case diraction::DOWN:

            
            for( int i = 0; i < size; i++)
            {
                pos part;
                part.x = start_pos.x;
                part.y = start_pos.y + i;

                new_wall.part.push_back( part);
            }

            last_part = --new_wall.part.end();
            new_wall.end_.y = last_part->y + size_move;
            new_wall.end_.x = last_part->x;

            new_wall.course = diraction::UP;

            break;

        case diraction::LEFT:

                
            for( int i = 0; i < size; i++)
            {
                pos part;
                part.x = start_pos.x - i;
                part.y = start_pos.y;

                new_wall.part.push_back( part);
            }

            last_part = --new_wall.part.end();
            new_wall.end_.y = last_part->y;
            new_wall.end_.x = last_part->x - size_move;

            new_wall.course = diraction::RIGHT;

            break;

        case diraction::RIGHT:

            
            for( int i = 0; i < size; i++)
            {
                pos part;
                part.x = start_pos.x + 1;
                part.y = start_pos.y;

                new_wall.part.push_back( part);
            }

            last_part = --new_wall.part.end();
            new_wall.end_.y = last_part->y;
            new_wall.end_.x = last_part->x + size_move;

            new_wall.course = diraction::RIGHT;

            break;
    };

    walls.push_back( new_wall);

}

void model::move_wall( wall& wl)
{

    switch (wl.course)
    {
    case diraction::UP:
        if( wl.start_.x == wl.part.begin()->x and wl.start_.y == (wl.part.begin())->y)
        {
            wl.course = diraction::DOWN;
        }
        break;

    case diraction::DOWN:
        if( wl.end_.x == (--wl.part.end())->x and wl.end_.y == (--wl.part.end())->y)
        {
            wl.course = diraction::UP;
        }
        break;

    case diraction::LEFT:
        if( wl.start_.x == wl.part.begin()->x and wl.start_.y == (wl.part.begin())->y)
        {
            wl.course = diraction::RIGHT;
        }
        break;

    case diraction::RIGHT:
        if( wl.end_.x == (--wl.part.end())->x and wl.end_.y == (--wl.part.end())->y)
        {
            wl.course = diraction::LEFT;
        }
        break;
    
    default:
        break;
    }

    pos body_1;
    auto head_wall = wl.part.begin();

    switch (wl.course)
    {
    case diraction::UP:

        head_wall = wl.part.begin();

        body_1.x = head_wall->x ;
        body_1.y = head_wall->y - 1; 

        wl.part.push_front(body_1);
    
        wl.last_delete.x = (--wl.part.end())->x;
        wl.last_delete.y = (--wl.part.end())->y;

        wl.part.erase(--wl.part.end());
        
        break;

    case diraction::DOWN:
            
        head_wall = --wl.part.end();
        
        body_1.x = head_wall->x ;
        body_1.y = head_wall->y + 1; 

        wl.part.push_back(body_1);

        wl.last_delete.x = wl.part.begin()->x;
        wl.last_delete.y = wl.part.begin()->y;

        wl.part.erase(wl.part.begin());
        break;

    case diraction::LEFT:
            
        body_1.x = head_wall->x - 1 ;
        body_1.y = head_wall->y; 

        wl.part.push_front(body_1);

        wl.last_delete.x = (--wl.part.end())->x;
        wl.last_delete.y = (--wl.part.end())->y;

        wl.part.erase(--wl.part.end());
        break;

    case diraction::RIGHT:
            
        head_wall = --wl.part.end();

        body_1.x = head_wall->x + 1 ;
        body_1.y = head_wall->y; 

        wl.part.push_back(body_1);

        wl.last_delete.x = (wl.part.begin())->x;
        wl.last_delete.y = wl.part.begin()->y;

        wl.part.erase(wl.part.begin());
        // for( auto& gouda: snake_1.body)
        // fprintf(fd , "svo : x = %d, y = %d\n", gouda.coord.x, gouda.coord.y);
        break;
    }
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

        
        if( event == event::nothing)
        {
            last_delete_part.coord.x = snake_1.body.begin()->coord.x;
            last_delete_part.coord.y = snake_1.body.begin()->coord.y;

            snake_1.body.erase(snake_1.body.begin());
        }
        break;

    case diraction::DOWN:
        body_1.coord.x = head_snake->coord.x ;
        body_1.coord.y = head_snake->coord.y + 1;     

        snake_1.body.push_back(body_1);

        
        if( event == event::nothing)
        {
            last_delete_part.coord.x = snake_1.body.begin()->coord.x;
            last_delete_part.coord.y = snake_1.body.begin()->coord.y;

            snake_1.body.erase(snake_1.body.begin());
        }
        break;

    case diraction::LEFT:
        body_1.coord.x = head_snake->coord.x - 1;
        body_1.coord.y = head_snake->coord.y; 

        snake_1.body.push_back(body_1);

        
        if( event == event::nothing)
        {
            last_delete_part.coord.x = snake_1.body.begin()->coord.x;
            last_delete_part.coord.y = snake_1.body.begin()->coord.y;

            snake_1.body.erase(snake_1.body.begin());
        }
        break;

    case diraction::RIGHT:
        body_1.coord.x = head_snake->coord.x +1 ;
        body_1.coord.y = head_snake->coord.y; 

        snake_1.body.push_back(body_1);

        
        if( event == event::nothing)
        {
            last_delete_part.coord.x = snake_1.body.begin()->coord.x;
            last_delete_part.coord.y = snake_1.body.begin()->coord.y;

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

        auto check_z = check_block_for_z( next_block);
        if(  check_z != rabbits.end())
        {
            snake.score++;
            
            change new_change;
            new_change.event_ = event::eat_rabbit;
            new_change.snake_ = snake;

            changes.push_back(new_change);
            crawl_snake( snake, event::eat_rabbit);

            rabbits.erase( check_z);

            return ;
        }

        crawl_snake( snake, event::nothing);

    }

    for( auto& wl: walls)
    {
        move_wall( wl);
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
        
        for( auto& wl: walls)
        {
            for ( auto& wl_part: wl.part )
            {
                if ( wl_part.x == block.x and wl_part.y == block.y)
                {
                    flag = 1;
                    break;
                }
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

std::list<rabbit>::iterator model::check_block_for_z( pos block)
{
    rabbit if_rabbit;
    if_rabbit.coord.x = block.x;
    if_rabbit.coord.y = block.y;

    return std::find( rabbits.begin(), rabbits.end(), if_rabbit);

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