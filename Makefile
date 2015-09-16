CCOPTS=-I src -Wall -O2 -Wconversion -Wno-sign-conversion -std=c++14

all: sim

clean:
	rm lib/*.o sim
	
lib:
	mkdir lib

lib/atoms.o: src/atoms.hpp src/atoms.cpp | lib
	$(CXX) $(CCOPTS) -c src/atoms.cpp -o lib/atoms.o

lib/lennardjones.o: src/atoms.hpp src/lennardjones.hpp src/lennardjones.cpp | lib
	$(CXX) $(CCOPTS) -c src/lennardjones.cpp -o lib/lennardjones.o
	
lib/verlet.o: src/atoms.hpp src/lennardjones.hpp src/verlet.hpp src/verlet.cpp | lib
	$(CXX) $(CCOPTS) -c src/verlet.cpp -o lib/verlet.o

sim: lib/verlet.o lib/lennardjones.o lib/atoms.o
	$(CXX) $(CCOPTS) lib/verlet.o lib/lennardjones.o lib/atoms.o src/sim.cpp -o sim
