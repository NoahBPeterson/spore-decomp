// Slice s00bc4730 -- the creature "property record" registry: the 0x7b4-byte PropRecord
// (init/destroy/copy), its Elem98 fixed-vector helpers, and the intrusive-list Entry
// container (Node {next, prev, Entry}; Entry {key, PropRecord @0x20, state, busy, 4 vectors}).
//
// Layout derived from the ctors 0x00bc4630 / 0x00bc4820 and the teardown 0x00bc53f0:
//   PropRecord 0x7b4: +0x008 fixed_vector<uint32,8>   (buf 0x020, cap 0x040)
//                     +0x040 fixed_vector<Vector2,32>  (buf 0x058, cap 0x158)
//                     +0x158 fixed_vector<float,32>    (buf 0x170, cap 0x1f0)
//                     +0x1f0 fixed_vector<uint8,32>    (buf 0x208, cap 0x228)
//                     +0x228 fixed_vector<Vector3,2>   (buf 0x240, cap 0x258)
//                     +0x258 fixed_vector<Vector2,2>   (buf 0x270, cap 0x280)
//                     +0x280 fixed_vector<Elem98,8>    (buf 0x298, cap 0x758)
//                     +0x758 fixed_string32            (buf 0x76c, cap 0x78c)
//   Entry 0x954: +0x000 key, +0x020 PropRecord, +0x7d5 disabled, +0x7d8 state,
//                +0x7dc busy, +0x7e0 fixed_vector<void*,32>, +0x878 fixed_vector<void*,16>,
//                +0x8d4 fixed_vector<void*,16>, +0x92c fixed_vector<void*,4>
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>

extern "C" void __cdecl operator_delete__(void*);   // 0x00f47380 operator delete[]
void* __cdecl operator_new(unsigned size, const char* name, int, int, const char* file, int line); // 0x00f473a0
void** __cdecl VectorErasePtr(void** first, void** last, void** end);          // 0x0042f530
void** __cdecl VectorCopyPtr(void** first, void** last, void** dst);           // 0x006782c0
void* __cdecl GetAudioSystem();                                            // 0x00a206f0

static const char* const kSimulator = "Simulator";
static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

static inline void freeBuf(void* p) { if (p && ((int*)p)[-1] != 0) operator_delete__(p); }

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Quad16 { uint32_t a, b, c, d; };

// ---- EASTL fixed_vector: begin/end/capacity + allocator words + inline buffer ----------
template <typename T, int N>
struct fixed_vector {
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    T mBuffer[N];

    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    size_type capacity() const { return (size_type)(mpCapacity - mpBegin); }

    void init() {
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
        mAllocator[2] = 0;
    }
};

struct Elem98 : fixed_vector<Quad16, 8> {
    void assign(const Elem98& other);                        // 0x00bc3f50
};
typedef char chk_elem98[(sizeof(Elem98) == 0x98) ? 1 : -1];

// ---- out-of-line Elem98 range helpers (element size 0x98) ------------------------------
Elem98* __cdecl ElemVecAllocN(unsigned n, const Elem98* first, const Elem98* last);   // 0x00bc4d90
Elem98* __cdecl ElemVecFreeN(Elem98* first, Elem98* last, Elem98* out);               // 0x00bc3ec0
Elem98* __cdecl ElemVecCopyBack(Elem98* first, Elem98* last, Elem98* out);            // 0x00bc4060
void    __cdecl ElemVecFillN(Elem98* first, unsigned n, const Elem98* val);           // 0x00bc4280
Elem98* __cdecl ElemVecCopyConstruct(Elem98* first, Elem98* last, Elem98* out);       // 0x00bc4310
Elem98* __cdecl ElemVecInsertCopy(void* out, Elem98* first, Elem98* last, Elem98* dst); // 0x00bc4370
Elem98* __cdecl ElemVecAssignRange(Elem98* first, Elem98* last, Elem98* out);         // 0x00bc42d0
Elem98* __cdecl ElemVecFillRange(Elem98* first, Elem98* last, const Elem98* val);     // 0x00bc4590

struct ElemVecOps : fixed_vector<Elem98, 8> {
    void destroyRange(Elem98* first, Elem98* last);   // 0x00bc3f10
};

struct fixed_string32 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mPad;
    char* mpBuffer;
    char mBuffer[32];
};

struct PropRecord {
    uint32_t mValue0;                                 // +0x000
    int32_t  mCount;                                  // +0x004
    fixed_vector<uint32_t, 8> mIndices;               // +0x008
    fixed_vector<Vector2, 32> mVec2A;                 // +0x040
    fixed_vector<float, 32>   mAngles;                // +0x158
    fixed_vector<uint8_t, 32> mFlags;                 // +0x1f0
    fixed_vector<Vector3, 2>  mVec3;                  // +0x228
    fixed_vector<Vector2, 2>  mVec2B;                 // +0x258
    fixed_vector<Elem98, 8>   mLists;                 // +0x280
    fixed_string32            mName;                  // +0x758
    float    mF78C;                                   // +0x78c
    float    mF790;                                   // +0x790
    uint32_t mU794;                                   // +0x794
    uint32_t mU798;                                   // +0x798
    uint8_t  mB79C;                                   // +0x79c
    uint8_t  mB79D;                                   // +0x79d
    uint16_t mPad79E;                                 // +0x79e
    uint32_t mU7A0;                                   // +0x7a0
    uint32_t mU7A4;                                   // +0x7a4
    uint32_t mU7A8;                                   // +0x7a8
    uint32_t mBitMask;                                // +0x7ac
    uint32_t mFourCC;                                 // +0x7b0

    void init();                                      // 0x00bc4630
    void destroy();                                   // 0x00bc4730
    void copyFrom(const PropRecord& src);             // 0x00bc54f0
};
typedef char chk_rec[(sizeof(PropRecord) == 0x7b4) ? 1 : -1];

// ---- Entry vectors (fixed_vector<void*,N> plus alignment padding) ----------------------
typedef fixed_vector<void*, 32> EntryVec32;
struct EntryVec16 { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[3]; void* mBuffer[16];
    void init() { void** p = mBuffer; mpBegin = p; mpEnd = p; p += 16; mpCapacity = p; mAlloc[2] = 0; } };
struct EntryVec16P { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[3]; void* mBuffer[16]; uint32_t mPad;
    void init() { void** p = mBuffer; mpBegin = p; mpEnd = p; p += 16; mpCapacity = p; mAlloc[2] = 0; } };
struct EntryVec4  { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[3]; void* mBuffer[4];
    void init() { void** p = mBuffer; mpBegin = p; mpEnd = p; p += 4; mpCapacity = p; mAlloc[2] = 0; } };

struct Entry {
    uint32_t mKey;                                    // +0x000
    uint32_t mPad04[7];                               // +0x004
    PropRecord rec;                                   // +0x020
    uint8_t  mB7D4;                                   // +0x7d4
    uint8_t  mDisabled;                               // +0x7d5
    uint16_t mPad7D6;                                 // +0x7d6
    int32_t  mState;                                  // +0x7d8
    int32_t  mBusy;                                   // +0x7dc
    EntryVec32  mCreatures;                           // +0x7e0
    EntryVec16P mA878;                                // +0x878
    EntryVec16  mSounds;                              // +0x8d4
    EntryVec4   mFx;                                  // +0x92c

    Entry* init();                                    // 0x00bc4820
};
typedef char chk_entry[(sizeof(Entry) == 0x954) ? 1 : -1];

struct Node {
    Node* mpNext;                                     // +0x00
    Node* mpPrev;                                     // +0x04
    Entry mEntry;                                     // +0x08
};

// external creature/locomotive/planet types
struct Loco {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual float GetScale();                         // +0x74
};
struct Creature {
    virtual void v0();
    virtual void Release();                           // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
    virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46();
    virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53();
    virtual void SetFacing(const void* q);            // +0xd8 (0x36*4)
    virtual void SetPos(const void* v);               // +0xdc
    virtual void v56();
    virtual void SetCurrentPose(const void* v);       // +0xe4
    virtual void v58(); virtual void v59();
    virtual void SetMotion(const void* v);            // +0xec
    uint32_t mPad04[0x2f];                            // +0x04 .. +0xbf
    Loco loco;                                        // +0xc0
    void MoveToPointAndFacingAtSpeed(int mode, const Vector3* pos, const Vector3* facing,
                                     float speed, float scale);  // 0x00c1c5c0
};
void* __cdecl PlanetSnapB(void* out, Vector3* in, int flag);        // 0x00b82970
void* __cdecl PlanetBuildSurface(void* out, Vector3* pos, Vector3* up); // 0x00b7f250

Vector3* __stdcall BuildOffset(void* out, Entry* e, const float* vec2, float scale); // 0x00bc3c20
Vector3* __cdecl normalized_safe(void* scratch, const Vector3* v);   // 0x00449c20
void* __cdecl QuatMulVec3(void* out, const void* q, const Vector3* v); // 0x0059aed0
void __cdecl SetSkinFlag(Entry* e, int on);        // 0x00c0d950
void __cdecl E1C7F0(Creature** ref);                  // 0x00e1c7f0

// the registry object
struct FixedAlloc {
    bool __thiscall AddCore(void* block, unsigned flags);   // 0x00926650
};

struct Reg {
    uint32_t mPad00[6];                               // +0x00
    Node*    mpFree;                                  // +0x18
    Node     mSentinel;                               // +0x1c

    void resetEntry(Entry* e);                        // 0x00bc4bf0
    void resetAll();                                  // 0x00bc4d60
    void resetByKey(uint32_t key);                    // 0x00bc5040
    void enable(uint32_t key, Creature* c);           // 0x00bc52a0
    int  tryMove(Creature* c, Creature* dest, int flag); // 0x00bc4900
    Node* newNode();                                  // 0x00bc51c0
    void teardown();                                  // 0x00bc53f0
};

// two vector<PropRecord> containers with different member offsets
struct PropVecA {
    PropRecord* mpBegin;                              // +0
    PropRecord* mpEnd;                                // +4
    PropRecord* mpCapacity;                           // +8
    void destroy();                                   // 0x00bc5210
};
struct PropVecB {
    uint32_t mTag;                                    // +0
    PropRecord* mpBegin;                              // +4
    PropRecord* mpEnd;                                // +8
    PropRecord* mpCapacity;                           // +0xc
    void destroy();                                   // 0x00bc5300

    // vector<Elem98> member ops share this TU's fixed_vector<Elem98,8>
};

struct ElemVec : fixed_vector<Elem98, 8> {
    ElemVec* assign(const ElemVec& src);               // 0x00bc5070
    void insert(Elem98* pos, unsigned n, const Elem98* val); // 0x00bc4df0
    void resize(unsigned n);                           // 0x00bc5340
    Elem98* erase(Elem98* first, Elem98* last);        // 0x00bc5250
};

// =========================================================================================
// PropRecord
// =========================================================================================

void PropRecord::init()
{
    uint32_t zero = 0;
    mIndices.init();
    mIndices.mAllocator[2] = zero;
    mVec2A.init();
    mVec2A.mAllocator[2] = zero;
    mAngles.init();
    mAngles.mAllocator[2] = zero;
    mFlags.init();
    mFlags.mAllocator[2] = zero;
    mVec3.init();
    mVec3.mAllocator[2] = zero;
    mVec2B.init();
    mVec2B.mAllocator[2] = zero;
    mLists.init();
    mLists.mAllocator[2] = zero;
    mName.mpBegin = mName.mpBuffer = mName.mBuffer;
    mName.mpEnd = mName.mBuffer;
    mName.mpCapacity = mName.mBuffer + 32;
    mName.mBuffer[0] = 0;
}

// @ 0x00bc4730
void PropRecord::destroy()
{
    char* begin = mName.mpBegin;
    if ((mName.mpCapacity - begin) > 1 && begin != 0 && begin != mName.mpBuffer)
        operator_delete__(begin);

    ElemVecOps* lv = (ElemVecOps*)&mLists;
    lv->destroyRange(lv->mpBegin, lv->mpEnd);
    freeBuf(lv->mpBegin);
    freeBuf(mVec2B.mpBegin);
    freeBuf(mVec3.mpBegin);
    freeBuf(mFlags.mpBegin);
    freeBuf(mAngles.mpBegin);
    freeBuf(mVec2A.mpBegin);
    freeBuf(mIndices.mpBegin);
}

// @ 0x00bc54f0
void PropRecord::copyFrom(const PropRecord& src)
{
    mValue0 = src.mValue0;
    mCount = src.mCount;

    mIndices.init();
    mIndices = *(const fixed_vector<uint32_t, 8>*)&src.mIndices;

    mVec2A.init();
    mVec2A = *(const fixed_vector<Vector2, 32>*)&src.mVec2A;

    mAngles.init();
    mAngles = *(const fixed_vector<float, 32>*)&src.mAngles;

    mFlags.init();
    mFlags = *(const fixed_vector<uint8_t, 32>*)&src.mFlags;

    mVec3.init();
    mVec3 = *(const fixed_vector<Vector3, 2>*)&src.mVec3;

    mVec2B.init();
    mVec2B = *(const fixed_vector<Vector2, 2>*)&src.mVec2B;

    mLists.init();
    mLists = *(const fixed_vector<Elem98, 8>*)&src.mLists;

    mName.mpBegin = mName.mpBuffer = mName.mBuffer;
    mName.mpEnd = mName.mBuffer;
    mName.mpCapacity = mName.mBuffer + 32;
    mName.mBuffer[0] = 0;
    {
        const char* first = src.mName.mpBegin;
        size_t n = (size_t)(src.mName.mpEnd - first);
        if ((size_t)(mName.mpCapacity - mName.mpBegin) < n) {
            char* buf = (char*)operator_new((unsigned)(n + 1), kSimulator, 0, 0, kAllocFile, 0xd1);
            mName.mpBegin = mName.mpEnd = buf;
            mName.mpCapacity = buf + n + 1;
        }
        memcpy(mName.mpBegin, first, n);
        mName.mpBegin[n] = 0;
        mName.mpEnd = mName.mpBegin + n;
    }

    mF78C = src.mF78C;
    mF790 = src.mF790;
    mU794 = src.mU794;
    mU798 = src.mU798;
    mB79C = src.mB79C;
    mB79D = src.mB79D;
    mU7A0 = src.mU7A0;
    mU7A4 = src.mU7A4;
    mU7A8 = src.mU7A8;
    mBitMask = src.mBitMask;
    mFourCC = src.mFourCC;
}

// =========================================================================================
// Entry
// =========================================================================================

// @ 0x00bc4820
Entry* Entry::init()
{
    rec.init();
    mCreatures.init();
    mA878.init();
    mSounds.init();
    mFx.init();
    return this;
}

// =========================================================================================
// Elem98 fixed_vector<Elem98,8>
// =========================================================================================

void Elem98::assign(const Elem98& src)
{
    if (&src == this)
        return;
    Quad16* first = src.mpBegin;
    size_t n = (size_t)(src.mpEnd - first);
    size_t cap = (size_t)(mpCapacity - mpBegin);
    if (n > cap) {
        Quad16* buf = (Quad16*)ElemVecAllocN((unsigned)n, 0, 0);
        freeBuf(mpBegin);
        mpBegin = buf;
        mpEnd = buf + n;
        mpCapacity = buf + n;
        memcpy(buf, first, n * sizeof(Quad16));
        return;
    }
    size_t cur = (size_t)(mpEnd - mpBegin);
    if (cur < n) {
        memcpy(mpBegin, first, cur * sizeof(Quad16));
        memcpy(mpEnd, first + cur, (n - cur) * sizeof(Quad16));
        mpEnd = mpBegin + n;
    } else {
        memcpy(mpBegin, first, n * sizeof(Quad16));
        mpEnd = mpBegin + n;
    }
}

void ElemVecOps::destroyRange(Elem98* first, Elem98* last)
{
    while (first < last) {
        freeBuf(first->mpBegin);
        ++first;
    }
}

// @ 0x00bc4df0
void ElemVec::insert(Elem98* pos, unsigned n, const Elem98* val)
{
    if (n == 0)
        return;
    if (n > capacity() - size()) {
        unsigned oldSize = size();
        unsigned len = oldSize + n;
        unsigned cap = oldSize * 2;
        if (oldSize == 0)
            cap = 1;
        if (cap < len)
            cap = len;
        Elem98* newBuf;
        if (cap != 0)
            newBuf = (Elem98*)operator_new(cap * 0x98, kSimulator, 0, 0, kAllocFile, 0xd1);
        else
            newBuf = 0;
        Elem98* mid = ElemVecCopyConstruct(mpBegin, pos, newBuf);
        ElemVecFreeN(mpBegin, pos, newBuf);
        ElemVecFillN(mid, n, val);
        Elem98* after = mid + n;
        Elem98* tail = ElemVecCopyConstruct(pos, mpEnd, after);
        ElemVecFreeN(pos, mpEnd, after);
        freeBuf(mpBegin);
        mpEnd = tail;
        mpBegin = newBuf;
        mpCapacity = newBuf + cap;
        return;
    }

    Elem98 tmp;
    tmp.init();
    tmp.assign(*val);
    unsigned tailCount = (unsigned)(mpEnd - pos);
    if (n < tailCount) {
        Elem98* first = mpEnd - n;
        void* sret;
        ElemVecInsertCopy(&sret, first, mpEnd, mpEnd);
        mpEnd = mpEnd + n;
        ElemVecCopyBack(pos, first, mpEnd);
        ElemVecFillRange(pos, pos + n, &tmp);
    } else {
        ElemVecFillN(mpEnd, n - tailCount, &tmp);
        mpEnd = mpEnd + (n - tailCount);
        Elem98* mid = mpEnd - (n - tailCount);
        void* sret;
        ElemVecInsertCopy(&sret, pos, mid, mpEnd);
        mpEnd = mpEnd + tailCount;
        ElemVecFillRange(pos, mid, &tmp);
    }
    freeBuf(tmp.mpBegin);
}

// @ 0x00bc5070
ElemVec* ElemVec::assign(const ElemVec& src)
{
    if (this == &src)
        return this;
    Elem98* sfirst = src.mpBegin;
    unsigned n = (unsigned)(src.mpEnd - sfirst);
    if (n > capacity()) {
        Elem98* newBuf = ElemVecAllocN(n, sfirst, src.mpEnd);
        ElemVecOps* self = (ElemVecOps*)this;
        self->destroyRange(mpBegin, mpEnd);
        freeBuf(mpBegin);
        mpBegin = newBuf;
        mpEnd = newBuf + n;
        mpCapacity = newBuf + n;
        return this;
    }
    unsigned cur = size();
    if (cur < n) {
        ElemVecAssignRange(mpBegin, sfirst + cur, sfirst);
        mpEnd = mpBegin + (n - cur);
        ElemVecInsertCopy(0, sfirst + cur, src.mpEnd, mpEnd);
        mpEnd = mpEnd + cur;
        ElemVecFillRange(mpBegin, sfirst + cur, sfirst);
    } else {
        ElemVec* r = (ElemVec*)ElemVecAssignRange(mpBegin, sfirst + n, sfirst);
        ElemVecOps* self = (ElemVecOps*)this;
        self->destroyRange((Elem98*)r, mpEnd);
        mpEnd = mpBegin + n;
    }
    return this;
}

// @ 0x00bc5250
Elem98* ElemVec::erase(Elem98* first, Elem98* last)
{
    if (first != last)
        ElemVecCopyBack(last, mpEnd, first);
    mpEnd = mpEnd - (last - first);
    return first;
}

// @ 0x00bc5340
void ElemVec::resize(unsigned n)
{
    if (n > size()) {
        Elem98 tmp;
        tmp.init();
        insert(mpEnd, n - size(), &tmp);
        freeBuf(tmp.mpBegin);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// =========================================================================================
// Reg
// =========================================================================================

// @ 0x00bc4bf0
void Reg::resetEntry(Entry* e)
{
    for (void** p = e->mSounds.mpBegin; p < e->mSounds.mpEnd; ++p) {
        void* sys = GetAudioSystem();
        if (sys) {
            (*(void (__thiscall**)(void*, int))**(void***)sys)(sys, 0x347536b);
            (*(void (__thiscall**)(void*, int, void*))((*(void***)sys)[0x10]))(sys, 0x3475385, *p);
            (*(void (__thiscall**)(void*, int, int))((*(void***)sys)[0x10]))(sys, 0x34753a0, 0);
            (*(void (__thiscall**)(void*))((*(void***)sys)[0x16]))(sys);
        }
    }
    for (void** p = e->mFx.mpBegin; p < e->mFx.mpEnd; ++p) {
        if (*p)
            (*(void (__thiscall**)(void*, int))**(void***)*p)(*p, 1);
    }
    void** rEnd = e->mFx.mpEnd;
    void** r = VectorErasePtr(rEnd, rEnd, e->mFx.mpBegin);
    for (; r < e->mFx.mpEnd; ++r) {
        if (*r)
            (*(void (__thiscall**)(void*))((*(void***)*r)[1]))(*r);
    }
    e->mFx.mpEnd = e->mFx.mpBegin;

    e->mDisabled = 1;

    void** cEnd = e->mCreatures.mpEnd;
    void** c = VectorCopyPtr(cEnd, cEnd, e->mCreatures.mpBegin);
    for (; c < e->mCreatures.mpEnd; ++c) {
        if (*c)
            (*(void (__thiscall**)(void*))((*(void***)*c)[1]))(*c);
    }
    e->mCreatures.mpEnd = e->mCreatures.mpBegin;
}

// @ 0x00bc4d60
void Reg::resetAll()
{
    Node* end = &mSentinel;
    for (Node* n = mSentinel.mpNext; n != end; n = n->mpNext)
        resetEntry(&n->mEntry);
}

// @ 0x00bc5040
void Reg::resetByKey(uint32_t key)
{
    for (Node* n = mSentinel.mpNext; n != &mSentinel; n = n->mpNext) {
        if (n->mEntry.mKey == key) {
            resetEntry(&n->mEntry);
            return;
        }
    }
}

// @ 0x00bc52a0
void Reg::enable(uint32_t key, Creature* c)
{
    Node* end = &mSentinel;
    for (Node* n = mSentinel.mpNext; n != end; n = n->mpNext) {
        if (n->mEntry.mKey != key)
            continue;
        void** first = n->mEntry.mCreatures.mpBegin;
        void** last = n->mEntry.mCreatures.mpEnd;
        bool found = false;
        for (void** p = first; p != last; ++p) {
            if (*p == c) {
                found = true;
                break;
            }
        }
        if (found) {
            ++n->mEntry.mBusy;
            resetByKey(key);
        }
        return;
    }
}

// @ 0x00bc51c0
Node* Reg::newNode()
{
    char* p;
    for (;;) {
        if (mpFree) {
            p = (char*)mpFree;
            mpFree = mpFree->mpNext;
            break;
        }
        if (!((FixedAlloc*)((char*)this + 8))->AddCore(0, 0))
            p = 0;
        else
            continue;
        break;
    }
    Node* node = (Node*)(p + 8);
    node->mEntry.init();
    node->mpNext = (Node*)this;
    node->mpPrev = *(Node**)((char*)this + 4);
    node->mpPrev->mpNext = node;
    *(Node**)((char*)this + 4) = node;
    return node;
}

// @ 0x00bc53f0
void Reg::teardown()
{
    Node* end = &mSentinel;
    Node* n = mSentinel.mpNext;
    while (n != end) {
        Node* next = n->mpNext;
        Entry* e = &n->mEntry;
        for (void** p = e->mFx.mpBegin; p < e->mFx.mpEnd; ++p) {
            if (*p)
                (*(void (__thiscall**)(void*))((*(void***)*p)[1]))(*p);
        }
        freeBuf(e->mFx.mpBegin);
        freeBuf(e->mSounds.mpBegin);
        freeBuf(e->mA878.mpBegin);
        for (void** p = e->mCreatures.mpBegin; p < e->mCreatures.mpEnd; ++p) {
            if (*p)
                (*(void (__thiscall**)(void*))((*(void***)*p)[1]))(*p);
        }
        freeBuf(e->mCreatures.mpBegin);
        e->rec.destroy();
        n->mpNext = mpFree;
        mpFree = n;
        n = next;
    }
}

// @ 0x00bc4900
int Reg::tryMove(Creature* c, Creature* dest, int flag)
{
    Node* end = &mSentinel;
    Node* node = mSentinel.mpNext;
    while (node != end) {
        if ((Creature*)node->mEntry.mKey == c)
            break;
        node = node->mpNext;
    }
    if (node == end)
        return 0;
    Entry* e = &node->mEntry;
    if (e->mDisabled)
        return 0;
    if (e->mBusy == 0)
        return 0;

    int i = (int)(e->mCreatures.mpEnd - e->mCreatures.mpBegin);
    if (dest) {
        (*(void (__thiscall**)(Creature*))**(void***)dest)(dest);
    }
    E1C7F0(&dest);
    if (dest)
        (*(void (__thiscall**)(Creature*))((*(void***)dest)[1]))(dest);

    float* mv = (float*)&e->rec.mVec2A.mpBegin[i];
    Vector2 v2;
    v2.x = mv[0];
    v2.y = mv[1];

    float scale = dest->loco.GetScale();
    Vector3 off;
    Vector3* o = BuildOffset(&off, e, (const float*)&v2, scale);
    Vector3 pos;
    pos.x = o->x; pos.y = o->y; pos.z = o->z;

    float angle = e->rec.mAngles.mpBegin[i];
    Vector3 facing;
    if (e->rec.mValue0 == 1) {
        facing.x = e->rec.mVec3.mpBegin[0].x;
        facing.y = e->rec.mVec3.mpBegin[0].y;
        facing.z = e->rec.mVec3.mpBegin[0].z;
    } else {
        Vector3* sn = (Vector3*)PlanetSnapB(0, &e->rec.mVec3.mpBegin[0], 0);
        Vector3 d;
        d.x = sn->x - pos.x;
        d.y = sn->y - pos.y;
        d.z = sn->z - pos.z;
        facing = *normalized_safe(0, &d);
    }
    if (angle != 0.0f) {
        Vector3* n = normalized_safe(0, &pos);
        float s = sinf(angle * 0.5f);
        float c = cosf(angle * 0.5f);
        float q[4];
        q[0] = n->x * s;
        q[1] = n->y * s;
        q[2] = n->z * s;
        q[3] = c;
        facing = *(Vector3*)QuatMulVec3(0, q, &facing);
    }
    if (e->rec.mFlags.mpBegin[i] == 1) {
        (*(void (__thiscall**)(Creature*, void*))((*(void***)dest)[0x39]))(dest, (char*)this + 0x68);
        SetSkinFlag(e, 1);
    }
    if (flag == 0) {
        dest->MoveToPointAndFacingAtSpeed(2, &pos, &facing, 0.1f, scale);
        --e->mBusy;
        return 1;
    }
    void* op = PlanetBuildSurface(0, &pos, &facing);
    dest->SetFacing(op);
    --e->mBusy;
    return 1;
}

// @ 0x00bc5210
void PropVecA::destroy()
{
    PropRecord* p = mpBegin;
    PropRecord* last = mpEnd;
    while (p < last) {
        p->destroy();
        p = (PropRecord*)((char*)p + 0x7b4);
    }
    freeBuf(mpBegin);
}

// @ 0x00bc5300
void PropVecB::destroy()
{
    PropRecord* p = mpBegin;
    PropRecord* last = mpEnd;
    while (p < last) {
        p->destroy();
        p = (PropRecord*)((char*)p + 0x7b4);
    }
    freeBuf(mpBegin);
}
