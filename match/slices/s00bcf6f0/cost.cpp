// Slice s00bcf6f0 (continued): cost-formula helpers (0x00bcff00..0x00bd0110).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;

// The shared price helper: FUN_00bcd480(empireID, float mul, float base) -> float.
// It returns the float through x87 and takes (uint, float, float).
float __cdecl F00bcd480_cdecl(uint empireID, float mul, float base);   // 0x00bcd480

// Globals referenced by the four cost wrappers (float constants).
extern float g_costA1;    // 0x0169c0fc
extern float g_costA2;    // 0x0169c100
extern float g_costB1;    // 0x0169c07c
extern float g_costB2;    // 0x0169c080
extern float g_costC1;    // 0x0169c0a8
extern float g_costC2;    // 0x0169c0ac
extern float g_costD1;    // 0x0169c1b0
extern float g_costD2;    // 0x0169c1b4

struct CostObj {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48();
    virtual uint GetPoliticalID();            // 0x4c

    float GetCost_A();                        // 0x00bcff00
    float GetCost_B();                        // 0x00bcff40
    float GetCost_C();                        // 0x00bcff80
    float GetCost_D();                        // 0x00bd0110
};

// @ 0x00bcff00
float CostObj::GetCost_A()
{
    uint id = GetPoliticalID();
    float b = g_costA2;
    return F00bcd480_cdecl(id, g_costA1, b);
}

// @ 0x00bcff40
float CostObj::GetCost_B()
{
    uint id = GetPoliticalID();
    float b = g_costB2;
    return F00bcd480_cdecl(id, g_costB1, b);
}

// @ 0x00bcff80
float CostObj::GetCost_C()
{
    uint id = GetPoliticalID();
    float b = g_costC2;
    return F00bcd480_cdecl(id, g_costC1, b);
}

// @ 0x00bd0110
float CostObj::GetCost_D()
{
    uint id = GetPoliticalID();
    float b = g_costD2;
    return F00bcd480_cdecl(id, g_costD1, b);
}
