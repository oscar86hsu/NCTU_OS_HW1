#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	pid = fork();//fork0
	if(pid==0)
		printf("fork0: I'm %d, my parent is %d\n",(int)getpid(),getppid());
	else
		wait(NULL);
	for(int i=0;i<2;i++)
	{
		if(pid==0)
		{
			pid = fork();//fork1
			if(pid == 0)
				printf("fork1-%d: I'm %d, my parent is %d\n",i,(int)getpid(),getppid());
			else
				wait(NULL);
			pid = fork();//fork2
			if(pid == 0)
				printf("fork2-%d: I'm %d, my parent is %d\n",i,(int)getpid(),getppid());
			else
				wait(NULL);
		}
		else if(pid > 0)
		{
			wait(NULL);
			pid = fork();//fork3
			if(pid == 0)
				printf("fork3-%d: I'm %d, my parent is %d\n",i,(int)getpid(),getppid());
			else
				wait(NULL);
		}
		else
		{
			printf("Error");
		}
	}
	return 0;

}