// Slice s00496300 (batch w1g0, slice 93), 0x00496300..0x00496d2c.
// /Od editor-region code: limb-structure helpers.

#include "types.h"

struct Vector3 {
    float x, y, z;
};

Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b);   // 0x0041db10
float VectorLength(const Vector3* v);                                     // 0x0040ae50
void* GetBoneForHandle(void* h);                                          // 0x004aa030

struct Bone {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual int v4();
    void* Get();                          // 0x0047e6c0
    int GetSomething();                   // 0x0047e680
    int Check();                          // 0x0044f220
};

struct LimbStructure {
    char pad[0x5c];
    void Ctor();                          // 0x00488850
    void Init(void* limb, int a, int b);  // 0x004891a0
    void UpdateScaleRange(void* limb, float f); // 0x0048b370
    void F();                             // 0x00488980
    ~LimbStructure();                     // 0x00488900
};

struct HolderA {
    void* Get();                          // 0x0047e6c0
};

struct HolderB {
    char pad[0x64];
};

// @ 0x00496b60
void FUN_00496b60(HolderA* a, float f) {
    void* limb = a->Get();
    LimbStructure ls;
    ls.Ctor();
    ls.Init(limb, 0, 0);
    ls.UpdateScaleRange(limb, f);
    ls.F();
    ls.~LimbStructure();
}

// @ 0x00496bb0
int FUN_00496bb0(char* p, float f) {
    Bone* bone = (Bone*)GetBoneForHandle(p + 100);
    int c = 0;
    if (bone != 0)
        c = (int)bone->Get();
    if (bone != 0 && bone->v4() == 0x50e8e23 && c != 0 &&
        *(int*)(c + 0x3e0) != 0) {
        int t = bone->GetSomething();
        if (t != 0 && p != 0) {
            Vector3 d;
            Vector3_Sub(&d, (Vector3*)(t + 0xc), (Vector3*)(p + 0xc));
            float len = VectorLength(&d);
            if (len < 0.01f) {
                float s = f >= 0.0f ? 1.0f : -1.0f;
                int n = ((Bone*)c)->Check();
                if (s != (float)n)
                    c = *(int*)(c + 0x3e0);
            }
        }
    }
    return c;
}

// @ 0x00496300
void FUN_00496300(void* p, void* a, void* b) {
    (void)p;
    (void)a;
    (void)b;
}

// @ 0x00496760
void FUN_00496760(void* p, void* a) {
    (void)p;
    (void)a;
}
