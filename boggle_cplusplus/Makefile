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
	g++ -ggdb -shared -o boggle_solver.so boggle_solver.o

.PHONY: test
test:
	g++ -ggdb -o test test.h test.cpp boggle_solver.so -std=gnu++0x


.PHONY: clean
clean:
	rm -rf boggle_solver boggle_generator *.o *.so test

.PHONY: distclean
distclean:
	git clean -fdX
