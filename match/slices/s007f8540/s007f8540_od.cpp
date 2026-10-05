// slice s007f8540: /Od tail region (UI/cSPUIAnimationSequence helpers).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include "types.h"

struct AnimMgr {
    char  pad0[0x3a];   // +0x00
    bool  b3a;          // +0x3a
    char  pad3b;        // +0x3b
    float f3c;          // +0x3c

    void  Reset();
    void  AddTime(float dt);
    bool  Set(int key, float value);
    bool  Get(int key, float* out);
    bool  Has(int key);
    void  Clear();

    void* Find(int key) {
        return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)this + 0x5c)))(this, key);
    }
    void Shutdown() {
        ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)this + 0x60)))(this);
    }
};

// @ 0x007f93f0
void AnimMgr::Reset() {
    f3c = 0.0f;
}

// @ 0x007f9430
void AnimMgr::AddTime(float dt) {
    f3c = f3c + dt;
}

// @ 0x007f9460
bool AnimMgr::Set(int key, float value) {
    void* p = Find(key);
    if (p != 0) {
        *(float*)p = value;
        b3a = true;
    }
    return p != 0;
}

// @ 0x007f94b0
bool AnimMgr::Get(int key, float* out) {
    void* p = Find(key);
    if (p != 0 && out != 0) {
        *out = *(float*)p;
    }
    return p != 0;
}

// @ 0x007f9500
bool AnimMgr::Has(int key) {
    return Find(key) != 0;
}

// @ 0x007f9530
void AnimMgr::Clear() {
    Shutdown();
}
