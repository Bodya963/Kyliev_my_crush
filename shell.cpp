#include "header.h"

int main () 
{
    char buff[SIZE_BUFF] = {};

    printf("Hello my LORD ^w^\n");

    while( true)
    {
        buff[0] = '\0';  // обнуляем буффер
        int size_argv = 0; // кол=во аргументов программ в входном буффере 
        
        print_interface();    // интерфейс командной строки

        if ( fgets( buff, SIZE_BUFF, stdin) == NULL)  //читаем строчку из stdio
        {
            printf(" ошибка чтения в буфер\n");
            exit(1);
        }

        if( buff[0] == '\n') continue;       // чекаем пустою строчку
            
        printf("buff = %s\n", buff);

        nto0( buff, SIZE_BUFF);         // \n меняем на \0 в буффере

        if( buff[0] == 'q' && buff[1] == '\0') break; // q выходит из программы 

        char **my_argv = buff_split( buff, SIZE_BUFF, &size_argv);

        print_arr( my_argv, size_argv);

        // pipeline--------------

        int count_argv[size_argv] = {}; // массив с длиной аргументов для каждой программы
        int count_fantom = 0; // забей это для их подсчета 
        int index_argv_pipe = 0; // индекс программы для каждой программы
        int size_prog = 0; // кол-во программ в входном буффере

        for( int i = 0; i < size_argv; i++)
        {
            printf( " %d\n", i);
            if(  my_argv[i] == NULL)
            {
                count_argv[index_argv_pipe] = count_fantom;
                count_fantom = 0;
                index_argv_pipe++;
                size_prog++;
                break;
            }
            printf( "index_argv_pipe = %d\n", index_argv_pipe);
            if ( my_argv[i][0] == '|')
            {
                count_argv[index_argv_pipe] = count_fantom;
                count_fantom = 0;
                index_argv_pipe++;
                size_prog++;
            }
            else
            {
                count_fantom++;
            }
        }

        index_argv_pipe = 0;
        for ( int i = 0; i < size_argv; i++)
        {
            if( my_argv[i] == NULL)
            {
                break;
            }
            
            if( my_argv[i][0] == '|' )
            {
                pipe_prog(my_argv+i-count_argv[index_argv_pipe], count_argv[index_argv_pipe],  my_argv+i+1, count_argv[index_argv_pipe+1] );
                
                index_argv_pipe++;
            }
        }
        
        printf( "size_prog = %d\n", size_prog);

        if ( size_prog == 1)
        {
            char ** copy_argv = run_prog( my_argv, size_argv);
            all_free(copy_argv, size_argv);
        }

        for (size_t i = 0; i < size_prog; i++)
        {
            printf( "count_argv[%d] = %d\n", i, count_argv[i]);   /* code */
        }
        

        //-----------------------

        wait_all(size_prog);
        all_free( my_argv, size_argv);
    }

    printf("Bye bye :3\n");

    return 0;
}
