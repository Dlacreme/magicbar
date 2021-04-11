#include "include/magic_bar.h"

static const char CONFIG_PATHNAME[100] = ".magic_bar";

void run_command(char *cmd)
{
    system(cmd);
}

int main(int argc, char **argv)
{
    t_config  config = parse_config(CONFIG_PATHNAME);
    t_gtk_ui  ui = setup_ui();
    return start_ui(&ui, &config, &run_command, argc, argv);
    // return run_command(config.default_command);
}
