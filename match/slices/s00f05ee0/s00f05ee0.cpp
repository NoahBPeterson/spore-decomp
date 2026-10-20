// slice s00f05ee0 -- SP::cSPPlayModeSubModeMovie (play-mode movie sub-mode; YouTube upload flow).
//   0x00f05ee0  PostRecordingDone()
//   0x00f06150  CheckRecordingPreconditions() -> bool
//   0x00f063c0  HandleMessage(unsigned int, void*)            (IHandler subobject at +0x04)
//   0x00f065d0  ShowUploadProgressDialog()
//   0x00f06660  ShowSendVideoURLDialog()
//   0x00f066c0  SelectRecording(unsigned int*, void*) -> bool
//   0x00f067b0  Update(unsigned int)
//   0x00f069a0  BeginRecording(unsigned char) -> bool
//   0x00f06ac0  ClearIndicatorTextures()
//   0x00f06ce0  RegisterMessageHandlers()
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// NOTE: the migrated header src/game/include/SP/cSPPlayModeSubModeMovie.h is the *editor* class
// (module SPEditors/SPSubModeMovie.obj, retail size 0x2360, symbol suffix `_s0063_ba50`).  The
// functions in THIS slice belong to the genuine play-mode class whose retail layout is smaller and
// is reconstructed locally below from the disassembly (handler subobject at +0x04, UI at +0x2c,
// dialog state at +0x28, ...).
#include "types.h"
#include <string.h>

#pragma warning(disable: 4100)

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

struct MovieHandler { void* mVtbl; u32 mSrv;                   // IHandler subobject at +0x04
    void HandleMessage(u32 unused, u32 msgId);                 // 0x00f063c0
};
struct VtblPart { void* mVtbl0; };                            // primary vtable at +0x00

void* __cdecl operator_new(u32);                              // 0x00f473a0
void  __cdecl operator_delete(void*);                         // 0x00f47380
int   __cdecl sprintfA(void* str, const char* fmt, ...);      // 0x00472fe0
int   __cdecl sprintfW(void* str, const wchar_t* fmt, ...);   // 0x0041e050
void* __cdecl GetSaveArea(u32 id);                            // 0x006b1f90
void* __cdecl ConvertToString8(void* out, void* in, int a3);  // 0x0093c570
void* __cdecl ConvertToString8Impl(void* out, const wchar_t* s, u32 n); // 0x0093c440
void* __cdecl StrAssign(void* str, void* a, void* b);         // 0x00454cb0
char  __cdecl FindParentDir2(int, int, int);                  // 0x006375e0
void* __cdecl EStringCopyCtor(void* dst, void* src);          // 0x0057cb10
void  __cdecl FUN_00637570(void* p);                          // 0x00637570
void* __cdecl FUN_0067dd30();                                 // 0x0067dd30 ConfigManager
void* __cdecl FUN_0067dd60();                                 // 0x0067dd60
void* __cdecl FUN_0067dcc0();                                 // 0x0067dcc0 MessageServer
void* __cdecl FUN_0067de40();                                 // 0x0067de40
void  __cdecl FUN_00809db0(MovieHandler* obj, u32 msg);       // 0x00809db0 UI::CalloutMessageBox
void* __cdecl FUN_00f04530(int);                              // 0x00f04530
void  __cdecl FUN_00ed4f00(int);                              // 0x00ed4f00
void* __cdecl FUN_00607a60();                                 // 0x00607a60 AuthManager
void  __cdecl FUN_0063bc70();                                 // 0x0063bc70 CreateConnectingDialog
void  __cdecl FUN_0063c060(int);                              // 0x0063c060 DestroyConnectingDialog
void  __cdecl FUN_0063bc10(int);                              // 0x0063bc10 SetUpYouTubeErrorMessage
void  __cdecl FUN_0063be00();                                 // 0x0063be00 ShowYouTubeUploadVideoDialog
void  __cdecl FUN_0063bd50();                                 // 0x0063bd50 ShowLoginToYouTubeDialog
void  __cdecl FUN_0063c750(void* p);                          // 0x0063c750 ~cEditorYouTubeVideoUploadMessage
char  __cdecl GetYTPrompt();                                  // 0x0063b890
char  __cdecl FUN_00407190(void* propList, u32 id, void* out); // 0x00407190 GetBoolProperty
u8    __cdecl OpenBrowser(const wchar_t* url, int flag);      // 0x00935fb0
void* __cdecl FUN_006f43e0(void* a, void* b, void* c);        // 0x006f43e0 eastl copy dispatch
void* __cdecl GameTimeManager();                              // 0x00b3d380 SP::GameTimeManager
u32   __cdecl DoInsertValue_impl(void* vec, void* pos, void* val); // 0x00425a80

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* p);
extern char _sAppProperties;                                  // 0x015fd918
#define gAppProperties (*(void**) 0x015fd918)

// ---- vtable-slot helper (obj->vftable[byteOffset/4]) -------------------------
static inline void* VT(void* o, int off) { return ((void**) (*(void**) o))[off / 4]; }

typedef void* (__thiscall *FnWin2)(void*, int, int);
typedef void* (__thiscall *FnWinU)(void*, u32);
typedef void  (__thiscall *FnU0)(void*);
typedef void* (__thiscall *FnR0)(void*);
typedef char  (__thiscall *FnC0)(void*);
typedef void* (__thiscall *FnR2)(void*, void*, void*);
typedef void* (__thiscall *FnR3)(void*, void*, void*, void*);
typedef void* (__thiscall *FnRU2)(void*, u32, void*);

namespace SP {

// eastl strings ------------------------------------------------------------
struct EStringA { void* mpBegin; void* mpEnd; void* mpCap; void* mpAlloc; };

// UTFWin window layout (only the methods this slice calls) ------------------
struct cSPUILayout { void* FindWindowByID(u32 id, int flag); };   // 0x008105b0

// SP::cString (small string helper with ctor/dtor) -------------------------
struct cString { char m[0x14]; cString(); ~cString(); };          // 0x006b5060 / 0x006b5240

// SP::cGameTimeManager (only the method this slice calls) ------------------
struct cGameTimeManager { void IncPauseGate(u32 id); };           // 0x00b32220

// intrusive ref-counted pointer vector ------------------------------------
struct RefVec {
    void** mpBegin;   // +0
    void** mpEnd;     // +4
    void** mpCap;     // +8
    void  Release(void* elem);                     // 0x00760c40
    void  DoInsertValue(void* where, void* val);   // 0x00425a80
    void  DestroyRange(void* a, void* b);          // 0x0070f520
};

struct cDirectPropertyList { char m[0x18];           // +0x100
    void SetBoolProperty();                          // 0x0093a2e0
};

// cSPPlayModeSubModeMovie (play-mode) --------------------------------------
struct cSPPlayModeSubModeMovie : VtblPart, MovieHandler {
    char   m08[8];        // +0x0c
    void*  mServer;       // +0x14
    void*  mHandlerObj;   // +0x18
    void*  mMsgTable;     // +0x1c
    u32    mMsgCount;     // +0x20
    u32    m24;           // +0x24
    u32    mDialog;       // +0x28
    void*  mUI;           // +0x2c  cSPUILayout*
    char   m30[8];        // +0x30
    void*  m38;           // +0x38
    char   m3c[0x18];     // +0x3c
    void*  m54;           // +0x54  wchar_t*
    char   m58[0x1c];     // +0x58
    u32    m74;           // +0x74
    bool   m78;           // +0x78
    char   m79[3];        // +0x79
    void*  m7c;           // +0x7c  char*
    char   m80[0x0c];     // +0x80
    void*  m8c;           // +0x8c  char*
    char   m90[0x0c];     // +0x90
    void*  m9c;           // +0x9c  char*
    char   ma0[0x1c];     // +0xa0
    bool   mbc;           // +0xbc
    bool   mbd;           // +0xbd
    bool   mbe;           // +0xbe
    bool   mbf;           // +0xbf
    bool   mc0;           // +0xc0
    bool   mc1;           // +0xc1
    bool   mc2;           // +0xc2
    bool   mc3;           // +0xc3
    bool   mc4;           // +0xc4
    char   mc5[3];        // +0xc5
    u32    mc8;           // +0xc8
    char   mcc[4];        // +0xcc
    RefVec mVecA;         // +0xd0
    char   mdc[8];        // +0xdc
    RefVec mVecB;         // +0xe4
    char   mf0[8];        // +0xf0
    bool   mf8;           // +0xf8
    bool   mf9;           // +0xf9
    char   mfa[6];        // +0xfa
    cDirectPropertyList mPropList;  // +0x100
    long long mDeadline;  // +0x118

    void  PostRecordingDone();                        // 0x00f05ee0
    bool  CheckRecordingPreconditions();              // 0x00f06150
    void  ShowUploadProgressDialog();                 // 0x00f065d0
    void  ShowSendVideoURLDialog();                   // 0x00f06660
    bool  SelectRecording(int* pIndex, void* pOut);   // 0x00f066c0
    void  Update(u32 dt);                             // 0x00f067b0
    bool  BeginRecording(u8 flag);                    // 0x00f069a0
    void  ClearIndicatorTextures();                   // 0x00f06ac0
    void  RegisterMessageHandlers();                  // 0x00f06ce0

    // callees in this module (declared only)
    void FUN_00f05c40();                              // 0x00f05c40
    void FUN_00f05dc0(void* msg);                     // 0x00f05dc0
    void FUN_00f05d00();                              // 0x00f05d00 LoginToYouTube
    void FUN_00f055c0();                              // 0x00f055c0
    void FUN_00f05790();                              // 0x00f05790
    void FUN_00f03de0();                              // 0x00f03de0
    void FUN_00f03e40();                              // 0x00f03e40
    void FUN_00f03e90();                              // 0x00f03e90
    void FUN_00f03d20();                              // 0x00f03d20
    void FUN_00f03d50();                              // 0x00f03d50
    void FUN_00f041a0();                              // 0x00f041a0
    void FUN_00f044d0();                              // 0x00f044d0
    void FUN_00f03fc0(int);                           // 0x00f03fc0
    void FUN_00f04070(int);                           // 0x00f04070

    MovieHandler* GetHandlerSub() { return static_cast<MovieHandler*>(this); }
};

}  // namespace SP

using namespace SP;

// ---------------------------------------------------------------------------
// @ 0x00f05ee0  cSPPlayModeSubModeMovie::PostRecordingDone()
void cSPPlayModeSubModeMovie::PostRecordingDone()
{
    mc3 = true;
    mc4 = false;
    mc2 = false;

    // build the cEditorYouTubeVideoUploadMessage on the stack
    char msg[0x98];
    memset(msg, 0, sizeof(msg));
    *((void**) (msg + 0x00)) = (void*) 0x1667bac;   // empty string16 x3 (username)
    *((void**) (msg + 0x04)) = (void*) 0x1667bac;
    *((void**) (msg + 0x08)) = (void*) 0x1667bae;
    FUN_00f05dc0(msg);

    wchar_t wbuf[0x104];
    void* p54 = m54;
    *((void**) (wbuf + 0x00)) = (void*) 0x1667bac;
    *((void**) (wbuf + 0x02)) = (void*) 0x1667bac;
    *((void**) (wbuf + 0x04)) = (void*) 0x1667bae;
    sprintfW(wbuf, L"%s.avi", p54);

    void* area = GetSaveArea(0x11ac197);
    void* obj;
    if (area == 0)
        obj = 0;
    else
        obj = ((FnRU2) VT((void*) ((char*) area + 4), 0xc))((char*) area + 4, 0x226a1de, 0);
    char* xmlName = 0;
    ((FnR2) VT(obj, 0x68))(obj, wbuf, (void*) &xmlName);

    sprintfA(msg + 0x10, "%s", m8c);
    sprintfA(msg + 0x20, "%s", (void*) 0x13ff3d8);
    sprintfA(msg + 0x30, "%s", m7c);
    sprintfA(msg + 0x40, "%s",
             "AI39si7ypzxvEPSQoJdcrjAiy54bV93uKhoZcQt-96m9eEIFHZYgJwxiKefFgGSYX7r9jFanihf0DUEuKLlOKK3lrW8UF4bC5g");

    char* s8 = (char*) ConvertToString8(msg + 0x88, xmlName, 0);
    sprintfA(msg + 0x50, "%s.avi", *((void**) s8));

    {
        void* b = *((void**) (msg + 0x68));
        void* e = *((void**) (msg + 0x6c));
        if ((int) ((char*) e - (char*) b) > 1 && b)
            operator_delete(b);
    }
    sprintfA(msg + 0x60, "%s", *((void**) (msg + 0x68)));

    void* msvr = FUN_0067dcc0();
    ((FnR3) VT(msvr, 0x14))(msvr, (void*) 0x55e8bc8, msg + 0x10, (void*) 0);

    FUN_0063c750(msg);

    {
        void* b = *((void**) (msg + 0x28));
        void* e = *((void**) (msg + 0x2c));
        if ((int) ((char*) e - (char*) b) > 1 && b)
            operator_delete(b);
    }
    {
        void* b = *((void**) (wbuf + 0x0a));
        void* e = *((void**) (wbuf + 0x0c));
        if ((int) ((char*) e - (char*) b) > 1 && (char*) b != 0)
            operator_delete(b);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f06150  cSPPlayModeSubModeMovie::CheckRecordingPreconditions() -> bool
bool cSPPlayModeSubModeMovie::CheckRecordingPreconditions()
{
    char s1[0x10], s2[0x10];

    void* wnd = ((cSPUILayout*) mUI)->FindWindowByID(0x4581d50, 1);
    void* text = ((FnWin2) VT(wnd, 0x3c))(wnd, (int) -1, 0);
    char tmpA[0x10];
    ConvertToString8Impl(tmpA, (const wchar_t*) text, 0xffffffff);
    sprintfA(s1, "%s", *((void**) (tmpA + 4)));

    wnd = ((cSPUILayout*) mUI)->FindWindowByID(0x4581d78, 1);
    text = ((FnWin2) VT(wnd, 0x3c))(wnd, (int) -1, 0);
    char tmpB[0x10];
    char* r = (char*) ConvertToString8Impl(tmpB, (const wchar_t*) text, 0xffffffff);
    if (r != tmpA)
        StrAssign(r, *((void**) r), *((void**) (r + 4)));
    {
        void* b = *((void**) (tmpB + 4));
        void* e = *((void**) (tmpB + 8));
        if ((int) ((char*) e - (char*) b) > 1 && b)
            operator_delete(b);
    }

    bool failed = false;
    if (*((void**) (tmpA + 4)) != *((void**) tmpA)) {
        EStringCopyCtor(s2, tmpA);
        char d = FindParentDir2(0, 0, 0);
        if (d != 0)
            goto after;
    }
    {
        wnd = ((cSPUILayout*) mUI)->FindWindowByID(0x3f67620, 1);
        ((FnWin2) VT(wnd, 0x7c))(wnd, 1, 0);
        FUN_00809db0(GetHandlerSub(), 0x15ad4d4);
        mDialog = 0xe;
        failed = true;
    }
after:
    sprintfA(s2, "%s", *((void**) (tmpA + 4)));

    wnd = ((cSPUILayout*) mUI)->FindWindowByID(0x4581d90, 1);
    text = ((FnWin2) VT(wnd, 0x3c))(wnd, (int) -1, 0);
    r = (char*) ConvertToString8Impl(tmpB, (const wchar_t*) text, 0xffffffff);
    if (r != tmpA)
        StrAssign(r, *((void**) r), *((void**) (r + 4)));
    {
        void* b = *((void**) (tmpB + 4));
        void* e = *((void**) (tmpB + 8));
        if ((int) ((char*) e - (char*) b) > 1 && b)
            operator_delete(b);
    }
    sprintfA(s2, "%s", *((void**) (tmpA + 4)));

    {
        void* ms = FUN_0067de40();
        void* v = ((FnR0) VT(ms, 0x14))(ms);
        char tmpC[0x10];
        char* s = (char*) ConvertToString8Impl(tmpC, *((const wchar_t**) v), 0xffffffff);
        sprintfA(s2, "%s", *((void**) s));
    }
    if (!failed) {
        void* msvr = FUN_0067dcc0();
        ((FnR3) VT(msvr, 0x14))(msvr, (void*) 0x56cd8c4, s1, (void*) 0);
    }
    {
        void* b = *((void**) (s1 + 4));
        void* e = *((void**) (s1 + 8));
        if ((int) ((char*) e - (char*) b) > 1 && b)
            operator_delete(b);
    }
    FUN_00637570(s2);
    return failed;
}

// ---------------------------------------------------------------------------
// @ 0x00f063c0  MovieHandler::HandleMessage(unsigned int, unsigned int)  (this == outer + 0x04; returns void)
void MovieHandler::HandleMessage(u32 unused, u32 msgId)
{
    cSPPlayModeSubModeMovie* o = static_cast<cSPPlayModeSubModeMovie*>(this);
    switch (o->mDialog) {
    case 1:
        if (msgId == 0x5107b17) {
            o->FUN_00f03de0();
            OpenBrowser(L"http://youtube.com/t/terms", 1);
            return;
        }
        if (msgId == 0x5107b19)
            goto L_5107b19;
        if (msgId == 0x5107b1a) {
            void* am = FUN_00607a60();
            if (!((FnC0) VT(am, 0x58))(am)) {
                o->mDialog = 8;
                FUN_00809db0(this, 0x15ad498);
                return;
            }
            am = FUN_00607a60();
            if (((FnC0) VT(am, 0x24))(am)) {
                o->mDialog = 7;
                FUN_00809db0(this, 0x15ad48c);
                return;
            }
            if (!GetYTPrompt()) {
                FUN_0063bc70();
                o->FUN_00f05c40();
                return;
            }
            goto L_5107b1a;
        }
        break;
    case 2:
        if (msgId == 0x5107b19) goto L_5107b19;
        if (msgId == 0x5107b1a) goto L_5107b1a;
        break;
    case 3:
        o->mDialog = 0;
        return;
    case 4:
    case 6:
    L_5107b19:
        o->FUN_00f044d0();
        return;
    case 5:
        if (msgId == 0x5107b19) goto L_5107b19;
        if (msgId == 0x5107b1a) {
            o->FUN_00f041a0();
            return;
        }
        break;
    case 7:
    case 8:
        if (msgId == 0x5107b19) goto L_5107b19;
        if (msgId == 0x5107b1a) {
            void* am = FUN_00607a60();
            ((FnU0) VT(am, 0x44))(am);
            return;
        }
        break;
    case 10:
    case 0xb:
        if (msgId == (u32) -0xf) goto L_5107b19;
        break;
    case 0xc:
        if (msgId == 0x5107b19) {
        L_5107b1a:
            o->FUN_00f03e90();
            return;
        }
        if (msgId == 0x5107b1a) {
            o->FUN_00f03e90();
            OpenBrowser(L"http://www.youtube.com/signup", 1);
            return;
        }
        break;
    case 0xd:
        if (msgId == 0x5107b19) {
            o->FUN_00f05790();
            return;
        }
        if (msgId == 0x5107b1a) {
            o->FUN_00f05790();
            OpenBrowser(L"http://youtube.com/t/terms", 1);
            return;
        }
        break;
    case 0xe:
        if (msgId == (u32) -0xf)
            o->FUN_00f03fc0(1);
        break;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f065d0  cSPPlayModeSubModeMovie::ShowUploadProgressDialog()
void cSPPlayModeSubModeMovie::ShowUploadProgressDialog()
{
    void* w = ((cSPUILayout*) mUI)->FindWindowByID(0x5650568, 1);
    ((FnWin2) VT(w, 0x7c))(w, 1, 0);
    mDialog = 0;
    w = ((cSPUILayout*) mUI)->FindWindowByID(0x5650498, 1);
    void* s = (*(FnR0*) ((char*) (*(void**) w) + 0x3c))(w);
    sprintfA((char*) this + 0x8c, "%ls", s);
    w = ((cSPUILayout*) mUI)->FindWindowByID(0x5650500, 1);
    s = (*(FnR0*) ((char*) (*(void**) w) + 0x3c))(w);
    sprintfA((char*) this + 0x9c, "%ls", s);
    FUN_0063bc70();
    FUN_00f05c40();
}

// ---------------------------------------------------------------------------
// @ 0x00f06660  cSPPlayModeSubModeMovie::ShowSendVideoURLDialog()
void cSPPlayModeSubModeMovie::ShowSendVideoURLDialog()
{
    cString tmp;
    if (!CheckRecordingPreconditions()) {
        void* w = ((cSPUILayout*) mUI)->FindWindowByID(0x3f67620, 1);
        ((FnWin2) VT(w, 0x7c))(w, 1, 0);
        FUN_00809db0(GetHandlerSub(), 0x15ad4a4);
        mDialog = 10;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f066c0  cSPPlayModeSubModeMovie::SelectRecording(u32*, void*) -> bool
bool cSPPlayModeSubModeMovie::SelectRecording(int* pIndex, void* pOut)
{
    mVecA.Release(&mVecA.mpBegin[*pIndex]);
    mVecB.Release(&mVecB.mpBegin[*pIndex]);

    int n = (int) (mVecA.mpEnd - mVecA.mpBegin);
    if (*pIndex == n && *pIndex != 0)
        --*pIndex;
    bool sel = (*pIndex < (int) (mVecA.mpEnd - mVecA.mpBegin));
    if (sel) {
        void* mgr = FUN_0067dd60();
        char loc[12];
        void* res = ((FnR2) VT(mgr, 0x2c))(mgr, loc, (void*) (size_t) mVecA.mpBegin[*pIndex]);
        *((u32*) pOut + 0) = *((u32*) res + 0);
        *((u32*) pOut + 1) = *((u32*) res + 1);
        *((u32*) pOut + 2) = *((u32*) res + 2);
    }
    bool bVar6 = ((u32) (mVecA.mpEnd - mVecA.mpBegin) < 0x32);
    if (m38 != 0) {
        void* w = ((FnR2) VT(m38, 0xf0))(m38, (void*) 0x78d57d8, (void*) 1);
        if (w != 0)
            ((FnWin2) VT(w, 0x7c))(w, 2, (int) bVar6);
    }
    if (*(u32*) 0x16c7aa4 != 0 && *(u32*) (0x16c7aa4 + 0x14) != 0)
        FUN_00ed4f00((int) bVar6);
    return sel;
}

// ---------------------------------------------------------------------------
// @ 0x00f067b0  cSPPlayModeSubModeMovie::Update(unsigned int)
void cSPPlayModeSubModeMovie::Update(u32 dt)
{
    if (*((u32*) &mPropList) || *((u32*) ((char*) &mPropList + 4))) {
        long long now;
        QueryPerformanceCounter(&now);
        if (mDeadline - now < 0) {
            mPropList.SetBoolProperty();
            mf8 = false;
            FUN_00f04070(1);
        }
    }
    if (m78) {
        m74 += dt;
        if ((int) m74 > 500) {
            FUN_00f03e40();
            m74 = 0;
        }
    }
    if (mbe && mbd) {
        if (mbc) {
            void* cm = FUN_0067dd30();
            ((FnU0) VT(cm, 0x3c))(cm);
            FUN_00f055c0();
            FUN_0063bd50();
            FUN_00f05d00();
        } else {
            FUN_0063c060(0);
            FUN_0063bc10(0);
            if (mc8 == 0x193)
                FUN_00f03d20();
            else
                FUN_00f03d50();
        }
        mbe = false;
    }
    if (mc1 && mc0) {
        if (mbf) {
            FUN_0063be00();
            u8 v = 0;
            FUN_00407190(gAppProperties, 0x566387e, &v);
            if (v != 0)
                PostRecordingDone();
            else {
                mc3 = true;
                mc4 = true;
                mc2 = false;
            }
        } else {
            FUN_0063c060(0);
            FUN_0063bc10(0);
            FUN_00809db0(GetHandlerSub(), 0x15ad468);
            mDialog = 4;
        }
        mc1 = false;
    }
    if (mc3 && mc4) {
        if (mc2) {
            FUN_0063c060(1);
            FUN_00809db0(GetHandlerSub(), 0x15ad480);
            mc3 = false;
            mDialog = 5;
            return;
        }
        FUN_0063c060(0);
        FUN_0063bc10(1);
        FUN_00809db0(GetHandlerSub(), 0x15ad474);
        mDialog = 6;
        mc3 = false;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f069a0  cSPPlayModeSubModeMovie::BeginRecording(unsigned char) -> bool
bool cSPPlayModeSubModeMovie::BeginRecording(u8 flag)
{
    if (mf8 || (u32) (mVecA.mpEnd - mVecA.mpBegin) > 0x31)
        return false;

    void* ref = FUN_00f04530(0);
    if (ref)
        (*((volatile int*) ((char*) ref + 8)))++;

    if (mVecA.mpEnd < mVecA.mpCap) {
        void** slot = mVecA.mpEnd;
        mVecA.mpEnd = slot + 1;
        if (slot != 0) {
            *slot = ref;
            if (ref)
                (*((volatile int*) ((char*) ref + 8)))++;
        }
    } else {
        mVecA.DoInsertValue(mVecA.mpEnd, &ref);
    }
    if (ref) {
        volatile int* rc = (volatile int*) ((char*) ref + 8);
        --*rc;
        if (*rc < 1)
            ++*rc;
    }
    if (m38 != 0) {
        void* w = ((FnR2) VT(m38, 0xf0))(m38, (void*) 0x78d57d8, (void*) 1);
        if (w != 0)
            ((FnWin2) VT(w, 0x7c))(w, 2, 0);
    }
    if (*(u32*) (0x16c7aa4 + 0x14) != 0)
        FUN_00ed4f00(0);
    ((cGameTimeManager*) GameTimeManager())->IncPauseGate(0x4bf38a7);
    mf8 = true;
    mf9 = (flag != 0);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00f06ac0  cSPPlayModeSubModeMovie::ClearIndicatorTextures()
void cSPPlayModeSubModeMovie::ClearIndicatorTextures()
{
    void** b = mVecA.mpBegin;
    void** e = mVecA.mpEnd;
    void* r = FUN_006f43e0(e, e, b);
    mVecA.DestroyRange(r, mVecA.mpEnd);
    mVecA.mpEnd = (void**) ((char*) mVecA.mpEnd + ((char*) e - (char*) b) * -1);

    b = mVecB.mpBegin;
    e = mVecB.mpEnd;
    r = FUN_006f43e0(e, e, b);
    mVecB.DestroyRange(r, mVecB.mpEnd);
    mVecB.mpEnd = (void**) ((char*) mVecB.mpEnd + ((char*) e - (char*) b) * -1);

    char* src = (char*) (*(u32*) (0x16c7aa4 + 0x74));
    src = *(char**) (src + 0x10) + 8;
    int off = -0x38;
    int n = 0x32;
    do {
        u32 v10 = *(u32*) (src + 0x10);
        u32 v08 = *(u32*) (src + 0x08);
        u32 v0c = *(u32*) (src + 0x0c);
        u32 h1 = ((u32) (off - 100) ^ v10) & 0xff ^ v10;
        void* mgr = FUN_0067dd60();
        void* r1 = ((FnR2) VT(mgr, 0x1c))(mgr, (void*) v08, (void*) (size_t) h1);
        (void) r1;
        u32 v10b = *(u32*) (src + 0x10);
        u32 v10c = *(u32*) (src + 0x10);
        mgr = FUN_0067dd60();
        u32 h2 = (v10b ^ ((u32) off)) & 0xff ^ v10c;
        void* r2 = ((FnR2) VT(mgr, 0x1c))(mgr, (void*) v08, (void*) (size_t) h2);
        (void) v0c;
        (void) r2;
        ++off;
        --n;
    } while (n != 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f06ce0  cSPPlayModeSubModeMovie::RegisterMessageHandlers()
void cSPPlayModeSubModeMovie::RegisterMessageHandlers()
{
    ClearIndicatorTextures();
    void* handlerObj = (this != 0) ? (void*) ((char*) this + 8) : 0;
    void* srv = FUN_0067dcc0();
    mServer = srv;
    mHandlerObj = handlerObj;
    mMsgTable = (void*) 0x148b9a4;
    mMsgCount = 0xf;
    m24 = 0;
    if (srv != 0 && handlerObj != 0) {
        for (u32 i = 0; i < 0x3c; i += 4) {
            u32 id = *(u32*) (0x148b9a4 + i);
            ((FnR2) VT(srv, 0x24))(srv, handlerObj, (void*) (size_t) id);
        }
    }
}
