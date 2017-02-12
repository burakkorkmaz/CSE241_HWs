all: exe

exe:_mainTester.o BigramMap.o BigramDyn.o
	g++ _mainTester.o BigramMap.o BigramDyn.o -o exe

_mainTester.o:
	g++ -std=c++11 -c _mainTester.cpp

BigramMap.o:
	g++ -std=c++11 -c BigramMap.cpp

BigramDyn.o:
	g++ -std=c++11 -c BigramDyn.cpp
		
clean:
	rm -f *.o exe
