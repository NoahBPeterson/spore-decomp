// src/game/SPEngine/SPGraphicsEffectsRenderer.cpp -- migrated from slice(s) s006ec0c0, s006eae40, s006e8f90, s006f1770, s006f0890, s006ef990, s006ee1f0, s006ed2c0, s006ea030, s006e80d0, s006e7110, s006e6100 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsEffectsRenderer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_0067dd50();
#include <math.h>
#include <algorithm>
#include <string.h>
#include <intrin.h>
#include "SP/cEffectsRenderer.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cViewer.h"
#include "rw/graphics/GlobalState.h"
#include <new>
#include "SP/cEffectsCameraManager.h"
#include "rw/graphics/EmbeddedState.h"
#include "SP/cFrustumCull.h"
#include "rw/graphics/VertexBuffer.h"
#include "rw/graphics/ActiveState.h"
#include <xmmintrin.h>
#include <stdlib.h>
#include "rw/core/arena/Arena.h"
#include "SP/cTextRenderer.h"

// ---- items of slice s006e6100 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Inner {
    void F2(int, float);            // 0x006f40b0
    void F1(float);                 // 0x006f3f00
    void F3(int, float, int);       // 0x006f4a10
};
class ShaderHost {
public:
    uint32_t pad[0x100];            // 0x400-byte object

    char HandleMessage2(int msg, int extra);                  // 0x006e6810
    void CallF2(int a, float b);                              // 0x006e69a0
    void CallF1(float b);                                     // 0x006e6930
    void CallF3(int a, float b, int c);                       // 0x006e6970
    void SetMode(int mode, int value);                        // 0x006e69e0
    int  ComputeSize(int a, int b, int c);                    // 0x006e6a20
    int  ResetCounter();                                      // 0x006e6b40
    void SetParams(int a, int b, char c1, char c2, char c3);  // 0x006e6b70
    void CallIface(int v);                                    // 0x006e6c20
    bool IsDone();                                            // 0x006e6c60
    void TailVirtual();                                       // 0x006e6c80
    char Write(void* stream);                                 // 0x006e6100
};
struct Manager {
    void* vtbl;
};
typedef int(__thiscall* VirtualFn1)(void*, int);
typedef void(__thiscall* VirtualFn3)(void*, int, int, int);
// ---- items of slice s006e6100 end

// ---- items of slice s006e7110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_0067dd40();                 // 0x0067dd40
extern "C" void* FUN_0067ddf0();                 // 0x0067ddf0
extern "C" void* FUN_0067dda0();                 // 0x0067dda0
extern "C" void* FUN_0067dd70();                 // 0x0067dd70
extern "C" void* FUN_0067dcc0();                 // 0x0067dcc0
extern "C" int   rw_VertexDescriptor_AreEqual(int, int);
extern int* g_1618d10;
extern "C" void  FUN_00777bf0();                 // 0x00777bf0 pushShaderDataNull
extern "C" void  FUN_00777b50(void*);            // 0x00777b50 SP::SetShaderData
extern "C" void  FUN_00777ae0(int, int, int);    // 0x00777ae0 shader
extern "C" void  FUN_00777c10();                 // 0x00777c10 shader flush
extern "C" void  __fastcall FUN_007789d0(void*, int); // 0x007789d0 ShaderDataState_Push (thiscall)
extern "C" void  FUN_007611a0(int);              // 0x007611a0
extern "C" void  __fastcall FUN_011f9710(void*, int); // 0x011f9710 (thiscall)
extern "C" int   FUN_011f2e70(const void*, const void*); // 0x011f2e70 VertexDescriptor::AreEqual
extern "C" void  __fastcall FUN_011f2bc0(void*, int); // 0x011f2bc0 SetActiveVertexDescriptor (thiscall)
extern "C" void  FUN_011ee580(void*);            // 0x011ee580 CompiledState::Dispatch
extern "C" char  __fastcall FUN_006a25a0(void*, int, unsigned);  // 0x006a25a0 GetDescription
extern "C" int*  __fastcall FUN_0041ea00(void*, int);            // 0x0041ea00 Property::GetUInt
extern "C" int*  __fastcall FUN_0041e990(void*, int);            // 0x0041e990 Property::GetInt
extern "C" void* FUN_00f473a0(unsigned, const char*, int, int, int, int); // 0x00f473a0 operator new
extern "C" void  __fastcall FUN_007c4dd0(void*, int, int);       // 0x007c4dd0 cViewer::Init
extern "C" void  __fastcall FUN_007c3cc0(void*, int, unsigned);  // 0x007c3cc0 cViewer::Clear
extern "C" void* __fastcall FUN_007c3f70(void*, int);            // 0x007c3f70 cViewer::Create
extern "C" char  __fastcall FUN_007c4fd0(void*, int);            // 0x007c4fd0 cViewer::Update
extern "C" void  __fastcall FUN_007c3c10(void*, int);            // 0x007c3c10
extern "C" void  __fastcall FUN_007c4180(void*, int, void*, void*); // 0x007c4180
extern "C" void  __fastcall FUN_0076acd0(void*, int);            // 0x0076acd0 RegisterListener
extern "C" void* FUN_00776730(void*);            // 0x00776730
extern "C" void* FUN_00776920(void*);            // 0x00776920
extern "C" void* FUN_0076c660(void*);            // 0x0076c660 cRTTCapture ctor
extern uint32_t  g_16f85a8;                      // 0x016f85a8
extern void*     g_16f65a0;                      // 0x016f65a0
extern uint32_t  g_16f9110;                      // 0x016f9110
extern void*     g_16fa380;                      // 0x016fa380 matrix source
extern float     g_16f96a8;                      // 0x016f96a8 material colour
extern float     g_16f96ac;
extern float     g_16f96b0;
extern float     g_16f96b4;
extern uint32_t  g_140aef8;                      // 0x0140aef8 reset colour
extern float     g_1485720;                      // 0x01485720 _HK_REAL_ONE
extern float     g_1471064;                      // 0x01471064
extern void*     g_15fd918;                      // 0x015fd918 property list
extern const wchar_t g_140af84[];                // 0x0140af84 L"Arial"
extern const char    g_13eb8a4[];                // 0x013eb8a4 "Graphics"
extern const char g_matName7cc0[];
struct Inner7c {
    char F7(int, int, int, int, int, int, int);       // 0x0076bc50
    void F12(int, int, int, int, int, int, int, int, // 0x0076ba30
             int, int, int, int);
    void FF(float);                                   // 0x00776450
    void FI(int);                                     // 0x006f4280 / 0x0076cd30
    int  Fp(int, int);                                // 0x... vtable +0x10
    void Fq(int, int, float);                         // vtable +0x18/+0x1c
};
struct RefObj {
    virtual void v0(int);
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    uint32_t refCount;                                // +0x04
};
struct VObj {
    virtual void v0(void*);
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
};
struct EmbeddedState {
    uint8_t pad0[8];
    uint8_t flags;                                    // +0x08
    uint8_t pad9[7];
    void D3D9SetTransform(const void* m, int n);      // 0x011edc10
    void SetMaterialColor(const void* c);             // 0x011eda00
    void Dispatch();                                  // 0x011ee580
};
struct Record12 { uint32_t a, b, c; };
struct TextRenderer_s006e_7110 {
    uint8_t pad[0x20];
    void Init();                                    // 0x007a84d0
    void SetStyle(int);                             // 0x007a82a0
    void SetFontName(const wchar_t*);               // 0x007a8550
    void SetFontSize(float);                        // 0x007a85a0
    void SetColor(const void*);                     // 0x007a85e0
    void SetStyleScale(float);                      // 0x007a82d0
    void DrawString(float, float, uint32_t);        // 0x007a91b0
};
struct Elemc0 {
    uint8_t  enabled;                                 // +0x00
    uint8_t  pad1[3];
    uint32_t text0;                                   // +0x04
    uint8_t  pad8[0x90];
    float    f98;                                     // +0x98
    float    f9c;                                     // +0x9c
    uint32_t styleA0;                                 // +0xa0
    uint32_t styleA4;                                 // +0xa4
    float    fontA8;                                  // +0xa8
    float    fAc;                                     // +0xac
    uint32_t colorB0;                                 // +0xb0
    uint32_t colorB4;                                 // +0xb4
    uint32_t colorB8;                                 // +0xb8
    float    scaleBc;                                 // +0xbc
};
struct Renderable {
    VObj*    m00;        // +0x00
    uint32_t pad04[3];
    uint8_t  m10;        // +0x10
    uint8_t  pad11[0x17];
    uint32_t m28;        // +0x28
    float    m2c, m30, m34;
    float    m38, m3c, m40;
    uint32_t pad44[6];
    uint32_t m5c;        // +0x5c
    void*    m60;        // +0x60
    void*    m64;        // +0x64
    void*    m68;        // +0x68
};
struct MidObj {
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual void  v3();
    virtual void  v4();
    virtual void  v5();
    virtual void* v6(float, const float*);              // +0x18
    virtual void* v7(float, const float*, uint32_t);    // +0x1c
};
struct SizeProvider {
    virtual void* v0();
    virtual void* v1();
    virtual void* v2();
    virtual void* v3();
    virtual void* v4();
    virtual void* v5();
    virtual void* v6();
    virtual void* v7();                                 // +0x1c
};
class Host3 {
public:
    RefObj*  m00;        // +0x000 ref-counted
    uint32_t m04;
    void*    m08;        // +0x008 12-byte dispatch records (begin)
    void*    m0c;        // +0x00c ... end
    uint32_t m10;
    uint32_t m14;        // +0x014 message target
    uint32_t m18[2];     // +0x018
    void*    m20;        // +0x020
    void*    m24;        // +0x024 sub-object / capture
    void*    m28;        // +0x028 ref-counted
    uint32_t m2c[5];
    void*    m40;        // +0x040 ref-counted
    uint32_t m44;
    void*    m48;        // +0x048 0x70-stride vector (begin)
    void*    m4c;        // +0x04c ... end
    uint32_t m50[4];
    void*    m60;        // +0x060 released sub-object
    void*    m64;        // +0x064
    uint32_t m68[7];
    uint32_t m84[4];     // +0x084 material
    uint32_t m94[12];
    uint32_t mc4[4];     // +0x0c4 material
    uint32_t md4[32];
    uint32_t m154;       // +0x154
    uint8_t  m158;       // +0x158
    uint8_t  m159;       // +0x159
    uint8_t  m15a[2];
    uint32_t m15c;       // +0x15c
    uint32_t m160;       // +0x160
    uint32_t m164;
    uint32_t m168;       // +0x168
    uint32_t m16c[2];
    void*    m174;       // +0x174 0x70-stride vector (begin)
    void*    m178;       // +0x178 ... end
    uint32_t m17c[13];
    uint32_t m1b0;       // +0x1b0
    uint32_t m1b4;       // +0x1b4
    void*    m1b8;       // +0x1b8 0x68-stride vector (begin)
    void*    m1bc;       // +0x1bc ... end
    uint32_t m1c0[8];
    MidObj*  m1e0;       // +0x1e0
    uint32_t m1e4[8];
    TextRenderer_s006e_7110 m204;   // +0x204 text renderer
    void*    m224;       // +0x224 0xc0-stride vector (begin)
    void*    m228;       // +0x228 ... end
    uint32_t m22c[8];
    void*    m24c;       // +0x24c
    void*    m250;
    void*    m254;
    void*    m258;
    void*    m25c;
    uint32_t m260[62];
    uint32_t m358;       // +0x358
    void*    m35c;       // +0x35c
    void*    m360;       // +0x360 ref-counted
    void*    m364;       // +0x364 ref-counted
    uint8_t  m368;
    uint8_t  m369;       // +0x369
    uint8_t  m36a[18];
    uint32_t m37c;       // +0x37c
    uint32_t m380[0x40]; // pad to 0x480

    void Method7110(int);                                    // 0x006e7110
    void Method7270(void*, void*);                           // 0x006e7270
    void DispatchList(unsigned char* list, int arg);         // 0x006e73d0
    char Method7450(unsigned char flags);                    // 0x006e7450
    void Method7880(int arg);                                // 0x006e7880
    void Method78b0(void* a, void* b, int c);                // 0x006e78b0
    void Method79b0(int index, float f2, float f3, int a4, float f5,
                    int a6, int a7, int a8, int a9, float f10, float f11); // 0x006e79b0
    void SetFlag(int index, unsigned char v);                // 0x006e7aa0
    void Method7ac0(void* arg);                              // 0x006e7ac0
    void Method7b50(void* arg);                              // 0x006e7b50
    char Method7c60();                                       // 0x006e7c60
    char Method7c80(int, int, int, int, int, int);           // 0x006e7c80
    void Method7cc0(int, int, int, int);                     // 0x006e7cc0
    void Method7d00(float);                                  // 0x006e7d00
    void Method7d40(int, uint32_t*, float);                 // 0x006e7d40
    void Method7da0();                                       // 0x006e7da0
    void Method7dd0(int, float*, float);                     // 0x006e7dd0
    void Method7ed0(int, uint32_t*, float);                 // 0x006e7ed0
    void Method7f30();                                       // 0x006e7f30
    int  Method7fa0(int index, int value);                   // 0x006e7fa0
    void Method8000(int index, float* v, float w);           // 0x006e8000
    void Method8090(int index, int a, float b);              // 0x006e8090
};
typedef int(__thiscall* VGet)(void*, int, int);
typedef void(__thiscall* VSet)(void*, int, float*, float);
typedef void(__thiscall* VSet2)(void*, int, int, float);
typedef void  (__thiscall* VFn0)(void*);                 // slot(...)
typedef void* (__thiscall* VFnR)(void*);                 // slot(...) -> ptr
typedef char  (__thiscall* VFnB)(void*, unsigned, void**); // property fetch
typedef void  (__thiscall* VFnS)(void*, void*, int, int);  // viewer setup
typedef void  (__thiscall* VFnM)(void*, int, int, void*);  // material create
typedef void  (__thiscall* VFnP)(void*, void*, unsigned);  // message register
void __fastcall FUN_006e7270(void* self, int dummy, void* a, int arg);  // 0x006e7270
// ---- items of slice s006e7110 end

// ---- items of slice s006e80d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  F_67dd50();
extern void*  F_67dd70();   // SP::MaterialManager
extern void*  F_67dd40();
extern void*  F_67ddb0();
extern void   F_777ae0(int, void*, int);
extern void*  g15ddc84;    // _spInstance_..StaticBufferDraw
extern void*  g15d0838;    // default camera raster
extern void*  g1618d10;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned long long u64;
struct Ext {
    void* r6f2050(int, int);
    char  r6f4170();
    void* r6f41e0(int);
    void* r6f3fe0();
    void  r6f3ee0(int);
    void* r6f3f20(int);
    float r6f3ff0(int);
    float r6f4010(int);
    float r6f4000(int);
    void  r6f4190(void*);
    void* r6f3fb0(int);
    void  r7c4010(void*);
    void  r7c50b0(int, int, int);
    void  r7c4ad0(float, float);
    void  r7c4ba0(float);
    void  r7c4bc0(float);
    void  r7c4be0(void*, int);
    void  r7c3c50(int);
    void  r7c3cb0(void*);
    void  r7a4420(int, int, int, int);
    int   r7a47c0(int, int, int);
    char  r7a4910(int, int, int, int, int);
    void  r7a4650();
    void* r776420(float, float);
    void  r776440();
    void  r7764a0();
    void  r7764c0(int, int, float, float);
    void  r776520(int, int, float, float);
    void  r776a60(int, void*, void*);
    char  r7773c0(unsigned int, int, int, int);
    char  r7775a0(unsigned int, int, int, int);
};
#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]
struct CCreature {
    char m_unk[0x9c0];
    // 0x006e80d0
    void m80d0(int idx, int a, int b);
    // 0x006e8160
    void m8160(float a, float b);
    // 0x006e8200
    char m8200(char* p, int a);
    // 0x006e82b0
    void m82b0(int a, int b, float c, float d);
    // 0x006e8360
    void m8360(int a);
    // 0x006e83e0
    void m83e0(int a, int* out1, int* out2);
    // 0x006e8420
    void m8420(int a, void* b);
    // 0x006e8480
    void m8480(void* b);
    // 0x006e8810
    void m8810(uint* flags, void** p3, uint* p4);
    // 0x006e8d70 / 0x006e8dd0 forwarders
    void m8d70(int, int, void*, int, int, int, int, int, int);
    void m8dd0(int, int, int, int, void*, int, int, int, int, int, int, int);
    // 0x006e8e40
    void m8e40(int a, int b);
    // 0x006e8ee0
    int  m8ee0(int a, int b, int c);
    // 0x006e8f20
    char m8f20(int a, int b, int c, int d, int e);
    // 0x006e8f60
    u64  m8f60(int a);
};
int f8f50();
struct PropList_s006e_80d0 {
    float F_6a2710(int key);      // 0x6a2710 GetFloatProperty
    int   F_6a2660(int key);      // 0x6a2660 GetIntProperty
    uchar F_6a25a0(int key);      // 0x6a25a0 GetDescription (byte)
};
struct Vec3 { float x, y, z; };
struct Vec28Sink {
    void push76d5c0(int a2, int a3, Vec3 v, int a5, int a6, int a7, int a8, int a9, int a10);
};
struct Vec3Sink {
    void push76d6e0(int a2, int a3, int a4, int a5, Vec3 v, int a7, int a8, int a9, int a10,
                    int a11, int a12, int a13);
};
// ---- items of slice s006e80d0 end

// ---- items of slice s006ea030 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  f67dd70();
extern void   f6e6ee0(void*, int, float, int);
extern void   f6e95a0(void*);
extern void   f6e8e40(int, int);
extern void   f6e6500(void*);
extern void   f6e6710(char, void*, void*);
extern int    f7c4fd0();
extern void   f777bf0();
extern void   f777c10();
extern char   f777c90();
extern void   f7c3c10();
extern void   f6ddde0(int, int);
extern void   f6ddef0(int);
extern void   f777ae0(int, int, int);
extern void   f7789d0();
extern void   f7a3e60(int, int);
extern float  g1533c74;
extern float  g1471064;
extern float  g1533c98;
extern float  g1533c9c;
extern float  g1533ca0;
extern float  g1533ca4;
extern void   f777b50(void*);   // 0x777b50 SP::SetShaderData            (cdecl, 1 arg)
extern void   f11ee580(void*);  // 0x11ee580 rw::graphics::CompiledState::Dispatch (thiscall)
extern void   f11f1280(int, void*); // 0x11f1280 rw::graphics::ActiveState::SetTexture
extern void   f7a4710(void*);   // 0x7a4710 SP::cStaticBuffer::Flush      (thiscall)
extern void   f700120();        // 0x700120 cFrustumCull::FrustumTestSphere (thiscall, 3 args)
extern int    g140afc4;         // 0x140afc4 identity/default quad state
struct E6 {
    void  r537dc0(void*);     // cSPTransform::operator=
    void  r6e6ee0(void*, int, float, int);
    void  r7c4fd0_dummy();
};
extern void** g15ddc84_s006e_a030;      // 0x15ddc84: singleton slot for cStaticBufferDraw
extern uint   g16f8b00;         // 0x16f8b00 raster-delta dirty mask
extern uint   g16f9110;         // 0x16f9110 soft-state dirty mask
struct R70 {
    char m[0x70];
    R70* mabc0(const R70& src);   // 0x6eabc0 copy ctor
    R70* mac80(const R70& src);   // 0x6eac80 assign
};
struct S6 {
    char m_unk[0x380];

    // 0x6ea030 render pass A
    void m030(int a, int b, int c);
    // 0x6ea470 render pass B
    void m470(int a, uint flags, int c, void* viewer);
    // 0x6ea920 EH dtor
    void m920();
    // 0x6ea9e0 setter
    void m9e0(int idx, float* box, float pad);
    // 0x6ead40 transform setter
    void mad40(int idx, void* xf);
};
// ---- items of slice s006ea030 end

// ---- items of slice s006ed2c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VTSLOT(o, off) (*(void**)((char*)(*(void**)o) + (off)))
typedef char     (__thiscall *TFc_v)(void*);
typedef char     (__thiscall *TFc_p)(void*, void*);
typedef void     (__thiscall *TFv_v)(void*);
typedef void     (__thiscall *TFv_i)(void*, int);
typedef void     (__thiscall *TFv_u)(void*, unsigned);
typedef void     (__thiscall *TFv_p)(void*, void*);
typedef unsigned (__thiscall *TFu_v)(void*);
struct IRefCounted {
    virtual void AddRef() = 0;   // vtable +0
    virtual void Release() = 0;  // vtable +4
};
template<class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Release() { T* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
    AutoRefCount& operator=(T* p) { if (mpObject) { T* old = mpObject; mpObject = p; old->Release(); } else mpObject = p; return *this; }
};
template<class T>
struct evec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    char mAllocator[4];
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T& operator[](unsigned n) { return *(mpBegin + n); }
    void push_back(const T& v);
    void erase(T* first, T* last);
};
struct UIntVecInl {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity;
    void DoInsertValue(unsigned* pos, const unsigned& v);   // 0x004558A0
    void push_back(const unsigned& v) {
        unsigned* e = mpEnd;
        if (e < mpCapacity) { mpEnd = e + 1; if (e) *e = v; }
        else DoInsertValue(e, v);
    }
};
struct UIntVecOut {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity;
    void push_back(const unsigned& v);                      // 0x00454860
    void DoInsertValue(unsigned* pos, const unsigned& v);   // 0x004558A0
};
struct cTextureParticleSet {
    char pad0[0x48];
    bool mActive;        // +0x48
    bool mInActiveList;  // +0x49
    char pad1[0x70 - 0x4a];
    void* mabc0(const cTextureParticleSet& v);   // 0x006EABC0 (placement construct)
};
struct cModelParticleSet {
    void* mpRef0;            // +0x00 (intrusive reference-counted object)
    char pad0[0x50 - 0x04];
    bool mActive;            // +0x50
    char pad1[0x5c - 0x51];
    void* mpField5c;         // +0x5c
    IRefCounted* mpField60;  // +0x60
    int mField64;            // +0x64
    void* m6eb8c0(void* p);  // 0x006EB8C0 (destroy-last helper)
    void  m6eac80(void* p);  // 0x006EAC80 (construct/assign helper)
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
};
struct DispatchData { void* p0; void* p1; void* p2; };
class cEffectsModel {
public:
    void* mpVtable;                                  // +0x00
    int   mField4;                                   // +0x04
    evec<DispatchData> mDispatchData;                // +0x08
    void* mDispatchInlinePtr;                        // +0x18
    char  padD0[4];                                  // +0x1c
    char  mDispatchBuf[0x30];                        // +0x20 .. +0x50
    Vector3 mBoxMin;                                 // +0x50
    Vector3 mBoxMax;                                 // +0x5c
    float   mBoundingRadius;                         // +0x68
    AutoRefCount<IRefCounted> mAsyncRequest;         // +0x6c
    evec<AutoRefCount<IRefCounted> > mResourceRefs;  // +0x70
    void* mResInlinePtr;                             // +0x80
    char  padR0[4];                                  // +0x84
    char  mResBuf[0x10];                             // +0x88 .. +0x98

    cEffectsModel(unsigned a, unsigned b, unsigned c, const float* box);  // 6ed8d0
    void AddResourceRef(IRefCounted* p);                                  // 6edaa0
    void Reset();                                                         // 6edb10
    void UpdateFromResource(int* res);                                    // 6edbc0
    char Update();                                                        // 6ee140
    void me90(int a, unsigned b, unsigned c);                             // 0x006ECE90
    void mdd0(int a, int b);                                              // 0x006ECDD0
    void me30(int a, int b, int c);                                       // 0x006ECE30
    void ComputeRadius();
};
class cEffectsRenderer {
public:
    char pad0[0x174];
    evec<cTextureParticleSet> mTextureParticleSets;    // +0x174
    char pad1[4];                                       // +0x184
    evec<unsigned short> mActiveTextureParticleSets;   // +0x188
    char pad2[0x1b8 - 0x198];
    cModelParticleSet* mModelBegin;      // +0x1b8
    cModelParticleSet* mModelEnd;        // +0x1bc
    cModelParticleSet* mModelCapacity;   // +0x1c0
    char pad3[0x1cc - 0x1c4];
    UIntVecOut mFreeIDs;                 // +0x1cc
    char pad4[0x1e0 - 0x1d8];
    IRefCounted* mSys1e0;                // +0x1e0

    void SetTextureParticleActive(int index, bool active);   // 6ed2c0
    void RemoveParticleSet(int index);                       // 6ed340
};
struct cEffectsKeyedList {
    char pad0[0x0c];
    void* mpObj0c;        // +0x0c
    UIntVecInl mIds;      // +0x10
    int ActivateByKey(unsigned a, unsigned b);   // 6ed440
};
void cEffectsModel::ComputeRadius()
{
    float bx = mBoxMax.x, by = mBoxMax.y, bz = mBoxMax.z;
    float nx = -mBoxMin.x, ny = -mBoxMin.y, nz = -mBoxMin.z;
    float xf = (bx <= nx) ? nx : bx;
    float yf = (by <= ny) ? ny : by;
    float zf = (bz <= nz) ? nz : bz;
    float m = (yf <= xf) ? xf : yf;
    if (m <= zf && zf != m)
        m = zf;
    mBoundingRadius = m;
}
// ---- items of slice s006ed2c0 end

// ---- items of slice s006ef990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00762a60(void* p);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* CreateTestModel();
extern "C" void* FUN_007c3af0(const char* s);
extern "C" void* FUN_00762b70(void* p, int a, int b, int c);
struct Dispatch3 { void* p0; void* p1; void* p2; };   // 0xc
struct cEffectsModelR {
    void** mpVtable;      // +0x00
    int    mnRefCount;    // +0x04
    Dispatch3* mpBegin;   // +0x08
    Dispatch3* mpEnd;     // +0x0c

    void Reset();         // 6edb10
};
struct cEffectsModel2;
class cEffectsRendererSystem {
public:
    char pad0[4];
    cEffectsModel2* mpModel;        // +0x04
    char pad1[0x30d50 - 0x08];
    void* mAt30d50;                 // +0x30d50
    void* mAt30d54;                 // +0x30d54  (vector begin)
    void* mAt30d58;                 // +0x30d58  (vector end)
    char pad2[0x30d68 - 0x30d5c];
    void* mAt30d68;                 // +0x30d68
    void* mAt30d6c;                 // +0x30d6c
    char pad3[0x30d7c - 0x30d70];
    void* mAt30d7c;                 // +0x30d7c
    void* mAt30d80;                 // +0x30d80
    int   mAt30d84;                 // +0x30d84

    bool Init();                    // 6ef9e0
    char Shutdown();                // 6efa90
private:
    void* SetDeviceState();
    void* GetImageResource(void*);
    void  FUNecf10(int);
};
struct cERSDtor;
extern cERSDtor* g_pEffectsRendererSystem;   // DAT_01618d10
void* CreateMesh(int n);           // SP::CreateMesh
struct MeshStub {
    void FUN96e0(int);
    void FUN9670(int, void*);
};
struct cEffectsModel2 {
    void** mpVtable;    // +0
    int    mnRefCount;  // +4
};
struct cERSDtor { void Shutdown(); ~cERSDtor(); };
// ---- items of slice s006ef990 end

// ---- items of slice s006f0890 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_softStateDirty;     // 0x016f9528
extern "C" void* __cdecl MoveShorts(void* dst, const void* src, unsigned n);  // 0x011e0744
extern unsigned g_samplerA;           // 0x016f9530
extern unsigned g_samplerB;           // 0x016f9534
extern unsigned g_renderDirty;        // 0x016fa38c
extern unsigned g_renderDirty2;       // 0x016fa39c
extern int g_s0;  // 0x016f9fe0
    extern int g_s1; // 0x016f9fdc
    extern int g_s2; // 0x016f9fe4
    extern int g_s3; // 0x016fa018
    extern int g_s4; // 0x016fa014
    extern int g_s5; // 0x016fa01c
extern int g_s6;  // 0x016f9238
extern int g_fogType;                 // 0x016f9f7c
extern int g_r250, g_r410;            // 0x016f9250, 0x016f9410
extern int g_b218;  // 0x016f9218
extern int g_b23c;  // 0x016f923c
extern int g_b21c;  // 0x016f921c
extern int g_b244;  // 0x016f9244
extern int g_b240;  // 0x016f9240
void* __cdecl EaNew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void __cdecl EaDelete(void* p);  // 0x00f47380
struct RcObj {
    void* vt;
    int pad;
    long rc;
    void Release()
    {
        long* p = &rc;
        _InterlockedExchangeAdd(p, -1);
        long n = _InterlockedExchangeAdd(p, 0);
        if (n < 1)
            _InterlockedExchangeAdd(p, 1);
        else
            _InterlockedExchangeAdd(p, 0);
    }
};
struct ImageRef {
    RcObj* p;
    ImageRef() : p(0) {}
    ~ImageRef() { if (p) p->Release(); }
    void Assign(RcObj* o);  // 0x00576650
};
struct IMessageServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void RemoveListener(void* handler, unsigned msgId, int mask);  // +0x2c
};
struct IFlagSink {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual void SetFlag(int f);  // +0x50
};
struct IObj1 { virtual void v0(); virtual void Release1(); };                       // slot 1
struct IObj3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void Release3(); };
struct IObj5 {
virtual void v0();
virtual void v1();
virtual void Release2();
virtual void v3();
virtual void v4();
virtual void Flush();
};  // Release2 +8, Flush +0x14
struct Viewer24 {
    char pad[8];
    IObj3 sub;
    void Teardown();  // 0x0076b000
};
struct SubObj {  // 0x24c/0x250/0x254 members
    void Cleanup();  // 0x007c3ba0
    void Dtor();     // 0x007c4000
};
extern IMessageServer* __cdecl MessageServer();      // 0x0067dcc0
extern IFlagSink* __cdecl GetFlagSink();             // 0x0067dd50
struct P8 { int a, b; };
struct V8 {
    P8* mpBegin;
    P8* mpEnd;
    int pad[3];
    __forceinline void Erase(P8* first, P8* last)
    {
        P8* d = first;
        P8* e0 = mpEnd;
        for (P8* s = last; s != e0; ++s, ++d) {
            d->a = s->a;
            d->b = s->b;
        }
        mpEnd += -(last - first);
    }
};
struct E70 {
    char d[0x70];
    E70();                       // 0x006e9b00
    ~E70();                      // 0x006ea920
    void Assign(const E70* o);   // 0x006ebb80
    void Copy(const E70* o);     // 0x006eabc0
};
struct TextRenderer {
    void Release();  // 0x007a8530
};
struct VE70 {  // vector of 0x70-byte elements, erase with assignment + dtor
    E70* mpBegin;
    E70* mpEnd;
    __forceinline void Erase(E70* first, E70* last)
    {
        E70* d = first;
        E70* e0 = mpEnd;
        for (E70* s = last; s != e0; ++s, ++d)
            d->Assign(s);
        E70* e = mpEnd;
        for (; d < e; ++d)
            d->~E70();
        mpEnd += (last - first);
    }
};
struct V70Owner {  // object at +0x174 (this for 0x6eb990)
    E70* mpBegin;
    E70* mpEnd;
    void DestroyRange(E70* first, E70* last);  // 0x006eb990
    __forceinline void Erase(E70* first, E70* last)
    {
        E70* d = first;
        E70* e0 = mpEnd;
        for (E70* s = last; s != e0; ++s, ++d)
            d->Copy(s);
        DestroyRange(d, mpEnd);
        mpEnd += (last - first);
    }
};
struct VShort {
    short* mpBegin;
    short* mpEnd;
    __forceinline void Erase(short* first, short* last)
    {
        MoveShorts(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd += -(last - first);
    }
};
struct Effects890 {
    char pad0[0x14];
    char handler[4];
    int m18, m1c;
    int m20;
    Viewer24* mViewer;           // +0x24
    IObj3* m28;                  // +0x28
    char pad2c[0x40 - 0x2c];
    IObj1* m40;                  // +0x40
    char pad44[4];
    VE70 mSets;                  // +0x48
    char pad50[0x5c - 0x50];
    VShort mAct;                 // +0x5c
    char pad64[0x104 - 0x64];
    V8 mDrawLists[4];            // +0x104 (stride 0x14)
    char pad154[0x174 - 0x154];
    V70Owner mV174;              // +0x174
    char pad17c[0x188 - 0x17c];
    VShort mFree;                // +0x188
    char pad190[0x1b0 - 0x190];
    int m1b0, m1b4;
    char pad1b8[0x204 - 0x1b8];
    TextRenderer mText;          // +0x204
    char pad208[0x24c - 0x208];
    SubObj* m24c;
    SubObj* m250;
    SubObj* m254;
    char pad258[0x360 - 0x258];
    IObj5* m360;
    IObj5* m364;
    char pad368[1];
    bool m369;

    bool Shutdown();
};
extern unsigned g_softStateDirty_s006f_0890;     // 0x016f9528
void __cdecl SetBlendMode(int mode);  // 0x011f1340
struct D3DCaps { char pad[0xc4]; unsigned c4; char pad2[4]; unsigned cc; };
D3DCaps* __cdecl GetD3DCAPS9();       // 0x011f8af0
struct ViewIface {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void v8();
    virtual void SetView(int v);  // +0x24
};
struct IStateSink {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual void SetTarget(void* t);  // +0x50
};
extern IStateSink* __cdecl GetStateSink();  // 0x0067ddc0
struct Prop {
    char pad[0x10];
    unsigned char flags;
    char pad2;
    unsigned short type;
};
struct IProps {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void v8();
    virtual bool Get(unsigned key, Prop** out);  // +0x24
};
extern struct PropList* g_pProps;  // 0x015fd918
struct PropList : IProps {
    float GetFloatProperty(unsigned key);  // 0x006a2710
};
struct Viewer250 {
    void Copy(int src, int a, int b);  // 0x007c50b0 (static-like: this = viewer)
    float GetA();                      // 0x007c3c90
    float GetB();                      // 0x007c3ca0
    void SetA(float f);                // 0x007c4ba0
    void SetB(float f);                // 0x007c4bc0
};
struct Region {
    int a, b, c, d;
};
struct CamBlock {
    void SetA(float f);  // 0x006ffa80 (this = renderer+0x260)
    void Set(const void* p);  // 0x006ffe00
};
struct Effects0B90 {
    char pad0[0x44];
    struct Inner { char pad[0x110]; bool m110; }* m44;
    char pad48[0x5c - 0x48];
    short* m5c;
    short* m60;
    char pad64[0x188 - 0x64];
    int m188, m18c;
    char pad190[0x1e0 - 0x190];
    ViewIface* m1e0;
    char pad1e4[0x250 - 0x1e4];
    Viewer250* m250;
    char pad254[0x260 - 0x254];
    CamBlock m260;

    void Render(unsigned flags, Region** pr, int arg);
    void DispatchWithAdditionalMaterial(unsigned flags, Region** pr, int arg);  // 0x006ee6f0
    void Pass2(unsigned flags, Region** pr, int arg);                           // 0x006efc70
    void RenderTextureParticles(unsigned flags, Region* pr, int arg);           // 0x006efe90
    void Pass40(unsigned flags, Region** pr, int arg);                          // 0x006e78b0
    void Pass80(unsigned flags, Region** pr, int arg);                          // 0x006ea030
};
struct MatPair { int a, b; };
struct IMatMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual int Find(int lo);  // +0x28
};
struct IResMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual RcObj* Get(int lo, int hi, int flag);  // +0x20
};
extern IMatMgr* __cdecl MaterialManager();    // 0x0067dd70
extern IResMgr* __cdecl ResourceManager();    // 0x0067dd60
extern RcObj** g_defaultImage;                // 0x01618d10
struct MatCache {
    MatPair* Find(int lo, int hi);   // 0x006f2050
    RcObj* GetImg(int lo, int hi);   // 0x006e65e0
};
struct SetDesc {
    int lo, hi;
    char pad8;
    unsigned char kind;   // +9
    unsigned char fl;     // +0xa
    char padb[0x18 - 0xb];
    int lo2, hi2;
    char rest[0x20 - 0x20];
};
struct Effects0FB0 {
    char pad0[0x40];
    MatCache* m40;
    char pad44[4];
    E70* mSetsBegin;        // +0x48
    E70* mSetsEnd;          // +0x4c
    char pad50[0x70 - 0x50];
    int* mFreeBegin;        // +0x70
    int* mFreeEnd;          // +0x74
    char pad78[0x84 - 0x78];
    int mMat84[0x10];       // +0x84
    int mMatC4[0x10];       // +0xc4
    char pad104[0x1e4 - 0x104];
    bool m1e4;

    bool AddParticleSet(int id, const SetDesc* d, int* outIndex);
};
void PushSet(E70** vec, const E70* v);  // 0x006f0810
struct IEffectsMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
    virtual int GetDefault();  // +0xa0
};
extern IEffectsMgr* __cdecl EffectsManager();  // 0x0067ddd0
struct IPassA {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual void Render(unsigned flags, unsigned type, int a, int b);  // +0xc
};
struct App3c { char pad[0xc]; int m0c; };
struct AppProps_s006f_0890 { char pad[0x3c]; App3c* m3c; };
extern AppProps_s006f_0890* g_app;  // 0x015fd918
struct PassB {
    bool Ready();  // 0x007764b0
    void Render(unsigned flags, unsigned type, int a, int b);  // 0x00776e60
};
struct cEffectsRendererLayer {
    char pad0[0x2c];
    int mAt2c;
    char pad1[0x344 - 0x30];
    IPassA* mAt344;
    char pad2[0x34c - 0x348];
    PassB* mAt34c;
    char pad3[0x354 - 0x350];
    int mAt354;

    void RenderMainEffectsLayer(unsigned flags, unsigned type, int a, int b);
};
struct EffectsOuter {
    void RenderTex(unsigned flags, int a, int b);  // 0x006e8810
    void RenderMain(unsigned flags, int a, int b); // 0x006f0b90
};
struct Elt {
    int f0;
    char* m4;
    int f8;
    char* mC;
    int f10;
    char* m14;
    char rest[0xc0 - 0x18];
    Elt();                               // 0x006ec730
    Elt(const Elt& o);                   // 0x006ecaa0
    Elt& operator=(const Elt& o);        // 0x006ecfc0
    ~Elt()
    {
        if (((int)(mC - m4) & ~1) > 2 && m4 && m4 != m14)
            EaDelete(m4);
    }
};
Elt* __cdecl EltCopyBackward(Elt* first, Elt* last, Elt* dstEnd);  // 0x006ed890
Elt* __cdecl EltUninitCopy(Elt* first, Elt* last, Elt* dst);       // 0x006ecd40
void __cdecl EltDestroyRange(Elt* first, Elt* last, Elt* dst);     // 0x006ec6d0
struct EltVector {
    Elt* mpBegin;
    Elt* mpEnd;
    Elt* mpCapacity;
    void Insert(Elt* pos, const Elt* val);
    void PushBack();
};
// ---- items of slice s006f0890 end

// ---- items of slice s006e8f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  f67dd40();
extern void   f6e6e90(const float* src, float* dst);   // copies |m| of a 3x3 (nine floats)
extern char   g13ec47c;
extern void*  g1618f60;
extern "C" double sqrt(double);
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchangeAdd)
struct E5 {
    void  r7c5350(float);
    void  r7c4ba0(float);
    void  r7c4bc0(float);
    int   r7c4010(void*);
    void  r41cb40(void*);     // rw::math::Matrix33::Assign
    void  r76c210(int);
    void  r76ba30(int, int, int, int, int, int, int, int, int, int, int, int);
    void  r7c50b0(int, int, int);
};
struct S5 {
    char m_unk[0x240];

    // 0x6e8f90
    void m8f90(float a, float b, float c, unsigned char flags);
    // 0x6e9120
    int  m9120(uint a, uint b);
    // 0x6e9150
    void m9150(int i);
    // 0x6e91c0
    void m91c0();
    // 0x6e91e0
    void m91e0(int a, int b);
    // 0x6e9230
    void m9230(void* src);
    // 0x6e9330
    void m9330(void* src);
    // 0x6e94a0 (free, but declared here for convenience) -- not used
    // 0x6e9530 -- returns this (original: mov eax, ecx)
    S5* m9530();
    // 0x6e95a0
    void m95a0(unsigned char* p);
    // 0x6e9910
    void m9910(float d);
    // 0x6e9990
    void m9990();
    // 0x6e9a30
    void m9a30();
    // 0x6e9b00
    S5* m9b00();
    // 0x6e9bf0
    S5* m9bf0();
    // 0x6e9cc0
    void* m9cc0();
    // 0x6e9d50
    void m9d50(void* out);
};
int f94a0(int p1, int p2, int p3);
struct RefObj_s006e_8f90 {
    char pad[8];
    volatile long ref;
};
struct RefP {
    RefObj_s006e_8f90* p;
    RefP(const RefP& o) : p(o.p) {
        if (p)
            _InterlockedIncrement(&p->ref);
    }
    ~RefP() {
        RefObj_s006e_8f90* q = p;
        if (q) {
            _InterlockedDecrement(&q->ref);
            if (_InterlockedExchangeAdd(&q->ref, 0) < 1) {
                _InterlockedIncrement(&q->ref);
                return;
            }
            _InterlockedExchangeAdd(&q->ref, 0);
        }
    }
};
struct Iface4 {
    virtual void v0();
    virtual void AddRef();
    virtual void v2();
    virtual void v3();
};
struct RawRef {
    Iface4* p;
    RawRef(const RawRef& o) : p(o.p) {
        if (p)
            p->AddRef();
    }
};
struct Blob32 {
    int a[8];
};
struct C9230 {
    int m0;
    char pad4[4];
    Blob32 m8;
    RefP m28;
    RefP m2c;
    float f30, f34, f38, f3c, f40, f44;
    uchar b48, b49;
    char pad4a[2];
    float f4c, f50, f54, f58;
    int d5c, d60, d64, d68;
    RawRef r6c;
    C9230(const C9230& o);
};
struct Bounds6 {
    float minX;                  // +0x00
    float minY;                  // +0x04
    float minZ;                  // +0x08
    float maxX;                  // +0x0c
    float maxY;                  // +0x10
    float maxZ;                  // +0x14
};
struct UnitBox {
    uchar flags;                 // +0x00  bit 1 selects the matrix path
    uchar pad00[3];
    float centreX;               // +0x04
    float centreY;               // +0x08
    float centreZ;               // +0x0c
    float scale;                 // +0x10
    float absMatrix[9];          // +0x14  f6e6e90 copies |m| of the 3x3 here
};
struct ProjMatrix {
    float m00, m01, m02, m03;    // +0x100
    float m10, m11, m12, m13;    // +0x110
    float m20, m21, m22, m23;    // +0x120
    float m30, m31, m32, m33;    // +0x130
};
struct FrameTail {
    float viewport[3];           // +0x98  copy of the block's own +0x80 viewport origin (float bits)
    float dirX;                  // +0xa4
    float dirY;                  // +0xa8
    float dirZ;                  // +0xac
    uchar hasDir;                // +0xb0
    uchar padB1[3];              // +0xb1
    int   frame;                 // +0xb4
    int   frameTag;              // +0xb8
};
struct RefT {
    void* p;
    ~RefT() {
        if (p)
            ((Iface4*)((char*)p + 8))->v3();
    }
};
struct C9990 {
    void* m4;
    RefT m8;
    void* mC;
    void* m10;
    virtual ~C9990();
};
struct C9A30 {
    RefP m0;
    int* m4;
    char pad[0x30d54 - 8];
    void* m30d54;
    char pad2[0x10];
    void* m30d68;
    ~C9A30();
};
// ---- items of slice s006e8f90 end

// ---- items of slice s006eae40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void   f_f47380(void*);
extern void   f7c4d00(int);
extern int  g_16f921c, g_16f9244, g_16f9240;
static inline Vec3 MakeV3(float c) { Vec3 v; v.x = c; v.y = c; v.z = c; return v; }
struct E7 {
    void GetImageResource(void*);   // refcount-copy helper (0x576650)
    void r41cb40(void*);            // rw::math::Matrix33::Assign
};
void __stdcall f990(char* p1, char* p2);             // 0x6eb990
void f9d0(uint* p1, uint* p2, int extra);            // 0x6eb9d0
void fbe50(uint* p1, uint* p2, uint v);              // 0x6ebe50
void fbea0(uint* p1, uint* p2, uint* p3, int p4);    // 0x6ebea0
extern void f_ac2060(uint*, int, int, int, uint, uint, int);
extern void f_ac3fa0(uint*, uint*, int);
struct CEM7 {
    char m[0x20];
    void UpdateCameraView(int a, uint flags);
};
struct S7 {
    char m_unk[0x240];
    void m6eb8c0(void* src);
    S7*  m6ebb80(void* src);
    S7*  mebf50();
    void mec090();
};
struct RefCounted {
    virtual void v0();
    int mRefCount;                     // +0x4 (bumped by the +0x00 member's inlined copy)
};
struct RefCountedVirt {                // +0x60 member: its copy calls vtable slot 0
    virtual void v0();
    int mRefCount;
};
struct SmartPtrRef {
    RefCounted* mp;
    SmartPtrRef() : mp(0) {}
    SmartPtrRef(const SmartPtrRef& o) : mp(o.mp) { if (mp) mp->mRefCount++; }
    ~SmartPtrRef() { if (mp) mp->mRefCount--; }
};
struct SmartPtrVirt {
    RefCountedVirt* mp;
    SmartPtrVirt() : mp(0) {}
    SmartPtrVirt(const SmartPtrVirt& o) : mp(o.mp) { if (mp) mp->v0(); }
    ~SmartPtrVirt() { if (mp) mp->mRefCount--; }
};
struct Matrix33 {                      // +0x2c (copy constructor 0x0041cb40, out of line)
    float m[9];
    Matrix33(const Matrix33&);
};
struct RenderEntity {
    SmartPtrRef  mBase;                // +0x00
    float        mF4, mF8, mFC, mF10, mF14;   // +0x04
    unsigned short mW18, mW1A;         // +0x18
    float        mG1C, mG20, mG24, mG28;      // +0x1c
    Matrix33     mMat;                 // +0x2c
    char         mA;                   // +0x50
    char         mB;                   // +0x51
    int          mI0, mI1, mI2;        // +0x54
    SmartPtrVirt mExtra;               // +0x60
    int          mI3;                  // +0x64
    RenderEntity(const RenderEntity& src);
};
struct RefBase {
    void* mpTable;                     // +0x00  dispatch table (0x013ef094)
    int   mRefCount;                   // +0x04
    ~RefBase() { mpTable = (void*)0x013ef094; }
};
void __cdecl FreeBlock(void* p) throw();       // 0x00f47380 (operator delete)
struct FixedVec {
    void* mpBegin;                     // +0x00
    void* mpEnd;                       // +0x04
    void* mpCap;                       // +0x08
    void* mpReserved;                  // +0x0c
    void* mpInline;                    // +0x10
    ~FixedVec() { if (mpBegin && mpBegin != mpInline) FreeBlock(mpBegin); }
};
struct SmartRef {
    void* mp;
    ~SmartRef() { if (mp) ((void(__thiscall*)(void*))VFN(mp, 4))(mp); }
};
struct PropVec {
    void* mpBegin; void* mpEnd; void* mpCap; void* mpReserved; void* mpInline;
    ~PropVec();
};
struct FxEntity : RefBase {
    FixedVec  mCont;                   // +0x08
    int       mGap1C;                  // +0x1c
    int       mInline[12];             // +0x20
    Vec3      mV50;                    // +0x50
    Vec3      mV5C;                    // +0x5c
    float     mF68;                    // +0x68
    SmartRef  mPtr6C;                  // +0x6c
    PropVec   mProp;                   // +0x70
    ~FxEntity();
};
struct V3 {                                                         // 3 floats with a user copy ctor (movss copies)
    float x, y, z;
    V3() {}
    V3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    V3(const V3& o) : x(o.x), y(o.y), z(o.z) {}
};
__declspec(align(16)) struct Vector4 {
    union {
        __m128 m;
        struct { float x, y, z, w; };
    };
    Vector4() {}
    Vector4(float ax, float ay, float az, float aw) { m = _mm_set_ps(aw, az, ay, ax); }
    Vector4(const Vector4& o) : m(o.m) {}
    Vector4& operator=(const Vector4& o) { m = o.m; return *this; }
};
struct IDirect3DDevice9 {
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
virtual void pv6();
virtual void pv7();
virtual void pv8();
virtual void pv9();
virtual void pv10();
virtual void pv11();
virtual void pv12();
virtual void pv13();
virtual void pv14();
virtual void pv15();
virtual void pv16();
virtual void pv17();
virtual void pv18();
virtual void pv19();
virtual void pv20();
virtual void pv21();
virtual void pv22();
virtual void pv23();
virtual void pv24();
virtual void pv25();
virtual void pv26();
virtual void pv27();
virtual void pv28();
virtual void pv29();
virtual void pv30();
virtual void pv31();
virtual void pv32();
virtual void pv33();
virtual void pv34();
virtual void pv35();
virtual void pv36();
virtual void pv37();
virtual void pv38();
virtual void pv39();
virtual void pv40();
virtual void pv41();
virtual void pv42();
virtual void pv43();
virtual void pv44();
virtual void pv45();
virtual void pv46();
virtual void pv47();
virtual void pv48();
virtual void pv49();
virtual void pv50();
virtual void pv51();
virtual void pv52();
virtual void pv53();
virtual void pv54();
virtual void pv55();
virtual void pv56();
virtual void pv57();
virtual void pv58();
virtual void pv59();
virtual void pv60();
virtual void pv61();
virtual void pv62();
virtual void pv63();
virtual void pv64();
virtual void pv65();
virtual void pv66();
virtual void pv67();
virtual void pv68();
virtual void pv69();
virtual void pv70();
virtual void pv71();
virtual void pv72();
virtual void pv73();
virtual void pv74();
virtual void pv75();
virtual void pv76();
virtual void pv77();
virtual void pv78();
virtual void pv79();
virtual void pv80();
virtual void pv81();
virtual void pv82();
virtual void pv83();
virtual void pv84();
virtual void pv85();
virtual void pv86();
virtual void pv87();
virtual void pv88();
virtual void pv89();
virtual void pv90();
virtual void pv91();
virtual void pv92();
virtual void pv93();
virtual void pv94();
virtual void pv95();
virtual void pv96();
virtual void pv97();
virtual void pv98();
virtual void pv99();
virtual void pv100();
virtual void pv101();
    virtual long __stdcall SetStreamSourceFreq(uint stream, uint setting);   // +0x198
};
struct ModelInstance {
    Vector4 mRow[4];     // +0x00 transform; row 3 holds the translation
    uint    mColor[4];   // +0x40 RGBA
};
struct VertexBuffer {
    char pad00[8];
    uint mStart;                                                    // +0x08
    int  Lock(int type, void** ppData, int* pStart, int start, int count);   // 0x006dd250
    void Unlock();                                                  // 0x011f36a0
};
struct RenderState {                                                // object at g+0x30d7c
    char pad00[0x1c];
    int  mField1c;
    int  mField20;
    void SetA(int v);                                               // 0x011f96e0
    void SetB(int v);                                               // 0x011f96b0
    void SetC(int a, int b);                                        // 0x011f9670
    void Draw();                                                    // 0x011f9710
};
struct RenderCtx {                                                  // *0x01618d10
    char pad00[0x10];
    ModelInstance mInstances[1];                                    // +0x10, stride 0x50
    char padRest[0x30d7c - 0x10 - 0x50];
    RenderState*  mState;                                           // +0x30d7c
    VertexBuffer* mVB;                                              // +0x30d80
    uint          mUsed;                                            // +0x30d84
};
extern RenderCtx* g_pCtx;                                           // 0x01618d10
struct ShaderDataItem { char pad[8]; void Push(); };                // 0x007789d0 (thiscall)
struct EmbeddedState_s006e_ae40 {
    char pad00[4];
    uint mState;                                                    // +0x04
    uint mSoftStateDirty;                                           // +0x08
    void D3D9SetTransform(const void* m, int slot, int flag);       // 0x011edc10
    void Dispatch();                                                // 0x011ee580 (CompiledState::Dispatch)
};
struct DrawData {                                                   // per-dispatch draw description
    char pad00[8];
    int  mField08;                                                  // +0x08
    char pad0c[0xc];
    int  mField18;                                                  // +0x18
    char pad1c[8];
    struct { char pad[0xc]; int mField0c; }* mpField24;             // +0x24
};
struct StateHolder { char pad[4]; EmbeddedState_s006e_ae40* mpState; };        // +0x04
struct DispatchPair {                                               // 12-byte dispatch entry
    DrawData*       mpData;                                         // +0x00
    StateHolder*    mpHolder;                                       // +0x04
    ShaderDataItem* mpShader;                                       // +0x08
};
struct ModelBase {                                                  // SP::cEffectsModel
    char pad00[8];
    DispatchPair* mDispatchBegin;                                   // +0x08
    DispatchPair* mDispatchEnd;                                     // +0x0c
    char pad10[0x40];
    Vec3 mBoxMin;                                                   // +0x50
    Vec3 mBoxMax;                                                   // +0x5c
    void DispatchWithAdditionalMaterial(int material);              // 0x006e7110
    void DispatchList(void* list, int material);                    // 0x006e73d0
};
struct FrustumCull {
    uint FrustumTestSphere(const V3* mn, const V3* mx, int flags);   // 0x00700120
};
struct AppConfig { char pad[0xe0]; float mMinAlpha; };
struct AppProps { char pad[0x3c]; AppConfig* mConfig; };
extern AppProps* sAppProperties;                                    // 0x015fd918
struct ColorRGBA { uint r, g, b, a; };
extern ColorRGBA g_whiteColor;                                      // 0x0140afc4
extern ColorRGBA g_color;                                           // 0x016f96a8
extern uint g_renderStateDirty;                                     // 0x016fa38c
extern uint g_softStateDirty;                                       // 0x016f9528
void  __cdecl SetBlendMode(uint mode);                              // 0x011f1340
uint  __cdecl ColorRGBAToU32(const void* rgba);                     // 0x004580c0
void  __cdecl EffectsDispatch(const void* m, int mode);            // 0x005291f0
bool  __cdecl PushShaderDataNull();                                 // 0x00777bf0
void  __cdecl PopShaderData();                                      // 0x00777c10
void  __cdecl SetShaderData(EmbeddedState_s006e_ae40* s);                      // 0x00777b50
void  __cdecl SetVertexDescriptor(void* vdesc);                     // 0x007611a0
void  __cdecl VertexDescriptorChange(void* vdesc);                  // 0x006dd2a0
extern IDirect3DDevice9* g_d3dDevice;                               // 0x016f89d0
struct EffectsRenderer {
    char pad000[0x14c];
    void* mCurrentVDesc;                                            // +0x14c
    char pad150;
    bool  mCanUseInstancing;                                        // +0x151
    char pad152[6];
    int   mMinInstancingCount;                                      // +0x158
    int   mBufferedCount;                                           // +0x15c
    int   mFlag160;                                                 // +0x160
    char pad164[0x1a8 - 0x164];
    ModelBase* mModel;                                              // +0x1a8
    void*      mList;                                               // +0x1ac
    char pad1b0[0x258 - 0x1b0];
    FrustumCull mFrustum;                                           // +0x258
    char pad25c[0x364 - 0x259];
    int   mMaterial;                                                // +0x364
    char pad368[4];
    int   mCounter36c;                                              // +0x36c
    int   mCounter370;                                              // +0x370

    int ReleaseAndDrawModelBuffer();                                // 0x006eae40
};
static inline Vector4 GetRow(const ModelInstance& m, int i) { return m.mRow[i]; }
static inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
struct Box3 { V3 mMin, mMax; };
// ---- items of slice s006eae40 end

// ---- items of slice s006ec0c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int    f_7c3af0(int);
extern void   f_6ebd20(int, int);
extern void   f_6f66a0(int*);
extern void   f_grow4(void*, int*);
extern void*  f_f47380_s006e_c0c0(void*);
extern int    f_ac3fa0_s006e_c0c0(uint*, uint*, int);
extern int    f_6ebe50(uint*, int, uint, uint, int);
struct VecC {
    int* b;
    int* e;
    int* cap;
    void DoInsert(int* pos, int* v);   // 0x6ec260
};
// Inline small-string storage helper (thiscall, two int args).
struct SmallStrObj {
    void FUN_006ebd20(int a, int b);   // 0x006ebd20
};
// eastl::vector<unsigned int> (grow path lives in 0x4558a0).
struct VecU32_s006e_c0c0 {
    int* b;
    int* e;
    int* cap;
    void DoInsertValue(int* pos, const int* v);   // 0x004558a0
};
// cVecU16 (end at +4, capacity at +8; this = object+0x5c).
struct VecU16_s006e_c0c0 {
    ushort* b;
    ushort* e;
    ushort* cap;
    void FUN_006f66a0(const ushort* v);   // 0x006f66a0
};
struct S8 {
    char m_unk[0x30d80];

    void m0c0(int a, int b, int c, int d, int e, void* f);  // 0x6ec0c0
    void mecc0();                                           // 0x6ec0c0 helper? (unused)
    void m260();                                            // placeholder
    void m4a0();                                            // 0x6ec4a0 (declared via VecC helper)
    void m660(void* src);                                   // 0x6ec660
    S8*  m730();                                            // 0x6ec730
    void m840(int a, int b);                                // 0x6ec840
    void m8a0();                                            // 0x6ec8a0
    void maa0();                                            // 0x6ecaa0
    void mb40();                                            // 0x6ecb40
    void mdd0(int a, int b);                                // 0x6ecdd0
    void me30(int a, int b, int c);                         // 0x6ece30
    void me90(int n, int* a, int* b);                       // 0x6ece90
    void mf10();                                            // 0x6ecf10
    S8*  mfc0(void* src);                                   // 0x6ecfc0 (returns this)
    void md070();                                           // 0x6ed070
    void md1a0(int idx, char v);                            // 0x6ed1a0
    void md210(int idx);                                    // 0x6ed210
};
int  __cdecl f6d0(int p1, int p2, int p3);     // 0x6ec6d0
void __stdcall fca50(char* p1, char* p2);      // 0x6eca50
void f5b0(uint* p1, int p2, int p3, int p4);   // 0x6ec5b0
// ---- items of slice s006ec0c0 end

// ---- items of slice s006ee1f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);
extern "C" void  __stdcall _eh_vector_ctor(void* p, unsigned sz, unsigned n,
                                           void (__stdcall* ctor)(void*),
                                           void (__stdcall* dtor)(void*));   // ??_L
extern "C" void  __stdcall _eh_vector_dtor(void* p, unsigned sz, unsigned n,
                                           void (__stdcall* dtor)(void*));   // ??_M
extern "C" void  __cdecl operator_delete(void* p);                          // 0xf47380
extern "C" void  FUN_006eca50(void* first, void* last);                     // vector<inner> dt
extern "C" void  FUN_006ec1f0(void* self);                                  // +0x48 subobject
extern "C" void  FUN_006ebcb0(void* self);                                  // +0x1b8 subobject
extern "C" void  FUN_006ebc50(void* self);                                  // +0x174 subobject
extern "C" void  FUN_006e9990(void* self);                                  // subobject at +0x1c
extern "C" void  FUN_006ec730(void* out);                                   // temp build into [esp+4]
extern "C" void  FUN_006ecfc0(void* dst, void* src);                        // temp assign
extern "C" void  FUN_006ecb40(void* end, unsigned extra, const void* val);  // vector<bool> grow
extern "C" void* operator_new_graphics(unsigned n, const char* name,
                                       int a, int b, const char* file, int line);
extern "C" void  FUN_007a8790(void);          // cTextRenderer::~cTextRenderer (this=ecx)
struct IRefObj {                       // refcount at slot 1 (vtable+4)
    virtual void v0();
    virtual int  Release();            // slot 1
};
struct IWeakObj {                      // weak-release at slot 2 (vtable+8)
    virtual void v0();
    virtual void v1();
    virtual void Release();            // slot 2
};
struct cTextRenderer {                 // SP::cTextRenderer at +0x204
    char pad[0x100];
    cTextRenderer();                   // 0x7a8390
    ~cTextRenderer();                  // 0x7a8790
};
template<class T>
struct evec_s006e_e1f0 {
    T*   mpBegin;      // +0x00
    T*   mpEnd;        // +0x04
    T*   mpCapacity;   // +0x08
    char mAllocator[4];// +0x0c
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void DoInsertValue(T* pos, const T& v);   // 0x4558a0
};
class cEffectsRenderer_s006e_e1f0 {
public:
    // --- base vptrs (-0x00..-0x1c) ---
    void* vptr00;                     // +0x000
    void* vptr04;                     // +0x004
    void* vptr08;                     // +0x008
    void* vptr0c;                     // +0x00c
    uint32_t f10;                     // +0x010
    void* vptr14;                     // +0x014
    void* vptr18;                     // +0x018
    void* vptr1c;                     // +0x01c
    uint32_t f20, f24, f28, f2c, f30, f34;   // +0x020..+0x037
    IRefObj* p40;                     // +0x040
    uint32_t f44, f48, f4c, f50;      // +0x044..+0x053
    uint32_t f54;                     // +0x054
    uint32_t f58;                     // +0x058
    void*   p5c;                      // +0x05c
    uint32_t f60, f64;                // +0x060,+0x064
    uint32_t pad68;                   // +0x068
    void*   p70;                      // +0x070
    uint32_t f74, f78;                // +0x074,+0x078
    uint8_t  pad7c[0x104 - 0x7c];

    uint8_t  mVec104[0x50];           // +0x104  EH vector: 4 x 0x14 bytes

    uint32_t pad154_0;                // +0x154
    uint8_t  b158;                    // +0x158
    uint8_t  b159;                    // +0x159
    uint8_t  pad15a[2];
    uint32_t n15c;                    // +0x15c = 3000
    uint32_t n160;                    // +0x160 = 10
    uint32_t n164;                    // +0x164
    int32_t  n168;                    // +0x168 = -1
    void*    p16c;                    // +0x16c (vtable)
    uint32_t f170, f174, f178, f17c;  // +0x170..+0x17f
    uint32_t pad180;                  // +0x180
    uint32_t f184;                    // +0x184
    uint32_t f188, f18c, f190;        // +0x188..+0x193
    uint32_t pad194;                  // +0x194
    uint32_t f198;                    // +0x198
    uint32_t f19c, f1a0, f1a4;        // +0x19c..+0x1a7
    uint32_t pad1a8[2];               // +0x1a8,+0x1ac
    uint32_t f1b0, f1b4, f1b8, f1bc, f1c0;   // +0x1b0..+0x1c3
    uint32_t pad1c4, pad1c8;
    uint32_t f1cc, f1d0, f1d4;        // +0x1cc..+0x1d7
    uint32_t pad1d8[2];               // +0x1d8,+0x1dc
    IRefObj* p1e0;                    // +0x1e0
    uint8_t  b1e4;                    // +0x1e4
    uint8_t  b1e5;                    // +0x1e5
    uint8_t  pad1e6[2];
    float    f1e8, f1ec, f1f0;        // +0x1e8..+0x1f3
    uint8_t  b1f4;                    // +0x1f4
    uint8_t  pad1f5[3];
    uint32_t f1f8, f1fc, f200;        // +0x1f8..+0x203

    cTextRenderer mText;              // +0x204

    void*    p224;                    // +0x224 (vector<inner> begin)
    uint32_t f228;                    // +0x228
    uint32_t f22c;                    // +0x22c
    uint32_t pad230[2];               // +0x230,+0x234
    evec_s006e_e1f0<unsigned int> mVec238;       // +0x238

    uint32_t pad244[2];               // +0x244,+0x248
    uint32_t f24c, f250, f254, f258, f25c;  // +0x24c..+0x25f
    uint8_t  mFrustumCull[0x100];     // +0x260 (cFrustumCull, >= 0x100 bytes)

    uint8_t  pad360_0[0x350 - 0x360 + 0x360];
    float    f350;                    // +0x350 = 0.5f
    float    f354;                    // +0x354 = 200.0f
    void*    p358;                    // +0x358
    IWeakObj* p35c;                   // +0x35c
    IWeakObj* p360;                   // +0x360
    IWeakObj* p364;                   // +0x364
    uint8_t  b368;                    // +0x368
    uint8_t  b369;                    // +0x369
    uint8_t  pad36a[2];
    uint32_t f36c, f370, f374, f378, f37c, f380, f384;  // +0x36c..+0x387

    cEffectsRenderer_s006e_e1f0();                                            // 0x6ee1f0
    ~cEffectsRenderer_s006e_e1f0();                                           // 0x6ee4f0
    void AddActive(unsigned int id);                               // 0x6ee940
    void DispatchWithAdditionalMaterial(void* ctx, int mat, int extra);  // 0x6ee6f0
};
struct vbvec {
    unsigned short* mpBegin;      // +0x00
    unsigned short* mpEnd;        // +0x04
    unsigned short* mpCapacity;   // +0x08
    void resize(unsigned int n);  // 0x6eea80
};
struct Elem70 { uint8_t b[0x70]; };
struct Vector70 {
    Elem70* mpBegin;      // +0x00
    Elem70* mpEnd;        // +0x04
    Elem70* mpCapacity;   // +0x08
    // 0x6eeb60: insert `count` (always 1 here) copies of `val` at `pos`.
    void insert(Elem70* pos, const Elem70* val);
};
extern "C" void   FUN_006e9230(Elem70* src, const Elem70* val);   // copy-construct
extern "C" Elem70* FUN_006e93d0(Elem70* first, Elem70* last, Elem70* dst);  // uninit copy
extern "C" void   FUN_006eba30(Elem70* first, Elem70* last, Elem70* dst);   // destroy range
extern "C" void   FUN_006ebf10(Elem70* first, Elem70* last, Elem70* dst);   // move-backward
extern "C" Elem70* FUN_006ebb80(Elem70* dst, const Elem70* val);            // assign
// ---- items of slice s006ee1f0 end

// ---- items of slice s006f1770 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00a7bca0(int, int);
extern "C" void* FUN_0067dcd0();   // 0x0067dcd0 GetManager
extern "C" void* FUN_0067dd60();   // 0x0067dd60
extern unsigned gTypeTable[];      // 0x0140b568
#pragma intrinsic(_InterlockedDecrement, _InterlockedExchange, _InterlockedIncrement, _InterlockedExchangeAdd)
void* EAAllocate(unsigned int n, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
void* ZoneObjectNew(unsigned int n, const char* name, int flags, int align, const char* file, int line); // 0x00926020
bool FUN_006ac0a0(unsigned int flags, void* holder); // 0x006ac0a0
static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct RefObj0 {
    virtual void AddRef();
    long mRefCount;                    // +0x04
};
struct RefObjA {
    virtual void Destroy(int flags);
    long mRefCount;                    // +0x04
};
struct ResSub {
    virtual void s0();                 // AddRef
    virtual void s1();                 // Release
    virtual void s2();                 // AddRef (lookup result)
    virtual void s3();                 // Release (cleared from the list)
};
struct ResBase {
    virtual void b0();
    virtual void b1();                 // +0x04 : Release
    char     pad08[0x18 - 0x04];
    ResSub   mSub;                     // +0x18
};
struct ResRef {
    virtual void q0();
    virtual void q1();                 // Release
};
struct ResGuard {
    ResBase* mpRes;
    ResGuard() : mpRes(0) {}
    ~ResGuard() { if (mpRes) mpRes->b1(); }
    ResBase* get() const { return mpRes; }
    ResBase** addr() { return &mpRes; }
};
struct RefGuard {
    ResRef* mpRef;
    RefGuard() : mpRef(0) {}
    ~RefGuard() { if (mpRef) mpRef->q1(); }
    ResRef* get() const { return mpRef; }
    ResRef** addr() { return &mpRef; }
    void reset()
    {
        ResRef* p = mpRef;
        if (p)
        {
            mpRef = 0;
            p->q1();
        }
    }
};
struct SwarmObj {
    virtual void w0();
    virtual void AddRef();
    virtual void Release();
    SwarmObj* Init();                  // 0x00a7bb80
};
struct SwarmGuard {
    SwarmObj* mpObj;
    SwarmGuard(SwarmObj* p) : mpObj(p) { if (p) p->AddRef(); }
    ~SwarmGuard() { if (mpObj) mpObj->Release(); }
    SwarmObj* get() const { return mpObj; }
};
struct ResKey3 { unsigned instance, type, group; };
struct ResMgr {
    virtual void r00();
    virtual void r01();
    virtual void r02();
    virtual bool Lookup(ResKey3* key, ResBase** out, int a, int b, int c, int d);      // +0x0c
    virtual bool Lookup2(ResKey3* key, ResRef** out1, ResRef** out2,
                         int a, int b, int c, int d, int e);                             // +0x10
virtual void r05();
virtual void r06();
virtual void r07();
virtual void r08();
virtual void r09();
virtual void r10();
virtual void r11();
virtual void r12();
virtual void r13();
virtual void r14();
virtual void r15();
virtual void r16();
    virtual void AddSwarm(int flags, SwarmObj* p, int extra);                            // +0x44
    virtual int  GetSwarmType(unsigned id, int arg);                                     // +0x48
};
struct MaterialVt {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
    virtual void* LookupDesc(unsigned key);                                              // +0x28
};
struct KeyedVt {
virtual void k0();
virtual void k1();
virtual void k2();
virtual void k3();
virtual void k4();
virtual void k5();
virtual void k6();
virtual void k7();
    virtual void k8();
    virtual bool Contains(unsigned key);                                                 // +0x24
};
struct Node18 {
    unsigned m0;                       // +0x00
    unsigned m4;                       // +0x04
    RefObj0* mpRef;                    // +0x08
    unsigned mPad0c;                   // +0x0c
    Node18* mpNext;                    // +0x10
    unsigned mPad14;                   // +0x14
    Node18(const Node18& src);
};
struct HtValue {
    unsigned  mKey;                    // +0x00
    void*     mValue;                  // +0x04
    RefObjA*  mpRef;                   // +0x08
    ~HtValue();
};
struct HtNode  { unsigned mKey; void* mValue; void* mRef; HtNode* mpNext; };
struct HtIter  { HtNode* node; HtNode** bucket; };
struct HInsertResult { HtNode* node; HtNode** bucket; bool inserted; char pad[3]; };
struct HtTable {
    unsigned   mHash;                  // +0x00
    HtNode**   mBuckets;               // +0x04
    unsigned   mBucketCount;           // +0x08
    unsigned   mElementCount;          // +0x0c
    HtIter find(const unsigned& key);                                   // 0x00685f30
    HInsertResult insert(const HtValue& value, bool flag);              // 0x006f21b0
    void FreeBuckets(unsigned buckets, unsigned count);
    __declspec(noinline) unsigned* FindOrInsert2(const unsigned* key);
};
inline HtValue::~HtValue()
{
    RefObjA* p = mpRef;
    if (p)
    {
        if (_InterlockedDecrement(&p->mRefCount) == 0)
        {
            _InterlockedExchange(&p->mRefCount, 1);
            if (p) p->Destroy(1);
        }
    }
}
Node18::Node18(const Node18& src)
{
    m0 = src.m0;
    m4 = src.m4;
    mpRef = src.mpRef;
    if (mpRef)
        mpRef->AddRef();
}
struct StrSlot {
    wchar_t* mpBegin;                  // +0x00
    wchar_t* mpEnd;                    // +0x04
    wchar_t* mpCap;                    // +0x08
    void assign(const wchar_t* begin, const wchar_t* end);   // 0x006ebd20
};
struct PSetElem {
    int      f00;                      // +0x00
    StrSlot  mStr;                     // +0x04
    char     pad0c[0xa0 - 0x10];
    int      ma0;                      // +0xa0
    int      ma4;                      // +0xa4
    float    ma8;                      // +0xa8
    char     padac[0xc0 - 0xac];
};
struct PSetVec {                       // +0x224
    PSetElem* begin; PSetElem* end; PSetElem* cap;
    void PushBack();                   // 0x006f16c0 thiscall
};
struct IndexVec {                      // +0x238
    int* begin; int* end; int* cap;
};
static __forceinline int WStrLen(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p) ++p;
    return (int)(p - s);
}
struct PSetOwner {
    char     pad0[0x224];
    PSetVec  mVec;                     // +0x224
    char     pad22c[0x238 - 0x230];
    IndexVec mFree;                    // +0x238
    __declspec(noinline) bool AddParticleSet(wchar_t* name, int b, int c, float d, unsigned* out); // 0x006f1770
};
struct PtrVec {
    ResSub** begin; ResSub** end; ResSub** cap;      // +0x00/+0x04/+0x08
    void DoInsertValue(ResSub** pos, ResSub* const& v);   // 0x006ec4a0
    void push_back(ResSub* v) { if (end < cap) *end++ = v; else DoInsertValue(end, v); }
    void erase(ResSub** first, ResSub** last)
    {
        memcpy(first, last, (char*)end - (char*)last);
        end = end - (last - first);
    }
    void clear() { erase(begin, end); }
};
struct IntVec {
    int* begin; int* end; int* cap;
    void erase(int* first, int* last)
    {
        memcpy(first, last, (char*)end - (char*)last);
        end = end - (last - first);
    }
    void clear() { erase(begin, end); }
};
struct BigVt {
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void b7();
};
struct Model5c {
    virtual void c0();
    virtual void c1();
    char     pad8[0x5c - 0x04];
    void*    mp5c;                     // +0x5c
    void*    mp60;                     // +0x60
    void*    mp64;                     // +0x64
    void*    mp68;                     // +0x68
    BigVt*   mp6c;                     // +0x6c
};
struct Model98 {
    virtual void n0();
    Model98* Init();                   // 0x006ebf50
    void UpdateFromResource(void* res); // 0x006edbc0
    void LoadFrom(void* res);          // 0x006e7410
};
struct EffectsRenderer_s006f_1770 {
    char        pad0[0x0c];
    KeyedVt*    mpKeyed;               // +0x0c
    char        pad10[0x3c - 0x10];
    HtTable     mTable3c;              // +0x3c
    char        pad4c[0x50 - 0x4c];
    ResMgr*     mpManager;             // +0x50
    void*       mpField54;             // +0x54
    MaterialVt* mpMaterial;            // +0x58
    Model5c*    mpModel;               // +0x5c
    PtrVec      mObjVec;               // +0x60
    char        pad6c[0x74 - 0x6c];
    IntVec      mFreeVec;              // +0x74
    char        pad80[0x88 - 0x80];
    HtTable     mTable88;              // +0x88

    __declspec(noinline) bool ResourceInfoInit();                      // 0x006f1860
    __declspec(noinline) bool LookupAndUse(unsigned a, unsigned b, ResSub** out, unsigned index); // 0x006f1b60
    __declspec(noinline) bool CreateResource(unsigned a, unsigned b, Model98** out); // 0x006f1c40
    __declspec(noinline) int  ClassifyVertexDesc(unsigned key, unsigned unused, unsigned a); // 0x006f1f20
    __declspec(noinline) int  ContainsKey(unsigned key);               // 0x006f2000
    __declspec(noinline) void* FindEntry(unsigned key, unsigned unused); // 0x006f2050
    __declspec(noinline) bool InsertEntry(unsigned index, unsigned b, unsigned c, int* out); // 0x006f2310
    __declspec(noinline) bool ClearAll();                              // 0x006f2620
};
__declspec(noinline) void __stdcall Forward1840(int a, int b);
struct VtStub1950 {
    virtual void v0();
    virtual int  v1(int, int, int);
};
struct Owner1950 {
    char pad0[0x60];
    VtStub1950** mArray;   // +0x60
    __declspec(noinline) int Call(int idx, int a, int b, int c);
};
__declspec(noinline) Node18* __stdcall Alloc18(Node18* src);
// ---- items of slice s006f1770 end

// @ 0x006e6840
void __stdcall GetLayout(int type, unsigned char* out)
{
    switch (type) {
    case 0:
    case 6:
    case 7:
    case 8:
        out[1] = 0x0c; out[2] = 0x10; out[0] = 0; break;
    case 2:
    case 3:
        out[1] = 0x10; out[2] = 0x20; out[3] = 0x24; out[0] = 0; break;
    case 4:
        out[1] = 0x10; out[2] = 0x20; out[3] = 0x2c; out[4] = 0x30; out[0] = 0; break;
    case 5:
        out[1] = 0x0c; out[0] = 0; break;
    case 9:
        out[1] = 0x40; out[0] = 0; break;
    default:
        break;
    }
}

// @ 0x006e68e0
int __stdcall FindKnownValue(int* p)
{
    for (;;) {
        switch (*p) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 0x20:
            return *p;
        default:
            ++p;
            break;
        }
    }
}

// @ 0x006e6930
void ShaderHost::CallF1(float b)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F1(b);
    }
}

// @ 0x006e6970
void ShaderHost::CallF3(int a, float b, int c)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F3(a, b, c);
    }
}

// @ 0x006e69a0
void ShaderHost::CallF2(int a, float b)
{
    Inner* p = *(Inner**)((char*)this + 0x35c);
    if (p != 0) {
        p->F2(a, b);
    }
}

// @ 0x006e69e0
void ShaderHost::SetMode(int mode, int value)
{
    Manager* m = (Manager*)FUN_0067dd50();
    if (mode != 6 && mode != 5) {
        VirtualFn1 fn = (VirtualFn1)((void**)m->vtbl)[0x58 / 4];
        if (fn(m, 0x16) != 0) {
            *(char*)((char*)this + 0x368) = (char)value;
        }
    }
}

// @ 0x006e6b70
void ShaderHost::SetParams(int a, int b, char c1, char c2, char c3)
{
    *(int*)((char*)this + 0x1f8) = a;
    *(char*)((char*)this + 0x1f4) = 1;
    *(int*)((char*)this + 0x1fc) = b;
    *(int*)((char*)this + 0x200) = 0;
    if (c1 != 0) {
        *(int*)((char*)this + 0x200) = 1;
    }
    if (c2 != 0) {
        *(int*)((char*)this + 0x200) = *(int*)((char*)this + 0x200) | 2;
    }
    if (c3 != 0) {
        *(int*)((char*)this + 0x200) = *(int*)((char*)this + 0x200) | 4;
    }
}

// @ 0x006e6c20
void ShaderHost::CallIface(int v)
{
    Manager* o = *(Manager**)((char*)this + 0x25c);
    VirtualFn3 fn = (VirtualFn3)((void**)o->vtbl)[0xa8 / 4];
    fn(o, 0, v, 0);
}

// @ 0x006e6ca0
void SortPairsA(uint32_t* begin, uint32_t* end)
{
    uint32_t* p = begin;
    if (p != end) {
        while ((p = p + 2) != end) {
            uint32_t v1 = *p;
            uint32_t v2 = p[1];
            uint32_t* q = p;
            while (q != begin && q[-2] < v1) {
                *q = q[-2];
                q[1] = q[-1];
                q -= 2;
            }
            *q = v1;
            q[1] = v2;
        }
    }
}

// @ 0x006e6cf0
void SortPairsB(uint32_t* begin, uint32_t* end)
{
    for (uint32_t* p = begin; p != end; p += 2) {
        uint32_t v1 = *p;
        uint32_t v2 = p[1];
        uint32_t* q = p;
        uint32_t prev = q[-2];
        while (prev < v1) {
            *q = q[-2];
            q[1] = q[-1];
            q -= 2;
            prev = *q;
        }
        *q = v1;
        q[1] = v2;
    }
}

// @ 0x006e7110
void Host3::Method7110(int arg)
{
    Record12* it = (Record12*)m08;
    Record12* end = (Record12*)m0c;
    if (it == end) return;
    do {
        FUN_00777bf0();
        EmbeddedState* st = *(EmbeddedState**)((uint8_t*)*(void**)((uint8_t*)it + 4) + 4);
        if (st->flags & 1) {
            float mat[16];
            memcpy(mat, g_16fa380, 0x40);
            st->D3D9SetTransform(mat, 1);
        }
        if (st->flags & 0x10) {
            float col[4];
            col[0] = g_16f96a8;
            col[1] = g_16f96ac;
            col[2] = g_16f96b0;
            col[3] = g_16f96b4;
            st->SetMaterialColor(col);
        }
        void* m = *(void**)it;
        FUN_007611a0(*(int*)*(void**)((uint8_t*)m + 0x24));
        FUN_00777b50(st);
        st->Dispatch();
        FUN_00777ae0(3, 0, 0);
        FUN_00777ae0(4, 0, 0);
        void* sh = *(void**)((uint8_t*)*(void**)it + 8);
        g_16f85a8 = *(uint32_t*)((uint8_t*)sh + 0x14);
        int vd = *(int*)*(void**)((uint8_t*)*(void**)it + 0x24);
        void* prev = g_16f65a0;
        if (!(prev != 0 && FUN_011f2e70(prev, (void*)vd) != 0))
            g_16f9110 |= 0x100000;
        FUN_011f2bc0((void*)vd, 0);
        void* sh2 = *(void**)((uint8_t*)it + 8);
        if (sh2 != 0) FUN_007789d0(sh2, 0);
        FUN_011f9710(*(void**)it, 0);
        if (st->flags & 0x10)
            st->SetMaterialColor(&g_140aef8);
        FUN_00777c10();
        it = (Record12*)((uint8_t*)it + 0xc);
    } while (it != end);
}

// @ 0x006e7270
void Host3::Method7270(void* boxState, void* arg)
{
    (void)arg;
    Record12* it = (Record12*)m08;
    Record12* end = (Record12*)m0c;
    if (it == end) return;
    do {
        FUN_00777bf0();
        EmbeddedState* st = *(EmbeddedState**)((uint8_t*)*(void**)((uint8_t*)it + 4) + 4);
        if (st->flags & 1) {
            float mat[16];
            memcpy(mat, g_16fa380, 0x40);
            st->D3D9SetTransform(mat, 1);
        }
        if (st->flags & 0x10) {
            float col[4];
            col[0] = g_16f96a8;
            col[1] = g_16f96ac;
            col[2] = g_16f96b0;
            col[3] = g_16f96b4;
            st->SetMaterialColor(col);
        }
        void* m = *(void**)it;
        FUN_007611a0(*(int*)*(void**)((uint8_t*)m + 0x24));
        FUN_00777b50(st);
        st->Dispatch();
        FUN_00777b50(boxState);
        FUN_011ee580(boxState);
        void* box = *(void**)it;
        void* sh = *(void**)((uint8_t*)box + 8);
        g_16f85a8 = *(uint32_t*)((uint8_t*)sh + 0x14);
        int vd = *(int*)*(void**)((uint8_t*)box + 0x24);
        void* prev = g_16f65a0;
        if (!(prev != 0 && FUN_011f2e70(prev, (void*)vd) != 0))
            g_16f9110 |= 0x100000;
        FUN_011f2bc0((void*)vd, 0);
        FUN_011f9710(box, 0);
        if (st->flags & 0x10)
            st->SetMaterialColor(&g_140aef8);
        FUN_00777c10();
        it = (Record12*)((uint8_t*)it + 0xc);
    } while (it != end);
}

// @ 0x006e73d0
void Host3::DispatchList(unsigned char* list, int arg)
{
    if (*list != 0) {
        int i = 0;
        unsigned char* p = list;
        do {
            FUN_006e7270(this, 0, *(void**)(p + 4), arg);
            ++i;
            p += 4;
        } while (i < (int)(unsigned char)*list);
    }
}

// @ 0x006e7450
char Host3::Method7450(unsigned char flags)
{
    // +0x40 ref-counted handle: AddRef the new value, Release the old one.
    void* fresh = FUN_0067ddf0();
    if (fresh != m40) {
        if (fresh != 0) {
            VFn0 addRef = (VFn0)((void**)*(void**)fresh)[0];
            addRef(fresh);
        }
        void* old = m40;
        m40 = fresh;
        if (old != 0) {
            VFn0 release = (VFn0)((void**)*(void**)old)[1];
            release(old);
        }
    }

    void* props = g_15fd918;
    m158 = (uint8_t)FUN_006a25a0(props, 0, 0xdcd55da1);
    m159 = (uint8_t)FUN_006a25a0(props, 0, 0xe83cedc7);

    if (props != 0) {
        void* prop = 0;
        VFnB getProp = (VFnB)((void**)*(void**)props)[9];
        if (getProp(props, 0x4780d12, &prop) && *(uint16_t*)((uint8_t*)prop + 0x12) == 0xa)
            m15c = (uint32_t)(*FUN_0041ea00(prop, 0) * 3);
    }
    if (props != 0) {
        void* prop = 0;
        VFnB getProp = (VFnB)((void**)*(void**)props)[9];
        if (getProp(props, 0x4780d18, &prop) && *(uint16_t*)((uint8_t*)prop + 0x12) == 9)
            m160 = (uint32_t)*FUN_0041e990(prop, 0);
    }

    if (flags & 0x10) {
        void* vf = FUN_0067dd50();
        VFnS setup = (VFnS)((void**)*(void**)vf)[19];
        setup(vf, &m18, 0x12, 0);
        setup(vf, &m18, 3, 0);
        setup(vf, &m18, 0x20, 0);
        setup(vf, &m18, 0x16, 0);
        m369 = 1;
    }

    m204.Init();
    m258 = FUN_0067dda0();
    m25c = FUN_0067dd40();

    void* mm = FUN_0067dd70();
    VFnM makeMat = (VFnM)((void**)*(void**)mm)[11];
    makeMat(mm, 0x10, 0x1618f88, &m84);
    mm = FUN_0067dd70();
    makeMat = (VFnM)((void**)*(void**)mm)[11];
    makeMat(mm, 0x10, 0x1618fc8, &mc4);

    if (flags & 4) {
        void* o = m25c;
        VFnR f = (VFnR)((void**)*(void**)o)[40];
        m35c = f(o);
    }

    if (flags & 2) {
        void* p = FUN_00f473a0(0x1c8, g_13eb8a4, 0, 0, 0, 0);
        void* obj = 0;
        if (p != 0)
            obj = FUN_00776730(p);
        if (obj != m360) {
            if (obj != 0) { VFn0 a = (VFn0)((void**)*(void**)obj)[1]; a(obj); }
            void* old = m360;
            m360 = obj;
            if (old != 0) { VFn0 r = (VFn0)((void**)*(void**)old)[2]; r(old); }
        }
        VFn0 f = (VFn0)((void**)*(void**)m360)[4];
        f(m360);
    }

    if (flags & 1) {
        void* p = FUN_00f473a0(0x180, g_13eb8a4, 0, 0, 0, 0);
        void* obj = 0;
        if (p != 0)
            obj = FUN_00776920(p);
        if (obj != m364) {
            if (obj != 0) { VFn0 a = (VFn0)((void**)*(void**)obj)[1]; a(obj); }
            void* old = m364;
            m364 = obj;
            if (old != 0) { VFn0 r = (VFn0)((void**)*(void**)old)[2]; r(old); }
        }
        VFn0 f = (VFn0)((void**)*(void**)m364)[4];
        f(m364);
    }

    if (flags & 8) {
        void* p = FUN_00f473a0(0xb4, g_13eb8a4, 0, 0, 0, 0);
        void* obj = 0;
        if (p != 0)
            obj = FUN_0076c660(p);
        if (obj != m24) {
            if (obj != 0) {
                VFn0 a = (VFn0)((void**)*(void**)((uint8_t*)obj + 8))[2];
                a((uint8_t*)obj + 8);
            }
            void* old = m24;
            m24 = obj;
            if (old != 0) {
                VFn0 r = (VFn0)((void**)*(void**)((uint8_t*)old + 8))[3];
                r((uint8_t*)old + 8);
            }
        }
        FUN_0076acd0(m24, 0);
    }

    {
        void* p = FUN_00f473a0(0x174, g_13eb8a4, 0, 0, 0, 0);
        void* v = (p != 0) ? FUN_007c3f70(p, 0) : 0;
        m24c = v;
        FUN_007c4dd0(v, 0, 0);
        FUN_007c3cc0(m24c, 0, 0);
    }
    {
        void* p = FUN_00f473a0(0x174, g_13eb8a4, 0, 0, 0, 0);
        void* v = (p != 0) ? FUN_007c3f70(p, 0) : 0;
        m250 = v;
        FUN_007c4dd0(v, 0, 0);
    }
    {
        void* p = FUN_00f473a0(0x174, g_13eb8a4, 0, 0, 0, 0);
        void* v = (p != 0) ? FUN_007c3f70(p, 0) : 0;
        m254 = v;
        FUN_007c4dd0(v, 0, 0);
    }

    {
        void* ms = FUN_0067dcc0();
        VFnP reg = (VFnP)((void**)*(void**)ms)[8];
        reg(ms, &m14, 0x6694879);
    }

    m358 = 0;
    return 1;
}

// @ 0x006e7880
void Host3::Method7880(int arg)
{
    Inner7c* a = *(Inner7c**)((char*)this + 0x35c);
    if (a != 0) {
        a->FI(arg);
    }
    Inner7c* b = *(Inner7c**)((char*)this + 0x24);
    if (b != 0) {
        b->FI(arg);
    }
}

// @ 0x006e78b0
void Host3::Method78b0(void* a, void* b, int c)
{
    (void)a; (void)c;
    if (FUN_007c4fd0(*(void**)b, 0) == 0)
        return;
    int count = (int)(((uint8_t*)m228 - (uint8_t*)m224) / 0xc0);
    if (count > 0) {
        int off = 0;
        int n = count;
        do {
            Elemc0* e = (Elemc0*)((uint8_t*)m224 + off);
            if (e->enabled != 0) {
                if ((e->styleA0 & e->styleA4) == 0xffffffffu) {
                    m204.SetFontName(g_140af84);
                    m204.SetFontSize(e->fontA8);
                } else {
                    m204.SetStyle((int)e->styleA0);
                }
                m204.SetColor(&e->colorB0);
                m204.SetStyleScale(e->scaleBc);
                m204.DrawString(e->f98, e->f9c, e->text0);
            }
            off += 0xc0;
        } while (--n != 0);
    }
    FUN_007c3c10(*(void**)b, 0);
}

// @ 0x006e79b0
void Host3::Method79b0(int index, float f2, float f3, int a4, float f5, int a6, int a7, int a8, int a9, float f10, float f11)
{
    (void)a4;
    Elemc0* e = (Elemc0*)((uint8_t*)m224 + index * 0xc0);
    float rect[6];
    rect[0] = f2;
    rect[2] = f3;
    rect[4] = f5;
    FUN_007c4180(m20, 0, &rect[4], &rect[0]);
    SizeProvider* p = (SizeProvider*)FUN_0067dd50();
    void* sz = p->v7();
    float w = (float)*(int*)sz;
    float h = (float)*(int*)((uint8_t*)sz + 4);
    e->f9c = (1.0f - rect[4]) * h * g_1471064 + f11;
    e->f98 = (rect[3] + 1.0f) * w * g_1471064 + f10;
    e->fAc = f5;
    e->colorB0 = (uint32_t)a6;
    e->colorB4 = (uint32_t)a7;
    e->colorB8 = (uint32_t)a8;
    memcpy(&e->scaleBc, &a9, sizeof(e->scaleBc));
}

// @ 0x006e7aa0
void Host3::SetFlag(int index, unsigned char v)
{
    *(unsigned char*)(*(int*)((char*)this + 0x224) + index * 0xc0) = v;
}

// @ 0x006e7ac0
void Host3::Method7ac0(void* arg)
{
    int* p = (int*)arg;
    p[0x68 / 4] = 0;
    int* list = (int*)p[0x28 / 4];
    int* first = (int*)list[2];
    if (first != (int*)list[3]) {
        int obj = *first;
        if (*(unsigned int*)(obj + 0x18) < *(unsigned int*)((char*)this + 0x15c)) {
            int desc = **(int**)(obj + 0x24);
            int count = (*(int*)((char*)g_1618d10 + 0x30d58) - *(int*)((char*)g_1618d10 + 0x30d54)) >> 2;
            if (count > 0) {
                int i = 0;
                while (rw_VertexDescriptor_AreEqual(desc, *(int*)(*(int*)((char*)g_1618d10 + 0x30d54) + i * 4)) == 0) {
                    ++i;
                    if (count <= i) {
                        return;
                    }
                }
                p[0x68 / 4] = *(int*)(*(int*)((char*)g_1618d10 + 0x30d68) + i * 4);
            }
        }
    }
}

// @ 0x006e7b50
void Host3::Method7b50(void* arg)
{
    Renderable* a = (Renderable*)arg;
    float tmp[4];
    m1b0 = a->m28;
    m1b4 = a->m5c;
    tmp[0] = 0.0f;
    tmp[1] = 0.0f;
    tmp[2] = 0.0f;
    tmp[3] = g_1485720;
    m168 = a->m10;
    FUN_00777bf0();
    if (a->m60 != 0)
        FUN_007789d0(a->m60, 0);
    if (a->m64 != 0)
        FUN_00777ae0(0x219, *(int*)a->m64, 0);
    if (m158 != 0) {
        uint32_t v = (uint32_t)(unsigned)a->m68;
        if (v != 0) {
            m154 = v;
            float k = g_1471064;
            tmp[0] = (a->m38 + a->m2c) * k;
            tmp[1] = (a->m3c + a->m30) * k;
            tmp[2] = (a->m40 + a->m34) * k;
            FUN_00777ae0(0x226, (int)tmp, 1);
        }
    }
    a->m00->v0(&m08);
    FUN_00777c10();
    ++m37c;
    m154 = 0;
}

// @ 0x006e7c60
char Host3::Method7c60()
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        return p->F7(0, 0, 0, 0, 0, 0, 1);
    }
    return 0;
}

// @ 0x006e7c80
char Host3::Method7c80(int a, int b, int c, int d, int e, int f)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        return p->F7(a, b, c, d, e, f, 1);
    }
    return 0;
}

// @ 0x006e7cc0
void Host3::Method7cc0(int a, int b, int c, int d)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x24);
    if (p != 0) {
        p->F12(a, b, c, d, 0, 0, 0, (int)g_matName7cc0, 0, 0, 0, 0);
    }
}

// @ 0x006e7d00
void Host3::Method7d00(float v)
{
    Inner7c* p = *(Inner7c**)((char*)this + 0x360);
    if (p != 0) {
        p->FF(v);
    }
}

// @ 0x006e7d40
void Host3::Method7d40(int index, uint32_t* v, float w)
{
    if (index >= 0) {
        if (index < (*(int*)((char*)this + 0x4c) - *(int*)((char*)this + 0x48)) / 0x70) {
            char* e = (char*)(*(int*)((char*)this + 0x48) + index * 0x70);
            *(uint32_t*)(e + 0x4c) = v[0];
            *(uint32_t*)(e + 0x50) = v[1];
            *(uint32_t*)(e + 0x54) = v[2];
            *(float*)(e + 0x58) = w;
        }
    }
}

// @ 0x006e7da0
void Host3::Method7da0()
{
    int* p = *(int**)((char*)this + 0x28);
    if (p != 0) {
        int n = p[1] - 1;
        p[1] = p[1] - 1;
        if (n == 0) {
            p[1] = 1;
            typedef void(__thiscall* Fn)(void*, int);
            Fn fn = (Fn)((void**)*p)[0];
            fn(p, 1);
        }
    }
}

// @ 0x006e7dd0
void Host3::Method7dd0(int index, float* v, float w)
{
    if (index < 0)
        return;
    int count = (int)(((uint8_t*)m178 - (uint8_t*)m174) / 0x70);
    if (index >= count)
        return;
    uint8_t* e = (uint8_t*)m174 + index * 0x70;
    *(uint32_t*)(e + 0x38) = *(uint32_t*)((uint8_t*)v + 0x0c);
    *(uint32_t*)(e + 0x3c) = *(uint32_t*)((uint8_t*)v + 0x10);
    *(uint32_t*)(e + 0x40) = *(uint32_t*)((uint8_t*)v + 0x14);
    *(uint32_t*)(e + 0x2c) = *(uint32_t*)((uint8_t*)v + 0x00);
    *(uint32_t*)(e + 0x30) = *(uint32_t*)((uint8_t*)v + 0x04);
    *(uint32_t*)(e + 0x34) = *(uint32_t*)((uint8_t*)v + 0x08);
    *(float*)(e + 0x44) = w;

    MidObj* obj = m1e0;
    if (obj == 0)
        return;
    float mid[3];
    mid[0] = (v[0] + v[3]) * g_1471064;
    mid[1] = (v[1] + v[4]) * g_1471064;
    mid[2] = (v[2] + v[5]) * g_1471064;
    void* cur = *(void**)(e + 0x64);
    if (cur == 0) {
        *(void**)(e + 0x64) = obj->v6(1.0f, mid);
    } else {
        obj->v7(1.0f, mid, (uint32_t)(unsigned)cur);
    }
}

// @ 0x006e7ed0
void Host3::Method7ed0(int index, uint32_t* v, float w)
{
    if (index >= 0) {
        if (index < (*(int*)((char*)this + 0x178) - *(int*)((char*)this + 0x174)) / 0x70) {
            char* e = (char*)(*(int*)((char*)this + 0x174) + index * 0x70);
            *(uint32_t*)(e + 0x4c) = v[0];
            *(uint32_t*)(e + 0x50) = v[1];
            *(uint32_t*)(e + 0x54) = v[2];
            *(float*)(e + 0x58) = w;
        }
    }
}

// @ 0x006e7f30
void Host3::Method7f30()
{
    if (m60 != 0) {
        ((VObj*)m60)->v1();
    }
    if (m00 != 0) {
        uint32_t n = m00->refCount - 1;
        m00->refCount = n;
        if (n == 0) {
            m00->refCount = 1;
            m00->v0(1);
        }
    }
}

// @ 0x006e7fa0
int Host3::Method7fa0(int index, int value)
{
    char* e = (char*)(*(int*)((char*)this + 0x1b8) + index * 0x68);
    void* p = *(void**)(e + 0x60);
    if (p != 0) {
        VGet fn = (VGet)((void**)(*(void**)p))[0x10 / 4];
        return fn(p, index, value);
    }
    if (index >= 0) {
        int n = *(int*)((char*)this + 0x1bc) - *(int*)((char*)this + 0x1b8);
        int count = n / 0x68;
        if (index < count) {
            *(char*)(e + 0x50) = (char)value;
        }
        return (int)(0x4ec4ec4fu * (unsigned)n);
    }
    return (int)this;
}

// @ 0x006e8000
void Host3::Method8000(int index, float* v, float w)
{
    char* e = (char*)(*(int*)((char*)this + 0x1b8) + index * 0x68);
    void* p = *(void**)(e + 0x60);
    if (p != 0) {
        VSet fn = (VSet)((void**)(*(void**)p))[0x18 / 4];
        fn(p, index, v, w);
        return;
    }
    if (index >= 0) {
        int count = (*(int*)((char*)this + 0x1bc) - *(int*)((char*)this + 0x1b8)) / 0x68;
        if (index < count) {
            *(float*)(e + 4) = v[0];
            *(float*)(e + 8) = v[1];
            *(float*)(e + 0xc) = v[2];
            *(float*)((char*)(*(int*)((char*)this + 0x1b8) + index * 0x68) + 0x10) = w;
        }
    }
}

// @ 0x006e8090
void Host3::Method8090(int index, int a, float b)
{
    void* p = *(void**)(*(int*)((char*)this + 0x1b8) + index * 0x68 + 0x60);
    if (p != 0) {
        VSet2 fn = (VSet2)((void**)(*(void**)p))[0x1c / 4];
        fn(p, index, a, b);
    }
}

// @ 0x006e80d0
void CCreature::m80d0(int idx, int a, int b)
{
    char* self = (char*)this;
    int off = idx * 0x68;
    void* e = *(void**)(self + 0x1b8);
    void* p = *(void**)((char*)e + off + 0x60);
    if (p) {
        ((void(__thiscall*)(void*, int, int, int))VFN(p, 0x20))(p, idx, a, b);
        return;
    }
    void* r = ((Ext*)(*(void**)(self + 0x40)))->r6f2050(a, b);
    if (r) {
        *(uint*)((char*)*(void**)(self + 0x1b8) + off + 0x54) = *(uint*)r;
        *(uint*)((char*)*(void**)(self + 0x1b8) + off + 0x58) = *(uint*)((char*)r + 4);
        return;
    }
    void* mm = F_67dd70();
    void* base = (char*)*(void**)(self + 0x1b8) + off;
    int v = ((int(__thiscall*)(void*, int))VFN(mm, 0x28))(mm, a);
    *(uint*)((char*)base + 0x54) = (uint)v;
}

// @ 0x006e8160
void CCreature::m8160(float a, float b)
{
    if (*(void**)((char*)this + 0x20) == 0)
        return;
    int rect[4];
    ((Ext*)(*(void**)((char*)this + 0x20)))->r7c4010(rect);
    float x = a / (float)(rect[2] - rect[0]);
    float y = b / (float)(rect[3] - rect[1]);
    ((Ext*)(*(void**)((char*)this + 0x20)))->r7c4ad0(x, y);
    if (*(void**)((char*)this + 0x360))
        ((Ext*)(*(void**)((char*)this + 0x360)))->r776420(-x, -y);
}

// @ 0x006e8200
char CCreature::m8200(char* p, int a)
{
    char* self = (char*)this;
    if (*(char*)(self + 0x368)) {
        void* m = F_67dd50();
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x60))(m, 0x16, 2);
        *(char*)(self + 0x368) = 0;
    }
    if (*p == '\n') {
        void* q = *(void**)(self + 0x35c);
        if (q)
            return (char)((int(__thiscall*)(void*, void*, int, ushort))VFN(q, 0x18))(
                q, *(void**)(p + 0x10), a, *(ushort*)(p + 2));
        return 0;
    }
    void* h = *(void**)(self + 0x360);
    if (h && ((Ext*)h)->r7773c0((unsigned char)*p, *(int*)(p + 8), *(int*)(p + 0xc), a))
        return 1;
    void* h2 = *(void**)(self + 0x364);
    if (h2 && ((Ext*)h2)->r7775a0((unsigned char)*p, *(int*)(p + 8), *(int*)(p + 0xc), a))
        return 1;
    return 0;
}

// @ 0x006e82b0
void CCreature::m82b0(int a, int b, float c, float d)
{
    if (a >= 0xc) {
        if (*(void**)((char*)this + 0x35c) == 0)
            return;
        ((void(__thiscall*)(void*, int, int, float, float))VFN(
            *(void**)((char*)this + 0x35c), 0x1c))(
            *(void**)((char*)this + 0x35c), a, b, c, d);
        return;
    }
    if (a < 1)
        return;
    {
        void* h = *(void**)((char*)this + 0x360);
        int t = a - 1;
        if (h && (t == 5 || t == 4)) {
            ((Ext*)h)->r7764c0(a, b, c, d);
            return;
        }
    }
    {
        void* h2 = *(void**)((char*)this + 0x364);
        if (h2)
            ((Ext*)h2)->r776520(a, b, c, d);
    }
}

// @ 0x006e8360
void CCreature::m8360(int a)
{
    char* self = (char*)this;
    void* r = *(void**)(self + 0x35c);
    if (r && a >= 0xc) {
        ((void(__thiscall*)(void*, int))VFN(r, 0x20))(r, a);
        ((Ext*)(*(void**)(self + 0x20)))->r7c3cb0(g15d0838);
        goto done;
    }
    if (a < 1)
        goto done;
    {
        void* h = *(void**)(self + 0x360);
        int t = a - 1;
        if (h && (t == 5 || t == 4)) {
            ((Ext*)h)->r776440();
        } else {
            void* h2 = *(void**)(self + 0x364);
            if (h2)
                ((Ext*)h2)->r7764a0();
        }
    }
done:
    {
        void* m = F_67dd50();
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x60))(m, 0x16, 2);
        *(char*)(self + 0x368) = 0;
    }
}

// @ 0x006e83e0
void CCreature::m83e0(int a, int* out1, int* out2)
{
    *(int*)((char*)this + 0x15c) = std::min(a, 0x9c4);
    int v = (int)g1618d10 + 0x10;
    *out1 = v;
    *out2 = 0x50;
}

// @ 0x006e8420
void CCreature::m8420(int a, void* b)
{
    char* self = (char*)this;
    void* old = *(void**)(self + 0x28);
    if (b != old) {
        if (b)
            ((void(__thiscall*)(void*))VFN(b, 0x8))(b);
        *(void**)(self + 0x28) = b;
        if (old)
            ((void(__thiscall*)(void*))VFN(old, 0xc))(old);
    }
    if (a != 0) {
        *(void**)(self + 0x20) = (void*)a;
    } else {
        void* q = *(void**)(self + 0x28);
        *(void**)(self + 0x20) = (void*)((int(__thiscall*)(void*))VFN(q, 0x1c))(q);
    }
    if (*(void**)(self + 0x35c))
        ((Ext*)(*(void**)(self + 0x35c)))->r6f3ee0(a);
}

// @ 0x006e8480
void CCreature::m8480(void* b)
{
    char* self = (char*)this;
    if (*(void**)(self + 0x1e0) == b)
        return;
    if (*(void**)(self + 0x1e0) != 0) {
        int n = (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70;
        if (n > 0) {
            char* p = *(char**)(self + 0x48);
            for (int i = 0; i < n; i++, p += 0x70) {
                void* v = *(void**)(p + 0x68);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    *(void**)(p + 0x68) = 0;
                }
            }
        }
        n = (*(int*)(self + 0x178) - *(int*)(self + 0x174)) / 0x70;
        if (n > 0) {
            char* p = *(char**)(self + 0x174);
            for (int i = 0; i < n; i++, p += 0x70) {
                void* v = *(void**)(p + 0x64);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    *(void**)(p + 0x64) = 0;
                }
            }
        }
        n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                char* base = *(char**)(self + 0x1b8);
                void* v = *(void**)(base + i * 0x68 + 0x5c);
                if (v) {
                    void* q = *(void**)(self + 0x1e0);
                    ((void(__thiscall*)(void*, void*))VFN(q, 0x20))(q, v);
                    base = *(char**)(self + 0x1b8);
                    *(void**)(base + i * 0x68 + 0x5c) = 0;
                }
            }
        }
    }
    {
        void* old = *(void**)(self + 0x1e0);
        if (b != old) {
            if (b)
                ((void(__thiscall*)(void*))VFN(b, 0x0))(b);
            *(void**)(self + 0x1e0) = b;
            if (old)
                ((void(__thiscall*)(void*))VFN(old, 0x4))(old);
        }
    }
    if (*(void**)(self + 0x1e0) != 0) {
        int n = (*(int*)(self + 0x60) - *(int*)(self + 0x5c)) >> 1;
        for (int i = 0; i < n; i++) {
            int idx = *(ushort*)(*(int*)(self + 0x5c) + i * 2);
            char* e = *(char**)(self + 0x48) + idx * 0x70;
            if (*(char*)(e + 0x48)) {
                float c[3];
                c[0] = (*(float*)(e + 0x30) + *(float*)(e + 0x3c)) * 0.5f;
                c[1] = (*(float*)(e + 0x40) + *(float*)(e + 0x34)) * 0.5f;
                c[2] = (*(float*)(e + 0x44) + *(float*)(e + 0x38)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x68) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
        n = (*(int*)(self + 0x18c) - *(int*)(self + 0x188)) >> 1;
        for (int i = 0; i < n; i++) {
            int idx = *(ushort*)(*(int*)(self + 0x188) + i * 2);
            char* e = *(char**)(self + 0x174) + idx * 0x70;
            if (*(char*)(e + 0x48)) {
                float c[3];
                c[0] = (*(float*)(e + 0x2c) + *(float*)(e + 0x38)) * 0.5f;
                c[1] = (*(float*)(e + 0x3c) + *(float*)(e + 0x30)) * 0.5f;
                c[2] = (*(float*)(e + 0x40) + *(float*)(e + 0x34)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x64) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
        n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
        for (int i = 0; i < n; i++) {
            char* base = *(char**)(self + 0x1b8);
            char* e = base + i * 0x68;
            if (*(char*)(e + 0x50) && *(void**)e != 0) {
                void* v = *(void**)e;
                float c[3];
                c[0] = (*(float*)((char*)v + 0x5c) + *(float*)((char*)v + 0x50)) * 0.5f;
                c[1] = (*(float*)((char*)v + 0x60) + *(float*)((char*)v + 0x54)) * 0.5f;
                c[2] = (*(float*)((char*)v + 0x64) + *(float*)((char*)v + 0x58)) * 0.5f;
                void* q = *(void**)(self + 0x1e0);
                *(int*)(e + 0x5c) =
                    ((int(__thiscall*)(void*, float, float*))VFN(q, 0x18))(q, 1.0f, c);
            }
        }
    }
}

// @ 0x006e8810
void CCreature::m8810(uint* flags, void** p3, uint* p4)
{
    char* self = (char*)this;
    uint  fv = (uint)(intptr_t)flags;   // the flag word is the argument value itself
    void* m = F_67dd50();
    int   ddb0 = (int)(intptr_t)F_67ddb0();
    (void)ddb0;
#define MGR_0040(...)  ((void(__thiscall*)(void*, void*, int, int, void*, int, uint))VFN(m, 0x40))(m, __VA_ARGS__)
    if (*(void**)(self + 0x35c) == 0 ||
        ((Ext*)(*(void**)(self + 0x35c)))->r6f4170() != 0 ||
        (fv & 0x20) == 0) {
        if (*(void**)(self + 0x360) == 0)
            return;
        if ((fv & 8) == 0)
            return;
        ((Ext*)(*(void**)(self + 0x360)))->r776a60((int)fv, p3, p4);
        return;
    }

    void* handle = ((Ext*)(*(void**)(self + 0x35c)))->r6f41e0((int)(intptr_t)p3[0]);
    if (!handle)
        return;
    uint v40    = (uint)(int)handle;
    uint a3_1   = (uint)(intptr_t)p3[1];
    uint a3_2   = (uint)(intptr_t)p3[2];
    uint a3_3   = (uint)(intptr_t)p3[3];
    void* viewer = *(void**)(self + 0x254);

    if (*(void**)(self + 0x360) != 0 && (fv & 8) != 0) {
        void* q = *(void**)(self + 0x25c);
        if (!((char(__thiscall*)(void*))VFN(q, 0x104))(q))
            ((Ext*)(*(void**)(self + 0x360)))->r776a60((int)fv, (void*)&v40, p4);
    }

    if (((Ext*)(*(void**)(self + 0x35c)))->r6f3fe0()) {
        MGR_0040(p4, 4, 0x15, &v40, 1, 0);
        F_777ae0(0x223, 0, 1);
        uint  h3    = (uint)(int)((Ext*)(*(void**)(self + 0x35c)))->r6f3f20((int)(intptr_t)p3[0]);
        float f3ff0 = ((Ext*)(*(void**)(self + 0x35c)))->r6f3ff0((int)(intptr_t)p3[0]);
        float f4010 = ((Ext*)(*(void**)(self + 0x35c)))->r6f4010((int)(intptr_t)p3[0]);
        float f4000 = ((Ext*)(*(void**)(self + 0x35c)))->r6f4000((int)(intptr_t)p3[0]);
        (void)f4010; (void)f4000;
        F_777ae0(0x231, &f3ff0, 0);
        MGR_0040(p4, 8, 8, &h3, 1, 0x1000000);
        MGR_0040(p4, 0xa, 0xa, &h3, 1, 0x1000000);
        MGR_0040(p4, 0xc, 0xf, &h3, 1, 0x1000000);
        MGR_0040(p4, 0x12, 0x12, &h3, 1, 0x1000000);
        F_777ae0(0x231, 0, 0);
        F_777ae0(0x223, &h3, 1);
        goto done;
    }

    if (!((char(__thiscall*)(void*))VFN(*(void**)(self + 0x25c), 0x104))(*(void**)(self + 0x25c))) {
        MGR_0040(p4, 4, 0x15, &v40, 1, 0);
    } else {
        void* c = *(void**)(self + 0x25c);
        int  iVar5 = (int)((int(__thiscall*)(void*))VFN(c, 0x10c))(c);
        PropList_s006e_80d0* pl = (PropList_s006e_80d0*)g_15fd918;
        float  fVar17 = pl->F_6a2710(0x637fee8);
        int    iVar6  = pl->F_6a2660(0x628708c);
        uint   bVar2  = pl->F_6a25a0(0x6395f06);
        uint   bVar3  = pl->F_6a25a0(0x6395efa);
        uint   uVar15 = (bVar3 << 0x18) | (bVar2 << 0x10);
        if (*(void**)(self + 0x360) != 0 && (fv & 8) != 0)
            uVar15 = (uVar15 & 0xffff0000) | 0x100;
        else
            uVar15 = uVar15 & 0xffff0000;

        int slot0[2] = { -1, -1 };   // uStack_d4 / uStack_d0
        if (iVar6 == 3) {
            void* o = F_67dd40();
            ((void(__thiscall*)(void*, int, void*, int))VFN(o, 0xa8))(o, 0, slot0, 0);
        } else if (iVar6 == 2) {
            void* o = F_67dd40();
            ((void(__thiscall*)(void*, int, void*, int))VFN(o, 0xa8))(o, 3, slot0, 0);
        }

        int slot1[2] = { -1, -1 };   // ppuStack_c4 / uStack_c0
        ((Ext*)(*(void**)(self + 0x35c)))->r6f4190(slot1);
        ((Ext*)viewer)->r7c50b0((int)(intptr_t)p3[0], 0, 0);
        ((Ext*)viewer)->r7c4be0(slot0, 1);
        ((Ext*)viewer)->r7c3c50(7);
        uint vvec[4];
        vvec[0] = (uint)(intptr_t)p3[1];
        vvec[1] = (uint)(intptr_t)viewer;
        vvec[2] = (uint)(intptr_t)p3[2];
        vvec[3] = (uint)(intptr_t)p3[3];
        float* pfVar8 = (float*)((Ext*)(*(void**)(self + 0x35c)))->r6f3fb0((int)(intptr_t)p3[0]);
        uint pvec[4];
        pvec[0] = (uint)(intptr_t)p3[1];
        pvec[1] = (uint)(intptr_t)p3[2];
        pvec[2] = (uint)(intptr_t)p3[3];
        pvec[3] = (uint)(intptr_t)pfVar8;
        ((Ext*)viewer)->r7c4be0(slot0, 1);
        float fCur = ((float(__thiscall*)(void*))VFN(c, 0xf8))(c);
        ((Ext*)viewer)->r7c4ba0(fCur - fVar17);

        if (((uVar15 >> 0x10) & 0xff) != 0) {
            if (((uVar15 >> 8) & 0xff) != 0)
                ((Ext*)(*(void**)(self + 0x360)))->r776a60((int)fv, (void*)&vvec[1], p4);
            MGR_0040(p4, 4, 7, (void*)&pvec[0], 1, 0);
            if (iVar5 == 0) {
                MGR_0040(p4, 8, 8, (void*)&pvec[0], 1, 0x4000000);
                MGR_0040(p4, 0xa, 0xa, (void*)&slot1[1], 1, 0x4000000);
                MGR_0040(p4, 0xc, 0x15, (void*)&slot0[1], 1, 0x4000000);
            }
            if (iVar6 > 0)
                ((void(__thiscall*)(void*, int*, int*, int))VFN(slot0, 0x5c))(
                    slot0, slot0, slot1, 0);
        }
        if (((uVar15 >> 0x18) & 0xff) == 0 || iVar5 != 0) {
            if (iVar5 != 1)
                goto done;
            MGR_0040(p4, 8, 0x15, (void*)&vvec[0], 1, 0);
            goto done;
        }
        float fCur2 = ((float(__thiscall*)(void*))VFN(c, 0xf8))(c);
        ((Ext*)viewer)->r7c4bc0(fCur2 + fVar17);
        ((Ext*)viewer)->r7c3c50(6);
        MGR_0040(p4, 8, 0x15, (void*)&pvec[0], 1, 0x2000000);
    }
done:
    if (*(char*)(self + 0x368))
        ((void(__thiscall*)(void*, int, int))VFN(m, 0x5c))(m, 0x16, 2);
}

// @ 0x006e8d70
void CCreature::m8d70(int a2, int a3, void* a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
    Vec28Sink* o = (Vec28Sink*)*(void**)((char*)this + 0x24);
    if (o) {
        Vec3 v = *(Vec3*)a4;
        o->push76d5c0(a2, a3, v, a5, a6, a7, a8, a9, a10);
    }
}

// @ 0x006e8dd0
void CCreature::m8dd0(int a2, int a3, int a4, int a5, void* a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13)
{
    Vec3Sink* o = (Vec3Sink*)*(void**)((char*)this + 0x24);
    if (o) {
        Vec3 v = *(Vec3*)a6;
        o->push76d6e0(a2, a3, a4, a5, v, a7, a8, a9, a10, a11, a12, a13);
    }
}

// @ 0x006e8e40
void CCreature::m8e40(int a, int b)
{
    char* self = (char*)this;
    void* inst = g15ddc84;
    switch (b) {
    case 0:
        ((Ext*)inst)->r7a4420(a, 3, 2, 0);
        *(int*)(self + 4) = 4;
        return;
    case 2:
        ((Ext*)inst)->r7a4420(a, 3, 6, 0);
        *(int*)(self + 4) = 4;
        return;
    case 3:
        ((Ext*)inst)->r7a4420(a, 3, 7, 0);
        *(int*)(self + 4) = 4;
        return;
    case 4:
        ((Ext*)inst)->r7a4420(a, 3, 8, 0);
        *(int*)(self + 4) = 4;
        return;
    default:
        *(int*)(self + 4) = 0;
        return;
    }
}

// @ 0x006e8ee0
int CCreature::m8ee0(int a, int b, int c)
{
    char* self = (char*)this;
    if (*(int*)(self + 4)) {
        void* sb = *(void**)g15ddc84;
        int r = ((Ext*)sb)->r7a47c0(*(int*)(self + 4) * a, b, c);
        return r / *(int*)(self + 4);
    }
    return 0;
}

// @ 0x006e8f20
char CCreature::m8f20(int a, int b, int c, int d, int e)
{
    char* self = (char*)this;
    if (*(int*)(self + 4))
        return ((Ext*)*(void**)g15ddc84)->r7a4910(*(int*)(self + 4) * a, b, c, d, e);
    return 0;
}

// @ 0x006e8f50
int f8f50()
{
    void* sb = *(void**)g15ddc84;
    ((Ext*)sb)->r7a4650();
    return 0;
}

// @ 0x006e8f60
u64 CCreature::m8f60(int a)
{
    void* p = *(void**)((char*)this + 0xc);
    if (p)
        return (u64)((uint(__thiscall*)(void*, int))VFN(p, 0x44))(p, a);
    return 0xffffffffffffffffULL;
}

// @ 0x006e8f90
void S5::m8f90(float a, float b, float c, unsigned char flags)
{
    void* o = *(void**)((char*)this + 0xc);
    if (o == 0 || ((int(__thiscall*)(void*))VFN(o, 0x3c))(o) == 0) {
        if (0.0f < a)
            ((E5*)(*(void**)((char*)this + 4)))->r7c5350(a * 360.0f);
        if (0.0f < b)
            ((E5*)(*(void**)((char*)this + 4)))->r7c4ba0(b);
        if (c <= 0.0f)
            return;
        ((E5*)(*(void**)((char*)this + 4)))->r7c4bc0(c);
        return;
    }
    float v[3];
    v[0] = a; v[1] = b; v[2] = c;
    if ((flags & 0x10) != 0) {
        if (0.0f < a)
            ((void(__thiscall*)(void*, int, float*))VFN(*(void**)((char*)this + 0xc), 4))(
                *(void**)((char*)this + 0xc), 0x109d352, &v[0]);
        if (0.0f < b)
            ((void(__thiscall*)(void*, int, float*))VFN(*(void**)((char*)this + 0xc), 4))(
                *(void**)((char*)this + 0xc), 0x109d372, &v[1]);
        if (c <= 0.0f)
            return;
        ((void(__thiscall*)(void*, int, float*))VFN(*(void**)((char*)this + 0xc), 4))(
            *(void**)((char*)this + 0xc), 0x109d375, &v[2]);
        return;
    }
    if (0.0f < a)
        ((void(__thiscall*)(void*, int, float*))VFN(*(void**)((char*)this + 0xc), 4))(
            *(void**)((char*)this + 0xc), 0x109d174, &v[0]);
    if (0.0f < b)
        ((void(__thiscall*)(void*, int, float*))VFN(*(void**)((char*)this + 0xc), 4))(
            *(void**)((char*)this + 0xc), 0x109d1aa, &v[1]);
    if (c <= 0.0f)
        return;
    ((void(__thiscall*)(void*, int, float*))VFN(*(void**)((char*)this + 0xc), 4))(
        *(void**)((char*)this + 0xc), 0x109d1af, &v[2]);
}

// @ 0x006e9120
int S5::m9120(uint a, uint b)
{
    void* p = *(void**)((char*)this + 0xc);
    if (p != 0 && (a | b) != 0 && (a & b) != 0xffffffff)
        ((void(__thiscall*)(void*, uint))VFN(p, 0x34))(p, a);
    return 0;
}

// @ 0x006e9150
void S5::m9150(int i)
{
    int cnt = (*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) >> 2;
    if (i < cnt - 1) {
        *(int*)(*(int*)((char*)this + 0x10) + i * 4) = -1;
    } else {
        *(int*)((char*)this + 0x14) -= 4;
        int v = *(int*)(*(int*)((char*)this + 0x14) - 4);
        while (v < 0) {
            *(int*)((char*)this + 0x14) -= 4;
            v = *(int*)(*(int*)((char*)this + 0x14) - 4);
        }
        void* o = *(void**)((char*)this + 0xc);
        ((void(__thiscall*)(void*, int))VFN(o, 0x54))(
            o, *(int*)(*(int*)((char*)this + 0x14) - 4));
        if ((uint)((*(int*)((char*)this + 0x14) - *(int*)((char*)this + 0x10)) & 0xfffffffc) == 4)
            *(int*)((char*)this + 0x14) -= 4;
    }
}

// @ 0x006e91c0
void S5::m91c0()
{
    void* p = *(void**)((char*)this + 8);
    if (p)
        ((E5*)p)->r76c210(0x692ea61);
}

// @ 0x006e91e0
void S5::m91e0(int a, int b)
{
    if (*(int*)((char*)this + 8) != 0) {
        void* q = f67dd40();
        if (((char(__thiscall*)(void*))VFN(q, 0x38))(q) == 0) {
            ((E5*)(*(void**)((char*)this + 8)))->r76ba30(a, b, 0, b == 0, 0, 0, 0, (int)&g13ec47c, 0, 0, 0, 0);
        }
    }
}

// @ 0x006e9230
C9230::C9230(const C9230& o)
: m0(o.m0), m8(o.m8), m28(o.m28), m2c(o.m2c),
      f30(o.f30), f34(o.f34), f38(o.f38), f3c(o.f3c), f40(o.f40), f44(o.f44),
      b48(o.b48), b49(o.b49),
      f4c(o.f4c), f50(o.f50), f54(o.f54), f58(o.f58),
      d5c(o.d5c), d60(o.d60), d64(o.d64), d68(o.d68), r6c(o.r6c)
{
}

// @ 0x006e9330
void S5::m9330(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(uint*)d = *(uint*)s;
    memcpy(d + 8, s + 8, 32);
    *(void**)(d + 0x28) = *(void**)(s + 0x28);
    if (*(void**)(d + 0x28))
        (*(int*)((char*)*(void**)(d + 0x28) + 4))++;
    *(float*)(d + 0x2c) = *(float*)(s + 0x2c);
    *(float*)(d + 0x30) = *(float*)(s + 0x30);
    *(float*)(d + 0x34) = *(float*)(s + 0x34);
    *(float*)(d + 0x38) = *(float*)(s + 0x38);
    *(float*)(d + 0x3c) = *(float*)(s + 0x3c);
    *(float*)(d + 0x40) = *(float*)(s + 0x40);
    *(float*)(d + 0x44) = *(float*)(s + 0x44);
    *(uchar*)(d + 0x48) = *(uchar*)(s + 0x48);
    *(uchar*)(d + 0x49) = *(uchar*)(s + 0x49);
    *(float*)(d + 0x4c) = *(float*)(s + 0x4c);
    *(float*)(d + 0x50) = *(float*)(s + 0x50);
    *(float*)(d + 0x54) = *(float*)(s + 0x54);
    *(float*)(d + 0x58) = *(float*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(uint*)(d + 0x60) = *(uint*)(s + 0x60);
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    *(uint*)(d + 0x68) = *(uint*)(s + 0x68);
}

// @ 0x006e94a0
int f94a0(int p1, int p2, int p3)
{
    if (p1 != p2) {
        do {
            void* r = *(void**)(p1 + 0x28);
            if (r != 0) {
                int n = *(int*)((char*)r + 4);
                n += -1;
                *(int*)((char*)r + 4) = n;
                if (n == 0) {
                    *(int*)((char*)r + 4) = 1;
                    _ReadWriteBarrier();
                    ((void(__thiscall*)(void*, int))VFN(r, 0))(r, 1);
                }
            }
            p1 += 0x70;
            p3 += 0x70;
        } while (p1 != p2);
    }
    return p3;
}

// @ 0x006e9530
S5* S5::m9530()
{
    float c = g1533c74;
    *(Vec3*)((char*)this) = MakeV3(c);
    *(Vec3*)((char*)this + 0xc) = MakeV3(-c);
    return this;
}

// @ 0x006e95a0
void S5::m95a0(unsigned char* p)
{
    const UnitBox* box = (const UnitBox*)p;
    Bounds6* b = (Bounds6*)this;
    // 0x1533c74 is FLT_MAX (the "uninitialised bounds" sentinel), 0x13eb8b0 the sign mask of its negative
    if (b->minX == g1533c74 || b->minX == -g1533c74)
        return;
    if ((box->flags >> 1 & 1) != 0) {
        float m[9];
        f6e6e90(box->absMatrix, m);       // |m| of the 3x3, nine floats
        float h = box->scale * 0.5f;
        // half/half sums of the box (centre*2 and size*2) scaled by h
        float ea2 = (b->maxZ + b->minZ) * h;
        float ea1 = (b->maxY + b->minY) * h;
        float ea0 = (b->maxX + b->minX) * h;
        float ed2 = (b->maxZ - b->minZ) * h;
        float ed1 = (b->maxY - b->minY) * h;
        float ed0 = (b->maxX - b->minX) * h;
        float ax = (m[6] * ed2 + m[3] * ed1) + m[0] * ed0;   // extent along x
        float ay = (m[7] * ed2 + m[4] * ed1) + m[1] * ed0;   // extent along y
        float az = (m[8] * ed2 + m[5] * ed1) + m[2] * ed0;   // extent along z
        // the centre offset uses the signed matrix, the half extents the f6e6e90 copy of |m|
        float cx = box->centreX + ((box->absMatrix[6] * ea2 + box->absMatrix[3] * ea1) + ea0 * box->absMatrix[0]);
        float cy = box->centreY + ((box->absMatrix[7] * ea2 + box->absMatrix[4] * ea1) + box->absMatrix[1] * ea0);
        float cz = box->centreZ + ((box->absMatrix[8] * ea2 + box->absMatrix[5] * ea1) + box->absMatrix[2] * ea0);
        b->minX = cx - ax;
        b->minY = cy - ay;
        b->minZ = cz - az;
        b->maxX = cx + ax;
        b->maxY = cy + ay;
        b->maxZ = cz + az;
        return;
    }
    float k = box->scale;
    b->minX = b->minX * k + box->centreX;
    b->minY = box->centreY + b->minY * k;
    b->minZ = box->centreZ + b->minZ * k;
    b->maxX = b->maxX * k + box->centreX;
    b->maxY = box->centreY + b->maxY * k;
    b->maxZ = box->centreZ + b->maxZ * k;
}

// @ 0x006e9910
void S5::m9910(float d)
{
    float* p = (float*)this;
    float f = p[0];
    float C = g1533c74;
    if (f != C && f != -C) {
        p[0] = f - d;
        p[1] = p[1] - d;
        p[2] = p[2] - d;
        p[3] = p[3] + d;
        p[4] = p[4] + d;
        p[5] = p[5] + d;
    }
}

// @ 0x006e9990
C9990::~C9990()
{
    void* a = m10;
    if (a != 0 && *(int*)((char*)a - 4) != 0)
        f_f47380(a);
    if (mC != 0)
        ((Iface4*)mC)->v3();
}

// @ 0x006e9a30
C9A30::~C9A30()
{
    void* a = m30d68;
    if (a != 0 && *(int*)((char*)a - 4) != 0)
        f_f47380(a);
    a = m30d54;
    if (a != 0 && *(int*)((char*)a - 4) != 0)
        f_f47380(a);
    int* p = m4;
    if (p != 0) {
        int n = p[1] + -1;
        p[1] = n;
        if (n == 0) {
            p[1] = 1;
            _ReadWriteBarrier();
            ((void(__thiscall*)(void*, int))(*(void***)p)[0])(p, 1);
        }
    }
}

// @ 0x006e9b00
S5* S5::m9b00()
{
    char* p = (char*)this;
    *(uint*)(p + 0) = 0;
    *(int*)(p + 8) = -1;
    *(int*)(p + 0xc) = -1;
    *(uchar*)(p + 0x10) = 0;
    *(uchar*)(p + 0x11) = 0;
    *(uchar*)(p + 0x12) = 0;
    *(uchar*)(p + 0x13) = 0;
    *(ushort*)(p + 0x14) = 0;
    *(float*)(p + 0x18) = 0.0f;
    *(int*)(p + 0x20) = -1;
    *(int*)(p + 0x24) = -1;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x2c) = 0;
    float C = g1533c74;
    *(float*)(p + 0x30) = C;
    *(float*)(p + 0x34) = C;
    *(float*)(p + 0x38) = C;
    float N = -C;
    *(float*)(p + 0x3c) = N;
    *(float*)(p + 0x40) = N;
    *(float*)(p + 0x44) = N;
    *(uchar*)(p + 0x48) = 0;
    *(uchar*)(p + 0x49) = 0;
    float one = 1.0f;
    *(float*)(p + 0x4c) = one;
    *(float*)(p + 0x50) = one;
    *(float*)(p + 0x54) = one;
    *(float*)(p + 0x58) = one;
    *(int*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
    *(int*)(p + 0x64) = 0;
    *(int*)(p + 0x68) = 0;
    *(int*)(p + 0x6c) = 0;
    return this;
}

// @ 0x006e9bf0
S5* S5::m9bf0()
{
    char* p = (char*)this;
    *(uint*)(p + 0) = 0;
    *(float*)(p + 0x18) = 0.0f;
    float C = g1533c74;
    *(uchar*)(p + 0x10) = 0;
    *(uchar*)(p + 0x11) = 0;
    *(uchar*)(p + 0x12) = 0;
    *(uchar*)(p + 0x13) = 0;
    *(int*)(p + 8) = -1;
    *(int*)(p + 0xc) = -1;
    *(int*)(p + 0x20) = -1;
    *(int*)(p + 0x24) = -1;
    *(ushort*)(p + 0x14) = 0;
    *(int*)(p + 0x28) = 0;
    *(float*)(p + 0x2c) = C;
    *(float*)(p + 0x30) = C;
    *(float*)(p + 0x34) = C;
    float N = -C;
    *(float*)(p + 0x38) = N;
    *(float*)(p + 0x3c) = N;
    *(float*)(p + 0x40) = N;
    float one = 1.0f;
    *(float*)(p + 0x44) = one;
    *(uchar*)(p + 0x48) = 0;
    *(uchar*)(p + 0x49) = 0;
    *(float*)(p + 0x4c) = one;
    *(float*)(p + 0x50) = one;
    *(float*)(p + 0x54) = one;
    *(float*)(p + 0x58) = one;
    *(int*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
    *(int*)(p + 0x64) = 0;
    *(int*)(p + 0x68) = 0;
    return this;
}

// @ 0x006e9cc0
void* S5::m9cc0()
{
    char* p = (char*)this;
    float one = 1.0f;
    *(uint*)(p + 0) = 0;
    *(float*)(p + 4) = one;
    *(float*)(p + 8) = one;
    *(float*)(p + 0xc) = one;
    *(float*)(p + 0x10) = one;
    *(float*)(p + 0x14) = one;
    *(ushort*)(p + 0x1a) = 0;
    *(ushort*)(p + 0x18) = 0;
    *(float*)(p + 0x1c) = *(float*)0x1618de0;
    *(float*)(p + 0x20) = *(float*)0x1618de4;
    *(float*)(p + 0x24) = *(float*)0x1618de8;
    *(float*)(p + 0x28) = one;
    ((E5*)(p + 0x2c))->r41cb40(&g1618f60);
    *(uchar*)(p + 0x50) = 0;
    *(uchar*)(p + 0x51) = 0;
    *(int*)(p + 0x54) = 0;
    *(int*)(p + 0x58) = 0;
    *(int*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
    *(int*)(p + 0x64) = -1;
    return this;
}

// @ 0x006e9d50
void S5::m9d50(void* out)
{
    char* self = (char*)this;
    char* o = (char*)out;
    int* src = *(int**)(self + 0x20);
    if (!src)
        return;
    *(int*)(o + 0x5c) = src[0];
    *(int*)(o + 0x60) = src[1];
    *(int*)(o + 0x64) = src[2];
    *(int*)(o + 0x68) = src[4];
    *(int*)(o + 0x6c) = src[5];
    *(int*)(o + 0x70) = src[6];
    *(int*)(o + 0x74) = src[8];
    *(int*)(o + 0x78) = src[9];
    *(int*)(o + 0x7c) = src[10];
    *(int*)(o + 0x80) = src[0xc];
    *(int*)(o + 0x84) = src[0xd];
    *(int*)(o + 0x88) = src[0xe];
    if (*(char*)(self + 0x1e5) == 0) {
        *(int*)(o + 0x8c) = src[0xc];
        *(int*)(o + 0x90) = src[0xd];
        *(int*)(o + 0x94) = src[0xe];
    } else {
        *(int*)(o + 0x8c) = *(int*)(self + 0x1e8);
        *(int*)(o + 0x90) = *(int*)(self + 0x1ec);
        *(int*)(o + 0x94) = *(int*)(self + 0x1f0);
    }
    int* s = (int*)(*(int*)(self + 0x20) + 0xc0);
    int* d = (int*)(o + 0x1c);
    for (int i = 0; i < 0x10; i++)
        d[i] = s[i];
    if (*(char*)(self + 0x1f4) == 0) {
        *(char*)(o + 0xb0) = 0;
        *(int*)(self + 0x44) = (int)o;
        *(char*)(self + 0x1f4) = 0;
        return;
    }
    int rect[4];
    ((E5*)(*(void**)(self + 0x20)))->r7c4010(rect);
    int v1 = *(int*)(self + 0x1f8);
    int v2 = *(int*)(self + 0x1fc);
    *(int*)(o + 0x98) = *(int*)(o + 0x80);
    *(int*)(o + 0x9c) = *(int*)(o + 0x84);
    *(int*)(o + 0xa0) = *(int*)(o + 0x88);
    const ProjMatrix* pm = (const ProjMatrix*)(*(char**)(self + 0x20) + 0x100);
    FrameTail* frame = (FrameTail*)(o + 0x98);
    // screen -> clip: x and y go through their own denominators (the caller's rect, not the neighbour edge)
    float fy = (float)((rect[1] - v2) * 2) / (float)(rect[3] - rect[1]) + 1.0f;
    float fx = (float)((v1 - rect[0]) * 2) / (float)(rect[2] - rect[0]) - 1.0f;
    float iw = 1.0f / (((pm->m13 * fy + pm->m03 * fx) + pm->m33) + pm->m23);
    float pz = (((pm->m12 * fy + pm->m02 * fx) + pm->m32) + pm->m22) * iw - frame->viewport[2];
    float py = (((pm->m11 * fy + pm->m01 * fx) + pm->m31) + pm->m21) * iw - frame->viewport[1];
    float px = (((pm->m10 * fy + pm->m00 * fx) + pm->m30) + pm->m20) * iw - frame->viewport[0];
    frame->hasDir = 1;
    float n = 1.0f / (float)sqrt((double)(((py * py + px * px) + pz * pz) + 1e-08f));
    frame->dirX = n * px;
    frame->dirY = py * n;
    frame->dirZ = pz * n;
    frame->frameTag = frame->frame ^ *(uint*)(self + 0x200);
    frame->frame = *(uint*)(self + 0x200);
    *(int*)(self + 0x44) = (int)o;
    *(char*)(self + 0x1f4) = 0;
}

// @ 0x006ea030
void S6::m030(int a, int b, int c)
{
    char* self = (char*)this;
    void* mm = f67dd70();
    int uVar3 = (int)((int(__thiscall*)(void*, int))VFN(mm, 0x28))(mm, 0);
    if (f7c4fd0() == 0)
        return;
    f777bf0();
    int n = (*(int*)(self + 0x60) - *(int*)(self + 0x5c)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x5c) + i * 2) * 0x70 + *(int*)(self + 0x48);
        if ((*(uchar*)(e + 0x12) & 4) == 0)
            f6e6ee0((void*)(e + 0x30), uVar3, g1533c98, c);
    }
    n = (*(int*)(self + 0x60) - *(int*)(self + 0x5c)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x5c) + i * 2) * 0x70 + *(int*)(self + 0x48);
        if ((*(uchar*)(e + 0x12) & 4) != 0)
            f6e6ee0((void*)(e + 0x30), uVar3, g1533c9c, c);
    }
    n = (*(int*)(self + 0x18c) - *(int*)(self + 0x188)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x188) + i * 2) * 0x70 + *(int*)(self + 0x174);
        if ((*(uchar*)(e + 0x12) & 4) == 0) {
            float box[6];
            box[0] = *(float*)(e + 0x2c); box[1] = *(float*)(e + 0x30); box[2] = *(float*)(e + 0x34);
            box[3] = *(float*)(e + 0x38); box[4] = *(float*)(e + 0x3c); box[5] = *(float*)(e + 0x40);
            float d = *(float*)(*(int*)(e + 0x28) + 0x68) * *(float*)(e + 0x44);
            if (box[0] != g1533c74 && box[0] != -g1533c74) {
                box[0] -= d; box[1] -= d; box[2] -= d;
                box[3] += d; box[4] += d; box[5] += d;
            }
            f6e6ee0(box, uVar3, g1533c98, c);
        }
    }
    n = (*(int*)(self + 0x18c) - *(int*)(self + 0x188)) >> 1;
    for (int i = 0; i < n; i++) {
        int e = *(ushort*)(*(int*)(self + 0x188) + i * 2) * 0x70 + *(int*)(self + 0x174);
        if ((*(uchar*)(e + 0x12) & 4) != 0) {
            float box[6];
            box[0] = *(float*)(e + 0x2c); box[1] = *(float*)(e + 0x30); box[2] = *(float*)(e + 0x34);
            box[3] = *(float*)(e + 0x38); box[4] = *(float*)(e + 0x3c); box[5] = *(float*)(e + 0x40);
            float d = *(float*)(*(int*)(e + 0x28) + 0x68) * *(float*)(e + 0x44);
            if (box[0] != g1533c74 && box[0] != -g1533c74) {
                box[0] -= d; box[1] -= d; box[2] -= d;
                box[3] += d; box[4] += d; box[5] += d;
            }
            f6e6ee0(box, uVar3, g1533ca0, c);
        }
    }
    n = (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68;
    for (int i = 0; i < n; i++) {
        int e = *(int*)(self + 0x1b8) + i * 0x68;
        if (*(uchar*)(e + 0x50) != 0 && *(int*)e != 0) {
            float box[6];
            int v = *(int*)e;
            box[0] = *(float*)(v + 0x50); box[1] = *(float*)(v + 0x54); box[2] = *(float*)(v + 0x58);
            box[3] = *(float*)(v + 0x5c); box[4] = *(float*)(v + 0x60); box[5] = *(float*)(v + 0x64);
            f6e95a0((void*)(e + 0x18));
            f6e6ee0(box, uVar3, g1533ca4, c);
        }
    }
    f777c10();
    f7c3c10();
}

// @ 0x006ea470
void S6::m470(int a, uint flags, int c, void* viewer)
{
    char* self = (char*)this;
    *(int*)(self + 0x168) = -1;

    uchar mask = 0;
    if (flags & 0x20000) mask = 8;
    if (flags & 0x40000) mask |= 0x40;

    if (!((char(__thiscall*)(void*))f7c4fd0)(viewer))
        return;

    f777bf0();
    f6ddde0(3, 2);

    int* rec = *(int**)(self + 0x104 + a * 0x14);
    int** endp = (int**)(self + 0x108 + a * 0x14);
    float mid[3];
    mid[0] = mid[1] = mid[2] = 0.0f;

    uchar changed = 0;    // local_5e: a shader-data push is live
    uchar lastBit2 = 0;   // local_5d: previous entity's batched-draw bit
    int shader68 = 0, shader5c = 0, shader60 = 0, tex28 = 0, tex2c = 0;

    while (rec != *endp) {
        int* e = (int*)rec[1];
        uchar ef = *(uchar*)((char*)e + 0x12);
        bool pass = (ef & mask) == mask;
        bool skip = false;

        if ((ef & 0x10) == 0) {
            if (!pass) {
                skip = true;
            } else {
                float b1[3], b2[3];
                b1[0] = *(float*)((char*)e + 0x3c);
                b1[1] = *(float*)((char*)e + 0x40);
                b1[2] = *(float*)((char*)e + 0x44);
                b2[0] = *(float*)((char*)e + 0x30);
                b2[1] = *(float*)((char*)e + 0x34);
                b2[2] = *(float*)((char*)e + 0x38);
                uint r = ((uint(__thiscall*)(void*, float*, float*, uint))f700120)
                    (self + 0x260, b2, b1, 0x200);
                if ((r & 0x40) != 0)
                    skip = true;
            }
        } else if (!pass) {
            skip = true;
        }

        if (!skip && e[0] != 0) {
            uchar bit2 = (uchar)((ef >> 2) & 1);
            if (changed
                || shader5c != e[0x17] || shader60 != e[0x18]
                || tex28 != e[10] || tex2c != e[0xb]
                || *(uint*)(self + 0x168) != (uint)*(uchar*)((char*)e + 0x10)
                || shader68 != e[0x1a] || lastBit2 != bit2) {
                f6ddef0(c);
                if (changed)
                    f777c10();
                f777c10();
                *(uint*)(self + 0x168) = (uint)*(uchar*)((char*)e + 0x10);
                shader68 = e[0x1a];
                shader5c = e[0x17];
                shader60 = e[0x18];
                tex28 = e[10];
                tex2c = e[0xb];
                f777bf0();
                f777b50(*(void**)(shader5c + 4));
                if ((ef & 3) != 0)
                    f777ae0(0x223, 0, 1);
                ((void(__thiscall*)(void*))f11ee580)(*(void**)(shader5c + 4));
                if (e[10] != 0) {
                    f11f1280(0, *(void**)e[10]);
                    g16f8b00 |= 1;
                }
                if (e[0xb] != 0) {
                    f11f1280(1, *(void**)e[0xb]);
                    g16f8b00 |= 2;
                }
                if (e[0x18] != 0)
                    ((void(__thiscall*)(void*))f7789d0)((void*)e[0x18]);
                int outA, outB;
                f6e6710((char)e[4], &outA, &outB);
                f6ddde0(outA, outB);
                lastBit2 = bit2;
            }
            f777bf0();
            if (e[0x1a] != 0)
                f777ae0(0x219, *(int*)e[0x1a], 0);
            if (e[0x19] != 0)
                f777ae0(0x206, e[0x19], 0);
            if ((ef & 3) != 3) {
                mid[0] = ((float)e[0x0f] + (float)e[0x0c]) * g1471064;
                mid[1] = ((float)e[0x10] + (float)e[0x0d]) * g1471064;
                mid[2] = ((float)e[0x11] + (float)e[0x0e]) * g1471064;
                f777ae0(0x226, (int)mid, 1);
            }
            if (bit2 == 0) {
                void* obj = (void*)e[0];
                ((void(__thiscall*)(void*, void*))VFN(obj, 0))(obj, self + 4);
            } else {
                if (e[0x1b] == 0) {
                    ((void(__thiscall*)(void*, int, int))f6e8e40)
                        (self + 0x16c, 0, *(int*)(self + 0x168));
                    void* obj = (void*)e[0];
                    ((void(__thiscall*)(void*, void*))VFN(obj, 0))(obj, self + 0x16c);
                    int* q = (int*)e[0x1b];
                    if (q != 0) {
                        e[0x1b] = 0;
                        ((void(__thiscall*)(void*))VFN(q, 8))(q);
                    }
                    void** slot = (void**)g15ddc84_s006e_a030;
                    ((void(__thiscall*)(void*))f7a4710)(slot[0]);
                    e[0x1b] = (int)slot[0];
                    slot[0] = 0;
                }
                if (e[0x1b] != 0) {
                    int quad[4];
                    quad[0] = e[0x13]; quad[1] = e[0x14];
                    quad[2] = e[0x15]; quad[3] = e[0x16];
                    f6e6500(quad);
                    g16f9110 |= 0x10;
                    ((void(__thiscall*)(void*, int, int))f7a3e60)
                        ((void*)e[0x1b], c, 0);
                    uchar* pb = (uchar*)e[0x17];
                    if (pb != 0 && pb[0] > 1) {
                        int i = 1;
                        do {
                            ((void(__thiscall*)(void*))f11ee580)
                                (*(void**)(pb + i * 4 + 4));
                            ((void(__thiscall*)(void*, int, int))f7a3e60)
                                ((void*)e[0x1b], c, 0);
                            pb = (uchar*)e[0x17];
                            i++;
                        } while (i < (int)pb[0]);
                    }
                    f6e6500(&g140afc4);
                    g16f9110 |= 0x10;
                }
            }
            changed = (uchar)f777c90();
            if (!changed)
                f777c10();
            *(int*)(self + 0x370) += 1;
            endp = (int**)(self + 0x108 + a * 0x14);
        }
        rec += 2;
    }

    f6ddef0(c);
    if (changed)
        f777c10();
    f777c10();
    ((void(__thiscall*)(void*))f7c3c10)(viewer);
}

// @ 0x006ea920
void S6::m920()
{
    char* self = (char*)this;
    void* p = *(void**)(self + 0x6c);
    if (p)
        ((void(__thiscall*)(void*))VFN(p, 8))(p);
    void* q = *(void**)(self + 0x2c);
    if (q) {
        volatile long* rc = (volatile long*)((char*)q + 8);
        if (_InterlockedDecrement(rc) < 1)
            _InterlockedIncrement(rc);
    }
    void* r = *(void**)(self + 0x28);
    if (r) {
        volatile long* rc = (volatile long*)((char*)r + 8);
        if (_InterlockedDecrement(rc) < 1)
            _InterlockedIncrement(rc);
    }
}

// @ 0x006ea9e0
void S6::m9e0(int idx, float* box, float pad)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70)
        return;
    int e = idx * 0x70 + *(int*)(self + 0x48);
    *(float*)(e + 0x3c) = box[3];
    *(float*)(e + 0x40) = box[4];
    *(float*)(e + 0x44) = box[5];
    *(float*)(e + 0x30) = box[0];
    *(float*)(e + 0x34) = box[1];
    *(float*)(e + 0x38) = box[2];
    float f = *(float*)(e + 0x30);
    pad = pad * 0.5f;
    if (f != g1533c74 && f != -g1533c74) {
        *(float*)(e + 0x30) = f - pad;
        *(float*)(e + 0x34) = *(float*)(e + 0x34) - pad;
        *(float*)(e + 0x38) = *(float*)(e + 0x38) - pad;
        *(float*)(e + 0x3c) = pad + *(float*)(e + 0x3c);
        *(float*)(e + 0x40) = pad + *(float*)(e + 0x40);
        *(float*)(e + 0x44) = pad + *(float*)(e + 0x44);
    }
    void* h = *(void**)(self + 0x1e0);
    if (h) {
        float c[3];
        if (*box == g1533c74) {
            c[0] = *(float*)0x1618de0;
            c[1] = *(float*)0x1618de4;
            c[2] = *(float*)0x1618de8;
        } else {
            c[0] = (*box + box[3]) * 0.5f;
            c[1] = (box[4] + box[1]) * 0.5f;
            c[2] = (box[5] + box[2]) * 0.5f;
        }
        if (*(int*)(e + 0x68) == 0)
            *(int*)(e + 0x68) =
                ((int(__thiscall*)(void*, float, float*))VFN(h, 0x18))(h, 1.0f, c);
        else
            ((void(__thiscall*)(void*, float, float*, int))VFN(h, 0x1c))(
                h, 1.0f, c, *(int*)(e + 0x68));
    }
    void* vl = *(void**)(e + 0x6c);
    if (vl) {
        *(void**)(e + 0x6c) = 0;
        ((void(__thiscall*)(void*))VFN(vl, 8))(vl);
    }
}

// @ 0x006eabc0
R70* R70::mabc0(const R70& src)
{
    char* d = (char*)this;
    char* s = (char*)&src;
    *(uint*)d = *(uint*)s;
    memcpy(d + 8, s + 8, 32);
    void* n = *(void**)(s + 0x28);
    void* o = *(void**)(d + 0x28);
    if (n != o) {
        if (n)
            (*(int*)((char*)n + 4))++;
        *(void**)(d + 0x28) = n;
        if (o) {
            int v = (*(volatile int*)((char*)o + 4) += -1);
            if (v == 0) {
                *(int*)((char*)o + 4) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(void*, int))VFN(o, 0))(o, 1);
            }
        }
    }
    *(uint*)(d + 0x38) = *(uint*)(s + 0x38);
    *(uint*)(d + 0x3c) = *(uint*)(s + 0x3c);
    *(uint*)(d + 0x40) = *(uint*)(s + 0x40);
    *(uint*)(d + 0x2c) = *(uint*)(s + 0x2c);
    *(uint*)(d + 0x30) = *(uint*)(s + 0x30);
    *(uint*)(d + 0x34) = *(uint*)(s + 0x34);
    *(float*)(d + 0x44) = *(float*)(s + 0x44);
    *(uchar*)(d + 0x48) = *(uchar*)(s + 0x48);
    *(uchar*)(d + 0x49) = *(uchar*)(s + 0x49);
    *(uint*)(d + 0x4c) = *(uint*)(s + 0x4c);
    *(uint*)(d + 0x50) = *(uint*)(s + 0x50);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(float*)(d + 0x58) = *(float*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(uint*)(d + 0x60) = *(uint*)(s + 0x60);
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    *(uint*)(d + 0x68) = *(uint*)(s + 0x68);
    return this;
}

// @ 0x006eac80
R70* R70::mac80(const R70& src)
{
    char* d = (char*)this;
    char* s = (char*)&src;
    void* n = *(void**)s;
    void* o = *(void**)d;
    if (n != o) {
        if (n)
            (*(int*)((char*)n + 4))++;
        *(void**)d = n;
        if (o) {
            int v = (*(volatile int*)((char*)o + 4) += -1);
            if (v == 0) {
                *(int*)((char*)o + 4) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(void*, int))VFN(o, 0))(o, 1);
            }
        }
    }
    *(uint*)(d + 4) = *(uint*)(s + 4);
    *(uint*)(d + 8) = *(uint*)(s + 8);
    *(uint*)(d + 0xc) = *(uint*)(s + 0xc);
    *(float*)(d + 0x10) = *(float*)(s + 0x10);
    *(float*)(d + 0x14) = *(float*)(s + 0x14);
    ((E6*)(d + 0x18))->r537dc0(s + 0x18);
    *(uchar*)(d + 0x50) = *(uchar*)(s + 0x50);
    *(uchar*)(d + 0x51) = *(uchar*)(s + 0x51);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(uint*)(d + 0x58) = *(uint*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    _ReadWriteBarrier();
    void* n2 = *(void**)(s + 0x60);
    void* o2 = *(void**)(d + 0x60);
    if (n2 != o2) {
        if (n2)
            ((void(__thiscall*)(void*))VFN(n2, 0))(n2);
        *(void**)(d + 0x60) = n2;
        if (o2)
            ((void(__thiscall*)(void*))VFN(o2, 4))(o2);
    }
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    return this;
}

// @ 0x006ead40
void S6::mad40(int idx, void* xf)
{
    char* self = (char*)this;
    int e = idx * 0x68 + *(int*)(self + 0x1b8);
    void* o = *(void**)(e + 0x60);
    if (o) {
        ((void(__thiscall*)(void*, int, void*))VFN(o, 0x14))(o, idx, xf);
        return;
    }
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x1bc) - *(int*)(self + 0x1b8)) / 0x68)
        return;
    ((E6*)(e + 0x18))->r537dc0(xf);
    float a = *(float*)(e + 0x14);
    float b = *(float*)(e + 0x28);
    *(ushort*)(e + 0x18) |= 1;
    *(ushort*)(e + 0x1a) = *(ushort*)(e + 0x1a) + 1;
    *(float*)(e + 0x28) = a * b;
    void* h = *(void**)(self + 0x1e0);
    if (h) {
        float c[3];
        c[0] = *(float*)((char*)xf + 4);
        c[1] = *(float*)((char*)xf + 8);
        c[2] = *(float*)((char*)xf + 0xc);
        if (*(int*)(e + 0x5c) == 0)
            *(int*)(e + 0x5c) =
                ((int(__thiscall*)(void*, float, float*))VFN(h, 0x18))(h, 1.0f, c);
        else
            ((void(__thiscall*)(void*, float, float*, int))VFN(h, 0x1c))(
                h, 1.0f, c, *(int*)(e + 0x5c));
    }
}

// @ 0x006eae40
int EffectsRenderer::ReleaseAndDrawModelBuffer()
{
    if (mBufferedCount != 0) {
        SetBlendMode(0x60005);
        g_renderStateDirty |= 0x60100;
        g_16f921c = 1;
        g_16f9244 = 5;
        g_16f9240 = 0;

        if (mCurrentVDesc == 0 || mBufferedCount < mMinInstancingCount) {
            // Not enough instances to be worth hardware instancing: cull and draw each one.
            Box3 box = *(Box3*)&mModel->mBoxMin;
            V3 neg(-box.mMin.x, -box.mMin.y, -box.mMin.z);
            if (mList != 0) {
                V3 ext(Max(neg.x, box.mMax.x), Max(neg.y, box.mMax.y), Max(neg.z, box.mMax.z));
                float minAlpha = sAppProperties->mConfig->mMinAlpha;
                for (int i = 0; i < mBufferedCount; i++) {
                    RenderCtx* g = g_pCtx;
                    const ModelInstance& inst = g->mInstances[i];
                    if (*(float*)&inst.mColor[3] > minAlpha) {
                        float r = sqrtf(inst.mRow[0].z * inst.mRow[0].z + inst.mRow[0].y * inst.mRow[0].y +
                                        inst.mRow[0].x * inst.mRow[0].x);
                        V3 t = *(V3*)&inst.mRow[3];
                        V3 mn(t.x - ext.x * r, t.y - ext.y * r, t.z - ext.z * r);
                        V3 mx(ext.x * r + t.x, ext.y * r + t.y, ext.z * r + t.z);
                        if ((mFrustum.FrustumTestSphere(&mn, &mx, 0x200) & 0x40) == 0) {
                            const ModelInstance& cur = g_pCtx->mInstances[i];
                            EffectsDispatch(&cur, 2);
                            g_softStateDirty |= 0x10;
                            g_color = *(ColorRGBA*)&g_pCtx->mInstances[i].mColor;
                            mModel->DispatchList(mList, mMaterial);
                        }
                    }
                }
            } else {
                V3 ext(Max(neg.x, box.mMax.x), Max(neg.y, box.mMax.y), Max(neg.z, box.mMax.z));
                float minAlpha = sAppProperties->mConfig->mMinAlpha;
                for (int i = 0; i < mBufferedCount; i++) {
                    RenderCtx* g = g_pCtx;
                    const ModelInstance& inst = g->mInstances[i];
                    if (*(float*)&inst.mColor[3] > minAlpha) {
                        float r = sqrtf(inst.mRow[0].z * inst.mRow[0].z + inst.mRow[0].y * inst.mRow[0].y +
                                        inst.mRow[0].x * inst.mRow[0].x);
                        V3 t = *(V3*)&inst.mRow[3];
                        V3 mn(t.x - ext.x * r, t.y - ext.y * r, t.z - ext.z * r);
                        V3 mx(ext.x * r + t.x, ext.y * r + t.y, ext.z * r + t.z);
                        if ((mFrustum.FrustumTestSphere(&mn, &mx, 0x200) & 0x40) == 0) {
                            const ModelInstance& cur = g_pCtx->mInstances[i];
                            EffectsDispatch(&cur, 2);
                            g_softStateDirty |= 0x10;
                            g_color = *(ColorRGBA*)&g_pCtx->mInstances[i].mColor;
                            mModel->DispatchWithAdditionalMaterial(mMaterial);
                        }
                    }
                }
            }
        } else {
            // Hardware instancing: pack every queued transform into the instance vertex buffer
            // and draw them with one call.
            int i;
            if (g_pCtx->mUsed + mBufferedCount > 0x9c4)
                g_pCtx->mUsed = 0;
            if (!mCanUseInstancing)
                g_pCtx->mUsed = 0;
            int start = g_pCtx->mUsed;
            void* data;
            int lockType = 6;
            if (start != 0)
                lockType = 10;
            if (!g_pCtx->mVB->Lock(lockType, &data, &start, start, mBufferedCount))
                return 0;
            g_pCtx->mUsed += mBufferedCount;

            float* dst = (float*)data;
            for (i = 0; i < mBufferedCount; i++, dst += 13) {
                const ModelInstance& m = g_pCtx->mInstances[i];
                dst[0] = GetRow(m, 0).x;
                dst[1] = GetRow(m, 1).x;
                dst[2] = GetRow(m, 2).x;
                dst[3] = GetRow(m, 3).x;
                dst[4] = GetRow(m, 0).y;
                dst[5] = GetRow(m, 1).y;
                dst[6] = GetRow(m, 2).y;
                dst[7] = GetRow(m, 3).y;
                dst[8] = GetRow(m, 0).z;
                dst[9] = GetRow(m, 1).z;
                dst[10] = GetRow(m, 2).z;
                dst[11] = GetRow(m, 3).z;
                *(uint*)&dst[12] = ColorRGBAToU32(&m.mColor);
            }
            g_pCtx->mVB->Unlock();

            DispatchPair* entry = mModel->mDispatchBegin;
            if (entry != mModel->mDispatchEnd) {
                PushShaderDataNull();
                DrawData* draw = entry->mpData;
                EmbeddedState_s006e_ae40* state = entry->mpHolder->mpState;
                g_pCtx->mState->mField1c = 0;
                g_pCtx->mState->mField20 = draw->mpField24->mField0c;
                g_pCtx->mState->SetA(draw->mField08);
                g_pCtx->mState->SetB(draw->mField18);
                g_pCtx->mState->SetC(0, (int)draw->mpField24);

                struct { Vector4 r[4]; } ident = {
                    { Vector4(1.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f),
                      Vector4(0.0f, 0.0f, 1.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f) } };
                if (state->mSoftStateDirty & 1)
                    state->D3D9SetTransform(&ident, 4, 1);
                else
                    EffectsDispatch(&ident, 4);
                g_softStateDirty |= 0x10;
                g_color = g_whiteColor;
                SetVertexDescriptor(mCurrentVDesc);
                SetShaderData(state);
                state->Dispatch();
                if (entry->mpShader)
                    entry->mpShader->Push();
                VertexDescriptorChange(mCurrentVDesc);
                g_d3dDevice->SetStreamSourceFreq(0, mBufferedCount | 0x40000000);
                g_d3dDevice->SetStreamSourceFreq(1, 0x80000001);
                VertexBuffer* vb = g_pCtx->mVB;
                vb->mStart = start;
                g_pCtx->mState->Draw();
                vb->mStart = 0;
                g_d3dDevice->SetStreamSourceFreq(0, 1);
                g_d3dDevice->SetStreamSourceFreq(1, 1);
                PopShaderData();
            }
        }
        mBufferedCount = 0;
    }
    if (mFlag160 == 0)
        mCounter36c++;
    else
        mCounter370++;
    return 0;
}

// @ 0x006eb6e0
void CEM7::UpdateCameraView(int a, uint flags)
{
    char* self = (char*)this;
    void* cam = *(void**)(self + 0xc);
    if (cam == 0 || ((int(__thiscall*)(void*))VFN(cam, 0x3c))(cam) == 0) {
        f7c4d00(a);
        return;
    }
    float v[3];
    v[0] = *(float*)(a + 4);
    v[1] = *(float*)(a + 8);
    v[2] = *(float*)(a + 0xc);
    if (flags & 1) {
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b542, v);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b541, v);
    } else {
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b537, v);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101b534, v);
    }
    if (flags & 8) {
        cam = *(void**)(self + 0xc);
        float q = *(float*)(a + 0x10);
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d445, &q);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d4c7, &q);
    }
    if (flags & 2) {
        cam = *(void**)(self + 0xc);
        float q[4];
        q[0] = *(float*)(a + 0x18);
        q[1] = *(float*)(a + 0x1c);
        q[2] = *(float*)(a + 0x20);
        q[3] = *(float*)(a + 0x24);
        if (flags & 0x10)
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d51f, q);
        else
            ((void(__thiscall*)(void*, int, void*))VFN(cam, 4))(cam, 0x101d576, q);
    }
}

// @ 0x006eb8c0
RenderEntity::RenderEntity(const RenderEntity& src)
: mBase(src.mBase), mF4(src.mF4), mF8(src.mF8), mFC(src.mFC), mF10(src.mF10),
      mF14(src.mF14), mW18(src.mW18), mW1A(src.mW1A), mG1C(src.mG1C), mG20(src.mG20),
      mG24(src.mG24), mG28(src.mG28), mMat(src.mMat), mA(src.mA), mB(src.mB),
      mI0(src.mI0), mI1(src.mI1), mI2(src.mI2), mExtra(src.mExtra), mI3(src.mI3) {}

// @ 0x006eb990
void __stdcall f990(char* p1, char* p2)
{
    for (; p1 < p2; p1 += 0x70) {
        void* r = *(void**)(p1 + 0x28);
        if (r != 0) {
            int v = (*(volatile int*)((char*)r + 4) += -1);
            if (v == 0) {
                *(int*)((char*)r + 4) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(void*, int))VFN(r, 0))(r, 1);
            }
        }
    }
}

// @ 0x006eb9d0
void f9d0(uint* p1, uint* p2, int extra)
{
    int n = (int)p2 - (int)p1 >> 3;
    if (n > 1) {
        uint* e = p2 - 2;
        do {
            uint a = e[0], b = e[1];
            e[0] = p1[0];
            e[1] = p1[1];
            f_ac2060(p1, 0, n - 1, 0, a, b, extra);
            e -= 2;
            n = (8 - (int)p1) + (int)e >> 3;
        } while (n > 1);
    }
}

// @ 0x006ebb80
S7* S7::m6ebb80(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(uint*)d = *(uint*)s;
    memcpy(d + 8, s + 8, 32);
    ((E7*)(d + 0x28))->GetImageResource(*(void**)(s + 0x28));
    ((E7*)(d + 0x2c))->GetImageResource(*(void**)(s + 0x2c));
    *(uint*)(d + 0x3c) = *(uint*)(s + 0x3c);
    *(uint*)(d + 0x40) = *(uint*)(s + 0x40);
    *(uint*)(d + 0x44) = *(uint*)(s + 0x44);
    *(uint*)(d + 0x30) = *(uint*)(s + 0x30);
    *(uint*)(d + 0x34) = *(uint*)(s + 0x34);
    *(uint*)(d + 0x38) = *(uint*)(s + 0x38);
    *(uchar*)(d + 0x48) = *(uchar*)(s + 0x48);
    *(uchar*)(d + 0x49) = *(uchar*)(s + 0x49);
    *(uint*)(d + 0x4c) = *(uint*)(s + 0x4c);
    *(uint*)(d + 0x50) = *(uint*)(s + 0x50);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(float*)(d + 0x58) = *(float*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(uint*)(d + 0x60) = *(uint*)(s + 0x60);
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
    *(uint*)(d + 0x68) = *(uint*)(s + 0x68);
    void* n = *(void**)(s + 0x6c);
    _ReadWriteBarrier();
    void* o = *(void**)(d + 0x6c);
    if (n != o) {
        if (n)
            ((void(__thiscall*)(void*))VFN(n, 4))(n);
        *(void**)(d + 0x6c) = n;
        if (o)
            ((void(__thiscall*)(void*))VFN(o, 8))(o);
    }
    return this;
}

// @ 0x006ebe50
void fbe50(uint* p1, uint* p2, uint v)
{
    while (1) {
        while (*p1 > v)
            p1 += 2;
        p2 -= 2;
        while (*p2 < v)
            p2 -= 2;
        if (p2 <= p1)
            break;
        uint a = p1[0], b = p1[1];
        p1[0] = p2[0];
        p1[1] = p2[1];
        p2[0] = a;
        p2[1] = b;
        p1 += 2;
    }
}

// @ 0x006ebea0
void fbea0(uint* p1, uint* p2, uint* p3, int p4)
{
    f_ac3fa0(p1, p2, p4);
    for (uint* it = p2; it < p3; it += 2) {
        uint a = *it;
        if (*p1 < a) {
            uint b = it[1];
            *it = *p1;
            it[1] = p1[1];
            f_ac2060(p1, 0, ((int)p2 - (int)p1) >> 3, 0, a, b, p4);
        }
    }
    f9d0(p1, p2, p4);
}

// @ 0x006ebf50
S7* S7::mebf50()
{
    char* p = (char*)this;
    float C = g1533c74;
    *(void**)p = (void*)0x140afd4;
    *(int*)(p + 4) = 0;
    char* q = p + 0x20;
    *(void**)(p + 0x18) = q;
    *(void**)(p + 0xc) = q;
    *(void**)(p + 8) = q;
    *(void**)(p + 0x10) = p + 0x50;
    *(Vec3*)(p + 0x50) = MakeV3(C);
    *(Vec3*)(p + 0x5c) = MakeV3(-C);
    *(float*)(p + 0x68) = 0.0f;
    *(int*)(p + 0x6c) = 0;
    char* q2 = p + 0x88;
    *(void**)(p + 0x80) = q2;
    *(void**)(p + 0x74) = q2;
    *(void**)(p + 0x70) = q2;
    *(void**)(p + 0x78) = p + 0x98;
    return this;
}

// @ 0x006ec000
FxEntity::~FxEntity()
{}

// @ 0x006ec090
void S7::mec090()
{
    char* p = (char*)this;
    int i = *(int*)(p + 4);
    if ((int)((*(int*)(p + 0xc) - i) & 0xfffffffe) > 2 && i != 0 && i != *(int*)(p + 0x14))
        f_f47380((void*)i);
}

// @ 0x006ec0c0
void S8::m0c0(int a, int b, int c, int d, int e, void* f)
{
    // 253-byte skill/effect resource installer; body omitted (partial).
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
}

// @ 0x006ec260
void VecC::DoInsert(int* pos, int* v)
{
    int* end = e;
    if (end != cap) {
        if (pos <= v && v < end)
            v += 3;
        if (end) {
            end[0] = end[-3];
            end[1] = end[-2];
            end[2] = end[-1];
        }
        int* d = e;
        int* s = e;
        while (s - 3 != pos) {
            d[-3] = s[-6];
            d[-2] = s[-5];
            d[-1] = s[-4];
            d -= 3;
            s -= 3;
        }
        pos[0] = v[0];
        pos[1] = v[1];
        pos[2] = v[2];
        e = e + 3;
        return;
    }
    int n = ((int)end - (int)b) / 0xc;
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    int* dst = (int*)malloc(n * 0xc);
    memcpy(dst, b, (int)pos - (int)b);
    int* mid = dst + ((int)pos - (int)b) / 4;
    if (mid) {
        mid[0] = v[0];
        mid[1] = v[1];
        mid[2] = v[2];
    }
    memcpy(mid + 3, pos, (int)end - (int)pos);
    if (b != 0)
        free(b);
    int* ne = (int*)((char*)mid + 0xc + ((int)end - (int)pos));
    b = dst;
    e = ne;
    cap = (int*)((char*)dst + n * 0xc);
}

// @ 0x006ec4a0
void S8::m4a0()
{ }

// @ 0x006ec5b0
void f5b0(uint* p1, int p2, int p3, int p4)
{
    uint d = p2 - (int)p1;
    while ((int)(d & 0xfffffff8) > 0xe0 && p3 > 0) {
        uint a = *p1;
        int i = (p2 - (int)p1) >> 3;
        i = (i - (i >> 0x1f)) >> 1;
        uint x = p1[i * 2];
        uint y = x;
        uint* m = p1 + i * 2;
        uint* p = p1;
        if (x < a) { y = a; m = p1; p = p1 + i * 2; a = x; }
        if (a <= *(uint*)(p2 - 8) && *(uint*)(p2 - 8) < y)
            p = (uint*)(p2 - 8);
        int r = f_6ebe50(p1, p2, *p, p[1], p4);
        p3--;
        f5b0((uint*)r, p2, p3, p4);
        d = r - (int)p1;
        p2 = r;
    }
    if (p3 == 0)
        f_ac3fa0_s006e_c0c0(p1, (uint*)p2, p4);
}

// @ 0x006ec660
void S8::m660(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    char* q = d + 0x14;
    *(void**)(d + 0x10) = q;
    *(void**)(d + 4) = q;
    *(void**)d = q;
    *(void**)(d + 8) = d + 0x94;
    *(ushort*)q = 0;
    ((SmallStrObj*)d)->FUN_006ebd20(*(int*)s, *((int*)s + 1));
}

// @ 0x006ec6d0
int __cdecl f6d0(int p1, int p2, int p3)
{
    if (p1 != p2) {
        do {
            int i = *(int*)(p1 + 4);
            if ((int)((*(int*)(p1 + 0xc) - i) & 0xfffffffe) > 2 && i != 0 &&
                i != *(int*)(p1 + 0x14))
                f_f47380_s006e_c0c0((void*)i);
            p1 += 0xc0;
            p3 += 0xc0;
        } while (p1 != p2);
    }
    return p3;
}

// @ 0x006ec730
S8* S8::m730()
{
    char* p = (char*)this;
    *(uchar*)p = 0;
    char* q = p + 0x18;
    *(void**)(p + 0x14) = q;
    *(void**)(p + 8) = q;
    *(void**)(p + 4) = q;
    *(void**)(p + 0xc) = p + 0x98;
    *(ushort*)q = 0;
    *(int*)(p + 0x98) = 0;
    *(int*)(p + 0x9c) = 0;
    *(float*)(p + 0xa8) = 12.0f;
    *(int*)(p + 0xa0) = -1;
    *(int*)(p + 0xa4) = -1;
    float one = 1.0f;
    *(float*)(p + 0xac) = one;
    *(float*)(p + 0xb0) = one;
    *(float*)(p + 0xb4) = one;
    *(float*)(p + 0xb8) = one;
    *(float*)(p + 0xbc) = one;
    return this;
}

// @ 0x006ec840
void S8::m840(int a, int b)
{
    char* self = (char*)this;
    // eastl::vector<AutoRefCount<...>>::erase + release tail; approximate
    int* end = *(int**)(self + 4);
    int* it = end;
    for (; it < end; it++) { }
    (void)a; (void)b;
}

// @ 0x006ec8a0
void S8::m8a0()
{ }

// @ 0x006eca50
void __stdcall fca50(char* p1, char* p2)
{
    for (; p1 < p2; p1 += 0xc0) {
        int i = *(int*)(p1 + 4);
        if (((2 < (int)(*(int*)(p1 + 0xc) - i & 0xfffffffeU)) && (i != 0)) &&
            (i != *(int*)(p1 + 0x14)))
            f_f47380_s006e_c0c0((void*)i);
    }
}

// @ 0x006ecaa0
void S8::maa0()
{ }

// @ 0x006ecb40
void S8::mb40()
{ }

// @ 0x006ecdd0
void S8::mdd0(int a, int b)
{
    int loc[3];
    loc[0] = a; loc[1] = b; loc[2] = 0;
    VecC* v = (VecC*)((char*)this + 8);
    int* p = v->e;
    if (p < v->cap) {
        v->e = p + 3;
        if (p != 0) {
            p[0] = loc[0];
            p[1] = loc[1];
            p[2] = loc[2];
        }
        return;   // the shipped p==0 path still returns without growing
    }
    v->DoInsert(p, loc);
}

// @ 0x006ece30
void S8::me30(int a, int b, int c)
{
    int loc[3];
    loc[0] = a; loc[1] = b; loc[2] = c;
    VecC* v = (VecC*)((char*)this + 8);
    int* p = v->e;
    if (p < v->cap) {
        v->e = p + 3;
        if (p != 0) {
            p[0] = loc[0];
            p[1] = loc[1];
            p[2] = loc[2];
        }
        return;   // the shipped p==0 path still returns without growing
    }
    v->DoInsert(p, loc);
}

// @ 0x006ece90
void S8::me90(int n, int* a, int* b)
{
    char* self = (char*)this;
    while (n != 0) {
        int loc[3];
        loc[1] = *b;
        int* p = *(int**)(self + 0xc);
        loc[0] = *a;
        loc[2] = 0;
        n--;
        if (p < *(int**)(self + 0x10)) {
            *(int**)(self + 0xc) = p + 3;
            if (p != 0) {
                p[0] = loc[0]; p[1] = loc[1]; p[2] = 0;
            }
        } else {
            ((VecC*)(self + 8))->DoInsert(p, loc);
        }
        b++;
        a++;
    }
}

// @ 0x006ecf10
void S8::mf10()
{
    char* self = (char*)this;
    for (int i = 0; i < 0x28; i += 4) {
        int r = f_7c3af0(*(int*)(i + 0x1533cd0));
        VecC* v = (VecC*)(self + 0x30d54);
        int* p = v->e;
        if (p < v->cap) {
            v->e = p + 1;
            if (p)
                *p = r;
        } else {
            int loc = r;
            f_grow4(v, &loc);
        }
    }
    for (int i = 0; i < 0x28; i += 4) {
        int r = f_7c3af0(*(int*)(i + 0x1533ca8));
        VecC* v = (VecC*)(self + 0x30d68);
        int* p = v->e;
        if (p < v->cap) {
            v->e = p + 1;
            if (p)
                *p = r;
        } else {
            int loc = r;
            f_grow4(v, &loc);
        }
    }
}

// @ 0x006ecfc0
S8* S8::mfc0(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(uchar*)d = *(uchar*)s;
    if (d + 4 != s + 4) {
        int* d4 = *(int**)(d + 4);
        int* d8 = *(int**)(d + 8);
        if (d4 != d8) {
            *(ushort*)d4 = 0;
            *(int**)(d + 8) = d4;
        }
        ((SmallStrObj*)(d + 4))->FUN_006ebd20(*(int*)(s + 4), *(int*)(s + 8));
    }
    *(float*)(d + 0x98) = *(float*)(s + 0x98);
    *(float*)(d + 0x9c) = *(float*)(s + 0x9c);
    *(uint*)(d + 0xa0) = *(uint*)(s + 0xa0);
    *(uint*)(d + 0xa4) = *(uint*)(s + 0xa4);
    *(float*)(d + 0xa8) = *(float*)(s + 0xa8);
    *(float*)(d + 0xac) = *(float*)(s + 0xac);
    *(uint*)(d + 0xb0) = *(uint*)(s + 0xb0);
    *(uint*)(d + 0xb4) = *(uint*)(s + 0xb4);
    *(uint*)(d + 0xb8) = *(uint*)(s + 0xb8);
    *(uint*)(d + 0xbc) = *(uint*)(s + 0xbc);
    return this;
}

// @ 0x006ed070
void S8::md070()
{ }

// @ 0x006ed1a0
void S8::md1a0(int idx, char v)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70)
        return;
    int off = idx * 0x70;
    char* p = (char*)(*(int*)(self + 0x48) + 0x48 + off);
    if (*p != v) {
        *p = v;
        if (v != 0 && *(char*)(*(int*)(self + 0x48) + 0x49 + off) == 0) {
            int t = idx & 0xffff;
            ((VecU16_s006e_c0c0*)(self + 0x5c))->FUN_006f66a0((const ushort*)&t);
            *(char*)(*(int*)(self + 0x48) + 0x49 + off) = 1;
        }
    }
}

// @ 0x006ed210
void S8::md210(int idx)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x178) - *(int*)(self + 0x174)) / 0x70)
        return;
    int off = idx * 0x70;
    char* e = (char*)(*(int*)(self + 0x174) + off);
    if (*(int*)e == 0)
        return;
    int v = *(int*)(e + 0x64);   // read before the clears, like the emitted code
    *(int*)e = 0;
    *(uchar*)(e + 0x48) = 0;
    if (v != 0) {
        void* h = *(void**)(self + 0x1e0);
        if (h)
            ((void(__thiscall*)(void*, int))VFN(h, 0x20))(h, v);
        *(int*)(e + 0x64) = 0;
    }
    VecU32_s006e_c0c0* vv = (VecU32_s006e_c0c0*)(self + 0x19c);
    int* p = vv->e;
    if (p < vv->cap) {
        vv->e = p + 1;
        if (p)
            *p = idx;
        return;   // the shipped p==0 path still returns without growing
    }
    int loc = idx;
    vv->DoInsertValue(p, &loc);
}

// @ 0x006ed2c0
void cEffectsRenderer::SetTextureParticleActive(int index, bool active)
{
    if (index < 0 || index >= (int)mTextureParticleSets.size())
        return;
    cTextureParticleSet& p = mTextureParticleSets[index];
    if (p.mActive == active)
        return;
    p.mActive = active;
    if (!active)
        return;
    if (p.mInActiveList)
        return;
    mActiveTextureParticleSets.push_back((unsigned short)index);
    p.mInActiveList = 1;
}

// @ 0x006ed340
void cEffectsRenderer::RemoveParticleSet(int index)
{
    if (index >= 0 && index < (mModelEnd - mModelBegin)) {
        cModelParticleSet* p = mModelBegin + index;
        if (p->mpField60 != 0) {
            ((TFv_i)VTSLOT(p->mpField60, 0x0c))(p->mpField60, p->mField64);
            if (p->mpField60 != 0) {
                IRefCounted* q = p->mpField60;
                p->mpField60 = 0;
                ((TFv_v)VTSLOT(q, 0x04))(q);
            }
            p->mField64 = -1;
            unsigned* e = mFreeIDs.mpEnd;
            if (e < mFreeIDs.mpCapacity) {
                mFreeIDs.mpEnd = e + 1;
                if (e) *e = (unsigned)index;
            } else {
                mFreeIDs.DoInsertValue(e, (unsigned&)index);
            }
        } else {
            void* r = p->mpRef0;
            if (r != 0) {
                p->mpRef0 = 0;
                int* rc = (int*)((char*)r + 4);
                int n = *rc + (-1);
                *rc = n;
                if (n == 0) {
                    *rc = 1;
                    ((TFv_i)VTSLOT(r, 0x00))(r, 1);
                }
                p->mActive = false;
                if (p->mpField5c != 0) {
                    if (mSys1e0 != 0)
                        ((TFv_p)VTSLOT(mSys1e0, 0x20))(mSys1e0, p->mpField5c);
                    p->mpField5c = 0;
                }
                mFreeIDs.push_back((unsigned&)index);
            }
        }
    }
}

// @ 0x006ed440
int cEffectsKeyedList::ActivateByKey(unsigned a, unsigned b)
{
    if (mpObj0c != 0 && (a & b) != 0xffffffffu) {
        if (mIds.mpBegin == mIds.mpEnd) {
            unsigned id = ((TFu_v)VTSLOT(mpObj0c, 0x58))(mpObj0c);
            mIds.push_back(id);
        }
        ((TFv_u)VTSLOT(mpObj0c, 0x34))(mpObj0c, (a | b) ? a : 0u);
        unsigned idx = (unsigned)(mIds.mpEnd - mIds.mpBegin);
        mIds.push_back(a);
        return (int)idx;
    }
    return -1;
}

// @ 0x006ed8d0
cEffectsModel::cEffectsModel(unsigned a, unsigned b, unsigned c, const float* box)
{
    mField4 = 0;
    mpVtable = (void*)0x140afd4;
    DispatchData* dinl = (DispatchData*)((char*)this + 0x20);
    mDispatchInlinePtr = dinl;
    mDispatchData.mpEnd = dinl;
    mDispatchData.mpBegin = dinl;
    mDispatchData.mpCapacity = dinl + 4;
    const float f = 3.402823466e38f;
    mBoxMin = Vector3(f, f, f);
    mBoxMax = Vector3(-f, -f, -f);
    mAsyncRequest.mpObject = 0;
    AutoRefCount<IRefCounted>* rinl = (AutoRefCount<IRefCounted>*)((char*)this + 0x88);
    mResInlinePtr = rinl;
    mResourceRefs.mpEnd = rinl;
    mResourceRefs.mpBegin = rinl;
    mResourceRefs.mpCapacity = rinl + 4;
    me90(a, b, c);
    mBoxMin = Vector3(box[0], box[1], box[2]);
    mBoxMax = Vector3(box[3], box[4], box[5]);
    ComputeRadius();
}

// @ 0x006edaa0
void cEffectsModel::AddResourceRef(IRefCounted* p)
{
    AutoRefCount<IRefCounted> ref(p);
    mResourceRefs.push_back(ref);
}

// @ 0x006edb10
void cEffectsModel::Reset()
{
    const float f = 3.402823466e38f;
    Vector3 v(f, f, f);
    mBoxMin = v;
    mBoxMax = -v;
    mBoundingRadius = 0.0f;
    mAsyncRequest.Release();
    mDispatchData.erase(mDispatchData.mpBegin, mDispatchData.mpEnd);
    mResourceRefs.erase(mResourceRefs.mpBegin, mResourceRefs.mpEnd);
}

// @ 0x006ee140
char cEffectsModel::Update()
{
    IRefCounted* req = mAsyncRequest.mpObject;
    if (req != 0) {
        if (((TFc_v)VTSLOT(req, 0x10))(req)) {
            AutoRefCount<IRefCounted> local;
            if (((TFc_p)VTSLOT(mAsyncRequest.mpObject, 0x14))(mAsyncRequest.mpObject, &local.mpObject))
                UpdateFromResource((int*)local.mpObject);
            mAsyncRequest.Release();
            return 1;
        }
    }
    return 0;
}

// @ 0x006ee1f0
cEffectsRenderer_s006e_e1f0::cEffectsRenderer_s006e_e1f0()
{
    // First vtable pass (bases laid out in derived order, pre-icons).
    vptr04 = (void*)0x144934c;
    vptr08 = (void*)0x140af70;
    f10    = 0;
    vptr0c = (void*)0x13ef094;
    vptr14 = (void*)0x13eb384;
    vptr18 = (void*)0x13f1ab0;
    vptr1c = (void*)0x140af90;
    f20 = f24 = f28 = f2c = f30 = f34 = 0;

    // Second (final) vtable pass.
    vptr00 = (void*)0x140b1f0;
    vptr04 = (void*)0x140b1e0;
    vptr08 = (void*)0x140b1d8;
    vptr0c = (void*)0x140b1d4;
    vptr14 = (void*)0x140b1c4;
    vptr18 = (void*)0x140b1b4;
    vptr1c = (void*)0x140b190;

    p40 = 0;
    f44 = 0;
    f48 = 0;
    f4c = 0;
    f50 = 0;
    f54 = 0;
    f58 = 0;
    p5c = 0;
    f60 = 0;
    f64 = 0;
    p70 = 0;
    f74 = 0;
    f78 = 0;

    // EH vector at +0x104: 4 elements of 0x14 bytes.
    _eh_vector_ctor(mVec104, 0x14, 4, (void(__stdcall*)(void*))0x6e5790,
                    (void(__stdcall*)(void*))0x7a41a0);

    pad154_0 = 0;
    b158 = 0;
    b159 = 1;
    n15c = 3000;
    n160 = 10;
    n164 = 0;
    n168 = -1;
    p16c = (void*)0x140af78;
    f170 = f174 = f178 = f17c = 0;
    f188 = f18c = f190 = 0;
    f19c = f1a0 = f1a4 = 0;
    f1b0 = f1b4 = f1b8 = f1bc = f1c0 = 0;
    f1cc = f1d0 = f1d4 = 0;
    p1e0 = 0;
    b1e4 = 0;
    b1e5 = 0;
    f1e8 = 0.0f;
    f1ec = 0.0f;
    f1f0 = 0.0f;
    b1f4 = 0;
    f1f8 = f1fc = f200 = 0;

    mText = cTextRenderer();

    p224 = 0;
    f228 = 0;
    f22c = 0;
    mVec238.mpBegin = 0;
    mVec238.mpEnd = 0;
    mVec238.mpCapacity = 0;

    f350 = 0.5f;
    f24c = f250 = f254 = f258 = f25c = 0;
    f354 = 200.0f;

    p35c = 0;
    p360 = 0;
    p364 = 0;
    b368 = 0;
    b369 = 0;
    f36c = f370 = f374 = f378 = f37c = f380 = f384 = 0;
}

// @ 0x006ee4f0
cEffectsRenderer_s006e_e1f0::~cEffectsRenderer_s006e_e1f0()
{
    // First vtable pass (destruction order).
    vptr00 = (void*)0x140b1f0;
    vptr04 = (void*)0x140b1e0;
    vptr08 = (void*)0x140b1d8;
    vptr0c = (void*)0x140b1d4;
    vptr14 = (void*)0x140b1c4;
    vptr18 = (void*)0x140b1b4;
    vptr1c = (void*)0x140b190;

    if (p364) p364->Release();                 // weak release? (vtable+8)
    if (p360) p360->Release();

    if (mVec238.mpBegin && *(uint32_t*)((char*)mVec238.mpBegin - 4) != 0)
        operator_delete(mVec238.mpBegin);

    FUN_006eca50((void*)f228, p224);
    if (p224 && *(uint32_t*)((char*)p224 - 4) != 0)
        operator_delete(p224);

    FUN_007a8790();                            // ~cTextRenderer on &mText (this=ecx)

    if (p1e0) p1e0->Release();                 // vtable+4

    if (f1cc && *(uint32_t*)(f1cc - 4) != 0)
        operator_delete((void*)f1cc);

    FUN_006ebcb0(&f1b8);
    if (f19c && *(uint32_t*)(f19c - 4) != 0)
        operator_delete((void*)f19c);
    if (f188 && *(uint32_t*)(f188 - 4) != 0)
        operator_delete((void*)f188);

    FUN_006ebc50(&f174);

    _eh_vector_dtor(mVec104, 0x14, 4, (void(__stdcall*)(void*))0x7a41a0);

    if (p70 && *(uint32_t*)((char*)p70 - 4) != 0)
        operator_delete(p70);
    if (p5c && *(uint32_t*)((char*)p5c - 4) != 0)
        operator_delete(p5c);

    FUN_006ec1f0(&f48);

    if (p40) p40->Release();                   // vtable+4

    FUN_006e9990(&vptr1c);

    // Final vtable re-base to most-derived bases.
    vptr18 = (void*)0x13eb938;
    vptr14 = (void*)0x13eb394;
    vptr0c = (void*)0x13ef094;
}

// @ 0x006ee940
void cEffectsRenderer_s006e_e1f0::AddActive(unsigned int id)
{
    // temp 0xa0-byte scratch built at [esp+8], then released.
    uint8_t scratch[0xa0];
    FUN_006ec730(scratch);
    FUN_006ecfc0(scratch, &id);                 // scratch.assign(ptr id)

    // destroy scratch phases (mirrors the EH cleanup in the original)
    uint32_t* end = *(uint32_t**)(scratch + 0x10);
    uint32_t* begin = *(uint32_t**)(scratch + 0x08);
    int diff = (int)((char*)end - (char*)begin) & 0xfffffffe;
    if (diff > 2 && begin != 0 && begin != *(uint32_t**)(scratch + 0x18))
        operator_delete(begin);

    // append id (duplicates allowed) to the +0x238 vector.
    if (mVec238.mpEnd < (unsigned int*)mVec238.mpCapacity) {
        unsigned int* slot = mVec238.mpEnd;
        mVec238.mpEnd = slot + 1;
        if (slot)
            *slot = id;
    } else {
        mVec238.DoInsertValue(mVec238.mpEnd, id);
    }
}

// @ 0x006eea80
void vbvec::resize(unsigned int n)
{
    unsigned short* cur = mpEnd;
    unsigned int sz = (unsigned int)((char*)cur - (char*)mpBegin) >> 1;
    if (n > sz) {
        unsigned int extra = n - sz;
        unsigned short zero = 0;
        FUN_006ecb40(cur, extra, &zero);
        return;
    }
    // Shrink: the original memmoves zero bytes at the cut point (a no-op for
    // the 2-byte element) and then re-links the end pointer.
    unsigned short* dst = mpBegin + n;
    memcpy(dst, cur, 0);
    unsigned int removed = (unsigned int)((char*)cur - (char*)dst) >> 1;
    mpEnd = cur - removed;
}

// @ 0x006eeb60
void Vector70::insert(Elem70* pos, const Elem70* val)
{
    if (mpEnd != mpCapacity) {
        Elem70* slot = pos;
        if (pos < val || pos >= mpEnd)
            slot = pos + 1;                    // encoded as +0x70 bytes

        Elem70* last = mpEnd;
        // copy-construct the tail element, then move the range up by one.
        if (last != 0)
            FUN_006e9230(last - 1, (const Elem70*)(last - 1));   // ctor last from last
        FUN_006ebf10((Elem70*)val, last - 1, last);
        FUN_006ebb80(slot, val);
        mpEnd = (Elem70*)((char*)mpEnd + 0x70);
        return;
    }

    // --- reallocate: new capacity = 2 * size (or 1) ---
    unsigned int count = (unsigned int)((char*)mpEnd - (char*)mpBegin) / 0x70;
    unsigned int cap = count ? count * 2 : 1;

    Elem70* raw;
    if (cap != 0)
        raw = (Elem70*)operator_new_graphics(cap * 0x70, "Graphics", 0, 0,
                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                 0xd1);
    else
        raw = 0;

    Elem70* first = FUN_006e93d0(mpBegin, pos, raw);
    FUN_006eba30(mpBegin, pos, raw);
    Elem70* mid = first;
    if (mid != 0)
        FUN_006e9230(mid, val);

    Elem70* tail = (Elem70*)FUN_006e93d0(pos, mpEnd, mid + 1);
    FUN_006eba30(pos, mpEnd, mid + 1);

    if (mpBegin && *(uint32_t*)((char*)mpBegin - 4) != 0)
        operator_delete(mpBegin);

    mpCapacity = (Elem70*)((char*)raw + cap * 0x70);
    mpBegin = raw;
    mpEnd = tail;
}

// @ 0x006ef990
void Release(cEffectsModelR* self)
{
    Dispatch3* it = self->mpBegin;
    Dispatch3* end = self->mpEnd;
    for (; it != end; ++it)
        FUN_00762a60(it->p0);
    self->Reset();
    int n = self->mnRefCount - 1;
    self->mnRefCount = self->mnRefCount - 1;
    if (n == 0) {
        self->mnRefCount = 1;
        _ReadWriteBarrier();
        ((void (__thiscall*)(void*, int))self->mpVtable[0])(self, 1);
    }
}

// @ 0x006ef9e0
bool cEffectsRendererSystem::Init()
{    GetImageResource(SetDeviceState());
    cEffectsModel2* m = (cEffectsModel2*)CreateTestModel();
    cEffectsModel2* old = mpModel;
    if (m != old) {
        if (m)
            m->mnRefCount++;
        mpModel = m;
        if (old) {
            int n = old->mnRefCount - 1;
            old->mnRefCount = old->mnRefCount - 1;
            if (n == 0) {
                old->mnRefCount = 1;
                _ReadWriteBarrier();
                ((void (__thiscall*)(void*, int))old->mpVtable[0])(old, 1);
            }
        }
    }
    mAt30d50 = FUN_007c3af0("T0FT4FT4FT4FT4B");
    mAt30d80 = FUN_00762b70(mAt30d50, 0x9c4, 9, 0);
    mAt30d7c = CreateMesh(3);
    ((MeshStub*)mAt30d7c)->FUN96e0(0);
    ((MeshStub*)mAt30d7c)->FUN9670(1, mAt30d80);
    FUNecf10(1);
    mAt30d84 = 0;
    return true;
}

// @ 0x006efa90
char cEffectsRendererSystem::Shutdown()
{
    return 1;
}

// @ 0x006efb90
void CreateEffectsRendererSystem()
{
}

// @ 0x006efc10
void DestroyEffectsRendererSystem()
{
    g_pEffectsRendererSystem->Shutdown();
    cERSDtor* p = g_pEffectsRendererSystem;
    if (p) {
        p->~cERSDtor();
        EASTL_allocator_deallocate(p);
    }
    g_pEffectsRendererSystem = 0;
}

// @ 0x006efc70
void RenderSomething(int)
{
}

// @ 0x006efe90
void RenderTextureParticlesStub()
{
}

// @ 0x006f0320
void EffectsHelper320(int)
{
}

// @ 0x006f05a0
void EffectsHelper5a0(int)
{
}

// @ 0x006f0890
bool Effects890::Shutdown()
{
    IMessageServer* ms = MessageServer();
    ms->RemoveListener(this ? (void*)handler : 0, 0x6694879, (int)0xffffd8f1);
    m1b0 = 0;
    m1b4 = 0;
    if (m369) {
        IFlagSink* s = GetFlagSink();
        s->SetFlag(0x12);
        s->SetFlag(3);
        s->SetFlag(0x20);
        s->SetFlag(0x16);
    }
    m20 = 0;
    if (m28) {
        IObj3* t = m28;
        m28 = 0;
        t->Release3();
    }
    mText.Release();

    // clear four 8-byte-element vectors
    V8* v = mDrawLists;
    for (int i = 4; i != 0; --i, ++v)
        v->Erase(v->mpBegin, v->mpEnd);

    mSets.Erase(mSets.mpBegin, mSets.mpEnd);
    mAct.Erase(mAct.mpBegin, mAct.mpEnd);
    mV174.Erase(mV174.mpBegin, mV174.mpEnd);
    mFree.Erase(mFree.mpBegin, mFree.mpEnd);

    if (mViewer) {
        mViewer->Teardown();
        if (mViewer) {
            Viewer24* t = mViewer;
            mViewer = 0;
            t->sub.Release3();
        }
    }
    if (m360) {
        m360->Flush();
        if (m360) {
            IObj5* t = m360;
            m360 = 0;
            t->Release2();
        }
    }
    if (m364) {
        m364->Flush();
        if (m364) {
            IObj5* t = m364;
            m364 = 0;
            t->Release2();
        }
    }
    if (m24c) {
        m24c->Cleanup();
        SubObj* t = m24c;
        if (t) {
            t->Dtor();
            EaDelete(t);
        }
    }
    if (m250) {
        m250->Cleanup();
        SubObj* t = m250;
        if (t) {
            t->Dtor();
            EaDelete(t);
        }
    }
    if (m254) {
        m254->Cleanup();
        SubObj* t = m254;
        if (t) {
            t->Dtor();
            EaDelete(t);
        }
    }
    if (m40) {
        IObj1* t = m40;
        m40 = 0;
        t->Release1();
    }
    return true;
}

// @ 0x006f0b90
void Effects0B90::Render(unsigned flags, Region** pr, int arg)
{
    if (m1e0)
        m1e0->SetView(*(int*)pr);
    GetStateSink()->SetTarget(m1e0);
    unsigned skip = flags & 0x10000;
    if (skip == 0) {
        g_samplerA |= 0x20;
        g_renderDirty |= 0x8000;
        g_samplerA |= 0x10;
        g_samplerA |= 0x40;
        g_samplerB |= 0x20;
        g_samplerB |= 0x10;
        g_samplerB |= 0x40;
        g_softStateDirty_s006f_0890 = (g_softStateDirty_s006f_0890 & 0xfff1ffff) | 0x10000;
        g_s0 = 2;
        g_s1 = 2;
        g_s2 = 2;
        g_s3 = 2;
        g_s4 = 2;
        g_s5 = 2;
        g_s6 = 2;
        g_fogType = 0;
        D3DCaps* caps = GetD3DCAPS9();
        if (caps->c4 <= 0xfffe0000 || caps->cc <= 0xffff0000) {
            g_renderDirty |= 0x200000;
            g_r250 = 0;
        }
        if (caps->c4 <= 0xfffe0000) {
            g_renderDirty2 |= 0x20;
            g_r410 = 0;
        }
        g_renderDirty |= 0x10080;
        g_b23c = 4;
        g_b218 = 1;
        SetBlendMode(0x60005);
        g_renderDirty |= 0x60100;
        g_b21c = 1;
        g_b244 = 5;
        g_b240 = 0;
    }
    m260.Set((char*)*(int*)pr + 0xc0);
    if (g_pProps) {
        // cl homes the out-pointer of this first Get in the live-range-dead `flags`
        // argument slot, so a Get that returns true without writing *out leaves flags there
        Prop* p = (Prop*)(unsigned)flags;
        if (g_pProps->Get(0x13d7382, &p) && p->type == 0xd) {
            float* f = (float*)p;
            if (p->flags & 0x30)
                f = *(float**)p;
            m260.SetA(*f);
        }
    }
    if (g_pProps) {
        Prop* p;
        if (g_pProps->Get(0x63b0756, &p) && p->type == 0xd) {
            float* f = (float*)p;
            if (p->flags & 0x30)
                f = *(float**)p;
            m260.SetA(*f);
        }
    }
    if (flags & 4)
        DispatchWithAdditionalMaterial(flags, pr, arg);
    if ((flags & 2) && m188 != m18c)
        Pass2(flags, pr, arg);
    if ((flags & 1) && m5c != m60) {
        if (skip == 0) {
            g_renderDirty |= 0x10080;
            g_b218 = 0;
            g_b23c = 2;
            SetBlendMode(0x60005);
            g_renderDirty |= 0x60100;
            g_b21c = 1;
            g_b244 = 5;
            g_b240 = 0;
        }
        unsigned hi = flags & 0x4000000;
        Region* use;
        Region tmp;
        if (hi || (flags & 0x2000000)) {
            float f = g_pProps->GetFloatProperty(0x637fee8);
            m250->Copy(*(int*)pr, 0, 0);
            if (hi)
                m250->SetA(m250->GetA() + f);
            else if (flags & 0x2000000)
                m250->SetB(m250->GetB() - f);
            Region* src = *pr;
            tmp.a = (int)m250;
            tmp.b = src->b;
            tmp.c = src->c;
            tmp.d = src->d;
            use = &tmp;
        } else
            use = (Region*)pr;
        RenderTextureParticles(flags, use, arg);
    }
    if (flags & 0x40)
        Pass40(flags, pr, arg);
    if (skip == 0) {
        g_renderDirty |= 0x10080;
        g_b218 = 1;
        g_b23c = 2;
        SetBlendMode(0x10002);
        g_renderDirty |= 0x40100;
        g_b21c = 0;
        g_b244 = 8;
    }
    if ((char)flags < 0 && m44->m110)
        Pass80(flags, pr, arg);
    if (skip == 0) {
        g_renderDirty |= 0x8000;
        g_s6 = 2;
    }
}

// @ 0x006f0fb0
bool Effects0FB0::AddParticleSet(int id, const SetDesc* d, int* outIndex)
{
    ImageRef img1;
    int mat1 = 0;
    ImageRef img2;
    int mat2 = 0;
    // inline: resource lookup
    if (d->kind == 0xf) {
        MatPair* p = m40->Find(d->lo, d->hi);
        if (p) {
            mat1 = p->a;
            mat2 = p->b;
        } else
            mat1 = MaterialManager()->Find(d->lo);
        if (mat1 == 0)
            return false;
        if ((d->lo2 & d->hi2) != -1) {
            if (d->lo2 == 0x7f000000 && d->hi2 == 0) {
                img1.Assign(*g_defaultImage);
            } else {
                img1.Assign(m40->GetImg(d->lo2, d->hi2));
                if (img1.p) {
                    unsigned hi = (unsigned)d->hi2;
                    if ((hi & 0xc0000000) == 0x40000000 && (hi & 0xff00) == 0x2800) {
                        hi = (hi & 0xffff2cff) | 0x2c00;
                        img1.Assign(ResourceManager()->Get(d->lo2, hi, 0));
                    }
                }
            }
        }
    } else {
        if (d->fl & 3)
            mat1 = mMat84[d->kind];
        else
            mat1 = mMatC4[d->kind];
        if ((d->lo & d->hi) != -1) {
            if (d->lo == 0x7f000000 && d->hi == 0)
                img1.Assign(*g_defaultImage);
            else
                img1.Assign(ResourceManager()->Get(d->lo, d->hi, 0));
        }
        if ((d->lo2 & d->hi2) != -1) {
            if (d->lo2 == 0x7f000000 && d->hi2 == 0)
                img2.Assign(*g_defaultImage);
            else
                img2.Assign(ResourceManager()->Get(d->lo2, d->hi2, 0));
        }
        if (mat1 == 0)
            return false;
        if (!m1e4 && img1.p == 0)
            return false;
    }

    if (mFreeBegin == mFreeEnd) {
        *outIndex = (int)(mSetsEnd - mSetsBegin);
        E70 tmp;
        PushSet(&mSetsBegin, &tmp);
    } else {
        *outIndex = mFreeEnd[-1];
        mFreeEnd -= 1;
    }
    E70* s = mSetsBegin + *outIndex;
    unsigned char keep = ((unsigned char*)s)[0x49];
    {
        E70 tmp;
        s->Assign(&tmp);
    }
    *(int*)s = id;
    for (int i = 0; i < 8; ++i)
        ((int*)s)[2 + i] = ((const int*)d)[i];
    ((ImageRef*)((char*)s + 0x28))->Assign(img1.p);
    ((ImageRef*)((char*)s + 0x2c))->Assign(img2.p);
    *(int*)((char*)s + 0x5c) = mat1;
    *(int*)((char*)s + 0x60) = mat2;
    ((unsigned char*)s)[0x49] = keep;
    return true;
}

// @ 0x006f13a0
void cEffectsRendererLayer::RenderMainEffectsLayer(unsigned flags, unsigned type, int a, int b)
{
    if (g_app->m3c->m0c == 0)
        return;
    if (mAt2c == 0)
        mAt2c = EffectsManager()->GetDefault();
    if (flags == 0 || (flags & 0x6000000) != 0)
        flags |= 0xff;
    unsigned t = type;
    mAt354 = b;
    switch (t) {
    case 3:
        if (flags & 0x28) {
            ((EffectsOuter*)((char*)this - 0x18))->RenderTex(flags, a, b);
            mAt354 = 0;
            return;
        }
        break;
    case 6:
    case 18:
    case 19:
    case 24:
    case 28:
        if (flags & 0x47) {
            ((EffectsOuter*)((char*)this - 0x18))->RenderMain(flags, a, b);
            mAt354 = 0;
            return;
        }
        break;
    case 22:
        if (mAt344 && (flags & 0x20))
            mAt344->Render(flags, type, a, b);
        if (mAt34c && (flags & 0x10) && !mAt34c->Ready())
            mAt34c->Render(flags, type, a, b);
        break;
    case 32:
        if (mAt34c && (flags & 0x10) && mAt34c->Ready())
            mAt34c->Render(flags, type, a, b);
        break;
    default:
        break;
    }
    mAt354 = 0;
}

// @ 0x006f1510
void EltVector::Insert(Elt* pos, const Elt* val)
{
    if (mpEnd != mpCapacity) {
        const Elt* v = val;
        if (v >= pos && v < mpEnd)
            ++v;
        Elt* e = mpEnd;
        if (e)
            new (e) Elt(e[-1]);
        EltCopyBackward(pos, mpEnd - 1, mpEnd);
        *pos = *v;
        ++mpEnd;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    int newCap = n ? n * 2 : 1;
    Elt* newMem = newCap ? (Elt*)EaNew(newCap * sizeof(Elt), "Graphics", 0, 0,
                                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                           : 0;
    Elt* newEnd = EltUninitCopy(mpBegin, pos, newMem);
    EltDestroyRange(mpBegin, pos, newMem);
    if (newEnd)
        new (newEnd) Elt(*val);
    Elt* e = mpEnd;
    Elt* tail = EltUninitCopy(pos, e, newEnd + 1);
    EltDestroyRange(pos, e, newEnd + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        EaDelete(mpBegin);
    mpCapacity = newMem + newCap;
    mpBegin = newMem;
    mpEnd = tail;
}

// @ 0x006f16c0
void EltVector::PushBack()
{
    if (mpEnd < mpCapacity) {
        Elt* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            new (p) Elt();
        return;
    }
    Elt tmp;
    Insert(mpEnd, &tmp);
}

// @ 0x006f1770
bool PSetOwner::AddParticleSet(wchar_t* name, int b, int c, float d, unsigned* out)
{
    int* begin = mFree.begin;
    if (mFree.end != begin)
    {
        *out = (unsigned)mFree.end[-1];
        mFree.end -= 1;
    }
    else
    {
        *out = (unsigned)(mVec.end - mVec.begin);
        mVec.PushBack();
    }
    PSetElem* e = &mVec.begin[*out];
    StrSlot* s = &e->mStr;
    if (s->mpBegin != name)
    {
        if (s->mpBegin != s->mpEnd)
        {
            s->mpBegin[0] = 0;
            s->mpEnd = s->mpBegin;
        }
        s->assign(name, name + WStrLen(name));
    }
    e->ma0 = b;
    e->ma4 = c;
    e->ma8 = d;
    return true;
}

// @ 0x006f1840
void __stdcall Forward1840(int a, int b)
{
    FUN_00a7bca0(a, b);
}

// @ 0x006f1860
bool EffectsRenderer_s006f_1770::ResourceInfoInit()
{
    mpManager = (ResMgr*)FUN_0067dcd0();
    mpField54 = FUN_0067dd60();
    mpMaterial = (MaterialVt*)FUN_0067dd70();
    if (!mpManager)
        return true;
    if (mpManager->GetSwarmType(0xea5118b0, -1))
        return true;

    SwarmObj* raw = (SwarmObj*)ZoneObjectNew(8, "Swarm", 0, 0, 0, 0);
    SwarmObj* p = raw ? raw->Init() : 0;
    SwarmGuard guard(p);
    mpManager->AddSwarm(1, guard.get(), 0);
    return true;
}

// @ 0x006f1950
int Owner1950::Call(int idx, int a, int b, int c)
{
    mArray[idx]->v1(a, b, c);
    return 1;
}

// @ 0x006f1a30
Node18* __stdcall Alloc18(Node18* src)
{
    Node18* p = (Node18*)EAAllocate(0x18, "Graphics", 0, 0, kAllocatorFile, 0xd1);
    Node18* q = p;
    if (q)
        new (q) Node18(*src);
    p->mpNext = 0;
    return p;
}

// @ 0x006f1b60
bool EffectsRenderer_s006f_1770::LookupAndUse(unsigned a, unsigned b, ResSub** out, unsigned index)
{
    ResKey3 key;
    key.instance = a;
    key.type = gTypeTable[index];
    key.group = b;

    ResGuard res;
    if (!mpManager->Lookup(&key, res.addr(), 0, 0, 0, 0))
        return false;
    *out = res.get() ? &res.get()->mSub : 0;
    (*out)->s2();
    return true;
}

// @ 0x006f1c40
bool EffectsRenderer_s006f_1770::CreateResource(unsigned a, unsigned b, Model98** out)
{
    ResKey3 key;
    key.instance = a;
    key.type = 0xe6bce5;
    key.group = b;

    RefGuard refA;
    RefGuard refB;
    if (!mpManager->Lookup2(&key, refB.addr(), refA.addr(), 0, 0, 0, 0, 0))
    {
        key.type = 0x2f4e681b;
        refA.reset();
        refB.reset();
        if (!mpManager->Lookup2(&key, refB.addr(), refA.addr(), 0, 0, 0, 0, 0))
            return false;
    }

    Model98* raw = (Model98*)EAAllocate(0x98, "Graphics", 0, 0, 0, 0);
    *out = raw ? raw->Init() : 0;
    if (refA.get())
    {
        FUN_006ac0a0(4, refA.get());
        (*out)->UpdateFromResource(refB.get());
    }
    else
    {
        (*out)->LoadFrom(refB.get());
    }
    return true;
}

// @ 0x006f2050
void* EffectsRenderer_s006f_1770::FindEntry(unsigned key, unsigned)
{
    HtTable* t = &mTable88;
    unsigned k = key;
    HtIter it = t->find(k);
    if (it.node != t->mBuckets[t->mBucketCount])
        return (char*)it.node + 4;
    return 0;
}

// @ 0x006f2310
bool EffectsRenderer_s006f_1770::InsertEntry(unsigned index, unsigned b, unsigned c, int* out)
{
    if ((b & c) == 0xffffffff)
        return false;
    ResSub* obj = 0;
    if (!LookupAndUse(b, c, &obj, index))
        return false;
    if (!obj)
        return false;

    if (mFreeVec.begin != mFreeVec.end)
    {
        int slot = mFreeVec.end[-1];
        mFreeVec.end -= 1;
        mObjVec.begin[slot] = obj;
        *out = slot;
        return true;
    }
    mObjVec.push_back(obj);
    *out = (int)(mObjVec.end - mObjVec.begin) - 1;
    return true;
}
