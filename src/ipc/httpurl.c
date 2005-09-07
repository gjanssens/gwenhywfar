/* This file is auto-generated from "httpurl.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "httpurl_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/debug.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>


GWEN_LIST_FUNCTIONS(GWEN_HTTP_URL, GWEN_HttpUrl)
GWEN_LIST2_FUNCTIONS(GWEN_HTTP_URL, GWEN_HttpUrl)


GWEN_HTTP_URL *GWEN_HttpUrl_new() {
  GWEN_HTTP_URL *st;

  GWEN_NEW_OBJECT(GWEN_HTTP_URL, st)
  st->_usage=1;
  GWEN_LIST_INIT(GWEN_HTTP_URL, st)
  return st;
}


void GWEN_HttpUrl_free(GWEN_HTTP_URL *st) {
  if (st) {
    assert(st->_usage);
    if (--(st->_usage)==0) {
  if (st->protocol)
    free(st->protocol);
  if (st->server)
    free(st->server);
  if (st->path)
    free(st->path);
  if (st->vars)
    GWEN_DB_Group_free(st->vars);
  if (st->url)
    free(st->url);
  GWEN_LIST_FINI(GWEN_HTTP_URL, st)
  GWEN_FREE_OBJECT(st);
    }
  }

}


GWEN_HTTP_URL *GWEN_HttpUrl_dup(const GWEN_HTTP_URL *d) {
  GWEN_HTTP_URL *st;

  assert(d);
  st=GWEN_HttpUrl_new();
  if (d->protocol)
    st->protocol=strdup(d->protocol);
  if (d->server)
    st->server=strdup(d->server);
  st->port=d->port;
  if (d->path)
    st->path=strdup(d->path);
  if (d->vars)
    st->vars=GWEN_DB_Group_dup(d->vars);
  if (d->url)
    st->url=strdup(d->url);
  return st;
}


int GWEN_HttpUrl_toDb(const GWEN_HTTP_URL *st, GWEN_DB_NODE *db) {
  assert(st);
  assert(db);
  if (st->protocol)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "protocol", st->protocol))
      return -1;
  if (st->server)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "server", st->server))
      return -1;
  if (GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "port", st->port))
    return -1;
  if (st->path)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "path", st->path))
      return -1;
  if (st->vars)
    if (GWEN_DB_AddGroupChildren(st->vars, GWEN_DB_GetGroup(db, GWEN_DB_FLAGS_DEFAULT, "vars")))
      return -1;
  if (st->url)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "url", st->url))
      return -1;
  return 0;
}


GWEN_HTTP_URL *GWEN_HttpUrl_fromDb(GWEN_DB_NODE *db) {
GWEN_HTTP_URL *st;

  assert(db);
  st=GWEN_HttpUrl_new();
  GWEN_HttpUrl_SetProtocol(st, GWEN_DB_GetCharValue(db, "protocol", 0, 0));
  GWEN_HttpUrl_SetServer(st, GWEN_DB_GetCharValue(db, "server", 0, 0));
  GWEN_HttpUrl_SetPort(st, GWEN_DB_GetIntValue(db, "port", 0, 0));
  GWEN_HttpUrl_SetPath(st, GWEN_DB_GetCharValue(db, "path", 0, 0));
  if (1) {
    GWEN_DB_NODE *dbT;

    dbT=GWEN_DB_GetGroup(db, GWEN_PATH_FLAGS_NAMEMUSTEXIST, "vars");
    if (dbT) st->vars=GWEN_DB_Group_dup(dbT);
  }
  GWEN_HttpUrl_SetUrl(st, GWEN_DB_GetCharValue(db, "url", 0, 0));
  st->_modified=0;
  return st;
}


const char *GWEN_HttpUrl_GetProtocol(const GWEN_HTTP_URL *st) {
  assert(st);
  return st->protocol;
}


void GWEN_HttpUrl_SetProtocol(GWEN_HTTP_URL *st, const char *d) {
  assert(st);
  if (st->protocol)
    free(st->protocol);
  if (d)
    st->protocol=strdup(d);
  else
    st->protocol=0;
  st->_modified=1;
}


const char *GWEN_HttpUrl_GetServer(const GWEN_HTTP_URL *st) {
  assert(st);
  return st->server;
}


void GWEN_HttpUrl_SetServer(GWEN_HTTP_URL *st, const char *d) {
  assert(st);
  if (st->server)
    free(st->server);
  if (d)
    st->server=strdup(d);
  else
    st->server=0;
  st->_modified=1;
}


int GWEN_HttpUrl_GetPort(const GWEN_HTTP_URL *st) {
  assert(st);
  return st->port;
}


void GWEN_HttpUrl_SetPort(GWEN_HTTP_URL *st, int d) {
  assert(st);
  st->port=d;
  st->_modified=1;
}


const char *GWEN_HttpUrl_GetPath(const GWEN_HTTP_URL *st) {
  assert(st);
  return st->path;
}


void GWEN_HttpUrl_SetPath(GWEN_HTTP_URL *st, const char *d) {
  assert(st);
  if (st->path)
    free(st->path);
  if (d)
    st->path=strdup(d);
  else
    st->path=0;
  st->_modified=1;
}


GWEN_DB_NODE *GWEN_HttpUrl_GetVars(const GWEN_HTTP_URL *st) {
  assert(st);
  return st->vars;
}


void GWEN_HttpUrl_SetVars(GWEN_HTTP_URL *st, GWEN_DB_NODE *d) {
  assert(st);
  if (st->vars)
    GWEN_DB_Group_free(st->vars);
  if (d)
    st->vars=GWEN_DB_Group_dup(d);
  else
    st->vars=0;
  st->_modified=1;
}


const char *GWEN_HttpUrl_GetUrl(const GWEN_HTTP_URL *st) {
  assert(st);
  return st->url;
}


void GWEN_HttpUrl_SetUrl(GWEN_HTTP_URL *st, const char *d) {
  assert(st);
  if (st->url)
    free(st->url);
  if (d)
    st->url=strdup(d);
  else
    st->url=0;
  st->_modified=1;
}


int GWEN_HttpUrl_IsModified(const GWEN_HTTP_URL *st) {
  assert(st);
  return st->_modified;
}


void GWEN_HttpUrl_SetModified(GWEN_HTTP_URL *st, int i) {
  assert(st);
  st->_modified=i;
}


void GWEN_HttpUrl_Attach(GWEN_HTTP_URL *st) {
  assert(st);
  st->_usage++;
}
GWEN_HTTP_URL *GWEN_HttpUrl_List2__freeAll_cb(GWEN_HTTP_URL *st, void *user_data) {
  GWEN_HttpUrl_free(st);
return 0;
}


void GWEN_HttpUrl_List2_freeAll(GWEN_HTTP_URL_LIST2 *stl) {
  if (stl) {
    GWEN_HttpUrl_List2_ForEach(stl, GWEN_HttpUrl_List2__freeAll_cb, 0);
    GWEN_HttpUrl_List2_free(stl); 
  }
}




GWEN_HTTP_URL_LIST *GWEN_HttpUrl_List_dup(const GWEN_HTTP_URL_LIST *stl) {
  if (stl) {
    GWEN_HTTP_URL_LIST *nl;
    GWEN_HTTP_URL *e;

    nl=GWEN_HttpUrl_List_new();
    e=GWEN_HttpUrl_List_First(stl);
    while(e) {
      GWEN_HTTP_URL *ne;

      ne=GWEN_HttpUrl_dup(e);
      assert(ne);
      GWEN_HttpUrl_List_Add(ne, nl);
      e=GWEN_HttpUrl_List_Next(e);
    } /* while (e) */
    return nl;
  }
  else
    return 0;
}



