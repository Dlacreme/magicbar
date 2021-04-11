#include "include/magic_bar.h"

static const char CONFIG_PATHNAME[100] = ".magic_bar";

int run_command(char *cmd)
{
    return system(cmd);
}

int main(int argc, char **argv)
{
    t_config  config = parse_config(CONFIG_PATHNAME);
    t_gtk_ui  ui = setup_ui();
    start_ui(&ui, argc, argv, &config);
    return run_command(config.default_command);
}
