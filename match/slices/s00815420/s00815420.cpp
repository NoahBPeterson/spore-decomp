// Slice s00815420 (w2g7 #3), 32-bit MSVC 2008 SP1.
// UI cheats / text-style loading / cSPUIMainWin::InitFonts.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;

static inline void** Vtbl(void* o) { return *(void***)o; }

extern "C" void* __cdecl SP_ConfigManager();
extern "C" void* __cdecl SP_WindowManager();
extern "C" void* __cdecl EA_Text_GetFontServer(int);
extern "C" void* __cdecl EA_Text_GetStyleManager(int);
extern "C" void* __cdecl FUN_00805510(int);

void* __cdecl EAlloc(int size, int tag, int a, int b, int c, int d);   // 0xf473a0
void  __cdecl ArgScript_Output(void* parser, const char* fmt);          // 0x841000

// ---------------------------------------------------------------------------
// cSPUILayoutZoom-like outer object for the tiny wrappers
// ---------------------------------------------------------------------------
struct Inner { void Method(int, int); };   // 0x83b9d0
struct Outer {
    char pad0[0x4];
    int f4;                 // +0x4
    char pad1[0x10 - 0x8];
    Inner inner;            // +0x10
    void Wrap(int);         // 0x815b30
    void ExecuteColor(int); // 0x815a50
    char pad2[0xd8 - 0x10 - sizeof(Inner)];
    uint8_t bD8;            // +0xd8
};

// @ 0x00815b30
void Outer::Wrap(int arg) {
    inner.Method(arg, f4);
}

// @ 0x00815a50
void  __cdecl cString_SetColorLocalized(int);   // 0x6b5030
void Outer::ExecuteColor(int arg) {
    inner.Method(arg, f4);
    void* wm = SP_WindowManager();
    if (wm) {
        ((void(__thiscall*)(void*, int))Vtbl(wm)[0x90 / 4])(wm, bD8);
        cString_SetColorLocalized(bD8);
    }
}

// ---------------------------------------------------------------------------
// ConfigManager-backed cheat Execute
// ---------------------------------------------------------------------------
struct Mgr {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m0a();
    virtual void v2c(int, int);         // 0x2c
    virtual int  v30(int);              // 0x30
    virtual void p34(); virtual void p38();
    virtual void v3c();                 // 0x3c
};
struct Args {
    void MainArguments(void*, int, int);
};

struct Cheat {
    char pad0[0x4];
    void* mParser;          // +0x4
    void Execute(Args* args);   // 0x815990
};

// @ 0x00815990
void Cheat::Execute(Args* args) {
    int captured;
    args->MainArguments(&captured, 0, 0x7fffffff);
    Mgr* cm = (Mgr*)SP_ConfigManager();
    int v = cm->v30(0x631621a);
    cm = (Mgr*)SP_ConfigManager();
    cm->v2c(0x631621a, v == 0);
    cm = (Mgr*)SP_ConfigManager();
    cm->v3c();
    if (v != 0) {
        ArgScript_Output(mParser, "capture UI is off\n");
        return;
    }
    ArgScript_Output(mParser, "capture UI is on (captures at game resolution)\n");
}

// ---------------------------------------------------------------------------
// Text style loading + InitFonts
// ---------------------------------------------------------------------------
struct FontServer {
    virtual void f00(); virtual void f04();
    virtual void f08(int, int);
    virtual void f0c(); virtual void f10(); virtual void f14(); virtual void f18();
    virtual void f1c(); virtual void f20(); virtual void f24(); virtual void f28();
    virtual void f2c(); virtual void f30(); virtual void f34();
    virtual void f38(const wchar_t*, const wchar_t*);
    void* Init(void*);
};
struct StyleManager {
    void* Init(void*);
};
void __cdecl FUN_00885b00(void*);   // 0x885b00
void __cdecl FUN_00885af0(void*);   // 0x885af0
void __cdecl FUN_00885b50(void*);   // 0x885b50 (unused)
bool __cdecl LoadTextStyles(int, int);   // 0x815bd0

extern void* g_164d348;   // 0x164d348

// @ 0x00815ce0
bool cSPUIMainWin_InitFonts() {
    FontServer* fs = (FontServer*)EAlloc(0x2fd0, 0x13f6b3c, 0, 0, 0, 0);
    if (fs) fs = (FontServer*)fs->Init(FUN_00805510(1));
    else fs = 0;
    fs->f04();
    fs->f08(2, 1);
    FUN_00885b00(fs);
    fs->f38(L"web-default", L"Palatino Sans Infl Com");
    fs->f38(L"monospace", L"Lucida Console");
    StyleManager* sm = (StyleManager*)EAlloc(0x120, 0x13f6b3c, 0, 0, 0, 0);
    void* smp;
    if (sm) smp = sm->Init(FUN_00805510(1));
    else smp = 0;
    *(void**)((char*)g_164d348 + 0x10) = smp;
    FUN_00885af0(smp);
    LoadTextStyles(0x94da47e5, 0);
    LoadTextStyles(0x94da47e5, 1);
    return true;
}

// ---------------------------------------------------------------------------
// TextStyleReader bits (approximate)
// ---------------------------------------------------------------------------
void __cdecl EastlDealloc(void*);          // 0xf47380

struct HashtableStub {
  char pad0[4];
  void** buckets;    // +0x04
  unsigned n;        // +0x08
  int hC;            // +0x0c
  char pad10[0x0c];
  void* freeHead;    // +0x1c
  char pad20[4];
  void* rangeLo;     // +0x24
  void* rangeHi;     // +0x28
  char pad2c[4];
  void* sentinel;    // +0x30
  void DoFreeNodes(void** buckets, unsigned n);
};
struct TextStyleReaderStub {
  char pad0[0x10];
  void* m10;         // +0x10
  char pad14[4];
  int m18;           // +0x18
  char pad1c[0x18];
  void* m34;         // +0x34
  char pad38[4];
  int m3c;           // +0x3c
  char pad40[4];
  HashtableStub ht;  // +0x44
  void Dtor();
};

// @ 0x00815aa0
void HashtableStub::DoFreeNodes(void** buckets, unsigned n) {
    char* s = (char*)this;
    for (unsigned i = 0; i < n; ++i) {
        char* node = (char*)buckets[i];
        while (node) {
            char* next = *(char**)(node + 0x24);
            void* str = *(void**)node;
            int cap = *(int*)(node + 8) - *(int*)node;
            if (cap > 1 && str && str != *(void**)(node + 0x10))
                EastlDealloc(str);
            if (node != *(char**)(s + 0x30)) {
                if (node < *(char**)(s + 0x24) || node >= *(char**)(s + 0x28))
                    EastlDealloc(node);
                else { *(void**)node = *(void**)(s + 0x1c); *(void**)(s + 0x1c) = node; }
            }
            node = next;
        }
        buckets[i] = 0;
    }
}

// @ 0x00815b50
void TextStyleReaderStub::Dtor() {
    HashtableStub* s = &ht;
    s->DoFreeNodes(s->buckets, s->n);
    void* b = s->buckets;
    s->hC = 0;
    if (s->n > 1 && b != s->sentinel) {
        if (b >= s->rangeLo && b < s->rangeHi) {
            *(void**)b = s->freeHead;
            s->freeHead = b;
        } else {
            EastlDealloc(b);
        }
    }
    void* v = m34;
    if (m3c - (int)v > 1 && v) EastlDealloc(v);
    void* m = m10;
    if (m18 - (int)m > 1 && m) EastlDealloc(m);
}

// @ 0x00815bd0
// `anonymous namespace'::sLoadTextStylesFromCSS — open the style record as a
// stream and feed it to the text-style reader.  Returns true when the record
// could not be opened or the parse succeeded.
extern "C" int  __cdecl FUN_00808660(int mode, int* rec, void** outStream);
extern "C" void __cdecl FUN_005e9f50(void* self, unsigned n, const void* alloc);
extern "C" void __cdecl FUN_006861d0(int handle);
extern "C" char* __cdecl FUN_00897530(void* styleMgr, void* begin, void* end);
extern "C" bool __cdecl FUN_00897350(void* reader, void* arg, void* self);
extern "C" void __cdecl FUN_00815b50(void* reader);   // ~TextStyleReader

// The 12-byte record descriptor handed to the stream opener.
struct TextStyleRecord {
    void* mpResId;   // +0x0
    u32   mTag0;     // +0x4
    u32   mTag1;     // +0x8
};

// EASTL vector of one byte used as the stream buffer.
struct ByteVector {
    u8* mpBegin;   // +0x0
    u8* mpEnd;     // +0x4
    u8* mpCap;     // +0x8
};

// Stream interface: only slots 0x1c (read) and 0x30 (fill vector) are used.
struct RecordStream {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual void* ReadRaw(void* dst);            // +0x1c
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void Fetch(ByteVector* out);         // +0x30
};

bool __cdecl FUN_00815bd0(void* resId, int mode) {
    EA_Text_GetFontServer(1);
    void* const styleMgr = EA_Text_GetStyleManager(1);

    TextStyleRecord rec;
    rec.mpResId = resId;
    rec.mTag0 = 0x248f226;
    rec.mTag1 = 0x248e873;

    RecordStream* stream = 0;
    int handle = FUN_00808660(mode, (int*)&rec, (void**)&stream);
    if (handle == -1) {
        return true;
    }

    u8 firstByte;
    stream->ReadRaw(&firstByte);

    ByteVector buffer;
    FUN_005e9f50(&buffer, 1, &firstByte);
    stream->Fetch(&buffer);
    FUN_006861d0(handle);

    char* reader = FUN_00897530(styleMgr, buffer.mpBegin, buffer.mpEnd);

    struct { void* mpCallback; void* mpArg; } cb;
    cb.mpCallback = (void*)0x814b80;   // sTextStyleCallback
    cb.mpArg = (void*)0x15c3d8;
    const bool ok = FUN_00897350(reader, &cb, (void*)0x15c3d8);

    FUN_00815b50(reader);

    if (buffer.mpBegin != 0 && *(int*)(buffer.mpBegin - 4) != 0) {
        EastlDealloc(buffer.mpBegin);
    }
    (void)mode;
    return ok;
}

// ---------------------------------------------------------------------------
// @ 0x00815420
// cSPUIMainWin::Shutdown — tear down every UI subsystem the main window owns.
// `ecx` is read at entry and the trailing instruction is a plain `ret`, so the
// retail form is a zero-stack-argument thiscall (modelled here as __fastcall).
// ---------------------------------------------------------------------------

// The window/manager reached through the 0x67dce0 accessor: only slot 0x2c is
// called from this slice.
struct cMessageServer {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10();
    virtual void Post(u32* id, u32 msg, u32 arg);   // +0x2c
};
extern "C" cMessageServer* __cdecl FUN_0067dce0();   // message server

// Signature of cMessageServer slot 0x2c as invoked through its vtable.
typedef void (*MsgPostFn)(cMessageServer*, void*, u32, u32);

// Window-layout manager reached through 0x67de20; slots 0x1c and 0x34 are used.
struct cLayoutManager {
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03();
    virtual void l04(); virtual void l05(); virtual void l06();
    virtual void RemoveLayers(u32 id);               // +0x1c
    virtual void l20(); virtual void l24(); virtual void l28(); virtual void l2c();
    virtual void l30();
    virtual void ReleaseSubsystem(u32 id);           // +0x34
};
extern "C" cLayoutManager* __cdecl FUN_0067de20();

// Window manager around 0x67dcd0 / 0x67cbb0 / 0x67cbd0.
struct cWindowManager {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
    virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16();
    virtual void SetTarget(u32 win, u32 a, u32 b);   // +0x44
};
extern "C" cWindowManager* __cdecl FUN_0067dcd0();

// Generic teardown target: vtable slots 0x04 (release) and 0x08 (destroy).
struct cShutdownTarget {
    virtual void t00(); virtual void t04(); virtual void t08();
    virtual void t0c(); virtual void t10(); virtual void t14();
    virtual void t18(); virtual void t1c(); virtual void t20(); virtual void t24();
    virtual void t28(); virtual void t2c(); virtual void t30(); virtual void t34();
    virtual void t38(); virtual void t3c(); virtual void t40(); virtual void t44();
    virtual void t48(); virtual void t4c(u32 a, u32 b); virtual void t50();
    virtual void t54(); virtual void t58(); virtual void t5c(); virtual void t60();
    virtual void t64(); virtual void t68(); virtual void t6c(); virtual void t70();
    virtual void t74(); virtual void t78(); virtual void t7c(); virtual void t80();
    virtual void t84(); virtual void t88(); virtual void t8c(); virtual void t90();
    virtual void t94(u32 a);
};

extern "C" void  __cdecl FUN_007f4860();          // IMEServiceShutdown
extern "C" void* __cdecl FUN_006895b0();          // font/server list accessor
extern "C" void  __cdecl FUN_0080a5f0();          // pre-shutdown helper
extern "C" void  __cdecl FUN_008138e0();          // main-window helper
extern "C" void  __cdecl FUN_0081dce0(cShutdownTarget*);  // subsystem teardown
extern "C" void  __cdecl FUN_00811ad0(cShutdownTarget*);
extern "C" void  __cdecl FUN_008028e0(cShutdownTarget*);
extern "C" void  __cdecl FUN_008353a0(cShutdownTarget*);
extern "C" void  __cdecl FUN_0080fa20(cShutdownTarget*);
extern "C" void  __cdecl FUN_008175c0(cShutdownTarget*);
extern "C" void  __cdecl FUN_00816990(void*);
extern "C" void* __cdecl FUN_006782c0(void*, void*, void*);
extern "C" void* __cdecl FUN_0080fee0(void*);
extern "C" void  __cdecl FUN_008116e0(cShutdownTarget*);
extern "C" void  __cdecl FUN_00961e80(void*);
extern "C" void* __cdecl FUN_00885b00(int);
extern "C" void* __cdecl FUN_00885af0(int);
extern "C" void  __cdecl FUN_0067cbb0(u32);
extern "C" void  __cdecl FUN_0067cbd0(u32);
extern "C" void  __cdecl FUN_0082f8a0();
extern "C" void  __cdecl FUN_00957f40(u32);
extern "C" void  __cdecl FUN_0067cba0(u32);
extern "C" void* __cdecl FUN_006b1f90(const void*);
extern "C" void  __cdecl FUN_00889c80();

// The main window singleton; only the fields touched by Shutdown are named.
struct cSPUIMainWin {
    // vtable: the base window's virtuals.  Nothing here calls them directly,
    // but the compiler emits the vptr, so reserve the base.
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    u8   mUnk04[0x214 - 0x04];
    u32* mpMessageIdTarget;   // +0x214  (address passed to the message server)
    u8   mShutdownFlag;       // +0x218
    u8   mUnk219[0x244 - 0x219];
    cShutdownTarget* mUnk244; // +0x244
    u8   mUnk248[0x250 - 0x248];
    u32  mUnk250;             // +0x250  (target of a layout SetLayout call)
    u8   mUnk254[0x260 - 0x254];
    cShutdownTarget* mUnk260; // +0x260  subtitle layer (loop of 10)
    cShutdownTarget* mUnk264; // +0x264
    cShutdownTarget* mUnk268; // +0x268
    cShutdownTarget* mUnk26c; // +0x26c
    cShutdownTarget* mUnk270; // +0x270
    cShutdownTarget* mUnk274; // +0x274
    cShutdownTarget* mUnk27c; // +0x27c
    cShutdownTarget* mUnk280; // +0x280
    u32  mUnk284[0x294 - 0x284];
    cShutdownTarget* mUnk294; // +0x294
    cShutdownTarget* mUnk298; // +0x298
    void** mp2a0;             // +0x2a0  (vector begin)
    cShutdownTarget* mUnk2a4; // +0x2a4
    cShutdownTarget** mp2a8;  // +0x2a8  (vector begin of targets)
    cShutdownTarget** mp2ac;  // +0x2ac  (vector end of targets)
    u8   mUnk2b0[0x2d0 - 0x2b0];
    cShutdownTarget* mUnk2d0; // +0x2d0
    u8   mUnk2d4[0x2d8 - 0x2d4];
    cShutdownTarget* mUnk2d8; // +0x2d8
    u8   mUnk2dc;             // +0x2dc

    void Shutdown();
};

void __fastcall FUN_00815420(cSPUIMainWin* thiz) {
    cSPUIMainWin* const self = thiz;
    if (self->mShutdownFlag == 0) {
        return;
    }

    cShutdownTarget* t = 0;
    u32 win = 0;

    if (self->mUnk260 != 0) {
        for (u32 i = 0; i < 10; ++i) {
            cShutdownTarget* const layer = self->mUnk260;
            layer->t4c(i, win);
        }
    }

    {
        cMessageServer* const ms = FUN_0067dce0();
        u32* const vt = *(u32**)ms;
        (*(void(**)(cMessageServer*, u32, u32, u32))(vt + (0x2c / 4)))(
            ms, 7, win, win);
    }
    FUN_007f4860();

    {
        cLayoutManager* const lm = FUN_0067de20();
        u32* const vt = *(u32**)lm;
        (*(void(**)(cLayoutManager*, u32))(vt + (0x1c / 4)))(
            lm, *(u32*)0x1545194);
    }
    {
        cLayoutManager* const lm = FUN_0067de20();
        u32* const vt = *(u32**)lm;
        (*(void(**)(cLayoutManager*, u32))(vt + (0x1c / 4)))(
            lm, *(u32*)0x154519c);
    }
    {
        cLayoutManager* const lm = FUN_0067de20();
        u32* const vt = *(u32**)lm;
        (*(void(**)(cLayoutManager*, u32))(vt + (0x1c / 4)))(
            lm, *(u32*)0x15451a0);
    }

    if (self->mUnk27c != 0) {
        FUN_00811ad0(self->mUnk27c);
        cShutdownTarget* const p = self->mUnk27c;
        if (p != 0) {
            self->mUnk27c = 0;
            u32* const vt = *(u32**)p;
            (*(void(**)(cShutdownTarget*))(vt + (0x08 / 4)))(p);
        }
    }
    if (self->mUnk2d0 != 0) {
        FUN_0081dce0(self->mUnk2d0);
        cShutdownTarget* const p = self->mUnk2d0;
        if (p != 0) {
            self->mUnk2d0 = 0;
            u32* const vt = *(u32**)p;
            (*(void(**)(cShutdownTarget*))(vt + (0x0c / 4)))(p);
        }
    }

    FUN_0080a5f0();
    self->mShutdownFlag = 0;

    // Broadcast the teardown ids to the message server.
    cMessageServer* const ms = FUN_0067dce0();
    u32* const msVt = *(u32**)ms;
    void* const idTarget = (void*)&self->mpMessageIdTarget;
    {
        MsgPostFn const post = (MsgPostFn)(msVt + (0x2c / 4));
        post(ms, idTarget, 0xf62def,    0xffffd8f1);
        post(ms, idTarget, 0x1ee1001,   0xffffd8f1);
        post(ms, idTarget, 0x1ee1003,   0xffffd8f1);
        post(ms, idTarget, 0x1ee100d,   0xffffd8f1);
        post(ms, idTarget, 0x1ee1006,   0xffffd8f1);
        post(ms, idTarget, 0x1ee1007,   0xffffd8f1);
        post(ms, idTarget, 0x1ee1010,   0xffffd8f1);
        post(ms, idTarget, 0x1ee1011,   0xffffd8f1);
        post(ms, idTarget, 0x1ee1008,   0xffffd8f1);
        post(ms, idTarget, 0x1ee1002,   0xffffd8f1);
        post(ms, idTarget, 0x546bbb8,   0xffffd8f1);
        post(ms, idTarget, 0x61205e6,   0xffffd8f1);
    }

    {
        void* const fontList = FUN_006895b0();
        u32* const fvt = *(u32**)fontList;
        (*(void(**)(void*, u32, u32))(fvt + (0x2c / 4)))(
            fontList, 0x1545188, 1);
    }
    {
        MsgPostFn const post = (MsgPostFn)(msVt + (0x2c / 4));
        post(ms, idTarget, *(u32*)0x1545188, 0xffffd8f1);
    }

    self->mUnk2dc = 0;

    if (self->mUnk268 != 0) {
        cShutdownTarget* const p = self->mUnk268;
        self->mUnk268 = 0;
        u32* const vt = *(u32**)p;
        (*(void(**)(cShutdownTarget*))(vt + (0x04 / 4)))(p);
    }
    if (self->mUnk26c != 0) {
        cShutdownTarget* const p = self->mUnk26c;
        self->mUnk26c = 0;
        u32* const vt = *(u32**)p;
        (*(void(**)(cShutdownTarget*))(vt + (0x0c / 4)))(p);
    }

    {
        cLayoutManager* const lm = FUN_0067de20();
        u32* const vt = *(u32**)lm;
        (*(void(**)(cLayoutManager*, u32))(vt + (0x34 / 4)))(
            lm, (u32)self->mUnk2d8);
    }
    if (self->mUnk2d8 != 0) {
        FUN_008028e0(self->mUnk2d8);
        cShutdownTarget* const p = self->mUnk2d8;
        if (p != 0) {
            self->mUnk2d8 = 0;
            u32* const vt = *(u32**)p;
            (*(void(**)(cShutdownTarget*))(vt + (0x04 / 4)))(p);
        }
    }

    if (self->mUnk244 != 0) {
        u32* const msVt2 = *(u32**)ms;
        (*(void(**)(cMessageServer*, void*, u32, u32))(msVt2 + (0x2c / 4)))(
            ms, idTarget, 0x366b9aa, 0xffffd8f1);
        cShutdownTarget* const p = self->mUnk244;
        if (p != 0) {
            self->mUnk244 = 0;
            u32* const vt = *(u32**)p;
            (*(void(**)(cShutdownTarget*))(vt + (0x08 / 4)))(p);
        }
    }

    {
        cShutdownTarget* const p = self->mUnk2a4;
        u32* const vt = *(u32**)p;
        (*(void(**)(cShutdownTarget*))(vt + (0x14 / 4)))(p);
    }
    {
        cWindowManager* const wm = FUN_0067dcd0();
        u32* const vt = *(u32**)wm;
        (*(void(**)(cWindowManager*, u32, u32, u32))(vt + (0x44 / 4)))(
            wm, (u32)self->mUnk2a4, win, win);
    }
    if (self->mUnk2a4 != 0) {
        cShutdownTarget* const p = self->mUnk2a4;
        self->mUnk2a4 = 0;
        u32* const vt = *(u32**)p;
        (*(void(**)(cShutdownTarget*))(vt + (0x08 / 4)))(p);
    }

    FUN_0067cbb0(0);

    if (self->mUnk274 != 0) {
        FUN_008353a0(self->mUnk274);
        cShutdownTarget* const p = self->mUnk274;
        if (p != 0) {
            self->mUnk274 = 0;
            u32* const vt = *(u32**)p;
            (*(void(**)(cShutdownTarget*))(vt + (0x08 / 4)))(p);
        }
    }
    if (self->mUnk270 != 0) {
        FUN_0067cbd0(0);
        FUN_0080fa20(self->mUnk270);
        cShutdownTarget* const p = self->mUnk270;
        u32* const vt = *(u32**)p;
        (*(void(**)(cShutdownTarget*))(vt + (0x04 / 4)))(p);
        self->mUnk270 = 0;
    }
    if (self->mUnk280 != 0) {
        FUN_008175c0(self->mUnk280);
        cShutdownTarget* const p = self->mUnk280;
        if (p != 0) {
            self->mUnk280 = 0;
            u32* const vt = *(u32**)p;
            (*(void(**)(cShutdownTarget*))(vt + (0x04 / 4)))(p);
        }
    }

    {
        cShutdownTarget** begin = self->mp2a8;
        cShutdownTarget** end = self->mp2ac;
        for (cShutdownTarget** it = begin; it != end; ++it) {
            FUN_00816990(*it);
        }
        begin = self->mp2a8;
        end = self->mp2ac;
        cShutdownTarget** pit = (cShutdownTarget**)FUN_006782c0(end, end, begin);
        while (pit < end) {
            cShutdownTarget* const p = *pit;
            if (p != 0) {
                u32* const vt = *(u32**)p;
                (*(void(**)(cShutdownTarget*))(vt + (0x04 / 4)))(p);
            }
            ++pit;
        }
        const int removed = (int)((u32)(end - begin) >> 2);
        self->mp2ac += (-removed);
    }

    {
        void* const lm = FUN_0080fee0(0);
        FUN_008116e0((cShutdownTarget*)lm);
    }
    {
        void* const lm = FUN_0080fee0(0);
        u32* const vt = *(u32**)lm;
        (*(void(**)(void*))(vt + (0x0c / 4)))(lm);
    }
    FUN_00961e80(self);

    if (self->mUnk260 != 0) {
        cShutdownTarget* const p = self->mUnk260;
        u32* const vt = *(u32**)p;
        (*(void(**)(cShutdownTarget*, u32, u32))(vt + (0x08 / 4)))(p, win, 1);
        (*(void(**)(cShutdownTarget*))(vt + (0x00 / 4)))(p);
        if (self->mUnk260 != 0) {
            cShutdownTarget* const q = self->mUnk260;
            u32* const vt2 = *(u32**)q;
            (*(void(**)(cShutdownTarget*, u32))(vt2 + (0x94 / 4)))(q, 1);
        }
        self->mUnk260 = 0;
        FUN_008138e0();

        cWindowManager* const lm = FUN_0067dcd0();
        if (lm != 0 && self->mUnk294 != 0) {
            u32* const vt = *(u32**)lm;
            (*(void(**)(cWindowManager*, u32, u32, u32))(vt + (0x44 / 4)))(
                lm, (u32)self->mUnk294, win, win);            cShutdownTarget* const p2 = self->mUnk294;
            u32* const vt2 = *(u32**)p2;
            (*(void(**)(cShutdownTarget*))(vt2 + (0x14 / 4)))(p2);
            if (self->mUnk294 != 0) {
                self->mUnk294 = 0;
                u32* const vt3 = *(u32**)p2;
                (*(void(**)(cShutdownTarget*))(vt3 + (0x08 / 4)))(p2);
            }
        }

        {
            void* const p = FUN_00885b00(0);
            if (p != 0) {
                u32* const vt = *(u32**)p;
                (*(void(**)(void*))(vt + (0x0c / 4)))(p);
                (*(void(**)(void*, u32))(vt + (0x00 / 4)))(p, 1);
            }
        }
        {
            u32* const slot = (u32*)0x164d348;
            slot[4] = 0;   // +0x10
            void* const p = FUN_00885af0(0);
            if (p != 0) {
                u32* const vt = *(u32**)p;
                (*(void(**)(void*, u32))(vt + (0x00 / 4)))(p, 1);
            }
        }
        FUN_0082f8a0();
    }

    if (self->mUnk264 != 0) {
        cShutdownTarget* const p = self->mUnk264;
        u32* const vt = *(u32**)p;
        (*(void(**)(cShutdownTarget*, u32))(vt + (0x00 / 4)))(p, 1);
        self->mUnk264 = 0;
    }

    FUN_00957f40(0);
    FUN_0067cba0(0);

    {
        cShutdownTarget* const p = (cShutdownTarget*)FUN_006b1f90((void*)0x11ac19c);
        if (p != 0) {
            u32* const vt = *(u32**)p;
            u32 rec[1] = { 0 };
            const bool ok = (*(bool(**)(cShutdownTarget*, const void*, u32,
                                        u32, u32, u32, u32, u32))(
                vt + (0x34 / 4)))(p, (const void*)0x1545484, win, (u32)&rec,
                                  2, 2, 1, 0);
            if (ok) {
                cShutdownTarget* const r = *(cShutdownTarget**)&rec[0];
                u32* const rVt = *(u32**)r;
                void* const child = (*(void*(**)(cShutdownTarget*))(
                    rVt + (0x18 / 4)))(r);
                u32* const cVt = *(u32**)child;
                (*(void(**)(void*, u32, void*))(cVt + (0x38 / 4)))(
                    child, 8, (void*)&self->mUnk250);
                (*(void(**)(cShutdownTarget*))(rVt + (0x24 / 4)))(r);
            }
            if (*(cShutdownTarget**)&rec[0] != 0) {
                cShutdownTarget* const r = *(cShutdownTarget**)&rec[0];
                u32* const rVt = *(u32**)r;
                (*(void(**)(cShutdownTarget*))(rVt + (0x08 / 4)))(r);
            }
        }
    }

    FUN_00889c80();
}
