#include "include/magic_bar.h"
#include "include/config.h"

static const char CONFIG_PATHNAME[100] = ".magic_bar";

int main (__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    const t_config  config = parse_config(CONFIG_PATHNAME);

    return run_command("firefox");
}
