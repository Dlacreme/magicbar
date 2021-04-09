#ifndef parser_h
#define parser_h

#include "config.h"

typedef struct s_config_parser_item {
    char* key;
    void (*handler)(t_config*, char*);
    struct s_config_parser_item* next;
} t_config_parser_item;


#endif