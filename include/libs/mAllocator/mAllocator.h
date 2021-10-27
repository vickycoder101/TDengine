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

#ifndef _TD_MALLOCATOR_H_
#define _TD_MALLOCATOR_H_

#include "impl/mAllocatorImpl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Type exposed
typedef struct SMemAllocator SMemAllocator;

// Constructor and destructor
SMemAllocator *memAllocatorCreate();
void           memAllocatorDestroy(SMemAllocator *);
int            memAllocatorInit(SMemAllocator *);
void           memAllocatorClear(SMemAllocator *);

// Operations on
static FORCE_INLINE void *mMalloc(SMemAllocator *pma, size_t size) { return (*(pma->malloc))(pma, size); }
static FORCE_INLINE void *mCalloc(SMemAllocator *pma, size_t nmemb, size_t size) {
  return (*(pma->calloc))(pma, nmemb, size);
}
static FORCE_INLINE void *mRealloc(SMemAllocator *pma, void *ptr, size_t size) {
  return (*(pma->realloc))(pma, ptr, size);
}
static FORCE_INLINE void   mFree(SMemAllocator *pma, void *ptr) { (*(pma->free))(pma, ptr); }
static FORCE_INLINE size_t mUsage(SMemAllocator *pma) { return (size_t)atomic_load_64(&(pma->usage)); }

#ifdef __cplusplus
}
#endif

#endif /*_TD_MALLOCATOR_H_*/