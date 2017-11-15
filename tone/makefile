

GLIBS=-I/usr/local/Cellar/glib/2.54.2/lib/glib-2.0/include -I/usr/local/Cellar/glib/2.54.2/include/glib-2.0

tonertc : mainline.cpp
	g++ -o tonertc mainline.cpp -I ../src ${GLIBS} ../src/librtcdc.dylib

clean:
	rm tonertc





