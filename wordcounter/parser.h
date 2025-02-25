#pragma once

#include "header.h"
#include "floy.h"

struct parser;

struct parser * parser_create();
char **  parser_split( struct parser *,  struct floy *); // аналог split в питоне
void parser_delete( struct parser *);
int parser_get_size( struct parser* );