// Slice s0052f170: ArgScript skin-paint "distribute" commands (/Od /Ob1 /MD /Gy /TP /arch:SSE).
#include "types.h"
#include <stdarg.h>

inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void  operator delete(void* p);

// ---------------------------------------------------------------- ArgScript
namespace EA { namespace ArgScript {
struct cArguments {
    static void* MainArguments(cArguments* self, ...);
    static void* OptionArguments(cArguments* self, const char* name, int count);
    static unsigned char HasFlag(cArguments* self, const char* name);
};
struct cBlockCommandBase { virtual ~cBlockCommandBase(); };
struct cEffectsParser;
}}

using EA::ArgScript::cArguments;
using EA::ArgScript::cBlockCommandBase;

void  ErrorString(void* out, const char* fmt, ...);           // 0x0052df30
void  CxxThrowException(void*, void*);                        // _CxxThrowException
extern void* g_TI_cError;                                     // ThrowInfo
void  EastlStringAssign(void* str, const char* first, const char* last);
void  FUN_0047d390(void* first, void* last);
void* FUN_0052ea60();
void  FUN_0052eb40();
void  FUN_0052fb20(int);
void  FUN_0052fc10b();
void  FUN_0052fd80b();
void* FUN_0052fc10(void* self, int src);                      // 0x0052fc10
void  FUN_00530870(void*);
void  FUN_00530770(void*);
void  FUN_00a6f9c0(void*, int, void*);
int   GetInheritedDescription(void* parser, void* args, int n, int id);
void  AddAnonDescription(void* parser, void* args, int id, void* obj, int flag);
void  AddDescription(void* parser, void* args, void* name, int id, int flag);
void  ReleaseObj(void* p);
int   ParseRangedFloatI(void* self, void* arg, int lo, int hi);   // returns int/float
float ParseRangedFloatF(void* self, void* arg, int lo, int hi);
void  CosI(float x);
float GetCos();

// raw thiscall helpers for the many virtuals used here
typedef void* (__thiscall *VFn1)(void*, void*);
typedef int   (__thiscall *VFnI)(void*, void*);

// @ 0x0052f170  cSPSkinPaintDistributeParticlesCommand::OnEndParse
void DistributeParticles_OnEndParse(int param_1)
{
    void* cmd = *(void**)(param_1 + 0xc);
    int count = (int)((*(int*)((char*)cmd + 0x78) - *(int*)((char*)cmd + 0x74)) >> 3);
    if (count < 1) {
        char buf[16];
        ErrorString(buf, "no particles specified\n");
        CxxThrowException(buf, &g_TI_cError);
    }
    if (*(char*)((char*)cmd + 0x88) == 0) {
        float total = 0.0f;
        int nNeg = 0;
        for (int i = 0; i < count; i++) {
            float p = *(float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8);
            if (p < 0.0f) nNeg++;
            else total += p;
        }
        if (1.0001f < total) {
            char buf[16];
            ErrorString(buf, "total selection probability is greater than 1.0\n");
            CxxThrowException(buf, &g_TI_cError);
        }
        for (int i = 0; i < count; i++) {
            float* p = (float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8);
            if (*p <= 0.0f && *p != 0.0f)
                *p = (1.0f - total) / (float)nNeg;
        }
        float acc = 0.0f;
        for (int i = 0; i < count; i++) {
            acc += *(float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8);
            *(float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8) = acc;
        }
    }
}

// @ 0x0052f330  cSPSkinPaintDistributeSpacingCommand::Execute
void DistributeSpacing_Execute(int param_1, cArguments* args)
{
    void** p = (void**)cArguments::MainArguments(args, 1);
    VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x98);
    float v = (float)fn((void*)*(int*)(param_1 + 4), *p);
    *(float*)(*(int*)(param_1 + 0xc) + 0x54) = v;
    *(unsigned char*)(*(int*)(param_1 + 0xc) + 0x72) = cArguments::HasFlag(args, "cover");
    *(unsigned char*)(*(int*)(param_1 + 0xc) + 0x73) = cArguments::HasFlag(args, "ordered");
}

// @ 0x0052f3a0  distribute <limit> command
void DistributeLimit_Execute(int param_1, cArguments* args)
{
    void** p = (void**)cArguments::MainArguments(args, 1);
    VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x9c);
    int v = fn((void*)*(int*)(param_1 + 4), *p);
    *(int*)(*(int*)(param_1 + 0xc) + 0x58) = v;
}

// @ 0x0052f3f0  cSPSkinPaintDistributeRegionCommand::Execute
void DistributeRegion_Execute(int param_1, cArguments* args)
{
    cArguments::MainArguments(args, 0);
    int cmd = *(int*)(param_1 + 0xc);
    *(uint32_t*)(cmd + 0x5c) = 0;
    if (cArguments::HasFlag(args, "torso")) *(uint32_t*)(cmd + 0x5c) |= 1;
    if (cArguments::HasFlag(args, "limbs")) *(uint32_t*)(cmd + 0x5c) |= 2;
    if (cArguments::HasFlag(args, "parts")) *(uint32_t*)(cmd + 0x5c) |= 4;
    if (cArguments::HasFlag(args, "joints")) *(uint32_t*)(cmd + 0x5c) |= 0x20;
    void** o = (void**)cArguments::OptionArguments(args, (const char*)0x013f251c, 1);
    if (o) {
        *(uint32_t*)(cmd + 0x5c) |= 8;
        ParseRangedFloatI(*(void**)(param_1 + 4), *o, 0, 0x40000000);
        CosI(0);
        *(float*)(cmd + 0x60) = GetCos();
    }
    o = (void**)cArguments::OptionArguments(args, "belly", 1);
    if (o) {
        *(uint32_t*)(cmd + 0x5c) |= 0x10;
        ParseRangedFloatI(*(void**)(param_1 + 4), *o, 0, 0x40000000);
        CosI(0);
        *(float*)(cmd + 0x64) = -GetCos();
    }
    o = (void**)cArguments::OptionArguments(args, "bodyRange", 2);
    if (o == 0) {
        *(uint32_t*)(cmd + 0x68) = 0;
        *(uint32_t*)(cmd + 0x6c) = 0x3f800000;
    } else {
        *(float*)(cmd + 0x68) = ParseRangedFloatF(*(void**)(param_1 + 4), *o, 0, 0x3f800000);
        int cmd2 = *(int*)(param_1 + 0xc);
        *(float*)(cmd2 + 0x6c) = ParseRangedFloatF(*(void**)(param_1 + 4), o[1], 0, 0x3f800000);
    }
    *(unsigned char*)(cmd + 0x71) = cArguments::HasFlag(args, "centerOnly");
    *(unsigned char*)(cmd + 0x70) = cArguments::HasFlag(args, "inverse");
}

// @ 0x0052f6b0  SWARM_SPSkinPaintDistributeAddCommands
void SPSkinPaintDistributeAddCommands(int* a, int* b)
{
    void* obj = operator new(0x9c, "ArgScript/SPSkinPaintDistributeEffect", 0, 0, 0, 0);
    void* effect = obj ? (void*)FUN_0052ea60() : 0;
    (*(void(__thiscall**)(int*, void*, void*))(*(int*)b + 0x14))(b, (void*)0x0150cb48, effect);
    void* cmd = operator new(0x10, "ArgScript/SPSkinPaintDistributeInline", 0, 0, 0, 0);
    if (cmd) {
        // cCommandBase ctor + vtable fixes
        *(void**)cmd = (void*)0x013f1ffc;
        *(void**)cmd = (void*)0x013f1ffc;
        *(void**)cmd = (void*)0x013f2544;
    }
    (*(void(__thiscall**)(int*, void*, void*))(*(int*)a + 0x18))(a, (void*)0x0150cb48, cmd);
}

// @ 0x0052f7c0  cSPSkinPaintDistributeEffectCommand ctor
void* DistributeEffectCommandCtor(void* self)
{
    *(void**)self = (void*)0x013f25ac;
    FUN_0052ea60();
    int* p = (int*)((char*)self + 0x8c);
    p[0] = 0; p[1] = 0; p[2] = 0;
    p[0] = (int)&g_TI_cError;
    p[1] = p[0];
    p[2] = p[0] + 1;
    return self;
}

// @ 0x0052f890  distribute block parse
void DistributeBlock_Parse(int param_1, cArguments* args)
{
    int n = 0;
    void** p = (void**)cArguments::MainArguments(args, &n, 1, 3);
    char* s = (char*)*p;
    char* e = s;
    while (*e) e++;
    EastlStringAssign((void*)*p, s, e);
    int* str = (int*)(param_1 + 0x40);
    if (*str != *(int*)(param_1 + 0x44)) {
        *(char*)*str = 0;
        *(int*)(param_1 + 0x44) = *str;
    }
    *(uint32_t*)(param_1 + 0x50) = 0xffffffff;
    *(uint32_t*)(param_1 + 0x54) = 0x3e4ccccd;
    *(uint32_t*)(param_1 + 0x58) = 0xffffffff;
    *(uint32_t*)(param_1 + 0x5c) = 0xffffffff;
    *(unsigned char*)(param_1 + 0x70) = 0;
    *(unsigned char*)(param_1 + 0x71) = 0;
    *(unsigned char*)(param_1 + 0x72) = 0;
    *(unsigned char*)(param_1 + 0x73) = 0;
    FUN_0047d390(*(void**)(param_1 + 0x74), *(void**)(param_1 + 0x78));
    *(unsigned char*)(param_1 + 0x88) = 0;
    if (1 < n) {
        int d = GetInheritedDescription(*(void**)(param_1 + 0x30), p, n, 0x23);
        if (d) FUN_0052fb20(d);
    }
    (*(void(__thiscall**)(int, int))(*(int*)(*(int*)(param_1 + 4)) + 0x8c))(*(int*)(param_1 + 4), param_1);
}

// @ 0x0052f9f0  add named/anonymous effect to swarm description
void Distribute_AddEffect(int param_1, char param_2)
{
    if (param_2 == 0) {
        int obj = (int)operator new(0x54, "Swarm/SkinPaint", 0, 0, 0, 0);
        void* made = obj ? FUN_0052fc10((void*)0, param_1 + 0x38) : 0;
        FUN_00a6f9c0(*(void**)(param_1 + 0x8c), 0x23, made);
    }
    int* str = (int*)(param_1 + 0x8c);
    if (*str != *(int*)(param_1 + 0x90)) {
        *(char*)*str = 0;
        *(int*)(param_1 + 0x90) = *str;
    }
}

// @ 0x0052fb00
void __fastcall BlockCmdBaseDerivedDtor(cBlockCommandBase* p)
{
    p->~cBlockCommandBase();
}

// @ 0x0052fb20  copy effect params
int Distribute_CopyParams(int param_1, int param_2)
{
    if ((void*)(param_2 + 8) != (void*)(param_1 + 8))
        EastlStringAssign(*(void**)(param_2 + 8), *(const char**)(param_2 + 8), *(const char**)(param_2 + 0xc));
    *(uint32_t*)(param_1 + 0x18) = *(uint32_t*)(param_2 + 0x18);
    *(uint32_t*)(param_1 + 0x1c) = *(uint32_t*)(param_2 + 0x1c);
    *(uint32_t*)(param_1 + 0x20) = *(uint32_t*)(param_2 + 0x20);
    *(uint32_t*)(param_1 + 0x24) = *(uint32_t*)(param_2 + 0x24);
    *(uint32_t*)(param_1 + 0x28) = *(uint32_t*)(param_2 + 0x28);
    *(uint32_t*)(param_1 + 0x2c) = *(uint32_t*)(param_2 + 0x2c);
    *(uint32_t*)(param_1 + 0x30) = *(uint32_t*)(param_2 + 0x30);
    *(uint32_t*)(param_1 + 0x34) = *(uint32_t*)(param_2 + 0x34);
    *(unsigned char*)(param_1 + 0x38) = *(unsigned char*)(param_2 + 0x38);
    *(unsigned char*)(param_1 + 0x39) = *(unsigned char*)(param_2 + 0x39);
    *(unsigned char*)(param_1 + 0x3a) = *(unsigned char*)(param_2 + 0x3a);
    *(unsigned char*)(param_1 + 0x3b) = *(unsigned char*)(param_2 + 0x3b);
    FUN_00530870((void*)(param_2 + 0x3c));
    *(unsigned char*)(param_1 + 0x50) = *(unsigned char*)(param_2 + 0x50);
    return param_1;
}

// @ 0x0052fc10  skin-paint swarm effect (copy) ctor
void* Distribute_EffectCtor(void* self, int src)
{
    *(void**)self = (void*)0x013f22dc;
    *(uint32_t*)((char*)self + 4) = 0;
    *(uint32_t*)((char*)self + 8) = 0;
    *(uint32_t*)((char*)self + 0xc) = 0;
    *(uint32_t*)((char*)self + 0x10) = 0;
    FUN_0047d390(*(void**)(src + 8), *(void**)(src + 0xc));
    *(uint32_t*)((char*)self + 0x18) = *(uint32_t*)(src + 0x18);
    *(uint32_t*)((char*)self + 0x1c) = *(uint32_t*)(src + 0x1c);
    *(uint32_t*)((char*)self + 0x20) = *(uint32_t*)(src + 0x20);
    *(uint32_t*)((char*)self + 0x24) = *(uint32_t*)(src + 0x24);
    *(uint32_t*)((char*)self + 0x28) = *(uint32_t*)(src + 0x28);
    *(uint32_t*)((char*)self + 0x2c) = *(uint32_t*)(src + 0x2c);
    *(uint32_t*)((char*)self + 0x30) = *(uint32_t*)(src + 0x30);
    *(uint32_t*)((char*)self + 0x34) = *(uint32_t*)(src + 0x34);
    *(unsigned char*)((char*)self + 0x38) = *(unsigned char*)(src + 0x38);
    *(unsigned char*)((char*)self + 0x39) = *(unsigned char*)(src + 0x39);
    *(unsigned char*)((char*)self + 0x3a) = *(unsigned char*)(src + 0x3a);
    *(unsigned char*)((char*)self + 0x3b) = *(unsigned char*)(src + 0x3b);
    FUN_00530770((void*)(src + 0x3c));
    *(unsigned char*)((char*)self + 0x50) = *(unsigned char*)(src + 0x50);
    return self;
}

// @ 0x0052fd80
void __fastcall Distribute_CommandDtor(cBlockCommandBase* p)
{
    char* s = *(char**)((char*)p + 0x34);
    if (1 < (int)(*(int*)((char*)p + 0x38) - (int)s)) {
        if (s) {
            void* q = s;
            operator delete(q);
        }
    }
    FUN_0052eb40();
    p->~cBlockCommandBase();
}

// @ 0x0052fe20  cSPSkinPaintDistributeInlineCommand::Execute
void DistributeInline_Execute(int param_1, cArguments* args)
{
    int n = 0;
    void** p = (void**)cArguments::MainArguments(args, &n, 0, 1);
    if (n < 1) {
        int obj = (int)operator new(0x54, "Skinner/Swarm", 0, 0, 0, 0);
        void* made = obj ? FUN_0052ea60() : 0;
        if (made) *(int*)((char*)made + 4) = *(int*)((char*)made + 4) + 1;
        void** pp = (void**)cArguments::OptionArguments(args, "effect", 1);
        if (pp == 0) {
            char buf[16];
            ErrorString(buf, "must specify block name or use inline -effect ... syntax");
            CxxThrowException(buf, &g_TI_cError);
        }
        char* s = (char*)*pp;
        char* e = s;
        while (*e) e++;
        EastlStringAssign((void*)*pp, s, e);
        void** sp = (void**)cArguments::OptionArguments(args, "spacing", 1);
        if (sp) {
            VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x98);
            *(float*)((char*)made + 0x34) = (float)fn((void*)*(int*)(param_1 + 4), *sp);
        }
        void** lp = (void**)cArguments::OptionArguments(args, "limit", 1);
        if (lp) {
            VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x9c);
            *(int*)((char*)made + 0x38) = fn((void*)*(int*)(param_1 + 4), *lp);
        }
        *(unsigned char*)((char*)made + 0x72) = cArguments::HasFlag(args, "cover");
        *(unsigned char*)((char*)made + 0x73) = cArguments::HasFlag(args, "ordered");
        AddAnonDescription(*(void**)(param_1 + 0xc), args, 0x23, made, 0);
        if (made) ReleaseObj(made);
    } else {
        AddDescription(*(void**)(param_1 + 0xc), args, *p, 0x23, 0);
    }
}
