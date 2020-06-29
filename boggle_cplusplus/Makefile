.PHONY: default
default: solve

.PHONY: generate
generate:
	g++ -o boggle_generator boggle_generator.cpp -std=c++11


.PHONY: solve
solve:
	g++ -o boggle_solver boggle_solver.cpp -std=gnu++0x
	./boggle_solver

.PHONY: clean
clean:
	rm -rf boggle_solver boggle_generator

.PHONY: distclean
distclean:
	git clean -fdX
