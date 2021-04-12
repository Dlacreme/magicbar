#include "include/ui.h"

static void activate(GtkApplication*, gpointer);
static void submit(GtkWidget*, gpointer);
static void activate(GtkApplication*, gpointer);
static void key_press(GtkEntry*, gpointer);
GtkWidget *build_window(GtkApplication*);
GtkWidget *build_grid(GtkWidget*);
GtkWidget *build_input(GtkWidget*, char*);
char *get_input_content(GtkWidget*);
void set_input_content(GtkWidget*, char*);
void prepare_favorites(GtkWidget*, t_key_bin*);

int listlen(t_key_bin*);

t_gtk_ui    setup_ui()
{
    t_gtk_ui    ui = {NULL, NULL, NULL, NULL, NULL};

    ui.app = gtk_application_new("dlacreme.magicbar", G_APPLICATION_FLAGS_NONE);
    return ui;
}

int    start_ui(t_gtk_ui *ui, t_config *config, void (*callback)(char*), int argc, char **argv)
{
    t_gtk_callback_data data = {config, ui, callback, config->default_command};
    int status;
    ui->texts = malloc(sizeof(GtkWidget*) * listlen(config->favorite_head));

    g_signal_connect(ui->app, "activate", G_CALLBACK(activate), &data);
    status = g_application_run(G_APPLICATION(ui->app), argc, argv);
    g_object_unref(ui->app);
    return status;
}

static void activate(GtkApplication *app, gpointer ptr_data)
{
    t_gtk_callback_data *data = (t_gtk_callback_data*)ptr_data;
    data->ui->window = build_window(app);
    data->ui->grid = build_grid(data->ui->window);
    data->ui->input = build_input(data->ui->window, data->config->default_command);
    prepare_favorites(data->ui->window, data->config->favorite_head);
    g_signal_connect(GTK_ENTRY(data->ui->input), "activate", G_CALLBACK(key_press), data);
    gtk_window_present(GTK_WINDOW(data->ui->window));
}

static void key_press(GtkEntry *input, gpointer ptr_data)
{
    t_gtk_callback_data *data = (t_gtk_callback_data*)ptr_data;
    data->command = get_input_content(GTK_WIDGET(input));
    data->callback(data->command);
    gtk_window_close(GTK_WINDOW(data->ui->window));
}

GtkWidget* build_window(GtkApplication *app)
{
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "magic_bar");
    gtk_window_set_default_size(GTK_WINDOW(window), 420, 120);
    gtk_window_set_resizable(GTK_WINDOW(window), false);

    return window;
}

GtkWidget* build_grid(GtkWidget *window)
{
    GtkWidget *grid;
    grid = gtk_grid_new();
}

GtkWidget* build_input(GtkWidget *window, char *default_value)
{
    GtkWidget* input;
    input = gtk_entry_new();
    if (default_value) {
        set_input_content(input, default_value);
    }
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

void prepare_favorites(GtkWidget* window, t_key_bin *fav)
{
    GtkWidget *text;
    GtkTextBuffer *buffer;
    char *tmp;

    while (fav) {
        printf("Bind [%c] FOR %s\n", fav->key, fav->command);
        text = gtk_text_view_new();
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
        tmp = malloc(sizeof(char) * strlen(fav->command) + 4);
        sprintf(tmp, "[%c] %s", fav->key, fav->command);
        gtk_text_buffer_set_text(buffer, tmp, -1);
        fav = fav->next;
        free(tmp);
        gtk_window_set_child(GTK_WINDOW(window), text);
    }
}

int listlen(t_key_bin* list)
{
    int i = 0;
    while (list) {
        i++;
        list = list->next;
    }
    return i;
}