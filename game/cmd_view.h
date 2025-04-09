#pragma once

#include "header.h"
#include "view.h"
#include "controller.h"

class cmd_view: public view
{

    private:
        
        pollfd fd[1];
        int timeout;

        // fd_set readfds, writefds, exceptfds;
        // timeval timeout;



    public:
        cmd_view();

        //void reset_fds();

        virtual void draw( view *);

        virtual void run( view *);

        virtual void draw_rabbit( rabbit);
        
        virtual void draw_snake( snake, event);

        void draw_frame(); // рисует рамку

        void draw_wall( wall& );

        std::list<change>::iterator check_snk_in_change( snake& );

        void wait_input();

        void set_color( char *);
        void reset_color();


        void clr_win();

        void go_to( int , int);

        FILE * fd_log;
        void set_fd(FILE *);
};