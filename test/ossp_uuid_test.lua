local testcase = require('testcase')
local unpack = require('unpack')
local uuid = require('ossp-uuid')

function testcase.version()
    -- test that return a version
    assert.is_int(uuid.version())
end

function testcase.generate()
    -- test that return an uuid string
    local str = assert(uuid.generate(uuid.STR, uuid.V1))
    assert.re_match(str,
                    '^[[:xdigit:]]{8}-[[:xdigit:]]{4}-1[[:xdigit:]]{3}-[[:xdigit:]]{4}-[[:xdigit:]]{12}$')

    -- test that return an error
    local _, err = uuid.generate(uuid.STR, uuid.V3, uuid.NSX500, 'HelloWorld!')
    assert.is_nil(_)
    assert.match(err, 'invalid argument')

    -- test that throws an error if format is invalid
    err = assert.throws(function()
        uuid.generate(1234, uuid.V1)
    end)
    assert.match(err, '#1 .+[(]format must be', false)

    -- test that throws an error if version is invalid
    err = assert.throws(function()
        uuid.generate(uuid.STR, 1234)
    end)
    assert.match(err, '#2 .+[(]version must be', false)

    -- test that throws an error if namespace is invalid
    err = assert.throws(function()
        uuid.generate(uuid.STR, uuid.V3, 'invalid-namespace')
    end)
    assert.match(err, '#3 .+[(]invalid option', false)
end

function testcase.uuid_str()
    -- test that uuid str format
    for _, v in ipairs({
        {
            ver = 1,
            func = uuid.gen1str,
            args = {},
            exp = '^[[:xdigit:]]{8}-[[:xdigit:]]{4}-1[[:xdigit:]]{3}-[[:xdigit:]]{4}-[[:xdigit:]]{12}$',
        },
        {
            ver = 3,
            func = uuid.gen3str,
            args = {
                uuid.NSURL,
                'http://example.com/',
            },
            exp = '^[[:xdigit:]]{8}-[[:xdigit:]]{4}-3[[:xdigit:]]{3}-[[:xdigit:]]{4}-[[:xdigit:]]{12}$',
        },
        {
            ver = 4,
            func = uuid.gen4str,
            args = {},
            exp = '^[[:xdigit:]]{8}-[[:xdigit:]]{4}-4[[:xdigit:]]{3}-[[:xdigit:]]{4}-[[:xdigit:]]{12}$',
        },
        {
            ver = 5,
            func = uuid.gen5str,
            args = {
                uuid.NSURL,
                'http://example.com/',
            },
            exp = '^[[:xdigit:]]{8}-[[:xdigit:]]{4}-5[[:xdigit:]]{3}-[[:xdigit:]]{4}-[[:xdigit:]]{12}$',
        },
    }) do
        local str = assert(v.func(unpack(v.args)))
        assert.is_string(str)
        assert.re_match(str, v.exp)
    end
end

function testcase.uuid_siv()
    -- test that uuid siv format
    for _, v in ipairs({
        {
            ver = 1,
            func = uuid.gen1siv,
            args = {},
            exp = '^%d+$',
        },
        {
            ver = 3,
            func = uuid.gen3siv,
            args = {
                uuid.NSURL,
                'http://example.com/',
            },
            exp = '^%d+$',
        },
        {
            ver = 4,
            func = uuid.gen4siv,
            args = {},
            exp = '^%d+$',
        },
        {
            ver = 5,
            func = uuid.gen5siv,
            args = {
                uuid.NSURL,
                'http://example.com/',
            },
            exp = '^%d+$',
        },
    }) do
        local str = assert(v.func(unpack(v.args)))
        assert.is_string(str)
        assert.match(str, v.exp, false)
    end
end

function testcase.uuid_txt()
    -- test that uuid txt format
    for _, v in ipairs({
        {
            ver = 1,
            func = uuid.gen1txt,
            args = {},
            exp = 'version: 1',
        },
        {
            ver = 3,
            func = uuid.gen3txt,
            args = {
                uuid.NSURL,
                'http://example.com/',
            },
            exp = 'version: 3',
        },
        {
            ver = 4,
            func = uuid.gen4txt,
            args = {},
            exp = 'version: 4',
        },
        {
            ver = 5,
            func = uuid.gen5txt,
            args = {
                uuid.NSURL,
                'http://example.com/',
            },
            exp = 'version: 5',
        },
    }) do
        local str = assert(v.func(unpack(v.args)))
        assert.is_string(str)
        assert.match(str, v.exp)
    end
end

