all:cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa.o:cyoa.cpp cyoa.hpp
	g++ -o cyoa.o -c -std=gnu++98 -pedantic -g -Wall -Werror cyoa.cpp
cyoa-story4:cyoa-step4.cpp cyoa.o
	g++ -o cyoa-step4 -std=gnu++98 -pedantic -g -Wall -Werror cyoa-step4.cpp cyoa.o
cyoa-story3:cyoa-step3.cpp cyoa.o
	g++ -o cyoa-step3 -std=gnu++98 -pedantic -g -Wall -Werror cyoa-step3.cpp cyoa.o
cyoa-story2:cyoa-step2.cpp cyoa.o
	g++ -o cyoa-step2 -std=gnu++98 -pedantic -g -Wall -Werror cyoa-step2.cpp cyoa.o
cyoa-story1:cyoa-step1.cpp cyoa.o
	g++ -o cyoa-step1 -std=gnu++98 -pedantic -g -Wall -Werror cyoa-step1.cpp cyoa.o

.PHONY:clean
clean:
	rm -f cyoa *~ *.o
