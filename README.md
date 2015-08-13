#lua-ossp-uuid

OSSP uuid bindings for lua

## Dependencies

- OSSP uuid: http://www.ossp.org/pkg/lib/uuid/

## Installation

    luarocks install ossp-uuid --from=http://mah0x211.github.io/rocks/

## Methods

    uuid.generate( format, version, [namespace:string, str:string] );

    uuid.gen1str();
    uuid.gen1siv();
    uuid.gen1txt();

    uuid.gen3str( namespace:string, str:string );
    uuid.gen3siv( namespace:string, str:string );
    uuid.gen3txt( namespace:string, str:string );

    uuid.gen4str();
    uuid.gen4siv();
    uuid.gen4txt();

    uuid.gen5str( namespace:string, str:string );
    uuid.gen5siv( namespace:string, str:string );
    uuid.gen5txt( namespace:string, str:string );


## Constants

### Format

    uuid.str
    uuid.siv
    uuid.txt

### Version

    uuid.v1
    uuid.v3
    uuid.v4
    uuid.v5

### Namespace

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
