all: V_secuencial

V_secuencial: V_secuencial.cpp
	g++ -o V_secuencial V_secuencial.cpp `pkg-config --cflags --libs opencv4` -std=c++11

clean:
	rm -f V_secuencial
