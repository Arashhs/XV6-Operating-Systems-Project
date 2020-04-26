#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{

fork();
fork();
fork();

char res[50] = {' '};
res[0] = 'P';
res[1] = 'I';
res[2] = 'D';
res[3] = ':';
res[4] = ' ';
int pid = getpid();
int i;
for(i=0; pid!=0; i++, pid /= 10) {
	res[10-i] = ((pid % 10) + '0');

}
res[13] = ' ';
res[14] = 'P';
res[15] = 'P';
res[16] = 'I';
res[17] = 'D';
res[18] = ':';
res[19] = ' ';
int ppid = getppid();
for(i=0; ppid!=0; i++, ppid /= 10) {
	res[21-i] = ((ppid % 10) + '0');

}

int child = getChildren(getpid());
res[22] = ' ';
res[23] = 'C';
res[24] = 'H';
res[25] = 'I';
res[26] = 'L';
res[27] = 'D';
res[28] = 'R';
res[29] = 'E';
res[30] = 'N';
res[31] = ':';
res[32] = ' ';
for(i=0; child!=0; i++, child /= 10) {
	res[40-i] = ((child%10) + '0');

}

res[45] = '\n';

write(1, res, sizeof(res));


wait();
wait();
wait();
exit();
}
