// Slice s0103a480: SP::cSPSpaceTrading commodity/rare-commodity helpers + EASTL vector/heap helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <xmmintrin.h>

typedef unsigned int uint;

struct Obj { void* vptr; };

// generic vtable wrappers (each starts with a vptr, so a cast reaches the right slot)
struct V0c { virtual void z0(); virtual void z1(); virtual void z2(); virtual void* v0c(int); };
struct V14 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void v14(void*); };
struct V18 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual int v18(); };
struct V1c { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void v1c(); };
struct V20 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
             virtual void* v20(); };
struct V24 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
             virtual void z8(); virtual bool v24(uint id, void** out); };
struct V2c { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
             virtual void z8(); virtual void z9(); virtual void z10();
             virtual void v2c(int id, int key, void** out); };
struct V4  { virtual int AddRef(); virtual int Release(); };

// Heap element refcount interface: slot0 unknown, AddRef at +4, Release at +8.
struct HRef { virtual void h0(); virtual int AddRef(); virtual int Release(); };
struct AutoRef {
    HRef* mpRef;
    AutoRef(HRef* p = 0) : mpRef(p) { if (mpRef) mpRef->AddRef(); }
    AutoRef(const AutoRef& o) : mpRef(o.mpRef) { if (mpRef) mpRef->AddRef(); }
    ~AutoRef() { if (mpRef) mpRef->Release(); }
    AutoRef& operator=(const AutoRef& o) {
        if (mpRef != o.mpRef) {
            if (o.mpRef) o.mpRef->AddRef();
            HRef* old = mpRef;
            mpRef = o.mpRef;
            if (old) old->Release();
        }
        return *this;
    }
};
struct V38 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
             virtual void z8(); virtual void z9(); virtual void z10(); virtual void z11();
             virtual void z12(); virtual void z13(); virtual int v38(); };
struct V3c { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
             virtual void z8(); virtual void z9(); virtual void z10(); virtual void z11();
             virtual void z12(); virtual void z13(); virtual void z14(); virtual void v3c(void*); };
struct V70 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
             virtual void z8(); virtual void z9(); virtual void z10(); virtual void z11();
             virtual void z12(); virtual void z13(); virtual void z14(); virtual void z15();
             virtual void z16(); virtual void z17(); virtual void z18(); virtual void z19();
             virtual void z20(); virtual void z21(); virtual void z22(); virtual void z23();
             virtual void z24(); virtual void z25(); virtual void z26(); virtual void z27();
             virtual bool v70(int id, void* k); };
struct V74 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
             virtual void z8(); virtual void z9(); virtual void z10(); virtual void z11();
             virtual void z12(); virtual void z13(); virtual void z14(); virtual void z15();
             virtual void z16(); virtual void z17(); virtual void z18(); virtual void z19();
             virtual void z20(); virtual void z21(); virtual void z22(); virtual void z23();
             virtual void z24(); virtual void z25(); virtual void z26(); virtual void z27();
             virtual void z28(); virtual bool v74(void* k); };

struct Prop { char pad[0x12]; unsigned short type; float* GetFloat();   // 0x0041ea70
};
struct VProp24 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
                 virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
                 virtual void z8(); virtual bool v24(uint id, void** out); };
struct VProp2c { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
                 virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
                 virtual void z8(); virtual void z9(); virtual void z10();
                 virtual void v2c(int id, int key, void** out); };

struct cPropertyList {
    virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
    virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
    virtual void z8();
    virtual bool GetProperty(uint id, void** out);   // +0x24
};
struct IUnk { virtual int AddRef(); virtual int Release(); };
struct PropertyMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual void Unregister(int id, int key, IUnk** out);   // +0x2c
};

// ---- external callees
void* operator_new(int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void  operator_delete(void* p);                                                // 0x00f47380
void* PropertyManager();                                                       // 0x0067de30
void  cSPSpaceInventoryItem_ctor(void* p);                                     // 0x00c87660
void  SetPropertyList(void* item, void* list);                                 // 0x00c877f0
void  GetPropertyAsKey(void* list, uint id, void* out);                        // 0x006a1250
void  GetFloatProperty(void* list, uint id, void* out);                        // 0x0040cf10
void  GetIntProperty(void* list, uint id, void* out);                          // for 0103aa00 usage
void* SpaceGameGet();                                                          // 0x01002bd0
void* StarManager();                                                           // 0x00b3d2a0
void* NounManager();                                                           // 0x00b3d300
void* PlanetModel();                                                           // 0x00b3d350
void* GetPlayerEmpire();                                                       // 0x01021300
void  FUN_b3d2a0(void*);                                                       // 0x00b3d2a0 (StarManager)
int   GetCurrentGameMode();                                                    // 0x00b5b800
void* GetPlayerInventoryOf(void* sim);                                         // 0x00a1ad60
void* RBTreeIncrement(void* node);                                             // 0x00921580
void  WriteUint32(void* stream, const void* v, int a, int b);                  // 0x0093aa70
void  FUN_00ae2e40(void* a, void* b);                                          // 0x00ae2e40
void  FUN_00ff0350(float f);                                                   // 0x00ff0350
void  FUN_00c731a0(int a, int b, int c, int d, int e, int f, int g, int h, int i);  // 0x00c731a0
void  FUN_00c731a0(int a, int b, int c);                                       // 3-arg form (0x00c731a0)
void  FUN_00c731a0(int a, int b, int c, int d);                                // 4-arg form (0x00c731a0)
void* FUN_00ff5b80();                                                          // 0x00ff5b80
void* FUN_00b8dec0(int a);                                                     // 0x00b8dec0
void* FUN_00b8dad0(void* a, int b);                                            // 0x00b8dad0
void* FUN_00b8d970(void* a);                                                   // 0x00b8d970
void* FUN_00b8de30(void* a);                                                   // 0x00b8de30
int   FUN_00c30c60();                                                          // 0x00c30c60
void* FUN_00ba6dc0(int a);                                                     // 0x00ba6dc0
void* FUN_00ba9370(void* mgr, int id);                                         // 0x00ba9370
void* GetAvatar(void* o);                                                      // 0x00b1fdb0
void  FUN_00c69090(void* o);                                                   // 0x00c69090
void  FUN_00afa030(void* o);                                                   // 0x00afa030
void* FUN_00bd7f70(void* a, void* b);                                          // 0x00bd7f70
void* FUN_00bd7f50(void* a);                                                   // 0x00bd7f50
void* FUN_00afad70(void* a);                                                   // 0x00afad70
void* FUN_00572590();                                                          // 0x00572590 (thiscall getter)
void* FUN_00b81780(void* out, void* model, float a, float b, float c);         // 0x00b81780
void* FUN_00b7f190(void* model, void* out, void* in);                          // 0x00b7f190
void* FUN_00c74d30(void* artifact, int a, int b, void* c);                     // 0x00c74d30
void* FUN_00c87660(void* p);                                                   // 0x00c87660
void  FUN_00ff0350_(float f);                                                  // 0x00ff0350
void* FUN_00e5c780(void* a, void* b, void* c);                                 // eastl rbtree find helper
uint  RandomUint32Uniform(void* rng, int n);                                   // 0x00a68fb0
double RandomDoubleUniform(void* rng);                                         // 0x009360d0

extern void* g_rand;              // 0x01601760
extern int g_16df56c, g_16df570, g_16df574;   // key sentinel ints
extern float g_16df53c, g_16df540, g_16df544;
extern float g_13f4fd0;

struct Vec3f { float x, y, z; };
struct Vec3  { int x, y, z; };

// ---------------------------------------------------------------------------
// @ 0x0103a480  SP::cSPSpaceTrading::CreateCommodityFromID
// ---------------------------------------------------------------------------
struct Commodity {
    char pad0[0x10];
    int   mItemCount;    // +0x10
    int   mType;         // +0x14
    int   mCost;         // +0x18
    Commodity* ctor_00c87660();                 // thiscall ctor (ecx = item)
    void SetPropertyList_00c877f0(void* list);  // thiscall
};
struct VItemRef { virtual void z0(); virtual int AddRef(); };   // AddRef at +4
void __stdcall FUN_0103a480(void** out, int* id, int count, float cost) {
    Commodity* item = (Commodity*)operator_new(0x7c, "Simulator/cSpaceInventoryItem", 0, 0, 0, 0);
    Commodity* inst = item ? item->ctor_00c87660() : 0;
    IUnk* local = 0;
    PropertyMgr* pm = (PropertyMgr*)PropertyManager();
    if (local) {
        IUnk* old = local; local = 0; old->Release();
    }
    pm->Unregister(*id, 0x34d97fa, &local);
    ((V14*)inst)->v14(id);
    inst->mType = 4;
    inst->mItemCount = count;
    inst->mCost = (int)(cost + 0.5);   // rounds like the original's x87 fistp
    inst->SetPropertyList_00c877f0(local);
    ((VItemRef*)inst)->AddRef();
    *out = inst;
    if (local) local->Release();
}

// ---------------------------------------------------------------------------
// @ 0x0103a540
// ---------------------------------------------------------------------------
struct T540 {
    char pad0[0x34];
    int* mBegin;   // +0x34
    int* mEnd;     // +0x38
    uint scan(void* p);
};
uint T540::scan(void* p) {
    int n = ((int)mEnd - (int)mBegin) / 0xc;
    uint result = 0;
    IUnk* local = 0;
    int idx = 0;
    if (n > 0) {
        int count = n;
        do {
            void* e = (void*)((char*)mBegin + idx);
            void* q = (void*)((V18*)p)->v18();
            if (*(int*)e == *(int*)q) {
                PropertyMgr* pm = (PropertyMgr*)PropertyManager();
                if (local) { IUnk* old = local; local = 0; old->Release(); }
                pm->Unregister(*(int*)e, 0x34d97fa, &local);
                if (local) {
                    Prop* pr;
                    if (((VProp24*)local)->v24(0x58cbb75, (void**)&pr) && pr->type == 10) {
                        uint* base = (uint*)pr;
                        if ((base[4] & 0x30) != 0) base = (uint*)*base;
                        result = *base | 0xff000000;
                    }
                }
            }
            idx += 0xc;
            --count;
        } while (count != 0);
        if (local) local->Release();
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x0103a630
// ---------------------------------------------------------------------------
struct Vec3i { int x, y, z; };
struct HashObj { virtual void z0(); virtual void z1(); virtual void z2(); virtual int v3(uint id); };
struct V6 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
            virtual void z4(); virtual void z5(); virtual Vec3i* get(); };
struct HPosition { void get(void* out); };                    // 0x0104be80 (thiscall, ret 4)
struct TToolMgr { bool createTool(void* key, void** out); };  // 0x0104e340 (thiscall, ret 8)
void* FUN_00b3d390();                                          // 0x00b3d390 (global getter)
struct A630 {
    bool f_0103a630(void* item, int x, int y, int z);
};
// @ 0x0103a630
bool A630::f_0103a630(void* item, int x, int y, int z) {
    if (item == 0) return false;
    void* pi = (void*)((HashObj*)(*(void**)((char*)item + 0xc)))->v3(0x707459f0);
    if (pi == 0) return false;
    Vec3i tmp;
    Vec3i key = { 0, 0, 0 };
    ((HPosition*)pi)->get(&tmp);
    key.x = tmp.x;
    key.y = tmp.y;
    key.z = tmp.z;
    IUnk* local = 0;
    if (key.x != g_16df56c || key.y != g_16df570 || key.z != g_16df574) {
        if (((TToolMgr*)FUN_00b3d390())->createTool(&key, (void**)&local)) {
            bool r = f_0103a630(item, x, y, z);
            if (local) local->Release();
            return r;
        }
    }
    if (local) local->Release();
    Vec3i* v = ((V6*)pi)->get();
    return v->x == x && v->y == y && v->z == z;
}

// ---------------------------------------------------------------------------
// @ 0x0103a760
// ---------------------------------------------------------------------------
struct T760 {
    char pad0[0xbc];
    int* volatile mBegin;   // +0xbc
    int* volatile mEnd;     // +0xc0
    uint find(int id);
};
uint T760::find(int id) {
    uint i = 0;
    if ((uint)(((int)mEnd - (int)mBegin) / 0x24) == 0) return i;
    int* p = (int*)((char*)mBegin + 0xc);
    do {
        if (*p == id) return i;
        ++i;
        p += 9;
    } while (i < (uint)(((int)mEnd - (int)mBegin) / 0x24));
    return i;
}

// ---------------------------------------------------------------------------
// @ 0x0103a7d0  SP::cSPSpaceTrading::HandleMessage
// ---------------------------------------------------------------------------
struct MsgRef { virtual int AddRef(); virtual int Release(); };
struct B3Obj {
    void* get_ba6dc0(int id);      // 0x00ba6dc0 (thiscall, ret 4)
    int   get_ba9370(void* av);    // 0x00ba9370 (thiscall, ret 4)
};
struct NounObj { void* f_b8de30(); };   // 0x00b8de30 (thiscall)
struct AvObj   { void* f_b1fdb0(); };   // 0x00b1fdb0 (thiscall)
struct SPTrading {
    char pad0[0x2c];
    void** mBegin;   // +0x2c
    void** mEnd;     // +0x30
    int handleMessage(int msg, void* arg);
};
// @ 0x0103a7d0  SP::cSPSpaceTrading::HandleMessage
int SPTrading::handleMessage(int msg, void* arg) {
    if (msg < 0x4445d43 || msg > 0x4445d44) return 0;
    int a = *(int*)((char*)arg + 0x10);
    int b = *(int*)((char*)arg + 8);
    int player = (int)GetPlayerEmpire();
    int target;
    if (b == player) target = a;
    else if (a == player) target = b;
    else return 0;
    int count = (int)(mEnd - mBegin);
    if (count <= 0) return 0;
    int i = 0;
    do {
        void* entry = mBegin[i];
        int id = *(int*)((char*)entry + 0xc);
        void* noun = ((B3Obj*)StarManager())->get_ba6dc0(id);
        void* keep = 0;
        if (noun) {
            ((MsgRef*)noun)->AddRef();
            keep = noun;
        }
        void* av = ((NounObj*)keep)->f_b8de30();
        void* avatar = ((AvObj*)av)->f_b1fdb0();
        int emp = ((B3Obj*)StarManager())->get_ba9370(avatar);
        if (target == emp) {
            int n = (int)(mEnd - mBegin);
            if (i != n - 1) {
                void* last = mBegin[n - 1];
                void* cur = mBegin[i];
                if (last != cur) {
                    if (last) ((MsgRef*)((char*)last + 8))->AddRef();
                    mBegin[i] = last;
                    if (cur) ((MsgRef*)((char*)cur + 8))->Release();
                }
            }
            mEnd = mEnd - 1;
            void* popped = *mEnd;
            if (popped) ((MsgRef*)((char*)popped + 8))->Release();
        } else {
            ++i;
        }
        if (keep) ((MsgRef*)keep)->Release();
        count = (int)(mEnd - mBegin);
    } while (i < count);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0103a930
// ---------------------------------------------------------------------------
bool FUN_0103a930(int* list) {
    int n = (list[1] - *list) / 0xc;
    IUnk* local = 0;
    int idx = 0;
    if (n > 0) {
        int i = 0;
        int count = n;
        do {
            PropertyMgr* pm = (PropertyMgr*)PropertyManager();
            if (local) { IUnk* old = local; local = 0; old->Release(); }
            pm->Unregister(*(int*)(*list + idx), 0x34d97fa, &local);
            int key[3];
            key[0] = key[1] = key[2] = 0;
            GetPropertyAsKey(local, 0x34f1a4f, key);
            if (key[0] == 0x7ecbe6f5) {
                if (local) local->Release();
                return true;
            }
            ++i;
            idx += 0xc;
        } while (i < count);
        if (local) local->Release();
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0103aa00
// ---------------------------------------------------------------------------
struct Empire { int f_c30c60(); };                      // 0x00c30c60 (thiscall)
struct RngObj { double nextDouble(); };                 // 0x009360d0 (thiscall)
struct RareNoun { bool f_b8d970(); void* f_b8de30(); }; // 0x00b8d970 / 0x00b8de30
struct Trading34 {
    char pad0[0x34];
    int* mBegin;   // +0x34 (0xc-byte elements)
    int* mEnd;     // +0x38
    void addRareCommodity(void* p2);
};
// @ 0x0103aa00  SP::cSPSpaceTrading::AddRareCommodity
void Trading34::addRareCommodity(void* p2) {
    int count = (int)(((char*)mEnd - (char*)mBegin) / 0xc);
    if (GetCurrentGameMode() != 0x1654c05) return;
    if (*(int*)((char*)p2 + 0x28) <= 1) return;
    if (((RareNoun*)p2)->f_b8d970()) return;
    if (GetPlayerEmpire() == 0) return;
    int e1 = ((Empire*)GetPlayerEmpire())->f_c30c60();
    if ((int)((RareNoun*)p2)->f_b8de30() == e1) return;
    if (!FUN_0103a930((int*)((char*)this + 0x34))) return;
    IUnk* local = 0;
    bool found = false;
    do {
        int idx = 0;
        int left = count;
        while (left > 0) {
            if (local) { IUnk* old = local; local = 0; old->Release(); }
            PropertyMgr* pm = (PropertyMgr*)PropertyManager();
            pm->Unregister(*(int*)((char*)mBegin + idx), 0x34d97fa, &local);
            int key[3] = { 0, 0, 0 };
            GetPropertyAsKey(local, 0x34f1a4f, key);
            if (key[0] == 0x7ecbe6f5) {
                float chance = 0.0f;
                void* pr = 0;
                if (local && ((VProp24*)local)->v24(0x34f1a4e, &pr) &&
                    *(short*)((char*)pr + 0x12) == 0xd) {
                    float* f = ((Prop*)pr)->GetFloat();
                    chance = *f;
                }
                double roll = ((RngObj*)&g_rand)->nextDouble();
                if (roll < (double)chance) {
                    float amt = 0.0f;
                    GetFloatProperty(local, 0x34f1a49, &amt);
                    int n = (int)(amt + (amt >= 0.0f ? 0.5f : -0.5f));
                    FUN_00c731a0((int)p2, 4, *(int*)((char*)mBegin + idx), n, 0,
                                  *(int*)&g_16df53c, *(int*)&g_16df540, *(int*)&g_16df544, 1);
                    found = true;
                }
            }
            idx += 0xc;
            --left;
        }
    } while (!found);
    if (local) local->Release();
}

// ---------------------------------------------------------------------------
// @ 0x0103ac40
// ---------------------------------------------------------------------------
struct RBTreeT {
    void** find(void** out, const int* k);   // 0x00a21dc0
};
struct TAC40 {
    char pad0[0xa0];
    void* find(int* key);
};
void* TAC40::find(int* key) {
    void* node;
    void* p = *((RBTreeT*)((char*)this + 0xa0))->find((void**)&node, key);
    return (p != (void*)((char*)this + 0xa4)) ? *(void**)((char*)p + 0x1c) : 0;
}

// ---------------------------------------------------------------------------
// @ 0x0103ac70  SP::cSPSpaceTrading::IsRareGroupComplete
// ---------------------------------------------------------------------------
struct RareNode {
    char pad0[0x1c];
    int  mCount;      // +0x1c
};
struct RareTree {          // EASTL rbtree map living at trading+0xa0
    char  pad0[4];
    void* mAnchor;         // +0x4   header node (end iterator)
    char  pad1[4];
    void* mRoot;           // +0xc
    int   mCount;          // +0x10
    void** find(void** out, const int* key);   // 0x00a21dc0
};
struct GroupEntry {        // 0x24-byte element of the commodity-group table
    char pad0[0x10];
    int* mBegin;           // +0x10  int[3] keys, stride 0xc
    int* mEnd;             // +0x14
    char pad1[0xc];
};
struct SpaceGame {
    void* get_00a1ad60();  // GetPlayerInventory (thiscall)
};
struct TSx {
    char pad0[0xa0];
    RareTree  mRare;       // +0xa0
    char pad1[8];
    GroupEntry* mGroups;   // +0xbc
    bool f_ac70(int group, bool needInventory);
    void f_af90(void* p1, void* p2);
    bool f_b320(int* prop);
};
bool TSx::f_ac70(int group, bool needInventory) {
    uint n = (uint)(((int)mGroups[group].mEnd - (int)mGroups[group].mBegin) / 0xc);
    for (uint i = 0; i < n; ++i) {
        int* arr = mGroups[group].mBegin + i * 3;
        int key[3];
        key[0] = arr[0];
        key[1] = arr[1];
        key[2] = arr[2];
        void* node;
        void* p = *mRare.find((void**)&node, key);
        if (p == mRare.mAnchor) return false;
        if (((RareNode*)p)->mCount != 1) return false;
        if (needInventory) {
            void* inv = ((SpaceGame*)SpaceGameGet())->get_00a1ad60();
            if (!((V70*)inv)->v70(4, key)) return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0103ad50  SP::cSPSpaceTrading::AddCitySpicePile
// ---------------------------------------------------------------------------
struct ItemVecB { char pad0[0x3c]; void** mBegin; void** mEnd; };  // +0x3c / +0x40
struct ItemCtr  { ItemVecB* getItems(int kind); };                  // 0x00b8dec0 (thiscall, ret 4)
struct RngAd    { uint nextInt(int n); };                           // 0x00a68fb0 (thiscall, ret 4)
struct WorldItemAd { Vec3f* getPos(); };                            // 0x00572590 (thiscall)
struct VItem3 {
    virtual void z0(); virtual void z1(); virtual void Release(); virtual void z3();
    virtual void z4(); virtual void z5();
    virtual void* v18(int a, int b, Vec3f pos);                     // +0x18
};
struct VItem2 {
    virtual void z0(); virtual void z1(); virtual void Release(); virtual void z3();
    virtual void z4(); virtual void z5();
    virtual void* v18(int a, int b);                                // +0x18
};
struct VPosAd {
    virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
    virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
    virtual void z8(); virtual void z9(); virtual void z10();
    virtual int  get_2c();                                          // +0x2c
    virtual void z12();                                             // +0x30
    virtual void z13();                                             // +0x34
    virtual void get_38(Vec3f* out);                                // +0x38
    virtual void set_3c(int v);                                     // +0x3c
};
struct ArtifactAd {
    char pad0[0x34];
    VPosAd mPos;                                                    // +0x34 (vptr)
    void f_c69090();                                                // 0x00c69090 (thiscall)
};
struct SetterAd { void set(void* a, void* b); };                    // 0x00c74d30 (thiscall, 2 args)
struct ModelAd  { int build(int angle, Vec3f* pos); };              // 0x00b7f190 (thiscall, 2 args)
struct NounAd {
    virtual void z0(); virtual void z1(); virtual void z2();
    virtual void* getArtifact(int id);                              // +0x0c
};
struct NounMgrAd { void* createNoun(int id); };                     // 0x00b20c60 (thiscall, ret 4)

void FUN_0103ad50(void* self, int* p2, int a3, int a4) {
    if ((*(int*)((char*)self + 0x160) - *(int*)((char*)self + 0x15c)) == 0) return;
    ItemVecB* bp = ((ItemCtr*)self)->getItems(0);
    int cnt = (int)(bp->mEnd - bp->mBegin);
    if (cnt == 0) return;
    uint matches = 0;
    for (int* q = *(int**)((char*)self + 0x134); q != *(int**)((char*)self + 0x138); q += 3) {
        if (q[0] == p2[0]) ++matches;
    }
    if (matches >= (uint)(cnt * 2)) return;
    Vec3f pos;
    void* placed = 0;
    if (a4 == 0) {
        uint k = ((RngAd*)&g_rand)->nextInt(cnt);
        Vec3f* v = ((WorldItemAd*)bp->mBegin[k])->getPos();
        pos.x = v->x;
        pos.y = v->y;
        pos.z = v->z;
    } else {
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
    }
    void* item = 0;
    FUN_0103a480(&item, p2, a3, 0.0f);
    void* id = ((VItem3*)item)->v18(*(int*)((char*)item + 0x10), 1, pos);
    FUN_00c731a0((int)self, 4, (int)id, 0);
    if (a4 != 0) {
        void* mgr = NounManager();
        void* noun = mgr ? ((NounMgrAd*)mgr)->createNoun(0x2dd8c42) : 0;
        if (noun) {
            void* art = ((NounAd*)noun)->getArtifact(0x2dd8c33);
            if (art) {
                ArtifactAd* a = (ArtifactAd*)art;
                Vec3f apos;
                a->mPos.get_38(&apos);
                int angle = a->mPos.get_2c();
                ModelAd* model = (ModelAd*)PlanetModel();
                int orient = model->build(angle, &apos);
                a->mPos.set_3c(orient);
                a->f_c69090();
                void* aid = ((VItem2*)item)->v18(*(int*)((char*)item + 0x10), 1);
                ((SetterAd*)art)->set(*(void**)((char*)item + 0x14), aid);
                if (placed) FUN_00afa030(art);
            }
        }
    }
    ((VItem3*)item)->Release();
}

// ---------------------------------------------------------------------------
// @ 0x0103af90
// ---------------------------------------------------------------------------
struct Rng {                        // global RNG object at 0x01601760
    uint next_00a68fb0(int n);       // uniform int in [0,n)
};
struct WorldObj {
    Vec3i* pos_00b8dad0();           // returns this+0x198
    void*  item_00b8dec0(int idx);   // 0x00b8dec0
};
struct ItemVec {                     // container read at +0x3c/+0x40
    char pad0[0x3c];
    void** mBegin;                   // +0x3c
    void** mEnd;                     // +0x40
};
struct ItemElem {
    char  pad0[0x1c];
    float mValue;                    // +0x1c
    void add_00ff0350(float f);      // thiscall
};
struct Ad50 {                        // view of the trading object for the AddCitySpicePile call
    void call_0103ad50(void* star, Vec3i* pos, uint amount, int extra);
};
void TSx::f_af90(void* p1, void* p2) {
    uint a = ((Rng*)&g_rand)->next_00a68fb0(4) + 1;
    uint b = ((Rng*)&g_rand)->next_00a68fb0(4) + 1;
    Vec3i* v1 = ((WorldObj*)p1)->pos_00b8dad0();
    Vec3i* v2 = ((WorldObj*)p2)->pos_00b8dad0();
    if (v2->x == v1->x && v2->y == v1->y && v2->z == v1->z) {
        ItemVec* r = (ItemVec*)((WorldObj*)p1)->item_00b8dec0(0);
        if (r) {
            int n = ((int)r->mEnd - (int)r->mBegin) >> 2;
            if (n) {
                uint k = ((Rng*)&g_rand)->next_00a68fb0(n);
                ((ItemElem*)r->mBegin[k])->add_00ff0350((float)a);
            }
        }
        ItemVec* r2 = (ItemVec*)((WorldObj*)p2)->item_00b8dec0(0);
        if (r2) {
            int n = ((int)r2->mEnd - (int)r2->mBegin) >> 2;
            if (n) {
                uint k = ((Rng*)&g_rand)->next_00a68fb0(n);
                ((ItemElem*)r2->mBegin[k])->add_00ff0350((float)b);
            }
        }
    } else {
        ((Ad50*)this)->call_0103ad50(p1, ((WorldObj*)p2)->pos_00b8dad0(), a, 0);
        ((Ad50*)this)->call_0103ad50(p2, ((WorldObj*)p1)->pos_00b8dad0(), b, 0);
    }
}

// ===========================================================================
// EASTL helpers
// ===========================================================================
// @ 0x0103b0c0  eastl::vector<EA::AutoRefCount<SP::cNPCStore>, ...>::~vector
struct RefObj { char pad[8]; V4 base; };
struct VecDtor {
    void** mpBegin;    // +0
    void** mpEnd;      // +4
    void** mpCapacity; // +8
    void** mpFixed0;   // +0xc
    void** mpFixed;    // +0x10
    void dtor();
};
void VecDtor::dtor() {
    void** end = mpEnd;
    for (void** it = mpBegin; it < end; ++it) {
        void* p = *it;
        if (p) ((RefObj*)p)->base.Release();
    }
    void* begin = mpBegin;
    if (begin && begin != (void*)mpFixed) operator_delete(begin);
}

// @ 0x0103b100
void FUN_0103b100(void* stream, void* map) {
    int save = *(int*)((char*)map + 0x14);
    void* s = ((V20*)stream)->v20();
    int x = ((V18*)s)->v18();
    WriteUint32((void*)x, &save, 1, 0);
    int node = *(int*)((char*)map + 8);
    int stop = (int)map + 4;
    while (node != stop) {
        FUN_00ae2e40(stream, (void*)(node + 0x10));
        ((V1c*)stream)->v1c();
        int v = *(int*)(node + 0x1c);
        void* s2 = ((V20*)stream)->v20();
        int x2 = ((V18*)s2)->v18();
        WriteUint32((void*)x2, &v, 1, 0);
        ((V1c*)stream)->v1c();
        node = (int)RBTreeIncrement((void*)node);
    }
    ((V1c*)stream)->v1c();
}

// @ 0x0103b1b0  eastl heap adjust (AutoRefCount value + comparator function)
void FUN_0103a280(AutoRef* a, int top, int hole, AutoRef value, int (*fn)(int,int));
void FUN_0103b1b0(AutoRef* a, int top, int n, int start, AutoRef value, int (*fn)(int,int)) {
    int hole = start;
    int child = start * 2 + 2;
    while (child < n) {
        if (fn((int)a[child].mpRef, (int)a[child - 1].mpRef) != 0) --child;
        a[hole] = a[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == n) {
        a[hole] = a[child - 1];
        hole = child - 1;
    }
    FUN_0103a280(a, top, hole, value, fn);
}

// @ 0x0103a280  eastl heap sift-up (push_heap tail)
void FUN_0103a280(AutoRef* a, int top, int hole, AutoRef value, int (*fn)(int,int)) {
    while (hole > top) {
        int parent = (hole - 1) >> 1;
        if (fn((int)a[parent].mpRef, (int)value.mpRef) == 0) break;
        a[hole] = a[parent];
        hole = parent;
    }
    a[hole] = value;
}

// @ 0x0103b290  eastl pop_heap
void FUN_0103b290(AutoRef* a, AutoRef* b, int (*fn)(int,int)) {
    AutoRef value = b[-1];
    b[-1] = a[0];
    FUN_0103b1b0(a, 0, (int)(b - a) - 1, 0, value, fn);
}

// @ 0x0103b320
struct InvItems {
    void* list_00ff5b80();   // returns this+0x34
};
bool TSx::f_b320(int* prop) {
    void* self = this;
    int key[3] = { 0, 0, 0 };
    GetPropertyAsKey(prop, 0x35d5cb4, key);
    Vec3i k2;
    k2.x = key[0];
    k2.y = 0;
    k2.z = 0;
    void* inv = ((SpaceGame*)SpaceGameGet())->get_00a1ad60();
    if (((V74*)inv)->v74(&k2)) return false;
    void* list = ((InvItems*)((SpaceGame*)SpaceGameGet())->get_00a1ad60())->list_00ff5b80();
    for (void** it = *(void***)list; it != *(void***)((char*)list + 4); ++it) {
        if (((A630*)self)->f_0103a630(*it, k2.x, k2.y, k2.z)) return false;
    }
    return true;
}
