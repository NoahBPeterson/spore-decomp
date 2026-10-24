// @ 0x00b5e9a0: update of the UI "world" (layout) visibility from the current game state.
// Builds a local eastl::fixed_hash_map<uint32_t, bool> (world id -> should be visible), then
// applies it to the cSPUILayoutManager: SetWorldVisible(id, v) for every entry whose current
// IsWorldVisible(id) differs. Layout world ids are retail hashes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no EH: the original has no SEH prolog).
#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

struct cLayoutMgr {
    bool IsWorldVisible(u32 id);                  // 0x00810760 (ret 4)
    void SetWorldVisible(u32 id, bool v);         // 0x00810660 (ret 8)
    bool AnyWorldHidden();                        // 0x00810730
};
cLayoutMgr* __cdecl GetLayoutManager();           // 0x00805070

struct cB3d320 { char pad[0x28]; u8 mFlag28; };
cB3d320* __cdecl GetB3d320();                     // 0x00b3d320
unsigned __cdecl GetCurrentGameMode();            // 0x00b5b800

struct cCreatureModeStrategy {
    bool F();                                     // 0x00d38880
    static cCreatureModeStrategy* Instance();     // 0x00d38840
};
struct cTribeModeStrategy {
    bool F();                                     // 0x00cd4490
    static cTribeModeStrategy* Instance();        // 0x00cd40b0
};
struct cCivModeStrategy {
    bool F();                                     // 0x00cf7a40
    static cCivModeStrategy* Get();               // 0x00cf74c0
};
struct cB3d410 {
    bool F();                                     // 0x00e36fa0
    bool G();                                     // 0x00e393b0
};
cB3d410* __cdecl GetB3d410();                     // 0x00b3d410
struct cB3d4d0 { char pad[0x2c]; int m2c; };
cB3d4d0* __cdecl GetB3d4d0();                     // 0x00b3d4d0
struct cB3d3f0 { bool F(int a); };                // 0x00e18c70 (ret 4)
cB3d3f0* __cdecl GetB3d3f0();                     // 0x00b3d3f0

struct cFlagObj {
    bool F1();                                    // 0x00644db0
    bool F2();                                    // 0x00644dd0
    char pad[0x1c];
    u8 mFlag;
};
cFlagObj* __cdecl SporeGuide();                   // 0x00401040
cFlagObj* __cdecl AssetBrowser();                 // 0x00401030

struct IWinMgr {
    virtual void v0();
    virtual void* Get4();
};
IWinMgr* __cdecl WindowManager();                 // 0x0067caa0
struct cWinObj {
    bool Test();                                  // 0x00812d70
    bool Test2();                                 // 0x00812d90
    void Set(bool b);                             // 0x00812d60 (ret 4)
};
struct cC10666a0 { bool F(); };                   // 0x01065b30
cC10666a0* __cdecl GetC10666a0();                 // 0x010666a0
bool __cdecl FUN_00e00b00();
bool __cdecl FUN_00e00ac0();

extern const u32 kWorldIds[12];                   // 0x014617dc
extern u8 gUiBusyFlag;                            // 0x01686af0
extern u8 gUiFlagB;                               // 0x01686af1

void __cdecl EA_operator_delete(void* p);          // 0x00f47380

// ---- eastl::fixed_hash_map<u32, bool, 17 buckets, 16 nodes> ----------------------------------
struct TagA {};
struct TagB {};
struct Pair { u32 first; bool second; Pair() {} Pair(const u32& a, const bool& b) : first(a), second(b) {} };
struct Node { u32 key; bool val; Node* next; };
struct Iter {
    Node* node; Node** bucket;
    Iter() {}
    Iter(Node* n, Node** b) : node(n), bucket(b) {}
    Iter(const Iter& o) : node(o.node), bucket(o.bucket) {}
};
struct InsertRet { Iter it; bool inserted; };
struct InsertTag {};

struct VisMap {
    u32 pad0;
    Node** mpBucketArray;     // +04
    u32 mnBucketCount;        // +08
    u32 mnElementCount;       // +0c
    u32 mRehashPolicy[3];     // +10
    void* mpPoolHead;         // +1c
    void* mpPoolNext;         // +20
    void* mpPoolBegin;        // +24
    void* mpPoolEnd;          // +28
    u32 mnNodeSize;           // +2c
    Node** mpBucketBuffer;    // +30
    void* mBucketBuffer[18];
    char mNodeBuffer[192];
    double mAlign8;

    VisMap(const TagA&, const TagB&);                     // 0x00d2d5c0 (ret 8)
    __declspec(noinline) Iter find(const u32& key)        // 0x00645ed0 (real body: tells cl it never writes key)
    {
        Node** bucket = mpBucketArray + (key % mnBucketCount);
        for (Node* p = *bucket; p; p = p->next)
            if (p->key == key)
                return Iter(p, bucket);
        Iter e;
        e.node = mpBucketArray[mnBucketCount];
        e.bucket = mpBucketArray + mnBucketCount;
        return e;
    }
    InsertRet DoInsertValue(const Pair& v, InsertTag t);  // 0x00c15fd0
    void DoFreeNodes(Node** buckets, u32 n);              // 0x00a1b6c0
    bool& operator[](const u32& key);                     // 0x00b5e050 (out-of-line copy)
    __forceinline bool* At(const u32& key)                              // same body, inlined
    {
        Iter it = find(key);
        Node* node = it.node;
        if (node == mpBucketArray[mnBucketCount]) {
            InsertRet r = DoInsertValue(Pair(key, false), InsertTag());
            node = r.it.node;
        }
        bool* pv = &node->val;
        return pv;
    }
    ~VisMap()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1 && mpBucketArray != mpBucketBuffer) {
            if ((void*)mpBucketArray >= mpPoolBegin && (void*)mpBucketArray < mpPoolEnd) {
                *(void**)mpBucketArray = mpPoolHead;
                mpPoolHead = mpBucketArray;
            } else
                EA_operator_delete(mpBucketArray);
        }
    }
};

// @ 0x00b5e9a0
void __stdcall UpdateWorldVisibility(int unused)
{
    TagA tagA;
    TagB tagB;
    VisMap map(tagA, tagB);
    cLayoutMgr* lm = GetLayoutManager();

    for (u32 i = 0; i < 12; i++) {
        const u32 id = kWorldIds[i];
        if (lm->IsWorldVisible(id))
            *map.At(id) = false;
    }

    unsigned mode = GetCurrentGameMode();
    bool busy;
    if (GetB3d320()->mFlag28 || gUiBusyFlag)
        busy = true;
    else
        busy = false;
    u8 flagB = gUiFlagB;
    if (!busy) {
        switch (mode) {
        case 0x1654c01:
            busy = cCreatureModeStrategy::Instance()->F();
            break;
        case 0x1654c02:
            busy = cTribeModeStrategy::Instance()->F();
            flagB = false;
            break;
        case 0x1654c04:
            busy = cCivModeStrategy::Get()->F();
            break;
        case 0x1654c05:
            busy = GetB3d410()->F();
            break;
        }
    }

    void* w = WindowManager()->Get4();
    cWinObj* wo = w ? (cWinObj*)((char*)w - 4) : 0;
    bool woA = wo && wo->Test();
    bool woB = wo && wo->Test2();

    if (busy) {
        { const u32 k = 0x614de4c; *map.At(k) = true; }
        wo->Set(false);
    } else if (GetB3d410()->G()) {
        { const u32 k = 0x5b598f6; *map.At(k) = true; }
    } else {
        int m = GetB3d4d0()->m2c;
        if (m == 1 || m == 2) {
            { const u32 k = 0x5b598f8; map[k] = true; }
        } else if (SporeGuide()->F1() || SporeGuide()->F2() || SporeGuide()->mFlag ||
                   AssetBrowser()->F1() || AssetBrowser()->F2() || AssetBrowser()->mFlag) {
            { const u32 k = 0x5b598f6; map[k] = true; }
        } else if (GetC10666a0() && GetC10666a0()->F()) {
            { const u32 k = 0x2edd95ca; map[k] = true; }
        } else if (FUN_00e00b00()) {
            { const u32 k = 0x5b598f6; map[k] = true; }
        } else if (FUN_00e00ac0()) {
            { const u32 k = 0x5b598f6; map[k] = true; }
            { const u32 k = 0x5f1bfc10; map[k] = true; }
        } else if (GetB3d3f0()->F(0)) {
            { const u32 k = 0xe9f70df9; map[k] = true; }
            { const u32 k = 0x5b598f6; map[k] = true; }
            { const u32 k = 0x2edd95ca; map[k] = true; }
            { const u32 k = 0x3469e7a3; map[k] = true; }
            { const u32 k = 0x08d0f4fb; map[k] = true; }
        } else if (woA) {
            { const u32 k = 0x5b598f6; map[k] = true; }
        } else {
            { const u32 k = 0xe9f70df9; map[k] = !flagB; }
            { const u32 k = 0x5b598f6; map[k] = true; }
            { const u32 k = 0x5f1bfc10; map[k] = true; }
            { const u32 k = 0x2edd95ca; map[k] = true; }
            { const u32 k = 0x3f608b3e; map[k] = true; }
            { const u32 k = 0x3469e7a3; map[k] = true; }
            { const u32 k = 0xec2fd2c3; map[k] = true; }
            { const u32 k = 0x08d0f4fb; map[k] = true; }
            { const u32 k = 0xcbdf6e1d; map[k] = true; }
        }
    }

    if (lm->AnyWorldHidden()) {
        { const u32 k = 0x62efc8c; *map.At(k) = true; }
        { const u32 k = 0xa01a43c8; *map.At(k) = !woB; }
    }

    Node** b = map.mpBucketArray;
    Node* n = *b;
    Node** pb = b;
    if (!n) {
        pb = b + 1;
        while (!*pb) ++pb;
        n = *pb;
    }
    Node* pEnd = b[map.mnBucketCount];
    while (n != pEnd) {
        u32 id = n->key;
        bool v = n->val;
        if (lm->IsWorldVisible(id) != v)
            lm->SetWorldVisible(id, v);
        n = n->next;
        if (!n) {
            do { ++pb; n = *pb; } while (!n);
        }
    }
}

// ===========================================================================
// 0x00b5e260 / 0x00b5e380  ctor / dtor of the cGonzagoSubsystem subclass that
// owns five 0x20-byte eastl::hashtable channels at +0x1c..+0xbb.
// ===========================================================================
struct GonzSub2;
void __fastcall CGonzagoSubsystem_ctor(GonzSub2* self);      // 0x00b5b960
void __fastcall CGonzagoSubsystem_dtor(GonzSub2* self);      // 0x00b5b9a0
void* __cdecl sim_operator_new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0

struct AzerLCG { unsigned mState; void SetSeed(unsigned seed); };   // 0x00936090

struct AzerHT {                       // 0x20-byte eastl::hashtable
    unsigned mnPad00;                 // +0x00
    void*    mpBucketArray;           // +0x04
    unsigned mnBucketCount;           // +0x08
    unsigned mnElementCount;          // +0x0c
    float    mfLoad;                  // +0x10
    float    mfGrow;                  // +0x14
    unsigned mnPad18;                 // +0x18
    unsigned mnPad1c;                 // +0x1c
    void DoFreeBuckets(void* buckets, unsigned count);   // 0x00693230
};

struct GonzSub2 {                     // SP::cGonzagoSubsystem-derived
    void*  mpVftable0;                // +0x00
    void*  mpVftable1;                // +0x04
    char   mPad08[0x14];              // +0x08..+0x1b
    AzerHT mHT[5];                    // +0x1c..+0xbb
    AzerLCG mRng;                     // +0xbc
    GonzSub2* Construct();            // 0x00b5e260
    void Destroy();                   // 0x00b5e380
};

// @ 0x00b5e260
GonzSub2* GonzSub2::Construct()
{
    CGonzagoSubsystem_ctor(this);
    mpVftable0 = (void*)0x1462920;
    mpVftable1 = (void*)0x1462918;

    mHT[0].mfLoad = 1.0f;
    mHT[0].mfGrow = 2.0f;
    mHT[0].mnElementCount = 0;
    mHT[0].mnPad18 = 0;
    mHT[0].mnBucketCount = 1;
    mHT[0].mpBucketArray = (void*)0x154df28;

    mHT[1].mfLoad = 1.0f;
    mHT[1].mfGrow = 2.0f;
    mHT[1].mpBucketArray = (void*)0x154df28;
    mHT[1].mnBucketCount = 1;
    mHT[1].mnElementCount = 0;
    mHT[1].mnPad18 = 0;

    mHT[2].mfLoad = 1.0f;
    mHT[2].mfGrow = 2.0f;
    mHT[2].mpBucketArray = (void*)0x154df28;
    mHT[2].mnBucketCount = 1;
    mHT[2].mnElementCount = 0;
    mHT[2].mnPad18 = 0;

    mHT[3].mfLoad = 1.0f;
    mHT[3].mfGrow = 2.0f;
    mHT[3].mpBucketArray = (void*)0x154df28;
    mHT[3].mnBucketCount = 1;
    mHT[3].mnElementCount = 0;
    mHT[3].mnPad18 = 0;

    mHT[4].mfLoad = 1.0f;
    mHT[4].mfGrow = 2.0f;
    mHT[4].mpBucketArray = (void*)0x154df28;
    mHT[4].mnBucketCount = 1;
    mHT[4].mnElementCount = 0;
    mHT[4].mnPad18 = 0;

    mRng.SetSeed(0xffffffffu);
    return this;
}

// @ 0x00b5e380
void GonzSub2::Destroy()
{
    char* p = (char*)this + 0xbc;
    for (int i = 4; i >= 0; --i) {
        p -= 0x20;
        AzerHT* ht = (AzerHT*)p;
        ht->DoFreeBuckets(ht->mpBucketArray, ht->mnBucketCount);
        ht->mnElementCount = 0;
        if (ht->mnBucketCount > 1)
            EA_operator_delete(ht->mpBucketArray);
    }
    CGonzagoSubsystem_dtor(this);
}

// ===========================================================================
// 0x00b5e0b0  register a cGonzagoSubsystemContainer into the global
// "world object" hashtable and link it (thiscall receiver + one stack arg).
// ===========================================================================
struct StyleHTNode {                  // node of eastl hashtable<u32, ...>
    StyleHTNode* mpNext;              // +0x00
    void*        mpValue;             // +0x04
};

struct StyleHTIter { StyleHTNode* node; void* bucket; };
struct StyleMap {                     // eastl::hashtable<u32, pair<u32,void*>>
    unsigned      mBucketCount;       // +0x08
    StyleHTNode** mpBucketArray;      // +0x0c
    void Find(StyleHTIter* out, const unsigned* key);   // 0x00645ed0
    StyleHTNode* End() { return mpBucketArray[mBucketCount]; }
};
extern StyleMap g_StyleMap;           // 0x0152d69c

struct ContVec {                      // simple pointer vector (begin at +4)
    void*  mpFirst;                   // +0x00
    void** mpEnd;                     // +0x08 - 4
    void** mpCap;                     // +0x0c - 4
};

struct WObj {
    char    mPad00[0x18];
    ContVec mList18;                  // +0x18
    char    mPad24[0x08];
    void*   mpStr;                    // +0x2c (eastl::wstring)
};

void* __cdecl Big2_Init(void* self, void* arg);                        // 0x00694e60
void* __cdecl WStr_Format(void* dst, const wchar_t* fmt, void* arg);   // 0x0041e050
void __cdecl WaitingList1_Insert(void* end, void* value);              // 0x00690b80
void __cdecl WStr_Append(const wchar_t* a, const wchar_t* b);          // 0x00429580
void __cdecl WorldObjInsert(StyleHTNode** iter, void* pair, unsigned flag);   // 0x007c3990

// @ 0x00b5e0b0
unsigned __fastcall FUN_00b5e0b0(void** self, int dummy, ContVec* pVec)
{
    StyleHTIter it;
    g_StyleMap.Find(&it, (const unsigned*)self);
    StyleHTNode* iter = it.node;
    if (iter != g_StyleMap.End()) {
        WObj* obj = (WObj*)iter->mpValue;
        if (pVec->mpEnd < pVec->mpCap) {
            *pVec->mpEnd = obj;
            pVec->mpEnd += 1;
        } else {
            WaitingList1_Insert(pVec->mpEnd, obj);
        }
        if (obj->mList18.mpEnd < obj->mList18.mpCap) {
            *obj->mList18.mpEnd = pVec;
            obj->mList18.mpEnd += 1;
        } else {
            WaitingList1_Insert(obj->mList18.mpEnd, pVec);
        }
        return 1;
    }
    WObj* obj = (WObj*)sim_operator_new(0x74, "Simulator", 0, 0, 0, 0);
    if (obj != 0)
        obj = (WObj*)Big2_Init(obj, self);
    else
        obj = 0;
    WStr_Format(&obj->mpStr, L"cGonzagoSubsystemContainer @ 0x%08x", self);
    if (pVec->mpEnd < pVec->mpCap) {
        *pVec->mpEnd = obj;
        pVec->mpEnd += 1;
    } else {
        WaitingList1_Insert(pVec->mpEnd, obj);
    }
    if (obj->mList18.mpEnd < obj->mList18.mpCap) {
        *obj->mList18.mpEnd = pVec;
        obj->mList18.mpEnd += 1;
    } else {
        WaitingList1_Insert(obj->mList18.mpEnd, pVec);
    }
    {
        struct Pair2 { void* a; void* b; } pair;
        pair.a = self;
        pair.b = obj;
        WorldObjInsert(&it.node, &pair, 0);
    }
    if (*self != 0) {
        typedef void (__fastcall *Vfn)(void*, int, void*);
        void** vt = (void**)*self;
        ((Vfn)vt[0x34 / 4])(*self, 0, obj);
        return 1;
    }
    {
        const wchar_t* s = L" No subsystem!";
        const wchar_t* e = s;
        while (*e) ++e;
        WStr_Append(s, e);
    }
    return 1;
}

// ===========================================================================
// 0x00b5e3f0  per-game-mode update of day length / time-of-day / sky params
// driven by the "9:7:9:9" property group.  thiscall, ret 4.
// ===========================================================================
struct PropObj {
    bool Query(unsigned key, void** out);        // vtable slot +0x24
};
struct AppObj {
    void SetX100(int v);                         // vtable slot +0x100
    void SetX108(int v);                         // vtable slot +0x108
    void SetTime(float a, float b, float c, float d);   // vtable slot +0xf4
};
struct TimeMgr {                                 // eastl vector<float> at +0x10
    void* mpBegin;                               // +0x10
    void* mpEnd;                                 // +0x14
};

void* __stdcall PropertyManager();                                  // 0x0067de30
void* __stdcall GetPropMgrB();                                      // 0x0067dd40
void* __stdcall GetUniverse2();                                     // 0x01021080
int   __cdecl  Prop_GetAsFloatArray(void* val, unsigned key);       // 0x006a08b0
float* __cdecl Prop_GetFloat(void* props, unsigned key, void** out); // 0x0041ea70
void* __stdcall TimeOfDay_Instance();                               // 0x00bc30b0
void  __fastcall TimeOfDay_SetDayLength(void* self, int dummy, float v);  // 0x00bc2830
double __fastcall Sky_A(void* self);                                // 0x00b3ce80
double __fastcall Sky_B(void* self);                                // 0x00b3cec0
double __fastcall Sky_C(void* self);                                // 0x00b3cf00
void __cdecl Shader_SetConst3(unsigned id, void* data, int n);      // 0x00777ae0
void* __stdcall Sky_Get(void);                                      // 0x00b3d470
void __cdecl  Sky_Apply(void* self);                                // 0x010346b0
void __cdecl MemCopy(void* dst, void* src, unsigned n);             // 0x011e0744
unsigned __stdcall VecReserve(void* v, int n);                      // 0x004e0880
void __cdecl VecPushBack3(void* v, void* p);                        // 0x00455660

// @ 0x00b5e3f0
void __fastcall FUN_00b5e3f0(TimeMgr* self, int dummy, unsigned mode)
{
    PropObj* props = 0;
    void* mgr = PropertyManager();
    PropObj* p = props;
    if (props != 0) {
        props = 0;
        *(void**)(*(void**)p) ; // vtable available
    }
    /* release (slot +4) if any */
    bool ok = ((PropObj*)mgr)->Query(0x39393837, (void**)&props);
    if (!ok) return;
    unsigned aKey;
    if (mode == 0x01654c01)      aKey = 0x34ee1cb;
    else if (mode == 0x01654c02) aKey = 0x34ee1d3;
    else if (mode == 0x01654c04) aKey = 0x34ee1d6;
    else if (mode == 0x01654c05) aKey = 0x34ee1d9;
    else                         aKey = 0x22cfea6;
    int count = Prop_GetAsFloatArray(props, aKey);
    void* tm = TimeOfDay_Instance();
    float* beg = *(float**)((char*)tm + 0x10);
    float* end = *(float**)((char*)tm + 0x14);
    MemCopy(beg, end, (unsigned)(end - beg));
    *(int*)((char*)tm + 0x14) += (int)((end - beg) * -4) / 4 * 4 - (end - beg) + (int)(end - beg);
    VecReserve((char*)tm + 0x10, count);
    for (int i = 0; i < count; ++i)
        VecPushBack3((char*)tm + 0x10, &beg[i]);
    float f18 = 0.0f;
    float f1c = 0.0f;
    float f20 = 0.0f;
    unsigned k = 0x0d;
    unsigned mask = 0x30;
    if (props != 0) {
        void* v;
        if (((PropObj*)props)->Query(0x33dda25, &v) && *(short*)((char*)v + 0x12) == (short)k) {
            if ((*(unsigned char*)((char*)v + 0x10) & mask) != 0) v = *(void**)v;
            f20 = *(float*)v;
        }
    }
    {
        void* v2 = *(void**)&f20;
        TimeOfDay_SetDayLength(TimeOfDay_Instance(), 0, *(float*)&v2);
    }
    {
        float v1 = (float)Sky_A((void*)0x167ea80); *(float*)0x1687110 = v1;
        float v2b = (float)Sky_B((void*)0x167ea80); *(float*)0x1687114 = v2b;
        float v3 = (float)Sky_C((void*)0x167ea80); *(float*)0x1687118 = v3;
    }
    Shader_SetConst3(0x245, (void*)0x1687110, 1);
    if (mode == 0x01654c01 || mode == 0x01654c02 || mode == 0x01654c04 ||
        mode == 0x01654c05 || mode == 0x01654c10) {
        ((AppObj*)GetPropMgrB())->SetX100(1);
        int flag;
        if (mode == 0x01654c05) {
            flag = (GetUniverse2() != 0);
        } else {
            flag = 0;
        }
        ((AppObj*)GetPropMgrB())->SetX108(flag);
        if (p != 0) {
            void* v;
            if (((PropObj*)p)->Query(0x62efb36, &v) && *(short*)((char*)v + 0x12) == 0x0d) {
                if ((*(unsigned char*)((char*)v + 0x10) & 0x30) != 0) v = *(void**)v;
                f18 = *(float*)v;
            }
            if (p != 0) {
                void* v2c;
                if (((PropObj*)p)->Query(0x62efb3d, &v2c) && *(short*)((char*)v2c + 0x12) == 0x0d) {
                    if ((*(unsigned char*)((char*)v2c + 0x10) & 0x30) != 0) v2c = *(void**)v2c;
                    f1c = *(float*)v2c;
                }
            }
        }
        if (mode == 0x01654c01) {
            if (p != 0) {
                void* v;
                if (((PropObj*)p)->Query(0x6380a32, &v) && *(short*)((char*)v + 0x12) == 0x0d) {
                    if ((*(unsigned char*)((char*)v + 0x10) & 0x30) != 0) v = *(void**)v;
                    f20 = *(float*)v;
                }
                if (p != 0) {
                    void* v2c;
                    if (((PropObj*)p)->Query(0x6380a37, &v2c) && *(short*)((char*)v2c + 0x12) == 0x0d) {
                        if ((*(unsigned char*)((char*)v2c + 0x10) & 0x30) != 0) v2c = *(void**)v2c;
                        f1c = *(float*)v2c;
                    }
                }
            }
        } else if (mode == 0x01654c02) {
            if (p != 0) {
                void* v;
                if (((PropObj*)p)->Query(0x6380a3b, &v) && *(short*)((char*)v + 0x12) == 0x0d)
                    f20 = *Prop_GetFloat(p, 0x6380a3b, &v);
                if (p != 0) {
                    void* v2c;
                    if (((PropObj*)p)->Query(0x6380a40, &v2c) && *(short*)((char*)v2c + 0x12) == 0x0d)
                        f1c = *Prop_GetFloat(p, 0x6380a40, &v2c);
                }
            }
        } else if (mode == 0x01654c04) {
            if (p != 0) {
                void* v;
                if (((PropObj*)p)->Query(0x6380a44, &v) && *(short*)((char*)v + 0x12) == 0x0d)
                    f20 = *Prop_GetFloat(p, 0x6380a44, &v);
                if (p != 0) {
                    void* v2c;
                    if (((PropObj*)p)->Query(0x6380a54, &v2c) && *(short*)((char*)v2c + 0x12) == 0x0d)
                        f1c = *Prop_GetFloat(p, 0x6380a54, &v2c);
                }
            }
        } else if (mode == 0x01654c05 || mode == 0x01654c10) {
            if (p != 0) {
                void* v;
                if (((PropObj*)p)->Query(0x6380a5a, &v) && *(short*)((char*)v + 0x12) == 0x0d)
                    f20 = *Prop_GetFloat(p, 0x6380a5a, &v);
                if (p != 0) {
                    void* v2c;
                    if (((PropObj*)p)->Query(0x6380a61, &v2c) && *(short*)((char*)v2c + 0x12) == 0x0d)
                        f1c = *Prop_GetFloat(p, 0x6380a61, &v2c);
                }
            }
        }
        ((AppObj*)GetPropMgrB())->SetTime(f20, f18, f1c, f20);
    } else {
        ((AppObj*)GetPropMgrB())->SetX100(0);
    }
    if (mode == 0x01654c05) {
        float g20 = 3.0517578e-05f;
        float g18 = 3.0517578e-05f;
        float g1c = 3.0517578e-05f;
        if (p != 0) {
            void* v;
            if (((PropObj*)p)->Query(0x67a058f, &v) && *(short*)((char*)v + 0x12) == 0x0d) {
                if ((*(unsigned char*)((char*)v + 0x10) & 0x30) != 0) v = *(void**)v;
                g20 = *(float*)v;
            }
            if (p != 0) {
                void* v2c;
                if (((PropObj*)p)->Query(0x67a0598, &v2c) && *(short*)((char*)v2c + 0x12) == 0x0d) {
                    if ((*(unsigned char*)((char*)v2c + 0x10) & 0x30) != 0) v2c = *(void**)v2c;
                    g18 = *(float*)v2c;
                }
                if (p != 0) {
                    void* v3;
                    if (((PropObj*)p)->Query(0x67a059f, &v3) && *(short*)((char*)v3 + 0x12) == 0x0d) {
                        if ((*(unsigned char*)((char*)v3 + 0x10) & 0x30) != 0) v3 = *(void**)v3;
                        g1c = *(float*)v3;
                    }
                }
            }
        }
        Sky_Apply(Sky_Get());
        (void)g20; (void)g18; (void)g1c;
    }
    if (p != 0) {
        /* release p (vtable slot +4) */
    }
}

