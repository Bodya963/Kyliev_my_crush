#include "header.h"

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


char * str_cpy( const char * str_buff, int count_w)
{
    char * str_argv = (char *)calloc( count_w+1, sizeof(char));

    strncpy( str_argv, str_buff, count_w);

    str_argv[count_w] = '\0';

    return str_argv;
}

void all_free(char ** myargv)
{
    for ( int i = 0; i < SIZE_ARGV; i++)
    {
        free( myargv[i]);
    }
    free( myargv);
}

char ** buff_split( char buff[], int sz)
{
    char** myargv = (char **)calloc( SIZE_ARGV, sizeof(char *));
    int index_argv = 0;
    int count_w = 0;

    for( int i = 0; i < SIZE_BUFF; i++)
    {
        assert( 0 <= i < SIZE_ARGV);

        if(index_argv == (SIZE_ARGV - 1))break;

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
    myargv[ SIZE_ARGV - 1] = NULL;

    return myargv;

}