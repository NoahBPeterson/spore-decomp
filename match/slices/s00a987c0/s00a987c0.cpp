// Slice s00a987c0 — EA Swarm / ArgScript "LightEffect" command family.
// Source rebuilt from the retail disassembly.  Functions live in the same TU as
// ArgScript::LightEffect (vtable 0x0145884c) and its 0x58-byte serialisable
// sub-object (vtable 0x01458848, allocated with the name "Swarm").
// flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

// ------------------------------------------------------------------ referenced data
extern unsigned short gEmptyString16[];      // 0x01667bac  (wchar_t empty string)
extern void* g_156522c;                      // 0x0156522c  light parser data slot
extern void* g_1565230;                      // 0x01565230  LightType slot
extern void* g_1565234;                      // 0x01565234  LightLife slot
extern void* g_1565238;                      // 0x01565238  LightColor slot
extern void* g_156523c;                      // 0x0156523c  LightStrength slot
extern void* g_1565240;                      // 0x01565240  LightSize slot
extern void* g_1565244;                      // 0x01565244  LightSpotWidth slot
extern void* g_1565248;                      // 0x01565248  "ambient" enum table

extern const char g_str_LightType[];         // 0x01458974
extern const char g_str_LightLife[];         // 0x01458960
extern const char g_str_LightColor[];        // 0x01458948
extern const char g_str_LightStrength[];     // 0x01458930
extern const char g_str_LightSize[];         // 0x0145891c
extern const char g_str_LightSpotWidth[];    // 0x01458900
extern const char g_str_LightEffect[];       // 0x014589a0
extern const char g_str_GroupLight[];        // 0x01458988
extern const char g_str_ambient[];           // 0x01565248 (table->name)
extern const char g_str_penumbra[];          // 0x014589b8
extern const char g_str_Swarm[];             // 0x013f1fdc
extern const char g_str_EASTL[];             // 0x013f2150
extern const char g_str_allocator[];         // 0x013ebb38

// ------------------------------------------------------------------ external funcs
extern "C" {
void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0xf473a0
void  EADeallocate(void* p);                                                        // 0xf47380
void  operator_delete(void* p);                                                     // 0xf47380
}
void __stdcall ArgScript_Text_SetUserData(void* self, void* p);      // 0xfd9450
void __stdcall ArgScript_cCommandBase_ctor(void* p);                 // 0x83c800
void __stdcall ArgScript_cCommandBase_OnRegister(void* self, void* p1, void* p2); // 0x83c780
const char** __stdcall ArgScript_MainArguments1(void* args, int n);   // 0x838320 (ret 4 -> __stdcall)
const char** __stdcall ArgScript_MainArguments3(void* args, int* count, int a, int b); // 0x838020
void* __stdcall ArgScript_OptionArguments(const void* args, const char* name, int a); // 0x838330
unsigned char __stdcall ArgScript_ParseEnum(const char* s, const void* tbl); // 0x840bb0
void __stdcall Swarm_ScaleCurvePush(void* v0, void* dst, void* src); // 0x007ed1b0-style, ret 8
void __stdcall Vec0C_eraseVec(void* first, void* last, void* tail);  // 0x9e0480 (ret 8)
int  __stdcall EA_IO_WriteUint32(void* stream, const unsigned int* p, unsigned int n, int a); // 0x93aa70
void __stdcall EA_IO_ReadInt32(void* stream, void* out, int a, int b);  // 0x93a780
void __stdcall Swarm_cVisualEffectDescription_ctor(void* p);          // 0x83cdd0 (AppPropsFields base)
void __stdcall Sub_CopyVec3Field(void* dst, void* src);              // 0x6f5cd0 / 0x6f50f0
void __stdcall Sub_VecAssign(void* dst, void* src);                  // 0x50d4e0
void __stdcall Sub_VecResize(void* vec, int n, void* src);           // 0x4aa350
void __stdcall Sub_ElemCtor(void* dst, void* src);                   // 0x6fd140
void __stdcall Sub_ElemDtor(void* dst, void* src);                   // 0x6fd250
void* __stdcall ArgScript_StringAssign(void* dst, const char* begin, const char* end); // 0x454cb0
int  __stdcall Swarm_cEffectsParser_GetInheritedDescription(void* parser, void** argv, int n, int t); // 0xa6f090
void __stdcall DescInstaller_Install(void* self, void* desc, int t, void** s);   // 0xa6f9c0

// ------------------------------------------------------------------ new/alloc helpers
inline void* EAAlloc(unsigned int n, const char* name)
{
    return EAAllocate(n, name, 0, 0, 0, 0);
}

// ------------------------------------------------------------------ 7-float element (0x1c bytes)
struct Elem1C {
    float w[7];
};

// The 0x1c-element eastl::vector (5 words).
struct Elem1CVec {
    Elem1C* mpBegin;
    Elem1C* mpEnd;
    Elem1C* mpCapacity;
    const char* mpName;
    int mpExtra;
};

// ------------------------------------------------------------------ ArgScript::LightEffect sub-object (0x58 bytes)
struct FVec5 {                       // 5-word eastl::vector<float>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    const char* mpName;
    int   mpExtra;
    void assign(const FVec5& src);                       // 0x50d4e0
    void reserve(int n, const char* name);               // 0x4aa350
    float* insert_end(float* first, unsigned int n);     // 0x11e0744
};

struct Vec0C5 {                      // 5-word eastl::vector<3-float element>
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mpName;
    int   mpExtra;
    void assign(const Vec0C5& src);                      // 0x6f5cd0
    void copy_construct(const Vec0C5& src);              // 0x6f50f0
};

struct LightEffectSub {
    void* v00;                       // +0x00
    int   n04;                       // +0x04
    int   n08;                       // +0x08
    unsigned char n0c;               // +0x0c
    float f10;                       // +0x10
    short s14;                       // +0x14
    void* v18a;                      // +0x18 (3-float element storage)
    void* v18b;
    void* v18c;
    float f24;                       // +0x24
    float f28;                       // +0x28
    FVec5 v2c;                       // +0x2c
    FVec5 v40;                       // +0x40
    float f54;                       // +0x54

    LightEffectSub() {}
    LightEffectSub& operator=(const LightEffectSub& src);
    LightEffectSub& copy_construct(const LightEffectSub& src);
    void Read(void* stream, int n);
    void Install(char flag);
};

// ArgScript::LightEffect (0xa0 bytes).
struct LightEffect {
    void* v00;
    int   pad[12];
    void* p34;                       // +0x34
    LightEffectSub sub38;            // +0x38  (0x58 bytes)
    void* s90;                       // +0x90  string begin
    void* s94;                       // +0x94
    int   s98;
    void Install(char flag);
};

// Base for the Light* ArgScript commands (the light sub-data lives at +0xc).
struct ArgCommand {
    void* v00;                       // +0x00
    void* p04;                       // +0x04  parser / manager
    void* v08;                       // +0x08
    void* p0c;                       // +0x0c  light sub-data
    int   pad1[9];                   // +0x10 .. +0x33
    void* p34;                       // +0x34
    LightEffectSub sub38;            // +0x38
    void* s90;                       // +0x90
    void* s94;                       // +0x94
    int   s98;
    void ExecuteType(void* args);
    void ExecuteLife(void* args);
    void ExecuteColor(void* args);
    void ExecuteSize(void* args);
    void ExecuteSpotWidth(void* args);
    void ExecuteEffect(void* args);
    void OnRegister(void* parser, void* state);
};

// ------------------------------------------------------------------ simple vector (5 word, floats)
struct FloatVec {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    const char* mpName;
    int mpExtra;
    void DoInsertValue(float* pos, const float& v);   // 0x00455660 (ret 8)
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { float* p = mpEnd; mpEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mpEnd, v);
    }
};

// ------------------------------------------------------------------ slice targets (declarations)
void AddToScript(void* state, void* parser);
Elem1C* Elem1C_copy_range(Elem1C* dst, Elem1C* first, Elem1C* last);
Elem1C* Elem1C_fill(Elem1C* dst, unsigned int n, const Elem1C* v);
Elem1C* Elem1C_fill_off14(Elem1C* dst, unsigned int n, const Elem1C* v);
void* Elem1C_write_vector(void* stream, Elem1CVec* vec);
void* Elem1C_write_vector2(void* stream, Elem1CVec* vec);
void Elem1C_insert(Elem1CVec* vec, Elem1C* pos, unsigned int n, const Elem1C* v);

// ===========================================================================
static void* MakeCommand(unsigned int sz, const char* name, void* vtbl);
extern void* g_vtbl_LightType;      // 0x01458870
extern void* g_vtbl_LightLife;      // 0x01458888
extern void* g_vtbl_LightColor;     // 0x014588a0
extern void* g_vtbl_LightStrength;  // 0x014588b8
extern void* g_vtbl_LightSize;      // 0x014588d0
extern void* g_vtbl_LightSpotWidth; // 0x014588e8
extern void* g_vtbl_LightEffectSub;  // 0x01458848
void* __stdcall VecCopyRange(void* dst, void* first, unsigned int n);  // 0x11e0744

struct IVtParser {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void AddCommand(void* slot, void* cmd);   // +0x18
};

static void* MakeCommand(unsigned int sz, const char* name, void* vtbl)
{
    unsigned char* p = (unsigned char*)EAAlloc(sz, name);
    if (!p) return 0;
    ArgScript_cCommandBase_ctor(p);
    *(void**)p = vtbl;
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x00a987c0  ArgCommand::OnRegister
// ---------------------------------------------------------------------------
void ArgCommand::OnRegister(void* parser, void* state)
{
    void* sub = (state != 0) ? (void*)((int)state - 0xc) : 0;
    *(void**)((char*)this + 0x30) = sub;
    ArgScript_cCommandBase_OnRegister(this, parser, state);
    ArgScript_Text_SetUserData(this, (char*)this + 0x34);

    IVtParser* vt = (IVtParser*)this;
    vt->AddCommand(g_1565230, MakeCommand(0x10, g_str_LightType,     g_vtbl_LightType));
    vt->AddCommand(g_1565234, MakeCommand(0x10, g_str_LightLife,     g_vtbl_LightLife));
    vt->AddCommand(g_1565238, MakeCommand(0x10, g_str_LightColor,    g_vtbl_LightColor));
    vt->AddCommand(g_156523c, MakeCommand(0x10, g_str_LightStrength, g_vtbl_LightStrength));
    vt->AddCommand(g_1565240, MakeCommand(0x10, g_str_LightSize,     g_vtbl_LightSize));
    vt->AddCommand(g_1565244, MakeCommand(0x10, g_str_LightSpotWidth,g_vtbl_LightSpotWidth));
}

// ---------------------------------------------------------------------------
// @ 0x00a98990  AddToScript
// ---------------------------------------------------------------------------
// eastl::string (4-word) — assign is a __thiscall member.
struct EaString {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mpAlloc;
    void assign(const char* first, const char* last);   // 0x454cb0
};

// cArguments — MainArguments is a __thiscall member.
struct cArguments {
    const char** MainArguments(int n);                      // 0x838320
    const char** MainArguments(int* count, int a, int b);   // 0x838020
};

// cEffectsParser — GetInheritedDescription is a __thiscall member.
struct cEffectsParser {
    int GetInheritedDescription(void** argv, int n, int t);  // 0xa6f090
};

struct IVtScript {    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void AddCommand(void* slot, void* cmd, void* state);   // +0x14
    virtual void AddCommand18(void* slot, void* cmd);              // +0x18
};

extern void* g_vtbl_GroupLight;   // 0x01458830

// thiscall ctor on a freshly-allocated object.
struct CtorHost { void ctor(); };

void AddToScript(void* state, void* parser)
{
    unsigned char* le = (unsigned char*)EAAllocate(0xa0, g_str_LightEffect, 0, 0, 0, 0);
    if (le) ((CtorHost*)le)->ctor();          // ArgScript::LightEffect::LightEffect (0xa98670)
    else    le = 0;
    ((IVtScript*)parser)->AddCommand(g_156522c, le, state);

    unsigned char* cmd = (unsigned char*)EAAllocate(0x10, g_str_GroupLight, 0, 0, 0, 0);
    if (cmd) {
        ((CtorHost*)cmd)->ctor();             // cCommandBase::cCommandBase (0x83c800)
        *(void**)cmd = g_vtbl_GroupLight;
    } else {
        cmd = 0;
    }
    ((IVtScript*)parser)->AddCommand18(g_156522c, cmd);
}

// ---------------------------------------------------------------------------
// @ 0x00a98a80  ArgCommand::ExecuteType
// ---------------------------------------------------------------------------
extern void __stdcall FloatVec_DoInsertValue(float* pos, const float& v); // 0x00455660

void ArgCommand::ExecuteType(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    const char** a = args->MainArguments(1);
    unsigned char e = ArgScript_ParseEnum(a[0], g_str_ambient);
    unsigned char* sub = (unsigned char*)p0c;
    sub[0x10] = e;
    if (sub[0x10] == 4) {
        FloatVec* v = (FloatVec*)(sub + 0x44);
        if (v->mpBegin == v->mpCapacity) {
            v->push_back(1.0f);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a98b00  ArgCommand::ExecuteSize
// ---------------------------------------------------------------------------
extern void __stdcall Vec0C_erase(void* first, void* last);   // 0x9e0480 (ret 8)

// parser vtable: slot 0xb0 -> Vec3 ParseCommand(const char*), returns 3 floats.
struct IVtParser2 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual void   NotifyChanged(void* self);               // +0x8c
    virtual void v90(); virtual void v94();
    virtual float  ParseScalar(const char* s);              // +0x98
    virtual void v9c(); virtual void va0(); virtual void va4(); virtual void va8();
    virtual void vac();
    virtual float* ParseVec3(float* out, const char* s);    // +0xb0
};

// A 3-float (0xc byte) element vector used at sub+0x1c.
struct Vec0C {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    const char* mpName;
    int mpExtra;
};

// 3-float element.
struct Elem0C { float x, y, z; };
struct Elem0CVec {
    Elem0C* mpBegin;
    Elem0C* mpEnd;
    Elem0C* mpCapacity;
    const char* mpName;
    int mpExtra;
};

extern void __stdcall ScaleCurve(Elem0C* pos, const Elem0C* v);   // 0x7ed1b0 (ret 8)

void ArgCommand::ExecuteSize(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    Elem0CVec* v = (Elem0CVec*)(sub + 0x1c);
    Vec0C_erase(v->mpBegin, v->mpEnd);

    for (int i = 0; i < n; ++i) {
        float tmp[3];
        ((IVtParser2*)p04)->ParseVec3(tmp, a[i]);
        Elem0C* p = v->mpEnd;
        if (p < v->mpCapacity) {
            v->mpEnd = p + 1;
            if (p) { p->x = tmp[0]; p->y = tmp[1]; p->z = tmp[2]; }
        } else {
            ScaleCurve(p, (const Elem0C*)tmp);
        }
    }

    unsigned int* flags = (unsigned int*)((unsigned char*)p0c + 0xc);
    if (n > 0) *flags |= 1;
    else       *flags &= ~1u;
}

// ---------------------------------------------------------------------------
// @ 0x00a98bc0  ArgCommand::ExecuteLife
// ---------------------------------------------------------------------------
extern void __stdcall VecClear3(void* vec, void* p1, int zero);   // 0x11e0744

void ArgCommand::ExecuteLife(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    FloatVec* v = (FloatVec*)(sub + 0x30);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    VecClear3(begin, end, 0);
    v->mpEnd = v->mpEnd - (end - begin);

    for (int i = 0; i < n; ++i) {
        float f = ((IVtParser2*)p04)->ParseScalar(a[i]);
        v->push_back(f);
    }

    unsigned int* flags = (unsigned int*)((unsigned char*)p0c + 0xc);
    if (n > 0) *flags |= 2;
    else       *flags &= ~2u;
}

// ---------------------------------------------------------------------------
// @ 0x00a98c90  ArgCommand::ExecuteColor
// ---------------------------------------------------------------------------
void ArgCommand::ExecuteColor(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    FloatVec* v = (FloatVec*)(sub + 0x44);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    VecClear3(begin, end, 0);
    v->mpEnd = v->mpEnd - (end - begin);

    for (int i = 0; i < n; ++i) {
        float f = ((IVtParser2*)p04)->ParseScalar(a[i]);
        v->push_back(f);
    }

    unsigned int* flags = (unsigned int*)((unsigned char*)p0c + 0xc);
    if (n > 0) *flags |= 4;
    else       *flags &= ~4u;
}

// ---------------------------------------------------------------------------
// @ 0x00a98d60  ArgCommand::ExecuteSpotWidth
// ---------------------------------------------------------------------------
void ArgCommand::ExecuteSpotWidth(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    FloatVec* v = (FloatVec*)(sub + 0x44);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    VecClear3(begin, end, 0);
    v->mpEnd = v->mpEnd - (end - begin);

    for (int i = 0; i < n; ++i) {
        float f = ((IVtParser2*)p04)->ParseScalar(a[i]);
        v->push_back(f);
    }

    const char** opt = (const char**)ArgScript_OptionArguments(args, g_str_penumbra, 1);
    if (opt) {
        float f = ((IVtParser2*)p04)->ParseScalar(opt[0]);
        *(float*)((unsigned char*)p0c + 0x58) = f;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a98e40  LightEffectSub_assign
// ---------------------------------------------------------------------------
LightEffectSub& LightEffectSub::operator=(const LightEffectSub& src)
{
    n08 = src.n08;
    n0c = src.n0c;
    f10 = src.f10;
    s14 = src.s14;
    ((Vec0C5*)&v18a)->assign(*(const Vec0C5*)&src.v18a);
    v2c.assign(src.v2c);
    v40.assign(src.v40);
    f54 = src.f54;
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x00a98ea0  LightEffectSub_copyctor
// ---------------------------------------------------------------------------
LightEffectSub& LightEffectSub::copy_construct(const LightEffectSub& src)
{
    n04 = 0;
    v00 = (void*)&g_vtbl_LightEffectSub;             // 0x01458848 placeholder
    n08 = src.n08;
    n0c = src.n0c;
    f10 = src.f10;
    s14 = src.s14;
    ((Vec0C5*)&v18a)->copy_construct(*(const Vec0C5*)&src.v18a);

    v2c.reserve((int)(src.v2c.mpEnd - src.v2c.mpBegin), src.v2c.mpName);
    {
        float* r = v2c.insert_end(src.v2c.mpBegin, (unsigned int)(src.v2c.mpEnd - src.v2c.mpBegin));
        v2c.mpEnd = r;
    }
    v40.reserve((int)(src.v40.mpEnd - src.v40.mpBegin), src.v40.mpName);
    {
        float* r = v40.insert_end(src.v40.mpBegin, (unsigned int)(src.v40.mpEnd - src.v40.mpBegin));
        v40.mpEnd = r;
    }
    f54 = src.f54;
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x00a98f60  ArgCommand::ExecuteEffect
// ---------------------------------------------------------------------------
extern void __stdcall Sub_StringAssign(void* s, const char* begin, const char* end); // 0x454cb0
extern int  __stdcall cEffectsParser_GetInheritedDescription(void* parser, void** argv, int n, int t); // 0xa6f090

void ArgCommand::ExecuteEffect(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int argc;
    const char** a = args->MainArguments(&argc, 1, 3);

    const char* p = a[0];
    const char* e = p;
    const char* q = p + 1;
    while (*e++) { }
    const char* end = p + (e - q);
    ((EaString*)((char*)this + 0x90))->assign(p, end);

    if (argc > 1) {
        int desc = ((cEffectsParser*)*(void**)((char*)this + 0x30))->GetInheritedDescription((void**)a, argc, 10);
        if (desc) sub38.operator=(*(const LightEffectSub*)desc);
    }

    ((IVtParser2*)p04)->NotifyChanged(this);
}

struct DescInstaller {
    void Install(void* str, int t, void* desc);   // 0xa6f9c0 (thiscall: ecx=installer)
};

// ---------------------------------------------------------------------------
// @ 0x00a98fd0  LightEffect::Install
// ---------------------------------------------------------------------------
void LightEffect::Install(char flag)
{
    unsigned char* s = (unsigned char*)this;
    if (flag == 0) {
        void* p = EAAlloc(0x58, g_str_Swarm);
        void* d = p ? &((LightEffectSub*)p)->copy_construct(*(const LightEffectSub*)(s + 0x38)) : 0;
        ((DescInstaller*)*(void**)(s + 0x30))->Install(*(void**)(s + 0x90), 10, d);
    }
    if (*(unsigned char**)(s + 0x90) != *(unsigned char**)(s + 0x94)) {
        **(unsigned char**)(s + 0x90) = 0;
        *(void**)(s + 0x94) = *(void**)(s + 0x90);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a99040  LightEffectSub_Read
// ---------------------------------------------------------------------------
extern void Sub_ReadInt32(void* stream, void* out, int a, int b);  // 0x93a780
extern void Sub_ReadInt8(void* stream, void* out, int n);          // 0x93a6c0
extern void Sub_ReadByte(void* stream, void* out, int n, int a);   // 0x93a700
extern void Sub_ReadVec0C(void* stream, void* dst);                // 0x7ed920
extern void Sub_ReadFVec(void* stream, void* dst);                 // 0x7d27d0

void LightEffectSub_Read(void* stream, int n, LightEffectSub* self)
{
    unsigned char* s = (unsigned char*)self;
    unsigned int tmp;
    Sub_ReadInt32(stream, &tmp, 1, 0);
    *(int*)(s + 0x08) = (int)(tmp & 0xf);
    Sub_ReadInt8(stream, s + 0x0c, 1);
    if (n > 1) {
        Sub_ReadInt32(stream, s + 0x10, 1, 0);
        Sub_ReadByte(stream, s + 0x14, 1, 0);
    }
    Sub_ReadVec0C(stream, s + 0x18);
    Sub_ReadFVec(stream, s + 0x2c);
    Sub_ReadFVec(stream, s + 0x40);
    Sub_ReadInt32(stream, s + 0x54, 1, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00a990d0  LightEffectSub_CreateAndRead
// ---------------------------------------------------------------------------
LightEffectSub* LightEffectSub_CreateAndRead(void* stream, int n)
{
    unsigned char* p = (unsigned char*)EAAllocate(0x58, g_str_Swarm, 0, 0, 0, 0);
    unsigned char* sub = 0;
    if (p) {
        *(int*)(p + 0x04)   = 0;
        *(void**)p          = (void*)&g_vtbl_LightEffectSub;
        *(int*)(p + 0x08)   = 0;
        *(float*)(p + 0x10) = 1.0f;
        *(p + 0x0c)         = 1;
        *(short*)(p + 0x14) = 0;
        *(int*)(p + 0x18)   = 0;
        *(int*)(p + 0x1c)   = 0;
        *(int*)(p + 0x20)   = 0;
        *(int*)(p + 0x2c)   = 0;
        *(int*)(p + 0x30)   = 0;
        *(int*)(p + 0x34)   = 0;
        *(int*)(p + 0x40)   = 0;
        *(int*)(p + 0x44)   = 0;
        *(int*)(p + 0x48)   = 0;
        *(float*)(p + 0x54) = 0.0f;
        sub = p;
    }
    LightEffectSub_Read(stream, n, (LightEffectSub*)sub);
    return (LightEffectSub*)sub;
}

// ===========================================================================
// 0x1c-byte element vector helpers
// ===========================================================================
extern void __stdcall Elem1C_Write1(void* stream, void* elem);   // 0xa79710
extern void __stdcall Elem1C_Write2(void* stream, void* elem);   // 0xa797a0
extern void __stdcall Elem1C_Dtor(void* first, void* last, void* cap); // 0x6fd250
extern void __stdcall Elem1C_DtorAndFill(void* dst, void* end, const Elem1C* v); // 0x6fd140

// ---------------------------------------------------------------------------
// @ 0x00a99190  Elem1C_copy_range
// ---------------------------------------------------------------------------
Elem1C* Elem1C_copy_range(Elem1C* dst, Elem1C* first, Elem1C* last)
{
    Elem1C* s = first;
    if (s != last) {
        Elem1C* d = dst;
        do {
            if (d) {
                d->w[0]=s->w[0]; d->w[1]=s->w[1]; d->w[2]=s->w[2];
                d->w[3]=s->w[3]; d->w[4]=s->w[4]; d->w[5]=s->w[5]; d->w[6]=s->w[6];
            }
            ++s; ++d;
        } while (s != last);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00a991f0  Elem1C_fill
// ---------------------------------------------------------------------------
Elem1C* Elem1C_fill(Elem1C* dst, unsigned int n, const Elem1C* v)
{
    if (n && dst) {
        Elem1C* d = dst;
        do {
            d->w[0]=v->w[0]; d->w[1]=v->w[1]; d->w[2]=v->w[2];
            d->w[3]=v->w[3]; d->w[4]=v->w[4]; d->w[5]=v->w[5]; d->w[6]=v->w[6];
            --n; ++d;
        } while (n);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00a99240  Elem1C_fill_off14 (copies from +0x14 of the source element)
// ---------------------------------------------------------------------------
Elem1C* Elem1C_fill_off14(Elem1C* dst, unsigned int n, const Elem1C* v)
{
    if (n && dst) {
        float* src = (float*)v;
        Elem1C* d = dst;
        do {
            d->w[0]=src[0]; d->w[1]=src[1]; d->w[2]=src[2];
            d->w[3]=src[3]; d->w[4]=src[4]; d->w[5]=src[5]; d->w[6]=src[6];
            --n; ++d;
        } while (n);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00a99290  Elem1C_write_vector
// ---------------------------------------------------------------------------
void* Elem1C_write_vector(void* stream, Elem1CVec* vec)
{
    int n = (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x1c);
    EA_IO_WriteUint32(stream, (const unsigned int*)&n, 1, 0);
    if (n) {
        int off = 0;
        int c = n;
        do {
            Elem1C_Write1(stream, (char*)vec->mpBegin + off);
            off += 0x1c;
            --c;
        } while (c);
    }
    return stream;
}

// ---------------------------------------------------------------------------
// @ 0x00a992f0  Elem1C_write_vector2
// ---------------------------------------------------------------------------
void* Elem1C_write_vector2(void* stream, Elem1CVec* vec)
{
    int n = (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x1c);
    EA_IO_WriteUint32(stream, (const unsigned int*)&n, 1, 0);
    if (n) {
        int off = 0;
        int c = n;
        do {
            Elem1C_Write2(stream, (char*)vec->mpBegin + off);
            off += 0x1c;
            --c;
        } while (c);
    }
    return stream;
}

// ---------------------------------------------------------------------------
// @ 0x00a99350  Elem1C_ctor_range  (dst-ptr, srcFirst, srcLast, out)
// ---------------------------------------------------------------------------
Elem1C* Elem1C_ctor_range(Elem1C** out, Elem1C* first, Elem1C* last, Elem1C* dst)
{
    *out = dst;
    if (first != last) {
        Elem1C* s = first;
        Elem1C* d = dst;
        do {
            if (d) *d = *s;
            ++s; ++d;
        } while (s != last);
        *out = d;
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00a993b0  Elem1C_ctor_range_off14
// ---------------------------------------------------------------------------
Elem1C* Elem1C_ctor_range_off14(Elem1C** out, Elem1C* first, Elem1C* last, Elem1C* dst)
{
    *out = dst;
    if (first != last) {
        Elem1C* s = first;
        Elem1C* d = dst;
        do {
            if (d) *d = *s;
            ++s; ++d;
        } while (s != last);
        *out = d;
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00a99410  Elem1C_insert
// ---------------------------------------------------------------------------
void Elem1C_insert(Elem1CVec* vec, Elem1C* pos, unsigned int n, const Elem1C* v)
{
    unsigned int cap = (unsigned int)(((char*)vec->mpCapacity - (char*)vec->mpBegin) / 0x1c);
    if (cap < n) {
        // grow
        unsigned int oldN = (unsigned int)(((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x1c);
        unsigned int newCap = oldN * 2;
        if (oldN == 0) newCap = 1;
        unsigned int want = oldN + n;
        if (want > newCap) newCap = want;
        char* p = (char*)EAAllocate(newCap * 0x1c, "EASTL", 0, 0, 0, 0xd1);
        Elem1C* q = Elem1C_copy_range((Elem1C*)p, vec->mpBegin, pos);
        Elem1C_fill(q, n, v);
        Elem1C* r = Elem1C_copy_range(q + n, pos, vec->mpEnd);
        if (vec->mpBegin && *(int*)((char*)vec->mpBegin - 4) != 0)
            operator_delete(vec->mpBegin);
        vec->mpBegin = (Elem1C*)p;
        vec->mpEnd = r;
        vec->mpCapacity = (Elem1C*)(p + newCap * 0x1c);
        return;
    }

    if (n == 0) return;

    unsigned int rem = (unsigned int)(((char*)vec->mpEnd - (char*)pos) / 0x1c);
    unsigned int nn = n;
    Elem1C tmp = *v;

    if (nn < rem) {
        char* dstBase = (char*)vec->mpEnd - nn * 0x1c;
        Elem1C* r = Elem1C_ctor_range(0, (Elem1C*)dstBase, vec->mpEnd, vec->mpEnd);
        (void)r;
        unsigned int off = nn * 0x1c;
        vec->mpEnd = (Elem1C*)((char*)vec->mpEnd + off);
        Elem1C_Dtor((char*)pos, dstBase, vec->mpEnd);
        unsigned int n2 = n * 0x1c;
        Elem1C_DtorAndFill(pos, (char*)pos + n2, &tmp);
        return;
    }

    // nn >= rem
    unsigned int extra = nn - rem;
    Elem1C_fill(vec->mpEnd, extra, &tmp);
    vec->mpEnd = (Elem1C*)((char*)vec->mpEnd + extra * 0x1c);
    {
        Elem1C* dst = vec->mpEnd;
        Elem1C* o = pos;
        unsigned int m = rem;
        do {
            if (dst) *dst = *o;
            ++dst; ++o;
        } while (--m);
        vec->mpEnd = (Elem1C*)((char*)vec->mpEnd + rem * 0x1c);
    }
    Elem1C_DtorAndFill(pos, (char*)pos + rem * 0x1c, &tmp);
}
