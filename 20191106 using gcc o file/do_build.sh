mkdir build
cd build
rm -rf *

gcc -c ../main.c
gcc -c ../utils.c

gcc main.o utils.o -o main # default is dynamic 
# gcc -static main.o utils.o -lc -o main # no dynamic linking, bigger file 


./main $1
# readelf -s main # ELF information 

# ldd main

cd ..

