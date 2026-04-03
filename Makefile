CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra


all: businessdb business_test

businessdb: business_lib.o businessdb.o
	$(CC) business_lib.o businessdb.o -o businessdb

business_test: business_lib.o business_test.o
	$(CC) business_lib.o business_test.o -o business_test

business_test.o: business_test.c business_lib.h
	$(CC) $(CFLAGS) -c business_test.c

business_lib.o: business_lib.c business_lib.h
	$(CC) $(CFLAGS) -c business_lib.c

businessdb.o: businessdb.c  business_lib.h
	$(CC) $(CFLAGS) -c businessdb.c

clean:
	rm -f business_lib.o businessdb.o business_test.o businessdb business_test

format:
	clang-format -i -style=file *.[ch]
