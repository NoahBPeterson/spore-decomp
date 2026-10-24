// Slice s0064bc50 -- cSPUIAssetBrowser launch / update / message handling.
// Module flags: /O2 /MD /Gy /TP /GS-.
#include "types.h"

// Argument block built by Launch for AdvancedLaunch (0x48 bytes).
struct LaunchParams {
    uint32_t f00;
    uint32_t f04, f08, f0c;
    uint8_t  f10, f11, f12, f13, f14;
    uint8_t  pad15[3];
    uint32_t f18, f1c, f20;
    uint8_t  f24;
    uint8_t  pad25[3];
    uint32_t f28;
    uint8_t  f2c;
    uint8_t  pad2d[3];
    uint32_t f30;
    uint32_t f34;
    uint32_t f38;
    uint32_t f3c, f40, f44;
};

extern "C" void __cdecl AdvancedLaunch(LaunchParams* p);   // 0x0064a990

// @ 0x0064bc50
void __cdecl Launch(uint32_t a, uint32_t b, uint32_t c) {
    LaunchParams p;
    p.f04 = 0;
    p.f08 = 0;
    p.f0c = 0;
    p.f10 = 0;
    p.f11 = 0;
    p.f12 = 0;
    p.f14 = 0;
    p.f18 = 0;
    p.f1c = 0;
    p.f20 = 0;
    p.f28 = 0;
    p.f2c = 0;
    p.f3c = 0;
    p.f40 = 0;
    p.f44 = 0;
    p.f00 = a;
    const uint32_t one = 1;
    p.f13 = (uint8_t)one;
    p.f24 = (uint8_t)one;
    p.f34 = one;
    p.f38 = b;
    p.f30 = c;
    AdvancedLaunch(&p);
}

// ---------------------------------------------------------------------------
// Large methods; reconstructed only in outline (partial.txt).
// ---------------------------------------------------------------------------
// @ 0x0064bcd0
void __fastcall sub_64bcd0(void*) {}
// @ 0x0064c0d0
void __fastcall sub_64c0d0(void*) {}
// @ 0x0064c280
static volatile int s_64c280_sink;
__declspec(noinline) void __fastcall sub_64c280(void* self) {
    s_64c280_sink = (int)(size_t)self;
}

// ---------------------------------------------------------------------------
// cSPUIAssetBrowser::Update (0x0064c400)
// ---------------------------------------------------------------------------
struct AssetEntry {
    char pad[0x10];
    void* mpObject;
};

struct StopwatchData {
    uint32_t f00, f04, f08, f0c;
};

struct cSPUIAssetBrowserLayout {
    char pad00[0x14];
    void* mpAnimator;             // +0x14
    void* mpSomething18;          // +0x18
    unsigned char mActive;        // +0x1c
    char pad1d[2];
    unsigned char mField1f;       // +0x1f
    char pad20[0x1c];
    float mTimer;                 // +0x3c
    StopwatchData mStopwatch;     // +0x40
    char pad50[0xc];
    void* mpSomething5c;          // +0x5c
    char pad60[4];
    void* mpSomething64;          // +0x64
    char pad68[0x18];
    void* mpSomething80;          // +0x80
    void* mpSomething84;          // +0x84
    char pad88[0x30];
    void* mpSomethingB8;          // +0xb8
    void* mpSomethingBC;          // +0xbc
    void* mpSomethingC0;          // +0xc0
    char padC4[4];
    void* mpSomethingC8;          // +0xc8
    AssetEntry* mpEntriesBegin;   // +0xcc
    AssetEntry* mpEntriesEnd;     // +0xd0
    char padD4[0x10];
    void* mpVec2Begin;            // +0xe4
    void* mpVec2End;              // +0xe8
    char padEC[0x6c];
    void* mpSomething158;         // +0x158
    char pad15C[0x6c];
    unsigned char mExpanded;      // +0x1c8
    char pad1C9[0x85];
    unsigned char mField24e;      // +0x24e
};

typedef void (__fastcall *VCall_Int)(void*, int, int);
typedef void (__fastcall *VCall_IntInt)(void*, int, int, int);
typedef unsigned int (__fastcall *VCall_UInt)(void*);
typedef bool (__fastcall *VCall_Bool_UIntInt)(void*, int, unsigned int, int);
typedef bool (__fastcall *VCall_Bool_UInt)(void*, int, unsigned int);
typedef void (__fastcall *VCall_Ptr)(void*, int, void*);

static void** VTableOf(void* p) { return *(void***)p; }

void __fastcall FUN_00663350(void* self, int, int delta);                 // 0x00663350
void __fastcall FUN_00655ed0(void* self, int, int delta);                 // 0x00655ed0
void __fastcall FUN_010829f0(void* self, int, int delta);                 // 0x010829f0
void __fastcall FUN_007f63b0(void* self);                                 // 0x007f63b0
void* __cdecl FUN_0067cab0(void);                                         // 0x0067cab0
void __fastcall FUN_00801380(void* self);                                 // 0x00801380
void* __cdecl FUN_00401010(void);                                         // 0x00401010
int __cdecl FUN_004e1c30(void* tool, int id, int defaultValue);            // 0x004e1c30
unsigned long long __fastcall FUN_0093a5e0(StopwatchData* self);          // 0x0093a5e0
void __fastcall FUN_0050f740(void* self, int, void* begin, void* end);     // 0x0050f740
void __cdecl FUN_00809db0(void* p, void* message);                        // 0x00809db0
bool __fastcall FUN_006428b0(void* self);                                 // 0x006428b0
bool __fastcall FUN_00642910(void* self);                                 // 0x00642910
void __fastcall FUN_00644040(void* self, int, int value);                 // 0x00644040

// @ 0x0064c400
void __fastcall sub_64c400(cSPUIAssetBrowserLayout* self, int, int delta) {
    if (self->mActive) {
        if (self->mpSomethingC0)
            FUN_00663350(self->mpSomethingC0, 0, delta);
        if (self->mpSomethingBC)
            FUN_00655ed0(self->mpSomethingBC, 0, delta);
        if (self->mpSomething158)
            ((VCall_Int)VTableOf(self->mpSomething158)[0x14 / 4])(self->mpSomething158, 0, delta);
        if (self->mpSomethingC8)
            FUN_010829f0(self->mpSomethingC8, 0, delta);
        if (self->mpAnimator)
            FUN_007f63b0(self->mpAnimator);

        if (self->mTimer > 0.0f) {
            volatile float timerValue = self->mTimer;
            volatile float scale = (float)0.001;
            timerValue = timerValue - (float)(unsigned int)delta * scale;
            self->mTimer = timerValue;
            if (timerValue <= 0.0f && self->mpSomething84)
                ((VCall_IntInt)VTableOf(self->mpSomething84)[0x7c / 4])(self->mpSomething84, 0, 1, 0);
        }

        if (self->mExpanded) {
            for (int i = 0; i < (int)(self->mpEntriesEnd - self->mpEntriesBegin); ++i) {
                void* p = self->mpEntriesBegin[i].mpObject;
                if (!p) continue;
                unsigned int value = ((VCall_UInt)VTableOf(p)[0x40 / 4])(p);
                void* q = FUN_00401010();
                if (!((VCall_Bool_UIntInt)VTableOf(q)[0x1c / 4])(q, 0, value, 1)) {
                    q = FUN_00401010();
                    if (((VCall_Bool_UInt)VTableOf(q)[0x3c / 4])(q, 0, value))
                        goto skip_expanded_cleanup;
                }
            }
            {
                FUN_00801380(FUN_0067cab0());
                if (self->mpSomething80 && self->mpSomething5c) {
                    ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 1, self->mActive);
                    ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 0x40, 0);
                    if (self->mpSomething64)
                        ((VCall_Ptr)VTableOf(self->mpSomething5c)[0xe8 / 4])(self->mpSomething5c, 0, self->mpSomething64);
                    self->mField1f = 0;
                }
                self->mExpanded = 0;
                FUN_0050f740(&self->mpVec2Begin, 0, self->mpVec2Begin, self->mpVec2End);
                sub_64c280(self);
            }
        skip_expanded_cleanup: ;
        }

        int timeout = 2000;
        if (self->mpSomething18)
            timeout = FUN_004e1c30(self->mpSomething18, 0x91756c5, 2000);
        unsigned long long elapsed = FUN_0093a5e0(&self->mStopwatch);
        if (elapsed > (unsigned long long)(long long)timeout) {
            FUN_00801380(FUN_0067cab0());
            self->mStopwatch.f00 = 0;
            self->mStopwatch.f04 = 0;
            self->mStopwatch.f08 = 0;
            self->mStopwatch.f0c = 0;
            self->mField24e = 0;
            if (self->mpSomething80 && self->mpSomething5c) {
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 1, self->mActive);
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 0x40, 0);
                if (self->mpSomething64)
                    ((VCall_Ptr)VTableOf(self->mpSomething5c)[0xe8 / 4])(self->mpSomething5c, 0, self->mpSomething64);
                self->mField1f = 0;
            }
            FUN_00809db0((char*)self + 4, (void*)0x1525840);
        }
    }

    if (self->mpSomethingB8 && FUN_006428b0(self->mpSomethingB8) && !FUN_00642910(self->mpSomethingB8))
        FUN_00644040(self->mpSomethingB8, 0, 0);
}
// @ 0x0064c6b0
void __fastcall sub_64c6b0(void*) {}
