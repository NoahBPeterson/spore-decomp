// s00a550e0 -- the EA::Audio::Eapd "float outlet" scalar-node family (a Pure Data port).
// Every node keeps two floats at +0x28/+0x2c and a pointer at +0x0c to a bound outlet
// binder whose +0x08 holds the outlet list head; each accessor computes a scalar and
// broadcasts it to all bound outlets through Eapd::outlet_float, wrapped in a
// re-entrancy guard (DAT_0167545c, capped at 1000).  The slice also holds the
// spSin/spCos/spTan class factories and their perform bodies.
//
// The accessors are free functions taking the node pointer as their first argument
// (the original loads it from [esp+4], never from ecx).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

typedef unsigned int uint;
typedef unsigned long ulong;

// ---- EAPd (Pure Data port) runtime -----------------------------------------
namespace EA { namespace Audio { namespace Eapd {
int  __cdecl pd_new(void* cls);                       // 0x00a49390
int  __cdecl outlet_new(void* self, int a, int b);    // 0x00a49d30
void __cdecl outlet_float(void* o, float f);          // 0x00a49570
}}}

// ---- shared globals --------------------------------------------------------
extern "C" int DAT_0167545c;              // 0x0167545c  re-entrancy guard
extern "C" int DAT_016758c4;              // 0x016758c4
extern "C" int DAT_016758c8;              // 0x016758c8
extern "C" int DAT_016755d4;              // 0x016755d4  spSin class
extern "C" int DAT_016755a4;              // 0x016755a4  spCos class
extern "C" int DAT_016755cc;              // 0x016755cc  spTan class

// x87 fsin/fcos come from the double-precision intrinsics (MSVC 2008 emits fsin/fcos).
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sin)
#pragma intrinsic(cos)

// ---- the node layout -------------------------------------------------------
// +0x00 vptr, +0x04/+0x08 base words, +0x0c -> bound-outlet binder,
// +0x10..+0x27 scratch, +0x28 float value, +0x2c float right operand.
struct tOutNode {
    void*         mpVtbl;                     // +0x00
    void*         mPad04;                     // +0x04
    void*         mPad08;                     // +0x08
    void*         mpOutlets;                  // +0x0c  -> binder
    unsigned char pad_10[0x18];               // +0x10..+0x27
    float         mValue;                     // +0x28
    float         mOperand;                   // +0x2c
};

struct Outlet { Outlet* mpNext; int mIndex; };

static __forceinline Outlet* nodeOutlets(tOutNode* n)
{
    return *(Outlet**)((char*)n->mpOutlets + 8);
}

// broadcast a scalar to every bound outlet while the guard allows it.
static __forceinline void nodeBroadcast(tOutNode* n, float f)
{
    void* binder = n->mpOutlets;            // fetched before the guard bump
    ++DAT_0167545c;
    if (DAT_0167545c < 1000) {
        for (Outlet* o = *(Outlet**)((char*)binder + 8); o; o = o->mpNext)
            EA::Audio::Eapd::outlet_float((void*)o->mIndex, f);
    }
    --DAT_0167545c;
}

// =====================================================================
// equality / inequality
// =====================================================================
// @ 0x00a550e0
void __cdecl getEq(tOutNode* n)   { nodeBroadcast(n, (float)(n->mValue == n->mOperand)); }

// @ 0x00a55150
void __cdecl setEq(tOutNode* n, float v)
{
    float rhs = n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)(v == rhs));
}

// @ 0x00a55220
void __cdecl getNe(tOutNode* n)   { nodeBroadcast(n, (float)(n->mValue != n->mOperand)); }

// @ 0x00a55290
void __cdecl setNe(tOutNode* n, float v)
{
    float rhs = n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)(v != rhs));
}

// =====================================================================
// ordering
// =====================================================================
// @ 0x00a55360
void __cdecl getGt(tOutNode* n)
{
    nodeBroadcast(n, (float)(n->mValue > n->mOperand));
}

// @ 0x00a553d0
void __cdecl setGt(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (v > n->mOperand) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a554a0
void __cdecl getGe(tOutNode* n)
{
    int r = (n->mOperand > n->mValue) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55510
void __cdecl setGe(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (n->mOperand > v) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a555e0
void __cdecl getLt(tOutNode* n)
{
    int r = (n->mValue >= n->mOperand) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55650
void __cdecl setLt(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (v >= n->mOperand) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55720
void __cdecl getLe(tOutNode* n)
{
    int r = (n->mOperand >= n->mValue) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55790
void __cdecl setLe(tOutNode* n, float v)
{
    n->mValue = v;
    int r = (n->mOperand >= v) ? 1 : 0;
    nodeBroadcast(n, (float)r);
}

// =====================================================================
// integer/bitwise operations (truncated to int)
// =====================================================================
// @ 0x00a55860
void __cdecl getBitAnd(tOutNode* n)
{
    nodeBroadcast(n, (float)((int)n->mOperand & (int)n->mValue));
}

// @ 0x00a558d0
void __cdecl setBitAnd(tOutNode* n, float v)
{
    n->mValue = v;
    nodeBroadcast(n, (float)((int)n->mOperand & (int)v));
}

// @ 0x00a55ae0
void __cdecl getBitOr(tOutNode* n)
{
    nodeBroadcast(n, (float)((int)n->mOperand | (int)n->mValue));
}

// @ 0x00a55b50
void __cdecl setBitOr(tOutNode* n, float v)
{
    n->mValue = v;
    nodeBroadcast(n, (float)((int)n->mOperand | (int)v));
}

// @ 0x00a55c10
void __cdecl getAndL(tOutNode* n)
{
    int a = (int)n->mValue;
    nodeBroadcast(n, (float)((a != 0) || ((int)n->mOperand != 0)));
}

// @ 0x00a55c80
void __cdecl setAndL(tOutNode* n, float v)
{
    n->mValue = v;
    int a = (int)v;
    nodeBroadcast(n, (float)((a != 0) || ((int)n->mOperand != 0)));
}

// @ 0x00a55d50
void __cdecl getShl(tOutNode* n)
{
    int r = (int)n->mValue << (int)n->mOperand;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55dc0
void __cdecl setShl(tOutNode* n, float v)
{
    int sh = (int)n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)((int)v << sh));
}

// @ 0x00a55e80
void __cdecl getShr(tOutNode* n)
{
    int r = (int)n->mValue >> (int)n->mOperand;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a55ef0
void __cdecl setShr(tOutNode* n, float v)
{
    int sh = (int)n->mOperand;
    n->mValue = v;
    nodeBroadcast(n, (float)((int)v >> sh));
}
// =====================================================================
// division / modulus
// =====================================================================
// @ 0x00a55990
void __cdecl getDiv(tOutNode* n)
{
    int a = (int)n->mValue;
    nodeBroadcast(n, (float)((a != 0) && ((int)n->mOperand != 0)));
}

// @ 0x00a55a10
void __cdecl setDiv(tOutNode* n, float v)
{
    n->mValue = v;
    int a = (int)v;
    nodeBroadcast(n, (float)((a != 0) && ((int)n->mOperand != 0)));
}

// @ 0x00a55fb0
void __cdecl getMod(tOutNode* n)
{
    int d = (int)n->mOperand;
    if (d == 0)
        d = 1;
    nodeBroadcast(n, (float)((int)n->mValue % d));
}

// @ 0x00a56030
void __cdecl setMod(tOutNode* n, float v)
{
    int d = (int)n->mOperand;
    n->mValue = v;
    if (d == 0)
        d = 1;
    nodeBroadcast(n, (float)((int)v % d));
}

// @ 0x00a56100
void __cdecl getFmod(tOutNode* n)
{
    int d = (int)n->mOperand;
    if (d < 0)
        d = -d;
    else if (d == 0)
        d = 1;
    int r = (int)n->mValue % d;
    if (r < 0)
        r += d;
    nodeBroadcast(n, (float)r);
}

// @ 0x00a56180
void __cdecl setFmod(tOutNode* n, float v)
{
    n->mValue = v;
    getFmod(n);
}

// @ 0x00a561f0
void __cdecl getIntDiv(tOutNode* n)
{
    int d = (int)n->mOperand;
    int num = (int)n->mValue;
    if (d < 0)
        d = -d;
    else if (d == 0)
        d = 1;
    if (num < 0)
        num += (1 - d);
    nodeBroadcast(n, (float)(num / d));
}

// @ 0x00a56270
void __cdecl setIntDiv(tOutNode* n, float v)
{
    n->mValue = v;
    getIntDiv(n);
}

// =====================================================================
// spSin / spCos / spTan class factories
// =====================================================================
// @ 0x00a56290
int __cdecl spSinClassFactory()
{
    int r = EA::Audio::Eapd::pd_new((void*)DAT_016755d4);
    if (r)
        EA::Audio::Eapd::outlet_new((void*)r, DAT_016758c4, DAT_016758c8);
    return r;
}

// @ 0x00a562c0
void __cdecl spSinPerform(tOutNode* n, float f)
{
    float r = (float)sin((double)f);
    nodeBroadcast(n, r);
}

// @ 0x00a56320
int __cdecl spCosClassFactory()
{
    int r = EA::Audio::Eapd::pd_new((void*)DAT_016755a4);
    if (r)
        EA::Audio::Eapd::outlet_new((void*)r, DAT_016758c4, DAT_016758c8);
    return r;
}

// @ 0x00a56350
void __cdecl spCosPerform(tOutNode* n, float f)
{
    float r = (float)cos((double)f);
    nodeBroadcast(n, r);
}

// @ 0x00a563b0
int __cdecl spTanClassFactory()
{
    int r = EA::Audio::Eapd::pd_new((void*)DAT_016755cc);
    if (r)
        EA::Audio::Eapd::outlet_new((void*)r, DAT_016758c4, DAT_016758c8);
    return r;
}

// @ 0x00a563e0
void __cdecl spTanPerform(tOutNode* n, float f)
{
    float c = (float)cos((double)f);
    float r;
    if (c == 0.0f)
        r = 0.0f;
    else
        r = (float)sin((double)f) / c;
    nodeBroadcast(n, r);
}
