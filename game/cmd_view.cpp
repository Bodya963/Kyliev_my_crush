#include "cmd_view.h"

void cmd_view::run( view * main_view)
{
    clr_win();
 
    
    int i = 0;
    while(true)
    {
        if( i == 10) break;
        draw( main_view );
        
        rabbit new_rabbit = view_model->new_rabbit();
        draw_rabbit(new_rabbit);

        view_model->update();
        getchar();
        i++;
    }
    
}

void cmd_view::draw( view * main_view)
{
    for( auto& snake: view_model->snakes)
    {
        draw_snake(snake);
    }
}

void cmd_view::draw_snake(snake snake_1)
{
    set_color( RED);

    for(auto& part_body: snake_1.body)
    {
        go_to(part_body.coord.x, part_body.coord.y);
        printf("#");
    }
    
    go_to(view_model->last_delete_part.coord.x, view_model->last_delete_part.coord.y);
    printf(" ");
    
    auto head_snake = --snake_1.body.end();
    go_to( head_snake->coord.x, head_snake->coord.y);
    printf("@");

    reset_color();
    
    // for( auto& part: snake_1.body)
    // {
    //     fprintf(view_model->fd ," x = %d, y = %d\n", part.coord.x, part.coord.y);
    // }
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