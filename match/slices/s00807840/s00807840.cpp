// Slice s00807840 (w2g6 #18): SPUIHelpers window image/shader/transform helpers.
#include <math.h>
#pragma intrinsic(fabs)
static __forceinline float AbsF(float x) { return (float)fabs((double)x); }
// 32-bit MSVC 2008 SP1. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" void* FUN_009512c0();
extern "C" void* FUN_009512d0(int, int, const char*, void*);
extern "C" void* FUN_008051b0(int);
extern "C" void* FUN_008055a0(void*);
extern "C" void* GetImageFromLayout(void*, int);             // 0x008061c0
extern "C" char  CreateImageFromResource(void*, void**, char, int, int);  // 0x00806230
extern "C" char  FUN_00806aa0(void*, int, int);              // 0x00806aa0
extern "C" char  FUN_008068d0(void*, int, int);              // 0x008068d0
extern "C" unsigned char FUN_00806db0(void*, void*);         // 0x00806db0
extern "C" void  __fastcall DoErase(void*);                  // 0x008077f0
extern "C" void* SPUIShader_AcquireShaderProxy();            // 0x0082f630
extern "C" char  FUN_0064e6b0();                             // 0x0064e6b0
extern "C" void __fastcall FUN_0095eb00(void* self, int dummy, float angle); // 0x0095eb00
extern "C" void __fastcall FUN_0095ec30(void* self, int dummy, float angle); // 0x0095ec30
extern "C" void __fastcall FUN_0095ed60(void* self, int dummy, float angle); // 0x0095ed60
extern "C" void __fastcall FUN_0095f5c0(void* self, int dummy, void* v, float angle); // 0x0095f5c0
extern "C" void __fastcall FUN_0095ea30(void* self, int dummy, void* v);      // 0x0095ea30
extern "C" void __fastcall FUN_0095e890(void* self, int dummy, void* v);      // 0x0095e890
extern "C" void* SP_PropertyManager();                       // 0x00?????? // 0x0067de30
extern "C" char  SP_GetPropertyAsUint32Array(void*, int, int*, int*);   // 0x006a0840 (equiv t2)
extern "C" int   SP_OpenRecordAsStream(void*, void*);   // 0x00686490 (equiv t2)

struct WindowHelper {
    void* UI_Window_Window();
    void* UI_WinButton_WinButton();
};
struct ImgDrawCtor2 { void* ctor(); };                       // ImageDrawable ctor
struct ButtonDrawCtor { void* ctor(); };                     // ButtonDrawableRadio ctor
struct CbProc {
    char pad[0xc];
    int (*mpFn)(void*, void*, void*);
    void* mpCtx;
    char Invoke(void* a, void* b);
};
struct CbWinProc {
    void* vt0;    // +0x00
    void* vt1;    // +0x04
    int f8;       // +0x08
    void* fC;     // +0x0c
    void* f10;    // +0x10
    void* f14;    // +0x14
    int f18;      // +0x18
};
struct Xform {
    void* vt0;    // +0x00
    void* vt1;    // +0x04
    int f8;       // +0x08
    float fC;     // +0x0c
    float f10;    // +0x10
    float f14;    // +0x14
    float f18;    // +0x18
    float f1c;    // +0x1c
    float f20;    // +0x20
    float f24;    // +0x24
    float f28;    // +0x28
};

extern float DAT_01485720;
extern float DAT_01544384;
extern float DAT_01544388;
extern float DAT_0154438c;
extern float DAT_01544390;
extern void* SYM_13fa72c;
extern void* SYM_14179b8;
extern void* SYM_141799c;
extern void* SYM_1417a68;
extern void* SYM_1417a4c;
extern void* SYM_14178b0;
extern void* SYM_1417874;
extern void* SYM_141785c;
extern void* SYM_141788c;
extern int DAT_0164c4b8;
extern char DAT_0164c598;

typedef uint32_t u32;

#define S(n) virtual void* v##n();
struct W {
    S(00) S(04) S(08) S(0c) S(10) S(14) S(18) S(1c) S(20) S(24) S(28) S(2c) S(30)
    S(34) S(38) S(3c) S(40) S(44) S(48) S(4c) S(50) S(54) S(58) S(5c) S(60)
    S(64) S(68) S(6c) S(70) S(74) S(78) S(7c) S(80) S(84) S(88) S(8c) S(90)
    S(94) S(98) S(9c) S(a0) S(a4) S(a8) S(ac) S(b0) S(b4) S(b8) S(bc) S(c0)
    S(c4) S(c8)
    virtual void  mCc(void*);        // +0xcc
    virtual void* vD0(void*);        // +0xd0
    S(d4) S(d8) S(dc) S(e0) S(e4) S(e8) S(ec) S(f0) S(f4) S(f8) S(fc) S(100)
    virtual void  m104(void*);       // +0x104
};

static inline void* VSlot(void* p, unsigned byteOff) {
    return (void*)&((void**)*(void**)p)[byteOff / 4];
}

struct XAlign { void Update(void*, void*); };
bool VisitWindowTreeDepthFirst(W*, bool (*)(W*, void*), void*);

// Child-window list node: [0] = next, the owning window sits at node + DAT_1440aec.
struct ChildNode { ChildNode* mpNext; };
extern int DAT_1440aec;                       // 0x01440aec (runtime member offset)
struct RectOps { char FUN_0064e6b0(); };      // 0x0064e6b0: empty-rect test (thiscall)
float* FUN_00808370(float* out, W* w, void* flag);

// @ 0x00807840
void FUN_00807840(int a, int b, int c, int d, int e, int f, int g) {
    int key[3];
    key[0] = c; key[1] = a; key[2] = b;
    CreateImageFromResource(&key, (void**)d, (char)e, f, g);
}

// @ 0x00807c70
char FUN_00807c70(W* w, void* layout, int id, int p4) {
    void* img = GetImageFromLayout(layout, id);
    if (img == 0) return 0;
    if (p4 == -1) p4 = 0;
    return FUN_00806aa0(w, (int)img, p4);
}

// @ 0x00807bb0 SPUIHelpers::SetWindowImage
unsigned char SetWindowImage(W* w, void* res, int flag) {
    if (w == 0) return 0;
    float* a = (float*)w->v34();
    float x0 = a[0], y0 = a[1], x1 = a[2], y1 = a[3];
    void* img = 0;
    char c1 = CreateImageFromResource(res, &img, 0, (int)(x1 - x0 + 0.5f), (int)(y1 - y0 + 0.5f));
    char c2 = FUN_008068d0(w, (int)img, flag);
    unsigned char r;
    if (c2 == 0 || c1 == 0) r = 0;
    else r = 1;
    if (img != 0) (*(void(__thiscall**)(void*))VSlot(img, 4))(img);
    return r;
}

// @ 0x00807cb0
unsigned char FUN_00807cb0(W* w, void* res, int idx) {
    if (w == 0) return 0;
    w->v34();
    void* img = 0;
    char c = CreateImageFromResource(res, &img, 0, 0xffffffff, 0xffffffff);
    unsigned char r = 0;
    if (c != 0) r = FUN_00806aa0(w, (int)img, idx);
    if (img != 0) (*(void(__thiscall**)(void*))VSlot(img, 4))(img);
    return r;
}

// @ 0x00807dc0 SPUIHelpers::SetWindowSPShader
void* SetWindowSPShader(W* w, unsigned char flag, void* shader) {
    void* local = 0;
    unsigned char lflag = flag;
    (void)lflag;
    if (shader != 0) {
        (*(void(__thiscall**)(void*))VSlot(shader, 0))(shader);
        local = shader;
    } else {
        void* p = SPUIShader_AcquireShaderProxy();
        void* old = local;
        if (p != old) {
            if (p != 0) (*(void(__thiscall**)(void*))VSlot(p, 0))(p);
            local = p;
            if (old != 0) (*(void(__thiscall**)(void*, int))VSlot(old, 4))(old, 0);
        }
    }
    VisitWindowTreeDepthFirst(w, (bool (*)(W*, void*))FUN_00806db0, &local);
    void* r = local;
    if (local != 0) (*(void(__thiscall**)(void*, int))VSlot(local, 4))(local, 0);
    return r;
}

// @ 0x00807e50 UI::cWindowTransform::cWindowTransform
void* __fastcall WindowTransform_ctor(Xform* t) {
    t->vt1 = &SYM_13fa72c;
    t->fC = 0.0f;
    t->f10 = 0.0f;
    float one = DAT_01485720;
    t->f8 = 0;
    t->vt0 = &SYM_14179b8;
    t->vt1 = &SYM_141799c;
    t->f14 = one;
    t->f18 = one;
    t->f1c = DAT_01544384;
    t->f20 = DAT_01544388;
    t->f24 = DAT_0154438c;
    t->f28 = DAT_01544390;
    return t;
}

// @ 0x00807ed0
char __stdcall FUN_00807ed0(W* w) {
    w->v98();
    w->v90();
    return 0;
}

// @ 0x00807f50
void __fastcall FUN_00807f50(void* self, int dummy, void* a, void* b) {
    (void)a;
    float* f = (float*)self;
    int count = 0;
    unsigned mode = 0;
    if (AbsF(f[7]) > 1.1920929e-07f) { count = 1; }
    if (AbsF(f[8]) > 1.1920929e-07f) { count++; mode = 1; }
    if (AbsF(f[9]) > 1.1920929e-07f) { count++; mode = 2; }
    if (count > 1) mode = 3;
    if (count != 0) {
        switch (mode) {
        case 0: FUN_0095eb00(b, 0, f[10]); return;
        case 1: FUN_0095ec30(b, 0, f[10]); return;
        case 2: FUN_0095ed60(b, 0, f[10]); return;
        case 3: {
            float v[3];
            v[0] = f[7]; v[1] = f[8]; v[2] = f[9];
            FUN_0095f5c0(b, 0, v, f[10] * 0.017453292f);
        }
        }
    }
}

// @ 0x00808050
void XAlign::Update(void* a, void* b) {
    int p = (int)this;
    float* f = (float*)p;
    if (f[5] != 1.0f || f[6] != 1.0f) {
        float v[3];
        v[0] = f[5]; v[1] = f[6]; v[2] = 1.0f;
        FUN_0095ea30(b, 0, v);
    }
    if (f[7] != DAT_01544384 || f[8] != DAT_01544388 || f[9] != DAT_0154438c || f[10] != DAT_01544390) {
        FUN_00807f50(this, 0, a, b);
    }
    if (f[3] != 0.0f || f[4] != 0.0f) {
        float v[3];
        v[0] = f[3]; v[1] = f[4]; v[2] = 1.0f;
        FUN_0095e890(b, 0, v);
    }
}

// @ 0x00808190
void FUN_00808190(W* w, float a, float b) {
    if (w == 0) return;
    Xform* t = (Xform*)FUN_008051b0(0x3ec2e62);
    if (t == 0) {
        void* alloc = FUN_009512c0();
        void* mem = FUN_009512d0(0x2c, 4, "UI/cWindowTransform", alloc);
        t = mem ? (Xform*)WindowTransform_ctor((Xform*)mem) : 0;
        w->m104(t);
    }
    t->f14 = a;
    t->f18 = b;
    w->v98();
}

// @ 0x00808210 SPUIHelpers::SetWindowScale
void SetWindowScale(W* w, float s) {
    FUN_00808190(w, s, s);
}

// @ 0x00808230
void FUN_00808230(W* w, float* v) {
    if (w == 0) return;
    Xform* t = (Xform*)FUN_008051b0(0x3ec2e62);
    if (t == 0) {
        void* alloc = FUN_009512c0();
        void* mem = FUN_009512d0(0x2c, 4, "UI/cWindowTransform", alloc);
        t = mem ? (Xform*)WindowTransform_ctor((Xform*)mem) : 0;
        w->m104(t);
    }
    if (t->f1c != v[0] || t->f20 != v[1] || t->f24 != v[2] || t->f28 != v[3]) {
        t->f1c = v[0]; t->f20 = v[1]; t->f24 = v[2]; t->f28 = v[3];
        w->v98();
    }
}

// @ 0x008082f0
void FUN_008082f0(W* w, float a, float b) {
    if (w == 0) return;
    Xform* t = (Xform*)FUN_008051b0(0x3ec2e62);
    if (t == 0) {
        void* alloc = FUN_009512c0();
        void* mem = FUN_009512d0(0x2c, 4, "UI/cWindowTransform", alloc);
        t = mem ? (Xform*)WindowTransform_ctor((Xform*)mem) : 0;
        w->m104(t);
    }
    t->fC = a;
    t->f10 = b;
    w->v98();
}

// @ 0x00808590
char CbProc::Invoke(void* a, void* b) {
    if (mpFn != 0) return (char)mpFn(a, b, mpCtx);
    return 0;
}

// @ 0x008085d0
void FUN_008085d0(W* w, void* fn, void* ctx, void* a, void* b) {
    if (w == 0 || fn == 0) return;
    void* alloc = FUN_009512c0();
    CbWinProc* p = (CbWinProc*)FUN_009512d0(0x1c, 4, "UI/cCallbackWinProc ", alloc);
    if (p == 0) p = 0;
    else {
        p->vt1 = &SYM_13fa72c;
        p->f8 = 0;
        p->vt0 = &SYM_1417a68;
        p->vt1 = &SYM_1417a4c;
        p->fC = 0;
        p->f10 = 0;
        p->f14 = 0;
        p->f18 = -1;
    }
    p->f14 = a;
    p->f10 = b;
    p->f18 = (int)ctx;
    p->fC = fn;
    w->m104(p);
}

// @ 0x00808660 SPUIHelpers::OpenRecordAsStream
int OpenRecordAsStream(void* key, int* rec, void* stream) {
    int result = -1;
    if ((char)key != 0) {
        void* prop = SP_PropertyManager();
        void* list = 0;
        if (list != 0) (*(void(__thiscall**)(void*, int))VSlot(list, 4))(list, 0);
        char c = (*(char(__thiscall**)(void*, int, void**))VSlot(prop, 0x30))(prop, 0x5c770db7, &list);
        if (c != 0) {
            int count = 0, arr = 0;
            char ok = SP_GetPropertyAsUint32Array(list, rec[1], &count, &arr);
            if (ok != 0 && count > 0) {
                int i = 0;
                do {
                    if (result != -1) break;
                    int u = *(int*)(arr + i * 4);
                    int k[2];
                    k[0] = rec[0];
                    k[1] = rec[1];
                    (void)u;
                    result = SP_OpenRecordAsStream(k, stream);
                    i++;
                } while (i < count);
            }
        }
        if (list != 0) (*(void(__thiscall**)(void*, int))VSlot(list, 4))(list, 0);
        if (result != -1) return result;
    }
    return SP_OpenRecordAsStream(rec, stream);
}

// @ 0x00808780
void FUN_00808780() {
    DoErase(&DAT_0164c598);
    DAT_0164c4b8 = 0;
}

struct ImageDrawableCtor { void* ctor(); };
struct WindowCtor { void* ctor(); };
struct WinButtonCtor { void* ctor(); };
struct ButtonDrawableCtor { void* ctor(); };

// @ 0x00807880
int* FUN_00807880(float* key, float x, float y, void* parent) {
    float v[4];
    W* win = 0;
    void* img = 0;
    ((uint32_t*)v)[0] = ((uint32_t*)key)[0];
    ((uint32_t*)v)[1] = 0x2f7d0004u;
    ((uint32_t*)v)[2] = ((uint32_t*)key)[2];
    CreateImageFromResource(v, &img, 0, 0xffffffff, 0xffffffff);
    if (img != 0) {
        void* alloc = FUN_009512c0();
        void* mem = FUN_009512d0(0x50, 4, "UI/ImageDrawable", alloc);
        int* d = 0;
        if (mem != 0) {
            d = (int*)((ImageDrawableCtor*)mem)->ctor();
            if (d != 0) {
                (*(void(__thiscall**)(void*))VSlot(d, 0))(d);
                (*(void(__thiscall**)(void*, void*))VSlot((char*)d + 0xc, 0x14))((char*)d + 0xc, img);
                void* wa = FUN_009512c0();
                void* wm = FUN_009512d0(0x20c, 4, "UI/Window", wa);
                if (wm != 0) {
                    void* o = ((WindowCtor*)wm)->ctor();
                    if (o != 0) win = (W*)((char*)o + 4);
                }
                if (win != 0) {
                    (*(void(__thiscall**)(void*, int))VSlot(win, 0x54))(win, 0);
                    (*(void(__thiscall**)(void*, int))VSlot(win, 0x50))(win, 0);
                    int b = *(int*)((char*)img + 0x20);
                    int a = *(int*)((char*)img + 0x1c);
                    v[0] = 0.0f;
                    v[1] = 0.0f;
                    v[2] = (float)a;
                    v[3] = (float)b;
                    (*(void(__thiscall**)(void*, float*))VSlot(win, 0x60))(win, v);
                    (*(void(__thiscall**)(void*, float, float))VSlot(win, 0x64))(win, x, y);
                    (*(void(__thiscall**)(void*, int))VSlot(win, 0x5c))(win, -1);
                    (*(void(__thiscall**)(void*, int))VSlot(win, 0xac))(win, 0xffffff);
                    (*(void(__thiscall**)(void*, int, int))VSlot(win, 0x7c))(win, 1, 1);
                    (*(void(__thiscall**)(void*, int, int))VSlot(win, 0x7c))(win, 0x10, 0);
                    (*(void(__thiscall**)(void*, int, int))VSlot(win, 0x7c))(win, 2, 1);
                    (*(void(__thiscall**)(void*, void*))VSlot(win, 0xb0))(win, d);
                    if (parent != 0)
                        (*(void(__thiscall**)(void*, void*))VSlot(parent, 0xd8))(parent, win);
                    (*(void(__thiscall**)(void*))VSlot(win, 0x90))(win);
                }
                (*(void(__thiscall**)(void*))VSlot(d, 4))(d);
            }
        }
    }
    if (img != 0)
        (*(void(__thiscall**)(void*))VSlot(img, 4))(img);
    return (int*)win;
}

// @ 0x00807a50
int* FUN_00807a50(void* p1, int type, void* p3) {
    float local[3];
    local[0] = ((float*)p1)[0];
    local[2] = ((float*)p1)[2];
    local[1] = 0.0f;
    int img = 0;
    CreateImageFromResource(local, (void**)&img, 0, 0xffffffff, 0xffffffff);
    if (img == 0) return 0;
    void* alloc = FUN_009512c0();
    void* d = 0;
    if (type == 3) {
        d = FUN_009512d0(0x18, 4, "UI/ButtonDrawableRadio", alloc);
        if (d != 0) {
            ((ButtonDrawableCtor*)d)->ctor();
            *(void**)d = &SYM_14178b0;
            *(void**)((char*)d + 4) = &SYM_1417874;
            *(void**)((char*)d + 0xc) = &SYM_141785c;
        }
    } else {
        d = FUN_009512d0(0x18, 4, "UI/ButtonDrawableStandard", alloc);
        if (d != 0) {
            ((ButtonDrawableCtor*)d)->ctor();
            *(void**)d = &SYM_141788c;
            *(void**)((char*)d + 4) = &SYM_1417874;
            *(void**)((char*)d + 0xc) = &SYM_141785c;
        }
    }
    int* piVar6 = 0;
    if (d != 0) {
        (*(void(__thiscall**)(void*, void*))VSlot((char*)d + 0xc, 0))((char*)d + 0xc, 0);
        (*(void(__thiscall**)(void*, int))VSlot(d, 0x14))(d, img);
        (*(void(__thiscall**)(void*, void*, int))VSlot(d, 0x14))(d, (void*)img, 0);
        void* wa = FUN_009512c0();
        void* wm = FUN_009512d0(0x888, 4, "UI/WinButton", wa);
        W* btn = 0;
        if (wm != 0) {
            void* o = ((WinButtonCtor*)wm)->ctor();
            btn = o ? (W*)((char*)o + 0x20c) : 0;
        }
        (*(void(__thiscall**)(void*, void*))VSlot(btn, 0x60))(btn, d);
        piVar6 = (int*)btn;
        (*(void(__thiscall**)(void*, int))VSlot(d, 4))(d, 0);
    }
    (void)p3;
    return piVar6;
}

// @ 0x00807d30 SPUIHelpers::VisitWindowTreeDepthFirst
bool VisitWindowTreeDepthFirst(W* w, bool (*fn)(W*, void*), void* ctx) {
    if (!fn(w, ctx)) return 0;
    ChildNode* cur;
    ChildNode* end;
    w->mCc(&cur);
    while (cur != *(ChildNode**)w->vD0(&end)) {
        ChildNode* next = cur->mpNext;
        W* child = (W*)((char*)cur + DAT_1440aec);
        cur = next;
        if (!VisitWindowTreeDepthFirst(child, fn, ctx))
            return 0;
    }
    return 1;
}

// @ 0x00808370
float* FUN_00808370(float* out, W* w, void* flag) {
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    if ((char)flag == 0 || (((int)w->v28()) & 1) != 0) {
        ChildNode* cur;
        ChildNode* end;
        w->mCc(&cur);
        if (cur != *(ChildNode**)w->vD0(&end)) {
            do {
                W* child = (W*)((char*)cur + DAT_1440aec);
                cur = cur->mpNext;
                float r[4];
                FUN_00808370(r, child, flag);
                if (r[0] != r[2] && r[1] != r[3]) {
                    if (((RectOps*)out)->FUN_0064e6b0()) {
                        out[0] = r[0];
                        out[1] = r[1];
                        out[2] = r[2];
                        out[3] = r[3];
                    } else {
                        out[0] = out[0] < r[0] ? out[0] : r[0];
                        out[1] = r[1] < out[1] ? r[1] : out[1];
                        out[2] = out[2] > r[2] ? out[2] : r[2];
                        out[3] = out[3] > r[3] ? out[3] : r[3];
                    }
                }
            } while (cur != *(ChildNode**)w->vD0(&end));
        }
        float* p = (float*)w->v38();
        float x0 = out[0] + p[0];
        float x1 = out[1] + p[1];
        float x2 = out[2] + p[0];
        float x3 = out[3] + p[1];
        out[0] = x0 < p[0] ? x0 : p[0];
        out[1] = x1 < p[1] ? x1 : p[1];
        out[2] = x2 < p[2] ? x2 : p[2];
        out[3] = x3 < p[3] ? x3 : p[3];
    }
    return out;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
