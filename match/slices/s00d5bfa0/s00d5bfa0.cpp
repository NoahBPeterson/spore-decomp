// Slice s00d5bfa0 -- SP::cCityVisualizer population / vignette maintenance cluster.
//
//   00d5bfa0  MajorUpdate(char)   population grow / shrink, species refresh, per-creature slot flags
//   00d5c470  remove + record      (thiscall, 2 args, returns char)
//   00d5c580  ProfEnterZone(citizen)
//   00d5c620  (thiscall, 2 args)   per-creature stimulus emission over the citizen list
//   00d5c720  OnTick()             seed the four vignette slots
//   00d5c8c0  (thiscall, 0 args)   slot-circle layout update around the city hall
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include <math.h>
#include "types.h"

typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct cCityVisualizer;

// ----------------------------------------------------------------------------------------------
// thiscall-through-vtable helpers (retail: mov edx,[o] ; mov ecx,o ; call dword ptr [edx+slot*4]).
// ----------------------------------------------------------------------------------------------
template <class R> static inline R VC0(void* o, int slot) {
    typedef R (__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1(void* o, int slot, A a) {
    typedef R (__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}
template <class R, class A, class B, class C, class D> static inline R VC4(void* o, int slot,
                                                                        A a, B b, C c, D d) {
    typedef R (__thiscall * Fn)(void*, A, B, C, D);
    return ((Fn)(*(void***)o)[slot])(o, a, b, c, d);
}

// ----------------------------------------------------------------------------------------------
// external callees (retail VA in the comment)
// ----------------------------------------------------------------------------------------------
struct SPEditorSpeciesManager {
    void* GetAvatarProfile();                              // 0x004df420
};
SPEditorSpeciesManager* __cdecl FUN_00401090();             // 0x00401090 (setting 9)

struct cSim {
    void* UpdateVignettes(int id);                         // 0x00ad11f0 (ret 4)
};
cSim* __cdecl FUN_00b3d480();                              // 0x00b3d480

struct cNounManager {
    int GetPlayerEmpireOrMinus1();                         // 0x00b1f9d0
};
cNounManager* __cdecl FUN_00b3d300();                      // 0x00b3d300

// random number source (singleton at 0x01601760)
struct RandomLC {
    u32    RandomUint32Uniform(u32 n);                     // 0x00a68fb0 (ret 4)
    double RandomDoubleUniform();                          // 0x009360d0
};
extern RandomLC g_Random;                                  // 0x01601760

// the "sim" singleton behind FUN_00b3d4e0()
struct SimB {
    int  FUN_00bc3db0(void* id);                           // 0x00bc3db0 (ret 4)
    void FUN_00bc52a0(void* id, void* arg);                // 0x00bc52a0 (ret 8)
    char FUN_00bc4900(void* id, void* a, void* b);         // 0x00bc4900 (ret 0xc)
};
SimB* __cdecl FUN_00b3d4e0();                              // 0x00b3d4e0

// intrinsic-refcounted objects (vtable slot 0 = AddRef, slot 1 = Release)
struct RefCount {
    virtual void AddRef();
    virtual void Release();
};

// a pointer-to-array with a length word in front of it (operator delete[] idiom)
struct ArrayHeader { u32 mPad; u32 mAlloc; };

// ----------------------------------------------------------------------------------------------
// data types
// ----------------------------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

// a 4-byte-aligned object with only a vtable we poke at.
struct SubObj { void* mVtbl; };

// retail cActionCircle is 0x64 bytes.
struct cActionCircle {
    float mX, mY, mZ;                                      // +0x00 (direction / centre)
    float mPad0c[2];                                       // +0x0c
    float mA, mB, mC;                                      // +0x14
    u8    mPad20[0x64 - 0x20];
    void SetAtCenter(const void* center, float radius, const void* facing, float altitude); // 0xaf9cf0 (ret 0x10)
    void FUN_00afef10(int n, float f);                     // 0xafef10 (ret 8)
    void FUN_00afd6d0(float a, float b, int n);            // 0xafd6d0 (ret 0xc)
};

// 0x14-byte intrusive pointer vector used by the vignette-slot arrays.
struct SPVec {
    void** mBegin;                                         // +0x00
    void** mEnd;                                           // +0x04
    void** mCap;                                           // +0x08
    u32    mTag;                                           // +0x0c
    u32    mAlloc;                                         // +0x10
    void DoInsertPtr(void** pos, void* const& val);        // 0xaea5d0 (ret 8)
    void erase(void* first, void* last);                   // 0xe25bd0 (ret 8)
    void FUN_00b93c60(int count, void* alloc);             // 0x00b93c60 (ret 8)
};

// 0x1c-byte element of the per-culture actor list at +0xbbc.
struct Elem28 {
    void* mId;                                             // +0x00
    u8    mFlag;                                           // +0x04
    u8    mPad05[3];                                       // +0x05
    SPVec mVec;                                            // +0x08
};

// creature / vignette-instance view (retail offsets).
struct Entity {
    u8    pad_00[0x20];
    float m20, m24, m28;                                   // +0x20
    u8    pad_2c[0x34 - 0x2c];
    SubObj mSub34;                                         // +0x34
    u8    pad_38[0xc0 - 0x38];
    SubObj mSubC0;                                         // +0xc0
    u8    pad_c4[0xb4c - 0xc4];
    void* mB4c;                                            // +0xb4c
    u8    pad_b50[0xb54 - 0xb50];
    void* mB54;                                            // +0xb54
    u8    pad_b58[0xb62 - 0xb58];
    u8    mB62;                                            // +0xb62
    u8    pad_b63[0xff0 - 0xb63];
    void* mFF0;                                            // +0xff0
    // methods
    void* GetSpeciesProfile();                             // 0xc0bbd0
    void  FUN_00c222f0(void* prof);                        // 0xc222f0 (ret 4)
    void  FUN_00c0d950(int v);                             // 0xc0d950 (ret 4)
    void  SetCurrentToolEffect(int a, int b);              // 0xc24f40 (ret 8)
};

struct StimSet {
    void FUN_00bc97f0(int type, int a, float prio, int b); // 0xbc97f0 (ret 0x10)
};

struct cCity {
    void* FUN_00bd9e40();                                  // 0x00bd9e40 (avatar creature)
    void* GetCivilization();                               // 0x00bd9bf0
    void* GetCityHall();                                   // 0x00bd9b40
    void* FUN_00bd99e0();                                  // 0x00bd99e0
    int   FUN_00bd8160();                                  // 0x00bd8160
    void* GetMembers();                                    // 0x00c8e810
    void  FUN_00bd7f70(void* out1, void* out2);            // 0x00bd7f70 (ret 8)
    void  FUN_00bdf750(void* vec);                         // 0x00bdf750 (ret 4)
    u8    pad_00[0x120];
    SubObj mSub120;                                        // +0x120
    u8    pad_124[0x2a0 - 0x124];
    u8    m2a0;                                            // +0x2a0
};

// the "(first, count)" stack entry that FUN_00bdf750 fills.
struct SlotEntry { void* mPtr; int mCount; };

// stack storage backing the temporary slot vector built by cCity::FUN_00bdf750.
struct SlotVecBuf { SlotEntry mEntries[128]; };

// bit-flag holder reached through Entity::mB54 (+0x180 -> +0x4).
struct FlagOwner  { u32 mPad; u32 mFlags; };
struct Holder180  { u8 mPad[0x180]; FlagOwner* mOwner; };

// ----------------------------------------------------------------------------------------------
// cCityVisualizer
// ----------------------------------------------------------------------------------------------
struct cCityVisualizer {
    u8    pad_00[0x0c];
    cActionCircle mCircle0c;                               // +0x0c  (ends +0x70)
    cActionCircle mCircle70;                               // +0x70  (ends +0xd4)
    cActionCircle mCircleD4;                               // +0xd4  (ends +0x138)
    u8    pad_138[0x234 - 0x138];
    cActionCircle mCircle234;                              // +0x234 (ends +0x298)
    cActionCircle mCircle298;                              // +0x298 (ends +0x2fc)
    cActionCircle mCircle2fc;                              // +0x2fc
    u8    pad_360[0xa64 - 0x360];
    void** mCitizenBegin;                                  // +0xa64
    void** mCitizenEnd;                                    // +0xa68
    void** mCitizenCap;                                    // +0xa6c
    u32    mAllocA70;                                      // +0xa70
    u32    mAllocA74;                                      // +0xa74
    SPVec  mVignetteVec[4];                                // +0xa78 (stride 0x14)
    u8    pad_acc[0xaf0 - 0xac8];
    cCity* mCity;                                          // +0xaf0
    u8    mFlagAf4;                                        // +0xaf4
    u8    mFlagAf5;                                        // +0xaf5
    u8    pad_af6[0xbbc - 0xaf6];
    Elem28* mElemBegin;                                    // +0xbbc
    Elem28* mElemEnd;                                      // +0xbc0
    u8    pad_bc4[0xbd0 - 0xbc4];
    int   mCountBd0;                                       // +0xbd0
    // methods
    char  FUN_00d5c470(void* a, void* b);
    void  FUN_00d5c580(void* citizen);
    void  FUN_00d5c620(void* vec, int count);
    void  FUN_00d5c720();
    void  FUN_00d5c8c0();
    void  FUN_00d5bfa0(char enable);
    // external member callees
    int   FUN_00d57a00();                                  // 0x00d57a00 ComputeVisualizedPopulation
    void  FUN_00d57940(void* p);                           // 0x00d57940 (ret 4)
    void  FUN_00d58c50(void* p);                           // 0x00d58c50 (ret 4)
    void  FUN_00d5b9f0();                                  // 0x00d5b9f0 (ret 0)
};

// ----------------------------------------------------------------------------------------------
// external helpers
// ----------------------------------------------------------------------------------------------
void __cdecl FUN_00d588a0(void* profile, float* a, float* b, float* c);                 // 0x00d588a0
void __cdecl FUN_00d57800(void* effect, cCityVisualizer* viz, void* profile, int empire,
                          int idx, void* pos, float a, float b, float c);                // 0x00d57800
void __cdecl FUN_00d5aae0(void* container, void** out, void* val);                      // 0x00d5aae0
void __cdecl FUN_00d5bb50(void* a, void* b, float f0, float f1, float f2);               // 0x00d5bb50
void __cdecl FUN_00829110(void* out, void* first, void* last, void* dest, void* param);  // 0x00829110
void __cdecl FUN_00f47380(void* p);                                                      // 0x00f47380 (operator delete[])

struct VecBuilder {                                          // 0x00b93c60 (thiscall, 2 args, ret 8)
    void* mBegin;                                          // +0x00
    void* mEnd;                                            // +0x04
    void* mCap;                                            // +0x08
    u32   mTag;                                            // +0x0c
    u32   mAlloc;                                          // +0x10
    VecBuilder(int n, void* alloc);
};

// shared float constants
extern float g_c0x13eb8a0;                                 // 0.25
extern float g_c0x13eb8b0;                                 // sign-bit mask
extern float g_c0x13ec4b8;                                 // sqrt epsilon
extern float g_c0x13ec480;                                 // 0.2
extern float g_c0x13f7674;
extern float g_c0x1471064;
extern float g_c0x1470f1c;
extern float g_c0x1485548;                                 // 1.5
extern float g_c0x1485720;                                 // 1.0

extern void* g_p0x1583e08;                                 // 0x01583e08 message id

// ==============================================================================================
// @ 0x00d5c470
char cCityVisualizer::FUN_00d5c470(void* a, void* b) {
    char flag = mCity->m2a0;
    int n = (int)(mElemEnd - mElemBegin);
    if (n <= 0) return 0;
    int off = 0;
    for (int i = 0; i < n; ++i, off += 0x1c) {
        Elem28* e = (Elem28*)((char*)mElemBegin + off);
        if (FUN_00b3d4e0()->FUN_00bc3db0(e->mId) != 0 &&
            (flag == 0 || e->mFlag != 0)) {
            if (FUN_00b3d4e0()->FUN_00bc4900(e->mId, a, b) != 0) {
                --mCountBd0;
                RefCount* r = (RefCount*)a;
                if (r) r->AddRef();
                if (e->mVec.mEnd < e->mVec.mCap) {
                    void** slot = e->mVec.mEnd;
                    e->mVec.mEnd = slot + 1;
                    if (slot) {
                        *slot = r;
                        if (r) r->AddRef();
                    }
                } else {
                    e->mVec.DoInsertPtr(e->mVec.mEnd, r);
                }
                if (r) r->Release();
                return 1;
            }
        }
    }
    return 0;
}

// ==============================================================================================
// @ 0x00d5c580
void cCityVisualizer::FUN_00d5c580(void* citizen) {
    ((Entity*)citizen)->SetCurrentToolEffect(0, -1);
    int n = (int)(mElemEnd - mElemBegin);
    if (n <= 0) return;
    int off = 0;
    do {
        Elem28* e = (Elem28*)((char*)mElemBegin + off);
        void** it = e->mVec.mBegin;
        void** end = e->mVec.mEnd;
        while (it != end) {
            if (*it == citizen) break;
            ++it;
        }
        if (it != end) {
            FUN_00b3d4e0()->FUN_00bc52a0(e->mId, citizen);
            FUN_00d5aae0(&e->mVec, &citizen, citizen);
        }
        off += 0x1c;
    } while (--n != 0);
}

// ==============================================================================================
// @ 0x00d5c620
void cCityVisualizer::FUN_00d5c620(void* vec, int count) {
    VecBuilder tmp((int)(mCitizenEnd - mCitizenBegin), &mAllocA70);
    void* out;
    FUN_00829110(&out, mCitizenBegin, mCitizenEnd, tmp.mBegin, vec);
    FUN_00d5bb50(tmp.mBegin, out, ((float*)vec)[0], ((float*)vec)[1], ((float*)vec)[2]);
    int cnt = (int)((char*)out - (char*)tmp.mBegin) >> 2;
    if (cnt > 0) {
        int i = 0;
        do {
            if (count <= 0) break;
            Entity* cr = ((Entity**)tmp.mBegin)[i];
            StimSet* ss = (StimSet*)((char*)cr->mB4c + 8);
            ss->FUN_00bc97f0(0x2000, 0, 0.25f, 0);
            ++i;
            --count;
        } while (i < cnt);
    }
    for (void** it = (void**)tmp.mBegin; it < (void**)out; ++it) {
        if (*it) ((RefCount*)*it)->Release();
    }
    if (tmp.mBegin && ((ArrayHeader*)tmp.mBegin)[-1].mAlloc != 0) FUN_00f47380(tmp.mBegin);
}

// ==============================================================================================
// @ 0x00d5c720
void cCityVisualizer::FUN_00d5c720() {
    if (mFlagAf5 != 0) return;
    cSim* sim  = FUN_00b3d480();
    void* prof = mCity->FUN_00bd9e40();
    int   emp  = VC0<int>(mCity->GetCivilization(), 19);
    if (prof == 0) prof = FUN_00401090()->GetAvatarProfile();
    float f1 = g_c0x1485720;                               // 1.0
    float f2 = g_c0x13ec480;                               // 0.2
    float f3 = g_c0x1485548;                               // 1.5
    FUN_00d588a0(prof, &f1, &f2, &f3);
    float* pos = VC0<float*>(&mCity->mSub120, 11);
    float px = pos[0], py = pos[1], pz = pos[2];
    for (int i = 0; i < 4; ++i) {
        void* r = sim->UpdateVignettes(0x18eb4b7);
        if (r == 0) continue;
        void* vin = VC1<void*, int>(r, 3, 0x4f176642);
        if (vin == 0) continue;
        FUN_00d57800(vin, this, prof, emp, i, &px, f1, f2, f3);
        RefCount* rc = (RefCount*)vin;
        if (rc) rc->AddRef();
        SPVec* v = &mVignetteVec[i];
        if (v->mEnd < v->mCap) {
            void** slot = v->mEnd;
            v->mEnd = slot + 1;
            if (slot) {
                *slot = rc;
                if (rc) rc->AddRef();
            }
        } else {
            v->DoInsertPtr(v->mEnd, rc);
        }
        if (rc) rc->Release();
    }
    mFlagAf5 = 1;
}

// ==============================================================================================
// @ 0x00d5c8c0
void cCityVisualizer::FUN_00d5c8c0() {
    Vec3 hall; float r;
    mCity->FUN_00bd7f70(&hall, &r);
    void* ch = mCity->GetCityHall();
    float* hp = VC0<float*>(ch, 35);                       // vtable slot 0x8c
    float dx = hp[0] - hall.x;
    float dy = hp[1] - hall.y;
    float dz = hp[2] - hall.z;
    float inv = 1.0f / (float)sqrt((double)(dz * dz + (dx * dx + dy * dy) + g_c0x13ec4b8));

    float d1 = dx * inv, d2 = dy * inv, d3 = dz * inv;
    mCircle0c.SetAtCenter(&hall, r, &d1, 0.0f);
    mCircle0c.FUN_00afef10(3, 2.0f);
    mCircle0c.SetAtCenter(&hall, r, &mCircle0c.mX, 0.0f);
    mCircle0c.FUN_00afd6d0(1.0f, 1.0f, 12);

    float n1 = -mCircle0c.mX;
    float n2 = -mCircle0c.mY;
    float n3 = -mCircle0c.mZ;
    mCircle0c.SetAtCenter(&hall, r, &n1, 0.0f);
    mCircle0c.FUN_00afef10(4, 1.0f);

    float ax = mCircle0c.mA, ay = mCircle0c.mB, az = mCircle0c.mC;
    float ainv = 1.0f / (float)sqrt((double)(ax * ax + ay * ay + az * az) + g_c0x13ec4b8);
    float ux = ax * ainv, uy = ay * ainv, uz = az * ainv;

    float cx = mCircle0c.mB * uz - mCircle0c.mC * uy;
    float cy = mCircle0c.mC * ux - mCircle0c.mX * uz;
    float cz = mCircle0c.mX * uy - mCircle0c.mB * ux;

    float e1 = -cx, e2 = -cy, e3 = -cz;
    float half = r * 0.5f;
    float s1 = cx * half + ax;
    float s2 = cy * half + ay;
    float s3 = cz * half + az;
    float p1 = s1, p2 = s2, p3 = s3;
    mCircle2fc.SetAtCenter(&p1, r * 2.0f, &e1, 0.0f);
    mCircle2fc.FUN_00afef10(4, 1.0f);

    float q1 = ax - cx * half;
    float q2 = ay - cy * half;
    float q3 = az - cz * half;
    mCircle234.SetAtCenter(&q1, r * 2.0f, &cx, 0.0f);
    mCircle234.FUN_00afef10(4, 1.0f);

    void* ch2 = mCity->GetCityHall();
    if (ch2 != 0) {
        Vec3 q;
        VC1<void, void*>(&((SubObj*)((char*)ch2 + 0x34))->mVtbl, 23, &q);      // slot 0x5c
        Vec3 n;
        n.x = -q.x;
        n.y = -q.y;
        n.z = -q.z;
        void* center = VC1<void*, void*>(ch2, 35, &n);                          // slot 0x8c
        mCircleD4.SetAtCenter(center, g_c0x13f7674, &n, 0.0f);
        mCircleD4.FUN_00afd6d0(g_c0x1470f1c, g_c0x1471064, 20);
    }
    FUN_00d5b9f0();
}

// ==============================================================================================
// @ 0x00d5bfa0
void cCityVisualizer::FUN_00d5bfa0(char enable) {
    if (mCity == 0) return;
    int n = (int)(mCitizenEnd - mCitizenBegin);
    int pop = FUN_00d57a00();
    int mag = pop - n;
    bool grow = n < pop;
    if (mag < 0) mag = -mag;
    void* prof = mCity->FUN_00bd9e40();
    if (prof == 0) prof = FUN_00401090()->GetAvatarProfile();
    if (mag != 0) {
        cSim* sim = FUN_00b3d480();
        if (grow) {
            float f1 = g_c0x1485720;
            float f2 = g_c0x13ec480;
            float f3 = g_c0x1485548;
            FUN_00d588a0(prof, &f1, &f2, &f3);
            Vec3 range; Vec3 pos;
            mCity->FUN_00bd7f70(&range, &pos);
            void** members = (void**)mCity->GetMembers();
            for (int i = 0; i < mag; ++i) {
                void* r = sim->UpdateVignettes(0x18eb4b7);
                if (r == 0) continue;
                void* vin = VC1<void*, int>(r, 3, 0x4f176642);
                if (vin == 0) continue;
                float sx, sy, sz;
                if (members[0] == members[1]) {
                    sx = pos.x; sy = pos.y; sz = pos.z;
                } else {
                    u32 k = g_Random.RandomUint32Uniform((u32)(((char*)members[1] - (char*)members[0]) >> 2));
                    float* v = VC0<float*>(&((SubObj*)((char*)members[k] + 0x34))->mVtbl, 11);
                    sx = v[0]; sy = v[1]; sz = v[2];
                }
                Vec3 vpos;
                vpos.x = sx; vpos.y = sy; vpos.z = sz;
                RefCount* rc = (RefCount*)vin;
                if (rc) rc->AddRef();
                if (mCitizenEnd < mCitizenCap) {
                    void** slot = mCitizenEnd;
                    mCitizenEnd = slot + 1;
                    if (slot) {
                        *slot = vin;
                        if (rc) rc->AddRef();
                    }
                } else {
                    ((SPVec*)&mCitizenBegin)->DoInsertPtr(mCitizenEnd, vin);
                }
                if (rc) rc->Release();
                VC4<void, void*, int, int, void*>(vin, 58, mCity, 0, 1, &vpos);   // slot 0xe8
                FUN_00d58c50(vin);
                double rnd = g_Random.RandomDoubleUniform();
                float value = (float)(((rnd * range.y + range.z) - range.y * 0.5f) * pos.x);
                VC1<void, float>((char*)vin + 0xc0, 16, value);                    // slot 0x40
                int emp3 = VC0<int>(mCity->GetCivilization(), 19);
                VC1<void, int>(vin, 18, emp3);                                     // slot 0x48
                ((Entity*)vin)->mFF0 = (void*)emp3;
                if (!VC0<char>((char*)vin + 0xc0, 22)) {                           // slot 0x58
                    Holder180* h = (Holder180*)((Entity*)vin)->mB54;
                    h->mOwner->mFlags |= 0x800;
                }
            }
        } else if (pop >= 0 && pop < (int)(mCitizenEnd - mCitizenBegin)) {
            SPVec* v = (SPVec*)&mCitizenBegin;
            void** it = mCitizenBegin + pop;
            for (; it != mCitizenEnd; ++it) FUN_00d57940(*it);
            v->erase(mCitizenBegin + pop, mCitizenEnd);
        }
    }
    int cnt = (int)(mCitizenEnd - mCitizenBegin);
    for (int i = 0; i < cnt; ++i) {
        Entity* cr = (Entity*)mCitizenBegin[i];
        if (cr->GetSpeciesProfile() != prof) cr->FUN_00c222f0(prof);
    }
    if (enable != 0) {
        SlotVecBuf buf;
        SPVec vec;
        vec.mBegin = (void**)buf.mEntries;
        vec.mCap   = (void**)buf.mEntries;
        mCity->FUN_00bdf750(&vec);
        int cnt2 = (int)(mCitizenEnd - mCitizenBegin);
        void* curPtr = 0;
        int curCnt = 0;
        void* emp2 = VC0<void*>(mCity->GetCivilization(), 19);
        cNounManager* nm = FUN_00b3d300();
        int player = nm->GetPlayerEmpireOrMinus1();
        int mine = (emp2 == (void*)player) ? 1 : 0;
        for (int i = 0; i < cnt2; ++i) {
            if (curCnt == 0) {
                SlotEntry* end = (SlotEntry*)vec.mEnd;
                SlotEntry* bot = (SlotEntry*)vec.mBegin;
                while (end != bot) {
                    SlotEntry* e = end - 1;
                    void* p = e->mPtr;
                    int   c = e->mCount;
                    end = e;
                    vec.mEnd = (void**)end;
                    curPtr = p;
                    curCnt = c;
                    if (c != 0) break;
                }
                if (end == bot) {
                    curPtr = emp2;
                    curCnt = 999;
                }
            }
            Entity* cr = (Entity*)mCitizenBegin[i];
            VC1<void, void*>(cr, 18, emp2);                                   // slot 0x48
            cr->mFF0 = curPtr;
            if (mine) {
                VC1<void, void*>(cr, 57, &g_p0x1583e08);                      // slot 0xe4
                cr->FUN_00c0d950(0);
            } else {
                void* m = mCity->FUN_00bd99e0();
                VC1<void, void*>(cr, 57, m);
                cr->FUN_00c0d950(1);
            }
            --curCnt;
        }
        if (vec.mBegin && ((ArrayHeader*)vec.mBegin)[-1].mAlloc != 0) FUN_00f47380(vec.mBegin);
    }
    int k = mCity->FUN_00bd8160();
    int cnt3 = (int)(mCitizenEnd - mCitizenBegin);
    for (int i = 0; i < cnt3; ++i) {
        ((Entity*)mCitizenBegin[i])->mB62 = (i < k);
    }
}