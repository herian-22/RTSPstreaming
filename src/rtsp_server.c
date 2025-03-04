#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include "rtsp_server.h"

static GstRTSPServer *server = NULL; // RTSP server
static GMainLoop *loop = NULL;      // Main loop GStreamer

// Fungsi untuk memulai RTSP server
void start_rtsp_server() {
    if (server != NULL) {
        g_print("RTSP Server already running\n");
        return;
    }

    gst_init(NULL, NULL);  // Initialize GStreamer

    loop = g_main_loop_new(NULL, FALSE);
    server = gst_rtsp_server_new();

    // Set up mount points for the server
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

    // Define a GStreamer pipeline for video stream
    gst_rtsp_media_factory_set_launch(factory,
        "( autovideosrc ! videoconvert ! x264enc tune=zerolatency bitrate=2048 speed-preset=superfast ! rtph264pay name=pay0 pt=96 )");

    // Add the factory to the server's mount points at "/stream"
    gst_rtsp_mount_points_add_factory(mounts, "/stream", factory);
    gst_rtsp_server_attach(server, NULL);

    g_print("RTSP Streaming started at rtsp://192.168.9.17:8554/stream\n");

    g_main_loop_run(loop);  // Start the GStreamer main loop
}

// Fungsi untuk menghentikan RTSP server
void stop_rtsp_server() {
    if (server != NULL) {
        // Unreference the server and stop the loop
        g_object_unref(server);
        g_main_loop_quit(loop);
        g_print("RTSP Streaming stopped\n");

        // Unreference the loop
        g_main_loop_unref(loop);

        // Reset references
        server = NULL;
        loop = NULL;
    }
}