/*
 *  uuid.c
 *  lua-ossp-uuid
 *
 *  Created by Masatoshi Teruya on 13/03/04.
 *  Copyright 2013 Masatoshi Teruya. All rights reserved.
 *
 */

#include <stdlib.h>
#include <lauxlib.h>
#include <uuid.h>

#define uuid_export2lua(rc,L)({ \
    void *gen = NULL; \
    size_t len = 0; \
    if( ( *rc = uuid_export( uid, fmt, &gen, &len ) ) == UUID_RC_OK ){ \
        lua_pushlstring( L, gen, len - 1 ); \
        free( gen ); \
    } \
})

static int generate14( lua_State *L, uuid_fmt_t fmt, int ver )
{
    uuid_t *uid = NULL;
    uuid_rc_t rc = 0;
    
    if( ( rc = uuid_create( &uid ) ) == UUID_RC_OK &&
        ( rc = uuid_make( uid, ver ) ) == UUID_RC_OK ){
        uuid_export2lua( &rc, L );
        uuid_destroy( uid );
    }
    else if( uid ){
        uuid_destroy( uid );
    }

    return ( rc == UUID_RC_OK ) ? 1 : luaL_error( L, "%s", uuid_error( rc ) );
}

static int generate35( lua_State *L, uuid_fmt_t fmt, int ver, const char *ns, 
                       const char *name )
{
    uuid_rc_t rc = 0;
    uuid_t *uid = NULL;
    uuid_t *uid_ns = NULL;
    
    // create context
    if( ( rc = uuid_create( &uid ) ) == UUID_RC_OK && 
        ( rc = uuid_create( &uid_ns ) ) == UUID_RC_OK && 
        ( rc = uuid_load( uid_ns, ns ) ) == UUID_RC_OK && 
        ( rc = uuid_make( uid, ver, uid_ns, name ) ) == UUID_RC_OK ){
        uuid_export2lua( &rc, L );
        uuid_destroy( uid );
        uuid_destroy( uid_ns );
    }
    else if( uid )
    {
        uuid_destroy( uid );
        if( uid_ns ){
            uuid_destroy( uid_ns );
        }
    }
    
    return ( rc == UUID_RC_OK ) ? 1 : luaL_error( L, "%s", uuid_error( rc ) );
}

static int uuid_generate_lua( lua_State *L )
{
    uuid_fmt_t fmt = luaL_checknumber( L, 1 );
    int ver = luaL_checknumber( L, 2 );
    const char *ns = NULL;
    const char *name = NULL;
    
    if( fmt != UUID_FMT_STR && fmt != UUID_FMT_SIV && fmt != UUID_FMT_TXT ){
        return luaL_argerror( L, 1, "format must be str|siv|txt" );
    }
    
    switch( ver ) {
        case UUID_MAKE_V1:
        case UUID_MAKE_V4:
            return generate14( L, fmt, ver );
        break;
        case UUID_MAKE_V3:
        case UUID_MAKE_V5:
            ns = luaL_checkstring( L, 3 );
            name = luaL_checkstring( L, 4 );
            return generate35( L, fmt, ver, ns, name );
        break;
        default:
            return luaL_argerror( L, 2, "version must be v1|v3|v4|v5" );
    }
}

static int uuid_version_lua( lua_State *L )
{
    lua_pushnumber( L, uuid_version() );
    return 1;
}

// make error
static int const_newindex( lua_State *L ){
    return luaL_error( L, "attempting to change protected module" );
}

LUALIB_API int luaopen_uuid( lua_State *L )
{
    struct luaL_Reg funcs[] = {
        { "version", uuid_version_lua },
        { "generate", uuid_generate_lua },
        { NULL, NULL }
    };
    struct {
        const char *name;
        unsigned int val;
    } num_constants[] = {
        // version
        { "v1", UUID_MAKE_V1 },
        { "v3", UUID_MAKE_V3 },
        { "v4", UUID_MAKE_V4 },
        { "v5", UUID_MAKE_V5 },
        // format
        { "str", UUID_FMT_STR },
        { "siv", UUID_FMT_SIV },
        { "txt", UUID_FMT_TXT },
        { NULL, 0 }
    };
    struct {
        const char *name;
        const char *val;
    } str_constants[] = {
        // namespace
        { "ns_nil", "nil" },
        { "ns_dns", "ns:DNS" },
        { "ns_url", "ns:URL" },
        { "ns_oid", "ns:OID" },
        { "ns_x500", "ns:x500" },
        { NULL, 0 }
    };
    int i = 0;
    
    // create protected-table
    lua_newtable( L );
    // create __metatable
    lua_newtable( L );
    // create substance
    lua_pushstring( L, "__index" );
    lua_newtable( L );
    
    // set functions
    for( i = 0; funcs[i].name; i++ ){ 
        lua_pushstring( L, funcs[i].name );
        lua_pushcfunction( L, funcs[i].func );
        lua_rawset( L, -3 );
    }
    // set constants
    for( i = 0; num_constants[i].name; i++ ){
        lua_pushstring( L, num_constants[i].name );
        lua_pushnumber( L, num_constants[i].val );
        lua_rawset( L, -3 );
    }
    for( i = 0; str_constants[i].name; i++ ){
        lua_pushstring( L, str_constants[i].name );
        lua_pushstring( L, str_constants[i].val );
        lua_rawset( L, -3 );
    }
    
    // set substance to __metable.__index field
    lua_rawset( L, -3 );
    // set __newindex function to __metable.__newindex filed
    lua_pushstring( L, "__newindex" );
    lua_pushcfunction( L, const_newindex );
    lua_rawset( L, -3 );
    // convert protected-table to metatable
    lua_setmetatable( L, -2 );
    
    return 1;
}

