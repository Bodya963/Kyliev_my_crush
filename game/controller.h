#pragma once 

#include "header.h"
#include "model.h"

class controller 
{
    private:
    
        static termios old_termios_p;
        static termios new_termios_p;
        
        public:
        
        static void get_attr();
        
        static void set_mode_ter();
        
        static void reset_mode_ter();
        
        static FILE * fd_log;
    
        static void movement( model *);

};