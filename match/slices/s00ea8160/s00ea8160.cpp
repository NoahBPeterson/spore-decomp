// Audio setup (0xea8160, 2156 bytes, __thiscall, no args, returns true): creates the mix mode manager, then
// registers every creature-ability handler with the audio system and finally the layer object.
#include "types.h"
#include <stddef.h>

void* __cdecl operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0xf473a0

struct IRefCounted {
    virtual void v0();
    virtual void v1();
    virtual void AddRef();                  // +8
    virtual void Release();                 // +0xc
};

struct cMixModeManager : IRefCounted {
    uint32_t pad04[(0x6c - 4) / 4];
    cMixModeManager();                      // 0xeaa7c0
    void Shutdown();                        // 0xea9c70
    void Init();                            // 0xeaa9a0
};

// Intrusive smart pointer exactly as the engine's AutoRefCount: assignment adds the new reference first.
struct MixModeRef {
    cMixModeManager* mp;
    cMixModeManager* operator->() const { return mp; }
    operator bool() const { return mp != 0; }
    MixModeRef& operator=(cMixModeManager* p)
    {
        cMixModeManager* old = mp;
        if (p != old) {
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    void reset()
    {
        cMixModeManager* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
    }
};

// Creature-ability / audio handler objects; only their sizes and constructors matter here.
#define HANDLER(va, size) struct C_##va { uint32_t pad[(size) / 4]; C_##va(); };
HANDLER(00ea5b30, 0x38)   // 0xea5b30
HANDLER(00ea5cd0, 0x38)
HANDLER(00ea5db0, 0x38)
HANDLER(00ea5e90, 0x38)
HANDLER(00ea5f50, 0x38)
HANDLER(00ea5830, 0x3c)
HANDLER(00ea6010, 0x38)
HANDLER(00ea61a0, 0x38)
HANDLER(00ea59b0, 0x44)
HANDLER(00ea62b0, 0x38)
HANDLER(00ea55b0, 0x48)
HANDLER(00ea6360, 0x38)
HANDLER(00ea6580, 0x38)
HANDLER(00ea66d0, 0x38)
HANDLER(00ea6840, 0x38)
HANDLER(00ea6950, 0x38)
HANDLER(00ea6a50, 0x38)
HANDLER(00ea6bb0, 0x38)
HANDLER(00ea6d40, 0x38)
HANDLER(00ea6e90, 0x38)
HANDLER(00ea6f90, 0x38)
HANDLER(00ea7100, 0x38)
HANDLER(00ea7210, 0x38)
HANDLER(00ea7310, 0x4c)
HANDLER(00ea73a0, 0x4c)
HANDLER(00ea7440, 0x4c)
HANDLER(00ea74d0, 0x4c)
HANDLER(00ea7560, 0x4c)
HANDLER(00ea7600, 0x40)
HANDLER(00ea76d0, 0x40)
HANDLER(00ea77a0, 0x44)
HANDLER(00ea7910, 0x38)
HANDLER(00ea7a20, 0x38)
HANDLER(00ea7b50, 0x38)
HANDLER(00ea7c40, 0x38)
HANDLER(00ea7d20, 0x38)
HANDLER(00ea7e00, 0x38)
HANDLER(00ea7ee0, 0x38)
HANDLER(00ea8010, 0x38)

struct C_00e9e750 {                         // 0x7dc bytes, has a vtable
    virtual void v0();
    virtual void v1();
    virtual void vf2();                     // +8
    uint32_t pad04[(0x7dc - 4) / 4];
    C_00e9e750();                           // 0xe9e750
};
struct C_00ea4fd0 { uint32_t pad[3]; C_00ea4fd0(); };   // 0xea4fd0

// EA::Audio system (GetSystemAT): handlers are registered at slot 6.
struct cAudioAT {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Register(void* handler);   // +0x18
};
// SP::AudioSystem
struct cAudioSystem {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7();
    virtual void RegisterLayer(C_00e9e750* o);   // +0x20
    virtual void s9();
    virtual void SetObject(void* o);        // +0x28
};

cAudioAT* __cdecl GetSystemAT();            // 0xa206f0
cAudioSystem* __cdecl AudioSystem();        // 0x67cb00

struct AudioSetup {
    uint32_t pad00[3];
    MixModeRef mMixMgr;                     // +0xc
    bool Setup();
};

#define REGISTER(T) at->Register(new ("Audio", 0, 0, 0, 0) T())

// @ 0x00ea8160
bool AudioSetup::Setup()
{
    cAudioAT* at = GetSystemAT();
    cAudioSystem* sys = AudioSystem();
    if (at != 0 && sys != 0) {
        if (mMixMgr) {
            mMixMgr->Shutdown();
            mMixMgr.reset();
        }
        mMixMgr = new ("Audio", 0, 0, 0, 0) cMixModeManager();
        mMixMgr->Init();
        REGISTER(C_00ea5b30);
        REGISTER(C_00ea5cd0);
        REGISTER(C_00ea5db0);
        REGISTER(C_00ea5e90);
        REGISTER(C_00ea5f50);
        REGISTER(C_00ea5830);
        REGISTER(C_00ea6010);
        REGISTER(C_00ea61a0);
        REGISTER(C_00ea59b0);
        REGISTER(C_00ea62b0);
        REGISTER(C_00ea55b0);
        REGISTER(C_00ea6360);
        REGISTER(C_00ea6580);
        REGISTER(C_00ea66d0);
        REGISTER(C_00ea6840);
        REGISTER(C_00ea6950);
        REGISTER(C_00ea6a50);
        REGISTER(C_00ea6bb0);
        REGISTER(C_00ea6d40);
        REGISTER(C_00ea6e90);
        REGISTER(C_00ea6f90);
        REGISTER(C_00ea7100);
        REGISTER(C_00ea7210);
        REGISTER(C_00ea7310);
        REGISTER(C_00ea73a0);
        REGISTER(C_00ea7440);
        REGISTER(C_00ea74d0);
        REGISTER(C_00ea7560);
        REGISTER(C_00ea7600);
        REGISTER(C_00ea76d0);
        REGISTER(C_00ea77a0);
        REGISTER(C_00ea7910);
        REGISTER(C_00ea7a20);
        REGISTER(C_00ea7b50);
        REGISTER(C_00ea7c40);
        REGISTER(C_00ea7d20);
        REGISTER(C_00ea7e00);
        REGISTER(C_00ea7ee0);
        REGISTER(C_00ea8010);
        C_00e9e750* layer = new ("Audio", 0, 0, 0, 0) C_00e9e750();
        sys->RegisterLayer(layer);
        layer->vf2();
        sys->SetObject(new ("Audio", 0, 0, 0, 0) C_00ea4fd0());
    }
    return true;
}
