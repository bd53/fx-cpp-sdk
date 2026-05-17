local cwd = os.getcwd()
local musl_target = "x86_64-unknown-linux-musl"
local wasmtime_root = ("%s/vendor/wasmtime"):format(cwd)
local wasmtime_release = ("%s/target/%s/release"):format(wasmtime_root, musl_target)

os.execute("git submodule update --init vendor/wasmtime")
if not os.isfile(("%s/libwasmtime.a"):format(wasmtime_release)) then
        os.execute(("rustup target add %s"):format(musl_target))
        os.execute(("cargo build --release -p wasmtime-c-api --target %s --manifest-path %s/Cargo.toml"):format(musl_target, wasmtime_root))
end

return function()
        filter {}
        includedirs { ("%s/crates/c-api/include"):format(wasmtime_root) }
        local include = os.matchdirs(("%s/build/wasmtime-c-api-impl-*/out/include"):format(wasmtime_release))
        if #include > 0 then
                includedirs { include[1] }
        end
        linkoptions {
                ("%s/libwasmtime.a"):format(wasmtime_release),
                "-lpthread", "-ldl", "-lm",
        }
end
