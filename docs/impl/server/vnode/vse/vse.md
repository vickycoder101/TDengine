# Vnode Storage Engine

VES (**V**node **S**torate **E**ngine) is the storage engine of a vnode. The storage engine provides the storage and query of:
1. *meta data*
2. *time-series data*
3. *message queue data*.

VSE provides configurations including:
1. write buffer size
2. days per file in TSDB
3. retention policy of TSDB
4. retention policy of TQ
5. precision of timestamp in TSDB
6. compression policy of TSDB
7. update policy of TSDB
8. cache policy of TSDB
9. sma policy of TSDB
10. TTL policy of META

## APIs
```C
/* ------------------------ TYPES EXPOSED ------------------------ */
typedef struct SVnodeSE    SVnodeSE;
typedef struct SVSEOptions SVSEOptions;

/* ------------------------ SVnodeSE ------------------------ */
SVnodeSE *vseOpen(const SVSEOptions *);
void      vseClose(SVnodeSE *);
void      vseProcessReqBatch(SVnodeSE *, SReqBatch *);

/* ------------------------ SVSEOptions ------------------------ */
// SVSEOptions
```

## Usage examples

## Implementations