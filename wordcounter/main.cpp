#include "header.h"

//classes

#include "floy.h"
#include "parser.h"
#include "library.h"


int main( int argc, char ** argv)
{
    if( argc == 1)
    {
        struct floy * floy1 = floy_create_stdin( );
        struct parser * parser1 = parser_create();
        struct library * library1 = library_create();

        floy_readln( floy1);
        
        while( floy_get_first( floy1) != '\n')
        {
            
            printf(" first = %c\n", floy_get_first( floy1));

            char ** words = parser_split( parser1, floy1);
            
            for( int i = 0; i < parser_get_size(parser1); i++)
            {
                library_push( library1, words[i]);
            }

            all_free( words);


            floy_readln( floy1);
        }

        library_print(library1);

        floy_delete( floy1);
        parser_delete( parser1);
        library_delete( library1);

    }
    else
    {
        struct floy * floys[argc -1] = {};

        struct parser * parser1 = parser_create();
        struct library * library1 = library_create();

        for( int i = 0; i < (argc - 1); i++)
        {
            floys[i] = floy_create( argv[i+1]);
        }

        int check_EOF = 0;

        while(true)
        {
            check_EOF = 0;

            for( int i = 0; i < argc-1; i++)
            {
                if( floy_readln( floys[i]) == EOF)
                {
                    check_EOF++;
                    continue;
                }

                char ** words = parser_split( parser1, floys[i]);

                for ( int j = 0; j < parser_get_size(parser1); j++)
                {
                    library_push( library1, words[j]);
                }

                all_free(words);
            }

            if( check_EOF == argc-1)
            {
                break;
            }
        }

        library_print(library1);

        library_delete( library1);
        parser_delete( parser1);

        for( int i = 0; i < argc-1; i++)
        {
            floy_delete( floys[i]);
        }
    }

    return 0;
}

void all_free(char ** words)
{
    for ( int i = 0; i < (sizeof(words)/sizeof(words[0])); i++)
    {
        free(words[i]);
    }

    free( words);
}