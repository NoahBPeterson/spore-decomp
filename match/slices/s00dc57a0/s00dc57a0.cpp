// Slice s00dc57a0: 00dc59d0. Computes two scaled floats from the sub-object at +0x508,
// passes them to a helper, then calls two virtuals on the object returned by 0x00c9fee0
// and applies the results back to self.

typedef unsigned int uint32;

struct Vec3f { float x, y, z; };

struct Sub508 {
    float Get();                // thiscall, x87 float return (FUN_00bfc400)
};

struct Obj {
    char vtbl_pad[4];           // vtable pointer lives at +0; slots called via typed pointers below
};

struct Self {
    char pad[0x508];
    Sub508 mSub;                // +0x508
    Obj* GetObj();              // thiscall, no args (FUN_00c9fee0)
    void Apply(Vec3f v);        // thiscall, Vec3f by value, callee pops 0xc (FUN_00c9fb40)
    void Take(Vec3f* p);        // thiscall, one pointer arg, callee pops 4 (FUN_00ca97a0)
};

// FUN_00dc4ed0: cdecl helper, args (float*, float*, Self*, Obj*)
void Helper(float* a, float* b, Self* self, Obj* obj);

typedef Vec3f* (__thiscall *Vfn1)(Obj* self, float a);          // vslot 11, one float arg
typedef Vec3f* (__thiscall *Vfn2)(Obj* self, float a, float b); // vslot 11, two float args

// @ 0x00dc59d0
int ComputeAndApply(Self* self, uint32 a2, uint32 a3, uint32 a4, uint32 a5, float* out) {
    if (out) {
        *out = 0.0f;
    }
    Obj* obj = self->GetObj();
    if (!obj) {
        return 0;
    }
    float f8 = 8.0f;
    float f1 = self->mSub.Get() * 0.75f;
    float fLo = self->mSub.Get() - 1.0f;
    Helper(&f8, &f1, self, obj);
    void** vt = *(void***)obj;
    Vec3f* p1 = ((Vfn1)vt[11])(obj, f8);
    self->Take(p1);
    vt = *(void***)obj;
    Vec3f* p2 = ((Vfn2)vt[11])(obj, fLo, f1);
    self->Apply(*p2);
    return 1;
}
