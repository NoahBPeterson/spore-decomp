// Slice s006ba2f0: RenderWare/EA::Swarm math wrappers plus Spore alert/property helpers.
// Same module family: /O2 /MD /Gy /GS- /EHsc /TP /arch:SSE.
#include "types.h"

typedef unsigned int UINT;
typedef void* HWND;
typedef void* HANDLE;

extern "C" {
    __declspec(dllimport) int __stdcall MessageBoxA(HWND, const char*, const char*, UINT);
    __declspec(dllimport) int __stdcall MessageBoxW(HWND, const wchar_t*, const wchar_t*, UINT);
}
extern "C" int __cdecl sprintf(char*, const char*, ...);
void __cdecl EASTL_dealloc(void*);

// static empty strings
extern const char    g_emptyStrC[];   // 0x1667bac
extern const wchar_t g_emptyStrW[];   // 0x1667bae

// eastl::string stubs
struct EStrC {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mpAllocator;
    EStrC() : mpBegin((char*)g_emptyStrC), mpEnd((char*)g_emptyStrC), mpCapacity((char*)g_emptyStrC + 1) {}
    ~EStrC() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
struct EStrW {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void* mpAllocator;
    EStrW() : mpBegin((wchar_t*)g_emptyStrW), mpEnd((wchar_t*)g_emptyStrW), mpCapacity((wchar_t*)g_emptyStrW + 1) {}
    ~EStrW() { if (((char*)mpCapacity - (char*)mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
int __cdecl EStrC_sprintf(EStrC* s, const char* fmt, ...);
int __cdecl EStrW_format(EStrW* s, const wchar_t* fmt, ...);

// RenderWare math stub types
struct Matrix3 { float m[9]; void Assign(const void* src); };
struct cTransform {
    float tx, ty, tz;
    uint16_t flags;
    uint16_t modCount;
    float scale;
    Matrix3 rot;
};

// callees
void* __cdecl FUN_00453b20(Matrix3*, int, float);   // builds a Matrix3
void* __cdecl FUN_0069b1c0(void*, int, int);         // 0x69b1c0
void __cdecl FUN_006ba620(Matrix3*, const float*);  // transform apply
void __cdecl FUN_009322b0(const void*);             // path helper
int  __cdecl StrW_Insert(void*, const wchar_t*, const wchar_t*);   // 0x5f7da0
int  __cdecl FUN_006a17e0(int, int);
int  __cdecl FUN_006a1880(int, int, int);
int  __cdecl FUN_006a1910(int, int, float);
struct PropList {
    void Set(int, int);
    void SetInt(int, int);
    void SetFloat(int, float);
};
void __cdecl WStr_Format(EStrW*, const wchar_t*, ...);
extern PropList* g_appProperties;   // 0x15fd918
extern const wchar_t DAT_01409f64[];

// ---------------------------------------------------------------------------
// @ 0x006ba800
// ---------------------------------------------------------------------------
struct MatOwner {
    void SetA(int, float);
    void SetB(int, int);
    void SetMatrix(Matrix3*);
};
void MatOwner::SetA(int a, float b)
{
    Matrix3 tmp;
    void* r = FUN_00453b20(&tmp, a, b);
    Matrix3 m;
    m.Assign(r);
    SetMatrix(&m);
}
// @ 0x006ba840
void MatOwner::SetB(int a, int b)
{
    Matrix3 m;
    void* r = FUN_0069b1c0(&m, a, b);
    SetMatrix((Matrix3*)r);
}

// ---------------------------------------------------------------------------
// @ 0x006ba870  apply transform
// ---------------------------------------------------------------------------
struct XForm2 {
    uint16_t flags;
    uint16_t count;
    float    m4, m8, mc;
    float    m10;
    Matrix3  rot;   // 0x14
    void Apply(const float* other);
};
void XForm2::Apply(const float* other)
{
    if ((flags & 2) == 0) {
        for (int i = 0; i < 9; ++i) ((float*)&rot)[i] = other[i];
        flags |= 2;
    } else {
        FUN_006ba620(&rot, other);
    }
    float a = m4, b = m8, c = mc;
    float x0 = other[0], y0 = other[1], z0 = other[2];
    float x1 = other[4], y1 = other[5], z1 = other[6];
    float x2 = other[8], y2 = other[9], z2 = other[10];
    m4 = (x0 * a + x1 * b) + x2 * c;
    m8 = (y0 * a + y1 * b) + y2 * c;
    mc = (z0 * a + z1 * b) + z2 * c;
    count = (uint16_t)(count + 1);
}

// ---------------------------------------------------------------------------
// @ 0x006ba620  (referenced above)
// ---------------------------------------------------------------------------
void __cdecl FUN_006ba620(Matrix3* dst, const float* other)
{
    float r[9];
    for (int i = 0; i < 9; ++i) r[i] = dst->m[i];
    for (int i = 0; i < 3; ++i) {
        dst->m[i] = r[i] * other[0] + r[3 + i] * other[4] + r[6 + i] * other[8];
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ba940 / @ 0x006baa70  pre-rotate wrappers
// ---------------------------------------------------------------------------
void __cdecl PreRotateX(cTransform*, float);
void __cdecl PreRotateY(cTransform*, float);
void __cdecl FUN_006ba940(XForm2* p, float angle)
{
    cTransform t;
    t.tx = 0; t.ty = 0; t.tz = 0;
    t.flags = 0; t.modCount = 0; t.scale = 1.0f;
    t.rot.Assign((void*)0x16063f8);
    PreRotateX(&t, angle);
    if ((p->flags & 2) == 0) {
        for (int i = 0; i < 9; ++i) ((float*)&p->rot)[i] = ((float*)&t.rot)[i];
        p->flags |= 2;
    } else {
        FUN_006ba620(&p->rot, (float*)&t.rot);
    }
    float a = p->m4, b = p->m8, c = p->mc;
    p->m4 = a * t.rot.m[0] + b * t.rot.m[3] + c * t.rot.m[6];
    p->m8 = a * t.rot.m[1] + b * t.rot.m[4] + c * t.rot.m[7];
    p->mc = a * t.rot.m[2] + b * t.rot.m[5] + c * t.rot.m[8];
    p->count = (uint16_t)(p->count + 1);
}
void __cdecl FUN_006baa70(XForm2* p, float angle)
{
    (void)angle;
    p->count = (uint16_t)(p->count + 1);
}

// ---------------------------------------------------------------------------
// @ 0x006bab a0 / @ 0x006bac90 / @ 0x006badd0  (partial)
// ---------------------------------------------------------------------------
void __cdecl FUN_006baba0(void* self)
{
    (void)self;
}
struct Reporter { void* vptr; };
struct LogManager {
    void* m0;
    Reporter* m4;
    Reporter* m8;
    uint32_t m14;
    uint32_t m18;
    void* m1c;
    uint8_t m20;
    Reporter* m24;
    LogManager(void* p);
};
LogManager::LogManager(void* p)
{
    m0 = 0; m4 = 0; m8 = 0; m24 = 0;
    m1c = p;
    m14 = 0;
    m18 = m18 + 1;
    m20 = 1;
    m18 = 0;
}

// @ 0x006ba2f0
void __cdecl FUN_006ba2f0(void* self, const void* a, const void* b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x006bac90
void __cdecl FUN_006bac90(void* self)
{
    (void)self;
}

// ---------------------------------------------------------------------------
// @ 0x006bae50  application property setup
// ---------------------------------------------------------------------------
void __cdecl FUN_006bae50(void)
{
    PropList* p = g_appProperties;
    p->Set(2, 1);
    p->Set(3, 1);
    p->Set(4, 1);
    p->Set(5, 1);
    p->Set(6, 1);
    p->Set(0xb, 1);
    p->SetInt(0x1c, 0x800);
    p->SetFloat(0x1d, 3.0f);
}

// ---------------------------------------------------------------------------
// @ 0x006baec0  SP::FindDirectoryUp
// ---------------------------------------------------------------------------
void __cdecl FUN_006baec0(void* path);
void __cdecl FUN_006baec0(void* path)
{
    (void)path;
}

// ---------------------------------------------------------------------------
// @ 0x006baff0  SP::SporeAlert
// ---------------------------------------------------------------------------
namespace SP {
void __cdecl SporeAlert(const char* msg, int line, int type)
{
    UINT uType = 0x52000;
    switch (type) {
    case 0: uType = 0x52040; break;
    case 1: uType = 0x52030; break;
    case 2: uType = 0x52010; break;
    }
    EStrC str;
    EStrC_sprintf(&str, "%s [%d]", msg, line);
    MessageBoxA(0, str.mpBegin, "Alert", uType);
}
}

// ---------------------------------------------------------------------------
// @ 0x006bb0b0  wide alert
// ---------------------------------------------------------------------------
void __cdecl FUN_006bb0b0(const wchar_t* msg, int line, int type)
{
    UINT uType = 0x52000;
    if (type == 0) uType = 0x52040;
    else if (type == 1) uType = 0x52030;
    else if (type == 2) uType = 0x52010;
    EStrW str;
    EStrW_format(&str, L"%ls [%d]", msg, line);
    MessageBoxW(0, str.mpBegin, L"Alert", uType);
}
