// slice s00577130
// SP::cAppModeEditorBase methods, /O2 /arch:SSE /fp:fast (same module as s00575270).
#include <new>
#include <string.h>
#include <math.h>
#include "types.h"

namespace SP { namespace EditorUtils {
    void __cdecl PlayEditorSound(uint32_t id, uint32_t sound, float value, int flags);   // 0x435f40
    float __cdecl CalculateModelSize(void* model);                                      // 0x48ca10
    int   __cdecl CountModelParts(void* model);                                         // 0x48cc20
} }

void   __stdcall SomeGuardCall(void* p);          // 0x440b90
void   __cdecl PlayEditorEvent(uint32_t id);      // 0x4a88d0
int    __cdecl g_soundBlockCounter;               // 0x15e4eec

struct IObject {
    virtual void slot0();
    virtual void AddRef();                        // +0x4
    virtual void Release();                       // +0x8
};

struct ISkinManager {
    void* GetSkin(int);                           // 0x4c49e0
};

struct ObjF8 {
    void SomeMethod(int);                         // 0x697a10
};

struct ObjE4 {
    void* SomeCall();                             // 0x47e6c0
};

template <typename T> static inline T* Field(void* self, uint32_t off) {
    return *(T**)((char*)self + off);
}
template <typename T> static inline T& Ref(void* self, uint32_t off) {
    return *(T*)((char*)self + off);
}

namespace SP {
class cAppModeEditorBase {
public:
    char pad[0x458];

    void SetSoundBlockAdded(int);                 // 0x577130
    void SetSoundBlockRemoved(int);               // 0x5771f0
    void RemoveTorsoFromEffectsMask();            // 0x5772b0
    void PreloadResources();                      // 0x577310
    void SetSomeBlock(int);                       // 0x5774f0
    void UpdateBlockState();                      // 0x577520
    void SetTorsoBlock(void*, char);              // 0x577580
    bool HasSkin();                               // 0x577620
    void SaveSomething();                         // 0x577650
    bool HasAnyResource(void*, int);              // 0x577b20
    void LoadSomething(void*);                    // 0x577c40
    void SomeLoader();                            // 0x577dd0

    void SetRolloverHandle(int, int);             // 0x573d70
    void DoSomeOther(int, int);                   // 0x573c00
};
}

using SP::cAppModeEditorBase;

// @ 0x00577130
void cAppModeEditorBase::SetSoundBlockAdded(int param)
{
    int p = param;
    if (Ref<char>(this, 0x20e) != 0) {
        if (p != 0) {
            int local[3];
            SomeGuardCall(local);
            int n = g_soundBlockCounter + 1;
            g_soundBlockCounter = n;
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xc8b0416e, (float)n, 0);
        }
        if (Ref<char>(this, 0x20e) != 0) {
            float sz = SP::EditorUtils::CalculateModelSize(Field<void>(this, 0x98));
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xdef22b96, sz, 0);
            if (Ref<char>(this, 0x20e) != 0) {
                int cnt = SP::EditorUtils::CountModelParts(Field<void>(this, 0x98));
                SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0x5ee38119, (float)cnt, 0);
            }
        }
    }
}

// @ 0x005771f0
void cAppModeEditorBase::SetSoundBlockRemoved(int param)
{
    int p = param;
    if (Ref<char>(this, 0x20e) != 0) {
        if (p != 0) {
            int local[3];
            SomeGuardCall(local);
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xbb98bc04, (float)g_soundBlockCounter, 0);
        }
        if (Ref<char>(this, 0x20e) != 0) {
            float sz = SP::EditorUtils::CalculateModelSize(Field<void>(this, 0x98));
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xdef22b96, sz, 0);
            if (Ref<char>(this, 0x20e) != 0) {
                int cnt = SP::EditorUtils::CountModelParts(Field<void>(this, 0x98));
                SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0x5ee38119, (float)cnt, 0);
            }
        }
    }
}

// @ 0x005772b0
void cAppModeEditorBase::RemoveTorsoFromEffectsMask()
{
    void* p = Ref<void*>(this, 0xf0);
    if (p) {
        void** vt = *(void***)(*(void**)p);
        ((void(__stdcall*)(void*, int))vt[91])(p, 0);
        p = Ref<void*>(this, 0xf0);
        if (p) {
            Ref<void*>(this, 0xf0) = 0;
            int c = Ref<int>(p, 0x40);
            if (c > 1) {
                Ref<int>(p, 0x40) = c - 1;
                return;
            }
            unsigned r = Ref<unsigned>(p, 4);
            int b = (r >> 31) & 1;
            void** vt2 = *(void***)(*(void**)p);
            ((void(__stdcall*)(void*, int))vt2[92])(p, b);
        }
    }
}

// @ 0x005774f0
void cAppModeEditorBase::SetSomeBlock(int param)
{
    ((ObjF8*)((char*)this + 0xf8))->SomeMethod(param);
    if (param == 0)
        DoSomeOther(0, -1);
}

// @ 0x00577520
void cAppModeEditorBase::UpdateBlockState()
{
    void* p = Ref<void*>(this, 0xcc);
    if (p != 0) {
        unsigned bits = Ref<unsigned>(p, 0xdc8);
        unsigned flag = (bits >> 1) & 1;
        if (flag != 0)
            DoSomeOther(0, -1);
    }

    if (Ref<void*>(this, 0xe4) != 0) {
        void* r = ((ObjE4*)Ref<void*>(this, 0xe4))->SomeCall();
        if (r == 0 ||
            ((Ref<unsigned>(((ObjE4*)Ref<void*>(this, 0xe4))->SomeCall(), 0xdc8) >> 1) & 1) != 0)
            SetRolloverHandle(0, 1);
    }
}

// @ 0x00577580
void cAppModeEditorBase::SetTorsoBlock(void* block, char param)
{
    if (block != 0) {
        if (param != 0)
            param = 0;
        PlayEditorEvent(0xe5469985);
    } else {
        if (param != 0)
            PlayEditorEvent(0xe5469985);
    }
    void* prev = Ref<void*>(this, 0xdc);
    if (block != prev) {
        if (block)
            ((IObject*)block)->AddRef();
        Ref<void*>(this, 0xdc) = block;
        if (prev)
            ((IObject*)prev)->Release();
    }
    void* a = Ref<void*>(this, 0xd4);
    Ref<char>(this, 0xe0) = param;
    void* b = Ref<void*>(this, 0xd8);
    if (a != b) {
        if (a)
            ((IObject*)a)->AddRef();
        Ref<void*>(this, 0xd8) = a;
        if (b)
            ((IObject*)b)->Release();
    }
}

// @ 0x00577620
bool cAppModeEditorBase::HasSkin()
{
    if (Ref<int>(this, 0x360) != 0 && Ref<int>(this, 0x150) != 0) {
        if (Field<ISkinManager>(this, 0x150)->GetSkin(1) != 0)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Placeholders (see partial.txt)
// ---------------------------------------------------------------------------
void cAppModeEditorBase::PreloadResources() {}
void cAppModeEditorBase::SaveSomething() {}
bool cAppModeEditorBase::HasAnyResource(void*, int) { return false; }
void cAppModeEditorBase::LoadSomething(void*) {}
void cAppModeEditorBase::SomeLoader() {}
