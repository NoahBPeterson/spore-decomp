// Slice s00d391d0 -- creature-mode display strategy / texture preload setup.
// Module flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

// ---------------------------------------------------------------- types

struct PropKey {
    uint32_t group;                                        // +0x00
    uint32_t x;                                            // +0x04
    uint32_t inst;                                         // +0x08
};

// The intrusive AddRef/Release pair lives in a polymorphic sub-object at
// +0x38 of the display strategy.
struct CRefCount {
    virtual void AddRef();                                 // slot 0
    virtual void Release();                                // slot 1
};

struct CDisplayStrategy {
    uint8_t   mPad00[0x38];
    CRefCount mRef;                                        // +0x38
    uint8_t   mPad3c[0x320 - 0x3c];

    CDisplayStrategy();                                    // 0x00d2d690
    void Activate(bool nMode);                             // 0x00d2cb10
};

struct CTexturePreload {
    virtual void AddRef();                                 // slot 0
    virtual void Release();                                // slot 1
    void PreloadTextureList(PropKey* key);                 // 0x007b1e90

    CTexturePreload(int n);                                // 0x007b07e0
    uint8_t mPad04[0x34 - 0x04];
};

struct COwner {
    uint8_t mPad00[0x68];
    CDisplayStrategy* mpDisplay;                           // +0x68
    uint8_t mPad6c[0xd4 - 0x6c];
    CTexturePreload*  mpTextures;                          // +0xd4
};

struct CTestSystem {
    uint8_t mPad00[0x70];
    void*   mpList;                                        // +0x70
};

void* operator new(unsigned int size, const char* pName, int flags, int debugFlags,
                   const char* file, int line);        // 0x00f473a0

extern COwner*      g_pOwner;                              // 0x0169e294
extern CTestSystem* g_pTestSystem;                         // 0x015fd928
extern uint8_t      g_textureKeys[];                       // 0x015834e0

// ---------------------------------------------------------------- function

// The key loop lives in an inlined helper: keeping the whole loop (its `PropKey`
// local and the call) in one inlined body is what makes cl 15.00 defer the
// `key.group` store past the argument push and the `this` load, as retail does.
static __forceinline void PreloadCreatureKeys(COwner* o)
{
    PropKey key;
    key.x = 0xefbda3ff;
    key.inst = 0x40464100;
    for (uint32_t i = 0; i < 0x50; i += 4) {
        key.group = *(uint32_t*)(g_textureKeys + i);
        o->mpTextures->PreloadTextureList(&key);
    }
}

// @ 0x00d391d0
void InitCreatureDisplay(bool force)
{
    COwner* owner = g_pOwner;

    if (owner->mpDisplay == 0) {
        CDisplayStrategy* display = new ("Simulator", 0, 0, 0, 0) CDisplayStrategy();
        CDisplayStrategy* old = owner->mpDisplay;
        if (display != old) {
            if (display != 0)
                display->mRef.AddRef();
            owner->mpDisplay = display;
            if (old != 0)
                old->mRef.Release();
        }
        owner->mpDisplay->Activate(force);
    }

    if (g_pTestSystem != 0 &&
        g_pTestSystem->mpList != (void*)&g_pTestSystem->mpList &&
        force)
        return;

    CTexturePreload* preload = new ("Simulator", 0, 0, 0, 0) CTexturePreload(-1);
    CTexturePreload* oldPreload = owner->mpTextures;
    if (preload != oldPreload) {
        if (preload != 0)
            preload->AddRef();
        owner->mpTextures = preload;
        if (oldPreload != 0)
            oldPreload->Release();
    }

    // Residual diff, solved by the inlined helper above: keeping the key loop
    // in one inlined body makes cl sink `key.group` past the argument push and
    // the `this` load (retail: push ecx / mov ecx,[edi+0xd4] / mov [esp+0x10],eax).
    PreloadCreatureKeys(owner);
}
