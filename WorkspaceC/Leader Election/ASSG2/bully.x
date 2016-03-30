struct INPUT{

char *srcIP;
char *destIP;
int srcId;
int destId;

};


struct OUTPUT{

char *srcIP;
char *destIP;
int srcId;
int destId;

};


program BULLY_PGM{
				
		version BULLY_PGM_VERSION{
		OUTPUT leaderElection(INPUT)=1;	
		void  aliveMessage(INPUT)=1;	
		}=1;
}=0x23451101;
