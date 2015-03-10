package = "ossp-uuid"
version = "1.0.1-1"
source = {
    url = "git://github.com/mah0x211/lua-ossp-uuid.git",
    tag = "v1.0.1"
}
description = {
    summary = "OSSP uuid bindings for lua",
    homepage = "https://github.com/mah0x211/lua-ossp-uuid", 
    license = "MIT/X11",
    maintainer = "Masatoshi Teruya"
}
dependencies = {
    "lua >= 5.1"
}
external_dependencies = {
    OSSP_UUID = {
        header = "ossp/uuid.h",
        library = "uuid"
    },
    platforms = {
        linux = {
            OSSP_UUID = {
                library = "ossp-uuid"
            }
        }
   }
}
build = {
    platforms = {
        linux = {
            build_variables = {
                LIBUUID = "ossp-uuid"
            }
        }
    },
    type = "make",
    build_variables = {
        PACKAGE         = "ossp-uuid",
        LIBUUID         = "uuid",
        CFLAGS          = "$(CFLAGS)",
        WARNINGS        = "-Wall -Wno-trigraphs -Wmissing-field-initializers -Wreturn-type -Wmissing-braces -Wparentheses -Wno-switch -Wunused-function -Wunused-label -Wunused-parameter -Wunused-variable -Wunused-value -Wuninitialized -Wunknown-pragmas -Wshadow -Wsign-compare",
        CPPFLAGS        = "-I$(LUA_INCDIR) -I$(OSSP_UUID_INCDIR)",
        LDFLAGS         = "$(LIBFLAG) -L$(OSSP_UUID_LIBDIR)",
        LIB_EXTENSION   = "$(LIB_EXTENSION)"
    },
    install_variables = {
        PACKAGE         = "ossp-uuid",
        LIBDIR          = "$(LIBDIR)",
        PREFIX          = "$(PREFIX)",
        LIB_EXTENSION   = "$(LIB_EXTENSION)"
    }
}

