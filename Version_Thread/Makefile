all: V_thread

V_thread: V_thread.cpp
	g++ -o V_thread V_thread.cpp `pkg-config --cflags --libs opencv4` -std=c++11

clean:
	rm -f V_thread

