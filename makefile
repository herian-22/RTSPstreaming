CC=x86_64-w64-mingw32-gcc
CFLAGS=`pkg-config --cflags gtk+-3.0 gstreamer-1.0 gstreamer-rtsp-server-1.0 glib-2.0 gobject-2.0`
LIBS=`pkg-config --libs gtk+-3.0 gstreamer-1.0 gstreamer-rtsp-server-1.0 glib-2.0 gobject-2.0`

SRC=src/main.c src/rtsp_server.c
OBJ=build/main.o build/rtsp_server.o
EXEC=my_rtsp_app.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf build $(EXEC)
