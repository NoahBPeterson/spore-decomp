// Slice s007c9910 -- SP::cConfigManager option-list / eastl vector helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------- masked externs
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
void  __cdecl EA_Free(void*);        // 0x00f47380
void  __cdecl RegisterConfigScriptCommands(void*);   // 0x007c8530
void  __cdecl InsertAutoRef(void* dest, void* src);  // 0x007c8af0
void* __cdecl VecDoInsertValue(void);                // 0x011e0744
void* __cdecl VecAllocGrow(int n, void*, void*);     // 0x007c98b0
void  __cdecl VecDestroyRange16(void*, void*);       // 0x00b007f0
void* __cdecl VecCopyImpl(void*, void*, void*);      // 0x006782c0
void  __cdecl VecUninitCopy(void*, void*, void*, void*, void*); // 0x007c7d70
void  __cdecl VecDestroyRange(void*, void*);         // 0x007c8130
void* __cdecl VecCopyRange(void*, void*, void*);      // 0x007c7e10
void* __cdecl VecReserve(int n, void*, void*);       // 0x007c8210
void  __cdecl UIntVecPushSlow(void*, unsigned*);     // 0x004558a0
void  __cdecl UIntVecReserve(void*, unsigned);       // 0x004e0880

inline void* operator new(size_t size, const char* n, int f, unsigned d, const char* fi, int l)
{ return EA_New((unsigned)size, n, f, (int)d, fi, l); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

struct RC { virtual void AddRef(); virtual void Release(); };
struct AutoRef { uint32_t m0; uint32_t m4; RC* mRC; uint32_t mPad; };

// ---------------------------------------------------------------- vector stubs
struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void reserve(unsigned n);
    void push_back(uint32_t v) {
        if (mpEnd < mpCap) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            UIntVecPushSlow(this, &v);
        }
    }
};

struct AutoRefVec {
    AutoRef* mpBegin;
    AutoRef* mpEnd;
    AutoRef* mpCap;
    AutoRef  mInline[4];
    void DoAssignFromIterator(AutoRef* first, AutoRef* last);  // 0x007c9fa0
    void InsertOne(AutoRef* pos, AutoRef* value);              // 0x007c9dc0
};

struct Pair16 { uint64_t key; AutoRef val; };
struct PairVec {
    Pair16* mpBegin;
    Pair16* mpEnd;
    Pair16* mpCap;
    PairVec& operator=(const PairVec&);                        // 0x007ca060
};

struct Vec4 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    void InsertOne(uint32_t* pos, uint32_t* value);            // 0x007c99e0
    void InsertN(uint32_t* pos, int n, uint32_t* value);       // 0x007c9bc0
};

struct MapVec {                                                // 0x007ca8e0
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void Destroy();
};

struct cOption {
    uint32_t id; uint32_t def; uint32_t cur;
    uint8_t* resBegin; uint8_t* resEnd;
    char pad[0xac - 0x14];
};
struct cConfigManager {
    char pad00[0x64];
    cOption* mOptionsBegin;   // +0x64
    cOption* mOptionsEnd;     // +0x68
    char pad6c[0x80 - 0x6c];
    void* mStrings;           // +0x80
    void* mStringsEnd;        // +0x84

    void GetOptionIDs(UIntVec* out);          // 0x007ca150
    void Initialize();                        // 0x007ca1c0
};

// @ 0x007c9910
void* __cdecl CopyAutoRefRange(void* first, void* last, void* dest)
{
    while (first != last) {
        if (dest) {
            InsertAutoRef(dest, first);
            ((char*)dest)[0x14] = ((char*)first)[0x14];
        }
        first = (char*)first + 0x18;
        dest = (char*)dest + 0x18;
    }
    return dest;
}

// @ 0x007c99e0
void Vec4::InsertOne(uint32_t* pos, uint32_t* value)
{
    uint32_t* end = mpEnd;
    if (end != mpCap) {
        if (pos <= value && value < end)
            value++;
        uint32_t last = 0;
        if (end)
            last = *(end - 1);
        if (end) {
            *end = last;
            if (last)
                ((RC*)last)->AddRef();
        }
        VecCopyRange(pos, end - 1, end);
        uint32_t old = *value;
        uint32_t cur = *pos;
        if (old != cur) {
            if (old)
                ((RC*)old)->AddRef();
            *pos = old;
            if (cur)
                ((RC*)cur)->Release();
        }
        mpEnd = end + 1;
        return;
    }
    int count = (int)(end - mpBegin) >> 2;
    unsigned cap = count ? (unsigned)count * 2 : 1;
    uint32_t* buf = cap ? (uint32_t*)EA_New(cap * 4, "App", 0, 0, 0, 0xd1) : 0;
    (void)VecDoInsertValue();
    (void)value;
    mpBegin = buf;
}

// @ 0x007c9bc0
void Vec4::InsertN(uint32_t* pos, int n, uint32_t* value)
{
    int size = (int)(mpCap - mpEnd) >> 2;
    if ((unsigned)size < (unsigned)n) {
        int count = (int)(mpEnd - mpBegin) >> 2;
        unsigned cap = count * 2;
        if (count == 0) cap = 1;
        unsigned need = (unsigned)count + n;
        if (need < cap) need = cap;
        uint32_t* buf = need ? (uint32_t*)EA_New(need * 4, "App", 0, 0, 0, 0xd1) : 0;
        (void)VecDoInsertValue();
        mpBegin = buf;
    }
    (void)pos; (void)value;
}

// @ 0x007c9dc0
void AutoRefVec::InsertOne(AutoRef* pos, AutoRef* value)
{
    AutoRef* end = mpEnd;
    if (end != mpCap) {
        if (pos <= value && value < end)
            value++;
        if (end) {
            end->m0 = end[-1].m0;
            end->m4 = end[-1].m4;
            end->mRC = end[-1].mRC;
            if (end->mRC)
                end->mRC->AddRef();
        }
        VecCopyRange(pos, end - 1, end);
        pos->m0 = value->m0;
        pos->m4 = value->m4;
        RC* s = value->mRC;
        RC* d = pos->mRC;
        if (s != d) {
            if (s) s->AddRef();
            pos->mRC = s;
            if (d) d->Release();
        }
        mpEnd = end + 1;
        return;
    }
    int count = (int)(end - mpBegin);
    unsigned cap = count ? (unsigned)count * 2 : 1;
    AutoRef* buf = cap ? (AutoRef*)EA_New(cap * 0x10, "App", 0, 0, 0, 0xd1) : 0;
    (void)VecDoInsertValue();
    (void)value;
    mpBegin = buf;
}

// @ 0x007c9fa0
void AutoRefVec::DoAssignFromIterator(AutoRef* first, AutoRef* last)
{
    AutoRef* b = mpBegin;
    int n = (int)(last - first);
    if (n > (int)(mpCap - b)) {
        AutoRef* nb = (AutoRef*)VecAllocGrow(n, first, last);
        VecDestroyRange16(b, mpEnd);
        if (b != 0 && b != mInline)
            EA_Free(b);
        mpBegin = nb;
        mpEnd = nb + n;
        mpCap = nb + n;
        return;
    }
    if (n <= (int)(mpEnd - b)) {
        AutoRef* e = (AutoRef*)VecCopyImpl(first, last, b);
        VecDestroyRange16(e, mpEnd);
        mpEnd = e;
        return;
    }
    AutoRef* mid = first + (mpEnd - b);
    VecCopyImpl(first, mid, b);
    VecUninitCopy(0, mid, last, mpEnd, 0);
    mpEnd = mpBegin + n;
}

// @ 0x007ca060
PairVec& PairVec::operator=(const PairVec& x)
{
    if (&x != this) {
        int n = (int)(x.mpEnd - x.mpBegin);
        if (n > (int)(mpCap - mpBegin)) {
            Pair16* nb = (Pair16*)VecReserve(n, x.mpBegin, x.mpEnd);
            VecDestroyRange(mpBegin, mpEnd);
            if (mpBegin) EA_Free(mpBegin);
            mpBegin = nb;
            mpEnd = nb + n;
            mpCap = nb + n;
            return *this;
        }
        if (n <= (int)(mpEnd - mpBegin)) {
            Pair16* e = (Pair16*)VecCopyRange(x.mpBegin, x.mpEnd, mpBegin);
            VecDestroyRange(e, mpEnd);
            mpEnd = mpBegin + n;
            return *this;
        }
        VecCopyRange(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
        VecUninitCopy(0, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, 0);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x007ca150
void cConfigManager::GetOptionIDs(UIntVec* out)
{
    out->reserve((unsigned)((int)((char*)mOptionsEnd - (char*)mOptionsBegin) / 0xac));
    cOption* p = mOptionsBegin;
    while (p != mOptionsEnd) {
        out->push_back(p->id);
        p++;
    }
}

// @ 0x007ca1c0
void cConfigManager::Initialize()
{
    // parser/file-parser wiring + per-option property build (see partial.txt)
}

// @ 0x007ca8e0
void MapVec::Destroy()
{
    // element-wise teardown of vector_map<u64,AutoRef> then free (see partial.txt)
}
