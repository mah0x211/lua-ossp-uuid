#lua-ossp-uuid

OSSP uuid bindings for lua

## Install

    luarocks make ./uuid-1.0-0.rockspec OSSP_UUID_DIR=</path/to/ossp-uuid>

## Methods

    uuid.generate( format, version, [namespace:string, str:string] );

### format

    uuid.str
    uuid.siv
    uuid.txt

### version

    uuid.v1
    uuid.v3
    uuid.v4
    uuid.v5

### namespace

    uuid.nsNil:  'nil' 
    uuid.nsDNS:  'ns:DNS'
    uuid.nsURL:  'ns:URL'
    uuid.nsOID:  'ns:OID'
    uuid.nsx500: 'ns:X500'

## Example

    local uuid = require('ossp-uuid');

    print( 
        "version 1\n" ..
        '  str: ' .. uuid.generate( uuid.str, uuid.v1 ) .. "\n" .. 
        '  siv: ' .. uuid.generate( uuid.siv, uuid.v1 ) .. "\n" ..
        "  txt: \n" .. uuid.generate( uuid.txt, uuid.v1 ) );
    print( 
        "version 3\n" ..
        '  str: ' .. uuid.generate( uuid.str, uuid.v3, uuid.nsURL, 'http://example.com/' ) .. "\n" .. 
        '  siv: ' .. uuid.generate( uuid.siv, uuid.v3, uuid.nsURL, 'http://example.com/' ) .. "\n" .. 
        '  txt: ' .. uuid.generate( uuid.txt, uuid.v3, uuid.nsURL, 'http://example.com/' ) );
    print( 
        "version 4\n" ..
        '  str: ' .. uuid.generate( uuid.str, uuid.v4 ) .. "\n" .. 
        '  siv: ' .. uuid.generate( uuid.siv, uuid.v4 ) .. "\n" .. 
        "  txt: \n" .. uuid.generate( uuid.txt, uuid.v4 ) );
    print( 
        "version 5\n" ..
        '  str: ' .. uuid.generate( uuid.str, uuid.v5, uuid.nsURL, 'http://example.com/' ) .. "\n" ..
        '  siv: ' .. uuid.generate( uuid.siv, uuid.v5, uuid.nsURL, 'http://example.com/' ) .. "\n" .. 
        "  txt: \n" .. uuid.generate( uuid.txt, uuid.v5, uuid.nsURL, 'http://example.com/' ) );
