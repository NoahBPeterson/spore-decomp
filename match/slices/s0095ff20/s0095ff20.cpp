// Slice s0095ff20 -- EA::UTFWin Window geometry/message helpers and WindowListMarshaller.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// ---- free helpers (external) ------------------------------------------------
extern "C" void* __cdecl operator_new_arr(unsigned int a, int b, unsigned int c);
extern "C" void* __cdecl operator_new_size(unsigned int, const char*, int, int, const char*, int);
extern "C" void  __cdecl FUN_009580B0(void*);
extern "C" void  __cdecl FUN_009580E0(void*);
extern "C" void  __cdecl FUN_00958820(void*);
extern "C" void  __cdecl FUN_00958860(void*);
extern "C" void  __cdecl FUN_009588C0(void*);
extern "C" int   __cdecl FUN_0095A0B0(void*, int);
// 0x0095af00 -- UpdateWindowCachedTransforms, __stdcall ret 4 (no ecx).
extern "C" void  __stdcall FUN_0095AF00(void*);
extern "C" void  __stdcall FUN_00959E00(void*);   // WinMgr::DetachWindow, plain stack arg

// ---- the window manager (pointer held in Window::m30) -----------------------
struct W_s0095_9780 {
    void FUN_00959FE0(int w);     // 0x00959FE0
    void FUN_00959E00(void* w);   // 0x00959E00
    void FUN_009580E0(void* w);   // 0x009580E0
    void FUN_00958820(void* w);   // 0x00958820
    void FUN_009588C0(void* w);   // 0x009588C0
};

struct CM {                       // the cached-transform block at this+0x148
    float* TransformPoint4(float* out, const float* in);   // 0x0095f1c0 (ret 8)
};

struct RenderCtx {                // EA::UTFWin::RenderContext
    void* Begin2D(int flags);     // 0x0095bc10 (ret 4)
};

// A sentinel head whose first member is the list node itself (head.next at
// head+0, head.prev at head+4); `obj` points into the window at its +0x3c head.
struct MNode {
    MNode* next;
    MNode* prev;
};
struct MHead {
    MNode* next;   // +0x00
    MNode* prev;   // +0x04
};

struct HashNode {                 // one bucket entry
    unsigned int mHash;           // +0x00
    char         pad4[0xc];
    HashNode*    mNext;           // +0x10
};

struct HashTable {                // a chained hash table
    char       pad0[4];
    HashNode** mBuckets;          // +0x04
    unsigned   mCount;            // +0x08
    char       padc[0x1c - 0xc];
    void*      mAlloc;            // +0x1c
    int        mPool;             // +0x20
    void Rehash(unsigned int n);  // 0x9605a0
};

// ---- the window -------------------------------------------------------------
struct Window {
    char  pad0[0x28];
    int   m28;                 // +0x28
    int   m2c;                 // +0x2c
    void* m30;                 // +0x30 (mgr)
    int   m34;                 // +0x34
    int   m38;                 // +0x38
    char  pad1[0x60 - 0x3c];
    void* m60;                 // +0x60 (child list sentinel link)
    char  pad1b[0x84 - 0x64];
    float m84, m88, m8c, m90;  // +0x84 real area left/top/right/bottom
    float m94, m98, m9c, mA0;  // +0x94 previous area
    int   mA4;                 // +0xa4
    char  pad2[0x148 - 0xa8];
    float mMat[16];            // +0x148 cached transform
    char  pad3[0x1d8 - 0x188];
    int   m1d8;                // +0x1d8
    int   m1dc;                // +0x1dc (colour / flags)
    int   m1e0;                // +0x1e0 (drawable)
    int   m1e4;                // +0x1e4

    void MoveBy(float dx, float dy);                    // 0x95FF20
    void GrowBy(float dw, float dh);                    // 0x95FF70
    void MoveBy2(float dx, float dy);                   // 0x95FFD0
    void SetA4(int v);                                  // 0x960020
    void Set1E4(void* p);                               // 0x960050
    void OnPaint2();                                    // 0x9600A0
    void CallSlot();                                    // 0x9600D0
    void TransformPoint(float* out, float x, float y);   // 0x960100
    void ScreenToLocal(float* out, float x, float y);    // 0x960180
    void* GetChild(void* out, void* node);              // 0x9601E0
    void RemoveChild(void* node);                       // 0x960230
    void ClearChildren();                               // 0x960280
    int  Dispatch14(void* p);                           // 0x9602C0
    int  Dispatch(void* p);                             // 0x9602F0
    bool OnPaint(RenderCtx* rc);                        // 0x960310
    bool DoMessage(void* msg);                          // 0x960410
    void SetPhysicalArea(const float* r);               // 0x9608C0
    void InvalidateLayout();                            // 0x9609B0
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
    W_s0095_9780* mgr;
    if (mA4 == v)
        return;
    mA4 = v;
    mgr = (W_s0095_9780*)m30;
    if (mgr == 0)
        return;
    (*(void(__stdcall**)(void*, int))((char*)*(void**)mgr - 4))(mgr, (int)((char*)this - 4));
}

// @ 0x00960050
void Window::Set1E4(void* p) {
    if (p != (void*)m1e4) {
        void* old = (void*)m1e4;
        if (p != old) {
            if (p != 0)
                (*(void(__thiscall**)(void*))*(void**)p)(p);
            m1e4 = (int)p;
            if (old != 0)
                (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        (*(void(__thiscall**)(Window*))((char*)*(void**)this + 0x90))(this);
    }
}

// @ 0x009600A0
void Window::OnPaint2() {
    int f = m2c;
    if ((f & 4) == 0) {
        if ((f & 1) != 0 || (m28 & 1) != 0) {
            W_s0095_9780* mgr = (W_s0095_9780*)m30;
            if (mgr != 0)
                mgr->FUN_00958820((char*)this - 4);
        }
    }
}

// @ 0x009600D0
void Window::CallSlot() {
    W_s0095_9780* mgr = (W_s0095_9780*)m30;
    if (mgr != 0)
        (*(void(__stdcall**)(void*, int))((char*)*(void**)mgr - 4))(mgr, (int)((char*)this - 4));
}

// @ 0x00960100
void Window::TransformPoint(float* out, float x, float y) {
    void* mgr = m30;
    if (mgr != 0) {
        char* w = (char*)this - 4;
        char* found = 0;
        do {
            if ((*(unsigned char*)(w + 0x30) & 0x20) != 0)
                found = w;
            w = *(char**)(w + 0x38);
        } while (w != 0);
        if (found != 0)
            FUN_0095AF00(found);
    }
    float in[3];
    in[0] = x;
    in[1] = y;
    in[2] = 0.0f;
    float tmp[3];
    CM* cm = (CM*)((char*)this + 0x148);
    cm->TransformPoint4(tmp, in);
    out[0] = tmp[0];
    out[1] = tmp[1];
}

// @ 0x00960180
void Window::ScreenToLocal(float* out, float x, float y) {
    float pt[2];
    if ((*(bool(__thiscall**)(Window*, float, float, float*))
            ((char*)*(void**)this + 0xc8))(this, x, y, pt)) {
        out[0] = pt[0];
        out[1] = pt[1];
    } else {
        out[0] = 0.0f;
        out[1] = 0.0f;
    }
}

// @ 0x009601E0
void* Window::GetChild(void* out, void* node) {
    char* e;
    if (node == 0)
        e = 0;
    else
        e = (char*)node - 4;
    void* r;
    if (*(char**)(e + 0x38) == (char*)this - 4)
        r = e + 8;
    else
        r = *(void**)(*(void***(__thiscall**)(Window*, void**))
            ((char*)*(void**)this + 0xd0))(this, &node);
    *(void**)out = r;
    return out;
}

// @ 0x00960230
void Window::RemoveChild(void* node) {
    char* e;
    char* v;
    if (node == 0) {
        e = 0;
        v = 0;
    } else {
        e = (char*)node - 4;
        if (e != 0) {
            (*(void(__thiscall**)(char*))*(void**)e)(e);
            v = e + 4;
        } else {
            v = 0;
        }
    }
    (*(void(__thiscall**)(Window*, char*))((char*)*(void**)this + 0xdc))(this, v);
    (*(void(__thiscall**)(char*))((char*)*(void**)e + 0x1c))(e);
    (*(void(__thiscall**)(char*))((char*)*(void**)e + 4))(e);
}

// @ 0x00960280
void Window::ClearChildren() {
    char* head = (char*)this + 0x38;
    while (*(char**)(head + 4) != head) {
        char* v = *(char**)head;
        if (v != 0) {
            v -= 8;
            if (v != 0)
                v += 4;
        } else {
            v = 0;
        }
        (*(void(__thiscall**)(Window*, char*))((char*)*(void**)this + 0xe0))(this, v);
    }
}

// @ 0x009602C0
int Window::Dispatch14(void* p) {
    void* mgr = m30;
    if (mgr == 0)
        return 0;
    Window* self = (this - 1) ? this : 0;
    return (*(int(__thiscall**)(void*, int, Window*, void*))((char*)*(void**)mgr + 0x14))(
        mgr, *(int*)p, self, p);
}

// @ 0x009602F0
int Window::Dispatch(void* p) {
    W_s0095_9780* mgr = (W_s0095_9780*)m30;
    if (mgr != 0)
        return FUN_0095A0B0((char*)this - 4, (int)p);
    return 0;
}

// @ 0x00960310
bool Window::OnPaint(RenderCtx* rc) {
    if ((m1dc & 0xff000000) != 0) {
        void* c = rc->Begin2D(0);
        (*(void(__thiscall**)(void*, int))((char*)*(void**)c + 4))(c, m1dc);
        (*(void(__thiscall**)(void*, float, float, float, float))((char*)*(void**)c + 0x38))(
            c, 0.0f, 0.0f, m90 - m88, m94 - m8c);
    }
    if (m1e0 != 0) {
        int a[4];
        float b[4];
        a[0] = *(int*)((char*)this + 0xac);
        a[1] = 0;
        a[2] = m1dc;
        a[3] = m1d8;
        b[0] = 0.0f;
        b[1] = 0.0f;
        b[2] = m90 - m88;
        b[3] = m94 - m8c;
        (*(void(__thiscall**)(int, RenderCtx*, float*, int*))((char*)*(void**)m1e0 + 0x10))(
            m1e0, rc, b, a);
    }
    return true;
}

// @ 0x00960410
bool Window::DoMessage(void* msg) {
    int kind = *(int*)((char*)msg + 8);
    if (kind == 0xd)
        return (*(bool(__thiscall**)(Window*, int))((char*)*(void**)this + 0x24))(
            this, *(int*)((char*)msg + 0x18));
    if (kind == 0x16) {
        if (m1e0 != 0 && *(int*)((char*)msg + 0xc) == 0)
            return (*(bool(__thiscall**)(int, int, int, int))((char*)*(void**)m1e0 + 0x18))(
                m1e0, *(int*)((char*)msg + 0x18), 0, 0);
        return false;
    }
    if (kind == 0x14 && (((unsigned char*)this)[0x31] & 8) != 0 && m1e0 != 0) {
        float r[4];
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = m90 - m88;
        r[3] = m94 - m8c;
        int a[2];
        a[0] = (int)*(float*)((char*)msg + 0xc);
        a[1] = (int)*(float*)((char*)msg + 0x10);
        int b[4];
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        b[3] = -1;
        *(bool*)(*(int*)((char*)msg + 0x18)) =
            (*(bool(__thiscall**)(int, float*, int*, int*))((char*)*(void**)m1e0 + 0x14))(
                m1e0, r, a, b);
        return true;
    }
    return false;
}

// @ 0x00960550
void* __stdcall AllocPair(void* arg) {
    char* p = (char*)operator_new_size(0xc, (const char*)0x13f2150, 0, 0,
                                       (const char*)0x13ebb38, 0xd1);
    if (p != 0) {
        *(int*)p = *(int*)arg;
        int c = *(int*)((char*)arg + 4);
        *(int*)(p + 4) = c;
        if (c != 0)
            (*(void(__thiscall**)(int))*(void**)c)(c);
    }
    *(int*)(p + 8) = 0;
    return p;
}

// @ 0x009605A0
void HashTable::Rehash(unsigned int n) {
    char* s = (char*)this;
    unsigned int size = n * 4;
    void* allocator = *(void**)(s + 0x1c);
    char* dst = (char*)(*(void*(__thiscall**)(void*, unsigned int, int, int))
        ((char*)*(void**)allocator + 8))(allocator, size + 4, 0, *(int*)(s + 0x20));
    operator_new_arr((unsigned int)dst, 0, size);
    *(unsigned int*)(dst + size) = 0xffffffff;
    for (unsigned int i = 0; i < *(unsigned int*)(s + 8); i++) {
        for (char* node = *(char**)(*(int*)(s + 4) + i * 4); node != 0;
             node = *(char**)(*(int*)(s + 4) + i * 4)) {
            unsigned int idx = *(unsigned int*)node % n;
            char* next = *(char**)(node + 0x10);
            *(void**)(*(int*)(s + 4) + i * 4) = next;
            *(char**)(node + 0x10) = *(char**)(dst + idx * 4);
            *(char**)(dst + idx * 4) = node;
        }
    }
    if (*(unsigned int*)(s + 8) > 1) {
        (*(void(__thiscall**)(void*, void*, unsigned int))
            ((char*)*(void**)*(void**)(s + 0x1c) + 0xc))(
                *(void**)(s + 0x1c), *(void**)(s + 4), *(unsigned int*)(s + 8) * 4 + 4);
    }
    *(void**)(s + 4) = dst;
    *(unsigned int*)(s + 8) = n;
}

// @ 0x00960650
int WindowListMarshaller_Read(void* p1, void* p2, void* p3) {
    (void)p3;
    char* obj = *(char**)((char*)p1 + 4);
    MNode* head = (MNode*)(obj + 0x3c);
    MNode local;
    local.next = &local;
    local.prev = &local;

    while (head->prev != head) {
        char* node = *(char**)(obj + 0x40);
        char* w = node ? node - 8 : 0;
        MNode* n = head->prev;
        n->prev->next = head;
        head->prev = n->prev;
        if (n != head) {
            n->prev = 0;
            n->next = 0;
        }
        if (*(int*)(w + 0x34) != 0)
            (*(W_s0095_9780**)(w + 0x34))->FUN_00959E00(w);
        MNode* ln = (MNode*)(w + 8);
        ln->next = local.next;
        ln->prev = &local;
        local.next = ln;
        ln->next->prev = ln;
        *(int*)(w + 0x38) = 0;
    }

    int count = *(int*)((char*)p2 + 8);
    int* arr = *(int**)((char*)p2 + 4);
    int* p = arr + count - 1;
    while (count != 0) {
        int q = *p;
        p--;
        count--;
        if (q != 0) {
            char* r = (char*)(*(int(__thiscall**)(int, int))
                ((char*)*(void**)q + 0xc))(q, 0xeeee8218);
            if (r != 0) {
                char* w = r - 4;
                MNode* it = local.next;
                int removed = 0;
                if (it != &local) {
                    MNode* target = (MNode*)(r + 4);
                    while (it != target) {
                        it = it->next;
                        if (it == &local)
                            break;
                    }
                    if (it != &local) {
                        it->prev->next = it->next;
                        it->next->prev = it->prev;
                        it->next = 0;
                        it->prev = 0;
                        removed = 1;
                    }
                }
                (*(void(__thiscall**)(char*, char*))
                    ((char*)*(void**)(obj + 4) + 0xd8))(obj + 4, r);
                if (removed)
                    (*(void(__thiscall**)(char*))((char*)*(void**)w + 4))(w);
            }
        }
    }

    char* e = (char*)local.prev;
    while (e != (char*)&local) {
        char* w = e ? e - 8 : 0;
        *(char**)(*(char**)(e + 4)) = (char*)&local;
        *(char**)((char*)&local + 4) = *(char**)(*(char**)((char*)&local + 4) + 4);
        if (e != (char*)&local) {
            *(char**)(e + 4) = 0;
            *(char**)e = 0;
        }
        int fl = (*(int(__thiscall**)(char*))((char*)*(void**)(w + 4) + 0x28))(w + 4);
        if ((fl & 0x200) != 0) {
            (*(void(__thiscall**)(char*, char*))
                ((char*)*(void**)(obj + 4) + 0xd8))(obj + 4, w + 4);
        } else {
            (*(void(__thiscall**)(char*))((char*)*(void**)w + 0x1c))(w);
            (*(void(__thiscall**)(char*))((char*)*(void**)w + 4))(w);
        }
        e = (char*)local.prev;
    }

    char* f = (char*)local.next;
    while (f != (char*)&local) {
        char* nx = *(char**)f;
        *(char**)(f + 4) = 0;
        *(char**)f = 0;
        f = nx;
    }
    return 1;
}

// @ 0x009608C0
void Window::SetPhysicalArea(const float* r) {
    float area[4];
    area[0] = r[0];
    area[1] = r[1];
    area[2] = r[2];
    area[3] = r[3];
    if (m34 != 0) {
        char* obj = (char*)m34 + 4;
        float* prev = (*(float*(__thiscall**)(char*))((char*)*(void**)obj + 0x38))(obj);
        float save[4];
        save[0] = prev[0];
        save[1] = prev[1];
        save[2] = prev[2];
        save[3] = prev[3];
        char* end = *(char**)((char*)this + 0x60);
        for (char* it = (char*)this + 0x60; it != end; it = *(char**)(it + 4)) {
            int ob = *(int*)(*(int*)(it + 4) + 8);
            if (ob != 0) {
                int q = (*(int(__thiscall**)(int, int))((char*)*(void**)ob + 0xc))(
                    ob, 0xcf3df10b);
                if (q != 0) {
                    (*(void(__thiscall**)(int))*(void**)q)(q);
                    (*(void(__thiscall**)(int, float*, float*))((char*)*(void**)q + 0x18))(
                        q, save, area);
                    (*(void(__thiscall**)(int))((char*)*(void**)q + 4))(q);
                }
            }
        }
    }
    (*(void(__thiscall**)(Window*, float*))((char*)*(void**)this + 0x60))(this, area);
}

// @ 0x009609B0
void Window::InvalidateLayout() {
    W_s0095_9780* m = (W_s0095_9780*)m30;
    if (m != 0) {
        float l = m84;
        float t = m88;
        float r = m8c;
        float b = m90;
        char* w = (char*)this - 4;
        m->FUN_00959FE0((int)w);
        m->FUN_009588C0(w);
        m->FUN_009580E0(w);
        if ((r - l) != (m8c - m84) || (b - t) != (m90 - m88)) {
            m->FUN_00958820(w);
            char* head = (char*)this + 0x38;
            for (char* it = *(char**)head; it != head; it = *(char**)it) {
                char* c = it ? it - 8 : 0;
                if ((*(unsigned int*)(c + 0x2c) & 0x800) != 0 ||
                    (*(unsigned char*)(c + 0x31) & 2) != 0) {
                    (*(void(__thiscall**)(char*))((char*)*(void**)(c + 4) + 0x94))(c + 4);
                }
            }
        }
        return;
    }
    m84 = m94;
    m88 = m98;
    m8c = m9c;
    m90 = mA0;
}

// Child-list / layout-link view used by the two recursive flag walkers below.
struct LLink { LLink* next; LLink* prev; };
struct ChildNode { ChildNode* next; ChildNode* prev; };
struct NodeOwner {
    LLink*        m0;          // +0x00
    LLink*        m4;          // +0x04
    ChildNode*    m8;          // +0x08  child-list node (next)
    ChildNode*    mC;          // +0x0c
    LLink*        m10;         // +0x10
    LLink*        m14;         // +0x14
    char          pad18[0x2c - 0x18];
    unsigned int  m2c;         // +0x2c
    unsigned char m30;         // +0x30
    char          pad31[0xb];
    ChildNode*    mHeadNext;   // +0x3c  child-list sentinel (next)
    ChildNode*    mHeadPrev;   // +0x40
    void WalkFlagsUp();    // 0x00960AE0
    void WalkFlagsDown();  // 0x00960B40
};

// @ 0x00960AE0
void NodeOwner::WalkFlagsUp() {
    NodeOwner* self = this;
    unsigned char b = (((self->m2c & 0x400) == 0) && ((self->m30 & 2) == 0)) ? 0 : 1;
    ChildNode* head = (ChildNode*)((char*)self + 0x3c);
    for (ChildNode* it = self->mHeadNext; it != head; it = it->next) {
        NodeOwner* o = it ? (NodeOwner*)((char*)it - 8) : 0;
        unsigned char al = o->m30;
        if (b != (unsigned char)((al >> 1) & 1)) {
            o->m30 = (unsigned char)((((b * 2) ^ al) & 2) ^ al);
            o->WalkFlagsUp();
        }
    }
}

// @ 0x00960B40
void NodeOwner::WalkFlagsDown() {
    NodeOwner* self = this;
    unsigned char al0 = self->m30;
    bool b = !(((al0 & 4) == 0) && (((al0 & 1) != 0) || ((self->m2c & 1) != 0)));
    ChildNode* head = (ChildNode*)((char*)self + 0x3c);
    if (b) {
        for (ChildNode* it = self->mHeadNext; it != head; it = it->next) {
            NodeOwner* o = it ? (NodeOwner*)((char*)it - 8) : 0;
            if ((o->m30 & 4) == 0) {
                o->m30 = (unsigned char)((o->m30 & 0xef) | 4);
                if (o->m14 != 0) {
                    LLink* prev = (LLink*)o->m14;
                    LLink* next = (LLink*)o->m10;
                    prev->next = next;
                    next->prev = prev;
                    o->m10 = 0;
                    o->m14 = 0;
                }
                o->WalkFlagsDown();
            }
        }
    } else {
        for (ChildNode* it = self->mHeadNext; it != head; it = it->next) {
            NodeOwner* o = it ? (NodeOwner*)((char*)it - 8) : 0;
            if ((o->m30 & 4) != 0) {
                o->m30 = (unsigned char)(o->m30 & 0xfb);
                o->WalkFlagsDown();
            }
        }
    }
}
