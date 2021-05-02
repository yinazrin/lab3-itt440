#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
	int pipefds[2], num, i, flag=0;
	void sigint_handler(int sig);

	if(signal(SIGINT,sigint_handler) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}

	if(pipe(pipefds) == -1)
	{
		perror("pipe");
		exit;
	}

	pid_t pid = fork();

	if(pid == 0)
	{

		printf("Please enter a number:");
		scanf("%d",&num);

		close(pipefds[0]);
		write(pipefds[1],&num,sizeof(num));
		exit;
	}
  
	if (pid>0)
	{
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0],&num,sizeof(num));

    		for (i=2;i<=num/2;++i)
		{
     			if(num % i==0)
			{
      				flag =1;
      				break;
			}
		}

    		if(num==1)
		{
       			printf("1 is not a prime number.\n");
    		}
    		else
		{
			if(flag==0)
         		printf("%d is a prime number.\n",num);

   			 else
    			printf("%d is not a prime number.\n",num);
   	 	}

    		close(pipefds[0]);
  	}

  	return 0;
}

void sigint_handler(int sig)
{
  printf("Stop!!!\n");
}

