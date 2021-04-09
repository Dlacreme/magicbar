#include <stdlib.h>

int run_command(char *cmd)
{
    return system(cmd);
}