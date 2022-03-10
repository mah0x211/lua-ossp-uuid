local uuid = require('ossp-uuid');

print( 'library version: ' .. uuid.version() );
print( 
    'version 1 manual\n' .. 
    '  str: ' .. uuid.generate( uuid.str, uuid.v1 ) .. '\n' .. 
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v1 ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v1 ) );

print( 
    'version 1\n' .. 
    '  str: ' .. uuid.gen1str() .. '\n' .. 
    '  siv: ' .. uuid.gen1siv() .. '\n' .. 
    '  txt: \n' .. uuid.gen1txt() );

print( 
    'version 3 manual\n' .. 
    '  str: ' .. uuid.generate( uuid.str, uuid.v3, uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v3, uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v3, uuid.nsURL, 'http://example.com/' ) );

print( 
    'version 3\n' .. 
    '  str: ' .. uuid.gen3str( uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  siv: ' .. uuid.gen3siv( uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  txt: \n' .. uuid.gen3txt( uuid.nsURL, 'http://example.com/' ) );

print( 
    'version 4 manual\n' ..
    '  str: ' .. uuid.generate( uuid.str, uuid.v4 ) .. '\n' .. 
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v4 ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v4 ) );

print( 
    'version 4\n' ..
    '  str: ' .. uuid.gen4str() .. '\n' .. 
    '  siv: ' .. uuid.gen4siv() .. '\n' .. 
    '  txt: \n' .. uuid.gen4txt() );

print( 
    'version 5 manual\n' ..
    '  str: ' .. uuid.generate( uuid.str, uuid.v5, uuid.nsURL, 'http://example.com/' ) .. '\n' ..
    '  siv: ' .. uuid.generate( uuid.siv, uuid.v5, uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  txt: \n' .. uuid.generate( uuid.txt, uuid.v5, uuid.nsURL, 'http://example.com/' ) );

print( 
    'version 5\n' ..
    '  str: ' .. uuid.gen5str( uuid.nsURL, 'http://example.com/' ) .. '\n' ..
    '  siv: ' .. uuid.gen5siv( uuid.nsURL, 'http://example.com/' ) .. '\n' .. 
    '  txt: \n' .. uuid.gen5txt( uuid.nsURL, 'http://example.com/' ) );

