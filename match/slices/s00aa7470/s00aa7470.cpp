// Slice s00aa7470 -- EA::Swarm particle-effect description helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// data globals / string constants referenced by literal address
extern const char  DAT_014119cc[];    // "reset"
extern const float DAT_01485720;      // 1.0f
extern const float DAT_01457d54;
extern void*       DAT_016793a0[];    // dispatch table of function pointers
extern int         DAT_015655dc[];    // dword table

// ---------------------------------------------------------------------------
// external helpers (cdecl)
extern "C" void  operator_delete__(void* p);
extern "C" int   FUN_00a87470(int a, int b, int c);

extern "C" void  FUN_0093a780(void* s, void* buf, int n, int pad);   // ReadInt32
extern "C" void  FUN_0093a800(void* s, void* buf, int n, int pad);   // ReadUInt64
extern "C" void  FUN_0093a700(void* s, void* buf, int n, int pad);   // ReadUInt16
extern "C" void  FUN_0093a6c0(void* s, void* buf, int n);            // WriteExact
extern "C" void  FUN_007d27d0(void* s, void* dst);                   // ReadIntVector
extern "C" void  FUN_007ed920(void* s, void* dst);
extern "C" void  FUN_00a85b00(void* s, void* dst);
extern "C" void  FUN_00a9a870(void* s, void* dst);
extern "C" void  FUN_00a87f50(void* s, void* dst);
extern "C" void  FUN_00a7b9a0(void* s, void* dst);
extern "C" void  FUN_00a7ba10(void* s, void* dst);
extern "C" void  FUN_00a9a8d0(void* s, void* dst);

extern "C" void  FUN_00a7d280(void* a, void* b, void* c, void* d);   // ParseSurfaceOptions

// ---------------------------------------------------------------------------
// vtable-slot helpers
#define VTP(obj, off)   (*(void**)((char*)(*(void**)(obj)) + (off)))

// ---------------------------------------------------------------------------
// thiscall helpers modeled as methods so the compiler places "this" in ecx
struct CArgs {
    void* MainArguments(int n);              // 0x838320
    void* MainArgumentsX(void* out, int a, int b);  // 0x838020
    char  HasFlag(const char* name);         // 0x8380b0
};

struct StrAssign {
    void FUN_00454cb0(const char* begin, const char* end);  // eastl::basic_string::assign
};

struct CmdObj {
    void* FUN_00aa3460();     // ctor
    void  FUN_00aa32f0();     // dtor
};

struct Parser {
    void* FUN_00a6f090(void* args, int count, void* extra);  // GetInheritedDescription
};

struct XOp {   // generic thiscall helpers (1/2 pointer args) for eastl vectors etc.
    void FUN_0050d4e0(const void* rhs);       // eastl::vector<float,..>::operator=
    void FUN_006f5cd0(const void* rhs);       // vector_operator_assign_c
    void FUN_00a9a3d0(const void* rhs);
    void FUN_00a87b90(const void* rhs);
    void FUN_00a9a500(const void* rhs);
    void FUN_00a87280(const void* src);       // construct element at this
    void FUN_00a87d20(void* end, const void* src);
    void FUN_00a87300(int a, int b);
};

// generic description object (all access via byte offsets)
struct Self {
    char raw[0x2e0];
    Self* FUN_00aa7470(const Self* o);
    void  FUN_00aa82e0(char p);
    void  FUN_00aa8370(int p);
    bool  FUN_00aa7fb0(int p2, int* p3, int p4);
    void  FUN_00aa7910(void* args);
    void  FUN_00aa7a80(void* args);
};

// ===========================================================================
// @ 0x00aa7470
Self* Self::FUN_00aa7470(const Self* o)
{
    char* t = raw;
    const char* q = o->raw;
    *(int*)(t + 8)   = *(const int*)(q + 8);
    *(int*)(t + 0xc) = *(const int*)(q + 0xc);
    *(int*)(t + 0x10)= *(const int*)(q + 0x10);
    *(int*)(t + 0x14)= *(const int*)(q + 0x14);
    *(float*)(t + 0x18) = *(const float*)(q + 0x18);
    *(int*)(t + 0x1c)= *(const int*)(q + 0x1c);
    *(int*)(t + 0x20)= *(const int*)(q + 0x20);
    *(int*)(t + 0x24)= *(const int*)(q + 0x24);
    *(int*)(t + 0x28)= *(const int*)(q + 0x28);
    *(int*)(t + 0x38)= *(const int*)(q + 0x38);
    *(int*)(t + 0x3c)= *(const int*)(q + 0x3c);
    *(int*)(t + 0x40)= *(const int*)(q + 0x40);
    *(int*)(t + 0x2c)= *(const int*)(q + 0x2c);
    *(int*)(t + 0x30)= *(const int*)(q + 0x30);
    *(int*)(t + 0x34)= *(const int*)(q + 0x34);
    *(int*)(t + 0x44)= *(const int*)(q + 0x44);
    *(int*)(t + 0x48)= *(const int*)(q + 0x48);
    *(int*)(t + 0x58)= *(const int*)(q + 0x58);
    *(int*)(t + 0x5c)= *(const int*)(q + 0x5c);
    *(int*)(t + 0x60)= *(const int*)(q + 0x60);
    *(int*)(t + 0x4c)= *(const int*)(q + 0x4c);
    *(int*)(t + 0x50)= *(const int*)(q + 0x50);
    *(int*)(t + 0x54)= *(const int*)(q + 0x54);
    *(float*)(t + 0x64) = *(const float*)(q + 0x64);
    ((XOp*)(t + 0x68))->FUN_0050d4e0(q + 0x68);
    *(float*)(t + 0x7c) = *(const float*)(q + 0x7c);
    *(short*)(t + 0x80) = *(const short*)(q + 0x80);
    *(float*)(t + 0x84) = *(const float*)(q + 0x84);
    ((XOp*)(t + 0x88))->FUN_0050d4e0(q + 0x88);
    *(float*)(t + 0x9c) = *(const float*)(q + 0x9c);
    ((XOp*)(t + 0xa0))->FUN_0050d4e0(q + 0xa0);
    *(float*)(t + 0xb4) = *(const float*)(q + 0xb4);
    ((XOp*)(t + 0xb8))->FUN_0050d4e0(q + 0xb8);
    *(float*)(t + 0xcc) = *(const float*)(q + 0xcc);
    *(float*)(t + 0xd0) = *(const float*)(q + 0xd0);
    ((XOp*)(t + 0xd4))->FUN_006f5cd0(q + 0xd4);
    *(int*)(t + 0xe8)= *(const int*)(q + 0xe8);
    *(int*)(t + 0xec)= *(const int*)(q + 0xec);
    *(int*)(t + 0xf0)= *(const int*)(q + 0xf0);
    ((XOp*)(t + 0xf4))->FUN_0050d4e0(q + 0xf4);
    *(float*)(t + 0x108) = *(const float*)(q + 0x108);
    {
        struct Blk32 { int v[8]; };
        *(Blk32*)(t + 0x110) = *(const Blk32*)(q + 0x110);
    }
    *(unsigned char*)(t + 0x130) = *(const unsigned char*)(q + 0x130);
    *(unsigned char*)(t + 0x131) = *(const unsigned char*)(q + 0x131);
    *(unsigned char*)(t + 0x132) = *(const unsigned char*)(q + 0x132);
    *(unsigned char*)(t + 0x133) = *(const unsigned char*)(q + 0x133);
    *(unsigned char*)(t + 0x134) = *(const unsigned char*)(q + 0x134);
    *(unsigned char*)(t + 0x135) = *(const unsigned char*)(q + 0x135);
    *(unsigned char*)(t + 0x136) = *(const unsigned char*)(q + 0x136);
    *(unsigned char*)(t + 0x137) = *(const unsigned char*)(q + 0x137);
    *(float*)(t + 0x138) = *(const float*)(q + 0x138);
    *(int*)(t + 0x13c)= *(const int*)(q + 0x13c);
    *(int*)(t + 0x140)= *(const int*)(q + 0x140);
    *(int*)(t + 0x144)= *(const int*)(q + 0x144);
    *(float*)(t + 0x148) = *(const float*)(q + 0x148);
    *(float*)(t + 0x14c) = *(const float*)(q + 0x14c);
    *(float*)(t + 0x150) = *(const float*)(q + 0x150);
    *(int*)(t + 0x154)= *(const int*)(q + 0x154);
    *(int*)(t + 0x158)= *(const int*)(q + 0x158);
    *(int*)(t + 0x15c)= *(const int*)(q + 0x15c);
    *(float*)(t + 0x160) = *(const float*)(q + 0x160);
    *(float*)(t + 0x164) = *(const float*)(q + 0x164);
    *(float*)(t + 0x168) = *(const float*)(q + 0x168);
    ((XOp*)(t + 0x16c))->FUN_00a9a3d0(q + 0x16c);
    *(unsigned char*)(t + 0x180) = *(const unsigned char*)(q + 0x180);
    *(unsigned char*)(t + 0x181) = *(const unsigned char*)(q + 0x181);
    *(unsigned char*)(t + 0x182) = *(const unsigned char*)(q + 0x182);
    *(unsigned char*)(t + 0x183) = *(const unsigned char*)(q + 0x183);
    ((XOp*)(t + 0x184))->FUN_006f5cd0(q + 0x184);
    ((XOp*)(t + 0x198))->FUN_0050d4e0(q + 0x198);
    ((XOp*)(t + 0x1ac))->FUN_00a87b90(q + 0x1ac);
    *(float*)(t + 0x1c0) = *(const float*)(q + 0x1c0);
    *(float*)(t + 0x1c4) = *(const float*)(q + 0x1c4);
    *(float*)(t + 0x1c8) = *(const float*)(q + 0x1c8);
    *(float*)(t + 0x1cc) = *(const float*)(q + 0x1cc);
    *(float*)(t + 0x1d0) = *(const float*)(q + 0x1d0);
    *(float*)(t + 0x1d4) = *(const float*)(q + 0x1d4);
    *(float*)(t + 0x1d8) = *(const float*)(q + 0x1d8);
    *(int*)(t + 0x1dc)= *(const int*)(q + 0x1dc);
    *(int*)(t + 0x1e0)= *(const int*)(q + 0x1e0);
    *(int*)(t + 0x1e8)= *(const int*)(q + 0x1e8);
    *(int*)(t + 0x1ec)= *(const int*)(q + 0x1ec);
    *(int*)(t + 0x1f0)= *(const int*)(q + 0x1f0);
    *(int*)(t + 0x1f4)= *(const int*)(q + 0x1f4);
    *(int*)(t + 0x1f8)= *(const int*)(q + 0x1f8);
    *(int*)(t + 0x1fc)= *(const int*)(q + 0x1fc);
    *(int*)(t + 0x200)= *(const int*)(q + 0x200);
    *(int*)(t + 0x204)= *(const int*)(q + 0x204);
    *(int*)(t + 0x208)= *(const int*)(q + 0x208);
    *(int*)(t + 0x20c)= *(const int*)(q + 0x20c);
    *(float*)(t + 0x210) = *(const float*)(q + 0x210);
    *(float*)(t + 0x214) = *(const float*)(q + 0x214);
    *(float*)(t + 0x218) = *(const float*)(q + 0x218);
    ((XOp*)(t + 0x21c))->FUN_0050d4e0(q + 0x21c);
    *(unsigned char*)(t + 0x230) = *(const unsigned char*)(q + 0x230);
    *(int*)(t + 0x234)= *(const int*)(q + 0x234);
    *(int*)(t + 0x238)= *(const int*)(q + 0x238);
    *(int*)(t + 0x23c)= *(const int*)(q + 0x23c);
    {
        const char* op = q + 0x240;
        char* tp = t + 0x240;
        ((XOp*)tp)->FUN_0050d4e0(op);
        *(float*)(tp + 0x14) = *(const float*)(op + 0x14);
        *(float*)(tp + 0x18) = *(const float*)(op + 0x18);
    }
    ((XOp*)(t + 0x25c))->FUN_00a9a500(q + 0x25c);
    return this;
}

// ===========================================================================
// @ 0x00aa7910
void Self::FUN_00aa7910(void* args)
{
    char* s = raw;
    CArgs* ca = (CArgs*)args;

    // local surface-options block (0x58 bytes)
    union { unsigned int u; float f; } cvt;
    unsigned int opts[0x58 / 4];
    opts[0x00/4] = 0;
    opts[0x08/4] = 0xffffffffu;
    opts[0x0c/4] = 0xffffffffu;
    cvt.f = 1.0f; opts[0x10/4] = cvt.u;
    opts[0x14/4] = cvt.u;
    opts[0x18/4] = 0;
    opts[0x1c/4] = 0;
    opts[0x20/4] = 0;
    opts[0x24/4] = cvt.u;
    opts[0x28/4] = 0;
    opts[0x2c/4] = 0;
    opts[0x30/4] = 0;
    cvt.u = 0xce6e6b28u; opts[0x34/4] = cvt.u;
    opts[0x38/4] = 0xffffffffu;
    opts[0x3c/4] = 0xffffffffu;
    opts[0x40/4] = 0;
    opts[0x44/4] = 0;
    opts[0x48/4] = 0;

    void* mainArgs = ca->MainArguments(1);

    if (ca->HasFlag(DAT_014119cc) != 0) {
        char* iv = *(char**)(s + 0xc);
        int end   = *(int*)(iv + 0x1b8);
        int begin = *(int*)(iv + 0x1b4);
        int r = FUN_00a87470(end, end, begin);
        ((XOp*)(iv + 0x1b4))->FUN_00a87300(r, *(int*)(iv + 0x1b8));
        int diff = end - begin;
        int q = diff / 0x58;
        *(int*)(iv + 0x1b8) += q * 0x58;
    }

    FUN_00a7d280(*(void**)mainArgs, args, opts, *(void**)(*(char**)(s + 0xc) + 0x278));

    {
        char* iv = *(char**)(s + 0xc);
        int  e = *(int*)(iv + 0x1b8);
        int  cap = *(int*)(iv + 0x1bc);
        if ((unsigned)e < (unsigned)cap) {
            *(int*)(iv + 0x1b8) = e + 0x58;
            if (e != 0)
                ((XOp*)e)->FUN_00a87280(opts);
        } else {
            ((XOp*)(iv + 0x1b4))->FUN_00a87d20((void*)e, opts);
        }
        *(unsigned int*)(iv + 0x10) |= 0x1000u;
    }

    {
        int p = (int)opts[0x40/4];
        if (p != 0 && *(int*)(p - 4) != 0)
            operator_delete__((void*)p);
    }
}

// ===========================================================================
// @ 0x00aa7a80
void Self::FUN_00aa7a80(void* args)
{
    char* s = raw;
    CArgs* ca = (CArgs*)args;
    int count = 0;
    char cmdspace[0x260];

    void* puVar2 = ca->MainArgumentsX(&count, 1, 3);

    const char* pcVar1 = *(const char**)puVar2;
    const char* pcVar3;
    do { pcVar3 = pcVar1; pcVar1 = pcVar3 + 1; } while (*pcVar3 != '\0');

    ((StrAssign*)(s + 0x2b8))->FUN_00454cb0(*(const char**)puVar2, pcVar3);

    void* cmd = ((CmdObj*)cmdspace)->FUN_00aa3460();
    ((Self*)(s + 0x40))->FUN_00aa7470((const Self*)cmd);
    ((CmdObj*)cmdspace)->FUN_00aa32f0();

    s[0x2c8] = 0;
    s[0x2c9] = 0;

    if (count > 1) {
        void* desc = ((Parser*)(*(void**)(s + 0x30)))->FUN_00a6f090(puVar2, count, *(void**)(s + 0x34));
        if (desc != 0)
            ((Self*)(s + 0x40))->FUN_00aa7470((const Self*)desc);
    }

    void* o = *(void**)(s + 4);
    ((void(__thiscall*)(void*, void*))VTP(o, 0x8c))(o, this);
}

// ===========================================================================
// @ 0x00aa7b30
void __cdecl FUN_00aa7b30(void* stream, int unused, char* dst)
{
    (void)unused;
    int tmp;
    FUN_0093a780(stream, &tmp, 1, 0);
    *(int*)(dst + 8) = 0;
    *(unsigned int*)(dst + 0xc) = (unsigned int)tmp & 3;
    FUN_0093a780(stream, &tmp, 1, 0);
    *(unsigned int*)(dst + 8) |= (unsigned int)tmp;
    *(unsigned int*)(dst + 0xc) = *(unsigned int*)(dst + 0xc);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x10, 8);
    FUN_0093a780(stream, dst + 0x18, 1, 0);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x1c, 8);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x24, 8);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x2c, 0xc);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x38, 0xc);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x44, 8);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x4c, 0xc);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x58, 0xc);
    FUN_0093a780(stream, dst + 0x64, 1, 0);
    FUN_007d27d0(stream, dst + 0x68);
    FUN_0093a780(stream, dst + 0x7c, 1, 0);
    FUN_0093a700(stream, dst + 0x80, 1, 0);
    FUN_0093a780(stream, dst + 0x84, 1, 0);
    FUN_007d27d0(stream, dst + 0x88);
    FUN_0093a780(stream, dst + 0x9c, 1, 0);
    FUN_007d27d0(stream, dst + 0xa0);
    FUN_0093a780(stream, dst + 0xb4, 1, 0);
    FUN_0093a780(stream, dst + 0xcc, 1, 0);
    FUN_0093a780(stream, dst + 0xd0, 1, 0);
    FUN_007d27d0(stream, dst + 0xb8);
    FUN_007d27d0(stream, dst + 0xf4);
    FUN_0093a780(stream, dst + 0x108, 1, 0);
    FUN_007ed920(stream, dst + 0xd4);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0xe8, 0xc);
    FUN_00a85b00(stream, dst + 0x110);
    FUN_0093a6c0(stream, dst + 0x130, 1);
    FUN_0093a6c0(stream, dst + 0x131, 1);
    FUN_0093a6c0(stream, dst + 0x132, 1);
    FUN_0093a6c0(stream, dst + 0x133, 1);
    FUN_0093a6c0(stream, dst + 0x134, 1);
    FUN_0093a6c0(stream, dst + 0x135, 1);
    FUN_0093a6c0(stream, dst + 0x136, 1);
    FUN_0093a6c0(stream, dst + 0x137, 1);
    FUN_0093a780(stream, dst + 0x138, 1, 0);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x13c, 0xc);
    FUN_0093a780(stream, dst + 0x148, 1, 0);
    FUN_0093a780(stream, dst + 0x14c, 1, 0);
    FUN_0093a780(stream, dst + 0x150, 1, 0);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x154, 0xc);
    FUN_0093a780(stream, dst + 0x160, 1, 0);
    FUN_0093a780(stream, dst + 0x164, 1, 0);
    FUN_0093a780(stream, dst + 0x168, 1, 0);
    FUN_00a9a870(stream, dst + 0x16c);
    FUN_0093a6c0(stream, dst + 0x180, 1);
    FUN_0093a6c0(stream, dst + 0x181, 1);
    FUN_0093a6c0(stream, dst + 0x182, 1);
    FUN_0093a6c0(stream, dst + 0x183, 1);
    FUN_007ed920(stream, dst + 0x184);
    FUN_007d27d0(stream, dst + 0x198);
    FUN_00a87f50(stream, dst + 0x1ac);
    FUN_0093a780(stream, dst + 0x1c0, 1, 0);
    FUN_0093a780(stream, dst + 0x1c4, 1, 0);
    FUN_0093a780(stream, dst + 0x1c8, 1, 0);
    FUN_0093a780(stream, dst + 0x1cc, 1, 0);
    FUN_0093a780(stream, dst + 0x1d0, 1, 0);
    FUN_0093a780(stream, dst + 0x1d4, 1, 0);
    FUN_0093a780(stream, dst + 0x1d8, 1, 0);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x1dc, 8);
    FUN_0093a800(stream, dst + 0x1e8, 1, 0);
    FUN_0093a800(stream, dst + 0x1f0, 1, 0);
    FUN_0093a800(stream, dst + 0x1f8, 1, 0);
    FUN_00a7b9a0(stream, dst + 0x200);
    ((void(__thiscall*)(void*, void*, int))VTP(stream, 0x30))(stream, dst + 0x234, 0xc);
    FUN_00a7ba10(stream, dst + 0x240);
    FUN_00a9a8d0(stream, dst + 0x25c);
}

// ===========================================================================
// @ 0x00aa7fb0
bool Self::FUN_00aa7fb0(int param_2, int* param_3, int param_4)
{
    char* s = raw;

    if (param_2 == 0) {
        if (param_4 > 1 && param_3[1] != (int)*(unsigned char*)(*(int*)(s + 0x1c) + 0x131))
            return true;
        int v = *param_3;
        int hi = v >> 31;
        if (*(int*)(s + 0x1d0) == v && *(int*)(s + 0x1d4) == hi)
            return true;
        *(int*)(s + 0x1d0) = v;
        *(int*)(s + 0x1d4) = 0;
        if (*(int*)(s + 0x228) < 0)
            return true;

        void* p = *(void**)(s + 0x24);
        void* q = ((void*(__thiscall*)(void*))VTP(p, 0x20))(p);
        ((void(__thiscall*)(void*, int))VTP(q, 0x30))(q, *(int*)(s + 0x228));

        char blk[0x20];
        {
            const char* src = (const char*)(*(int*)(s + 0x1c) + 0x110);
            int i;
            for (i = 0; i < 8; i++)
                ((int*)blk)[i] = ((const int*)src)[i];
        }
        unsigned char tag9 = (unsigned char)blk[9];
        int ecx = *(int*)(s + 0x1d4);
        *(int*)(blk + 0) = v;
        *(int*)(blk + 4) = ecx;
        blk[8] = 9;
        if (tag9 == 0x0f) {
            void* a = ((void*(__thiscall*)(void*))VTP(*(void**)(s + 0x24), 0x30))(*(void**)(s + 0x24));
            void* b = ((void*(__thiscall*)(void*))VTP(a, 0x14))(a);
            char c9 = blk[8];
            int a2 = *(int*)(blk + 8);
            int a3 = *(int*)(blk + 4);
            ((void(__thiscall*)(void*, int, int, char))VTP(b, 0x24))(b, a3, a2, c9);
            blk[8] = *(char*)&c9;
        }

        void* iVar8 = ((char*)this - 8) ? (void*)((char*)this - 4) : 0;
        char cVar4 = ((char(__thiscall*)(void*, void*, void*, void*))VTP(q, 0x2c))(q, iVar8, blk, s + 0x228);
        if (cVar4 != 0) {
            char tag = blk[8];
            ((void(__thiscall*)(void*, int, void*))VTP(q, 0x10))(q, (int)tag, s + 0x230);
            s[0x234] = tag;
            if (s[0xc] == 0) return true;
            if (s[0xe] == 0) return true;
            ((void(__thiscall*)(void*, int, int))VTP(q, 0x38))(q, *(int*)(s + 0x228), 1);
            return true;
        }
        *(int*)(s + 0x228) = 0xffffffff;
        return true;
    }

    if (param_2 == 1) {
        if (param_4 > 1 && param_3[1] != (int)*(unsigned char*)(*(int*)(s + 0x1c) + 0x131))
            return true;
        int v = *param_3;
        int hi = v >> 31;
        if (*(int*)(s + 0x1d0) == v && *(int*)(s + 0x1d4) == hi)
            return true;
        *(int*)(s + 0x1d0) = v;
        *(int*)(s + 0x1d4) = 0;
        if (*(int*)(s + 0x22c) < 0)
            return true;

        void* p = *(void**)(s + 0x24);
        void* q = ((void*(__thiscall*)(void*))VTP(p, 0x20))(p);
        ((void(__thiscall*)(void*, int))VTP(q, 0x1c))(q, *(int*)(s + 0x22c));

        char* base = (char*)(*(int*)(s + 0x1c));
        char* src110 = base + 0x110;
        int uvar2 = *(int*)(s + 0x1d0);
        unsigned int uvar3 = *(unsigned int*)(s + 0x1d4);

        char blk[0x20];
        {
            int i;
            for (i = 0; i < 8; i++)
                ((int*)blk)[i] = ((const int*)src110)[i];
        }
        int e1 = uvar2, e2 = (int)uvar3;
        if ((uvar2 & uvar3) != 0xffffffffu) {
            e1 = uvar2; e2 = (int)uvar3;
        } else {
            e1 = *(int*)(blk + 0);
        }
        unsigned char tag9 = (unsigned char)blk[9];
        blk[8] = 0;
        if (tag9 == 0x0f) {
            if (((*(unsigned int*)(blk + 0x18) & *(unsigned int*)(blk + 0x1c)) != 0xffffffffu) &&
                ((uvar2 & uvar3) != 0xffffffffu)) {
                *(int*)(blk + 0x18) = uvar2;
                *(int*)(blk + 0x1c) = (int)uvar3;
                e1 = *(int*)(src110 + 0);
                e2 = *(int*)(src110 + 4);
            }
            void* a = ((void*(__thiscall*)(void*))VTP(*(void**)(s + 0x24), 0x30))(*(void**)(s + 0x24));
            void* b = ((void*(__thiscall*)(void*))VTP(a, 0x14))(a);
            char c9 = blk[8];
            int a2 = *(int*)(blk + 8);
            int a3 = *(int*)(blk + 4);
            ((void(__thiscall*)(void*, int, int, char))VTP(b, 0x24))(b, a3, a2, c9);
            blk[8] = *(char*)&c9;
        }
        int* endp = (int*)(s + 0x22c);
        if ((e1 | e2) != 0) {
            char cVar4 = ((char(__thiscall*)(void*, void*, void*, void*))VTP(q, 0x18))(q, (char*)this - 8, blk, endp);
            if (cVar4 != 0) {
                char tag = blk[8];
                ((void(__thiscall*)(void*, int, void*))VTP(q, 0x10))(q, (int)tag, s + 0x230);
                s[0x234] = tag;
                if (s[0xc] == 0) return true;
                if (s[0xe] == 0) return true;
                ((void(__thiscall*)(void*, int, int))VTP(q, 0x24))(q, *endp, 1);
                return true;
            }
        }
        *endp = 0xffffffff;
        return true;
    }

    if (param_2 == 2) {
        *(int*)(s + 0x17c) = *param_3;
        return true;
    }

    return false;
}

// ===========================================================================
// @ 0x00aa82e0
void Self::FUN_00aa82e0(char param_2)
{
    char* s = raw;
    s[0xe] = param_2;
    if (param_2 != 0) {
        *(int*)(s + 0x130) = *(int*)(s + 0xc4);
        *(int*)(s + 0x134) = *(int*)(s + 0xc8);
        *(int*)(s + 0x138) = *(int*)(s + 0xcc);
    }
    if (s[0xc] != 0) {
        if (*(int*)(s + 0x22c) >= 0) {
            void* p = *(void**)(s + 0x24);
            void* q = ((void*(__thiscall*)(void*))VTP(p, 0x20))(p);
            ((void(__thiscall*)(void*, int, char))VTP(q, 0x24))(q, *(int*)(s + 0x22c), s[0xe]);
            return;
        }
        if (*(int*)(s + 0x228) >= 0) {
            void* p = *(void**)(s + 0x24);
            void* q = ((void*(__thiscall*)(void*))VTP(p, 0x20))(p);
            ((void(__thiscall*)(void*, int, char))VTP(q, 0x38))(q, *(int*)(s + 0x228), s[0xe]);
        }
    }
}

// ===========================================================================
// @ 0x00aa8370
void Self::FUN_00aa8370(int param_2)
{
    char* s = raw;
    void* fn = DAT_016793a0[*(unsigned char*)(s + 0x23c)];
    if (fn != 0)
        ((void(__cdecl*)(void*, int, void*))fn)(this, param_2, s + 0x238);
    ++*(unsigned short*)(s + 0x144);
}

// ===========================================================================
// @ 0x00aa7fa0
void __cdecl FUN_00aa7fa0(int index, int value)
{
    DAT_015655dc[index] = value;
}
