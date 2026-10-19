// Slice s00535d00: Swarm skin-paint ArgScript paint-variable registration + 16-byte
// element vector copy ctor. The two large registration helpers (00535e40, 005361a0,
// 005365b0, 00536910, 00536b00) are stubbed (partial.txt). Unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0

// ---------------------------------------------------------------- @ 0x00535d00
struct Elem16 {
    uint32_t d[4];
};
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    uint32_t mAlloc[2];
    Vec16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Vec16(const Vec16& x);
};
void* uninitialized_copy16(Elem16* first, Elem16* last, Elem16* dest);   // 0x005371a0

// @ 0x00535d00
Vec16::Vec16(const Vec16& x)
{
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    Elem16* p = (n == 0) ? 0 : (Elem16*)EASTL_Allocate(mAlloc, n * 16, 4, 0);
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    mpEnd = (Elem16*)uninitialized_copy16(x.mpBegin, x.mpEnd, mpBegin);
}

// ---------------------------------------------------------------- @ 0x005368f0
struct Host5368f0 {
    char pad[0x30];
    char* p;
    void Set(void* a);   // @ 0x005368f0
};
void Host5368f0::Set(void* a)
{
    (void)a;
    *(int*)(p + 0x50) = 0xff;
}

// ---------------------------------------------------------------- stubs (partial)
// ---------------------------------------------------------------- 0x00535e40 classes
// RegisterPaintEvalCommands<cSPSkinPaintFloodEffectBlockCommand>: registers the 19 inherit-style
// PaintVariable commands, "modifier", rotate/varyHue/varySat/varyVal and the two compare commands.
void* operator new(size_t, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

struct PaintCompatB {                       // 0x10 bytes; out-of-line ctor at 0x0053b1f0
    virtual void v0();
    virtual void v1();
    uint32_t pad[3];
    PaintCompatB();                         // 0x0053b1f0
};
struct PaintCompatM : PaintCompatB {        // vtbl 0x013f2424 (ArgScript::PaintCompat)
    PaintCompatM() {}
    virtual void v0();
};
struct PaintVarCmd : PaintCompatM {         // 0x14 bytes, vtbl 0x013f2c74
    int mVar;                               // +0x10
    PaintVarCmd(int v) { mVar = v; }
    virtual void v0();
};
struct PaintCompatNormal : PaintCompatM {   // 0x10 bytes, vtbl 0x013f2bb4
    PaintCompatNormal() {}
    virtual void v0();
};
struct PaintCompatPosition : PaintCompatM { // 0x10 bytes, vtbl 0x013f2b8c
    PaintCompatPosition() {}
    virtual void v0();
};
struct PaintVarModifierB {                  // 0x34 bytes; out-of-line ctor at 0x0053cca0
    virtual void v0();
    virtual void v1();
    uint32_t pad[12];
    PaintVarModifierB();                    // 0x0053cca0
};
struct PaintVarModifierM : PaintVarModifierB {   // vtbl 0x013f2c34 (ArgScript::PaintVarModifier)
    PaintVarModifierM() {}
    virtual void v0();
};
struct PaintVarModifier : PaintVarModifierM {    // vtbl 0x013f2c10
    PaintVarModifier() {}
    virtual void v0();
};
struct PaintRegistry {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Register(const char* name, void* cmd);    // +0x18 (ret 8)
};
extern const char* const kFloodPaintNames[0x13];            // 0x013f2980

// @ 0x00535e40
void RegisterPaintEvalCommands(PaintRegistry* reg)
{
    for (int i = 0; i < 0x13; ++i)
        reg->Register(kFloodPaintNames[i], new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(i));
    reg->Register("modifier", new("ArgScript/PaintVarModifier", 0, 0, 0, 0) PaintVarModifier());
    reg->Register("rotate", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(2));
    reg->Register("varyHue", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(7));
    reg->Register("varySat", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(8));
    reg->Register("varyVal", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(9));
    reg->Register("compareNormal", new("ArgScript/PaintCompat", 0, 0, 0, 0) PaintCompatNormal());
    reg->Register("comparePosition", new("ArgScript/PaintCompat", 0, 0, 0, 0) PaintCompatPosition());
}
// @ 0x005361a0
void PaintVariableParseLineStub() {}
// @ 0x005365b0
void PaintVarModifierStub() {}
// @ 0x00536910
void PaintVarCommandStub() {}
// @ 0x00536b00
void PaintVarCommand2Stub() {}
