// slice s006589d0: SP::cSPUIAssetView mouse/update methods.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00657810(void*);   // 0x00657810 (Show)

struct AssetViewS68 {
    void SetPos(float x, float y, char snap);   // 0x00658e00 (ret 0xc)
};

// @ 0x006589d0  SP::cSPUIAssetView::OnLeftMouseDown (PARTIAL: 670-byte body).
void FUN_006589d0(void* self, void* ev) { (void)self; (void)ev; }

// @ 0x00658c70  SP::cSPUIAssetView helper (PARTIAL: 386-byte body).
void FUN_00658c70(void* self) { (void)self; }

// @ 0x00658e00  SP::cSPUIAssetView::SetPos(x, y, snap)
void AssetViewS68::SetPos(float x, float y, char snap) {
    char* s = (char*)this;
    *(float*)(s + 0xc) = x;
    *(float*)(s + 0x10) = y;
    void* w = *(void**)(s + 0x28);
    if (w && !snap) {
        (*(void(__thiscall**)(void*, float, float))((char*)*(void**)w + 0x64))(w, x, y);
    }
    w = *(void**)(s + 0x28);
    if (w) {
        float* p = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)w + 0x34))(w);
        if (p[0] != *(float*)(s + 0xc) || p[1] != *(float*)(s + 0x10))
            FUN_00657810(s);
    }
}

// @ 0x00658e80  SP::cSPUIAssetView::SelectAsset update (PARTIAL: 994-byte body).
void FUN_00658e80(void* self, void* a, void* b, void* c) { (void)self; (void)a; (void)b; (void)c; }

// @ 0x00659270  cSPUIAssetView helper (PARTIAL: 203-byte body).
void FUN_00659270(void* self) { (void)self; }

// @ 0x00659340  cSPUIAssetView release/destroy helper (PARTIAL: 122-byte body).
void FUN_00659340(void* self) { (void)self; }

// @ 0x006593c0  cSPUIAssetView helper (PARTIAL: 752-byte body).
void FUN_006593c0(void* self) { (void)self; }
