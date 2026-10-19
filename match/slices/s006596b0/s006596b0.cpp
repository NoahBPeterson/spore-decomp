// slice s006596b0: SP::cSPUIAssetView rollover/cleanup methods.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

struct TextZoomNameS69 {
    void Shutdown();   // 0x00834e30
};

struct AVTarget;
struct AVOwner {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
    virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47();
    virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55();
    virtual void Detach(AVTarget* target);   // +0xe0
};
struct AVTarget {
    virtual void t0();
    virtual void Release();                  // +0x04
    virtual void t2();
    virtual void t3();
    virtual AVOwner* GetOwner();             // +0x10
};
struct AVZoom {
    virtual void z0();
    virtual void z1();
    virtual void Release();                  // +0x08
};
struct AssetViewS69 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12();
    virtual void OnDetach();                 // +0x34
    char pad04[0x20 - 4];
    int m20;                                 // +0x20
    char pad24[0x54 - 0x24];
    AVTarget* mpTarget;                      // +0x54
    char pad58[0x94 - 0x58];
    AVZoom* mpZoom;                          // +0x94
    void Cleanup();   // 0x00659e30
    void ReleaseTargets();   // 0x00659340
};

// @ 0x006596b0  cSPUIAssetView update (PARTIAL: 870-byte body).
void FUN_006596b0(void* self) { (void)self; }

// @ 0x00659a20  SP::cSPUIAssetView::OnRollover (PARTIAL: 1000-byte body).
void FUN_00659a20(void* self, void* ev) { (void)self; (void)ev; }

// @ 0x00659e30  SP::cSPUIAssetView::Cleanup
void AssetViewS69::Cleanup() {
    if (m20 != 0)
        OnDetach();
    if (mpZoom != 0) {
        ((TextZoomNameS69*)mpZoom)->Shutdown();
        if (mpZoom != 0) {
            AVZoom* p = mpZoom;
            mpZoom = 0;
            p->Release();
        }
    }
    ReleaseTargets();
    if (mpTarget != 0 && mpTarget->GetOwner() != 0) {
        mpTarget->GetOwner()->Detach(mpTarget);
        if (mpTarget != 0) {
            AVTarget* p = mpTarget;
            mpTarget = 0;
            p->Release();
        }
    }
}

// @ 0x00659ec0  cSPUIAssetView update (PARTIAL: 420-byte body).
void FUN_00659ec0(void* self) { (void)self; }
