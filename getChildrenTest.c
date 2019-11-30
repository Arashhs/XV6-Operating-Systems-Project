#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{
int childpid = fork();
fork();


if(childpid > 0) {
printf(0, "--PID: %d	PPID: %d	GetChildren: %d\n", getpid(), getppid(), getChildren(getpid()));
wait();
exit();


}

else if(childpid == 0) {


}

}
