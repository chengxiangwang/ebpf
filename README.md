# ebpf
##libbpf
	```shell
	sudo apt-get install libbpf-dev zlib1g-dev libelf-dev libfl-dev

	#install  libbpf
	git clone https://github.com/libbpf/libbpf.git
	make && sudo make install
	# install bpftool
	git clone --recurse-submodules https://github.com/libbpf/bpftool.git
	git submodule update --init
	cd bpftool/src
	make && sudo make install

	# generate vmlinux.h
	sudo bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

	```
