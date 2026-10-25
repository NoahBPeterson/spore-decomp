// s00cb91d0.cpp -- gold6 batch, worker 25
// Reconstructed from the annotated disassembly + Ghidra decompiles in
// work/match/scratch_s00cb91d0_cards.txt.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
#include <math.h>

#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

extern "C" void  __cdecl FUN_00f47380(void*);                                  // operator_delete_array
extern "C" void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int);    // operator_new
extern "C" void  __cdecl FUN_009216a0(void*, void*, void*, int);                // eastl::RBTreeInsert
extern "C" void* __cdecl FUN_00b3d350(void);                                    // SP::PlanetModel
extern "C" void* __cdecl FUN_00b3d300(uint32_t);                                // SP::NounManager
extern "C" void  __cdecl FUN_00bff2d0(void*, int);
extern "C" void* __cdecl FUN_0067ddd0(void);                                    // EffectsManagerPtr
extern "C" void* __cdecl FUN_00b3d240(void);
extern "C" void* __cdecl FUN_0069b440(void*, void*);                            // Matrix3FromFacingAndUp
extern "C" float __fastcall FUN_0104bdc0(void* self);                            // 0x0104bdc0 (this in ecx)
extern "C" unsigned int __fastcall FUN_0104bf10(void* self);                     // 0x0104bf10
extern "C" unsigned int __fastcall FUN_0104bef0(void* self);                     // 0x0104bef0
extern "C" void* __cdecl FUN_0102ac50(int, void*);
extern "C" void* __cdecl FUN_0102acb0(int, void*, void*);
// spatial-query helpers used by the two large walkers (0x00cb9810 / 0x00cb9bd0)
extern "C" float __stdcall FUN_0104bdb0(void* vec, int a, int b, int c);          // 0x0104bdb0 fill spatial-object vector
extern "C" float __fastcall FUN_00ce6940(void* self);                             // 0x00ce6940 (this in ecx)
extern "C" unsigned int __fastcall RandomUint32Uniform(void* self, unsigned int n);  // 0x00a68fb0
extern "C" double __fastcall RandomDoubleUniform(void* self);                     // 0x009360d0
extern "C" void __fastcall FUN_00ad92d0(void* vec);                               // 0x00ad92d0 eastl::vector dtor
extern void* gMathRandom;                                                        // 0x01601760

extern float DAT_01485720;      // _HK_REAL_ONE
extern float DAT_013ec4d0;
extern float DAT_0169aa18;
extern float DAT_0169aa1c;
extern float DAT_0169aa20;
extern float DAT_0169a9f4;

class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void   F_18660();                       // 0x00b18660  SP::cGameData::cGameData
    void   F_c43860();                      // 0x00c43860
    void   F_c432e0();                      // 0x00c432e0
    void   F_184c0();                       // 0x00b184c0  SP::cGameData::~cGameData
    int    F_b7e3e0();                      // 0x00b7e3e0
    void*  F_b25f40();                      // 0x00b25f40
    void   F_0041cb40(void*);               // 0x0041cb40  rw::math::Matrix3::Assign

    // ---- slice targets -------------------------------------------------------
    TObj* FUN_00cb94b0();                                   // 0x00cb94b0 Simulator::cICBM::cICBM
    void* _virtual_dtor(uint8_t);                           // 0x00cb9600 Object::_virtual_dtor
    void* FUN_00cb9b90(uint8_t);                            // 0x00cb9b90 deleting dtor
    void  FUN_00cb9780(void**, void*, void**, char);        // 0x00cb9780 eastl rbtree insert helper
    void  FUN_00cb91d0();                                   // 0x00cb91d0 SP::cResourceProjectile::Explode
    void  FUN_00cb9650();                                   // 0x00cb9650 SP::cICBM::Explode
    void  FUN_00cb9810();                                   // 0x00cb9810 SpatialQuery helper
    void  FUN_00cb9bd0();                                   // 0x00cb9bd0 SP::cFlakProjectile::Explode
};

// EffectsManager spatial record (also used by the Explode family):
//   +0x00 u16 flags0  +0x02 u16 cnt0  +0x04 u16 flags1  +0x06 u16 cnt1
//   +0x08 f32 x       +0x0c f32 y     +0x10 f32 z       +0x14 f32 one
//   +0x18 f32 m[9]  (a Matrix3Rows)
struct Rec {
    uint16_t flags0;
    uint16_t cnt0;
    uint16_t flags1;
    uint16_t cnt1;
    float    x;
    float    y;
    float    z;
    float    one;
    float    m[9];
};

// ===========================================================================
// 0x00cb94b0 - Simulator::cICBM::cICBM (constructor)
// ===========================================================================
// @ 0x00cb94b0
TObj* TObj::FUN_00cb94b0() {
    ((TObj*)this)->F_18660();
    TObj* sub = (TObj*)((char*)this + 0x34);
    sub->F_c43860();
    *(uint32_t*)((char*)this + 0x504) = 0x145dca8;
    float zero = 0.0f;
    *(float*)((char*)this + 0x508) = zero;
    *(float*)((char*)this + 0x50c) = zero;
    *(float*)((char*)this + 0x510) = zero;
    *(uint8_t*)((char*)this + 0x514) = 0;
    *(uint32_t*)((char*)this + 0x000) = 0x1475ff8;
    *(uint32_t*)((char*)this + 0x004) = 0x1475fe4;
    *(uint32_t*)((char*)this + 0x034) = 0x1475ee8;
    *(uint32_t*)((char*)this + 0x108) = 0x1475edc;
    *(uint32_t*)((char*)this + 0x504) = 0x1475eb4;
    *(uint32_t*)((char*)this + 0x520) = 0;
    return this;
}

// ===========================================================================
// 0x00cb9600 - Object::_virtual_dtor (destroying destructor)
// ===========================================================================
// @ 0x00cb9600
void* TObj::_virtual_dtor(uint8_t param_2) {
    uint32_t p = *(uint32_t*)((char*)this + 0x520);
    if (p != 0) {
        ((void(__thiscall*)(uint32_t))VF(p, 0x64))(p);
    }
    TObj* sub = (TObj*)((char*)this + 0x34);
    *(uint32_t*)((char*)this + 0x504) = 0x145dca8;
    sub->F_c432e0();
    ((TObj*)this)->F_184c0();
    if ((param_2 & 1) != 0) {
        FUN_00f47380(this);
    }
    return this;
}

// ===========================================================================
// 0x00cb9b90 - deleting destructor (EA::Trace::ITracerBase / ContentValidationSummarizer)
// ===========================================================================
// @ 0x00cb9b90
void* TObj::FUN_00cb9b90(uint8_t param_2) {
    uint32_t p = *(uint32_t*)((char*)this + 0x10);
    if (p != 0 && *(uint32_t*)(p - 4) != 0) {
        FUN_00f47380((void*)p);
    }
    *(uint32_t*)((char*)this + 0x08) = 0x13ec458;
    *(uint32_t*)((char*)this + 0x00) = 0x13eb938;
    if ((param_2 & 1) != 0) {
        FUN_00f47380(this);
    }
    return this;
}

// ===========================================================================
// 0x00cb9780 - eastl red-black-tree insert helper (operator_new + RBTreeInsert)
// ===========================================================================
// @ 0x00cb9780
void TObj::FUN_00cb9780(void** param_2, void* param_3, void** param_4, char param_5) {
    int side;
    if (param_5 == 0 && param_3 != (void*)((char*)this + 4)
        && *(uint32_t*)param_4 >= *(uint32_t*)((char*)param_3 + 0x10)) {
        side = 1;
    } else {
        side = 0;
    }
    void* node = FUN_00f473a0(0x14, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    void** slot = (void**)((char*)node + 0x10);
    if (slot != 0) {
        void* val = *param_4;
        *slot = val;
        if (val != 0) {
            ((void(__thiscall*)(void*))VF(val, 0xbc))(val);
        }
    }
    FUN_009216a0(node, param_3, (char*)this + 4, side);
    *(uint32_t*)((char*)this + 0x14) += 1;
    *(uint32_t*)param_2 = (uint32_t)node;
}

// ===========================================================================
// 0x00cb91d0 - SP::cResourceProjectile::Explode (spatial effect record)
// ===========================================================================
// @ 0x00cb91d0
void TObj::FUN_00cb91d0() {
    void* em = FUN_0067ddd0();
    TObj* es = (TObj*)((void*(__thiscall*)(void*, uint32_t))VF(em, 0x54))(em, 0x3701a5c);
    uint32_t tag;
    int pm = ((TObj*)FUN_00b3d350())->F_b7e3e0();
    uint32_t t = *(uint32_t*)((char*)this + 0x51c);
    if (pm != 0) {
        if (*(uint8_t*)((char*)this + 0x554) != 0) {
            tag = 0xba78f977;
        } else if (t == 0 || *(float*)(t + 0x224) < DAT_013ec4d0) {
            tag = 0x95938523;
        } else {
            tag = 0x971fa14;
        }
    } else {
        if (*(uint8_t*)((char*)this + 0x554) != 0) {
            tag = 0xba78f977;
        } else if (t == 0 || *(float*)(t + 0x224) < DAT_013ec4d0) {
            tag = 0x96a1703;
        } else {
            tag = 0x63fbd7f4;
        }
    }
    void* ref = 0;
    char ok = ((char(__thiscall*)(void*, uint32_t, int, void**))VF(es, 8))(es, tag, 0, &ref);
    if (ok != 0) {
        Rec rec;
        rec.x = DAT_0169aa18;
        rec.y = DAT_0169aa1c;
        rec.flags0 = 0;
        rec.z = DAT_0169aa20;
        rec.cnt0 = 0;
        rec.one = 1.0f;
        ((TObj*)&rec.m[0])->F_0041cb40(&DAT_0169a9f4);
        TObj* sub = (TObj*)((char*)this + 0x34);
        float* pl = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        rec.x = pl[0];
        rec.y = pl[1];
        rec.z = pl[2];
        rec.flags0 |= 4;
        rec.cnt0++;
        float* pl2 = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        uint8_t tmp[0x10];
        void* fr = ((void*(__thiscall*)(void*, void*, float*))VF(sub, 0x5c))(sub, tmp, pl2);
        float mtmp[9];
        float* mret = (float*)FUN_0069b440(mtmp, fr);
        for (int i = 0; i < 9; i++) {
            rec.m[i] = mret[i];
        }
        rec.flags1 |= 2;
        rec.cnt1++;
        ((void(__thiscall*)(void*, void*))VF(ref, 0x18))(ref, &rec);
        TObj* q = (TObj*)((TObj*)FUN_00b3d300(*(uint32_t*)((char*)this + 0x550)))->F_b25f40();
        if (q != 0) {
            float pos[3];
            pos[0] = *(float*)((char*)q + 0xc4);
            pos[1] = *(float*)((char*)q + 0xc8);
            pos[2] = *(float*)((char*)q + 0xcc);
            ((void(__thiscall*)(void*, int, float*, int))VF(ref, 0x44))(ref, 5, pos, 3);
        }
        ((void(__thiscall*)(void*, int))VF(ref, 8))(ref, 0);
    }
    uint32_t t2 = *(uint32_t*)((char*)this + 0x51c);
    if (t2 != 0) {
        if (*(uint8_t*)((char*)this + 0x554) != 0) {
            FUN_00bff2d0((void*)*(uint32_t*)((char*)this + 0x550), 3);
        } else {
            *(uint8_t*)(t2 + 0x1e8) = 1;
        }
    }
    if (ref != 0) {
        ((void(__thiscall*)(void*))VF(ref, 4))(ref);
    }
}

// ===========================================================================
// 0x00cb9650 - SP::cICBM::Explode (spatial effect record)
// ===========================================================================
// @ 0x00cb9650
void TObj::FUN_00cb9650() {
    void* em = FUN_0067ddd0();
    TObj* es = (TObj*)((void*(__thiscall*)(void*, uint32_t))VF(em, 0x54))(em, 0x3701a5c);
    void* ref = 0;
    char ok = ((char(__thiscall*)(void*, uint32_t, int, void**))VF(es, 8))(es, 0x27e375b3, 0, &ref);
    if (ok != 0) {
        Rec rec;
        rec.x = DAT_0169aa18;
        rec.y = DAT_0169aa1c;
        rec.flags0 = 0;
        rec.z = DAT_0169aa20;
        rec.cnt0 = 0;
        rec.one = 1.0f;
        ((TObj*)&rec.m[0])->F_0041cb40(&DAT_0169a9f4);
        TObj* sub = (TObj*)((char*)this + 0x34);
        float* pl = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        rec.x = pl[0];
        rec.y = pl[1];
        rec.z = pl[2];
        rec.flags0 |= 4;
        rec.cnt0++;
        float* pl2 = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        uint8_t tmp[0x10];
        void* fr = ((void*(__thiscall*)(void*, void*, float*))VF(sub, 0x5c))(sub, tmp, pl2);
        float mtmp[9];
        float* mret = (float*)FUN_0069b440(mtmp, fr);
        for (int i = 0; i < 9; i++) {
            rec.m[i] = mret[i];
        }
        rec.flags1 |= 2;
        rec.cnt1++;
        ((void(__thiscall*)(void*, void*))VF(ref, 0x18))(ref, &rec);
        ((void(__thiscall*)(void*, int))VF(ref, 8))(ref, 0);
    }
    if (ref != 0) {
        ((void(__thiscall*)(void*))VF(ref, 4))(ref);
    }
}

// ===========================================================================
// 0x00cb9810 - spatial-object query walker (state 0 / 4 / other dispatch)
// ===========================================================================
// A local eastl::vector<AutoRefCount<cSpatialObject>> is filled by the loco sub-object's
// slot 0x2c; each element is filtered through its slot 0xb8 and its slot-8 object's position is
// used to build a normalised direction for the this slot 0x4c effect callback.  The vector is
// released through each element's slot 0xc0 and operator_delete_array with the allocator cookie.
struct ObjVec {
    void** mpBegin;   // +0x00
    void** mpEnd;     // +0x04
    void** mpCap;     // +0x08
};

// @ 0x00cb9810
void TObj::FUN_00cb9810() {
    void* mgr = FUN_00b3d240();
    uint32_t state = *(uint32_t*)((char*)this + 0x530);
    TObj* loco = (TObj*)((char*)this + 0x34);
    if (state == 0) {
        float xf[4];
        void* p = ((void*(__thiscall*)(void*, void*))VF(loco, 0x5c))(loco, xf);
        p = ((void*(__thiscall*)(void*, void*))VF(loco, 0x2c))(loco, p);
        ((void(__thiscall*)(void*, uint32_t, void*))VF(mgr, 0x60))(mgr, 0x147e293, p);
    }

    ObjVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    void* hit = ((void*(__thiscall*)(void*, float, ObjVec*, int, int, int))VF(loco, 0x2c))(
        loco, 3.0f, &vec, 0, 0, 0);
    ((void(__thiscall*)(void*, void*))VF(mgr, 0x48))(mgr, hit);

    int count = (int)((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2;
    if (state == 4) {
        for (int i = 0; i < count; i++) {
            void* el = vec.mpBegin[i];
            if (el == 0) {
                continue;
            }
            void* filter = ((void*(__thiscall*)(void*, uint32_t))VF(el, 0xb8))(el, 0x13f94d4);
            if (filter == 0) {
                continue;
            }
            void* owner = ((void*(__thiscall*)(void*))VF((char*)this + 0x504, 0x18))(
                (char*)this + 0x504);
            if (owner == 0) {
                continue;
            }
            void* src = ((void*(__thiscall*)(void*, uint32_t))VF(owner, 0x5c))(owner, 0x137e8e0);
            if (src == 0) {
                continue;
            }
            float height = *(float*)((char*)src + 0xc50);
            void* obj = ((void*(__thiscall*)(void*))VF(filter, 8))(filter);
            float* from = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
            float* to = ((float*(__thiscall*)(void*))VF(obj, 0x2c))(obj);
            float dx = to[0] - from[0];
            float dy = to[1] - from[1];
            float dz = to[2] - from[2];
            float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
            float dir[3];
            dir[0] = inv * dx;
            dir[1] = dy * inv;
            dir[2] = dz * inv;
            void* effect = ((void*(__thiscall*)(void*, uint32_t, float*, int))VF(this, 0x4c))(
                this, state, dir, 0);
            ((void(__thiscall*)(void*, float, void*))VF(filter, 0x18))(filter, height, effect);
        }
    } else if (state != 3) {
        for (int i = 0; i < count; i++) {
            void* el = vec.mpBegin[i];
            if (el == 0) {
                continue;
            }
            void* filter = ((void*(__thiscall*)(void*, uint32_t))VF(el, 0xb8))(el, 0xb033b403);
            if (filter == 0) {
                continue;
            }
            void* obj = ((void*(__thiscall*)(void*))VF(filter, 8))(filter);
            float* from = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
            float* to = ((float*(__thiscall*)(void*))VF(obj, 0x2c))(obj);
            float dx = to[0] - from[0];
            float dy = to[1] - from[1];
            float dz = to[2] - from[2];
            float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
            float dir[3];
            dir[0] = inv * dx;
            dir[1] = dy * inv;
            dir[2] = dz * inv;
            unsigned int span = *(uint32_t*)((char*)this + 0x52c)
                              - *(uint32_t*)((char*)this + 0x528);
            unsigned int r = RandomUint32Uniform(&gMathRandom, span);
            int level = (int)(*(uint32_t*)((char*)this + 0x528) + r);
            void* effect = ((void*(__thiscall*)(void*, uint32_t, float*, int))VF(this, 0x4c))(
                this, state, dir, 0);
            ((void(__thiscall*)(void*, float, void*))VF(filter, 0x18))(filter, (float)level, effect);
        }
    }

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        void* el = *it;
        if (el != 0) {
            ((void(__thiscall*)(void*))VF(el, 0xc0))(el);
        }
    }
    if (vec.mpBegin != 0 && ((uint32_t*)vec.mpBegin)[-1] != 0) {
        FUN_00f47380(vec.mpBegin);
    }
}

// ===========================================================================
// 0x00cb9bd0 - SP::cFlakProjectile::Explode (spatial effect record + spread)
// ===========================================================================
// Walks the spatial-object vector filled by FUN_0104bdb0 on this+0x518, filters each element
// through slot 0xb8(0xb033b403), and for every surviving pair writes a spread offset into the
// object's slot 0x18 using the clamped RandomDoubleUniform range and the this slot 0x4c effect.
// It then emits one effect record (tag from FUN_0104bf10/FUN_0104bef0) and releases the vector.
// @ 0x00cb9bd0
void TObj::FUN_00cb9bd0() {
    void* mgr = FUN_00b3d240();
    ObjVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    void* holder = *(void**)((char*)this + 0x518);
    if (holder == 0) {
        FUN_00ad92d0(&vec);
        return;
    }

    TObj* loco = (TObj*)((char*)this + 0x34);
    float radius = FUN_0104bdb0(&vec, 0, 0, 0);
    void* hit = ((void*(__thiscall*)(void*, float))VF(loco, 0x2c))(loco, radius);
    ((void(__thiscall*)(void*, void*))VF(mgr, 0x48))(mgr, hit);

    int count = (int)((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2;
    char any = 0;
    for (int i = 0; i < count; i++) {
        void* el = vec.mpBegin[i];
        if (el == 0) {
            continue;
        }
        void* filter = ((void*(__thiscall*)(void*, uint32_t))VF(el, 0xb8))(el, 0xb033b403);
        if (filter == 0) {
            continue;
        }
        void* holderObj = *(void**)((char*)holder + 0x114);
        void* tail = 0;
        if (holderObj != 0) {
            tail = ((void*(__thiscall*)(void*, uint32_t))VF(holderObj, 0xb8))(holderObj, 0x13f94d4);
        }
        float* from = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
        TObj* fself = (TObj*)((char*)filter + 0x34);
        float* to = ((float*(__thiscall*)(void*))VF(fself, 0x2c))(fself);
        float dx = to[0] - from[0];
        float dy = to[1] - from[1];
        float dz = to[2] - from[2];
        float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
        float dir[3];
        dir[0] = inv * dx;
        dir[1] = dy * inv;
        dir[2] = dz * inv;

        float lo = FUN_0104bdc0(holder);
        float hi = FUN_00ce6940(holder);
        double range = (double)(lo - hi);
        double spread = RandomDoubleUniform(&gMathRandom) * range;
        if (spread >= range) {
            spread = range;
        } else if (spread < 0.0) {
            spread = 0.0;
        }

        void* effect = ((void*(__thiscall*)(void*, uint32_t, float*, void*))VF(this, 0x4c))(
            this, 0, dir, tail);
        float offset = (float)((double)FUN_00ce6940(holder) + spread);
        ((void(__thiscall*)(void*, float, void*))VF(filter, 0x18))(filter, offset, effect);
        if (*(uint32_t*)((char*)filter + 0x714) == 0) {
            any = 1;
        }
    }

    unsigned int tag = FUN_0104bf10(holder);
    if (any != 0) {
        tag = FUN_0104bef0(holder);
    }

    void* em = FUN_0067ddd0();
    TObj* es = (TObj*)((void*(__thiscall*)(void*, uint32_t))VF(em, 0x54))(em, 0x3701a5c);
    void* ref = 0;
    char ok = ((char(__thiscall*)(void*, uint32_t, int, void**))VF(es, 8))(es, tag, 0, &ref);
    if (ok != 0) {
        Rec rec;
        rec.x = DAT_0169aa18;
        rec.y = DAT_0169aa1c;
        rec.flags0 = 0;
        rec.z = DAT_0169aa20;
        rec.cnt0 = 0;
        rec.one = DAT_01485720;
        ((TObj*)&rec.m[0])->F_0041cb40(&DAT_0169a9f4);
        float* pl = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
        rec.x = pl[0];
        rec.y = pl[1];
        rec.z = pl[2];
        rec.flags0 |= 4;
        rec.cnt0++;
        float* pl2 = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
        uint8_t tmp[0x10];
        void* fr = ((void*(__thiscall*)(void*, void*, float*))VF(loco, 0x5c))(loco, tmp, pl2);
        float mtmp[9];
        float* mret = (float*)FUN_0069b440(mtmp, fr);
        for (int i = 0; i < 9; i++) {
            rec.m[i] = mret[i];
        }
        rec.flags1 |= 2;
        rec.cnt1++;
        ((void(__thiscall*)(void*, void*))VF(ref, 0x18))(ref, &rec);
        ((void(__thiscall*)(void*, int))VF(ref, 8))(ref, 0);
    }
    if (ref != 0) {
        ((void(__thiscall*)(void*))VF(ref, 4))(ref);
    }

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        void* el = *it;
        if (el != 0) {
            ((void(__thiscall*)(void*))VF(el, 0xc0))(el);
        }
    }
    if (vec.mpBegin != 0 && ((uint32_t*)vec.mpBegin)[-1] != 0) {
        FUN_00f47380(vec.mpBegin);
    }
}