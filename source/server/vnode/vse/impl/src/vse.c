/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "vse.h"

typedef void SReqBatch;
typedef void SRequest;

int vseProcessReqBatch(SVnodeSE *pvse, SReqBatch *pReqBatch) {
  for (;;) {
    /* code: iter the req batch and process each req*/
  }

  return 0;
}

/* ------------------------ STATIC METHODS ------------------------ */
static int vseProcessReq(SVnodeSE *pvse, SRequest *pReq) {
  // int code;


  // tqPush(pReq);

  // if (1 /* REQUEST is META REQUEST */) {
  //   code = metaProcessReq(pvse, pReq);
  // } else {
  //   code = tsdbProcessReq(pvse, pReq);
  // }

  // Process the code

  // Send rsp

  return 0;
}