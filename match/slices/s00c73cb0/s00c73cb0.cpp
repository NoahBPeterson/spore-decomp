// Slice s00c73cb0: Simulator cPlanet scanned-entry accessors (species / cities /
// buildings / resources) plus cToolObject and cPlanetaryArtifact construction,
// destruction and hit handling. Retail build.
// Module flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

// ------------------------------------------------------------ free helpers ---
void* NounManager();                                                       // 0x00b3d300
void* eastl_lower_bound(void* b, void* e, void* k, unsigned char c);       // 0x00ba2e50
void* FUN_00d01260(void* b, void* e, void* k, unsigned char c);            // 0x00d01260
void* FUN_00ac0d80(void* b, void* e, void* k);                             // 0x00ac0d80
void* FUN_00ba57f0(void* key, int n);                                      // 0x00ba57f0
void* FUN_00ba5650(void* key, int n);                                      // 0x00ba5650
void* FUN_00ba5a60(void* x, int n);                                        // 0x00ba5a60
void* __stdcall FUN_00b3d4f0(void* x);                                     // 0x00b3d4f0
void* FUN_00b21340(void* mgr, void* f1, void* f2, void* f3, void* f4, void* id); // 0x00b21340
void* FUN_00f47380(void* p);                                               // 0x00f47380 operator delete[]
void* FUN_01021260();                                                      // 0x01021260
void  GetPropertyAsKey(void* obj, int key, void* out);                     // 0x006a1250
void  NotifyScannedCreatureSpecies(void* key, int flag);                   // 0x01058460
void  RemoveArtifact(void* a, void* b, void* c);                           // 0x00c71160
void* GetSpaceCombatTuning();                                              // 0x01029940

struct SpaceCombatTuning { float GetColonyObjectHealth(); };               // 0x0102a7f0
struct cCombatant { void TakeHit(float d, int a, int b, int c, int e); };  // 0x00bfcdd0
struct VecEraser { void eraseElem(void* p); };                            // 0x00eeee40

extern float g_13f08c0;   // 0x013f08c0
extern float g_13eb1bc;   // 0x013eb1bc

// notification sink used by FUN_00b3d4f0's result (0x00e30d20)
struct Notifier { void Notify(); };

// eastl rbtree map: {begin,end,...,comparator@+0x14}; 0x18 bytes
struct EaMap {
    void*         begin;          // +0x00
    void*         end;            // +0x04
    char          mPad08[0x0c];   // +0x08
    unsigned char mCmp14;         // +0x14
    char          mPad15[3];      // +0x15
    void* find(void* key);              // 0x00ba4e60  thiscall, ret 4
    void  find(void* out, void* key);   // 0x00c729b0  thiscall, ret 8
    void* insert(void* key);            // 0x00ba4520  thiscall, ret 4
};

struct EaVec { void* begin; void* end; };  // two-pointer eastl vector

// 12-byte inline keyed record stored in ComCtxRef's key vectors.
struct Key12 { unsigned k0, k1, k2; };

// 12-byte keyed record; eastl orders (k0, k2, k1)
inline bool KeyLess(const void* a, const void* b)
{
    const unsigned* x = (const unsigned*)a;
    const unsigned* y = (const unsigned*)b;
    if (x[0] != y[0]) return x[0] < y[0];
    if (x[2] != y[2]) return x[2] < y[2];
    return x[1] < y[1];
}

// ----------------------------------------------------------------- types -----
struct ComCtxRef {                 // the planet data reached through cPlanet::+0x13c
    char  mPad00[0xbc];            // +0x000
    EaVec mVecBC;                  // +0x0bc  scanned-key vector A (12-byte records)
    char  mPadC4[0xd0 - 0xc4];     // +0x0c4
    EaVec mVecD0;                  // +0x0d0  scanned-key vector B
    char  mPadD8[0x15c - 0xd8];    // +0x0d8
    EaVec mCivVec;                 // +0x15c  vector<cCivData*>
    char  mPad164[0x184 - 0x164];  // +0x164
    void* mCommCtx;                // +0x184
    void* GetCommContext();        // 0x00ce6950  returns mCommCtx
};

struct NounMgr {                   // SP::NounManager() result
    void* GetCurrentTerrainSphere();   // 0x00f67d90  returns this->+0x74
    void* FUN_00b25f40(int id);        // 0x00b25f40
    void  RemoveNoun(void* noun);      // 0x00b225d0
};

struct CivData {
    EaVec* GetCities();                // 0x005c65e0
    void*  GetResourceKey(void* elem); // 0x00ff0cd0
};

struct ScanNode {                  // rbtree node of ComCtxRef's +0x11c0 map
    char mPad00[8];                // +0x000
    EaMap mMaps[5];                // +0x008 species / +0x20 / +0x38 / +0x50 / +0x68
    char mPad80[0xa2 - 0x80];      // +0x080
    unsigned char mFlagA2;         // +0x0a2
};

struct PlanetCls {                 // SP::cPlanet / current terrain sphere
    char       mPad00[0x13c];      // +0x000
    ComCtxRef* mPData;             // +0x13c
    char       mPad140[0x11c0 - 0x140]; // +0x140
    EaMap      mScanned;           // +0x11c0

    void* FUN_00c73cb0(void* key);                 // +0x20 entry of a scanned map
    void* FUN_00c73cd0(void* key);                 // +0x68 entry of a scanned map
    void  FUN_00c73cf0(int flag);                 // scan the two key vectors into maps[0]
    char  SetSpeciesAsScanned(void* key);
    char  IsSpeciesScanned(void* key);
    void  FUN_00c73f80(void* key);
    void  FUN_00c73ff0();
    char  FUN_00c741a0(void* key);
    void  FUN_00c74210(void* key);
    void  FUN_00c74280();
    char  FUN_00c74400(void* key);
    void  FUN_00c74470(void* key);
    char  FUN_00c744e0(unsigned* key);
    char FUN_00c74550(unsigned* key);
    void  FUN_00c745d0(char flag, void* key);
    void  FUN_00c74650();
    void  FUN_00c74690(void* key, char b2, char b3);
    void  FUN_00c74730(void* k1, void* k2);
    int   FUN_00c73350(int* key);                  // defined in slice s00c72c60
    void* FUN_00c735e0(void* key);                 // defined in slice s00c72c60
};

// ---------------------------------------------------------- tool object ------
struct MovableOrn { void cMovOrnCtor(); void cMovOrnDtor(); void FUN_00c69030(); };

// 12-byte inline record at +0x640 (assigned by value in FUN_00c74a30)
struct Pod12 { void* a; void* b; void* c; };

struct cToolObject {
    void* mVtbl0;                  // +0x000
    void* mVtbl4;                  // +0x004
    char  mPad08[0x34 - 0x08];     // +0x008
    void* mVtbl34;                 // +0x034
    char  mPad38[0x108 - 0x38];    // +0x038
    void* mVtbl108;                // +0x108
    char  mPad10c[0x508 - 0x10c];  // +0x10c
    void* mVtbl508;                // +0x508
    char  mPad50c[0x534 - 0x50c];  // +0x50c
    float m534;                    // +0x534
    char  mPad538[0x540 - 0x538];  // +0x538
    float m540;                    // +0x540
    char  mPad544[0x5d0 - 0x544];  // +0x544
    void* mVtbl5d0;                // +0x5d0
    char  mPad5d4[0x638 - 0x5d4];  // +0x5d4
    void* m638;                    // +0x638
    void* m63c;                    // +0x63c
    Pod12 m640;                    // +0x640
    void* m64c;                    // +0x64c
    void* m650;                    // +0x650
    void* m654;                    // +0x654

    void* FUN_00c74950();          // ctor
    void* FUN_00c749e0(unsigned char flag);  // deleting dtor
    void  FUN_00c74a30(void* v);
};

// ------------------------------------------------------ planetary artifact ---
struct cPlanetaryArtifact {
    void* mVtbl0;                  // +0x000
    void* mVtbl4;                  // +0x004
    char  mPad08[0x34 - 0x08];     // +0x008
    union { void* p34; int i34; }; // +0x034  secondary vptr / state int
    char  mPad38[0x108 - 0x38];    // +0x038
    void* mVtbl108;                // +0x108
    char  mPad10c[0x130 - 0x10c];  // +0x10c
    void* m130;                    // +0x130
    char  mPad134[0x144 - 0x134];  // +0x134
    void* m144;                    // +0x144 (8-byte sub-record)
    char  mPad148[0x150 - 0x148];  // +0x148
    int   m150;                    // +0x150
    char  mPad154[0x508 - 0x154];  // +0x154
    void* mVtbl508;                // +0x508
    char  mPad50c[0x5d0 - 0x50c];  // +0x50c
    void* mVtbl5d0;                // +0x5d0
    char  mPad5d4[0x638 - 0x5d4];  // +0x5d4
    void* m638;                    // +0x638
    void* m63c;                    // +0x63c
    void* m640;                    // +0x640
    void* m644;                    // +0x644
    void* m648;                    // +0x648
    void* m64c;                    // +0x64c
    void* m650;                    // +0x650
    void* m654;                    // +0x654
    int   m658;                    // +0x658
    char  m65c;                    // +0x65c
    char  m65d;                    // +0x65d
    char  m65e;                    // +0x65e
    char  mPad65f[1];              // +0x65f
    float m660;                    // +0x660

    void* FUN_00c74a50();          // ctor
    void  FUN_00c74ba0();
    void  FUN_00c74bd0();
    void  FUN_00c74c20(float dmg, int a, int b, int c, int d);
    bool  FUN_00c74ca0();
};

// vc9 object with two leading virtuals used for the m63c / m13c releases
struct RefObj { virtual void v0(); virtual void v1(); };
struct RefObj3 : RefObj { virtual void v2(); };

// spatial object override (0x00c899a0 base)
struct SpatialObj { void func7Ch(int a, float* b); };
struct SpatialDerived : SpatialObj { void FUN_00c74880(int a, float* b); };

// --- forward-declare the cPlanet map-accessor virtual used by 00c74280 -------
struct ArtifactResObj { void* GetKey(int mode); };

// ===========================================================================
// @ 0x00c73cb0
// Return &node->mMaps[1]-relative entry (node+0x20) for `key`.
// ===========================================================================
void* PlanetCls::FUN_00c73cb0(void* key)
{
    return (char*)mScanned.find(&key) + 0x20;
}

// ===========================================================================
// @ 0x00c73cd0
// Return &node->mMaps[3]... entry (node+0x68) for `key`.
// ===========================================================================
void* PlanetCls::FUN_00c73cd0(void* key)
{
    return (char*)mScanned.find(&key) + 0x68;
}

// ===========================================================================
// @ 0x00c73cf0
// Scan the two inline key vectors (pd+0xbc then pd+0xd0) into maps[0],
// notifying each newly inserted (and, in the second pass, every) creature
// species when `flag` is set.
// ===========================================================================
void PlanetCls::FUN_00c73cf0(int flag)
{
    if (mPData == 0) return;
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[0];
    for (Key12* it = (Key12*)mPData->mVecBC.begin; it != (Key12*)mPData->mVecBC.end;
         it = (Key12*)((char*)it + 0xc)) {
        char* end = (char*)m->end;
        char* r = (char*)eastl_lower_bound(m->begin, end, it, m->mCmp14);
        if (r == end || KeyLess(it, r) || r == r + 0x10)
            r = end;
        if (r == end || *(char*)(r + 0xc) == 0) {
            *(char*)m->insert(it) = 1;
            void* e = FUN_00ba57f0(it, 2);
            if ((char)flag) ((Notifier*)FUN_00b3d4f0(e))->Notify();
        }
    }
    for (Key12* it = (Key12*)mPData->mVecD0.begin; it != (Key12*)mPData->mVecD0.end;
         it = (Key12*)((char*)it + 0xc)) {
        char* end = (char*)m->end;
        char* r = (char*)eastl_lower_bound(m->begin, end, it, m->mCmp14);
        if (r == end || KeyLess(it, r) || r == r + 0x10)
            r = end;
        if (r == end || *(char*)(r + 0xc) == 0) {
            NotifyScannedCreatureSpecies(it, flag);
            *(char*)m->insert(it) = 1;
            void* e = FUN_00ba5650(it, 2);
            if ((char)flag) ((Notifier*)FUN_00b3d4f0(e))->Notify();
        }
    }
}

// ===========================================================================
// @ 0x00c73ea0
// Whether the species `key` is flagged scanned for the current comm context.
// ===========================================================================
char PlanetCls::SetSpeciesAsScanned(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[0];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// ===========================================================================
// @ 0x00c73f10
// ===========================================================================
char PlanetCls::IsSpeciesScanned(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[1];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// ===========================================================================
// @ 0x00c73f80
// Mark the species as scanned, firing the notification when it was new.
// ===========================================================================
void PlanetCls::FUN_00c73f80(void* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[1];
    if (!IsSpeciesScanned(key))
        ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
    *(char*)m->insert(key) = 1;
}

// ===========================================================================
// @ 0x00c73ff0
// Mark every building of every city of every civ as scanned.
// ===========================================================================
void PlanetCls::FUN_00c73ff0()
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[1];

    ComCtxRef* pd = mPData;
    int nCiv = (int)((char*)pd->mCivVec.end - (char*)pd->mCivVec.begin) / 4;
    for (int i = 0; i < nCiv; ++i) {
        void* civ = ((void**)pd->mCivVec.begin)[i];
        EaVec* cities = ((CivData*)civ)->GetCities();
        int nCity = (int)((char*)cities->end - (char*)cities->begin) / 4;
        for (int j = 0; j < nCity; ++j) {
            char* city = ((char**)cities->begin)[j];
            int nBuild = (*(int*)(city + 0x80) - *(int*)(city + 0x7c)) / 0x38;
            for (int p = 0; p < nBuild; ++p) {
                void* key = ((CivData*)civ)->GetResourceKey(
                                (void*)(*(int*)(city + 0x7c) + p * 0x38));
                void* r = eastl_lower_bound(m->begin, m->end, key, m->mCmp14);
                if (r == m->end || KeyLess(key, r) || r == (void*)((char*)r + 0x10))
                    r = m->end;
                if (r == m->end)
                    ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
                *(char*)m->insert(key) = 1;
            }
        }
    }
}

// ===========================================================================
// @ 0x00c741a0
// ===========================================================================
char PlanetCls::FUN_00c741a0(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[2];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// ===========================================================================
// @ 0x00c74210
// ===========================================================================
void PlanetCls::FUN_00c74210(void* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[2];
    if (!FUN_00c741a0(key))
        ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
    *(char*)m->insert(key) = 1;
}

// ===========================================================================
// @ 0x00c74280
// Mark the resource key of every game-data object as scanned.
// ===========================================================================
void PlanetCls::FUN_00c74280()
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[2];

    void* vec = FUN_00b21340(NounManager(), (void*)0x00cd7d10, (void*)0x00d3d420,
                             (void*)0x00ae72d0, (void*)0x00b1e500, (void*)0x018c6de8);
    int n = (*(int*)((char*)vec + 8) - *(int*)((char*)vec + 4)) / 4;
    for (int i = 0; i < n; ++i) {
        unsigned char* d = (unsigned char*)(*(int*)((char*)vec + 4) + i * 4);
        ArtifactResObj* obj = (ArtifactResObj*)(d + 0x34);
        void* key = obj->GetKey(0);
        void* r = eastl_lower_bound(m->begin, m->end, key, m->mCmp14);
        if (r == m->end || KeyLess(key, r) || r == (void*)((char*)r + 0x10))
            r = m->end;
        if (r == m->end)
            ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(obj->GetKey(2), 2)))->Notify();
        *(char*)m->insert(obj->GetKey(0)) = 1;
    }
}

// ===========================================================================
// @ 0x00c74400
// ===========================================================================
char PlanetCls::FUN_00c74400(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[3];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// ===========================================================================
// @ 0x00c74470
// ===========================================================================
void PlanetCls::FUN_00c74470(void* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[3];
    if (!FUN_00c74400(key))
        ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
    *(char*)m->insert(key) = 1;
}

// ===========================================================================
// @ 0x00c744e0
// ===========================================================================
char PlanetCls::FUN_00c744e0(unsigned* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[4];
    char* end = (char*)m->end;
    char* r = (char*)FUN_00d01260(m->begin, end, key, m->mCmp14);
    if (r == end || *key < *(unsigned*)r || r == r + 8)
        r = end;
    return r == end ? (char)0 : *(char*)(r + 4);
}

// ===========================================================================
// @ 0x00c74550
// ===========================================================================
char PlanetCls::FUN_00c74550(unsigned* key)
{
    char r = FUN_00c744e0(key);
    if (r == 0) {
        void* y = ((NounMgr*)NounManager())->FUN_00b25f40(*key);
        void* x = FUN_00ba5a60(y, 1);
        ((Notifier*)FUN_00b3d4f0(x))->Notify();
    }
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    char* mp = (char*)node + 0x68;
    *(char*)((PlanetCls*)mp)->FUN_00c735e0(key) = 1;
    return r;
}

// ===========================================================================
// @ 0x00c745d0
// Drop `key` from the scanned vector at pd+0xbc/0xd0 and from the species map.
// ===========================================================================
void PlanetCls::FUN_00c745d0(char flag, void* key)
{
    ComCtxRef* pd = mPData;
    if (pd != 0) {
        EaVec* vec = flag ? &pd->mVecBC : &pd->mVecD0;
        void* end = vec->end;
        void* e = FUN_00ac0d80(vec->begin, end, key);
        if (e != end)
            ((VecEraser*)vec)->eraseElem(e);
        void* k;
        k = ((ComCtxRef*)mPData)->GetCommContext();
        PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
        ScanNode* node = (ScanNode*)s->mScanned.find(&k);
        char* mp = (char*)node + 8;
        ((PlanetCls*)mp)->FUN_00c73350((int*)key);
    }
}

// ===========================================================================
// @ 0x00c74650
// ===========================================================================
void PlanetCls::FUN_00c74650()
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    node->mFlagA2 = 1;
}

// ===========================================================================
// @ 0x00c74690
// ===========================================================================
void PlanetCls::FUN_00c74690(void* key, char b2, char b3)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[0];
    if (b3 != 0 && b2 != 0) {
        if (!SetSpeciesAsScanned(key)) {
            void* e;
            unsigned t = *(unsigned*)((char*)key + 4);
            if (t != 0x2b978c46) {
                if (t != 0x438f6347) goto done;
                e = FUN_00ba57f0(key, 2);
            } else {
                e = FUN_00ba5650(key, 2);
            }
            if (e) ((Notifier*)FUN_00b3d4f0(e))->Notify();
        }
    }
done:
    *(char*)m->insert(key) = b2;
}

// ===========================================================================
// @ 0x00c74730
// Replace the key `k1` with `k2` in the scanned vector B, then move the scan
// flag between the species and secondary maps.
// ===========================================================================
void PlanetCls::FUN_00c74730(void* k1, void* k2)
{
    unsigned* a1 = (unsigned*)k1;
    unsigned* a2 = (unsigned*)k2;
    if (a2[0] != a1[0] || a2[1] != a1[1] || a2[2] != a1[2]) {
        ComCtxRef* pd = mPData;
        void* e = FUN_00ac0d80(pd->mVecD0.begin, pd->mVecD0.end, a1);
        if (e != pd->mVecD0.end) {
            ((unsigned*)e)[0] = a2[0];
            ((unsigned*)e)[1] = a2[1];
            ((unsigned*)e)[2] = a2[2];
        }
        if (SetSpeciesAsScanned(a1)) {
            void* k;
            k = ((ComCtxRef*)mPData)->GetCommContext();
            PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
            ScanNode* node = (ScanNode*)s->mScanned.find(&k);
            *(char*)node->mMaps[0].insert(a2) = 1;
        }
        {
            void* k;
            k = ((ComCtxRef*)mPData)->GetCommContext();
            PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
            ScanNode* node = (ScanNode*)s->mScanned.find(&k);
            ((PlanetCls*)((char*)node + 8))->FUN_00c73350((int*)a1);
        }
    }
}

// ===========================================================================
// @ 0x00c74880
// ===========================================================================
void SpatialDerived::FUN_00c74880(int a, float* b)
{
    func7Ch(a, b);
    b[1] -= g_13f08c0;
}

// ===========================================================================
// @ 0x00c74950
// Simulator::cToolObject::cToolObject
// ===========================================================================
void* cToolObject::FUN_00c74950()
{
    ((MovableOrn*)this)->cMovOrnCtor();
    mVtbl0 = (void*)0x14729b0;
    mVtbl4 = (void*)0x147299c;
    mVtbl34 = (void*)0x14728a0;
    mVtbl108 = (void*)0x1472898;
    mVtbl508 = (void*)0x1472830;
    mVtbl5d0 = (void*)0x14727c8;
    m638 = 0;
    m63c = 0;
    m640.a = 0;
    m640.b = 0;
    m640.c = 0;
    m64c = 0;
    m650 = 0;
    m654 = 0;
    float h = ((struct SpaceCombatTuning*)GetSpaceCombatTuning())->GetColonyObjectHealth();
    m540 = h;
    m534 = h;
    return this;
}

// ===========================================================================
// @ 0x00c749e0
// cToolObject deleting destructor.
// ===========================================================================
void* cToolObject::FUN_00c749e0(unsigned char flag)
{
    mVtbl0 = (void*)0x14729b0;
    mVtbl4 = (void*)0x147299c;
    mVtbl34 = (void*)0x14728a0;
    mVtbl108 = (void*)0x1472898;
    mVtbl508 = (void*)0x1472830;
    mVtbl5d0 = (void*)0x14727c8;
    ((MovableOrn*)this)->cMovOrnDtor();
    if (flag & 1)
        FUN_00f47380(this);
    return this;
}

// ===========================================================================
// @ 0x00c74a30
// ===========================================================================
void cToolObject::FUN_00c74a30(void* v)
{
    Pod12 t;
    t.a = v;
    t.b = 0;
    t.c = 0;
    m640 = t;
}

// ===========================================================================
// @ 0x00c74a50
// Simulator::cPlanetaryArtifact::cPlanetaryArtifact
// ===========================================================================
void* cPlanetaryArtifact::FUN_00c74a50()
{
    ((MovableOrn*)this)->cMovOrnCtor();
    float f = g_13eb1bc;
    m638 = 0;
    mVtbl0 = (void*)0x1472bf0;
    mVtbl4 = (void*)0x1472bdc;
    p34 = (void*)0x1472ae0;
    mVtbl108 = (void*)0x1472ad8;
    mVtbl508 = (void*)0x1472a70;
    mVtbl5d0 = (void*)0x1472a08;
    m63c = 0;
    m640 = 0;
    m64c = *(void**)0x1694514;
    m650 = *(void**)0x1694518;
    m65c = 0;
    m65d = 0;
    m654 = *(void**)0x169451c;
    m658 = -1;
    m65e = 1;
    m660 = f;
    return this;
}

// ===========================================================================
// @ 0x00c74ba0
// ===========================================================================
void cPlanetaryArtifact::FUN_00c74ba0()
{
    if (m63c != 0) {
        void* p = m63c;
        m63c = 0;
        ((RefObj*)p)->v1();
    }
    ((MovableOrn*)this)->FUN_00c69030();
}

// ===========================================================================
// @ 0x00c74bd0
// ===========================================================================
void cPlanetaryArtifact::FUN_00c74bd0()
{
    mVtbl0 = (void*)0x1472bf0;
    mVtbl4 = (void*)0x1472bdc;
    p34 = (void*)0x1472ae0;
    mVtbl108 = (void*)0x1472ad8;
    mVtbl508 = (void*)0x1472a70;
    mVtbl5d0 = (void*)0x1472a08;
    if (m63c != 0)
        ((RefObj*)m63c)->v1();
    ((MovableOrn*)this)->cMovOrnDtor();
}

// ===========================================================================
// @ 0x00c74c20
// SP::cSPPlanetaryArtifact::TakeHit
// ===========================================================================
void cPlanetaryArtifact::FUN_00c74c20(float dmg, int a, int b, int c, int d)
{
    ((cCombatant*)this)->TakeHit(dmg, a, b, c, d);
    if (i34 == 2) {
        i34 = 0;
        if (m150 == 4) {
            void* p = FUN_01021260();
            if (p != 0)
                RemoveArtifact(*(void**)((char*)p + 0x13c), (void*)&m144, m130);
            ((NounMgr*)NounManager())->RemoveNoun((char*)this - 0x508);
        }
    }
}

// ===========================================================================
// @ 0x00c74ca0
// SP::cSPPlanetaryArtifact::IsRare
// ===========================================================================
bool cPlanetaryArtifact::FUN_00c74ca0()
{
    unsigned local[3];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    GetPropertyAsKey(m63c, 0x34f1a4f, local);
    return local[0] == 0x7ecbe6f5u;
}