program: main.cpp
	g++ -O3 -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system
	
run: program
	./main
