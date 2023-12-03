all: V_openMP

V_openMP: V_openMP.cpp
	 g++ -o V_openMP V_openMP.cpp `pkg-config --cflags --libs opencv4` -std=c++11 -fopenmp

clean:
	rm -f V_openMP
