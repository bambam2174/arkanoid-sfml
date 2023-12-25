all: release debug

release: build/release/arkanoid

build/release/arkanoid: main.cpp build/release/images
	mkdir -p build/release
	clang++ -O3 main.cpp -o build/release/arkanoid -lsfml-graphics -lsfml-window -lsfml-system

#debug: main.cpp
#	clang++ -g main.cpp -o build/debug/arkanoid -lsfml-graphics -lsfml-window -lsfml-system 

debug: build/debug/arkanoid


build/debug/arkanoid: main.cpp build/debug/images
	mkdir -p build/debug
	clang++ -g main.cpp -o build/debug/arkanoid -lsfml-graphics -lsfml-window -lsfml-system 
	
build/release/images: 
	mkdir -p build/release/images
	cp ./images/* ./build/release/images/

build/debug/images:
	mkdir -p build/debug/images
	cp -r ./images/* ./build/debug/images

compile: main.o

main.o: main.cpp
	clang++ -c main.cpp

link: arkanoid

arkanoid: main.o
	clang++ main.o -o arkanoid -lsfml-graphics -lsfml-window -lsfml-system

clean: 
	rm -f *.o arkanoid
	rm -rf build

install:
	ln -s "${PWD}/build/release/arkanoid" /usr/local/bin
