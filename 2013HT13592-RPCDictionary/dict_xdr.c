/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "dict.h"

bool_t
xdr_dictTuple (XDR *xdrs, dictTuple *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->word, 50,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->meaning, 50,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}
