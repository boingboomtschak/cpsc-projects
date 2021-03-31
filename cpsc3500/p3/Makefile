CC=gcc
ARGS=-Wall -Werror -pthread

all: pzip

pzip: pzip.c
	$(CC) pzip.c $(ARGS) -o pzip

test: pzip
	./pzip one.txt > one.z
	diff one.z_orig one.z
	./pzip two.txt > two.z
	diff two.z_orig two.z
	./pzip lorem.txt > lorem.z
	diff lorem.z_orig lorem.z
	./pzip pride.txt > pride.z
	diff pride.z_orig pride.z
	./pzip war.txt > war.z
	diff war.z war.z_orig

test-comprehensive: pzip
	./pzip $(c).txt > $(c).z
	./wunzip $(c).z > t_$(c)
	./wunzip $(c).z_orig > t_$(c)_orig
	diff t_$(c) t_$(c)_orig
	hexdump -C $(c).z > hex_$(c)
	hexdump -C $(c).z_orig > hex_$(c)_orig
	diff hex_$(c) hex_$(c)_orig

clean: pzip
	rm hex_*
	rm t_*

lazy: pzip.c
	$(CC) pzip.c -pthread -o pzip

optimized: pzip.c
	$(CC) pzip.c $(ARGS) -O -o pzip 

debug: pzip.c
	$(CC) pzip.c $(ARGS) -g -o pzip