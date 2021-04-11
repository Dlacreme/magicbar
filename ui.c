#include "include/ui.h"

static void activate(GtkApplication*, gpointer);
static void submit(GtkWidget*, gpointer);
static void activate(GtkApplication*, gpointer);
static void key_press(GtkEntry*, gpointer);
GtkWidget *build_window(GtkApplication*);
GtkWidget *build_input(GtkWidget*, char*);
char *get_input_content(GtkWidget*);
void set_input_content(GtkWidget*, char*);

t_gtk_ui    setup_ui()
{
    t_gtk_ui    ui = {NULL, NULL, NULL};

    ui.app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    return ui;
}

int    start_ui(t_gtk_ui *ui, t_config *config, void (*callback)(char*), int argc, char **argv)
{
    t_gtk_callback_data data = {config, ui, callback, config->default_command};
    int status;

    g_signal_connect(ui->app, "activate", G_CALLBACK(activate), &data);
    status = g_application_run(G_APPLICATION(ui->app), argc, argv);
    g_object_unref(ui->app);
    return status;
}

static void activate(GtkApplication *app, gpointer ptr_data)
{
    t_gtk_callback_data *data = (t_gtk_callback_data*)ptr_data;

    data->ui->window = gtk_application_window_new(app);
    data->ui->input = build_input(data->ui->window, data->config->default_command);
    g_signal_connect(GTK_ENTRY(data->ui->input), "activate", G_CALLBACK(key_press), data);
    gtk_window_present(GTK_WINDOW(data->ui->window));
}

static void key_press(GtkEntry *input, gpointer ptr_data)
{
    g_print("SUBMIT !!");
    t_gtk_callback_data *data = (t_gtk_callback_data*)ptr_data;
    data->command = get_input_content(GTK_WIDGET(input));
    data->callback(data->command);
    gtk_window_close(GTK_WINDOW(data->ui->window));
}

GtkWidget* build_window(GtkApplication *app)
{
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), 100, 400);

    return window;
}

GtkWidget* build_input(GtkWidget *window, char *default_value)
{
    GtkWidget* input;
    input = gtk_entry_new();
    set_input_content(input, default_value);
    gtk_window_set_child(GTK_WINDOW(window), input);
    return input;
}

char *get_input_content(GtkWidget* input)
{
    GtkEntryBuffer  *buffer;

    buffer = gtk_entry_get_buffer(GTK_ENTRY(input));
    gtk_entry_buffer_get_text(buffer);
}

void set_input_content(GtkWidget* input, char *value)
{
    GtkEntryBuffer  *buffer;

    buffer = gtk_entry_get_buffer(GTK_ENTRY(input));
    gtk_entry_buffer_set_text(buffer, value, -1);
}