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

#include "mAllocator.h"

typedef struct {
  bool isThreadSafe;  // now default is false
} SStackAllocator;

static void *stackAllocatorMalloc(struct SMemAllocator *pma, size_t size) {
  SStackAllocator *psa = (SStackAllocator *)(pma->impl);
  void *           ptr;

  ptr = malloc(size + sizeof(size_t));
  if (ptr) {
    *(size_t *)ptr = size;
    pma->usage += (size + sizeof(size_t));
  }

  return POINTER_SHIFT(ptr, sizeof(size_t));
}

static void *stackAllocatorCalloc(struct SMemAllocator *pma, size_t nmemb, size_t size) {
  void * ptr;
  size_t rsize = nmemb * size;

  ptr = stackAllocatorMalloc(pma, rsize);
  if (ptr) {
    memset(ptr, 0, rsize);
  }

  return NULL;
}

static void *stackAllocatorRealloc(struct SMemAllocator *pma, void *ptr, size_t size) {
  size_t bsize;
  void * tptr;
  void * nptr;

  tptr = POINTER_SHIFT(ptr, -sizeof(size_t));
  bsize = *(size_t *)tptr;

  if (bsize >= size) {
    return ptr;
  } else {
    // TODO: handle realloc error here
    nptr = realloc(tptr, size + sizeof(size_t));
    if (nptr == NULL) {
      return NULL;
    }

    *(size_t *)nptr = size;
    pma->usage += (size - bsize);
    return POINTER_SHIFT(nptr, sizeof(size_t));
  }
}

static void stackAllocatorFree(struct SMemAllocator *pma, void *ptr) {
  size_t bsize;
  void * tptr;
  if (ptr) {
    tptr = POINTER_SHIFT(ptr, -sizeof(size_t));
    bsize = *(size_t *)tptr;
    free(tptr);
    pma->usage -= (bsize + sizeof(size_t));
  }
}