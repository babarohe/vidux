#include "capture_gui.hpp"


void ViduxCaptureGui::init()
{
    int argc;
    char **argv;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);;
    gtk_widget_set_size_request(window, 300, 200);
    gtk_window_set_title(GTK_WINDOW(window), "VIDUX - Capture");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);


}



void ViduxCaptureGui::main()
{
    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
    gtk_widget_show_all(window);

    gtk_main();

}
