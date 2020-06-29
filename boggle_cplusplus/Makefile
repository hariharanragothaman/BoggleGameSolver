.PHONY: default
default: solve

.PHONY: generate
generate:
	g++ -o boggle_generator boggle_generator.cpp -std=c++11


.PHONY: solve
solve:
	g++ -o boggle_solver boggle_solver.cpp -std=gnu++0x
	./boggle_solver

.PHONY: shared
shared:
	g++ -fpic -c  boggle_solver.cpp -o boggle_solver.o -std=gnu++0x
	g++ -shared -o boggle_solver.so boggle_solver.o


.PHONY: clean
clean:
	rm -rf boggle_solver boggle_generator *.o *.so test

.PHONY: distclean
distclean:
	git clean -fdX
