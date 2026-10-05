// w1g1 slice s00505850 -- nSPSkinner / Simulator::cCreatureAbility helpers.
//
// Flags for this region: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE).
//
// 0x505850 is a 2.7 KB /Od two-segment closest-point routine (six Vector3*
// args); too large for the per-function budget, so it is recorded as PARTIAL.
// The remaining four functions are small ctors/dtors around
// nSPSkinner::cRTTBuffer and Simulator::cCreatureAbility; complete behavioural
// ports are given, but they are not byte-exact (class/vtable scheduling).

typedef unsigned int uint32_t;

inline void* operator new(unsigned int, void* p) { return p; }

void* ea_new(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  ea_free(void* p);                                                    // 0x00f47380
void  ea_delete(void* p);                                                  // operator_delete__

// ---------------------------------------------------------------------------
// @ 0x00505850  (PARTIAL skeleton)
// ---------------------------------------------------------------------------
float __cdecl ClosestSegSeg(const float* a0, const float* a1,
                            const float* b0, const float* b1,
                            float* s, float* t)
{
    // Original: d1=a1-a0, d2=b1-b0, r=a0-b0, a=d1.d1, e=d2.d2, f=d2.r,
    // c=d1.r, b=d1.d2, denom=abs(a*e-b*b), then clamped s,t in [0,1].
    // Only the parameter skeleton is reproduced here (see partial.txt).
    (void)a0; (void)a1; (void)b0; (void)b1;
    *s = 0.0f;
    *t = 0.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------
struct cRTTBuffer { cRTTBuffer(int w, int h); };            // 100-byte object

struct cCreatureAbility {
    virtual void v0();      // vtbl_Simulator::cCreatureAbility[0]
    int*  mField4;          // +0x04
    void* mObj;             // +0x08
    void* mObj2;            // +0x0c
    void* mSlots[3];        // +0x10
    int   mParam;           // +0x1c
    float mF20, mF24, mF28, mF2c, mF30;
    uint32_t mKey;          // +0x34
    void* mHandle;          // +0x38
};

void* CreateRTT(int param)
{
    cRTTBuffer* p = (cRTTBuffer*)ea_new(100, "Skinner", 0, 0, 0, 0);
    if (p) return new ((void*)p) cRTTBuffer(param, param);
    return 0;
}

// @ 0x005062f0  (constructor)
cCreatureAbility* __fastcall cCreatureAbility_ctor(cCreatureAbility* self)
{
    self->mField4 = 0;
    self->mObj = ea_new(0x54, "Skinner", 0, 0, 0, 0);
    self->mObj2 = ea_new(0x54, "Skinner", 0, 0, 0, 0);
    self->mSlots[0] = 0;
    self->mSlots[1] = 0;
    self->mSlots[2] = 0;
    self->mF20 = 0.5f;
    self->mF24 = 1.0f;
    self->mF28 = 20.0f;
    self->mF2c = 1.0f;
    self->mF30 = 1.0f;
    self->mKey = 0;
    self->mHandle = 0;
    return self;
}

void CleanupResource(void* p);         // 0x00762a00
uint32_t HashName(const char* s);      // 0x007c3af0
void* Lookup(uint32_t k, int a, int b, int c);  // 0x00762b70

// @ 0x005064a0  (destructor)
void __fastcall cCreatureAbility_dtor(cCreatureAbility* self)
{
    CleanupResource(self->mHandle);
    self->mHandle = 0;
    self->mKey = 0;
    if (self->mObj) {
        ea_delete(self->mObj);
        self->mObj = 0;
    }
    if (self->mObj2) {
        ea_delete(self->mObj2);
        self->mObj2 = 0;
    }
}

// @ 0x00506590  (Setup)
void __fastcall cCreatureAbility_Setup(cCreatureAbility* self, int param)
{
    self->mSlots[0] = CreateRTT(param);
    self->mSlots[1] = CreateRTT(param);
    self->mSlots[2] = CreateRTT(param);
    self->mParam = param;
    self->mF20 = 0.5f;
    self->mF24 = 1.0f;
    self->mF28 = 20.0f;
    self->mF2c = 1.0f;
    self->mF30 = 1.0f;
}

struct Disposable { void Destroy(); };   // 0x00528e20

// @ 0x005066d0  (Cleanup)
void __fastcall cCreatureAbility_Cleanup(cCreatureAbility* self)
{
    for (int i = 0; i < 3; ++i) {
        if (self->mSlots[i] != 0) {
            ((Disposable*)self->mSlots[i])->Destroy();
            ea_free(self->mSlots[i]);
            self->mSlots[i] = 0;
        }
    }
}
