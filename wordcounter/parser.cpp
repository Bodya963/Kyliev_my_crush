
#include "parser.h" 


struct floy
{
    char * name;
    char * buff;
    size_t size;
    FILE * fd;
};


struct parser
{
    int max_words;
};

struct parser * parser_create()
{
    struct parser * parser1 = (struct parser *)calloc( 1, sizeof(struct parser));

    parser1->max_words = 60;

    return parser1;
}

char ** parser_split( struct parser * parser1, struct floy * floy1)
{
    parser1->max_words = 1;

    for (int i = 0; i < floy1->size; i++)
    {
        if( floy1->buff[i] == ' ')
        {
            parser1->max_words = parser1->max_words + 1;
        }
    }

    char ** words = (char **)calloc( parser1->max_words, sizeof(char *));

    int size_word = 0;
    int num_word = 0;

    for (int i = 0; i < floy1->size; i++)
    {
        if( floy1->buff[i] == ' ' or floy1->buff[i] == '\n')
        {
            words[num_word] = (char *)calloc(size_word+1, 1);
            words[num_word][size_word] = '\0';

            floy1->buff[i] = '\0';

            strcpy( words[num_word], &(floy1->buff[i-size_word]));

            num_word++;
            size_word = 0;
        }
        else
        {
            size_word++;
        }
    }

    // for( int i = 0 ; i< parser1->max_words; i++)
    // {
    //     printf(" i[%d] = %s\n", i, words[i]);
    // }

    return words;
}

int parser_get_size( struct parser * parser1)
{
    return parser1->max_words;
}

void parser_delete( struct parser * parser1)
{
    free( parser1);
}