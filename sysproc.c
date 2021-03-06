#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//return PID of the parent process
int
sys_getppid(void)
{
	struct proc *thisProc = myproc();
	return thisProc -> parent -> pid;

}

//return children's pid
int
sys_getChildren(void)
{
	int gpid; //given process id
	argint(0, &gpid);
	int res = getChildren(gpid);
	return res;
}

//return number of times a certain process has been invoked
int
sys_getCount(void)
{
	int count; //given process id
	argint(0, &count);
	struct proc *thisProc = myproc();
  if(count <= 0)
    return -1;
	return thisProc -> sysCounter[count-1];
}

//Change priority, return 1 if successful. If not, return -1
int
sys_changePriority(void)
{
	int pr;
	argint(0, &pr);
	struct proc *thisProc = myproc();
	if (pr<1 || pr>5)
		return -1;
	thisProc -> priority = pr;
//	cprintf("Priority: %d\n", thisProc -> priority);
	return 1;
	
}

//Change scheduler's policy
int
sys_changePolicy(void)
{
	int policy;
	argint(0, &policy);
	int res = changePolicy(policy);
	return res;
}

//Wait for child
int
sys_waitForChild(void)
{
	struct timeVariables * tv;
  argptr(0, (void*)&tv ,sizeof(*tv));
  //cprintf("tv: %d %d %d %d %d\n", tv->creationTime, tv->readyTime, tv->runningTime, tv->sleepingTime, tv->terminationTime);
  return waitForChild(tv);
}
