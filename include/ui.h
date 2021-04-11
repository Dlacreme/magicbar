#ifndef ui_h
#define ui_h

#include <gtk/gtk.h>
#include "config.h"

typedef struct s_gtk_ui {
    GtkApplication  *app;
} t_gtk_ui;

t_gtk_ui setup_ui();
int start_ui(t_gtk_ui*, int, char**, t_config*);

#endif
