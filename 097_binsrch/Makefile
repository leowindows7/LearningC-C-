test-bsearch: search.o test-bsearch.o
	g++ -o test-bsearch -ggdb search.o test-bsearch.o
search.o: search.cpp function.h
	g++ -Wall -ggdb -Werror -pedantic -std=gnu++98 -c search.cpp
test-bsearch.o: test-bsearch.cpp function.h
	g++ -ggdb -Wall -Werror -pedantic -std=gnu++98 -c test-bsearch.cpp

.PHONY:clean
clean:
	rm -f *~ *.o
