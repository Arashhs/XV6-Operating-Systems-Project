#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{
int childpid = fork();


if(childpid > 0) {
//	printf(1, "id: %d\n", getpid());
//	printf(1, "getChildren: %d\n", getChildren(getpid()));


}

else if(childpid == 0) {

//	printf(1, "Child id: %d\n", getpid());
//	printf(1, "Parent id: %d\n", getppid());
//	write(1, "Hello child", 13);

}
	write(1, "PID: ", 5);
	int pid = getpid();
	printf(1, "%d", pid);
wait();
exit();

}
