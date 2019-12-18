#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    changePolicy(2); //Set scheduling policy to Modified Priority Scheduling Policy
    struct timeVariables * tv = malloc (sizeof (struct timeVariables));

   // printf( 1, "[dad] pid %d\n", getpid() );

   char printData[10];
    printData[3] = ':';
    printData[4] = ' ';
    printData[9] = '\n';
    int temp;

    for ( int i = 1; i < 26; i++ ){
        if ( fork() == 0 )
        {
            temp = i;
            for (int k = 2; k>=0; k--){
                if(temp == 0) {
                    printData[k] = ' ';
                    continue;
                }
                printData[k] = (temp % 10) + '0';
                temp /= 10;
            }

            if(i < 6)
                changePriority(5);
            else if(6 <= i && i < 11)
                changePriority(4);
            else if(11 <= i && i < 16)
                changePriority(3);
            else if(16 <= i && i < 21)
                changePriority(2);
            else if(21 <= i)
                changePriority(1);

            for(int j = 0; j<500; j++) {
                temp = j;
                for (int k = 8; k>4; k--){
                if(temp == 0) {
                    printData[k] = ' ';
                    continue;
                }
                printData[k] = (temp % 10) + '0';
                temp /= 10;
                }
            //    printf( 1, "%d: %d\n", i, j);
             write(1, printData, sizeof(printData));
            }
            exit();
        }
    }
    int stats[25][8];
    for(int i = 0; i<25; i++){
        stats[i][0] = waitForChild(tv); //Child's pid
        stats[i][1] = tv->creationTime;
        stats[i][2] = tv->readyTime;
        stats[i][3] = tv->runningTime; //CBT
        stats[i][4] = tv->sleepingTime;
        stats[i][5] = tv->terminationTime;
    } 
    printf(1, "\n\nIndividual Results:\n\n");
    int avgTT = 0, avgCBT = 0, avgWT = 0;
    int avgPTT[5], avgPCBT[5], avgPWT[5];
    int minNum = stats[0][0];
    for(int i = 0; i<25; i++){
        if(stats[i][0] < minNum )
            minNum = stats[i][0];
    }
    minNum -= 1;
    int childNum;
    for(int i = 0; i<25; i++) {
        childNum = stats[i][0] - minNum;
        stats[i][6] = stats[i][5] - stats[i][1]; //TurnAround Time
        stats[i][7] = stats[i][6] - (stats[i][3] + stats[i][4]); //Waiting Time
        printf(1, "Child num: %d  pid: %d  TurnAroundTime: %d  CBT: %d  WaitingTime: %d\n",childNum, stats[i][0], stats[i][6], stats[i][3], stats[i][7]);
        //printf(1, "pid: %d  Creation: %d  Ready: %d  Running: %d  Sleeping: %d", stats[i][0], stats[i][1], stats[i][2], stats[i][3], stats[i][4]);
        //printf(1, "  Termination: %d\n", stats[i][5]);

        avgTT += stats[i][6];
        avgCBT += stats[i][3];
        avgWT += stats[i][7];

        avgPTT[(childNum - 1)/5] += stats[i][6];
        avgPCBT[(childNum - 1)/5] += stats[i][3];
        avgPWT[(childNum - 1)/5] += stats[i][7];
    }
    avgTT /= 25;
    avgCBT /= 25;
    avgWT /= 25;

    printf(1, "\n\nGroup Result:\n\n");
    int groupFinalElem;
    for(int i = 0; i<5; i++) {
        avgPTT[i] /= 5;
        avgPCBT[i] /= 5;
        avgPWT[i] /= 5;
        groupFinalElem = 5 * i + 5;
        printf(1, "Group:[%d-%d]  AVG TurnAroundTime: %d  AVG CBT: %d  AVG WaitingTime: %d\n",groupFinalElem - 4, groupFinalElem, avgPTT[i], avgPCBT[i], avgPWT[i]);

    }
    printf(1, "\n\nAll Together Result:\n\n");
    printf(1, "Average TurnAroundTime: %d  Average CBT: %d  average WaitingTime: %d\n\n", avgTT, avgCBT, avgWT);

    exit();


} 
