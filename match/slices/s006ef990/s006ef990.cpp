// Slice s006ef990 — SP::cEffectsRendererSystem / SP::cEffectsModel helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"
#include <intrin.h>

extern "C" void FUN_00762a60(void* p);
extern "C" void EASTL_allocator_deallocate(void* p);

struct Dispatch3 { void* p0; void* p1; void* p2; };   // 0xc

// cEffectsModel layout (retail): vptr +0, refcount +4, dispatch vector +8.
struct cEffectsModelR {
    void** mpVtable;      // +0x00
    int    mnRefCount;    // +0x04
    Dispatch3* mpBegin;   // +0x08
    Dispatch3* mpEnd;     // +0x0c

    void Reset();         // 6edb10
};

// ---- 0x006ef990 (free function, cdecl: takes the model pointer) -------------
// @ 0x006ef990
void Release(cEffectsModelR* self)
{
    Dispatch3* it = self->mpBegin;
    Dispatch3* end = self->mpEnd;
    for (; it != end; ++it)
        FUN_00762a60(it->p0);
    self->Reset();
    int n = self->mnRefCount - 1;
    self->mnRefCount = self->mnRefCount - 1;
    if (n == 0) {
        self->mnRefCount = 1;
        _ReadWriteBarrier();
        ((void (__thiscall*)(void*, int))self->mpVtable[0])(self, 1);
    }
}

// ---- cEffectsRendererSystem -------------------------------------------------
struct cEffectsModel2;
class cEffectsRendererSystem {
public:
    char pad0[4];
    cEffectsModel2* mpModel;        // +0x04
    char pad1[0x30d50 - 0x08];
    void* mAt30d50;                 // +0x30d50
    void* mAt30d54;                 // +0x30d54  (vector begin)
    void* mAt30d58;                 // +0x30d58  (vector end)
    char pad2[0x30d68 - 0x30d5c];
    void* mAt30d68;                 // +0x30d68
    void* mAt30d6c;                 // +0x30d6c
    char pad3[0x30d7c - 0x30d70];
    void* mAt30d7c;                 // +0x30d7c
    void* mAt30d80;                 // +0x30d80
    int   mAt30d84;                 // +0x30d84

    bool Init();                    // 6ef9e0
    char Shutdown();                // 6efa90
private:
    void* SetDeviceState();
    void* GetImageResource(void*);
    void  FUNecf10(int);
};

struct cERSDtor;
extern cERSDtor* g_pEffectsRendererSystem;   // DAT_01618d10

extern "C" void* CreateTestModel();
extern "C" void* FUN_007c3af0(const char* s);
extern "C" void* FUN_00762b70(void* p, int a, int b, int c);
void* CreateMesh(int n);           // SP::CreateMesh

struct MeshStub {
    void FUN96e0(int);
    void FUN9670(int, void*);
};
struct cEffectsModel2 {
    void** mpVtable;    // +0
    int    mnRefCount;  // +4
};

// ---- 0x006ef9e0 -------------------------------------------------------------
// @ 0x006ef9e0
bool cEffectsRendererSystem::Init()
{    GetImageResource(SetDeviceState());
    cEffectsModel2* m = (cEffectsModel2*)CreateTestModel();
    cEffectsModel2* old = mpModel;
    if (m != old) {
        if (m)
            m->mnRefCount++;
        mpModel = m;
        if (old) {
            int n = old->mnRefCount - 1;
            old->mnRefCount = old->mnRefCount - 1;
            if (n == 0) {
                old->mnRefCount = 1;
                _ReadWriteBarrier();
                ((void (__thiscall*)(void*, int))old->mpVtable[0])(old, 1);
            }
        }
    }
    mAt30d50 = FUN_007c3af0("T0FT4FT4FT4FT4B");
    mAt30d80 = FUN_00762b70(mAt30d50, 0x9c4, 9, 0);
    mAt30d7c = CreateMesh(3);
    ((MeshStub*)mAt30d7c)->FUN96e0(0);
    ((MeshStub*)mAt30d7c)->FUN9670(1, mAt30d80);
    FUNecf10(1);
    mAt30d84 = 0;
    return true;
}

// ---- 0x006efa90 (skeleton) --------------------------------------------------
// @ 0x006efa90
char cEffectsRendererSystem::Shutdown()
{
    return 1;
}

// ---- 0x006efb90 (skeleton: static singleton factory) ------------------------
// @ 0x006efb90
void CreateEffectsRendererSystem()
{
}

// ---- 0x006efc10 -------------------------------------------------------------
// @ 0x006efc10
struct cERSDtor { void Shutdown(); ~cERSDtor(); };

void DestroyEffectsRendererSystem()
{
    g_pEffectsRendererSystem->Shutdown();
    cERSDtor* p = g_pEffectsRendererSystem;
    if (p) {
        p->~cERSDtor();
        EASTL_allocator_deallocate(p);
    }
    g_pEffectsRendererSystem = 0;
}

// ---- 0x006efc70 (skeleton) --------------------------------------------------
// @ 0x006efc70
void RenderSomething(int)
{
}

// ---- 0x006efe90 (skeleton: RenderTextureParticles) --------------------------
// @ 0x006efe90
void RenderTextureParticlesStub()
{
}

// ---- 0x006f0320 / 0x006f05a0 (skeletons) -----------------------------------
// @ 0x006f0320
void EffectsHelper320(int)
{
}
// @ 0x006f05a0
void EffectsHelper5a0(int)
{
}
