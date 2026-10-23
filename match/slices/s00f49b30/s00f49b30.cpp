// Slice s00f49b30 -- ArgScript brush commands: the brush-effect registrar that installs the
// per-property sub-commands, the individual brush argument commands, and the brush state
// copy-constructor / copy-assignment.
//
//   0x00f49b30  BrushCondRangeCommand::Execute      (enum + 3/5 float args)
//   0x00f49c50  BrushVecCommand::Execute            (2 three-float vectors, "vary")
//   0x00f49cf0  cBrushEffectCommand::OnRegister     (installs 15 sub-commands)
//   0x00f4a130  BrushFloatsCommand::Execute         (float list + "255" scale)
//   0x00f4a3b0  cBrushSizeCommand::Execute          (float list, "vary", "global")
//   0x00f4a4c0  BrushVaryCommand::Execute           (float list + "vary")
//   0x00f4a5d0  BrushState::operator=
//   0x00f4a810  BrushState::BrushState(const BrushState&)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"

typedef unsigned int  u32;
typedef unsigned char u8;

#define VFN(o, off, T) ((T)(*(void***)(o))[((off) >> 2)])

// ------------------------------------------------------------- thiscall thunk types
typedef void  (__thiscall *TC_vp)(void*, void*);
typedef void  (__thiscall *TC_vpp)(void*, void*, void*);
typedef float (__thiscall *TC_fp)(void*, const char*);
typedef void* (__thiscall *TC_ppp)(void*, void*, const char*);

// ------------------------------------------------------------- cdecl callees
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int, int, int, int); // 0xf473a0
extern "C" char  __cdecl ParseEnum(const char* s, const void* table);                // 0x840bb0
extern "C" float __cdecl ParseRangedFloat(void* parser, const char* s, float lo, float hi); // 0x840d50
extern "C" void* __cdecl eastl_vector_insert(void* dst, const void* src, u32 bytes);  // 0x11e0744
extern "C" void  __cdecl op_delete(void* p);                                          // 0xf47380

// ------------------------------------------------------------- literals / tables / vtables
extern "C" char  T_148de50[];      // 0x0148de50  ParseEnum table
extern "C" char  S_vary[];         // 0x013f2d14  "vary"
extern "C" char  S_global[];       // 0x01458ba8  "global"
extern "C" float KF_13eecd4;       // 0x013eecd4  (1/255)

extern "C" char  VT_148dec8[];     // 0x0148dec8  BrushState vtable
extern "C" char  VT_148def0[];     // 0x0148def0  BrushRibbon
extern "C" char  VT_148df3c[];     // 0x0148df3c  BrushIntensity / BrushIntensity255
extern "C" char  VT_148df54[];     // 0x0148df54  BrushSize
extern "C" char  VT_148df6c[];     // 0x0148df6c  BrushSpacing
extern "C" char  VT_148df84[];     // 0x0148df84  BrushLife
extern "C" char  VT_148df9c[];     // 0x0148df9c  BrushRate
extern "C" char  VT_148dfb4[];     // 0x0148dfb4  BrushTexture
extern "C" char  VT_148dfd8[];     // 0x0148dfd8  BrushFilter
extern "C" char  VT_148dff0[];     // 0x0148dff0  BrushCond
extern "C" char  VT_148e008[];     // 0x0148e008  BrushFractalCond / BrushFractalCondRange
extern "C" char  VT_148e020[];     // 0x0148e020  BrushCondRange
extern "C" char  VT_148e038[];     // 0x0148e038  BrushGradientCondRange
extern "C" char  VT_148e050[];     // 0x0148e050  BrushRotate

// pointer globals holding the registered command name strings
extern "C" void* P_15b09f8;        // "ribbon"
extern "C" void* P_15b09bc;        // "intensity"
extern "C" void* P_15b09c0;        // "intensity255"
extern "C" void* P_15b09c4;        // "size"
extern "C" void* P_15b09ec;        // "spacing"
extern "C" void* P_15b09cc;        // "life"
extern "C" void* P_15b09d0;        // "rate"
extern "C" void* P_15b09d4;        // "texture"
extern "C" void* P_15b09d8;        // "filter"
extern "C" void* P_15b09dc;        // "cond"
extern "C" void* P_15b09e8;        // "fractalCond"
extern "C" void* P_15b09f0;        // "fractalCondRange"
extern "C" void* P_15b09e0;        // "condRange"
extern "C" void* P_15b09e4;        // "gradientCondRange"
extern "C" void* P_15b09f4;        // "rotate"

// ------------------------------------------------------------- argument parser
struct cArguments {
    const char** MainArguments(int* out, int lo, int hi);                    // 0x838020
    const char** OptionArguments(const char* name, int n);                   // 0x838330
    const char** OptionArguments(const char* name, int* out, int a, int b);  // 0x838130
    const char*  operator[](int i);                                          // 0x837f20
};

// ------------------------------------------------------------- eastl vector<float>
struct Vec {
    float* begin;   // +0x00
    float* end;     // +0x04
    float* cap;     // +0x08
    void*  alloc;   // +0x0c

    Vec(const Vec& o) {
        int n = (int)(o.end - o.begin);
        Init(n, &o.alloc);
        void* r = eastl_vector_insert(begin, o.begin, (u32)((char*)o.end - (char*)o.begin));
        end = (float*)r + n;
    }
    Vec& operator=(const Vec& o);             // 0x50d4e0
    void Init(int n, const void* a);          // 0x4aa350
    void DoInsertValue(float* pos, const float& v);   // 0x455660
    void push_back(const float& v) {
        if (end < cap) { float* p = end; end = p + 1; if (p) *p = v; }
        else DoInsertValue(end, v);
    }
    void erase(float* first, float* last) {
        eastl_vector_insert(first, last, (u32)((char*)end - (char*)last));
        *(int*)&end += (int)(((char*)last - (char*)first) >> 2) * -4;
    }
};

// ------------------------------------------------------------- brush state
struct BrushState {
    void* vt;        // +0x00
    int   f04;       // +0x04
    float f08;       // +0x08
    float f0c;       // +0x0c
    float f10;       // +0x10
    int   f14;       // +0x14  (never copied)
    int   f18;       // +0x18
    int   f1c;       // +0x1c
    u8    b20;       // +0x20
    u8    b21;       // +0x21
    char  pad22[2];  // +0x22
    float f24;       // +0x24
    float f28;       // +0x28
    Vec   v2c;       // +0x2c
    int   f3c;       // +0x3c
    Vec   v40;       // +0x40
    int   f50;       // +0x50
    u8    b54;       // +0x54
    char  pad55[3];  // +0x55
    float f58;       // +0x58
    float f5c;       // +0x5c
    float f60;       // +0x60
    float f64;       // +0x64
    float f68;       // +0x68
    float f6c;       // +0x6c
    float f70;       // +0x70
    float f74;       // +0x74
    float f78;       // +0x78
    float f7c;       // +0x7c
    u8    b80;       // +0x80
    u8    b81;       // +0x81
    u8    b82;       // +0x82
    u8    b83;       // +0x83
    float f84;       // +0x84
    Vec   v88;       // +0x88
    int   f98;       // +0x98
    float f9c;       // +0x9c
    u8    ba0;       // +0xa0
    char  pada1[3];  // +0xa1
    float fa4;       // +0xa4
    float fa8;       // +0xa8
    u8    bac;       // +0xac
    char  padad[3];  // +0xad
    float fb0;       // +0xb0
    float fb4;       // +0xb4
    u8    bb8;       // +0xb8
    char  padb9[3];  // +0xb9
    float fbc;       // +0xbc
    float fc0;       // +0xc0
    u8    bc4;       // +0xc4
    char  padc5[3];  // +0xc5
    float fc8;       // +0xc8
    float fcc;       // +0xcc
    u8    bd0;       // +0xd0
    char  padd1[3];  // +0xd1
    float fd4;       // +0xd4  (copied as int in operator=)
    float fd8;       // +0xd8
    float fdc;       // +0xdc
    float fe0;       // +0xe0
    float fe4;       // +0xe4
    float fe8;       // +0xe8
    u8    bec;       // +0xec
    char  paded[3];  // +0xed
    int   ff0;       // +0xf0
    int   ff4;       // +0xf4
    int   ff8;       // +0xf8
    int   ffc;       // +0xfc
    u8    b100;      // +0x100

    BrushState(const BrushState& o);            // 0x00f4a810
    BrushState& operator=(const BrushState& o); // 0x00f4a5d0
};

// The sub-command state pointer is (BrushState - 8); these are the members it touches.
struct BrushSubState {
    char  pad00[0x34];   // +0x00
    Vec   v2c;           // +0x34  (= BrushState::v2c)
    char  pad44[4];      // +0x44
    Vec   v40;           // +0x48  (= BrushState::v40)
    char  pad58[8];      // +0x58
    float f60;           // +0x60  (= BrushState::f58)
    float f64;           // +0x64  (= BrushState::f5c)
    char  pad68[0x21];   // +0x68
    u8    b89;           // +0x89  (= BrushState::b81)
    char  pad8a[6];      // +0x8a
    Vec   v88;           // +0x90  (= BrushState::v88)
    char  padA0[4];      // +0xa0
    float fA4;           // +0xa4  (= BrushState::f9c)
};

// ------------------------------------------------------------- command base
struct cCommandBase {
    void* vt;        // +0x00
    void* parser;    // +0x04
    int   f08;       // +0x08
    void* state;     // +0x0c

    cCommandBase();                                        // 0x83c800
    void OnRegister(cArguments* p, void* s);               // 0x83c780
    void SetUserData(void* p);                             // 0xfd9450
    void* operator new(u32, const char*, int, int, int, int);
};

#define CMD_CLASS(NAME, VT) \
    struct NAME : cCommandBase { NAME() : cCommandBase() { vt = (void*)VT; } };

CMD_CLASS(cCmdRibbon, VT_148def0)
CMD_CLASS(cCmdIntensity, VT_148df3c)
CMD_CLASS(cCmdIntensity255, VT_148df3c)
CMD_CLASS(cCmdSize, VT_148df54)
CMD_CLASS(cCmdSpacing, VT_148df6c)
CMD_CLASS(cCmdLife, VT_148df84)
CMD_CLASS(cCmdRate, VT_148df9c)
CMD_CLASS(cCmdTexture, VT_148dfb4)
CMD_CLASS(cCmdFilter, VT_148dfd8)
CMD_CLASS(cCmdCond, VT_148dff0)
CMD_CLASS(cCmdFractalCond, VT_148e008)
CMD_CLASS(cCmdFractalCondRange, VT_148e008)
CMD_CLASS(cCmdCondRange, VT_148e020)
CMD_CLASS(cCmdGradientCondRange, VT_148e038)
CMD_CLASS(cCmdRotate, VT_148e050)

// ------------------------------------------------------------- brush-effect registrar
struct cBrushEffectCommand : cCommandBase {
    char  pad10[0x20];   // +0x10
    void* f30;           // +0x30
    void* f34;           // +0x34
    char  stbuf[0x110];  // +0x38  embedded state
    void* f148;          // +0x148

    void OnRegister(cArguments* parser, void* state);      // 0x00f49cf0
};

// ------------------------------------------------------------- brush sub-commands
struct cBrushCondRangeCommand : cCommandBase { void Execute(cArguments* args); };   // 0x00f49b30
struct cBrushVecCommand : cCommandBase { void Execute(cArguments* args); };         // 0x00f49c50
struct cBrushFloatsCommand : cCommandBase { void Execute(cArguments* args); };      // 0x00f4a130
struct cBrushSizeCommand : cCommandBase { void Execute(cArguments* args); };        // 0x00f4a3b0
struct cBrushVaryCommand : cCommandBase { void Execute(cArguments* args); };        // 0x00f4a4c0

// ================================================================================================
// @ 0x00f49b30
void cBrushCondRangeCommand::Execute(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 0x7fffffff);
    *(u8*)((char*)this->state + 0xc0) = (u8)ParseEnum(a[0], T_148de50);
    *(u8*)((char*)this->state + 0xcc) = 0;
    if (*(u8*)((char*)this->state + 0xc0) == 3 && n == 5) {
        *(u8*)((char*)this->state + 0xcc) = 1;
        *(float*)((char*)this->state + 0xd0) =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[1]);
        *(float*)((char*)this->state + 0xc4) =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[2]);
        *(float*)((char*)this->state + 0xc8) =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[3]);
        *(float*)((char*)this->state + 0xd4) =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[4]);
        return;
    }
    if (n == 3) {
        *(u8*)((char*)this->state + 0xcc) = 1;
        *(float*)((char*)this->state + 0xd0) =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[2]);
        *(float*)((char*)this->state + 0xc4) =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[1]);
        return;
    }
    *(u8*)((char*)this->state + 0xc0) = 0;
}

// ================================================================================================
// @ 0x00f49c50
struct Vec3f { float x, y, z; };

void cBrushVecCommand::Execute(cArguments* args)
{
    Vec3f tmp;
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    const Vec3f* r = (const Vec3f*)VFN(this->parser, 0xa8, TC_ppp)(this->parser, &tmp, a[0]);
    char* st = (char*)this->state;
    *(Vec3f*)(st + 0xdc) = *r;
    const char** o = args->OptionArguments(S_vary, 1);
    if (o) {
        const Vec3f* r2 = (const Vec3f*)VFN(this->parser, 0xa8, TC_ppp)(this->parser, &tmp, o[0]);
        char* st2 = (char*)this->state;
        *(Vec3f*)(st2 + 0xe8) = *r2;
    }
}

// ================================================================================================
// @ 0x00f49cf0
void cBrushEffectCommand::OnRegister(cArguments* parser, void* state)
{
    this->f30 = state ? (void*)((char*)state - 0xc) : 0;
    cCommandBase::OnRegister(parser, state);
    this->f148 = this->f30;
    this->SetUserData(this->stbuf);

    {
        cCommandBase* c = new ("ArgScript/BrushRibbon", 0, 0, 0, 0) cCmdRibbon;
        VFN(this, 0x18, TC_vpp)(this, P_15b09f8, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushIntensity", 0, 0, 0, 0) cCmdIntensity;
        VFN(this, 0x18, TC_vpp)(this, P_15b09bc, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushIntensity255", 0, 0, 0, 0) cCmdIntensity255;
        VFN(this, 0x18, TC_vpp)(this, P_15b09c0, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushSize", 0, 0, 0, 0) cCmdSize;
        VFN(this, 0x18, TC_vpp)(this, P_15b09c4, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushSpacing", 0, 0, 0, 0) cCmdSpacing;
        VFN(this, 0x18, TC_vpp)(this, P_15b09ec, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushLife", 0, 0, 0, 0) cCmdLife;
        VFN(this, 0x18, TC_vpp)(this, P_15b09cc, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushRate", 0, 0, 0, 0) cCmdRate;
        VFN(this, 0x18, TC_vpp)(this, P_15b09d0, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushTexture", 0, 0, 0, 0) cCmdTexture;
        VFN(this, 0x18, TC_vpp)(this, P_15b09d4, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushFilter", 0, 0, 0, 0) cCmdFilter;
        VFN(this, 0x18, TC_vpp)(this, P_15b09d8, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushCond", 0, 0, 0, 0) cCmdCond;
        VFN(this, 0x18, TC_vpp)(this, P_15b09dc, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushFractalCond", 0, 0, 0, 0) cCmdFractalCond;
        VFN(this, 0x18, TC_vpp)(this, P_15b09e8, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushFractalCondRange", 0, 0, 0, 0) cCmdFractalCondRange;
        VFN(this, 0x18, TC_vpp)(this, P_15b09f0, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushCondRange", 0, 0, 0, 0) cCmdCondRange;
        VFN(this, 0x18, TC_vpp)(this, P_15b09e0, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushGradientCondRange", 0, 0, 0, 0) cCmdGradientCondRange;
        VFN(this, 0x18, TC_vpp)(this, P_15b09e4, c);
    }
    {
        cCommandBase* c = new ("ArgScript/BrushRotate", 0, 0, 0, 0) cCmdRotate;
        VFN(this, 0x18, TC_vpp)(this, P_15b09f4, c);
    }
}

#define SUBST ((BrushSubState*)this->state)

// ================================================================================================
// @ 0x00f4a130
void cBrushFloatsCommand::Execute(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);

    Vec* v = &SUBST->v40;
    v->erase(v->begin, v->end);
    for (int i = 0; i < n; i++) {
        float f = VFN(this->parser, 0x98, TC_fp)(this->parser, a[i]);
        SUBST->v40.push_back(f);
    }

    const char** o = args->OptionArguments(S_vary, 1);
    if (o)
        SUBST->f60 = ParseRangedFloat(this->parser, o[0], 0.0f, 1.0f);

    const char* s = args->operator[](0);
    bool is255 = (s[0] == '2' && s[1] == '5' && s[2] == '5' && s[3] == '\0');
    if (is255) {
        Vec* w = &SUBST->v40;
        int cnt = (int)(w->end - w->begin);
        for (int i = 0; i < cnt; i++)
            w->begin[i] = w->begin[i] * KF_13eecd4;
    }
}

// ================================================================================================
// @ 0x00f4a3b0
void cBrushSizeCommand::Execute(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);

    Vec* v = &SUBST->v2c;
    v->erase(v->begin, v->end);
    for (int i = 0; i < n; i++) {
        float f = VFN(this->parser, 0x98, TC_fp)(this->parser, a[i]);
        SUBST->v2c.push_back(f);
    }

    const char** o = args->OptionArguments(S_vary, 1);
    if (o)
        SUBST->f64 = ParseRangedFloat(this->parser, o[0], 0.0f, 1.0f);

    if (args->OptionArguments(S_global, &n, 0, 1))
        SUBST->b89 = 1;
}

// ================================================================================================
// @ 0x00f4a4c0
void cBrushVaryCommand::Execute(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);

    SUBST->fA4 = 0.0f;
    Vec* v = &SUBST->v88;
    v->erase(v->begin, v->end);
    for (int i = 0; i < n; i++) {
        float f = VFN(this->parser, 0x98, TC_fp)(this->parser, a[i]);
        SUBST->v88.push_back(f);
    }

    const char** o = args->OptionArguments(S_vary, 1);
    if (o)
        SUBST->fA4 = ParseRangedFloat(this->parser, o[0], 0.0f, 1.0f);
}

// ================================================================================================
// @ 0x00f4a5d0
BrushState& BrushState::operator=(const BrushState& o)
{
    *(int*)((char*)this + 0x08) = *(int*)((char*)&o + 0x08);
    *(int*)((char*)this + 0x0c) = *(int*)((char*)&o + 0x0c);
    *(int*)((char*)this + 0x10) = *(int*)((char*)&o + 0x10);
    f18 = o.f18;
    f1c = o.f1c;
    b20 = o.b20;
    b21 = o.b21;
    f24 = o.f24;
    f28 = o.f28;
    v2c = o.v2c;
    v40 = o.v40;
    b54 = o.b54;
    f58 = o.f58;
    f5c = o.f5c;
    f60 = o.f60;
    *(int*)((char*)this + 0x64) = *(int*)((char*)&o + 0x64);
    *(int*)((char*)this + 0x68) = *(int*)((char*)&o + 0x68);
    f6c = o.f6c;
    f70 = o.f70;
    f74 = o.f74;
    f78 = o.f78;
    f7c = o.f7c;
    b80 = o.b80;
    b81 = o.b81;
    b82 = o.b82;
    b83 = o.b83;
    f84 = o.f84;
    v88 = o.v88;
    f9c = o.f9c;
    ba0 = o.ba0;
    fa4 = o.fa4;
    fa8 = o.fa8;
    bac = o.bac;
    fb0 = o.fb0;
    fb4 = o.fb4;
    bb8 = o.bb8;
    fbc = o.fbc;
    fc0 = o.fc0;
    bc4 = o.bc4;
    fc8 = o.fc8;
    fcc = o.fcc;
    bd0 = o.bd0;
    *(int*)((char*)this + 0xd4) = *(int*)((char*)&o + 0xd4);
    *(int*)((char*)this + 0xd8) = *(int*)((char*)&o + 0xd8);
    *(int*)((char*)this + 0xdc) = *(int*)((char*)&o + 0xdc);
    *(int*)((char*)this + 0xe0) = *(int*)((char*)&o + 0xe0);
    *(int*)((char*)this + 0xe4) = *(int*)((char*)&o + 0xe4);
    *(int*)((char*)this + 0xe8) = *(int*)((char*)&o + 0xe8);
    bec = o.bec;
    ff0 = o.ff0;
    ff4 = o.ff4;
    ff8 = o.ff8;
    ffc = o.ffc;
    b100 = o.b100;
    return *this;
}

// ================================================================================================
// @ 0x00f4a810
BrushState::BrushState(const BrushState& o)
    : vt((void*)VT_148dec8), f04(0),
      f08(o.f08), f0c(o.f0c), f10(o.f10),
      f18(o.f18), f1c(o.f1c),
      b20(o.b20), b21(o.b21),
      f24(o.f24), f28(o.f28),
      v2c(o.v2c), v40(o.v40),
      b54(o.b54),
      f58(o.f58), f5c(o.f5c), f60(o.f60), f64(o.f64), f68(o.f68),
      f6c(o.f6c), f70(o.f70), f74(o.f74), f78(o.f78), f7c(o.f7c),
      b80(o.b80), b81(o.b81), b82(o.b82), b83(o.b83),
      f84(o.f84), v88(o.v88),
      f9c(o.f9c), ba0(o.ba0),
      fa4(o.fa4), fa8(o.fa8),
      bac(o.bac), fb0(o.fb0), fb4(o.fb4), bb8(o.bb8),
      fbc(o.fbc), fc0(o.fc0), bc4(o.bc4),
      fc8(o.fc8), fcc(o.fcc), bd0(o.bd0),
      fd4(o.fd4), fd8(o.fd8), fdc(o.fdc), fe0(o.fe0), fe4(o.fe4), fe8(o.fe8),
      bec(o.bec), ff0(o.ff0), ff4(o.ff4), ff8(o.ff8), ffc(o.ffc), b100(o.b100)
{
}
