// src/game/SPEngine/SPGraphicsFragmentVS.cpp -- migrated from slice(s) s006fe430, s006fd520 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFragmentVS.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char*** g_namesBegin_1628b14;
extern char*** g_namesEnd_1628b18;
extern void*   g_16f6dac;
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// ---- items of slice s006fd520 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_006fcb90(int n, void* first, int b);
extern char*** g_namesBegin_1628b14;
extern char*** g_namesEnd_1628b18;
extern void*   g_16f6dac;
struct V1c { char* begin; char* end; };
// ---- items of slice s006fd520 end

// ---- items of slice s006fe430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_fragInfoTable;     // 0x1624710, stride 0x44
extern unsigned int  g_15345b0;           // 0x15345b0
extern void*         g_1624568;           // 0x1624568 currently-selected vertex shader
extern void*         g_16f6564;           // 0x16f6564 m_vertexShader
extern unsigned int  g_16f8cf8;           // 0x16f8cf8
extern void*         g_16f89d0;           // 0x16f89d0 d3d9 device
extern char* g_vs_begin;  // 0x1628c20
extern char* g_vs_end;    // 0x1628c24
void* __cdecl FUN_011e073e(void* p, int a, unsigned size);   // operator_new[]
void  __cdecl FUN_00928dc0();
bool  __cdecl FUN_006fe350(void* e);
void  __cdecl FUN_006fe3c0(int a, int b);
struct FragElem {              // 0x1c
    const char*      sBegin;   // +0x00
    const char*      sEnd;     // +0x04
    char             pad08[8];
    unsigned short   w10;      // +0x10
    unsigned short   w12;      // +0x12
    unsigned short   w14;      // +0x14
    unsigned short   w16;      // +0x16
    unsigned int     d18;      // +0x18
};
struct FragInfo {              // 0x44
    int              f00;      // +0x00
    const char*      nameBegin;// +0x04
    const char*      nameEnd;  // +0x08
    const char*      nameCap;  // +0x0c
    char             pad10[4];
    const char*      uniBegin; // +0x14
    const char*      uniEnd;   // +0x18
    const char*      uniCap;   // +0x1c
    char             pad20[4];
    FragElem*        vecBegin; // +0x24
    FragElem*        vecEnd;   // +0x28
    FragElem*        vecCap;   // +0x2c
    char             pad30[8];
    int              f38;      // +0x38
    int              f3c;      // +0x3c
    unsigned char    b40;      // +0x40
    unsigned char    b41;      // +0x41
    unsigned char    b42;      // +0x42
};
struct Vec130 {                // 0x130-byte-element vector
    char* begin;   // +0x00
    char* end;     // +0x04
    char* cap;     // +0x08
    void Insert(char* pos, unsigned n, void* value);  // 0x6fe600 (not byte-exact)
    void Destroy(char* first, char* last);            // 0x6fae30
    void Reserve(unsigned n);                         // 0x6faae0
    void Resize(unsigned n);                          // 0x6ff060
    int Size() const { return (int)(end - begin) / 0x130; }
};
namespace {

struct EString {
    char* begin;   // +0x00
    char* end;     // +0x04
    char* cap;     // +0x08
    void assign(const char* first, const char* last);
};
struct VecStub24 {
    char pad[0x14];
    void CopyFrom(void* src);
};
struct cVertexFragmentInfo {
    int f00;                    // +0x00
    EString name;               // +0x04
    char pad10[4];
    EString uni;                // +0x14
    char pad20[4];
    VecStub24 vec;              // +0x24
    int f38;                    // +0x38
    int f3c;                    // +0x3c
    unsigned char b40;          // +0x40
    unsigned char b41;          // +0x41
    unsigned char b42;          // +0x42
    cVertexFragmentInfo& operator=(const cVertexFragmentInfo& o);
};

} // namespace
// ---- items of slice s006fe430 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_006fe8f0(int a, int b);  // 0x006fe8f0 (stays in the slice: not this object's)

// @ 0x006fe350
bool __cdecl FUN_006fe350(void* name)
{
    char*** begin = g_namesBegin_1628b14;
    int n = (int)(g_namesEnd_1628b18 - begin);
    for (int i = 0; i < n; i++) {
        if (strcmp(begin[i][0], *(char**)name) == 0)
            return true;
    }
    return false;
}

// @ 0x006fe3c0
void __cdecl FUN_006fe3c0(int a, int b)
{
    int idx = 0;
    int g = (int)(size_t)g_16f6dac;
    if (g != 0) {
        idx = *(int*)(g + 4);
        V1c* v = (V1c*)(a + 0x48 + idx * 0x14);
        if (v->begin == v->end)
            idx = 0;
    }
    V1c* v = (V1c*)(a + 0x48 + idx * 0x14);
    int first = (int)v->begin;
    int n = ((int)v->end - first) / 0x1c;
    char* r = (char*)FUN_006fcb90(n, (void*)first, b);
    r[b] = 0;
}

// @ 0x006fe960
char* AddFragmentDeclarations(char* buf, int idx, int* reg)
{
    FragInfo* fi = (FragInfo*)((char*)&g_fragInfoTable + idx * 0x44);
    if (fi->vecBegin != fi->vecEnd) {
        int count = (int)((char*)fi->vecEnd - (char*)fi->vecBegin) / 0x1c;
        if (count > 0) {
            int off = 0;
            do {
                FragElem* e = (FragElem*)((char*)fi->vecBegin + off);
                if (!FUN_006fe350(e)) {
                    FUN_006fe8f0((int)e, *reg);
                    buf += sprintf(buf, "extern uniform %s : register(c%d);\n", e->sBegin, *reg);
                    *reg += e->w14;
                }
                off += 0x1c;
            } while (--count);
        }
    }
    if (fi->uniBegin != fi->uniEnd)
        buf += sprintf(buf, "\n%s\n\n", fi->uniBegin);
    return buf;
}

// @ 0x006fea30
void __cdecl FUN_006fea30(int a1, int a2)
{
    (void)a1; (void)a2;
}

// @ 0x006fec40
int __cdecl FUN_006fec40(void* a1, void* a2)
{
    (void)a1; (void)a2;
    return 0;
}

// @ 0x006feee0
bool __cdecl FUN_006feee0(void* a1, const char* name)
{
    const char* nm = name;
    void* cur = g_1624568;
    int shader;
    if (cur != 0 && strcmp((const char*)cur, nm) == 0) {
        *(unsigned int*)((char*)cur + 0x24) = g_16f8cf8;
        shader = *(int*)((char*)g_1624568 + 0x20);
    } else {
        shader = FUN_006fec40(a1, (void*)nm);
    }
    bool changed = (g_16f6564 != (void*)shader);
    if (changed) {
        void* dev = g_16f89d0;
        void* fn = (*(void***)dev)[0x170 / 4];
        ((void(__stdcall*)(void*, void*))fn)(dev, (void*)shader);
        g_16f6564 = (void*)shader;
    }
    return changed;
}

// @ 0x006fef70
void __cdecl FUN_006fef70(int a)
{
    char buf[32];
    FUN_006fe3c0(a, (int)buf);
    FUN_006feee0((void*)a, buf);
}

// @ 0x006fefa0
void __cdecl FUN_006fefa0()
{
    ((Vec130*)0x01628C20)->Destroy(g_vs_begin, g_vs_end);
    unsigned int n = g_15345b0;
    if (n == 0)
        n = 0x200;
    ((Vec130*)0x01628C20)->Reserve(n);
    g_1624568 = 0;
}

// @ 0x006fefe0
void __cdecl FUN_006fefe0()
{
    int count = (int)(g_vs_end - g_vs_begin) / 0x130;
    if (count > 0) {
        int off = 0;
        do {
            void** slot = (void**)(g_vs_begin + off + 0x20);
            void* obj = *slot;
            if (obj) {
                void* fn = (*(void***)obj)[2];
                ((void(__stdcall*)(void*))fn)(obj);
                *slot = 0;
                g_vs_begin = *(char**)0x01628C20;
            }
            off += 0x130;
        } while (--count);
    }
    ((Vec130*)0x01628C20)->Destroy(g_vs_begin, g_vs_end);
    FUN_00928dc0();
}

// @ 0x006ff060
void Vec130::Resize(unsigned n)
{
    if ((unsigned)Size() < n) {
        char temp[0x130];
        FUN_011e073e(temp, 0, 0x130);
        Insert(end, n - Size(), temp);
    } else {
        Destroy(begin + n * 0x130, end);
    }
}

// @ 0x006ff100
cVertexFragmentInfo& cVertexFragmentInfo::operator=(const cVertexFragmentInfo& o)
{
    const cVertexFragmentInfo* s = &o;
    f00 = s->f00;
    if (&s->name != &name)
        name.assign(s->name.begin, s->name.end);
    if (&s->uni != &uni)
        uni.assign(s->uni.begin, s->uni.end);
    vec.CopyFrom((void*)&s->vec);
    f38 = s->f38;
    f3c = s->f3c;
    b40 = s->b40;
    b41 = s->b41;
    b42 = s->b42;
    return *this;
}
