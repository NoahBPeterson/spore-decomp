// Slice s00e1eab0 (batch gold7, worker 19). Region 0x00e1eab0-0x00e1fb20.
// A Simulator UI panel family (derived from cUIMissionCardPanel): a property-reading
// notify handler, a list of {int,byte,ref} records with its push/splice/sort helpers, and
// the panel constructor/destructor pair.
//
// No exact PDB match was found for these VAs, so functions are named by role and the panel
// layout is taken from the disassembly byte offsets through a local stub class.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

#pragma warning(disable : 4100)

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef          int   s32;

// ---------------------------------------------------------------------------------------------
// retail record type (stride 0xc) and its reference-counted payload.
// ---------------------------------------------------------------------------------------------
class RefObj
{
  public:
    virtual void v00();            // +0x00
    virtual void AddRef();         // +0x04
    virtual void Release();        // +0x08
};

struct ListRec { u32 key; u8 flag; u8 pad[3]; RefObj* ref; };   // 0xc

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
extern "C" {
void* __cdecl FUN_00b3d300();                       // 0x00b3d300 SP::NounManager()
void* __cdecl FUN_00b3d3f0();                       // 0x00b3d3f0
void* __cdecl FUN_00b3d3c0();                       // 0x00b3d3c0
void* __cdecl FUN_00a206f0();                       // 0x00a206f0 EA::Audio::GetSystemAT
void* __cdecl FUN_0067de30();                       // 0x0067de30 SP::PropertyManager
void* __cdecl FUN_0067dcc0();                       // 0x0067dcc0 MessageServer
bool  __fastcall FUN_00c8e850(void* tribe);          // 0x00c8e850 tribe herbivore test (ecx)
void* __fastcall FUN_00bfc5f0(void* nouns);          // 0x00bfc5f0 cGameNounManager::GetPlayerTribe (ecx)
u32   __cdecl FUN_00bda3b0(int a, int b, int c, int d); // 0x00bda3b0
u32   __cdecl FUN_00932e80(const char* s, int seed, int flag); // 0x00932e80 FNVHash
void* __cdecl FUN_0041ea00(void* prop);              // 0x0041ea00 Property::GetUInt
void  __fastcall FUN_00e186d0(void* self, int, int a, int b, int c, int d); // 0x00e186d0 OnNotify (ecx=this)
void  __fastcall FUN_00e0a390(void* p);              // 0x00e0a390 Init
void  __fastcall FUN_00e0a400(void* p);              // 0x00e0a400 Destroy
void  __fastcall FUN_00e18bb0(void* p);              // 0x00e18bb0 Construct
void  __fastcall FUN_00e18980(void* p);              // 0x00e18980 DestroyMembers
void  __fastcall FUN_00e1e120(void* p);              // 0x00e1e120
void  __fastcall FUN_00e1f280(void* p);              // 0x00e1f280
void  __fastcall FUN_00e1e500(void* self, int, u32 k, u32 a, u32 b, u32 c, u32 d); // 0x00e1e500
void  __fastcall FUN_00e0a4c0(void* self, int, void* w);  // 0x00e0a4c0
void* __cdecl FUN_00f473a0(u32 size, const char* file, int line, int a, const char* f2, int b); // 0x00f473a0 operator new
void  __cdecl FUN_00f47380(void* p);                 // 0x00f47380 operator delete
void  __cdecl FUN_00973d10(void* out, void* iter);   // 0x00973d10 ListErase

// ef90 helpers
void  __fastcall FUN_005ed320(void* p, int, int a);  // 0x005ed320 palette item enable
void* __fastcall FUN_005ed360(void* p, int, int a);  // 0x005ed360 cSPPaletteItemRollover ctor (ecx)
void  __fastcall FUN_005ed6c0(void* p);              // 0x005ed6c0 Hide
void* __fastcall FUN_00663040(void* p);              // 0x00663040 cSPUIFeedList ctor
int   __fastcall FUN_00662a10(void* p);              // 0x00662a10 feed list category count
void* __fastcall FUN_00662a20(void* p, int, int i);  // 0x00662a20 feed list category at i
int   __fastcall FUN_00664600(void* p);              // 0x00664600 item count
void* __fastcall FUN_00664610(void* p, int, int i);  // 0x00664610 item at i
void  __fastcall FUN_006644e0(void* p, int, int a);  // 0x006644e0 select category
void  __fastcall FUN_00663860(void* p, int, void* w, u32 a, u32 b, u32 c); // 0x00663860 configure feed list
void  __fastcall FUN_00e30a60(void* self, int, int a);   // 0x00e30a60
void  __fastcall FUN_00eada10(void* list, int, void* a); // 0x00eada10 cList push
int   __cdecl FUN_00432f10(int a);                   // 0x00432f10 RemapTypeId
void* __fastcall FUN_00a16f40(void* x);              // 0x00a16f40 AsPPTypeParam (ecx)
void  __cdecl FUN_006a1250(void* obj, u32 key, void* out); // 0x006a1250 GetPropertyAsKey
void  __cdecl FUN_006a12a0(void* obj, u32 key, void* out); // 0x006a12a0 GetPropertyAsKeyInstance
void* __fastcall FUN_0059f030(void* self, int, u32 rk0, u32 rk1, u32 rk2, u32 key, u32 a, u32 b, u32 c); // 0x0059f030 ctor
void  __fastcall FUN_005ee480(void* self, int, void* rec, void* holder, void* veh, u32 flag); // 0x005ee480 SetItem
void  __fastcall FUN_008283a0(void* self, int, float a, float b, float c, float d); // 0x008283a0 SetPositionAndOffset
void  __cdecl FUN_00435ed0(u32 id, void* audio);     // 0x00435ed0 KillSetiEffects
void* __cdecl FUN_008105b0(void* layout, u32 id, int a); // 0x008105b0 FindWindowByID

// small-list helpers (see cards); record stride 0xc = {u32 key; u8 flag; pad; RefObj* ref}
void* __cdecl FUN_00e1e240(void* dst, void* src, void* end); // 0x00e1e240 uninitialized_move
void* __cdecl FUN_00e1e290(void* dst, void* src, void* end); // 0x00e1e290 destroy range
void* __cdecl FUN_00e1e390(void* begin, void* end, void* val); // 0x00e1e390 lower_bound
void  __cdecl FUN_00e1e3f0(void* a, void* b, void* c);       // 0x00e1e3f0 move_backward
void  __cdecl FUN_00e1e450(void* a, void* b);                // 0x00e1e450 iter_swap
void  __cdecl FUN_00e1e6d0(void* a, void* b, void* c);       // 0x00e1e6d0 heap/insertion
void  __cdecl FUN_00e1e7d0(void* a, void* b, void* c);       // 0x00e1e7d0 heap/insertion
void* __cdecl FUN_00e1e8c0(void* a, int b, int c, int d, u32 key, u8 flag, RefObj* ref, void* cmp); // 0x00e1e8c0 heap adjust
void  __cdecl FUN_00e1f5c0(void* a, void* b, void* c, void* d); // 0x00e1f5c0 insertion sort
}

// ---------------------------------------------------------------------------------------------
// UI panel stub with the retail byte offsets used by this cluster.
// ---------------------------------------------------------------------------------------------
class PanelBase
{
  public:
    void* mVt0;                    // 0x00 vtable
    unsigned char pad004[0x08];
    void* mMsg0c;                  // 0x0c message target
    unsigned char pad010[0x04];
    u32   mKey14;                  // 0x14 player tribe type key
    void* mLayout18;               // 0x18 UI layout
    unsigned char pad01c[0x40 - 0x1c];
    RefObj* mpRef40;               // 0x40
    RefObj* mpRef44;               // 0x44
    RefObj* mpRef48;               // 0x48
    unsigned char pad04c[0xbc - 0x4c];
    RefObj* mpRefBC;               // 0xbc
    unsigned char pad0c0[0xd4 - 0xc0];
    ListRec* mListBegin;           // 0xc0
    ListRec* mListEnd;             // 0xc4  (see note: helpers use +0xc0/+0xc4 as raw list)
    unsigned char pad0c8[0xd4 - 0xc8];
    u32 mPropD4;                   // 0xd4
    u32 mPropD8;                   // 0xd8
    u32 mPropDC;                   // 0xdc
    u32 mPropE0;                   // 0xe0
    u16 mWordE4;                   // 0xe4
};

// ---------------------------------------------------------------------------------------------
// 0x00e1eab0 -- UI panel notify handler: translate the notification id into a property id, read
// the configured uint properties, then dispatch either a "create palette" path or a message.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1eab0
void __fastcall FUN_00e1eab0(PanelBase* self, int, int notifyId, int arg2, int arg3, int arg4)
{
    (*(void (__thiscall**)(PanelBase*))(*(char**)self + 0x14))(self);

    u32 key;
    if (notifyId == 0x01654c00)
        key = 0xa426730b;
    else if (notifyId == 0x01654c01)
        key = 0xad56080c;
    else
        key = ((u32)(-(s32)(arg2 != 0x6722bd6)) & 0xc5456627u) + 0x31da3cea;

    void* prop = 0;
    void* pm = FUN_0067de30();
    if (prop) {
        void* t = prop;
        prop = 0;
        (*(void (__thiscall**)(void*))(*(char**)t + 4))(t);
    }
    (*(void (__thiscall**)(void*, u32, u32, void**))(*(char**)pm + 0x2c))(pm, key, 0x7b2c1325, &prop);
    if (prop) {
        void* pv;
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x5eea218, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            self->mPropD4 = *(u32*)FUN_0041ea00(pv);
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x9377367d, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            self->mPropD8 = *(u32*)FUN_0041ea00(pv);
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x55dd9f6, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            self->mPropDC = *(u32*)FUN_0041ea00(pv);
    }
    u16 wE4 = 0x268b;
    if (prop) {
        void* pv;
        if ((*(bool (__thiscall**)(void*, u32, void**))(*(char**)prop + 0x24))(prop, 0x84ce9c17, &pv)
                && *(u16*)((char*)pv + 0x12) == 10)
            wE4 = *(u16*)FUN_0041ea00(pv);
    }
    self->mWordE4 = wE4;

    FUN_00e186d0(self, 0, notifyId, arg2, arg3, arg4);

    u32 s0 = 0xffffffff, s1 = 0xffffffff, s2 = 0;
    if (notifyId == 0x01654c00) { s0 = 0x1d2ec0a4; s1 = 0xdfad9f51; s2 = 0x3d97a8e4; }
    else if (notifyId == 0x01654c01) { s0 = 0x465c50ba; s1 = 0x9ea3031a; s2 = 0x2b978c46; }
    else if (notifyId == 0x01654c02) { s0 = 0x156276d1; s1 = 0x372e2c04; s2 = 0x2b978c46; }

    u32 qk = 0, qa = 0, qb = 0;
    if (self->mKey14 == 0x6722bd6) {
        void* nouns = FUN_00b3d300();
        void* tribe = FUN_00bfc5f0(nouns);
        if (tribe == 0) {
            void* ms = FUN_0067dcc0();
            (*(void (__thiscall**)(void*, void*, u32))(*(char**)ms + 0x24))(ms, self->mMsg0c, 0x1e8c9e0);
        } else {
            qa = 0xb1b104;
            qb = 0x406b6a00;
            void* nouns2 = FUN_00b3d300();
            void* tribe2 = FUN_00bfc5f0(nouns2);
            const char* name = FUN_00c8e850(tribe2) ? "PaletteIDTribeHerbivore" : "PaletteIDTribeCarnivore";
            u32 a = FUN_00932e80(name, 0x811c9dc5, 1);
            u32 b = FUN_00932e80("CommunityEditor", 0x811c9dc5, 1);
            qk = FUN_00bda3b0(b, 0, a, 0x41);
        }
    } else {
        void* prop2 = 0;
        void* pm2 = FUN_0067de30();
        if (prop2) {
            void* t = prop2;
            prop2 = 0;
            (*(void (__thiscall**)(void*))(*(char**)t + 4))(t);
        }
        (*(void (__thiscall**)(void*, u32, u32, void**))(*(char**)pm2 + 0x2c))(pm2, s0, 0x015a5200, &prop2);
        FUN_006a1250(prop2, 0xf5cbe065, &qk);
        if (prop2)
            (*(void (__thiscall**)(void*))(*(char**)prop2 + 4))(prop2);
    }

    FUN_00e1e500(self, 0, qk, qa, qb, s1, s2);

    if (self->mpRefBC == 0) {
        void* mem = FUN_00f473a0(0xc8, (const char*)0x013f6b3c, 0, 0, (const char*)0, 0);
        void* n = mem ? FUN_005ed360(mem, 0, 1) : 0;
        RefObj* old = self->mpRefBC;
        if (n != old) {
            if (n)
                (*(void (__thiscall**)(void*))(*(char**)n + 0))(n);
            self->mpRefBC = (RefObj*)n;
            if (old)
                (*(void (__thiscall**)(RefObj*))(*(char**)old + 4))(old);
        }
    }
    (*(void (__thiscall**)(RefObj*))(*(char**)self->mpRefBC + 0x1c))(self->mpRefBC);

    if (self->mPropDC != 0) {
        void* mem = FUN_00f473a0(0x6c, (const char*)0x013f6b3c, 0, 0, (const char*)0, 0);
        void* n = mem ? FUN_00663040(mem) : 0;
        RefObj* old = self->mpRef48;
        if (n != old) {
            if (n)
                (*(void (__thiscall**)(void*))(*(char**)n + 0))(n);
            self->mpRef48 = (RefObj*)n;
            if (old)
                (*(void (__thiscall**)(RefObj*))(*(char**)old + 4))(old);
        }
        void* w = FUN_008105b0(self->mLayout18, 0x5e95451, 1);
        FUN_00663860(self->mpRef48, 0, w, self->mPropDC, 0, 0);

        int ncat = FUN_00662a10(self->mpRef48);
        int cat = 0;
        int itemIdx = 0;
        while (cat < ncat) {
            void* c = FUN_00662a20(self->mpRef48, 0, cat);
            if (c != 0) {
                int nitems = FUN_00664600(c);
                for (int i = 0; i < nitems; ++i) {
                    void* it = FUN_00664610(c, 0, i);
                    if (it != 0) {
                        void* obj = *(void**)((char*)it + 0xa0);
                        ++itemIdx;
                        (*(void (__thiscall**)(void*, int))(*(char**)obj + 0x50))(obj, itemIdx + 0x66f5fde);
                    }
                }
            }
            ++cat;
        }
        if (FUN_00662a10(self->mpRef48) == 1) {
            void* c = FUN_00662a20(self->mpRef48, 0, 0);
            FUN_006644e0(c, 0, 0);
        }
        void* ms = FUN_0067dcc0();
        (*(void (__thiscall**)(void*, void*, u32))(*(char**)ms + 0x24))(ms, self->mMsg0c, 0x5bf34455);
    }

    void* w2 = FUN_008105b0(self->mLayout18, 0x5e9545c, 1);
    FUN_00e0a4c0((char*)self + 0x4c, 0, w2);

    if (prop)
        (*(void (__thiscall**)(void*))(*(char**)prop + 4))(prop);
}

// ---------------------------------------------------------------------------------------------
// 0x00e1ef90 -- palette item rollover handler: on hover, configure the feed list / vehicle
// abilities panel for the hovered record, or hide the rollover on un-hover.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1ef90
void __fastcall FUN_00e1ef90(void* self, int, void* item, int flag)
{
    if (item == 0)
        return;

    int idx = (*(int (__thiscall**)(void*))(*(char**)item + 0x1c))(item);
    int count = (*(int*)((char*)self + 0xc4) - *(int*)((char*)self + 0xc0)) / 0xc;
    int rec = idx - 0x66652c2;
    if ((u32)rec >= (u32)count)
        return;

    void* roll = (*(void* (__thiscall**)(void*, u32, int))(*(char**)item + 0xf0))(item, 0x60b0e48, 0);
    if (roll != 0)
        (*(void (__thiscall**)(void*, int, int))(*(char**)roll + 0x7c))(roll, 1, flag);

    if (flag == 0) {
        FUN_005ed6c0(*(void**)((char*)self + 0xbc));
        return;
    }

    void* audio = FUN_00a206f0();
    void* audioObj = audio ? (void*)(*(int (__thiscall**)(void*))(*(char**)audio + 0x20))(audio) : 0;
    FUN_00435ed0(0x8821b509, audioObj);

    void* recPtr = (char*)*(void**)((char*)self + 0xc0) + rec * 0xc;
    void* ref = *(void**)((char*)recPtr + 8);

    void* wrapObj = FUN_00b3d3f0();
    void* wrap = *(void**)((char*)wrapObj + 0x5c);
    FUN_00e30a60(wrap, 0, idx);
    FUN_00eada10((char*)self + 0x34, 0, (char*)ref + 0xc);

    void* holder = *(void**)((char*)self + 0x44);
    int key = *(int*)((char*)holder + 0x2c);
    if (key != -1) {
        int mt = FUN_00432f10(key);
        if (mt != -1) {
            u32 loc[3] = { 0, 0, 0 };
            void* propObj = 0;
            void* pp = FUN_00a16f40((void*)&propObj);
            void* pm = FUN_0067de30();
            (*(void (__thiscall**)(void*, int, u32, void*))(*(char**)pm + 0x2c))(pm, mt, 0x015a5200, pp);
            if (propObj != 0) {
                FUN_006a1250(propObj, 0x4aa3989, loc);
                if (loc[0] != 0) {
                    void* propObj2 = 0;
                    void* pp2 = FUN_00a16f40((void*)&propObj2);
                    void* pm2 = FUN_0067de30();
                    (*(void (__thiscall**)(void*, u32, u32, void*))(*(char**)pm2 + 0x2c))(pm2, loc[1], loc[2], pp2);
                    if (propObj2 != 0) {
                        FUN_006a12a0(propObj2, 0x4ab54c1, &loc[0]);
                        (*(void (__thiscall**)(void*))(*(char**)propObj2 + 4))(propObj2);
                    }
                }
                (*(void (__thiscall**)(void*))(*(char**)propObj + 4))(propObj);
            }
        }
    }

    void* mem = FUN_00f473a0(0x64, (const char*)0x013f6b3c, 0, 0, (const char*)0, 0);
    void* veh = 0;
    if (mem != 0) {
        veh = FUN_0059f030(mem, 0, *(u32*)((char*)ref + 0), *(u32*)((char*)ref + 4), *(u32*)((char*)ref + 8),
                           *(u32*)((char*)holder + 0x2c), 0x14880158, 0, 1);
        if (veh != 0)
            (*(void (__thiscall**)(void*))(*(char**)veh + 4))(veh);
    }
    FUN_005ee480(*(void**)((char*)self + 0xbc), 0, ref, *(void**)((char*)self + 0x44), veh, 1);

    int* pv = (int*)(*(int (__thiscall**)(void*))(*(char**)item + 0x34))(item);
    float d = *(float*)((char*)pv + 0xc) - *(float*)((char*)pv + 4);
    float local[2] = { 0.0f, d };
    (*(void (__thiscall**)(void*, float*))(*(char**)item + 0xc0))(item, local);

    FUN_008283a0(*(void**)((char*)self + 0xbc), 0, local[0], local[1], -10.0f, 5.0f);
    FUN_005ed320(*(void**)((char*)self + 0xbc), 0, 2);

    if (veh != 0)
        (*(void (__thiscall**)(void*))(*(char**)veh + 8))(veh);
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f2c0 -- rebuild a max-heap over the panel record vector.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f2c0
int __cdecl FUN_00e1f2c0(ListRec* first, ListRec* last, void* cmp)
{
    int n = (int)(((char*)last - (char*)first) / 0xc);
    int r = (int)(u32)(0x2aaaaaabu * (u32)((char*)last - (char*)first));
    if (n > 1) {
        int i = ((n - 2) >> 1) + 1;
        ListRec* p = first + i;
        do {
            u32 key = p[-1].key;
            u8 flag = p[-1].flag;
            RefObj* ref = p[-1].ref;
            --i;
            if (ref)
                (*(void (__thiscall**)(RefObj*))(*(char**)ref + 4))(ref);
            r = (int)(size_t)FUN_00e1e8c0(first, i, n, i, key, flag, ref, cmp);
            --p;
        } while (i != 0);
    }
    return r;
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f390 -- panel constructor: install vtables, Init sub-objects, zero the members.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f390
void* __fastcall FUN_00e1f390(void* self)
{
    FUN_00e18bb0(self);
    *(void**)self = (void*)0x14803ac;
    *(void**)((char*)self + 8) = (void*)0x1480390;
    *(void**)((char*)self + 0xc) = (void*)0x1480388;
    *(void**)((char*)self + 0x40) = 0;
    *(void**)((char*)self + 0x44) = 0;
    *(void**)((char*)self + 0x48) = 0;
    FUN_00e0a390((char*)self + 0x4c);
    *(void**)((char*)self + 0xbc) = 0;
    *(void**)((char*)self + 0xc0) = 0;
    *(void**)((char*)self + 0xc4) = 0;
    *(void**)((char*)self + 0xc8) = 0;
    *(void**)((char*)self + 0xd4) = 0;
    *(void**)((char*)self + 0xd8) = 0;
    *(void**)((char*)self + 0xdc) = 0;
    *(void**)((char*)self + 0xe0) = 0;
    return self;
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f420 -- panel destructor.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f420
void __fastcall FUN_00e1f420(void* self)
{
    *(void**)self = (void*)0x14803ac;
    *(void**)((char*)self + 8) = (void*)0x1480390;
    *(void**)((char*)self + 0xc) = (void*)0x1480388;
    FUN_00e1e120(self);
    FUN_00e1f280((char*)self + 0xc0);
    RefObj* r1 = *(RefObj**)((char*)self + 0xbc);
    if (r1)
        (*(void (__thiscall**)(RefObj*))(*(char**)r1 + 4))(r1);
    FUN_00e0a400((char*)self + 0x4c);
    RefObj* r2 = *(RefObj**)((char*)self + 0x48);
    if (r2)
        (*(void (__thiscall**)(RefObj*))(*(char**)r2 + 4))(r2);
    RefObj* r3 = *(RefObj**)((char*)self + 0x44);
    if (r3)
        (*(void (__thiscall**)(RefObj*))(*(char**)r3 + 8))(r3);
    RefObj* r4 = *(RefObj**)((char*)self + 0x40);
    if (r4)
        (*(void (__thiscall**)(RefObj*))(*(char**)r4 + 8))(r4);
    FUN_00e18980(self);
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f4a0 -- notification callback: dispatch on the notification subtype.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f4a0
u8 __fastcall FUN_00e1f4a0(void* self, int, void* arg1, void* msg)
{
    int* p = (int*)msg;
    (void)arg1;
    u32 r;
    if (p[2] == 0x1b) {
        r = (*(u32 (__thiscall**)(int))(*(int*)*p + 0x20))(*p);
        if (r == 0x66651c3)
            FUN_00e1ef90((char*)self - 8, 0, (void*)*p, 1);
    } else {
        r = (u32)p[2] - 0x1c;
        if (r == 0) {
            r = (*(u32 (__thiscall**)(int))(*(int*)*p + 0x20))(*p);
            if (r == 0x66651c3)
                FUN_00e1ef90((char*)self - 8, 0, (void*)*p, 0);
        }
    }
    return (u8)(r & 0xffffff00);
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f500 -- append a copy of the node range [first,last) to the list headed by `head`.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f500
void __stdcall FUN_00e1f500(void* head, void* first, void* last, void* extra)
{
    char* cur = (char*)first;
    (void)extra;
    while (cur != last) {
        char* node = (char*)FUN_00f473a0(0x10, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        node = node;
        *(u32*)(node + 8) = *(u32*)(cur + 8);
        *(u32*)(node + 0xc) = *(u32*)(cur + 0xc);
        *(void**)node = head;
        *(void**)(node + 4) = *(void**)((char*)head + 4);
        *(void**)(*(void**)((char*)head + 4)) = node;
        *(void**)((char*)head + 4) = node;
        cur = *(char**)cur;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f570 -- partition for the record sort.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f570
void* __cdecl FUN_00e1f570(void* first, void* last, u32 key, u8 flag, RefObj* ref, void* cmp)
{
    char* f = (char*)first;
    char* l = (char*)last;
    u32 pivot = key;
    for (;;) {
        while (*(u32*)f < pivot)
            f += 0xc;
        do {
            l -= 0xc;
        } while (pivot < *(u32*)l);
        if (f >= l)
            break;
        FUN_00e1e450(f, l);
        f += 0xc;
    }
    if (ref)
        (*(void (__thiscall**)(RefObj*))(*(char**)ref + 8))(ref);
    (void)flag;
    (void)cmp;
    return f;
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f700 -- insert [a,b) into the sorted record vector, destroying any overwritten tail.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f700
void* __fastcall FUN_00e1f700(void* self, int, void* a, void* b)
{
    char* end = *(char**)((char*)self + 4);
    char* pos = (char*)FUN_00e1e390((char*)b, end, (char*)a);
    if (pos < end) {
        char* p = pos + 8;
        int n = (int)((end - pos) - 1) / 0xc + 1;
        do {
            RefObj* r = *(RefObj**)p;
            if (r)
                (*(void (__thiscall**)(RefObj*))(*(char**)r + 8))(r);
            p += 0xc;
            --n;
        } while (n != 0);
    }
    *(char**)((char*)self + 4) = end + (int)(((char*)a - (char*)b) / 0xc) * 0xc;
    return a;
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f780 -- record-vector insert/emplace at `pos` with value `val` (grows to 2x).
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f780
void __fastcall FUN_00e1f780(void* self, int, void* pos, void* val)
{
    char* begin = *(char**)((char*)self);
    char* end = *(char**)((char*)self + 4);
    char* cap = *(char**)((char*)self + 8);
    if (end != cap) {
        if (pos <= val && val < end)
            val = (char*)val + 0xc;
        if (end) {
            *(u32*)end = *(u32*)(end - 0xc);
            *(u8*)(end + 4) = *(u8*)(end - 8);
            RefObj* r = *(RefObj**)(end - 4);
            *(RefObj**)(end + 8) = r;
            if (r)
                (*(void (__thiscall**)(RefObj*))(*(char**)r + 4))(r);
        }
        FUN_00e1e3f0(pos, end - 0xc, end);
        *(u32*)pos = *(u32*)val;
        *(u8*)((char*)pos + 4) = *(u8*)((char*)val + 4);
        RefObj* rn = *(RefObj**)((char*)val + 8);
        RefObj* ro = *(RefObj**)((char*)pos + 8);
        if (rn != ro) {
            if (rn)
                (*(void (__thiscall**)(RefObj*))(*(char**)rn + 4))(rn);
            *(RefObj**)((char*)pos + 8) = rn;
            if (ro)
                (*(void (__thiscall**)(RefObj*))(*(char**)ro + 8))(ro);
        }
        *(char**)((char*)self + 4) = end + 0xc;
        return;
    }

    int count = (int)((end - begin) / 0xc);
    int newcap;
    char* mem;
    if (count == 0) {
        newcap = 1;
    } else {
        newcap = count * 2;
        if (newcap == 0) {
            mem = 0;
            goto build;
        }
    }
    mem = (char*)FUN_00f473a0(newcap * 0xc, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
build:
    {
        char* mid = (char*)FUN_00e1e240(begin, pos, mem);
        FUN_00e1e290(begin, pos, mem);
        if (mid) {
            *(u32*)mid = *(u32*)val;
            *(u8*)(mid + 4) = *(u8*)((char*)val + 4);
            RefObj* r = *(RefObj**)((char*)val + 8);
            *(RefObj**)(mid + 8) = r;
            if (r)
                (*(void (__thiscall**)(RefObj*))(*(char**)r + 4))(r);
        }
        char* tailEnd = (char*)FUN_00e1e240(pos, end, mid + 0xc);
        FUN_00e1e290(pos, end, mid + 0xc);
        if (begin && *(int*)(begin - 4) != 0)
            FUN_00f47380(begin);
        *(char**)((char*)self + 4) = tailEnd;
        *(char**)((char*)self) = mem;
        *(char**)((char*)self + 8) = mem + newcap * 0xc;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00e1f920 -- intro-sort recursion over the record vector.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1f920
void __cdecl FUN_00e1f920(char* first, char* last, int depth, void* cmp)
{
    while (0x1c < (int)((last - first) / 0xc) && depth > 0) {
        int n = (int)((last - first) / 0x18);
        char* mid = first + n * 0xc;
        u32 ukFirst = *(u32*)first;
        u32 ukMid = *(u32*)mid;
        u32 ukLast = *(u32*)(last - 0xc);
        char* med;
        if (ukFirst >= ukMid) {
            if (ukFirst >= ukLast)
                med = (ukMid >= ukLast) ? mid : last - 0xc;
            else
                med = first;
        } else {
            if (ukMid < ukLast)
                med = mid;
            else
                med = (ukFirst >= ukLast) ? first : last - 0xc;
        }

        ListRec pivot = *(ListRec*)med;
        if (pivot.ref)
            (*(void (__thiscall**)(RefObj*))(*(char**)pivot.ref + 4))(pivot.ref);
        char* p = (char*)FUN_00e1f570(first, last, pivot.key, pivot.flag, pivot.ref, cmp);
        --depth;
        FUN_00e1f920(p, last, depth, cmp);
        last = p;
    }
    if (depth == 0)
        FUN_00e1f5c0(first, last, last, cmp);
}

// ---------------------------------------------------------------------------------------------
// 0x00e1fa20 -- splice the node range of one list into another.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1fa20
void* __fastcall FUN_00e1fa20(void* self, int, void* other)
{
    char* s = (char*)self;
    char* o = (char*)other;
    if (s != o) {
        char* p2 = *(char**)o;
        char* p1 = *(char**)s;
        while (p1 != s) {
            if (p2 == o)
                goto erase;
            *(void**)(p1 + 8) = *(void**)(p2 + 8);
            *(void**)(p1 + 0xc) = *(void**)(p2 + 0xc);
            p2 = *(char**)p2;
            p1 = *(char**)p1;
        }
        if (p2 == o) {
erase:
            FUN_00973d10(&o, p1);
            return self;
        }
        FUN_00e1f500(s, p2, o, o);
    }
    return self;
}

// ---------------------------------------------------------------------------------------------
// 0x00e1fa90 -- sort the record vector, falling back to a partial sort for long ranges.
// ---------------------------------------------------------------------------------------------
// @ 0x00e1fa90
void __cdecl FUN_00e1fa90(char* first, char* last, void* cmp)
{
    if (first != last) {
        int n = (int)((last - first) / 0xc);
        int bits = 0;
        for (int v = n; v != 0; v >>= 1)
            ++bits;
        FUN_00e1f920(first, last, bits * 2 - 2, cmp);
        if (n > 0x1c) {
            FUN_00e1e6d0(first, first + 0x150, cmp);
            FUN_00e1e7d0(first + 0x150, last, cmp);
        } else {
            FUN_00e1e6d0(first, last, cmp);
        }
    }
}
