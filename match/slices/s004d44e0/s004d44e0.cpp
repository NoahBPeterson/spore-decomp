// Slice s004d44e0: species database helpers (scale getter, id->index searches) and
// larger surrounding operations.  Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

struct SpeciesDB {
    char  pad0[0x5ac];
    float mScale;      // +0x5ac
    char  pad2[0x6d4 - 0x5b0];
    int   mVecBegin;   // +0x6d4
    int   mVecEnd;     // +0x6d8

    float GetScale();
    uint32_t FindField8(int id);
    uint32_t FindField10(int id);
};

// @ 0x004D46B0
float SpeciesDB::GetScale()
{
    return mScale * 0.025f * 100.0f;
}

// @ 0x004D46D0
uint32_t SpeciesDB::FindField8(int id)
{
    uint32_t i = 0;
    int* vec = (int*)((char*)this + 0x6d4);
    int n = (vec[1] - vec[0]) >> 2;
    for (; i < (uint32_t)n; i = i + 1) {
        int* slot = (int*)(mVecBegin + i * 4);
        int elem = *slot;
        if (*(int*)(elem + 8) == id)
            return i;
    }
    return 0xffffffff;
}

// @ 0x004D4750
uint32_t SpeciesDB::FindField10(int id)
{
    uint32_t i = 0;
    int* vec = (int*)((char*)this + 0x6d4);
    int n = (vec[1] - vec[0]) >> 2;
    for (; i < (uint32_t)n; i = i + 1) {
        int* slot = (int*)(mVecBegin + i * 4);
        int elem = *slot;
        if (*(int*)(elem + 0x10) == id)
            return i;
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// Larger neighbours: the container-heavy SpeciesDB destructor, the indexed
// field getter, the random field picker and the profile update helper.
// ---------------------------------------------------------------------------
struct ResKey {
    uint32_t mInstance;   // +0
    uint32_t mType;       // +4
    uint32_t mGroup;      // +8
};

struct HTableLayout {
    char pad[0x504];
    ~HTableLayout();                                          // 0x004e0a60
};

struct WStringLayout {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
    void* mpCap;     // +8
    void* mAlloc;    // +0xc
    ~WStringLayout();                                         // 0x004237d0
};

struct VAllocByte { char b; };

struct E4 { uint32_t m; ~E4() {} };
struct E56 { char pad[0x38]; ~E56() {} };
struct P4 { void* mp; ~P4(); };                               // 0x00453540

template <class T, int PAD>
struct SimpleVecT {
    T* mpBegin;      // +0
    T* mpEnd;        // +4
    T* mpCap;        // +8
    uint32_t mAlloc; // +0xc
    char pad[PAD];
    void Free();                                              // 0x00425990
    __forceinline ~SimpleVecT()
    {
        T* p;
        for (p = mpBegin; p < mpEnd; p = p + 1) {
        }
        Free();
    }
};

struct Vec56 {
    E56* mpBegin;    // +0
    E56* mpEnd;      // +4
    E56* mpCap;      // +8
    uint32_t mAlloc; // +0xc
    char pad[0xc];
    void Free();                                              // 0x00427440
    __forceinline ~Vec56()
    {
        E56* p;
        for (p = mpBegin; p < mpEnd; p = p + 1) {
        }
        Free();
    }
};

struct VecInt6d4 {
    int* mpBegin;    // +0
    int* mpEnd;      // +4
    int* mpCap;      // +8
    uint32_t mAlloc; // +0xc
    char pad[0x58];
    ~VecInt6d4();                                             // 0x00432d60
};

struct VecPtr73c {
    P4* mpBegin;     // +0
    P4* mpEnd;       // +4
    P4* mpCap;       // +8
    uint32_t mAlloc; // +0xc
    char pad[0x58];
    void DestroyRange(P4* first, P4* last);                   // 0x004e3210
    void Free();                                              // 0x00425990
    __forceinline ~VecPtr73c()
    {
        DestroyRange(mpBegin, mpEnd);
        Free();
    }
};

struct VSet {
    uint32_t* mpBegin;   // +0
    uint32_t* mpEnd;     // +4
    uint32_t* mpCap;     // +8
    uint32_t m0c;        // +0xc
    uint32_t m10;        // +0x10
    uint32_t m14;        // +0x14
    char mStorage[0x50]; // +0x18
    VSet(const VAllocByte& alloc);                            // 0x00540470
    void Init();                                              // 0x004e07d0
    void push_back(const uint32_t& v);                        // 0x00454860
    uint32_t* erase(uint32_t* first, uint32_t* last);         // 0x004769b0
    int size();                                               // 0x004746a0
    ~VSet();                                                  // 0x004e1bf0
};

struct RandomLCG {
    uint32_t RandomUint32Uniform(uint32_t n);                 // 0x00a68fb0
};
extern RandomLCG gRandom;                                     // 0x01601760

template <class T>
inline T& Max2(T& a, T& b)
{
    return a < b ? b : a;
}

inline bool IsOne(uint32_t v)
{
    return v == 1;
}

struct SpeciesDBLayout {
    HTableLayout mTable;                          // +0x000
    ResKey mKey504;                               // +0x504
    ResKey mKey510;                               // +0x510
    WStringLayout mStr51c;                        // +0x51c
    WStringLayout mStr52c;                        // +0x52c
    char pad53c[0x5ac - 0x53c];
    float mScale;                                 // +0x5ac
    char pad5b0[0x5d4 - 0x5b0];
    uint32_t mField5d4;                           // +0x5d4
    uint32_t mField5d8;                           // +0x5d8
    uint32_t mField5dc;                           // +0x5dc
    uint32_t mField5e0;                           // +0x5e0
    uint32_t mField5e4;                           // +0x5e4
    uint32_t mField5e8;                           // +0x5e8
    uint32_t mField5ec;                           // +0x5ec
    uint32_t mField5f0;                           // +0x5f0
    char pad5f4[0x614 - 0x5f4];
    int mField614;                                // +0x614
    char pad618[0x620 - 0x618];
    int mField620;                                // +0x620
    int mField624;                                // +0x624
    char pad628[0x644 - 0x628];
    float mField644;                              // +0x644
    char pad648[0x64c - 0x648];
    int mField64c;                                // +0x64c
    int mField650;                                // +0x650
    int mField654;                                // +0x654
    int mField658;                                // +0x658
    int mField65c;                                // +0x65c
    int mField660;                                // +0x660
    int mField664;                                // +0x664
    int mField668;                                // +0x668
    float mField66c;                              // +0x66c
    int mField670;                                // +0x670
    int mField674;                                // +0x674
    int mField678;                                // +0x678
    int mField67c;                                // +0x67c
    int mField680;                                // +0x680
    int mField684;                                // +0x684
    int mField688;                                // +0x688
    int mField68c;                                // +0x68c
    int mField690;                                // +0x690
    char pad694[0x698 - 0x694];
    int mField698;                                // +0x698
    int mField69c;                                // +0x69c
    int mField6a0;                                // +0x6a0
    int mField6a4;                                // +0x6a4
    int mField6a8;                                // +0x6a8
    int mField6ac;                                // +0x6ac
    char pad6b0[0x6b4 - 0x6b0];
    int mField6b4;                                // +0x6b4
    Vec56 mVec6b8;                                // +0x6b8
    VecInt6d4 mVec6d4;                            // +0x6d4
    VecPtr73c mVec73c;                            // +0x73c
    SimpleVecT<E4, 0x5c> mVec7a4;                 // +0x7a4
    SimpleVecT<E4, 0x58> mVec810;                 // +0x810
    SimpleVecT<E4, 0x58> mVec878;                 // +0x878
    SimpleVecT<E4, 0x58> mVec8e0;                 // +0x8e0
    SimpleVecT<E4, 0x58> mVec948;                 // +0x948
    SimpleVecT<E4, 0x58> mVec9b0;                 // +0x9b0

    ~SpeciesDBLayout();
    int GetField(int index);
    void PickRandomFields();
    bool Update(void* obj);                       // 0x004d5020
    bool Apply(const ResKey* key);
};

bool ComputeVerbIcons(const ResKey* key, void** out);         // 0x004bafc0
void InvalidEditorModelKey(ResKey* key, int flag);            // 0x0068c700

__forceinline void ReleaseObject(void* obj)
{
    (*(void (__thiscall**)(void*))(*(uint32_t*)obj + 4))(obj);
}// @ 0x004D44E0 SpeciesDBLayout::~SpeciesDBLayout
SpeciesDBLayout::~SpeciesDBLayout()
{
}

// @ 0x004D47D0
int SpeciesDBLayout::GetField(int index)
{
    switch (index) {
    case 0x1e: return mField5d4;
    case 0x1f: return mField5d8;
    case 0x20: return mField5dc;
    case 0x21: return mField5e0;
    case 0x22: return mField5e8;
    case 0x23: return mField5f0;
    case 0x24: return mField5ec;
    case 0x25: return mField5e4;
    case 0x3d: return mField64c;
    case 0x3e: return mField650;
    case 0x40: return mField654;
    case 0x41: return mField658;
    case 0x42: return mField65c;
    case 0x43: return mField660;
    case 0x44: return mField664;
    case 0x45: return mField668;
    case 0x46: return (uint32_t)mField66c;
    case 0x47: return mField670;
    case 0x48: return mField674;
    case 0x49: return mField678;
    case 0x4a: return mField67c;
    case 0x4b: return mField680;
    case 0x4c: return mField684;
    case 0x4d: return mField688;
    case 0x4e: return mField68c;
    case 0x4f: return mField690;
    case 0x50: return mField614;
    case 0x51: return mField698;
    case 0x52: return mField69c;
    case 0x53: return mField6a0;
    case 0x54: return mField6a4;
    case 0x55: return mField6a8;
    case 0x56: return mField6ac;
    case 0x57: return (uint32_t)mField644;
    default:   return 0;
    }
}

// @ 0x004D4AD0
void SpeciesDBLayout::PickRandomFields()
{
    uint32_t maxB;
    uint32_t maxA;
    {
    VAllocByte alloc;
    VSet vec(alloc);
    vec.Init();

    maxA = Max2(Max2(mField5e4, mField5e8), Max2(mField5ec, mField5f0));
    maxB = Max2(Max2(mField5d4, mField5d8), Max2(mField5dc, mField5e0));

    if (maxB > maxA)
        mField6b4 = 2;
    else if (maxA > maxB)
        mField6b4 = 1;

    if (mField5e8 == maxA) vec.push_back(0x22);
    if (mField5e4 == maxA) vec.push_back(0x25);
    if (mField5ec == maxA) vec.push_back(0x24);
    if (mField5f0 == maxA) vec.push_back(0x23);

    uint32_t n = (uint32_t)(vec.mpEnd - vec.mpBegin);
    uint32_t idx = gRandom.RandomUint32Uniform(n - 1);
    mField620 = vec.mpBegin[idx];
    vec.erase(vec.mpBegin, vec.mpEnd);

    if (mField5d4 == maxA) vec.push_back(0x1e);
    if (mField5dc == maxA) vec.push_back(0x20);
    if (mField5d8 == maxA) vec.push_back(0x1f);
    if (mField5e0 == maxA) vec.push_back(0x21);

    if ((uint32_t)(vec.mpEnd - vec.mpBegin) > 0) {
        uint32_t n2 = vec.size() - 1;
        uint32_t idx2 = gRandom.RandomUint32Uniform(n2);
        mField624 = vec.mpBegin[idx2];
    } else {
        mField624 = 0x1e;
    }
    }
}

// @ 0x004D4F10
bool SpeciesDBLayout::Apply(const ResKey* key)
{
    void* obj = 0;
    if (obj != 0) {
        void* old = obj;
        obj = 0;
        ReleaseObject(old);
    }

    if (!ComputeVerbIcons(key, &obj)) {
        bool failed = false;
        if (obj != 0)
            (*(void (__thiscall**)(void*))(*(uint32_t*)obj + 4))(obj);
        return failed;
    }

    mKey504 = *key;
    mKey510 = *key;
    uint32_t group = mKey510.mGroup;
    if (IsOne((group >> 30) & 3))
        InvalidEditorModelKey(&mKey510, 1);

    void* arg = obj;
    bool ok = Update(arg);
    if (obj != 0)
        (*(void (__thiscall**)(void*))(*(uint32_t*)obj + 4))(obj);
    return ok;
}
