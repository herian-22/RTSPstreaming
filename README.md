# RTSPstreaming 
# Fitur:
Start Streaming: Memulai streaming video dengan RTSP menggunakan kamera.
Stop Streaming: Menghentikan streaming dan server RTSP.
GUI dengan GTK3: Menampilkan tombol dan status streaming.
Persyaratan Sistem:
MSYS2 (MINGW64)
GTK3 dan GStreamer yang terinstal di sistem.
# Langkah Instalasi:
Instalasi Dependencies: Install GTK3 dan GStreamer di MSYS2 dengan perintah:


pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-gstreamer mingw-w64-x86_64-gst-plugins-base mingw-w64-x86_64-gst-plugins-good mingw-w64-x86_64-gst-plugins-bad mingw-w64-x86_64-gst-plugins-ugly mingw-w64-x86_64-glib2 mingw-w64-x86_64-gobject-introspection

#Build Aplikasi: Jalankan perintah berikut untuk meng-compile aplikasi:

make

#Jalankan Aplikasi: Setelah build selesai, jalankan aplikasi dengan perintah:


./my_rtsp_app.exe

#Penggunaan:
Setelah aplikasi berjalan, tombol Start Streaming akan memulai streaming video RTSP, dan tombol Stop Streaming akan menghentikan streaming dan server RTSP.

Command Line Interface (CLI):
Untuk memulai server RTSP tanpa menggunakan GUI, Anda bisa menggunakan command line berikut:

#Start Streaming via RTSP (jalankan di terminal):

gst-launch-1.0 autovideosrc ! videoconvert ! x264enc tune=zerolatency bitrate=2048 speed-preset=superfast ! rtph264pay name=pay0 pt=96 ! udpsink host=<IP_PENGIRIM> port=5000
Gantilah <IP_PENGIRIM> dengan IP dari komputer pengirim.

#Menerima Streaming Video dengan GStreamer: Di komputer penerima, gunakan GStreamer untuk menerima stream RTSP:

gst-launch-1.0 playbin uri=rtsp://<IP_PENGIRIM>:8554/stream
Gantilah <IP_PENGIRIM> dengan IP dari komputer pengirim.

#Menangkap Video dari Kamera dengan Command Line: Jika ingin menangkap video dari kamera menggunakan GStreamer secara langsung, Anda bisa menggunakan pipeline berikut:

gst-launch-1.0 v4l2src ! videoconvert ! autovideosink
