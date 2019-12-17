#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    changePolicy(1); //XV6 modified original policy
    if(0==fork())
		fork();
	for(;;);


} 
