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


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "padd_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/error.h>
#include <gwenhywfar/cryptdefs.h>
#include <string.h>
#include <stdlib.h>




/*
 * This code has been taken from OpenHBCI (rsakey.cpp, written by Fabian
 * Kaiser)
 */
unsigned char GWEN_Padd_permutate(unsigned char input) {
  unsigned char leftNibble;
  unsigned char rightNibble;
  static const unsigned char lookUp[2][16] =
    {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
    {14,3,5,8,9,4,2,15,0,13,11,6,7,10,12,1}};

  rightNibble = input & 15;
  leftNibble = input & 240;
  leftNibble = leftNibble / 16;
  rightNibble = lookUp[1][rightNibble];
  leftNibble = lookUp[1][leftNibble];
  leftNibble = leftNibble * 16;

  return leftNibble + rightNibble;
}



/*
 * The original code (in C++) has been written by Fabian Kaiser for OpenHBCI
 * (file rsakey.cpp). Translated to C by Martin Preuss
 */
int GWEN_Padd_PaddWithISO9796(GWEN_BUFFER *src) {
  unsigned char *p;
  unsigned int l;
  unsigned int i;
  unsigned char buffer[GWEN_PADD_ISO9796_KEYSIZE];
  unsigned char hash[20];
  unsigned char c;

  p=(unsigned char*)GWEN_Buffer_GetStart(src);
  l=GWEN_Buffer_GetUsedBytes(src);
  memmove(hash, p, l);

  /* src+src+src */
  if (GWEN_Buffer_AppendBytes(src, (const char*)hash, l)) {
    DBG_INFO(GWEN_LOGDOMAIN, "here");
    return -1;
  }

  if (GWEN_Buffer_AppendBytes(src, (const char*)hash, l)) {
    DBG_INFO(GWEN_LOGDOMAIN, "here");
    return -1;
  }

  /* src=src(20,40) */
  if (GWEN_Buffer_Crop(src, 20, 40)) {
    DBG_INFO(GWEN_LOGDOMAIN, "here");
    return -1;
  }

  memset(buffer, 0, sizeof(buffer));

  /* append redundancy */
  p=(unsigned char*)GWEN_Buffer_GetStart(src);
  for (i=0; i<=47; i++) {
    int j1, j2, j3;

    j1=1 + sizeof(buffer) - (2*i);
    j2=40-i;
    j3=sizeof(buffer) - (2*i);

    if (j1>=0 && j1<(int)sizeof(buffer) && j2>=0) {
      buffer[j1]=p[j2];
    }
    if (j3>=0 && j3<(int)sizeof(buffer) && j2>=0) {
      buffer[j3]=GWEN_Padd_permutate(p[j2]);
    }
  } /* for */

  /* copy last 16 bytes to the beginning */
  memmove(buffer, buffer+(sizeof(buffer)-16), 16);

  p=buffer;
  /* finish */
  c=p[sizeof(buffer)-1];
  c = (c & 15) * 16;
  c += 6;
  p[sizeof(buffer)-1]=c;
  p[0] = p[0] & 127;
  p[0] = p[0] | 64;
  p[sizeof(buffer) - 40] = p[sizeof(buffer) - 40] ^ 1;

  GWEN_Buffer_Reset(src);
  if (GWEN_Buffer_AppendBytes(src, (const char*)buffer, sizeof(buffer))) {
    DBG_INFO(GWEN_LOGDOMAIN, "here");
    return -1;
  }

  return 0;
}


#if 0
int GWEN_Padd_PaddWithIso9796_2(GWEN_BUFFER *buf, int dstSize){
  unsigned int diff;
  char *p;
  int i;

  if ((unsigned int)dstSize<GWEN_Buffer_GetUsedBytes(buf)+31) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Buffer contains too much data");
    return GWEN_ERROR_INVALID;
  }

  /* add trailer */
  GWEN_Buffer_AppendByte(buf, 0xbc);

  /* reset position to 0 */
  GWEN_Buffer_Rewind(buf);

  /* insert room for header */
  diff=dstSize-31;
  if (GWEN_Buffer_InsertRoom(buf, 1+diff+1+8)) {
    DBG_ERROR(GWEN_LOGDOMAIN,
	      "Could not insert room for %d bytes",
	      1+diff+1+8);
    return GWEN_ERROR_GENERIC;
  }

  /* insert header and more-data-bit */
  p=GWEN_Buffer_GetStart(buf);
  *(p++)=0x60;

  /* insert padding field */
  for (i=0; i<diff; i++)
    *(p++)=0x0;
  *(p++)=0x01;

  /* insert 8 random bytes */
  GWEN_Crypt_Random(2, (uint8_t*)p, 8);
  for (i=0; i<8; i++) {
    if (*p==0)
      /* TODO: Need to find a better but yet fast way */
      *p=0xff;
    p++;
  }
  *(p++)=0x01;

  return 0;
}



int GWEN_Padd_UnpaddWithIso9796_2(GWEN_BUFFER *buf){
  uint32_t l;

  l=GWEN_Buffer_GetUsedBytes(buf);
  if (l<31) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Buffer contains too few bytes");
    return GWEN_ERROR_INVALID;
  }

  GWEN_Buffer_Crop(buf, l-21, 20);

  return 0;
}

#else
int GWEN_Padd_PaddWithIso9796_2(GWEN_BUFFER *buf, int dstSize){
  unsigned int diff;
  char *p;
  int i;

  if ((unsigned int)dstSize<GWEN_Buffer_GetUsedBytes(buf)+12) {
    /*DBG_ERROR(GWEN_LOGDOMAIN, "Buffer contains too much data");*/
    return GWEN_ERROR_INVALID;
  }

  /* add trailer */
  GWEN_Buffer_AppendByte(buf, 0xbc);

  /* reset position to 0 */
  GWEN_Buffer_Rewind(buf);

  /* insert room for header */
  diff=dstSize-GWEN_Buffer_GetUsedBytes(buf)-11+1;
  if (GWEN_Buffer_InsertRoom(buf, 1+diff+1+8)) {
    DBG_ERROR(GWEN_LOGDOMAIN,
	      "Could not insert room for %d bytes",
	      1+diff+1+8);
    return GWEN_ERROR_GENERIC;
  }

  /* insert header and more-data-bit */
  p=GWEN_Buffer_GetStart(buf);
  *(p++)=0x60;

  /* insert padding field */
  for (i=0; i<diff; i++)
    *(p++)=0x0;
  *(p++)=0x01;

  /* insert 8 random bytes */
  GWEN_Crypt_Random(2, (uint8_t*)p, 8);
  for (i=0; i<8; i++) {
    if (*p==0)
      /* TODO: Need to find a better but yet fast way */
      *p=0xff;
    p++;
  }

  return 0;
}


int GWEN_Padd_UnpaddWithIso9796_2(GWEN_BUFFER *buf){
  uint32_t l;
  uint32_t realSize;
  const uint8_t *p;

  l=GWEN_Buffer_GetUsedBytes(buf);
  if (l<11) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Buffer contains too few bytes");
    return GWEN_ERROR_INVALID;
  }

  p=(const uint8_t*)GWEN_Buffer_GetStart(buf);
  if (*p!=0x60) {
    DBG_ERROR(GWEN_LOGDOMAIN, "First byte is not a 0x60");
    return GWEN_ERROR_BAD_DATA;
  }
  p++;
  l=0;
  while(*p==0x00) {
    l++;
    p++;
  }
  if (*p!=0x01) {
    /*DBG_ERROR(GWEN_LOGDOMAIN, "First byte after padding is not a 0x01");*/
    return GWEN_ERROR_BAD_DATA;
  }

  realSize=GWEN_Buffer_GetUsedBytes(buf)-11-l;
  GWEN_Buffer_Crop(buf, 10+l, realSize);

  return 0;
}
#endif




int GWEN_Padd_PaddWithAnsiX9_23(GWEN_BUFFER *src) {
  unsigned char paddLength;
  unsigned int i;

  paddLength=8-(GWEN_Buffer_GetUsedBytes(src) % 8);
  for (i=0; i<paddLength; i++)
    GWEN_Buffer_AppendByte(src, paddLength);
  return 0;
}



int GWEN_Padd_UnpaddWithAnsiX9_23(GWEN_BUFFER *src) {
  const char *p;
  unsigned int lastpos;
  unsigned char paddLength;

  lastpos=GWEN_Buffer_GetUsedBytes(src);
  if (lastpos<8) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Buffer too small");
    return -1;
  }
  lastpos--;

  p=GWEN_Buffer_GetStart(src)+lastpos;
  paddLength=*p;
  if (paddLength<1 || paddLength>8) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Invalid padding (%d bytes ?)", paddLength);
    return -1;
  }
  GWEN_Buffer_Crop(src, 0, GWEN_Buffer_GetUsedBytes(src)-paddLength);
  GWEN_Buffer_SetPos(src, lastpos-paddLength);
  return 0;
}



int GWEN_Padd_PaddWithPkcs1Bt1(GWEN_BUFFER *buf, int dstSize){
  unsigned int diff;
  char *p;

  if ((unsigned int)dstSize<GWEN_Buffer_GetUsedBytes(buf)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Buffer contains too much data");
    return GWEN_ERROR_INVALID;
  }
  diff=dstSize-GWEN_Buffer_GetUsedBytes(buf);
  if (diff<11) {
    /* honour minimum padding length for BT 1 of 8 bytes, plus the
     * leading and the trailing zero and the block type identifier */
    DBG_ERROR(GWEN_LOGDOMAIN,
              "Buffer contains too many bytes (diff is <11)");
    return GWEN_ERROR_INVALID;
  }

  /* reset position to 0 */
  GWEN_Buffer_Rewind(buf);
  if (GWEN_Buffer_InsertRoom(buf, diff)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not insert room for %d bytes", diff);
    return GWEN_ERROR_GENERIC;
  }

  p=GWEN_Buffer_GetStart(buf);
  *(p++)=0x00;
  *(p++)=0x01; /* block type 01 */
  if (diff>3) {
    memset(p, 0xff, diff-3);
    p+=diff-3;
  }
  *(p++)=0x00;

  return 0;
}



int GWEN_Padd_PaddWithPkcs1Bt2(GWEN_BUFFER *buf, int dstSize){
  unsigned int diff;
  char *p;
  int i;

  if ((unsigned int)dstSize<GWEN_Buffer_GetUsedBytes(buf)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Buffer contains too much data");
    return GWEN_ERROR_INVALID;
  }
  diff=dstSize-GWEN_Buffer_GetUsedBytes(buf);
  if (diff<11) {
    /* honour minimum padding length for BT 1 of 8 bytes, plus the
     * leading and the trailing zero and the block type identifier */
    DBG_ERROR(GWEN_LOGDOMAIN,
              "Buffer contains too many bytes (diff is <11)");
    return GWEN_ERROR_INVALID;
  }

  /* reset position to 0 */
  GWEN_Buffer_Rewind(buf);
  if (GWEN_Buffer_InsertRoom(buf, diff)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not insert room for %d bytes", diff);
    return GWEN_ERROR_GENERIC;
  }

  p=GWEN_Buffer_GetStart(buf);
  *(p++)=0x00;
  *(p++)=0x02; /* block type 02 */
  GWEN_Crypt_Random(2, (uint8_t*)p, diff-3);
  for (i=0; i<diff-3; i++) {
    if (*p==0)
      /* TODO: Need to find a better but yet fast way */
      *p=0xff;
    p++;
  }
  *(p++)=0x00;

  return 0;
}



int GWEN_Padd__UnpaddWithPkcs1Bt1Or2(GWEN_BUFFER *buf) {
  char *p;
  uint32_t len;
  uint32_t paddBytes;

  assert(buf);
  len=GWEN_Buffer_GetUsedBytes(buf);
  assert(len);

  p=GWEN_Buffer_GetStart(buf);
  if  (*p==0) {
    p++;
    len--;
  }
  if (len<11) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Too few bytes left (%d)", len);
    return GWEN_ERROR_INVALID;
  }

  if (*p!=0x01 && *p!=0x02) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Unsupported block type %02x", *p);
    return GWEN_ERROR_INVALID;
  }
  p++; len--;

  /* skip padding bytes */
  paddBytes=0;
  while(*p!=0x00 && len) {
    p++; len--;
    paddBytes++;
  }

  if (*p!=0x00) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Bad padding");
    return GWEN_ERROR_INVALID;
  }
  p++; len--;

  if (paddBytes<8) {
    /* at least 8 padding bytes are needed */
    DBG_ERROR(GWEN_LOGDOMAIN, "Bad padding (too few padding bytes)");
    return GWEN_ERROR_INVALID;
  }

  GWEN_Buffer_Crop(buf, GWEN_Buffer_GetUsedBytes(buf)-len, len);

  return 0;
}



int GWEN_Padd_UnpaddWithPkcs1Bt1(GWEN_BUFFER *src){
  return GWEN_Padd__UnpaddWithPkcs1Bt1Or2(src);
}



int GWEN_Padd_UnpaddWithPkcs1Bt2(GWEN_BUFFER *src){
  return GWEN_Padd__UnpaddWithPkcs1Bt1Or2(src);
}



int GWEN_Padd_ApplyPaddAlgo(const GWEN_CRYPT_PADDALGO *a, GWEN_BUFFER *buf) {
  int rv;
  unsigned int diff;
  unsigned int bsize;
  unsigned int dstSize;
  unsigned int chunkSize;
  GWEN_CRYPT_PADDALGOID aid;

  assert(a);
  assert(buf);

  aid=GWEN_Crypt_PaddAlgo_GetId(a);
  if (aid==GWEN_Crypt_PaddAlgoId_None)
    /* short return if there is no padding to be done */
    return 0;

  chunkSize=GWEN_Crypt_PaddAlgo_GetPaddSize(a);
  if (chunkSize==0) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Invalid chunk size (0)");
    return GWEN_ERROR_INVALID;
  }

  bsize=GWEN_Buffer_GetUsedBytes(buf);
  dstSize=bsize+(chunkSize-1);
  dstSize=(dstSize/chunkSize)*chunkSize;
  diff=dstSize-bsize;

  DBG_INFO(GWEN_LOGDOMAIN, "Padding with algo \"%s\"",
	   GWEN_Crypt_PaddAlgoId_toString(aid));

  switch(aid) {
  case GWEN_Crypt_PaddAlgoId_None:
    rv=0;
    break;

  case GWEN_Crypt_PaddAlgoId_Iso9796_1A4:
    if (dstSize>96) {
      DBG_ERROR(GWEN_LOGDOMAIN,
		"Padding size must be <=96 bytes (is %d)",
		dstSize);
      return GWEN_ERROR_INVALID;
    }
    rv=GWEN_Padd_PaddWithISO9796(buf);
    break;

  case GWEN_Crypt_PaddAlgoId_Pkcs1_1:
    rv=GWEN_Padd_PaddWithPkcs1Bt1(buf, dstSize);
    break;

  case GWEN_Crypt_PaddAlgoId_Pkcs1_2:
    rv=GWEN_Padd_PaddWithPkcs1Bt2(buf, dstSize);
    break;

  case GWEN_Crypt_PaddAlgoId_LeftZero:
    rv=GWEN_Buffer_FillLeftWithBytes(buf, 0, diff);
    break;

  case GWEN_Crypt_PaddAlgoId_RightZero:
    rv=GWEN_Buffer_FillWithBytes(buf, 0, diff);
    break;

  case GWEN_Crypt_PaddAlgoId_AnsiX9_23:
    return GWEN_Padd_PaddWithAnsiX9_23(buf);

  case GWEN_Crypt_PaddAlgoId_Iso9796_2:
    return GWEN_Padd_PaddWithIso9796_2(buf, dstSize);

  case GWEN_Crypt_PaddAlgoId_Iso9796_1:
  default:
    DBG_INFO(GWEN_LOGDOMAIN, "Algo-Type %d (%s) not supported",
	     aid, GWEN_Crypt_PaddAlgoId_toString(aid));
    return GWEN_ERROR_NOT_AVAILABLE;
  }

  if (rv) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Error padding with algo %d (%s)",
	      aid, GWEN_Crypt_PaddAlgoId_toString(aid));
    return GWEN_ERROR_GENERIC;
  }

  return rv;
}



int GWEN_Padd_UnapplyPaddAlgo(const GWEN_CRYPT_PADDALGO *a, GWEN_BUFFER *buf){
  int rv;
  GWEN_CRYPT_PADDALGOID aid;

  assert(a);
  assert(buf);

  aid=GWEN_Crypt_PaddAlgo_GetId(a);
  DBG_INFO(GWEN_LOGDOMAIN, "Unpadding with algo \"%s\"",
	   GWEN_Crypt_PaddAlgoId_toString(aid));

  switch(aid) {
  case GWEN_Crypt_PaddAlgoId_None:
    rv=0;
    break;

  case GWEN_Crypt_PaddAlgoId_Pkcs1_1:
    rv=GWEN_Padd_UnpaddWithPkcs1Bt1(buf);
    break;

  case GWEN_Crypt_PaddAlgoId_Pkcs1_2:
    rv=GWEN_Padd_UnpaddWithPkcs1Bt2(buf);
    break;

  case GWEN_Crypt_PaddAlgoId_AnsiX9_23:
    return GWEN_Padd_UnpaddWithAnsiX9_23(buf);

  case GWEN_Crypt_PaddAlgoId_Iso9796_2:
    return GWEN_Padd_UnpaddWithIso9796_2(buf);

  case GWEN_Crypt_PaddAlgoId_Iso9796_1:
  case GWEN_Crypt_PaddAlgoId_LeftZero:
  case GWEN_Crypt_PaddAlgoId_RightZero:
  case GWEN_Crypt_PaddAlgoId_Iso9796_1A4:
  default:
    DBG_INFO(GWEN_LOGDOMAIN, "Algo-Type %d (%s) not supported",
	     aid, GWEN_Crypt_PaddAlgoId_toString(aid));
    return GWEN_ERROR_NOT_AVAILABLE;
  }

  if (rv) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Error padding with algo %d (%s)",
	      aid, GWEN_Crypt_PaddAlgoId_toString(aid));
    return GWEN_ERROR_GENERIC;
  }

  return rv;
}





