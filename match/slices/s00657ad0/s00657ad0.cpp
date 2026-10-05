// slice s00657ad0: SP::cSPUIAssetView/UI::AssetDiscovery_View helpers.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

struct cSPUILayout {
    void SetReloadCallback(void* fn, void* self);   // 0x00810090 (thiscall)
};
extern "C" void FUN_00657930(void*, int);           // 0x00657930
void FUN_00657e20(void* obj, int arg);              // 0x00657e20 (cdecl)

struct AssetView {
    void SetWindowArea(char animate);   // 0x00657ad0
    char IsReady();                     // 0x00657dd0
    void OnDetach();                    // 0x00657e00
    void UpdateVerbIcon();              // 0x00657e60
};

// @ 0x00657ad0  SP::cSPUIAssetView::SetWindowArea(bool animate)
void AssetView::SetWindowArea(char animate) {
    char* s = (char*)this;
    if (!*(void**)(s + 0x4c) || !*(void**)(s + 0x50))
        return;
    {
        void* w = *(void**)(s + 0x4c);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x7c))(w, 1, animate);
    }
    {
        void* w = *(void**)(s + 0x50);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x7c))(w, 1, animate);
    }
    FUN_00657930(this, s[0x15]);
    if (!*(void**)(s + 0x28) || !*(void**)(s + 0x24) || !s[0xfc])
        return;
    void* target = *(void**)(s + 0x24);
    float* r = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)target + 0x38))(target);
    float x0 = r[0], y0 = r[1], x1 = r[2], y1 = r[3];
    if (!animate) {
        void* src = *(void**)(s + 0x4c);
        float* r2 = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)src + 0x34))(src);
        y1 = (r2[3] - r2[1]) + y1;
    }
    void* dst = *(void**)(s + 0x28);
    (*(void(__thiscall**)(void*, float, float))((char*)*(void**)dst + 0x74))(dst, x1 - x0,
                                                                             y1 - y0);
}

// @ 0x00657dd0  bool SP::cSPUIAssetView::IsAnimTargetReady()
char AssetView::IsReady() {
    char* s = (char*)this;
    void* p = *(void**)(s + 0x98);
    if (!p || !(*(unsigned char*)((char*)p + 4) & 1))
        return 0;
    void* q = *(void**)(s + 0x9c);
    if (!q || !(*(unsigned char*)((char*)q + 4) & 1))
        return 0;
    return 1;
}

// @ 0x00657e00  SP::cSPUIAssetView::OnDetach
void AssetView::OnDetach() {
    char* s = (char*)this;
    void* layout = *(void**)(s + 0x20);
    if (layout)
        ((cSPUILayout*)layout)->SetReloadCallback(0, 0);
    (*(void(__thiscall**)(void*))((char*)*(void**)s + 0x44))(s);
}

// @ 0x00657e20  select-slot helper (find child by id 0x0105a93d)
void FUN_00657e20(void* obj, int arg) {
    if (!obj)
        return;
    void* r = (*(void*(__thiscall**)(void*, int))((char*)*(void**)obj + 0xc))(obj, 0x105a93d);
    if (!r)
        return;
    (*(void(__thiscall**)(void*, int))((char*)*(void**)r + 0x14))(r, arg);
    (*(void(__thiscall**)(void*, int, int))((char*)*(void**)obj + 0x7c))(obj, 1, 1);
}

// @ 0x00657e60  SP::cSPUIAssetView::UpdateVerbIcon
void AssetView::UpdateVerbIcon() {
    char* s = (char*)this;
    void* p = *(void**)(s + 0x90);
    if (!p)
        return;
    int v = (*(int(__thiscall**)(void*))((char*)*(void**)p + 0x38))(p);
    if (v > 0x7fffffff)
        return;
    void* obj = *(void**)(s + 0x74);
    switch (v) {
    case -2: FUN_00657e20(obj, 6); return;
    case -1: return;
    case 0:  FUN_00657e20(obj, 0); return;
    case 1:  FUN_00657e20(obj, 1); return;
    case 2:  FUN_00657e20(obj, 5); return;
    case 3:  FUN_00657e20(obj, 2); return;
    case 4:  FUN_00657e20(obj, 3); return;
    case 5:  FUN_00657e20(obj, 4); return;
    default: return;
    }
}

// @ 0x00657bc0  SP::cSPUIAssetView key handler (PARTIAL: switch head + window
// manager paths; remaining branches approximate).
char FUN_00657bc0(void* self, void* ev) {
    char* s = (char*)self;
    if (!s[0xf5])
        return 0;
    int key = *(int*)((char*)ev + 8);
    if (key == 0x1b)
        return 1;
    if (key == 6) {
        void* w = *(void**)(s + 0x28);
        (void)w;
        return 1;
    }
    if (key == 7) {
        void* w = *(void**)(s + 0x28);
        (void)w;
        return 1;
    }
    if (key == 8) {
        void* w = *(void**)(s + 0x28);
        (void)w;
        return 1;
    }
    return 0;
}

// @ 0x00657f70  UI::AssetDiscovery_View::AssetDiscovery_View (PARTIAL skeleton)
void* FUN_00657f70(void* self, void* parent) {
    (void)parent;
    return self;
}

// @ 0x006580b0  (PARTIAL skeleton: 576-byte UI update)
void FUN_006580b0(void* self) { (void)self; }

// @ 0x006582f0  (PARTIAL skeleton: 330-byte UI update)
void FUN_006582f0(void* self) { (void)self; }

// @ 0x00658440  (PARTIAL skeleton: 1417-byte UI update)
void FUN_00658440(void* self) { (void)self; }
