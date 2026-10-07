// Slice s00960be0 -- EA::UTFWin::Window flag / geometry / serialization helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- stubs
struct Mat44 {
    float m[16];
    float* TransformPoint3(float* out, const float* v);          // 0x95eeb0
    float* TransformPoint3NoTrans(float* out, const float* v);   // 0x95efb0
};

struct Transform {
    float m[17];                                                 // 0x44 bytes
    void Invert();                                               // 0x95f620
};

struct Node {
    Node*    next;      // +0x00
    Node*    prev;      // +0x04
    void*    field8;    // +0x08
    unsigned fieldc;    // +0x0c
};

// IUnknown-ish object stored at +0x1dc (and 0x1e0).
struct IUnk {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void QueryInterface(int id, void** out);    // +0x1c
};

// manager-ish object at +0x30 (and +0x34)
struct IMgr {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void SendEvent(int a, int b, void* c, int d);   // +0x10
};

struct Win {
    char   pad_00[0x28];
    unsigned    mFlags28;               // +0x28
    unsigned char mBits2c;              // +0x2c
    unsigned char mBits2d;              // +0x2d
    unsigned char m2e, m2f;
    IMgr*  mpMgr30;                     // +0x30
    void*  mp34;                        // +0x34
    void*  m38;                         // +0x38
    void*  m3c;                         // +0x3c
    char   pad_40[0x20];                // ..0x60
    void*  m60;                         // +0x60
    void*  m64;                         // +0x64
    void*  m68;                         // +0x68
    void*  alloc6c;                     // +0x6c
    unsigned m70;                       // +0x70
    unsigned flag74;                    // +0x74
    char   pad_78[0xc];                 // ..0x84
    float  f84, f88, f8c, f90;          // +0x84
    char   pad_94[0x30];                // ..0xc4
    Transform mXformC4;                 // +0xc4
    Transform mXform108;                // +0x108
    char   pad_14c[0x40];               // ..0x18c
    Mat44  mMat18c;                     // +0x18c
    char   pad_1d0[0xc];                // ..0x1dc
    IUnk*  mpUnk1dc;                    // +0x1dc
    IUnk*  mpUnk1e0;                    // +0x1e0
    char   pad_1e4[0x1c];               // ..0x200

    void  SetUserData(IUnk* p);
    bool  TestHit(float x, float y);
    bool  ScreenToWindow(float x, float y, float* out);
    void  GetId(void** out);
    void  GetIdAddr(void** out);
    void  ListRemove(void* iface);
    void  ListInsert(void* iface);
    void* Find60(void* key);
    void  RecomputeFlags();
    void  NotifyTree();
    void  SerUpdate();
    void* CloneNode(int unused);
    void  SetFlag(unsigned flag, unsigned char on);
    void  Show();
    void  Hide();
    void  DestroyProc(void* proc);
    void  ClearProcs();
    void  PurgeProcs();
    bool  SerUpdateTrue(int unused);
};

// ---------------------------------------------------------------- externs
extern "C" void FUN_008fe6d0(void* a, void* b, void* c);          // 0x8fe6d0
extern "C" void FUN_0095af00(void* p);                              // 0x95af00
extern "C" void FUN_009592a0(void* p);                              // 0x9592a0
extern "C" void FUN_00958110(void* p);                              // 0x958110
extern "C" void FUN_009580e0(void* p);                              // 0x9580e0
extern "C" void FUN_009588c0(void* p);                              // 0x9588c0
extern "C" void FUN_00960b40(void* p);                              // 0x960b40
extern "C" void FUN_00960ae0(void* p);                              // 0x960ae0
extern "C" int  FUN_0095fc50(void* p, int arg);                     // 0x95fc50
extern "C" void FUN_009634b60(void* out, void* a, void* b);         // 0x634b60
extern "C" unsigned g_SerTypeTable[];                               // 0x154eea0

// ---------------------------------------------------------------- 00960be0 (geometry)
// @ 0x00960be0
bool FUN_00960be0(void* self, float* out)
{
    char* p = (char*)self;
    unsigned uVar4 = *(unsigned*)(p + 0x2c) & 0x400;
    if (uVar4 == 0 && (*(unsigned char*)(p + 0x30) & 2) == 0)
        return false;
    bool bVar6 = uVar4 != 0;
    if (bVar6) {
        float f7  = *(float*)(p + 0x90);
        float f9  = *(float*)(p + 0x94);
        float f10 = *(float*)(p + 0x88);
        float f8  = *(float*)(p + 0x8c);
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = f7 - f10;
        out[3] = f9 - f8;
    }
    if ((*(unsigned char*)(p + 0x30) & 2) != 0) {
        float f7  = *(float*)(p + 0x90);
        float f9  = *(float*)(p + 0x88);
        float f10 = *(float*)(p + 0x94);
        float f8  = *(float*)(p + 0x8c);
        float local_18 = -((*(float*)(p + 0x90) - *(float*)(p + 0x88)) * 0.5f);
        float local_14 = -((*(float*)(p + 0x94) - *(float*)(p + 0x8c)) * 0.5f);
        float local_10 = 0.0f;
        float local_c[3];
        float* pf = ((Mat44*)(p + 0xc4))->TransformPoint3(local_c, &local_18);
        local_18 = pf[0] + (f7 + f9) * 0.5f;
        local_14 = pf[1] + (f10 + f8) * 0.5f;
        local_10 = pf[2];
        for (unsigned i = *(unsigned*)(p + 0x38); i != 0; i = *(unsigned*)(i + 0x38)) {
            if ((*(unsigned*)(i + 0x2c) & 0x400) != 0) {
                float a = -local_18;
                float b = -local_14;
                float c = (*(float*)(i + 0x90) - *(float*)(i + 0x88)) + a;
                float d = (*(float*)(i + 0x94) - *(float*)(i + 0x8c)) + b;
                if (!bVar6) {
                    out[0] = a;
                    out[1] = b;
                    out[3] = d;
                    out[2] = c;
                } else if (out[2] <= a || c <= out[0] || out[3] <= b || d <= out[1]) {
                    out[3] = 0.0f;
                    out[1] = 0.0f;
                    out[0] = 0.0f;
                    out[2] = 0.0f;
                } else {
                    if (a < out[0]) a = out[0];
                    out[0] = a;
                    if (b < out[1]) b = out[1];
                    out[1] = b;
                    if (out[2] < c) c = out[2];
                    out[2] = c;
                    float t = out[3];
                    if (d <= out[3]) t = d;
                    out[3] = t;
                }
                bVar6 = true;
            }
            if ((*(unsigned char*)(i + 0x30) & 2) == 0)
                return bVar6;
            float f7b  = *(float*)(i + 0x90);
            float f9b  = *(float*)(i + 0x88);
            float f10b = *(float*)(i + 0x94);
            float f8b  = *(float*)(i + 0x8c);
            local_18 = local_18 - (*(float*)(i + 0x90) - *(float*)(i + 0x88)) * 0.5f;
            local_14 = local_14 - (*(float*)(i + 0x94) - *(float*)(i + 0x8c)) * 0.5f;
            pf = ((Mat44*)(p + 0xc4))->TransformPoint3(local_c, &local_18);
            local_18 = pf[0] + (f7b + f9b) * 0.5f;
            local_14 = pf[1] + (f10b + f8b) * 0.5f;
            local_10 = pf[2];
        }
    }
    return bVar6;
}

// ---------------------------------------------------------------- 00960f20
// @ 0x00960f20
void Win::SetUserData(IUnk* p)
{
    if (p != mpUnk1dc) {
        IUnk* old = mpUnk1dc;
        if (p != old) {
            if (p) p->AddRef();
            mpUnk1dc = p;
            if (old) old->Release();
        }
        void* q = 0;
        if (mpUnk1dc) mpUnk1dc->QueryInterface(0x19c46fb, &q);
        unsigned char bit = (unsigned char)((((q != 0) ? 8 : 0) ^ mBits2d) & 8);
        mBits2d ^= bit;
        if (mpMgr30) {
            int local[3];
            local[0] = 0xe;
            local[1] = 4;
            int self = (this != (Win*)4) ? (int)this : 0;
            (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
                mpMgr30, self, self, local, 0);
        }
    }
}

// ---------------------------------------------------------------- 00960fe0 (hit test)
// @ 0x00960fe0
bool Win::TestHit(float x, float y)
{
    char* p = (char*)this;
    float local_30 = (*(float*)(p + 0x90) - *(float*)(p + 0x88)) * 0.5f;
    float fVar1    = (*(float*)(p + 0x8c) - *(float*)(p + 0x84)) * 0.5f;
    float dx = x - fVar1;  if (dx < 0) dx = -dx;
    float dy = y - local_30; if (dy < 0) dy = -dy;
    if (fVar1 < dx || local_30 < dy)
        return false;
    float rect[4];
    bool cVar2 = FUN_00960be0((char*)this - 4, rect);
    if (cVar2) {
        float b[4];
        b[0] = 0.0f;
        b[1] = 0.0f;
        b[2] = *(float*)(p + 0x8c) - *(float*)(p + 0x84);
        b[3] = *(float*)(p + 0x90) - *(float*)(p + 0x88);
        FUN_009634b60(rect, rect, b);
        if (x < rect[0]) return false;
        if (y < rect[1]) return false;
        if (rect[2] <= x) return false;
        if (rect[3] <= y) return false;
    }
    unsigned char local_31 = 1;
    if (mpMgr30 != 0 &&
        (((*(unsigned char*)(p + 0x28) & 0x20) != 0) || ((*(unsigned char*)(p + 0x2d) & 0xc) != 0))) {
        int local[4];
        local[0] = 0x14;
        local[1] = 0;   // overwritten below with pointer to local_31
        *(float*)((char*)local + 8) = x;
        *(float*)((char*)local + 0xc) = y;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, (int)this, (int)this, local, 0);
    }
    return local_31 != 0;
}

// ---------------------------------------------------------------- 00961150 Window::ScreenToWindow
// @ 0x00961150
bool Win::ScreenToWindow(float x, float y, float* out)
{
    char* p = (char*)this;
    if (mpMgr30) {
        char* eax = p - 4;
        char* q = 0;
        do {
            if (*(unsigned char*)(eax + 0x30) & 0x20) q = eax;
            eax = *(char**)(eax + 0x38);
        } while (eax != 0);
        if (q) FUN_0095af00(q);
    }
    float in0[3];
    in0[0] = x;
    in0[1] = y;
    in0[2] = 0.0f;
    float a[3];
    ((Mat44*)(p + 0x18c))->TransformPoint3(a, in0);
    float in1[3];
    in1[0] = 0.0f;
    in1[1] = 0.0f;
    in1[2] = -1.0f;
    float b[3];
    ((Mat44*)(p + 0x18c))->TransformPoint3NoTrans(b, in1);
    if (b[2] <= 1.1920929e-07f && -1.1920929e-07f <= b[2]) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        return false;
    }
    out[0] = a[0] - b[0] * (a[2] / b[2]);
    out[1] = a[1] - b[1] * (a[2] / b[2]);
    return true;
}

// ---------------------------------------------------------------- 00961260 / 00961270 accessors
// @ 0x00961260
void Win::GetId(void** out)
{
    *out = m38;
}

// @ 0x00961270
void Win::GetIdAddr(void** out)
{
    *out = (void*)&m38;
}

// ---------------------------------------------------------------- 00961280 (list remove)
// @ 0x00961280
void Win::ListRemove(void* iface)
{
    char* ip = (char*)iface;
    if (!iface)
        return;
    unsigned r = (*(unsigned(__thiscall**)(void*))*(void**)ip)(iface);
    if (r != (unsigned)((this != (Win*)4) ? (unsigned)this : 0))
        return;
    char* head = (char*)&m38;
    char* n = (char*)m38;
    char* anchor = ip + 4;
    if ((*(unsigned char*)(ip + 0x28) & 0x40) == 0) {
        if (n == anchor)
            return;
        while (true) {
            char* q = n ? n - 8 : 0;
            if ((*(unsigned char*)(q + 0x2c) & 0x40) == 0)
                break;
            n = *(char**)n;
            if (n == anchor)
                return;
        }
    }
    if (n != anchor) {
        FUN_008fe6d0(n, head, anchor);
        if (*(int*)((char*)this + 0x30) != 0)
            FUN_00958110(mpMgr30);
    }
}

// ---------------------------------------------------------------- 00961300 (list insert)
// @ 0x00961300
void Win::ListInsert(void* iface)
{
    char* ip = (char*)iface;
    if (!iface)
        return;
    unsigned r = (*(unsigned(__thiscall**)(void*))*(void**)ip)(iface);
    if (r != (unsigned)((this != (Win*)4) ? (unsigned)this : 0))
        return;
    char* anchor = ip + 4;
    char* head = (char*)&m38;
    if ((*(unsigned char*)(ip + 0x28) & 0x40) == 0) {
        FUN_008fe6d0(head, head, anchor);
    } else {
        char* n = *(char**)anchor;
        char* i = n;
        for (; i != head; i = *(char**)i) {
            char* q = i ? i - 8 : 0;
            if ((*(unsigned char*)(q + 0x2c) & 0x40) == 0)
                break;
        }
        if (i != anchor) {
            char* edx = *(char**)(ip + 8);
            *(char**)(n + 4) = edx;
            *(char**)edx = n;
            char* e2 = *(char**)(i + 4);
            *(char**)e2 = anchor;
            *(char**)(i + 4) = anchor;
            *(char**)(ip + 8) = e2;
            *(char**)anchor = i;
        }
    }
    if (*(int*)((char*)this + 0x30) != 0)
        FUN_00958110(mpMgr30);
}

// ---------------------------------------------------------------- 009613a0 (list lookup)
// @ 0x009613a0
void* Win::Find60(void* key)
{
    Node* head = (Node*)&m60;
    Node* p = (Node*)m60;
    bool b = (key == 0);
    while (true) {
        if (p == head)
            return 0;
        if (b)
            break;
        b = (p->field8 == key);
        p = p->next;
    }
    return p->field8;
}

// ---------------------------------------------------------------- 009613e0 (flag recompute)
// @ 0x009613e0
void Win::RecomputeFlags()
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    Node* p = *(Node**)(a + 0x64);
    *(unsigned char*)(a + 0x31) &= 0xf9;
    unsigned char bl = 0;
    for (; p != head; p = p->next) {
        unsigned v = p->fieldc;
        if (v & 2)     bl = 1;
        if (v & 0x100) *(unsigned char*)(a + 0x31) |= 2;
        if (v & 0x20)  *(unsigned char*)(a + 0x31) |= 4;
    }
    unsigned char cl = *(unsigned char*)(a + 0x31);
    unsigned char dl = cl & 1;
    if (dl == bl)
        return;
    dl = (unsigned char)((((cl ^ bl) & 1) ^ cl));
    *(unsigned char*)(a + 0x31) = dl;
    if (*(unsigned char*)(a + 0x2c) & 8)
        return;
    if (*(unsigned*)(a + 0x34) == 0)
        return;
    FUN_009592a0(a);
}

// ---------------------------------------------------------------- 00961450 (recursive notify)
// @ 0x00961450
void Win::NotifyTree()
{
    char* a = (char*)this;
    (*(void(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x90))(a + 4);
    Node* head = (Node*)(a + 0x3c);
    for (Node* p = *(Node**)(a + 0x3c); p != head; p = p->next) {
        char* q = p ? (char*)p - 8 : 0;
        if (((*(unsigned char*)(q + 0x30) & 1) != 0) || ((*(unsigned char*)(q + 0x2c) & 1) != 0))
            ((Win*)q)->NotifyTree();
    }
}

// ---------------------------------------------------------------- 009614a0 Window::SerUpdate
// @ 0x009614a0
void Win::SerUpdate()
{
    char* a = (char*)this;
    float* src = (float*)(a + 0xc4);
    float* dst = (float*)(a + 0x108);
    for (int i = 0; i < 0x11; i++)
        dst[i] = src[i];
    ((Transform*)dst)->Invert();
    void* q = 0;
    if (mpUnk1e0)
        mpUnk1e0->QueryInterface(0x19c46fb, &q);
    unsigned char bit = (unsigned char)((((q != 0) ? 8 : 0) ^ *(unsigned char*)(a + 0x31)) & 8);
    *(unsigned char*)(a + 0x31) ^= bit;
    void* m34 = *(void**)(a + 0x34);
    if (m34 == 0) {
        *(float*)(a + 0x88) = *(float*)(a + 0x98);
        *(float*)(a + 0x8c) = *(float*)(a + 0x9c);
        *(float*)(a + 0x90) = *(float*)(a + 0xa0);
        *(float*)(a + 0x94) = *(float*)(a + 0xa4);
        return;
    }
    if (*(unsigned char*)(a + 0x2c) & 1) {
        unsigned r = (*(unsigned(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x14))(a + 4);
        if (r != 0) {
            NotifyTree();
            goto lab;
        }
    }
    (*(void(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x90))(a + 4);
lab:
    FUN_009580e0(m34);
    FUN_009588c0(m34);
    FUN_00958110(m34);
    (*(void(__thiscall**)(char*))((char*)*(void**)(a + 4) + 0x94))(a + 4);
    int local[3];
    local[0] = 0xe;
    local[1] = -1;
    (*(void(__thiscall**)(void*, char*, char*, int*, int))((char*)*(void**)m34 + 0x10))(
        m34, a + 4, a + 4, local, 0);
}

// ---------------------------------------------------------------- 00961680 (node clone)
// @ 0x00961680
void* Win::CloneNode(int unused)
{
    (void)unused;
    char* p = (char*)this;
    char* src = *(char**)(p + 0x20);
    void* alloc = *(void**)(p + 0x1c);
    char* obj = (char*)(*(void*(__thiscall**)(void*, int, int, void*))((char*)*(void**)alloc + 8))(
        alloc, 0x18, 0, src);
    if (obj) {
        *(unsigned*)obj = *(unsigned*)src;
        *(unsigned*)(obj + 4) = *(unsigned*)(src + 4);
        void* q = *(void**)(src + 8);
        *(void**)(obj + 8) = q;
        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
        q = *(void**)(src + 0xc);
        *(void**)(obj + 0xc) = q;
        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
    }
    *(unsigned*)(obj + 0x10) = 0;
    return obj;
}

// ---------------------------------------------------------------- 009616f0 (build serialization table)
// @ 0x009616f0
bool FUN_009616f0(unsigned* param_1, void* param_2, char* param_3, void* param_4)
{
    (void)param_2;
    unsigned* lp = (unsigned*)((char*)param_1[1] + 0x64);
    unsigned* lhead = lp;
    unsigned count = 0;
    for (unsigned* p = (unsigned*)*lp; p != lhead; p = (unsigned*)*p)
        count++;
    param_1[2] = count;
    unsigned* arr = (unsigned*)(*(void*(__thiscall**)(void*, unsigned, int))*(void**)param_4)(
        param_4, count * 4, 4);
    param_1[1] = (unsigned)arr;
    param_1[0] = g_SerTypeTable[(*(unsigned short*)(param_3 + 0xc)) & 0xfff];
    if (arr == 0)
        return false;
    for (unsigned* p = (unsigned*)*lhead; p != lhead; p = (unsigned*)*p) {
        *arr = p[2];
        arr++;
    }
    return true;
}

// ---------------------------------------------------------------- 00961760 Window::SetFlag
// @ 0x00961760
void Win::SetFlag(unsigned flag, unsigned char on)
{
    char* a = (char*)this;
    unsigned old = mFlags28;
    unsigned nv = ~flag & old;
    if (on) nv |= flag;
    if (nv == old)
        return;
    mFlags28 = nv;
    if (flag < 9) {
        if (flag == 8) {
            if ((mBits2d & 1) != 0)
                goto lab;
            if (mpMgr30 != 0)
                FUN_009592a0(a);
            goto lab;
        }
        if (flag == 1) {
            if ((mBits2c & 4) == 0) {
                FUN_00960b40(a - 4);
                if (!on) FUN_0095fc50(a - 4, 1);
                NotifyTree();
                if (mpMgr30 != 0)
                    FUN_00958110(mpMgr30);
            }
            goto lab;
        }
        if (flag != 2)
            goto lab;
        if (!on) FUN_0095fc50(a - 4, 1);
    } else if (flag != 0x400) {
        goto lab;
    }
    FUN_00960ae0(a - 4);
    NotifyTree();
lab:
    if (mpMgr30 != 0) {
        int local[3];
        local[0] = 0xe;
        local[1] = 1;
        local[2] = (int)old;
        int self = (this != (Win*)4) ? (int)this : 0;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, self, self, local, 0);
    }
}

// ---------------------------------------------------------------- 00961860 (show)
// @ 0x00961860
void Win::Show()
{
    char* a = (char*)this;
    if (*(unsigned char*)(a + 0x2c) & 1)
        return;
    if (((*(unsigned char*)(a + 0x28) & 1) == 0) && mpMgr30 != 0)
        FUN_00958110(mpMgr30);
    *(unsigned char*)(a + 0x2c) |= 1;
    FUN_00960b40(a - 4);
    NotifyTree();
    if (mpMgr30 != 0) {
        int local[3];
        local[0] = 0xf;
        local[1] = *(unsigned char*)(a + 0x2c) & 1;
        int self = (this != (Win*)4) ? (int)this : 0;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, self, self, local, 0);
    }
}

// ---------------------------------------------------------------- 009618e0 (hide)
// @ 0x009618e0
void Win::Hide()
{
    char* a = (char*)this;
    if ((*(unsigned char*)(a + 0x2c) & 1) == 0)
        return;
    *(unsigned char*)(a + 0x2c) &= 0xfe;
    FUN_00960b40(a - 4);
    if (mpMgr30 != 0)
        FUN_00958110(mpMgr30);
    if (mpMgr30 != 0) {
        int local[3];
        local[0] = 0xf;
        local[1] = *(unsigned char*)(a + 0x2c) & 1;
        int self = (this != (Win*)4) ? (int)this : 0;
        (*(void(__thiscall**)(IMgr*, int, int, int*, int))((char*)*(void**)mpMgr30 + 0x10))(
            mpMgr30, self, self, local, 0);
    }
}

// ---------------------------------------------------------------- 00961990 (destroy winproc entry)
// @ 0x00961990
void Win::DestroyProc(void* proc)
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    Node* p = *(Node**)(a + 0x64);
    if (p == head)
        return;
    while (p->field8 != proc) {
        p = p->next;
        if (p == head)
            return;
    }
    int local[3];
    local[0] = 0x1001;
    (*(void(__thiscall**)(void*, char*, int*))((char*)*(void**)proc + 0x18))(proc, a + 4, local);
    (*(void(__thiscall**)(void*))((char*)*(void**)proc + 4))(proc);
    if (*(int*)(a + 0x74) == 0) {
        Node* nx = p->next;
        Node* pv = p->prev;
        pv->next = nx;
        nx->prev = pv;
        (*(void(__thiscall**)(void*, Node*, int))((char*)*(void**)alloc6c + 0xc))(alloc6c, p, 0x10);
        return;
    }
    p->field8 = (void*)0x154ef48;
    p->fieldc = 0;
}

// ---------------------------------------------------------------- 00961a30
struct Iface4 {
    void DestroyProcAndRecompute(int proc);
};

// @ 0x00961a30
void Iface4::DestroyProcAndRecompute(int proc)
{
    Win* w = (Win*)((char*)this - 4);
    w->DestroyProc((void*)proc);
    w->RecomputeFlags();
}

// ---------------------------------------------------------------- 00961a50 (clear all winprocs)
// @ 0x00961a50
void Win::ClearProcs()
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    for (Node* p = *(Node**)(a + 0x64); p != head; p = p->next) {
        void* proc = p->field8;
        if (proc == (void*)0x154ef48)
            continue;
        int local[3];
        local[0] = 0x1001;
        (*(void(__thiscall**)(void*, char*, int*))((char*)*(void**)proc + 0x18))(proc, a + 4, local);
        (*(void(__thiscall**)(void*))((char*)*(void**)proc + 4))(proc);
        p->field8 = (void*)0x154ef48;
        p->fieldc = 0;
    }
    if (*(int*)(a + 0x74) == 0) {
        Node* p = *(Node**)(a + 0x64);
        while (p != head) {
            Node* nxt = p->next;
            (*(void(__thiscall**)(void*, Node*, int))((char*)*(void**)alloc6c + 0xc))(alloc6c, p, 0x10);
            p = nxt;
        }
        *(void**)(a + 0x64) = (void*)(a + 0x64);
        *(void**)(a + 0x68) = (void*)(a + 0x64);
    }
    RecomputeFlags();
}

// ---------------------------------------------------------------- 00961ae0 (purge destroyed entries)
// @ 0x00961ae0
void Win::PurgeProcs()
{
    char* a = (char*)this;
    Node* head = (Node*)(a + 0x64);
    Node* p = *(Node**)(a + 0x64);
    while (p != head) {
        if (p->field8 == (void*)0x154ef48) {
            Node* nxt = p->next;
            Node* pv = p->prev;
            pv->next = nxt;
            nxt->prev = pv;
            (*(void(__thiscall**)(void*, Node*, int))((char*)*(void**)alloc6c + 0xc))(alloc6c, p, 0x10);
            p = nxt;
        } else {
            p = p->next;
        }
    }
}

// ---------------------------------------------------------------- 00961b30
// @ 0x00961b30
bool Win::SerUpdateTrue(int unused)
{
    (void)unused;
    SerUpdate();
    return true;
}

// ---------------------------------------------------------------- 00961b40 (vector-of-lists copy)
// @ 0x00961b40
unsigned* FUN_00961b40(unsigned* dst, unsigned* src)
{
    dst[0] = src[0];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    if (dst[3] != 0) {
        unsigned size = dst[2] * 4;
        void* alloc = (void*)dst[7];
        void* buf = (*(void*(__thiscall**)(void*, unsigned, int, void*))((char*)*(void**)alloc + 8))(
            alloc, size + 4, 0, (void*)dst[8]);
        *(unsigned*)((char*)buf + size) = 0xffffffff;
        dst[1] = (unsigned)buf;
        unsigned idx = 0;
        if (src[2] != 0) {
            do {
                unsigned* slot = (unsigned*)((char*)dst[1] + idx * 4);
                unsigned* node = *(unsigned**)((char*)src[1] + idx * 4);
                for (; node != 0; node = (unsigned*)node[4]) {
                    unsigned* obj = (unsigned*)(*(void*(__thiscall**)(void*, int, int, void*))(
                        (char*)*(void**)alloc + 8))(alloc, 0x18, 0, (void*)dst[8]);
                    if (obj != 0) {
                        obj[0] = node[0];
                        obj[1] = node[1];
                        void* q = (void*)node[2];
                        obj[2] = (unsigned)q;
                        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
                        q = (void*)node[3];
                        obj[3] = (unsigned)q;
                        if (q) (*(void(__thiscall**)(void*))*(void**)q)(q);
                    }
                    obj[4] = 0;
                    *slot = (unsigned)obj;
                    slot = obj + 4;
                }
                idx++;
            } while (idx < src[2]);
        }
        return dst;
    }
    dst[2] = 1;
    dst[1] = 0x154df28;
    dst[3] = 0;
    dst[6] = 0;
    return dst;
}

// ---------------------------------------------------------------- 00961d50
// @ 0x00961d50
bool FUN_00961d50(Win* p)
{
    p->SerUpdate();
    return true;
}
