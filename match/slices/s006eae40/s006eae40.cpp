// Slice s006eae40 -- effects camera manager, render-entity copy/sort/dtor helpers.
#include <string.h>
#include <intrin.h>
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

struct Vec3 { float x, y, z; };
static inline Vec3 MakeV3(float c) { Vec3 v; v.x = c; v.y = c; v.z = c; return v; }

struct E7 {
    void GetImageResource(void*);   // refcount-copy helper (0x576650)
    void r41cb40(void*);            // rw::math::Matrix33::Assign
};

extern void   f_f47380(void*);
extern void   f7c4d00(int);
extern float  g1533c74;

#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]

// ---- free helpers ----
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
    void mae40();
    void m6eb8c0(void* src);
    S7*  m6ebb80(void* src);
    void mebf50();
    void mec000();
    void mec090();
};

// ---------------------------------------------------------------------------
// @ 0x006eae40
void S7::mae40()
{
    // 2186-byte routine; only the entry shape is reproduced (partial).
    (void)this;
}

// ---------------------------------------------------------------------------
// @ 0x006eb6e0  SP::cEffectsCameraManager::UpdateCameraView
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

// ---------------------------------------------------------------------------
// @ 0x006eb8c0
void S7::m6eb8c0(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(void**)d = *(void**)s;
    if (*(void**)d)
        (*(int*)((char*)*(void**)d + 4))++;
    for (int off = 4; off <= 0x28; off += 4)
        *(uint*)(d + off) = *(uint*)(s + off);
    ((E7*)(d + 0x2c))->r41cb40(s + 0x2c);
    *(uchar*)(d + 0x50) = *(uchar*)(s + 0x50);
    *(uchar*)(d + 0x51) = *(uchar*)(s + 0x51);
    *(uint*)(d + 0x54) = *(uint*)(s + 0x54);
    *(uint*)(d + 0x58) = *(uint*)(s + 0x58);
    *(uint*)(d + 0x5c) = *(uint*)(s + 0x5c);
    *(void**)(d + 0x60) = *(void**)(s + 0x60);
    if (*(void**)(d + 0x60))
        ((void(__thiscall*)(void*))VFN(*(void**)(d + 0x60), 0))(*(void**)(d + 0x60));
    *(uint*)(d + 0x64) = *(uint*)(s + 0x64);
}

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x006ebf50
void S7::mebf50()
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
}

// ---------------------------------------------------------------------------
// @ 0x006ec000
void S7::mec000()
{
    char* p = (char*)this;
    // vector dtor at +0x70 + refcount/vector teardown (EH); approximated
    *(void**)p = (void*)0x13ef094;
    void* r = *(void**)(p + 0x6c);
    if (r)
        ((void(__thiscall*)(void*))VFN(r, 4))(r);
    int b = *(int*)(p + 8);
    if (b != 0 && b != *(int*)(p + 0x18))
        f_f47380((void*)b);
}

// ---------------------------------------------------------------------------
// @ 0x006ec090
void S7::mec090()
{
    char* p = (char*)this;
    int i = *(int*)(p + 4);
    if ((int)((*(int*)(p + 0xc) - i) & 0xfffffffe) > 2 && i != 0 && i != *(int*)(p + 0x14))
        f_f47380((void*)i);
}
