/* This file is auto-generated from "ssl_cert_descr.xml" by the typemaker
   tool of Gwenhywfar.
   Do not edit this file -- all changes will be lost! */
#ifndef SSL_CERT_DESCR_H
#define SSL_CERT_DESCR_H

/** @page P_GWEN_SSLCERTDESCR_PUBLIC GWEN_SslCertDescr (public)
This page describes the properties of GWEN_SSLCERTDESCR
@anchor GWEN_SSLCERTDESCR_CountryName
<h3>CountryName</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetCountryName,
get it with @ref GWEN_SslCertDescr_GetCountryName
</p>

@anchor GWEN_SSLCERTDESCR_CommonName
<h3>CommonName</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetCommonName,
get it with @ref GWEN_SslCertDescr_GetCommonName
</p>

@anchor GWEN_SSLCERTDESCR_OrganizationName
<h3>OrganizationName</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetOrganizationName,
get it with @ref GWEN_SslCertDescr_GetOrganizationName
</p>

@anchor GWEN_SSLCERTDESCR_OrganizationalUnitName
<h3>OrganizationalUnitName</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetOrganizationalUnitName,
get it with @ref GWEN_SslCertDescr_GetOrganizationalUnitName
</p>

@anchor GWEN_SSLCERTDESCR_LocalityName
<h3>LocalityName</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetLocalityName,
get it with @ref GWEN_SslCertDescr_GetLocalityName
</p>

@anchor GWEN_SSLCERTDESCR_StateOrProvinceName
<h3>StateOrProvinceName</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetStateOrProvinceName,
get it with @ref GWEN_SslCertDescr_GetStateOrProvinceName
</p>

@anchor GWEN_SSLCERTDESCR_NotBefore
<h3>NotBefore</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetNotBefore,
get it with @ref GWEN_SslCertDescr_GetNotBefore
</p>

@anchor GWEN_SSLCERTDESCR_NotAfter
<h3>NotAfter</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetNotAfter,
get it with @ref GWEN_SslCertDescr_GetNotAfter
</p>

@anchor GWEN_SSLCERTDESCR_IpAddress
<h3>IpAddress</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetIpAddress,
get it with @ref GWEN_SslCertDescr_GetIpAddress
</p>

@anchor GWEN_SSLCERTDESCR_FingerPrint
<h3>FingerPrint</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetFingerPrint,
get it with @ref GWEN_SslCertDescr_GetFingerPrint
</p>

@anchor GWEN_SSLCERTDESCR_FingerPrintSha1
<h3>FingerPrintSha1</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetFingerPrintSha1,
get it with @ref GWEN_SslCertDescr_GetFingerPrintSha1
</p>

@anchor GWEN_SSLCERTDESCR_FingerPrintSha512
<h3>FingerPrintSha512</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetFingerPrintSha512,
get it with @ref GWEN_SslCertDescr_GetFingerPrintSha512
</p>

@anchor GWEN_SSLCERTDESCR_PubKeyModulus
<h3>PubKeyModulus</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetPubKeyModulus,
get it with @ref GWEN_SslCertDescr_GetPubKeyModulus
</p>

@anchor GWEN_SSLCERTDESCR_PubKeyExponent
<h3>PubKeyExponent</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetPubKeyExponent,
get it with @ref GWEN_SslCertDescr_GetPubKeyExponent
</p>

@anchor GWEN_SSLCERTDESCR_StatusText
<h3>StatusText</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetStatusText,
get it with @ref GWEN_SslCertDescr_GetStatusText
</p>

@anchor GWEN_SSLCERTDESCR_IsError
<h3>IsError</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetIsError,
get it with @ref GWEN_SslCertDescr_GetIsError
</p>

@anchor GWEN_SSLCERTDESCR_StatusFlags
<h3>StatusFlags</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_SslCertDescr_SetStatusFlags,
get it with @ref GWEN_SslCertDescr_GetStatusFlags
</p>

*/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct GWEN_SSLCERTDESCR GWEN_SSLCERTDESCR;

#ifdef __cplusplus
} /* __cplusplus */
#endif

#include <gwenhywfar/db.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/list2.h>
/* headers */
#include <gwenhywfar/gwentime.h>
#include <gwenhywfar/ssl_cert_flags.h>

#ifdef __cplusplus
extern "C" {
#endif


GWEN_LIST_FUNCTION_LIB_DEFS(GWEN_SSLCERTDESCR, GWEN_SslCertDescr, GWENHYWFAR_API)
GWENHYWFAR_API GWEN_SSLCERTDESCR_LIST *GWEN_SslCertDescr_List_dup(const GWEN_SSLCERTDESCR_LIST *stl);

GWEN_LIST2_FUNCTION_LIB_DEFS(GWEN_SSLCERTDESCR, GWEN_SslCertDescr, GWENHYWFAR_API)

/** Destroys all objects stored in the given LIST2 and the list itself
*/
GWENHYWFAR_API void GWEN_SslCertDescr_List2_freeAll(GWEN_SSLCERTDESCR_LIST2 *stl);

/** Creates a new object.
*/
GWENHYWFAR_API GWEN_SSLCERTDESCR *GWEN_SslCertDescr_new(void);
/** Creates an object from the data in the given GWEN_DB_NODE
*/
GWENHYWFAR_API GWEN_SSLCERTDESCR *GWEN_SslCertDescr_fromDb(GWEN_DB_NODE *db);
/** Creates and returns a deep copy of thegiven object.
*/
GWENHYWFAR_API GWEN_SSLCERTDESCR *GWEN_SslCertDescr_dup(const GWEN_SSLCERTDESCR *st);
/** Destroys the given object.
*/
GWENHYWFAR_API void GWEN_SslCertDescr_free(GWEN_SSLCERTDESCR *st);
/** Increments the usage counter of the given object, so an additional free() is needed to destroy the object.
*/
GWENHYWFAR_API void GWEN_SslCertDescr_Attach(GWEN_SSLCERTDESCR *st);
/** Reads data from a GWEN_DB.
*/
GWENHYWFAR_API int GWEN_SslCertDescr_ReadDb(GWEN_SSLCERTDESCR *st, GWEN_DB_NODE *db);
/** Stores an object in the given GWEN_DB_NODE
*/
GWENHYWFAR_API int GWEN_SslCertDescr_toDb(const GWEN_SSLCERTDESCR *st, GWEN_DB_NODE *db);
/** Returns 0 if this object has not been modified, !=0 otherwise
*/
GWENHYWFAR_API int GWEN_SslCertDescr_IsModified(const GWEN_SSLCERTDESCR *st);
/** Sets the modified state of the given object
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetModified(GWEN_SSLCERTDESCR *st, int i);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_CountryName
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetCountryName(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_CountryName
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetCountryName(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_CommonName
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetCommonName(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_CommonName
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetCommonName(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_OrganizationName
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetOrganizationName(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_OrganizationName
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetOrganizationName(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_OrganizationalUnitName
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetOrganizationalUnitName(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_OrganizationalUnitName
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetOrganizationalUnitName(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_LocalityName
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetLocalityName(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_LocalityName
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetLocalityName(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_StateOrProvinceName
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetStateOrProvinceName(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_StateOrProvinceName
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetStateOrProvinceName(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_NotBefore
*/
GWENHYWFAR_API const GWEN_TIME *GWEN_SslCertDescr_GetNotBefore(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_NotBefore
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetNotBefore(GWEN_SSLCERTDESCR *el, const GWEN_TIME *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_NotAfter
*/
GWENHYWFAR_API const GWEN_TIME *GWEN_SslCertDescr_GetNotAfter(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_NotAfter
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetNotAfter(GWEN_SSLCERTDESCR *el, const GWEN_TIME *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_IpAddress
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetIpAddress(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_IpAddress
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetIpAddress(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_FingerPrint
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetFingerPrint(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_FingerPrint
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetFingerPrint(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_FingerPrintSha1
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetFingerPrintSha1(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_FingerPrintSha1
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetFingerPrintSha1(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_FingerPrintSha512
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetFingerPrintSha512(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_FingerPrintSha512
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetFingerPrintSha512(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_PubKeyModulus
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetPubKeyModulus(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_PubKeyModulus
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetPubKeyModulus(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_PubKeyExponent
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetPubKeyExponent(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_PubKeyExponent
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetPubKeyExponent(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_StatusText
*/
GWENHYWFAR_API const char *GWEN_SslCertDescr_GetStatusText(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_StatusText
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetStatusText(GWEN_SSLCERTDESCR *el, const char *d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_IsError
*/
GWENHYWFAR_API int GWEN_SslCertDescr_GetIsError(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_IsError
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetIsError(GWEN_SSLCERTDESCR *el, int d);

/**
* Returns the property @ref GWEN_SSLCERTDESCR_StatusFlags
*/
GWENHYWFAR_API uint32_t GWEN_SslCertDescr_GetStatusFlags(const GWEN_SSLCERTDESCR *el);
/**
* Set the property @ref GWEN_SSLCERTDESCR_StatusFlags
*/
GWENHYWFAR_API void GWEN_SslCertDescr_SetStatusFlags(GWEN_SSLCERTDESCR *el, uint32_t d);


#ifdef __cplusplus
} /* __cplusplus */
#endif


#endif /* SSL_CERT_DESCR_H */
