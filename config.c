#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "include/magic_bar.h"

t_config_parser_item    *get_parser();

const char    *get_config_pathname(const char *pathname)
{
    char* homepath = getenv("HOME");
    char* path = malloc((strlen(pathname) + strlen(homepath) + 2) * sizeof(char));
    sprintf(path, "%s/%s", homepath, pathname);
    return path;
}

int parse_line(t_config_parser_item **parser, t_config *config, char *line)
{
    t_config_parser_item *parser_item = *parser;
    while (parser_item) {
        if (strstr(line, parser_item->key) != NULL) {
            parser_item->handler(config, line);
        }
        parser_item = parser_item->next;
    }
    return 0;
}

void free_key_bin_list(t_key_bin* list_head)
{
    // TODO: free list
    return;
}

void clean_config(t_config config)
{
    if (config.submit) {
        free(config.submit);
    }
    if (config.default_command) {
        free(config.default_command);
    }
    if (config.favorite_head) {
        free_key_bin_list(config.favorite_head);
    }
}

t_config parse_config(const char *pathname)
{
    t_config_parser_item *parser;
    t_config    config = {NULL,NULL,NULL};
    FILE     *fd;
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read;

    parser = get_parser();
    fd = fopen(get_config_pathname(pathname), "r");
    if (fd == NULL) {
        // Program should be able to run without a valid config
        return config;
    }
    while ((read = getline(&line, &len, fd)) != -1) {
        if (parse_line(&parser, &config, line) == -1) {
            printf("Invalid line on config file:\n%s\n\n", line);
            clean_config(config);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fd);
    if (line) {
        free(line);
    }
    return config;
}
