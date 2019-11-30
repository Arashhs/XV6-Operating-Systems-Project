#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{
int fd1[2];
int fd2[2];

int childpid;
pipe(fd1);
pipe(fd2);



childpid = fork();
        
if(childpid  == -1) { //Error
	exit();
}

if(childpid == 0) { // 1256664876886345212
	/* Child process */
	// close(fd[0]);
	close(fd1[1]);
	close(fd2[0]);
	
	char getIn[50]; 
	read(fd1[0], getIn, sizeof(getIn)); //Get input from parent

	int numSize = 0;
	int i = 0;;
	for(i=0; getIn[i] != '\0' ; ++i);
	numSize = i - 1; //Number of digits of the input number

	
	int sumOfEvens = 0;
	
	/* Calculating sum of even digits */
	for(i=0; i<numSize; i++) {
		int d = getIn[i] - '0';
		if (d%2 == 0)
			sumOfEvens += d;
	}


	int sumDigits = 0;
	int sumTemp = sumOfEvens;
	
	/* Calculating number of digits of sumOfEvens */
	while(sumTemp != 0) {
	sumDigits++;
	sumTemp /= 10;
	}


	char outStr[100] = "The sum of even digits in the input number :";
	for(i=0; outStr[i] != '\0' ; i++);
	int outStrLen = i - 1;

	sumTemp = sumOfEvens;
	
	/* Concatenating outStr with sumOfEvens */
	
	for(i=sumDigits-1 ; i>=0; i--) {
		int tmp1 = sumTemp%10;
		sumTemp /= 10;
		char c = (char) (tmp1 + '0');
		outStr[outStrLen + i + 1] = c;
	}


	write(fd2[1], outStr, sizeof(outStr)); //Sending result to the parent

	close(fd1[0]);
	close(fd2[1]);
	
	exit();

	
}

else {
	/* Parent process */
//	close(fd[1]);

	close(fd1[0]);
	close(fd2[1]);

	char inputNum[50];
	printf(1, "Enter your number: ");
	read(0, inputNum, sizeof(inputNum)); //Getting input
	

	write(fd1[1], inputNum, sizeof(inputNum)); //Sending input to the child

	char result[100];
	wait();
	read(fd2[0], result, sizeof(result)); //Getting result from the child
	printf(1, "%s\n", result);
	
	close(fd1[1]);
	close(fd2[0]);

	exit();
}

}
