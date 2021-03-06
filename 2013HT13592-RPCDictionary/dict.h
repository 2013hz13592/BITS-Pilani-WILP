/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DICT_H_RPCGEN
#define _DICT_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct dictTuple {
	char word[50];
	char meaning[50];
};
typedef struct dictTuple dictTuple;

#define DICTIONARY 0x01313592
#define INSERT_LOOKUP_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define INSERT_LOOKUP 1
extern  int * insert_lookup_1(dictTuple *, CLIENT *);
extern  int * insert_lookup_1_svc(dictTuple *, struct svc_req *);
extern int dictionary_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define INSERT_LOOKUP 1
extern  int * insert_lookup_1();
extern  int * insert_lookup_1_svc();
extern int dictionary_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_dictTuple (XDR *, dictTuple*);

#else /* K&R C */
extern bool_t xdr_dictTuple ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DICT_H_RPCGEN */
