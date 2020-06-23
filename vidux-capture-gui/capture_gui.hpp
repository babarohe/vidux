#ifndef   CAPTURE_GUI_HPP
#define   CAPTURE_GUI_HPP

#include <gtkmm.h>

class ViduxCaptureGui
{
private:
    GtkWidget *window;
    GtkWidget *grid;


public:
    void init();
    void main();
};

#endif


    // GtkWidget *window;
    // GtkWidget *grid;

    // GtkWidget *frame1;
    // GtkWidget *frame2;
    // GtkWidget *frame3;
    // GtkWidget *frame4;
    // GtkWidget *label1;
    // GtkWidget *label2;
    // GtkWidget *label3;
    // GtkWidget *label4;

    // gtk_init(&argc, &argv);

    // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // //ウィンドウを画面の中央に配置
    // gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    // gtk_widget_set_size_request(window, 300, 200);
    // gtk_window_set_title(GTK_WINDOW(window), "GtkFrame");
    // gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // grid = gtk_grid_new();
    // gtk_container_add(GTK_CONTAINER(window), grid);

    // label1 = gtk_label_new("Label1");
    // label2 = gtk_label_new("Label2");
    // label3 = gtk_label_new("Label3");
    // label4 = gtk_label_new("Label4");

    // frame1 = gtk_frame_new("Shadow In");
    // gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
    // gtk_grid_attach(GTK_GRID(grid), frame1, 0, 0, 2, 2);
    // gtk_container_add(GTK_CONTAINER(frame1), label1);

    // frame2 = gtk_frame_new("Shadow Out");
    // gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_OUT);
    // gtk_grid_attach(GTK_GRID(grid), frame2, 3, 0, 2, 2);
    // gtk_container_add(GTK_CONTAINER(frame2), label2);

    // frame3 = gtk_frame_new("Shadow Etched In");
    // gtk_frame_set_shadow_type(GTK_FRAME(frame3), GTK_SHADOW_ETCHED_IN);
    // gtk_grid_attach(GTK_GRID(grid), frame3, 0, 3, 2, 2);
    // gtk_container_add(GTK_CONTAINER(frame3), label3);

    // frame4 = gtk_frame_new("Shadow Etched Out");
    // gtk_frame_set_shadow_type(GTK_FRAME(frame4), GTK_SHADOW_ETCHED_OUT);
    // gtk_grid_attach(GTK_GRID(grid), frame4, 3, 3, 2, 2);
    // gtk_container_add(GTK_CONTAINER(frame4), label4);

    // g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    // gtk_widget_show_all(window);

    // gtk_main();

    // return 0;
