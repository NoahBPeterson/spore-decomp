// s012b4a70 -- a block of VS2008 (cl 14.0) static initializers and small global-config
// writers from the SporeApp renderer / gameplay-data layer:
//   * a SerializedProperty descriptor table copied into the global registration table
//     (012b4a70, the mCrossGameData fields).
//   * FNV1_String8 name->hash registrations for particle, screen and decl techniques.
//   * vector/float global initialisers (012cc270.., 012e3860, 012dde20, 012d7850, ...).
//   * a table of default colours written through UintArray::Self() (012f61e0..012f64a0).
//   * lib_crt static-array / stack-allocator constructors that register an atexit hook.
//   * a leaf global descriptor table (012f5e60).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

#include <xmmintrin.h>

typedef unsigned int   uint;
typedef unsigned short ushort;

// ---- runtime helpers (declared, resolved at link time) ----------------------
unsigned int __cdecl FNV1_String8(const char* s, unsigned int basis, int flags); // 0x00932e80
struct UintArray {
    void* Self();                                                                // 0x00572590
};

// lib_crt array/stack-allocator constructors and atexit.
extern "C" void __stdcall lib_crt_ctor_array(void* base, unsigned int n, int sz,
                                             void (__cdecl* ctor)(void*),
                                             void (__cdecl* dtor)(void*));      // 0x011e0b85 ??_L
extern "C" int  __cdecl lib_crt_atexit(void (__cdecl*)());                       // 0x011e07ef
struct StackAllocator {
    void ctor(void* p, uint n, void* alloc, void* free, void* ctx);              // 0x00928cd0
};

// Matrix3::Assign(this, const float*)
struct Matrix3 {
    void Assign(const void* src);                                                // 0x0041cb40
};

// ---- globals referenced by name ---------------------------------------------
extern float DAT_01485720;                  // 0x01485720  common "1.0" scale
extern float DAT_014853e0;                  // 0x014853e0  reciprocal scale
extern float DAT_01471064;                  // 0x01471064

// x87 fsqrt (double) -- /fp:fast inlines sqrt; the single-precision store truncates.
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// The particle / screen / decl technique hash tables (written by the registrars).
extern uint DAT_01618f88, DAT_01618f8c, DAT_01618f90, DAT_01618f94;
extern uint DAT_01618f98, DAT_01618f9c, DAT_01618fa0, DAT_01618fa4;
extern uint DAT_01618fa8, DAT_01618fac, DAT_01618fb0, DAT_01618fb4;
extern uint DAT_01618fb8, DAT_01618fbc, DAT_01618fc0, DAT_01618fc4;
extern uint DAT_01618fc8, DAT_01618fcc, DAT_01618fd0, DAT_01618fd4;
extern uint DAT_01618fd8, DAT_01618fdc, DAT_01618fe0, DAT_01618fe4;
extern uint DAT_01618fe8, DAT_01618fec, DAT_01618ff0, DAT_01618ff4;
extern uint DAT_01618ff8, DAT_01618ffc, DAT_01619000, DAT_01619004;
extern uint DAT_01631058, DAT_0163105c, DAT_01631060, DAT_01631064;
extern uint DAT_01631068, DAT_0163106c, DAT_01631070, DAT_01631074;
extern uint DAT_01631078, DAT_0163107c;
extern uint DAT_016304c8, DAT_016304cc, DAT_016304d0, DAT_016304d4;
extern uint DAT_016304d8, DAT_016304dc;
extern uint DAT_01633e34, DAT_01633e38, DAT_01633e3c, DAT_01633e40;

// =============================================================================
// 012b4a70 -- SerializedProperty table for the mCrossGameData fields.
// =============================================================================
// The compiler builds a 0x3c-byte descriptor in a stack frame and block-copies it
// (rep movsd of 0xf dwords) into the global table at TABLE_BASE + i*0x3c.
struct PropDesc {
    const char*  name;          // +0x00
    unsigned int kind;          // +0x04
    unsigned int offset;        // +0x08
    unsigned int u0c;           // +0x0c  (left untouched by the initialiser)
    unsigned int u10;           // +0x10
    unsigned int u14;           // +0x14
    unsigned int zero18;        // +0x18
    unsigned int zero1c;        // +0x1c
    unsigned int defOffset;     // +0x20
    unsigned int getter;        // +0x24
    unsigned int setter;        // +0x28
    unsigned int serializer;    // +0x2c
    unsigned int clearBuffer;   // +0x30
    unsigned int fn34;          // +0x34
    unsigned int fn38;          // +0x38
};

// @ 0x012b4a70
void __cdecl CrossGameData_InitProps()
{
    const unsigned int z      = 0;
    const unsigned int DefOff = 0x00692ca0;   // Simulator::Attribute::DefaultOffset
    const unsigned int Ser    = 0x00c2e4e0;   // UTFWin::ILayoutElement::SetSerializer
    const unsigned int Clear  = 0x00692fb0;   // ?ClearBuffer@@YAXPAPAC@Z
    const unsigned int Get    = 0x00676140;
    const unsigned int Set    = 0x00675790;
    const unsigned int F34    = 0x00675850;
    const unsigned int F38    = 0x006761f0;

    PropDesc d;

    d.name = "mAchievementSet";            d.kind = 0xabce0000;
    d.zero18 = z; d.zero1c = z;
    d.defOffset = DefOff;
    d.getter = 0x00676540; d.setter = 0x00f27200;
    d.serializer = Ser; d.clearBuffer = Clear;
    d.fn34 = 0x00b1fbf0; d.fn38 = 0x00675ff0;
    d.offset = 0x24;
    *(PropDesc*)0x01529330 = d;

    d.name = "mCrossGameData.mEncounteredCreatures"; d.kind = 0xabce0004;
    d.zero18 = z; d.zero1c = z;
    d.defOffset = DefOff;
    d.getter = Get; d.setter = Set;
    d.serializer = Ser; d.clearBuffer = Clear;
    d.fn34 = F34; d.fn38 = F38;
    d.offset = 0x5c;
    *(PropDesc*)0x0152936c = d;

    d.name = "mCrossGameData.mTribeGamesCompleted"; d.kind = 0xabce0005;
    d.zero18 = z; d.zero1c = z;
    d.defOffset = DefOff;
    d.getter = Get; d.setter = Set;
    d.serializer = Ser; d.clearBuffer = Clear;
    d.fn34 = F34; d.fn38 = F38;
    d.offset = 0x9c;
    *(PropDesc*)0x015293a8 = d;

    d.name = "mCrossGameData.mEatenCreatures"; d.kind = 0xabce0006;
    d.zero18 = z; d.zero1c = z;
    d.defOffset = DefOff;
    d.getter = Get; d.setter = Set;
    d.serializer = Ser; d.clearBuffer = Clear;
    d.fn34 = F34; d.fn38 = F38;
    d.offset = 0x7c;
    *(PropDesc*)0x015293e4 = d;

    d.name = "mCrossGameData.mCellGameIDs"; d.kind = 0xabce0007;
    d.zero18 = z; d.zero1c = z;
    d.defOffset = DefOff;
    d.getter = Get; d.setter = Set;
    d.serializer = Ser; d.clearBuffer = Clear;
    d.fn34 = F34; d.fn38 = F38;
    d.offset = 0x3c;
    *(PropDesc*)0x01529420 = d;
}

// =============================================================================
// Small bit-field mask writers.
// =============================================================================
extern uint DAT_01604e60, DAT_01604e68, DAT_015301e8, DAT_015301f0, DAT_015301f8;

// @ 0x012c7900
void __cdecl Mask_1()
{
    DAT_01604e60 &= 0xff0fffff;
    *(unsigned char*)0x01604e63 = 0;
    DAT_01604e60 &= 0xfff00000;
}

// @ 0x012c7920
void __cdecl Mask_2()  { DAT_01604e68 &= 0xff000000; }

// @ 0x012c7930
void __cdecl Mask_3()  { DAT_015301e8 &= 0xff000000; }

// @ 0x012c7940
void __cdecl Mask_4()  { DAT_015301f0 &= 0xff000000; }

// @ 0x012c7950
void __cdecl Mask_5()  { DAT_015301f8 &= 0xff000000; }

// =============================================================================
// FNV1_String8 name -> hash registrations.
// =============================================================================
// @ 0x012d1c80
void __cdecl Particles_RegisterTechniques()
{
    DAT_01618f88 = FNV1_String8("Particles_Decal", 0x811c9dc5, 1);
    DAT_01618f8c = FNV1_String8("Particles_DecalInvertDepth", 0x811c9dc5, 1);
    DAT_01618f90 = FNV1_String8("Particles_DecalIgnoreDepth", 0x811c9dc5, 1);
    DAT_01618f94 = FNV1_String8("Particles_DepthDecal", 0x811c9dc5, 1);
    DAT_01618f98 = FNV1_String8("Particles_Additive", 0x811c9dc5, 1);
    DAT_01618f9c = FNV1_String8("Particles_AdditiveInvertDepth", 0x811c9dc5, 1);
    DAT_01618fa0 = FNV1_String8("Particles_AdditiveIgnoreDepth", 0x811c9dc5, 1);
    DAT_01618fa4 = FNV1_String8("Particles_Modulate", 0x811c9dc5, 1);
    DAT_01618fa8 = FNV1_String8("Particles_NormalMap", 0x811c9dc5, 1);
    DAT_01618fac = FNV1_String8("Particles_DepthNormalMap", 0x811c9dc5, 1);
    DAT_01618fb0 = FNV1_String8("Particles_AlphaTestDissolve", 0x811c9dc5, 1);
    DAT_01618fb4 = FNV1_String8("Particles_Decal", 0x811c9dc5, 1);
    DAT_01618fb8 = 0;
    DAT_01618fbc = 0;
    DAT_01618fc0 = 0;
    DAT_01618fc4 = 0;
}

// @ 0x012d1db0
void __cdecl ParticlesLightFog_RegisterTechniques()
{
    DAT_01618fc8 = FNV1_String8("ParticlesLightFog_Decal", 0x811c9dc5, 1);
    DAT_01618fcc = FNV1_String8("ParticlesLightFog_DecalInvertDepth", 0x811c9dc5, 1);
    DAT_01618fd0 = FNV1_String8("ParticlesLightFog_DecalIgnoreDepth", 0x811c9dc5, 1);
    DAT_01618fd4 = FNV1_String8("ParticlesLightFog_DepthDecal", 0x811c9dc5, 1);
    DAT_01618fd8 = FNV1_String8("Particles_Additive", 0x811c9dc5, 1);
    DAT_01618fdc = FNV1_String8("Particles_AdditiveInvertDepth", 0x811c9dc5, 1);
    DAT_01618fe0 = FNV1_String8("Particles_AdditiveIgnoreDepth", 0x811c9dc5, 1);
    DAT_01618fe4 = FNV1_String8("Particles_Modulate", 0x811c9dc5, 1);
    DAT_01618fe8 = FNV1_String8("Particles_NormalMap", 0x811c9dc5, 1);
    DAT_01618fec = FNV1_String8("Particles_DepthNormalMap", 0x811c9dc5, 1);
    uint h = FNV1_String8("Particles_AlphaTestDissolve", 0x811c9dc5, 1);
    DAT_01618ff0 = h;
    DAT_01618ff4 = 0;
    DAT_01618ff8 = 0;
    DAT_01618ffc = 0;
    DAT_01619000 = 0;
    DAT_01619004 = 0;
}

// @ 0x012e2af0
void __cdecl Screen_RegisterTechniques()
{
    DAT_01631058 = FNV1_String8("ScreenAdditive", 0x811c9dc5, 1);
    DAT_0163105c = FNV1_String8("ScreenBlend", 0x811c9dc5, 1);
    DAT_01631060 = FNV1_String8("ScreenTint", 0x811c9dc5, 1);
    DAT_01631064 = FNV1_String8("ScreenBrighten", 0x811c9dc5, 1);
    DAT_01631068 = FNV1_String8("ScreenSkyBox", 0x811c9dc5, 1);
    DAT_0163106c = FNV1_String8("ScreenBackground", 0x811c9dc5, 1);
    DAT_01631070 = FNV1_String8("ScreenAdditiveTexture", 0x811c9dc5, 1);
    DAT_01631074 = FNV1_String8("ScreenBlendTexture", 0x811c9dc5, 1);
    DAT_01631078 = FNV1_String8("ScreenTintTexture", 0x811c9dc5, 1);
    DAT_0163107c = FNV1_String8("ScreenBrightenTexture", 0x811c9dc5, 1);
}

// @ 0x012e1190
void __cdecl Placeholder_RegisterMaps()
{
    DAT_016304c8 = FNV1_String8("PlaceholderSpecGlossMap", 0x811c9dc5, 1);
    DAT_016304cc = 0;
    DAT_016304d0 = 0x40002700;
    DAT_016304d4 = FNV1_String8("PlaceholderNormalMap", 0x811c9dc5, 1);
    DAT_016304d8 = 0;
    DAT_016304dc = 0x40002700;
}

// @ 0x012e3f10
void __cdecl BuildBasis_RegisterTechniques()
{
    DAT_01633e34 = FNV1_String8("BuildBasis_0_0", 0x811c9dc5, 1);
    DAT_01633e38 = FNV1_String8("BuildBasis_0_1", 0x811c9dc5, 1);
    DAT_01633e3c = FNV1_String8("BuildBasis_1_0", 0x811c9dc5, 1);
    DAT_01633e40 = FNV1_String8("BuildBasis_1_1", 0x811c9dc5, 1);
}

// =============================================================================
// Small float / vector global initialisers.
// =============================================================================
// Named float globals produce the retail `movss xmm0,[src]; movss [dst],xmm0` form.
extern float DAT_01606a3c, DAT_01606a40, DAT_01606a44, DAT_01606a48;
extern float DAT_01606d34, DAT_01606d38, DAT_01606d3c, DAT_01606d40;
extern float DAT_01531bd4, DAT_01531bd8, DAT_01531bdc, DAT_01531be0;
extern float DAT_01606d44, DAT_01606d48, DAT_01606d4c, DAT_01606d50;
extern float DAT_01606a30, DAT_01606a34, DAT_01606a38;
extern float DAT_01531ca8, DAT_01531cac, DAT_01531cb0;

// @ 0x012cc270
void __cdecl CopyVec4_1()
{
    DAT_01606d34 = DAT_01606a3c;
    DAT_01606d38 = DAT_01606a40;
    DAT_01606d3c = DAT_01606a44;
    DAT_01606d40 = DAT_01606a48;
}

// @ 0x012cc320
void __cdecl CopyVec4_2()
{
    DAT_01606d44 = DAT_01531bd4;
    DAT_01606d48 = DAT_01531bd8;
    DAT_01606d4c = DAT_01531bdc;
    DAT_01606d50 = DAT_01531be0;
}

// @ 0x012cc370
void __cdecl CopyVec3_AndMatrix()
{
    DAT_01531ca8 = DAT_01606a30;
    DAT_01531cac = DAT_01606a34;
    DAT_01531cb0 = DAT_01606a38;
    ((Matrix3*)0x01531cb8)->Assign((const void*)0x01606c0c);
}

struct V3 { float x, y, z; };
extern V3 V3_1606ae0, V3_1606aec;
static inline V3 Make3(float v)
{
    V3 r;
    r.x = v;
    r.y = v;
    r.z = v;
    return r;
}

// @ 0x012cc3b0
void __cdecl SetVec3Pair()
{
    V3_1606ae0 = Make3(*(float*)0x0140a014);
    V3_1606aec = Make3(*(float*)0x013f51ac);
}

// @ 0x012d7850
void __cdecl SetRecipSqrt_1()
{
    // x87: fld [x]; fmul [scale]; fld1; fdivrp st(1); fsqrt; fstp [dst]
    //     = sqrt(1.0 / (x * scale))
    *(float*)0x016299f4 = (float)sqrt(1.0 / (double)(*(float*)0x01535958 * DAT_014853e0));
}

// @ 0x012e45f0
void __cdecl SetRecipSqrt_2()
{
    *(float*)0x01634100 = (float)sqrt(1.0 / (double)(*(float*)0x0163411c * DAT_014853e0));
}

// @ 0x012e4930
void __cdecl SetRecipSqrt_3()
{
    *(float*)0x016340e0 = (float)sqrt(1.0 / (double)(*(float*)0x0163411c * DAT_014853e0));
}

// @ 0x012dde20
void __cdecl SetOneMinus()
{
    *(float*)0x0162f0e8 = DAT_01485720 - *(float*)0x01538130;
}

// The identity-matrix globals are written as whole 16-byte SSE stores.
extern __m128 M1632c90, M1632ca0, M1632cb0, M1632cc0;

// @ 0x012e3860
void __cdecl SetIdentityMatrix()
{
    M1632c90 = _mm_set_ps(1.0f, 0.0f, 0.0f, 1.0f);
    M1632ca0 = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
    M1632cb0 = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
    M1632cc0 = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
}

// =============================================================================
// lib_crt static-array constructors that register an atexit hook.
// =============================================================================
// @ 0x012c5ae0
void __cdecl RegList_Init()
{
    lib_crt_ctor_array((void*)0x016032a8, 0x150, 0xb,
                       (void (__cdecl*)(void*))0x006ac770,
                       (void (__cdecl*)(void*))0x006ac6f0);
    lib_crt_atexit((void (__cdecl*)())0x013bed40);
}

// @ 0x012d3830
void __cdecl PixelFrag_Init()
{
    lib_crt_ctor_array((void*)0x016198c0, 0x64, 0x100,
                       (void (__cdecl*)(void*))0x006fafe0,
                       (void (__cdecl*)(void*))0x006fb040);
    lib_crt_atexit((void (__cdecl*)())0x013bf360);
}

// @ 0x012d51f0
void __cdecl VertexFrag_Init()
{
    lib_crt_ctor_array((void*)0x01624710, 0x44, 0x100,
                       (void (__cdecl*)(void*))0x006fe7f0,
                       (void (__cdecl*)(void*))0x006fe830);
    lib_crt_atexit((void (__cdecl*)())0x013bf480);
}

// @ 0x012d5250
void __cdecl PoolAlloc_Init()
{
    ((StackAllocator*)0x01628b98)->ctor((void*)0, 0xffffffff,
                                        (void*)0x00928ad0, (void*)0x00f47410,
                                        (void*)0x0140c35c);
    lib_crt_atexit((void (__cdecl*)())0x013bf410);
}

// @ 0x012d3890
void __cdecl PoolAllocPS_Init()
{
    ((StackAllocator*)0x0161fda4)->ctor((void*)0, 0xffffffff,
                                        (void*)0x00928ad0, (void*)0x00f47410,
                                        (void*)0x0140bbcc);
    lib_crt_atexit((void (__cdecl*)())0x013bf2f0);
}

// =============================================================================
// 012f5e60 -- leaf initialiser for a fixed descriptor table at 0x015424bc.
// =============================================================================
// @ 0x012f5e60
void __cdecl InitDescTable()
{
    uint five = 5;
    *(uint*)0x015424bc = 1;
    *(uint*)0x015424c0 = 0;
    *(uint*)0x015424c4 = 0;
    *(uint*)0x015424c8 = 0xeec1d007;
    *(unsigned short*)0x015424cc = (unsigned short)five;
    *(uint*)0x015424d0 = 0x230;
    *(uint*)0x015424d4 = 1;
    *(uint*)0x015424d8 = 0;
    *(uint*)0x015424dc = 0;
    *(uint*)0x015424e0 = 0xeec1d008;
    *(unsigned short*)0x015424e4 = (unsigned short)five;
    *(uint*)0x015424e8 = 0x23c;
    *(uint*)0x015424ec = 1;
    *(uint*)0x015424f0 = 0;
    *(uint*)0x015424f4 = 0;
    *(uint*)0x015424f8 = 0xeec1d009;
    *(unsigned short*)0x015424fc = (unsigned short)five;
    *(uint*)0x01542500 = 0x240;
    *(uint*)0x01542504 = 1;
}

// =============================================================================
// Default colour / vector table written through UintArray::Self().
// =============================================================================
// Each function calls UintArray::Self() to obtain the base pointer (returned in
// eax, discarded) and then writes a fixed 3- or 4-lane float vector at the
// addressed global.
// @ 0x012f61e0
void __cdecl SetColor_1()
{
    ((UintArray*)0x0164b394)->Self();
    float one = DAT_01485720;
    *(float*)0x0164b394 = one;
    *(float*)0x0164b398 = one;
    *(float*)0x0164b39c = one;
}

// @ 0x012f6210
void __cdecl SetColor_2()
{
    ((UintArray*)0x0164b200)->Self();
    *(float*)0x0164b200 = 0.0f;
    *(float*)0x0164b204 = 0.0f;
    *(float*)0x0164b208 = 0.0f;
}

// @ 0x012f6240
void __cdecl SetColor_3()
{
    ((UintArray*)0x0164b3e4)->Self();
    *(float*)0x0164b3e4 = DAT_01485720;
    *(float*)0x0164b3e8 = 0.0f;
    *(float*)0x0164b3ec = 0.0f;
}

// @ 0x012f6270
void __cdecl SetColor_4()
{
    ((UintArray*)0x0164b298)->Self();
    float zero4 = 0.0f;
    *(float*)0x0164b298 = zero4;
    float one4 = DAT_01485720;
    *(float*)0x0164b29c = one4;
    *(float*)0x0164b2a0 = zero4;
}

// @ 0x012f62a0
void __cdecl SetColor_5()
{
    ((UintArray*)0x0164b4b8)->Self();
    *(float*)0x0164b4b8 = 0.0f;
    *(float*)0x0164b4bc = 0.0f;
    *(float*)0x0164b4c0 = DAT_01485720;
}

// @ 0x012f62d0
void __cdecl SetColor_6()
{
    ((UintArray*)0x0164b378)->Self();
    float one = DAT_01485720;
    float zero = 0.0f;
    *(float*)0x0164b378 = one;
    *(float*)0x0164b37c = zero;
    *(float*)0x0164b380 = one;
}

// @ 0x012f6300
void __cdecl SetColor_7()
{
    ((UintArray*)0x0164b4d4)->Self();
    float one = DAT_01485720;
    *(float*)0x0164b4d4 = one;
    *(float*)0x0164b4d8 = one;
    *(float*)0x0164b4dc = 0.0f;
}

// @ 0x012f6330
void __cdecl SetColor_8()
{
    ((UintArray*)0x0164b504)->Self();
    *(float*)0x0164b504 = 0.0f;
    float one = DAT_01485720;
    *(float*)0x0164b508 = one;
    *(float*)0x0164b50c = one;
}

// @ 0x012f6360
void __cdecl SetColor_9()
{
    ((UintArray*)0x0164b2c4)->Self();
    *(float*)0x0164b2c4 = DAT_01485720;
    *(float*)0x0164b2c8 = DAT_01471064;
    *(float*)0x0164b2cc = 0.0f;
}

// @ 0x012f63a0
void __cdecl SetColor_10()
{
    ((UintArray*)0x0164b4c4)->Self();
    float one = DAT_01485720;
    *(float*)0x0164b4c4 = one;
    *(float*)0x0164b4c8 = one;
    *(float*)0x0164b4cc = one;
    *(float*)0x0164b4d0 = one;
}

// @ 0x012f63e0
void __cdecl SetColor_11()
{
    ((UintArray*)0x0164b330)->Self();
    *(float*)0x0164b330 = 0.0f;
    *(float*)0x0164b334 = 0.0f;
    *(float*)0x0164b338 = 0.0f;
    *(float*)0x0164b33c = DAT_01485720;
}

// @ 0x012f6420
void __cdecl SetColor_12()
{
    ((UintArray*)0x0164b26c)->Self();
    float one = DAT_01485720;
    *(float*)0x0164b26c = one;
    *(float*)0x0164b270 = 0.0f;
    *(float*)0x0164b274 = 0.0f;
    *(float*)0x0164b278 = one;
}

// @ 0x012f6460
void __cdecl SetColor_13()
{
    ((UintArray*)0x0164b2a4)->Self();
    float zero13 = 0.0f;
    *(float*)0x0164b2a4 = zero13;
    float one13 = DAT_01485720;
    *(float*)0x0164b2a8 = one13;
    *(float*)0x0164b2ac = zero13;
    *(float*)0x0164b2b0 = one13;
}

// @ 0x012f64a0
void __cdecl SetColor_14()
{
    ((UintArray*)0x0164b448)->Self();
    *(float*)0x0164b448 = 0.0f;
    *(float*)0x0164b44c = 0.0f;
    float one = DAT_01485720;
    *(float*)0x0164b450 = one;
    *(float*)0x0164b454 = one;
}
