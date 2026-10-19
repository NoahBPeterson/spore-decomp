// src/game/SPEditors/SPUIMissingExpansionPackPage.cpp -- migrated from slice(s) s00671840, s006708d0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIMissingExpansionPackPage.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned g_key_expansion_frame;    // [0x015282e4]
extern char     g_key_xhtml_dialog;       // [0x015285a4]
#include <stdio.h>
#include <intrin.h>
#include "SP/cSPUIMissingExpansionPackPage.h"
#include "SP/cSPUISearchBox.h"
#include "SP/cTribeTool.h"

// ---- items of slice s006708d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void   (__thiscall *FnV1)(void*);
typedef void   (__thiscall *FnV2ii)(void*, int, int);
typedef int    (__thiscall *FnVi2ii)(void*, int, int);
void DeleteObj(void* p);                 // 0x00f47380: operator delete
struct FrameSet {
    void  Ctor(void* factory);                                   // 0x00996cc0
    void  Dtor();                                                // 0x009968a0
    void  Setup(int a, int b, int c, int d);                     // 0x00996280
    void* GetFrame(unsigned key);                                // 0x00996d40
    bool  CheckWin(void* win, unsigned key);                     // 0x009979f0
    bool  HandleLocationChange(unsigned key, unsigned a, unsigned b, int c); // 0x00997730
    bool  HandleFormSubmit(unsigned a, unsigned b);              // 0x009978b0
};
extern unsigned g_key_expansion_frame;    // [0x015282e4]
extern char     g_key_xhtml_dialog;       // [0x015285a4]
void FUN_00809db0(int a, void* b);        // 0x00809db0
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
// ---- items of slice s006708d0 end

// ---- items of slice s00671840 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct MissingPage_s0067_1840 {
  char pad[0x400];
  bool ShowMissingExpansionPacks(void* a, int b);
};
// ---- items of slice s00671840 end

// @ 0x006715d0
MissingPage::MissingPage()
{
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

// @ 0x00671630
MissingPage* MissingPage::Destroy(unsigned flags)
{
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
bool MissingPage::Init(void* w)
{
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
bool MissingPage::DoMessage(int unused, int* msg)
{
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
void MissingPage::SetVisibility(int vis)
{
    void* fr = ((FrameSet*)((char*)this + 0xc))->GetFrame(g_key_expansion_frame);
    if (fr) {
        void* p = (char*)fr + 4;
        ((FnV2ii)((VObj*)p)->vt[0x7c / 4])(p, 1, vis);
    }
    void* x = mpContentWin;
    void* r = (void*)((FnVi2ii)((VObj*)x)->vt[0xf0 / 4])(x, 0x34a5bc7a, 1);
    if (r) ((FnV2ii)((VObj*)r)->vt[0x7c / 4])(r, 1, vis);
}

// @ 0x00671840
bool MissingPage_s0067_1840::ShowMissingExpansionPacks(void* a, int b)
{
  (void)a; (void)b;
  return false;
}
