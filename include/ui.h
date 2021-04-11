#ifndef ui_h
#define ui_h

#include <gtk/gtk.h>
#include "config.h"

typedef struct s_gtk_ui {
    GtkApplication  *app;
    GtkWidget *window;
    GtkWidget *input;
} t_gtk_ui;

typedef struct s_gtk_callback_data {
    t_config    *config;
    t_gtk_ui    *ui;
    void (*callback)(char*);
    char        *command;
} t_gtk_callback_data;

t_gtk_ui setup_ui();
int start_ui(t_gtk_ui*, t_config*, void (*)(char*), int, char**);
void set_input_content(GtkWidget*, char*);

#endif
