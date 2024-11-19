#include "header.h"

int main () 
{
    char buff[SIZE_BUFF] = {};

    printf("Hello my LORD ^w^\n");

    while( true)
    {
        buff[0] = '\0';  // обнуляем буффер

        print_interface();    // интерфейс командной строки

        if ( fgets( buff, SIZE_BUFF, stdin) == NULL)  //читаем строчку из stdio
        {
            printf(" ошибка чтения в буфер\n");
            exit(1);
        }

        if( buff[0] == '\n') continue;       // чекаем пустою строчку
            
        //printf("buff = %s\n", buff);

        nto0( buff, SIZE_BUFF);         // \n меняем на \0 в буффере

        if( buff[0] == 'q' && buff[1] == '\0') break;

        char **my_argv = buff_split( buff, SIZE_BUFF);

        // for (int i = 0; i < SIZE_ARGV; i++)
        // {
        //     printf("my_argv[%d] =%s \n", i,  my_argv[i]);
        // }

        if( !fork())
        { 
            execvp(my_argv[0], my_argv);

            printf(" `%s` no such in directory\n", my_argv[0]);
            exit(1);
        }

        wait(0);
        all_free( my_argv);
    }

    printf("Bye bye :3\n");

    return 0;
}
