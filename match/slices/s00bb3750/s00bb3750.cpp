// match/slices/s00bb3750/s00bb3750.cpp
// Object file: SPStarManager.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Star-manager civ bookkeeping.  FUN_00bb3750 looks a civ's star record up in the
// civ->star counter map and creates / registers one on a miss; FUN_00bb3800 and
// FUN_00bb3a40 turn cached star property weights into the search-type index used by
// the star search; FUN_00bb3c70 draws a random spot in an annulus around the origin,
// rejects it when it falls on a civ capital, and returns the first nearby star record
// that has at least 20 candidate neighbours.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- globals (address in comment) -------------------------------------------
extern double g_1400;        // 0x14661c8 1400.0
extern double g_700;         // 0x14661c0 700.0
extern double g_n700;        // 0x14661b8 -700.0
extern float  g_490000;      // 0x14661b0 490000.0
extern float  g_90;          // 0x156c50c 90.0
extern float  g_100;         // 0x13ec4d0 100.0
extern float  g_10;          // 0x1473c70 10.0
extern float  g_20;          // 0x1465e90 20.0
extern float  g_3;           // 0x1465ea8 3.0
extern float  g_m1;          // 0x13eb1bc -1.0
extern u32    g_staticGuard; // 0x1689e98 function-local static init guard
extern u8     g_propsLoaded; // 0x1689e3c star-property cache flag
extern void   FUN_013c3060();// 0x13c3060 vecMain atexit thunk
extern void   FUN_013c3050();// 0x13c3050 vecAlt atexit thunk

struct RandomGlobal {
    double RandomDouble();   // 0x9360d0
};
extern RandomGlobal g_random;    // 0x1601760

// ---- external callees -------------------------------------------------------
extern "C" int  __cdecl atexit(void (__cdecl*)(void));    // 0x11e07ef
int  __cdecl    FUN_00ba7320(const void* vec);            // 0xba7320
void __cdecl    FUN_00f47380(void* p);                    // 0xf47380 operator delete
struct Vector3;
Vector3* __fastcall FUN_005c65e0(void* civ);              // 0x5c65e0 GetCities

// ---- small value types ------------------------------------------------------
struct Vector3 {
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
};

// The star record: a ref-counted object with the "already handled" byte at +0xac.
struct cStarRecord {
    virtual int  AddRef();          // +0x00
    virtual void Release();         // +0x04
    char pad008[0xac - 4];
    u8   mHandled;                  // +0xac
    void FUN_00c8b6d0(void* p);     // 0xc8b6d0
};

struct Empire {
    void AddStar(void* p);          // 0xc341a0
};

// The game noun walking around (a game-noun-manager / player object).
struct GameObj {
    char pad000[0x70];
    void* mpPlayerObject;           // +0x70
    int FUN_00bb9ae0();             // 0xbb9ae0
    int GetAvatar();                // 0xb1fdb0
};

// A star property object (the GetProp out value).
struct Prop {
    char pad000[0x12];
    u16  mType;                     // +0x12
    int* GetInt();                  // 0x41e990
};

// The property owner: the lookup is virtual slot +0x24.
struct PropOwner {
    virtual char v00();             // +0x00
    virtual char v01();             // +0x04
    virtual char v02();             // +0x08
    virtual char v03();             // +0x0c
    virtual char v04();             // +0x10
    virtual char v05();             // +0x14
    virtual char v06();             // +0x18
    virtual char v07();             // +0x1c
    virtual char v08();             // +0x20
    virtual char GetProp(u32 hash, Prop** out);   // +0x24
};

// ---- civ counter map (eastl rbtree keyed by u32) ----------------------------
struct RBNode {
    RBNode* mpLeft;     // +0x00
    RBNode* mpRight;    // +0x04
    RBNode* mpParent;   // +0x08
    int     mColor;     // +0x0c
    u32     mKey;       // +0x10
    void*   mValue;     // +0x14
};

struct RBTree {
    int     mCount;         // +0x00
    RBNode* mpSentinel;     // +0x04
    int     mPad08;         // +0x08
    RBNode* mpRoot;         // +0x0c

    void Find(RBNode** out, const u32* key);    // 0xe5c780
    u32& GetCounter(const u32* key);            // 0xbadea0
};

// ---- star-record vector -----------------------------------------------------
template <class T>
struct AutoRefCount {
    T* mpObject;
    __forceinline AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    __forceinline AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    __forceinline ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

struct sp_vector_allocator {
    u32 mData[2];
};

typedef AutoRefCount<cStarRecord> StarRef;

StarRef* __cdecl DoCopy(StarRef* first, StarRef* last, StarRef* dst);  // 0x6782c0

struct StarVector {
    StarRef* mpBegin;           // +0x00
    StarRef* mpEnd;             // +0x04
    StarRef* mpCapacity;        // +0x08
    sp_vector_allocator mAllocator;   // +0x0c

    void erase(StarRef* first, StarRef* last);      // 0xe25bd0

    __forceinline ~StarVector()
    {
        for (StarRef* p = mpBegin; p < mpEnd; ++p)
            p->~StarRef();
        if (mpBegin && ((u32*)mpBegin)[-1] != 0)
            FUN_00f47380(mpBegin);
    }
};

// ---- star-search criteria ---------------------------------------------------
struct Crit {
    u32   mTypes;    // +0x00
    u32   mSolar;    // +0x04
    u32   mMisc;     // +0x08
    float mF0c;      // +0x0c
    float mRadius;   // +0x10
    float mF14;      // +0x14
    u32   mF18;      // +0x18
};

// ---- inline-buffer int vector ----------------------------------------------
struct IntVec6 {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCap;      // +0x08
    int  mPad[2];    // +0x0c
    int  mData[6];   // +0x14

    void Insert(int* position, int n, int* value);  // 0xc33da0
};

struct IntVec7 {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCap;      // +0x08
    int  mPad[2];    // +0x0c
    int  mData[7];   // +0x14

    void Insert(int* position, int n, int* value);  // 0xc33da0
};

// The two function-local statics of FUN_00bb3800.
extern IntVec6 g_vecMain;    // 0x1689e6c
extern IntVec6 g_vecAlt;     // 0x1689e40

// ---- the star manager -------------------------------------------------------
struct StarMgr {
    char pad000[0x20];
    RBTree mCivStars;                 // +0x20
    char pad030[0xdc - 0x30];
    void** mpCivBeginDC;              // +0xdc
    void** mpCivEndE0;                // +0xe0
    char pad0e4[0xf0 - 0xe4];
    void** mpCivBeginF0;              // +0xf0
    void** mpCivEndF4;                // +0xf4
    char pad0f8[0x1a0 - 0xf8];
    PropOwner* mpPropOwner;           // +0x1a0

    cStarRecord* FUN_00bac7d0();                       // 0xbac7d0
    Empire* FUN_00bb1340(void* p);                     // 0xbb1340
    void GetStarRecords(Vector3* pos, Crit* crit, StarVector* out);  // 0xbb1080

    // Store a property's int value into *out (property lookups by hash).
    __forceinline void GetIntProp(u32 hash, int* out) {
        PropOwner* po = mpPropOwner;
        Prop* prop;
        if (po != 0 && po->GetProp(hash, &prop) && prop->mType == 9)
            *out = *prop->GetInt();
    }

    void FUN_00bb3750(GameObj* p, cStarRecord** out);  // 0xbb3750
    int  FUN_00bb3800(char useMain);                   // 0xbb3800
    int  FUN_00bb3a40(u32* flags);                     // 0xbb3a40
    cStarRecord* FUN_00bb3c70();                       // 0xbb3c70
};

// ---------------------------------------------------------------------------
// @ 0x00bb3750
// ---------------------------------------------------------------------------
void StarMgr::FUN_00bb3750(GameObj* p, cStarRecord** out) {
    *out = 0;
    if (p == 0)
        return;

    u32 key = (u32)p->mpPlayerObject;
    RBNode* it;
    mCivStars.Find(&it, &key);
    if (it != (RBNode*)&mCivStars.mpSentinel) {
        cStarRecord* rec = (cStarRecord*)it->mValue;
        *out = rec;
        rec->AddRef();
        return;
    }

    cStarRecord* rec = FUN_00bac7d0();
    *out = rec;
    if (rec == 0)
        return;
    rec->AddRef();
    (*out)->FUN_00c8b6d0(p);
    mCivStars.GetCounter(&key) = (u32)(void*)*out;
    if (p->FUN_00bb9ae0() == 5 && p->GetAvatar() != -1) {
        Empire* e = FUN_00bb1340(p);
        e->AddStar(p);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00bb3800
// ---------------------------------------------------------------------------
int StarMgr::FUN_00bb3800(char useMain) {
    if ((g_staticGuard & 1) == 0) {
        g_staticGuard |= 1;
        int zero = 0;
        g_vecMain.mpEnd = g_vecMain.mData;
        g_vecMain.mpBegin = g_vecMain.mData;
        g_vecMain.mpCap = g_vecMain.mData + 6;
        g_vecMain.Insert(g_vecMain.mData, 6, &zero);
        atexit(FUN_013c3060);
    }
    if ((g_staticGuard & 2) == 0) {
        g_staticGuard |= 2;
        int zero = 0;
        g_vecAlt.mpEnd = g_vecAlt.mData;
        g_vecAlt.mpBegin = g_vecAlt.mData;
        g_vecAlt.mpCap = g_vecAlt.mData + 6;
        g_vecAlt.Insert(g_vecAlt.mData, 6, &zero);
        atexit(FUN_013c3050);
    }

    if (g_propsLoaded == 0) {
        GetIntProp(0x2f8299a, g_vecMain.mpBegin + 1);
        GetIntProp(0x2f8353b, g_vecMain.mpBegin + 2);
        g_vecMain.mpBegin[3] = 0;
        GetIntProp(0x2f827ce, g_vecMain.mpBegin + 4);
        GetIntProp(0x2f827d5, g_vecMain.mpBegin + 5);

        g_vecAlt.mpBegin[1] = g_vecMain.mpBegin[1];
        g_vecAlt.mpBegin[2] = g_vecMain.mpBegin[2];
        g_vecAlt.mpBegin[3] = 0;
        g_vecAlt.mpBegin[4] = g_vecMain.mpBegin[4];
        g_vecAlt.mpBegin[5] = 0;
        g_vecMain.mpBegin[1] += g_vecMain.mpBegin[5];
        g_vecMain.mpBegin[5] = 0;
        g_propsLoaded = 1;
    }

    const void* v = useMain ? (const void*)&g_vecMain : (const void*)&g_vecAlt;
    int r = FUN_00ba7320(v);
    if (r == 6)
        r = 1;
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00bb3a40
// ---------------------------------------------------------------------------
int StarMgr::FUN_00bb3a40(u32* flags) {
    IntVec7 v;
    v.mpEnd = v.mData;
    v.mpBegin = v.mData;
    int zero = 0;
    v.mpCap = v.mData + 7;
    v.Insert(v.mData, 7, &zero);

    u8 b2 = (u8)((*flags >> 2) & 1);
    if (b2)
        GetIntProp(0x306b188, v.mpBegin + 2);
    u8 b3 = (u8)((*flags >> 3) & 1);
    if (b3)
        GetIntProp(0x2c378c2, v.mpBegin + 3);
    u8 b4 = (u8)((*flags >> 4) & 1);
    if (b4)
        GetIntProp(0x306b131, v.mpBegin + 4);
    u8 b5 = (u8)((*flags >> 5) & 1);
    if (b5)
        GetIntProp(0x306b133, v.mpBegin + 5);
    u8 b1 = (u8)((*flags >> 1) & 1);
    if (b1)
        GetIntProp(0x2c378fc, v.mpBegin + 1);
    u8 b0 = (u8)(*flags & 1);
    if (b0)
        GetIntProp(0x2c37907, v.mpBegin);
    u8 b6 = (u8)((*flags >> 6) & 1);
    if (b6)
        GetIntProp(0x42a2267, v.mpBegin + 6);

    int r = FUN_00ba7320(&v);
    if (r == 7)
        r = 2;
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00bb3c70
// ---------------------------------------------------------------------------
cStarRecord* StarMgr::FUN_00bb3c70() {
    float minDist2 = g_90 * g_90;

    StarVector vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;
    vec.erase(vec.mpBegin, vec.mpEnd);
    u32 n = (u32)(vec.mpEnd - vec.mpBegin);

    cStarRecord* result = 0;
    u32 attempts = 0;
    bool ok;

    do {
        float x;
        float y;
        float dist2;
        do {
            double rx = g_random.RandomDouble() * g_1400 - g_700;
            if (rx >= g_700)
                rx = g_700;
            else if (rx < g_n700)
                rx = g_n700;
            x = (float)rx;

            double ry = g_random.RandomDouble() * g_1400 - g_700;
            if (ry >= g_700)
                ry = g_700;
            else if (ry < g_n700)
                ry = g_n700;
            y = (float)ry;

            dist2 = y * y + x * x;
        } while (dist2 < minDist2 || dist2 > g_490000);

        ok = true;
        u32 count = (u32)(mpCivEndF4 - mpCivBeginF0);
        for (u32 i = 0; i < count; ++i) {
            void* civ = mpCivBeginF0[i];
            float dx = FUN_005c65e0(civ)->x - x;
            float dy = FUN_005c65e0(civ)->y - y;
            if (dx * dx + dy * dy < g_100)
                ok = false;
        }
        count = (u32)(mpCivEndE0 - mpCivBeginDC);
        for (u32 j = 0; j < count; ++j) {
            void* civ = mpCivBeginDC[j];
            float dx = FUN_005c65e0(civ)->x - x;
            float dy = FUN_005c65e0(civ)->y - y;
            if (dx * dx + dy * dy < g_100)
                ok = false;
        }
        if (!ok) {
            if (attempts++ < 1000)
                continue;
        }

        Crit crit;
        crit.mTypes = 0x10;
        crit.mSolar = 0x3f;
        crit.mMisc = 0;
        crit.mF0c = 0.0f;
        crit.mRadius = g_10;
        crit.mF14 = g_m1;
        crit.mF18 = 0;

        {
            StarRef* r = (StarRef*)DoCopy(vec.mpEnd, vec.mpEnd, vec.mpBegin);
            for (StarRef* p = r; p < vec.mpEnd; ++p)
                p->~StarRef();
            vec.mpEnd -= n;
        }

        Vector3 pos;
        pos.x = x;
        pos.y = y;
        pos.z = 0.0f;
        GetStarRecords(&pos, &crit, &vec);

        n = (u32)(vec.mpEnd - vec.mpBegin);
        if (n == 0) {
            if (attempts++ < 1000)
                continue;
        }

        {
            StarVector vec2;
            vec2.mpBegin = 0;
            vec2.mpEnd = 0;
            vec2.mpCapacity = 0;

            for (u32 i = 0; i < n; ++i) {
                cStarRecord* rec = vec.mpBegin[i].mpObject;
                if (rec->mHandled != 0)
                    continue;

                StarRef* r = (StarRef*)DoCopy(vec2.mpEnd, vec2.mpEnd, vec2.mpBegin);
                for (StarRef* p = r; p < vec2.mpEnd; ++p)
                    p->~StarRef();
                vec2.mpEnd -= vec2.mpEnd - vec2.mpBegin;

                crit.mTypes = 0x1fff;
                crit.mSolar = 0x3f;
                crit.mMisc = 0;
                crit.mF0c = 0.0f;
                crit.mRadius = g_20;
                crit.mF14 = g_3;
                crit.mF18 = 0;
                GetStarRecords(FUN_005c65e0(rec), &crit, &vec2);

                if ((u32)(vec2.mpEnd - vec2.mpBegin) >= 20) {
                    result = rec;
                    break;
                }
            }
        }

        if (result == 0) {
            if (attempts++ < 1000)
                continue;
        }
        break;
    } while (true);

    return result;
}
