// Slice s006708d0 - SP UI missing-expansion-pack page + galaxy game-entry message handling.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (same region as s00671840).
#include "types.h"
#include <stdio.h>
#include <intrin.h>

struct VObj { void** vt; };
typedef void   (__thiscall *FnV1)(void*);
typedef void   (__thiscall *FnV2ii)(void*, int, int);
typedef void*  (__thiscall *FnV0)(void*);
typedef void*  (__thiscall *FnV0i)(void*, int);
typedef int    (__thiscall *FnVi0)(void*);
typedef int    (__thiscall *FnVi2ii)(void*, int, int);

void DeleteObj(void* p);                 // 0x00f47380: operator delete

// ---- EA::UTFWinExtras::cXHTMLFrameSet ---------------------------------
struct FrameSet {
    void  Ctor(void* factory);                                   // 0x00996cc0
    void  Dtor();                                                // 0x009968a0
    void  Setup(int a, int b, int c, int d);                     // 0x00996280
    void* GetFrame(unsigned key);                                // 0x00996d40
    bool  CheckWin(void* win, unsigned key);                     // 0x009979f0
    bool  HandleLocationChange(unsigned key, unsigned a, unsigned b, int c); // 0x00997730
    bool  HandleFormSubmit(unsigned a, unsigned b);              // 0x009978b0
};

// globals holding frame keys / error dialog key
extern unsigned g_key_expansion_frame;    // [0x015282e4]
extern char     g_key_xhtml_dialog;       // [0x015285a4]

void FUN_00809db0(int a, void* b);        // 0x00809db0

// ---- SP::cSPUIMissingExpansionPackPage --------------------------------
struct MissingPage {
    void** vt;            // +0x00
    void** vt4;           // +0x04
    int    m8;            // +0x08
    char   fs[0x64];      // +0x0c .. +0x70  (cXHTMLFrameSet)
    void*  mpContentWin;  // +0x70
    void*  mpXHTMLWin;    // +0x74

    MissingPage();
    MissingPage* Destroy(unsigned flags);
    bool Init(void* w);
    bool DoMessage(int unused, int* msg);
    void SetVisibility(int vis);
};

// constructor
// @ 0x006715d0
MissingPage::MissingPage() {
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    m8 = 0;
    ((FrameSet*)((char*)this + 0xc))->Ctor((void*)0x623f40);
    *(void**)this = (void*)0x1400944;
    *(void**)((char*)this + 4) = (void*)0x1400934;
    _ReadWriteBarrier();
    mpContentWin = 0;
    mpXHTMLWin = 0;
    ((FnV1)((VObj*)((char*)this + 0xc))->vt[0])((char*)this + 0xc);
}

// deleting destructor
// @ 0x00671630
MissingPage* MissingPage::Destroy(unsigned flags) {
    *(void**)this = (void*)0x1400944;
    *(void**)((char*)this + 4) = (void*)0x1400934;
    _ReadWriteBarrier();
    if (mpXHTMLWin) ((FnV1)((VObj*)mpXHTMLWin)->vt[1])(mpXHTMLWin);
    if (mpContentWin) ((FnV1)((VObj*)mpContentWin)->vt[1])(mpContentWin);
    ((FrameSet*)((char*)this + 0xc))->Dtor();
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    *(void**)this = (void*)0x13eb938;
    if (flags & 1) DeleteObj(this);
    return this;
}

// @ 0x00671690
bool MissingPage::Init(void* w) {
    void* old = mpContentWin;
    if (w != old) {
        if (w) ((FnV1)((VObj*)w)->vt[0])(w);
        mpContentWin = w;
        if (old) ((FnV1)((VObj*)old)->vt[1])(old);
    }
    if (!mpContentWin) return false;
    ((FrameSet*)((char*)this + 0xc))->Setup(0x1002, 0x1006, 0x1003, 0x1024);
    ((FnV1)((VObj*)w)->vt[0x104 / 4])(w);
    if (!((FrameSet*)((char*)this + 0xc))->CheckWin(w, 0x34a5bc79)) return false;
    void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_key_expansion_frame);
    void* nw = fr ? (char*)fr + 4 : 0;
    void* old2 = mpXHTMLWin;
    if (nw != old2) {
        if (nw) ((FnV1)((VObj*)nw)->vt[0])(nw);
        mpXHTMLWin = nw;
        if (old2) ((FnV1)((VObj*)old2)->vt[1])(old2);
    }
    return mpXHTMLWin != 0;
}

// @ 0x00671760
bool MissingPage::DoMessage(int unused, int* msg) {
    (void)unused;
    if ((void*)msg[0] != mpXHTMLWin) return false;
    int k = msg[2];
    if (k == 0x3326e8a) {
        int* p = (int*)msg[6];
        return ((FrameSet*)((char*)this + 0xc))
            ->HandleLocationChange((unsigned)msg[0], (unsigned)p[0], (unsigned)p[1], 0);
    }
    if (k == 0x3326e8b) {
        return ((FrameSet*)((char*)this + 0xc))
            ->HandleFormSubmit((unsigned)msg[0], (unsigned)msg[6]);
    }
    if (k == 0x43b0aee) {
        FUN_00809db0(0, &g_key_xhtml_dialog);
        return true;
    }
    return false;
}

// @ 0x006717e0
void MissingPage::SetVisibility(int vis) {
    void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_key_expansion_frame);
    if (fr) {
        void* p = (char*)fr + 4;
        ((FnV2ii)((VObj*)p)->vt[0x7c / 4])(p, 1, vis);
    }
    void* x = mpContentWin;
    void* r = (void*)((FnVi2ii)((VObj*)x)->vt[0xf0 / 4])(x, 0x34a5bc7a, 1);
    if (r) ((FnV2ii)((VObj*)r)->vt[0x7c / 4])(r, 1, vis);
}

// ---- 0x006708d0 : SP::cGalaxyGameEntryImpl::DeleteGame (partial) ------
struct BigPage {
    void DeleteGame(int a, int* b);
};
// @ 0x006708d0
void BigPage::DeleteGame(int a, int* b) { (void)a; (void)b; }

// ---- 0x00670eb0 : setup from layout (partial) -------------------------
struct BigPage2 {
    void SetupPage(void* layout, int* a);
};
// @ 0x00670eb0
void BigPage2::SetupPage(void* layout, int* a) { (void)layout; (void)a; }

// ---- 0x00671440 : message handler (complete, non-matching) ------------
struct MsgHandler { unsigned Handle(unsigned msg, int* arg); };

extern int* FUN_0067cb30();
extern bool SP_AddPollinatorDebugInfo(int* a, unsigned* b, int c);
extern unsigned FUN_0066f8e0(int a, int b, unsigned lo, unsigned hi);

// @ 0x00671440
unsigned MsgHandler::Handle(unsigned msg, int* arg) {
    if (msg == 0x1dd7bda9) {
        int flag = (arg[0] == 1);
        int* obj = (int*)arg[1];
        if (!obj) return 0;
        int id = ((FnVi0)((VObj*)obj)->vt[0x10 / 4])(obj);
        if (id == (int)0x86080586) {
            ((BigPage*)((char*)this - 4))->DeleteGame(flag, obj);
        }
        id = ((FnVi0)((VObj*)obj)->vt[0x10 / 4])(obj);
        if (id == 0x3053c62 && obj[3] == 1) {
            unsigned lo = 0xffffffff, hi = 0xffffffff;
            if (sscanf((char*)obj[7], "tag:spore.com,2006:user/%I64u", &lo) == 1) {
                FUN_0066f8e0(flag, (int)obj, lo, hi);
            }
        }
    } else if (msg == 0x9421c619) {
        int a = arg[0], b = arg[1], c = arg[2];
        unsigned lo = 0xffffffff, hi = 0xffffffff;
        FUN_0067cb30();
        if (SP_AddPollinatorDebugInfo(&a, &lo, 0)) {
            int* p = (int*)((char*)this + 0x8c);
            int* q = (int*)((char*)this + 0x14);
            for (int i = 2; i != 0; --i) {
                if ((unsigned)q[0] == lo && (unsigned)q[1] == hi) {
                    if (p[-2]) ((FnV2ii)((VObj*)p[-2])->vt[0x7c / 4])((void*)p[-2], 1, 0);
                    if (*p) ((FnV2ii)((VObj*)*p)->vt[0x7c / 4])((void*)*p, 1, 1);
                }
                ++p;
                q += 10;
            }
        }
    }
    return 0;
}
