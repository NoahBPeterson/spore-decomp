// Slice s0095eeb0 -- EA::UTFWin / rw::math FPU matrix + transform and Window base
// helpers (ModulateARGB32, AsInterface, refcount Release, area setters).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

extern "C" {
unsigned __int64 __rdtsc(void);
__declspec(dllimport) double __cdecl sin(double);
__declspec(dllimport) double __cdecl cos(double);
}
extern "C" void __cdecl FUN_00958860(void*);
extern "C" void __cdecl FUN_009580E0(void*);
extern "C" void __cdecl MatMulVec(void*, const void*, const void*);     // 0x0095E040
extern "C" char __cdecl MatInvertFull(void*, void*);                    // 0x0095E0B0
extern "C" void __cdecl FUN_0045EAC0(void* out, const void* a, const void* b); // 0x0045EAC0
extern "C" void __cdecl Inv3(float* out, float* in, float* det);        // 0x0095F490

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---------------------------------------------------------------------------
// 4x4 float matrix
// ---------------------------------------------------------------------------
struct CM {
    float m[16];

    void  TransformPoint3(float* out, const float* v);
    void  TransformPoint3B(float* out, const float* v);
    float* TransformPoint4(float* out, const float* v);
    void* BuildMat33(const float* src);
    void  SetRotationAtLeast2(float* axis, float angle);
    void  Invert();
    void  Multiply(const float* o);
};

// @ 0x0095EEB0
void CM::TransformPoint3(float* out, const float* v) {
    float x = v[0], y = v[1], z = v[2];
    out[0] = m[12] + (m[8] * z + (m[4] * y + x * m[0]));
    out[1] = m[13] + (m[9] * z + (m[1] * x + m[5] * y));
    out[2] = m[14] + (m[10] * z + (m[2] * x + m[6] * y));
}

// @ 0x0095EFB0
void CM::TransformPoint3B(float* out, const float* v) {
    float x = v[0], y = v[1], z = v[2];
    out[0] = m[8] * z + (m[4] * y + x * m[0]);
    out[1] = m[9] * z + (m[1] * x + m[5] * y);
    out[2] = m[10] * z + (m[2] * x + m[6] * y);
}

// @ 0x0095F090
void* CM_SetAxes(void* self, float* a, float* b, float* c) {
    ((float*)self)[0] = a[0]; ((float*)self)[1] = a[1]; ((float*)self)[2] = a[2]; ((float*)self)[3] = a[3];
    ((float*)self)[4] = b[0]; ((float*)self)[5] = b[1]; ((float*)self)[6] = b[2]; ((float*)self)[7] = b[3];
    ((float*)self)[8] = c[0]; ((float*)self)[9] = c[1]; ((float*)self)[10] = c[2]; ((float*)self)[11] = c[3];
    return self;
}

// @ 0x0095F0F0
void* CM::BuildMat33(const float* src) {
    m[0] = src[0]; m[1] = src[1]; m[2] = src[2];
    m[4] = src[4]; m[5] = src[5]; m[6] = src[6];
    m[8] = src[8]; m[9] = src[9]; m[10] = src[10];
    return this;
}

// @ 0x0095F1C0
float* CM::TransformPoint4(float* out, const float* v) {
    float x = v[0], y = v[1], z = v[2];
    float r0 = m[12] + (m[8] * z + (m[4] * y + x * m[0]));
    float r1 = m[13] + (m[9] * z + (m[5] * y + m[1] * x));
    float r2 = m[14] + (m[10] * z + (m[6] * y + m[2] * x));
    float w = m[15] + (m[11] * z + (m[7] * y + m[3] * x));
    out[0] = r0;
    out[1] = r1;
    out[2] = r2;
    if (w != 1.0f) {
        w = 1.0f / w;
        out[0] = w * r0;
        out[1] = w * r1;
        out[2] = w * r2;
    }
    return out;
}

// @ 0x0095F320 (free)
void BuildRotation(float* out, float* axis, float angle) {
    float s = (float)sin(angle);
    float c = (float)cos(angle);
    float t = 1.0f - c;
    float x = axis[0], y = axis[1], z = axis[2];
    out[0] = x * (x * t) + c;
    out[1] = y * (x * t) + z * s;
    out[2] = z * (x * t) - y * s;
    out[3] = 0.0f;
    out[5] = y * (y * t) + c;
    out[7] = 0.0f;
    out[4] = x * (y * t) - z * s;
    out[6] = z * (y * t) + x * s;
    out[11] = 0.0f;
    out[8] = x * (z * t) + y * s;
    out[9] = y * (z * t) - x * s;
    out[10] = z * (z * t) + c;
    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;
}

// @ 0x0095F5C0
void CM::SetRotationAtLeast2(float* axis, float angle) {
    if (m[16] < 2.0f)
        m[16] = 2.0f;
    float rot[16];
    BuildRotation(rot, axis, angle);
    float tmp[16];
    FUN_0045EAC0(tmp, this, rot);
    for (int i = 0; i < 16; i++)
        m[i] = tmp[i];
}

// @ 0x0095F620 (partial: full 4x4 invert path approximated)
void CM::Invert() {
    int type = *(int*)&m[16];
    if (type == 1) {
        float f1 = m[9];
        float f6 = 1.0f / m[10];
        m[10] = f6;
        float f2 = m[11];
        float f7 = 1.0f / m[15];
        m[15] = f7;
        float f5 = 1.0f / m[0];
        m[0] = f5;
        m[12] = -(m[12] * f5);
        m[13] = -(f1 * f6);
        m[14] = -(f2 * f7);
        m[15] = 1.0f;
    } else if (type == 2) {
        float axes[12];
        CM_SetAxes(axes, m + 8, m + 4, m);
        float inv[12];
        float det;
        Inv3(inv, axes, &det);
        for (int i = 0; i < 12; i++)
            m[i] = inv[i];
        m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f;
        m[12] = -m[12]; m[13] = -m[13]; m[14] = -m[14];
        m[15] = 1.0f;
    } else if (type == 3) {
        if (MatInvertFull(this, this))
            *(int*)&m[16] = *(int*)&m[16];
        else
            *(int*)&m[16] = 4;
    }
}

// @ 0x0095F8C0 (free)
uint32_t ModulateARGB32(uint32_t c1, uint32_t c2) {
    uint32_t g = (c1 >> 8 & 0xff) * (c2 & 0xff00) + 0x100;
    uint32_t r = (c1 >> 0x10 & 0xff) * (c2 & 0xff0000) + 0x10000;
    uint32_t b = (c1 & 0xff) * (c2 & 0xff) + 1;
    uint32_t a = (c1 >> 0x18) * (c2 >> 0x18) + 1;
    return (((g >> 8) + g) & 0xff0000) | (((r >> 8) + r) & 0xff0000ff) |
           (((b >> 8) + b)) | ((((a & 0xffffff00) + a * 0x100) & 0xff0000) << 8);
}

// ---------------------------------------------------------------------------
// UTFWin Window base
// ---------------------------------------------------------------------------
struct Window {
    char pad[0x28];
    volatile long mRefCount;   // +0x28
    char pad2[4];              // +0x2c
    int m30;                   // +0x30
    int m34;                   // +0x34
    int m38;                   // +0x38
    char pad3[0x1d4 - 0x3c];
    int m1d4;                  // +0x1d4
    int m1d8;                  // +0x1d8
    int m1dc;                  // +0x1dc

    Window* AsInterface(int iid);
    int     Release();
    int     GetAt34();
    void    Set1D8(int v);
    bool    IsAncestorOf(void* other);
    bool    Test30Slot48(int v);
    bool    Test30Slot54(int v);
    bool    AllDescendants(char param);
    bool    AllDescendantsAll(char param);
    int     FindChild(int arg);
    int     WalkChildren(int* iface);
    void    SetA8(int v);
    void    Set1D4(int v);
    void    SetArea(float* area);
    void    ResizeBy(float dx, float dy);
};

// @ 0x0095F960
Window* Window::AsInterface(int iid) {
    if (iid == (int)0xee3f516e)
        goto common;
    if (iid == (int)0xeec58382)
        return this;
    if (iid != (int)0xeeee8218)
        return 0;
common:
    if (this == 0)
        return 0;
    return (Window*)((char*)this + 4);
}

// @ 0x0095F9A0
int Window::Release() {
    int n = _InterlockedExchangeAdd(&mRefCount, -1) - 1;
    if (n == 0) {
        _InterlockedExchangeAdd(&mRefCount, 1);
        if (this != 0)
            (*(void(__thiscall**)(Window*, int))((char*)*(void**)this + 8))(this, 1);
    }
    return n;
}

// @ 0x0095F9D0
int Window::GetAt34() {
    if (m34 != 0)
        return m34 + 4;
    return 0;
}

// @ 0x0095FA60
void Window::Set1D8(int v) {
    if (m1d8 != v) {
        m1d8 = v;
        (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x90))(this);
        if (m30 != 0) {
            int local[3];
            local[0] = 0xe;
            local[1] = 4;
            int a = ((char*)this - 4) != 0 ? (int)this : 0;
            (*(void(__thiscall**)(int, int, int, int, int))((char*)*(void**)m30 + 0x10))(
                m30, a, a, (int)local, 0);
        }
    }
}

// @ 0x0095FAD0
bool Window::IsAncestorOf(void* other) {
    if (other == 0)
        return false;
    void* p = (*(void*(__thiscall**)(void*))((char*)*(void**)other + 0x10))(other);
    while (p != 0) {
        if (p == (void*)((char*)this - 4))
            return true;
        p = (*(void*(__thiscall**)(void*))((char*)*(void**)p + 0x10))(p);
    }
    return false;
}

// @ 0x0095FB20
bool Window::Test30Slot48(int v) {
    if (m30 != 0) {
        int r = (*(int(__thiscall**)(int, int))((char*)*(void**)m30 + 0x48))(m30, v);
        if (r == (int)this)
            return true;
    }
    return false;
}

// @ 0x0095FB60
bool Window::Test30Slot54(int v) {
    if (m30 != 0) {
        int r = (*(int(__thiscall**)(int, int))((char*)*(void**)m30 + 0x54))(m30, v);
        if (r == (int)this)
            return true;
    }
    return false;
}

// @ 0x0095FBB0
bool Window::AllDescendants(char param) {
    unsigned mask = ((param != 0) - 1) & 2 | 1;
    int node = m38;
    while (node != 0) {
        unsigned r = (*(unsigned(__thiscall**)(int))((char*)*(void**)(node + 4) + 0x28))(node + 4);
        if ((mask & r) == 0)
            break;
        node = *(int*)(node + 0x38);
    }
    return node == 0;
}

// @ 0x0095FC00
bool Window::AllDescendantsAll(char param) {
    unsigned mask = ((param != 0) - 1) & 2 | 1;
    int node = m38;
    while (node != 0) {
        unsigned r = (*(unsigned(__thiscall**)(int))((char*)*(void**)(node + 4) + 0x28))(node + 4);
        if ((r & mask) == mask)
            return true;
        node = *(int*)(node + 0x38);
    }
    return false;
}

// @ 0x0095FC50 (partial)
int Window::FindChild(int arg) {
    int edi = m34;
    if (edi == 0)
        return 0;
    for (int i = 0; i < 2; i++) {
        int r = (*(int(__thiscall**)(int, int))((char*)*(void**)edi + 0x48))(edi, i);
        if (r == 0)
            break;
        r -= 4;
        if (r == 0)
            break;
        int node = r;
        while (node != 0 && node != (int)this)
            node = *(int*)(node + 0x38);
        if (node == 0)
            break;
        (void)arg;
        return node + 4;
    }
    return 0;
}

// @ 0x0095FCC0 (partial)
int Window::WalkChildren(int* iface) {
    (void)iface;
    return 0;
}

// @ 0x0095FD60
void Window::SetA8(int v) {
    int old = *(int*)((char*)this + 0xa8);
    if (v != old) {
        *(int*)((char*)this + 0xa8) = v;
        int local[4];
        local[0] = 0x13;
        local[2] = v;
        local[3] = old;
        (*(void(__thiscall**)(Window*, int*))((char*)*(void**)this + 0x114))(this, local);
        if (*(int*)((char*)this + 0x1dc) != 0)
            (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x90))(this);
    }
}

// @ 0x0095FDC0
void Window::Set1D4(int v) {
    if (m1d4 != v) {
        m1d4 = v;
        if (m30 != 0) {
            FUN_00958860((char*)this - 4);
            FUN_009580E0((char*)this - 4);
        }
    }
}

// @ 0x0095FE40
void Window::SetArea(float* area) {
    float x = area[0];
    if (*(float*)((char*)this + 0x94) == x &&
        *(float*)((char*)this + 0x98) == area[1] &&
        *(float*)((char*)this + 0x9c) == area[2] &&
        *(float*)((char*)this + 0xa0) == area[3])
        return;
    *(float*)((char*)this + 0x94) = x;
    *(float*)((char*)this + 0x98) = area[1];
    *(float*)((char*)this + 0x9c) = area[2];
    *(float*)((char*)this + 0xa0) = area[3];
    (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x94))(this);
}

// @ 0x0095FEC0
void Window::ResizeBy(float dx, float dy) {
    float area[4];
    area[0] = dx;
    area[1] = dy;
    area[2] = (*(float*)((char*)this + 0x9c) - *(float*)((char*)this + 0x94)) + dx;
    area[3] = (*(float*)((char*)this + 0xa0) - *(float*)((char*)this + 0x98)) + dy;
    (*(void(__thiscall**)(Window*, float*))((char*)*(void**)this + 0x60))(this, area);
}

// @ 0x0095F860
void CM::Multiply(const float* o) {
    if (m[16] == 0.0f) {
        for (int i = 0; i < 0x11; i++)
            m[i] = o[i];
        return;
    }
    if (((int*)o)[0x10] != 0) {
        float tmp[16];
        FUN_0045EAC0(tmp, this, o);
        for (int i = 0; i < 16; i++)
            m[i] = tmp[i];
        if (((int*)m)[0x10] < ((int*)o)[0x10])
            ((int*)m)[0x10] = ((int*)o)[0x10];
    }
}
