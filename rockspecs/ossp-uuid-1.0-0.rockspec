package = "ossp-uuid"
version = "1.0-0"
source = {
    url = "git://github.com/mah0x211/lua-ossp-uuid.git"
}
description = {
    summary = "OSSP uuid bindings for lua",
    detailed = [[]],
    homepage = "https://github.com/mah0x211/lua-ossp-uuid", 
    license = "MIT/X11",
    maintainer = "Masatoshi Teruya"
}
dependencies = {
    "lua >= 5.1"
}
external_dependencies = {
    OSSP_UUID = {
        header = "uuid.h",
        library = "uuid"
    }
}
build = {
    type = "builtin",
    modules = {
        ['ossp-uuid'] = {
            sources = { "uuid.c" },
            libraries = { "uuid" },
            incdirs = { 
                "$(OSSP_UUID_INCDIR)"
            },
            libdirs = { 
                "$(OSSP_UUID_LIBDIR)"
            }
        }
    }
}

