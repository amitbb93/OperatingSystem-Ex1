#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include "md5.h"


int main()
{
	char str1[20], str2[32];
	char inbuf1[20];char inbuf2[32];
	int p1[2], p2[2]; 
	pipe(p1);pipe(p2);
	if (p1 < 0 || p2 < 0) exit(1); 
    
	printf("Hello user, please enter a string with maximum length of 20:\n");
	scanf("%s",str1);
	if(strlen(str1)>20){printf("You inserted wrong input");exit(3);}
	int f = fork();
  
	if (f > 0) { 
        write(p1[1], str1, strlen(str1));
		wait(NULL);
		if(read(p2[0], inbuf2, 32) > 0){
			printf("\n");
			for(int i=0;i<32;i++)
				printf("%c",inbuf2[i]);
			close(p1[0]);
			close(p2[1]);
			close(p1[1]);
			close(p2[0]);
		}
		else exit(2); 
    } 
    else{ 
        if(read(p1[0], inbuf1, strlen(str1)) > 0){
			std::string sm= md5(inbuf1);
			stpcpy(str2,sm.c_str());
			if(strlen(str2) == 32)write(p2[1], str2, 32);
			else printf("function does not work");
		}
		else exit(2); 
    } 

    return 0;
}