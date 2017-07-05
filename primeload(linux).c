/*
des: A multi-thread program to generate load on CPU (#threads adjustable)
algm: Prime numbers search
compiling: gcc primeload.c -o primeload -lpthread -lm 
author: Wingter.WU
Date: 15-06-25
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// running prime algm
void *thread(void *threadid)
{
int tid;
tid = (int)threadid;
printf("Hello wwt! thread #%d is running prime...\n", tid);
int i,j;
int primes_found[32767];
int index = 0;
int n = 6666666;// about 2 min

    for(i=2; i<=n; i++)
    {  
      for(j=2; j<=sqrt(i); j++) //最小质因数<=平方根
        {
          if(j%i==0)
          break;
        }

       if(j>sqrt(i)) 
          primes_found[index++] = i;
       if(index>=32766)
          index = 0; // cover the old primes
       
    }

pthread_exit(NULL);
}

int main(void)
{
pthread_t id;
void *ret;
int i,retv,t;
int number_of_thrds = 1;
// max number of thrds < 99
pthread_t ids[99];
for(t=0;t<99;t++)
  ids[t] = 0;

printf("input number of thrds(>1): ");
scanf("%d", &number_of_thrds);

// create threads
for(t=0;t<number_of_thrds;t++)
{
  retv=pthread_create(&id,NULL,(void *) thread,(void *)t);
  ids[t] = id;

   if (retv!=0)
   {
    printf ("Create pthread error!/n");
    return 1;
   }
}


  printf("main process is playing...\n");

for(t=0;t<number_of_thrds;t++)
   pthread_join(ids[t],NULL);

  printf("main process ends...\n");

return 0;
}


