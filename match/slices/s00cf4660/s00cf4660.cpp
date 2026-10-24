// Decompiled from SporeApp.exe (gold6 batch, worker 33).
// Slice s00cf4660: Simulator::cCityInputStrategy construction, reset, init,
// destruction, and the species-scan messaging callback.

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// free functions / runtime helpers
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_00b3d230();
extern "C" void* __cdecl GameInputManager();          // 0x00b3d250
extern "C" void* __cdecl GetGameTerrainCursor();      // 0x00b30d70
extern "C" void* __cdecl MessageServer();             // 0x0067dcc0
extern "C" void* __cdecl FUN_01021260();              // active planet
extern "C" void* __cdecl NounManager();               // 0x00b3d300
extern "C" void* __cdecl op_new(u32 size, const char* name,
                                int a, int b, int c, int d);   // 0x00f473a0
extern "C" void  __cdecl op_del_array(void* p);                // 0x00f47380
extern "C" void  __cdecl RemoveHandler(void* h, void* a, void* b,
                                       void* c, void* d);       // 0x00571db0
extern "C" void* __cdecl FUN_00ba5e10(void* o, int v);
extern "C" void* __cdecl FUN_00ba57a0(void* o, int v);
extern "C" void* __cdecl FUN_00ba58e0(void* o, int v);
extern "C" void* __cdecl FUN_00b3d4f0(void* o);

// ---------------------------------------------------------------------------
// thiscall helper objects (definitions live in other translation units)
// ---------------------------------------------------------------------------
struct TreeOps {
    void ResetA(u32 alloc);      // 0x00b1b830
    void ResetB(u32 alloc);      // 0x00e4b990
};

struct ArgCmd {
    void Ctor(void* arg);            // 0x00b198d0
    void SetName(const char* name);  // 0x00b1b410
    void Finish();                   // 0x00b19b60
    void Destroy();                  // 0x0083c750
    u8   mPad[0x14];
};

struct Stopwatch {
    void Ctor(int a, int b);         // 0x0093a560
    u8   mPad[0x18];
};

struct PieMenu {
    PieMenu* Ctor();                 // 0x00b7d170
};

struct CommEditor {
    CommEditor* Ctor();                          // 0x00d0d200
    void Init(u32 a, u32 b, u32 c, u32 d);       // 0x00d0a760
};

struct SmallObj {
    SmallObj* Ctor();                // 0x00e34f40
};

struct PieMenuVec {
    void** mpBegin;                  // +0x00
    void** mpEnd;                    // +0x04
    void DestroyRange(void** a, void** b);  // 0x00b7cf10
};

struct AutoRefVector {
    u32  mpBegin;                    // +0x00
    u32  mpEnd;                      // +0x04
    u32  mpCap;                      // +0x08
    u8   mPad[8];                    // +0x0c
    void Dtor();                     // 0x00ae6970
};

// Pair of intrusive trees that live at +0x04 and +0x84 of the strategy.
struct TreePairLayout {
    u32 mn00;                        // +0x00 tree A header
    u32 mn04;                        // +0x04 self pointer
    u32 mn08;                        // +0x08
    u32 mn0C;                        // +0x0c element count
    union { u32 mn10; u8 mb10; };    // +0x10
    u32 mn14;                        // +0x14
    u32 mn18;                        // +0x18
    u32 mn1C;                        // +0x1c tree B header
    u32 mn20;                        // +0x20 self pointer
    u32 mn24;                        // +0x24
    u32 mn28;                        // +0x28 element count
    union { u32 mn2C; u8 mb2C; };    // +0x2c
    u32 mn30;                        // +0x30
};

struct ScanObj {
    u32* FUN_c0bc00();               // 0x00c0bc00
};

struct Planet {
    bool SetSpeciesAsScanned(u32* sp);   // 0x00c73ea0
    bool IsScanned(u32* sp);             // 0x00c73f10
    bool Known(u32* key);                // 0x00c744e0
};

struct StarRec {
    void* GetCommContext();          // 0x00ce6950
};

// Object handed back for the 0x629baec scan: the tribe link lives at +0x10c.
struct TribeHolder {
    u8    mPad00[0x10c];
    void* mpTribe;                   // +0x10c
};

struct NounMgr {
    void* GetTerrain();              // 0x00f67d90
};

struct Sphere {
    void* GetEntry(u32* commCtx);    // 0x00ba4e60
};

struct Entry8  { u8* Find(u32* sp); };   // 0x00ba4520
struct Entry20 { u8* Find(u32* sp); };   // 0x00ba4520
struct Entry38 { u8* Find(u32* sp); };   // 0x00ba4520
struct Entry68 { u8* Find(u32* key); };  // 0x00c735e0

struct Edition {
    int GetFileCount();              // 0x008e7f80
};

struct ObjA {
    void* FUN_c9d9e0();              // 0x00c9d9e0
};

struct ObjB {
    void* GetTribe();                // 0x00c22f50
};

struct Obj9 {
    void Do();                       // 0x00e30d20
};

// ---------------------------------------------------------------------------
// Simulator::cCityInputStrategy
// ---------------------------------------------------------------------------
struct CityInputStrategy {
    void* mpVtbl;            // +0x000
    u32   mTreeBase04;       // +0x004
    u32   mn08;              // +0x008
    u32   mn0C;              // +0x00c
    u32   mn10;              // +0x010
    union { u32 mn14; u8 mb14; };   // +0x014
    u32   mn18;              // +0x018
    u32   mn1C;              // +0x01c
    u32   mTreeBase20;       // +0x020
    u32   mn24;              // +0x024
    u32   mn28;              // +0x028
    u32   mn2C;              // +0x02c
    union { u32 mn30; u8 mb30; };   // +0x030
    u32   mn34;              // +0x034
    u32   mn38;              // +0x038
    void* mpVtbl3C;          // +0x03c
    void* mpVtbl40;          // +0x040
    u32   mn44;              // +0x044
    u8    mb48;              // +0x048
    u8    mPad49[3];         // +0x049
    u32   mn4C;              // +0x04c
    void* mp50;              // +0x050
    void* mp54;              // +0x054
    void* mp58;              // +0x058
    void* mp5C;              // +0x05c
    void* mp60;              // +0x060
    void* mp64;              // +0x064
    void* mp68;              // +0x068
    void* mp6C;              // +0x06c
    void* mp70;              // +0x070
    u32*  mp74;              // +0x074
    u32   mn78;              // +0x078
    u32   mn7C;              // +0x07c
    void* mp80;              // +0x080
    u32   mTreeBase84;       // +0x084
    u32   mn88;              // +0x088
    u32   mn8C;              // +0x08c
    u32   mn90;              // +0x090
    union { u32 mn94; u8 mb94; };   // +0x094
    u32   mn98;              // +0x098
    u32   mn9C;              // +0x09c
    u32   mTreeBaseA0;       // +0x0a0
    u32   mnA4;              // +0x0a4
    u32   mnA8;              // +0x0a8
    u32   mnAC;              // +0x0ac
    union { u32 mnB0; u8 mbB0; };   // +0x0b0
    u32   mnB4;              // +0x0b4
    u8    mPadB8[8];         // +0x0b8
    Stopwatch mStopwatch;    // +0x0c0
    void* mpD8;              // +0x0d8
    u8    mbDC;              // +0x0dc
    u8    mPadDD[3];         // +0x0dd
    u32   mnE0;              // +0x0e0
    void* mpE4;              // +0x0e4
    AutoRefVector mE8Vector; // +0x0e8
    u32   mnFC;              // +0x0fc
    u32   mn100;             // +0x100
    u32   mn104;             // +0x104
    u32   mn108;             // +0x108
    u32   mn10C;             // +0x10c
    u32   mn110;             // +0x110
    u32   mn114;             // +0x114
    u32   mn118;             // +0x118
    u32   mn11C;             // +0x11c
    u32   mn120;             // +0x120
    u32   mn124;             // +0x124
    u32   mn128;             // +0x128
    u32   mn12C;             // +0x12c
    u32   mn130;             // +0x130
    u8    mb134;             // +0x134
    u8    mb135;             // +0x135
    u8    mb136;             // +0x136
    u8    mPad137;           // +0x137
    u32   mn138;             // +0x138
    u32   mn13C;             // +0x13c
    u32   mn140;             // +0x140

    CityInputStrategy* Ctor(u32 param);   // 0x00cf4ca0
    void Reset(u32 mode);                 // 0x00cf4c00
    void Init();                          // 0x00cf4660
    void Destroy();                       // 0x00cf4ea0
};

// ===========================================================================
// 0x00cf4ca0 -- Simulator::cCityInputStrategy::cCityInputStrategy
// ===========================================================================
// @ 0x00cf4ca0
CityInputStrategy* CityInputStrategy::Ctor(u32 param)
{
    mn0C = 0;
    mn10 = 0;
    mn14 = 0;
    mn10 = 0;
    mb14 = 0;
    mn18 = 0;
    mn08 = (u32)((char*)this + 8);
    mn0C = (u32)((char*)this + 8);
    mn28 = 0;
    mn2C = 0;
    mn30 = 0;
    mn2C = 0;
    mb30 = 0;
    mn34 = 0;
    mn24 = (u32)((char*)this + 0x24);
    mn28 = (u32)((char*)this + 0x24);
    mpVtbl3C = (void*)0x13eb384;
    mpVtbl40 = (void*)0x13ec458;
    mn44 = 0;
    mn4C = param;
    mpVtbl = (void*)0x14787bc;
    mpVtbl3C = (void*)0x14787ac;
    mpVtbl40 = (void*)0x147879c;
    mb48 = 0;
    mp50 = 0;
    mp54 = 0;
    mp58 = 0;
    mp5C = 0;
    mp60 = 0;
    mp64 = 0;
    mp68 = 0;
    mp6C = 0;
    mp70 = 0;
    mp74 = 0;
    mn78 = 0;
    mn7C = 0;
    mp80 = 0;
    mn8C = 0;
    mn90 = 0;
    mn94 = 0;
    mn88 = (u32)((char*)this + 0x88);
    mn8C = (u32)((char*)this + 0x88);
    mn90 = 0;
    mb94 = 0;
    mn98 = 0;
    mnA8 = 0;
    mnAC = 0;
    mnB0 = 0;
    mnA4 = (u32)((char*)this + 0xA4);
    mnA8 = (u32)((char*)this + 0xA4);
    mnAC = 0;
    mbB0 = 0;
    mnB4 = 0;
    mStopwatch.Ctor(4, 0);
    mpD8 = 0;
    mbDC = 0;
    mnE0 = 0;

    SmallObj* obj = (SmallObj*)op_new(0x28, (const char*)0x13f09b4, 0, 0, 0, 0);
    if (obj != 0)
        obj = obj->Ctor();
    mpE4 = obj;
    if (obj != 0)
        ((void(__fastcall*)(void*))(*(void***)obj)[4 / 4])(obj);

    mE8Vector.mpBegin = 0;
    mE8Vector.mpEnd = 0;
    mE8Vector.mpCap = 0;
    mn100 = (u32)-1;
    mn140 = (u32)-1;
    mnFC = 0;
    mn104 = 0;
    mn108 = 0;
    mn10C = 0;
    mn110 = 0;
    mn114 = 0;
    mn118 = 0;
    mn11C = 0;
    mn120 = 0;
    mn124 = 0;
    mn128 = 0;
    mn12C = 0;
    mn130 = 0;
    mb134 = 0;
    mb135 = 0;
    mb136 = 0;
    mn13C = 0;
    mn138 = 0x1510d07;
    return this;
}

// ===========================================================================
// 0x00cf4ea0 -- Simulator::cCityInputStrategy::~cCityInputStrategy
// ===========================================================================
// @ 0x00cf4ea0
void CityInputStrategy::Destroy()
{
    mpVtbl = (void*)0x14787bc;
    mpVtbl3C = (void*)0x14787ac;
    mpVtbl40 = (void*)0x147879c;

    PieMenuVec* v = (PieMenuVec*)mp50;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp54;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp5C;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp60;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp64;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp68;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }

    void* o = mpE4;
    if (o != 0) {
        mpE4 = 0;
        ((void(__fastcall*)(void*))(*(void***)o)[8 / 4])(o);
    }
    mE8Vector.Dtor();
    o = mpE4;
    if (o != 0)
        ((void(__fastcall*)(void*))(*(void***)o)[8 / 4])(o);
    o = mpD8;
    if (o != 0)
        ((void(__fastcall*)(void*))(*(void***)o)[4 / 4])(o);

    TreePairLayout* t84 = (TreePairLayout*)&mTreeBase84;
    ((TreeOps*)&t84->mn1C)->ResetB(t84->mn28);
    ((TreeOps*)t84)->ResetA(t84->mn0C);
    o = mp80;
    if (o != 0)
        ((void(__fastcall*)(void*))(*(void***)o)[0xc / 4])(o);

    void* handler = mp6C;
    if (handler != 0) {
        mp6C = 0;
        RemoveHandler(handler, mp70, mp74, (void*)mn78, (void*)mn7C);
    }

    mpVtbl40 = (void*)0x13ec458;
    mpVtbl3C = (void*)0x13eb394;
    mpVtbl = (void*)0x14771e0;
    TreePairLayout* t = (TreePairLayout*)&mTreeBase04;
    ((TreeOps*)&t->mn1C)->ResetB(t->mn28);
    ((TreeOps*)t)->ResetA(t->mn0C);
}

// ===========================================================================
// 0x00cf4c00 -- reset the input strategy to a fresh translate/rotate mode
// ===========================================================================
// @ 0x00cf4c00
void CityInputStrategy::Reset(u32 mode)
{
    TreePairLayout* t1 = (TreePairLayout*)&mTreeBase04;
    ((TreeOps*)t1)->ResetA(t1->mn0C);
    t1->mn04 = (u32)&t1->mn04;
    t1->mn08 = (u32)&t1->mn04;
    t1->mn0C = 0;
    t1->mb10 = 0;
    t1->mn14 = 0;

    TreePairLayout* t2 = (TreePairLayout*)&mTreeBase20;
    ((TreeOps*)t2)->ResetB(t2->mn0C);
    t2->mn04 = (u32)&t2->mn04;
    t2->mn08 = (u32)&t2->mn04;
    t2->mn0C = 0;
    t2->mb10 = 0;
    t2->mn14 = 0;

    ArgCmd local;
    local.Ctor(&mTreeBase04);
    local.SetName((const char*)0x1478788);
    switch (mode) {
    case 0:
        local.SetName((const char*)0x147875c);
        break;
    case 1:
        local.SetName((const char*)0x1478774);
        break;
    default:
        local.SetName((const char*)0x147875c);
        break;
    }
    local.Finish();
    local.Destroy();
}

// ===========================================================================
// 0x00cf4660 -- Simulator::cCityInputStrategy::Init
// ===========================================================================
// @ 0x00cf4660
void CityInputStrategy::Init()
{
    if (mb48 != 0)
        return;
    mb48 = 1;

    if (mpE4 != 0) {
        void* mgr = FUN_00b3d230();
        ((void(__thiscall*)(void*, void*, int))(*(void***)mgr)[0x38 / 4])
            (mgr, mpE4, 1);
    }

    void* input = GameInputManager();
    if (input == 0)
        return;

    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0xfa0, (const char*)0x147874c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x132, (const char*)0x147873c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e8514, (const char*)0x147872c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37ea1bd, (const char*)0x1478714);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4d2b5fd, (const char*)0x14786fc);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e851a, (const char*)0x14786ec);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e851b, (const char*)0x14786d4);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95bd, (const char*)0x14786c0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95bc, (const char*)0x14786a8);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95ba, (const char*)0x1478694);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95b9, (const char*)0x1478684);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x3e9, (const char*)0x1478670);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x3ea, (const char*)0x147865c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x3eb, (const char*)0x1478648);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f7, (const char*)0x147863c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x12d, (const char*)0x1478628);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x12e, (const char*)0x147861c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x12f, (const char*)0x147860c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x130, (const char*)0x1478600);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x131, (const char*)0x14785f0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f5, (const char*)0x14785e8);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f7, (const char*)0x147863c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f6, (const char*)0x14785d8);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x7d1, (const char*)0x14785c4);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x7d2, (const char*)0x14785b0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf27, (const char*)0x147859c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf28, (const char*)0x1478588);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf28, (const char*)0x1478574);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf29, (const char*)0x1478560);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x38b, (const char*)0x147854c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x406d0d8, (const char*)0x147853c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95bb, (const char*)0x1478534);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x51b4174, (const char*)0x1478528);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x46ee610, (const char*)0x1478520);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x51b40a4, (const char*)0x1478514);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x49363f1, (const char*)0x1478504);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x6264b4d, (const char*)0x14784f0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4e54bb3, (const char*)0x14784cc);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4e540ec, (const char*)0x14784ac);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4e540ed, (const char*)0x147848c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4518450, (const char*)0x147847c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x58b3913, (const char*)0x1478468);

    void* cursor = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, u32))(*(void***)cursor)[0xb8 / 4])(cursor, 0);

    void* server = MessageServer();
    void* handler = (void*)&mpVtbl3C;
    mp6C = server;
    mp70 = handler;
    mp74 = (u32*)0x14782f0;
    mn78 = 0x4a;
    mn7C = 0;
    if (server != 0 && handler != 0) {
        for (u32 i = 0; i < 0x4a; ++i)
            ((void(__thiscall*)(void*, void*, u32))(*(void***)server)[0x24 / 4])
                (server, handler, ((u32*)0x14782f0)[i]);
    }

    CommEditor* ce = (CommEditor*)op_new(0x2fc, (const char*)0x1477120, 0, 0, 0, 0);
    if (ce != 0)
        ce = ce->Ctor();

    CommEditor* old = (CommEditor*)mp80;
    if (ce != old) {
        if (ce != 0)
            ((void(__fastcall*)(void*))(*(void***)ce)[8 / 4])(ce);
        mp80 = ce;
        if (old != 0)
            ((void(__fastcall*)(void*))(*(void***)old)[0xc / 4])(old);
    }
    ce = (CommEditor*)mp80;
    if (ce != 0)
        ce->Init(0x169d248, 0x5b9c8704, 0, 0);

    mn130 = 0;
    ((TreeOps*)&mTreeBase84)->ResetA(mn90);
    mn90 = 0;
    mn98 = 0;
    mn88 = (u32)((char*)this + 0x88);
    mn8C = (u32)((char*)this + 0x88);
    mb94 = 0;
    ((TreeOps*)&mTreeBaseA0)->ResetB(mnAC);
    mnA4 = (u32)((char*)this + 0xA4);
    mnA8 = (u32)((char*)this + 0xA4);
    mnAC = 0;
    mbB0 = 0;
    mnB4 = 0;

    ArgCmd local;
    local.Ctor(&mTreeBase84);
    local.SetName((const char*)0x1478450);
    local.Finish();

    PieMenu* menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp50 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp54 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp5C = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp60 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp64 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp68 = menu;
    local.Destroy();
}

// ===========================================================================
// 0x00cf50e0 -- species-scan message callback
// ===========================================================================
// @ 0x00cf50e0
u32 __stdcall FUN_00cf50e0(void* a1, void* a2)
{
    if (a1 == 0)
        return 0;

    u32 v1 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0xd0036e08);
    u32 v2 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0xe9cb8ba);
    u32 v3 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0xee02c7);
    u32 v4 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x137e8e0);
    u32 v5 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x4f176642);
    u32 v6 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x116d858);
    u32 v7 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x629baec);

    void* planet = FUN_01021260();

    if (v1 != 0) {
        u32* sp = ((ScanObj*)v1)->FUN_c0bc00();
        if (!((Planet*)planet)->SetSpeciesAsScanned(sp)) {
            u32 commCtx;
            commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
            void* terrain = ((NounMgr*)NounManager())->GetTerrain();
            void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
            sp = ((ScanObj*)v1)->FUN_c0bc00();
            u8* slot = ((Entry8*)((char*)node + 8))->Find(sp);
            *slot = 1;
            void* r = FUN_00ba5e10((void*)v1, 1);
            ((Obj9*)FUN_00b3d4f0(r))->Do();
        }
    }

    if (v4 != 0) {
        void* sub = (char*)v4 + 0x34;
        u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
        if (!((Planet*)planet)->Known(sp)) {
            u32 commCtx;
            commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
            void* terrain = ((NounMgr*)NounManager())->GetTerrain();
            void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
            sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
            u8* slot = ((Entry38*)((char*)node + 0x38))->Find(sp);
            *slot = 1;
            void* r = FUN_00ba57a0((void*)v4, 1);
            ((Obj9*)FUN_00b3d4f0(r))->Do();
        }
    }

    if (v2 != 0) {
        if (((Edition*)((char*)v2 + 0x120))->GetFileCount() != 2) {
            void* sub = (char*)v2 + 0x34;
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
            u32 key = (u32)sp;
            if (!((Planet*)planet)->IsScanned(sp)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr*)NounManager())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
                u8* slot = ((Entry20*)((char*)node + 0x20))->Find(sp);
                *slot = 1;
                void* r = FUN_00ba57a0((void*)v2, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
            (void)key;
        }
    }

    if (v3 != 0) {
        void* obj = ((void*(__fastcall*)(void*))(*(void***)v3)[0x58 / 4])((void*)v3);
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr*)NounManager())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    if (v6 != 0) {
        void* obj = ((ObjA*)v6)->FUN_c9d9e0();
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr*)NounManager())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    if (v5 != 0) {
        void* obj = ((ObjB*)v5)->GetTribe();
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr*)NounManager())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    if (v7 != 0) {
        void* obj = ((TribeHolder*)v7)->mpTribe;
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr*)NounManager())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    return 0;
}
