#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
int fd[2];
pid_t childpid;
pipe(fd);



childpid = fork();
        
if(childpid  == -1) { //Error
	perror("fork");
	exit(1);
}

if(childpid == 0) {
	/* Child process closes up input side of pipe */
	// close(fd[0]);
	
}

else {
	/* Parent process closes up output side of pipe */
//	close(fd[1]);
	char inputNum[50];
	printf("Enter your number: ");
	scanf("%s", inputNum);
	printf("%s %d\n", inputNum, sizeof(inputNum));
	write(fd[1], inputNum, sizeof(inputNum));
	
}

return 0;
}
