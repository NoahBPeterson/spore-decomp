// Slice s0095ff20 -- EA::UTFWin Window geometry/message helpers and WindowListMarshaller.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

extern "C" void __cdecl FUN_009580B0(void*);
extern "C" void __cdecl FUN_00958820(void*);
extern "C" void __cdecl FUN_009588C0(void*);
extern "C" void __cdecl FUN_00958860(void*);
extern "C" void __cdecl FUN_009580E0(void*);
extern "C" int  __cdecl FUN_0095A0B0(void*, int);
extern "C" void __cdecl FUN_0095AF00(void*);
extern "C" void* __cdecl operator_new_arr(unsigned int, const char*, int, int, const char*, int);
extern "C" void* __cdecl operator_new_size(unsigned int, const char*, int, int, const char*, int);

struct Window {
    char  pad0[0x28];
    int   m28;                 // +0x28
    int   m2c;                 // +0x2c
    int   m30;                 // +0x30
    int   m34;                 // +0x34
    int   m38;                 // +0x38
    char  pad1[0x84 - 0x3c];
    float m84, m88, m8c, m90;  // +0x84
    float m94, m98, m9c, mA0;  // +0x94
    int   mA4;                 // +0xa4
    char  pad2[0x148 - 0xa8];
    float mMat[16];            // +0x148
    char  pad3[0x1d4 - 0x188];
    int   m1d4;                // +0x1d4
    int   m1d8;                // +0x1d8
    int   m1dc;                // +0x1dc
    void* m1e4;                // +0x1e4

    void MoveBy(float dx, float dy);            // 0x0095FF20
    void GrowBy(float dw, float dh);            // 0x0095FF70
    void MoveBy2(float dx, float dy);           // 0x0095FFD0
    void SetA4(int v);                          // 0x00960020
    void Set1E4(void* p);                       // 0x00960050
    void OnPaint2();                            // 0x009600A0
    void CallSlot();                            // 0x009600D0
    void TransformPoint(float x, float y, float* out);  // 0x00960100
    void ScreenToLocal(float x, float y, float* out);   // 0x00960180
    void GetChild(void* out, void* node);       // 0x009601E0
    void RemoveChild(void* node);               // 0x00960230
    void ClearChildren();                       // 0x00960280
    int  Dispatch14(void* p);                   // 0x009602C0
    int  Dispatch(void* p);                     // 0x009602F0
    void OnPaint();                             // 0x00960310 (partial)
    void DoMessage();                           // 0x00960410 (partial)
    void SetPhysicalArea();                     // 0x009608C0 (partial)
    void InvalidateLayout();                    // 0x009609B0 (partial)
};

// @ 0x0095FF20
void Window::MoveBy(float dx, float dy) {
    float a[4];
    a[0] = m94;
    a[1] = m98;
    a[2] = a[0] + dx;
    a[3] = a[1] + dy;
    (*(void(__thiscall**)(Window*, float*))((char*)*(void**)this + 0x60))(this, a);
}

// @ 0x0095FF70
void Window::GrowBy(float dw, float dh) {
    float a[4];
    a[0] = dw;
    a[1] = dh;
    a[2] = (m8c - m84) + dw;
    a[3] = (m90 - m88) + dh;
    (*(void(__thiscall**)(Window*, float*))((char*)*(void**)this + 0x6c))(this, a);
}

// @ 0x0095FFD0
void Window::MoveBy2(float dx, float dy) {
    float a[4];
    a[0] = m84;
    a[1] = m88;
    a[2] = a[0] + dx;
    a[3] = a[1] + dy;
    (*(void(__thiscall**)(Window*, float*))((char*)*(void**)this + 0x6c))(this, a);
}

// @ 0x00960020
void Window::SetA4(int v) {
    if (mA4 != v) {
        mA4 = v;
        if (m30 != 0) {
            FUN_009580B0((char*)this - 4);
        }
    }
}

// @ 0x00960050
void Window::Set1E4(void* p) {
    if (p != m1e4) {
        void* old = m1e4;
        if (p != old) {
            if (p != 0)
                (*(void(__thiscall**)(void*))((char*)*(void**)p))(p);
            m1e4 = p;
            if (old != 0)
                (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x90))(this);
    }
}

// @ 0x009600A0
void Window::OnPaint2() {
    if ((m2c & 4) == 0) {
        if ((m2c & 1) != 0 || (m28 & 1) != 0) {
            if (m30 != 0)
                FUN_00958820((char*)this - 4);
        }
    }
}

// @ 0x009600D0
void Window::CallSlot() {
    if (m30 != 0)
        FUN_009588C0((char*)this - 4);
}

// @ 0x00960100
void Window::TransformPoint(float x, float y, float* out) {
    Window* w = (Window*)((char*)this - 4);
    if (m30 != 0) {
        Window* found = 0;
        do {
            if ((*((uint8_t*)w + 0x30) & 0x20) != 0)
                found = w;
            w = (Window*)((char*)w + 0x38);
        } while (w != 0);
        if (found != 0)
            FUN_0095AF00(found);
    }
    out[0] = x;
    out[1] = y;
}

// @ 0x00960180 (partial)
void Window::ScreenToLocal(float x, float y, float* out) {
    (void)x;
    (void)y;
    out[0] = 0.0f;
    out[1] = 0.0f;
}

// @ 0x009601E0 (partial)
void Window::GetChild(void* out, void* node) {
    *(void**)out = node;
}

// @ 0x00960230 (partial)
void Window::RemoveChild(void* node) {
    if (node != 0) {
        (*(void(__thiscall**)(void*))((char*)*(void**)node))(node);
        (*(void(__thiscall**)(Window*, void*))((char*)*(void**)this + 0xdc))(this, node);
        (*(void(__thiscall**)(void*))((char*)*(void**)node + 0x1c))(node);
        (*(void(__thiscall**)(void*))((char*)*(void**)node + 4))(node);
    }
}

// @ 0x00960280
void Window::ClearChildren() {
    int* head = (int*)((char*)this + 0x38);
    while (head[1] != (int)head) {
        int node = *head;
        int v;
        if (node == 0 || node == 8)
            v = 0;
        else
            v = node - 4;
        (*(void(__thiscall**)(Window*, int))((char*)*(void**)this + 0xe0))(this, v);
    }
}

// @ 0x009602C0
int Window::Dispatch14(void* p) {
    if (m30 != 0)
        return (*(int(__thiscall**)(int, int, void*))((char*)*(void**)m30 + 0x14))(
            m30, *(int*)p, p);
    return 0;
}

// @ 0x009602F0
int Window::Dispatch(void* p) {
    if (m30 != 0)
        return FUN_0095A0B0((char*)this - 4, (int)p);
    return 0;
}

// @ 0x00960310 (partial: paint traversal not reconstructed)
void Window::OnPaint() {
}

// @ 0x00960410 (partial: message dispatch not reconstructed)
void Window::DoMessage() {
}

// @ 0x009608C0 (partial)
void Window::SetPhysicalArea() {
}

// @ 0x009609B0 (partial)
void Window::InvalidateLayout() {
}

// ===========================================================================
// EASTL allocator pair helper + hash-table rehash
// ===========================================================================

// @ 0x00960550
void* __stdcall AllocPair(void* p) {
    int* r = (int*)operator_new_size(
        0xc, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (r != 0) {
        r[0] = ((int*)p)[0];
        int* q = (int*)((int*)p)[1];
        r[1] = (int)q;
        if (q != 0)
            (*(void(__thiscall**)(int*))(*q))(q);
    }
    r[2] = 0;
    return r;
}

// @ 0x009605A0 (partial)
void Rehash(void* self, unsigned int n) {
    (void)self;
    (void)n;
}

// ===========================================================================
// WindowListMarshaller
// ===========================================================================
struct WindowList {
    char pad[0x1c];
    void* mBegin;   // +0x1c
    void* mEnd;     // +0x20
};

// @ 0x00960650 (partial: marshaller read not reconstructed)
int WindowListMarshaller_Read(void* self, void* src, void* dst) {
    (void)self;
    (void)src;
    (void)dst;
    return 0;
}

// @ 0x00960AE0 (partial)
int FUN_00960AE0(void* self) {
    (void)self;
    return 0;
}

// @ 0x00960B40 (partial)
int FUN_00960B40(void* self) {
    (void)self;
    return 0;
}
