/***************************************************************************
    begin       : Sun Dec 16 2018
    copyright   : (C) 2018 by Martin Preuss
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


#ifndef GWEN_XML2DB_H
#define GWEN_XML2DB_H


#include <gwenhywfar/db.h>
#include <gwenhywfar/xml.h>



GWENHYWFAR_API int GWEN_Xml2Db(GWEN_XMLNODE *xmlNodeDocument,
                               GWEN_XMLNODE *xmlNodeSchema,
                               GWEN_DB_NODE *dbDestination);



#endif /* GWEN_XML2DB_H */
