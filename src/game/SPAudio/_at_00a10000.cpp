// src/game/SPAudio/_at_00a10000.cpp -- migrated from slice(s) s00a13fc0, s00a102e0, s00a0f350 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00a10000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureAnimManager.h"
#include "EA/ArgScript/cCommandBase.h"
#include <string.h>
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/VoiceContainer.h"
#include <stdlib.h>
#include <new>

// ---- items of slice s00a0f350 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
namespace EA {
namespace Audio {
class Command_s00a0_f350 {
public:
    u8* mCommandStart;
    u8* mCommandEnd;
    u8* mCommandPtr;
    u32 mCommandId;
    u32 mCommandSize;
    u32 mNumParameters;

    void Clear() {
        mCommandStart = 0; mCommandEnd = 0; mCommandPtr = 0;
        mCommandId = 0; mCommandSize = 0; mNumParameters = 0;
    }
    void Load(u32* p) {
        mCommandStart = (u8*)p;
        mCommandId = *p++;
        mCommandSize = *p++;
        mNumParameters = *p++;
        mCommandPtr = (u8*)p;
        mCommandEnd = mCommandPtr + mCommandSize;
    }
    u8*  EnumParameter(u32* pos, u32* id, u32* type, int* size);  // 0x00a0f880 (EA::Audio::Command::EnumParameter)
    void* Find(int id, int* type, int* size);  // 0x00a0f8e0 (EA::Audio::Command::Find)
    bool SetT1(int id, int* type, int* size);
    bool GetFloat(int id, float* out);
    bool GetUint32(int id, u32* out);  // 0x00a0fab0 (EA::Audio::Command::GetUint32)
    bool GetString8(int id, char* buf, u32* pSize);  // 0x00a0faf0 (EA::Audio::Command::GetString8)
    const char* GetString8(int id);  // 0x00a0fb60 (EA::Audio::Command::GetString8)
    bool GetVoidPtr(int id, void** out);  // 0x00a0fb90 (EA::Audio::Command::GetVoidPtr)
    void* GetData(int id, void** out);  // 0x00a0fbd0 (EA::Audio::Command::GetData)
    bool GetVector3(int id, float* out);  // 0x00a0fc10 (EA::Audio::Command::GetVector3)
    bool GetMatrix33(int id, float* out);  // 0x00a0fc60 (EA::Audio::Command::GetMatrix33)
    bool SetUint64(int id, u32 v);  // 0x00a0fcf0 (EA::Audio::Command::SetUint64)
    bool SetFloat(int id, float v);  // 0x00a0fd30 (EA::Audio::Command::SetFloat)
    void DeleteParameter(int id);  // 0x00a0fd70 (EA::Audio::Command::DeleteParameter)
};
}  // namespace
}
struct CmdQueue {
    u32 mBegin, mEnd, mCap;      // +0 (fixed vector)
    u8  pad[0x14 - 0xc];
    EA::Audio::Command_s00a0_f350 mCmd;     // +0x14
    u32 mWrite;                  // +0x2c
    u32 mRead;                   // +0x30
    u32 mCmdBase;                // +0x34
    u32 mSizePtr;                // +0x38
    u32 mCountPtr;               // +0x3c
    u32 mNumCmds;                // +0x40
    u32 mCapacity;               // +0x44
    u32 mParamCount;             // +0x48
    u32 mReadIndex;              // +0x4c

    CmdQueue();
    void Swap(CmdQueue* o);
    void Grow(u32 n);
    void ResizeBuffer(u32 n);   // 0x4c0410
    void Append(const void* data, u32 size);
    void AddFloat(u32 id, u32 v);
    void AddUint32(u32 id, u32 v);
    void AddVoidPtr(u32 id, u32 v);
    bool Reset(u32 n);
    void FinishCommand();
    void CancelCommand();
    bool ReadNext();
    void BeginRead();
    void RewindRead();
    void Clear();
    void Ensure4() { if ((u32)((mBegin - mWrite) + mCapacity) < 4) Grow((mEnd - mBegin) * 2); }
    void Put(u32 v) { Ensure4(); *(u32*)mWrite = v; mWrite += 4; }
};
// ---- items of slice s00a0f350 end

// ---- items of slice s00a102e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_166d868;
struct TreeBase {
    void Nuke(void*);
};
struct Serializer {
    uint8_t* mpBase;      // 0x00
    uint8_t* mpEnd;       // 0x04
    uint8_t* mpPad08[9];  // 0x08
    uint8_t* mpWrite;     // 0x2c
    uint8_t* mpRead;      // 0x30
    uint8_t* mpMark0;     // 0x34
    uint8_t* mpMark1;     // 0x38
    uint32_t* mpCountSlot;// 0x3c
    uint32_t mPad40;      // 0x40
    uint32_t mSize;       // 0x44
    uint32_t mCount;      // 0x48

    void Grow(uint32_t);
    void WriteBytes(const void*, uint32_t);
    void WriteFloatRaw(int, float); // 0xa10060 (elsewhere)

    __forceinline void Ensure(uint32_t n) {
        if ((uint32_t)(mpBase - mpWrite) + mSize < n) Grow((uint32_t)(mpEnd - mpBase) * 2);
    }
    __forceinline void W32(uint32_t v) {
        Ensure(4);
        *(uint32_t*)mpWrite = v;
        mpWrite += 4;
    }
    __forceinline void W32p(const uint32_t* p) {
        Ensure(4);
        if (p) *(uint32_t*)mpWrite = *p;
        mpWrite += 4;
    }

    void BeginTree(uint32_t id);                            // 0xa102e0
    void WriteFloat(int, float);                            // 0xa10390
    void WriteString(int, const char*, int);                // 0xa103c0
    void WriteBlob(int, const void*, int);                  // 0xa10490
    void WriteVec3(int, const uint32_t*);                   // 0xa10540
    void WriteArr9(int, const uint32_t*);                   // 0xa10670
};
struct IChild {
    virtual void AddRef();                   // 0x00
    virtual void Release();                  // 0x04
    virtual bool q08(int);                   // 0x08
    virtual void q0c(void*, int);            // 0x0c
    virtual void q10(void*, int);            // 0x10
    virtual void q14(int);                   // 0x14
    virtual bool q18(int);                   // 0x18
virtual void q1c();
virtual void q20();
virtual void q24();
virtual void q28();
virtual void q2c();
virtual void q30();
virtual void q34();
virtual void q38();
    virtual int  q3c(int);                   // 0x3c
    virtual int  q40(int);                   // 0x40
    virtual bool q44(int, int, int);         // 0x44
    virtual bool q48(int, int, int);         // 0x48
    virtual bool q4c(int, int, int);         // 0x4c
};
struct Ability {
    void*   vtbl0;   // 0x00
    void*   vtbl1;   // 0x04
    int     ref;     // 0x08
    IChild* childA;  // 0x0c
    IChild* childB;  // 0x10

    void* ctor();                         // 0xa107a0
    void  dtor();                         // 0xa10800
    Ability* ctor2(IChild*, IChild*);     // 0xa10860
    bool  q08(int);                       // 0xa10960
    void  q10(void*, int);                // 0xa109a0
    void  q14(int);                       // 0xa109d0
    bool  q18(int);                       // 0xa10a00
    int   q3c(int);                       // 0xa10cc0
    int   q40(int);                       // 0xa10d00
    bool  q44(int, int, int);             // 0xa10d40
    bool  q48(int, int, int);             // 0xa10da0
    bool  q4c(int, int, int);             // 0xa10e00
    void  q0c(void*, char);                // 0xa10e90
};
void* g_166d868;
// ---- items of slice s00a102e0 end

// ---- items of slice s00a13fc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kFloat16;    // 16.0f
extern char gType_14bc0fc;      // "type" pointer stored at object +0
typedef unsigned short u16;
void  FUN_00a22220(void* self, u32 n);
void  FUN_00a240b0(void* self, void* a, void* b, void* c, void* d, void* e, void* f);
u32   FUN_00921340(u32 n);
u32   FUN_009213c0(void* self, u32 v);
void  FUN_00921260(void* pool, void* begin, u32 n, u32 size, u32 align, u32 flags);
struct SoundList {
    unsigned* mpBegin;      // +0x00
    unsigned* mpEnd;        // +0x04
    unsigned* mpCapacity;   // +0x08
    unsigned  mBuffer[30];  // +0x0c

    unsigned* begin()       { return mpBegin; }
    unsigned* end()         { return mpEnd; }
    unsigned  size() const  { return (unsigned)(mpEnd - mpBegin); }

    // eastl::vector<unsigned, fixed_vector_allocator<...> >::erase
    __forceinline unsigned* erase(unsigned* first, unsigned* last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
};
struct Playlist {
    void*      mVtbl;        // +0x00 RefCountTemplate
    int        mRefCount;    // +0x04
    SoundList  mSounds;      // +0x08  (0x84 bytes)
    unsigned   mPad8c[3];    // +0x8c
    unsigned   mLastChoice;  // +0x98
    unsigned*  mpIterator;   // +0x9c

    unsigned Choose();                       // 0x00a146a0
    void     Shuffle();                      // 0x00a14730
    bool     Clear();                        // 0x00a147b0
};
struct pointer_to_unary_function {
    int (*mpFunc)(int);
    int operator()(int n) const { return mpFunc(n); }
};
struct tDelayLine {
    int m0, m4, m8, mc, m10;
    tDelayLine();
    ~tDelayLine();
};
tDelayLine::~tDelayLine()
{
}
struct AudioEffect {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual ~AudioEffect() {}
    char mData[0x20];           // +0x04 .. +0x24
};
struct Chorus : AudioEffect {
    tDelayLine mDelays[6];      // +0x24 .. +0x9c
    Chorus();
    ~Chorus();
};
struct MixSource {
    char  m00[0x0c];
    void* mpValue;              // +0x0c
    char  m10[0x11];
    u8    mChannels;            // +0x21
    char  m22[0x06];
    float mBits;                // +0x28 (16.0f)
    float mBlend;               // +0x30 (0.0f)
};
struct AudioBuffer {
    void* mp0;                  // +0x00
    float* mpData;              // +0x04
    char  m08[6];
    u16   mStride;              // +0x0e
};
struct MixCtx {
    char         m00000[0x3000c];
    AudioBuffer* mpSrc;         // +0x3000c
    AudioBuffer* mpDst;         // +0x30010
    char         m30014[0x0c];
    int          mCount;        // +0x30020
};
struct PHNode { u32 hash; void* value; PHNode* next; };   // 12 bytes
struct PHTable {
    u32      m00;
    PHNode** mpBuckets;        // +0x04
    u32      mnBucketCount;    // +0x08
    u32      mnElementCount;   // +0x0c
    u32      m10;
    u32      m14;
    u32      m18;
    PHNode*  mpFreeList;       // +0x1c
    u32      m20;
    void*    mpPoolBegin;      // +0x24
    void*    mpPoolEnd;        // +0x28
    u32      m2c;
    void*    mpInline;         // +0x30

    void FreeBuckets(PHNode** buckets, u32 count);
    ~PHTable();
};
PHTable::~PHTable()
{
    FreeBuckets(mpBuckets, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1 && mpBuckets != (PHNode**)mpInline) {
        if ((char*)mpBuckets < (char*)mpPoolBegin || (char*)mpPoolEnd <= (char*)mpBuckets)
            operator delete(mpBuckets);
        else {
            *(void**)mpBuckets = mpFreeList;
            mpFreeList = (PHNode*)mpBuckets;
        }
    }
}
struct FHT1 {
    PHTable mTable;                              // +0x00
    char    mPad[0xff0 - sizeof(PHTable)];
    FHT1() {}
    FHT1(unsigned& a, unsigned& b);
};
struct HTable28 {
    PHTable mTable;                              // +0x00
    char    mPad[0x438 - sizeof(PHTable)];
    HTable28() {}
    __declspec(noinline) HTable28(unsigned& a, unsigned& b);
};
struct MixableBase {
    void* mVtbl;
};
struct RefCountBase {
    void* mRefVtbl;
    ~RefCountBase() { mRefVtbl = (void*)0x13ef094; }
};
struct Group : MixableBase, RefCountBase {
    int       mRefCount;     // +0x08
    u32       mId;           // +0x0c
    u32       mPauseCount;   // +0x10
    FHT1      mMixees;       // +0x14
    HTable28  mRegisters;    // +0x1004
    HTable28  mAggregates;   // +0x143c

    Group(u32 id);
    bool ConnectPrimitive(u32 id, void* prim);
    bool Shutdown();
    ~Group();
};
// ---- items of slice s00a13fc0 end

// @ 0x00a10060
void CmdQueue::AddFloat(u32 id, u32 v)
{
    Put(id); Put(4); Put(0); Put(v);
    mParamCount++;
    *(u32*)mCountPtr = mParamCount;
}

// @ 0x00a10120
void CmdQueue::AddUint32(u32 id, u32 v)
{
    Put(id); Put(4); Put(1); Put(v);
    mParamCount++;
    *(u32*)mCountPtr = mParamCount;
}

// @ 0x00a101e0
void CmdQueue::AddVoidPtr(u32 id, u32 v)
{
    Put(id); Put(4); Put(4); Put(v);
    mParamCount++;
    *(u32*)mCountPtr = mParamCount;
}

// @ 0x00a102a0
bool CmdQueue::Reset(u32 n)
{
    mWrite = 0;
    Grow(n);
    mCmdBase = 0;
    mSizePtr = 0;
    mCountPtr = 0;
    mNumCmds = 0;
    mParamCount = 0;
    mRead = 0;
    mReadIndex = 0;
    mWrite = mBegin;
    return true;
}

// @ 0x00a102e0
void Serializer::BeginTree(uint32_t id)
{
    if (mpMark1 != 0 && mpMark0 != 0) {
        mpWrite = mpMark0;
        mpMark0 = 0;
        mpMark1 = 0;
        mpCountSlot = 0;
    }
    mpMark0 = mpWrite;
    W32(id);
    mpMark1 = mpWrite;
    W32(0);
    mpCountSlot = (uint32_t*)mpWrite;
    W32(0);
    mCount = 0;
}

// @ 0x00a10390
void Serializer::WriteFloat(int id, float v)
{ WriteFloatRaw(id, v); }

// @ 0x00a103c0
void Serializer::WriteString(int id, const char* s, int n)
{
    if (n == 0) {
        const char* p = s;
        while (*p) ++p;
        n = (int)(p - s);
    }
    ++n;
    W32((uint32_t)id);
    W32((uint32_t)n);
    W32(3);
    WriteBytes(s, (uint32_t)n);
    ++mCount;
    *mpCountSlot = mCount;
}

// @ 0x00a10490
void Serializer::WriteBlob(int id, const void* data, int n)
{
    W32((uint32_t)id);
    W32((uint32_t)n);
    W32(5);
    WriteBytes(data, (uint32_t)n);
    ++mCount;
    *mpCountSlot = mCount;
}

// @ 0x00a10540
void Serializer::WriteVec3(int id, const uint32_t* p)
{
    W32((uint32_t)id);
    W32(0xc);
    W32(6);
    W32p(p);
    W32p(p + 1);
    W32p(p + 2);
    ++mCount;
    *mpCountSlot = mCount;
}

// @ 0x00a10670
void Serializer::WriteArr9(int id, const uint32_t* p)
{
    W32((uint32_t)id);
    W32(0x24);
    W32(7);
    for (int i = 0; i < 9; ++i) W32p(p + i);
    ++mCount;
    *mpCountSlot = mCount;
}

// @ 0x00a10780
void f_00a10780(void** node)
{
    *node = g_166d868;
    g_166d868 = node;
}

// @ 0x00a107a0
void* Ability::ctor()
{
    vtbl1 = (void*)0x13ef094;
    ref = 0;
    vtbl0 = (void*)0x14492a0;
    vtbl1 = (void*)0x1449298;
    childA = 0;
    childB = 0;
    return this;
}

// @ 0x00a10800
void Ability::dtor()
{
    if (childB) childB->Release();
    if (childA) childA->Release();
    vtbl1 = (void*)0x13ef094;
}

// @ 0x00a10860
Ability* Ability::ctor2(IChild* a, IChild* b)
{
    vtbl1 = (void*)0x13ef094;
    ref = 0;
    vtbl0 = (void*)0x14492a0;
    vtbl1 = (void*)0x1449298;
    childA = a;
    if (a) a->AddRef();
    childB = b;
    if (b) b->AddRef();
    return this;
}

// @ 0x00a10960
bool Ability::q08(int x)
{
    if (childA && childA->q08(x)) return true;
    if (childB && childB->q08(x)) return true;
    return false;
}

// @ 0x00a109a0
void Ability::q10(void* p, int x)
{
    IChild* c = childA;
    if (c) return c->q10(p, x);
    c = childB;
    if (c) return c->q10(p, x);
}

// @ 0x00a109d0
void Ability::q14(int x)
{
    IChild* c = childA;
    if (c) c->q14(x);
    c = childB;
    if (c) c->q14(x);
}

// @ 0x00a10a00
bool Ability::q18(int x)
{
    return (childA && childA->q18(x)) || (childB && childB->q18(x));
}

// @ 0x00a10cc0
int Ability::q3c(int x)
{
    int r = 0;
    IChild* c = childA;
    if (c) { r = c->q3c(x); if (r) return r; }
    c = childB;
    if (c) r = c->q3c(x);
    return r;
}

// @ 0x00a10d00
int Ability::q40(int x)
{
    int r = 0;
    IChild* c = childA;
    if (c) { r = c->q40(x); if (r) return r; }
    c = childB;
    if (c) r = c->q40(x);
    return r;
}

// @ 0x00a10d40
bool Ability::q44(int a, int b, int c)
{
    return (childA && childA->q44(a, b, c)) || (childB && childB->q44(a, b, c));
}

// @ 0x00a10da0
bool Ability::q48(int a, int b, int c)
{
    return (childA && childA->q48(a, b, c)) || (childB && childB->q48(a, b, c));
}

// @ 0x00a10e00
bool Ability::q4c(int a, int b, int c)
{
    return (childA && childA->q4c(a, b, c)) || (childB && childB->q4c(a, b, c));
}

// @ 0x00a10e90
void Ability::q0c(void* p, char flag)
{
    if (flag) {
        ((TreeBase*)p)->Nuke(*(void**)((char*)p + 0xc));
        *(void**)((char*)p + 4) = (char*)p + 4;
        *(void**)((char*)p + 8) = (char*)p + 4;
        *(void**)((char*)p + 0xc) = 0;
        *(uint8_t*)((char*)p + 0x10) = 0;
        *(void**)((char*)p + 0x14) = 0;
    }
    IChild* c = childA;
    if (c) c->q0c(p, 0);
    c = childB;
    if (c) c->q0c(p, 0);
}

// @ 0x00a14380
Group::~Group()
{
    mVtbl = (void*)0x1449454;
    mRefVtbl = (void*)0x1449450;
}

// @ 0x00a144c0
HTable28::HTable28(unsigned& a, unsigned& b)
{
    char* pool = (char*)this + 0x104;
    FUN_00921260((char*)this + 0x0c, pool, 600, 0xc, 4, 0);
    mTable.m10 = 0x461c4000;      // 10000.0f
    mTable.m14 = 0x40000000;      // 2.0f
    mTable.m18 = 0;
    u32 h = FUN_00921340(0x33);
    FUN_00a240b0(this, &a, &b, &a, &b, &a, &b);
    (void)h;
    u32 cap = FUN_009213c0(this, mTable.m10);
    if (mTable.mnBucketCount < cap)
        FUN_00a22220(this, cap);
}

// @ 0x00a145c0
Group::Group(u32 id)
{
    mRefVtbl = (void*)0x13ef094;
    mRefCount = 0;
    mId = id;
    mPauseCount = 0;
    mVtbl = (void*)0x1449454;
    mRefVtbl = (void*)0x1449450;
    new (&mMixees) FHT1(id, id);
    new (&mRegisters) HTable28(id, id);
    new (&mAggregates) HTable28(id, id);
}

// @ 0x00a14680
int __cdecl FUN_00a14680(int n)
{
    return rand() % n;
}

// @ 0x00a146a0
unsigned Playlist::Choose()
{
    if (mSounds.begin() == mSounds.end())
        return 0;
    if (mpIterator == 0 || mpIterator == mSounds.end())
        mpIterator = mSounds.begin();
    mLastChoice = *mpIterator++;
    return mLastChoice;
}

// @ 0x00a146e0
void __cdecl FUN_00a146e0(unsigned* first, unsigned* last, pointer_to_unary_function& rng)
{
    for (unsigned* i = first + 1; i < last; ++i) {
        unsigned* j = first + rng((i - first) + 1);
        unsigned tmp = *i;
        *i = *j;
        *j = tmp;
    }
}

// @ 0x00a14730
void Playlist::Shuffle()
{
    pointer_to_unary_function rng = { &FUN_00a14680 };
    FUN_00a146e0(mSounds.mpBegin, mSounds.mpEnd, rng);
    mpIterator = mSounds.mpBegin;
    if (mSounds.size() > 1 && *mSounds.mpBegin == mLastChoice)
        Choose();
}

// @ 0x00a147b0
bool Playlist::Clear()
{
    mSounds.erase(mSounds.begin(), mSounds.end());
    mpIterator = mSounds.mpBegin;
    return true;
}

// @ 0x00a14810
bool __cdecl FUN_00a14810(MixSource* src, MixCtx* ctx)
{
    int n = 0x10 - (int)src->mBits;
    if (n != 0) {
        float blend = src->mBlend;
        u16   mask = (u16)~((1 << n) - 1);
        int   channels = src->mChannels;
        AudioBuffer* pa = ctx->mpSrc;
        AudioBuffer* pb = ctx->mpDst;
        int count = ctx->mCount;
        for (int i = 0; i < channels; i++) {
            float* s = (float*)((char*)pa->mpData + (u32)pa->mStride * i * 4);
            float* d = (float*)((char*)pb->mpData + (u32)pb->mStride * i * 4);
            for (int j = 0; j < count; j++) {
                float v = s[j];
                if (blend == 0.0f) {
                    d[j] = v;
                } else {
                    float q = (float)(short)((int)(v * 32767.0f) & mask) * 3.0518509447574615e-05f;
                    if (blend != 1.0f)
                        q = q * blend + v * (1.0f - blend);
                    d[j] = q;
                }
            }
        }
        ctx->mpDst = pa;
        ctx->mpSrc = pb;
    }
    return true;
}

// @ 0x00a14940
bool __cdecl FUN_00a14940(void* p)
{
    if (p != 0)
        *(void**)p = &gType_14bc0fc;
    float* pf = (float*)((char*)p + 0x28);
    *pf = kFloat16;
    *(void**)((char*)p + 0x0c) = pf;
    *(float*)((char*)p + 0x30) = 0.0f;
    return true;
}

// @ 0x00a14980
tDelayLine::tDelayLine()
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    mc = 0;
    m10 = 0;
}

// @ 0x00a149b0
Chorus::Chorus()
{
}

// @ 0x00a14a10
Chorus::~Chorus()
{
}
