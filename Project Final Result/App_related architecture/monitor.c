#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>

void sig_handler(int signo)
{
	/*
	 * not done
	 * 1. Request packet info through IPC
	 * 2. Send fake ACK
	 * Actually, how to construct fack ACK is covered in other directories...
	 */
}

void register_pid(void)
{
	int pid;
	FILE *fp;
	pid = getpid();
	fp = fopen("/proc/sender_pid", "w+");
	if(fp) {
		fprintf(fp, "%d", pid);
		fclose(fp);
	} else
		perror("fopen proc entry");
}

int main() {
	int pid;
	int my_pid;
	pid  = fork();
	if(pid<0) exit(1); // fork error
	if(pid>0) exit(0); // parent exits */

	if(signal(SIGUSR1, sig_handler) == SIG_ERR)
		perror("signal");

	register_pid();	// kernel thread and this thread change information via proc file system

	for(;;) {
		sleep(UINT_MAX);
	}
}
