cd ../space-invaders-emulator/wasm
emcc src/*.c -Iinclude -o ../index.html -s USE_SDL=2 -s FULL_ES2=1 -s ALLOW_MEMORY_GROWTH=1
cd ..
cd ..