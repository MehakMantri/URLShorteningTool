CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LIBS = -lcurl

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o $(LIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f main main.o