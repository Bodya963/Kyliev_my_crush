#include "header.h"

void print_arr( char * my_argv[], int size)
{
    for (int i = 0; i < size; i++)
        {
            printf("my_argv[%d] =%s \n", i,  my_argv[i]);
        }
}

void print_interface()
{
    char * pwd  = NULL;

    if( (pwd = getcwd( pwd, 0)) == 0) 
    {
        printf( "print_interface: get pwd is broken, bro\n");
        strcpy( pwd ,"pwd broken:");
    }

    printf( ANSI_COLOR_GREEN "%s:"  ANSI_COLOR_BLUE "~~" ANSI_COLOR_RESET "$ ", pwd);
}

int nto0( char buff[], int size)
{
    for( int i = 0; i < size; i++)
    {
        assert( i < 0 || i < size);

        if( buff[i] == '\0') break;
        if( buff[i] == '\n') buff[i] = '\0';
            
    }
    return 0;
}

int pipe_prog( char ** argv_1, int size_1, char ** argv_2, int size_2)
{
    int pipe_fd[2];

    if( pipe(pipe_fd) == -1)
    {
        printf(" in pipe_prog: pipe drop((\n");
        exit(1);
    }

    all_free( run_prog( argv_1, size_1, pipe_fd, 1), size_1);
    all_free( run_prog( argv_2, size_2, pipe_fd, 0), size_2);

    return 1;
}

char ** run_prog( char * my_argv[], int size, int* fd, int pipe_st)
{

    char **copy_argv = (char **)calloc( size+1, sizeof(char *));

    for (int i = 0; i < size; i++)
    {
        copy_argv[i] = str_cpy( my_argv[i], str_len(my_argv[i]));
    }
    
    copy_argv[size] = NULL;

    print_arr( copy_argv, size+1);
    
    if( !fork())
        { 
            printf( " cxz %d , %d, %d\n", fd[0], fd[1], pipe_st);
            printf( "%d dkdkd\n", dup2( fd[pipe_st], pipe_st)); 
            printf( "zxc %d , %d\n", pipe_st, !pipe_st);
            close( fd[ !pipe_st]);

            execvp(copy_argv[0], copy_argv);

            printf(" `%s` no such in directory\n",copy_argv[0]);
            exit(1);
        }

    return copy_argv;
}

char ** run_prog( char * my_argv[], int size)
{

    char **copy_argv = (char **)calloc( size+1, sizeof(char *));

    for (int i = 0; i < size; i++)
    {
        if( my_argv[i] == NULL) break;
        copy_argv[i] = str_cpy( my_argv[i], str_len(my_argv[i]));
    }
    
    copy_argv[size] = NULL;

    if( !fork())
        { 
            execvp(copy_argv[0], copy_argv);

            printf(" `%s` no such in directory\n",copy_argv[0]);
            exit(1);
        }

    return copy_argv;
}


char * str_cpy( char * str_buff, int count_w)
{
    char * str_argv = (char *)calloc( count_w+1, sizeof(char));

    strncpy( str_argv, str_buff, count_w);

    str_argv[count_w] = '\0';

    return str_argv;
}

void all_free(char ** myargv, int size_argv)
{
    for ( int i = 0; i < size_argv; i++)
    {
        free( myargv[i]);
    }
    free( myargv);
}

void wait_all( int size_prog)
{
    for( int i = 0; i < size_prog; i++)
    {
        wait(0);
    }
}

int str_len( char * st)
{
    int count_str = 0;

    while( st[count_str] != '\0')
    {
        count_str++;
    }

    return count_str++;
}

int argv_len( char buff[], int size)
{
    int count_argv = 1;
    for( int i = 0; i < size; i++)
    {
        if( buff[i] == ' ')
        {
            count_argv++;
        }
    }
    return count_argv;
}

char ** buff_split( char buff[], int sz, int * size_argv)
{
    *size_argv = argv_len( buff, sz) + 1;
    printf( "size_argv = %d\n", *size_argv);

    char** myargv = (char **)calloc( (*size_argv), sizeof(char *));
    int index_argv = 0;
    int count_w = 0;

    for( int i = 0; i < SIZE_BUFF; i++)
    {
        assert( 0 <= i < SIZE_BUFF);

        if(index_argv == ((*size_argv)-1))break;

        if( buff[i] == ' ' || buff[i] == '\0')
        {
            myargv[index_argv] = str_cpy( &buff[i-count_w], count_w );
            //printf(" myargv[]")
            count_w = 0;
            index_argv++;
        }        
        else
            count_w++;
        if(buff[i] == '\0') break;
    }
    myargv[ (*size_argv)-1] = NULL;

    return myargv;

}