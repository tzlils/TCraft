WINCC=i686-w64-mingw32-g++
LINCC=g++

CFLAGS= -Wall -lGL -ldl -lglfw -I/usr/include/bullet/ -lBulletDynamics -lBulletCollision -lLinearMath

WINFLAGS= -Wall -lopengl32 -lglfw3 -lglfw3dll
OBJS=$(shell ls src/*.c*) $(shell ls src/*/*.c*)

all:
	$(LINCC) $(CFLAGS) $(OBJS) -o out/main.out

start:
	./out/main.out
