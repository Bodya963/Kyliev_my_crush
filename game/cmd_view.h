#pragma once

#include "header.h"
#include "view.h"

class cmd_view: public view
{
    public:

        virtual void draw( view *);

        virtual void run( view *);

        virtual void draw_rabbit( rabbit);
        
        virtual void draw_snake( snake);
        
        void set_color( char *);
        void reset_color();

        void clr_win();

        void go_to( int , int);
};