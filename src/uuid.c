/**
 * Copyright (C) 2013-2022 Masatoshi Fukunaga
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include <lauxlib.h>
#include <stdlib.h>
#include <uuid.h>

#define uuid_export2lua(rc, L)                                                 \
 ({                                                                            \
void *gen  = NULL;                                                              \
size_t len = 0;                                                                 \
if ((*rc = uuid_export(uid, fmt, &gen, &len)) == UUID_RC_OK) {                  \
lua_pushlstring(L, gen, len - 1);                                              \
free(gen);                                                                     \
}                                                                               \
 })

static int generate14(lua_State *L, uuid_fmt_t fmt, int ver)
{
    uuid_t *uid  = NULL;
    uuid_rc_t rc = 0;

    if ((rc = uuid_create(&uid)) == UUID_RC_OK &&
        (rc = uuid_make(uid, ver)) == UUID_RC_OK) {
        uuid_export2lua(&rc, L);
        uuid_destroy(uid);
    } else if (uid) {
        uuid_destroy(uid);
    }

    return (rc == UUID_RC_OK) ? 1 : luaL_error(L, "%s", uuid_error(rc));
}

static int generate35(lua_State *L, uuid_fmt_t fmt, int ver, const char *ns,
                      const char *name)
{
    uuid_rc_t rc   = 0;
    uuid_t *uid    = NULL;
    uuid_t *uid_ns = NULL;

    // create context
    if ((rc = uuid_create(&uid)) == UUID_RC_OK &&
        (rc = uuid_create(&uid_ns)) == UUID_RC_OK &&
        (rc = uuid_load(uid_ns, ns)) == UUID_RC_OK &&
        (rc = uuid_make(uid, ver, uid_ns, name)) == UUID_RC_OK) {
        uuid_export2lua(&rc, L);
        uuid_destroy(uid);
        uuid_destroy(uid_ns);
    } else if (uid) {
        uuid_destroy(uid);
        if (uid_ns) {
            uuid_destroy(uid_ns);
        }
    }

    return (rc == UUID_RC_OK) ? 1 : luaL_error(L, "%s", uuid_error(rc));
}

static int generate_lua(lua_State *L)
{
    uuid_fmt_t fmt   = luaL_checknumber(L, 1);
    int ver          = luaL_checknumber(L, 2);
    const char *ns   = NULL;
    const char *name = NULL;

    if (fmt != UUID_FMT_STR && fmt != UUID_FMT_SIV && fmt != UUID_FMT_TXT) {
        return luaL_argerror(L, 1, "format must be str|siv|txt");
    }

    switch (ver) {
    case UUID_MAKE_V1:
    case UUID_MAKE_V4:
        return generate14(L, fmt, ver);
        break;
    case UUID_MAKE_V3:
    case UUID_MAKE_V5:
        ns   = luaL_checkstring(L, 3);
        name = luaL_checkstring(L, 4);
        return generate35(L, fmt, ver, ns, name);
        break;
    default:
        return luaL_argerror(L, 2, "version must be v1|v3|v4|v5");
    }
}

// version 1
static int gen1str_lua(lua_State *L)
{
    return generate14(L, UUID_FMT_STR, UUID_MAKE_V1);
}

static int gen1siv_lua(lua_State *L)
{
    return generate14(L, UUID_FMT_SIV, UUID_MAKE_V1);
}

static int gen1txt_lua(lua_State *L)
{
    return generate14(L, UUID_FMT_TXT, UUID_MAKE_V1);
}

// version 3
static int gen3str_lua(lua_State *L)
{
    const char *ns   = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);

    return generate35(L, UUID_FMT_STR, UUID_MAKE_V3, ns, name);
}

static int gen3siv_lua(lua_State *L)
{
    const char *ns   = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);

    return generate35(L, UUID_FMT_SIV, UUID_MAKE_V3, ns, name);
}

static int gen3txt_lua(lua_State *L)
{
    const char *ns   = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);

    return generate35(L, UUID_FMT_TXT, UUID_MAKE_V3, ns, name);
}

// version 4
static int gen4str_lua(lua_State *L)
{
    return generate14(L, UUID_FMT_STR, UUID_MAKE_V4);
}

static int gen4siv_lua(lua_State *L)
{
    return generate14(L, UUID_FMT_SIV, UUID_MAKE_V4);
}

static int gen4txt_lua(lua_State *L)
{
    return generate14(L, UUID_FMT_TXT, UUID_MAKE_V4);
}

// version 5
static int gen5str_lua(lua_State *L)
{
    const char *ns   = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);

    return generate35(L, UUID_FMT_STR, UUID_MAKE_V5, ns, name);
}

static int gen5siv_lua(lua_State *L)
{
    const char *ns   = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);

    return generate35(L, UUID_FMT_SIV, UUID_MAKE_V5, ns, name);
}

static int gen5txt_lua(lua_State *L)
{
    const char *ns   = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);

    return generate35(L, UUID_FMT_TXT, UUID_MAKE_V5, ns, name);
}

static int version_lua(lua_State *L)
{
    lua_pushnumber(L, uuid_version());
    return 1;
}

// make error
static int const_newindex(lua_State *L)
{
    return luaL_error(L, "attempting to change protected module");
}

LUALIB_API int luaopen_uuid(lua_State *L)
{
    struct luaL_Reg funcs[] = {
        {"version",  version_lua },
        {"generate", generate_lua},
        {"gen1str",  gen1str_lua },
        {"gen1siv",  gen1siv_lua },
        {"gen1txt",  gen1txt_lua },
        {"gen3str",  gen3str_lua },
        {"gen3siv",  gen3siv_lua },
        {"gen3txt",  gen3txt_lua },
        {"gen4str",  gen4str_lua },
        {"gen4siv",  gen4siv_lua },
        {"gen4txt",  gen4txt_lua },
        {"gen5str",  gen5str_lua },
        {"gen5siv",  gen5siv_lua },
        {"gen5txt",  gen5txt_lua },
        {NULL,       NULL        }
    };
    struct {
        const char *name;
        unsigned int val;
    } num_constants[] = {
  // version
        {"v1",  UUID_MAKE_V1},
        {"v3",  UUID_MAKE_V3},
        {"v4",  UUID_MAKE_V4},
        {"v5",  UUID_MAKE_V5},
 // format
        {"str", UUID_FMT_STR},
        {"siv", UUID_FMT_SIV},
        {"txt", UUID_FMT_TXT},
        {NULL,  0           }
    };
    struct {
        const char *name;
        const char *val;
    } str_constants[] = {
  // namespace
        {"nsNil",  "nil"    },
        {"nsDNS",  "ns:DNS" },
        {"nsURL",  "ns:URL" },
        {"nsOID",  "ns:OID" },
        {"nsx500", "ns:x500"},
        {NULL,     0        }
    };
    int i = 0;

    // create protected-table
    lua_newtable(L);
    // create __metatable
    lua_newtable(L);
    // create substance
    lua_pushstring(L, "__index");
    lua_newtable(L);

    // set functions
    for (i = 0; funcs[i].name; i++) {
        lua_pushstring(L, funcs[i].name);
        lua_pushcfunction(L, funcs[i].func);
        lua_rawset(L, -3);
    }
    // set constants
    for (i = 0; num_constants[i].name; i++) {
        lua_pushstring(L, num_constants[i].name);
        lua_pushnumber(L, num_constants[i].val);
        lua_rawset(L, -3);
    }
    for (i = 0; str_constants[i].name; i++) {
        lua_pushstring(L, str_constants[i].name);
        lua_pushstring(L, str_constants[i].val);
        lua_rawset(L, -3);
    }

    // set substance to __metable.__index field
    lua_rawset(L, -3);
    // set __newindex function to __metable.__newindex filed
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, const_newindex);
    lua_rawset(L, -3);
    // convert protected-table to metatable
    lua_setmetatable(L, -2);

    return 1;
}
