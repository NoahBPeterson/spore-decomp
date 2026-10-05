// SP::cSPEditorBlock — scale/transform plumbing (unoptimized /Od /Ob1 /arch:SSE).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Matrix3 { float m[9]; Matrix3() {} Matrix3(const Matrix3&); };

// 28-byte transform-ish record used by the +0x4C8 element list.
struct Trans {
    uint32_t flag;   // +0x00
    Vec3     a;      // +0x04
    Vec3     b;      // +0x10
    Trans();
    Trans(const Trans& o);
};

struct cSPEditorBlock {
    char        pad00[0x10];
    void*       mModel;      // +0x10
    char        pad14[0x18 - 0x14];
    void*       p18;         // +0x18
    char        pad1c[0x33C - 0x1c];
    cSPEditorBlock* link33c; // +0x33C
    char        pad340[0x3EC - 0x340];
    void*       p3ec;        // +0x3EC
    char        pad3f0[0x4C8 - 0x3F0];
    void*       list4c8;     // +0x4C8
    void*       list4cc;     // +0x4CC
    char        pad4d0[0x5F8 - 0x4D0];
    Vec3        v5f8;        // +0x5F8
    char        pad604[0xDC8 - 0x604];
    uint32_t    flags0;      // +0xDC8
    uint32_t    flags1;      // +0xDCC

    Vec3* F40b90(Vec3* out);                    // 00440B90
    void  F40bc0(const Vec3* v);                // 00440BC0
    void  F40c00(float f);                      // 00440C00
    void  F40c40(void* item, int flag);         // 00440C40
    bool  F40d80(void* out);                    // 00440D80
    void  F40e00(cSPEditorBlock* o);            // 00440E00
    void  F40e60(void* key);                    // 00440E60
    void  F40390(float f);                      // 00440390
    void  F40420(float f, char b);              // 00440420
    void  F404f0(Matrix3 m);                    // 004404F0
    void  F40110(float f);                      // 00440110
    void  F40520(float f, char b, int c);       // 00440520
    void  SetFlag(int a, int b);                // 00435A10
};

void* Sub_454420(void* p);
void  Sub_4525990(void* p);
void* Sub_4553b0(void* out, void* key);        // map find (thiscall on vec)
void  Sub_4B8750(void* a, void* b, void* out, int flag);
void  Sub_4B8180(void* p);
void  Sub_698650(void* m);
void  Sub_4A070();
bool  Sub_43EBC0();
bool  Sub_43ECB0();

extern const Vec3 g_v3_241c;   // 015D241C

// @ 0x00440B90
Vec3* cSPEditorBlock::F40b90(Vec3* out)
{
    *out = v5f8;
    return out;
}

// @ 0x00440BC0
void cSPEditorBlock::F40bc0(const Vec3* v)
{
    if (mModel != 0) {
        void* m = mModel;
        *(Vec3*)((char*)m + 0x4C) = *v;
    }
}

// @ 0x00440C00
void cSPEditorBlock::F40c00(float f)
{
    if (mModel != 0) {
        void* m = mModel;
        *(float*)((char*)m + 0x58) = f;
    }
}

// @ 0x00440390
void cSPEditorBlock::F40390(float f)
{
    float lo = 0.0f, hi = 1.0f;
    float v = f;
    if (v < lo) v = lo;
    if (v > hi) v = hi;
    if (v != *(float*)((char*)this + 0x1D0)) {
        *(float*)((char*)this + 0x1D0) = v;
        SetFlag(9, 1);
    }
}

// @ 0x00440420
void cSPEditorBlock::F40420(float f, char b)
{
    float old = *(float*)((char*)this + 0x1DC);
    *(float*)((char*)this + 0x1DC) = f;
    if (*(float*)((char*)this + 0x1DC) > *(float*)((char*)this + 0x1E4)) {
        *(float*)((char*)this + 0x1DC) = *(float*)((char*)this + 0x1E4);
    } else if (*(float*)((char*)this + 0x1E0) > *(float*)((char*)this + 0x1DC)) {
        *(float*)((char*)this + 0x1DC) = *(float*)((char*)this + 0x1E0);
    }
    if (b != 0 && p3ec != 0) {
        F40110((*(float*)((char*)this + 0x1DC) / old) * *(float*)((char*)this + 0x1D4));
    }
}

// @ 0x004404F0
void cSPEditorBlock::F404f0(Matrix3 m)
{
    Sub_698650(&m);
    uint32_t* dst = (uint32_t*)((char*)this + 0xF0);
    uint32_t* src = (uint32_t*)&m;
    for (int i = 0; i < 9; i++) dst[i] = src[i];
}

// @ 0x00440F60
Trans::Trans()
{
    flag = 0;
    a = g_v3_241c;
    b = g_v3_241c;
}

// @ 0x00440FF0
Trans::Trans(const Trans& o)
{
    flag = o.flag;
    a = o.a;
    b = o.b;
}

// @ 0x00440C40
void cSPEditorBlock::F40c40(void* item, int flag)
{
    (void)item; (void)flag;
}

// @ 0x00440D80
bool cSPEditorBlock::F40d80(void* out)
{
    (void)out;
    return false;
}

// @ 0x00440E00
void cSPEditorBlock::F40e00(cSPEditorBlock* o)
{
    char* it = (char*)o->list4c8;
    char* end = (char*)o->list4cc;
    for (; it != end; it += 0x20) {
        F40c40(it + 4, *(int*)it);
    }
}

// @ 0x00440E60
void cSPEditorBlock::F40e60(void* key)
{
    (void)key;
}

// @ 0x00440110
void cSPEditorBlock::F40110(float f)
{
    (void)f;
}

// @ 0x00440520
void cSPEditorBlock::F40520(float f, char b, int c)
{
    (void)f; (void)b; (void)c;
}

} // namespace SP
