local rockspec = ...

local UUID_DIR = "./deps/uuid-1.6.2"

local function run(cmd)
    print("preprocess: " .. cmd)
    local ok, _, code = os.execute(cmd)
    if ok == true or ok == 0 then
        return
    end
    error("preprocess command failed: " .. cmd .. " (code=" .. tostring(code) .. ")")
end

local f = io.open(UUID_DIR .. "/.libs/libuuid.a", "rb")
if f then
    f:close()
    print("preprocess: " .. UUID_DIR .. "/.libs/libuuid.a already built")
    return
end

run("cd ./deps && tar -xzf ./uuid-1.6.2.tar.gz")
run("cd " .. UUID_DIR .. " && CFLAGS='-O2 -fPIC' ./configure --disable-shared --without-perl --without-php --without-pgsql")
run("cd " .. UUID_DIR .. " && make")
