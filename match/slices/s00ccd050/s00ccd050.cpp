// Slice s00ccd050: 0x00CCD050..0x00CCDC30.
//  0x00ccd050  SP::cTribeDisplayStrategy::Deactivate            (848 B)
//  0x00ccd3a0  SP::cTribeDisplayStrategy::UpdateTargetedTreeEffects (1277 B)
//  0x00ccd8a0  SP::cTribeDisplayStrategy::MakeTribeIcons         (902 B)
//  0x00ccdc30  SP::cTribeDisplayStrategy::DrawLayer              (310 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct cSphere {
    char  pad_00[0x10f0];
    float mA;      // +0x10f0
    float mB;      // +0x10f4
};

struct cTerrainEditor {
    cSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};

struct cNounMgr {
    void* SetGameDataOwner2();            // 0x00bfc5f0
};

struct cCam {
    void*  FUN_00b13900(void* out);       // 0x00b13900
    float* FUN_00b10200();                // 0x00b10200
};

struct c70Obj {
    void FUN_00e0c490(float* b, void* a); // 0x00e0c490
};

struct c50Obj {
    void FUN_00e313c0(float f);           // 0x00e313c0
};

struct c78Obj {
    void FUN_00ccb2c0(float f);           // 0x00ccb2c0
};

struct cProgressBar {
    void Update(float progress, void* amount);  // 0x00e29da0
};

struct cTribe {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0();
    virtual void* v0a4();   // +0xa4
};

struct tLocal3 { int a, b, c; };

struct cTribeDisplayStrategy {
    char     pad_00[0x50];
    c50Obj*  m50;      // +0x50
    char     pad_54[0x70 - 0x54];
    c70Obj*  m70;      // +0x70
    char     pad_74[0x78 - 0x74];
    c78Obj*  m78;      // +0x78
    char     pad_7c[0xb0 - 0x7c];
    cProgressBar* mb0; // +0xb0

    void DrawLayer(void* p2, unsigned p3, unsigned p4);   // 0x00ccdc30
    void FUN_00ccc640();     // 0x00ccc640
    void FUN_00ccd3a0();     // 0x00ccd3a0
    void OnWinProcAdd(void* p2);   // 0x010829f0
};

void  VerbTray_Update(float f);   // 0x00d4a930
void* GetCameraCtl();             // 0x00b3d280
void* NounManager();              // 0x00b3d300
void  FUN_00cc9890();             // 0x00cc9890

// ---------------------------------------------------------------- 0x00ccd050

// @ 0x00ccd050
void FUN_00ccd050(void) {}

// ---------------------------------------------------------------- 0x00ccd3a0

// @ 0x00ccd3a0
void FUN_00ccd3a0(void) {}

// ---------------------------------------------------------------- 0x00ccd8a0

// @ 0x00ccd8a0
void FUN_00ccd8a0(void) {}

// ---------------------------------------------------------------- 0x00ccdc30

// @ 0x00ccdc30
void cTribeDisplayStrategy::DrawLayer(void* p2, unsigned p3, unsigned p4)
{
    float f = (float)p3;
    VerbTray_Update(f * 0.0001f);

    cCam* cam = (cCam*)GetCameraCtl();
    if (cam != 0 && m70 != 0) {
        tLocal3 local_c;
        void* a = cam->FUN_00b13900(&local_c);
        float* b = cam->FUN_00b10200();
        m70->FUN_00e0c490(b, a);
    }

    cNounMgr* nm = (cNounMgr*)NounManager();
    cTribe* tribe = (cTribe*)nm->SetGameDataOwner2();
    if (tribe != 0) {
        cTerrainEditor* te = (cTerrainEditor*)NounManager();
        cSphere* s = te->GetCurrentTerrainSphere();
        float* q = &s->mA;
        if (s->mA > s->mB)
            q = &s->mB;
        float ratio = *q / s->mB;
        if (mb0 != 0) {
            void* v = tribe->v0a4();
            mb0->Update(ratio, v);
        }
        FUN_00ccc640();
        FUN_00ccd3a0();
        FUN_00cc9890();
        m78->FUN_00ccb2c0(f * 0.001f);
        m50->FUN_00e313c0((float)p4 * 0.001f);
        OnWinProcAdd(p2);
    }
}