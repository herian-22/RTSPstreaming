#include <gtk/gtk.h>
#include <gst/gst.h>
#include "rtsp_server.h"

static GtkWidget *status_label;  // Label untuk menampilkan status kamera
static GstElement *pipeline = NULL;  // GStreamer pipeline

// Fungsi untuk memulai streaming RTSP
static void on_start_clicked(GtkWidget *widget, gpointer data) {
    start_rtsp_server(); // Assuming you have a function to start RTSP server
    gtk_button_set_label(GTK_BUTTON(widget), "Streaming Started");
    gtk_label_set_text(GTK_LABEL(status_label), "Camera Ready: Streaming Started");
}

// Fungsi untuk menghentikan streaming RTSP
static void on_stop_clicked(GtkWidget *widget, gpointer data) {
    if (pipeline != NULL) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = NULL;
        gtk_button_set_label(GTK_BUTTON(widget), "Start Streaming");
        gtk_label_set_text(GTK_LABEL(status_label), "Camera Ready: Stopped");
    }
}

// Fungsi untuk menambahkan label status dan tombol ke GUI
static void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *start_button, *stop_button;
    GtkWidget *box;

    // Buat Window GTK
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "RTSP Streaming Server");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Menambahkan Label Status Kamera
    status_label = gtk_label_new("Camera Ready: Waiting to Start");

    // Membuat Tombol Start dan Stop
    start_button = gtk_button_new_with_label("Start Streaming");
    stop_button = gtk_button_new_with_label("Stop Streaming");

    // Menambahkan sinyal pada tombol
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_clicked), NULL);
    g_signal_connect(stop_button, "clicked", G_CALLBACK(on_stop_clicked), NULL);

    // Membuat Box Layout
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(box), status_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), start_button, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), stop_button, FALSE, FALSE, 10);

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}

// Fungsi utama untuk menjalankan aplikasi GTK
int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    gst_init(&argc, &argv);  // Initialize GStreamer

    app = gtk_application_new("com.example.rtspserver", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}