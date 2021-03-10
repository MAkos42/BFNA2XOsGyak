#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main() {
	pid_t child_pid, wpid;
	int status = 0;

	if ((child_pid = fork()) == 0) {
        int a = 0/0;
	}

	while ((wpid = wait(&status)) > 0);
	return 0;

}
