// Slice s00804920 (w2g6 #15), 32-bit MSVC 2008.
// UTFWin::cSPUIFrameSequencer methods + SPUIHelpers wrappers + Rect/allocator helpers.

typedef unsigned int u32;
#include <intrin.h>

extern "C" void* SP_WindowManager();                 // 0x0067caa0
extern "C" void* EA_UTFWin_GetManager();             // 0x00957f30
extern "C" void* EA_Messaging_GetServer();           // 0x00883860
extern "C" void  FUN_00812f70(void*, void*, void*);  // (not called directly; see Helper)
extern "C" void* FUN_009512c0();
extern "C" void* FUN_009512b0(void*);
extern "C" void* FUN_009512d0(int, int, const char*, void*);
extern "C" void* GetDefaultAllocator();
extern "C" void* AllocEAL(int, const char*, int, int, int, int);
extern "C" void  DeallocEAL(void*);
extern "C" int   AddCore(void*, int, int);

static inline void* VSlot(void* p, unsigned byteOff) { return (void*)&((void**)*(void**)p)[byteOff / 4]; }
static inline void* VFn(void* p, unsigned byteOff) { return ((void**)*(void**)p)[byteOff / 4]; }
static inline void AddRefObj(void* p) { (*(void(__thiscall**)(void*))VSlot(p, 0))(p); }
static inline void ReleaseObj(void* p) { (*(void(__thiscall**)(void*))VSlot(p, 4))(p); }

struct Variant { char d[0x10]; void Destruct(int); Variant& operator=(const Variant&); };

struct F4 {
    float x, y, z, w;
    void Bounds(F4* a, F4* b);   // 0x00805530 (this = out)
};

// helper object so `self` lands in ecx (matching the original thiscall callees)
struct Helper {
    void   H70(void*, void*);
    void   Hf0(float, float);
    void   Hc0(int);
    void   H40(void*, float, float, void*);
    void   Hb0();
    float  H70b();
};
struct IWnd {
    void H0();
    void H4();
    int  H30();
    void H5c(int);
    void H90();
};

// ---------------------------------------------------------------------------
// UTFWin::cSPUIFrameSequencer
// ---------------------------------------------------------------------------
struct Sec {
    void** vtable;          // +0x00
    float mTime;            // +0x04
    float mFrameTime;       // +0x08
    float mDuration;        // +0x0c
    float mOOFrameCount;    // +0x10
    float mOOFrameCountPP;  // +0x14
    float mFrameDuration;   // +0x18
    float mOOFrameDuration; // +0x1c
    int mDirection;         // +0x20
    int mEndingMode;        // +0x24
    int mFrameCount;        // +0x28
    int mCurrentFrame;      // +0x2c
    int mLoopCount;         // +0x30
    int mCurrentLoop;       // +0x34
    int mStateFlags;        // +0x38
    void* mpFS;             // +0x3c
    void* mpVisitor;        // +0x40
    Variant mContext;       // +0x44
    int mFlags2;            // +0x54

    bool SetSequence(void* seq);            // 0x00804920
    bool Update();                          // 0x00804ab0
    bool Advance(float, char);              // 0x00804b30
    bool Set(int, Variant*);                // 0x00804e00
};
struct cSPUIFrameSequencer {
    void** vtable;  // +0x00
    int mRefCount;  // +0x04
    Sec sec;        // +0x08
    cSPUIFrameSequencer();
    void* DeletingDtor(char flags);
};

#define SEC_VT(i) ((void**)*(void**)this)[i]
#define SEC_CALL(i) (*(int(__thiscall**)(void*))VSlot(this, (i) * 4))(this)

// 0x00804920
bool Sec::SetSequence(void* seq) {
    Variant local;
    local.d[0] = 0; local.d[4] = 0;
    mpVisitor = 0;
    mContext = local;
    if ((local.d[4] & 4) != 0) local.Destruct(0);
    if (seq != mpFS) {
        mCurrentFrame = 0;
        if (mpFS != 0) {
            int t = (*(int(__thiscall**)(void*))VSlot(mpFS, 0x18))(mpFS);
            mCurrentFrame = t;
            ReleaseObj(mpFS);
        }
        SEC_CALL(0x0a);
        mpFS = seq;
        if (seq != 0) {
            AddRefObj(seq);
            int c = (*(int(__thiscall**)(void*))VSlot(seq, 0x10))(seq);
            mFrameCount = c;
            mOOFrameCount = 1.0f / ((float)c - 1e-05f);
            if (c == 0) mOOFrameCountPP = 1.0f;
            int a = (*(int(__thiscall**)(void*))VSlot(seq, 0x2c))(seq);
            SEC_CALL(0x13);
            (void)a;
            int b = (*(int(__thiscall**)(void*))VSlot(seq, 0x1c))(seq);
            SEC_CALL(0x08);
            (void)b;
            int d = (*(int(__thiscall**)(void*))VSlot(seq, 0x28))(seq);
            SEC_CALL(0x11);
            (void)d;
            int r = SEC_CALL(0x12);
            if (r == 0 && mCurrentFrame != 0) {
                mCurrentFrame = 0;
                (*(void(__thiscall**)(void*, int))VSlot(seq, 0x14))(seq, 0);
                return true;
            }
            if (r == 1 && mCurrentFrame != mFrameCount - 1)
                mCurrentFrame = mFrameCount - 1;
            (*(void(__thiscall**)(void*, int))VSlot(seq, 0x14))(seq, mCurrentFrame);
            return true;
        }
        SEC_CALL(0x13);
        mOOFrameCount = 1.0f;
        SEC_CALL(0x08);
    }
    return true;
}

// 0x00804ab0
bool Sec::Update() {
    SEC_CALL(0x0a);              // zero/reset
    if (SEC_CALL(0x06)) {        // v+0x18
        mStateFlags |= 1;
        int r = SEC_CALL(0x12);  // v+0x48
        if (r == 0 && mCurrentFrame != 0) {
            mCurrentFrame = 0;
        } else {
            int r2 = SEC_CALL(0x12);
            if (r2 == 1 && mCurrentFrame != mFrameCount - 1)
                mCurrentFrame = mFrameCount - 1;
        }
        (*(void(__thiscall**)(void*, int))VSlot(mpFS, 0x14))(mpFS, mCurrentFrame);
    }
    return (bool)SEC_CALL(0x0e); // v+0x38 tail
}

// 0x00804b30
bool Sec::Advance(float dt, char force) {
    bool r38 = (bool)SEC_CALL(0x0e);
    bool r34 = (bool)SEC_CALL(0x0d);
    if ((r38 && r34) || force) {
        // proceed
        int old = mCurrentFrame;
        SEC_CALL(0x12);
        float t = dt + mFrameTime;
        mFrameTime = t;
        int last = SEC_CALL(0x12);
        (void)last;
        if (t > mFrameDuration && t != mFrameDuration) {
            int n = (int)(mOOFrameDuration * t);
            mFrameTime = mFrameTime - (float)n * mFrameDuration;
            if (n > 0 && mFrameCount > 1) {
                int nf = old + n;
                if (mDirection == 0) {
                    if (nf < mFrameCount) mCurrentFrame = nf;
                    else { /* ending mode handling */ }
                } else if (mDirection == 1) {
                    /* ping-pong handling */
                } else if (mDirection == 3) {
                    /* loop-count handling */
                }
            }
        }
        int cur = mCurrentFrame;
        if (old != cur) {
            mCurrentFrame = cur;
            int r = SEC_CALL(0x18);
            if (r == 1 && SEC_CALL(0x1a)) {
                (*(void(__thiscall**)(void*, int))VSlot(mpFS, 0x14))(mpFS, cur);
            } else {
                (*(void(__thiscall**)(void*, int))VSlot(mpFS, 0x14))(mpFS, cur);
            }
        }
    }
    return true;
}

// 0x00804e00
bool Sec::Set(int a, Variant* v) {
    mpVisitor = (void*)a;
    mContext = *v;
    return true;
}

// 0x00804e20
cSPUIFrameSequencer::cSPUIFrameSequencer() {
    mRefCount = 0;
    sec.vtable = (void**)0x1417718;
    vtable = (void**)0x1417804;
    sec.vtable = (void**)0x1417790;
    sec.mLoopCount = 0;    // +0x30
    sec.mCurrentLoop = 0;  // +0x34
    sec.mStateFlags = 0;   // +0x38
    sec.mpFS = 0;          // +0x3c
    sec.mpVisitor = 0;     // +0x40
    sec.mContext.d[0] = 0;
    sec.mContext.d[1] = 0;
    sec.mContext.d[2] = 0;
    sec.mContext.d[3] = 0;
    sec.mFlags2 = 0;
    sec.SetSequence(0);
}

// 0x00804e70
void* cSPUIFrameSequencer::DeletingDtor(char flags) {
    vtable = (void**)0x1417804;
    sec.vtable = (void**)0x1417790;
    _ReadWriteBarrier();
    (*(void(__thiscall**)(void*, int))VSlot(&sec, 0x10))(&sec, 0);
    if ((sec.mFlags2 & 4) != 0) sec.mContext.Destruct(0);
    sec.vtable = (void**)0x13eb938;
    vtable = (void**)0x13ec458;
    if (flags & 1) {
        extern void MultiHeapDelete(void*);
        MultiHeapDelete(this);
    }
    return this;
}

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------
// WindowManager interface stub: slot order matters, only +4 and +0x48 are used.
struct WMgr {
    virtual void  s0();   // +0x00
    virtual void* s1();   // +0x04
    virtual void  s2();   // +0x08
    virtual void  s3();   // +0x0c
    virtual void  s4();   // +0x10
    virtual void  s5();   // +0x14
    virtual void  s6();   // +0x18
    virtual void  s7();   // +0x1c
    virtual void  s8();   // +0x20
    virtual void  s9();   // +0x24
    virtual void  s10();  // +0x28
    virtual void  s11();  // +0x2c
    virtual void  s12();  // +0x30
    virtual void  s13();  // +0x34
    virtual void  s14();  // +0x38
    virtual void  s15();  // +0x3c
    virtual void  s16();  // +0x40
    virtual void  s17();  // +0x44
    virtual void* s18(int); // +0x48
};
static inline void* WMStuff() {
    WMgr* wm = (WMgr*)SP_WindowManager();
    return wm->s1();
}
static inline Helper* WMObj() {
    void* r = WMStuff();
    return r ? (Helper*)((char*)r - 4) : 0;
}

// 0x00804ed0
void HelpWFun(void* p1, void* p2) {
    WMObj()->H70(p1, p2);
}
// 0x00804f10
void HelpFF(float a, float b) {
    WMObj()->Hf0(a, b);
}
// 0x00804f50
void UpdateMouseFocus(int v) {
    WMObj()->Hc0(v);
}
// 0x00804f80
void Help2(void* a, float f, float g, void* b) {
    WMObj()->H40(a, f, g, b);
}
// 0x00804fc0
void SetWindowAlpha(void* w, float a) {
    if (w == 0) return;
    IWnd* p = (IWnd*)w;
    int c = (*(int(__thiscall**)(void*))VSlot(w, 0x30))(w);
    int v = (int)(a * 255.0f);
    if ((c & 0xff000000) != (v << 24)) {
        p->H5c((c & 0xffffff) | (v << 24));
        p->H90();
        (*(void(__thiscall**)(void*))VSlot(w, 0x90))(w);
    }
}
// 0x00805040
float GetAlpha(int* p) {
    if (p == 0) return 1.0f;
    unsigned v = (*(unsigned(__thiscall**)(void*))VSlot(p, 0x30))(p);
    return (float)(v >> 0x18) * 0.0039215689f;
}
// 0x00805080
struct IWin2 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual int  s7();   // +0x1c
};
float GetElapsedSeconds() {
    WMgr* wm = (WMgr*)SP_WindowManager();
    void* r = wm->s1();
    if (r != 0) {
        Helper* self = (Helper*)((char*)r - 4);
        return self->H70b();
    }
    return 0.0f;
}
// 0x008050b0
int WalkAll(int* p) {
    if (p != 0) {
        for (;;) {
            int r = (*(int(__thiscall**)(void*))VSlot(p, 0x28))(p);
            if ((r & 1) == 0) return 0;
            p = (int*)(*(void*(__thiscall**)(void*))VSlot(p, 0x10))(p);
            if (p == 0) return 1;
        }
    }
    return 0;
}
// 0x008050f0
int* WalkFind(int* p) {
    if (p == 0) return 0;
    do {
        int* n = (int*)(*(void*(__thiscall**)(void*))VSlot(p, 0x10))(p);
        if (n != 0) {
            int r = (*(int(__thiscall**)(void*))VSlot(n, 0x1c))(n);
            if (r != 0) return (int*)r;
        }
        p = (int*)(*(void*(__thiscall**)(void*))VSlot(p, 0x10))(p);
    } while (p != 0);
    return 0;
}
// 0x00805150
bool Contains(int* a, int* b) {
    if (a == 0) return false;
    while (b != 0) {
        if (a == b) return true;
        b = (int*)(*(void*(__thiscall**)(void*))VSlot(b, 0x10))(b);
    }
    return false;
}
// 0x00805180
void WinB0() {
    WMObj()->Hb0();
}
// 0x008051b0  (self in edi in the original)
int* FindByKey(int* self, int key) {
    int* n = (int*)((void*(__thiscall*)(void*, int))VFn(self, 0x10c))(self, 0);
    while (n != 0) {
        if (((int(__thiscall*)(void*, int))VFn(n, 0xc))(n, key) != 0) return n;
        n = (int*)((void*(__thiscall*)(void*, void*))VFn(self, 0x10c))(self, n);
    }
    return 0;
}
// 0x00805200
float AttrF14(int* p) {
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0x14);
    }
    return 1.0f;
}
// 0x00805230
float AttrF18(int* p) {
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0x18);
    }
    return 1.0f;
}
// 0x00805260
void* AttrP1c(int* p) {
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return (char*)q + 0x1c;
    }
    return (void*)0x1544384;
}
// 0x00805290
float AttrF0c(int* p) {
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0xc);
    }
    return 0.0f;
}
// 0x008052c0
float AttrF10(int* p) {
    if (p != 0) {
        int* q = FindByKey(p, 0x3ec2e62);
        if (q != 0) return *(float*)((char*)q + 0x10);
    }
    return 0.0f;
}
// 0x00805310
bool CreditsTabInit(int param1, int param2, void** out) {
    char layout[0x18];
    extern void LayoutCtor(char*);
    extern bool LayoutInit(char*, int, int, int);
    extern void LayoutDtor(char*);
    extern void* LayoutFindById(char*, int, int);
    extern void LayoutShutdown(char*, int);
    LayoutCtor(layout);
    if (!LayoutInit(layout, param1, 0, 0x5b598fa)) {
        LayoutDtor(layout);
        return false;
    }
    void* w = LayoutFindById(layout, param2, 1);
    *out = w;
    bool ok;
    if (w == 0) ok = false;
    else {
        AddRefObj(w);
        void* o = (*(void*(__thiscall**)(void*))VSlot(w, 0x10))(w);
        if (o != 0) (*(void(__thiscall**)(void*, void*))VSlot(o, 0xdc))(o, w);
        ok = true;
    }
    LayoutShutdown(layout, 1);
    LayoutDtor(layout);
    return ok;
}
// 0x008053b0
int IsSomething() {
    WMgr* wm = (WMgr*)SP_WindowManager();
    IWin2* p = (IWin2*)wm->s18(0);
    if (p != 0) {
        if (p->s7() == 0x7a7c0bb) return 1;
    }
    return 0;
}
// 0x008053e0
void* AllocCoreBlock(int size) {
    return AllocEAL(size, "UI/FixedAllocationBin/CoreBlock", 0, 0, 0, 0);
}
// 0x00805400
void FreeCoreBlock(void* p) { DeallocEAL(p); _ReadWriteBarrier(); }
// 0x00805410
static void* g_allocGPtr;
void* FixedAlloc(char* self, int size, int a3, int a4) {
    unsigned idx = (((size + 0x13) & 0xfffffff0) >> 4) - 1;
    unsigned* chunk;
    if ((int)idx < 0x9e) {
        char* block = *(char**)(self + 4 + idx * 4);
        while (*(void**)(block + 0x10) == 0) {
            if (!AddCore(block, 0, 0)) {
                *(unsigned*)0 = idx;
                return (void*)4;
            }
        }
        chunk = *(unsigned**)(block + 0x10);
        *(void**)(block + 0x10) = (void*)*chunk;
        *chunk = idx;
        return chunk + 1;
    }
    unsigned aligned = (unsigned)((size + 0x13) & 0xfffffff0);
    unsigned* out = (unsigned*)(*(void*(__thiscall**)(void*, unsigned, int, int))VSlot(g_allocGPtr, 8))(g_allocGPtr, aligned, a3, a4);
    *out = idx;
    return out + 1;
}
// 0x00805490
void CallVt8(int* self, int a, int b, int c) {
    (*(void(__thiscall**)(void*, int, int, int))VSlot(self, 8))(self, a, b, c);
}
// 0x008054b0
void FixedFree(int* self, void* p) {
    int* base = (int*)((char*)p - 4);
    int idx = *base;
    if (idx < 0x9e) {
        char* block = *(char**)((char*)self + 4 + idx * 4);
        *base = *(int*)(block + 0x10);
        *(int**)(block + 0x10) = base;
        return;
    }
    (*(void(__thiscall**)(void*, int*, int))VSlot(*(void**)0x164c4b8, 0xc))(*(void**)0x164c4b8, base, 0);
}
// 0x008054f0
void* g_alloc;
void InitAlloc() {
    g_alloc = GetDefaultAllocator();
    *(void**)0x164c4b8 = g_alloc;
    FUN_009512b0(&g_alloc);
}
// 0x00805510
void* ChooseAlloc(char b) {
    if (b != 0) return FUN_009512c0();
    return GetDefaultAllocator();
}
// 0x00805530
void F4::Bounds(F4* a, F4* b) {
    float ax = a->x, bx = b->x;
    x = (bx > ax) ? ax : bx;
    float ay = a->y, by = b->y;
    y = (by > ay) ? ay : by;
    float az = a->z, bz = b->z;
    z = (az > bz) ? az : bz;
    float aw = a->w, bw = b->w;
    w = (aw > bw) ? aw : bw;
}
// 0x008055c0
int Feq(F4* a, F4* b) {
    if (a->x == b->x && a->y == b->y && a->z == b->z && a->w == b->w) return 1;
    return 0;
}
// 0x00805660
bool ExpandRect(int* p, F4* r) {
    if ((*(int(__thiscall**)(void*))VSlot(p, 0x28))(p) & 1) {
        F4 o;
        extern void GetBounds(F4*, void*, int);
        GetBounds(&o, p, 0);
        if (r->x != r->z) {
            if (r->y != r->w) {
                if (o.x <= r->x) r->x = o.x;
                if (o.y <= r->y) r->y = o.y;
                if (o.z < r->z) o.z = r->z;
                r->z = o.z;
                if (o.w < r->w) o.w = r->w;
                r->w = o.w;
                return true;
            }
        }
        *r = o;
    }
    return true;
}
// 0x00805740  (x87 arc / pie drawing)
void DrawArc(void* self, float cx, float cy, float r, float start, float end,
             float seg, int target, float step, float extra) {
    (void)self; (void)cx; (void)cy; (void)r; (void)start; (void)end;
    (void)seg; (void)target; (void)step; (void)extra;
}
