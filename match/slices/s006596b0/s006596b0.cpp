// slice s006596b0: SP::cSPUIAssetView rollover/cleanup methods.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00834e30(void*);   // 0x00834e30
extern "C" void FUN_00659340(void*);   // 0x00659340

struct AssetViewS69 {
    void Cleanup();   // 0x00659e30
};

// @ 0x006596b0  cSPUIAssetView update (PARTIAL: 870-byte body).
void FUN_006596b0(void* self) { (void)self; }

// @ 0x00659a20  SP::cSPUIAssetView::OnRollover (PARTIAL: 1000-byte body).
void FUN_00659a20(void* self, void* ev) { (void)self; (void)ev; }

// @ 0x00659e30  SP::cSPUIAssetView::Cleanup
void AssetViewS69::Cleanup() {
    char* s = (char*)this;
    if (*(void**)(s + 0x20))
        (*(void(__thiscall**)(void*))((char*)*(void**)s + 0x34))(s);
    void* p = *(void**)(s + 0x94);
    if (p) {
        FUN_00834e30(p);
        void* q = *(void**)(s + 0x94);
        if (q) {
            *(void**)(s + 0x94) = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)q + 8))(q);
        }
    }
    FUN_00659340(this);
    void* h = *(void**)(s + 0x54);
    if (h) {
        void* r = (*(void*(__thiscall**)(void*))((char*)*(void**)h + 0x10))(h);
        if (r) {
            void* r2 = (*(void*(__thiscall**)(void*))((char*)*(void**)h + 0x10))(h);
            (*(void(__thiscall**)(void*, void*))((char*)*(void**)r2 + 0xe0))(r2, h);
            void* q = *(void**)(s + 0x54);
            if (q) {
                *(void**)(s + 0x54) = 0;
                (*(void(__thiscall**)(void*))((char*)*(void**)q + 4))(q);
            }
        }
    }
}

// @ 0x00659ec0  cSPUIAssetView update (PARTIAL: 420-byte body).
void FUN_00659ec0(void* self) { (void)self; }
