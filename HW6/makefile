all: exe

exe: _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o PFADyn.o
	g++ _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o PFADyn.o -o exe



_mainTester.o:
	g++ -c -std=c++11 _mainTester.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp
	
CPUProgramDyn.o: CPUProgramDyn.cpp
	g++ -c -std=c++11 CPUProgramDyn.cpp
	
Memory.o:
	g++ -c -std=c++11 Memory.cpp
	
Computer.o:
	g++ -c -std=c++11 Computer.cpp
	
PFADyn.o:
	g++ -c -std=c++11 PFADyn.cpp

	
clean:
	rm *.o exe
