all:
	g++ -std=c++11 Piece.cpp Board.cpp Graphics.cpp -lncurses Game.cpp -pthread main.cpp -o main.o
