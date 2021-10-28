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

#include "treq.h"

void rbiInit(SReqBatchIter *pRbi, SReqBatch *pReqBatch) {
  pRbi->pReqBatch = pReqBatch;
  pRbi->it = 0;
}

const SRequest *rbiNext(SReqBatchIter *pRbi) {
  if (pRbi->it >= pRbi->pReqBatch->nReqs) {
    return NULL;
  } else {
    return pRbi->pReqBatch->reqs[pRbi->it++];
  }
}