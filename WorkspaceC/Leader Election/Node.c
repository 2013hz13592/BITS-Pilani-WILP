/*
 * Node.c
 *
 *  Created on: Mar 22, 2015
 *      Author: pras
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "bully.h"
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <rpc/rpc.h>
#include<time.h>
#define N 3
#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

int tcur=0,LEADER=0,hostID,alive=1,flag=1,tcuralive,leaderID,leaderID_alive;
char *ip[]={"172.16.47.137","172.16.6.115","172.16.46.182"};
int count,value,a[N],down;

OUTPUT *leaderelection_1_svc(INPUT *argp, struct svc_req *rqstp)
{
	static OUTPUT  result;
	int i,min;

	printf("Leader Election Taking Place...................in %d\n",hostID);
	printf("Message From SrcIP :: SrcId: %d\n",argp->srcId);
	a[count]=argp->srcId;
	count=count+1;
	printf("Count Value in Election Fun:%d",count);
	value=count;

	return &result;
}

void *alivemessage_1_svc(INPUT *argp, struct svc_req *rqstp)
{
	static char * result;
	tcuralive=tcur;
	printf("Alive Message from Leader\n");
	leaderID_alive=(argp->srcId);
	return (void *) &result;
}

static void bully_pgm_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		INPUT leaderelection_1_arg;
		INPUT alivemessage_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case leaderElection:
		_xdr_argument = (xdrproc_t) xdr_INPUT;
		_xdr_result = (xdrproc_t) xdr_OUTPUT;
		local = (char *(*)(char *, struct svc_req *)) leaderelection_1_svc;
		break;

	case aliveMessage:
		_xdr_argument = (xdrproc_t) xdr_INPUT;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) alivemessage_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}


void* server_func(){

register SVCXPRT *transp;

	pmap_unset (BULLY_PGM, BULLY_PGM_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, BULLY_PGM, BULLY_PGM_VERSION, bully_pgm_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (BULLY_PGM, BULLY_PGM_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, BULLY_PGM, BULLY_PGM_VERSION, bully_pgm_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (BULLY_PGM, BULLY_PGM_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}

void* client_func(){

	CLIENT *clnt;
	OUTPUT  *result_1;
	INPUT  leaderelection_1_arg;
	void  *result_2;
	INPUT  alivemessage_1_arg;
	char* host;
	int i,min;

	int count;
	pthread_t client;
	time_t start,end;
	time(&start);
	printf("Timer Sarted in HOST %d\n",hostID);

	while(tcur<5100){
	time(&end);
	tcur=difftime(end,start);

	if((tcur-tcuralive>8)&&(flag==1)&&(LEADER==0)){
	printf("HostID:%d making ELECTION Call\n",hostID);
	flag=0;
	down=down+1;
	count=0;
	printf("Down For %d times\n",down);

	for(i=0;i<N;i++){
	printf("Ip:%s",ip[i]);
	clnt = clnt_create (ip[i], BULLY_PGM, BULLY_PGM_VERSION, "udp");
	if (clnt == NULL)
	{
	 clnt_pcreateerror ("127.0.0.1");
	 exit (1);
	}

	leaderelection_1_arg.srcId=hostID;
	result_1 = leaderelection_1(&leaderelection_1_arg, clnt);

	if (result_1 == (void *) NULL) {
	clnt_perror (clnt, "call failed");
		}
	clnt_destroy (clnt);
	sleep(1);

	}
	sleep(2);
	printf("Checking Count :value=%d\n",value);


	if(value==(N-down))
	{
	  min=0;
	for(i=0;i<value;i++){
	if(a[i]<a[min]){
	min=i;
	}
	count=0;
	}
	count=0;
	leaderID=a[min];
	printf("Declared Leader in HOST:%d=%d",hostID,leaderID);
	}


	if(hostID==leaderID)
	{
	printf("Im Leader\n");
	LEADER=1;
	}
	flag=1;

		}
	if((LEADER==1) &&(tcur%5==0)){
	printf("Leader is :%d\n",hostID);
	printf("Now Sending Alive Message\n");
	for(i=0;i<N;i++){
	host=ip[i];

	clnt = clnt_create (host, BULLY_PGM, BULLY_PGM_VERSION, "udp");

	if (clnt == NULL) {
	clnt_pcreateerror ("127.0.0.1");
	exit (1);
		}

	alivemessage_1_arg.srcId=hostID;

	result_2 = alivemessage_1(&alivemessage_1_arg, clnt);
	if (result_2 == (void *) NULL) {
	clnt_perror (clnt, "call failed");
		}
	clnt_destroy (clnt);
		}

	}
}
}

int main(int argc,char *argv[])
{
	pthread_t t,client,server;
	int count,i=0,j=0;
	FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

	if (argc < 2) {
		printf ("usage: %s NODE_ID\n", argv[0]);
		exit (1);
	}
	hostID = atoi(argv[1]);

	count=pthread_create(&server,NULL,server_func,NULL);
	sleep(1);
	count=pthread_create(&client,NULL,client_func,NULL);
	sleep(2);
	if(hostID==1 && leaderID_alive==0)
	{LEADER=1;}

	while(1){ }


 return 0;
}

