// Slice s0077d800: EASTL vector helpers and shader-constant registration tables.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- EASTL-ish container helpers ---------------------------------------------------------
struct Float4_77d800 { float x, y, z, w; };

void __cdecl operator_delete__(void* p);   // 0x00f47380

struct U32Vec {
    unsigned* begin;   // +0
    unsigned* end;     // +4
    unsigned* cap;     // +8
    void DoInsertValue(unsigned* pos, unsigned* val);   // 0x004558a0
};

extern void __cdecl copy_impl_r(void* a, void* b, void* c);  // 0x00705250
extern void* __cdecl FUN_00706ab0(void* a, void* b, void* c);

struct Vec16 {
    char pad[0x14];
    void Grow(void* a, unsigned b, void* c);   // 0x0077d510
};

struct Vec8Thing {
    char pad[8];
    int  FUN_0077d970(unsigned val);
    void FUN_0077d800(void* first, void* last);
    void FUN_0077d9c0(unsigned n, void* val);
};

struct BigVec {
    char pad[0x14];
    void* FUN_0077e260(unsigned a, unsigned b);
    void* FUN_0077e2c0(void* a, void* b);
};

struct CamThing {
    char pad[0x180];
    void FUN_0077ef60(float* v);
};

#pragma warning(disable:4035)
static __forceinline int FloorToInt(float f) {
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// @ 0x0077d970
int Vec8Thing::FUN_0077d970(unsigned val) {
    U32Vec* v = (U32Vec*)((char*)this + 8);
    unsigned* end = v->end;
    if (end < v->cap) {
        v->end = end + 1;
        if (end != 0) {
            *end = val;
            return (int)(v->end - v->begin) - 1;
        }
    } else {
        v->DoInsertValue(end, &val);
    }
    return (int)(v->end - v->begin) - 1;
}

// @ 0x0077d9c0
void Vec8Thing::FUN_0077d9c0(unsigned n, void* val) {
    int p = (int)this;
    int end = *(int*)(p + 4);
    int cur = (end - *(int*)(p)) >> 4;
    if (n > (unsigned)cur) {
        ((Vec16*)p)->Grow((void*)end, n - cur, val);
        return;
    }
    int dest = n * 0x10 + *(int*)(p);
    copy_impl_r((void*)end, (void*)end, (void*)dest);
    *(int*)(p + 4) = *(int*)(p + 4) + (((end - dest) >> 4) * -0x10);
}

// @ 0x0077eef0  linear interpolation into a float array (x87 return)
// The accumulator is a double on purpose: under /arch:SSE MSVC computes doubles in x87 but floats
// in SSE, and 0x0077eef0 does the interpolation with flds/fsub/fmuls/faddp, i.e. one rounding at
// the end (and `t` is overwritten with the fractional part, which is why the fraction lands in the
// parameter's stack slot).
float __cdecl FUN_0077eef0(int n, float* arr, float t) {
    if (n == 1)
        return arr[0];
    t = (float)(n - 1) * t;
    int i = FloorToInt(t);
    double r = arr[i];
    t = t - (float)i;
    if (t > 0.0f)
        r = (arr[i + 1] - r) * t + r;
    return (float)r;
}

struct Float3 { float x, y, z; };

// @ 0x0077ef60
void CamThing::FUN_0077ef60(float* v) {
    char* th = (char*)this;
    float f = 1.0f - (*(float*)(th + 0x16c) * v[2] +
                      *(float*)(th + 0x168) * v[1] +
                      *(float*)(th + 0x164) * v[0]);
    if (f > *(float*)(th + 0x20c))
        *(Float3*)(th + 0x164) = *(Float3*)v;
    *(Float3*)(th + 0x170) = *(Float3*)v;
}

// ---- partial skeletons (see partial.txt) -------------------------------------------------

// A 16-byte-stride EASTL vector with inline storage.  begin/end/cap at +0/+4/+8; the
// inline buffer address (used to decide whether the heap block must be freed) is at +0x10.
struct Vec4_77d800 {
  char*  begin;    // +0x00
  char*  end;      // +0x04
  char*  cap;      // +0x08
  char   pad0c[4]; // +0x0c
  char*  inlineCap;// +0x10  address of the inline buffer (== cap for the inline case)
  void Assign(char* first, char* last, void* unused);
};

extern "C" char* FUN_0077d6c0_va(void* self, char* first, char* last, unsigned count); // 0x0077d6c0
extern "C" char* UninitCopy_va(char* first, char* last, char* dst);                    // 0x00706ab0

// @ 0x0077d800  (191 bytes) assign a [first,last) range of 16-byte elements into the vector.
void Vec4_77d800::Assign(char* first, char* last, void* unused) {
  (void)unused;
  char* begin = this->begin;
  const unsigned count = (unsigned)((last - first) >> 4);
  if ((unsigned)((this->cap - begin) >> 4) < count) {
    char* nbeg = FUN_0077d6c0_va(this, first, last, count);
    char* obeg = this->begin;
    if (obeg != 0 && obeg != this->inlineCap)
      operator_delete__(obeg);
    char* nend = count * 0x10 + nbeg;
    this->begin = nbeg;
    this->cap   = nend;
    this->end   = nend;
    return;
  }
  const unsigned have = (unsigned)((this->end - begin) >> 4);
  if (count <= have) {
    char* d = begin;
    for (char* s = first; s != last; s += 0x10, d += 0x10)
      *(Float4_77d800*)d = *(Float4_77d800*)s;
    this->end = d;
    return;
  }
  char* mid = first + have * 0x10;
  char* d = begin;
  for (char* s = first; s != mid; s += 0x10, d += 0x10)
    *(Float4_77d800*)d = *(Float4_77d800*)s;
  this->end = UninitCopy_va(mid, last, this->end);
}

// @ 0x0077d8c0  (168 bytes) EH destructor: release every element, reset the vector, swap vftable.
struct ElemVec_77d8c0 {
  void*   m00;   // +0x00 vftable
  char    pad04[4];
  void**  begin;// +0x08
  void**  end;  // +0x0c
  void Dtor();
};
extern "C" void* __cdecl memcpy_vd(void*, const void*, size_t);    // 0x011e0744

void ElemVec_77d8c0::Dtor() {
  this->m00 = (void*)0x140e878;                 // ??_7...@@6B@ intermediate vftable
  int n = (int)(this->end - this->begin) >> 2;
  for (int i = 0; i < n; ++i) {
    void* p = this->begin[i];
    if (p != 0)
      (*(void(__thiscall**)(void*, int))(*(void***)p)[0])(p, 1);   // vcall slot 0 with 1
  }
  void** b = this->begin;
  void** e = this->end;
  // The original emits memcpy(begin, end, 0): an EASTL move the compiler folded to a no-op.
  memcpy_vd(b, e, 0);
  int bytes = (int)((char*)e - (char*)b);
  this->end = (void**)((char*)this->end + (-(bytes >> 2)) * 4);
  void* nb = this->begin;
  if (nb != 0 && ((int*)nb)[-1] != 0)
    operator_delete__(nb);
  this->m00 = (void*)0x13ef094;                 // ??_7hkReferencedObject@@6B@
}

// @ 0x0077e260  (93 bytes) EH ctor: vector with a 0x100-byte inline buffer at +0x18.
struct Inline100_77e260 {
  char* begin;    // +0x00
  char* end;      // +0x04
  char* cap;      // +0x08
  char  pad0c[4]; // +0x0c
  char* inlineCap;// +0x10  == this+0x18
  char  pad14[4]; // +0x14
  char  buf[0x100]; // +0x18
  void* Ctor(unsigned a, void* b);
};

void* Inline100_77e260::Ctor(unsigned a, void* b) {
  char* inl = (char*)this + 0x18;
  this->inlineCap = inl;
  this->end = inl;
  this->begin = inl;
  this->cap = inl + 0x100;
  ((Vec8Thing*)this)->FUN_0077d9c0(a, b);   // 0x0077d9c0 eastl_vector_Resize
  return this;
}

// @ 0x0077e2c0  (471 bytes) EH ctor: vector with a 0x40-byte inline buffer at +0x20, assign range.
struct Inline40_77e2c0 {
  char* begin;    // +0x00
  char* end;      // +0x04
  char* cap;      // +0x08
  char  pad0c[4]; // +0x0c
  char* inlineCap;// +0x10  == this+0x20
  char  pad14[0xc]; // +0x14
  char  buf[0x40];  // +0x20
  void* Ctor(void* a, char* b);
};
void* Inline40_77e2c0::Ctor(void* a, char* b) {
  char* inl = (char*)this + 0x20;
  this->inlineCap = inl;
  this->end = inl;
  this->begin = inl;
  this->cap = inl + 0x40;
  ((Vec4_77d800*)this)->Assign((char*)a, b, b);
  return this;
}

// @ 0x0077e4a0  (560 bytes) set up the normalization shader constants and apply them.
extern unsigned* g_matrixActive;      // 0x016f85ac -> Matrix44Affine* ActiveState
extern int       g_matrixType;        // 0x016f8b50
extern void*     g_d3d9Device;        // 0x016f89d0
extern unsigned  g_shaderState_cn;    // 0x016f6e0c

extern "C" void* FUN_00778060_cn(void* out, void* src, int type);       // 0x00778060
extern "C" void  FUN_0041cb40_cn(void* self, void* src);                // 0x0041cb40 (cSPMatrix3::Assign)
extern "C" void  FUN_006b92d0_cn(void* self);                           // 0x006b92d0 (Basis3::Normalize)
extern "C" void  RemoveNormConsts_cn(int n, void* p);                   // 0x00783830
extern "C" void  thunk_7864c0_cn(void* a, int b, void* c, void* d);     // 0x00795eb0
extern "C" void  ApplyNormConsts_cn(int n, void* p);                    // 0x00783590

// A 3x4 affine matrix: 0x40 bytes, copied a xmmword at a time.
struct Matrix44Affine_cn { float m[16]; };
// The 0x34-byte matrix33 the assign/normalize pair builds on the stack.
struct Matrix33_cn { char m[0x34]; };

// Named globals at their retail addresses.
static Matrix44Affine_cn& g_normalizationMat  = *(Matrix44Affine_cn*)0x01632c90;
static Matrix33_cn&       g_normalizationMat33 = *(Matrix33_cn*)0x01632c90;
static void*&             g_inverseTransform  = *(void**)0x016f9120;
static Matrix44Affine_cn& g_normalizationRows = *(Matrix44Affine_cn*)0x01633b90;

void FUN_0077e4a0(unsigned reg, unsigned p2, int isVS) {
  unsigned state = g_shaderState_cn;
  if (state == 0 || *(unsigned char*)(state + 1) < 4)
    return;

  // Snapshot the active transform, invert it, store the inverse back.
  g_normalizationMat = *(Matrix44Affine_cn*)g_matrixActive;
  Matrix33_cn scratch;
  Matrix44Affine_cn* inv =
      (Matrix44Affine_cn*)FUN_00778060_cn(&scratch, &g_normalizationMat, g_matrixType);
  g_normalizationMat = *inv;

  // Build the 3x3 basis from the fixed normalisation constants.
  float n0 = *(float*)0x01632bfc;
  float n1 = *(float*)0x01632c00;
  float n2 = *(float*)0x01632c04;
  g_inverseTransform = &g_normalizationMat33;

  struct { float x, y, z; short a, b; } rows;   // +0x18 window (12 bytes + 2 shorts)
  rows.x = n0; rows.y = n1; rows.z = n2;
  rows.a = 0; rows.b = 0;

  FUN_0041cb40_cn(&rows, (void*)0x01632d7c);
  rows.z = 1.0f;
  FUN_006b92d0_cn(&g_normalizationMat33);
  ++rows.a;
  rows.y = 1.0f;

  Inline40_77e2c0 vec;
  vec.Ctor((void*)(state + 0x30), (char*)(state + 0x70));

  RemoveNormConsts_cn(2, vec.begin);
  Matrix33_cn basis;
  thunk_7864c0_cn(&basis, 2, vec.begin, (void*)0x01633b80);
  ApplyNormConsts_cn(2, (void*)0x01633b80);

  // Scale the three normalisation rows by 2/3.
  const float s = *(float*)0x0140e87c;
  for (int i = 0; i < 12; ++i)
    g_normalizationRows.m[i] *= s;

  void* dev = g_d3d9Device;
  void** vt = *(void***)dev;
  if (isVS != 0)
    ((void(__thiscall*)(void*, unsigned))vt[0x178 / 4])(dev, reg);
  else
    ((void(__thiscall*)(void*, unsigned, void*, int))vt[0x1b4 / 4])(dev, reg, (void*)0x01633b80, 4);

  if (vec.begin != 0 && vec.begin != vec.inlineCap)
    operator_delete__(vec.begin);
}

// @ 0x0077e6d0  registers the whole rw shader-constant table: SetShaderDef(id, a, b, c, setter),
// then records each constant's size (bytes) in g_shConstSizes[id].
typedef void (__cdecl *ShFn)();
extern void __cdecl SetShaderDef(int id, ShFn a, ShFn b, ShFn c, ShFn setter);   // 0x011f4270
extern int g_shConstSizes[0x340];                                                  // 0x01631ef0
extern "C" void* __cdecl memset(void*, int, size_t);
extern void __cdecl ShNoOp();                    // 0x00c2e4e0 (ret)
extern void __cdecl ShResolveTwo();              // 0x011fb1c0
extern void __cdecl ShUnresolveTwo();            // 0x011fb1f0
extern void __cdecl ShNoOp2();                   // 0x011fb220
extern void __cdecl F777e10(); extern void __cdecl F777e30();
extern void __cdecl F777cb0(); extern void __cdecl F777d60();
extern void __cdecl SkinBones();      extern void __cdecl SkinWeights();    extern void __cdecl UvTweak();
extern void __cdecl ExpandAmount();   extern void __cdecl RatePair();       extern void __cdecl F77da20();
extern void __cdecl TransformBasis(); extern void __cdecl F77daf0();        extern void __cdecl SunDir();
extern void __cdecl Flag();           extern void __cdecl Color();          extern void __cdecl F777e50();
extern void __cdecl F777e90();        extern void __cdecl BoneMatrix3();    extern void __cdecl LightRows();
extern void __cdecl LightRowsXform(); extern void __cdecl ArrayA();         extern void __cdecl F77e320();
extern void __cdecl Normalization();  extern void __cdecl FocusDistance();  extern void __cdecl F77dbc0();
extern void __cdecl F77dc90();        extern void __cdecl ViewportRatios(); extern void __cdecl F777ed0();
extern void __cdecl F779790();        extern void __cdecl Projector();      extern void __cdecl ArrayB();
extern void __cdecl F77dd60();        extern void __cdecl CameraLight();    extern void __cdecl F77de30();
extern void __cdecl DirectionBasis(); extern void __cdecl TransformBlock(); extern void __cdecl F77af70();
extern void __cdecl LightBlock();     extern void __cdecl F777f00();        extern void __cdecl F777f40();
extern void __cdecl F77df00();        extern void __cdecl F77dfd0();        extern void __cdecl F77cd50();
extern void __cdecl F778fd0();        extern void __cdecl F779030();        extern void __cdecl F779130();
extern void __cdecl F77cb40();        extern void __cdecl F77e0a0();        extern void __cdecl F77e170();
extern void __cdecl F777f80();        extern void __cdecl F77c8b0();

void __cdecl FUN_0077e6d0() {
    SetShaderDef(0x200, F777e10, F777e30, F777e30, SkinBones);
    memset(g_shConstSizes, 0, 0xd00);
    SetShaderDef(4, ShResolveTwo, ShUnresolveTwo, ShUnresolveTwo, F777cb0);
    SetShaderDef(3, ShNoOp2, ShNoOp2, ShNoOp2, F777d60);
    SetShaderDef(0x201, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x201] = 8;
    SetShaderDef(0x202, ShNoOp, ShNoOp, ShNoOp, SkinWeights);   g_shConstSizes[0x202] = 0x14;
    SetShaderDef(0x203, ShNoOp, ShNoOp, ShNoOp, UvTweak);   g_shConstSizes[0x203] = 8;
    SetShaderDef(0x204, ShNoOp, ShNoOp, ShNoOp, ExpandAmount);   g_shConstSizes[0x204] = 0x10;
    SetShaderDef(0x205, ShNoOp, ShNoOp, ShNoOp, RatePair);   g_shConstSizes[0x205] = 0x14;
    SetShaderDef(0x206, ShNoOp, ShNoOp, ShNoOp, F77da20);   g_shConstSizes[0x206] = 0x100;
    SetShaderDef(0x207, 0, 0, 0, 0);
    SetShaderDef(0x208, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x208] = 8;
    SetShaderDef(0x209, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x209] = 4;
    SetShaderDef(0x20a, ShNoOp, ShNoOp, ShNoOp, TransformBasis);   g_shConstSizes[0x20a] = 0x40;
    SetShaderDef(0x20b, ShNoOp, ShNoOp, ShNoOp, F77daf0);   g_shConstSizes[0x20b] = 0x40;
    SetShaderDef(0x20c, ShNoOp, ShNoOp, ShNoOp, SunDir);   g_shConstSizes[0x20c] = 0x10;
    SetShaderDef(0x20d, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x20d] = 0x64;
    SetShaderDef(0x20e, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x20e] = 8;
    SetShaderDef(0x20f, ShNoOp, ShNoOp, ShNoOp, Flag);   g_shConstSizes[0x20f] = 8;
    SetShaderDef(0x210, ShNoOp, ShNoOp, ShNoOp, Color);   g_shConstSizes[0x210] = 0x14;
    SetShaderDef(0x211, ShNoOp, ShNoOp, ShNoOp, F777e50);   g_shConstSizes[0x211] = 0x14;
    SetShaderDef(0x212, ShNoOp, ShNoOp, ShNoOp, F777e90);   g_shConstSizes[0x212] = 0x20;
    SetShaderDef(0x213, ShNoOp, ShNoOp, ShNoOp, BoneMatrix3);   g_shConstSizes[0x213] = 0x30;
    SetShaderDef(0x214, 0, 0, 0, LightRows);
    SetShaderDef(0x215, 0, 0, 0, LightRowsXform);
    SetShaderDef(0x216, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x216] = 1;
    SetShaderDef(0x217, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x217] = 1;
    SetShaderDef(0x219, 0, 0, 0, ArrayA);
    SetShaderDef(0x21a, 0, 0, 0, F77e320);
    SetShaderDef(0x254, 0, 0, 0, Normalization);
    SetShaderDef(0x21b, 0, 0, 0, FocusDistance);
    SetShaderDef(0x21c, ShNoOp, ShNoOp, ShNoOp, F77dbc0);   g_shConstSizes[0x21c] = 0x20;
    SetShaderDef(0x21e, ShNoOp, ShNoOp, ShNoOp, F77dc90);   g_shConstSizes[0x21e] = 0x10;
    SetShaderDef(0x21f, 0, 0, 0, ViewportRatios);
    SetShaderDef(0x220, ShNoOp, ShNoOp, ShNoOp, F777ed0);   g_shConstSizes[0x220] = 0x10;
    SetShaderDef(0x221, 0, 0, 0, F779790);
    SetShaderDef(0x222, 0, 0, 0, Projector);
    SetShaderDef(0x223, ShNoOp, ShNoOp, ShNoOp, ArrayB);   g_shConstSizes[0x223] = 0xa4;
    SetShaderDef(0x224, ShNoOp, ShNoOp, ShNoOp, F77dd60);   g_shConstSizes[0x224] = 0x98;
    SetShaderDef(0x225, 0, 0, 0, CameraLight);
    SetShaderDef(0x226, ShNoOp, ShNoOp, ShNoOp, F77de30);   g_shConstSizes[0x226] = 0x10;
    SetShaderDef(0x23e, 0, 0, 0, DirectionBasis);
    SetShaderDef(0x227, 0, 0, 0, TransformBlock);
    SetShaderDef(0x228, 0, 0, 0, F77af70);
    SetShaderDef(0x229, 0, 0, 0, LightBlock);
    SetShaderDef(0x24b, 0, 0, 0, F777f00);
    SetShaderDef(0x252, 0, 0, 0, F777f40);
    SetShaderDef(0x22d, ShNoOp, ShNoOp, ShNoOp, F77df00);   g_shConstSizes[0x22d] = 0x10;
    SetShaderDef(0x22e, ShNoOp, ShNoOp, ShNoOp, F77dfd0);   g_shConstSizes[0x22e] = 0x10;
    SetShaderDef(0x22f, ShNoOp, ShNoOp, ShNoOp, F77cd50);   g_shConstSizes[0x22f] = 0x3fcc;
    SetShaderDef(0x230, ShNoOp, ShNoOp, ShNoOp, F778fd0);   g_shConstSizes[0x230] = 4;
    SetShaderDef(0x231, ShNoOp, ShNoOp, ShNoOp, F779030);   g_shConstSizes[0x231] = 0xc;
    SetShaderDef(0x232, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x232] = 1;
    SetShaderDef(0x237, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x237] = 1;
    SetShaderDef(0x23b, ShNoOp, ShNoOp, ShNoOp, F779130);   g_shConstSizes[0x23b] = 0x60;
    SetShaderDef(0x244, ShNoOp, ShNoOp, ShNoOp, 0);   g_shConstSizes[0x244] = 1;
    SetShaderDef(0x22e, ShNoOp, ShNoOp, ShNoOp, F77cb40);   g_shConstSizes[0x22e] = 0x10;
    SetShaderDef(0x245, ShNoOp, ShNoOp, ShNoOp, ShNoOp);   g_shConstSizes[0x245] = 0xc;
    SetShaderDef(0x246, ShNoOp, ShNoOp, ShNoOp, ShNoOp);   g_shConstSizes[0x246] = 0x14;
    SetShaderDef(0x247, ShNoOp, ShNoOp, ShNoOp, F77e0a0);   g_shConstSizes[0x247] = 0x10;
    SetShaderDef(0x248, ShNoOp, ShNoOp, ShNoOp, F77e170);   g_shConstSizes[0x248] = 0x10;
    SetShaderDef(0x255, ShNoOp, ShNoOp, ShNoOp, F777f80);   g_shConstSizes[0x255] = 0x20;
    SetShaderDef(0x256, ShNoOp, ShNoOp, ShNoOp, F77c8b0);
    g_shConstSizes[0x256] = 0x10;
}
