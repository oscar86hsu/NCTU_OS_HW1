#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int fork3()
{
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		printf("Fork3. I'm the child %d, my parent is %d\n",getpid(),getppid());
		return 0;
	}
	else if(pid>0)
	{
		wait(NULL);
		return 0;
	}
	else
	{
		fprintf(stderr, "Fork Failed");
		return 1;
	}
}

int main()
{
	int status;
	pid_t pid1,pid2;
	printf("Main Process ID : %d\n", getpid());
	pid1=fork();
	if(pid1==0)
	{
		printf("Fork1. I'm the child %d, my parent is %d\n",getpid(),getppid());
		pid2=fork();
		if(pid2==0)
		{
			printf("Fork2. I'm the child %d, my parent is %d\n",getpid(),getppid());
			return fork3();
		}
		else if(pid2>0)
		{
			wait(NULL);
			return fork3();
		}
		else
		{
			fprintf(stderr, "Fork Failed");
			return 1;
		}
	}
	else if(pid1>0)
	{
		wait(NULL);
		return fork3();
	}
	else
	{
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	
	
}