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
	close(fd1[1]);
	close(fd2[0]);
	
	char getIn[50]; //input number
	read(fd1[0], getIn, sizeof(getIn));

	int numSize = 0;
	int i = 0;;
	for(i=0; getIn[i] != '\0' ; ++i);
	numSize = i;
	
	int sumOfEvens;
	
	
	for(i=0; i<numSize; i++) {
		int d = getIn[i] - '0';
		if (d%2 == 0)
			sumOfEvens += d;
	}

	write(fd2[1], &sumOfEvens, sizeof(getIn));

	close(fd1[0]);
	close(fd2[1]);
	


	
}

else {
	/* Parent process */
//	close(fd[1]);

	close(fd1[0]);
	close(fd2[1]);

	char inputNum[50];
	printf("Enter your number: ");
	scanf("%s", inputNum);
	

	write(fd1[1], inputNum, sizeof(inputNum));

	int evensSum;
	read(fd2[0], &evensSum, sizeof(inputNum));
	printf("%s The sum of even digits in the input number :%d\n", inputNum, evensSum);
	
	close(fd1[1]);
	close(fd2[0]);

	
}

return 0;
}
