// Havok 3.1.0 slice s0111f260 -- the MOPP "query object" (vtable 0x014a6108, ctor 0x0111fbd0) and the
// helpers it drives: the primitive-array bounds accumulation, the axis/SAH split heuristic, the bucket
// merging passes and the node free lists. All of it is code EA linked out of a Havok 3.1.0 static
// library built with VC .NET 2003, hence /vc71 (see tools/matching/cl71.sh).
//
// VTABLE EVIDENCE (.rdata):
//   0x014a6108 = the query object of this slice: { 0111fc00, 0x0052e650, 0111fa60, 0111fa90, 011202d0 }
//                (0x0111fc00/0x011202d0 are outside this slice; 0111fbd0 stores this pointer).
//   The object owns two collaborators reached through +0x20 and +0x28; only the vtable slots the code
//   below actually calls are declared (slot numbers come from the call offsets in the disassembly).
#include "../s0111e2c0/s0111e2c0.h"

// ---------------------------------------------------------------------------------------------------
// A primitive reference record: 16 bytes, the float key the bucket sorts live on at +0x8. Records are
// copied as whole 16-byte blocks (two 16-byte-aligned locals in 0x0111faa0), so the alignment matters.
// ---------------------------------------------------------------------------------------------------
#define MCF(p, off) (*(float*)((char*)(p) + (off)))

struct __declspec(align(16)) MoppPrimRec
{
    uint32_t m_u0;   // +0x0
    uint32_t m_u4;   // +0x4
    float    m_key;  // +0x8
    uint32_t m_uC;   // +0xc

    bool operator<(const MoppPrimRec& o) const { return m_key < o.m_key; }
};

// { pointer to the first record, number of records, number of extra records appended after them }
struct MoppPrimArray
{
    MoppPrimRec* m_first;   // +0x0
    int32_t      m_count;   // +0x4
    int32_t      m_extra;   // +0x8
};

// 0x0120ad30 (outside this slice): Havok's float -> int conversion helper.
int32_t hkFloatToInt(float v);

struct MoppAxisBlock;
struct MoppBucket;

// ---------------------------------------------------------------------------------------------------
// The collaborator at query+0x28: only the slots this slice actually calls are declared (4 to 7).
// ---------------------------------------------------------------------------------------------------
struct MoppSplitter
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    // slot 4: cell coordinates of a record range on one axis (two integer results).
    virtual void getRangeCells(MoppAxisBlock* ctx, const MoppPrimRec* first, int32_t count,
                               int32_t* lo, int32_t* hi);
    // slot 5: quantise the given cell range into the 0x60-byte block at +0x34.
    virtual void splitCells(void* ctx, uint32_t a, int32_t b, int32_t* lo, int32_t* hi);
    // slot 6: clip a record against the split plane. Two argument shapes are used by the callers,
    // (record, plane, a, b, out) from 0x0111f9e0 and (record, a, b, -plane, record) from 0x0111f7e0,
    // so it is declared with an ellipsis; the callee pops the arguments.
    virtual void clipVector(const MoppPrimRec* rec, ...);
    // slot 7: per-axis cell coordinates of one record (returns the axis count).
    virtual int getAxisCells(const MoppPrimRec* rec, int* out);
};

// The collaborator at query+0x20: two distance probes and a range notification.
struct MoppProbe
{
    virtual void slot0();
    virtual void slot1();
    virtual float probeLo(MoppBucket* bucket);                          // slot 2
    virtual float probeHi(MoppBucket* bucket);                          // slot 3
    virtual void slot4();
    virtual void notify(void* node, void* range);                       // slot 5
};

// One of the three 0x20-byte axis records reached through query+0x34.
struct MoppAxisBlock
{
    int32_t m_w[8];
};

// The per-bucket working descriptor 0x0111f670 builds on its stack and hands to 0x0111f260 and
// 0x0111f7e0. 0x0111f260 rewrites the +0x30..+0x38 tail as it walks the candidate split positions.
struct MoppBucket
{
    int32_t      m_i00;    // +0x00  record budget left over from the previous round
    int32_t      m_p04;    // +0x04  query +0x38
    MoppPrimRec* m_p08;    // +0x08  first record of the array being split
    int32_t      m_i0c;    // +0x0c  record count
    float        m_f10;    // +0x10  1/(bucket width) or 1 when the width is degenerate
    int32_t      m_i14;    // +0x14
    int32_t      m_i18;    // +0x18  record count (again)
    float        m_f1c;    // +0x1c  1/(float)record count
    float        m_f20;    // +0x20  sort key of the record currently examined
    float*       m_p24;    // +0x24  the split plane (four floats)
    int32_t      m_i28;    // +0x28  lowest record key seen
    int32_t      m_i2c;    // +0x2c  highest record key seen
    int32_t      m_i30;    // +0x30  candidate split position
    int32_t      m_i34;    // +0x34  split index + start offset
    MoppPrimRec* m_p38;    // +0x38  current record
};

// The split state the query builds while a bucket is being searched (see 0x0111f260/0x0111f7e0).
struct MoppBucketState
{
    int32_t m_pad00[3];   // +0x00
    float   m_fAxis0Lo;   // +0x0c
    float   m_fAxis0Hi;   // +0x10
    float   m_fAxis1Lo;   // +0x14
    float   m_fAxis1Hi;   // +0x18
    float   m_fAxis2Lo;   // +0x1c
    float   m_fAxis2Hi;   // +0x20
    int32_t m_pad24[0x25]; // +0x24 .. +0xb7
    float*  m_pPlane;     // +0xb8  split plane; its sixth word is the axis count
    float   m_fBC;        // +0xbc
    float   m_fC0;        // +0xc0
    float   m_fC4;        // +0xc4  best (lowest) split cost so far
    int32_t m_tail[4];    // +0xc8  range handed to the probe notification
};

// { start, count, remainder } handed back out of 0x0111fe30.
struct MoppBucketOut
{
    MoppPrimRec* m_first;   // +0x0
    int32_t      m_count;   // +0x4
    int32_t      m_remain;  // +0x8
};

// A bucket/chunk descriptor as 0x0111f260 and 0x0111f7e0 use it.
struct MoppQueryChunk
{
    int32_t  m_u0;     // +0x00
    int32_t  m_i04;    // +0x04
    int32_t  m_u08;    // +0x08
    int32_t  m_u0c;    // +0x0c
    int32_t  m_u10;    // +0x10
    int32_t  m_u14;    // +0x14
    int32_t  m_u18;    // +0x18
    int32_t  m_u1c;    // +0x1c
    int32_t  m_i20;    // +0x20
    float*   m_p24;    // +0x24  axis lo bounds (four floats)
    int32_t  m_u28;    // +0x28
    int32_t  m_i2c;    // +0x2c
    int32_t  m_i30;    // +0x30
    int32_t  m_i34;    // +0x34
    int32_t* m_p38;    // +0x38
};

// ---------------------------------------------------------------------------------------------------
// The query object (vtable 0x014a6108).
// ---------------------------------------------------------------------------------------------------
struct MoppQuery;

struct MoppQuery
{
    uint32_t           m_vtbl;             // +0x00  0x014a6108
    uint16_t           m_memSizeAndFlags;  // +0x04
    uint16_t           m_refCount;         // +0x06  1
    MoppCompiler*      m_p08;              // +0x08  the builder (its +0x08/+0x0c/+0x10 are read)
    MoppPriorityQueue* m_queue;            // +0x0c
    MoppChainNode*     m_allocList;        // +0x10  nodes handed out (flag byte +0x4 == 0)
    int32_t            m_nAlloc;           // +0x14
    MoppChainNode*     m_freeList;         // +0x18  nodes on the free list (flag byte +0x4 != 0)
    int32_t            m_nFree;            // +0x1c
    MoppProbe*         m_probe;            // +0x20
    uint32_t           m_pad24;            // +0x24
    MoppSplitter*      m_splitter;         // +0x28
    uint32_t           m_pad2c;            // +0x2c
    uint32_t           m_pad30;            // +0x30
    MoppAxisBlock*     m_axisCtx;          // +0x34  three 0x20-byte axis records
    int32_t*           m_p38;              // +0x38

    MoppQuery* ctor();                                                       // 0x0111fbd0
    void freeNode(MoppChainNode* node);                                     // 0x0111fa60
    int  nodeCount();                                                       // 0x0111fa90
    MoppChainNode* newNode(MoppChainNode* parent, MoppPrimArray* prims);    // 0x0111f9e0
    void collectBounds(MoppPrimArray* prims, MoppChainNode* node);          // 0x0111f400
    void chooseSplitAxis(MoppChainNode* node, int* order, float* score);    // 0x0111f4c0
    void pickBestNode(int32_t idx, MoppBucketState* state, int32_t* best,
                      MoppBucket* bucket, MoppPrimArray* prims);             // 0x0111f260
    void bucketPass(int32_t mode, MoppBucketState* state, int32_t arg, int32_t* p3, int32_t* p4,
                    MoppPrimRec** p5, MoppPrimRec** p6, MoppPrimRec** p7,
                    MoppPrimRec** p8);                                      // 0x0111f7e0
    void splitBuckets(MoppPrimRec** p0, MoppPrimRec** p1, MoppPrimRec** p2, MoppPrimRec** p3,
                      MoppPrimRec** p4, MoppPrimRec** p5, MoppBucketState* state); // 0x0111fc30
    void mergeBuckets(MoppPrimArray* prims, MoppBucketState* state, int32_t arg,
                      MoppBucketOut* outA, MoppBucketOut* outB);            // 0x0111fe30
    void processBuckets(MoppBucketState* state, float* plane, MoppPrimArray* prims,
                        float* range, int32_t extra);                       // 0x0111f670
};

// 0x0111f9e0
// @ 0x0111f9e0
MoppChainNode* MoppQuery::newNode(MoppChainNode* parent, MoppPrimArray* prims)
{
    MoppChainNode* node = m_freeList;
    m_freeList = (MoppChainNode*)node->m_parent;
    m_nFree--;
    MoppChainNode* ret = node;
    node->reset();
    node->m_parent = parent;
    node->m_b04 = 1;
    node->m_iB8 = (uint32_t)prims->m_first;
    collectBounds(prims, node);
    for (int i = 0; i < 0x60; i += 0x20)
    {
        m_splitter->splitCells((char*)m_axisCtx + i, (uint32_t)prims->m_first, prims->m_count,
                               (int32_t*)((char*)node + 0xc), (int32_t*)((char*)node + 0x10));
        node = (MoppChainNode*)((char*)node + 8);
    }
    return ret;
}

// 0x0111fa90
// @ 0x0111fa90
int MoppQuery::nodeCount()
{
    return m_nFree + m_nAlloc;
}

// 0x0111fbd0
// @ 0x0111fbd0
MoppQuery* MoppQuery::ctor()
{
    m_refCount = 1;
    m_vtbl = 0x014a6108;
    m_allocList = 0;
    m_nAlloc = 0;
    m_freeList = 0;
    m_nFree = 0;
    m_p08 = 0;
    m_queue = 0;
    return this;
}

// 0x0111fa60
// @ 0x0111fa60
void MoppQuery::freeNode(MoppChainNode* node)
{
    if (node)
    {
        if (node->m_b04)
        {
            node->m_parent = m_freeList;
            m_freeList = node;
            m_nFree++;
        }
        else
        {
            node->m_parent = m_allocList;
            m_allocList = node;
            m_nAlloc++;
        }
    }
}

// 0x0111faa0
// @ 0x0111faa0
void MoppSortRecs(MoppPrimRec* base, int lo, int hi, int unused)
{
    MoppPrimRec tmp;
    int i;
    int j;
    do
    {
        MoppPrimRec pivot = base[(lo + hi) >> 1];
        i = lo;
        j = hi;
        do
        {
            for (; base[i].m_key < pivot.m_key; i++)
                ;
            for (; pivot.m_key < base[j].m_key; j--)
                ;
            if (j < i)
                break;
            if (j != i)
            {
                tmp = base[j];
                base[j] = base[i];
                base[i] = tmp;
            }
            j--;
            i++;
        } while (i <= j);
        if (lo < j)
            MoppSortRecs(base, lo, j, unused);
        lo = i;
    } while (i < hi);
}

// 0x0111f4c0
// @ 0x0111f4c0
void MoppQuery::chooseSplitAxis(MoppChainNode* node, int* order, float* score)
{
    if (node != 0)
    {
    float best = 0.0f;
    float len[3];
    int axis = 0;
    len[0] = MCF(node, 0x10) - MCF(node, 0xc);
    if ((MoppAxisBlock*)node->m_iB8 == m_axisCtx)
        len[0] = len[0] * 0.66f;
    if (len[0] > 0.0f)
        best = len[0];
    len[1] = MCF(node, 0x18) - MCF(node, 0x14);
    if ((MoppAxisBlock*)node->m_iB8 == m_axisCtx + 1)
        len[1] = len[1] * 0.66f;
    if (len[1] > best)
    {
        axis = 1;
        best = len[1];
    }
    len[2] = MCF(node, 0x20) - MCF(node, 0x1c);
    if ((MoppAxisBlock*)node->m_iB8 == m_axisCtx + 2)
        len[2] = len[2] * 0.66f;
    if (len[2] > best)
    {
        axis = 2;
        best = len[2];
    }
    int a1 = (axis + 1) % 3;
    int a2 = (axis + 2) % 3;
    order[0] = axis;
    score[0] = 0.0f;
    float d;
    if (len[a1] < len[a2])
    {
        order[1] = a2;
        d = (best - len[a2]) / best;
        score[1] = d * d * d * 16.0f * 0.05f;
        order[2] = a1;
        d = (best - len[a1]) / best;
    }
    else
    {
        order[1] = a1;
        d = (best - len[a1]) / best;
        score[1] = d * d * d * 16.0f * 0.05f;
        order[2] = a2;
        d = (best - len[a2]) / best;
    }
    score[2] = d * d * d * 16.0f * 0.05f;
    return;
    }
    order[0] = 0;
    order[1] = 1;
    order[2] = 2;
    score[0] = 0;
    score[1] = 0;
    score[2] = 0;
}

// 0x0111f400
// @ 0x0111f400
void MoppQuery::collectBounds(MoppPrimArray* prims, MoppChainNode* node)
{
    uint32_t* cur = (uint32_t*)prims->m_first;
    uint32_t low = *cur;
    uint32_t high = low;

    node->m_nAxes = 0;
    node->m_pad30[1] = 0;
    node->m_pad30[0] = -1;
    int n = prims->m_count - 1;
    if (n >= 0)
    {
        int out[3];
        n++;
        do
        {
            uint32_t v = *cur;
            if (v > high)
                high = v;
            if (v < low)
                low = v;
            int nAxes = m_splitter->getAxisCells((const MoppPrimRec*)cur, out);
            if (node->m_nAxes < nAxes)
                node->m_nAxes = nAxes;
            for (int ax = 0; ax < nAxes; ax++)
            {
                uint32_t c = out[ax];
                if (c < MCW(node, 0x30))
                    MCW(node, 0x30) = c;
                if (MCW(node, 0x34 + ax * 4) < c)
                    MCW(node, 0x34 + ax * 4) = c;
            }
            cur += 4;
        } while (--n != 0);
    }
    node->m_i24 = low;
    MCW(node, 0x08) = prims->m_count;
    node->m_i28 = high;
}

// 0x0111f670
// @ 0x0111f670
void MoppQuery::processBuckets(MoppBucketState* state, float* plane, MoppPrimArray* prims,
                               float* range, int32_t extra)
{
    MoppBucket bucket;
    bucket.m_i00 = extra;
    bucket.m_p04 = (int32_t)m_p38;
    bucket.m_p08 = prims->m_first;
    bucket.m_i0c = prims->m_count;
    bucket.m_i18 = prims->m_count;
    bucket.m_f1c = 1.0f / (float)prims->m_count;
    bucket.m_p24 = plane;
    bucket.m_i28 = (int32_t)prims->m_first->m_u0;
    bucket.m_i2c = (int32_t)prims->m_first->m_u0;
    float span = range[1] - range[0];
    bucket.m_f10 = 1.0f;
    if (span >= 0.001f)
        bucket.m_f10 = 1.0f / span;

    int32_t limit = prims->m_extra;
    if ((int32_t)m_p08->m_pad08 < limit)
        limit = (int32_t)m_p08->m_pad08;

    int32_t best = 0;
    if (prims->m_count > 0)
    {
        for (int32_t i = 0; i < prims->m_count; i++)
        {
            MoppPrimRec* rec = prims->m_first + i;
            bucket.m_i14 = 0;
            bucket.m_f20 = rec->m_key;
            if ((int32_t)rec->m_u0 < bucket.m_i28)
                bucket.m_i28 = (int32_t)rec->m_u0;
            if ((int32_t)rec->m_u0 > bucket.m_i2c)
                bucket.m_i2c = (int32_t)rec->m_u0;
            m_queue->popAbove(rec->m_key);
            MoppPriorityQueue* q = m_queue;
            for (int32_t k = q->m_count - 1; limit < k; k--)
            {
                q->m_heap[k - 1] = q->m_heap[k];
                q->m_heap[k] = 0;
                q->m_count--;
            }
            pickBestNode(i, state, &best, &bucket, prims);
        }
    }
    MoppPriorityQueue* q = m_queue;
    for (int32_t k = q->m_count - 1; 0 < k; k--)
        q->m_heap[k] = 0;
    q->m_out = 0;
    q->m_count = 0;
}

// 0x0111f260
// @ 0x0111f260
void MoppQuery::pickBestNode(int32_t idx, MoppBucketState* state, int32_t* best,
                             MoppBucket* bucket, MoppPrimArray* prims)
{
    MoppProbe* probe = m_probe;
    int32_t half = (int32_t)m_p08->m_p0c >> 1;
    float base = probe->probeLo(bucket);
    MoppPriorityQueue* q = m_queue;
    int32_t n = q->m_count;
    float bestKey = 1e7f;
    int32_t lo = 0;
    int32_t i;

    if (n == 0)
    {
        MoppChainNode* node = q->m_out;
        if (node == 0)
            goto insert;
        bucket->m_p38 = *(MoppPrimRec**)&node->m_key;   // the node's payload word
        i = 0;
    }
    else
    {
        if (!(base <= state->m_fC4))
            goto insert;
        if (half <= 0)
        {
            i = n;
        }
        else
        {
            i = *best + half;
            if (i > n)
                i = n;
            lo = *best - half;
            if (lo < 0)
                lo = 0;
        }
    }

    for (;;)
    {
        bucket->m_i30 = i;
        bucket->m_i34 = prims->m_count - idx + i;
        float cost = probe->probeHi(bucket) + base;
        if (cost < bestKey)
        {
            bestKey = cost;
            *best = i;
            if (cost < state->m_fC4)
            {
                state->m_fC4 = cost;
                state->m_pPlane = bucket->m_p24;
                state->m_fBC = bucket->m_f20;
                state->m_fC0 = *(const float*)&bucket->m_p38;
                int32_t d = i - half;
                if (d < lo)
                {
                    lo = d;
                    if (d < 0)
                        lo = 0;
                }
                probe->notify(bucket, state->m_tail);
            }
        }
        if (--i < lo)
            break;
        MoppChainNode* node = (i > q->m_count) ? 0 : q->m_heap[i];
        bucket->m_p38 = *(MoppPrimRec**)&node->m_key;   // the node's payload word
    }
    (*best)--;

insert:
    // The queue stores untyped node pointers; here the entry is the record itself.
    m_queue->insert((MoppChainNode*)(prims->m_first + idx));
}

// 0x0111f7e0
// @ 0x0111f7e0
void MoppQuery::bucketPass(int32_t mode, MoppBucketState* state, int32_t arg, int32_t* p3,
                           int32_t* p4, MoppPrimRec** p5, MoppPrimRec** p6, MoppPrimRec** p7,
                           MoppPrimRec** p8)
{
    MoppPrimRec tmpA;
    MoppPrimRec tmpB;
    switch (mode)
    {
    case 3:
        *p5 += 1;
        return;
    case 1:
        *p7 -= 1;
        *p6 -= 1;
        if (*p5 == *p7)
            return;
        tmpA = **p6;
        **p7 = **p5;
        **p5 = tmpA;
        return;
    case 2:
        (*p3)--;
        (*p4)++;
        *p7 -= 1;
        {
            float* plane = state->m_pPlane;
            float mid = (state->m_fC0 + state->m_fBC) * 0.5f;
            m_splitter->clipVector(*p5, plane, *(float*)&arg, mid, *p7);
            float neg[4];
            neg[0] = -plane[0];
            neg[1] = -plane[1];
            neg[2] = -plane[2];
            neg[3] = -plane[3];
            m_splitter->clipVector(*p5, arg, -mid, neg, *p5);
        }
        *p5 += 1;
        return;
    case 0:
        *p7 -= 1;
        *p8 -= 1;
        *p6 -= 1;
        {
            MoppPrimRec* a = *p5;
            MoppPrimRec* b = *p6;
            MoppPrimRec* c = *p7;
            MoppPrimRec* d = *p8;
            tmpA = *a;
            tmpB = *b;
            *c = *d;
            *d = tmpA;
            if (a != b)
                *a = tmpB;
        }
        return;
    }
}

// 0x0111fc30
// @ 0x0111fc30
void MoppQuery::splitBuckets(MoppPrimRec** p0, MoppPrimRec** p1, MoppPrimRec** p2,
                             MoppPrimRec** p3, MoppPrimRec** p4, MoppPrimRec** p5,
                             MoppBucketState* state)
{
    int32_t nAxes = ((const int32_t*)state->m_pPlane)[5];
    int32_t axis = 0;
    float best = 0.0f;
    float len;

    if (nAxes != 0)
    {
        len = state->m_fAxis0Hi - state->m_fAxis0Lo;
        if (len > 0.0f)
            best = len;
    }
    if (nAxes != 1)
    {
        len = state->m_fAxis1Hi - state->m_fAxis1Lo;
        if (len > best)
        {
            axis = 1;
            best = len;
        }
    }
    if (nAxes != 2)
    {
        len = state->m_fAxis2Hi - state->m_fAxis2Lo;
        if (len > best)
            axis = 2;
    }

    MoppPrimRec* first = *p4;
    int32_t count = (int32_t)(*p5 - first);
    int32_t cells[2];
    m_splitter->getRangeCells(m_axisCtx + axis, first, count, &cells[0], &cells[1]);
    if (count > 1)
        MoppSortRecs(first, 0, count - 1, 0);

    bool aShort = (int32_t)((*p1 - *p0) & ~15) < (int32_t)((*p3 - *p2) & ~15);
    MoppPrimRec tmpX;
    MoppPrimRec tmpY;
    MoppPrimRec tmpZ;
    while (*p4 < *p5)
    {
        int32_t na = (int32_t)(*p1 - *p0);
        int32_t nb = (int32_t)(*p3 - *p2);
        if (aShort)
            nb *= 4;
        else
            na *= 4;
        if (na >= nb)
        {
            *p3 += 1;
            *p4 += 1;
            aShort = false;
        }
        else
        {
            MoppPrimRec* end = *p5 - 1;
            tmpX = *end;
            tmpY = **p2;
            tmpZ = *end;
            *end = **p4;
            **p1 = tmpZ;
            **p4 = tmpY;
            *p1 += 1;
            *p2 += 1;
            *p4 += 1;
            *p3 += 1;
            aShort = true;
        }
    }
}

// 0x0111fe30
// @ 0x0111fe30
void MoppQuery::mergeBuckets(MoppPrimArray* prims, MoppBucketState* state, int32_t arg,
                             MoppBucketOut* outA, MoppBucketOut* outB)
{
    MoppPrimRec* first = prims->m_first;
    int32_t extra = prims->m_extra;
    MoppPrimRec* mid = first + prims->m_count;
    MoppPrimRec* end = mid + extra;
    MoppPrimRec* base = first;
    MoppPrimRec* cursor = first;
    MoppPrimRec* endA = end;
    MoppPrimRec* endB = end;
    MoppPrimRec* midCopy = mid;
    int32_t counter = 0;

    while (cursor < mid)
    {
        float key0 = *((const float*)cursor + 2);
        float key1 = *((const float*)cursor + 3);
        int32_t mode;
        if (key0 < state->m_fBC)
            mode = (key1 <= state->m_fC0) ? 0 : 2;
        else
            mode = (key1 <= state->m_fC0) ? 1 : 3;
        bucketPass(mode, state, arg, &extra, &counter, &cursor, &mid, &endA, &endB);
    }

    MoppPrimRec* cur = base;
    endB = end;
    splitBuckets(&cur, &mid, &endB, &endA, &endB, &endA, state);

    int32_t count = (int32_t)((char*)mid - (char*)cur) / 16;
    outA->m_count = count;
    outA->m_remain = hkFloatToInt((float)count * (float)extra / (float)prims->m_count);
    outB->m_count = (int32_t)((char*)endA - (char*)endB) / 16;
    outB->m_remain = arg - outA->m_remain;
    outA->m_first = base;
    MoppPrimRec* dst = mid + outA->m_remain;
    outB->m_first = dst;
    if (outB->m_remain != 0)
    {
        while (endB < endA)
        {
            *dst++ = *endB++;
        }
    }
}
