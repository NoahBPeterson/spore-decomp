// Slice s00e3dca0 -- destructor body (no delete) of a large editor/UI object whose vtables are
// 0x01481eb4 / 0x01481e98 / ... : releases ~60 owned interface pointers, 19 EASTL strings, a
// string hashtable, maps, an EA::Messaging handler registration, then chains to cGonzagoSubsystem.
#include "types.h"

typedef unsigned short char16;

extern "C" void __cdecl operator_delete_arr(void* p);                // 0x00f47380 operator delete[]
extern "C" void __cdecl EA_Messaging_RemoveHandler(void* server, void* a, void* b, void* c, void* d); // 0x00571db0

// Interfaces released through a vtable slot.
struct IRel4 { virtual void v0(); virtual void Release(); };                    // Release at +4
struct IRel8 { virtual void v0(); virtual void v1(); virtual void Release(); }; // Release at +8

// 16-byte EASTL string16 (begin/end/capacity + allocator), inline destructor.
struct string16 {
    char16* mpBegin; char16* mpEnd; char16* mpCapacity; uint32_t mAllocator;
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_arr(mpBegin);
        }
    }
};

// Out-of-line members of stub types (thiscall).
struct Sub24 { void* vtbl; uint32_t d[2]; void Dtor(); };                       // 0x005725a0
struct GonzagoBase { uint32_t d[7]; void Dtor(); };                             // 0x00b5b9a0 ~cGonzagoSubsystem
struct StrMapA { uint32_t d[3]; void* mpRoot; uint32_t e[3]; void Nuke(void* root); ~StrMapA() { Nuke(mpRoot); } };                       // 0x00d0c930
struct StrMapB { uint32_t d[3]; void* mpRoot; uint32_t e[3]; void Nuke(void* root); ~StrMapB() { Nuke(mpRoot); } };                       // 0x00f240d0
struct StrMapC { uint32_t d[3]; void* mpRoot; uint32_t e[3]; void Nuke(void* root); ~StrMapC() { Nuke(mpRoot); } };                       // 0x009a9600 rbtree::DoNukeSubtree
struct Blk170 { uint32_t d[5]; void Dtor(); };                                  // 0x004b5440
struct StarVec { uint32_t d[5]; void Dtor(); };                                 // 0x00ae6970 vector<AutoRefCount<cStarRecord>>::~vector
struct Blk198 { uint32_t d[12]; void Dtor(); };                                 // 0x008e2b20

struct StrHashtable {                                                           // hashtable<wchar_t const*, ...>
    void* mTraits;
    void** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    void DoFreeNodes(void** buckets, uint32_t n);                               // 0x00693230
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    ~StrHashtable() {
        clear();
        if (mnBucketCount > 1)
            operator_delete_arr(mpBucketArray);
    }
};

struct Obj3c4 { uint32_t pad[4]; IRel4 sec; };                                  // released via secondary base at +0x10

struct MsgHandlerReg {                                                          // EA::Messaging registration
    void* mpServer; void* mA; void* mB; void* mC; void* mD;
    ~MsgHandlerReg() {
        void* h = mpServer;
        if (h) {
            mpServer = 0;
            EA_Messaging_RemoveHandler(h, mA, mB, mC, mD);
        }
    }
};

struct cBigEditorObject {
    void* vtbl0;                    // 0x000
    void* vtbl4;                    // 0x004
    GonzagoBase gonzago;            // 0x008 (0x1c bytes; its vtables live at +8 and +0xc)
    Sub24 sub24;                    // 0x024
    IRel8* r30; IRel8* r34;         // 0x030, 0x034
    IRel4* r38[16];                 // 0x038 .. 0x074
    uint32_t pad78[12];             // 0x078
    IRel4* ra8;                     // 0x0a8
    uint32_t padac[7];              // 0x0ac
    StrMapA mapC8;                  // 0x0c8
    StrMapB mapE4;                  // 0x0e4
    StrMapB map100;                 // 0x100
    StrMapB map11c;                 // 0x11c
    StrMapC map138;                 // 0x138
    StrMapC map154;                 // 0x154
    Blk170 blk170;                  // 0x170
    StarVec stars184;               // 0x184
    Blk198 blk198;                  // 0x198
    IRel4* r1c8; IRel8* r1cc; IRel8* r1d0; IRel4* r1d4; IRel4* r1d8; // 0x1c8 .. 0x1d8
    uint32_t pad1dc[(0x250 - 0x1dc) / 4]; // 0x1dc .. 0x24f
    StrMapC map250;                 // 0x250
    uint32_t pad26c[(0x330 - 0x26c) / 4];
    IRel4* r330;                    // 0x330
    MsgHandlerReg reg334;           // 0x334
    IRel8* r348; IRel8* r34c;       // 0x348, 0x34c
    uint32_t pad350[(0x374 - 0x350) / 4];
    IRel4* arrA[10];                // 0x374
    IRel4* arrB[10];                // 0x39c
    Obj3c4* o3c4;                   // 0x3c4
    IRel4* arrC[10];                // 0x3c8
    uint32_t pad3f0[(0x460 - 0x3f0) / 4];
    char* a460;                     // 0x460
    uint32_t pad464[(0x474 - 0x464) / 4];
    char* a474;                     // 0x474
    uint32_t pad478[(0x560 - 0x478) / 4];
    StrHashtable ht560;             // 0x560
    uint32_t pad570[(0x5d4 - 0x570) / 4];
    string16 str0;
    string16 str1;
    string16 str2;
    string16 str3;
    string16 str4;
    string16 str5;
    string16 str6;
    string16 str7;
    string16 str8;
    string16 str9;
    string16 str10;
    string16 str11;
    string16 str12;
    string16 str13;
    string16 str14;
    string16 str15;
    string16 str16;
    string16 str17;
    string16 str18;

    void Dtor();                    // @ 0x00e3dca0
};

#include <stddef.h>
template<int A,int B> struct Eq; template<int A> struct Eq<A,A>{};
#define CHK(f, o) Eq<offsetof(cBigEditorObject, f), (o)> chk_##f
CHK(sub24,0x24); CHK(r30,0x30); CHK(r38,0x38); CHK(ra8,0xa8); CHK(mapC8,0xc8); CHK(mapE4,0xe4); CHK(map100,0x100);
CHK(map11c,0x11c); CHK(map138,0x138); CHK(map154,0x154); CHK(blk170,0x170); CHK(stars184,0x184); CHK(blk198,0x198);
CHK(r1c8,0x1c8); CHK(r1d8,0x1d8); CHK(map250,0x250); CHK(r330,0x330); CHK(reg334,0x334); CHK(r348,0x348);
CHK(arrA,0x374); CHK(arrB,0x39c); CHK(o3c4,0x3c4); CHK(arrC,0x3c8); CHK(a460,0x460); CHK(a474,0x474);
CHK(ht560,0x560); CHK(str0,0x5d4); CHK(str18,0x6f4);

extern char gVt_1481eb4[], gVt_1481e98[], gVt_1481e48[], gVt_1481e44[], gVt_1481e2c[];
extern char gVt_13eb938[], gVt_13eb394[];

static inline void FreeCounted(char* p) {
    if (p) {
        if (((int*)p)[-1] != 0)
            operator_delete_arr(p);
    }
}

static inline void ReleaseAll(IRel4* (&a)[10]) {
    IRel4** p = a + 10;
    for (int n = 9; n >= 0; --n) {
        IRel4* o = *--p;
        if (o) o->Release();
    }
}

// @ 0x00e3dca0
void cBigEditorObject::Dtor() {
    vtbl0 = gVt_1481eb4;
    vtbl4 = gVt_1481e98;
    ((void**)this)[2] = gVt_1481e48;
    ((void**)this)[3] = gVt_1481e44;
    sub24.vtbl = gVt_1481e2c;

    str18.~string16();
    str17.~string16();
    str16.~string16();
    str15.~string16();
    str14.~string16();
    str13.~string16();
    str12.~string16();
    str11.~string16();
    str10.~string16();
    str9.~string16();
    str8.~string16();
    str7.~string16();
    str6.~string16();
    str5.~string16();
    str4.~string16();
    str3.~string16();
    str2.~string16();
    str1.~string16();
    str0.~string16();
    ht560.~StrHashtable();
    FreeCounted(a474);
    FreeCounted(a460);
    ReleaseAll(arrC);
    if (o3c4) o3c4->sec.Release();
    ReleaseAll(arrB);
    ReleaseAll(arrA);
    if (r34c) r34c->Release();
    if (r348) r348->Release();
    reg334.~MsgHandlerReg();
    if (r330) r330->Release();
    map250.~StrMapC();
    if (r1d8) r1d8->Release();
    if (r1d4) r1d4->Release();
    if (r1d0) r1d0->Release();
    if (r1cc) r1cc->Release();
    if (r1c8) r1c8->Release();
    blk198.Dtor();
    stars184.Dtor();
    blk170.Dtor();
    map154.~StrMapC();
    map138.~StrMapC();
    map11c.~StrMapB();
    map100.~StrMapB();
    mapE4.~StrMapB();
    mapC8.~StrMapA();
    if (ra8) ra8->Release();
    if (r38[15]) r38[15]->Release();
    if (r38[14]) r38[14]->Release();
    if (r38[13]) r38[13]->Release();
    if (r38[12]) r38[12]->Release();
    if (r38[11]) r38[11]->Release();
    if (r38[10]) r38[10]->Release();
    if (r38[9]) r38[9]->Release();
    if (r38[8]) r38[8]->Release();
    if (r38[7]) r38[7]->Release();
    if (r38[6]) r38[6]->Release();
    if (r38[5]) r38[5]->Release();
    if (r38[4]) r38[4]->Release();
    if (r38[3]) r38[3]->Release();
    if (r38[2]) r38[2]->Release();
    if (r38[1]) r38[1]->Release();
    if (r38[0]) r38[0]->Release();
    if (r34) r34->Release();
    if (r30) r30->Release();
    sub24.Dtor();
    gonzago.Dtor();
    vtbl4 = gVt_13eb938;
    vtbl0 = gVt_13eb394;
}
