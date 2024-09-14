mkdir temp
cd ./temp
cmake -B./ -S../
make
cd ../
rm -r temp