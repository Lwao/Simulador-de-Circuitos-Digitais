all:METODOS
	g++ circuito-main.cpp circuito.o -o previa_circuito
METODOS:
	g++ -c circuito.cpp
