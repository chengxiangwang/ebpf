#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "k_demo.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,va_list args) {
	return vfprintf(stderr,format,args);
}


int main(int argc,char **argv){
	struct k_demo *ks;
	int err;
	libbpf_set_print(libbpf_print_fn);
	//open 
	ks = k_demo__open();
	if(!ks) {
		fprintf(stderr,"Failed to open BPF skeleton\n");
		return 1;
	}
	ks->bss->my_id = getpid();
	
	//load
	err = k_demo__load(ks);
	if(err) {
		fprintf(stderr,"Failed to load and verify BPF demo\n");
		goto cleanup;
	}


	//attach tracepoint handler
	err = k_demo__attach(ks);
	if(err) {
		fprintf(stderr,"Failed to attach BPF demo\n");
		goto cleanup;
	}

	printf("Successfully started! Please run `sudo cat /sys/kernel/debug/tracing/trace_pipe` "
	       "to see output of the BPF programs.\n");
	for(;;) {
		fprintf(stderr,".");
		sleep(1);
	}
cleanup:
	k_demo__destroy(ks);
	return -err;
}
