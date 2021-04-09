#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "include/config.h"

const char    *get_config_pathname(const char *pathname)
{
    char* homepath = getenv("HOME");
    char* path = malloc((strlen(pathname) + strlen(homepath) + 2) * sizeof(char));
    strcat(path, homepath);
    strcat(path + strlen(homepath), "/");
    strcat(path + strlen(homepath) + 1, pathname);
    return path;
}

int    parse_line(t_config *config, char *line)
{
    return 0;
}

void free_key_bin_list(t_key_bin* list_head)
{
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
    t_config    config = {NULL,NULL,NULL};
    FILE     *fd;
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read;


    fd = fopen(/* TODO: it fails? get_config_pathname(pathname) */ "/home/dlacreme/.magic_bar", "r");
    if (fd == NULL) {
        printf("Error opening '%s' ; ERROR=%d\n", get_config_pathname(pathname), errno);
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fd)) != -1) {
        if (parse_line(&config, line) == -1) {
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
