cmake -B./build ./src/rcon && make -s -C ./build
cp ./build/libmcrcon.so /usr/local/lib
rsync -arvz --progress --include='*.hpp' --include="*/" --exclude="*" ./src/rcon headers/
cp -r headers/* /usr/local/include/mcrcon
rm -r headers/