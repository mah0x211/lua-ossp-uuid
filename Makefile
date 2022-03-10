TARGET=$(PACKAGE).$(LIB_EXTENSION)
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)
INSTALL?=install
ifdef OSSP_UUID_COVERAGE
COVFLAGS=--coverage
endif

.PHONY: all preprocess install

all: preprocess $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(WARNINGS) $(COVFLAGS) $(CPPFLAGS) -o $@ -c $<

$(TARGET): $(OBJS)
	$(CC) $(LIBFLAG) $(LDFLAGS) $(PLATFORM_LDFLAGS) $(COVFLAGS) -o $@ $^ ./deps/uuid-1.6.2/.libs/libuuid.a

preprocess:
	cd ./deps; \
	tar -xzf ./uuid-1.6.2.tar.gz; \
	cd ./uuid-1.6.2; \
	./configure; \
	make; \
	make check

install:
	$(INSTALL) $(TARGET) $(INST_LIBDIR)
	rm -rf deps/uuid-1.6.2
	rm -f $(OBJS) $(TARGET)
