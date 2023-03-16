all: clean compile
	sudo ./u_demo
compile:
	clang-12 -g -O2 -target bpf -c k_demo.c -o k_demo.o
	bpftool gen skeleton k_demo.o > k_demo.h
	clang-12 -g -O2 -Wall -I . -o u_demo.o -c u_demo.c
	clang-12 -g -O2 -Wall u_demo.o -static -lbpf -lelf -lz -o u_demo
clean:
	rm -f *.o u_demo
