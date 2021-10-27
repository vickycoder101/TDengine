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

#ifndef _TD_MALLOCATOR_INTERNAL_H_
#define _TD_MALLOCATOR_INTERNAL_H_

#include "os.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MEM_ALLOCATOR_APIS                                            \
  void *(*malloc)(struct SMemAllocator *, size_t size);               \
  void *(*calloc)(struct SMemAllocator *, size_t nmemb, size_t size); \
  void *(*realloc)(struct SMemAllocator *, void *, size_t size);      \
  void (*free)(struct SMemAllocator *, void *);

struct SMemAllocator {
  size_t usage;
  void * impl;
  MEM_ALLOCATOR_APIS
};

#ifdef __cplusplus
}
#endif

#endif /*_TD_MALLOCATOR_INTERNAL_H_*/