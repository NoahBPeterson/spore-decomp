// Slice s007391f0 — mesh merge pass in the model/mesh region of SporeApp.exe.
//
// 3870-byte /O2 routine with an SEH frame and __cdecl calling convention.  Given a list of
// source "parts" and an output mesh container it
//   1. gathers the union of all vertex streams (key triple + payload) into the output,
//   2. merges the index batches (dedup by remapped id list) and builds per-batch remap tables,
//   3. finalises every stream/batch/vertex entry, copies payloads with the computed offsets,
//   4. rebuilds the range table of the output.
// Layouts below are recovered from the disassembly (offsets in comments).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"
#include <new>

typedef unsigned int uint;
typedef unsigned short ushort;

struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};

extern void* __cdecl SporeNew(unsigned size, const char* name, int a, int b, const char* file, int line);
extern void __cdecl operator_delete__(void* p);

// ---- containers -------------------------------------------------------------------
// One id entry of a batch: low half = stream index, high half = vertex-entry slot
struct IdEntry { short lo; short hi; };

// fixed_vector<IdEntry, 6> as laid out by the engine (0x30 bytes)
struct IdVec {
    IdEntry* begin;     // +0
    IdEntry* end;       // +4
    IdEntry* cap;       // +8
    int pad0c;          // +0xc
    IdEntry* inlinePtr; // +0x10
    IdEntry buf[6];     // +0x18
    void __thiscall DoAssign(IdEntry* first, IdEntry* last, int n);
    ~IdVec() { if (begin && begin != inlinePtr) operator_delete__(begin); }
};

// 16-byte per-vertex-entry record of a batch
struct VertEntry { int count; int pad4; short fmt; short pad0a; int pad0c; };
// fixed_vector<VertEntry, 3> embedded in a batch at +0x44 (0x48 bytes)
struct VertVec {
    VertEntry* begin;       // +0
    VertEntry* end;         // +4
    VertEntry* cap;         // +8
    int pad0c;
    VertEntry* inlinePtr;   // +0x10
    int pad14;
    VertEntry buf[3];       // +0x18
    VertVec() { begin = end = buf; cap = buf + 3; inlinePtr = buf; }
    ~VertVec();                         // 0x0041f9b0
    void __thiscall Resize(int n);      // 0x004751a0
};

// 0x20-byte stream payload (starts at +0x10 of a stream entry)
struct Payload {
    int count;          // +0
    char* data;         // +4
    short fmt;          // +8
    ushort stride;      // +0xa
    IRefCount* ref;     // +0xc
};
// a source stream (element of a part's stream vector)
struct SrcStream {
    int k0, k1, k2;     // key triple
    int type;           // +0xc (8, 5 or 9 matter)
    Payload payload;    // +0x10
};
// an output stream
struct OutStream {
    int k0, k1, k2, k3;
    Payload payload;
};

// 0x8c-byte index batch
struct Batch {
    int base;           // +0
    int kind;           // +4
    short fmt;          // +8
    short fmtB;         // +0xa
    IRefCount* ref;     // +0xc
    int count;          // +0x10
    IdVec ids;          // +0x14
    VertVec verts;      // +0x44
    Batch()
    {
        base = 0; kind = 0; fmt = 0; fmtB = 0; ref = 0; count = 0;
        ids.begin = ids.end = ids.buf; ids.cap = ids.buf + 6; ids.inlinePtr = ids.buf;
    }
    ~Batch() { if (ref) ref->Release(); }
};

// 0x14-byte range record
struct Range { int a, b, c, d, e; };

struct Part {
    char pad0[8];
    SrcStream* streams;     // +8
    SrcStream* streamsEnd;  // +0xc
    char pad10[0xc];
    Batch* batches;         // +0x1c
    Batch* batchesEnd;      // +0x20
    char pad24[0xc];
    Range* ranges;          // +0x30
    Range* rangesEnd;       // +0x34
};
struct PartList { Part** begin; Part** end; };

struct OutRangeVec {
    Range* begin; Range* end; Range* cap;
    void __thiscall DoInsertValue(Range* pos, Range* v);
};
// vector<OutStream> insert helper (0x00736660) living inside OutMesh at +8
struct OutStreamVec {
    OutStream* begin; OutStream* end;
    void __thiscall Insert(OutStream* pos, OutStream* value);
};
// vector<Batch> push (0x004754e0) living inside OutMesh at +0x1c
struct OutBatchVec {
    Batch* begin; Batch* end;
    void __thiscall PushBack(Batch* value);
};
struct OutMesh {
    char pad0[8];
    OutStreamVec streams;   // +8
    char pad10[0xc];
    OutBatchVec batches;    // +0x1c
    char pad24[0xc];
    OutRangeVec ranges;     // +0x30
};

// arrays created by the two engine helpers (new[] with element-count cookie)
struct PartStat {
    int pad0;
    int v8, base8;      // value for stream type 8 and running base
    int v5, base5;      // type 5
    int v9, base9;      // type 9
};
struct PartStatArray {
    PartStat* data;
    PartStatArray(int n, char* alloc);                          // 0x00733400
    ~PartStatArray() { if (data && ((int*)data)[-1]) operator_delete__(data); }
};
struct IntVec {
    int* begin; int* end; int* cap;
    void __thiscall DoInsertValues(int* pos, int n, const int& v);    // 0x004cea40
};
struct BatchMap {           // 0x24 bytes per source batch
    int outIdx;             // +0   index of the output batch (-1 = none)
    int off;                // +4
    int off2;               // +8
    int count;              // +0xc
    IntVec remap;           // +0x10
    int pad1c, pad20;
    void ResizeRemap(int n)
    {
        int cur = remap.end - remap.begin;
        if (n > cur) {
            int zero = 0;
            remap.DoInsertValues(remap.end, n - cur, zero);
        } else {
            remap.end = remap.begin + n;
        }
    }
};
struct BatchMapArray {
    BatchMap* begin;
    BatchMap* end;
    BatchMapArray(int n, char* alloc);                          // 0x00737dc0
    ~BatchMapArray()
    {
        for (BatchMap* p = begin; p < end; p++)
            if (p->remap.begin && ((int*)p->remap.begin)[-1]) operator_delete__(p->remap.begin);
        if (begin && ((int*)begin)[-1]) operator_delete__(begin);
    }
};
struct StreamPair { int idx; int off; };

// ---- engine helpers ---------------------------------------------------------------
extern int __cdecl FindStream(OutMesh* out, int k0, int k1, int k2, int flags);      // 0x0071ddc0
extern int __cdecl FindBatch(OutMesh* out, IdVec* ids);                                // 0x00731fa0
extern void __cdecl Finalize(void* p);                                                 // 0x00720070
extern void __cdecl CopyPayload(Payload* src, Payload* dst, int off);                  // 0x0071fce0
extern void __cdecl FixupIndices(OutStream* s, int a, int b, int c);                   // 0x00732040
extern void __cdecl CopyBatchA(int srcCount, void* dst, int a, int b);                 // 0x0071ff50
extern void __cdecl CopyBatchB(void* src, void* dst, int a, int b);                    // 0x0071fe10

template <class T> static inline T imax(const T& a, const T& b) { return (a < b) ? b : a; }

// @ 0x007391f0
void __cdecl MeshBuildSort(PartList* parts, OutMesh* out)
{
    char allocTag;

    // total number of source streams
    int nParts = parts->end - parts->begin;
    int totalStreams = 0;
    for (int i = 0; i < nParts; i++)
        totalStreams += parts->begin[i]->streamsEnd - parts->begin[i]->streams;

    // pass 1: collect the union of stream keys and per-part type statistics
    PartStatArray stat(nParts, &allocTag);
    {
        int acc8 = 0, acc5 = 0, acc9 = 0;
        int nP = parts->end - parts->begin;
        PartStat* st = stat.data;
        for (int i = 0; i < nP; i++, st++) {
            st->v5 = 0;
            st->v8 = 0;
            Part* part = parts->begin[i];
            int nS = part->streamsEnd - part->streams;
            for (int k = 0; k < nS; k++) {
                SrcStream* src = &parts->begin[i]->streams[k];
                if (FindStream(out, src->k0, src->k1, src->k2, 0xe) < 0) {
                    // insertion point: first output stream greater than the new key
                    OutStreamVec* ov = &out->streams;
                    int pos = 0;
                    if ((int)((char*)ov->end - (char*)ov->begin) & 0xffffffe0) {
                        OutStream* e = ov->begin;
                        do {
                            if (e->k0 > src->k0) break;
                            if (e->k0 == src->k0) {
                                if (e->k1 > src->k1) break;
                                if (e->k1 == src->k1 && e->k2 > src->k2) break;
                            }
                            pos++;
                            e++;
                        } while (pos < ov->end - ov->begin);
                    }
                    OutStream tmp;
                    tmp.k0 = src->k0; tmp.k1 = src->k1; tmp.k2 = src->k2; tmp.k3 = src->type;
                    tmp.payload.count = 0;
                    tmp.payload.data = 0;
                    tmp.payload.fmt = 0;
                    tmp.payload.stride = 0;
                    tmp.payload.ref = 0;
                    ov->Insert(ov->begin + pos, &tmp);
                    if (tmp.payload.ref) tmp.payload.ref->Release();
                    ov->begin[pos].payload.fmt = (short)src->payload.fmt;
                }
                int type = src->type;
                if (type == 8) {
                    if (st->v8 == 0) st->v8 = src->payload.count;
                } else if (type == 5) {
                    if (st->v5 == 0) st->v5 = src->payload.count;
                } else if (type == 9 && st->v9 == 0) {
                    st->v9 = src->payload.count;
                }
            }
            st->base8 = acc8;  acc8 += st->v8;
            st->base5 = acc5;  acc5 += st->v5;
            st->base9 = acc9;  acc9 += st->v9;
        }
    }

    // pass 2: map every source stream to an output stream and its payload offset
    StreamPair* map;
    StreamPair* mapEnd;
    if (totalStreams) {
        map = (StreamPair*)SporeNew(totalStreams * 8, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    } else {
        map = 0;
    }
    mapEnd = map + totalStreams;
    {
        StreamPair* p = map;
        for (int n = totalStreams; n != 0; n--, p++) {
            if (p) { p->idx = 0; p->off = 0; }
        }
    }
    {
        int n = 0;
        int nP = parts->end - parts->begin;
        for (int i = 0; i < nP; i++) {
            int nS = parts->begin[i]->streamsEnd - parts->begin[i]->streams;
            for (int k = 0; k < nS; k++) {
                SrcStream* src = &parts->begin[i]->streams[k];
                int idx = FindStream(out, src->k0, src->k1, src->k2, 0xe);
                map[n].idx = idx;
                map[n].off = out->streams.begin[idx].payload.count;
                out->streams.begin[idx].payload.count += src->payload.count;
                n++;
            }
        }
    }

    // pass 3: merge index batches
    int totalBatches = 0;
    for (int i = 0; i < nParts; i++) {
        Part* p = parts->begin[i];
        totalBatches += (p->batchesEnd - p->batches);
    }
    BatchMapArray bmap(totalBatches, &allocTag);
    {
        int nP = parts->end - parts->begin;
        int streamBase = 0;
        int bi = 0;
        for (int i = 0; i < nP; i++) {
            int nB = parts->begin[i]->batchesEnd - parts->begin[i]->batches;
            for (int j = 0; j < nB; j++, bi++) {
                Batch* b = &parts->begin[i]->batches[j];
                IdVec ids;
                ids.begin = ids.end = ids.buf;
                ids.inlinePtr = ids.buf;
                ids.cap = ids.buf + 6;
                ids.DoAssign(b->ids.begin, b->ids.end, nP);
                int nIds = ids.end - ids.begin;
                for (int k = 0; k < nIds; k++)
                    ids.begin[k].lo = (short)map[ids.begin[k].lo + streamBase].idx;
                int ib = FindBatch(out, &ids);
                if (ib < 0) {
                    ib = out->batches.end - out->batches.begin;
                    {
                        Batch tmp;
                        out->batches.PushBack(&tmp);
                    }
                    Batch* nb = out->batches.end - 1;
                    nb->count = 0;
                    IdVec* dst = &nb->ids;
                    if (dst != &ids) {
                        dst->end = dst->begin;
                        dst->DoAssign(ids.begin, ids.end, nP);
                    }
                    nb->verts.Resize(ids.end - ids.begin);
                    int m = dst->end - dst->begin;
                    for (int k = 0; k < m; k++) dst->begin[k].hi = (short)k;
                }
                Batch* d = &out->batches.begin[ib];
                BatchMap* bm = &bmap.begin[bi];
                bm->outIdx = ib;
                bm->count = d->count;
                d->count += b->count;
                bm->ResizeRemap(b->ids.end - b->ids.begin);
                int nI = b->ids.end - b->ids.begin;
                for (int k = 0; k < nI; k++)
                    bm->remap.begin[k] = map[b->ids.begin[k].lo + streamBase].off;
                bm->off = d->base;
                d->base += b->base;
                bm->off2 = bm->count;
            }
            streamBase += parts->begin[i]->streamsEnd - parts->begin[i]->streams;
        }
    }

    // pass 4: finalise streams and batches
    {
        int nS = out->streams.end - out->streams.begin;
        for (int i = 0; i < nS; i++) Finalize(&out->streams.begin[i].payload);
        int nB = out->batches.end - out->batches.begin;
        for (int i = 0; i < nB; i++) {
            Batch* b = &out->batches.begin[i];
            b->fmt = (b->count & 0xffff0000) ? 4 : 2;
            Finalize(b);
            int nI = b->ids.end - b->ids.begin;
            for (int k = 0; k < nI; k++) {
                VertEntry* entry = b->verts.begin + b->ids.begin[k].hi;
                entry->count = b->count;
                entry->fmt = (out->streams.begin[b->ids.begin[k].lo].payload.count & 0xffff0000) ? 4 : 2;
                Finalize(b->verts.begin + b->ids.begin[k].hi);
            }
        }
    }

    // pass 5: copy stream payloads and fix up vertex entries
    {
        int nP = parts->end - parts->begin;
        int n = 0;
        PartStat* st = stat.data;
        for (int i = 0; i < nP; i++, st++) {
            int nS = parts->begin[i]->streamsEnd - parts->begin[i]->streams;
            int streamBase = n;
            for (int k = 0; k < nS; k++, n++) {
                Payload* src = &parts->begin[i]->streams[k].payload;
                if (map[n].idx < 0) continue;
                OutStream* dst = &out->streams.begin[map[n].idx];
                CopyPayload(src, &dst->payload, map[n].off);
                if (st->base5 > 0 && dst->k0 == 9) {
                    FixupIndices(dst, st->base5 * 3, map[n].off, src->count + map[n].off);
                } else if (dst->k2 == 0x10) {
                    int first = map[n].off;
                    int last = src->count + first;
                    for (int v = first; v < last; v++) {
                        char* vert = dst->payload.data + dst->payload.stride * v;
                        *(int*)(vert + 8) += st->base8;
                        *(int*)(vert + 0x10) += st->base5;
                        *(int*)(vert + 0x18) += st->base9;
                        if (*(int*)(vert + 4) == 0) *(int*)(vert + 4) = st->v8;
                        if (*(int*)(vert + 0xc) == 0) *(int*)(vert + 0xc) = st->v5;
                        if (*(int*)(vert + 0x14) == 0) *(int*)(vert + 0x14) = st->v9;
                    }
                }
            }
            (void)streamBase;
        }
    }

    // pass 6: copy batch data
    {
        int nP = parts->end - parts->begin;
        int bi = 0;
        for (int i = 0; i < nP; i++) {
            int nB = parts->begin[i]->batchesEnd - parts->begin[i]->batches;
            for (int j = 0; j < nB; j++, bi++) {
                Batch* sb = &parts->begin[i]->batches[j];
                BatchMap* bm = &bmap.begin[bi];
                if (bm->outIdx < 0) continue;
                Batch* db = &out->batches.begin[bm->outIdx];
                if (sb->kind == 0) CopyBatchA(sb->count, db, bm->off, bm->off2);
                else CopyBatchB(sb, db, bm->off, bm->off2);
                int nI = sb->ids.end - sb->ids.begin;
                if (sb->verts.begin == sb->verts.end) {
                    for (int k = 0; k < nI; k++)
                        CopyBatchA(sb->count, db->verts.begin + db->ids.begin[k].hi,
                                   bm->count, bm->remap.begin[k]);
                } else {
                    for (int k = 0; k < nI; k++)
                        CopyBatchB(sb->verts.begin + sb->ids.begin[k].hi,
                                   db->verts.begin + db->ids.begin[k].hi,
                                   bm->count, bm->remap.begin[k]);
                }
            }
        }
    }

    // pass 7: rebuild the range table
    {
        int nP = parts->end - parts->begin;
        int batchBase = 0;
        int indexBase = 0;
        PartStat* st = stat.data;
        for (int i = 0; i < nP; i++, st++) {
            Part* part = parts->begin[i];
            int nR = part->rangesEnd - part->ranges;
            int maxIdx = -1;
            for (int r = 0; r < nR; r++) {
                Range* src = &parts->begin[i]->ranges[r];
                Range tmp;
                tmp.a = src->a;
                tmp.e = src->e;
                BatchMap* bm = &bmap.begin[src->b + batchBase];
                if (bm->outIdx >= 0) {
                    tmp.b = bm->outIdx;
                    tmp.c = src->c + bm->off;
                    tmp.d = src->d + bm->off;
                    maxIdx = imax(maxIdx, src->e);
                    tmp.e = src->e + indexBase;
                    OutRangeVec* rv = &out->ranges;
                    if (rv->end < rv->cap) {
                        Range* p = rv->end++;
                        if (p) *p = tmp;
                    } else {
                        rv->DoInsertValue(rv->end, &tmp);
                    }
                }
            }
            batchBase += parts->begin[i]->batchesEnd - parts->begin[i]->batches;
            if (st->v8 == 0) indexBase += maxIdx + 1;
            else indexBase += st->v8;
        }
    }
}
