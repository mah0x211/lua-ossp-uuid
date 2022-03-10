# lua-ossp-uuid

[![test](https://github.com/mah0x211/lua-ossp-uuid/actions/workflows/test.yml/badge.svg)](https://github.com/mah0x211/lua-ossp-uuid/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/mah0x211/lua-ossp-uuid/branch/master/graph/badge.svg)](https://codecov.io/gh/mah0x211/lua-ossp-uuid)

OSSP uuid bindings for lua.


## Installation

```sh
luarocks install ossp-uuid
```

## Usage

```lua
local uuid = require('ossp-uuid');

print( 
    "version 1\n" ..
    '  str: ' .. uuid.gen1str() .. "\n" .. 
    '  siv: ' .. uuid.gen1siv() .. "\n" ..
    "  txt: \n" .. uuid.gen1txt() )
print( 
    "version 3\n" ..
    '  str: ' .. uuid.gen3str( uuid.NSURL, 'http://example.com/' ) .. "\n" .. 
    '  siv: ' .. uuid.gen3siv( uuid.NSURL, 'http://example.com/' ) .. "\n" .. 
    '  txt: ' .. uuid.gen3txt( uuid.NSURL, 'http://example.com/' ) )
print( 
    "version 4\n" ..
    '  str: ' .. uuid.gen4str() .. "\n" .. 
    '  siv: ' .. uuid.gen4siv() .. "\n" .. 
    "  txt: \n" .. uuid.gen4txt() )
print( 
    "version 5\n" ..
    '  str: ' .. uuid.gen5str( uuid.NSURL, 'http://example.com/' ) .. "\n" ..
    '  siv: ' .. uuid.gen5siv( uuid.NSURL, 'http://example.com/' ) .. "\n" .. 
    "  txt: \n" .. uuid.gen5txt( uuid.NSURL, 'http://example.com/' ) )
```


## str, err = uuid.generate( format, version, [namespace, name] )

creates a new universally unique identifier.

**Parameters**

- `format:integer`: specify the following format;
  - `uuid.STR`, `uuid.SIV` or  `uuid.TXT`
- `version:integer`: specify the following version;
  - `uuid.V1`, `uuid.V3`, `uuid.V4` or `uuid.V5`
- `namespace:string`: specify the following namespace;
  - `uuid.NSNIL`, `uuid.NSDNS`, `uuid.NSURL`, `uuid.NSOID` or `uuid.NSX500`
- `name:string`: specify the name string.

**Returns**

- `str:string`: a generated uuid string.
- `err:string: error message.


## str, err = uuid.gen1str()

equivalent to `uuid.generate( uuid.STR, uuid.V1 )`.

## str, err = uuid.gen1siv()

equivalent to `uuid.generate( uuid.SIV, uuid.V1 )`.

## str, err = uuid.gen1txt()

equivalent to `uuid.generate( uuid.TXT, uuid.V1 )`.

## str, err = uuid.gen3str( namespace, name )

equivalent to `uuid.generate( uuid.STR, uuid.V3, namespace, name )`.

## str, err = uuid.gen3siv( namespace, name )

equivalent to `uuid.generate( uuid.SIV, uuid.V3, namespace, name )`.

## str, err = uuid.gen3txt( namespace, name )

equivalent to `uuid.generate( uuid.TXT, uuid.V3, namespace, name )`.

## str, err = uuid.gen4str()

equivalent to `uuid.generate( uuid.STR, uuid.V4 )`.

## str, err = uuid.gen4siv()

equivalent to `uuid.generate( uuid.SIV, uuid.V4 )`.

## str, err = uuid.gen4txt()

equivalent to `uuid.generate( uuid.TXT, uuid.V4 )`.

## str, err = uuid.gen5str( namespace, name )

equivalent to `uuid.generate( uuid.str, uuid.v5, namespace, name )`.

## str, err = uuid.gen5siv( namespace, name )

equivalent to `uuid.generate( uuid.siv, uuid.v5, namespace, name )`.

## str, err = uuid.gen5txt( namespace, name )

equivalent to `uuid.generate( uuid.txt, uuid.v5, namespace, name )`.

