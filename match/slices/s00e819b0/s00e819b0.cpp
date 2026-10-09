// Slice s00e819b0: Cell mode lifecycle + resource/effect helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Vector3 { float x, y, z; Vector3() {} Vector3(float a,float b,float c):x(a),y(b),z(c){} };

struct ObjectPool { void* Get(int h) const; void* GetChecked(int h) const; int Alloc(); void Free(int h); };

struct cCellGame {
    char pad0[0x410c];
    char mField410c;      // 0x410c
    char pad410d[0x4110 - 0x410d];
    int mField4110;       // 0x4110
    char pad4114[0x411c - 0x4114];
    int mHandle411c;      // 0x411c
    char pad4120;
    char mByte4121;       // 0x4121
    char pad4122[0x5190 - 0x4122];
    int* mLevelInfo;      // 0x5190
    char pad5194[0x519c - 0x5194];
    int* mVec519c;        // 0x519c
    int* mVec51a0;        // 0x51a0
};

struct cCellGfx {
    char pad0[0x40];
    char mArray40[0x10];   // 0x40
    int* mField50;         // 0x50
    int* mField54;         // 0x54
    int* mField58;         // 0x58
};

struct CellState {
    char pad0[0xe0];
    int mFieldE0;
    char padE4[0xf4 - 0xe4];
    float mFieldF4;
    char padF8[0x936 - 0xf8];
    char mField936;
};

extern cCellGame* gspCellGame;    // 0x016b3c04
extern cCellGfx* gspCellGfx;      // 0x016b3c08
extern CellState* gspCellState;   // 0x016b3c0c
extern int* gListSentinel;        // 0x016b44f0
extern int* gspCellMode3de0;      // 0x016b3de0
extern char gFieldL_01654c00;     // 0x01654c00
extern int  gField_016b44ec;      // 0x016b44ec
extern void* gField_016b44d8;     // 0x016b44d8
extern char gInitMarker;          // marker
int __cdecl atexit(void (*)(void));
int   FUN_00e932e80(int a, int b, int c);   // 0x00e932e80
int*  FUN_00a206f0();                        // 0x00a206f0
void  Start3dSoundByName(int a, int b, int c, int d, int e);   // 0x00571f80
void  KillSetiEffects();                     // 0x00435ed0

// ---- callees ----
void  FUN_00e4cde0();                     // 0x00e4cde0
void  sInitGfx();                         // 0x00e4cdb0 (SP::sInitGfx)
void* EffectsManager();                   // 0x00e4cd10
void* ModelManager();                     // 0x00e4cd20
void* MessageServer();                    // 0x00e4cd30
void* AppSystem();                        // 0x00e4cd40
void* GameInputManager();                 // 0x00b3d250
void* NounManager();                      // 0x00b3d300
int   GetCurrentTerrainSphere(void* ed);  // 0x00f67d90
int   DebugNameFromSPID(int a, int b, int c);  // 0x00e4bf30
void  FUN_00e84e40(const char* fmt, ...); // 0x00e84e40
int   EA_ResourceMan_GetManager();        // 0x0067dcd0 (returns ptr)
int*  FUN_0067cb20b();                    // 0x0067cb20
int*  FUN_0067dd00();                     // 0x0067dd00
int*  FUN_006eea10();                     // 0x006eea10
int*  FUN_00401010();                     // 0x00401010
int*  FUN_00401090(void* p);              // 0x00401090
void  FUN_004df310();                     // 0x004df310
void  SetAvatarSpecies(int* p);           // 0x004df310
int   FUN_00b3d320(void* p);              // 0x00b3d320
void  __fastcall FUN_00b1e410(int x);     // 0x00b1e410
extern char gFieldL_01654c01;             // 0x01654c01
void  FUN_0067de90x();
void  FUN_00e666f0();                     // 0x00e666f0
void  FUN_00e511b0();                     // 0x00e511b0
void  FUN_00743b50(void* it);             // 0x00743b50
int*  FUN_00e4ce40(void* x);              // 0x00e4ce40
void  FUN_00e67610(int x);                // 0x00e67610
void  FUN_00e67670();                     // 0x00e67670
void  FUN_00e54270(int x);                // 0x00e54270
void  FUN_00e80ba0();                     // 0x00e80ba0
void  FUN_00e809a0();                     // 0x00e809a0
void  FUN_00e7f960();                     // 0x00e7f960
void  FUN_00e7f9b0();                     // 0x00e7f9b0
void  FUN_00e548d0();                     // 0x00e548d0
void  FUN_00e66980();                     // 0x00e66980
void  FUN_00e661c0();                     // 0x00e661c0
void  FUN_00e4ce20();                     // 0x00e4ce20
int   FUN_00e823e0();                     // 0x00e823e0
void  FUN_00e646d0();                     // 0x00e646d0
void  FUN_00e647d0();                     // 0x00e647d0
void  FUN_00e61aa0();                     // 0x00e61aa0
void  FUN_00e61b00();                     // 0x00e61b00
void  FUN_00e834d0();                     // 0x00e834d0
void  FUN_00e4c8c0();                     // 0x00e4c8c0
void  FUN_00e4db10();                     // 0x00e4db10
void  FUN_00e4fe50();                     // 0x00e4fe50
void  FUN_00e83590(void* p);              // 0x00e83590
void  CellDataShutdownForApp();           // 0x00e4?
void  FUN_00e4c9e0();                     // 0x00e4c9e0
int   FUN_00f473a0(int sz, const char* name, int a, int b, int c, int d);  // operator new
void  FUN_00f47380(void* p);              // operator delete
void  FUN_013c7e60();                     // 0x013c7e60
void  FUN_00692f60();                     // 0x00692f60
void  FUN_00692850();                     // 0x00692850
int   FUN_00ab30c0();                     // 0x00ab30c0
struct C006a17e0 { void FUN_006a17e0(int a, int b); };
extern int* gField_15fd918;               // 0x015fd918

struct IVtbl17 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual char m(int a, int b);
};
struct IVtbl30 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29();
    virtual void m(int a);
};
int   SetGlobalProperty(int a, float b);  // 0x005ca880
void  PlayEditorSound(int a, int b, float c, int d);  // 0x00435f40
void  FUN_00572020(int a, int b);         // 0x00572020
void  FUN_009fbc50(int a, float x, float y, float z);  // 0x009fbc50
int   FUN_00c75420();                     // 0x00c75420
int   FUN_00e834d0_fn();                  // placeholder

// @ 0x00e82130
void __fastcall FUN_00e82130(int* it)
{
    if (*it != 0)
        (*(int*)(*it + 0xc))--;
}

// @ 0x00e82140
bool SP_sCellResourceLoadFailure(int param_1, int* param_2)
{
    struct { int a; int b; int c; } k;
    k.b = *(int*)(param_1 + 8);
    k.a = 0x7a638526;
    k.c = 0;
    int* mgr = (int*)EA_ResourceMan_GetManager();
    if (((bool(*)(void*,int*,int,int,int,int))mgr[7])(&k, param_2, 0, 0, 0, 0) == 0)
        return false;
    if (*(int*)(param_1 + 0x20) != 0) {
        if (*param_2 != 0) {
            int* o = (int*)(*(int(**)(int))(*(int*)*param_2 + 0xc))(0x2269ed1);
            ((void(*)(int))*(int*)(param_1 + 0x20))(*(int*)((char*)o + 0x14));
            return true;
        }
        ((void(*)(int))*(int*)(param_1 + 0x20))(*(int*)0x14);
    }
    return true;
}

// @ 0x00e821d0
bool FUN_00e821d0(unsigned id, int param_2, int* param_3)
{
    if (id == 0 || id == 0xffffffff)
        return false;
    struct { unsigned a; int b; int c; } k;
    k.a = id;
    k.b = *(int*)(param_2 + 8);
    k.c = 0;
    int* mgr = (int*)EA_ResourceMan_GetManager();
    if (!((bool(*)(void*,int*))mgr[5])(&k, param_3)) {
        int* mgr2 = (int*)EA_ResourceMan_GetManager();
        if (!((bool(*)(void*,int*,int,int,int,int))mgr2[3])(&k, param_3, 0, 0, 0, 0))
            return false;
        int iVar3 = 0;
        if (*param_3 != 0)
            iVar3 = (*(int(**)(int))(*(int*)*param_3 + 0xc))(0x2269ed1);
        if (*(void(**)(int))(param_2 + 0x20) != 0)
            (*(void(**)(int))(param_2 + 0x20))(*(int*)(iVar3 + 0x14));
    }
    return true;
}

// @ 0x00e82280
void FUN_00e82280()
{
    int* p = (int*)*gListSentinel;
    if (p != gListSentinel) {
        do {
            int* q = (int*)p[4];
            if (q != 0) {
                p[4] = 0;
                (*(void(**)(void))(*q + 4))();
            }
            p = (int*)*p;
        } while (p != gListSentinel);
    }
}

// @ 0x00e822c0
namespace SP {
void LoadResource(int* param_1)
{
    int* piVar2 = (int*)param_1[2];
    int* piVar1 = param_1 + 2;
    if (piVar2 != 0) {
        *piVar1 = 0;
        (*(void(**)(void))(*piVar2 + 4))();
    }
    char c = FUN_00e821d0((unsigned)*param_1, param_1[1], piVar1) ? 1 : 0;
    if (c == 0) {
        int uVar4 = DebugNameFromSPID(*param_1, *param_1, *(int*)param_1[1]);
        FUN_00e84e40("cannot load asset id:%s (0x%X), type:%s", uVar4);
        int* piVar2b = (int*)*piVar1;
        if (piVar2b != 0) {
            *piVar1 = 0;
            (*(void(**)(void))(*piVar2b + 4))();
        }
        SP_sCellResourceLoadFailure(param_1[1], piVar1);
    }
}
}

// @ 0x00e82340
int __stdcall FUN_00e82340(int* param_1)
{
    int iVar2 = FUN_00f473a0(0x18,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0, 0, 0, 0xd1);
    if ((int*)(iVar2 + 8) != 0) {
        *(int*)(iVar2 + 8) = *param_1;
        *(int*)(iVar2 + 0xc) = param_1[1];
        int* puVar1 = (int*)param_1[2];
        *(int**)(iVar2 + 0x10) = puVar1;
        if (puVar1 != 0)
            (*(void(**)(void))(*puVar1))();
        *(int*)(iVar2 + 0x14) = param_1[3];
    }
    return iVar2;
}

// @ 0x00e823a0
int FUN_00e823a0(int param_1, int* param_2)
{
    *param_2 = param_1;
    (*(int*)(param_1 + 0xc))++;
    if (*(int*)(param_1 + 8) == 0)
        SP::LoadResource((int*)param_1);
    if (*(int*)(param_1 + 8) != 0) {
        int iVar1 = (*(int(**)(int))(**(int**)(param_1 + 8) + 0xc))(0x2269ed1);
        return *(int*)(iVar1 + 0x14);
    }
    return *(int*)0x14;
}

// @ 0x00e82420
int* FUN_00e82420(int param_1, int param_2)
{
    int* puVar1 = gListSentinel;
    int* puVar2 = (int*)*gListSentinel;
    for (;;) {
        if (puVar2 == gListSentinel) {
        add:
            struct { int a; int b; int c; int d; } local;
            local.c = param_2;
            local.d = 0;
            local.a = param_1;
            local.b = 0;
            puVar2 = (int*)FUN_00e82340((int*)&local);
            *puVar2 = (int)puVar1;
            puVar2[1] = puVar1[1];
            *(int**)puVar1[1] = puVar2;
            puVar1[1] = (int)puVar2;
            return puVar2 + 2;
        }
        if (puVar2[2] == param_1 && puVar2[3] == param_2) {
            if (puVar2 + 2 != 0)
                return puVar2 + 2;
        }
        puVar2 = (int*)*puVar2;
    }
}

// @ 0x00e82490
void FUN_00e82490()
{
    int* p = (int*)FUN_00f473a0(0xc, 0, 0, 0, 0, 0);
    if (p != 0) {
        *p = (int)p;
        p[1] = (int)p;
        gListSentinel = p;
        return;
    }
    gListSentinel = 0;
}

// @ 0x00e824d0
void FUN_00e824d0()
{
    FUN_00e82280();
    int iVar1 = (int)gListSentinel;
    if (gListSentinel != 0) {
        FUN_00e823e0();
        FUN_00f47380((void*)iVar1);
    }
}

// @ 0x00e82500
void FUN_00e82500(int a)
{
    ((C006a17e0*)gField_15fd918)->FUN_006a17e0(0x28, a);
}

// @ 0x00e82690
void FUN_00e82690(int a, float b)
{
    SetGlobalProperty(a, b);
}

// @ 0x00e826b0
void FUN_00e826b0(int a, int b, float c)
{
    if (a != 0)
        PlayEditorSound(a, b, c, 0);
}

// @ 0x00e826e0
void FUN_00e826e0(int a)
{
    if (a != 0)
        FUN_00572020(a, 0);
}

// @ 0x00e82700
void FUN_00e82700(int a, float* v)
{
    if (a != 0)
        FUN_009fbc50(a, v[0], v[1], v[2]);
}

// @ 0x00e82730
int* FUN_00e82730(int a)
{
    int* p = (int*)FUN_006eea10();
    ((IVtbl30*)p)->m(a);
    return p;
}

// @ 0x00e82760
void FUN_00e82760()
{
    int* p = (int*)FUN_0067dd00();
    int* vt = (int*)*p;
    (*(void(__fastcall*)(void*))vt[0x54 / 4])(p);
}

// @ 0x00e82770
char FUN_00e82770(int param_1)
{
    int* piVar2 = (int*)FUN_00401010();
    piVar2 = (int*)(*(int(**)(int,int))(*piVar2 + 0x58))(*(int*)(param_1 + 0x88), *(int*)(param_1 + 0x84));
    if (piVar2 == 0)
        return 1;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x100f0f5a)) return 12;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a74)) return 2;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a70)) return 3;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x32f92e6)) return 9;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a72)) return 10;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a71)) return 7;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a78)) return 4;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a75)) return 6;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a76)) return 5;
    if ((*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a77)) return 8;
    bool c = (*(bool(**)(int))(*piVar2 + 0x1c))(0x11b79a73);
    return (-(c != 0) & 10U) + 1;
}

// @ 0x00e828c0
void FUN_00e828c0()
{
    FUN_00b1e410(FUN_00b3d320(&gFieldL_01654c01));
}

// @ 0x00e82900
bool FUN_00e82900(int a, int b)
{
    int* p = (int*)GameInputManager();
    return ((IVtbl17*)p)->m(a, b) != 0;
}

// @ 0x00e82920
int* FUN_00e82920(int* param_1)
{
    int* ed = (int*)NounManager();
    int iVar3 = GetCurrentTerrainSphere(ed);
    if (iVar3 == 0) {
        param_1[0] = 0; param_1[1] = 0; param_1[2] = 0;
        return param_1;
    }
    ed = (int*)NounManager();
    iVar3 = GetCurrentTerrainSphere(ed);
    param_1[0] = *(int*)(iVar3 + 0x68c);
    param_1[1] = *(int*)(iVar3 + 0x690);
    param_1[2] = *(int*)(iVar3 + 0x694);
    return param_1;
}

// @ 0x00e82970
int FUN_00e82970()
{
    int* ed = (int*)NounManager();
    int iVar2 = GetCurrentTerrainSphere(ed);
    if (iVar2 == 0)
        return 1;
    ed = (int*)NounManager();
    GetCurrentTerrainSphere(ed);
    return FUN_00c75420();
}

// @ 0x00e829a0
void FUN_00e829a0()
{
    int* pcVar1 = (int*)FUN_00401090(&pcVar1);
    SetAvatarSpecies(pcVar1);
}

// @ 0x00e819b0
void FUN_00e819b0(char param_1)
{
    gspCellGame->mByte4121 = 1;
    FUN_00e4cde0();
    sInitGfx();
    int* em = (int*)EffectsManager();
    int* a = (int*)(*(int(**)(const char*, int, int))(*em + 0x4c))("CellPreloadedEffectsWorld", 0x1010051, 0);
    int** s50 = &gspCellGfx->mField50;
    if (a != *s50) {
        if (a != 0) (*(void(**)(void))*a)();
        *s50 = a;
        if (*s50 != 0) (*(void(**)(void))(**s50 + 4))();
    }
    int* mm = (int*)ModelManager();
    int* b = (int*)(*(int(**)(const char*, int))(*mm + 0x14))("CellPreloadedModelWorld", 0x1010050);
    int** s54 = &gspCellGfx->mField54;
    if (b != *s54) {
        if (b != 0) (*(void(**)(void))*b)();
        *s54 = b;
        if (*s54 != 0) (*(void(**)(void))(**s54 + 4))();
    }
    int* cb = FUN_0067cb20b();
    int* c = (int*)(*(int(**)(const wchar_t*))(*cb + 0x20))(L"CellGame-Preloaded");
    int** s58 = &gspCellGfx->mField58;
    if (c != *s58) {
        if (c != 0) (*(void(**)(void))*c)();
        *s58 = c;
        if (*s58 != 0) (*(void(**)(void))(**s58 + 4))();
    }
    (*(void(**)(int, int, int, int))(**(int**)((char*)gspCellGfx + 0x58) + 0x1c))(
        (int)*(int**)((char*)gspCellGfx + 0x54), 1, 0, 0);
    (*(void(**)(int))(**(int**)((char*)gspCellGfx + 0x58) + 0x18))(
        (int)*(int**)((char*)gspCellGfx + 0x50));
    FUN_00e666f0();
    FUN_00e511b0();
    int it[4];
    FUN_00743b50(it);
    int iVar3 = (int)FUN_00e4ce40(it);
    FUN_00e67610(*(int*)(iVar3 + 0x3c));
    FUN_00e67610(*(int*)(iVar3 + 0x40));
    FUN_00e82130(it);
    FUN_00e67670();
    int* piVar1 = gspCellMode3de0;
    if (param_1 != 0) {
        int* piVar2 = gspCellGame->mLevelInfo;
        if (piVar2 != gspCellMode3de0) {
            if (piVar2 != 0) (*(void(**)(void))*piVar2)();
            gspCellMode3de0 = piVar2;
            if (piVar1 != 0) (*(void(**)(void))(*piVar1 + 4))();
        }
    }
    FUN_00e54270(param_1);
    FUN_00e80ba0();
    {
        int* p = (int*)MessageServer();
        (*(void(**)(void(*)(), int, int, int, int))(*p + 0x28))(FUN_00e809a0, 0, 0x30c11c7, 0, 0);
    }
    {
        int* p = (int*)MessageServer();
        (*(void(**)(void(*)(), int, int, int, int))(*p + 0x28))(FUN_00e7f960, 0, 0x445f729, 0, 0);
    }
}

// @ 0x00e81ba0
void FUN_00e81ba0()
{
    int* p = (int*)MessageServer();
    (*(void(**)(void(*)(), int, int))(*p + 0x30))(FUN_00e7f960, 0x445f729, 0xffffd8f1);
    p = (int*)MessageServer();
    (*(void(**)(void(*)(), int, int))(*p + 0x30))(FUN_00e809a0, 0x30c11c7, 0xffffd8f1);
    FUN_00e7f9b0();
    FUN_00e548d0();
    FUN_00e66980();
    FUN_00e661c0();
    (*(void(**)(void))(**(int**)((char*)gspCellGfx + 0x58) + 0x20))();
    {
        int* piVar1 = *(int**)((char*)gspCellGfx + 0x58);
        if (piVar1 != 0) {
            *(int*)((char*)gspCellGfx + 0x58) = 0;
            (*(void(**)(void))(*piVar1 + 4))();
        }
    }
    p = (int*)EffectsManager();
    (*(void(**)(int))(*p + 0x50))(0x1010051);
    {
        int* piVar1 = *(int**)((char*)gspCellGfx + 0x50);
        if (piVar1 != 0) {
            *(int*)((char*)gspCellGfx + 0x50) = 0;
            (*(void(**)(void))(*piVar1 + 4))();
        }
    }
    p = (int*)ModelManager();
    (*(void(**)(int))(*p + 0x18))(0x1010050);
    {
        int* piVar1 = *(int**)((char*)gspCellGfx + 0x54);
        if (piVar1 != 0) {
            *(int*)((char*)gspCellGfx + 0x54) = 0;
            (*(void(**)(void))(*piVar1 + 4))();
        }
    }
    FUN_00e4ce20();
    gspCellGame->mByte4121 = 0;
}

// @ 0x00e81c90
int FUN_00e81c90(int param_1, int param_2)
{
    if (*(int**)(param_2 + 8) == (int*)&gFieldL_01654c00)
        return 1;   // NOTE: bool-returning handler body omitted (partial)
    return 1;
}

// @ 0x00e81cf0
int __fastcall FUN_00e81cf0(int param_1)
{
    if ((gField_016b44ec & 1) == 0) {
        gField_016b44ec |= 1;
        FUN_00692f60();
        gField_016b44d8 = &gInitMarker;
        atexit(FUN_013c7e60);
    }
    if (FUN_00ab30c0() == 0)
        FUN_00692850();
    gspCellGame = 0;
    gspCellGfx = 0;
    gspCellState = 0;
    gspCellGame->mByte4121 = 0;
    gspCellGame->mField410c = 0;
    gspCellGame->mField4110 = 0;
    return 1;
}

// @ 0x00e81f30
int __fastcall FUN_00e81f30(int param_1)
{
    if (gspCellGame->mByte4121 != 0)
        FUN_00e81ba0();
    CellDataShutdownForApp();
    FUN_00e4c9e0();
    FUN_00e83590(&gspCellGfx->mArray40);
    int* p = (int*)EffectsManager();
    (*(void(**)(int, int, int))(*p + 0x88))(0x1010003, 0, 0);
    p = (int*)EffectsManager();
    (*(void(**)(int, int))(*p + 0x98))(7, 0);
    p = (int*)MessageServer();
    (*(void(**)(int(*)(int,int), int, int))(*p + 0x30))(FUN_00e81c90, 0x212d3e7, 0xffffd8f1);
    return 1;
}

// @ 0x00e82520
unsigned FUN_00e82520(float a, float b)
{
    // custom xmm-register convention in the original; logic only
    return 0;
}

// @ 0x00e82620
int FUN_00e82620(int param_1, int* param_2)
{
    int uVar1 = FUN_00e932e80(param_1, 0x811c9dc5, 1);
    int* piVar2 = (int*)FUN_00a206f0();
    int uVar3;
    if (piVar2 == 0)
        uVar3 = 0;
    else
        uVar3 = (*(int(**)(void))(*piVar2 + 0x20))();
    if (param_2 != 0) {
        Start3dSoundByName(uVar1, uVar3, param_2[0], param_2[1], param_2[2]);
        return uVar3;
    }
    KillSetiEffects();
    return uVar3;
}

