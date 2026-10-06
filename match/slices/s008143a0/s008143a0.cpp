// Slice s008143a0 (w2g7 #2), 32-bit MSVC 2008 SP1.
// cSPUIMainWin message/key handling and AutoRefCount vector helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

static inline void** Vtbl(void* o) { return *(void***)o; }

extern "C" void* __cdecl GetManager();
extern "C" void* __cdecl SP_AppSystem();
extern "C" void* __cdecl SP_MovieSystem();

// refcounted element (ILogReporter-ish)
struct Elem {
    virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
    virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
    virtual void e08(); virtual void e09();
    void OnWindowClosed();   // 0x816990
};

// eastl::vector<AutoRefCount<Elem>> prefix
struct Vec {
    void* mBegin;   // +0
    void* mEnd;     // +4
    void* mCap;     // +8
    void erase(void* first, void* last);
};

void __cdecl CopyImpl(void* first, void* last, void* dst);   // 0x6782c0
void __cdecl FUN_00814a30(void*, void**);                    // 0x814a30

struct WinBase { void SetArea(int); };
struct WinSub : WinBase {};

struct MainWin {
    char pad0[0x4];
    WinSub win;                 // +0x4
    char pad1[0x220 - 0x4 - sizeof(WinSub)];
    uint8_t b220;               // +0x220
    uint8_t b221;               // +0x221
    char pad2[0x268 - 0x222];
    void* mp268;                // +0x268
    void* mp26c;                // +0x26c
    char pad3[0x28d - 0x270];
    uint8_t b28d;               // +0x28d
    char pad4[0x2a8 - 0x28e];
    Vec   mVec;                 // +0x2a8

    void OnKeyDown();                  // 0x8143a0
    void MovieToggle();                // 0x8145d0
    bool SaveReadme(int);              // 0x8148b0
    bool KeyHandler2(int a, int key, int mod);  // 0x814d50
    void HandleMessage(unsigned id, int* msg);  // 0x814e40
    void RemoveElem(int val);          // 0x815310
    void AddElem(Elem* p);             // 0x815370
    void CloseAll();                   // 0x8153e0
};

struct Y2 {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08();
    virtual bool a09(int, int);   // 0x24
    virtual bool a0a(int, int);   // 0x28
};
struct X2 {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b0a();
    virtual Y2*  b0b();           // 0x2c
    virtual void b0c(); virtual void b0d();
    virtual Y2*  b0e();           // 0x38
};

void* __cdecl FUN_0067de00();
void __cdecl FUN_0067dd50();
void __cdecl SP_ConfigManager();
void __cdecl EA_DateTime_Set(int);
int  __cdecl EA_DateTime_GetParameter(void*, int);
void __cdecl WStr_Format(void*, const wchar_t*, ...);
void* __cdecl FUN_00688cd0();

bool __cdecl sOnEnterEscKeys(int, int, int);   // 0x80a310

// @ 0x00814d50
bool MainWin::KeyHandler2(int a, int key, int mod) {
    if (b28d) return true;
    if ((key == 0x1b || key == 0xd) && mod == 0 && sOnEnterEscKeys(a, key, 0)) return true;
    if (key == 0x56) {
        if (mod == 0) { MovieToggle(); return true; }
    } else if (key == 0x70) {
        void* as = SP_AppSystem();
        if (((bool(__thiscall*)(void*))Vtbl(as)[0x54 / 4])(as) && SaveReadme(mod)) return true;
    }
    if (b220) {
        if (mp268) {
            X2* p = (X2*)mp268;
            if (p->b0b()->a09(key, mod)) return true;
        }
        if (mp26c) {
            X2* q = (X2*)mp26c;
            if (q->b0e()->a0a(key, mod)) return true;
        }
    }
    if (key == 0x43 && mod == 0) { OnKeyDown(); return true; }
    return false;
}

// @ 0x00815310
void MainWin::RemoveElem(int val) {
    Vec* v = &mVec;
    Elem** pi = (Elem**)v->mBegin;
    Elem** end = (Elem**)v->mEnd;
    for (; pi != end; ++pi) {
        if ((int)*pi == val) {
            if (pi + 1 < (Elem**)v->mEnd) CopyImpl(pi + 1, v->mEnd, pi);
            v->mEnd = (char*)v->mEnd - 4;
            Elem* last = *(Elem**)v->mEnd;
            if (last) last->e01();
            return;
        }
    }
}

// @ 0x00815370
void MainWin::AddElem(Elem* p) {
    b221 = 0;
    if (p) p->e00();
    Elem* tmp = p;
    if (mVec.mEnd < mVec.mCap) {
        Elem** slot = (Elem**)mVec.mEnd;
        mVec.mEnd = (char*)mVec.mEnd + 4;
        if (slot) {
            *slot = p;
            if (p) p->e00();
        }
    } else {
        FUN_00814a30(mVec.mEnd, (void**)&tmp);
    }
    if (tmp) tmp->e01();
}

// @ 0x008153e0
void MainWin::CloseAll() {
    Vec* v = &mVec;
    Elem** i = (Elem**)mVec.mBegin;
    Elem** end = (Elem**)mVec.mEnd;
    for (; i != end; ++i) (*i)->OnWindowClosed();
    v->erase(mVec.mBegin, mVec.mEnd);
}

// ---------------------------------------------------------------------------
// remaining (approximate / partial)
// ---------------------------------------------------------------------------
// @ 0x008143a0  (partial: SaveGame-name flow only)
void MainWin::OnKeyDown() {
    void* p = FUN_0067de00();
    if (!p) return;
    FUN_0067dd50();
    // heavy Date/time + sprintf naming flow summarised
}

// @ 0x008145d0  (partial)
void MainWin::MovieToggle() {
    void* ms = SP_MovieSystem();
    if (!ms) return;
    if (((bool(__thiscall*)(void*))Vtbl(ms)[0x30 / 4])(ms)) {
        ((void(__thiscall*)(void*))Vtbl(ms)[0x38 / 4])(ms);
        return;
    }
    // movie-area property flow summarised
}

// @ 0x008148b0  (partial: README open flow)
bool MainWin::SaveReadme(int mode) {
    if (mode != 0) return false;
    void* f = FUN_00688cd0();
    (void)f;
    return true;
}

// @ 0x008149c0  (string SSO construction)
void* StringConstruct(void* self, void* str, unsigned idx) {
    return self;
}

// @ 0x00814b80  (text style callback)
void sTextStyleCallback(int n, void* args, void* p) {
    if (n < 2) return;
}

// @ 0x00814e40  (partial: message dispatch)
void MainWin::HandleMessage(unsigned id, int* msg) {
    (void)id; (void)msg;
}
