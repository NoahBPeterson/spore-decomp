// Slice s0103a480: SP::cSPSpaceTrading commodity/rare-commodity helpers + EASTL vector/heap helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

struct Obj { void* vptr; };

// generic vtable wrappers (each starts with a vptr, so a cast reaches the right slot)
struct V0c { virtual void z0(); virtual void z1(); virtual void z2(); virtual void* v0c(int); };
struct V14 { virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
             virtual void z4(); virtual void v14(int); };
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
             virtual bool v70(void* k); };
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
void  RBTreeIncrement(void* node);                                             // 0x00921580
void  WriteUint32(void* stream, const void* v, int a, int b);                  // 0x0093aa70
void  FUN_00ae2e40(void* a, void* b);                                          // 0x00ae2e40
void  FUN_00ff0350(float f);                                                   // 0x00ff0350
void  FUN_00c731a0(int a, int b, int c, int d, int e, int f, int g, int h, int i);  // 0x00c731a0
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
void* FUN_00572590(void* a, int b);                                            // 0x00572590
void* FUN_00b81780(void* out, void* model, float a, float b, float c);         // 0x00b81780
void* FUN_00b7f190(void* model, void* out, void* in);                          // 0x00b7f190
void* FUN_00c74d30(void* artifact, int a, int b, void* c);                     // 0x00c74d30
void* FUN_00c87660(void* p);                                                   // 0x00c87660
void  FUN_00ff0350_(float f);                                                  // 0x00ff0350
void* FUN_00e5c780(void* a, void* b, void* c);                                 // eastl rbtree find helper
uint  RandomUint32Uniform(void* rng, int n);                                   // 0x00a68fb0
double RandomDoubleUniform(void* rng);                                         // 0x009360d0

extern void* g_rand;              // 0x01601760
extern float g_16df56c, g_16df570, g_16df574;
extern float g_16df53c, g_16df540, g_16df544;
extern float g_13f4fd0;

// ---------------------------------------------------------------------------
// @ 0x0103a480  SP::cSPSpaceTrading::CreateCommodityFromID
// ---------------------------------------------------------------------------
struct Commodity {
    char pad0[0x10];
    int   mItemCount;    // +0x10
    int   mType;         // +0x14
    int   mCost;         // +0x18
};
void FUN_0103a480(void** out, int* id, int count, float cost) {
    void* item = operator_new(0x7c, "Simulator/cSpaceInventoryItem", 0, 0, 0, 0);
    void* inst = item ? FUN_00c87660(item) : 0;
    IUnk* local = 0;
    PropertyMgr* pm = (PropertyMgr*)PropertyManager();
    if (local) {
        IUnk* old = local; local = 0; old->Release();
    }
    pm->Unregister(*id, 0x34d97fa, &local);
    ((V14*)inst)->v14(*id);
    Commodity* c = (Commodity*)inst;
    c->mType = 4;
    c->mItemCount = count;
    c->mCost = (int)cost;
    SetPropertyList(inst, local);
    ((V4*)inst)->AddRef();
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
bool FUN_0103a630(void* self, int a, int b, int c) {
    (void)self;
    if (a == 0) return false;
    void* pi = (void*)((HashObj*)(*(void**)((char*)a + 0xc)))->v3(0x707459f0);
    if (pi == 0) return false;
    Vec3i v;
    Vec3i* got = (Vec3i*)((V38*)pi)->v38();
    (void)got;
    // placeholder body
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0103a760
// ---------------------------------------------------------------------------
struct T760 {
    char pad0[0xbc];
    int* mBegin;   // +0xbc
    int* mEnd;     // +0xc0
    uint find(int id);
};
uint T760::find(int id) {
    int total = (int)mEnd - (int)mBegin;
    int n = total / 0x24;
    uint i = 0;
    if (n == 0) return 0;
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
struct SPTrading {
    char pad0[0x2c];
    int* mBegin;   // +0x2c
    int* mEnd;     // +0x30
};
bool FUN_0103a7d0(SPTrading* self, int msg, void* arg) {
    if (msg < 0x4445d43 || msg > 0x4445d44) return false;
    int a = *(int*)((char*)arg + 8);
    int b = *(int*)((char*)arg + 0x10);
    int player = (int)GetPlayerEmpire();
    int target;
    if (a == player) target = b;
    else if (b == player) target = a;
    else return false;
    int count = (int)(self->mEnd - self->mBegin) >> 2;
    bool found = false;
    int i = 0;
    if (count > 0) {
        do {
            void* entry = (void*)self->mBegin[i];
            int id = *(int*)((char*)entry + 0xc);
            void* q = FUN_00ba6dc0(id);
            // ... complex; approximate
            (void)q; (void)found; (void)target;
            ++i;
        } while (i < (int)(self->mEnd - self->mBegin) >> 2);
    }
    return false;
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
void FUN_0103aa00(void* self, void* p2) {
    int count = (*(int*)((char*)self + 0x38) - *(int*)((char*)self + 0x34)) / 0xc;
    if (GetCurrentGameMode() != 0x1654c05) return;
    if (*(int*)((char*)p2 + 0x28) <= 1) return;
    if (FUN_00b8d970(p2)) return;
    if (GetPlayerEmpire() == 0) return;
    int e1 = FUN_00c30c60();
    if ((int)FUN_00b8de30(p2) == e1) return;
    if (!FUN_0103a930((int*)((char*)self + 0x34))) return;
    // body: scan rare list, random chance, spawn pile — approximate
    (void)count;
}

// ---------------------------------------------------------------------------
// @ 0x0103ac40
// ---------------------------------------------------------------------------
struct RBTreeT {
    void** find(int* k);   // 0x00a21dc0
};
struct TAC40 {
    char pad0[0xa0];
    void* find(int* key);
};
void* TAC40::find(int* key) {
    int k = *key;
    void** node = ((RBTreeT*)((char*)this + 0xa0))->find(&k);
    if (*node != (void*)((char*)this + 0xa4)) return *(void**)((char*)*node + 0x1c);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0103ac70  SP::cSPSpaceTrading::IsRareGroupComplete
// ---------------------------------------------------------------------------
bool FUN_0103ac70(void* self, int group, bool needInventory) {
    int base = *(int*)((char*)self + 0xbc) + group * 0x24;
    int n = (*(int*)(base + 0x14) - *(int*)(base + 0x10)) / 0xc;
    if (n == 0) return true;
    int idx = 0;
    int i = 0;
    int count = n;
    do {
        int* arr = (int*)(*(int*)((char*)self + 0xbc) + group * 0x24 + 0x10);
        int key[3];
        key[0] = *arr;
        key[1] = arr[1];
        key[2] = arr[2];
        extern void* RBFind(void* tree, int* k);   // 0x00a21dc0
        void** node = (void**)RBFind((char*)self + 0xa0, key);
        (void)idx;
        if (*node == (char*)self + 0xa4) return false;
        if (*(int*)((char*)*node + 0x1c) != 1) return false;
        if (needInventory) {
            void* inv = GetPlayerInventoryOf(SpaceGameGet());
            if (!((V70*)inv)->v70(key)) return false;
        }
        ++arr;
        ++i;
        (void)arr;
        idx += 0xc;
    } while (i < count);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0103ad50  SP::cSPSpaceTrading::AddCitySpicePile
// ---------------------------------------------------------------------------
void FUN_0103ad50(void* self, int* p2, int a3, int a4) {
    if ((*(int*)((char*)self + 0x160) - *(int*)((char*)self + 0x15c)) == 0) return;
    void* bp = FUN_00b8dec0(0);
    int cnt = (*(int*)((char*)bp + 0x40) - *(int*)((char*)bp + 0x3c)) >> 2;
    if (cnt == 0) return;
    uint matches = 0;
    for (int* q = *(int**)((char*)self + 0x134); q != *(int**)((char*)self + 0x138); q += 0xb)
        if (*q == *p2) ++matches;
    if (matches >= (uint)(cnt * 2)) return;
    // ... complex pile placement — approximate
    (void)a3; (void)a4;
}

// ---------------------------------------------------------------------------
// @ 0x0103af90
// ---------------------------------------------------------------------------
void FUN_0103af90(void* p1, void* p2) {
    int a = (int)RandomUint32Uniform(g_rand, 4) + 1;
    int b = (int)RandomUint32Uniform(g_rand, 4) + 1;
    int* v1 = (int*)FUN_00b8dad0(p1, 0);
    int* v2 = (int*)FUN_00b8dad0(p2, 0);
    if (v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2]) {
        void* r = FUN_00b8dec0(0);
        if (r) {
            int n = (*(int*)((char*)r + 0x40) - *(int*)((char*)r + 0x3c)) >> 2;
            if (n) {
                int k = (int)RandomUint32Uniform(g_rand, n);
                FUN_00ff0350((float)a);
                (void)k;
            }
        }
        void* r2 = FUN_00b8dec0(0);
        if (r2) {
            int n = (*(int*)((char*)r2 + 0x40) - *(int*)((char*)r2 + 0x3c)) >> 2;
            if (n) {
                int k = (int)RandomUint32Uniform(g_rand, n);
                FUN_00ff0350((float)b);
                (void)k;
            }
        }
    } else {
        FUN_0103ad50(p1, (int*)FUN_00b8dad0(p1, 0), a, 0);
        FUN_0103ad50(p2, (int*)FUN_00b8dad0(p2, 0), b, 0);
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
    if (node == stop) return;   // note: tail path differs; approximate
    while (node != stop) {
        FUN_00ae2e40(stream, (void*)(node + 0x10));
        ((V1c*)stream)->v1c();
        int v = *(int*)(node + 0x1c);
        void* s2 = ((V20*)stream)->v20();
        int x2 = ((V18*)s2)->v18();
        WriteUint32((void*)x2, &v, 1, 0);
        ((V1c*)stream)->v1c();
        RBTreeIncrement((void*)node);
    }
}

// @ 0x0103b1b0  eastl heap adjust (AutoRefCount comparator)
void FUN_0103a280(int* a, int b, int n);
void FUN_0103b1b0(int* a, int param2, int n, int start, int* cmp, int (*fn)(int,int)) {
    for (;;) {
        int c = start * 2 + 2;
        if (c >= n) break;
        if (fn(a[c], a[c - 1]) != 0) --c;
        int* cur = &a[start];
        int* next = &a[c];
        if (*next != *cur) {
            if (*next) ((V4*)(*next))->AddRef();
            *cur = *next;
            if (cur) ((V4*)(cur))->Release();
        }
        start = c;
    }
    if (start * 2 + 2 == n) {
        int c = start * 2 + 2;
        int* cur = &a[start];
        int* next = &a[c - 1];
        if (*next != *cur) {
            if (*next) ((V4*)(*next))->AddRef();
            *cur = *next;
            if (cur) ((V4*)(cur))->Release();
        }
        start = c - 1;
    }
    if (cmp) ((V4*)(cmp))->AddRef();
    FUN_0103a280(a, param2, start);
    if (cmp) ((V4*)(cmp))->Release();
}

// @ 0x0103a280
void FUN_0103a280(int* a, int b, int n) {
    (void)a; (void)b; (void)n;
}

// @ 0x0103b290
void FUN_0103b290(int* a, int b, int c) {
    if (*(int*)(b - 4)) ((V4*)(*(int*)(b - 4)))->AddRef();
    if (a[0] != *(int*)(b - 4)) {
        if (a[0]) ((V4*)(a[0]))->AddRef();
        *(int*)(b - 4) = a[0];
        if (*(int*)(b - 4)) ((V4*)(*(int*)(b - 4)))->Release();
    }
    FUN_0103b1b0(a, 0, (b - (int)a) / 4 - 1, 0, 0, 0);
    (void)c;
}

// @ 0x0103b320
bool FUN_0103b320(void* self, int* prop) {
    int key[3];
    key[0] = key[1] = key[2] = 0;
    GetPropertyAsKey(prop, 0x35d5cb4, key);
    int k2[3] = { key[0], 0, 0 };
    void* inv = GetPlayerInventoryOf(SpaceGameGet());
    if (((V74*)inv)->v74(k2)) return false;
    void* inv2 = GetPlayerInventoryOf(SpaceGameGet());
    void* list = FUN_00ff5b80();
    (void)inv2;
    int* it = *(int**)list;
    int* end = *(int**)((char*)list + 4);
    while (it != end) {
        if (FUN_0103a630(self, *it, k2[0], k2[1])) return false;
        ++it;
    }
    return true;
}
