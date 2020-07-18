
example: example.cpp transition.h output.h
	c++ example.cpp -o example

.PHONY: clean
clean:
	rm example

