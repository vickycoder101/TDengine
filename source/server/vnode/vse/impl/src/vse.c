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
#include "vseCommit.h"
#include "vseDef.h"
#include "vseOptions.h"

static SVnodeSE *vseNew();
static void      vseFree(SVnodeSE *pVse);
static int       vseProcessReq(SVnodeSE *pVse, const SRequest *pReq);

/* ------------------------ IMPL ------------------------ */
SVnodeSE *vseOpen(const SVSEOptions *pVseOpt) {
  SVnodeSE *pVse = NULL;

  if (!vseValidateOptions(pVseOpt)) {
    return NULL;
  }

  pVse = vseNew();
  if (pVse == NULL) {
    return NULL;
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

static SVnodeSE *vseNew() {
  SVnodeSE *pVse = NULL;

  pVse = (SVnodeSE *)calloc(1, sizeof(*pVse));

  return pVse;
}

static void vseFree(SVnodeSE *pVse) {
  if (pVse) {
    free(pVse);
  }
}