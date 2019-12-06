#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
int i, argint = 0;
char *a = argv[1];
for(i=0;a[i] != '\0'; i++);
if (i == 1) {
	argint = a[0] - '0';
}
changePolicy(argint);

int id = fork();
if (id == 0)
	changePriority(1);
int z,x;
 for ( z = 0; z < 10; z += 0.0001 ) {
         x =  x + 3.14 * 89.64;
	printf(1, "PID: %d\n", getpid());
	}

exit();
} 
