#include <stdlib.h>
#include <stdio.h>

void print_uids(const char* str_relation);

int main(int argc, char* argv[]) {
	print_uids("new process spawned");
	return 0;
}

void print_uids(const char* str_relation) {
	printf("%s\n", str_relation);
	
	int proc_euid = geteuid();
        printf("euid: %i\n", proc_euid);

        int proc_uid = getuid();
        printf("uid %i\n", proc_uid);
}
