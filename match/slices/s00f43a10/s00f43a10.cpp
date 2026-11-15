// Slice s00f43a10 -- unnamed action/vector helpers, slice 7 of bfs1.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* __cdecl eastl_alloc(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl eastl_free(void* p);                                                                   // 0x00f47380

// ---------------------------------------------------------------- element stride 0x534
struct Sub534 { void destroy() throw(); };                 // 0x00f280f0
struct SubVec534 {
    char* begin;                                           // +0x00
    char* end;                                             // +0x04
    void destroyRange(char* first, char* last) throw();    // 0x00dfc600
};
struct T534 {
    Sub534 m0;                                             // +0x000 (empty, size 1)
    char   pad001[0x3c - 0x01];
    Sub534 m3c;                                            // +0x03c
    char   pad03d[0x84 - 0x3d];
    SubVec534 mvec;                                        // +0x084
    char   pad8c[0x534 - 0x8c];
    void Construct(const T534&) throw();
    void ConstructDefault() throw();
};
void __cdecl eastl_copy534(T534* first, T534* last, T534* dest);  // 0x00dfd2c0

struct Vec534 {
    T534* mpBegin; T534* mpEnd; T534* mpCapacity; char alloc[4];
    T534* insert(T534* pos, const T534& value);   // 0x00f44780
    void  DoInsert(T534* pos, const T534& value); // 0x00f2f050
    T534* pushBackDefault();                      // 0x00f446f0
    T534* erase(T534* pos);                       // 0x00f44190
};

// @ 0x00f44780
T534* Vec534::insert(T534* pos, const T534& value)
{
    int index = pos - mpBegin;
    if (pos == mpEnd && mpEnd != mpCapacity) {
        T534* p = mpEnd++;
        if (p != 0)
            p->Construct(value);
    } else {
        DoInsert(pos, value);
    }
    return mpBegin + index;
}

// @ 0x00f44190
T534* Vec534::erase(T534* pos)
{
    if ((char*)pos + 0x534 < (char*)mpEnd)
        eastl_copy534(pos + 1, mpEnd, pos);
    mpEnd = (T534*)((char*)mpEnd - 0x534);
    T534* last = mpEnd;
    last->mvec.destroyRange(last->mvec.begin, last->mvec.end);
    if (last->mvec.begin != 0 && *(int*)(last->mvec.begin - 4) != 0)
        eastl_free(last->mvec.begin);
    last->m3c.destroy();
    last->m0.destroy();
    return pos;
}

// @ 0x00f446f0  push_back() (default-constructed value)
T534* Vec534::pushBackDefault()
{
    if (mpEnd < mpCapacity) {
        T534* p = mpEnd++;
        if (p != 0)
            p->ConstructDefault();
        return p;
    }
    T534 temp;
    temp.ConstructDefault();
    DoInsert(mpEnd, temp);
    temp.mvec.destroyRange(temp.mvec.begin, temp.mvec.end);
    if (temp.mvec.begin != 0 && *(int*)(temp.mvec.begin - 4) != 0)
        eastl_free(temp.mvec.begin);
    temp.m3c.destroy();
    temp.m0.destroy();
    return mpEnd;
}

// ========================================================================================
// Action-list / action-record helpers (slice 7).  The W object owns a World at +0x10 whose
// members are reached through the layouts below.  All W:: helpers are __thiscall; the free
// helper 0x00f43a10 uses no register argument.
extern "C" void* __stdcall FUN_00f3be60(void*);   // 0x00f3be60  find action-state by key
extern "C" void* FUN_00f3e8a0();        // 0x00f3e8a0  find action record by key
extern "C" void  FUN_00f2bd10();   // 0x00f2bd10
extern "C" void  FUN_00f0b390();   // 0x00f0b390
extern "C" void  FUN_00dfd020();   // 0x00dfd020
extern "C" void  FUN_00f2e0e0();   // 0x00f2e0e0
extern "C" void  FUN_00dfbba0();   // 0x00dfbba0
extern "C" void* FUN_00b3d310(void*);   // 0x00b3d310
extern "C" void  FUN_00b52020();   // 0x00b52020
extern "C" int   FUN_00eecba0(void*);   // 0x00eecba0  ResourceLookupEntryId
extern "C" void  FUN_00f2d680();   // 0x00f2d680
extern "C" char  FUN_00f25730();   // 0x00f25730
extern "C" void  FUN_00f42a50();   // 0x00f42a50
extern "C" void  FUN_00f438f0();   // 0x00f438f0
extern "C" void  FUN_00f425d0();   // 0x00f425d0
extern "C" char  FUN_00f43200(void*, int, int);   // 0x00f43200
extern "C" char  FUN_00f41a10();   // 0x00f41a10
extern "C" char  FUN_00f3c330();   // 0x00f3c330  (this, ptr) thiscall
extern "C" void  FUN_00f3bce0();   // 0x00f3bce0
extern "C" void  FUN_00f41bb0(void*);             // 0x00f41bb0
extern "C" void* FUN_00b3d300(void*);   // 0x00b3d300  SP::NounManager
extern "C" void* FUN_00b1fdb0();   // 0x00b1fdb0  cGameNounManager::GetAvatar
extern "C" int   FUN_004eb930(void*, void*);      // 0x004eb930
extern "C" int   FUN_004bbe20(void*, int);        // 0x004bbe20  cSPAssetDataList::SetAssetData
extern "C" void* FUN_0067dcc0();   // 0x0067dcc0  SP::MessageServer
extern "C" void  FUN_00dfd2c0(void*, void*, void*);   // 0x00dfd2c0
extern "C" void  FUN_00dfc170(void*, void*, void*);   // 0x00dfc170
extern "C" int   FUN_00ef1990(void*, void*, void*);   // 0x00ef1990
extern "C" void* FUN_00f2aac0();   // 0x00f2aac0
extern "C" int   FUN_00f2ed20();   // 0x00f2ed20
extern "C" void  FUN_00dfc5b0();   // 0x00dfc5b0
extern "C" float FUN_00f3b520();   // 0x00f3b520
extern "C" void  FUN_00eec3d0(void*, void*);          // 0x00eec3d0
extern "C" float FUN_00f409a0(void*, void*, float, int, void*);   // 0x00f409a0
extern "C" void  FUN_00f42ef0();   // 0x00f42ef0
extern "C" void  FUN_00eef7d0(void*);                 // 0x00eef7d0
extern "C" void* FUN_00efc520();   // 0x00efc520  ScenarioTutorials_GetActive
extern "C" void* FUN_00f3fa20(void*, void*);          // 0x00f3fa20
extern "C" void* FUN_00b474c0();   // 0x00b474c0
extern "C" void* FUN_00b6ff20();   // 0x00b6ff20
extern "C" void  FUN_00eec440(void*);                 // 0x00eec440
extern "C" void  FUN_00f3da90();   // 0x00f3da90
extern "C" void  FUN_00f40bb0();   // 0x00f40bb0
extern "C" void  FUN_00f427c0();   // 0x00f427c0
extern "C" void* FUN_00883860();   // 0x00883860  EA::Messaging::GetServer
extern "C" void  FUN_00f43420();   // 0x00f43420
extern "C" void  FUN_00b5f950();   // 0x00b5f950  AutoRefCount::operator=
extern "C" void  FUN_00f43af0();   // 0x00f43af0  forward (called from 00f43bf0)
extern "C" char  FUN_00f43bf0();   // 0x00f43bf0  forward (called from 00f43f20/00f440b0)
extern "C" void* FUN_00f44190();   // 0x00f44190  Vec534::erase (forward)
extern "C" int __cdecl atexit(void (__cdecl*)(void));   // 0x011E07EF

extern uint32_t DAT_016c8b34;      // 0x016c8b34  action-scratch static-init guard
extern void*    DAT_016c7aa4;      // 0x016c7aa4  global message-dispatcher root
extern float    DAT_01471064;      // 0x01471064  default action progress (0.5f)
extern uint8_t  DAT_016c89c4[];    // 0x016c89c4

// ----------------------------------------------------------------------------------------
// 0x188-byte action-state scratch object at 0x016c89ac.
struct ActionScratch {
  uint32_t mField00;                 // +0x00
  uint32_t mField04;                 // +0x04
  uint32_t mField08;                 // +0x08
  uint32_t mField0C;                 // +0x0c
  uint8_t  mRest[0x188 - 0x10];
};
extern ActionScratch DAT_016c89ac; // 0x016c89ac

// Object returned by FUN_00f3be60: holds a 0x188-strided vector at +0x84.
struct Vec188 { char* begin; char* end; char* cap; };   // 0x188-strided element vector
struct ActionStateObj {
  uint8_t  mPad000[0x84];
  Vec188   mVec;                     // +0x84
};

// Object returned by FUN_00f3e8a0.
struct ActionRec {
  uint32_t mKey00;                   // +0x00
  uint32_t mKey04;                   // +0x04
  uint32_t mKey08;                   // +0x08
  uint8_t  mPad0C[0x18 - 0x0c];
  uint32_t mId18;                    // +0x18
  uint8_t  mPad1C[0x24 - 0x1c];
  int32_t  mMode24;                  // +0x24
  uint8_t  mSub28[0x20];             // +0x28
  int32_t  mMode48;                  // +0x48
  uint8_t  mSub50[0x20];             // +0x50
  uint8_t  mSet70[0x10];             // +0x70
};

// 0x27e8-strided action list in World::mLists*.
struct ActionList {
  uint32_t mField00;                 // +0x00
  uint32_t mField04;                 // +0x04
  uint32_t mKey08;                   // +0x08
  uint32_t mKey0C;                   // +0x0c
  uint32_t mKey10;                   // +0x10
  uint8_t  mPad14[0x20 - 0x14];
  uint32_t mKey20;                   // +0x20
  uint8_t  mFlag24;                  // +0x24
  uint8_t  mPad25[0x2c - 0x25];
  uint32_t mMode2C;                  // +0x2c
  uint32_t mTri30;                   // +0x30
  uint32_t mTri34;                   // +0x34
  uint32_t mTri38;                   // +0x38
  uint8_t  mPad3C[0x48 - 0x3c];
  uint32_t mKey48;                   // +0x48
  uint8_t  mFlag4C;                  // +0x4c
  uint8_t  mPad4D[0x50 - 0x4d];
  uint32_t mMode50;                  // +0x50
  uint32_t mTri58;                   // +0x58
  uint32_t mTri5C;                   // +0x5c
  uint32_t mTri60;                   // +0x60
  uint8_t  mPad64[0x70 - 0x64];
  uint32_t mKey70;                   // +0x70
  uint8_t  mFlag74;                  // +0x74
  uint8_t  mPad75[0x78 - 0x75];
  void*    mSubBegin;                // +0x78
  void*    mSubEnd;                  // +0x7c
  uint8_t  mPad80[0x27e8 - 0x80];
};

// 0x38-strided entry in World::mActions*.
struct ActionEntry {
  uint32_t mField00;                 // +0x00
  uint32_t mField04;                 // +0x04
  uint32_t mField08;                 // +0x08
};

// 0x238-strided item in World::mItems*.
struct WorldItem {
  uint32_t mField00;                 // +0x000
  uint32_t mField04;                 // +0x004  (= key when addressed at begin+4)
  uint32_t mField08;                 // +0x008
  uint32_t mField0C;                 // +0x00c
  uint32_t mField10;                 // +0x010
  uint32_t mField14;                 // +0x014
  uint32_t mField18;                 // +0x018
  uint32_t mField1C;                 // +0x01c
  uint32_t mField20;                 // +0x020
  float    mF24;                     // +0x024
  float    mF28;                     // +0x028
  void*    mSubBegin;                // +0x02c
  void*    mSubEnd;                  // +0x030
  uint8_t  mPad34[0x224 - 0x34];
  float    mF224;                    // +0x224
  uint8_t  mPad228[0x22c - 0x228];
  uint32_t mIndex;                   // +0x22c
};

struct World {
  uint8_t  mPad0000[0x0130];
  int32_t  mSelKey0;                 // +0x0130
  int32_t  mSelKey1;                 // +0x0134
  int32_t  mSelKey2;                 // +0x0138
  uint8_t  mPad013C[0x014C - 0x013C];
  uint8_t  mDirty14C;                // +0x014C
  uint8_t  mPad014D[0x0178 - 0x014D];
  void*    mActionsBegin;            // +0x0178
  void*    mActionsEnd;              // +0x017C
  uint8_t  mPad0180[0x023C - 0x0180];
  void*    mNounsBegin;              // +0x023C
  void*    mNounsEnd;                // +0x0240
  uint8_t  mPad0244[0x2BF4 - 0x0244];
  void*    mListsBegin;              // +0x2BF4
  void*    mListsEnd;                // +0x2BF8
  uint8_t  mPad2BFC[0x2C10 - 0x2BFC];
  void*    mItemsBegin;              // +0x2C10
  void*    mItemsEnd;                // +0x2C14
  uint8_t  mPad2C18[0x2C24 - 0x2C18];
  uint32_t mItemsSize;               // +0x2C24
};

// Message-dispatcher chain walked by ApplyAction.
struct VtblObj { void** mpVtbl; };
struct MsgRoot { uint8_t mPad00[0x14]; void* mSink1; };    // +0x14
struct MsgLink { uint8_t mPad00[0x18]; void* mNext; };     // +0x18
struct MsgTail { uint8_t mPad00[0x14]; VtblObj* mObj; };   // +0x14

struct W {
  uint8_t  mPad000[0x10];
  World*   mpWorld;               // +0x010
  uint8_t  mFlag014;              // +0x014
  uint8_t  mPad015[0x2c - 0x15];
  uint8_t  mFlag02C;              // +0x02c
  uint8_t  mPad02D[0x8c - 0x2d];
  void*    mpActive;              // +0x08c
  uint8_t  mSet090[0x20];         // +0x090
  uint8_t  mSet0B0[0x20];         // +0x0b0
  void  SetAction(int a, void* b);                          // 0x00f43af0
  bool  ApplyAction(int a, int b, int c);                   // 0x00f43bf0
  bool  RefreshActions();                                   // 0x00f43f20
  uint32_t HandleMessage(unsigned msg, int arg);          // 0x00f440b0
  void  RemoveAction(int idx);                            // 0x00f44210
  void* CreateAction(int a, void* b, void* c, float d);   // 0x00f44370
  void* PickAction(int* a);                               // 0x00f445c0
};

// Applies the "state" ramp/normalisation for a 3-dword action key.
static void DispatchActionNotify(const W* self, int key)
{
    (void)self;
    MsgRoot* root = (MsgRoot*)DAT_016c7aa4;
    if (root == 0)
        return;
    MsgLink* l1 = (MsgLink*)root->mSink1;
    if (l1 == 0)
        return;
    MsgLink* l2 = (MsgLink*)l1->mNext;
    if (l2 == 0)
        return;
    MsgTail* tail = (MsgTail*)l2->mNext;
    VtblObj* obj = tail->mObj;
    if (obj == 0)
        return;
    ((void(__thiscall*)(void*, int))obj->mpVtbl[0x1c / 4])(obj, key);
}

// @ 0x00f43a10
int __stdcall PushActionState(void* key, int a, int b, int c)
{
    int result = -1;
    ActionStateObj* obj = (ActionStateObj*)FUN_00f3be60(key);
    if (obj != 0) {
        uint32_t count = (uint32_t)(obj->mVec.end - obj->mVec.begin) / 0x188;
        result = (int)count;
        if ((int)count < 3) {
            if ((DAT_016c8b34 & 1) == 0) {
                DAT_016c8b34 |= 1;
                ((void(__thiscall*)(void*))FUN_00f2bd10)(&DAT_016c89ac);
                atexit((void(__cdecl*)(void))0x013c9910);
            }
            DAT_016c89ac.mField00 = (uint32_t)a;
            DAT_016c89ac.mField04 = (uint32_t)b;
            DAT_016c89ac.mField08 = (uint32_t)c;
            DAT_016c89ac.mField0C = 1;
            ((void(__thiscall*)(void*, int))FUN_00f0b390)(DAT_016c89c4, 5);
            char* end = obj->mVec.end;
            if (end < obj->mVec.cap) {
                obj->mVec.end = end + 0x188;
                if (end != 0) {
                    ((void(__thiscall*)(void*, void*))FUN_00dfd020)(&obj->mVec, &DAT_016c89ac);
                    return result;
                }
            } else {
                ((void(__thiscall*)(void*, void*, void*))FUN_00f2e0e0)(&obj->mVec, end, &DAT_016c89ac);
            }
        }
    }
    return result;
}

// @ 0x00f43af0
void W::SetAction(int a, void* b)
{
    ActionRec* rec = (ActionRec*)((void*(__thiscall*)(void*, void*))FUN_00f3e8a0)(this, (void*)a);
    if (rec == 0)
        return;
    int mode = rec->mMode24;
    if (mode >= 0) {
        if (mode <= 1) {
            FUN_00b3d310(rec);
            ((void(__stdcall*)(void*))FUN_00b52020)(rec);
        } else if (mode == 2) {
            FUN_00b3d310(&rec->mSub28);
            ((void(__stdcall*)(void*))FUN_00b52020)(&rec->mSub28);
        }
    }
    if (rec->mMode48 == 2) {
        FUN_00b3d310(&rec->mSub50);
        ((void(__stdcall*)(void*))FUN_00b52020)(&rec->mSub50);
    }

    uint32_t* src = (uint32_t*)b;
    rec->mKey00 = src[0];
    rec->mKey04 = src[1];
    rec->mKey08 = src[2];
    rec->mId18 = (uint32_t)FUN_00eecba0(b);

    uint8_t local[0x4e0];
    ((void(__thiscall*)(void*))FUN_00f2d680)(&local);
    if (((char(__thiscall*)(void*))FUN_00f25730)(rec) != 0) {
        ((void(__thiscall*)(void*))FUN_00f42a50)(&local);
        uint32_t n = (uint32_t)((char*)mpWorld->mNounsEnd - (char*)mpWorld->mNounsBegin) / 0x534;
        ((void(__thiscall*)(void*, void*, uint32_t))FUN_00f438f0)(&rec->mSet70, &local, n);
        rec->mMode24 = 0;
        rec->mMode48 = 0;
    }
    ((void(__thiscall*)(void*, int))FUN_00f425d0)(this, a);
    ((void(__thiscall*)(void*))FUN_00dfbba0)(&local);
}

// @ 0x00f43bf0
bool W::ApplyAction(int a, int b, int c)
{
    int local_c = 0;
    int local_8 = 0;
    int local_4 = 0;
    char found = 0;

    World* w = mpWorld;
    ActionList* it = (ActionList*)w->mListsBegin;
    ActionList* end = (ActionList*)w->mListsEnd;
    if (it != end) {
        do {
            uint32_t key = it->mField00;
            if (it->mKey08 == (uint32_t)a && it->mKey0C == (uint32_t)b &&
                it->mKey10 == (uint32_t)c) {
                if (found == 0) {
                    if (FUN_00f43200(&local_c, b, it->mKey20) == 0) {
                        local_c = a; local_8 = b; local_4 = c;
                    }
                    found = 1;
                }
                ((void(__thiscall*)(void*, int, void*))FUN_00f43af0)(this, (int)key, &local_c);
                it->mFlag24 = 1;
            }
            if (it->mMode2C == 2 && it->mTri30 == (uint32_t)a && it->mTri34 == (uint32_t)b &&
                it->mTri38 == (uint32_t)c) {
                if (found == 0) {
                    if (FUN_00f43200(&local_c, b, it->mKey48) == 0) {
                        local_c = a; local_8 = b; local_4 = c;
                    }
                    found = 1;
                }
                it->mTri30 = (uint32_t)local_c;
                it->mTri34 = (uint32_t)local_8;
                it->mTri38 = (uint32_t)local_4;
                it->mFlag4C = 1;
                ((void(__thiscall*)(void*, int))FUN_00f41a10)(this, (int)key);
                DispatchActionNotify(this, (int)key);
            }
            if (it->mMode50 == 2 && it->mTri58 == (uint32_t)a && it->mTri5C == (uint32_t)b &&
                it->mTri60 == (uint32_t)c) {
                if (found == 0) {
                    if (FUN_00f43200(&local_c, b, it->mKey70) == 0) {
                        local_c = a; local_8 = b; local_4 = c;
                    }
                    found = 1;
                }
                it->mTri58 = (uint32_t)local_c;
                it->mTri5C = (uint32_t)local_8;
                it->mTri60 = (uint32_t)local_4;
                it->mFlag74 = 1;
                ((void(__thiscall*)(void*, int))FUN_00f41a10)(this, (int)key);
                DispatchActionNotify(this, (int)key);
            }
            it = (ActionList*)((char*)it + 0x27e8);
        } while (it != end);
        if (found != 0)
            goto commit;
    }
    if (FUN_00f43200(&local_c, b, -1) == 0) {
        local_c = a; local_8 = b; local_4 = c;
    }

commit:
    {
        int idx = 0;
        ActionEntry* e = (ActionEntry*)w->mActionsBegin;
        ActionEntry* eEnd = (ActionEntry*)w->mActionsEnd;
        for (; e != eEnd; e = (ActionEntry*)((char*)e + 0x38)) {
            if (e->mField00 == (uint32_t)a && e->mField04 == (uint32_t)b &&
                e->mField08 == (uint32_t)c) {
                ((void(__thiscall*)(void*, int, void*))FUN_00f3bce0)(this, idx, &local_c);
                ((uint8_t*)e)[0x1c] = 1;
                found = 1;
            }
            ++idx;
        }
    }

    World* mgr = mpWorld;
    if (mgr->mSelKey0 == a && mgr->mSelKey1 == b && mgr->mSelKey2 == c) {
        mgr->mSelKey0 = local_c;
        mgr->mSelKey1 = local_8;
        mgr->mSelKey2 = local_4;
        if (mpActive != 0) {
            ((void*(__thiscall*)(void*))FUN_00b1fdb0)(FUN_00b3d300(&local_c));
            FUN_00f41bb0(this);
        }
        mgr->mDirty14C = 1;
        return 1;
    }
    return found;
}

// @ 0x00f43f20
bool W::RefreshActions()
{
    char dirty = 0;
    World* w = mpWorld;
    ActionList* it = (ActionList*)w->mListsBegin;
    ActionList* end = (ActionList*)w->mListsEnd;
    if (it != end) {
        do {
            if (((char(__thiscall*)(void*, void*))FUN_00f3c330)(this, &it->mKey08)) {
                ((char(__thiscall*)(void*, int, int, int))FUN_00f43bf0)(
                    this, (int)it->mKey08, (int)it->mKey0C, (int)it->mKey10);
                dirty = 1;
            }
            if (it->mTri30 != 0 && ((char(__thiscall*)(void*, void*))FUN_00f3c330)(this, &it->mTri30)) {
                ((char(__thiscall*)(void*, int, int, int))FUN_00f43bf0)(
                    this, (int)it->mTri30, (int)it->mTri34, (int)it->mTri38);
                dirty = 1;
            }
            if (it->mTri58 != 0 && ((char(__thiscall*)(void*, void*))FUN_00f3c330)(this, &it->mTri58)) {
                ((char(__thiscall*)(void*, int, int, int))FUN_00f43bf0)(
                    this, (int)it->mTri58, (int)it->mTri5C, (int)it->mTri60);
                dirty = 1;
            }
            it = (ActionList*)((char*)it + 0x27e8);
        } while (it != end);
    }

    ActionEntry* e = (ActionEntry*)w->mActionsBegin;
    ActionEntry* eEnd = (ActionEntry*)w->mActionsEnd;
    for (; e != eEnd; e = (ActionEntry*)((char*)e + 0x38)) {
        if (((char(__thiscall*)(void*, void*))FUN_00f3c330)(this, e)) {
            e->mField04 = 0x2b978c46;
            ((char(__thiscall*)(void*, int, int, int))FUN_00f43bf0)(
                this, (int)e->mField00, (int)e->mField04, (int)e->mField08);
            dirty = 1;
        }
    }

    World* mgr = mpWorld;
    int* sel = &mgr->mSelKey0;
    if (((char(__thiscall*)(void*, void*))FUN_00f3c330)(this, sel)) {
        mgr->mSelKey1 = 0x2b978c46;
        ((char(__thiscall*)(void*, int, int, int))FUN_00f43bf0)(
            this, mgr->mSelKey0, mgr->mSelKey1, mgr->mSelKey2);
        return 1;
    }
    return dirty;
}

// @ 0x00f440b0
uint32_t W::HandleMessage(unsigned msg, int arg)
{
    uint32_t r = msg;
    if (msg == 0x04249453) {
        int a = *(int*)(arg + 0x08);
        int b = *(int*)(arg + 0x10);
        int c = *(int*)(arg + 0x18);
        r = (uint32_t)FUN_004bbe20((void*)a, 0);
        if ((char)r != 0) {
            if (((char(__thiscall*)(void*, int, int, int))FUN_00f43bf0)(this, c, a, b))
                mFlag014 = 1;
            void* ms = FUN_0067dcc0();
            r = (uint32_t)((int(__thiscall*)(void*, int, int, int))(*((void***)ms))[0x14 / 4])(
                ms, 0x072bdb11, 0, 0);
        }
    } else if (msg == 0x57be4886) {
        mFlag02C = 1;
    } else if (msg == 0xf1ff568b) {
        if (*(char*)(arg + 0x0c) != 0) {
            r = (uint32_t)mpWorld;
            if (mpWorld != 0) {
                r = (uint32_t)FUN_004eb930((void*)arg, (char*)mpWorld + 8);
                if ((char)r != 0) {
                    *(uint32_t*)(arg + 0x10) = 0xa6c97621;
                    *(uint32_t*)(arg + 0x14) = 0x00b1b104;
                    *(uint32_t*)(arg + 0x18) = 0x490f6945;
                    *(uint8_t*)(arg + 0x0c) = 0;
                    r = 0xa6c97621;
                }
            }
        }
    }
    return r & 0xffffff00u;
}

// @ 0x00f44210
void W::RemoveAction(int idx)
{
    if (idx < 0)
        return;
    World* w = mpWorld;
    int count = (int)((char*)w->mNounsEnd - (char*)w->mNounsBegin) / 0x534;
    if (idx >= count)
        return;

    ((void*(__thiscall*)(void*, void*))FUN_00f44190)((char*)w + 0x23c,
        (char*)w->mNounsBegin + idx * 0x534);

    ActionList* it = (ActionList*)w->mListsBegin;
    ActionList* end = (ActionList*)w->mListsEnd;
    if (it != end) {
        uint32_t off = (uint32_t)idx * 0x4e0;
        do {
            char* p = (char*)it->mSubBegin + off;
            char* pe = (char*)it->mSubEnd;
            if (p + 0x4e0 < pe)
                eastl_copy534((T534*)(p + 0x4e0), (T534*)pe, (T534*)p);
            it->mSubEnd = pe - 0x4e0;
            ((void(__thiscall*)(void*))FUN_00dfbba0)(it->mSubEnd);
            it = (ActionList*)((char*)it + 0x27e8);
        } while (it != end);
    }

    WorldItem* cur;
    if (w->mItemsSize < 0x3fffffffu)
        cur = (WorldItem*)((char*)w->mItemsBegin + w->mItemsSize * 0x238);
    else
        cur = (WorldItem*)w->mItemsEnd;
    WorldItem* endIt = (WorldItem*)w->mItemsEnd;
    if (cur != endIt) {
        uint32_t subOff = (uint32_t)idx * 0x34;
        do {
            char* sub = (char*)cur->mSubBegin + subOff;
            char* subEnd = (char*)cur->mSubEnd;
            if (sub + 0x34 < subEnd)
                FUN_00dfc170(sub + 0x34, subEnd, sub);
            cur->mSubEnd = subEnd - 0x34;
            char* tailp = (char*)cur->mSubEnd;
            void* fp = *(void**)(tailp + 0x1c);
            if (fp != 0 && ((int*)((char*)fp - 4))[0] != 0)
                eastl_free(fp);
            do {
                uint32_t v = cur->mField00;
                cur = (WorldItem*)((char*)cur + 0x238);
                if (((v >> 0x1e) & 1) != 0)
                    break;
            } while (*(int*)cur < 0);
        } while (cur != endIt);
    }
}

// @ 0x00f44370
void* W::CreateAction(int a, void* b, void* c, float d)
{
    ActionRec* rec = (ActionRec*)((void*(__thiscall*)(void*, void*))FUN_00f3e8a0)(this, (void*)a);
    if (rec == 0)
        return 0;

    World* w = mpWorld;
    void* itemBase;
    if (w->mItemsSize < 0x3fffffffu)
        itemBase = (char*)w->mItemsBegin + w->mItemsSize * 0x238;
    else
        itemBase = w->mItemsEnd;
    if (FUN_00ef1990(itemBase, w->mItemsEnd, b) >= 0x400)
        return 0;

    uint8_t nameBuf[0x248];
    void* name = ((void*(__thiscall*)(void*))FUN_00f2aac0)(&nameBuf);
    int index = ((int(__thiscall*)(void*, void*))FUN_00f2ed20)((char*)w + 0x2c10, name);
    ((void(__thiscall*)(void*))FUN_00dfc5b0)(&nameBuf);

    WorldItem* v = (WorldItem*)((char*)w->mItemsBegin + 4 + index * 0x238);
    v->mField04 = (uint32_t)a;
    v->mIndex = (uint32_t)index;
    uint32_t* p3 = (uint32_t*)b;
    v->mField08 = p3[0];
    v->mField0C = p3[1];
    v->mField10 = p3[2];
    uint32_t* p4 = (uint32_t*)c;
    v->mField14 = p4[0];
    v->mField18 = p4[1];
    v->mField1C = p4[2];
    v->mField20 = p4[3];
    if (d > 0.0f) {
        uint8_t scratch[0x240];
        FUN_00eec3d0(scratch, v);
        v->mF24 = FUN_00f409a0(v, scratch, d, 0, &v->mF28);
    } else {
        v->mF24 = FUN_00f3b520();
        v->mF28 = DAT_01471064;
    }
    v->mF224 = 0.0f;

    uint32_t n = (uint32_t)((char*)w->mNounsEnd - (char*)w->mNounsBegin) / 0x534;
    ((void(__thiscall*)(void*, uint32_t))FUN_00f42ef0)(&v->mSubBegin, n);
    FUN_00eef7d0(v);
    void* active = FUN_00efc520();
    void* ref = FUN_00f3fa20(rec, active);

    int* h = (int*)((void*(__thiscall*)(void*, void*))FUN_00b474c0)(mSet090, &ref);
    *h = index;
    int** r = (int**)((void*(__thiscall*)(void*, void*))FUN_00b6ff20)(mSet0B0, &ref);
    int* old = *r;
    if (ref != old) {
        if (ref != 0)
            ((void(__thiscall*)(void*))(*((void***)ref))[0])(ref);
        *r = (int*)ref;
        if (old != 0)
            ((void(__thiscall*)(void*))(*((void***)old))[1])(old);
    }

    FUN_00eec440(v);
    ((void(__thiscall*)(void*, void*, int))FUN_00f3da90)(this, v, 0);
    ((void(__thiscall*)(void*, void*, void*))FUN_00f40bb0)(this, v, ref);
    ((void(__thiscall*)(void*))FUN_00f427c0)(this);

    void* srv = FUN_00883860();
    ((int(__thiscall*)(void*, int, int, int))(*((void***)srv))[0x14 / 4])(srv, 0x07311fe9, a, 0);
    return v;
}

// @ 0x00f445c0
void* W::PickAction(int* a)
{
    if (*a == -2) {
        if (mpActive == 0)
            ((void(__thiscall*)(void*, void*, void*))FUN_00f43420)(this, a + 1, a + 4);
        return mpActive;
    }

    void* item = 0;
    ActionRec* rec = (ActionRec*)((void*(__thiscall*)(void*, void*))FUN_00f3e8a0)(this, (void*)*a);
    if (rec != 0) {
        World* w = mpWorld;
        void* base;
        if (w->mItemsSize < 0x3fffffffu)
            base = (char*)w->mItemsBegin + w->mItemsSize * 0x238;
        else
            base = w->mItemsEnd;
        if (FUN_00ef1990(base, w->mItemsEnd, a) < 0x400) {
            int index = ((int(__thiscall*)(void*, void*))FUN_00f2ed20)((char*)w + 0x2c10, a);
            WorldItem* v = (WorldItem*)((char*)w->mItemsBegin + 4 + index * 0x238);
            v->mIndex = (uint32_t)index;
            item = v;
            void* active = FUN_00efc520();
            void* ref = FUN_00f3fa20(rec, active);
            int* h = (int*)((void*(__thiscall*)(void*, void*))FUN_00b474c0)(mSet090, &ref);
            *h = index;
            void* slot = ((void*(__thiscall*)(void*, void*))FUN_00b6ff20)(mSet0B0, &ref);
            ((void(__thiscall*)(void*, void*))FUN_00b5f950)(slot, ref);
            ((void(__thiscall*)(void*, void*, int))FUN_00f3da90)(this, v, 0);
            ((void(__thiscall*)(void*, void*, void*))FUN_00f40bb0)(this, v, ref);
            void* srv = FUN_00883860();
            ((int(__thiscall*)(void*, int, int, int))(*((void***)srv))[0x14 / 4])(
                srv, 0x07311fe9, *a, 0);
        }
    }
    return item;
}
