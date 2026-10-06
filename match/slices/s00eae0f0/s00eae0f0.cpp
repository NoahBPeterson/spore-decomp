// Slice s00eae0f0 (bfs3 slice 21) -- SP::Audio city-music + EASTL vector instances.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- vector helpers
// Three-pointer vector (begin/end/capacity) of 4-byte elements, EASTL layout.
static int* VecGrowN(int* v, int* pos, unsigned n, int val)
{
    int* begin = (int*)v[0];
    int* end = (int*)v[1];
    unsigned cap = (unsigned)(v[2] - (int)end) >> 2;
    if (cap < n) {
        unsigned oldLen = (unsigned)(end - begin);
        unsigned newCap = oldLen * 2;
        if (oldLen == 0)
            newCap = 1;
        unsigned want = oldLen + n;
        if (newCap < want)
            newCap = want;
        int* dst = newCap ? new int[newCap] : 0;
        int* p = begin;
        int* out = dst;
        while (p != pos)
            *out++ = *p++;
        int* fillEnd = out + n;
        int* q = out;
        while (q != fillEnd)
            *q++ = val;
        while (p != end)
            *out++ = *p++;
        delete[] begin;
        v[0] = (int)dst;
        v[1] = (int)out;
        v[2] = (int)(dst + newCap);
        return out;
    }
    if (n != 0) {
        unsigned tail = (unsigned)(end - pos);
        if (n < tail) {
            unsigned cnt = (unsigned)(end - (pos + n));
            int* d = end;
            int* s = end - n;
            while (cnt--)
                *--d = *--s;
            v[1] = (int)(end + n);
            int* s2 = pos;
            while (s2 != pos + n)
                *s2++ = val;
            return pos;
        } else {
            unsigned copyFirst = tail;
            int* w = end;
            for (unsigned i = 0; i < n - tail; ++i)
                *w++ = val;
            v[1] = (int)w;
            int* s = pos;
            int* d = end;
            while (copyFirst--)
                *d++ = *s++;
            v[1] = (int)d;
            int* s2 = pos;
            while (s2 != pos + n)
                *s2++ = val;
            return pos;
        }
    }
    return pos;
}

// 0x00eae430  vector<int>::insert(pos, val)  (slot 0x11e0744 thunk)
void FUN_00eae430(int* v, int* pos, int* val)
{
    int* end = (int*)v[1];
    if (end != (int*)v[2]) {
        if (pos <= val && val < end)
            val = (int*)((char*)val + 4);
        if (end != 0)
            *end = end[-1];
        int* p = pos;
        int* e = (int*)v[1];
        unsigned n = (unsigned)((e - 1) - pos) + 1;
        int* q = e - n;
        for (unsigned i = 0; i < n; ++i)
            q[i] = p[i];
        *pos = *val;
        v[1] = v[1] + 4;
        return;
    }
    int* begin = (int*)v[0];
    int* end2 = (int*)v[1];
    int oldLen = (int)(end2 - begin);
    int newCap = oldLen ? oldLen * 2 : 1;
    int* dst = newCap ? new int[newCap] : 0;
    int before = (int)(pos - begin);
    for (int i = 0; i < before; ++i)
        dst[i] = begin[i];
    dst[before] = *val;
    for (int i = before; i < oldLen; ++i)
        dst[i + 1] = begin[i];
    if (v[0])
        delete[] begin;
    v[0] = (int)dst;
    v[1] = (int)(dst + oldLen + 1);
    v[2] = (int)(dst + newCap);
}

// 0x00eae540  eastl::vector<float,SP_STL_Sound>::operator=
int* FUN_00eae540(int* v, int* other)
{
    if (other == v)
        return v;
    float* src = (float*)other[0];
    float* dst = (float*)v[0];
    float* srcEnd = (float*)other[1];
    unsigned n = (unsigned)(srcEnd - src);
    unsigned cap = (unsigned)((float*)v[2] - dst);
    if (cap < n) {
        float* nw = new float[n];
        float* p = src; float* q = nw;
        while (p != srcEnd) *q++ = *p++;
        if (v[0]) delete[] (float*)v[0];
        v[0] = (int)nw; v[1] = (int)(nw + n); v[2] = (int)(nw + n);
        return v;
    }
    unsigned have = (unsigned)((float*)v[1] - dst);
    if (have < n) {
        float* p = src; float* q = dst;
        while (q != (float*)v[1]) *q++ = *p++;
        float* q2 = (float*)v[1]; float* p2 = (float*)other[0] + have;
        while (p2 != srcEnd) *q2++ = *p2++;
        v[1] = (int)((float*)v[0] + n);
        return v;
    }
    float* p = src; float* q = dst; float* e = (float*)other[1];
    while (p != e) *q++ = *p++;
    v[1] = (int)((float*)v[0] + n);
    return v;
}

// 0x00eaeef0  eastl::vector<float,SP_STL_Sound>::assign(first,last)
void FUN_00eaeef0(int* v, float* first, float* last)
{
    float* begin = (float*)v[0];
    unsigned n = (unsigned)(last - first);
    if ((unsigned)((float*)v[2] - begin) < n) {
        float* nw = new float[n];
        float* p = first; float* q = nw;
        while (p != last) *q++ = *p++;
        if (v[0]) delete[] (float*)v[0];
        v[0] = (int)nw; v[1] = (int)(nw + n); v[2] = (int)(nw + n);
        return;
    }
    unsigned have = (unsigned)((float*)v[1] - begin);
    if (n <= have) {
        float* p = first; float* q = begin;
        while (p != last) *q++ = *p++;
        v[1] = (int)(begin + n);
        return;
    }
    float* mid = first + have;
    float* p = first; float* q = begin;
    while (p != mid) *q++ = *p++;
    float* q2 = (float*)v[1];
    while (mid != last) *q2++ = *mid++;
    v[1] = (int)q2;
}

// 0x00eaeb60  vector<int>::insert_n(pos, n, val)
void FUN_00eaeb60(int* v, int* pos, unsigned n, int* val)
{
    int* end = (int*)v[1];
    unsigned have = (unsigned)(v[2] - (int)end) >> 2;
    if (have < n) {
        VecGrowN(v, pos, n, *val);
        return;
    }
    if (n == 0)
        return;
    int value = *val;
    unsigned tail = (unsigned)(end - pos);
    if (n < tail) {
        int* d = end;
        int* s = end - n;
        while (s != end) *--d = *--s;
        v[1] = v[1] + n * 4;
        int* w = pos;
        unsigned k = n;
        while (k--) *w++ = value;
        return;
    }
    unsigned extra = n - tail;
    int* w = end;
    for (unsigned i = 0; i < extra; ++i)
        *w++ = value;
    v[1] += extra * 4;
    int* s = pos;
    int* d = end;
    while (s != end) *d++ = *s++;
    v[1] += tail * 4;
    int* w2 = pos;
    unsigned k = n;
    while (k--) *w2++ = value;
}

// 0x00eaed40  vector<float,SP_STL_Sound>::insert_n(pos, n, val)
void FUN_00eaed40(int* v, int* pos, unsigned n, float* val)
{
    int* end = (int*)v[1];
    unsigned have = (unsigned)(v[2] - (int)end) >> 2;
    if (have < n) {
        int* begin = (int*)v[0];
        unsigned oldLen = (unsigned)(end - begin) >> 2;
        unsigned newCap = oldLen * 2;
        if (oldLen == 0)
            newCap = 1;
        if (newCap <= oldLen + n)
            newCap = oldLen + n;
        float* dst = newCap ? new float[newCap] : 0;
        unsigned before = (unsigned)(pos - begin) >> 2;
        float* out = dst;
        float* p = (float*)begin;
        for (unsigned i = 0; i < before; ++i) *out++ = *p++;
        float value = *val;
        for (unsigned i = 0; i < n; ++i) *out++ = value;
        while (p != (float*)end) *out++ = *p++;
        if (v[0]) delete[] (float*)v[0];
        v[0] = (int)dst;
        v[1] = (int)out;
        v[2] = (int)(dst + newCap);
        return;
    }
    if (n == 0)
        return;
    float value = *val;
    unsigned tail = (unsigned)(end - pos);
    if (n < tail) {
        int* d = end;
        int* s = end - n;
        while (s != end) *--d = *--s;
        v[1] = v[1] + n * 4;
        float* w = (float*)pos;
        unsigned k = n;
        while (k--) *w++ = value;
        return;
    }
    unsigned extra = n - tail;
    float* w = (float*)end;
    for (unsigned i = 0; i < extra; ++i) *w++ = value;
    v[1] += extra * 4;
    float* s = (float*)pos;
    float* d = (float*)end;
    while (s != (float*)end) *d++ = *s++;
    v[1] += tail * 4;
    float* w2 = (float*)pos;
    unsigned k = n;
    while (k--) *w2++ = value;
}

// ---------------------------------------------------------------- audio system
struct AT {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(int);
    virtual void v3c(int, float); virtual void v40(int, int); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58();
};
AT* __cdecl GetSystemAT();   // 0x00a206f0

static void NoteEvent(int which, int val, int tagB)
{
    AT* at = GetSystemAT();
    if (at) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, which);
        float f = (float)val;
        if (val < 0)
            f += 4294967296.0f;
        at->v3c(0x34753aa, f);
        at->v58();
    }
    at = GetSystemAT();
    if (at) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, tagB);
        at->v3c(0x34753aa, (float)val);
        at->v58();
    }
}

// ---------------------------------------------------------------- cPlayerCityMusic
struct cPlayerCityMusic {
    char   pad0[0x110];
    unsigned mNoteStateIdx;   // +0x110
    float* mNoteStatesBegin;  // +0x114
    float* mNoteStatesEnd;    // +0x118
    char   pad11c[0x128 - 0x11c];
    float* mVec128B;          // +0x128
    float* mVec128E;          // +0x12c
    char   pad130[0x13c - 0x130];
    float* mVec13cB;          // +0x13c
    float* mVec13cE;          // +0x140
    char   pad144[0x150 - 0x144];
    float  mDownbeat;         // +0x150
    char   pad154[0x1b8 - 0x154];
    int*   mList1b8;          // +0x1b8
    char   pad1bc[0x1cc - 0x1bc];
    float* mNoteDegB;         // +0x1cc
    float* mNoteDegE;         // +0x1d0
    char   pad1d4[0x1e0 - 0x1d4];
    float* mVec1e0B;          // +0x1e0
    float* mVec1e0E;          // +0x1e4
    void DeselectAmbience(float value, unsigned* idx, float* out);
    void RemoveNote(unsigned idx);
};

// 0x00eae0f0  SP::Audio::cPlayerCityMusic::DeselectAmbience
void cPlayerCityMusic::DeselectAmbience(float value, unsigned* idx, float* out)
{
    unsigned count = (unsigned)(this->mNoteStatesEnd - this->mNoteStatesBegin);
    if (this->mNoteStateIdx < count) {
        *idx = 0;
        if (count != 0) {
            do {
                unsigned i = *idx;
                if ((unsigned)this->mNoteStatesBegin[i] == 0) {
                    this->mNoteStatesBegin[i] = value;
                    NoteEvent(0x330df985, (int)value, 0x3fbc0a67);
                    this->mNoteStateIdx++;
                    break;
                }
                *idx = i + 1;
            } while (*idx < count);
        }
    } else {
        int* node = this->mList1b8;
        *out = *(float*)(node[2]);
        *(int*)node[1] = node[0];
        *(int*)(node[0] + 4) = node[1];
        delete node;
        *idx = 0;
        if (count != 0) {
            do {
                unsigned i = *idx;
                if (*out == this->mNoteStatesBegin[i]) {
                    this->mNoteStatesBegin[i] = value;
                    NoteEvent(0xaa1b3b8d, (int)value, 0x330df985);
                    break;
                }
                *idx = i + 1;
            } while (*idx < count);
        }
    }
    float* n = new float[3];
    if (n + 2 != 0)
        n[2] = value;
    *(int*)n = (int)&this->mNoteStatesBegin;
    *(int*)(n + 1) = (int)this->mNoteStatesEnd;
    this->mNoteStatesEnd = n;
}

// 0x00eae610  SP::Audio::cPlayerCityMusic::RemoveNote
void cPlayerCityMusic::RemoveNote(unsigned idx)
{
    unsigned off = idx * 4;
    this->mDownbeat = this->mDownbeat - *(float*)((char*)this + 0x1cc + off);
    *(int*)((char*)this + 0x1d0) -= 4;
    *(int*)((char*)this + 0x1e4) -= 4;
    *(int*)((char*)this + 0x140) -= 4;
    *(int*)((char*)this + 0x12c) -= 4;

    unsigned count = (unsigned)(*(int*)((char*)this + 0x1d0) -
                                *(int*)((char*)this + 0x1cc)) >> 2;
    for (; idx < count; ++idx) {
        NoteEvent(0xe7b72656, (int)idx, 0xfe31e5d9);
        NoteEvent(0xc309bcc9, (int)*(float*)(*(int*)((char*)this + 0x1e0) + idx * 4), 0);
    }
    NoteEvent(0xead8248, (int)count, 0);
}

// ---------------------------------------------------------------- serialization readers
struct IStream;
struct IReader {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual IStream* v20();
};
struct IStream {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual IStream* s18();
};
void __cdecl ReadInt32(void* stream, int* out, int a, int b);   // 0x0093a780
void __cdecl FUN_00eade60(int a);
void __cdecl FUN_00eadf40(int* at, int* val);
void __cdecl FUN_00ea9440(int* at, int* val);
int* __cdecl FUN_00b968b0(unsigned n, int* src, int end);

// 0x00eae8a0  SP::ReadSTLSequenceT<eastl::fixed_vector<float,3,0>>
void FUN_00eae8a0(IReader* reader, int* v)
{
    int* begin = (int*)v[0];
    int* end = (int*)v[1];
    v[1] = (int)end - ((int)end - (int)begin);
    int count = 0;
    IStream* s = reader->v20()->s18();
    ReadInt32(s, &count, 1, 0);
    unsigned n = (unsigned)count;
    if ((unsigned)(v[2] - v[0]) >> 2 < n) {
        delete[] (int*)v[0];
        v[0] = 0;
        v[1] = 0;
        v[2] = v[0] + n * 4;
    }
    for (unsigned i = 0; i < n; ++i) {
        IStream* s2 = reader->v20()->s18();
        int val = 0;
        ReadInt32(s2, &val, 1, 0);
        if ((int*)v[1] < (int*)v[2])
            *(int*)v[1] = val, v[1] += 4;
        else
            FUN_00eadf40((int*)v[1], &val);
    }
    reader->v1c();
}

// 0x00eae9b0
void FUN_00eae9b0(IReader* reader, int* v)
{
    int* begin = (int*)v[0];
    int* end = (int*)v[1];
    v[1] = (int)end - ((int)end - (int)begin);
    int count = 0;
    IStream* s = reader->v20()->s18();
    ReadInt32(s, &count, 1, 0);
    FUN_00eade60(count);
    for (unsigned i = 0; i < (unsigned)count; ++i) {
        IStream* s2 = reader->v20()->s18();
        int val = 0;
        ReadInt32(s2, &val, 1, 0);
        if ((int*)v[1] < (int*)v[2])
            *(int*)v[1] = val, v[1] += 4;
        else
            FUN_00ea9440((int*)v[1], &val);
    }
    reader->v1c();
}

// 0x00eaea80  SP::ReadSTLSequenceT<eastl::vector<float,SP_STL_Sound>>
void FUN_00eaea80(IReader* reader, int* v)
{
    int* begin = (int*)v[0];
    int* end = (int*)v[1];
    v[1] = (int)end - ((int)end - (int)begin);
    int count = 0;
    IStream* s = reader->v20()->s18();
    ReadInt32(s, &count, 1, 0);
    FUN_00eade60(count);
    for (unsigned i = 0; i < (unsigned)count; ++i) {
        IStream* s2 = reader->v20()->s18();
        float val = 0.0f;
        ReadInt32(s2, (int*)&val, 1, 0);
        if ((float*)v[1] < (float*)v[2])
            *(float*)v[1] = val, v[1] += 4;
        else
            FUN_00eae430((int*)v, (int*)v[1], (int*)&val);
    }
    reader->v1c();
}
