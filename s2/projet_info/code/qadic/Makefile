aled: $(wildcard qadic/*.o) test/t-ctx_init.o
	gcc -o main $(wildcard qadic/*.o) test/t-ctx_init.o -lgmp -lflint

$(wildcard qadic/*.o): $(wildcard qadic/*.c)
	cd qadic
	gcc -c $(wildcard *.c)
	cd ..

test/t-ctx_init.o: test/t-ctx_init.c
	gcc -o test/t-ctx_init.o -c test/t-ctx_init.c
