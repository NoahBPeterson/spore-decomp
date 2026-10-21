// Slice s00f63a50 (batch gold4, slice 8) -- SP::cTerrainDistributeDescription / SP::cDistGrid
//   0x00f63a50  SP::cTerrainDistributeDescription::operator=
//   0x00f63ab0  eastl vector<Quad16> resize helper (cTDDDistGroups)
//   0x00f63b40  SP::cTerrainDistributeEffectCommand::Execute
//   0x00f63bf0  SP::cTerrainDistributeDescription::Read (serializer)
//   0x00f63d00  SP::ReadDescription
//   0x00f63da0  SP::cDistGrid::CellIndex
//   0x00f63e10  SP::AngleToCos helper
//   0x00f63eb0  SP::cDistGrid::Init
//   0x00f64180  SP::cDistGrid::SetTerrainMapSet
//   0x00f64230  SP::cDistGrid::~cDistGrid
//   0x00f64270  SP::cTerrainDistributeEffect::SetIsVisible
// Object file: SPTerrain/SPTerrainDistributeDescription.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
#include "game/types.h"
#include <math.h>

namespace EA {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    AutoRefCount& operator=(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}

namespace SP {
using EA::AutoRefCount;

extern const float kFXMaxFloat;     // 0x015b0cb0

struct cCellEffectInfo {            // 0x10
    int   mEffectIndex;             // +0x0
    float mMinHeight;               // +0x4
    float mMaxHeight;               // +0x8
    char  mDistributeType;          // +0xc
    char  mResourceType;            // +0xd
    unsigned char mOverrideSet;     // +0xe

    cCellEffectInfo()
        : mEffectIndex(-1), mMinHeight(0.0f), mMaxHeight(kFXMaxFloat),
          mDistributeType((char)0xff), mResourceType((char)0xff), mOverrideSet(0) {}
};

// eastl::copy for cCellEffectInfo (0x00705250); returns the new dest end.
extern "C" cCellEffectInfo* __cdecl eastl_copy(const cCellEffectInfo* first,
                                               const cCellEffectInfo* last,
                                               cCellEffectInfo* dst);

// eastl::vector<cCellEffectInfo> with sp allocator (0x14 bytes)
struct EffectVector {
    cCellEffectInfo* mpBegin;       // +0x0
    cCellEffectInfo* mpEnd;         // +0x4
    cCellEffectInfo* mpCapacity;    // +0x8
    int mAllocator[2];              // +0xc

    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }

    EffectVector& operator=(const EffectVector& rhs);   // 0x00f63570
    void DoInsertValues(cCellEffectInfo* pos, unsigned n, const cCellEffectInfo& v); // 0x0088fe00
    void resize(unsigned n);                            // 0x00f63ab0

    cCellEffectInfo* erase(cCellEffectInfo* first, cCellEffectInfo* last)
    {
        eastl_copy(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }

    void resize_inline(unsigned n)
    {
        if (n > size())
            DoInsertValues(mpEnd, n - size(), cCellEffectInfo());
        else
            erase(mpBegin + n, mpEnd);
    }
};

struct cLevelInfo {                 // 0x28 (retail; the 2008 PDB says 0x20)
    float mActiveDist;              // +0x0
    float mChildActiveDist;         // +0x4
    float mActiveFacing;            // +0x8
    float mChildActiveFacing;       // +0xc
    float mExtra;                   // +0x10
    EffectVector mEffectInfo;       // +0x14

    cLevelInfo& operator=(const cLevelInfo& rhs)
    {
        mActiveDist = rhs.mActiveDist;
        mChildActiveDist = rhs.mChildActiveDist;
        mActiveFacing = rhs.mActiveFacing;
        mChildActiveFacing = rhs.mChildActiveFacing;
        mExtra = rhs.mExtra;
        mEffectInfo = rhs.mEffectInfo;
        return *this;
    }
};

struct Quad16 { uint32_t m[4]; };

struct cDistLevelVector {           // eastl::vector<Quad16, sp_allocator>
    Quad16* mpBegin;                // +0x0
    Quad16* mpEnd;                  // +0x4
    Quad16* mpCapacity;             // +0x8
    int mAllocator[2];              // +0xc

    void resizeAdd(unsigned n);     // 0x00f63ab0
};

struct cTerrainDistributeDescription {   // 0xd4
    int   mVtbl;                    // +0x0
    int   mPad4;                    // +0x4
    int   mFlags;                   // +0x8  eastl::bitset<3>
    cLevelInfo mLevelInfo[5];       // +0xc .. +0xd4

    cTerrainDistributeDescription();                             // 0x00f63000
    ~cTerrainDistributeDescription();                            // 0x00f62e60
    cTerrainDistributeDescription& operator=(const cTerrainDistributeDescription& rhs);
    void ReadDescription2(void* reader, int one, int myFlags);   // 0x00f63bf0
    void Read(void* reader, int one, int myFlags);              // 0x00f63d00
};

struct cCell {                      // 0x18
    unsigned short mMinHeight;      // +0x0
    unsigned short mMaxHeight;      // +0x2
    unsigned short mTypeMask;       // +0x4
    short mActiveSlot;              // +0x6
    short mActiveChildren;          // +0x8
    float mDirX, mDirY, mDirZ;      // +0xc
};

struct cArguments;

// cHeightRanges-style view used by CellIndex (offsets differ from cDistGrid: face size at +0,
// level offsets at +4, the cell base at +0x18).
struct cHeightRanges {
    int mFaceSize;                      // +0x00
    int mLevelOffsets[5];               // +0x04
    int* mCellData;                     // +0x18
};

// cTerrainDistributeInfo, viewed as the cHeightRanges producer (slice s00f65070)
struct cTerrainDistributeInfo {
    int mFaceSize;                      // +0x00
    int mLevelOffsets[5];               // +0x04
    cCell* mCellData;                   // +0x18
};

// cTerrainDistributeEffect (spatial layout for SetIsVisible)
struct cTerrainDistributeEffect {
    int mVtbl;                          // +0x0
    int mPad4;                          // +0x4
    int mPad8;                          // +0x8
    cTerrainDistributeDescription* mDesc;// +0xc
    int mCollectionIndex;               // +0x10
    void* mGlobalParams;                // +0x14
    void* mChildParams;                 // +0x18
    void* mTerrainSphere;               // +0x1c
    void* mDistGrid;                    // +0x20
    uint32_t mFlags;                    // +0x24
    void SetIsVisible(char visible);
};

// cDistGrid (see slice s00f65070 for the full definition of the same object)
struct cDistGrid {                      // 0x108+
    void* mWorld;                       // +0x00
    int   mCollectionIndex;             // +0x04
    int   mFaceSize;                    // +0x08
    cLevelInfo* mLevelInfo;             // +0x0c
    int   mLevelOffsets[5];             // +0x10
    cCell* mCellData;                   // +0x24
    void* mTerrainMapSet;               // +0x28
    float mHeightBase;                  // +0x2c
    float mHeightRange16;               // +0x30
    void* mActiveCellSlots[8];          // +0x34 (slot_deque, 0x24 bytes) ... +0x54
    void* mSlots[8];                    // +0x54
    float mDistInfo0;                   // +0x74
    float mDistInfo1;                   // +0x78
    cTerrainDistributeInfo* mDistInfo;  // +0xa0
    uint32_t mPadA4;                    // +0xa4

    void Init(cLevelInfo* level, int collectionIndex);
    void SetTerrainMapSet(void* mapset);
    void ReleaseSlots();
    int* CellIndex(int level, int face, unsigned char a, unsigned char b);
};
}  // namespace SP

using namespace SP;

// ---- external helpers (addresses in comments) ----
void __cdecl io_ReadInt32(void* reader, void* dst, int n, int flag);   // 0x0093a780
void __cdecl io_ReadUint8(void* reader, void* dst, int flag);          // 0x0093a6c0
void __cdecl SP_ReadLevel(void* reader, int count, cLevelInfo* level); // 0x00f63bf0
void __fastcall SP_DistGrid_ReleaseSlots(void* self);                   // 0x00f64230

struct cArgScriptArgs;                                   // EA::ArgScript::cArguments

// EA::ArgScript::cArguments::MainArguments (0x00838020)
struct cArgMain {
    static const char** __thiscall MainArguments(cArgScriptArgs* self, int* count, int a, int b);
};
// EA::Swarm::cEffectsParser::GetInheritedDescription (0x00a6f090)
struct cParserInherit {
    void* __thiscall GetInheritedDescription(int* args, int count, int id);
};
struct cEffectString {                                    // eastl::string at +0x114
    const char* mpBegin;                                  // +0x0
    const char* mpEnd;                                    // +0x4
    const char* mpCapacity;                               // +0x8
    void assign(const char* first, const char* last);     // 0x00454cb0
};


struct cEffectCommand {                                   // 0x118 bytes used; "this" of Execute
    int mVtbl;                                            // +0x0
    int* mOuter;                                          // +0x4  (object whose vtable+0x8c is called)
    uint32_t mPad08[10];                                  // +0x8 .. +0x2f
    cParserInherit* mParser;                              // +0x30
    uint32_t mPad34[1];                                   // +0x34
    cTerrainDistributeDescription mDesc;                  // +0x38 .. +0x10b
    int mDebugLevel;                                      // +0x10c
    uint32_t mPad110;                                     // +0x110
    cEffectString mString;                                // +0x114

    void Execute(cArgScriptArgs* args);
};

// EA refcounted base: refcount at +0x4, AddRef/Release non-virtual (the refcount block is
// open-coded at each call site as seen at 0x00f64180); vtable slot 0 is the destructor.
struct cRefCounted {                                      // non-virtual AddRef/Release
    int mVtbl;                                            // +0x0
    int mRefCount;                                        // +0x4
    void AddRef() { ++mRefCount; }
    void Release()
    {
        if (--mRefCount == 0) {
            mRefCount = 1;
            (*(void(__thiscall**)(void*, int))mVtbl)(this, 1);
        }
    }
};

struct cTerrainMapSet : cRefCounted {};

// cTerrainMapSet's real payload: mpObject at +0, whose mHeightRanges sits at +0x58.
struct cTerrainMapSetObject {
    cHeightRanges* mHeightRanges;          // +0x58
};
struct cTerrainMapSetView {
    cTerrainMapSetObject* mpObject;        // +0x0
};

// Effects manager (0x0067ddd0): vtable slot 0x54 returns the world for a given id.
struct cEffectsManager {
    int mVtbl;                             // +0
};
cEffectsManager* __cdecl EffectsManager();

// ---- external data (addresses in comments) ----
extern const uint8_t g_swizzle[16];                    // 0x01491464
extern const float   g_half;                            // 0x01485720  (1.0f)
extern const float   g_one;                             // 0x01471064  (0.5f)
extern const float   g_two;                             // 0x01470f1c  (2.0f)
extern const float   g_signMask;                        // 0x013eb8b0  (-0.0f)
extern const int     g_faceMap[16];                     // 0x0148f44c
extern const float   g_inv32768;                        // 0x0148f474  (3.0517578125e-05)
extern const float   g_angleK1;                         // 0x015b0cc4
extern const float   g_angleK2;                         // 0x013f1168  (1e-10f)
extern const float   g_angleK3;                         // 0x1457910   (0.9817f)
extern const float   g_angleK4;                         // 0x145790c   (0.1963f)
extern const float   g_angleZero;                       // 0x1485378
extern const float   g_angleThree;                      // 0x013eb95c  (3.0f)

// @ 0x00f63a50
cTerrainDistributeDescription& SP::cTerrainDistributeDescription::operator=(
    const cTerrainDistributeDescription& rhs)
{
    mFlags = rhs.mFlags;
    for (int i = 0; i < 5; i++)
        mLevelInfo[i] = rhs.mLevelInfo[i];
    return *this;
}

// @ 0x00f63ab0
void SP::EffectVector::resize(unsigned n)
{
    if (n > size())
        DoInsertValues(mpEnd, n - size(), cCellEffectInfo());
    else
        erase(mpBegin + n, mpEnd);
}

// @ 0x00f64270
void SP::cTerrainDistributeEffect::SetIsVisible(char visible)
{
    if (visible == 0)
        mDistGrid = (void*)((uint32_t)mDistGrid | 2);
    else
        mDistGrid = (void*)((uint32_t)mDistGrid & 0xfffffffd);
}

// @ 0x00f63bf0
void __cdecl SP_ReadLevel(void* reader, int count, cLevelInfo* level)
{
    io_ReadInt32(reader, &level->mActiveDist, 1, 0);
    io_ReadInt32(reader, &level->mChildActiveDist, 1, 0);
    if (count >= 2)
        io_ReadInt32(reader, &level->mActiveFacing, 1, 0);
    io_ReadInt32(reader, &level->mChildActiveFacing, 1, 0);
    io_ReadInt32(reader, &level->mExtra, 1, 0);
    unsigned n;
    io_ReadInt32(reader, &n, 1, 0);
    level->mEffectInfo.resize(n);
    int total = (int)(level->mEffectInfo.mpEnd - level->mEffectInfo.mpBegin);
    if (total > 0) {
        int off = 0;
        do {
            io_ReadInt32(reader, (char*)level->mEffectInfo.mpBegin + off, 1, 0);
            io_ReadInt32(reader, (char*)level->mEffectInfo.mpBegin + off + 4, 1, 0);
            io_ReadInt32(reader, (char*)level->mEffectInfo.mpBegin + off + 8, 1, 0);
            io_ReadUint8(reader, (char*)level->mEffectInfo.mpBegin + off + 0xc, 1);
            io_ReadUint8(reader, (char*)level->mEffectInfo.mpBegin + off + 0xd, 1);
            io_ReadUint8(reader, (char*)level->mEffectInfo.mpBegin + off + 0xe, 1);
            off += 16;
        } while (--total);
    }
}

// @ 0x00f63b40
void cEffectCommand::Execute(cArgScriptArgs* args)
{
    int count;
    const char** argv = cArgMain::MainArguments(args, &count, 1, 3);

    const char* p = argv[0];
    const char* q = p;
    while (*q)
        ++q;
    mString.assign(p, q);

    mDesc = cTerrainDistributeDescription();
    if (count > 1) {
        void* inherited = mParser->GetInheritedDescription((int*)argv, count, 0x2a);
        if (inherited)
            mDesc = *(cTerrainDistributeDescription*)inherited;
    }
    mDebugLevel = 0;
    (*(void(__thiscall**)(void*, cEffectCommand*))(*(int*)mOuter + 0x8c))(mOuter, this);
}

// @ 0x00f63d00
void __cdecl SP_ReadDescription(void* reader, int count, cTerrainDistributeDescription* desc)
{
    unsigned local;
    io_ReadInt32(reader, &local, 1, 0);
    desc->mFlags = local & 7;
    cLevelInfo* level = desc->mLevelInfo;
    for (int i = 0; i < 5; i++) {
        SP_ReadLevel(reader, count, level);
        level = (cLevelInfo*)((char*)level + 0x28);
    }
}

// @ 0x00f64230
void SP::cDistGrid::ReleaseSlots()
{
    char* p = (char*)this + 0x58;
    int i = 7;
    do {
        char* slot = p;
        p = slot - 4;
        void* obj = *(void**)p;
        if (obj)
            (*(void(__thiscall**)(void*))(*(int*)obj + 4))(obj);
        i--;
    } while (i >= 0);
}

// @ 0x00f64180
void SP::cDistGrid::SetTerrainMapSet(void* mapset)
{
    cTerrainMapSet* set = (cTerrainMapSet*)mapset;
    if (set != mTerrainMapSet) {
        if (set)
            set->AddRef();
        cTerrainMapSet* old = (cTerrainMapSet*)mTerrainMapSet;
        mTerrainMapSet = set;
        if (old)
            old->Release();
    }
    float b = *((float*)set + 0xd);
    mHeightBase = b;
    float a = *((float*)set + 0xe);
    mHeightBase = b - a;
    mHeightRange16 = a * g_inv32768;
}

// @ 0x00f63da0
int* SP::cDistGrid::CellIndex(int level, int face, unsigned char a, unsigned char b)
{
    int t = g_swizzle[b >> 4] * 2 | g_swizzle[a >> 4];
    t = t << 7 | g_swizzle[b & 0xf];
    t = t << 1 | g_swizzle[a & 0xf];
    return ((cHeightRanges*)this)->mCellData +
           (t + ((cHeightRanges*)this)->mLevelOffsets[level] +
            ((cHeightRanges*)this)->mFaceSize * face);
}

// @ 0x00f63e10
double SP_AngleToCos(float a)
{
    float s = (float)sqrt((double)(1.0f - a * a));
    float f = (s - fabsf(a)) / (fabsf(a) + s + g_angleK2);
    f = (g_angleK3 - f * f * g_angleK4) * f;
    if (a >= 0.0f)
        return g_angleK1 + f;
    return g_angleK1 * g_angleThree - f;
}

// @ 0x00f63eb0
void SP::cDistGrid::Init(cLevelInfo* level, int collectionIndex)
{
    mLevelInfo = level;
    mCollectionIndex = collectionIndex;
    mPadA4 = 0;

    // mWorld = EffectsManager()->GetWorld(0x3fbae24), kept as a refcounted handle
    cRefCounted* mgr = (cRefCounted*)EffectsManager();
    void* newWorld = (*(void*(__thiscall**)(void*, int))mgr->mVtbl)(mgr, 0x3fbae24);
    void* oldWorld = mWorld;
    if (newWorld != oldWorld) {
        if (newWorld)
            (*(void(__thiscall**)(void*))(*(int*)newWorld))(newWorld);
        mWorld = newWorld;
        if (oldWorld)
            (*(void(__thiscall**)(void*))(*(int*)oldWorld + 4))(oldWorld);
    }

    cHeightRanges* ranges = ((cTerrainMapSetView*)mTerrainMapSet)->mpObject->mHeightRanges;

    int face = 0;
    do {
        int* cellOff = mLevelOffsets;
        int lvl = 0;
        int* rangeOff = &ranges->mFaceSize;   // walks the range's level-offset table
        do {
            rangeOff = (int*)ranges->mLevelOffsets;
            int n = 1 << lvl;
            int i = 0;
            if (n > 0) {
                int rowBase = (face >> 1) * 4;
                do {
                    float fy = (((float)i + 0.5f) * (1.0f / (float)n)) * 2.0f - 1.0f;
                    int j = 0;
                    do {
                        float fx = (((float)j + 0.5f) * (1.0f / (float)n)) * 2.0f - 1.0f;
                        float inv = 1.0f / (float)sqrt((fx * fx + fy * fy) + 1.0f);

                        unsigned t = ((unsigned)(unsigned char)g_swizzle[((unsigned)i & 0xff) >> 4] * 2
                                    | (unsigned)(unsigned char)g_swizzle[(j & 0xff) >> 4]);
                        t = t << 7 | (unsigned)(unsigned char)g_swizzle[i & 0xf];
                        t = t * 2 | (unsigned)(unsigned char)g_swizzle[j & 0xf];
                        cCell* cell = mCellData + (t + mFaceSize * face + *cellOff);

                        float sign = (face & 1) ? -inv : inv;
                        float vec[3];
                        vec[(unsigned char)g_faceMap[rowBase + 0]] = sign * fx;
                        vec[(unsigned char)g_faceMap[rowBase + 1]] = inv * fy;
                        vec[(unsigned char)g_faceMap[rowBase + 2]] = sign;
                        cell->mDirX = vec[0];
                        cell->mDirY = vec[1];
                        cell->mDirZ = vec[2];

                        unsigned a = ((unsigned)(unsigned char)g_swizzle[i >> 4] * 2
                                    | (unsigned)(unsigned char)g_swizzle[j >> 4]);
                        a = a << 7 | (unsigned)(unsigned char)g_swizzle[i & 0xf];
                        a = a * 2 | (unsigned)(unsigned char)g_swizzle[j & 0xf];
                        cCell* src = (cCell*)ranges->mCellData + (a + ranges->mFaceSize * face + *rangeOff);
                        cell->mMinHeight = src->mMinHeight;
                        cell->mMaxHeight = src->mMaxHeight;
                        cell->mTypeMask = 0x7fff;
                        cell->mActiveSlot = -1;
                        cell->mActiveChildren = 0;

                        ++j;
                    } while (j < n);
                    ++i;
                } while (i < n);
            }
            ++cellOff;
            ++lvl;
        } while (lvl < 5);
        ++face;
    } while (face < 6);
}
