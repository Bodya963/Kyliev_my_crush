#include "header.h"


// КЛАССЫ---------------

#include "model.h"
#include "view.h"
#include "controller.h"

// --------------------

int main( int argc, char ** argv)
{
    if( argc == 1)
    {
        printf("less argument((((((\n");
    }

    model main_model = model();
    view * main_view = get_view( argv[2]);

    main_view->set_model( &main_model);

    main_view->run();
    



    return 0;
}