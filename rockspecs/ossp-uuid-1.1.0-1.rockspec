package = "ossp-uuid"
version = "1.1.0-1"
source = {
    url = "git://github.com/mah0x211/lua-ossp-uuid.git",
    tag = "v1.1.0"
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
build = {
    type = "make",
    build_variables = {
        PACKAGE         = "ossp-uuid",
        CFLAGS          = "$(CFLAGS)",
        WARNINGS        = "-Wall -Wno-trigraphs -Wmissing-field-initializers -Wreturn-type -Wmissing-braces -Wparentheses -Wno-switch -Wunused-function -Wunused-label -Wunused-parameter -Wunused-variable -Wunused-value -Wuninitialized -Wunknown-pragmas -Wshadow -Wsign-compare",
        LUA_INCDIR      = "$(LUA_INCDIR)",
        LIBFLAG         = "$(LIBFLAG)",
        LIB_EXTENSION   = "$(LIB_EXTENSION)"
    },
    install_variables = {
        PACKAGE         = "ossp-uuid",
        LIBDIR          = "$(LIBDIR)",
        PREFIX          = "$(PREFIX)",
        LIB_EXTENSION   = "$(LIB_EXTENSION)"
    }
}

