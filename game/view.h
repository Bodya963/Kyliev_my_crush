#pragma once

#include "header.h"

class view
{
    public:
    {
        static view * get_view( char *);

    
        void set_model( model *);
    

        virtual void run(void);
    }
};