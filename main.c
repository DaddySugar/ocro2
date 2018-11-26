#include <gtk/gtk.h>

 
GtkWidget *entry;
GtkImage *image_box;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry_path"));
	
	image_box = GTK_IMAGE(gtk_builder_get_object(builder, "image_box_01"));
	gtk_image_clear(image_box);
	
    g_object_unref(builder);
    
    g_signal_connect(window, "destroy", gtk_main_quit, NULL);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
 
void on_btn_load_clicked()
{
	gtk_image_set_from_file(image_box, gtk_entry_get_text(GTK_ENTRY(entry)));
}

void on_entry_path_activate()
{
	gtk_image_set_from_file(image_box, gtk_entry_get_text(GTK_ENTRY(entry)));
}
 
void on_window_main_destroy()
{
    gtk_main_quit();
}
