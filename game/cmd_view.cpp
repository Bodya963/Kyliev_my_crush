#include "cmd_view.h"


cmd_view::cmd_view()
{
    setvbuf(stdout, nullptr, _IONBF, 0);

    fd[0].fd = STDIN_FILENO;
    fd[0].events = POLLIN;
    fd[0].revents = POLLIN;

    timeout = 200;

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
        if( check_snk_in_change( snake))
        {
            draw_snake(snake, event::eat_rabbit);

            draw_rabbit( view_model->new_rabbit());
        }
        else
        {
            draw_snake( snake, event::nothing);
        }


        go_to( 1, view_model->get_ws_col() - 11);
        printf("score = %d", snake.score);
    }
}

void cmd_view::draw_snake(snake snake_1, event event)
{
    set_color( RED);

    for(auto& part_body: snake_1.body)
    {
        go_to(part_body.coord.x, part_body.coord.y);
        printf("#");
    }
    
    if( event == event::nothing)
    {
        go_to(view_model->last_delete_part.coord.x, view_model->last_delete_part.coord.y);
        printf(" ");
    }
    
    auto head_snake = --snake_1.body.end();
    go_to( head_snake->coord.x, head_snake->coord.y);
    printf("@");

    reset_color();
    
    // for( auto& part: snake_1.body)
    // {
    //     fprintf(view_model->fd ," x = %d, y = %d\n", part.coord.x, part.coord.y);
    // }
}

int cmd_view::check_snk_in_change( snake& snk)
{
    for ( auto& change : view_model->changes)
    {
        auto tail = ++(snk.body).begin() ;

        if( (tail->coord.x == (++change.snake_.body.begin())->coord.x) and (tail->coord.y == (++change.snake_.body.begin())->coord.y) )
        {
            fprintf( fd_log, "gousa\n");
            return 1;
        }
    }

    return 0;
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