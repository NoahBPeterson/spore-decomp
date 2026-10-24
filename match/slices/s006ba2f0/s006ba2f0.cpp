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

// eastl allocator deallocation (operator delete)
void __cdecl EASTL_dealloc(void*);                                  // 0x00f47380

// static empty strings and read-only game constants
extern const char    g_emptyStrC[];                                 // 0x1667bac
extern const wchar_t g_emptyStrW[];                                 // 0x1667bae
extern const wchar_t gEmptyString16[];                              // 0x1667bac
extern const wchar_t DAT_01409f64[];                                // 0x1409f64

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

// RenderWare/EA::Swarm math stub types
struct Matrix3 {
    float m[9];
    void Assign(const void* src);                                   // 0x0041cb40
};
struct cTransform {
    float    tx, ty, tz;
    uint16_t flags;
    uint16_t modCount;
    float    scale;
    Matrix3  rot;
    void PreRotateX(float angle);                                   // 0x005a2d90
    void PreRotateY(float angle);                                   // 0x004099b0
};

// read-only matrix/scalar constants used by the pre-rotate wrappers
extern const float        DAT_016062b8;                             // 0x16062b8
extern const float        DAT_016062bc;                             // 0x16062bc
extern const unsigned int DAT_016062c0;                             // 0x16062c0
extern const float        DAT_01485720;                             // 0x1485720
extern const Matrix3      DAT_016063f8;                             // 0x16063f8

// callees
void* __cdecl FUN_00453b20(Matrix3*, int, float);                   // builds a Matrix3
void* __cdecl FUN_0069b1c0(void*, int, int);                        // 0x0069b1c0
Matrix3* __cdecl FUN_006ba620(Matrix3* dst, const float* other);
bool  __cdecl FUN_009322b0(const void*);                            // 0x009322b0  EA::IO::Directory::Exists
int   __cdecl FUN_006a17e0(int, int);
int   __cdecl FUN_006a1880(int, int, int);
int   __cdecl FUN_006a1910(int, int, float);
struct PropList {
    void Set(int, int);
    void SetInt(int, int);
    void SetFloat(int, float);
};
void __cdecl WStr_Format(EStrW*, const wchar_t*, ...);
extern PropList* g_appProperties;   // 0x15fd918

// eastl::basic_string<wchar_t>::insert, __thiscall (ecx = the string), 3 stack args
struct EStrWInsert {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mpAllocator;
    void insert(wchar_t* dst, const wchar_t* first, const wchar_t* last);   // 0x005f7da0
};

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
    void SetA(int a, float b);
    void SetB(int a, int b);
    void PreRotateX(float angle);
    void PreRotateY(float angle);
};
void XForm2::Apply(const float* other)
{
    if ((flags & 2) == 0) {
        for (int i = 0; i < 9; ++i) rot.m[i] = other[i];
        flags |= 2;
    } else {
        FUN_006ba620(&rot, other);
    }
    float a = m4, b = m8, c = mc;
    m4 = ((other[3] * b + other[6] * c) + other[0] * a);
    m8 = ((other[1] * a + other[4] * b) + other[7] * c);
    mc = ((other[2] * a + other[5] * b) + other[8] * c);
    count = (uint16_t)(count + 1);
}

__declspec(noinline)
// ---------------------------------------------------------------------------
// @ 0x006ba620  (referenced above)
// ---------------------------------------------------------------------------
Matrix3* __cdecl FUN_006ba620(Matrix3* dst, const float* other)
{
    float r[9];
    r[0] = (dst->m[0] * other[0] + dst->m[1] * other[3]) + dst->m[2] * other[6];
    r[1] = (dst->m[0] * other[1] + dst->m[1] * other[4]) + dst->m[2] * other[7];
    r[2] = (dst->m[0] * other[2] + dst->m[1] * other[5]) + dst->m[2] * other[8];
    r[3] = (dst->m[3] * other[0] + dst->m[4] * other[3]) + dst->m[5] * other[6];
    r[4] = (dst->m[3] * other[1] + dst->m[4] * other[4]) + dst->m[5] * other[7];
    r[5] = (dst->m[3] * other[2] + dst->m[4] * other[5]) + dst->m[5] * other[8];
    r[6] = (dst->m[6] * other[0] + dst->m[7] * other[3]) + dst->m[8] * other[6];
    r[7] = (dst->m[6] * other[1] + dst->m[7] * other[4]) + dst->m[8] * other[7];
    r[8] = (dst->m[6] * other[2] + dst->m[7] * other[5]) + dst->m[8] * other[8];
    float* d = dst->m;
    const float* s = r;
    for (int i = 0; i < 9; ++i) *d++ = *s++;
    return dst;
}

// ---------------------------------------------------------------------------
// pre-rotate wrappers
// ---------------------------------------------------------------------------
void __cdecl PreRotateY(cTransform*, float);
// @ 0x006ba940
void XForm2::PreRotateX(float angle)
{
    cTransform t;
    t.tx = 0.0f;
    t.ty = DAT_016062b8;
    t.tz = DAT_016062bc;
    t.flags = (uint16_t)DAT_016062c0;
    t.modCount = (uint16_t)(DAT_016062c0 >> 16);
    t.scale = DAT_01485720;
    t.rot.Assign(&DAT_016063f8);
    t.PreRotateX(angle);

    if ((flags & 2) == 0) {
        rot = t.rot;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)&t.rot);
    }

    float a = m4, b = m8, c = mc;
    m4 = ((a * t.rot.m[0] + b * t.rot.m[3]) + c * t.rot.m[6]);
    m8 = ((a * t.rot.m[1] + c * t.rot.m[7]) + b * t.rot.m[4]);
    mc = ((a * t.rot.m[2] + c * t.rot.m[8]) + b * t.rot.m[5]);
    count = (uint16_t)(count + 1);
}
// @ 0x006baa70
void XForm2::PreRotateY(float angle)
{
    cTransform t;
    t.tx = 0.0f;
    t.ty = DAT_016062b8;
    t.tz = DAT_016062bc;
    t.flags = (uint16_t)DAT_016062c0;
    t.modCount = (uint16_t)(DAT_016062c0 >> 16);
    t.scale = DAT_01485720;
    t.rot.Assign(&DAT_016063f8);
    t.PreRotateY(angle);

    if ((flags & 2) == 0) {
        rot = t.rot;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)&t.rot);
    }

    float a = m4, b = m8, c = mc;
    m4 = ((a * t.rot.m[0] + b * t.rot.m[3]) + c * t.rot.m[6]);
    m8 = ((a * t.rot.m[1] + c * t.rot.m[7]) + b * t.rot.m[4]);
    mc = ((a * t.rot.m[2] + c * t.rot.m[8]) + b * t.rot.m[5]);
    count = (uint16_t)(count + 1);
}

// ---------------------------------------------------------------------------
// @ 0x006baba0  build a matrix from (int, float) and apply it
// ---------------------------------------------------------------------------
void XForm2::SetA(int a, float b)
{
    Matrix3 tmp;
    void* r = FUN_00453b20(&tmp, a, b);
    Matrix3 m;
    m.Assign(r);

    if ((flags & 2) == 0) {
        rot = m;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)&m);
    }

    float u = m4, v = m8, w = mc;
    m4 = ((u * m.m[0] + v * m.m[3]) + w * m.m[6]);
    m8 = ((u * m.m[1] + v * m.m[4]) + w * m.m[7]);
    mc = ((u * m.m[2] + v * m.m[5]) + w * m.m[8]);
    count = (uint16_t)(count + 1);
}

// ---------------------------------------------------------------------------
// @ 0x006bac90  build a matrix from two vectors and apply it
// ---------------------------------------------------------------------------
void XForm2::SetB(int a, int b)
{
    Matrix3 m;
    Matrix3* r = (Matrix3*)FUN_0069b1c0(&m, a, b);

    if ((flags & 2) == 0) {
        rot = *r;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)r);
    }

    float u = m4, v = m8, w = mc;
    m4 = ((r->m[3] * v + r->m[6] * w) + r->m[0] * u);
    m8 = ((r->m[1] * u + r->m[4] * v) + r->m[7] * w);
    mc = ((r->m[2] * u + r->m[5] * v) + r->m[8] * w);
    count = (uint16_t)(count + 1);
}

// ---------------------------------------------------------------------------
// @ 0x006badd0  logging manager constructor
// ---------------------------------------------------------------------------
struct LogVector {
    void* mpBegin;   // 0x00
    void* mpEnd;     // 0x04
    void* mpCap;     // 0x08
    void erase(void* begin, void* end);                             // 0x00e25bd0
};
struct ILogReporter;
struct ILogReporterVtbl {
    void (__thiscall* mSlot0)(ILogReporter*);
    void (__thiscall* mSlot1)(ILogReporter*);
};
struct ILogReporter {
    ILogReporterVtbl* mpVtbl;
};
struct LogManager {
    LogVector     mVector;      // 0x00
    unsigned int  m0c;          // 0x0c
    unsigned int  m10;          // 0x10
    unsigned int  m14;          // 0x14
    unsigned int  m18;          // 0x18
    void*         m1c;          // 0x1c
    uint8_t       m20;          // 0x20
    uint8_t       mPad21[3];    // 0x21
    ILogReporter* m24;          // 0x24
    LogManager(void* p);
};
LogManager::LogManager(void* p)
{
    mVector.mpBegin = 0;
    mVector.mpEnd = 0;
    mVector.mpCap = 0;
    m24 = 0;
    m1c = p;
    m14 = 0;
    mVector.erase(mVector.mpBegin, mVector.mpEnd);
    m18 = m18 + 1;
    m20 = 1;
    if (m24 != 0) {
        ILogReporter* r = m24;
        m24 = 0;
        r->mpVtbl->mSlot1(r);
    }
    m18 = 0;
}

// transform context: flag byte followed by the rotation matrix at +0x14
struct XFormMat {
    uint8_t  mFlags;        // 0x00
    uint8_t  mPad01[0x13];  // 0x01
    Matrix3  mRot;          // 0x14
};

#define XFORM_APPLY(P, V)                                                             \
    do {                                                                              \
        if (((P)->mFlags & 2) != 0) {                                                 \
            float fx = (V)[0], fy = (V)[1], fz = (V)[2];                              \
            (V)[0] = (((P)->mRot.m[3] * fy + (P)->mRot.m[6] * fz) + (P)->mRot.m[0] * fx); \
            (V)[1] = (((P)->mRot.m[1] * fx + (P)->mRot.m[4] * fy) + (P)->mRot.m[7] * fz); \
            (V)[2] = (((P)->mRot.m[2] * fx + (P)->mRot.m[5] * fy) + (P)->mRot.m[8] * fz); \
        }                                                                             \
    } while (0)

// ---------------------------------------------------------------------------
// @ 0x006ba2f0
// ---------------------------------------------------------------------------
void __cdecl FUN_006ba2f0(void* ctx, int count, char* data, int stride)
{
    XFormMat* p = (XFormMat*)ctx;
    if (((p->mFlags >> 1) & 1) == 0) return;

    int done = 0;
    if (count > 3)
    {
        unsigned int blocks = ((unsigned int)(count - 4) >> 2) + 1;
        done = (int)(blocks * 4);
        do
        {
            XFORM_APPLY(p, (float*)data); data += stride;
            XFORM_APPLY(p, (float*)data); data += stride;
            XFORM_APPLY(p, (float*)data); data += stride;
            XFORM_APPLY(p, (float*)data); data += stride;
            --blocks;
        } while (blocks != 0);
    }
    if (done < count)
    {
        int remaining = count - done;
        do
        {
            XFORM_APPLY(p, (float*)data); data += stride;
        } while (--remaining != 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006baec0  SP::FindDirectoryUp
// ---------------------------------------------------------------------------
void __cdecl FUN_006baec0(void* path)
{
    EStrWInsert* str = (EStrWInsert*)path;
    EStrWInsert local;
    local.mpBegin = (wchar_t*)gEmptyString16;
    local.mpEnd = (wchar_t*)gEmptyString16;
    local.mpCapacity = (wchar_t*)gEmptyString16 + 1;

    bool found = false;
    if (FUN_009322b0(str->mpBegin)) {
        found = true;
    } else {
        for (;;) {
            const wchar_t* first = DAT_01409f64;
            const wchar_t* last = first;
            while (*last != 0) ++last;
            local.insert(local.mpBegin, first, last);

            if (!FUN_009322b0(local.mpBegin)) break;

            first = DAT_01409f64;
            last = first;
            while (*last != 0) ++last;
            str->insert(str->mpBegin, first, last);

            if (FUN_009322b0(str->mpBegin)) { found = true; break; }
        }
    }
    (void)found;

    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin != 0)
        EASTL_dealloc(local.mpBegin);
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