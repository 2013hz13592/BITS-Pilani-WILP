//Lamport Logical Clock
//2013HT13592
//Prasenjit Das

import java.util.Random;

class LamportThread implements Runnable 
{
	static int msg;
	static int msgPid;
	static int ProcessCount;
	int pid;
	LamportThread(int instance)
	{
		pid = instance;
		ProcessCount = ProcessCount + 1;
	}
	public void run()
	{
		int localClock = 0;
		final int max = 100;
		final int min = 1;
		Random rand = new Random();
		for(int i=0;i<100;i++)
		{
			int randomNum = rand.nextInt((max - min) + 1) + min;
			int randomProcess = randomNum%ProcessCount + 1;
			if((randomNum%5)==0)
			{
				localClock = localClock + 1;
				System.out.println("Local Time at Process" + pid + ": " + localClock);
			}
			if((randomNum%7)==0)
			{
				msg = 1;
				msgPid = randomProcess;
			}
			if (msg==1 && msgPid==pid)
			{
				msg=0;
				localClock = localClock + 1;
				System.out.println("Message Received at Process"+pid);
				System.out.println("Local Time at Process" + pid + ": " + localClock);
				
			}
		}
	}
}

public class Lamport
{
	public static void main(String [] args)
	{
		LamportThread lt1 = new LamportThread(1);
		LamportThread lt2 = new LamportThread(2);
		Thread t1 = new Thread(lt1);
		Thread t2 = new Thread(lt2);
		t1.start();
		t2.start();
	}
}