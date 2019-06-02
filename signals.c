#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#define SIGCATHCHER  1

void sigCathcher();
int pids[5] = {0,0,0,0,0};
int savePrev;
int pid;

int main()
{
	signal(SIGCATHCHER, sigCathcher);
    pid = getpid();
	savePrev = 0;
    for (int i = 0; i < 5; i++)// 5 processes
    {
        if ((pids[i] = fork()) < 0){perror("fork didn't work successfully");exit(1);}
		if (pids[i] == 0)
        {
            printf("PID %d ready \n", getpid()); //Each process prints a msg with his PID when he is ready
			savePrev = pids[i-1];
            break;
        }
    }
	
	sleep(1);
    if (pids[4] != 0)
        kill(pids[4], SIGCATHCHER);

    sleep(1);
    if(pid == getpid())
    for (int i = 0; i < 5; i++) {
        int temp = wait(&pid); // The parent collects all the zombies and then exits
        printf("Process %d is dead \n", temp);
    }
    return 0;
}

void sigCathcher()
{
    printf("PID %d caught one \n", getpid());
    if (savePrev != 0)
		kill(savePrev, SIGCATHCHER); // The signals activate the procedure sigCathcher which sends a signal to the next process (his sibling) by kill command.
	exit(0); //Each child process exits after receiving the signal
}