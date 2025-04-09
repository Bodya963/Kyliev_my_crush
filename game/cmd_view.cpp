#include "cmd_view.h"


cmd_view::cmd_view()
{
    setvbuf(stdout, nullptr, _IONBF, 0);

    fd[0].fd = STDIN_FILENO;
    fd[0].events = POLLIN;
    fd[0].revents = POLLIN;

    timeout = 150;

    //timeout.tv_sec = 1;
    //timeout.tv_usec = 0;
}

void cmd_view::run( view * main_view)
{
    //начальные настройки --------------
    
    controller::set_mode_ter();

    clr_win();    
    draw_frame();
    
    draw_rabbit(view_model->new_rabbit());
    draw_rabbit(view_model->new_rabbit());
    draw_rabbit(view_model->new_rabbit());

    
    
    //---------------------------------
    
    while(view_model->finish != 1)
    {
        draw( main_view );
    
        wait_input();
        
        view_model->update();
        
    }

    controller::reset_mode_ter();
    
}

void cmd_view::wait_input()
{
    auto start = std::chrono::steady_clock::now();

    int res = poll( fd, 1, timeout);

    auto end = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> diff = end - start;

    if( res != 0)
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( timeout) - diff);
        controller::movement( view_model);
    }

    // Для логов --------------------------

    // std::ofstream svo_log;
    // svo_log.open( "svo_log", std::ios::app);

    // auto end_2 = std::chrono::steady_clock::now();
    // std::chrono::duration<double> diff_2 = end_2 - start;
    // svo_log << "res = " << res << '\n';
    // svo_log << "diff_2 = " << diff_2.count() << '\n';
    
    // svo_log.close();
    
    //-------------------------------------

}

void cmd_view::draw( view * main_view)
{
    for( auto& snake: view_model->snakes)
    {
        auto change = check_snk_in_change( snake);
        if( change != view_model->changes.end())
        {
            
            draw_snake(snake, change->event_);
            
            if( change->event_ == event::eat_rabbit)
            {
                draw_rabbit( view_model->new_rabbit());
            }
            view_model->changes.erase( change);
        }
        else
        {
            draw_snake( snake, event::nothing);
        }



    for( auto& wl: view_model->walls)
    {
        draw_wall( wl);
    }


        go_to( 1, view_model->get_ws_col() - 11);
        printf("score = %d", snake.score);
    }
}

void cmd_view::draw_wall( wall& wl)
{
    for( auto& part: wl.part)
    {
        go_to( part.x, part.y);
        printf("1");
    }

    go_to( wl.last_delete.x, wl.last_delete.y);
    printf(" ");
}

void cmd_view::draw_snake(snake snake_1, event event)
{

    if( event == event::kill_snake)
    {
        for ( auto& part : snake_1.body)
        {
            go_to( part.coord.x, part.coord.y);
            printf(" ");
        }

        return;

    }

    set_color( RED);

    auto head_snake = --snake_1.body.end();
    go_to( head_snake->coord.x, head_snake->coord.y);
    printf("@");

    head_snake--;
    go_to( head_snake->coord.x, head_snake->coord.y);
    printf( "#");
    
    
    if( event == event::nothing)
    {
        go_to(view_model->last_delete_part.coord.x, view_model->last_delete_part.coord.y);
        printf(" ");
    }



    reset_color();
    
    // for( auto& part: snake_1.body)
    // {
    //     fprintf(view_model->fd ," x = %d, y = %d\n", part.coord.x, part.coord.y);
    // }
}

std::list<change>::iterator cmd_view::check_snk_in_change( snake& snk)
{
    for ( auto change = view_model->changes.begin(); change != view_model->changes.end(); change++)
    {
        
        if( change->snake_.name == snk.name)
        {
            fprintf( fd_log, "gousa\n");
            return change;
        }
    }

    return view_model->changes.end();
}

void cmd_view::go_to( int col, int row)
{
    printf("\e[%d;%dH", row, col);
}

void cmd_view::draw_rabbit( rabbit new_rabbit)
{
    go_to( new_rabbit.coord.x, new_rabbit.coord.y);

    set_color( GREEN);
    printf("Z");
    reset_color();
}

void cmd_view::draw_frame()
{
    set_color( PURPLE);

    for (int x = 1; x <= view_model->get_ws_col(); x++)
    {
        go_to( x, 1);
        printf("$");

        go_to( x, view_model->get_ws_row());
        printf("$");
    }

    for (int y = 1; y <= view_model->get_ws_row(); y++)
    {
        go_to( 1, y);
        printf("$");

        go_to( view_model->get_ws_col(), y);
        printf("$");
    }

    reset_color();
}

void cmd_view::clr_win() // clear windows
{
    printf("\e[2J");
}

void cmd_view::set_color( char * color)
{
    printf("%s", color);
}

void cmd_view::reset_color()
{
    printf("%s", RESET);
}

void cmd_view::set_fd( FILE * fd)
{
    fd_log = fd;
}