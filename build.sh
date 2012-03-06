gcc src/epollserver.c -o build/epollserver.o
gcc src/epollclient.c -o build/epollclient.o

cp build/epollserver.o install/epollserver
cp build/epollclient.o install/epollclient
