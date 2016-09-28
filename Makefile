CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall
DEBUGFLAG = -DDEBUG
EXECUTABLE = \
	clz_recursive clz_iteration \
	clz_byteshift clz_binarysearch \
	benchmark_clz

default: clz.o
	$(CC) $(CFLAGS) clz.o time_test.c -DRECURSIVE -o clz_recursive
	$(CC) $(CFLAGS) clz.o time_test.c -DITERATION -o clz_iteration
	$(CC) $(CFLAGS) clz.o time_test.c -DBYTESHIFT -o clz_byteshift
	$(CC) $(CFLAGS) clz.o time_test.c -DBINARYSEARCH -o clz_binarysearch
	$(CC) $(CFLAGS) clz.o benchmark_clz.c -o benchmark_clz

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

check:
	time ./clz_recursive
	time ./clz_iteration
	time ./clz_byteshift
	time ./clz_binarysearch

debug: clz.o
	$(CC) $(CFLAGS) clz.o time_test.c -DRECURSIVE $(DEBUGFLAG) -o clz_recursive
	$(CC) $(CFLAGS) clz.o time_test.c -DITERATION $(DEBUGFLAG) -o clz_iteration
	$(CC) $(CFLAGS) clz.o time_test.c -DBYTESHIFT $(DEBUGFLAG) -o clz_byteshift
	$(CC) $(CFLAGS) clz.o time_test.c -DBINARYSEARCH $(DEBUGFLAG) -o clz_binarysearch
	$(CC) $(CFLAGS) clz.o benchmark_clz.c -o benchmark_clz

gencsv: default
	printf ",recursive,iteration,byte-shift,binary search technique\n" > result_clock_gettime.csv
	for i in `seq 1 1 100`; do \
		printf "%d," $$i;\
		./benchmark_clz $$i; \
	done >> result_clock_gettime.csv

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv
