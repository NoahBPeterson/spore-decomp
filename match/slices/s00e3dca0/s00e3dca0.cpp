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

// A ResourceMan key (three dwords) and a SpVector of them.
struct KeyTriple {
    uint32_t mInstance;             // 0x00
    uint32_t mType;                 // 0x04
    uint32_t mGroup;                // 0x08
};

// Eastl-style wide string header (begin/end/capacity sentinels).
struct WStr {
    const char16* mpBegin;          // 0x00
    const char16* mpEnd;            // 0x04
    const char16* mpCap;            // 0x08
};

struct KeyVec {
    KeyTriple* mpBegin;             // 0x00
    KeyTriple* mpEnd;               // 0x04
    KeyTriple* mpCapacity;          // 0x08
    void Clear();                   // 0x0050f740 do_copy(mpBegin, mpEnd)
    void PushBack(KeyTriple& k);    // 0x004e3e10 DoInsertKey on growth
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
    uint32_t v1dc;                  // 0x1dc  asset-key triple loaded by PrepareBuildingMenu
    uint32_t v1e0;                  // 0x1e0
    uint32_t v1e4;                  // 0x1e4
    uint32_t pad1e8[(0x250 - 0x1e8) / 4]; // 0x1e8 .. 0x24f
    StrMapC map250;                 // 0x250
    uint32_t pad26c[(0x330 - 0x26c) / 4];
    IRel4* r330;                    // 0x330
    MsgHandlerReg reg334;           // 0x334
    IRel8* r348; IRel8* r34c;       // 0x348, 0x34c
    uint32_t pad350[(0x370 - 0x350) / 4];
    uint8_t  mb370;                 // 0x370  space-trading panel active
    uint8_t  pad371[3];
    IRel4* arrA[10];                // 0x374
    IRel4* arrB[10];                // 0x39c
    Obj3c4* o3c4;                   // 0x3c4
    IRel4* arrC[10];                // 0x3c8
    uint32_t mn3f0;                 // 0x3f0  cleared on activation
    uint32_t pad3f4[(0x45c - 0x3f4) / 4];
    int32_t  mn45c;                 // 0x45c  active window id (-1 = none)
    KeyVec   vec460;                // 0x460
    uint32_t pad46c[2];             // 0x46c
    KeyVec   vec474;                // 0x474
    uint32_t pad480[2];             // 0x480
    uint32_t mn488;                 // 0x488  attempt budget
    uint8_t  mb48c;                 // 0x48c
    uint8_t  pad48d[3];
    uint32_t pad490[(0x560 - 0x490) / 4];
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
    void Activate(char bOn, const void* pKey, char bFlag);          // @ 0x00e3e350
    void PrepareBuildingMenu();                                      // @ 0x00e3e7f0
    void RandomKey(KeyTriple* out);                                  // @ 0x00e3ea70
};

// Descending-key ordered map used by 00e3ec20.  The map object begins at the
// sentinel node (offset 0 of the map = node.left); the root lives in the
// sentinel's parent slot (+8), i.e. +0xc when the node base is at +0.
struct MapNode {
    MapNode*  mpLeft;    // +0x00
    MapNode*  mpRight;   // +0x04
    MapNode*  mpParent;  // +0x08
    uint32_t  mColor;    // +0x0c
    int32_t   mKey;      // +0x10
    KeyTriple mValue;    // +0x14
};

// Map view: 00e3ec20's `this` points 4 bytes before the sentinel node, so the
// sentinel starts at +4 and the root (sentinel.mpParent) reads as +0xc.
struct KeyMap {
    uint32_t mpHead;      // +0x00
    MapNode  mAnchor;     // +0x04  (root stored in mAnchor.mpParent)

    KeyTriple* FindOrInsertKey(const KeyTriple* pKey);  // @ 0x00e3ec20
};

#include <stddef.h>
template<int A,int B> struct Eq; template<int A> struct Eq<A,A>{};
#define CHK(f, o) Eq<offsetof(cBigEditorObject, f), (o)> chk_##f
CHK(sub24,0x24); CHK(r30,0x30); CHK(r38,0x38); CHK(ra8,0xa8); CHK(mapC8,0xc8); CHK(mapE4,0xe4); CHK(map100,0x100);
CHK(map11c,0x11c); CHK(map138,0x138); CHK(map154,0x154); CHK(blk170,0x170); CHK(stars184,0x184); CHK(blk198,0x198);
CHK(r1c8,0x1c8); CHK(r1d8,0x1d8); CHK(map250,0x250); CHK(r330,0x330); CHK(reg334,0x334); CHK(r348,0x348);
CHK(arrA,0x374); CHK(arrB,0x39c); CHK(o3c4,0x3c4); CHK(arrC,0x3c8); CHK(mn45c,0x45c); CHK(vec460,0x460);
CHK(vec474,0x474); CHK(mn488,0x488); CHK(mb48c,0x48c); CHK(ht560,0x560); CHK(str0,0x5d4); CHK(str18,0x6f4);;

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
    FreeCounted((char*)vec474.mpBegin);
    FreeCounted((char*)vec460.mpBegin);
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

// ============================================================================================
// SP::cSPUITimeline / cCityInputStrategy helpers (migrated gold7 slice s00e3dca0).
// ============================================================================================

// A UI window reached through cSPUILayout::FindWindowByID.  The vtable slots used here are the
// two generic setters: slot 0x7c takes two ints, slot 0x80 takes a wide string.
struct IWindow {
    virtual void v00();   // +0x00
    virtual void v04();   // +0x04
    virtual void v08();   // +0x08
    virtual void v0c();   // +0x0c
    virtual void v10();   // +0x10
    virtual void v14();   // +0x14
    virtual void v18();   // +0x18
    virtual void v1c();   // +0x1c
    virtual void v20();   // +0x20
    virtual void v24();   // +0x24
    virtual void v28();   // +0x28
    virtual void v2c();   // +0x2c
    virtual void v30();   // +0x30
    virtual void v34();   // +0x34
    virtual void v38();   // +0x38
    virtual void v3c();   // +0x3c
    virtual void v40();   // +0x40
    virtual void v44();   // +0x44
    virtual void v48();   // +0x48
    virtual void v4c();   // +0x4c
    virtual void v50();   // +0x50
    virtual void v54();   // +0x54
    virtual void v58();   // +0x58
    virtual void v5c();   // +0x5c
    virtual void v60();   // +0x60
    virtual void v64();   // +0x64
    virtual void v68();   // +0x68
    virtual void v6c();   // +0x6c
    virtual void v70();   // +0x70
    virtual void v74();   // +0x74
    virtual void v78();   // +0x78
    virtual void SetVis(int a, int b);  // +0x7c
    virtual void SetText(const void* pText); // +0x80
};

// cSPUILayout (only the two statics this slice uses).
struct cSPUILayout {
    static IWindow* FindWindowByID(cSPUILayout* pThis, uint32_t id, int recursive); // 0x008105b0
    static void     SetVisibility(cSPUILayout* pThis, int bVisible);                // 0x00810590
};

// 8 dummy vtable slots covering +0x00..+0x1c (indices 0..7).
#define SP_8SLOTS virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); \
                  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c()

// arrC element: generic release at +0x04 and a re-query slot at +0x20.
struct IArrC {
    virtual void v00();       // +0x00
    virtual void Release();   // +0x04
    virtual void v08();       // +0x08
    virtual void v0c();       // +0x0c
    virtual void v10();       // +0x10
    virtual void v14();       // +0x14
    virtual void v18();       // +0x18
    virtual void v1c();       // +0x1c
    virtual void v20();       // +0x20
};

// Object exposing a single accessor at +0x20 (used by the asset-name pipeline).
struct ISlot20 {
    SP_8SLOTS;
    virtual void* v20();      // +0x20
};

// Object exposing a name-setter at +0x34.
struct ISlot34 {
    SP_8SLOTS;
    virtual void v20();             // +0x20
    virtual void v24();             // +0x24
    virtual void v28();             // +0x28
    virtual void v2c();             // +0x2c
    virtual void v30();             // +0x30
    virtual void v34(const char16*, int); // +0x34
};

// Change-notification interface; the slot used here sits at +0x104.
struct IRef104 {
    SP_8SLOTS;
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100();                       // +0x100
    virtual void Notify(void* pBase);          // +0x104
};

// The window-owner object passed around as an IWindow-ish handle with a Release at +4.
struct IRefCounted {
    virtual void     Obj0();        // +0x00
    virtual void     Release();     // +0x04
    virtual void*    Obj8();        // +0x08
    virtual void*    ObjC(void*);   // +0x0c
};

// The asset resource handle returned by the resource manager (metadata-like).
struct AssetMeta {
    virtual void      Null0();       // +0x00
    virtual void      Release();     // +0x04
    virtual void      Obj8();        // +0x08
    virtual AssetMeta* ObjC(uint32_t); // +0x0c
    const char16* GetName();         // 0x00414e10
    const char16* GetSummary();      // 0x005508c0
};

struct IKernel; // opaque

// Message server singleton + its vtable slot 0x14 (Post).
struct IMessageServer {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void Post(uint32_t msg, void* p1, int p2);  // +0x14
};

// A tiny 3-dword triple (e.g. an index/handle triple).
struct Triple {
    uint32_t a; // 0x00
    uint32_t b; // 0x04
    uint32_t c; // 0x08
};

// A 0x18-byte value built from two triples and passed by value.
struct SixDwords {
    uint32_t a; uint32_t b; uint32_t c;
    uint32_t d; uint32_t e; uint32_t f;
};

// ---------------------------------------------------------------- externs (retail addresses)
extern "C" void  __cdecl FUN_00685520(int flag);                                     // 0x00685520
extern "C" int   __cdecl IsWorldLayoutFlagSet(int flag);                             // 0x00685520
extern "C" void* __cdecl GetGameModeHash();                                          // 0x00e36c80
extern "C" void* __cdecl GetPlayerEmpire();                                          // 0x01021300
extern "C" void* __cdecl ResourceMan_GetManager();                                   // 0x0067dcd0
extern "C" void* __cdecl MsgServer();                                                // 0x0067dcc0
extern "C" void* __cdecl FUN_0067de40();                                             // 0x0067de40
extern "C" void* __cdecl FUN_0067cab0();                                             // 0x0067cab0
extern "C" void* __cdecl GameTimeManager();                                          // 0x00b3d380
extern "C" void* __stdcall FUN_0067de90(int n, SixDwords v);                         // 0x0067de90
extern "C" void  __cdecl FUN_00e3a6b0(void* pWindow, void* pKey);                    // 0x00e3a6b0
extern "C" void  __cdecl FUN_00e3b0f0(void* pThis);                                  // 0x00e3b0f0
extern "C" void  __cdecl FUN_00e3b180(void* pThis);                                  // 0x00e3b180
struct Builder { void Init(); };                                                     // 0x00e3d9e0 __thiscall
extern "C" void* __cdecl FUN_00e3da30(void* pOut, void* pHint, void* pKey, void* pPair); // 0x00e3da30
extern "C" void  __cdecl FUN_00b6ec50(void* pOut, uint32_t group, int n, void* pStr); // 0x00b6ec50
extern "C" void* __cdecl WStr_Ctor(void* pOut, const char16* pSrc);                  // 0x0041df50
extern "C" void  __cdecl WString_DeallocateSelf(void* pStr);                         // 0x00933960
extern "C" void* __cdecl SpVector_erase(void* first, void* last);                    // 0x0050f740
extern "C" void* __cdecl RandomUint32Uniform(void* self, uint32_t n);                // 0x00a68fb0
struct RandomLCG { uint32_t RandomUint32Uniform(uint32_t n); };                      // 0x00a68fb0 __thiscall
extern "C" void  __cdecl SpVector_DoInsertKey(KeyTriple* pos, KeyTriple* value);      // 0x004e3e10
extern "C" void* __cdecl SPUI_BeginModal();                                          // 0x008099a0
extern "C" void* __cdecl SPUI_EndModal(void* w, int a, int b);                       // 0x00809c50
extern "C" void  __cdecl UI_ShowX(void* pThis);                                      // 0x00801360
extern "C" void  __cdecl UI_HideX(void* pThis);                                      // 0x00801380
extern "C" void* __cdecl eastl_wstring_appendAssign(void* pStr, const char16* pSrc); // 0x005c3d90
extern "C" void  __cdecl cString_Ctor(void* pStr);                                   // 0x006b5060
extern "C" const char16* __cdecl cString_GetText(void* pStr);                        // 0x006b55c0
extern "C" void  __cdecl cString_Dtor(void* pStr);                                   // 0x006b5240
extern "C" void* __cdecl GetCities(void* pCivData);                                  // 0x005c65e0

extern RandomLCG gRandomGlobal;                                                      // 0x01601760
extern void* gKeySentinel654c10;                                                     // 0x01654c10
extern char16 gEmptyString16[];                                                      // 0x01667bac

// Resource-name globals used to build the tradeship key.
extern uint32_t gKeyA_15accc8;   // 0x015accc8
extern uint32_t gKeyA_15acccc;   // 0x015acccc
extern uint32_t gKeyA_15accd0;   // 0x015accd0
extern uint32_t gKeyB_15accd4;   // 0x015accd4
extern uint32_t gKeyB_15accd8;   // 0x015accd8
extern uint32_t gKeyB_15accdc;   // 0x015accdc
extern uint32_t gKeyC_15acce0;   // 0x015acce0
extern uint32_t gKeyC_15acce4;   // 0x015acce4
extern uint32_t gKeyC_15acce8;   // 0x015acce8

void KeyVec::Clear() {
    SpVector_erase(mpBegin, mpEnd);
}

void KeyVec::PushBack(KeyTriple& k) {
    if (mpEnd != mpCapacity) {
        KeyTriple* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            *p = k;
    } else {
        SpVector_DoInsertKey(mpEnd, &k);
    }
}


// @ 0x00e3ea00  forward a pair of triples into a 0xc-stride builder then its initialiser
void ForwardTriples(Triple* p1, Triple* p2)
{
    SixDwords v;
    v.a = p1->a; v.b = p1->b; v.c = p1->c;
    v.d = p2->a; v.e = p2->b; v.f = p2->c;

    Builder* b = (Builder*)FUN_0067de90(0xc, v);
    b->Init();
}

// @ 0x00e3ea70  pick a random key from vec460 that has not already been tried (vec474), bounded by mn488
void cBigEditorObject::RandomKey(KeyTriple* out)
{
    int count = (int)((char*)vec460.mpEnd - (char*)vec460.mpBegin) / 12;
    bool recorded = false;
    uint32_t tries = 0;

    if (count == 0) {
        out->mInstance = 0;
        out->mType     = 0;
        out->mGroup    = 0;
        return;
    }

    for (;;) {
        count = (int)((char*)vec460.mpEnd - (char*)vec460.mpBegin) / 12;
        uint32_t idx = gRandomGlobal.RandomUint32Uniform((uint32_t)count);

        KeyTriple* e = vec460.mpBegin + idx;
        KeyTriple v;
        v.mInstance = e->mInstance;
        v.mType     = e->mType;
        v.mGroup    = e->mGroup;

        count = (int)((char*)vec460.mpEnd - (char*)vec460.mpBegin) / 12;
        if ((uint32_t)count < mn488) {
            out->mInstance = v.mInstance;
            out->mType     = v.mType;
            out->mGroup    = v.mGroup;
            return;
        }

        KeyTriple* p = vec474.mpBegin;
        KeyTriple* pEnd = vec474.mpEnd;
        while (p != pEnd &&
               !(p->mInstance == v.mInstance && p->mType == v.mType && p->mGroup == v.mGroup))
            ++p;

        if (p == vec474.mpEnd) {
            out->mInstance = v.mInstance;
            out->mType     = v.mType;
            out->mGroup    = v.mGroup;
            vec474.PushBack(*e);
            recorded = true;
        }

        ++tries;
        if (tries > mn488) {
            out->mInstance = v.mInstance;
            out->mType     = v.mType;
            out->mGroup    = v.mGroup;
            return;
        }
        if (recorded)
            return;
    }
}

// @ 0x00e3ec20  map lookup-or-insert over the rbtree keyed at node+0x10 (value at node+0x14)
KeyTriple* KeyMap::FindOrInsertKey(const KeyTriple* pKey)
{
    MapNode* pAnchor = &mAnchor;
    MapNode* pParent = &mAnchor;
    MapNode* pNode = mAnchor.mpParent;      // root
    int32_t  key = (int32_t)pKey->mInstance;

    while (pNode) {
        if ((int32_t)pNode->mKey < key) {
            pNode = pNode->mpLeft;          // tree is ordered descending
        } else {
            pParent = pNode;
            pNode = pNode->mpRight;
        }
    }

    if (pParent != pAnchor && key >= (int32_t)pParent->mKey)
        return &pParent->mValue;

    // Insert: marshal a pair<hint, key> and hand it to the rbtree insert.
    struct PairIn  { MapNode* mpHint; int32_t mKey; };
    struct PairOut { MapNode* mpNode; uint8_t mInserted; };
    PairIn  in;
    PairOut out;
    in.mpHint = pParent;
    in.mKey   = key;
    out.mpNode = 0;
    out.mInserted = 0;
    FUN_00e3da30(&out, pParent, &in.mKey, &in);
    return &out.mpNode->mValue;
}

// ---------------------------------------------------------------- additional externs
extern "C" void  __cdecl FUN_00e3abf0(void* pThis, const void* pKey);   // 0x00e3abf0 UpdateTransition
extern "C" void  __cdecl IncPauseGate(void* pMgr, uint32_t gate);       // 0x00b32220
extern "C" void  __cdecl DecPauseGate(void* pMgr, uint32_t gate);       // 0x00b32250

// Resource manager (singleton returned by 0x67dcd0).  Slot +0x0c is a
// find-by-asset-key returning a bool and writing the found record out.
struct IAssetKey { uint32_t mInstance; uint32_t mType; uint32_t mGroup; };

struct IResourceManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual char Find(const IAssetKey* pKey, void** ppOut, int a, int b, int c, int d); // +0x0c
};

// Asset metadata (Pollen).  Slot +0x0c re-resolves, GetName at 0x414e10.
struct IAssetRecord {
    virtual void  v00();                 // +0x00
    virtual void  Release();             // +0x04
    virtual void  v08();                 // +0x08
    virtual void* ObjC(uint32_t group);  // +0x0c
    const char16* GetName();             // 0x00414e10
    const char16* GetSummary();          // 0x005508c0
};

// A stack-resident cString-like object (opaque blob, ctor/dtor/getText).
struct CStr16 { uint32_t mBlob[6]; };

extern "C" void  __cdecl QualifyNameWithGroup(void* pOut, void* pIn, int n, uint32_t grp, void* pDst); // 0x00b6ec50

// @ 0x00e3e7f0  build the menu title string for the current city/asset
void cBigEditorObject::PrepareBuildingMenu()
{
    IWindow* pWin = cSPUILayout::FindWindowByID((cSPUILayout*)r30, 0xd54aa976, 1);
    if (!pWin)
        return;
    if (!v1dc)
        return;

    WStr name;
    name.mpBegin = gEmptyString16;
    name.mpEnd   = gEmptyString16;
    name.mpCap   = gEmptyString16 + 1;

    if ((uintptr_t)GetGameModeHash() == 0x2db6dad3u) {
        void* pEmpire = GetPlayerEmpire();
        if (pEmpire) {
            uint32_t* pCities = (uint32_t*)GetCities(pEmpire);
            eastl_wstring_appendAssign(&name, (const char16*)*pCities);
        }
        goto setText;
    }

    {
        IAssetKey ak;
        ak.mInstance = v1dc;
        ak.mType     = 0x30bdee3;
        ak.mGroup    = v1e4;
        void* hRes = 0;
        IResourceManager* pMan = (IResourceManager*)ResourceMan_GetManager();
        if (hRes) {
            void* pOld = hRes;
            hRes = 0;
            ((IRefCounted*)pOld)->Release();
        }
        if (pMan->Find(&ak, &hRes, 0, 0, 0, 0)) {
            CStr16 cstr;
            cString_Ctor(&cstr);
            IAssetRecord* pRec = hRes
                ? (IAssetRecord*)((IRefCounted*)hRes)->ObjC((void*)0x30bdee3) : 0;
            uintptr_t mode = (uintptr_t)GetGameModeHash();
            if (mode == 0xbeb528cbu) {                 // -0x414ad735
                char16 nm[4];
                const char16* pName = pRec->GetName();
                WStr_Ctor(nm, pName);
                QualifyNameWithGroup(&cstr, nm, 0xd, 0x53dbcf1, 0);
                WString_DeallocateSelf(nm);
                const char16* t = cString_GetText(&cstr);
                eastl_wstring_appendAssign(&name, t);
            } else if (mode == 0xa426730bu || mode == 0xad56080cu) {
                eastl_wstring_appendAssign(&name, pRec->GetName());
            } else if (mode == 0xf71fa311u) {          // 0xf71fa311 == -0x8e05cef
                char16 nm[4];
                const char16* pName = pRec->GetName();
                WStr_Ctor(nm, pName);
                QualifyNameWithGroup(&cstr, nm, 0xe, 0x53dbcf1, 0);
                WString_DeallocateSelf(nm);
                const char16* t = cString_GetText(&cstr);
                eastl_wstring_appendAssign(&name, t);
            }
            cString_Dtor(&cstr);
        }
        if (hRes) {
            void* pOld = hRes;
            ((IRefCounted*)pOld)->Release();
        }
    }

setText:
    pWin->SetText(name.mpBegin);
    if ((int)(((const char*)name.mpEnd - (const char*)name.mpCap) & 0xfffffffeu) > 2 && name.mpCap)
        operator_delete_arr((void*)name.mpCap);
}

// @ 0x00e3e350  turn the space-trading panel on/off (arg1=on, arg2=key, arg3=quiet)
void cBigEditorObject::Activate(char bOn, const void* pKey, char bFlag)
{
    if (mb370 == 0 && bOn == 0 && bFlag != 0)
        return;

    IWindow* pWin = 0;
    cSPUILayout* pLayout = 0;

    if (IsWorldLayoutFlagSet(2)) {
        pWin = cSPUILayout::FindWindowByID((cSPUILayout*)r34c, 0x762350f, 1);
        if (pKey == (const void*)&gKeySentinel654c10) {
            pLayout = (cSPUILayout*)r34c;
            mn3f0 = 0;

            IAssetKey ak;
            ak.mInstance = gKeyA_15accc8 ? gKeyA_15accc8 : gKeyB_15accd4;
            ak.mType     = 0x30bdee3;
            ak.mGroup    = gKeyA_15accc8 ? gKeyA_15accd0 : gKeyB_15accdc;

            void* hRes = 0;
            IResourceManager* pMan = (IResourceManager*)ResourceMan_GetManager();
            if (hRes) { void* p = hRes; hRes = 0; ((AssetMeta*)p)->Release(); }
            pMan->Find(&ak, &hRes, 0, 0, 0, 0);

            AssetMeta* pRec = hRes
                ? (AssetMeta*)((AssetMeta*)hRes)->ObjC(0x30bdee3) : 0;
            if (pRec) {
                pRec->Null0();
                const char16* pName = pRec->GetName();
                ISlot20* pL10 = (ISlot20*)FUN_0067de40();
                ISlot34* pL14 = (ISlot34*)pL10->v20();
                pL14->v34(pName, 0);
                IWindow* pSum = cSPUILayout::FindWindowByID((cSPUILayout*)r34c, 0x76236bc, 1);
                if (pSum)
                    pSum->SetText(pRec->GetSummary());
            }
            if (pWin)
                pWin->SetVis(1, 1);

            IAssetKey kBe;
            kBe.mInstance = gKeyC_15acce0;
            kBe.mType     = 0x2f7d0004;
            kBe.mGroup    = gKeyC_15acce8;
            FUN_00e3a6b0(cSPUILayout::FindWindowByID((cSPUILayout*)r34c, 0x76236be, 1), &kBe);

            IAssetKey kBd;
            kBd.mInstance = gKeyA_15accc8;
            kBd.mType     = 0x2f7d0004;
            kBd.mGroup    = gKeyA_15accd0;
            FUN_00e3a6b0(cSPUILayout::FindWindowByID((cSPUILayout*)r34c, 0x76236bd, 1), &kBd);

            if (pRec) pRec->Release();
            if (hRes) ((AssetMeta*)hRes)->Release();
        } else {
            pLayout = (cSPUILayout*)r348;
            if (pWin)
                pWin->SetVis(1, 0);
        }
    } else {
        pLayout = (cSPUILayout*)r348;
    }

    mn45c = (int32_t)(intptr_t)pKey;
    vec460.Clear();
    vec474.Clear();

    for (int i = 0; i < 10; ++i) {
        IArrC* pc = (IArrC*)arrC[i];
        if (pc && bOn == 0) {
            pc->v20();
            if (arrC[i]) {
                arrC[i] = 0;
                ((IArrC*)arrC[i])->Release();
            }
        }
        if (arrA[i])
            ((IWindow*)arrA[i])->SetVis(1, 0);
    }

    IWindow* wT = cSPUILayout::FindWindowByID((cSPUILayout*)r348, 0x64db520, 1);
    if (wT)
        wT->SetVis(1, 0);
    if (IsWorldLayoutFlagSet(2)) {
        IWindow* wT2 = cSPUILayout::FindWindowByID((cSPUILayout*)r34c, 0x64db520, 1);
        if (wT2)
            wT2->SetVis(1, 0);
    }

    mb370 = (uint8_t)bOn;

    if (bOn) {
        cSPUILayout::SetVisibility(pLayout, 1);
        FUN_00e3abf0(this, pKey);
        if (mb48c)
            FUN_00e3b0f0(this);
        IMessageServer* pMsg = (IMessageServer*)MsgServer();
        pMsg->Post(0x490a868, (void*)&pKey, 0);
        if (bFlag) {
            void* pGT = GameTimeManager();
            IncPauseGate(pGT, 0x4bf38a7);
        }
    } else {
        if (IsWorldLayoutFlagSet(2))
            cSPUILayout::SetVisibility((cSPUILayout*)r34c, 0);
        cSPUILayout::SetVisibility((cSPUILayout*)r348, 0);
        if (mb48c)
            FUN_00e3b180(this);
        if (bFlag) {
            void* pGT = GameTimeManager();
            DecPauseGate(pGT, 0x4bf38a7);
        }
        IMessageServer* pMsg = (IMessageServer*)MsgServer();
        pMsg->Post(0x47d2b68, (void*)&pKey, 0);
    }

    {
        IWindow* wM = cSPUILayout::FindWindowByID(pLayout, 0xffffffff, 1);
        if (wM) {
            if (bOn)
                SPUI_BeginModal();
            else
                SPUI_EndModal(wM, 0, 0);
        }
    }

    if (mn45c != -1) {
        void* pCab = FUN_0067cab0();
        if (bOn)
            UI_ShowX(pCab);
        else
            UI_HideX(pCab);
    }

    void* pBase = (void*)&vtbl4;
    if (r38[1]) ((IRef104*)r38[1])->Notify(pBase);
    if (r38[5]) ((IRef104*)r38[5])->Notify(pBase);
    if (r38[7]) ((IRef104*)r38[7])->Notify(pBase);
    if (r38[0]) ((IRef104*)r38[0])->Notify(pBase);
}
