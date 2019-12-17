#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    changePolicy(1); //XV6 modified original policy
    struct timeVariables *tv = malloc (sizeof (struct timeVariables));
    int id = fork();
    if(id==0) { // Child Process 
        int i = 0, j=0;
        for(i=0;i<2;i++)
            fork(); 
        for(j=0; j<100; j++)
            printf(2, "PID: %d\n", getpid());
        waitForChild(tv);
        int taTime, wtime;
        taTime = tv->terminationTime - tv->creationTime;
        wtime = taTime - tv->runningTime;
        printf(2, "TA Time: %d  WTime: %d\n", taTime, wtime);
        waitForChild(tv);

    } 
    else { // Parent Process
        struct timeVariables *tv = malloc (sizeof (struct timeVariables));
        int k;
     //   int taTime, wtime;
        for(k=0; k<9; k++) {
            waitForChild(tv);
       //     taTime = tv->terminationTime - tv->creationTime;
         //   wtime = taTime - tv->runningTime;
            //printf(1, "tv: %d %d %d %d %d\n", tv->creationTime, tv->readyTime, tv->runningTime, tv->sleepingTime, tv->terminationTime);
            //printf(1, "TA Time: %d  WTime: %d\n", taTime, wtime);
        }


    }

    exit();




} 
