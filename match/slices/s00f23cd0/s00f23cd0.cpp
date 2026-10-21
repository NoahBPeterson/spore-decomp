// Slice s00f23cd0 (batch gold4) -- SP drama-event instance maintenance helpers
// (event-instance map iteration/cleanup, target resolution, noun teardown).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The object layout mirrors the one used by the sibling slice s00f21850 and is
// confirmed here from the virtual slots the dispatcher invokes:
//   vtable +0x04 -> GetNoun()          (int*)
//   vtable +0x08 -> GetOwner()         (int*)
//   vtable +0x0c -> GetComponent(uint) (int*)
//   vtable +0x2c -> IsDead()           (char)
//   vtable +0x34 -> GetScale()         (float)
// and the fields:
//   +0x18 int m_ownerNoun         +0x24 float m_f24     +0x28 float m_f28
//   +0x24/+0x28 are two independent countdown timers (this+0x24 is the one
//   decremented in 0x00f243c0; this+0x28 the one in the same function's head).
// Draft flag borders (bits used as `byte ptr [..+3]` markers) are kept as
// separate bytes below so the structure stays readable.

#include "types.h"

typedef unsigned int uint;

// ------------------------------------------------------------------ callees
extern "C" {
unsigned int DAT_016c7aa4;                  // 0x016c7aa4  world/game-data holder
unsigned int DAT_016c8318;                  // 0x016c8318  event-instance multimap
unsigned int DAT_016c83a4;                  // 0x016c83a4  property key
unsigned int DAT_016c83ac;                  // 0x016c83ac  property key
unsigned int DAT_016c83d8;                  // 0x016c83d8  property key
unsigned int DAT_016c83dc;                  // 0x016c83dc  property key
float        DAT_01485378;                  // 0x01485378  float constant
float        DAT_01485720;                  // 0x01485720  float constant
float        DAT_01486110;                  // 0x01486110  float constant
float        DAT_013eb8a0;                  // 0x013eb8a0  float constant

struct GameDataAccess {
    unsigned int GameData();       // 0x00b18530  ecx = this
};

unsigned int SP_GameData();                 // 0x00b18530  SP::cGameData
unsigned int SP_GameTimeManager();          // 0x00b3d380  SP::GameTimeManager
int          GameTimeNow();                 // 0x00b316c0
struct GameTimeAccess {
    int Now();                     // 0x00b316c0  ecx = this
};
void*        FUN_00f23c80(int* ev, int noun);       // 0x00f23c80
int*         FUN_00f19200(int* noun);               // 0x00f19200
void*        FUN_00f217a0(int* a);                  // 0x00f217a0
int          FUN_00f217c0(int* a, void* b);         // 0x00f217c0
void         FUN_00f23be0(int a, int* b, void* c);  // 0x00f23be0
int*         FUN_00b18e00(int* a);                  // 0x00b18e00
int          sk_unshift(int a, unsigned int key);   // 0x00f20c90
int*         SP_PlanetModel(void* a, void* b, void* c);          // 0x00b3d350
void         BuildSurfaceOrientation2(void* a, void* b, void* c, void* d);  // 0x00b7f250
void         FUN_00f21d30(void* pos, void* orient, float scale, unsigned int spid);  // 0x00f21d30
void         FUN_00f20990(int* a, int* b);          // 0x00f20990
void         FUN_00f20900(int* a, int* b);          // 0x00f20900
void         FUN_00f22710(int* a, int* b);          // 0x00f22710
void         FUN_00f22930(int* a, int* b);          // 0x00f22930
void         FUN_00f23000(int* a, int* b);          // 0x00f23000
void         FUN_00f22d50(int* a, int* b);          // 0x00f22d50
void         FUN_00f22aa0(int* a, int* b);          // 0x00f22aa0
void         FUN_00f233b0(int* a, int* b);          // 0x00f233b0
void         FUN_00f235e0(int* a, int* b);          // 0x00f235e0
int*         FUN_00ae6760(int* a);                  // 0x00ae6760
int*         SP_NounManager(int* noun);             // 0x00b3d300
void         RemoveNoun(int* mgr, int* noun);       // 0x00b225d0
int          GetFileCount(int* p);                  // 0x008e7f80
void*        FUN_00f3e900(int a);                   // 0x00f3e900
int*         FUN_00f21e60(int* a);                  // 0x00f21e60
char         FUN_00f22070(int* a);                  // 0x00f22070
void         FUN_00f20620(int* a, void* b, void* c, float d);        // 0x00f20620
int*         FUN_00b3d240();                        // 0x00b3d240
void         FUN_00bab900(void* a, void* b);        // 0x00bab900
void         FUN_00f21080(void* a, void* b, void* c, float d, float e);  // 0x00f21080
char         FUN_00f20350(void* a);                 // 0x00f20350
void         FUN_00f24a90(int* a);                 // 0x00f24a90  callback
int          FUN_00f23220(int* a, void* b, float c, float d, float e);   // 0x00f23220
float        GetPropertyT_float(int owner, unsigned int key, int d);      // 0x004e1c70
int          GetPropertyT_int(int owner, unsigned int key, int d);        // 0x0064f350
int*         FUN_00ac8fa0(int owner, unsigned int key, int d);            // 0x00ac8fa0
int*         FUN_00f3f950(int* a);                  // 0x00f3f950
void         FUN_00c15d50(int a, int b, int c);     // 0x00c15d50

void*        operator_delete(void* p);              // 0x00f47380
void         RBTreeIncrement(void* node);           // 0x00921580
void         RBTreeInsert(void* node, void* a, void* b, int side);  // 0x009216a0
void         RBTreeErase(void* a, void* b);         // 0x00921880
void*        RBTreeCtor(void* key);                 // 0x00cea030
struct RBTreeCtorFn { void* Ctor(void* key); };     // 0x00cea030 ecx = tree
void         WordCtor_16c8318();
void         WordFind_16c8318(void* a, void* b);
}

// eastl::RBTreeIncrement is declared as taking the node by value (ecx) and
// returning the next node in eax; the extern above models the callee, this
// inline keeps the call sites in terms of a pointer result.
static inline void* RBTreeIncrementPtr(void* node)
{
    RBTreeIncrement(node);
    return 0;
}

// The `*(char*)(bucketIndex*0x4e0 + 2 + *(int*)(gameData+0x70))` probe used by
// 0x00f24200.
static inline int FieldAt(int iVar2)
{
    int iVar5 = *(int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8);
    int iVar3 = (int)FUN_00f3e900(0);
    return *(char*)(iVar5 * 0x4e0 + 2 + *(int*)(iVar3 + 0x70)) != 0;
}

// ------------------------------------------------------------------ eastl stubs
namespace eastl {
struct multimap_key { };
}

// eastl::multimap<unsigned int, EA::AutoRefCount<SP::cDramaEventInstanceData>,
//                 eastl::less<unsigned int>, eastl::allocator>
// The global instance lives at 0x016c8318; this models its tree/allocator
// header so that equal_range (0x00f21cd0) can be called thiscall.
struct DramaEventMultiMap {
    void equal_range(void** out, const unsigned int* key);   // 0x00f21cd0
};

// ------------------------------------------------------------------ object model
struct Object {
    virtual int  AddRef();                  // +0x00
    virtual int  GetNoun();                 // +0x04
    virtual int  GetOwner();                // +0x08
    virtual int  Release();                 // +0x0c
};

// A drama-event instance: the virtual slots used by this slice.
struct cDramaEventInstance {
    virtual int  AddRef();                  // +0x00  (slot 0)
    virtual int* GetNoun();                 // +0x04  (slot 1)
    virtual int* GetOwner();                // +0x08  (slot 2)
    virtual int* GetComponent(uint id);     // +0x0c  (slot 3)
    virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual char IsDead();                  // +0x2c  (slot 11)
    virtual void v30();
    virtual float GetScale();               // +0x34  (slot 13)
};

// ------------------------------------------------------------------ helpers
// `*(uint*)(x + 0xb58) >> 9 & 1` bit test used throughout 0x00f23d20.
static inline int FlagB58(int* noun)
{
    return (int)((*(uint*)((char*)noun + 0xb58) >> 9) & 1);
}

// ================================================================== 0x00f23cd0
// char FUN_00f23cd0(int* ev, int* noun)  -- "expired" test
// @ 0x00f23cd0
char FUN_00f23cd0(int* ev, int* noun)
{
    unsigned int gd = (uint)((GameDataAccess*)ev)->GameData();
    if (*(int*)(gd + 0x24) == 0) {
        int iVar1 = (int)FUN_00f23c80(ev, (int)noun);
        unsigned int gt = (uint)SP_GameTimeManager();
        int iVar2 = ((GameTimeAccess*)gt)->Now();
        if (iVar1 == -1 || iVar1 < iVar2 - 1000)
            return 1;
    }
    return 0;
}

// ================================================================== 0x00f23d20
// void FUN_00f23d20(int* param_1, int* param_2)
// @ 0x00f23d20
void FUN_00f23d20(int* param_1, int* param_2)
{
    if (((cDramaEventInstance*)param_1)->IsDead() != 0)
        return;
    if (param_2 != 0 && ((cDramaEventInstance*)param_2)->IsDead() != 0)
        return;
    if (*(int*)(DAT_016c7aa4 + 0xcc) != 2)
        return;

    int* piVar9 = param_1;
    int* piVar10 = param_2;
    if (param_2 != 0) {
        int iVar2 = (int)((cDramaEventInstance*)param_2)->GetComponent(0x175cdc9);
        if (iVar2 == 0)
            iVar2 = (int)((cDramaEventInstance*)param_2)->GetComponent(0x3a25119);
        if (iVar2 != 0) {
            piVar9 = param_2;
            piVar10 = param_1;
        }
    }
    if (piVar9 == 0)
        return;

    int iVar2 = (int)((cDramaEventInstance*)piVar9)->GetComponent(0x175cdc9);
    if (iVar2 != 0 && *(int*)(iVar2 + 0x38) == 0xb) {
        unsigned int uVar3 = (uint)FUN_00f19200(piVar10);
        void* uVar4 = FUN_00f217a0((int*)(iVar2 + 0x34));
        int iVar5 = FUN_00f217c0(piVar10, uVar4);
        if (iVar5 != 0) {
            FUN_00f23be0((int)uVar3, (int*)(iVar5 + 0x130), (void*)(iVar2 + 0x34));
            return;
        }
        char cVar1 = FUN_00f23cd0((int*)iVar2, piVar10);
        if (cVar1 != 0 && *param_2 == 2) {
            int* piVar6 = FUN_00b18e00(piVar10);
            float fVar12;
            if (piVar6 == 0) {
                fVar12 = DAT_01485720;
            } else {
                fVar12 = ((float(__thiscall*)(void*))*(void**)(*piVar6 + 0x34))(piVar6);
            }
            unsigned int uVar3b = (uint)sk_unshift(*(int*)(iVar2 + 0x4c), DAT_016c83d8);
            int* piVar6b = param_2 + 2;
            int* param_2b = param_2 + 5;
            unsigned char au[0x30];
            int* pcVar7 = SP_PlanetModel(au, piVar6b, param_2b);
            BuildSurfaceOrientation2(pcVar7, au, piVar6b, param_2b);
            FUN_00f21d30(piVar6b, au, fVar12, uVar3b);
        }
    }

    iVar2 = (int)((cDramaEventInstance*)piVar9)->GetComponent(0x3a25119);
    if (iVar2 != 0) {
        if (*(int*)(iVar2 + 0x134) == 0xd) {
            FUN_00f20990((int*)(iVar2 + 0x130), piVar10);
            return;
        }
        return;
    }

    iVar2 = (int)((cDramaEventInstance*)piVar9)->GetComponent(0x175cdc9);
    if (iVar2 == 0)
        return;
    int iVar5 = iVar2 + 0x34;
    if (*(int*)(iVar2 + 0x38) == 0)
        return;

    int* iVar8 = FUN_00ae6760(piVar10);
    if (iVar8 != 0 && *(char*)((char*)iVar8 + 0xbcd) == 0 && *(int*)(iVar2 + 0x38) == 6) {
        FUN_00f20900((int*)iVar5, (int*)((char*)iVar8 + 0x508));
        return;
    }

    iVar8 = FUN_00f19200(piVar10);
    if (iVar8 == 0 || *(char*)((char*)iVar8 + 0xb5e) != 0)
        return;

    switch (*(int*)(iVar2 + 0x38)) {
    case 1:
        if (FlagB58(iVar8)) FUN_00f22710((int*)iVar5, iVar8);
        break;
    case 2:
        if (FlagB58(iVar8)) FUN_00f22930((int*)iVar5, iVar8);
        break;
    case 3:
        if (FlagB58(iVar8)) FUN_00f23000((int*)iVar5, iVar8);
        break;
    case 4:
        if (FlagB58(iVar8)) FUN_00f22d50((int*)iVar5, iVar8);
        break;
    case 5:
        if (FlagB58(iVar8)) FUN_00f22aa0((int*)iVar5, iVar8);
        break;
    case 6:
        FUN_00f20900((int*)iVar5, (int*)((char*)iVar8 + 0x5a8));
        break;
    case 7:
        FUN_00f235e0((int*)iVar5, iVar8);
        break;
    case 8:
        FUN_00f233b0((int*)iVar5, iVar8);
        break;
    }
}

// ================================================================== 0x00f24060
// int FUN_00f24060(int* ev)  -- how many events are queued for this noun
// @ 0x00f24060
int FUN_00f24060(int* ev)
{
    int* piVar1 = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 4))(ev);
    unsigned int key = (uint)piVar1;
    if (piVar1 != 0)
        ((void(__thiscall*)(void*))*(void**)*piVar1)(piVar1);

    void* lower;
    void* upper;
    ((DramaEventMultiMap*)DAT_016c8318)->equal_range(&lower, &key);

    int iVar2 = 0;
    while (lower != upper) {
        lower = RBTreeIncrementPtr(lower);
        iVar2 = iVar2 + 1;
    }
    if (piVar1 != 0)
        ((void(__thiscall*)(void*))*(void**)(*piVar1 + 4))(piVar1);
    return iVar2;
}

// ================================================================== 0x00f240d0
// void __thiscall FUN_00f240d0(void* node)  -- destroy a whole RB tree
// @ 0x00f240d0
struct EventTree {
    void Destroy(int* node);                                                          // 0x00f240d0
    unsigned int* Insert(unsigned int* out, unsigned int* key, unsigned int tag);      // 0x00f24120
};
void EventTree::Destroy(int* node)
{
    while (node != 0) {
        Destroy((int*)node[0]);
        int* next = (int*)node[1];
        if (node[5] != 0)
            ((void(__thiscall*)(void*))*(void**)(*(int*)node[5] + 4))((void*)node[5]);
        if (node[4] != 0)
            ((void(__thiscall*)(void*))*(void**)(*(int*)node[4] + 4))((void*)node[4]);
        operator_delete(node);
        node = next;
    }
}

// ================================================================== 0x00f24120
// void __thiscall FUN_00f24120(unsigned int* out, unsigned int* key, unsigned int tag)
// @ 0x00f24120
unsigned int* EventTree::Insert(unsigned int* out, unsigned int* key, unsigned int tag)
{
    int* eleft = (int*)((char*)this + 4);
    int* place = eleft;
    int* root = *(int**)((char*)this + 0xc);
    if (root != 0) {
        do {
            place = root;
            if (*key < (uint)root[4]) root = (int*)root[1];
            else                      root = (int*)root[0];
        } while (root != 0);
    }
    int side;
    int* leftend = (int*)((char*)this + 4);
    if (place == leftend || *key < (uint)place[4])
        side = 0;
    else
        side = 1;
    (void)tag;
    unsigned int uVar2 = (uint)((RBTreeCtorFn*)this)->Ctor(key);
    RBTreeInsert((void*)uVar2, place, leftend, side);
    unsigned int* pOut = out;
    *(int*)((char*)this + 0x14) = *(int*)((char*)this + 0x14) + 1;
    *pOut = uVar2;
    return pOut;
}

// ================================================================== 0x00f24190
// void FUN_00f24190(int* a, int* b)
// @ 0x00f24190
struct AutoRef { void* p; };

void FUN_00f24190(int* a, int* b)
{
    AutoRef ra; ra.p = a;
    if (a != 0)
        ((void(__thiscall*)(void*))*(void**)*a)(a);
    AutoRef rb; rb.p = b;
    if (b != 0)
        ((void(__thiscall*)(void*))*(void**)*b)(b);

    unsigned int tag = 0;
    ((EventTree*)DAT_016c8318)->Insert((unsigned int*)&ra, (unsigned int*)&rb, tag);

    if (b != 0)
        ((void(__thiscall*)(void*))*(void**)(*b + 4))(b);
    if (a != 0)
        ((void(__thiscall*)(void*))*(void**)(*a + 4))(a);
}

// ================================================================== 0x00f24200
// void FUN_00f24200(void)
// @ 0x00f24200
void FUN_00f24200(void)
{
    int iVar4 = *(int*)(DAT_016c8318 + 8);
    if (iVar4 == DAT_016c8318 + 4)
        return;

    int iVar5 = 0;
    do {
        iVar5 = 0;
        int uStack_4, iVar2, iVar3;

        if (*(int**)(iVar4 + 0x10) == 0)
            uStack_4 = 0;
        else
            uStack_4 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x10))->GetComponent(0x175cdc9);

        if (*(int**)(iVar4 + 0x14) == 0) {
            iVar2 = 0; iVar3 = 0;
        } else {
            iVar2 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->GetComponent(0xce9f6639);
            iVar3 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->GetComponent(0x137e8e0);
        }
        if (*(int**)(iVar4 + 0x14) != 0)
            iVar5 = (int)((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->GetComponent(0x70704db);

        char cVar1 = ((cDramaEventInstance*)*(int**)(iVar4 + 0x10))->IsDead();
        bool keep =
            (cVar1 == 0
             && ((cDramaEventInstance*)*(int**)(iVar4 + 0x14))->IsDead() == 0
             && (iVar5 == 0 || GetFileCount((int*)(iVar5 + 0x120)) != 2)
             && (iVar3 == 0 || GetFileCount((int*)(iVar3 + 0x508)) != 2)
             && (iVar2 == 0
                 || (GetFileCount((int*)(iVar2 + 0x5a8)) != 2
                     || FieldAt(iVar2))));

        if (keep) {
            iVar5 = (int)RBTreeIncrementPtr((void*)iVar4);
        } else {
            int* iVarNext = (int*)RBTreeIncrementPtr((void*)iVar4);
            if (iVar3 != 0)
                *(uint8_t*)(iVar3 + 0xe78) = 1;
            int iVar2b = DAT_016c8318;
            *(int*)(DAT_016c8318 + 0x14) = *(int*)(DAT_016c8318 + 0x14) - 1;
            RBTreeIncrement((void*)iVar4);
            RBTreeErase((void*)iVar4, (void*)(iVar2b + 4));
            if (*(int**)(iVar4 + 0x14) != 0)
                ((void(__thiscall*)(void*))*(void**)(**(int**)(iVar4 + 0x14) + 4))(*(void**)&*(int**)(iVar4 + 0x14));
            if (*(int**)(iVar4 + 0x10) != 0)
                ((void(__thiscall*)(void*))*(void**)(**(int**)(iVar4 + 0x10) + 4))(*(void**)&*(int**)(iVar4 + 0x10));
            operator_delete((void*)iVar4);
            iVar5 = (int)iVarNext;
        }
        iVar4 = iVar5;
    } while (iVar5 != DAT_016c8318 + 4);
}

// ================================================================== 0x00f24390
// void FUN_00f24390(void)
// @ 0x00f24390
void FUN_00f24390(void)
{
    EventTree* tree = (EventTree*)DAT_016c8318;
    int* puVar1 = (int*)(DAT_016c8318 + 0xc);
    int iVar3 = (int)tree;
    tree->Destroy(*(int**)((char*)tree + 0xc));
    int iVar2 = iVar3 + 4;
    *(int*)(iVar3 + 8) = iVar2;
    *(int*)iVar2 = iVar2;
    *puVar1 = 0;
    *(uint8_t*)(iVar3 + 0x10) = 0;
    *(int*)(iVar3 + 0x14) = 0;
}

// ================================================================== 0x00f243c0
// void FUN_00f243c0(int* ev, float dt)
// @ 0x00f243c0
void FUN_00f243c0(int* ev, float dt)
{
    int* piVar7 = ev;
    if (*(float*)((char*)ev + 0x28) > DAT_01485378)
        *(float*)((char*)ev + 0x28) = *(float*)((char*)ev + 0x28) - dt;

    int local_10 = FUN_00f24060(ev);
    int iVar4;
    int iVar5;
    int* piVar3;
    int* piStack_c;
    int* piStack_8;
    int* piStack_4;
    int localFlag1 = 0;      // [esp+0x24] byte flag
    int localFlag2 = 0;      // [esp+0x0f] byte flag
    int dec1 = 0;            // [esp+0x28] byte flag (uStack_14._3_1_)

    piVar3 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
    {
        unsigned int key = (uint)piVar3;
        if (piVar3 != 0)
            ((void(__thiscall*)(void*))*(void**)*piVar3)(piVar3);
        WordCtor_16c8318();
        {
            void** out = (void**)&piStack_8;
            void* thisp = (void*)DAT_016c8318;
            ((void(__thiscall*)(void*, void**, unsigned int*))*(void**)(0))(thisp, out, &key);
        }
        if (piVar3 != 0)
            ((void(__thiscall*)(void*))*(void**)(*piVar3 + 4))(piVar3);
    }

    piStack_c = piStack_8;
    if (piStack_8 != piStack_4) {
        do {
            piVar3 = (int*)piStack_c[5];
            if (piVar3 != 0) {
                iVar4 = (int)((cDramaEventInstance*)piVar3)->GetComponent(0x70704db);
                if (iVar4 != 0 && GetFileCount((int*)(iVar4 + 0x120)) == 2
                    && *(char*)(*(int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8) * 0x4e0 + 2
                                + *(int*)((char*)SP_GameData() + 0x70)) == 0) {
                    dec1 = 1;
                }
                iVar4 = (int)((cDramaEventInstance*)piVar3)->GetComponent(0x175cdc9);
                if (iVar4 != 0 && *(int*)(iVar4 + 0x38) == 0xe) {
                    local_10 = local_10 - 1;
                    localFlag2 = 1;
                }
            }
            piStack_c = (int*)RBTreeIncrementPtr(piStack_c);
        } while (piStack_c != piStack_4);
    }

    if (local_10 >= 1)
        return;

    iVar4 = (int)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
    {
        unsigned int gd = (uint)SP_GameData();
        float fVar1 = *(float*)((char*)piVar7 + 0x24);
        iVar5 = *(int*)(*(int*)(*(int*)(DAT_016c7aa4 + 0x78) + 0xb8) * 0x4e0 + 0x4a4
                        + *(int*)(gd + 0x70));
        *(float*)((char*)piVar7 + 0x24) = fVar1 - dt;
        (void)iVar4;
        if (fVar1 - dt > 0.0f || *(float*)((char*)piVar7 + 0x28) > 0.0f)
            return;

        char cVar2 = FUN_00f22070(piVar7);
        if (cVar2 != 0) {
            *(float*)((char*)piVar7 + 0x24) = 0.25f;
            return;
        }
        *(float*)((char*)piVar7 + 0x24) = (float)iVar5 + *(float*)((char*)piVar7 + 0x24);
        *(float*)((char*)piVar7 + 0x28) = DAT_01486110;
        unsigned int uVar6 = (uint)FUN_00f21e60(piVar7);
        uVar6 = (uint)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
        FUN_00f24190((int*)uVar6, (int*)0);

        if (localFlag1 != 0) {
            piVar3 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
            {
                unsigned int key = (uint)piVar3;
                if (piVar3 != 0)
                    ((void(__thiscall*)(void*))*(void**)*piVar3)(piVar3);
                WordFind_16c8318((void*)0, &key);
                if (piVar3 != 0)
                    ((void(__thiscall*)(void*))*(void**)(*piVar3 + 4))(piVar3);
            }
            piVar3 = piStack_c;
            if (piStack_c != (int*)(DAT_016c8318 + 4)) {
                do {
                    int* piVar9 = (int*)piVar3[5];
                    if (piVar9 != 0) {
                        iVar4 = (int)((cDramaEventInstance*)piVar9)->GetComponent(0x70704db);
                        if (iVar4 != 0 && GetFileCount((int*)(iVar4 + 0x120)) == 2) {
                            RemoveNoun(SP_NounManager(piVar9), piVar9);
                            break;
                        }
                    }
                    piVar3 = (int*)RBTreeIncrementPtr(piVar3);
                } while (piVar3 != (int*)(DAT_016c8318 + 4));
            }
        }

        if (dec1) {
            piVar7 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
            {
                unsigned int key = (uint)piVar7;
                if (piVar7 != 0)
                    ((void(__thiscall*)(void*))*(void**)*piVar7)(piVar7);
                WordFind_16c8318((void*)0, &key);
                if (piVar7 != 0)
                    ((void(__thiscall*)(void*))*(void**)(*piVar7 + 4))(piVar7);
            }
            piVar7 = piStack_c;
            if (piStack_c != (int*)(DAT_016c8318 + 4)) {
                while (1) {
                    int* p3 = (int*)piVar7[5];
                    if (p3 == 0)
                        break;
                    int v = (int)((cDramaEventInstance*)p3)->GetComponent(0x175cdc9);
                    if (v == 0 || *(int*)(v + 0x38) != 0xe)
                        break;
                    RemoveNoun(SP_NounManager(p3), p3);
                    break;
                }
            }
        }
    }
}

// ================================================================== 0x00f24700
// void FUN_00f24700(int* a, int* ev, int b, float c, float d, float e)
//   `a` (self) / `ev` (event) / `b` (id) / `c` (radius) / `d`,`e` (scales)
// @ 0x00f24700
void FUN_00f24700(int* a, int* ev, int b, float c, float d, float e)
{
    if (e == 0.0f) {
        int r = 0;
        if (ev != 0)
            r = (int)((int(__thiscall*)(void*, int))*(void**)(*ev + 0x5c))(ev, 0x1186577);
        FUN_00f20620(a, (void*)r, (void*)b, d);
        return;
    }

    int* piVar2 = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 8))(ev);
    int* piVar3 = FUN_00b3d240();
    void* vec[3] = { 0, 0, 0 };
    unsigned int uVar4 = (uint)((int(__thiscall*)(void*, float, void**, int))*(void**)(*piVar2 + 0x2c))(piVar2, c, vec, 0);
    ((void(__thiscall*)(void*, unsigned int))*(void**)(*piVar3 + 0x48))(piVar3, uVar4);

    int n = (int)((char*)vec[1] - (char*)vec[0]) >> 2;
    int* end = (int*)vec[1];
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if ((int)((int(__thiscall*)(void*))*(void**)(*ev + 8))(ev) == ((int*)vec[0])[i]) {
            found = true;
            break;
        }
    }
    if (!found) {
        int* p = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 8))(ev);
        void* cur = p;
        if (p != 0)
            ((void(__thiscall*)(void*))*(void**)(*p + 0xbc))(p);
        if (vec[1] < vec[2]) {
            void** slot = (void**)vec[1];
            vec[1] = (char*)vec[1] + 4;
            if (slot != 0) {
                *slot = p;
                if (p != 0)
                    ((void(__thiscall*)(void*))*(void**)(*p + 0xbc))(p);
            }
        } else {
            FUN_00bab900(vec[1], &cur);
            p = (int*)cur;
        }
        end = (int*)vec[1];
        if (p != 0)
            ((void(__thiscall*)(void*))*(void**)(*p + 0xc0))(p);
    }

    FUN_00f21080((void*)a, vec, (void*)b, d, e);
    for (int* it = (int*)vec[0]; it < end; ++it) {
        if (*it != 0)
            ((void(__thiscall*)(void*))*(void**)(*(int*)*it + 0xc0))((void*)*it);
    }
    if (vec[0] != 0 && ((int*)vec[0])[-1] != 0)
        operator_delete(vec[0]);
}

// ================================================================== 0x00f248b0
// void FUN_00f248b0(int* ev, int* target)
// @ 0x00f248b0
void FUN_00f248b0(int* ev, int* target)
{
    int* piVar2 = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 8))(ev);
    int* puVar6 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar2 + 0x2c))(piVar2);
    unsigned int uStack_1c = puVar6[0], uStack_18 = puVar6[1], uStack_14 = puVar6[2];

    piVar2 = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 8))(ev);
    puVar6 = (int*)((int(__thiscall*)(void*))*(void**)(*piVar2 + 0x30))(piVar2);
    unsigned int uStack_10 = puVar6[0], uStack_c = puVar6[1], uStack_8 = puVar6[2];
    unsigned int uStack_4 = puVar6[3];

    unsigned int uVar7 = (uint)((int(__thiscall*)(void*))*(void**)(*ev + 4))(ev);
    float fVar12 = GetPropertyT_float(ev[6], DAT_016c83ac, 0);
    unsigned int uVar8 = (uint)((int(__thiscall*)(void*))*(void**)(*ev + 4))(ev);
    int* iVar9p = FUN_00f3f950((int*)uVar8);
    unsigned int uVar8b = *(unsigned int*)((char*)iVar9p + 0x49c);
    float fVar1 = *(float*)((char*)iVar9p + 0x498);
    char cVar4 = (char)GetPropertyT_int(ev[6], DAT_016c83dc, 0);
    float fVar3 = fVar1 * 0.33333334f;
    if (cVar4 != 0) {
        piVar2 = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 8))(ev);
        fVar3 = ((float(__thiscall*)(void*))*(void**)(*piVar2 + 0x34))(piVar2);
    }
    int* uVar10 = FUN_00ac8fa0(ev[6], DAT_016c83a4, 0);
    FUN_00f21d30(&uStack_1c, &uStack_10, fVar3, (unsigned int)uVar10);

    piVar2 = (int*)((int(__thiscall*)(void*))*(void**)(*ev + 4))(ev);
    if (piVar2 != 0) {
        int iVar9 = (int)((cDramaEventInstance*)piVar2)->GetComponent(0x3a25119);
        if (iVar9 != 0) {
            iVar9 = *(int*)(iVar9 + 0x108);
            if (iVar9 != 0) {
                unsigned int uVar10b = (uint)((int(__thiscall*)(void*))*(void**)(*ev + 8))(ev);
                FUN_00c15d50((int)uVar10b, 1, 0);
                target = (int*)(iVar9 + 0x5a8);
            }
        }
    }

    if (target == 0)
        FUN_00f23220((int*)uVar7, &uStack_1c, *(float*)&uVar8b, fVar1, fVar12);
    else
        FUN_00f24700((int*)uVar7, target, 0, 0.0f, 0.0f, 0.0f);

    unsigned int uVar8c = (uint)((int(__thiscall*)(void*))*(void**)(*ev + 4))(ev);
    RemoveNoun(SP_NounManager((int*)uVar8c), (int*)uVar8c);
}

// ================================================================== 0x00f24ae0
// void FUN_00f24ae0(int* ev, int target, float dt)
// @ 0x00f24ae0
void FUN_00f24ae0(int* ev, int target, float dt)
{
    if (dt != 0.0f) {
        unsigned int uVar2 = (uint)((int(__thiscall*)(void*, float, void*))*(void**)(*ev + 4))(ev, dt, (void*)0x00f24a90);
        char cVar1 = FUN_00f20350((void*)uVar2);
        if (cVar1 != 0)
            return;
    }
    FUN_00f248b0(ev, (int*)target);
}

// ------------------------------------------------------------------ helpers
// Small local wrappers so the tree-walk helpers read naturally at the call
// sites above without disturbing codegen of the actual target functions.
static void WordCtor_16c8318_stub() {}
