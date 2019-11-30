#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{
int childpid = fork();

if(childpid == 0) {
	
}

else {
	printf(1, "Child id: %d\n", childpid);
}

exit();

}
