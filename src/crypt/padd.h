/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Mon Jan 05 2004
 copyright   : (C) 2004 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GWEN_PADD_H
#define GWEN_PADD_H

#include <gwenhywfar/buffer.h>

#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup MOD_CRYPT_PADD Padding Functions
 * @ingroup MOD_CRYPT
 * These functions are used for padding when encrypting/decrypting data
 * using 2-key-triple-DES or when signing data.
 * The original code (in C++) has been written by
 * <strong>Fabian Kaiser</strong> for <strong>OpenHBCI</strong>
 * (file rsakey.cpp). Translated to C and slightly modified by me
 * (Martin Preuss)
 */
/*@{*/

/**
 * This function padds the given buffer according to ISO9796.
 * The given buffer is expected to contain a 20 byte hash created using
 * RIPEMD 160. This is padded to 96 bytes according to ISO 9796 (including
 * appendices).
 */
int GWEN_Padd_PaddWithISO9796(GWEN_BUFFER *src);

/**
 * This function is used to pad the plain text data to a multiple of 8 bytes
 * size before encrypting it.
 */
int GWEN_Padd_PaddWithANSIX9_23(GWEN_BUFFER *src);

/**
 * This function is used to remove padding from plain text data after
 * decrypting it.
 */
int GWEN_Padd_UnpaddWithANSIX9_23(GWEN_BUFFER *src);


/*@}*/

#ifdef __cplusplus
}
#endif



#endif /* GWEN_PADD_H */

