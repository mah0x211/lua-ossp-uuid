local uuid = require('uuid');

print( 'library version: ' .. uuid.version() );
print( 
    'version 1\n' .. 
    '  str: ' .. uuid.generate( uuid.str, uuid.v1 ) .. '\n' .. 
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v1 ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v1 ) );
print( 
    'version 3\n' .. 
    '  str: ' .. uuid.generate( uuid.str, uuid.v3, uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v3, uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v3, uuid.nsURL, 'http://example.com/' ) );
print( 
    'version 4\n' ..
    '  str: ' .. uuid.generate( uuid.str, uuid.v4 ) .. '\n' .. 
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v4 ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v4 ) );
print( 
    'version 5\n' ..
    '  str: ' .. uuid.generate( uuid.str, uuid.v5, uuid.nsURL, 'http://example.com/' ) .. '\n' ..
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v5, uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v5, uuid.nsURL, 'http://example.com/' ) );

