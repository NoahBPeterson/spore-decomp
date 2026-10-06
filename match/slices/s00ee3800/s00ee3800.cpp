// Slice s00ee3800 -- 0x00ee3800..0x00ee41e0  (/O2 /MD /Gy /TP /fp:fast)
//
// More scenario-edit-mode behaviour UI handlers (same editor object as
// slices s00edcfc0 / s00ee2860).
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void* DAT_016c7aa4;
extern int   DAT_0148a9c8[];

struct Mgrs {
    char pad00[0x10];
    int  f10;
    int  F3be60(int);
    int  F45970();
    int  F45a80();
    int  F427c0();
    int  F3be30();
};
#define MGR()  (*(Mgrs**)((char*)DAT_016c7aa4 + 0x74))

#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
#define VCP2(p,off,a,b) (((void*(__thiscall*)(void*,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))

struct L18 { char pad[4]; void F3630(int); void FCD30(int); };
struct L48 { char pad[4]; void FBDD0(int); void FBD30(int); };

extern "C" int  FUN_00efc8f0();
extern "C" int  FUN_00efc520();
extern "C" int  FUN_00efe5b0();
extern "C" int  FUN_00f3e8a0(int, int);
extern "C" int  FUN_00efc8c0(int);
extern "C" void* SP_MessageServer();
extern "C" int  FUN_00f25490();
extern "C" int  FUN_00f25670();
extern "C" void  EA_Messaging_RemoveHandler(int, int, int, int, int);
extern "C" int  FUN_00edcd30(int);
extern "C" void  FUN_00edbdd0();

struct Bee {
    char pad[0x300];
    void F3E40(char);
    void F3F20(int);
    void F3F60(int*, int*);
    void F3940();
    void F40F0();
    void FEDD810();
    void FEDDA20();
    void FEDF240();
    void FEDF410();
    void FEDF4C0();
    void FEDF510();
    void FEE16F0();
    void FEE31D0();
    void FEE30D0();
    void FEE31D0_();
};

// ============================================================ 0x00ee3f20
// @ 0x00ee3f20
void Bee::F3F20(int param)
{
    char* t = (char*)this;
    ((L18*)*(void**)(t + 0x18))->F3630(param);
    ((L48*)*(void**)(t + 0x48))->FBDD0(param);
    void* p24 = *(void**)(t + 0x24);
    if (p24 != 0)
        ((int(__thiscall*)(void*,int,bool))VTP(p24)[0x7c/4])(p24, 2, *(char*)(t + 0xc5) == 0);
}

// ============================================================ 0x00ee3e40
// @ 0x00ee3e40
void Bee::F3E40(char param)
{
    char* t = (char*)this;
    int ebx = (int)param;
    if (param == 0) {
        FEDD810();
        int h = *(int*)(t + 0xf0);
        if (h != 0) {
            *(int*)(t + 0xf0) = 0;
            EA_Messaging_RemoveHandler(h, *(int*)(t + 0xf4), *(int*)(t + 0xf8), *(int*)(t + 0xfc), *(int*)(t + 0x100));
        }
        FEE30D0();
    } else {
        int b2 = (this != 0) ? (int)(t + 0x10) : 0;
        void* ms = SP_MessageServer();
        *(void**)(t + 0xf0) = ms;
        *(int*)(t + 0xf4) = b2;
        *(void**)(t + 0xf8) = (void*)DAT_0148a9c8;
        *(int*)(t + 0xfc) = 10;
        *(int*)(t + 0x100) = 0;
        if (ms != 0 && b2 != 0) {
            for (unsigned u = 0; u < 0x28; u += 4)
                VC2(ms, 0x24, b2, *(int*)((char*)DAT_0148a9c8 + u));
        }
        FEE31D0();
    }
    ((L18*)*(void**)(t + 0x18))->FCD30(ebx);
    ((L48*)*(void**)(t + 0x48))->FBD30(ebx);
    *(char*)(t + 0xc4) = param;
}

// ============================================================ 0x00ee3800  (partial)
// @ 0x00ee3800
bool __cdecl f00ee3800(int a1, int a2, int a3, int a4)
{
    (void)a1; (void)a2; (void)a3; (void)a4;
    return false;   // 308-byte selection handler not reconstructed
}

// ============================================================ 0x00ee3940  (partial)
// @ 0x00ee3940
void Bee::F3940()
{
    (void)this;   // 1271-byte handler not reconstructed
}

// ============================================================ 0x00ee3f60  (partial)
// @ 0x00ee3f60
void Bee::F3F60(int* a, int* b)
{
    (void)this; (void)a; (void)b;   // message dispatch not reconstructed
}

// ============================================================ 0x00ee40f0  (partial)
// @ 0x00ee40f0
void Bee::F40F0()
{
    (void)this;   // EASTL random-selection helper not reconstructed
}

// ============================================================ 0x00ee41e0  (partial)
// @ 0x00ee41e0
bool __cdecl f00ee41e0(int a, int b, int c, int d, char e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return false;   // 427-byte handler not reconstructed
}
