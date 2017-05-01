#include "types.h"
#include "user.h"


int main(int argc, char **argv)
{
	// printf(1,"hello world (pid = %d)\n", (int) getpid());
	int ret = fork();
	if (ret < 0)
	{
		printf(1,"Error: fork\n");
		exit();
	}
	else if (ret == 0)
	{	
		int i = 0;
		for (i = 0; i < 150; i++){
		printf(1,"Child (pid = %d),(prio = %d)\n", (int) getpid(), (int)getprio());
		}
	}
	else
	{
		wait();
		printf(1,"Parent of %d (pid = %d),(prio = %d)\n", ret, (int) getpid(), (int)getprio());
	}
	exit();
}