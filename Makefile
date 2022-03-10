TARGET=$(PACKAGE).$(LIB_EXTENSION)
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

all: preprocess $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(WARNINGS) -I$(LUA_INCDIR) $(CPPFLAGS) -Ideps/uuid-1.6.2 -o $@ -c $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ deps/uuid-1.6.2/.libs/libuuid.a $(LIBFLAG) $(PLATFORM_LDFLAGS)

preprocess:
	cd ./deps; \
	tar -xzf ./uuid-1.6.2.tar.gz; \
	cd ./uuid-1.6.2; \
	./configure CC=gcc; \
	make CC=gcc; \
	make check

install:
	mkdir -p $(LIBDIR)
	cp $(TARGET) $(LIBDIR)
	rm -rf deps/uuid-1.6.2
	rm -f $(OBJS) $(TARGET)
