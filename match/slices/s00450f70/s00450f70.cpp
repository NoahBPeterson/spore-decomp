// slice s00450f70 -- accessors around a tracker sub-object.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"

struct Vec3 {
    float x, y, z;
};

struct RCObj {
    virtual void AddRef();
    virtual void Release();
};

struct SubInner {
    char  pad0[0x1c];
    void* field;        // +0x1c
};
struct Sub {
    char     pad0[0x1c];
    SubInner inner;     // +0x1c
};

struct Tracker {
    char   pad0[4];
    RCObj* field4;      // +4
    char   pad8[0x14 - 8];
    Vec3   vec14;       // +0x14
    char   pad20[0x44 - 0x20];
    int    field44;     // +0x44

    void Call(void* tmp, int a, unsigned char b);   // 0x004e9500
};

struct Block2 {
    char     pad0[0x18];
    void*    mp18;        // +0x18
    int      mInstance;   // +0x1c
    int      mGroup;      // +0x20
    char     pad24[0x28 - 0x24];
    int      mField28;    // +0x28
    char     pad2c[0x48 - 0x2c];
    Vec3     mVec48;      // +0x48
    char     pad54[0x188 - 0x54];
    void*    mPtr188;     // +0x188
    Sub*     mSub18c;     // +0x18c
    char     pad190[0x194 - 0x190];
    Vec3     mVec194;     // +0x194
    bool     mFlag1a0;    // +0x1a0
    char     pad1a1[0x1a4 - 0x1a1];
    int      mField1a4;   // +0x1a4
    char     pad1a8[0x1d8 - 0x1a8];
    float    mField1d8;   // +0x1d8
    float    mField1dc;   // +0x1dc
    char     pad1e0[0x33c - 0x1e0];
    void*    mPtr33c;     // +0x33c
    char     pad340[0x378 - 0x340];
    Tracker* mTracker;    // +0x378
    char     pad37c[0xdc8 - 0x37c];
    unsigned int mFlags[2]; // +0xdc8

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }
    void SetBit(unsigned int n) { unsigned int w = n / 32; mFlags[w] |= (1u << (n % 32)); }
    void ClearBit(unsigned int n) { unsigned int w = n / 32; mFlags[w] &= ~(1u << (n % 32)); }

    int    GetA();                        // 0x004511f0
    int    GetB();                        // 0x00451210
    void   SetF(void* a, unsigned char b);// 0x00451240
    void   SetRef(RCObj* p);              // 0x00451280
    Vec3*  GetVec14(Vec3* out);           // 0x004512e0
    void   SetVec194(int x, int y, int z);// 0x00451330
    void   ResetVec194();                 // 0x00451360
    Vec3*  GetVec194(Vec3* out);          // 0x004513a0
    void   SetPtr188(void* p);            // 0x00451e20
    void   SetSub38(void* p);             // 0x00451e50
    void*  GetSub38();                    // 0x00451e90
    void   Reset188();                    // 0x00451ed0
    unsigned char Rebuild(int a, int b, float c, char d, unsigned char e); // 0x00450f70
    void   Shutdown2();                   // 0x00451400 (partial)
    void   FUN_00452040();                // 0x00452040
    void   FUN_00451fe0();                // 0x00451fe0
    void   FUN_00440520(float f, int a, int b);   // 0x00440520
    void   FUN_00449ed0();                // 0x00449ed0
    void   FUN_00448e90(void* p, int a);  // 0x00448e90
    void   FUN_00449420(void* p, int a);  // 0x00449420
    unsigned char BuildBlock(int inst, int grp, int a, int b, float c, char d, unsigned char e, int one); // 0x00441040
};

// @ 0x004511f0
int Block2::GetA() {
    int result = (int)mTracker->field4;
    return result;
}

// @ 0x00451210
int Block2::GetB() {
    if (mTracker != 0) {
        return mTracker->field44;
    } else {
        return -1;
    }
}

// @ 0x00451240
void Block2::SetF(void* a, unsigned char b) {
    void* tmp = mPtr33c;
    mTracker->Call(tmp, (int)a, b);
}

// @ 0x00451280
void Block2::SetRef(RCObj* p) {
    RCObj** slot = &mTracker->field4;
    RCObj* old;
    if (p != *slot) {
        old = *slot;
        if (p != 0) p->AddRef();
        *slot = p;
        if (old != 0) old->Release();
    }
}

// @ 0x004512e0
Vec3* Block2::GetVec14(Vec3* out) {
    Vec3* p = &mTracker->vec14;
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x00451330
void Block2::SetVec194(int x, int y, int z) {
    *(int*)&mVec194.x = x;
    *(int*)&mVec194.y = y;
    *(int*)&mVec194.z = z;
    mFlag1a0 = true;
}

// @ 0x00451360
void Block2::ResetVec194() {
    mVec194 = mVec48;
    mFlag1a0 = false;
}

// @ 0x004513a0
Vec3* Block2::GetVec194(Vec3* out) {
    Vec3* p = &mVec194;
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x00451e20
void Block2::SetPtr188(void* p) {
    mPtr188 = p;
    FUN_00452040();
}

// @ 0x00451e50
void Block2::SetSub38(void* p) {
    if (mSub18c != 0) {
        SubInner* q = &mSub18c->inner;
        q->field = p;
    }
}

// @ 0x00451e90
void* Block2::GetSub38() {
    if (mSub18c != 0) {
        SubInner* q = &mSub18c->inner;
        void* result = q->field;
        return result;
    } else {
        return 0;
    }
}

// @ 0x00451ed0
void Block2::Reset188() {
    FUN_00451fe0();
    mPtr188 = 0;
}

// @ 0x00450f70
unsigned char Block2::Rebuild(int a, int b, float c, char d, unsigned char e) {
    bool f12 = GetFlag(0xc);
    bool f39 = GetFlag(0x39);
    mFlags[0] = 0;
    mFlags[1] = 0;
    if (f12) SetBit(0xc); else ClearBit(0xc);
    if (f39) SetBit(0x39); else ClearBit(0x39);
    unsigned char r = BuildBlock(mInstance, mGroup, a, b, c, d, e, 1);
    FUN_00440520(mField1d8, 0, 1);
    mField1dc = mField1d8;
    if (d != 0)
        FUN_00449ed0();
    FUN_00448e90((char*)this + 0x48, 0);
    FUN_00449420((char*)this + 0xa8, 0);
    return r;
}

// @ 0x00451400 -- incomplete: only the entry sequence is reproduced.
void Block2::Shutdown2() {
    if (mField1a4 != 0) {
        mField1a4 = 0;
    }
    Reset188();
    mFlags[0] |= 2;
    mField28 = 0;
    // Remaining teardown (model/socket/handle release, resource map clear)
    // is not reconstructed.
}
