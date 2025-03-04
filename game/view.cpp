#include "view.h"
#include "cmd_view.h"
#include "gui_view.h"

 view * view::get_view( char * str)
{
    if( strcmp( "gui", str) == 0)
    {
        //gui_view * obj = new gui_view;
        printf("gui not working yet, sorry\n");
        //return (view *)obj;
    }

    if( strcmp( "cmd", str) == 0)
    {
        cmd_view * obj = new cmd_view;

        printf("svo\n");

        return (view *)obj;
    }

   return nullptr;
}


void view::set_model( model * m)
{
    view_model = m;
}