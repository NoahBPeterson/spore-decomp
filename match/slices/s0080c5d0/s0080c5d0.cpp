// Slice s0080c5d0 (batch w2g6).
// cSPUIInfoLine subsystem (an element type + a tray holding ea::vector<cSPUIInfoLine>)
// plus UTFWin::cSPUILaunchScreenWinProc.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE2 (no frame pointer; SSE scalar float).
//
// Reconstructions that are not byte-exact are documented in partial.txt (approximate)
// or nonmatching.txt (complete but not byte-exact).
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;

// ---- external callees (relocation targets; names are arbitrary) ----
void* __cdecl  GameAlloc(size_t size, const char* name, int, int, const char* file, int line);
void  __cdecl  GameFree(void* p);
void  __stdcall ArrayCopy(void* dst, const void* src, unsigned elemSize, int count, void* copyfn);void  __fastcall ElemCopy28(void* dst, const void* src);
void* __fastcall LayoutCtor(void* self);              // 0x810000
void  __fastcall VecDtorInline(void* self);           // 0x80b8f0
void  __fastcall VecDtorVec(void* self);              // 0x80b930
u8    __fastcall IsActive(void* self);                // 0x80b400
void  __fastcall Setup1(void* self, void* ctx);       // 0x80b4d0
void  __fastcall Setup2(void* self);                  // 0x80b6b0
void  __fastcall Setup3(void* self);                  // 0x80b000
void* __fastcall FindElem(void* self, float, float, void*); // 0x80c520
void* __cdecl  VecEraseMove(void* last, void* end, void* first);   // 0x80cab0
void  __cdecl  VecDestroy(void* first, void* last, void* dst);      // 0x80aee0
void* __cdecl  VecCopyCtor(void* first, void* last, void* dst);     // 0x80cbd0
void  __cdecl  VecMoveBack(void* first, void* last, void* dst);     // 0x80caf0
u32   __cdecl  Shader_GetId();                             // 0x82f6e0
void* __cdecl  SPUIShader_AcquireProxy();                  // 0x82f630
void  __cdecl  SPUIShader_Bind(void*, void*);              // 0x82e670

// ---- generic virtual-call helpers ----
typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void* (__thiscall *VF1)(void*, void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void  (__thiscall *VFIF)(void*, int, float);
typedef void  (__thiscall *VFFv)(void*, float, float);
typedef void  (__thiscall *VFF)(void*, float, float);
static inline void** VT(void* o) { return *(void***)o; }

struct cSPUIInfoLine;

// ---- verbatim-copied prefix of cSPUIInfoLine (0x1c0 bytes at +4) ----
struct LineHead {
    void* f4;
    void* f8;
    u8    v1[0x1b8];
};

// ---- cSPUILayout (external type; AddRef slot 1, Release slot 2) ----
class cSPUILayout { public:
    virtual void v00();
    virtual void AddRef();
    virtual void Release();
    void* __thiscall FindWindowByID(u32 id, int flag);   // 0x8105b0
    u8    __thiscall Init(const u32* key, int a, u32 b); // 0x8120d0
    void  __thiscall Shutdown(int a);                    // 0x811ad0
};

// ---- window reference held by the inline window record (Release slot 1) ----
struct WinRef {
    virtual void v00();
    virtual void Release();                              // vtable +4
};

// ---- 0x34-byte record stored in cSPUIInfoLine::v2 ----
struct WinRec {
    void**  vtbl;        // +0x00 (0x1417cac)
    u8      body[0x28];  // +0x04 .. +0x2c
    WinRef* win;         // +0x2c
    u32     f30;         // +0x30
    WinRec* __thiscall Make(const void* src, void* win);  // 0x80af20
    WinRec* __thiscall CopyFrom(const WinRec* src);       // 0x80af90
};

// ---- inline-storage vector of WinRec (11 elements of 0x34) ----
struct SubVec {
    WinRec* begin;      // +0x00
    WinRec* end;        // +0x04
    WinRec* cap;        // +0x08
    void*   pad0c;      // +0x0c
    void*   alloc;      // +0x10 (points into buf)
    void*   pad14;      // +0x14
    u8      buf[0x23c]; // +0x18
    void __thiscall InitInline();
    void __thiscall CopyRange(void* first, void* last, const void* owner); // 0x80bbe0
    void __thiscall EraseRange(void* first, void* last);                   // 0x80bcf0
    void __thiscall PushBack(WinRec* rec);                                 // 0x80baa0
};

// ---- element type: 0x42c bytes ----
struct cSPUIInfoLine {
    void**        vtbl;        // +0x000
    void*         f4;          // +0x004
    void*         f8;          // +0x008
    u8            v1[0x1b8];   // +0x00c .. +0x1c4 (0xb * 0x28)
    SubVec        v2;          // +0x1c4 .. +0x418
    cSPUILayout*  layout;      // +0x418
    u8            flag41c;     // +0x41c
    u8            pad41d[3];   // +0x41d
    u32           f420;        // +0x420
    f32           f424;        // +0x424
    f32           f428;        // +0x428

    cSPUIInfoLine* __thiscall ctor(const void* src);              // 0x80c840
    cSPUIInfoLine* __thiscall assign(const cSPUIInfoLine* o);     // 0x80c9f0
    cSPUIInfoLine* __thiscall ctor2(const cSPUIInfoLine* o);      // 0x80cb30
};

// ---- the tray: { vtbl, current, layout, ea::vector<InfoLine> } ----
struct InfoVec {
    cSPUIInfoLine* begin;   // +0x00
    cSPUIInfoLine* end;     // +0x04
    cSPUIInfoLine* cap;     // +0x08
    void*          pad0c;   // +0x0c
    void*          alloc;   // +0x10 (inline buffer pointer)

    i32 Count() const { return (i32)((u8*)end - (u8*)begin) / 0x42c; }
    cSPUIInfoLine* __thiscall Erase(cSPUIInfoLine* first, cSPUIInfoLine* last); // 0x80cc10
    void __thiscall Insert(cSPUIInfoLine* pos, const cSPUIInfoLine* val);       // 0x80cc80
};
struct cSPUIInfoLineTray {
    void**          vtbl;     // +0x00
    cSPUIInfoLine*  mCurrent; // +0x04
    cSPUILayout*    mLayout;  // +0x08
    InfoVec         mVec;     // +0x0c

    void  __thiscall Method(void* p, float fA, float fB, void* ctx);      // 0x80c5d0
    void  __thiscall dtor();                                               // 0x80cdd0
    void  __thiscall Add(const void* src);                                 // 0x80ce20
    void* __thiscall ScalarDeletingDtor(u8 flags);                         // 0x80ceb0
};

void __thiscall SubVec::InitInline()
{
    u8* inl = buf;
    alloc = inl;
    end = (WinRec*)inl;
    begin = (WinRec*)inl;
    cap = (WinRec*)(inl + 0x23c);
}

// =========================== function bodies ===========================

static inline f32 MaxF(f32 a, f32 b) { return a < b ? b : a; }
static inline f32 MinF(f32 a, f32 b) { return a < b ? a : b; }

// @ 0x0080c5d0
void __thiscall cSPUIInfoLineTray::Method(void* p, float fA, float fB, void* ctx)
{
    cSPUIInfoLine* old = mCurrent;
    if (p != old) {
        if (p) ((VF0v)VT(p)[0])(p);          // AddRef
        mCurrent = (cSPUIInfoLine*)p;
        if (old) ((VF0v)VT(old)[1])(old);    // Release
    }
    f32 acc = 0.0f;
    for (u32 i = 0, off = 0; i < (u32)mVec.Count(); ++i, off += 0x42c) {
        cSPUIInfoLine* e = (cSPUIInfoLine*)((u8*)mVec.begin + off);
        if (IsActive(e) && e->layout && e->flag41c) {
            void* win = e->layout->FindWindowByID(0x79830aa, 0);
            Setup1(e, ctx);
            Setup2(e);
            Setup3(e);
            if (win) {
                float* r = (float*)((VF0)VT(win)[0x38 / 4])(win);
                f32 d = r[2] - r[0];
                acc = MaxF(acc, d);
            }
        }
    }
    acc = MinF(MaxF(acc, fA), fB);
    f32 pos = 0.0f;
    for (u32 i = 0, off = 0; i < (u32)mVec.Count(); ++i, off += 0x42c) {
        cSPUIInfoLine* e = (cSPUIInfoLine*)((u8*)mVec.begin + off);
        if (!IsActive(e)) continue;
        cSPUIInfoLine* x = (cSPUIInfoLine*)FindElem(e, acc, acc, ctx);
        if (!x) continue;
        ((VF0v)VT(x)[0])(x);                       // AddRef
        void* s = ((VF0)VT(x)[0x10 / 4])(x);
        if (s) {
            void* s2 = ((VF0)VT(x)[0x10 / 4])(x);
            ((VF1v)VT(s2)[0xdc / 4])(s2, x);
        }
        ((VF1v)VT(p)[0xd8 / 4])(p, x);
        ((VFFv)VT(x)[0x70 / 4])(x, 0.0f, pos);
        float* r = (float*)((VF0)VT(x)[0x38 / 4])(x);
        pos += r[3] - r[1];
        ((VF0v)VT(x)[1])(x);                       // Release
    }
    ((VFFv)VT(p)[0x74 / 4])(p, acc, pos);
}


// @ 0x0080c840
cSPUIInfoLine* __thiscall cSPUIInfoLine::ctor(const void* src)
{
    vtbl = (void**)0x1417cb0;
    f4 = *(void* const*)src;
    f8 = *((void* const*)src + 1);
    ArrayCopy(v1, (const u8*)src + 8, 0x28, 0xb, (void*)ElemCopy28);
    v2.InitInline();
    layout = 0;
    flag41c = 1;
    void* w = f4 ? f4 : (void*)0x40464100;
    cSPUILayout* lay = (cSPUILayout*)GameAlloc(0x18, "UI/cSPUIInfoLine", 0, 0, 0, 0);
    if (lay) lay = (cSPUILayout*)LayoutCtor(lay);
    if (lay != layout) {
        if (lay) lay->AddRef();
        cSPUILayout* prev = layout;
        layout = lay;
        if (prev) prev->Release();
    }
    u32 key[3];
    key[0] = (u32)f8;
    key[1] = 0x510a95b;
    key[2] = (u32)w;
    if (!layout->Init(key, 0, 0x5b598fa)) {
        layout->Shutdown(1);
        if (layout) { cSPUILayout* l2 = layout; layout = 0; l2->Release(); }
        flag41c = 0;
    }
    if (layout) {
        for (i32 i = 0; i < 0xb; ++i) {
            u32 id = *(u32*)(v1 + i * 0x28);
            if (id == 0) break;
            void* win = layout->FindWindowByID(id, 1);
            WinRec tmp;
            WinRec* r = tmp.Make(v1 + i * 0x28, win);
            if (v2.end < v2.cap) {
                WinRec* slot = v2.end;
                v2.end = (WinRec*)((u8*)v2.end + 0x34);
                if (slot) slot->CopyFrom(r);
            } else {
                v2.PushBack(r);
            }
            tmp.vtbl = (void**)0x1417cac;
            if (tmp.win) { WinRef* wr = tmp.win; tmp.win = 0; wr->Release(); }
            if (tmp.win) tmp.win->Release();
        }
    }
    return this;
}


// @ 0x0080c9f0
cSPUIInfoLine* __thiscall cSPUIInfoLine::assign(const cSPUIInfoLine* o)
{
    *(LineHead*)&f4 = *(const LineHead*)&o->f4;
    if (&v2 != &o->v2) {
        SubVec& sv = v2;
        sv.EraseRange(sv.begin, sv.end);
        const SubVec& ov = o->v2;
        sv.CopyRange(ov.begin, ov.end, o);
    }
    cSPUILayout* nl = o->layout;
    cSPUILayout* prev = layout;
    if (nl != prev) {
        if (nl) nl->AddRef();
        layout = nl;
        if (prev) prev->Release();
    }
    flag41c = o->flag41c;
    f420 = o->f420;
    f424 = o->f424;
    f428 = o->f428;
    return this;
}


// @ 0x0080cb30
cSPUIInfoLine* __thiscall cSPUIInfoLine::ctor2(const cSPUIInfoLine* o)
{
    vtbl = (void**)0x1417cb0;
    f4 = o->f4;
    f8 = o->f8;
    ArrayCopy(v1, o->v1, 0x28, 0xb, (void*)ElemCopy28);
    v2.InitInline();
    const SubVec& ov = o->v2;
    v2.CopyRange(ov.begin, ov.end, o);
    layout = o->layout;
    if (layout) layout->AddRef();
    flag41c = o->flag41c;
    f420 = 0;
    return this;
}

// @ 0x0080cc10
cSPUIInfoLine* __thiscall InfoVec::Erase(cSPUIInfoLine* first, cSPUIInfoLine* last)
{
    cSPUIInfoLine* p = (cSPUIInfoLine*)VecEraseMove(last, end, first);
    cSPUIInfoLine* e = end;
    while (p < e) {
        ((VF1v)VT(p)[0])(p, 0);
        p = (cSPUIInfoLine*)((u8*)p + 0x42c);
    }
    end -= last - first;
    return first;
}


// @ 0x0080cc80
void __thiscall InfoVec::Insert(cSPUIInfoLine* pos, const cSPUIInfoLine* val)
{
    if (end != cap) {
        cSPUIInfoLine* v = (cSPUIInfoLine*)val;
        if (v >= pos && v < end) v = (cSPUIInfoLine*)((u8*)v + 0x42c);
        if (end) ((cSPUIInfoLine*)end)->ctor2((cSPUIInfoLine*)((u8*)end - 0x42c));
        VecMoveBack(pos, (cSPUIInfoLine*)((u8*)end - 0x42c), end);
        pos->assign(v);
        end = (cSPUIInfoLine*)((u8*)end + 0x42c);
        return;
    }
    i32 n = (i32)((u8*)end - (u8*)begin) / 0x42c;
    u32 newCap = n ? (u32)n * 2 : 1;
    u8* mem;
    if (newCap) mem = (u8*)GameAlloc(newCap * 0x42c, (const char*)0x13f6b3c, 0, 0, (const char*)0x13ebb38, 0xd1);
    else        mem = 0;
    u8* p = (u8*)VecCopyCtor(begin, pos, mem);
    VecDestroy(begin, pos, mem);
    if (p) ((cSPUIInfoLine*)p)->ctor2(val);
    cSPUIInfoLine* e = end;
    u8* p2 = (u8*)VecCopyCtor(pos, e, p + 0x42c);
    VecDestroy(pos, e, p + 0x42c);
    if (begin && begin != (cSPUIInfoLine*)alloc) GameFree(begin);
    begin = (cSPUIInfoLine*)mem;
    end = (cSPUIInfoLine*)p2;
    cap = (cSPUIInfoLine*)(mem + newCap * 0x42c);
}


// @ 0x0080cdd0
void __thiscall cSPUIInfoLineTray::dtor()
{
    if (mLayout) mLayout->Shutdown(1);
    if (mLayout) {
        cSPUILayout* l = mLayout;
        mLayout = 0;
        ((VF0v)VT(l)[2])(l);
    }
    if (mCurrent) {
        cSPUIInfoLine* c = mCurrent;
        mCurrent = 0;
        ((VF0v)VT(c)[1])(c);
    }
    mVec.Erase(mVec.begin, mVec.end);
}

// @ 0x0080ce20
void __thiscall cSPUIInfoLineTray::Add(const void* src)
{
    cSPUIInfoLine tmp;
    cSPUIInfoLine* e = tmp.ctor(src);
    InfoVec* v = &mVec;
    if (v->end < v->cap) {
        cSPUIInfoLine* slot = v->end;
        v->end = (cSPUIInfoLine*)((u8*)slot + 0x42c);
        if (slot) slot->ctor2(e);
    } else {
        v->Insert(v->end, e);
    }
    cSPUILayout* l = tmp.layout;
    tmp.vtbl = (void**)0x1417cb0;
    if (l) { tmp.layout = 0; l->Release(); }
    if (tmp.layout) tmp.layout->Release();
    VecDtorInline(&tmp.v2);
}


// @ 0x0080ceb0
void* __thiscall cSPUIInfoLineTray::ScalarDeletingDtor(u8 flags)
{
    vtbl = (void**)0x1417cb4;
    dtor();
    VecDtorVec(&mVec);
    if (mLayout) ((VF0v)VT(mLayout)[2])(mLayout);
    if (mCurrent) ((VF0v)VT(mCurrent)[1])(mCurrent);
    if (flags & 1) GameFree(this);
    return this;
}

// @ 0x0080d590
void __stdcall SetFlag8(char* p) { p[0x10] = 0; }

// @ 0x0080d5a0
char* __fastcall GetInnerA(char* p) {
    if (p) {
        char* q = p - 0x250;
        if (q) return q + 0xc;
    }
    return 0;
}

struct InnerSetter {
    void __thiscall SetInnerFlag(u8 v);
};
// @ 0x0080d5c0
void InnerSetter::SetInnerFlag(u8 v) {
    char* p = GetInnerA((char*)this);
    if (p) p[0x240] = v;
    else   p[0x24c] = v;
}

// @ 0x0080d5f0
char* __fastcall GetInnerB(char* p) {
    if (p) {
        char* q = p - 0x250;
        if (q) {
            char* c = q + 0xc;
            if (c) return c + 0x54;
        }
    }
    return (char*)0x60;
}

// @ 0x0080d610
char* __fastcall GetInnerBase(char* p) { return p ? p - 0x250 : 0; }

// @ 0x0080d620
u8 __cdecl ShaderBind(void* self, void* arg2) {
    void* p = ((VF0)VT(self)[0x4c / 4])(self);
    if (p == 0 || p == (void*)Shader_GetId()) {
        p = SPUIShader_AcquireProxy();
        ((VF1v)VT(self)[0x8c / 4])(self, p);
    }
    ((VF0v)VT(self)[0x90 / 4])(self);
    SPUIShader_Bind(p, arg2);
    return 1;
}

// ---- window / message stubs for DoMessage (vtable slot = offset / 4) ----
struct Rect4 { float x1, y1, x2, y2; };
struct IWin;
struct WinAux {                       // object returned by IWin slot 0x2a
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual IWin* Query(u32 id);      // 0x0c
};
struct Dims { char pad[0x1c]; int w; int pad2; int h; };   // h at +0x20, w at +0x1c
struct WinInner {                     // object returned by Query(0xef3c47cf)
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5();
    virtual Dims* GetDims();          // 0x18
};
struct IWin {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual IWin* GetParent();                          // 0x10
    virtual void s5();
    virtual void s6();
    virtual u32 GetControlID();                         // 0x1c
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual u32 GetFlagsValue();                        // 0x2c
    virtual void s12(); virtual void s13();
    virtual Rect4* GetArea();                           // 0x38
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void SetShadeColor(u32 c);                  // 0x5c
    virtual void SetArea(Rect4* r);                     // 0x60
    virtual void SetLocation(float x, float y);         // 0x64
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void SetFlag(int flag, int on);             // 0x7c
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void s37();
    virtual void Invalidate();                          // 0x98
    virtual void s39(); virtual void s40(); virtual void s41();
    virtual WinAux* GetAux();                           // 0xa8
    virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50();
    virtual int** ChildBegin(int** out);                // 0xcc
    virtual int** ChildEnd(int** out);                  // 0xd0
    virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59();
    virtual IWin* FindWindowByID(u32 id, int flag);     // 0xf0
};
struct Xform { char pad[0x40]; int dirty; char pad2[0x10]; void __thiscall Scale(const float* v); };  // 0x95ea30
struct WinMsg {
    IWin* source;     // +0
    u32   pad4;
    u32   type;       // +8
    u32   flagsNew;   // +0xc
    u32   flagsOld;   // +0x10
    u32   pad14;
    Xform* xform;     // +0x18
};
extern int gChildNodeOff;   // 0x1440aec: node-to-object offset of the child list

static inline IWin* ChildOf(int* node) { return (IWin*)((char*)node + gChildNodeOff); }

// ================= UTFWin::cSPUILaunchScreenWinProc =================
class cSPUILaunchScreenWinProc { public:
    void** vtbl;   // +0
    void** vtbl2;  // +4
    u32    f8;     // +8
    u32    fC;     // +0xc
    i32    f10;    // +0x10

    cSPUILaunchScreenWinProc* __thiscall ctor();             // 0x80cf00
    u8   __thiscall DoMessage(IWin* window, WinMsg* msg);    // 0x80cf80
};

// @ 0x0080cf00
cSPUILaunchScreenWinProc* __thiscall cSPUILaunchScreenWinProc::ctor()
{
    vtbl2 = (void**)0x13ec458;
    f8 = 0;
    vtbl = (void**)0x1417d14;
    vtbl2 = (void**)0x1417d04;
    fC = 3;
    f10 = -1;
    return this;
}

// @ 0x0080cf80
u8 __thiscall cSPUILaunchScreenWinProc::DoMessage(IWin* window, WinMsg* msg)
{
    u32 type = msg->type;
    if (type == 0x11) {
        IWin* top = window->FindWindowByID(0x279b810, 0);
        if (top) top->SetShadeColor(0xffffff);
        u32 kIds[3] = { 0x279bad0, 0x279bad4, 0 };
        for (const u32* pid = kIds; *pid; ++pid) {
            IWin* c = window->FindWindowByID(*pid, 0);
            Rect4* r = c->GetArea();
            Rect4 local;
            float nx = -r->x1, ny = -r->y1;
            local.x1 = nx + r->x1;
            local.y1 = ny + r->y1;
            local.x2 = r->x2 + nx;
            local.y2 = r->y2 + ny;
            int* tmp1; int* tmp2;
            int* it = *c->ChildBegin(&tmp1);
            if (it != *c->ChildEnd(&tmp2)) {
                float cx = (local.x2 + local.x1) * 0.5f;
                float cy = (local.y2 + local.y1) * 0.5f;
                int* next;
                do {
                    next = (int*)*it;
                    IWin* ch = ChildOf(it);
                    ch->SetFlag(1, ch->GetControlID() == 0x279e540);
                    WinAux* aux = ch->GetAux();
                    if (aux) {
                        WinInner* in = (WinInner*)aux->Query(0xef3c47cf);
                        if (in && in->GetDims()) {
                            int h = in->GetDims()->h;
                            Rect4 sz;
                            sz.x1 = 0.0f;
                            sz.y1 = 0.0f;
                            sz.x2 = (float)in->GetDims()->w;
                            sz.y2 = (float)h;
                            ch->SetArea(&sz);
                        }
                    }
                    Rect4* a = ch->GetArea();
                    ch->SetLocation(a->x1 - ((a->x2 + a->x1) * 0.5f - cx),
                                    a->y1 - ((a->y2 + a->y1) * 0.5f - cy));
                    it = next;
                } while (next != *c->ChildEnd(&tmp2));
            }
        }
        window->SetFlag(1, 0);
        window->Invalidate();
        return 0;
    }
    if (type == 0x12) return 0;
    if (type == 0x287259f6) {
        IWin* src = msg->source;
        if (src->GetControlID() == 0x279b810) {
            IWin* t = window->FindWindowByID(0x279bd58, 0);
            if (t) {
                u8 on = (u8)((src->GetFlagsValue() >> 2) & 1);
                t->SetFlag(1, on);
                if (on) src->SetShadeColor(0xffffffff);
                else    src->SetShadeColor(0xffffff);
                return 0;
            }
        }
        return 0;
    }
    if (type == 0xc) return 0;
    if (type == 0x15) {
        IWin* parent = window->GetParent();
        Rect4 A = *window->GetArea();
        Rect4* P = parent->GetArea();
        float p0 = P->x1, p2 = P->x2, p1 = P->y1, p3 = P->y2;
        window->SetLocation(A.x1 - ((A.x2 + A.x1) * 0.5f - (p2 + p0) * 0.5f),
                            A.y1 - ((A.y2 + A.y1) * 0.5f - (p3 + p1) * 0.5f));
        float sx = (p2 - p0) / (A.x2 - A.x1);
        float sy = (p3 - p1) / (A.y2 - A.y1);
        if (sx > sy) sx = sy;
        float v[3];
        v[0] = sx; v[1] = sx; v[2] = 1.0f;
        msg->xform->Scale(v);
        window->SetFlag(1, 1);
        window->Invalidate();
        return 0;
    }
    if (type == 0x13) {
        if (((msg->flagsOld ^ msg->flagsNew) & 8) == 0) return 0;
        u32 id = msg->source->GetControlID();
        if (id == 0 || id == 0x279b810) return 0;
        u8 on = (u8)((msg->flagsNew >> 3) & 1);
        if (on) f10 = id;
        else if (f10 == (i32)id) f10 = -1;
        u32 kIds[3] = { 0x279bad0, 0x279bad4, 0 };
        for (const u32* pid = kIds; *pid; ++pid) {
            IWin* c = window->FindWindowByID(*pid, 0);
            if (!c) continue;
            int* tmp1; int* tmp2;
            int* it = *c->ChildBegin(&tmp1);
            if (it != *c->ChildEnd(&tmp2)) {
                int* next;
                do {
                    next = (int*)*it;
                    IWin* ch = ChildOf(it);
                    u8 sel = on && ch->GetControlID() == (u32)f10;
                    ch->SetFlag(1, sel);
                    if (!on && f10 < 0 && ch->GetControlID() == 0x279e540)
                        ch->SetFlag(1, 1);
                    it = next;
                } while (next != *c->ChildEnd(&tmp2));
            }
        }
        return 0;
    }
    return 0;
}
