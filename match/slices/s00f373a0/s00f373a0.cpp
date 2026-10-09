// Slice s00f373a0 -- planet/terraform scenario UI-panel methods (0x00f373a0..0x00f38154).
// Module flags: /O2 /MD /Gy /TP
//
// The object is a scenario/planet UI panel: a property list at +0xc, an
// AutoRefCount at +0x10, several eastl vectors (12/56/4/16-byte elements),
// four vec3 pairs at +0x130.., an id at +0x160 and a MessageServer handler
// block at +0x178.  Callees keep retail names (FUN_<addr>, DAT_<addr>) so the
// equivalence harness can resolve them by address.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// constants / globals
// ---------------------------------------------------------------------------
extern u32   DAT_016c851c, DAT_016c8520, DAT_016c8524, DAT_016c8528;
extern u8    DAT_016c8504, DAT_016c8505;
extern void* DAT_016c7aa4;                 // SP::cSPLivingUniverse singleton
extern float DAT_01486110;
extern u32   DAT_016c8538;                 // matrix constant
extern wchar_t DAT_0148d044[];
extern u32   DAT_0148d084;
extern u32   DAT_0148d088;

// ---------------------------------------------------------------------------
// cdecl / stdcall callees
// ---------------------------------------------------------------------------
void   __cdecl  FUN_00f31f20(void*, u32, int, void*);          // 0x00f31f20
void   __cdecl  FUN_007dade0(u32);                             // 0x007dade0 SP::SetEffectSeed
float* __stdcall FUN_0059c190(void*, const void*);            // 0x0059c190 Matrix3FromQuaternion
void   __stdcall FUN_00f31c40(int);                            // 0x00f31c40
void   __stdcall FUN_00f31cb0(int);                            // 0x00f31cb0
void   __cdecl  FUN_006a0ae0(void*, u32, int*, void**);        // 0x006a0ae0
void   __stdcall FUN_00f3e3b0(int);                            // 0x00f3e3b0
void*  __cdecl  FUN_00f473a0(int, const char*, int, int, int, int); // operator new
void*  __stdcall FUN_00b3d350_3(void*, int, int);             // 0x00b3d350 SP::PlanetModel(3 args)
void*  __stdcall FUN_00b3d350();                               // SP::PlanetModel (no-arg form)
void*  __cdecl  FUN_00f48a80();                                // 0x00f48a80
void   __cdecl  FUN_00f26330();                                // 0x00f26330
void*  __stdcall FUN_00f32790(void*);                          // 0x00f32790
void   __cdecl  FUN_00f97660();                                // 0x00f97660
void*  __cdecl  FUN_00ecc100(u32);                             // 0x00ecc100
void*  __cdecl  FUN_010212a0();                                // GetActivePlanetRecord
void*  __cdecl  FUN_01021260();                                // GetActivePlanet
void   __cdecl  FUN_0068d840(int*, const wchar_t*, int, int);  // SPKeyFromName
void*  __stdcall FUN_00b3d300(u32);                            // SP::NounManager
void*  __stdcall FUN_00b3d430(void*);                          // SP::TerraformingManager
void*  __cdecl  FUN_0067dcc0();                                // SP::MessageServer
void*  __cdecl  FUN_0067de30();                                // SP::PropertyManager
void*  __cdecl  FUN_0067de60();                                // SP::IDGenerator
void*  __cdecl  FUN_0067dcd0();                                // ResourceMan::GetManager
void*  __cdecl  FUN_006a1c40(void*);                           // cPropertyList ctor helper
void   __cdecl  FUN_00eeee40(void);                            // (never called raw)

// ---------------------------------------------------------------------------
// thiscall callees on foreign objects (all args on stack, ecx = this).
// Method names carry the retail address for difftest resolution.
// ---------------------------------------------------------------------------
struct Ext {
    u32* FUN_0041ea00();                                       // 0x0041ea00 property get
    void FUN_0041cb40(const void*);                            // 0x0041cb40 Matrix3::Assign
    void FUN_0093db80(int);                                    // 0x0093db80 Variant::Destruct
    void FUN_00427fd0(void*);                                  // 0x00427fd0 Variant_SetInt
    void FUN_00f35a70(int, int, void*, int, int, int);         // 0x00f35a70
    void FUN_00f35c80();                                       // 0x00f35c80
    void FUN_00f368b0();                                       // 0x00f368b0
    void FUN_00f32bf0(int);                                    // 0x00f32bf0
    void FUN_00f34660();                                       // 0x00f34660
    void FUN_00f347e0();                                       // 0x00f347e0
    void FUN_00f32440(int);                                    // 0x00f32440
    void FUN_00f35f70();                                       // 0x00f35f70
    void FUN_00f32cb0();                                       // 0x00f32cb0
    void FUN_00f32d10();                                       // 0x00f32d10
    void FUN_00f343a0(int);                                    // 0x00f343a0
    void FUN_00f344e0(void*, void*);                           // 0x00f344e0
    void FUN_00f31f80();                                       // 0x00f31f80
    void FUN_00fb7a90();                                       // 0x00fb7a90
    void FUN_00fbaf50(int);                                    // 0x00fbaf50
    void FUN_00fbaf10(int);                                    // 0x00fbaf10
    void FUN_00fbd6b0(int);                                    // 0x00fbd6b0
    void FUN_00fb9240(float, float, float);                    // 0x00fb9240
    void FUN_00fb91d0(float, float, float);                    // 0x00fb91d0
    void FUN_00fbd6e0(float, float, float);                    // 0x00fbd6e0
    void FUN_00fbd7b0(float, float, float);                    // 0x00fbd7b0
    void FUN_00b8dde0(void*, int);                             // 0x00b8dde0
    void* FUN_00b8d8a0();                                      // 0x00b8d8a0
    void FUN_00b87bb0();                                       // 0x00b87bb0
    void FUN_00b84270();                                       // 0x00b84270
    void FUN_00b87dc0();                                       // 0x00b87dc0 ComputeContinents
    void* FUN_00b8d8e0();                                      // 0x00b8d8e0
    void FUN_00f9b8c0(int, int, int, int, float);              // 0x00f9b8c0
    void FUN_00eeee40(void*);                                  // 0x00eeee40 vector erase
    void FUN_00f33a10(void*, void*, void*);                    // 0x00f33a10 copy<16>
    void FUN_00f339d0(void*, void*, void*);                    // 0x00f339d0 copy<0x38>
    void FUN_0057edf0(void*);                                  // 0x0057edf0 erase<bool>
    void FUN_00553d60(void*);                                  // 0x00553d60 erase<string>
    void* FUN_00ecff90(void*);                                 // 0x00ecff90 ctor helper
    void FUN_00c70910(int);                                    // 0x00c70910 cPlanet::SetRotationNull
    void FUN_00b225d0(void*);                                  // 0x00b225d0 RemoveNoun
    int  FUN_00bbc670();                                       // 0x00bbc670 returns int
    float FUN_00fb8a00();                                      // 0x00fb8a00 returns float
    float FUN_00fb7b90();                                      // 0x00fb7b90 returns float
    void FUN_00f401a0();                                       // 0x00f401a0 RefreshAll
    void FUN_00f427c0();                                       // 0x00f427c0
};
static inline Ext* E(void* p) { return (Ext*)p; }

// ---------------------------------------------------------------------------
// local layouts
// ---------------------------------------------------------------------------
struct Mat3 { float m[9]; };
struct Vec3 { float x, y, z; };
struct XForm {
    u16 flags;          // +0x00
    u16 mod;            // +0x02
    float tx, ty, tz;   // +0x04
    float scale;        // +0x10
    float rot[9];       // +0x14
};
struct Variant16 { u16 a, b, c, d; u16 flags; u16 pad0; u8 pad[8]; };
struct NounRef { void* noun; int* unk4; int idx; };   // 12 bytes

// ---------------------------------------------------------------------------
// the panel object
// ---------------------------------------------------------------------------
struct SPObj {
    u8 raw[0x200];
    void f373a0(int, int, u32*, int, int, int);
    void f374a0(void*);
    void f374f0();
    void f37690(void*);
    void f37a40(void*, char);
    void f37b20();
    void f37b60();
    char f37be0();
    void f37f20(int);
    void f38150(void*);
};

static inline void** VTP(void* o) { return *(void***)o; }

// ===========================================================================
// 0x00f373a0
// ===========================================================================
// @ 0x00f373a0
void SPObj::f373a0(int a2, int a3, u32* a4, int a5, int a6, int a7) {
    u32 seed = 0;
    void* obj = *(void**)(raw + 0xc);
    if (obj) {
        void* prop = 0;
        char ok = ((char(__thiscall*)(void*, u32, void**))VTP(obj)[0x24 / 4])(obj, 0x2a907b7, &prop);
        if (ok && *(u16*)((char*)prop + 0x12) == 10) {
            u32* r = E(prop)->FUN_0041ea00();
            seed = *r;
        }
    }
    FUN_007dade0(seed);

    XForm t;
    t.flags = 0;
    t.mod = 0;
    E(&t.rot[0])->FUN_0041cb40(&DAT_016c8538);
    *(Vec3*)&t.tx = *(Vec3*)a4;
    t.flags |= 4;
    t.mod += 1;

    Mat3 tmp;
    Mat3* m = (Mat3*)FUN_0059c190(&tmp, (const void*)a5);
    *(Mat3*)t.rot = *m;

    t.flags |= 2;
    t.mod += 2;
    t.scale = *(float*)&a6;
    E(this)->FUN_00f35a70(a2, a3, &t, (int)seed, 0, a7);
}

// ===========================================================================
// 0x00f374a0
// ===========================================================================
// @ 0x00f374a0
void SPObj::f374a0(void* p) {
    void* obj = *(void**)(raw + 0xc);
    if (obj) {
        int* v = (int*)p;
        FUN_00f31f20(obj, 0x4e13cb7, (v[1] - v[0]) / 12, (void*)v[0]);
        E(this)->FUN_00f35c80();
    }
}

// ===========================================================================
// 0x00f374f0
// ===========================================================================
// @ 0x00f374f0
void SPObj::f374f0() {
    *(u32*)(raw + 0x1bc) = DAT_016c851c;
    *(u32*)(raw + 0x1c0) = DAT_016c8520;
    *(u32*)(raw + 0x1c4) = DAT_016c8524;
    *(u32*)(raw + 0x1c8) = DAT_016c8528;
    void* pm = (void*)(*(int*)(raw + 0xc) + 8);

    if (*(u8*)(raw + 0x18c) != 0) {
        void* p = *(void**)(raw + 0x190);
        if (p) *(u8*)((char*)p + 0x880) = 1;
        void* pmr = FUN_00b3d350_3(pm, 0, 1);
        E(pmr)->FUN_00b8d8a0();
        void* r2 = FUN_00b3d350();
        *(void**)(raw + 0x190) = *(void**)((char*)r2 + 0x24);
        if (DAT_016c8505 == 0) *(u8*)(raw + 0x18c) = 0;
    } else {
        void* b = FUN_00b3d350();
        void* edi = *(void**)(raw + 0x190);
        if (DAT_016c8504 == 0) {
            FUN_00f97660();
        } else {
            ((void(__thiscall*)(void*))VTP(edi)[0xac / 4])(edi);
        }
        ((void(__thiscall*)(void*))VTP(edi)[0xec / 4])(edi);
        ((void(__thiscall*)(void*))VTP(edi)[0xf8 / 4])(edi);
        E(*(void**)(raw + 0x194))->FUN_00fb7a90();
        *(u8*)((char*)edi + 0x880) = 1;
        void* p190 = *(void**)(raw + 0x190);
        ((void(__thiscall*)(void*, void*))VTP(p190)[0x114 / 4])(p190, *(void**)(raw + 0xc));
        E(edi)->FUN_00f9b8c0(0, 0, 0, 1, DAT_01486110);
        void* p190b = *(void**)(raw + 0x190);
        ((void(__thiscall*)(void*))VTP(p190b)[0xa8 / 4])(p190b);
        E(b)->FUN_00b87bb0();
        E(b)->FUN_00b84270();
    }

    void* p190 = *(void**)(raw + 0x190);
    if (p190) {
        void* iVar5 = ((void*(__thiscall*)(void*))VTP(p190)[0x10 / 4])(p190);
        void* iVar6 = ((void*(__thiscall*)(void*))VTP(p190)[0x0c / 4])(p190);
        if (iVar5 != (void*)-0x2f4 && iVar6) {
            char* c6 = (char*)iVar6;
            char* c5 = (char*)iVar5;
            float f1 = *(float*)(c6 + 0x3c);
            float f2 = *(float*)(c6 + 0x38);
            float f0 = *(float*)(c6 + 0x40);
            *(float*)(c5 + 0x444) = (*(float*)(c6 + 0x44) + f1) * f2;
            *(float*)(c5 + 0x448) = (f0 + f1) * f2;
        }
    }
    E(this)->FUN_00f368b0();
}

// ===========================================================================
// 0x00f37690
// ===========================================================================
// @ 0x00f37690
void SPObj::f37690(void* arg) {
    E(this)->FUN_00f32bf0((int)arg);

    Variant16 v;
    v.a = 0; v.b = 0;
    void* obj = *(void**)(raw + 0xc);
    ((void(__thiscall*)(void*, u32, void*))VTP(obj)[0x14 / 4])(obj, 0x40539d4, &v);
    if (v.flags & 4) {
        E(&v)->FUN_0093db80(0);
    }

    int* idp = (int*)(raw + 0x160);
    *idp = 0;
    obj = *(void**)(raw + 0xc);
    char c = ((char(__thiscall*)(void*, u32))VTP(obj)[0x1c / 4])(obj, 0x56b14f05);
    if (!c) {
        int cnt = 0;
        void* ptr = 0;
        FUN_006a0ae0(obj, 0x40cf84f, &cnt, &ptr);
        if (cnt > 0) {
            *idp = *(int*)ptr;
            Variant16 v2;
            v2.a = 0; v2.b = 0;
            E(&v2)->FUN_00427fd0(idp);
            obj = *(void**)(raw + 0xc);
            ((void(__thiscall*)(void*, u32, void*))VTP(obj)[0x14 / 4])(obj, 0x56b14f05, &v2);
            if (v2.flags & 4) {
                E(&v2)->FUN_0093db80(0);
            }
        }
    }

    obj = *(void**)(raw + 0xc);
    if (obj) {
        void* prop = 0;
        char ok = ((char(__thiscall*)(void*, u32, void**))VTP(obj)[0x24 / 4])(obj, 0x56b14f05, &prop);
        if (ok && *(u16*)((char*)prop + 0x12) == 10) {
            u32* r = E(prop)->FUN_0041ea00();
            *idp = (int)*r;
        }
    }

    E(this)->FUN_00f34660();
    f374f0();
    void* rec = FUN_010212a0();
    if (*(int*)((char*)DAT_016c7aa4 + 0xd0) == 2) {
        E(this)->FUN_00f31f80();
    }
    void* model = FUN_00b3d350();
    void* pm = *(void**)((char*)model + 0x24);
    *(void**)(raw + 0x190) = pm;
    void* p194 = ((void*(__thiscall*)(void*))VTP(pm)[0x10 / 4])(pm);
    *(void**)(raw + 0x194) = p194;
    *(float*)((char*)rec + 0xb4) = E(p194)->FUN_00fb8a00();
    *(float*)((char*)rec + 0xb0) = E(*(void**)(raw + 0x194))->FUN_00fb7b90();

    int x = E(FUN_00b3d430(rec))->FUN_00bbc670();
    *(int*)((char*)rec + 0x28) = x + 2;

    int a = *(int*)(raw + 0xec);
    if ((u32)(a - 1) <= 0xe) E(*(void**)(raw + 0x194))->FUN_00fbaf50(a);
    int b = *(int*)(raw + 0xf0);
    if ((u32)(b - 1) <= 0xe) E(*(void**)(raw + 0x194))->FUN_00fbaf10(b);

    FUN_00f31c40((int)*(float*)(raw + 0xe0));
    FUN_00f31cb0((int)*(float*)(raw + 0xe4));

    if (*(u8*)(raw + 0x104) == 0) E(this)->FUN_00f343a0(1);
    E(*(void**)(raw + 0x194))->FUN_00fbd6b0(1);
    *(u8*)(raw + 0x104) = 1;

    E(*(void**)(raw + 0x194))->FUN_00fb9240(
        *(float*)(raw + 0x148), *(float*)(raw + 0x14c), *(float*)(raw + 0x150));
    E(*(void**)(raw + 0x194))->FUN_00fb91d0(
        *(float*)(raw + 0x154), *(float*)(raw + 0x158), *(float*)(raw + 0x15c));
    E(*(void**)(raw + 0x194))->FUN_00fbd6e0(
        *(float*)(raw + 0x130), *(float*)(raw + 0x134), *(float*)(raw + 0x138));
    E(*(void**)(raw + 0x194))->FUN_00fbd7b0(
        *(float*)(raw + 0x13c), *(float*)(raw + 0x140), *(float*)(raw + 0x144));

    E(this)->FUN_00f344e0((void*)(raw + 0x11c), (void*)(raw + 0x108));
    E(rec)->FUN_00b8dde0((void*)(*(int*)(raw + 0xc) + 8), 1);

    E(this)->FUN_00f35c80();
    E(this)->FUN_00f347e0();
    E(this)->FUN_00f34660();
    E(this)->FUN_00f32440(1);
    E(this)->FUN_00f35f70();
    *(u8*)(raw + 0x1ba) = 0;
    *(u8*)(raw + 0x1b9) = 0;

    void* ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, u32, int, int, int))VTP(ms)[0x18 / 4])(
        ms, 0x36b154d8, 0, 0, 0);

    void* p100 = *(void**)(raw + 0x100);
    if (p100) {
        char c2 = ((char(__thiscall*)(void*))VTP(p100)[0x10 / 4])(p100);
        if (c2) {
            ((void(__thiscall*)(void*, int))VTP(p100)[0x0c / 4])(p100, 1);
            void* p100b = *(void**)(raw + 0x100);
            if (p100b) {
                *(void**)(raw + 0x100) = 0;
                ((void(__thiscall*)(void*))VTP(p100b)[4 / 4])(p100b);
            }
        }
    }
    E(this)->FUN_00f32cb0();
}

// ===========================================================================
// 0x00f37a40
// ===========================================================================
// @ 0x00f37a40
void SPObj::f37a40(void* arg, char flag) {
    int local_10 = 0;
    if (!flag) {
        void* pman = FUN_0067de30();
        int old = local_10;
        if (old) {
            local_10 = 0;
            ((void(__thiscall*)(void*))VTP((void*)old)[1])((void*)old);
        }
        char c = ((char(__thiscall*)(void*, u32, int, int*))VTP(pman)[0x2c / 4])(
            pman, *(u32*)arg, *(int*)((char*)arg + 8), &local_10);
        if (c) goto done;
    }
    {
        int local_c = 0, local_8 = 0, local_4 = 0;
        void* idg = FUN_0067de60();
        ((void(__thiscall*)(void*, int*, u32, int))VTP(idg)[8 / 4])(
            idg, &local_c, 0xb1b104, *(int*)((char*)arg + 8));
        void* m = FUN_00f48a80();
        void* got = ((void*(__thiscall*)(void*, void*))VTP(m)[4 / 4])(m, &local_c);
        int old = local_10;
        if (got != (void*)old) {
            if (got) ((void(__thiscall*)(void*))VTP(got)[0])(got);
            local_10 = (int)got;
            if (old) ((void(__thiscall*)(void*))VTP((void*)old)[1])((void*)old);
        }
    }
done:
    if (local_10) {
        f37690((void*)local_10);
        if (local_10) {
            ((void(__thiscall*)(void*))VTP((void*)local_10)[1])((void*)local_10);
        }
    }
}

// ===========================================================================
// 0x00f37b20
// ===========================================================================
// @ 0x00f37b20
void SPObj::f37b20() {
    int k[3];
    k[0] = 0; k[1] = 0; k[2] = 0;
    FUN_0068d840(k, L"@planet+templates_artDirected!", 0, 0);
    f37a40(k, 1);
}

// ===========================================================================
// 0x00f37b60
// ===========================================================================
// @ 0x00f37b60
void SPObj::f37b60() {
    *(void**)(raw + 0x198) = *(void**)((char*)DAT_016c7aa4 + 0x74);
    if (*(u8*)(raw + 0x1ba) != 0) {
        f37690(*(void**)(raw + 0xc));
        *(void**)(raw + 0x198) = *(void**)((char*)DAT_016c7aa4 + 0x74);
        FUN_00f3e3b0(0);
        void* model = (void*)FUN_00b3d350();
        E(model)->FUN_00b87dc0();
        E(*(void**)(raw + 0x198))->FUN_00f401a0();
        E(*(void**)(raw + 0x198))->FUN_00f427c0();
    }
    if (*(u8*)(raw + 0x1b9) != 0) {
        E(this)->FUN_00f347e0();
        *(u8*)(raw + 0x1b9) = 0;
    }
}

// ===========================================================================
// 0x00f37be0
// ===========================================================================
// @ 0x00f37be0
char SPObj::f37be0() {
    char local = 0;
    int n1 = (*(int*)(raw + 0x18) - *(int*)(raw + 0x14)) / 12;
    if (n1 != 0) {
        int* base = (int*)(raw + 0x14);
        for (int i = 0; i < n1; ++i) {
            if (FUN_00ecc100((u32)base[0] + i * 12) != 0) {
                int* v14 = (int*)(raw + 0x14);
                E(v14)->FUN_00eeee40((void*)(v14[0] + i * 12));
                int nt = (*(int*)(raw + 0x2c) - (*(int*)(raw + 0x28) + i * 0x38)) / 0x38;
                *(int*)(raw + 0x2c) += nt * -0x38;
                int j = i * 4;
                int* v50 = (int*)(raw + 0x50);
                E(v50)->FUN_0057edf0((void*)(v50[0] + j));
                *(int*)(raw + 0x54) -= 4;
                if (*(int*)(raw + 0x64) != *(int*)(raw + 0x68)) {
                    int* v64 = (int*)(raw + 0x64);
                    E(v64)->FUN_00f339d0((void*)(v64[0] + j + 4), (void*)v64[1], (void*)(v64[0] + j));
                }
                *(int*)(raw + 0x68) -= 4;
                int* v3c = (int*)(raw + 0x3c);
                E(v3c)->FUN_0057edf0((void*)(v3c[0] + j));
                *(int*)(raw + 0x40) -= 4;
                if (*(int*)(raw + 0x78) != *(int*)(raw + 0x7c)) {
                    E((void*)(raw + 0x78))->FUN_00553d60((void*)(*(int*)(raw + 0x78) + i * 16));
                }
                int* v8c = (int*)(raw + 0x8c);
                E(v8c)->FUN_0057edf0((void*)(v8c[0] + j));
                *(int*)(raw + 0x90) -= 4;
                local = 1;
                break;
            }
        }
    }
    char found2 = 0;
    int n2 = (*(int*)(raw + 0xa4) - *(int*)(raw + 0xa0)) / 12;
    if (n2 != 0) {
        int* base = (int*)(raw + 0xa0);
        for (int i = 0; i < n2; ++i) {
            if (FUN_00ecc100((u32)base[0] + i * 12) != 0) {
                int nt = (*(int*)(raw + 0xa4) - (*(int*)(raw + 0xa0) + i * 12)) / 12;
                *(int*)(raw + 0xa4) += nt * -12;
                int m = (*(int*)(raw + 0xb8) - (*(int*)(raw + 0xb4) + i * 0x38)) / 0x38;
                *(int*)(raw + 0xb8) += m * -0x38;
                found2 = 1;
                break;
            }
        }
    }
    if (local || found2) {
        E(this)->FUN_00f35f70();
        E(this)->FUN_00f32d10();
        *(u8*)(raw + 0x1ba) = 1;
        f37b60();
    }
    return local;
}

// ===========================================================================
// 0x00f37f20
// ===========================================================================
// @ 0x00f37f20
void SPObj::f37f20(int arg) {
    *(u8*)(raw + 0x18c) = 1;
    *(u8*)(raw + 0x1b9) = 1;
    *(u8*)(raw + 0x1ba) = 1;
    if (*(int*)((char*)DAT_016c7aa4 + 0xd0) == 2) {
        void* rec = E(FUN_010212a0())->FUN_00b8d8e0();
        void* pman = FUN_0067de30();
        void* cur = *(void**)(raw + 0xc);
        if (cur) {
            *(void**)(raw + 0xc) = 0;
            ((void(__thiscall*)(void*))VTP(cur)[1])(cur);
        }
        ((void(__thiscall*)(void*, int, int, void**))VTP(pman)[0x2c / 4])(
            pman, *(int*)rec, *(int*)((char*)rec + 8), (void**)(raw + 0xc));
    } else {
        void* p = FUN_00f473a0(0x38, "Simulator", 0, 0, 0, 0);
        void* plist = 0;
        if (p) plist = FUN_006a1c40(p);
        void* cur = *(void**)(raw + 0xc);
        if (plist != cur) {
            if (plist) ((void(__thiscall*)(void*))VTP(plist)[0])(plist);
            *(void**)(raw + 0xc) = plist;
            if (cur) ((void(__thiscall*)(void*))VTP(cur)[1])(cur);
        }
        int local_c = 0, local_8 = 0, local_4 = 0;
        void* idg = FUN_0067de60();
        ((void(__thiscall*)(void*, int*, u32, int, int, int))VTP(idg)[4 / 4])(
            idg, &local_c, 0xb1b104, 0x84, 0, 0xa0);
        void* pman = FUN_0067de30();
        ((void(__thiscall*)(void*, void*, int, void*))VTP(pman)[0x34 / 4])(
            pman, *(void**)(raw + 0xc), 0xa0, 0);
    }

    int* A = (int*)arg;
    if (A[0] == 0) {
        if (A[3] == 0) {
            f37b20();
        } else {
            void* r = 0;
            void* mgr = FUN_0067dcd0();
            ((void(__thiscall*)(void*, void*, void*, int, int, int, int))VTP(mgr)[0x0c / 4])(
                mgr, (void*)&A[3], &r, 0, 0, 0, 0);
            void* out = 0;
            if (r) out = ((void*(__thiscall*)(void*, u32))VTP(r)[0x0c / 4])(r, 0xe742574a);
            FUN_00f26330();
            if (r) ((void(__thiscall*)(void*))VTP(r)[1])(r);
        }
    }

    void* ap = FUN_01021260();
    if (ap) E(ap)->FUN_00c70910(1);

    void* p = FUN_00f473a0(0xc, "Simulator/cScenarioTerraformEconomy", 0, 0, 0, 0);
    void* obj = 0;
    if (p) obj = E(p)->FUN_00ecff90(this);

    int* old = *(int**)(raw + 0x10);
    if (obj != old) {
        if (obj) *(int*)((char*)obj + 4) += 1;
        *(void**)(raw + 0x10) = obj;
        if (old) {
            int n = old[1] - 1;
            old[1] = n;
            if (n == 0) {
                old[1] = 1;
                ((void(__thiscall*)(void*, int))VTP(old)[0])(old, 1);
            }
        }
    }

    void* ms = FUN_0067dcc0();
    *(void**)(raw + 0x178) = ms;
    *(void**)(raw + 0x17c) = this;
    *(void**)(raw + 0x180) = &DAT_0148d084;
    *(int*)(raw + 0x184) = 1;
    *(int*)(raw + 0x188) = 0;
    if (ms) ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, this, 0x36b154d8);
}

// ===========================================================================
// 0x00f38150
// ===========================================================================
// @ 0x00f38150
void SPObj::f38150(void* arg) {
    NounRef* p = (NounRef*)FUN_00f32790(arg);
    if (!p) return;
    int idx = p->idx;
    int off = ((int)p - *(int*)(raw + 0x19c)) >> 4;
    if (*(u8*)((char*)p->unk4 + 0x68) == 0) {
        E((void*)(raw + 0x14))->FUN_00eeee40((void*)(*(int*)(raw + 0x14) + idx * 12));
        int base = *(int*)(raw + 0x28) + idx * 0x38;
        if ((u32)(base + 0x38) < *(u32*)(raw + 0x2c))
            E((void*)(raw + 0x28))->FUN_00f339d0((void*)(base + 0x38), (void*)*(int*)(raw + 0x2c), (void*)base);
        *(int*)(raw + 0x2c) -= 0x38;
        int j = idx * 4;
        {
            int* v50 = (int*)(raw + 0x50);
            if ((u32)(v50[0] + j + 4) < (u32)v50[1])
                E(v50)->FUN_00f339d0((void*)(v50[0] + j + 4), (void*)v50[1], (void*)(v50[0] + j));
            v50[1] -= 4;
        }
        if (*(int*)(raw + 0x64) != *(int*)(raw + 0x68))
            E((void*)(raw + 0x64))->FUN_0057edf0((void*)(*(int*)(raw + 0x64) + j));
        {
            int* v3c = (int*)(raw + 0x3c);
            if ((u32)(v3c[0] + j + 4) < (u32)v3c[1])
                E(v3c)->FUN_00f339d0((void*)(v3c[0] + j + 4), (void*)v3c[1], (void*)(v3c[0] + j));
            v3c[1] -= 4;
        }
        if (*(int*)(raw + 0x78) != *(int*)(raw + 0x7c))
            E((void*)(raw + 0x78))->FUN_00553d60((void*)(*(int*)(raw + 0x78) + idx * 16));
        {
            int* v8c = (int*)(raw + 0x8c);
            if ((u32)(v8c[0] + j + 4) < (u32)v8c[1])
                E(v8c)->FUN_00f339d0((void*)(v8c[0] + j + 4), (void*)v8c[1], (void*)(v8c[0] + j));
            v8c[1] -= 4;
        }
    } else {
        E((void*)(raw + 0xa0))->FUN_00eeee40((void*)(*(int*)(raw + 0xa0) + idx * 12));
        int base = *(int*)(raw + 0xb4) + idx * 0x38;
        if ((u32)(base + 0x38) < *(u32*)(raw + 0xb8))
            E((void*)(raw + 0xb4))->FUN_00f339d0((void*)(base + 0x38), (void*)*(int*)(raw + 0xb8), (void*)base);
        *(int*)(raw + 0xb8) -= 0x38;
    }
    void* noun = p->noun;
    E(FUN_00b3d300((u32)(int)noun))->FUN_00b225d0(noun);
    int* n2 = (int*)p->noun;
    if (n2) {
        p->noun = 0;
        ((void(__thiscall*)(void*))VTP(n2)[1])(n2);
    }
    int base2 = *(int*)(raw + 0x19c) + off * 16;
    if ((u32)(base2 + 16) < *(u32*)(raw + 0x1a0))
        E((void*)(raw + 0x19c))->FUN_00f33a10((void*)(base2 + 16), (void*)*(int*)(raw + 0x1a0), (void*)base2);
    *(int*)(raw + 0x1a0) -= 16;
    int** tail = (int**)(*(int*)(raw + 0x1a0));
    if (tail && *tail) {
        ((void(__thiscall*)(void*))VTP(*tail)[1])(*tail);
    }
    E(this)->FUN_00f35f70();
    E(this)->FUN_00f32d10();
    *(u8*)(raw + 0x1ba) = 1;
    f37b60();
}
