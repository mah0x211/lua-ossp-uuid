TARGET=$(PACKAGE).$(LIB_EXTENSION)
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LIBS=`pkg-config $(LIBUUID) --libs`

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(WARNINGS) $(CPPFLAGS) -o $@ -c $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) $(PLATFORM_LDFLAGS)


install:
	mkdir -p $(LIBDIR)
	cp $(TARGET) $(LIBDIR)
	rm -f $(OBJS) $(TARGET)

