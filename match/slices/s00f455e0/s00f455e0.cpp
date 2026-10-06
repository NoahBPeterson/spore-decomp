// Slice s00f455e0 -- unnamed scenario/action system, slice 9 of bfs1.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ------------------------------------------------------------------ small shared types
struct IRef {
    virtual void AddRef();     // +0
    virtual void Release();    // +4
};
struct RefPtr { IRef* p; void assign(IRef* o); };   // EA::AutoRefCount<...>::operator=

struct Flagged { uint32_t m0; uint32_t m4; char pad8[0x54]; uint8_t m5c; };   // m4 |= 8, m5c = 1
struct InfoBase {
    // vtable: 43 placeholder slots then GetFlagged (offset 0xac)
    virtual void iv0();
    virtual void iv1();
    virtual void iv2();
    virtual void iv3();
    virtual void iv4();
    virtual void iv5();
    virtual void iv6();
    virtual void iv7();
    virtual void iv8();
    virtual void iv9();
    virtual void iv10();
    virtual void iv11();
    virtual void iv12();
    virtual void iv13();
    virtual void iv14();
    virtual void iv15();
    virtual void iv16();
    virtual void iv17();
    virtual void iv18();
    virtual void iv19();
    virtual void iv20();
    virtual void iv21();
    virtual void iv22();
    virtual void iv23();
    virtual void iv24();
    virtual void iv25();
    virtual void iv26();
    virtual void iv27();
    virtual void iv28();
    virtual void iv29();
    virtual void iv30();
    virtual void iv31();
    virtual void iv32();
    virtual void iv33();
    virtual void iv34();
    virtual void iv35();
    virtual void iv36();
    virtual void iv37();
    virtual void iv38();
    virtual void iv39();
    virtual void iv40();
    virtual void iv41();
    virtual void iv42();
    virtual Flagged* GetFlagged();
    char pad04[0x4c];
    uint32_t mFlags;          // +0x50
    char pad54[0x1a];
    uint8_t m6e;              // +0x6e
    char pad6f[9];
    uint8_t m78;              // +0x78
};
struct TypeA { char pad[0xb63]; uint8_t b63; char pad2[0xe78 - 0xb64]; uint8_t e78; };
struct TypeC { char pad[0xe68]; uint8_t e68; };
struct Obj : IRef {
    virtual void v2();
    virtual void* QueryInterface(uint32_t id);   // +0xc
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool IsX();                          // +0x2c
};

struct Elem {                      // 0x4e0 bytes
    uint8_t b0; char b1; uint8_t b2;
    char pad3[0x4bc - 3];
    uint32_t f4bc, f4c0, f4c4;
    char pad4c8[0x4e0 - 0x4c8];
};
struct SlotSub70 { void FUN_00f438f0(uint32_t n, void* tmp); };
struct Slot {                      // 0x27e8 bytes
    int mId;                       // +0
    char pad04[0x2c - 4];
    int mKind1;                    // +0x2c
    char pad30[0x50 - 0x30];
    int mKind2;                    // +0x50
    char pad54[0x70 - 0x54];
    Elem* mElems;                  // +0x70
    uint32_t m74;
    Elem* mVecBegin;               // +0x78
    Elem* mVecEnd;                 // +0x7c
    char pad80[0x2790 - 0x80];
    char sub2790[0x27e8 - 0x2790];
    bool FUN_00f25ed0();
    bool FUN_00f25360();
    void FUN_00dfee80(void* p);
};
struct PoolNode {                  // 0x238 bytes
    uint32_t mFlags;               // +0
    uint32_t mId;                  // +4
    char pad08[0x228 - 8];
    uint32_t mBits;                // +0x228
    uint32_t mKey;                 // +0x22c
    char pad230[8];
};
struct Pool {                      // at State+0x2c10
    char* mBase;
    char* mEnd;
    char pad08[0xc];
    uint32_t mCount;               // +0x14
    void FUN_00f410f0(uint32_t key);
    uint32_t IndexOf(void* node);  // W::IndexOf (0x00f3c100)
};
struct SlotVec {                   // at State+0x2bf4
    Slot* b;
    Slot* e;
    char pad08[0xc];
    uint8_t mFlag;                 // +0x14
    char pad15[3];
    int mNextId;                   // +0x18
    Slot* FUN_00ed37c0(const uint32_t* id);
};
struct State {
    char pad00[0x68];
    int a68, a6c, a70, a74;
    char pad78[0x150 - 0x78];
    float f150, f154, f158, f15c;
    char pad160[0x23c - 0x160];
    char* m23c;
    char* m240;
    char pad244[0x2bf4 - 0x244];
    SlotVec slots;                 // +0x2bf4
    Pool pool;                     // +0x2c10
};

struct MsgServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t id, uint32_t a, int b);      // +0x14
};
struct HashNode { uint32_t key; uint32_t val; HashNode* next; };
struct Vec3W { uint32_t* p; uint32_t b, c; };

struct Mgr { void FUN_b22960(); };
struct Scenario9;
struct S2790 { void FUN_00f280f0(); };
extern uint32_t g16c87f8, g16c87fc, g16c8800;
struct Reg15 { void FUN_00efc6c0(uint32_t id); };
extern Reg15 g15ad328;
void* __cdecl SP_NounManager();            // 0x00b3d300
struct NounMgr { uint32_t GetAvatar(); };  // 0x00b1fdb0
MsgServer* __cdecl EA_Messaging_GetServer();
void __cdecl operator_delete__(void*);
struct Obj52 { void FUN_00b52020(); };
Obj52* __stdcall FUN_00b3d310(void* p);
void __cdecl FUN_00eef570(uint32_t v, Vec3W* out);
void __cdecl FUN_00eec940(Vec3W* v, int x);
void __cdecl FUN_00eef4b0(Vec3W* v);
Slot* __cdecl FUN_00ed29b0(Slot* b, Slot* e, int* id, uint8_t flag);
void __cdecl FUN_00dff2f0(Slot* a, Slot* b, Slot* c);
InfoBase* __cdecl FUN_00b18e00(Obj* o);
Obj* __cdecl FUN_00eec0d0(uint32_t* pId);
Obj* __cdecl FUN_00f3fa20(Scenario9* self /* passed in eax */, Slot* slot, int idx);
void __cdecl FUN_00f20d80(void* p);
void __cdecl FUN_00f42a50(void* b, int param /* usercall: eax=param, esi=b */);
struct HashA { uint32_t* FUN_00b474c0(Obj** pp); };
struct HashB { RefPtr* FUN_00b6ff20(uint32_t* key); };

// ---- helper objects of 0x4e0 / 0x27d0 bytes living on the stack of 0x00f46450
struct TmpB { uint32_t d[0x138]; void FUN_00f2d680(); void FUN_00dfbba0(); };
struct TmpA { uint32_t d[0x9f8]; void* FUN_00f2d260(); void FUN_00dfce90(); };

// ---- objects owned by the scenario (smart-ref'd)
struct RefObj : IRef {             // 0x2cb0 bytes
    char pad[0x2cb0 - 4];
    RefObj();                      // 0x00f2e7d0
    void FUN_00dffa30(State* s);
};
struct Holder { char pad[0x14]; RefObj* mpRef; };
struct IFace : IRef {
    virtual void v2();
    virtual Holder* Query(uint32_t id);    // +0xc
};
struct Reg { IFace* FUN_00f31ee0(); void FUN_00f342d0(Holder* h); };
extern Reg g16065d8;
extern uint8_t g16065f8;
extern uint32_t g16065ec;
extern IFace* g16065fc;
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
struct Scenario9;
struct ScnObj : IFace {            // 0x18 bytes
    char pad[0x14];
    ScnObj(Scenario9* s, RefObj* r, int z);   // 0x00f3cc40
};

struct Scenario9 {
    char  pad00[0x10];
    State* mpManager;                                // +0x10
    char  pad14[0x18 - 0x14];
    int   mField18;                                  // +0x18
    char  pad1c[0x2c - 0x1c];
    char  mField2C;                                  // +0x2c
    char  pad2d[0x3c - 0x2d];
    int   mField3C;                                  // +0x3c
    int   mField40;                                  // +0x40
    int   mField44;                                  // +0x44
    int   mField48;                                  // +0x48
    char  pad4c[0x8c - 0x4c];
    uint32_t* mpAvatarId;                            // +0x8c
    HashA mTabA;                                     // +0x90
    char  pad94[0xb0 - 0x94];
    HashB mTabB;                                     // +0xb0
    HashNode** mBuckets;                             // +0xb4
    uint32_t mBucketCount;                           // +0xb8

    void Sub41300();                                 // 0x00f41300
    void Sub3cf10(int);                              // 0x00f3cf10
    bool f44fe0();                                   // 0x00f44fe0
    void FUN_00f3bc20(uint32_t id);
    void FUN_00f3fd90(uint32_t* pId);                // ScenarioNode_Destroy
    void FUN_00f414b0();
    void FUN_00f427c0();
    void FUN_00f43af0(int id, int p);
    void FUN_00f3da90(uint32_t* pId, int z);
    void FUN_00f3c610(Obj* o);
    Obj* FUN_00f3d780(uint32_t* pId);
    void FUN_00f43420(float* a, float* b);
    void f45c30(int mode, int idx, char c4, char c5);   // 0x00f45c30
    int  f46020(int mode, int ia, int ib, char c4, char c5);  // 0x00f46020

    void f455e0(uint32_t id);                        // 0x00f455e0
    void f45970();                                   // 0x00f45970
    void f45a80();                                   // 0x00f45a80
    bool f45b50();                                   // 0x00f45b50
    void f45fd0(int a, int b, char c);               // 0x00f45fd0
    void f46410(int a, int b, int c);                // 0x00f46410
    int  f46450(int a);                              // 0x00f46450
};

// ------------------------------------------------------------------ wrappers (byte-exact)
// @ 0x00f45fd0
void Scenario9::f45fd0(int a, int b, char c)
{
    if (c == 0)
        Sub41300();
    f45c30(a, b, 1, 1);
    ((Mgr*)SP_NounManager())->FUN_b22960();
    f45c30(a, b, 0, 0);
}

// @ 0x00f46410
void Scenario9::f46410(int a, int b, int c)
{
    f46020(a, b, c, 1, 1);
    ((Mgr*)SP_NounManager())->FUN_b22960();
    f46020(a, b, c, 0, 0);
}

// ------------------------------------------------------------------ helpers
static inline PoolNode* PoolStart(State* s)
{
    if (s->pool.mCount < 0x3fffffff)
        return (PoolNode*)s->pool.mBase + s->pool.mCount;
    return (PoolNode*)s->pool.mEnd;
}

// ------------------------------------------------------------------ 0x00f455e0
// Remove scenario object `id`: clears references to it, destroys its pool nodes, drops the slot.
void Scenario9::f455e0(uint32_t id)
{
    int sid = (int)id;
    State* s = mpManager;
    Slot* end = s->slots.e;
    Slot* found = FUN_00ed29b0(s->slots.b, end, &sid, s->slots.mFlag);
    if (found == end || sid < found->mId)
        found = end;
    if (end == found)
        return;
    FUN_00f3bc20(id);
    Slot* sl = mpManager->slots.b;
    Slot* slEnd = mpManager->slots.e;
    if (sl != slEnd) {
        do {
            int n = (int)(sl->mVecEnd - sl->mVecBegin);
            Elem* e = sl->mVecBegin;
            for (; n != 0; --n, ++e) {
                if (e->f4bc == id) e->f4bc = 0xffffffff;
                if (e->f4c0 == id) e->f4c0 = 0xffffffff;
                if (e->f4c4 == id) e->f4c4 = 0xffffffff;
            }
            ++sl;
        } while (sl != slEnd);
    }

    s = mpManager;
    PoolNode* cur = PoolStart(s);
    if (s->pool.mEnd != (char*)cur) {
        do {
            PoolNode* p;
            uint32_t fl;
            do {
                p = cur;
                fl = cur->mFlags;
                ++cur;
                if ((fl >> 0x1e) & 1)
                    break;
            } while ((cur->mFlags >> 0x1f) & 1);
            uint32_t* pId = &p->mId;
            if (*pId == id) {
                Vec3W vec;
                vec.p = 0; vec.b = 0; vec.c = 0;
                uint32_t ov;
                if (pId == mpAvatarId) {
                    ov = ((NounMgr*)SP_NounManager())->GetAvatar();
                } else {
                    uint32_t key = p->mKey;
                    uint32_t idx = key % mBucketCount;
                    HashNode* hn = mBuckets[idx];
                    for (; hn; hn = hn->next) {
                        if (hn->key == key)
                            break;
                    }
                    ov = hn ? hn->val : 0;
                }
                FUN_00eef570(ov, &vec);
                uint32_t oid = *pId;
                FUN_00f3fd90(pId);
                if (oid == 0xfffffffe) {
                    State* st = mpManager;
                    *(uint32_t*)&st->f150 = g16c87f8;
                    *(uint32_t*)&st->f154 = g16c87fc;
                    *(uint32_t*)&st->f158 = g16c8800;
                } else {
                    mpManager->pool.FUN_00f410f0(p->mKey);
                }
                EA_Messaging_GetServer()->Post(0x7311ff7, oid, 0);
                FUN_00eec940(&vec, 0);
                FUN_00eef4b0(&vec);
                if (vec.p && vec.p[-1] != 0)
                    operator_delete__(vec.p);
            }
        } while (mpManager->pool.mEnd != (char*)cur);
    }

    // release the objects held by the slot
    int k = found->mKind1;
    char* o = (char*)found + 8;
    if (k >= 0) {
        if (k > 1) {
            if (k != 2)
                goto skip1;
            o = (char*)found + 0x30;
        }
        FUN_00b3d310(o)->FUN_00b52020();
    }
skip1:
    if (found->mKind2 == 2) {
        char* o2 = (char*)found + 0x58;
        FUN_00b3d310(o2)->FUN_00b52020();
    }
    s = mpManager;
    if (found + 1 < s->slots.e)
        FUN_00dff2f0(found + 1, s->slots.e, found);
    s->slots.e = s->slots.e - 1;
    Slot* last = s->slots.e;
    ((S2790*)last->sub2790)->FUN_00f280f0();
    Elem* eb = last->mVecEnd;
    for (Elem* e = last->mVecBegin; e < eb; ++e)
        ((TmpB*)e)->FUN_00dfbba0();
    Elem* arr = last->mVecBegin;
    if (arr && ((int*)arr)[-1] != 0)
        operator_delete__(arr);
    FUN_00f414b0();
    g15ad328.FUN_00efc6c0(id);
    FUN_00f427c0();
}

// ------------------------------------------------------------------ 0x00f45970
void Scenario9::f45970()
{
    if (!g16065f8)
        return;
    Holder* h = 0;
    if (g16065ec > 0) {
        IFace* r = g16065d8.FUN_00f31ee0();
        h = r ? r->Query(0x743bb11) : 0;
    }
    RefObj* ref = 0;
    if (h) {
        RefObj* r = h->mpRef;
        if (r) {
            r->AddRef();
            ref = r;
        }
    } else {
        RefObj* r = new ("Simulator", 0, 0, 0, 0) RefObj();
        if (r) {
            r->AddRef();
            ref = r;
        }
        ref->FUN_00dffa30(mpManager);
    }
    ScnObj* n = new ("Simulator", 0, 0, 0, 0) ScnObj(this, ref, 0);
    IFace* old = g16065fc;
    if (n != old) {
        if (n)
            n->AddRef();
        g16065fc = n;
        if (old)
            old->Release();
    }
    g16065f8 = 0;
    if (ref)
        ref->Release();
}

// ------------------------------------------------------------------ 0x00f45a80
void Scenario9::f45a80()
{
    if (g16065f8 == 0 && g16065fc) {
        Holder* h = g16065fc->Query(0x743bb11);
        if (h) {
            RefObj* r = new ("Simulator", 0, 0, 0, 0) RefObj();
            RefObj* old = h->mpRef;
            if (r != old) {
                if (r)
                    r->AddRef();
                h->mpRef = r;
                if (old)
                    old->Release();
            }
            h->mpRef->FUN_00dffa30(mpManager);
            g16065f8 = 1;
            g16065d8.FUN_00f342d0(h);
            IFace* f = g16065fc;
            if (f) {
                g16065fc = 0;
                f->Release();
            }
        }
    }
}

// ------------------------------------------------------------------ 0x00f45b50
bool Scenario9::f45b50()
{
    switch (mField18) {
    case 1: {
        if (mField2C == 0)
            return false;
        State* s = mpManager;
        uint8_t dl = 0;
        if (s->a68 == 1 && mField3C == 0)
            s->a68 = 0;
        s = mpManager;
        if (s->a68 != 3)
            dl = 1;
        if (s->a6c == 1 && mField40 == 0)
            s->a6c = dl ? 3 : 0;
        s = mpManager;
        if (s->a6c != 3)
            dl = 1;
        if (s->a70 == 1 && mField44 == 0)
            s->a70 = dl ? 3 : 0;
        s = mpManager;
        if (s->a70 != 3)
            dl = 1;
        if (s->a74 == 1 && mField48 == 0)
            s->a74 = dl ? 3 : 0;
        int i = 0;
        int* p = &mpManager->a68;
        do {
            if (*p == 0) {
                mField18 = 2;
                Sub3cf10(1);
                return false;
            }
            ++i;
            ++p;
        } while (i < 4);
        return f44fe0();
    }
    case 2:
        if (mField2C != 0)
            return f44fe0();
        break;
    }
    return false;
}

// ------------------------------------------------------------------ 0x00f45c30
// Register/unregister the scenario objects of every pool node for action `idx` (mode 1/2).
static inline Obj* RegisterObj(Scenario9* self, PoolNode* it, Slot* slot, int idx)
{
    Obj* o = FUN_00f3fa20(self, slot, idx);
    uint32_t* pKey = &it->mKey;
    *pKey = (uint32_t)(((char*)it - self->mpManager->pool.mBase) / 0x238);
    Obj* tmp = o;
    uint32_t* pv = self->mTabA.FUN_00b474c0(&tmp);
    *pv = *pKey;
    RefPtr* rp = self->mTabB.FUN_00b6ff20(pKey);
    IRef* old = rp->p;
    if (o != old) {
        if (o)
            o->AddRef();
        rp->p = o;
        if (old)
            old->Release();
    }
    return o;
}

void Scenario9::f45c30(int mode, int idx, char c4, char c5)
{
    bool idxIsM1 = idx == -1;
    if (idxIsM1)
        idx = 0;
    State* s = mpManager;
    PoolNode* it = PoolStart(s);
    PoolNode* end = (PoolNode*)s->pool.mEnd;
    if (end != it) {
        do {
            uint32_t* pId = &it->mId;
            Slot* slot = mpManager->slots.FUN_00ed37c0(pId);
            char cVar3 = ((char*)slot->mElems)[idx * 0x4e0];
            if (mode == 1) {
                Obj* o;
                if (c4 == 0)
                    o = FUN_00eec0d0(pId);
                else
                    o = RegisterObj(this, it, slot, idx);
                if (o) {
                    InfoBase* info = FUN_00b18e00(o);
                    if (((info->mFlags & 0x2000) != 0x2000) != (bool)c5) {
                        FUN_00f3da90(pId, 0);
                        if (cVar3 == 0)
                            info->m78 = 1;
                        uint32_t bits = it->mBits;
                        if (((bits >> 4) & 1) || ((bits >> 1) & 1) || ((bits >> 2) & 1)) {
                            InfoBase* i2 = FUN_00b18e00(o);
                            i2->m6e = 1;
                            Flagged* f = i2->GetFlagged();
                            if (f) {
                                f->m4 |= 8;
                                f->m5c = 1;
                            }
                        }
                    }
                }
            } else if (mode == 2) {
                if ((cVar3 != 0 || idxIsM1)) {
                    uint32_t bits = it->mBits;
                    if (((bits >> 4) & 1) == 0 && ((bits >> 1) & 1) == 0 && ((bits >> 2) & 1) == 0) {
                        Obj* o;
                        if (c4 == 0)
                            o = FUN_00eec0d0(pId);
                        else
                            o = RegisterObj(this, it, slot, idx);
                        if (o) {
                            InfoBase* info = FUN_00b18e00(o);
                            if (((info->mFlags & 0x2000) != 0x2000) != (bool)c5) {
                                FUN_00f3da90(pId, 0);
                                FUN_00f3c610(o);
                            }
                        }
                    }
                }
            }
            uint32_t fl;
            do {
                fl = it->mFlags;
                ++it;
                if ((fl >> 0x1e) & 1)
                    break;
            } while ((it->mFlags >> 0x1f) & 1);
        } while (end != it);
    }
    if (c4) {
        State* st = mpManager;
        if (st->f150 != *(float*)&g16c87f8 || st->f154 != *(float*)&g16c87fc ||
            st->f158 != *(float*)&g16c8800)
            FUN_00f43420(&mpManager->f150, &mpManager->f15c);
    }
}

// ------------------------------------------------------------------ 0x00f46020
// Compare two element rows (ia, ib) of every slot and sync the objects whose state differs.
int Scenario9::f46020(int mode, int ia, int ib, char c4, char c5)
{
    State* s = mpManager;
    PoolNode* it = PoolStart(s);
    PoolNode* end = (PoolNode*)s->pool.mEnd;
    if (end == it)
        return 0;
    int offB = ib * 0x4e0;
    int offA = ia * 0x4e0;
    do {
        uint32_t* pId = &it->mId;
        Slot* slot = mpManager->slots.FUN_00ed37c0(pId);
        char* base = (char*)slot->mElems;
        uint8_t a2 = base[offA + 2];
        uint8_t a0 = base[offA];
        uint8_t b0 = base[offB];
        uint8_t b2 = base[offB + 2];
        if (a0 == b0) {
            if (mode == 2 && b0 != 0) {
                Obj* o;
                bool direct = false;     // taken when we only need the node itself
                if (!slot->FUN_00f25ed0()
                    && ((b2 != 0 && slot->FUN_00f25360()) ||
                        (a2 != 0 && b2 == 0 && !slot->FUN_00f25360()))) {
                    Obj* node = FUN_00f3d780(pId);
                    bool skip = false;
                    if (node) {
                        TypeA* r2 = (TypeA*)node->QueryInterface(0xd0036e08);
                        bool x = node->IsX();
                        if (!x && (!r2 || !r2->b63))
                            skip = true;
                        else if (r2 && r2->e78 == 1)
                            skip = true;
                    }
                    if (skip) {
                        o = node;
                        goto touch;
                    }
                    if (c4 != 0) {
                        Obj* n2 = FUN_00f3fa20(this, slot, ib);
                        uint32_t* pKey = &it->mKey;
                        *pKey = mpManager->pool.IndexOf(it);
                        Obj* tmp = n2;
                        uint32_t* pv = mTabA.FUN_00b474c0(&tmp);
                        *pv = *pKey;
                        mTabB.FUN_00b6ff20(pKey)->assign(n2);
                        o = n2;
                    } else {
                        o = node;
                    }
                    if (!o)
                        goto next;
                    {
                        InfoBase* info = FUN_00b18e00(o);
                        if (((info->mFlags & 0x2000) != 0x2000) != (bool)c5) {
                            FUN_00f3da90(pId, 0);
                            FUN_00f3c610(o);
                        }
                    }
                } else {
                    o = FUN_00f3d780(pId);
                    if (c4 == 0)
                        FUN_00f3c610(o);
                }
touch:
                if (o) {
                    TypeC* q = (TypeC*)o->QueryInterface(0xce9f6639);
                    if (q)
                        q->e68 = 0;
                }
            }
        } else if (mode == 1) {
            if (c4 == 0) {
                InfoBase* info = FUN_00b18e00(FUN_00f3d780(pId));
                if (info)
                    info->m78 = (b0 == 0);
            }
        } else if (mode == 2) {
            if (b0 == 0) {
                if (c4 != 0) {
                    if (slot->FUN_00f25ed0()) {
                        Obj* node = FUN_00f3d780(pId);
                        void* q = 0;
                        if (node) {
                            char* t = (char*)node->QueryInterface(0x175cdc9);
                            if (t)
                                q = t + 0x34;
                        }
                        FUN_00f20d80(q);
                    }
                    FUN_00f3fd90(pId);
                }
            } else {
                Obj* o;
                if (c4 == 0) {
                    o = FUN_00f3d780(pId);
                } else {
                    o = RegisterObj(this, it, slot, ib);
                }
                if (o) {
                    InfoBase* info = FUN_00b18e00(o);
                    if (((info->mFlags & 0x2000) != 0x2000) != (bool)c5) {
                        FUN_00f3da90(pId, 0);
                        FUN_00f3c610(o);
                    }
                }
            }
        }
next:
        uint32_t fl;
        do {
            fl = it->mFlags;
            ++it;
            if ((fl >> 0x1e) & 1)
                break;
        } while ((it->mFlags >> 0x1f) & 1);
    } while (end != it);
    return 0;
}

// ------------------------------------------------------------------ 0x00f46450
int Scenario9::f46450(int param)
{
    State* s = mpManager;
    if ((int)(s->slots.e - s->slots.b) >= 0x400)
        return -1;
    int id = s->slots.mNextId;
    s->slots.mNextId = id + 1;
    uint32_t idv = (uint32_t)id;
    Slot* ns = mpManager->slots.FUN_00ed37c0(&idv);
    TmpA a;
    ns->FUN_00dfee80(a.FUN_00f2d260());
    a.FUN_00dfce90();
    FUN_00f43af0(id, param);
    TmpB b;
    b.FUN_00f2d680();
    FUN_00f42a50(&b, param);
    ((SlotSub70*)((char*)ns + 0x70))->FUN_00f438f0((uint32_t)((mpManager->m240 - mpManager->m23c) / 0x534), &b);
    b.FUN_00dfbba0();
    return id;
}
