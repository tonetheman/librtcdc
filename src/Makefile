# Makefile
# Copyright (c) 2015 Xiaohan Song <chef@dark.kitchen>
# This file is licensed under a BSD license.

GLIBS=-I/usr/local/Cellar/glib/2.54.2/include/glib-2.0 -I/usr/local/Cellar/glib/2.54.2/lib/glib-2.0/include \
-I /usr/local/Cellar/libnice/0.1.14/include

CFLAGS+=-g -O2 -DINET -DINET6 -DDEBUG_SCTP -fPIC -Wno-deprecated `pkg-config --cflags openssl nice` ${GLIBS}
LDFLAGS+=`pkg-config --libs openssl nice` -lusrsctp -lpthread
SOURCES=util.c dtls.c sctp.c ice.c sdp.c dcep.c rtcdc.c
OBJECTS=$(SOURCES:.c=.o)
NAME=rtcdc

ifeq "$(OS)" ""
	OS = $(shell uname -s)
endif

ifeq "$(OS)" "Darwin"
	TARGET=lib$(NAME).dylib
else
	TARGET=lib$(NAME).so
endif

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -shared -fPIC $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.so *.dylib *.a example 

