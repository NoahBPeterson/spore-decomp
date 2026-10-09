// Slice s006fe430: vertex-fragment declaration serialization, generated-vertex-shader string
// assembly, shader selection and the cVertexFragmentInfo table support routines.
// Region 0x6fe430-0x6ff170. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <stdio.h>
#include <string.h>

// ---- external callees -------------------------------------------------------------------
void* __cdecl FUN_011e073e(void* p, int a, unsigned size);   // operator_new[]
void* __cdecl FUN_011e0744(void* a, void* b, unsigned c);    // vector DoInsertValue
void  __cdecl FUN_00928dc0();
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380

// EA::IO helpers
void __cdecl EA_WriteUint32(void* stream, const void* p, int n, int flag);
void __cdecl EA_WriteUint16(void* stream, const void* p, int n, int flag);   // 0x0093a9d0 (equiv t2)
void __cdecl EA_operator_shl(void* stream, const void* p, int n);   // 0x0093a9a0 (equiv t3)
void __cdecl FUN_0093adb0(void* stream, const void* p, unsigned n, int flag);

// slice-26 callees (declared, not defined here)
char* __cdecl SP_TextCopy(char* d, const char* s);
char* __cdecl SP_TextCopySubstitute(char* d, const char* s, int a3, int a4, int a5, int a6);
char* __cdecl GenerateInputStruct(char* d, unsigned flags);
char* __cdecl GenerateCurrentStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes);
char* __cdecl GenerateOutputStruct(char* d, unsigned flags, unsigned ntex, const unsigned char* sizes);
char* __cdecl GenerateFillCurrentStruct(char* d, unsigned flags, int ntex);
char* __cdecl GenerateFillOutputStruct(char* d, unsigned flags, unsigned ntex);
bool  __cdecl FUN_006fe350(void* e);
void  __cdecl FUN_006fe3c0(int a, int b);

// ---- globals ----------------------------------------------------------------------------
extern unsigned char g_fragInfoTable;     // 0x1624710, stride 0x44
extern const char*   g_str1534e44;        // 0x1534e44 -> "cVertOut main(...)"
extern const char*   g_str1534e40;        // 0x1534e40 -> "\nreturn Out;\n}\n"
extern unsigned int  g_15345b0;           // 0x15345b0
extern unsigned char g_15345ac;           // 0x15345ac
extern void*         g_1624568;           // 0x1624568 currently-selected vertex shader
extern char          g_1620300;           // 0x1620300 shader text buffer
extern void*         g_16f6564;           // 0x16f6564 m_vertexShader
extern unsigned int  g_16f8cf8;           // 0x16f8cf8
extern void*         g_16f89d0;           // 0x16f89d0 d3d9 device

// vector globals (begin/end/cap dwords)
extern int* g_v1_begin;   // 0x1628b14
extern int* g_v1_end;     // 0x1628b18
extern int* g_v1_cap;     // 0x1628b1c
extern int* g_v2_begin;   // 0x16246fc
extern int* g_v2_end;     // 0x1624700
extern int* g_v2_cap;     // 0x1624704
extern char* g_vs_begin;  // 0x1628c20
extern char* g_vs_end;    // 0x1628c24

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

struct Vec4 {                  // 4-byte-element vector with out-of-line grow
    void* begin;
    void* end;
    void* cap;
    void Grow(void* pos, const void* value);
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

// @ 0x006fe430
void __cdecl FUN_006fe430(void* stream) {
    unsigned char* p = (unsigned char*)0x0162477C;
    do {
        int v = *(int*)(p + 0x10);
        EA_WriteUint32(stream, &v, 1, 0);
        v = *(int*)(p + 0x14);
        EA_WriteUint32(stream, &v, 1, 0);
        unsigned char c = *(unsigned char*)(p + 0x19);
        EA_operator_shl(stream, &c, 1);
        c = *(unsigned char*)(p + 0x1a);
        EA_operator_shl(stream, &c, 1);
        c = *(unsigned char*)(p + 0x18);
        EA_operator_shl(stream, &c, 1);
        v = *(int*)(p - 0x28);
        EA_WriteUint32(stream, &v, 1, 0);
        FUN_0093adb0(stream, *(void**)(p - 0x24),
                     *(int*)(p - 0x20) - *(int*)(p - 0x24), 0);
        FUN_0093adb0(stream, *(void**)(p - 0x14),
                     *(int*)(p - 0x10) - *(int*)(p - 0x14), 0);
        v = (*(int*)(p) - *(int*)(p - 4)) / 0x1c;
        EA_WriteUint32(stream, &v, 1, 0);
        v = (*(int*)(p) - *(int*)(p - 4)) / 0x1c;
        if (v > 0) {
            int off = 0;
            do {
                unsigned char* e = (unsigned char*)(*(int*)(p - 4) + off);
                FUN_0093adb0(stream, *(void**)e, *(int*)(e + 4) - *(int*)e, 0);
                unsigned short u = *(unsigned short*)(e + 0x10);
                EA_WriteUint16(stream, &u, 1, 0);
                u = *(unsigned short*)(e + 0x12);
                EA_WriteUint16(stream, &u, 1, 0);
                u = *(unsigned short*)(e + 0x14);
                EA_WriteUint16(stream, &u, 1, 0);
                u = *(unsigned short*)(e + 0x16);
                EA_WriteUint16(stream, &u, 1, 0);
                unsigned int d = *(unsigned int*)(e + 0x18);
                EA_WriteUint32(stream, &d, 1, 0);
                off += 0x1c;
            } while (--v);
        }
        p += 0x44;
    } while ((int)p < 0x1628B38);
}

// @ 0x006fe600  -- vector<0x130-block>::insert (stub, see partial.txt)
void Vec130::Insert(char* pos, unsigned n, void* value) {
    (void)pos; (void)n; (void)value;
}

// @ 0x006fe7f0
void* __fastcall FUN_006fe7f0(char* p) {
    *(int*)(p + 0x00) = 0;
    *(void**)(p + 0x0c) = (void*)0x01667BAD;
    *(void**)(p + 0x04) = (void*)0x01667BAC;
    *(void**)(p + 0x08) = (void*)0x01667BAC;
    *(void**)(p + 0x14) = (void*)0x01667BAC;
    *(void**)(p + 0x18) = (void*)0x01667BAC;
    *(void**)(p + 0x1c) = (void*)0x01667BAD;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x38) = 0;
    *(int*)(p + 0x3c) = 0;
    *(unsigned char*)(p + 0x40) = 0;
    *(unsigned char*)(p + 0x41) = 0;
    *(unsigned char*)(p + 0x42) = 0;
    return p;
}

// @ 0x006fe830
void __fastcall FUN_006fe830(char* p) {
    void* a = *(void**)(p + 0x24);
    void* b = *(void**)(p + 0x28);
    ((Vec130*)(p + 0x24))->Destroy((char*)a, (char*)b);
    void* q = *(void**)(p + 0x24);
    if (q && ((int*)q)[-1]) EASTL_allocator_deallocate(q);
    q = *(void**)(p + 0x14);
    if ((int)(*(int*)(p + 0x1c) - (int)q) > 1 && q) EASTL_allocator_deallocate(q);
    q = *(void**)(p + 0x04);
    if ((int)(*(int*)(p + 0x0c) - (int)q) > 1 && q) EASTL_allocator_deallocate(q);
}

// @ 0x006fe890
void __cdecl FUN_006fe890() {
    int* b1 = g_v1_begin;
    int* e1 = g_v1_end;
    FUN_011e0744(b1, e1, 0);
    g_v1_end = (int*)g_v1_end - (e1 - b1);
    int* b2 = g_v2_begin;
    int* e2 = g_v2_end;
    FUN_011e0744(b2, e2, 0);
    g_v2_end = (int*)g_v2_end - (e2 - b2);
}

// @ 0x006fe8f0
void __cdecl FUN_006fe8f0(int a, int b) {
    if (g_v1_end < g_v1_cap) {
        int* pos = g_v1_end;
        g_v1_end = g_v1_end + 1;
        if (pos)
            *pos = a;
    } else {
        ((Vec4*)&g_v1_begin)->Grow(g_v1_end, &a);
    }
    if (g_v2_end < g_v2_cap) {
        int* pos = g_v2_end;
        g_v2_end = g_v2_end + 1;
        if (pos)
            *pos = b;
    } else {
        ((Vec4*)&g_v2_begin)->Grow(g_v2_end, &b);
    }
}

namespace {

// @ 0x006ff100
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

cVertexFragmentInfo& cVertexFragmentInfo::operator=(const cVertexFragmentInfo& o) {
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

// @ 0x006fe960
char* AddFragmentDeclarations(char* buf, int idx, int* reg) {
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
} // namespace

// @ 0x006fea30  -- GenerateVertexShader (stub, see partial.txt)
void __cdecl FUN_006fea30(int a1, int a2) {
    (void)a1; (void)a2;
}

// @ 0x006fec40  -- GetGeneratedVertexShader (stub, see partial.txt)
int __cdecl FUN_006fec40(void* a1, void* a2) {
    (void)a1; (void)a2;
    return 0;
}

// @ 0x006feee0
bool __cdecl FUN_006feee0(void* a1, const char* name) {
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
void __cdecl FUN_006fef70(int a) {
    char buf[32];
    FUN_006fe3c0(a, (int)buf);
    FUN_006feee0((void*)a, buf);
}

// @ 0x006fefa0
void __cdecl FUN_006fefa0() {
    ((Vec130*)0x01628C20)->Destroy(g_vs_begin, g_vs_end);
    unsigned int n = g_15345b0;
    if (n == 0)
        n = 0x200;
    ((Vec130*)0x01628C20)->Reserve(n);
    g_1624568 = 0;
}

// @ 0x006fefe0
void __cdecl FUN_006fefe0() {
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
void Vec130::Resize(unsigned n) {
    if ((unsigned)Size() < n) {
        char temp[0x130];
        FUN_011e073e(temp, 0, 0x130);
        Insert(end, n - Size(), temp);
    } else {
        Destroy(begin + n * 0x130, end);
    }
}
// --- equivalence checker address annotations
    void EASTL_allocator_deallocate(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
