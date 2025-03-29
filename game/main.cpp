#include "header.h"


// КЛАССЫ---------------

#include "model.h"
#include "view.h"
#include "controller.h"

// --------------------

int main( int argc, char ** argv)
{
    FILE * fd_log = nullptr;

    fd_log = fopen("log", "w");

    if( argc < 2 )
    {
        printf("less argument((((((\n");
        exit(1);
    }

    model main_model;
    controller main_controller;
    //printf("argv = %s, center = (%d, %d), win_size = ( %d, %d)\n",argv[1],  main_model.center.x, main_model.center.y, main_model.win_size.ws_col, main_model.win_size.ws_row);

    view * main_view = view::get_view( argv[1]);

    main_model.set_fd( fd_log);
    main_view->set_fd( fd_log);

    controller::fd_log = fd_log;

    main_view->set_model( &main_model);

    main_view->run(main_view);

    
    fclose(fd_log); 

    delete main_view;

    return 0;
}