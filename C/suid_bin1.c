#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void print_uids();

int main(int argc, char* argv[]) {
	
	int pid = 0;

	if((pid = fork()) != 0) {
		execvp("suid_bin2.bin", argv);
		printf("!!ERROR!!: %s\n", strerror(errno));
	} else {
		print_uids("parent");	
	}	
	return 0;
}

void print_uids(const char* str_relation) {
	printf("%s\n", str_relation);
	
	int proc_euid = geteuid();
        printf("euid: %i\n", proc_euid);

        int proc_uid = getuid();
        printf("uid %i\n", proc_uid);
}
