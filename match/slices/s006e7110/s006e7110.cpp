// slice s006e7110 -- render/dispatch + bounding-volume helper cluster.
// Flags: /O2 /MD /Gy /EHsc /TP (SSE scalar; some x87 float).
#include "types.h"
#include <string.h>

struct Inner7c {
    char F7(int, int, int, int, int, int, int);       // 0x0076bc50
    void F12(int, int, int, int, int, int, int, int, // 0x0076ba30
             int, int, int, int);
    void FF(float);                                   // 0x00776450
    void FI(int);                                     // 0x006f4280 / 0x0076cd30
    int  Fp(int, int);                                // 0x... vtable +0x10
    void Fq(int, int, float);                         // vtable +0x18/+0x1c
};

// Ref-counted object: vtable at +0x00, reference count at +0x04.
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

// Plain virtual object (vtable at +0x00).
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

// rw::graphics::EmbeddedState (members this slice touches).
struct EmbeddedState {
    uint8_t pad0[8];
    uint8_t flags;                                    // +0x08
    uint8_t pad9[7];
    void D3D9SetTransform(const void* m, int n);      // 0x011edc10
    void SetMaterialColor(const void* c);             // 0x011eda00
    void Dispatch();                                  // 0x011ee580
};

// One 12-byte dispatch record (0x006e7110 / 0x006e7270).
struct Record12 { uint32_t a, b, c; };

// SP::cTextRenderer (embedded at Host3 +0x204; calls go to the retail methods).
struct TextRenderer {
    uint8_t pad[0x20];
    void Init();                                    // 0x007a84d0
    void SetStyle(int);                             // 0x007a82a0
    void SetFontName(const wchar_t*);               // 0x007a8550
    void SetFontSize(float);                        // 0x007a85a0
    void SetColor(const void*);                     // 0x007a85e0
    void SetStyleScale(float);                      // 0x007a82d0
    void DrawString(float, float, uint32_t);        // 0x007a91b0
};

// Object at +0x00 of a 0xc0-stride element (0x006e78b0 / 0x006e79b0 records).
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

// Object passed to 0x006e7b50 (an effects renderable).
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

// Interface reached through Host3 +0x1e0 (vtable slots 0x18 / 0x1c).
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

// Object returned by 0x0067dd50; slot 0x1c yields a {width,height} pair.
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

// The renderer/effects host. Field names are the retail offsets.
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
    TextRenderer m204;   // +0x204 text renderer
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

// Vtable-dispatch shims for the opaque interfaces touched by 0x006e7450.
typedef void  (__thiscall* VFn0)(void*);                 // slot(...)
typedef void* (__thiscall* VFnR)(void*);                 // slot(...) -> ptr
typedef char  (__thiscall* VFnB)(void*, unsigned, void**); // property fetch
typedef void  (__thiscall* VFnS)(void*, void*, int, int);  // viewer setup
typedef void  (__thiscall* VFnM)(void*, int, int, void*);  // material create
typedef void  (__thiscall* VFnP)(void*, void*, unsigned);  // message register

extern "C" void* FUN_0067dd50();                 // 0x0067dd50
extern "C" void* FUN_0067dd40();                 // 0x0067dd40
extern "C" void* FUN_0067ddf0();                 // 0x0067ddf0
extern "C" void* FUN_0067dda0();                 // 0x0067dda0
extern "C" void* FUN_0067dd70();                 // 0x0067dd70
extern "C" void* FUN_0067dcc0();                 // 0x0067dcc0
extern "C" void* operator_new(unsigned int, const char*, int, int, int, int);
extern "C" int   rw_VertexDescriptor_AreEqual(int, int);
void __fastcall FUN_006e7270(void* self, int dummy, void* a, int arg);  // 0x006e7270
extern int* g_1618d10;

// --- renderer helpers used by the 8 rework targets ---
extern "C" void  FUN_00777bf0();                 // 0x00777bf0 pushShaderDataNull
extern "C" void  FUN_00777b50(void*);            // 0x00777b50 SP::SetShaderData
extern "C" void  FUN_00777ae0(int, int, int);    // 0x00777ae0 shader
extern "C" void  FUN_00777c10();                 // 0x00777c10 shader flush
extern "C" void  __fastcall FUN_007789d0(void*, int); // 0x007789d0 ShaderDataState_Push (thiscall)
extern "C" void  FUN_007611a0(int);              // 0x007611a0
extern "C" void  __fastcall FUN_011f9710(void*, int); // 0x011f9710 (thiscall)
extern "C" int   FUN_011f2e70(const void*, const void*); // 0x011f2e70 VertexDescriptor::AreEqual
extern "C" void  __fastcall FUN_011f2bc0(void*, int); // 0x011f2bc0 SetActiveVertexDescriptor (thiscall)
extern "C" void  FUN_011eda00(void*, const void*); // 0x011eda00 SetMaterialColor
extern "C" void  FUN_011edc10(void*, const void*, int); // 0x011edc10 D3D9SetTransform
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
extern "C" void  __fastcall FUN_007a84d0(void*, int);            // 0x007a84d0 cTextRenderer::Init

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

volatile int g_host3Sink;

extern const char g_matName7cc0[];

// ===========================================================================
// Bodies
// ===========================================================================

// @ 0x006e7110  SP::cEffectsModel::DispatchWithAdditionalMaterial
// Walks the 12-byte dispatch records and replays each state's shader setup.
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

// @ 0x006e7270  SP::cEffectsRenderer::RenderBoundingBoxes
// Same record walk as 006e7110, plus a second (bounding-box) shader pass.
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

// @ 0x006e7450  SP::cEffectsRenderer::Initialize
// Builds the renderer: reseats the +0x40 handle, reads two property
// descriptions, then wires the material manager, the three viewer slots and
// (per flags) the optional capture / RTT sub-objects.
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
// Per-element text refresh: for every enabled 0xc0-stride element, bind the
// text-renderer style/colour/scale and draw its string.
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
// Screen-space quad: projects the element through the current render target and
// writes its two screen corners, depth and per-instance data.
void Host3::Method79b0(int index, float f2, float f3, int a4, float f5,
                       int a6, int a7, int a8, int a9, float f10, float f11)
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
// Binds a renderable's shader state, pushes its shader data and flushes.
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
// Stores an element's two endpoints and weight, then refreshes its midpoint
// through the +0x1e0 interface.
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
// Releases the +0x60 sub-object and the ref-counted +0x00 object.
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
