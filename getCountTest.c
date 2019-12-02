#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{

//int a = getCount(2);
int i, argint = 0;
char *a = argv[1];
for(i=0;a[i] != '\0'; i++);
if (i == 1) {
	argint = a[0] - '0';
}
else if (i == 2) {
	argint = a[0] - '0';
	argint *= 10;
	argint += (a[1] - '0');
}
wait();
wait();
printf(1, "%d\n", getCount(argint));
exit();
}
