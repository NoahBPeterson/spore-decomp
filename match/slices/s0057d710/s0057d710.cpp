// slice s0057d710 — SP::cAppModeEditorBase helpers (oversized FUN_0057d710 stubbed).
#include "types.h"

struct cVector4 {
    float x, y, z, w;
    cVector4() {}
    cVector4(const cVector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};
extern cVector4 gTorsoColor;   // 0x0150ce40 (x,y,z,w)
extern char gVtbl0;
extern char gVtbl1;
void* FUN_00401060();
void  FUN_0043cfc0(int, int);
void  operator delete[](void*);

struct cUnk0057d710 { void FUN_0057d710(); };

struct cEditorModel {
    void FUN_004ad110();       // 0x004ad110
};

struct cSkinManager {
    void* GetSkin(bool create);          // 0x004c49e0
    void* GetSceneObject(int flags);     // 0x004c45d0
    void  FUN_005d1600(int a, int b);    // 0x005d1600
};

struct cAnimCreatureManager {
    void* GetCreature(void* viewer);     // 0x0059ca70
};

struct cTrayRow { bool* mpStates; char pad0[0x10]; };   // 0x14 bytes

struct cSphereListItem {
    char pad0[0x28];
    char* mpBegin;      // +0x28
    char* mpEnd;        // +0x2c
};

struct cAppModeEditorBase {
    char pad0[0x70];
    float m70;                          // +0x70
    char pad74[0x84 - 0x74];
    void* mSaveModelWorld;              // +0x84
    char pad88[0x98 - 0x88];
    cEditorModel* mEditorSaveModel;     // +0x98
    char pad9c[0xd4 - 0x9c];
    void* mD4;                          // +0xd4
    char padD8[0xe9 - 0xd8];
    bool mTorsoSelected;                // +0xe9
    char padEA[0x14c - 0xea];
    cSkinManager* mSaveSkinManager;     // +0x14c
    cSkinManager* mSaveLoadFactory;     // +0x150
    char pad154[0x1cc - 0x154];
    void* mLaunchData;                  // +0x1cc
    char pad1d0[0x360 - 0x1d0];
    cAnimCreatureManager* mAnimCreatureManager;  // +0x360
    void* mShadowViewer;                // +0x364
    char pad368[0x385 - 0x368];
    bool mAnimatingCreatureActive;      // +0x385
    char pad386[0x472 - 0x386];
    bool m472;
    char pad473[1];
    float m474;
    char pad478[0x480 - 0x478];
    float m480;
    float m484;
    char pad488[0x48c - 0x488];
    int m48c;
    int m490;
    char pad494[0x4d4 - 0x494];
    bool m4d4;
    char pad4d5[3];
    void* m4d8;                         // +0x4d8
    char pad4dc[0x508 - 0x4dc];
    cTrayRow mTrayRows[6];              // +0x508

    void RemoveTorsoFromEffectsMask();                    // 0x005772b0
    void AddTorsoToEffectsMask(cVector4 v);              // 0x0057a610
    void SetTorsoIsSelected(bool);
    void FUN_00573970();                                  // 0x00573970
    int  GetCurrentTrayRow();                             // 0x00576140
    void UpdateAnimatedCreature();                        // 0x0057ae10
    void FUN_0057e220(float, float, void*, int);
    void FUN_0057e340(bool);
};

// @ 0x0057e160  SP::cAppModeEditorBase::SetTorsoIsSelected
void cAppModeEditorBase::SetTorsoIsSelected(bool selected)
{
    if (selected == mTorsoSelected)
        return;
    if (selected)
        AddTorsoToEffectsMask(gTorsoColor);
    else
        RemoveTorsoFromEffectsMask();
    mTorsoSelected = selected;
}

// ---------------------------------------------------------------------------------------------
// 0x0057e1d0 — scalar deleting destructor of a resourced object (ret 4).
struct cResourcedObject {
    void* mpVtbl0;      // +0
    void* mpVtbl1;      // +4
    char  pad8[4];
    char* mpBegin;      // +0xc
    char* mpEnd;        // +0x10
    char* mpCapacity;   // +0x14
    cResourcedObject* Delete(unsigned flags);
};

// @ 0x0057e1d0
cResourcedObject* cResourcedObject::Delete(unsigned flags)
{
    char* begin = mpBegin;
    if (((mpCapacity - begin) & ~1) > 2 && begin)
        operator delete[](begin);
    mpVtbl1 = (void*)&gVtbl1;
    mpVtbl0 = (void*)&gVtbl0;
    if (flags & 1)
        operator delete[](this);
    return this;
}

// @ 0x0057e220
void cAppModeEditorBase::FUN_0057e220(float a, float b, void* block, int extra)
{
    if (m4d4) {
        m4d4 = false;
        if (!mAnimCreatureManager || !mSaveLoadFactory || mSaveLoadFactory->GetSkin(true) == 0) {
            mEditorSaveModel->FUN_004ad110();
            mAnimatingCreatureActive = false;
        }
        FUN_00573970();
    }
    if (mSaveSkinManager && block) {
        uint32_t creatureFlags = *(uint32_t*)((char*)block + 0xdc8);
        bool bActive = (creatureFlags >> 7) & 1;
        if (bActive)
            mSaveSkinManager->FUN_005d1600(1, 1);
    }
    m480 = a;
    m484 = b;
    m474 = 0.0f;
    m48c = (int)block;
    m490 = extra;
    m472 = true;
    void* p = FUN_00401060();
    if (p) {
        typedef void (__thiscall *Fn)(void*, int, float, float, int);
        Fn fn = *(Fn*)(*(char**)p + 0x1c);
        fn(p, 0x1012, 1.0f, 0.2f, 1);
    }
    *(uint8_t*)((char*)m4d8 + 2) = 1;
    int row = GetCurrentTrayRow();
    if (row < 6 && mLaunchData && *(char*)((char*)mLaunchData + 0x6e))
        mTrayRows[row].mpStates[2] = 1;
}

// @ 0x0057e340
void cAppModeEditorBase::FUN_0057e340(bool active)
{
    mAnimatingCreatureActive = active;
    if (mAnimCreatureManager) {
        void* creature = mAnimCreatureManager->GetCreature(mShadowViewer);
        if (creature && *(char**)((char*)creature + 0x17c)) {
            cSphereListItem* list = *(cSphereListItem**)(*(char**)((char*)creature + 0x17c) + 0x2c0);
            if (list) {
                int n = (int)((list->mpEnd - list->mpBegin) / 0x14);
                if (n > 0) {
                    int off = 0;
                    do {
                        char* item = *(char**)&list->mpBegin[off + 0xc];
                        if (item) {
                            char* iface = *(char**)item;
                            if (iface) {
                                typedef void (__cdecl *Fn)(void*, int, int, int);
                                Fn fn = *(Fn*)(*(char**)iface + 0xc4);
                                fn(item, active, active, 0);
                            }
                        }
                        off += 0x14;
                        --n;
                    } while (n != 0);
                }
            }
        }
    }
    if (!active) {
        m70 = 0.0f;
    } else if (mD4) {
        FUN_0043cfc0(0, 1);
    }
    cEditorModel* model = mEditorSaveModel;
    int* modelBegin = *(int**)((char*)model + 0x18);
    int  count = (int)((*(int**)((char*)model + 0x1c) - modelBegin));
    int  n = count >> 2;
    if (n > 0) {
        int i = 0;
        do {
            char* item = (char*)modelBegin[i];
            if (item) {
                typedef void (__thiscall *Fn0)(void*);
                (*(Fn0*)(*(char**)item + 4))(item);
                void* a = *(void**)(item + 0x10);
                char* b = *(char**)(item + 0x18);
                if (a && b) {
                    typedef void (__cdecl *Fn3)(void*, int, int, int);
                    Fn3 fn = *(Fn3*)(*(char**)b + 0xc4);
                    fn(a, !active, !active, 0);
                }
                (*(Fn0*)(*(char**)item + 8))(item);
            }
            ++i;
        } while (i < n);
    }
    UpdateAnimatedCreature();
}

// @ 0x0057d710  (2631 bytes) — NOT reconstructed (oversized; see docs/Papercuts.md)
void cUnk0057d710::FUN_0057d710() {}
