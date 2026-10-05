// Slice s005300d0: Swarm skin-paint "distribute" effect.
// cSPSkinPaintDistributeDescription serialization (Read/Write), the basic_string<char>
// and eastl::vector<pair<int,float>> helpers it uses, and two cCommandStateT::OnRegister
// thunks. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc needed
// except for the vector copy constructor).
#include "types.h"

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);   // 0x00f473a0
extern "C" void EASTL_allocator_deallocate(void* p);                     // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags); // 0x0042dee0

// ---------------------------------------------------------------- IStream
struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual int Read(void* data, uint32_t size);                  // +0x30
    virtual void v13();
    virtual bool Write(const void* data, uint32_t size);          // +0x38
};
bool ReadInt32(IStream* s, int32_t* p, uint32_t count, int endian);   // 0x0093a780
bool ReadBool8(IStream* s, bool* p);                                  // 0x0093ac80
bool WriteUint32(IStream* s, const uint32_t* p, uint32_t count, int endian); // 0x0093aa70
bool WriteBool8(IStream* s, const bool* p, uint32_t count);           // 0x0093a9a0

// ---------------------------------------------------------------- eastl::basic_string<char>
struct StrAllocator {
    void* allocate(uint32_t n) { return EASTL_allocator_allocate(n, "Editor", 0, 0, __FILE__, 0xd1); }
};
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    StrAllocator mAllocator;
    ~string();                                                    // @ 0x00530670
    void push_back(char c);                                       // @ 0x005306c0
    void reserve(uint32_t n);                                     // @ 0x0047c600
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(char* p, uint32_t n) { if (p) Deallocate(p, n); }
    void Deallocate(char* p, uint32_t) { char* q = p; EASTL_allocator_deallocate(q); }
};

// ---------------------------------------------------------------- pair / vector
struct PairIF {
    int first;
    float second;
    PairIF() : first(0), second(0.0f) {}
};
struct VectorIF {
    PairIF* mpBegin;
    PairIF* mpEnd;
    PairIF* mpCapacity;
    uint32_t mAlloc[2];
    VectorIF() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    VectorIF(const VectorIF& x);
    VectorIF& operator=(const VectorIF& x);
    PairIF* erase(PairIF* first, PairIF* last);                   // @ 0x00530c80
    void resize(uint32_t n);                                      // @ 0x00530b70
    PairIF* DoAllocateCopy(uint32_t n, const PairIF* first, const PairIF* last); // @ 0x00530d20
    void DoInsertValues(PairIF* position, uint32_t n, const PairIF& value);      // @ 0x00530db0
};
PairIF* uninitialized_copy(const PairIF* first, const PairIF* last, PairIF* dest, bool tag); // @ 0x005311a0

// ---------------------------------------------------------------- description
struct cDescription {
    void* mVT;
    int mRefCount;
};
struct cSPSkinPaintDistributeDescription : cDescription {
    string mEffect;                           // +0x08
    int mParticleDescId;                      // +0x18
    float mSpacing;                           // +0x1c
    uint32_t mLimit;                          // +0x20
    uint32_t mRegionFlags;                    // +0x24
    float mBackCutoff;                        // +0x28
    float mBellyCutoff;                       // +0x2c
    float mSpineRange[2];                     // +0x30
    bool mInvertRegions;                      // +0x38
    bool mCenterOnly;                         // +0x39
    bool mExtraCover;                         // +0x3a
    bool mNonRandom;                          // +0x3b
    VectorIF mParticleSelect;                 // +0x3c
    bool mParticleSelectIndependent;          // +0x50
};

// ---------------------------------------------------------------- stream helpers
inline bool WriteValue32(IStream* s, uint32_t value) { return WriteUint32(s, &value, 1, 0); }
inline bool Write(IStream* s, uint32_t value) { return WriteValue32(s, value); }
inline bool Write(IStream* s, int value) { return WriteValue32(s, (uint32_t)value); }
inline bool WriteFloat32(IStream* s, float value) { return WriteUint32(s, (uint32_t*)&value, 1, 0); }
inline bool Write(IStream* s, float value) { return WriteFloat32(s, value); }
inline bool WriteBool(IStream* s, uint8_t value) { return WriteBool8(s, (const bool*)&value, 1); }
inline bool Write(IStream* s, bool value) { return WriteBool(s, value ? 1 : 0); }

// ---------------------------------------------------------------- @ 0x005302b0
// Reads a null-terminated byte string into *str.
IStream* ReadString(IStream* stream, string* str)
{
    if (str->mpBegin != str->mpEnd) {
        str->mpBegin[0] = 0;
        str->mpEnd = str->mpBegin;
    }
    char c;
    while (stream->Read(&c, 1) == 1 && c != 0)
        str->push_back(c);
    return stream;
}

// ---------------------------------------------------------------- @ 0x005305c0
// Writes *str followed by a terminating zero byte.
IStream* WriteString(IStream* stream, string* str)
{
    uint32_t n = (uint32_t)(str->mpEnd - str->mpBegin);
    char* z = str->mpBegin;
    stream->Write(z, n);
    char p = 0;
    stream->Write(&p, 1);
    return stream;
}

// ---------------------------------------------------------------- @ 0x005300d0
void ReadDistributeDescription(IStream* stream, int version, cSPSkinPaintDistributeDescription* d)
{
    ReadString(stream, &d->mEffect);
    ReadInt32(stream, &d->mParticleDescId, 1, 0);
    ReadInt32(stream, (int32_t*)&d->mSpacing, 1, 0);
    ReadInt32(stream, (int32_t*)&d->mLimit, 1, 0);
    ReadInt32(stream, (int32_t*)&d->mRegionFlags, 1, 0);
    ReadInt32(stream, (int32_t*)&d->mBackCutoff, 1, 0);
    ReadInt32(stream, (int32_t*)&d->mBellyCutoff, 1, 0);
    stream->Read(&d->mSpineRange, 8);
    ReadBool8(stream, &d->mInvertRegions);
    ReadBool8(stream, &d->mCenterOnly);
    ReadBool8(stream, &d->mExtraCover);
    ReadBool8(stream, &d->mNonRandom);
    if (version < 2) {
        d->mParticleSelect.erase(d->mParticleSelect.mpBegin, d->mParticleSelect.mpEnd);
        d->mParticleSelectIndependent = false;
    } else {
        int count;
        ReadInt32(stream, &count, 1, 0);
        d->mParticleSelect.resize((uint32_t)count);
        for (int i = 0; i < count; ++i) {
            PairIF* p = d->mParticleSelect.mpBegin + i;
            ReadInt32(stream, &p->first, 1, 0);
            ReadInt32(stream, (int32_t*)&p->second, 1, 0);
        }
        ReadBool8(stream, &d->mParticleSelectIndependent);
    }
}

// ---------------------------------------------------------------- @ 0x00530310
void WriteDistributeDescription(IStream* stream, cSPSkinPaintDistributeDescription* d)
{
    WriteString(stream, &d->mEffect);
    Write(stream, d->mParticleDescId);
    Write(stream, d->mSpacing);
    Write(stream, d->mLimit);
    Write(stream, d->mRegionFlags);
    Write(stream, d->mBackCutoff);
    Write(stream, d->mBellyCutoff);
    stream->Write(&d->mSpineRange, 8);
    Write(stream, d->mInvertRegions);
    Write(stream, d->mCenterOnly);
    Write(stream, d->mExtraCover);
    Write(stream, d->mNonRandom);
    int32_t count = (int32_t)(d->mParticleSelect.mpEnd - d->mParticleSelect.mpBegin);
    Write(stream, count);
    for (int i = 0; i < count; ++i) {
        PairIF* p = d->mParticleSelect.mpBegin + i;
        Write(stream, p->first);
        Write(stream, p->second);
    }
    Write(stream, d->mParticleSelectIndependent);
}

// ---------------------------------------------------------------- @ 0x00530670
string::~string()
{
    DeallocateSelf();
}

// ---------------------------------------------------------------- @ 0x005306c0
void string::push_back(char c)
{
    if (mpEnd + 1 == mpCapacity) {
        uint32_t nRequired = (uint32_t)(mpEnd - mpBegin) + 1;
        uint32_t nCapacity = (uint32_t)(mpCapacity - mpBegin) - 1;
        uint32_t nNewCapacity = (nCapacity > 8) ? nCapacity * 2 : 8;
        reserve(nRequired < nNewCapacity ? nNewCapacity : nRequired);
    }
    *mpEnd = c;
    mpEnd = mpEnd + 1;
    *mpEnd = 0;
}

// ---------------------------------------------------------------- @ 0x00530c80
PairIF* VectorIF::erase(PairIF* first, PairIF* last)
{
    PairIF* pEnd = mpEnd;
    PairIF* p = first;
    for (PairIF* q = last; q != pEnd; ++q, ++p)
        *p = *q;
    for (PairIF* q = p; q < mpEnd; ++q) {
    }
    mpEnd = mpEnd - (last - first);
    return first;
}

// ---------------------------------------------------------------- @ 0x00530b70
void VectorIF::resize(uint32_t n)
{
    if ((uint32_t)(mpEnd - mpBegin) < n) {
        PairIF value;
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// ---------------------------------------------------------------- @ 0x00530d20
PairIF* VectorIF::DoAllocateCopy(uint32_t n, const PairIF* first, const PairIF* last)
{
    PairIF* p;
    if (n == 0)
        p = 0;
    else
        p = (PairIF*)EASTL_Allocate(mAlloc, n * 8, 4, 0);
    PairIF* result = p;
    uninitialized_copy(first, last, p, false);
    return result;
}

// ---------------------------------------------------------------- @ 0x00530770
VectorIF::VectorIF(const VectorIF& x)
{
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    PairIF* p;
    if (n == 0)
        p = 0;
    else
        p = (PairIF*)EASTL_Allocate(mAlloc, n * 8, 4, 0);
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    mpEnd = uninitialized_copy(x.mpBegin, x.mpEnd, mpBegin, false);
}

// ---------------------------------------------------------------- @ 0x00530870
VectorIF& VectorIF::operator=(const VectorIF& x)
{
    if (&x != this) {
        uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if ((uint32_t)(mpCapacity - mpBegin) < n) {
            PairIF* p = DoAllocateCopy(n, x.mpBegin, x.mpEnd);
            for (PairIF* q = mpBegin; q < mpEnd; ++q) {
            }
            if (mpBegin != 0 && ((uint32_t*)mpBegin)[-1] != 0)
                EASTL_allocator_deallocate(mpBegin);
            mpBegin = p;
            mpCapacity = mpBegin + n;
        } else if ((uint32_t)(mpEnd - mpBegin) < n) {
            PairIF* pEnd = mpEnd;
            PairIF* pSrc = x.mpBegin + (mpEnd - mpBegin);
            PairIF* pSrcEnd = x.mpBegin;
            PairIF* pDst = mpBegin;
            for (PairIF* q = pSrcEnd; q != pSrc; ++q, ++pDst)
                *pDst = *q;
            uninitialized_copy(pSrc, x.mpEnd, mpEnd, false);
        } else {
            PairIF* pDst = mpBegin;
            for (PairIF* q = x.mpBegin; q != x.mpEnd; ++q, ++pDst)
                *pDst = *q;
            for (PairIF* q = pDst; q < mpEnd; ++q) {
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------- @ 0x00530c00 / @ 0x00530c40
struct CBlockCommandBase {
    char pad[0x30];
    void OnRegister(void* parser, void* state);   // 0x0083c780
};
struct CmdStateBlock : CBlockCommandBase {
    void* mState;                                  // +0x30
    void OnRegister(void* parser, void* state);
};
void CmdStateBlock::OnRegister(void* parser, void* state)
{
    mState = state ? (void*)((char*)state - 0xc) : 0;
    CBlockCommandBase::OnRegister(parser, state);
}

struct CMetaCommandBase {
    char pad[0x0c];
    void OnRegister(void* parser, void* state);   // 0x0083c7f0
};
struct CmdStateMeta : CMetaCommandBase {
    void* mState;                                  // +0x0c
    void OnRegister(void* parser, void* state);
};
void CmdStateMeta::OnRegister(void* parser, void* state)
{
    mState = state ? (void*)((char*)state - 0x34) : 0;
    CMetaCommandBase::OnRegister(parser, state);
}
