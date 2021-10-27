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

typedef struct SPANode {
  struct SPANode *prev;
  size_t          tsize;
  size_t          used;
  char            data[];
} SPANode;

typedef struct {
  size_t   ssize;  // step size
  SPANode *inuse;
  SPANode  node;
} SPoolAllocator;

static SPANode *PANodeNew(size_t size);
static void     PANodeFree(SPANode *pNode);

static void *poolAllocatorMalloc(struct SMemAllocator *pma, size_t size) {
  SPoolAllocator *ppa = (SPoolAllocator *)(pma->impl);
  void *          ptr = NULL;
  size_t          tsize = size + sizeof(size_t);  // total size need to allocate
  size_t          rsize;                          // remain size

  rsize = ppa->inuse->tsize - ppa->inuse->used;
  if (rsize < tsize) {
    SPANode *pNode = PANodeNew(MAX(ppa->ssize, tsize));
    if (pNode == NULL) {
      return NULL;
    }

    pNode->prev = ppa->inuse;
    ppa->inuse = pNode;
    pma->usage += rsize;
  }

  ptr = ppa->inuse->data + ppa->inuse->used;
  ppa->inuse->used += tsize;
  *(size_t *)ptr = size;
  ptr = POINTER_SHIFT(ptr, sizeof(size_t));
  pma->usage += tsize;

  return ptr;
}

static void *poolAllocatorCalloc(struct SMemAllocator *pma, size_t nmemb, size_t size) {
  void * ptr = NULL;
  size_t rsize = nmemb * size;

  ptr = poolAllocatorMalloc(pma, rsize);
  if (ptr) {
    memset(ptr, 0, rsize);
  }

  return NULL;
}

static size_t poolAllocatorFree(struct SMemAllocator *pma, void *ptr) {
  SPoolAllocator *ppa = (SPoolAllocator *)(pma->impl);

  if (ptr) {
    size_t size = *(size_t *)POINTER_SHIFT(ptr, -sizeof(size_t));
    if (POINTER_SHIFT(ptr, size) == POINTER_SHIFT(ppa->inuse->data, ppa->inuse->used)) {
      ppa->inuse->used -= (size + sizeof(size_t));
      pma->usage -= (size + sizeof(size_t));

      if ((ppa->inuse->used == 0) && (ppa->inuse != &(ppa->node))) {
        SPANode *pNode = ppa->inuse;
        ppa->inuse = pNode->prev;
        PANodeFree(pNode);
      }
    }
  }
}

static void *poolAllocatorRealloc(struct SMemAllocator *pma, void *ptr, size_t size) {
  ASSERT(0);
  //   TODO: try to implement this function
  size_t          bsize;  // buffer size
  SPoolAllocator *ppa = (SPoolAllocator *)(pma->impl);

  if (ptr == NULL) {
    bsize = 0;
  } else {
    bsize = *(size_t *)POINTER_SHIFT(ptr, sizeof(size_t));
  }

  if (bsize >= size) {
    return ptr;
  }

  // TODO: Free and reallocate
  if (POINTER_SHIFT(ptr, bsize) == POINTER_SHIFT(ppa->inuse->data, ppa->inuse->used)) {
    // May can realloc in place
    size_t rsize = ppa->inuse->tsize - ppa->inuse->used + bsize + sizeof(size_t);
    if (rsize >= size) {
      *(size_t *)POINTER_SHIFT(ptr, sizeof(size_t)) = size;
      ppa->inuse->used = ppa->inuse->used + size - bsize;
      pma->usage += ppa->inuse->used + size - bsize;
    } else {
      // TODO
    }
  } else {
    //   TODO
  }

  return NULL;
}

static SPANode *PANodeNew(size_t size) {
  SPANode *pNode = NULL;

  pNode = (SPANode *)malloc(size + sizeof(*pNode));
  if (pNode) {
    pNode->prev = NULL;
    pNode->tsize = size;
    pNode->used = 0;
  }

  return pNode;
}

static void PANodeFree(SPANode *pNode) {
  if (pNode) {
    free(pNode);
  }
}