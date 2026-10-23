// Slice s00e72430 (frozen batch spcg1): object SPGonzago/SPCellGame.obj.
// Cell-game special-ability event emission: builds 0x7c-byte "effect record"
// entries into the +0x54 object list of the cell game, drives the gfx-state
// byte, and the per-ability trigger helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- globals
struct cCellGame;                    // defined after ObjectPool below
extern cCellGame* gspCellGame;       // 0x16b3c04
extern uint8_t* gspCellGfx;     // 0x16b3c08
extern uint8_t* gspCellState;   // 0x16b3c0c
extern "C" int   g_16b3c28, g_16b3c2c, g_16b3c30;             // world centre
extern "C" int   g_15a7c4c, g_15a7c50, g_15a7c54, g_15a7c58;  // default orientation/scale
extern "C" float g_1486d94;     // 0.125f

// ---------------------------------------------------------------- helpers / callees
struct ObjectPool {
    void* GetChecked(int handle);   // 0x00b721d0
    void* Get(int handle);          // 0x00b72210
    int   Alloc();                  // 0x00b72160
};
// Cell-game object as addressed by the 0x16b3c04 pointer.  Only the fields this
// slice touches are declared; everything else is padding.
struct cCellGame {
    char pad0[0x1c];
    ObjectPool mCells;                          // 0x1c
    char pad1d[0x54 - 0x1d];
    ObjectPool mEffects;                        // 0x54
    char pad55[0x411c - 0x55];
    int  mHandle411c;                           // 0x411c
    char pad4120[0x5158 - 0x4120];
    int  mState5158;                            // 0x5158
    char pad515c[0x5169 - 0x515c];
    uint8_t mByte5169;                          // 0x5169
    char pad516a[0x5190 - 0x516a];
    void* mpLevelInfo;                          // 0x5190
    int  mHandle5194;                           // 0x5194
};
#define gspCG ((uint8_t*)gspCellGame)   // raw byte view
struct ModalObj { void setModal(int); };      // method 0x00ad7e40

struct cSPTransform {
    uint16_t mFlags; uint16_t mModCount;
    float mTranslation[3]; float mScale; float mRotation[9];
    cSPTransform& copyFrom(const cSPTransform&);   // 0x0040ce80
    cSPTransform& invert();                        // 0x0040efa0
    cSPTransform& compose(const cSPTransform&);    // 0x0040ccb0
};

extern "C" void* __cdecl FUN_00b3d4d0();                              // trigger mgr
extern "C" float __cdecl FUN_00e6d200(int, int, int, int);            // 0x00e6d200
extern "C" void  __cdecl FUN_00e59470(int);
extern "C" void  __cdecl FUN_00e59640(int, int, int, int, int);
extern "C" void  __cdecl FUN_00e59710(int, int, int, float, float, int);
extern "C" void  __cdecl FUN_00e59800(int);
extern "C" void  __cdecl FUN_00e599b0(int);
extern "C" void  __cdecl FUN_00e59a30();
extern "C" void  __cdecl FUN_00e59af0(int, int);
extern "C" void  __cdecl FUN_00e59b50(int, int, int);
extern "C" bool  __cdecl FUN_00e57460(int, int);
extern "C" int   __cdecl FUN_00e4ff50(int);
extern "C" float __fastcall FUN_00e4eef0(void* self, int v);          // CellLevel_GetRatio
extern "C" void  __cdecl FUN_00e57170(float);
extern "C" void  __cdecl FUN_00e53580();
extern "C" void  __cdecl FUN_00e53130();
extern "C" void  __cdecl FUN_00e6d560();
extern "C" void  __cdecl FUN_00e6d600();
extern "C" void  __cdecl FUN_00e4f660(int);
extern "C" void  __cdecl FUN_00e82c10(void*, int, int, int);
extern "C" void  __cdecl FUN_00e528f0(int, float);
extern "C" void  __cdecl FUN_00e59200(int);
extern "C" int   __cdecl SP_sAttach(int, int, int, void*, int);       // 0x00e5f450
extern "C" void  __cdecl FUN_00e51ee0(int, int, int, int, int, int, int, int,
                                      int, int, int, int, int, int, int, int);
extern "C" void  __cdecl SP_CreateEffectSafe(int, unsigned, int, void**);  // 0x00628450
extern "C" int   __cdecl FUN_00e6a090(int, int, int, float, float);
extern "C" int   __cdecl FUN_00e69c10(int, int, int, float, float);
extern "C" int   __cdecl FUN_00e69e00(int, int, int, float, float);
extern "C" int   __cdecl FUN_00e69f90(int, int);

static int     FB(float f) { union { float f; int i; } u; u.f = f; return u.i; }
static void**  VT(void* p) { return *(void***)p; }

// shared 0x7c-byte effect-record layout
struct EvRec {
    char pad0[4];
    int  f04;              // +0x04
    uint8_t f08;           // +0x08
    char pad09[0x13];
    float f1c, f20;        // +0x1c +0x20
    int f24, f28, f2c;     // +0x24 +0x28 +0x2c
    int f30, f34, f38, f3c;
    float f40, f44;
    int v48, v4c, v50, v54, v58, v5c, v60, v64, v68, f6c;
    int f70;
    uint8_t f74;
    char pad75[3];
    int f78;
};

// ================================================================ 00e72430
// @ 0x00e72430
void FUN_00e72430(int* param_1) {
    void* e = gspCellGame->mCells.Get(*param_1);
    float f = FUN_00e6d200((int)e, 0, 0x3d, *(int*)((char*)e + 0x1b0));
    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f1c = f;
    r->f28 = *param_1;
    r->f20 = f;
    r->f2c = 0;
    r->f38 = 0;
    r->f3c = 0;
    r->f24 = 0x2a;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->f30 = -1;
    r->f34 = -1;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e59470(*param_1);
}

// ================================================================ 00e72530
// @ 0x00e72530
// NOTE: original consumes ESI (self) and EDI from the caller; not reproducible
// with the standard ABI (see nonmatching.txt).
void FUN_00e72530(int* self, int ediVal, int arg1, int arg2, int arg3) {
    if (*(char*)((char*)self + 0x113) != 0) return;
    if (*(char*)((char*)self + 0x112) != 0) return;
    void* e = gspCellGame->mCells.Get(*self);
    float f = FUN_00e6d200((int)e, 0, ediVal, *(int*)((char*)e + 0x1b0));
    FUN_00e51ee0(0x15, FB(f), *self, arg1, arg2, -1, ediVal, 0, 0, 0,
                 arg3, 0, 0, 0, 0, 0);
    FUN_00e59640(*self, arg1, arg2, ediVal, arg3);
}

// ================================================================ 00e725c0
// @ 0x00e725c0
int FUN_00e725c0(int* self, int* edi_obj, int param_1) {
    if (*(char*)((char*)self + 0x179) != 0) return 1;
    if (*(char*)((char*)self + 0x17b) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x178) != 0) return 0;
    if (FUN_00e57460((int)edi_obj, (int)self)) return 0;

    void* e = gspCellGame->mCells.Get(*edi_obj);
    float f = FUN_00e6d200((int)e, 0, 0xd, *(int*)((char*)e + 0x1b0));
    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f2c = *self;
    r->f28 = *edi_obj;
    r->f1c = f;
    r->f20 = f;
    r->f3c = self[0x42];
    r->f24 = 0x14;
    r->f30 = param_1;
    r->f34 = 0;
    r->f38 = 4;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;

    void* r2 = gspCellGame->mEffects.Get(h);
    *(float*)((char*)r2 + 0x10) = f;
    void* r3 = gspCellGame->mEffects.Get(h);
    *(float*)((char*)r3 + 0xc) = f * g_1486d94;

    cSPTransform local;
    local.copyFrom(*(cSPTransform*)((char*)self + 0x48));
    local.invert();
    local.compose(*(cSPTransform*)((char*)edi_obj + 0x48));
    int att = SP_sAttach(*self, -1, *edi_obj, &local, 0);
    *(int*)((char*)self + 0x168) = att;
    FUN_00e59710(*edi_obj, *self, param_1, f * g_1486d94, f, 0);
    return 1;
}

// ================================================================ 00e727e0
// @ 0x00e727e0
int FUN_00e727e0(int* self, int* edi_obj, int param_1) {
    if (*(char*)((char*)self + 0x179) != 0) return 1;
    if (*(char*)((char*)self + 0x17b) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x178) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x113) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x112) != 0) return 0;
    if (FUN_00e57460((int)edi_obj, (int)self)) return 0;

    void* e = gspCellGame->mCells.Get(*edi_obj);
    float f = FUN_00e6d200((int)e, 0, 0xd, *(int*)((char*)e + 0x1b0));
    void* e2 = gspCellGame->mCells.Get(*self);
    FUN_00e6d200((int)e2, 0, 0x20, *(int*)((char*)e2 + 0x1b0));
    FUN_00e51ee0(0x13, FB(f), *edi_obj, *self, param_1, 0, 4, self[0x42],
                 0, 0, 0, 0, 0, 0, 0, 0);
    float q = f * g_1486d94;
    FUN_00e528f0(0, q);
    FUN_00e69c10(*edi_obj, *self, param_1, q, 0.0f);
    return 1;
}

// ================================================================ 00e72910
// @ 0x00e72910
int FUN_00e72910(int* self, int* param_1, int param_2) {
    if (*(char*)((char*)self + 0x179) != 0) return 1;
    if (*(char*)((char*)self + 0x17b) != 0) return 0;
    if (*(char*)((char*)param_1 + 0x178) != 0) return 0;

    void* e = gspCellGame->mCells.Get(*param_1);
    float f = FUN_00e6d200((int)e, 0, 0xd, *(int*)((char*)e + 0x1b0));
    if (self[0xdc]) FUN_00e59200(self[0xdc]);

    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f2c = *self;
    r->f28 = *param_1;
    r->f1c = f;
    r->f20 = f;
    r->f3c = self[0x42];
    r->f24 = 0x12;
    r->f30 = param_2;
    r->f34 = 0;
    r->f38 = 4;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;

    void* r2 = gspCellGame->mEffects.Get(h);
    *(float*)((char*)r2 + 0xc) = f * g_1486d94;
    FUN_00e69e00(*param_1, *self, param_2, f * g_1486d94, 0.0f);
    return 1;
}

// ================================================================ 00e72ac0
// @ 0x00e72ac0
void FUN_00e72ac0() {
    ((ModalObj*)FUN_00b3d4d0())->setModal(0);
    *(uint8_t*)(gspCellState + 0x936) = 0;
    FUN_00e6d560();
    FUN_00e59800(0);
    void* local_4 = 0;
    SP_CreateEffectSafe(*(int*)(gspCellGfx + 0x161c8), 0xa1b0293d, 0, &local_4);
    if (local_4) ((void(__thiscall*)(void*, int))VT(local_4)[2])(local_4, 0);
    *(uint8_t*)(gspCellState + 0x936) = 1;
    if (local_4) ((void(__thiscall*)(void*))VT(local_4)[1])(local_4);
}

// ================================================================ 00e72b40
// @ 0x00e72b40
// NOTE: original consumes ESI (self) from the caller.
void FUN_00e72b40(int* self) {
    void* e = gspCellGame->mCells.Get(*self);
    float v = FUN_00e6d200((int)e, 0, 0x1d, *(int*)((char*)e + 0x1b0));
    if (v == 0.0f) {
        gspCellGame->mCells.GetChecked(*self);
        return;
    }
    void* lvl = *(void**)(gspCG + 0x5190);
    FUN_00e57170(FUN_00e4eef0(lvl, *(int*)((char*)lvl + 0x1c)));

    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f1c = v;
    r->f20 = v;
    r->f28 = *self;
    r->f2c = 0;
    r->f38 = 0;
    r->f3c = 0;
    r->f24 = 0x1f;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->f30 = -1;
    r->f34 = -1;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e599b0(*self);
}

// ================================================================ 00e72c80
// @ 0x00e72c80
void FUN_00e72c80() {
    int* e = (int*)gspCellGame->mCells.GetChecked(*(int*)(gspCG + 0x411c));
    if (!e) return;
    if (*(char*)((char*)e + 0x113) == 1) return;
    if (*(char*)((char*)e + 0x112) == 1) return;

    *(uint8_t*)(gspCG + 0x5169) = 1;
    if (*(int*)(gspCG + 0x5158) == 3) return;

    FUN_00e53580();
    *(int*)(gspCG + 0x5158) = 3;
    FUN_00e53130();
    FUN_00e6d600();

    int* e2 = (int*)gspCellGame->mCells.GetChecked(*(int*)(gspCG + 0x411c));
    int local_c = 0, local_8 = 0, local_4 = 0;
    if (e2) {
        local_c = *(int*)((char*)e2 + 0xfc);
        local_8 = *(int*)((char*)e2 + 0x100);
        local_4 = *(int*)((char*)e2 + 0x104);
    }
    int* lvl = *(int**)(gspCG + 0x5190);
    FUN_00e82c10(&local_c, *(int*)((char*)lvl + 0x74), *(int*)((char*)lvl + 0x70),
                 *(int*)((char*)lvl + 0x6c));
    FUN_00e4f660(1);

    void* e3 = gspCellGame->mCells.Get(*(int*)(gspCG + 0x411c));
    float f = FUN_00e6d200((int)e3, 0, 0x2e, *(int*)((char*)e3 + 0x1b0));
    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f1c = f;
    r->f20 = f;
    r->f24 = 0x1f;
    r->f28 = 0;
    r->f2c = 0;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->f30 = -1;
    r->f34 = -1;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    *(int*)(gspCG + 0x5194) = h;
    FUN_00e59a30();
}

// ================================================================ 00e72e70
// @ 0x00e72e70
void FUN_00e72e70(int* param_1, int param_2) {
    char* pFlag = (char*)FUN_00e69f90((int)param_1, param_2);
    if (*pFlag == 1) return;
    int b = (param_2 != 6);
    *pFlag = 1;

    void* e = gspCellGame->mCells.Get(*param_1);
    float f = FUN_00e6d200((int)e, 0, b + 0x3f, *(int*)((char*)e + 0x1b0));
    int v = *param_1;
    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f1c = f;
    r->f20 = f;
    r->f24 = 0x27;
    r->f28 = v;
    r->f2c = 0;
    r->f30 = param_2;
    r->f34 = -1;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e59af0(*param_1, param_2);
}

// ================================================================ 00e72fb0
// @ 0x00e72fb0
void FUN_00e72fb0(int* param_1, int param_2) {
    char* pFlag = (char*)FUN_00e69f90((int)param_1, param_2);
    if (*pFlag == 1) return;
    *pFlag = 1;

    void* e = gspCellGame->mCells.Get(*param_1);
    float f = FUN_00e6d200((int)e, 0, 0x34, *(int*)((char*)e + 0x1b0));
    int v = *param_1;
    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f1c = f;
    r->f20 = f;
    r->f24 = 0x28;
    r->f28 = v;
    r->f2c = 0;
    r->f30 = param_2;
    r->f34 = -1;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e59af0(*param_1, param_2);
}

// ================================================================ 00e730d0
// @ 0x00e730d0
bool FUN_00e730d0(int param_1, int param_2, int param_3) {
    if (!gspCellGame->mCells.GetChecked(param_1)) return false;
    int other = (int)gspCellGame->mCells.GetChecked(param_2);
    if (!other) return false;
    if (FUN_00e4ff50(other) == 1) {
        FUN_00e72fb0((int*)other, param_3);
        return true;
    }
    FUN_00e72e70((int*)other, param_3);
    return true;
}

// ================================================================ 00e73140
// @ 0x00e73140
bool FUN_00e73140(int* param_1, int* param_2, int param_3) {
    if (*(char*)((char*)param_1 + 0x178) != 0) return false;

    void* e = gspCellGame->mCells.Get(*param_1);
    float f = FUN_00e6d200((int)e, 0, 0x3b, *(int*)((char*)e + 0x1b0));
    if (param_2[0xdc]) FUN_00e59200(param_2[0xdc]);

    int h = gspCellGame->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame->mEffects.Get(h);
    r->f28 = *param_1;
    r->f1c = f;
    r->f20 = f;
    r->f30 = param_3;
    r->f24 = 0x29;
    r->f2c = *param_2;
    r->f34 = -1;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28; r->v4c = g_16b3c2c; r->v50 = g_16b3c30;
    r->v54 = g_16b3c28; r->v58 = g_16b3c2c; r->v5c = g_16b3c30;
    r->v60 = g_15a7c4c; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;

    float q = f * g_1486d94;
    void* r2 = gspCellGame->mEffects.Get(h);
    *(float*)((char*)r2 + 0xc) = q;
    FUN_00e6a090(*param_1, *param_2, param_3, q, 0.0f);
    return true;
}

// ================================================================ 00e732d0
// @ 0x00e732d0
void FUN_00e732d0(int* param_1, int* param_2, int param_3, int param_4, int param_5) {
    if (*(char*)((char*)param_1 + 0x112) == 1) return;
    if (*(char*)((char*)param_1 + 0x113) == 1) return;
    if (*(char*)((char*)param_1 + 0x17f) != 0) return;

    void* e = gspCellGame->mCells.Get(*param_1);
    float f = FUN_00e6d200((int)e, 0, 0x1c, *(int*)((char*)e + 0x1b0));
    FUN_00e51ee0(0x26, FB(f), *param_1, *param_2, param_3, param_4, 0, 0, 0, 0,
                 param_5, 0, 0, 0, 0, 0);
    FUN_00e59b50(*param_1, param_3, param_5);
    FUN_00e730d0(*param_1, *param_2, param_4);
}
