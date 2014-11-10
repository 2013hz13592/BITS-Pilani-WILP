/*
 * llf.c
 *
 *  Created on: Sep 18, 2014
 *      Author: pras
 */
/*2013hz13592*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_INT 32765
#define CONSOLE_INPUT 1

/*Each row of the array represents a task*/
/*The columns are in the order Release Time, Period, Execution Time, Deadline*/
int taskInfo[50][4];

FILE* fileOpen();
int fReadNumOfTasks(FILE*);
void fReadTaskDetails(FILE* fp, int numberOfTasks);
float calculateDensity(int numberOfTasks);
float calculateCpuUtilization(int numberOfTasks);
int calculateHyperPeriod(int numberOfTasks);
void calculateLLF(int numberOfTasks, int hyperperiod);
void fileClose(FILE*);

main()
{
 int screenInput=CONSOLE_INPUT;
 int numberOfTasks=0;
 int count=0;
 float density=0;
 float utilization=0;
 int hyperperiod=0;
 FILE* fp;

 if(screenInput)
 {
	 printf("Enter Number of Tasks: ");
	 scanf("%d",&numberOfTasks);
	 while (count < numberOfTasks)
	 {
		 	 printf("Enter Release Time of Task %d: ", count);
		 	 scanf("%d",&taskInfo[count][0]);
		 	 printf("Enter Period of Task %d: ", count);
		 	 scanf("%d",&taskInfo[count][1]);
		 	 printf("Enter Execution Time of Task %d: ", count);
		 	 scanf("%d",&taskInfo[count][2]);
		 	 printf("Enter Deadline of Task %d: ", count);
		 	 scanf("%d",&taskInfo[count][3]);
	 		 count++;
	 }
 }
 else
 {
	 fp=fileOpen();
	 numberOfTasks=fReadNumOfTasks(fp);
	 printf("Number of Tasks: %d\n",numberOfTasks);
	 fReadTaskDetails(fp, numberOfTasks);
	 while (count < numberOfTasks)
	 {
		 printf("%d %d %d %d\n",taskInfo[count][0], taskInfo[count][1], taskInfo[count][2], taskInfo[count][3]);
		 count++;
	 }
	 fileClose(fp);
 }
 density=calculateDensity(numberOfTasks);
 printf("Density: %f\n",density);
 utilization=calculateCpuUtilization(numberOfTasks);
 printf("Utilization: %f\n",utilization);
 if (density > 1)
 {
	 printf("Density for the task set is more than 1. Schedule cannot be created.");
 }
 else
 {
	 hyperperiod=calculateHyperPeriod(numberOfTasks);
	 printf("Hyperperiod: %d\n",hyperperiod);
	 calculateLLF(numberOfTasks, hyperperiod);
 }
}

FILE* fileOpen()
{
 FILE *fp;
 fp = fopen("edfinput","r");
 if(fp==NULL)
 {
  printf("File could not be opened.\n");
 }
 return fp;
}

int fReadNumOfTasks(FILE* fp)
{
 int numberOfTasks=0;
 fscanf(fp,"%d",&numberOfTasks);
 return numberOfTasks;
}

void fReadTaskDetails(FILE* fp, int numberOfTasks)
{
 int count=0;

 while (count < numberOfTasks)
 {
  fscanf(fp,"%d %d %d %d", &taskInfo[count][0], &taskInfo[count][1], &taskInfo[count][2], &taskInfo[count][3]);
  count++;
 }
}

float calculateDensity(numberOfTasks)
{
 float density=0;
 int count=0;
 float denominator=0;
 while (count < numberOfTasks)
 {
  /*Sum of execution time divided by periodicity of all the tasks*/
  denominator=(taskInfo[count][1]<taskInfo[count][3]?taskInfo[count][1]:taskInfo[count][3]);
  density+=(float)taskInfo[count][2]/denominator;
  count++;
 }
 return density;
}

float calculateCpuUtilization(numberOfTasks)
{
 float utilization=0;
 int count=0;
 while (count < numberOfTasks)
 {
  /*Sum of execution time divided by periodicity of all the tasks*/
  utilization+=(float)taskInfo[count][2]/(float)taskInfo[count][1];
  count++;
 }
 return utilization;
}

int calculateHyperPeriod(numberOfTasks)
{
 int hyperperiod=0;
 int max=0;
 int count=0;
 int num1;
 int num2;

 /*Calculate LCM of Periods*/
 num1=taskInfo[0][1];
 num2=taskInfo[1][1];
 count = count + 1;
 while (count < numberOfTasks)
 {
  max=(num1>num2)?num1:num2;
  num1=max;
  count++;
  num2=taskInfo[count][1];
 }
 count=0;
 while (1)
 {
  while (count < numberOfTasks)
  {
   if(max%taskInfo[count][1]!=0)
     break;
   count++;
  }
  if(count==numberOfTasks)
    break;
  max=max+1;
 }
 /*HyperPeriod is the LCM of Periods*/
 hyperperiod=max;
 return hyperperiod;
}

void calculateLLF(int numberOfTasks, int hyperperiod)
{
 /*Stores Laxity Deadline, Remaining Time, Number of PreEmpts, Min Response, Max Response, Start Time, Absolute Deadline*/
 int taskQueue[50][7];
 int clockTime=0;
 int llf_abs;
 int runJob=-1;
 int currJob=-1;
 int count=0;
 int respTime=0;

 clockTime=0;
 count=0;
 while (clockTime <= hyperperiod)
 {
  count=0;
  while (count < numberOfTasks)
  {
   if ((clockTime==taskInfo[count][0]) || (clockTime%taskInfo[count][1]==0) || (taskQueue[count][1] - clockTime==0) || 1)
   {
    /*Initialize Remaining Time to Execution Time at Phase*/
    if (taskInfo[count][0] == clockTime)
    {
     taskQueue[count][1] = taskInfo[count][2];
     /*Save Start Time*/
     taskQueue[count][5] = clockTime;
     /*Compute the absolute deadline*/
     taskQueue[count][6] = taskInfo[count][3] + clockTime;
     /*Initialize Laxity Deadline*/
     taskQueue[count][0] = taskInfo[count][3] - taskInfo[count][2];
    }

    /*Initialize Remaining Time to Execution Time at Periodic Release Interval*/
    if (clockTime!=0)
    {
     if (clockTime%taskInfo[count][1]==0)
     {
      taskQueue[count][1] = taskInfo[count][2];
      /*Save Start Time*/
      taskQueue[count][5] = clockTime;
      /*Compute the absolute deadline*/
      taskQueue[count][6] = taskInfo[count][3] + clockTime;
      /*Initialize Laxity Deadline*/
      taskQueue[count][0] = taskInfo[count][3] - taskInfo[count][2];
     }
    }
   }

   /*PreEmpts*/
   if (clockTime==0)
     taskQueue[count][2] = 0;

   /*Min Response is initialized to relative deadline*/
   if (clockTime==0)
     taskQueue[count][3] = taskInfo[count][3];

   /*Max Response is initialized to execution time*/
   if (clockTime==0)
     taskQueue[count][4] = taskInfo[count][2];

   /*Re-Calculate Laxity Deadline*/
   if (taskQueue[count][0] != MAX_INT)
     taskQueue[count][0] = taskQueue[count][6] - clockTime - taskQueue[count][1];

   count++;
  }

  count=0;
  llf_abs=MAX_INT;
  runJob=-1;
  while(count < numberOfTasks)
  {
   if ((taskQueue[count][0] < llf_abs) && (clockTime >= taskInfo[count][0]))
   {
	llf_abs=taskQueue[count][0];
	runJob=count;
	if(taskQueue[runJob][0]==taskQueue[currJob][0])
	{
		runJob=currJob;
	}
   }
   /*printf("Clock: %d, Remaining Time: %d, Absolute Deadline: %d, Run Job: %d\n", clockTime, taskQueue[count][1], taskQueue[count][0],runJob);*/
   count++;
  }

  count=0;
  while(count < numberOfTasks)
  {
   if (count==runJob)
   {
    taskQueue[count][1] = taskQueue[count][1] - 1;
   }

   /*Re-Calculate Laxity Deadline*/
   if (taskQueue[count][0] != MAX_INT)
     taskQueue[count][0] = taskQueue[count][6] - clockTime - taskQueue[count][1];

   /*If remaining time is zero then set absolute deadline to max integer*/
   if (taskQueue[count][1]==0)
   {
    /*If job has finished earlier and absolute deadline is initialized to max int*/
    /*We will will not calculate resp time*/
    if (taskQueue[count][0] != MAX_INT)
    {
     respTime = clockTime - taskQueue[count][5] + 1;
     if (respTime < taskQueue[count][3])
       taskQueue[count][3] = respTime;
     if (respTime > taskQueue[count][4])
       taskQueue[count][4] = respTime;
    }
    /*absolute deadline is initialized to max if the job has completed*/
    taskQueue[count][0] = MAX_INT;
   }
   count++;
  }

  if (currJob!=runJob)
  {
   if (currJob!=-1 && taskQueue[currJob][1]!=0)
     taskQueue[currJob][2]=taskQueue[currJob][2]+1;
   printf("Time: %d, Running Job: %d Previous Job: %d\n", clockTime, runJob, currJob);
   currJob=runJob;
  }
  else
  {
   printf("Time: %d, Running Job: %d\n", clockTime, runJob);
  }
  clockTime++;
 }
 count=0;
 while (count < numberOfTasks)
 {
  printf("JobId: %d, Prempts: %d, Min Response: %d, Max Response: %d\n",  count, taskQueue[count][2], taskQueue[count][3], taskQueue[count][4]);
  count++;
 }
}

void fileClose(FILE* fp)
{
 fclose(fp);
}


