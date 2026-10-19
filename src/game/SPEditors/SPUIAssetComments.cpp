// src/game/SPEditors/SPUIAssetComments.cpp -- migrated from slice(s) s0064dbd0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIAssetComments.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIAssetComments.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPUIAssetGrid.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned);
extern "C" int64_t __cdecl StrtoU6416(wchar_t*, int, int);
extern "C" void* __cdecl MessageServer();           // FUN_0067dcc0
extern "C" void  __cdecl FUN_809db0(void*, void*);           // FUN_00809db0
extern void* g_CommentsFrame;          // 0x015258dc
extern void* g_sporeprofile;           // 0x015258e0
extern uint32_t g_sporeprofileLen;     // 0x015f9a28
extern char g_vtbl_cSPUIAssetComments_primary[];    // 0x013ff9fc
extern char g_vtbl_cSPUIAssetComments_secondary[];  // 0x013ff9ec
extern char g_vtbl_cSPUIAssetComments_base[];       // 0x013ec458
extern char g_vtbl_cEditorResource[];               // 0x013eb938
#include <intrin.h>

// ---- items of slice s0064dbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* p) { return *(void***)p; }
struct PBase1 {
    virtual void pv();
};
struct PBase2 {
    virtual void pv();
    int mRef;
    PBase2() : mRef(0) {}
};
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned);
extern "C" int64_t __cdecl StrtoU6416(wchar_t*, int, int);
extern "C" void* __cdecl MessageServer();           // FUN_0067dcc0
extern "C" void  __cdecl FUN_809db0(void*, void*);           // FUN_00809db0
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
void* __cdecl EASTL_deallocate(void*);                     // FUN_00f47380
extern char g_vtbl_cSPUIAssetComments_primary[];    // 0x013ff9fc
extern char g_vtbl_cSPUIAssetComments_secondary[];  // 0x013ff9ec
extern char g_vtbl_cSPUIAssetComments_base[];       // 0x013ec458
extern char g_vtbl_cEditorResource[];               // 0x013eb938
namespace SP {
struct cSPUIAssetComments_s0064_dbd0 : PBase1, PBase2 {
    char mFrameSet[0x64];     // +0x0c  (retail size)
    void* mpContentWin;       // +0x70
    void* mpXHTMLWin;         // +0x74

    cSPUIAssetComments_s0064_dbd0();
    bool Init(void* win);  // 0x0064e230 (SP::cSPUIAssetComments::Init)
    void SetVisibility(int visible);  // 0x0064e400 (SP::cSPUIAssetComments::SetVisibility)
    bool LoadAssetComments();  // 0x0064e460 (SP::cSPUIAssetComments::LoadAssetComments)
    bool DoMessage(void* sender, int* msg);
    void* deleting_dtor(unsigned flags);
};  // namespace SP
}
// ---- items of slice s0064dbd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* __cdecl AuthManager();             // FUN_00607a60
extern "C" void  __cdecl FUN_4e0850(void*, const wchar_t*, int64_t);
extern "C" int64_t __cdecl PollenGetURL(uint32_t, void*);    // FUN_006214c0

// @ 0x0064e1d0
void* SP::cSPUIAssetComments_s0064_dbd0::deleting_dtor(unsigned flags)
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

// @ 0x0064e230
bool SP::cSPUIAssetComments_s0064_dbd0::Init(void* win)
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

// @ 0x0064e300
bool SP::cSPUIAssetComments_s0064_dbd0::DoMessage(void* sender, int* msg)
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

// @ 0x0064e400
void SP::cSPUIAssetComments_s0064_dbd0::SetVisibility(int visible)
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

// @ 0x0064e460
bool SP::cSPUIAssetComments::LoadAssetComments(unsigned __int64 a1)
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
