#include "include/ui.h"

static void activate(GtkApplication*, gpointer);

t_gtk_ui    setup_ui()
{
    t_gtk_ui    ui = {NULL};
    ui.app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);

    return ui;
}

int    start_ui(t_gtk_ui *ui, int argc, char **argv, t_config *config)
{
    int status;
    g_signal_connect(ui->app, "activate", G_CALLBACK(activate), config);
    status = g_application_run(G_APPLICATION(ui->app), argc, argv);
    g_object_unref(ui->app);
    return status;
}

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print ("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    t_config *config = (t_config*)user_data;
    GtkWidget *window;
    GtkWidget *button;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_window_set_child (GTK_WINDOW (window), button);

    gtk_window_present (GTK_WINDOW (window));
}