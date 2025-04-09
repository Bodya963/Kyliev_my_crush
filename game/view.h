#pragma once

#include "header.h"
#include "model.h"

class cmd_view;
class gui_view;

class view
{
    protected:

        model * view_model;

    public:
    
        static view * get_view( char *);
    
        void set_model( model *);

        virtual void run( view *) = 0;

        virtual void draw(view *) = 0; 

        virtual void draw_snake( snake, event) = 0;

        virtual void draw_rabbit( rabbit) = 0;

        virtual void set_fd( FILE *) = 0;

        virtual ~view() ;
};