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
#include "vseDef.h"
#include "vseOptions.h"

static int  vseProcessReq(SVnodeSE *pVse, const SRequest *pReq);
static bool vseShouldCommit(SVnodeSE *pVse);
static void vseAsyncCommit(SVnodeSE *pVse);

/* ------------------------ IMPL ------------------------ */
SVnodeSE *vseOpen(const SVSEOptions *pVseOpt) {
  if (!vseValidateOptions(pVseOpt)) {
    /* TODO */
  }

  // TODO
  return NULL;
}

void vseClose(SVnodeSE *pVse) {
  // TODO
}

void vseProcessReqBatch(SVnodeSE *pVse, SReqBatch *pReqBatch) {
  SReqBatchIter rbi = {0};

  // Loop to process each request
  rbiInit(&rbi, pReqBatch);
  for (;;) {
    const SRequest *pReq = rbiNext(&rbi);
    if (pReq == NULL) break;
    // TODO

    int code = vseProcessReq(pVse, pReq);
    { /* TODO: handle the code */
    }
  }
  rbiClear(&rbi);

  // Check if the vse should commit
  if (vseShouldCommit(pVse)) {
    vseAsyncCommit(pVse);
  }
}

/* ------------------------ STATIC METHODS ------------------------ */
static int vseProcessReq(SVnodeSE *pVse, const SRequest *pReq) {
  // TODO
  return 0;
}

static bool vseShouldCommit(SVnodeSE *pVse) {
  // TODO
  return true;
}

static void vseAsyncCommit(SVnodeSE *pVse) {
  // TODO
}