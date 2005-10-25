/* This file is auto-generated from "request.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef REQUEST_P_H
#define REQUEST_P_H

#include "request_l.h"


struct GWEN_IPC_REQUEST {
  GWEN_INHERIT_ELEMENT(GWEN_IPC_REQUEST)
  GWEN_LIST_ELEMENT(GWEN_IPC_REQUEST)
  int _usage;
  int _modified;

  GWEN_TYPE_UINT32 id;
  char *name;
  GWEN_TYPE_UINT32 ipcId;
  GWEN_TIME *expires;
  GWEN_IPC_REQUEST_LIST *subRequests;
  GWEN_IPC_REQUEST_STATUS status;
  GWEN_IPC_REQUEST_WORK_FN workFn;
};











#endif /* REQUEST_P_H */