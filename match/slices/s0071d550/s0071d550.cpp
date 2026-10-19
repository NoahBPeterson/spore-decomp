// Slice s0071d550: SP mesh model helpers.  A couple of tiny accessors plus the
// stream-lookup helpers and the two big UV-sphere / disc mesh emitters that drive
// a polymorphic RenderWare-style stream writer (vtable slots 3,4,6,7,8,14,19,...).
// Optimized module: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sin, cos, fabs)

// ---------------------------------------------------------------------------
// Layouts inferred from this slice and from s0046f2a0 (DumpZPR).
// ---------------------------------------------------------------------------

struct Stream {                 // vertex/index stream
    int      count;             // +0x00
    char*    data;              // +0x04
    uint16_t format;            // +0x08
    uint16_t stride;            // +0x0A
    int      unk0c;             // +0x0C
};

struct ModelStreamEntry {       // 0x20 bytes
    int    semantic;            // +0x00
    int    usageIdx;            // +0x04
    int    number;              // +0x08
    int    type;                // +0x0C
    Stream stream;              // +0x10
};

struct StreamRef {              // 4 bytes
    short stream;               // +0x00 index into the model's stream array
    short remap;                // +0x02
};

struct Mesh {                   // 0x8C bytes
    Stream      mIndices;       // +0x00
    uint32_t    pad10;          // +0x10
    StreamRef*  mStreamMap;     // +0x14
    StreamRef*  mStreamMapEnd;  // +0x18
    uint32_t    pad1c[28];      // +0x1C .. +0x8C
};

struct Sec14 {                  // 0x14 bytes
    int type;                   // +0x00
    int idx;                    // +0x04
    int f8;                     // +0x08
    int fC;                     // +0x0C
    int f10;                    // +0x10
};

struct Model {
    uint32_t          pad00[2];       // +0x00
    ModelStreamEntry* mStreamsBegin;  // +0x08
    ModelStreamEntry* mStreamsEnd;    // +0x0C
    uint32_t          pad10[3];       // +0x10 .. +0x1C
    Mesh*             mMeshesBegin;   // +0x1C
    Mesh*             mMeshesEnd;     // +0x20
    uint32_t          pad24[3];       // +0x24 .. +0x30
    Sec14*            mSecBegin;      // +0x30
    Sec14*            mSecEnd;        // +0x34

    int sumSection();                 // 0x0071dcc0
};

// A generic object holding a base pointer at +0x1c and arrays at +0x30 etc.
struct Obj13 {
    char pad_00[0x1c];
    char* mBase;        // +0x1c
    bool func_dc90(int idx);
    int  findShort(int idx, int key);
};

struct Vec20 {              // 0x20-byte entry
    uint32_t mA;            // +0x00
    uint32_t mB;            // +0x04
    uint32_t mC;            // +0x08
    uint32_t mKey;          // +0x0c
    uint32_t mVal;          // +0x10
    uint32_t mD, mE, mF;    // +0x14..
};
struct VecDescr {
    char pad_00[8];
    char* mpBegin;          // +0x08
    char* mpEnd;            // +0x0c
    char* mpCapacity;       // +0x10
};

struct Vector3 { float x, y, z; };

// The polymorphic stream writer seen in the emitters (RenderWare-style sink).
// Only the used slots are named; they are addressed by vtable byte offset.
struct Rend {
    virtual void v0() = 0;                          // +0x00
    virtual void v1() = 0;                          // +0x04
    virtual void v2() = 0;                          // +0x08
    virtual void v3() = 0;                          // +0x0C
    virtual void v4() = 0;                          // +0x10
    virtual void v5() = 0;                          // +0x14
    virtual void v6(Vector3* p) = 0;                // +0x18
    virtual void v7(Vector3* p) = 0;                // +0x1C
    virtual void v8(Vector3* p, int n) = 0;         // +0x20
    virtual void v9() = 0;                          // +0x24
    virtual void v10() = 0;                         // +0x28
    virtual void v11() = 0;                         // +0x2C
    virtual void v12() = 0;                         // +0x30
    virtual void v13() = 0;                         // +0x34
    virtual void v14(const void* p, int n) = 0;     // +0x38
    virtual void v15() = 0;                         // +0x3C
    virtual void v16() = 0;                         // +0x40
    virtual void v17() = 0;                         // +0x44
    virtual void v18() = 0;                         // +0x48
    virtual void v19(int n) = 0;                    // +0x4C
    virtual void v20(int n) = 0;                    // +0x50
    virtual void v21(int n) = 0;                    // +0x54
    virtual void v22(int n) = 0;                    // +0x58
    virtual void v23() = 0;                         // +0x5C
    virtual void v24() = 0;                         // +0x60
    virtual void v25(int a, int b) = 0;             // +0x64
    virtual void v26() = 0;                         // +0x68
    virtual void v27() = 0;                         // +0x6C
    virtual void v28() = 0;                         // +0x70
    virtual void v29() = 0;                         // +0x74
    virtual void v30() = 0;                         // +0x78
    virtual void v31() = 0;                         // +0x7C
    virtual void v32(int n) = 0;                    // +0x80
    virtual void v33() = 0;                         // +0x84
    virtual void v34() = 0;                         // +0x88
    virtual void v35(int a, int b, float f) = 0;    // +0x8C
};

// EA::IO stream sinks (0x0093aa70 / 0x0093a9d0)
bool __cdecl WriteUint32(Rend* s, const uint32_t* p, uint32_t n, int flags);   // 0x0093aa70
bool __cdecl WriteUint16(Rend* s, const uint16_t* p, uint32_t n, int flags);   // 0x0093a9d0

// character tables used by Model::sumSection
extern const int8_t g_secTabA[];   // 0x0140cf84
extern const int8_t g_secTabB[];   // 0x0140cf90

// float constants read out of the module's constant pool
extern const float g_angleStep;    // 0x0162a8e0  sphere row angle step scale
extern const float g_subdivK;      // 0x01471064  segment falloff scale
extern const float g_discStep;     // 0x015366f0  disc row angle step scale
extern Vector3 g_axis;             // 0x01536718  fixed normal for the sphere cap

struct IntVec {                    // eastl-style vector of ints (8 bytes)
    int* mpBegin;                  // +0x00
    int* mpEnd;                    // +0x04
};

// @ 0x0071dc90
bool Obj13::func_dc90(int idx)
{
    int* p = (int*)(mBase + idx * 0x8c + 0x44);
    return p[0] != p[1];
}

// @ 0x0071dd80
int Vec20_find(const VecDescr* v, uint32_t key)
{
    int n = (int)((v->mpEnd - v->mpBegin) >> 5);
    const char* begin = v->mpBegin;
    for (int i = 0; i < n; ++i)
        if (*(const uint32_t*)(begin + i * 0x20 + 0xc) == key)
            return *(const int*)(begin + i * 0x20 + 0x10);
    return 0;
}

// @ 0x0071e040
int Obj13_findShort(Obj13* self, int idx, int key)
{
    int* p = (int*)(self->mBase + idx * 0x8c + 0x14);
    const short* q = (const short*)p[0];
    int n = (int)((p[1] - (int)q) >> 2);
    const short* ps = q;
    for (int i = 0; i < n; ++i, ps += 2)
        if (*ps == key)
            return i;
    return -1;
}

// ---------------------------------------------------------------------------
// Large mesh emitters
// ---------------------------------------------------------------------------

// Sphere: rings x segments, with a normal, a UV pair and per-segment blend values;
// finishes with two triangle-strip index runs and one quad strip.
// @ 0x0071d550
void __cdecl EmitSphere(Rend* w, float r, float zscale, int count, int seg, int subdiv, char flag)
{
    w->v3();
    if (flag == 0)
        w->v19(0);
    if (seg != 0)
        w->v32(seg + 1);

    Vector3 p;
    Vector3 n;
    Vector3 uv;
    float angle = 0.0f;
    float invCount = 1.0f / (float)count;
    int vert = 0;
    int rowIdx = 0;
    if (count > 0) {
        float invLast = (float)(count - 1);
        do {
            float cosA = (float)cos(angle);
            float sinA = (float)sin(angle);
            float rowN = (float)rowIdx * invCount;
            int col = 0;
            do {
                float colN = (float)col / invLast;
                p.x = cosA * r;
                p.y = sinA * r;
                p.z = ((colN * 2.0f - 1.0f) * zscale) * r;
                w->v6(&p);
                n.x = cosA;
                n.y = sinA;
                n.z = 0.0f;
                w->v7(&n);
                uv.x = rowN;
                uv.y = colN;
                w->v8(&uv, 0);

                float base = (float)(seg - 1) * colN;
                float denom = (float)subdiv * g_subdivK;
                for (int k = 0; k < seg; ++k) {
                    double f = 1.0 - fabs((double)base - (double)k) / (double)denom;
                    if (f > 0.0)
                        w->v35(k + 1, vert, (float)f);
                }
                ++vert;
                ++col;
            } while (col < count);
            angle = g_angleStep * invCount + angle;
            ++rowIdx;
        } while (rowIdx < count);
    }

    Vector3 neg;
    w->v7(&g_axis);
    neg.x = -g_axis.x;
    neg.y = -g_axis.y;
    neg.z = -g_axis.z;
    w->v7(&neg);
    if (flag)
        w->v19(0);
    w->v20(9);
    w->v22(vert);

    if (count > 0) {
        int e = count - 1;
        int m = count;
        do {
            w->v25(5, e);
            e += count;
        } while (--m);
    }
    w->v31();

    if (flag)
        w->v19(1);
    w->v20(9);
    w->v22(vert + 1);
    if (count > 0) {
        int e = (count - 1) * count;
        int m = count;
        do {
            w->v25(5, e);
            e -= count;
        } while (--m);
    }
    w->v31();

    if (count > 0) {
        int rowBase = 0;
        int fourI = 0;
        int i = 0;
        do {
            if (flag)
                w->v19(fourI / count + 2);
            int a = (i == count - 1) ? 0 : (rowBase + count);
            for (int j = 0; j < count - 1; ++j) {
                int idx = a + 1 + j;
                w->v20(9);
                w->v25(7, idx - 1);
                w->v25(7, idx);
                w->v25(7, (rowBase - a) + idx);
                w->v25(7, rowBase + j);
                w->v31();
            }
            ++i;
            rowBase += count;
            fourI += 4;
        } while (i < count);
    }

    w->v4();
}

// Disc: rings x cols with a fixed normal, then an optional cap fan and a quad strip.
// @ 0x0071d960
void __cdecl EmitDisc(Rend* w, float a, float b, char flag, int count)
{
    w->v3();
    w->v19(0);

    float nb = -b;
    float nz = -(a / nb);
    float angle = 0.0f;
    int vert = 0;
    if (count > 0) {
        float invLast = (float)(count - 1);
        float fcount = (float)count;
        vert = count * count;
        int rows = count;
        do {
            float cosA = (float)cos(angle);
            float sinA = (float)sin(angle);
            int col = 0;
            do {
                Vector3 p;
                Vector3 n;
                float colN = (float)col / invLast;
                float X = colN * a;
                p.x = cosA * X;
                p.y = sinA * X;
                p.z = colN * nb;
                w->v6(&p);
                n.x = cosA;
                n.y = sinA;
                n.z = nz;
                w->v7(&n);
                ++col;
            } while (col < count);
            angle = (g_discStep * 2.0f) / fcount + angle;
        } while (--rows);
    }

    if (flag) {
        Vector3 n;
        n.x = 0.0f;
        n.y = 0.0f;
        n.z = -1.0f;
        w->v7(&n);
        w->v20(9);
        w->v22(vert);
        if (count > 0) {
            int e = vert - 1;
            int m = count;
            do {
                w->v21(e);
                e -= count;
            } while (--m);
        }
        w->v31();
    }

    if (count > 0) {
        int rowStart = 1;
        int i = 0;
        do {
            int last = count - 1;
            int aa = (i == last) ? 0 : (rowStart + last);
            if (last > 0) {
                int rb = aa;
                int idx = rowStart;
                int j = last;
                do {
                    w->v20(9);
                    w->v25(3, idx - 1);
                    w->v25(3, idx);
                    w->v25(3, (aa - rowStart + 1) + idx);
                    w->v25(3, rb);
                    w->v31();
                    ++idx;
                    ++rb;
                } while (--j);
            }
            ++i;
            rowStart += count;
        } while (i < count);
    }

    w->v4();
}

// ---------------------------------------------------------------------------
// Stream serialization / lookup helpers
// ---------------------------------------------------------------------------

// @ 0x0071dbf0
bool __cdecl WriteStream(Rend* w, const Stream* s)
{
    uint32_t count = s->count;
    WriteUint32(w, &count, 1, 0);
    uint16_t format = s->format;
    WriteUint16(w, &format, 1, 0);
    if (s->data) {
        if (s->format == s->stride) {
            w->v14(s->data, s->format * s->count);
            return true;
        }
        for (int i = 0; i < s->count; ++i)
            w->v14(s->data + s->stride * i, s->format);
    }
    return true;
}

// @ 0x0071dcc0
int Model::sumSection()
{
    int total = 0;
    int numMeshes = (int)(mMeshesEnd - mMeshesBegin);
    if (numMeshes > 0) {
        int meshIdx = 0;
        do {
            int numSec = (int)(mSecEnd - mSecBegin);
            if (numSec > 0) {
                Sec14* p = mSecBegin;
                int j = numSec;
                do {
                    if (p->idx == meshIdx) {
                        int t = p->type;
                        if (t < 1 || t > 9)
                            t = 0;
                        else if (t == 9)
                            t = 1;
                        else
                            t = ((int)g_secTabA[t] - p->f8 + p->fC) / (int)g_secTabB[t];
                        total += t;
                    }
                    ++p;
                } while (--j);
            }
            ++meshIdx;
        } while (meshIdx < numMeshes);
    }
    return total;
}

// @ 0x0071ddc0
int __cdecl FindStreamEntry(const Model* m, int semantic, int usageIdx, int number, int type)
{
    int n = (int)(m->mStreamsEnd - m->mStreamsBegin);
    if (n > 0) {
        const ModelStreamEntry* e = m->mStreamsBegin;
        int i = 0;
        do {
            if ((semantic == 0 || e->semantic == semantic) &&
                (usageIdx == -1 || e->usageIdx == usageIdx) &&
                (number == 0 || e->number == number)) {
                if (type == 0xe)
                    return i;
                if (e->type == type)
                    return i;
            }
            ++i;
            ++e;
        } while (i < n);
    }
    return -1;
}

// Returns the model's stream matching the filter, or the shared empty stream.
// @ 0x0071de40
Stream* __cdecl FindStream(const Model* m, int semantic, int usageIdx, int number, int type)
{
    int n = (int)(m->mStreamsEnd - m->mStreamsBegin);
    if (n > 0) {
        const ModelStreamEntry* e = m->mStreamsBegin;
        int i = 0;
        do {
            if ((semantic == 0 || e->semantic == semantic) &&
                (usageIdx < 0 || e->usageIdx == usageIdx) &&
                (number == 0 || e->number == number) &&
                (type == 0xe || e->type == type))
                return (Stream*)&e->stream;
            ++i;
            ++e;
        } while (i < n);
    }
    return (Stream*)0x162aa80;
}

// Greedy multi-stream selection: fills out[k] with the first unused stream index
// that matches filters k, or -1.  Returns whether all `count` outputs were filled.
// @ 0x0071ded0
bool __cdecl SelectStreams(const Model* m, int count, int* out, const int* semantics,
                           const int* usageIndex, const int* numbers, const int* types)
{
    int nStreams = (int)(m->mStreamsEnd - m->mStreamsBegin);
    int found = 0;
    if (count > 0) {
        int k = 0;
        do {
            bool matched = false;
            if (nStreams < 1) {
                out[k] = -1;
                ++k;
            } else {
                int i = 0;
                do {
                    const ModelStreamEntry* e = &m->mStreamsBegin[i];
                    if ((semantics == 0 || semantics[k] == 0 || e->semantic == semantics[k]) &&
                        (usageIndex == 0 || usageIndex[k] == -1 || e->usageIdx == usageIndex[k]) &&
                        (numbers == 0 || numbers[k] == 0 || e->number == numbers[k]) &&
                        (types == 0 || types[k] == 0xe || m->mStreamsBegin[k].type == types[k])) {
                        out[k] = i;
                        ++found;
                        ++k;
                        matched = true;
                        if (k == count)
                            break;
                    }
                    ++i;
                } while (i < nStreams);
                if (!matched) {
                    out[k] = -1;
                    ++k;
                }
            }
        } while (k < count);
    }
    return found == count;
}

// @ 0x0071e090
int __cdecl FindMeshStreamIndex(const Model* m, int meshIndex, int semantic, int usageIdx, int number)
{
    const Mesh* mesh = m->mMeshesBegin + meshIndex;
    const StreamRef* ref = mesh->mStreamMap;
    int n = (int)(mesh->mStreamMapEnd - ref);
    if (n > 0) {
        const ModelStreamEntry* streams = m->mStreamsBegin;
        int i = 0;
        do {
            const ModelStreamEntry* e = &streams[ref->stream];
            if ((semantic == 0 || e->semantic == semantic) &&
                (number == 0 || e->number == number)) {
                if (usageIdx == -1)
                    return i;
                if (e->usageIdx == usageIdx)
                    return i;
            }
            ++i;
            ++ref;
        } while (i < n);
    }
    return -1;
}

// Maps each requested (semantic, format, usage) onto the mesh's stream refs.
// @ 0x0071e110
bool __cdecl FindMeshStreams(const Model* m, int meshIndex, int count, const int* semantics,
                             const int* usageIndex, const int* formats, int* outIdx)
{
    const Mesh* mesh = m->mMeshesBegin + meshIndex;
    const StreamRef* ref = mesh->mStreamMap;
    int nRefs = (int)(mesh->mStreamMapEnd - ref);
    const ModelStreamEntry* streams = m->mStreamsBegin;
    int found = 0;
    if (count > 0) {
        int k = 0;
        do {
            bool matched = false;
            if (nRefs < 1) {
                outIdx[k] = -1;
                ++k;
            } else {
                int i = 0;
                do {
                    const ModelStreamEntry* e = &streams[ref[i].stream];
                    if ((semantics == 0 || semantics[k] == 0 || e->semantic == semantics[k]) &&
                        (formats == 0 || formats[k] == 0 || e->number == formats[k]) &&
                        (usageIndex == 0 || usageIndex[k] == -1 || e->usageIdx == usageIndex[k])) {
                        outIdx[k] = i;
                        ++found;
                        ++k;
                        matched = true;
                        if (k == count)
                            break;
                    }
                    ++i;
                } while (i < nRefs);
                if (!matched) {
                    outIdx[k] = -1;
                    ++k;
                }
            }
        } while (k < count);
    }
    return found == count;
}

// @ 0x0071e230
bool __cdecl MatchingIndices(const IntVec* v, int limit, const int* keys, int* out)
{
    int i = 0;
    int n = (int)(v->mpEnd - v->mpBegin);
    int count = 0;
    for (; i < n; ++i) {
        if (count >= limit)
            break;
        if ((short)v->mpBegin[i] == keys[count]) {
            if (out)
                out[count] = i;
            ++count;
        }
    }
    return count == limit;
}

// ---------------------------------------------------------------------------
// Not part of this slice's work list: kept as skeletons for the next agent.
// @ 0x0071e290
void Obj13_e290(void* self, void* a) { (void)self; (void)a; }
// @ 0x0071e320
void Obj13_e320(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
