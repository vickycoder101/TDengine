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

#ifndef _TD_META_H_
#define _TD_META_H_

#include "impl/metaImpl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------ APIs Exposed ------------------------ */

// Types exported
typedef struct SMeta            SMeta;
typedef struct SMetaOptions     SMetaOptions;
typedef struct SMetaQueryHandle SMetaQueryHandle;
typedef struct SMetaQueryOpts   SMetaQueryOpts;
typedef struct STableOpts       STableOpts;

// SMeta operations
int    metaCreate(const char *path);
void   metaDestroy(const char *path);
SMeta *metaOpen(SMetaOptions *);
void   metaClose(SMeta *);
int    metaCreateTable(SMeta *, const STableOpts *);
int    metaDropTable(SMeta *, uint64_t tuid_t);
int    metaAlterTable(SMeta *, void *);
int    metaCommit(SMeta *);

// Options
SMetaOptions *metaOptionsCreate();
void          metaOptionsDestroy(SMetaOptions *);
void          metaOptionsSetCache(SMetaOptions *, size_t capacity);

// SMetaQueryHandle
SMetaQueryHandle *metaQueryHandleCreate(SMetaQueryOpts *);
void              metaQueryHandleDestroy(SMetaQueryHandle *);

// SMetaQueryOpts
SMetaQueryOpts *metaQueryOptionsCreate();
void            metaQueryOptionsDestroy(SMetaQueryOpts *);

// STableOpts
#define META_TABLE_OPTS_DECLARE(name) STableOpts name = {0}
void metaNormalTableOptsInit(STableOpts *, const char *name, const STSchema *pSchema);
void metaSuperTableOptsInit(STableOpts *, const char *name, tb_uid_t uid, const STSchema *pSchema,
                            const STSchema *pTagSchema);
void metaChildTableOptsInit(STableOpts *, const char *name, tb_uid_t suid, const SKVRow tags);
void metaTableOptsClear(STableOpts *);

#ifdef __cplusplus
}
#endif

#endif /*_TD_META_H_*/
