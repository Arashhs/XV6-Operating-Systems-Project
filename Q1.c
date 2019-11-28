#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
int fd1[2];
int fd2[2];

pid_t childpid;
pipe(fd1);
pipe(fd2);



childpid = fork();
        
if(childpid  == -1) { //Error
	perror("fork");
	exit(1);
}

if(childpid == 0) { // 1256664876886345212
	/* Child process */
	// close(fd[0]);
	char getIn[50]; //input number
	read(fd[0], getIn, sizeof(getIn));

	printf("%s %d\n", getIn, sizeof(getIn));
	int numSize = 0;
	int i = 0;;
	for(i=0; getIn[i] != '\0' ; ++i);
	numSize = i;
	printf("%d\n", numSize);
	
	int sumOfEvens = 0;
	
	for(i=0; i<numSize; i++) {
		int d = getIn[i] - '0';
		if (d%2 == 0)
			sumOfEvens += d;
	}

	write(fd[1], sumOfEvens, sizeof(int));
	


	
}

else {
	/* Parent process */
//	close(fd[1]);
	char inputNum[50];
	printf("Enter your number: ");
	scanf("%s", inputNum);
	

	write(fd[1], inputNum, sizeof(inputNum));

	int evensSum;
	wait(3);
	read(fd[0], evensSum, sizeof(int));
	printf("%s The sum of even digits in the input number :%d\n", inputNum, evensSum);

	
}

return 0;
}
