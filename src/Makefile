.PHONY: build test
CC= g++ -std=c++17 -Wall -Werror -Wextra 
LFLAGS = -lgtest
OS = $(shell uname -s)
OPEN = open
ifeq ($(OS), Linux)
	LFLAGS += -lgtest -lpthread -lrt -lsubunit
	OPEN = xdg-open
endif

all: install

rebuild: clean uninstall all

install: build
	mkdir $(HOME)/Desktop/3DViewer_v2.0 
	mkdir $(HOME)/Desktop/3DViewer_v2.0/objects
	cp -rf ./build/Viewer.app $(HOME)/Desktop/3DViewer_v2.0
	cp objects/* $(HOME)/Desktop/3DViewer_v2.0/objects

build: 
	mkdir -p build
	cp -r view/* build/
ifeq ($(OS), Linux)
		cd build; qmake6
else
		cd build; qmake
endif
		make all -C ./build

uninstall:
	rm -rf $(HOME)/Desktop/3DViewer_v2.0
	rm -rf /Users/Shared/settings.conf

clean:
	$(RM)  *.o *.a *.out test
	$(RM) -rf build
	$(RM) view/.clang-format .clang-format
	$(RM) 3DViewer_v2.0.tar

dvi: 
	$(OPEN) documentation/dvi.html
	
dist:
	tar --totals -czf 3DViewer_v2.0.tar ./*

test:
	$(CC) test.cpp model.cpp -o test $(LFLAGS)
	./test

linter:
	cp ../materials/linters/.clang-format .clang-format
	cp ../materials/linters/.clang-format view/.clang-format
	clang-format -n *.cpp *.h view/*.cpp view/*.h

leaks: test
	CK_FORK=no leaks --atExit -- ./test

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./test

model.a: model.o
	ar rvs model.a *.o 

model.o: model.cpp model.h
	$(CC) -c model.cpp




