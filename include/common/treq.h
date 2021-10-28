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

#ifndef _TD_TREQ_H_
#define _TD_TREQ_H_

#include "impl/treqImpl.h"

#ifdef __cplusplus
extern "C" {
#endif

// TYPES EXPOSED
typedef struct SRequest      SRequest;
typedef struct SReqBatch     SReqBatch;
typedef struct SReqBatchIter SReqBatchIter;

// SRequest
#define REQ_TYPE(pReq) ((pReq)->type)

// SReqBatch

// SReqBatchIter
void            rbiInit(SReqBatchIter *, SReqBatch *);
const SRequest *rbiNext(SReqBatchIter *);
#define rbiClear(pReqBatch)

#ifdef __cplusplus
}
#endif

#endif /*_TD_TREQ_H_*/