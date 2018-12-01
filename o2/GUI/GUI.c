#include <gtk/gtk.h>
#include "treatmentGUI.c"

GtkImage *image_box;
char *file_path;
GtkBuilder      *builder;
GtkFileChooser *file_chooser;

int main(int argc, char *argv[])
{
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    
	image_box = GTK_IMAGE(gtk_builder_get_object(builder, "image_box_01"));
	gtk_image_clear(image_box);
	
	file_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "file_chooser"));
	
    g_object_unref(builder);
    
    g_signal_connect(window, "destroy", gtk_main_quit, NULL);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
 
void on_btn_load_clicked()
{
	gtk_image_set_from_file(image_box, file_path);
	printf("[o2] - Loaded file   : \"");
	printf("%s\"\n",file_path);
}

void on_window_main_destroy()
{
    gtk_main_quit();
}

void on_btn_exit_clicked()
{
    gtk_main_quit();
}

void file_selected()
{
	printf("[o2] - Selected file : \"");
	printf("%s\"\n",gtk_file_chooser_get_filename(file_chooser));
	file_path = gtk_file_chooser_get_filename(file_chooser);
}

void on_btn_grayscale_clicked()
{
	/*
	char format[] = "_grayed";
	char buffer[strlen(file_path) + strlen(format)]; 
	new_format(file_path,format,buffer);
	*/
	grayscale_GUI(file_path);
	gtk_image_set_from_file(image_box, file_path);
	printf("[o2] - Image grayscaled and saved as : \"%s\"\n",file_path);
}

void on_btn_bw_clicked()
{
	/*
	char format[] = "_bin";
	char buffer[strlen(file_path) + strlen(format)]; 
	new_format(file_path,format,buffer);
	*/
	binarize_GUI(file_path);
	gtk_image_set_from_file(image_box, file_path);
	printf("[o2] - Image binarized and saved as : \"%s\"\n",file_path);
}

void on_btn_rotate_l_clicked()
{
	SDL_Surface *img = load_image(file_path);
	SDL_Surface* img2;
	img2 = rotate90_l(img);
	SDL_SaveBMP(img2, file_path);
	gtk_image_set_from_file(image_box, file_path);
	printf("[o2] - Image rotated left : \"%s\"\n",file_path);
}

void on_btn_rotate_r_clicked()
{
	SDL_Surface *img = load_image(file_path);
	SDL_Surface* img2;
	img2 = rotate90_r(img);
	SDL_SaveBMP(img2, file_path);
	gtk_image_set_from_file(image_box, file_path);
	printf("[o2] - Image rotated right: \"%s\"\n",file_path);
}
