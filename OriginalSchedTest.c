#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    changePolicy(1); //Set scheduling policy to Modified Original Scheduling Policy
    struct timeVariables * tv = malloc (sizeof (struct timeVariables));

    // printf( 1, "[dad] pid %d\n", getpid() );
    char printData[10];
    printData[3] = ':';
    printData[4] = ' ';
    printData[9] = '\n';
    int temp;

    for ( int i = 0; i < 10; i++ ){
        if ( fork() == 0 )
        {
            temp = getpid();
            for (int k = 2; k>=0; k--){
                if(temp == 0) {
                    printData[k] = ' ';
                    continue;
                }
                printData[k] = (temp % 10) + '0';
                temp /= 10;
            }
            for(int j = 0; j<1000; j++) {
            temp = j;
            for (int k = 8; k>4; k--){
                if(temp == 0) {
                    printData[k] = ' ';
                    continue;
                }
                printData[k] = (temp % 10) + '0';
                temp /= 10;
            }
             //   printf( 1, "pid: %d\n", getpid());
             //   printf(1, "%d: %d\n", getpid(), j);
             write(1, printData, sizeof(printData));
            }
            exit();
        }
    }
    int stats[10][8];
    for(int i = 0; i<10; i++){
        stats[i][0] = waitForChild(tv); //Child's pid
        stats[i][1] = tv->creationTime;
        stats[i][2] = tv->readyTime;
        stats[i][3] = tv->runningTime; //CBT
        stats[i][4] = tv->sleepingTime;
        stats[i][5] = tv->terminationTime;
    } 
    printf(1, "\n\nResults:\n");
    int avgTT = 0, avgCBT = 0, avgWT = 0;
    for(int i = 0; i<10; i++) {
        stats[i][6] = stats[i][5] - stats[i][1]; //TurnAround Time
        stats[i][7] = stats[i][6] - (stats[i][3] + stats[i][4]); //Waiting Time
        printf(1, "pid: %d  TurnAroundTime: %d  CBT: %d  WaitingTime: %d\n", stats[i][0], stats[i][6], stats[i][3], stats[i][7]);
        //printf(1, "pid: %d  Creation: %d  Ready: %d  Running: %d  Sleeping: %d", stats[i][0], stats[i][1], stats[i][2], stats[i][3], stats[i][4]);
        //printf(1, "  Termination: %d\n", stats[i][5]);

        avgTT += stats[i][6];
        avgCBT += stats[i][3];
        avgWT += stats[i][7];
    }
    avgTT /= 10;
    avgCBT /= 10;
    avgWT /= 10;
    printf(1, "\n\nAverage TurnAroundTime: %d  Average CBT: %d  average WaitingTime: %d\n\n", avgTT, avgCBT, avgWT);
    exit();


} 
