#include "view.h"

 view * view::get_view( char * str)
{
    if( strcmp( "gui", str) == 0)
    {
        view * obj = (view *)gui_view();

        return obj;
    }

    if( strcmp( "cmd", str) == 0)
    {
        view * obj = (view *)cmd_view();

        return obj;
    }
}