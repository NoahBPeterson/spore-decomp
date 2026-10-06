// Slice s00eed3f0 -- 0x00eed3f0..0x00eedc10  (/O2 /MD /Gy /TP /fp:fast)
//
// Scenario-edit-mode property helpers (spin-control callbacks).
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void* DAT_016c7aa4;
extern int   DAT_016c7a28;
extern int   DAT_016c7a38;
extern int   DAT_015ac948;
extern int   DAT_015ac94c;
extern char  DAT_015acb40;

#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC4(p,off,a,b,c,d) (((int(__thiscall*)(void*,int,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c),(int)(d)))

struct Prop { char pad[4]; int* GetInt(); };
struct RefObj { virtual void v0(); virtual void Release(); };

extern "C" bool FUN_005bf0e0(int, int**);
extern "C" bool FUN_005bf7c0(int*, int);
extern "C" bool FUN_00eebfc0(int*, int);
extern "C" int  FUN_00eec760(int*, int);
extern "C" unsigned FUN_00eec870(int);

// ============================================================ 0x00eed920
// @ 0x00eed920
bool __cdecl f00eed920(int param1, int param2)
{
    int* local = 0;
    bool ok = FUN_005bf0e0(param1, &local) && FUN_005bf7c0(local, param2);
    if (local != 0)
        VC0(local, 4);
    return ok;
}

// ============================================================ 0x00eed970
// @ 0x00eed970
bool __cdecl f00eed970(int param1, int param2)
{
    int* local = 0;
    bool ok = FUN_005bf0e0(param1, &local) && FUN_00eebfc0(local, param2);
    if (local != 0)
        VC0(local, 4);
    return ok;
}

// ============================================================ 0x00eed9c0
// @ 0x00eed9c0
bool __cdecl f00eed9c0(int param1, int param2)
{
    int* local = 0;
    if (FUN_005bf0e0(param1, &local)) {
        FUN_00eec760(local, param2);
        if (local != 0)
            VC0(local, 4);
        return true;
    }
    if (local != 0)
        VC0(local, 4);
    return false;
}

// ============================================================ 0x00eed840
// @ 0x00eed840
bool __cdecl f00eed840(int param)
{
    int* local = 0;
    int out;
    bool ok;
    if (!FUN_005bf0e0(param, &local))
        goto fail;
    if (local == 0)
        goto fail;
    if (!((char(__thiscall*)(void*,int,int*))VTP(local)[0x24 / 4])(local, 0x5888ef41, &out))
        goto fail;
    if (*(short*)(out + 0x12) != 9)
        goto fail;
    if (*((Prop*)out)->GetInt() == DAT_016c7a28)
        ok = true;
    else
        goto fail;
    goto done;
fail:
    ok = false;
done:
    if (local != 0)
        ((RefObj*)local)->Release();
    return ok;
}

// ============================================================ 0x00eed3f0  (partial)
// @ 0x00eed3f0
void __cdecl f00eed3f0(int a, int b, int c, int d)
{
    (void)a; (void)b; (void)c; (void)d;   // 814-byte handler not reconstructed
}

// ============================================================ 0x00eed720  (partial)
// @ 0x00eed720
void __cdecl f00eed720(int* a, int* b, unsigned* c)
{
    (void)a; (void)b; (void)c;   // 282-byte spin-state evaluator not reconstructed
}

// ============================================================ 0x00eed8c0  (partial)
// @ 0x00eed8c0
int __cdecl f00eed8c0(int param)
{
    (void)param;   // property-bag read not reconstructed
    return 0;
}

// ============================================================ 0x00eeda20  (partial)
// @ 0x00eeda20
void __cdecl f00eeda20(int a, int b)
{
    (void)a; (void)b;   // 376-byte handler not reconstructed
}

// ============================================================ 0x00eedba0  (partial)
// @ 0x00eedba0
void __cdecl f00eedba0(int a, float* out)
{
    (void)a; (void)out;   // colour-unpack helper not reconstructed
}

// ============================================================ 0x00eedc10  (partial)
// @ 0x00eedc10
void __cdecl f00eedc10(int a, int b, int c)
{
    (void)a; (void)b; (void)c;   // 418-byte handler not reconstructed
}
