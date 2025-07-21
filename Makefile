all:
	g++ -o game main.cc Player.cc Player.hh Camera.cc Camera.hh -lraylib -lGL -lm -lpthread -ldl -lrt -lX11