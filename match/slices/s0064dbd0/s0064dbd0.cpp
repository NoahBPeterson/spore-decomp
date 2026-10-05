// Slice s0064dbd0: UI module functions around SP::cSPUIAssetComments / cSPUIAssetGrid.
// Built with /O2 (no frame pointer in most functions); UI module (no /EHsc needed).
// Stub interfaces carry only the vtable slots actually used; calls go through
// __thiscall function-pointer casts on the vtable (relocated slot addresses are masked).
#include "../../include/types.h"
#include <intrin.h>

static inline void** VT(void* p) { return *(void***)p; }

// two-base shape shared by the value constructors in this slice
struct PBase1 {
    virtual void pv();
};
struct PBase2 {
    virtual void pv();
    int mRef;
    PBase2() : mRef(0) {}
};

// ---------------------------------------------------------------------------
// stub interfaces / callees (addresses are masked relocations)
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned);
extern "C" int64_t __cdecl StrtoU6416(wchar_t*, int, int);
extern "C" void* __cdecl AuthManager();             // FUN_00607a60
extern "C" void* __cdecl MessageServer();           // FUN_0067dcc0
extern "C" void* __cdecl GetRecorderState();        // FUN_00435e90
extern "C" void* __cdecl AssetBrowser();            // FUN_00401030
extern "C" void* __cdecl SporeGuide();              // FUN_00401040
extern "C" void* __cdecl AppSystem();               // FUN_0067dd00
extern "C" void  __cdecl KillSetiEffects(void*, uint32_t);   // FUN_00435ed0
extern "C" void  __cdecl FUN_809db0(void*, void*);           // FUN_00809db0
extern "C" void  __cdecl FUN_4e0850(void*, const wchar_t*, int64_t);
extern "C" int64_t __cdecl PollenGetURL(uint32_t, void*);    // FUN_006214c0
extern "C" float __cdecl GetElapsedSeconds();       // FUN_00805080
extern "C" void  __cdecl FUN_808230(void*, void*);  // FUN_00808230
extern "C" void  __cdecl FUN_67cab0();
extern "C" void  __cdecl FUN_801380(void*);
extern "C" void  __cdecl FUN_644e20(int);
extern "C" void  __cdecl FUN_645160(void*);
extern "C" void  __cdecl FUN_646260(void*);
extern "C" void  __cdecl FUN_64c0d0(void*);
extern "C" void  __cdecl FUN_64c6b0(void*);
extern "C" void  __cdecl FUN_6448e0(void*);
extern "C" void  __cdecl FUN_644dd0(void*);
extern "C" void  __cdecl FUN_644df0(void*);
extern "C" void  __cdecl FUN_6452c0(void*);
extern "C" void* __cdecl FUN_645300(void*);
extern "C" void  __cdecl FUN_657a30(int, int, int, int, int, void*);
extern "C" void  __cdecl FUN_654100(void*, int, void*);
extern "C" void  __cdecl FUN_64aba0(void*, void*);
extern "C" void  __cdecl FUN_64ab20(void*);
extern "C" void  __cdecl FUN_6478c0(void*);
extern "C" void  __cdecl FUN_93a380(void*, uint32_t, uint32_t);

// Release helper on a sub-object (FUN_00659340), and the XHTML frame set.
struct X659340 { void Release(); };
struct FrameSet {
    void* GetFrame(void* id);                     // FUN_00996d40
    void  Params(int, int, int, int);             // FUN_00996280
    bool  LoadFrame(void* win, uint32_t key);     // FUN_009979f0
    bool  HandleLocationChange(void*, void*, void*, void*); // FUN_00997730
    bool  HandleFormSubmit(void*, void*);         // FUN_009978b0
    void  Construct(void* arg);                   // FUN_00996cc0
    void  Destroy();                              // FUN_009968a0
};

extern void* g_CommentsFrame;          // 0x015258dc
extern void* g_sporeprofile;           // 0x015258e0
extern uint32_t g_sporeprofileLen;     // 0x015f9a28
extern void* g_data15ee298;            // 0x015ee298 (object, field +0x3c)

void* __cdecl EASTL_deallocate(void*);                     // FUN_00f47380

// fabricated vtable symbols (immediates are relocations, masked by cmpobj)
extern char g_vtbl_cSPUIAssetComments_primary[];    // 0x013ff9fc
extern char g_vtbl_cSPUIAssetComments_secondary[];  // 0x013ff9ec
extern char g_vtbl_cSPUIAssetComments_base[];       // 0x013ec458
extern char g_vtbl_cEditorResource[];               // 0x013eb938
extern char g_vtbl_e740_a[];   // 0x013ec458
extern char g_vtbl_e740_b[];   // 0x013ff800
extern char g_vtbl_e740_c[];   // 0x013ff7fc

// ---------------------------------------------------------------------------
// named classes
// ---------------------------------------------------------------------------
namespace SP {

struct cSPUIAssetComments : PBase1, PBase2 {
    char mFrameSet[0x64];     // +0x0c  (retail size)
    void* mpContentWin;       // +0x70
    void* mpXHTMLWin;         // +0x74

    cSPUIAssetComments();
    bool Init(void* win);
    void SetVisibility(int visible);
    bool LoadAssetComments();
    bool DoMessage(void* sender, int* msg);
    void* deleting_dtor(unsigned flags);
};

} // namespace SP

// ---------------------------------------------------------------------------
// @ 0x0064DBD0  SP::cSPEditorNaming::DoMessage  (large /O2 message handler)
// ---------------------------------------------------------------------------
namespace SP {
struct cSPEditorNaming {
    char pad0[0x10];
    bool mIsExpanded;          // +0x10
    bool mAllowNameEdit;       // +0x11
    char pad1[0x14 - 0x12];
    void* mNameGuard;          // +0x14
    void* mLayout;             // +0x18
    void* mpDataProvider;      // +0x1c
    uint32_t mNameType;        // +0x20
    char pad2[0x34 - 0x24];
    void* mOriginalParent;     // +0x34
    char pad3[0x224];
    uint32_t f224;             // +0x224
    char pad4[0x234 - 0x228];
    bool f234;                 // +0x234

    bool DoMessage(void* sender, int* msg);
};
} // namespace SP

bool SP::cSPEditorNaming::DoMessage(void* sender, int* msg)
{
    (void)sender;
    int kind = msg[2];
    // approximate reconstruction of the large hash-switch handler
    if (kind == 1) {
        int a = msg[4];
        int b = msg[5];
        if (mIsExpanded)
            return true;
        if (a == 0x42) {
            if (b != 0 && mNameGuard)
                return false;
        }
        return true;
    }
    if (kind == 0x17) {
        if (mAllowNameEdit)
            return true;
        if (msg[3] == -0xe) {
            FUN_64aba0((char*)this + 0x14c, 0);
            return true;
        }
        if (msg[3] == 0x447060a) {
            FUN_64aba0((char*)this + 0x14c, 0);
            return true;
        }
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0064E170  SP::cSPUIAssetComments::cSPUIAssetComments
// ---------------------------------------------------------------------------
SP::cSPUIAssetComments::cSPUIAssetComments()
{
    ((FrameSet*)((char*)this + 0xc))->Construct((void*)0x623f40);
    mpContentWin = 0;
    mpXHTMLWin = 0;
    _ReadWriteBarrier();
    ((void(__thiscall*)(void*))VT((char*)this + 0xc)[0])((char*)this + 0xc);
}

// ---------------------------------------------------------------------------
// @ 0x0064E1D0  SP::cSPUIAssetComments::`scalar deleting destructor'
// ---------------------------------------------------------------------------
void* SP::cSPUIAssetComments::deleting_dtor(unsigned flags)
{
    *(void**)this = g_vtbl_cSPUIAssetComments_primary;
    *(void**)((char*)this + 4) = g_vtbl_cSPUIAssetComments_secondary;
    _ReadWriteBarrier();
    if (mpXHTMLWin)
        ((void(__thiscall*)(void*))VT(mpXHTMLWin)[1])(mpXHTMLWin);
    if (mpContentWin)
        ((void(__thiscall*)(void*))VT(mpContentWin)[1])(mpContentWin);
    ((FrameSet*)((char*)this + 0xc))->Destroy();
    *(void**)((char*)this + 4) = g_vtbl_cSPUIAssetComments_base;
    *(void**)this = g_vtbl_cEditorResource;
    if (flags & 1)
        EASTL_deallocate(this);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x0064E230  SP::cSPUIAssetComments::Init
// ---------------------------------------------------------------------------
bool SP::cSPUIAssetComments::Init(void* win)
{
    void* old = mpContentWin;
    if (win != old) {
        if (win)
            ((void(__thiscall*)(void*))VT(win)[0])(win);
        mpContentWin = win;
        if (old)
            ((void(__thiscall*)(void*))VT(old)[1])(old);
    }
    if (mpContentWin != 0) {
        ((FrameSet*)((char*)this + 0xc))->Params(0x1002, 0x1006, 0x1003, 0x1024);
        ((void(__thiscall*)(void*, void*))VT(win)[0x104 / 4])(win, this);
        if (((FrameSet*)((char*)this + 0xc))->LoadFrame(win, 0x53f6d0f)) {
            void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_CommentsFrame);
            void* frame = fr ? (char*)fr + 4 : 0;
            void* oldw = mpXHTMLWin;
            if (frame != oldw) {
                if (frame)
                    ((void(__thiscall*)(void*))VT(frame)[0])(frame);
                mpXHTMLWin = frame;
                if (oldw)
                    ((void(__thiscall*)(void*))VT(oldw)[1])(oldw);
            }
            return mpXHTMLWin != 0;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0064E300  SP::cSPUIAssetComments::DoMessage (PDB candidate)
// ---------------------------------------------------------------------------
bool SP::cSPUIAssetComments::DoMessage(void* sender, int* msg)
{
    (void)sender;
    if (*msg != *(int*)((char*)this + 0x74))
        return false;
    int id = msg[2];
    if (id == 0x3326e8a) {
        int* pp = (int*)msg[6];
        if (*pp != 0) {
            if (wcsncmp((const wchar_t*)*pp, (const wchar_t*)g_sporeprofile, g_sporeprofileLen) == 0) {
                wchar_t* rest = (wchar_t*)(*pp + g_sporeprofileLen * 2);
                if (rest) {
                    int64_t parsed = StrtoU6416(rest, 0, 10);
                    void* ms = MessageServer();
                    ((void(__thiscall*)(void*, uint32_t, int64_t*, int))VT(ms)[0x14 / 4])(ms, 0x6299932, &parsed, 0);
                }
            } else {
                return ((FrameSet*)((char*)this + 0xc))->HandleLocationChange((void*)*msg, (void*)*pp, (void*)pp[1], 0);
            }
        }
    } else if (id == 0x3326e8b) {
        void* p6 = (void*)msg[6];
        return ((FrameSet*)((char*)this + 0xc))->HandleFormSubmit((void*)*msg, p6);
    } else if (id == 0x43b0aee) {
        FUN_809db0(0, (void*)0x1525ba4);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0064E400  SP::cSPUIAssetComments::SetVisibility
// ---------------------------------------------------------------------------
void SP::cSPUIAssetComments::SetVisibility(int visible)
{
    void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_CommentsFrame);
    if (fr) {
        void* w = (char*)fr + 4;
        ((void(__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, visible);
    }
    typedef void* (__thiscall *FindFn)(void*, uint32_t, int);
    FindFn fn = (FindFn)VT(mpContentWin)[0xf0 / 4];
    void* w2 = fn(mpContentWin, 0x561dd60, 1);
    if (w2)
        ((void(__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 1, visible);
}

// ---------------------------------------------------------------------------
// @ 0x0064E460  SP::cSPUIAssetComments::LoadAssetComments
// ---------------------------------------------------------------------------
bool SP::cSPUIAssetComments::LoadAssetComments()
{
    void* am = AuthManager();
    char auth = ((char(__thiscall*)(void*))VT(am)[0x24 / 4])(am);
    void* w = ((void*(__thiscall*)(void*, uint32_t, int))VT(mpContentWin)[0xf0 / 4])(mpContentWin, 0x561dd60, 1);
    if (w)
        ((void(__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, auth);
    void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_CommentsFrame);
    if (!fr)
        return false;
    void* frame = (char*)fr + 4;
    ((void(__thiscall*)(void*, int, int))VT(frame)[0x7c / 4])(frame, 1, !auth);
    if (auth)
        return true;

    uint32_t buf[5];
    buf[0] = 0x1667bac;
    buf[1] = 0x1667bac;
    buf[2] = 0x1667bae;
    PollenGetURL(0x53f0df9, buf);
    int64_t val = *(int64_t*)(buf + 4);
    FUN_4e0850(buf + 2, L"%I64u", val);
    void* ms = MessageServer();
    (void)ms;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0064E5B0  small helper: forwards (0x80000000, -1) to a sub-object at +0x168
// ---------------------------------------------------------------------------
struct Sub168 {
    void method(uint32_t a, uint32_t b);
};
struct Outer168 {
    char pad[0x168];
    Sub168 sub;
    void Do();
};
void Outer168::Do()
{
    sub.method(0x80000000, 0xffffffff);
}

// ---------------------------------------------------------------------------
// @ 0x0064E5D0  card-layout cell position helper (SSE float)
// ---------------------------------------------------------------------------
struct CellCalc {
    char pad0[0x104];
    float f104;   // +0x104
    float f108;   // +0x108
    char pad1[4];
    int   n110;   // +0x110
    char pad2[4];
    float f118;   // +0x118
    float f11c;   // +0x11c
    float f120;   // +0x120
    float f124;   // +0x124
    void Compute(int index, float* out);
};
void CellCalc::Compute(int index, float* out)
{
    int n = n110;
    if (n > 0) {
        float t = (f118 + f104) * (float)(index % n);
        int ti = (int)t;
        out[0] = (float)ti + f120;
        float u = (f11c + f108) * (float)(index / n);
        int ui = (int)u;
        out[1] = (float)ui + f124;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0064E680  SP::cSPUIAssetGrid::HandleMessage
// ---------------------------------------------------------------------------
namespace SP {
struct cSPUIAssetGrid {
    char pad0[0x1e2];
    bool f1e2;
    bool f1e3;
    bool HandleMessage(unsigned msg, unsigned arg);
};
}
bool SP::cSPUIAssetGrid::HandleMessage(unsigned msg, unsigned)
{
    switch (msg) {
    case 0xd43aca3c:
    case 0xd4937185:
    case 0xd4937186:
        f1e2 = true;
        f1e3 = true;
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0064E6B0  Rect-ish float equality helper
// ---------------------------------------------------------------------------
struct RectF {
    float a, b, c, d;
    bool Equal() const;
};
bool RectF::Equal() const
{
    return a == c || b == d;
}

// ---------------------------------------------------------------------------
// @ 0x0064E6E0  small value constructor (5 args)
// ---------------------------------------------------------------------------
struct Key3 { int x, y, z; };
struct C_e6e0 {
    Key3 key;          // +0x00
    void* p2;          // +0x0c
    void* p3;          // +0x10
    uint32_t pad[2];   // +0x14
    bool b1;           // +0x1c
    bool b2;           // +0x1d
    C_e6e0(const Key3* src, void* p2, void* p3, bool b1, bool b2);
};
C_e6e0::C_e6e0(const Key3* src, void* p2, void* p3, bool b1, bool b2)
{
    key = *src;
    this->p2 = p2;
    if (p2)
        ((void(__thiscall*)(void*))VT((char*)p2 + 0x10)[0])((char*)p2 + 0x10);
    this->p3 = p3;
    if (p3)
        ((void(__thiscall*)(void*))VT(p3)[0])(p3);
    this->b1 = b1;
    this->b2 = b2;
}

// ---------------------------------------------------------------------------
// @ 0x0064E740  small value constructor (5 args, vtable stores)
// ---------------------------------------------------------------------------
struct C_e740 : PBase1, PBase2 {
    void* p;           // +0x0c
    bool b1;           // +0x10
    char pad1[3];
    int  n;            // +0x14
    bool b2;           // +0x18
    bool b3;           // +0x19
    C_e740(void* p, bool b1, int n, bool b2, bool b3);
};
C_e740::C_e740(void* p, bool b1, int n, bool b2, bool b3)
{
    this->p = p;
    if (p)
        ((void(__thiscall*)(void*))VT(p)[0])(p);
    this->b1 = b1;
    this->b3 = b3;
    this->n = n;
    this->b2 = b2;
}

// ---------------------------------------------------------------------------
// @ 0x0064E7A0  release helper
// ---------------------------------------------------------------------------
struct Node7a0 {
    char pad0[0x10];
    void* child;       // +0x10
};
struct R7a0 {
    char pad0[0xfc];
    Node7a0* p;        // +0xfc
    bool b100;         // +0x100
    void Reset();
};
void R7a0::Reset()
{
    if (p) {
        if (p->child)
            ((X659340*)p->child)->Release();
        p = 0;
    }
    b100 = false;
}

// ---------------------------------------------------------------------------
// @ 0x0064E7D0  visibility/bounds predicate (SSE float)
// ---------------------------------------------------------------------------
struct R7d0 {
    char pad0[0x18c];
    void* obj18c;      // +0x18c
    bool Test(uint32_t idx);
};
bool R7d0::Test(uint32_t idx)
{
    if (idx < (uint32_t)((*(int*)((char*)this + 0xec) - *(int*)((char*)this + 0xe8)) >> 5)
        && *(int*)((char*)this + 0x2c) != 0) {
        float f1 = *(float*)((char*)this + 0x108);
        float f2 = *(float*)(*(int*)((char*)this + 0xe8) + idx * 0x20 + 0x18);
        float f3 = *(float*)((char*)this + 0x184);
        void* o = *(void**)((char*)obj18c + 0x10);
        void* r = ((void*(__thiscall*)(void*, float, float))VT(o)[0x38 / 4])(o, f1 + f2, f2);
        if (f3 <= f1 + f2) {
            float hi = *(float*)((char*)r + 0xc) - *(float*)((char*)r + 4) + f3;
            if (f2 <= hi)
                return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0064E880  loading-indicator window updater
// ---------------------------------------------------------------------------
struct R880 {
    char pad0[0x2c];
    void* w2c;   // +0x2c
    void* w30;   // +0x30
    void* w34;   // +0x34
    void* w38;   // +0x38
    void Update(bool visible, uint32_t arg);
};
void R880::Update(bool visible, uint32_t arg)
{
    if (w30) {
        ((void(__thiscall*)(void*, int, int))VT(w30)[0x7c / 4])(w30, 1, visible);
        if (visible) {
            if (w38) {
                *(uint32_t*)((char*)g_data15ee298 + 0x3c) = arg;
                (void)w38;
            }
            if (w34) {
                float t = GetElapsedSeconds() * -2.0f;
                float v[4];
                v[0] = 0.0f; v[1] = 0.0f; v[2] = t; v[3] = 1.0f;
                FUN_808230(w34, v);
            }
        }
    }
    if (w2c)
        ((void(__thiscall*)(void*, int, int))VT(w2c)[0x7c / 4])(w2c, 1, !visible);
}

// ---------------------------------------------------------------------------
// @ 0x0064E980  scroll-bar layout helper
// ---------------------------------------------------------------------------
struct R980 {
    char pad0[0x3c];
    void* a3c;   // +0x3c
    void* a40;   // +0x40
    void* a44;   // +0x44
    void Layout(void* s1, void* s2, void* s3, bool flag);
};
void R980::Layout(void* s1, void* s2, void* s3, bool flag)
{
    if (a3c) {
        if (!s1) s1 = (void*)0x13ec468;
        ((void(__thiscall*)(void*, void*))VT(a3c)[0x80 / 4])(a3c, s1);
    }
    if (a40) {
        if (!s2) s2 = (void*)0x13ec468;
        ((void(__thiscall*)(void*, void*))VT(a40)[0x80 / 4])(a40, s2);
    }
    if (a44) {
        if (!s3) s3 = (void*)0x13ec468;
        ((void(__thiscall*)(void*, void*))VT(a44)[0x80 / 4])(a44, s3);
    }
    void* pa = a3c ? ((void*(__thiscall*)(void*, uint32_t))VT(a3c)[0xc / 4])(a3c, 0xf15f4bd) : 0;
    void* pb = a40 ? ((void*(__thiscall*)(void*, uint32_t))VT(a40)[0xc / 4])(a40, 0xf15f4bd) : 0;
    void* pc = a44 ? ((void*(__thiscall*)(void*, uint32_t))VT(a44)[0xc / 4])(a44, 0xf15f4bd) : 0;
    float tmp[4];
    ((void(__thiscall*)(void*, float*, int, int))VT(pa)[0x20 / 4])(pa, tmp, 0, 1);
    float x = tmp[2] + 30.0f;
    ((void(__thiscall*)(void*, float, float))VT(a44)[0x70 / 4])(a44, x, tmp[3]);
    ((void(__thiscall*)(void*, float*, int, int))VT(pc)[0x20 / 4])(pc, tmp, 0, 1);
    float x2 = tmp[2] + 30.0f;
    ((void(__thiscall*)(void*, float, float))VT(a40)[0x70 / 4])(a40, x2, tmp[3]);
    void* src = flag
        ? ((void*(__thiscall*)(void*))VT(pb)[0x24 / 4])(pb)
        : ((void*(__thiscall*)(void*))VT(pa)[0x24 / 4])(pa);
    ((void(__thiscall*)(void*, void*))VT(pc)[0x28 / 4])(pc, src);
}

// ---------------------------------------------------------------------------
// @ 0x0064EAF0  child-window visibility setter
// ---------------------------------------------------------------------------
struct Eaf0 {
    char pad0[0x14];
    bool m14;          // +0x14
    char pad1[7];
    void* m1c;         // +0x1c
    void* m20;         // +0x20
    void* m24;         // +0x24
    char pad2[0x10c - 0x28];
    bool m10c;         // +0x10c
    void SetVisible(bool b);
};
void Eaf0::SetVisible(bool b)
{
    m14 = b;
    if (m1c)
        ((void(__thiscall*)(void*, int, bool))VT(m1c)[0x7c / 4])(m1c, 1, b);
    if (m20)
        ((void(__thiscall*)(void*, int, bool))VT(m20)[0x7c / 4])(m20, 1, b);
    if (m24)
        ((void(__thiscall*)(void*, int, bool))VT(m24)[0x7c / 4])(m24, 1, b);
    if (!b && m10c) {
        void* a = AppSystem();
        ((void(__thiscall*)(void*, int))VT(a)[0x40 / 4])(a, 0);
        m10c = false;
    }
}
