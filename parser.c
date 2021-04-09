#include "include/magic_bar.h"

void    default_handler(t_config*, char*);
void    submit_handler(t_config*, char*);
void    favorite_handler(t_config*, char*);

char    *map_key(const char* key)
{
    char *res = malloc(sizeof(char) * strlen(key) + 1);
    strcpy(res, key);
    return res;
}

t_config_parser_item    *get_parser_item(const char *key, void(*handler)(t_config*, char*))
{
    t_config_parser_item *item;
    item = malloc(sizeof(t_config_parser_item));
    item->key = map_key(key);
    item->handler = handler;
    item->next = NULL;
    return item;
}

t_config_parser_item    *get_parser()
{
    t_config_parser_item    *def;
    t_config_parser_item    *submit;
    t_config_parser_item    *favorite;
    def = get_parser_item("default:", &default_handler);
    submit = get_parser_item("submit:", &submit_handler);
    favorite = get_parser_item("->", &favorite_handler);
    def->next = submit;
    submit->next = favorite;
    return def;
}


void default_handler(t_config *config, char *line)
{
    printf("Handler default");
    return;
}

void submit_handler(t_config *config, char *line)
{
    printf("Handle submit");
    return;
}

void favorite_handler(t_config *config, char *line)
{
    printf("Handle favorite");
    return;
}