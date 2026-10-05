// Slice s00667c80: SP::cSPUIFeedListItem - DoMessage (feed-item messages), SetName,
// QueryNumItems (number/icon refresh) and Update (per-frame animation).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef void  (__thiscall *FnVoidIII)(void*, int, int, int);
typedef void  (__thiscall *FnVoidIPI)(void*, unsigned, void*, int);
typedef int   (__thiscall *FnIntV)(void*);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl SP_AssetBrowser();
void* __cdecl SP_WindowManager();                 // 0x0067caa0
void* __cdecl SP_MessageServer();                 // 0x0067dcc0
void* __cdecl FUN_0067cb30();                      // 0x0067cb30
void* __cdecl FUN_00666b20(void* out, void* a, unsigned key);
void  __cdecl FUN_00667ac0(void* self);
void  __cdecl FUN_00667ae0(void* self);
void  __cdecl FUN_00668070(void* self);
void  __cdecl FUN_00667b00(void* self);            // OnLeftMouseDown
void  __cdecl FUN_0066b00_dummy();
void  __cdecl WString_Assign(void* dest, const wchar_t* first, const wchar_t* last);
bool  __cdecl FUN_0087da10(const wchar_t* a, void* b);
bool  __cdecl FUN_00805150(void* a, void* b);
unsigned char __cdecl StartBanMode(int id);        // 0x008d2fb0
int   __cdecl GetRecorderState();                  // 0x00435e90
void  __cdecl KillSetiEffects(int state, unsigned id);
void* __cdecl FUN_0054ea20(void* self, int a, int b);
void* __cdecl FUN_0054eac0(void* self, int a);

struct cSPUILayout {
    virtual void s0(); virtual void s1(); virtual int Release();
    void Shutdown(bool);
    void* FindWindowByID(unsigned id, int flag);   // 0x008105b0
};
struct Sub54 { unsigned char FUN_0054eac0(int v); void FUN_0054ea20(int a, int b); };

struct FeedItem {
    bool FUN_00667c80(void* a1, void* msg);
    void FUN_00668000(const wchar_t* s);
    void FUN_00668070();
    void FUN_00668550(int dt);
};

// -----------------------------------------------------------------------------
// @ 0x00667c80  SP::cSPUIFeedListItem::DoMessage
// -----------------------------------------------------------------------------
bool FeedItem::FUN_00667c80(void* a1, void* msg) {
    (void)a1;
    void* self = this;
    if (*(uint8_t*)((char*)self + 0xc3) && *(int*)((char*)msg + 8) != 0x1c &&
        *(int*)((char*)msg + 8) != 9)
        return false;

    uint32_t t = *(uint32_t*)((char*)msg + 8);
    if (t > 0x1b) {
        if (t == 0x1c) {
            // ---- case 0x1c
            if (*(int*)((char*)msg + 0xc) != 1) return false;
            if (*(uint8_t*)((char*)self + 0xc1)) {
                void* wm = SP_WindowManager();
                void* r = ((FnPtrV)VT(wm)[18])(wm);
                if (!FUN_00805150(*(void**)((char*)self + 0xa0), r)) {
                    *(uint8_t*)((char*)self + 0xc1) = 0;
                    FUN_00667ae0(self);
                }
            }
            if (*(void**)((char*)msg + 0x18) == *(void**)((char*)self + 0xa0)) return false;
            void* p = *(void**)((char*)msg + 0x18);
            ((FnVoid)VT(p)[0x42])(p);
            return false;
        }
        if (t != 0x287259f6) return false;

        // ---- case 0x287259f6 : window-id sub-dispatch
        switch (*(int*)((char*)msg + 0xc)) {
        case 0xd48f0e8a: {
            KillSetiEffects(GetRecorderState(), 0x6e2ce16d);
            void* ms = SP_MessageServer();
            ((FnVoidIPI)VT(ms)[5])(ms, 0x6134914, self, 0);
            return true;
        }
        case 0xb48e8be4: {
            KillSetiEffects(GetRecorderState(), 0x7bb89a55);
            if (!*(uint8_t*)((char*)self + 0x140)) {
                if (*(uint32_t*)((char*)self + 0x38) | *(uint32_t*)((char*)self + 0x3c)) {
                    void* ms = SP_MessageServer();
                    ((FnVoidIPI)VT(ms)[5])(ms, 0x6299932, (char*)self + 0x38, 0);
                }
            }
            return true;
        }
        case 0x948f0e66: {
            KillSetiEffects(GetRecorderState(), 0x32120868);
            void* ms = SP_MessageServer();
            ((FnVoidIPI)VT(ms)[5])(ms, 0x148f5c9d, 0, 0);
            return true;
        }
        case 0x748e61d2: {
            KillSetiEffects(GetRecorderState(), 0xabceb434);
            void* ms = SP_MessageServer();
            ((FnVoidIPI)VT(ms)[5])(ms, 0x5a86fa1, 0, 0);
            return true;
        }
        case 0x7c64df0:
        case 0x7c64218: {
            if (!*(void**)((char*)self + 0x94)) return true;
            if (!*(uint8_t*)((char*)self + 0xc2)) return true;
            KillSetiEffects(GetRecorderState(), 0xabceb434);
            bool bl = (*(int*)((char*)msg + 0xc) == 0x7c64218);
            void* eax = FUN_0067cb30();
            void* sub = *(void**)((char*)eax + 0x58);
            ((Sub54*)sub)->FUN_0054ea20(*(int*)((char*)self + 0x134), bl ? 1 : 0);
            void* layout = *(void**)((char*)self + 0x94);
            void* w = ((cSPUILayout*)layout)->FindWindowByID(0x7c64218, 1);
            if (w) {
                bool f = *(uint8_t*)((char*)self + 0xc2) && !bl;
                ((FnVoidII)VT(w)[31])(w, 1, f ? 1 : 0);
            }
            void* layout2 = *(void**)((char*)self + 0x94);
            void* w2 = ((cSPUILayout*)layout2)->FindWindowByID(0x7c64df0, 1);
            if (w2) {
                bool f = *(uint8_t*)((char*)self + 0xc2) && bl;
                ((FnVoidII)VT(w2)[31])(w2, 1, f ? 1 : 0);
            }
            return true;
        }
        default:
            return false;
        }
    }

    if (t == 0x1b) {
        // ---- case 0x1b
        if (*(int*)((char*)msg + 0xc) != 1) return false;
        if (!*(uint8_t*)((char*)self + 0xc1)) {
            unsigned char b1 = StartBanMode(0x3e8);
            unsigned char b2 = StartBanMode(0x3ea);
            unsigned char b3 = StartBanMode(0x3e9);
            if (!b1 && !b2 && !b3) {
                *(uint8_t*)((char*)self + 0xc1) = 1;
                FUN_00667ac0(self);
            }
        }
        if (*(void**)((char*)msg + 0x18) == *(void**)((char*)self + 0xa0)) return false;
        void* p = *(void**)((char*)msg + 0x18);
        ((FnVoid)VT(p)[0x41])(p);
        return false;
    }

    switch (t) {
    case 6: {
        if (*(void**)((char*)msg + 4) != *(void**)((char*)self + 0xa0)) return false;
        if (*(int*)((char*)msg + 0x18) != 0x3e8) return false;
        FUN_00667b00(self);
        return false;
    }
    case 9: {
        void* wm = SP_WindowManager();
        ((FnVoidIII)VT(wm)[4])(wm, (int)*(void**)((char*)self + 0xa0),
                               *(int*)((char*)self + 0x98), (int)msg);
        return false;
    }
    default:
        return false;
    }
}

// -----------------------------------------------------------------------------
// @ 0x00668000  SetName / assign the display string
// -----------------------------------------------------------------------------
void FeedItem::FUN_00668000(const wchar_t* s) {
    if (s && !FUN_0087da10(s, (char*)this + 0x18)) {
        const wchar_t* p = s;
        while (*p) ++p;
        WString_Assign((char*)this + 0x18, s, p);
        void* q = *(void**)((char*)this + 0xa4);
        if (q) {
            void* v = *(void**)((char*)this + 0x18);
            ((FnVoid)VT(q)[0x20])(q);
            (void)v;
        }
    }
}

// -----------------------------------------------------------------------------
// @ 0x00668070  SP::cSPUIFeedListItem::QueryNumItems  (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void FeedItem::FUN_00668070() {
    // Skeleton: the real body builds a large set of SPUI window-shade/scale animations
    // via the animator (cSPUIAnimator::AddAnimation/RemoveAnimation, SPUICreateWindowAnimation*,
    // SP::ColorRGBAToU32, Locale::SetNumberString, WStr_Format) - reconstructed only in outline.
    if (*(int*)((char*)this + 0x64) != -1 && *(void**)((char*)this + 0xb0) != 0) {
        void* browser = SP_AssetBrowser();
        if (browser) {
            browser = SP_AssetBrowser();
            if (browser && *(void**)((char*)browser + 0x18)) {
                // animation blocks omitted (partial)
            }
        }
    }
    if (!*(uint8_t*)((char*)this + 0xc2)) *(uint8_t*)((char*)this + 0x142) = 1;
    *(uint32_t*)((char*)this + 0x64) = *(uint32_t*)((char*)this + 0x60);
}

// -----------------------------------------------------------------------------
// @ 0x00668550  SP::cSPUIFeedListItem::Update  (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void FeedItem::FUN_00668550(int dt) {
    if (*(uint8_t*)((char*)this + 0x86)) {
        ((FeedItem*)this)->FUN_00668070();
        *(uint8_t*)((char*)this + 0x86) = 0;
    }
    float f = (dt < 0) ? (float)dt + 4294967296.0f : (float)dt;
    float a = f * 0.012f;
    if (a < 0.0f) a = 0.0f;
    if (a > 1.0f) a = 1.0f;
    float b = f * 0.0065f;
    if (b < 0.0f) b = 0.0f;
    if (b > 1.0f) b = 1.0f;
    (void)a; (void)b;
    if (*(float*)((char*)this + 0x8c) > 0.0f) {
        float v = *(float*)((char*)this + 0x8c) - f * 0.001f;
        *(float*)((char*)this + 0x8c) = v;
        if (v <= 0.0f) {
            *(float*)((char*)this + 0x8c) = 0.0f;
            *(uint8_t*)((char*)this + 0x84) = 0;
        }
    }
    if (*(float*)((char*)this + 0x88) > 0.0f) {
        float v = *(float*)((char*)this + 0x88) - f * 0.001f;
        *(float*)((char*)this + 0x88) = v;
        if (v <= 0.0f) {
            *(float*)((char*)this + 0x88) = 0.0f;
            *(uint8_t*)((char*)this + 0x85) = 0;
        }
    }
}
