#include "controller.h"

termios controller::old_termios_p;
termios controller::new_termios_p;

FILE* controller::fd_log = nullptr;

void controller::get_attr()
{
    tcgetattr( STDIN_FILENO, &old_termios_p);
}

void controller::set_mode_ter()
{
    get_attr();

    tcgetattr( STDIN_FILENO, &new_termios_p);

    cfmakeraw(&new_termios_p);
    tcsetattr( STDIN_FILENO, TCSANOW, &new_termios_p);

    //fprintf(fd_log, "gouda svo z\n");
}

void controller::reset_mode_ter( )
{
    tcsetattr( STDIN_FILENO, TCSANOW, &old_termios_p);
}

void controller::movement( model * obj_model)
{
    char input = 0;

    read( STDIN_FILENO, &input, 1);

    switch (input)
    {
    case 'w':
        obj_model->change_course( (obj_model->snakes).begin(), diraction::UP);
        break;

    case 's':
        obj_model->change_course( (obj_model->snakes).begin(), diraction::DOWN);
        break;

    case 'd':
        obj_model->change_course( (obj_model->snakes).begin(), diraction::RIGHT);
        break;

    case 'a':
        obj_model->change_course( (obj_model->snakes).begin(), diraction::LEFT);
        break;

    default:
        break;
    }
}