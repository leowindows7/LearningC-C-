CFLAGS = -std=gnu99 -pedantic -Wall
maxSeq: maxSeq.c
	gcc $(CFLAGS) -o maxSeq maxSeq.c test-subseq.c
.PHONY: clean
clean:
	rm -f maxSeq *.o *.c~ *.h~
