#ifndef config_h
#define config_h

struct s_key_bin;
// key bin stores a command and its matching shortcut; used as linked list
typedef struct s_key_bin {
    char    *command;
    char    key;
    struct s_key_bin*  next;
} t_key_bin;

typedef struct s_config {
    char    *submit;
    char    *default_command;
    t_key_bin   *favorite_head;
} t_config;

t_config parse_config(const char*);

#endif