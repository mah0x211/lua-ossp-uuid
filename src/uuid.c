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

#include "../deps/uuid-1.6.2/uuid.h"
// #include "uuid.h"
#include <lauxhlib.h>
#include <stdlib.h>

static int generate14(lua_State *L, uuid_fmt_t fmt, int ver)
{
    uuid_t *uid  = NULL;
    uuid_rc_t rc = uuid_create(&uid);

    if (rc == UUID_RC_OK) {
        void *gen  = NULL;
        size_t len = 0;

        if ((rc = uuid_make(uid, ver)) == UUID_RC_OK &&
            (rc = uuid_export(uid, fmt, &gen, &len)) == UUID_RC_OK) {
            if (fmt == UUID_FMT_SIV) {
                lua_pushstring(L, gen);
            } else {
                lua_pushlstring(L, gen, len - 1);
            }
            free(gen);
        }
        uuid_destroy(uid);
    }

    switch (rc) {
    // UUID_RC_OK   everything ok
    case UUID_RC_OK:
        return 1;

    // UUID_RC_ARG  invalid argument
    // UUID_RC_MEM  out of memory
    // UUID_RC_SYS  system error
    // UUID_RC_INT  internal error
    // UUID_RC_IMP  not implemented
    default:
        lua_pushnil(L);
        lua_pushstring(L, uuid_error(rc));
        return 2;
    }
}

static int generate35(lua_State *L, uuid_fmt_t fmt, int ver, const char *ns,
                      const char *name)
{
    uuid_t *uid  = NULL;
    uuid_rc_t rc = uuid_create(&uid);

    // create context
    if (rc == UUID_RC_OK) {
        uuid_t *uid_ns = NULL;

        rc = uuid_create(&uid_ns);
        if (rc == UUID_RC_OK) {
            void *gen  = NULL;
            size_t len = 0;

            if ((rc = uuid_load(uid_ns, ns)) == UUID_RC_OK &&
                (rc = uuid_make(uid, ver, uid_ns, name)) == UUID_RC_OK &&
                (rc = uuid_export(uid, fmt, &gen, &len)) == UUID_RC_OK) {
                if (fmt == UUID_FMT_SIV) {
                    lua_pushstring(L, gen);
                } else {
                    lua_pushlstring(L, gen, len - 1);
                }
                free(gen);
            }
            uuid_destroy(uid_ns);
        }
        uuid_destroy(uid);
    }

    switch (rc) {
    // UUID_RC_OK   everything ok
    case UUID_RC_OK:
        return 1;

    // UUID_RC_ARG  invalid argument
    // UUID_RC_MEM  out of memory
    // UUID_RC_SYS  system error
    // UUID_RC_INT  internal error
    // UUID_RC_IMP  not implemented
    default:
        lua_pushnil(L);
        lua_pushstring(L, uuid_error(rc));
        return 2;
    }
}

static int generate_lua(lua_State *L)
{
    const char *const namespaces[] = {"nil",    "ns:DNS",  "ns:URL",
                                      "ns:OID", "ns:x500", NULL};
    uuid_fmt_t fmt                 = lauxh_checkinteger(L, 1);
    int ver                        = lauxh_checkinteger(L, 2);
    const char *ns                 = NULL;
    const char *name               = NULL;

    if (fmt != UUID_FMT_STR && fmt != UUID_FMT_SIV && fmt != UUID_FMT_TXT) {
        return luaL_argerror(L, 1, "format must be str|siv|txt");
    }

    switch (ver) {
    case UUID_MAKE_V1:
    case UUID_MAKE_V4:
        return generate14(L, fmt, ver);

    case UUID_MAKE_V3:
    case UUID_MAKE_V5: {
        ns   = namespaces[luaL_checkoption(L, 3, NULL, namespaces)];
        name = lauxh_checkstring(L, 4);
        return generate35(L, fmt, ver, ns, name);
    }

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
    const char *ns   = lauxh_checkstring(L, 1);
    const char *name = lauxh_checkstring(L, 2);
    return generate35(L, UUID_FMT_STR, UUID_MAKE_V3, ns, name);
}

static int gen3siv_lua(lua_State *L)
{
    const char *ns   = lauxh_checkstring(L, 1);
    const char *name = lauxh_checkstring(L, 2);
    return generate35(L, UUID_FMT_SIV, UUID_MAKE_V3, ns, name);
}

static int gen3txt_lua(lua_State *L)
{
    const char *ns   = lauxh_checkstring(L, 1);
    const char *name = lauxh_checkstring(L, 2);
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
    const char *ns   = lauxh_checkstring(L, 1);
    const char *name = lauxh_checkstring(L, 2);
    return generate35(L, UUID_FMT_STR, UUID_MAKE_V5, ns, name);
}

static int gen5siv_lua(lua_State *L)
{
    const char *ns   = lauxh_checkstring(L, 1);
    const char *name = lauxh_checkstring(L, 2);
    return generate35(L, UUID_FMT_SIV, UUID_MAKE_V5, ns, name);
}

static int gen5txt_lua(lua_State *L)
{
    const char *ns   = lauxh_checkstring(L, 1);
    const char *name = lauxh_checkstring(L, 2);
    return generate35(L, UUID_FMT_TXT, UUID_MAKE_V5, ns, name);
}

static int version_lua(lua_State *L)
{
    lua_pushinteger(L, uuid_version());
    return 1;
}

LUALIB_API int luaopen_uuid(lua_State *L)
{
    lua_newtable(L);

    // version
    lauxh_pushint2tbl(L, "V1", UUID_MAKE_V1);
    lauxh_pushint2tbl(L, "V3", UUID_MAKE_V3);
    lauxh_pushint2tbl(L, "V4", UUID_MAKE_V4);
    lauxh_pushint2tbl(L, "V5", UUID_MAKE_V5);
    // format
    lauxh_pushint2tbl(L, "STR", UUID_FMT_STR);
    lauxh_pushint2tbl(L, "SIV", UUID_FMT_SIV);
    lauxh_pushint2tbl(L, "TXT", UUID_FMT_TXT);
    // namespace
    lauxh_pushstr2tbl(L, "NSNIL", "nil");
    lauxh_pushstr2tbl(L, "NSDNS", "ns:DNS");
    lauxh_pushstr2tbl(L, "NSURL", "ns:URL");
    lauxh_pushstr2tbl(L, "NSOID", "ns:OID");
    lauxh_pushstr2tbl(L, "NSX500", "ns:x500");
    // functions
    lauxh_pushfn2tbl(L, "version", version_lua);
    lauxh_pushfn2tbl(L, "generate", generate_lua);
    lauxh_pushfn2tbl(L, "gen1str", gen1str_lua);
    lauxh_pushfn2tbl(L, "gen1siv", gen1siv_lua);
    lauxh_pushfn2tbl(L, "gen1txt", gen1txt_lua);
    lauxh_pushfn2tbl(L, "gen3str", gen3str_lua);
    lauxh_pushfn2tbl(L, "gen3siv", gen3siv_lua);
    lauxh_pushfn2tbl(L, "gen3txt", gen3txt_lua);
    lauxh_pushfn2tbl(L, "gen4str", gen4str_lua);
    lauxh_pushfn2tbl(L, "gen4siv", gen4siv_lua);
    lauxh_pushfn2tbl(L, "gen4txt", gen4txt_lua);
    lauxh_pushfn2tbl(L, "gen5str", gen5str_lua);
    lauxh_pushfn2tbl(L, "gen5siv", gen5siv_lua);
    lauxh_pushfn2tbl(L, "gen5txt", gen5txt_lua);

    return 1;
}
