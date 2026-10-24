// Slice s00c68280: Simulator object helpers (ornament / nano-drone / ground-locomotion).
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast (SSE ucomiss code shape).
#include "types.h"
#include <stdlib.h>
#include <math.h>

// Vtable-slot read: slot value (a function pointer) at vptr+off.
#define VTSLOT(o, off) (*(void**)((char*)(*(void**)o) + (off)))

typedef void   (__thiscall *TFv_v)(void*);
typedef void   (__thiscall *TFv_i)(void*, int);
typedef void   (__thiscall *TFv_p)(void*, void*);
typedef char   (__thiscall *TFc_v)(void*);
typedef int    (__thiscall *TFi_v)(void*);
typedef int    (__thiscall *TFi_i)(void*, int);
typedef float* (__thiscall *TFf_v)(void*);
typedef float* (__thiscall *TFf_i)(void*, int);
typedef void*  (__thiscall *TFp_v)(void*);
typedef void*  (__thiscall *TFp_i)(void*, int);
typedef int    (__thiscall *TFi_ip)(void*, int, void*);
typedef char   (__thiscall *TFc_iii)(void*, int, int, void*);
typedef void   (__thiscall *TFv_ipii)(void*, int, void*, int);

// ---------------------------------------------------------------------------
// Small value / container types
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };

// A vector whose elements are 4-byte noun pointers (stride 4).
struct Vec {
    int** begin;
    int** end;
    int** cap;
    void erase(int** a, int** b);                 // 0x00e25bd0
    void F_00b05b40(int** pos, int** val);        // 0x00b05b40
    void DoInsertPtr(int** pos, int** val);       // 0x00aea5d0
};

// A vector of Vector3 (stride 0xc).
struct Vector3Vec {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    void erase(Vector3* a, Vector3* b);           // 0x0050f740
    void DoInsertValue(Vector3* pos, Vector3* val); // 0x004b5ad0
    void push_back(Vector3* v) {
        Vector3* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e != 0) { e->x = v->x; e->y = v->y; e->z = v->z; }
        } else {
            DoInsertValue(e, v);
        }
    }
};

// A vector of 16-byte run-info records (stride 0x10).
struct Elem16 { float x, y, z, w; };

struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    void Resize(unsigned n);                      // 0x00c00e90
    void Grow(Elem16* pos, Elem16* val);          // 0x00c67440
};
void* __cdecl FUN_00705250(void* first, void* last, void* dst);   // 0x00705250

// ---------------------------------------------------------------------------
// Embedded cSpatialObject vtable helpers (subobject at +0x34).
// ---------------------------------------------------------------------------
struct cSpatial {
    void** vt;
    float* GetPosition() {
        typedef float* (__thiscall* Fn)(cSpatial*);
        return ((Fn)vt[0x2c / 4])(this);
    }
    float* GetPositionI(int i) {
        typedef float* (__thiscall* Fn)(cSpatial*, int);
        return ((Fn)vt[0x2c / 4])(this, i);
    }
    void SetPosition(void* p) {
        ((void(__thiscall*)(cSpatial*, void*))vt[0x38 / 4])(this, p);
    }
    void F_00c421b0(void* p);                     // 0x00c421b0
    void Shutdown();                              // 0x00c43f90
};

// Generic Simulator object whose +0x34 is a cSpatialObject (used for the nouns
// created by FUN_00c68c00 and for the view objects passed to E980).
struct CObject {
    char     pad0[0x34];
    cSpatial mSpatial;
};

// A small owner object: byte flag at +0, vector of noun pointers at +4.
struct COrnList {
    char  mFlag0;
    char  pad001[3];
    Vec   mVec;                                   // +0x04
    void Collect(Vector3Vec* dst, char* out);     // 0x00c688a0
};

// The model head: a 32-bit flag word at +4.
struct CModelHead { char pad[4]; unsigned mFlags; };

// ---------------------------------------------------------------------------
// Class scaffolding for the constructors / destructors.  Members and bases are
// laid out so the compiler emits the original base-ctor / base-dtor sequence.
// ---------------------------------------------------------------------------
struct cGameData {
    void* mVt0;                                   // +0x00
    void* mVt4;                                   // +0x04
    char  pad08[0x34 - 0x08];
    cGameData();                                  // 0x00b18660
    ~cGameData();                                 // 0x00b184c0
};

// Occupies +0x34 .. +0x508 (0x4d4 bytes).
struct cLocoBase {
    void* mVt;                                    // +0x00 (= obj +0x34)
    char  pad04[0xd4 - 0x04];
    void* mVtD4;                                  // +0xd4 (= obj +0x108)
    char  padD8[0x4d4 - 0xd8];
    cLocoBase();                                  // 0x00c43860
    ~cLocoBase();                                 // 0x00c432e0
};

// Occupies 0xc8 bytes (obj +0x508 or +0x108).
struct cCombatant {
    void* mVt;
    char  pad04[0xc8 - 0x04];
    cCombatant();                                 // 0x00bfd4e0
    ~cCombatant();                                // 0x00bfcd00
};

struct cSub5d0 {
    void* mVt;                                    // +0x00 (= obj +0x5d0)
    cSub5d0();                                    // 0x00abfe50
    ~cSub5d0();                                   // 0x00abfec0
};

// Occupies +0x34 .. +0x108 (0xd4 bytes).
struct cSpatialObjectBase {
    void* mVt;                                    // +0x00 (= obj +0x34)
    char  pad04[0xd4 - 0x04];
    cSpatialObjectBase();                         // 0x00c89630
    ~cSpatialObjectBase();                        // 0x00c8a420
};

struct cMovableDestructibleOrnament : cGameData {
    cLocoBase  mLoco;                             // +0x34
    cCombatant mCombatant;                        // +0x508
    cSub5d0    mSub;                              // +0x5d0
    cMovableDestructibleOrnament();               // 0x00c68e30
    ~cMovableDestructibleOrnament();              // 0x00c68ed0
};

struct cNanoDrone : cGameData {
    cSpatialObjectBase mSpatial;                  // +0x34
    cCombatant         mCombatant;                // +0x108
    void* mp1d0;                                  // +0x1d0
    int   m1d4;                                   // +0x1d4
    cNanoDrone();                                 // 0x00c69150
    ~cNanoDrone();                                // 0x00c69290
};

// A cAgentOrderManager (only its destructor is needed here).
struct cAgentOrderManager { void F_00bcae90(); }; // 0x00bcae90

// The sub-objects of COrn reached through thiscall method calls.
struct COrnCombatantSlot { void* mVt; void F_00bfc720(); };  // 0x00bfc720
struct COrnTailSlot      { void* mVt; void F_00abf710(); };  // 0x00abf710

// ---------------------------------------------------------------------------
// COrn: a locomotive-derived Simulator object (the "ornament").  Unknown spans
// are padded; the fields actually touched by this slice are named.
// ---------------------------------------------------------------------------
struct COrn {
    char   mByte0;                     // +0x00
    char   pad001[3];
    Vec    mVec4;                      // +0x04  noun-ref vector
    char   pad010[0x2c - 0x10];
    int*   mp2c;                       // +0x2c (interface, released in Shutdown)
    char   pad030[0x34 - 0x30];
    cSpatial mSpatial;                 // +0x34
    char   pad038[0xd0 - 0x38];
    int*   mpModel;                    // +0xd0
    char   pad0d4[0x118 - 0xd4];
    float  mPosX, mPosY, mPosZ;        // +0x118,+0x11c,+0x120
    char   mFlag124;                   // +0x124
    char   pad125[3];
    int    mKey128;                    // +0x128
    float  mF12c;                      // +0x12c
    int    mCount130;                  // +0x130 (segment count)
    int*   mVec134;                    // +0x134 (view / effect object)
    char   pad138[0x508 - 0x138];
    COrnCombatantSlot mCombatant;      // +0x508
    char   pad50c[0x5d0 - 0x50c];
    COrnTailSlot mTail;                // +0x5d0

    __declspec(noinline) void Update();  // 0xc68280
    void H3f90();                      // 0xc63f90
    void H4460(int x);                 // 0xc64460
    void E850(int* noun);              // 0xc68850
    void E930();                       // 0xc68930
    void E980(void* view);             // 0xc68980
    void Eaa0();                       // 0xc68aa0
    void Eae0(float* p);               // 0xc68ae0
    void Eb40(int key);                // 0xc68b40
    void Ebd0(float v);                // 0xc68bd0
    char Ed20(int* noun);              // 0xc68d20
    void Ed70(Vector3* pos, Vector3Vec* v); // 0xc68d70
    void F030();                       // 0xc69030
    void F090();                       // 0xc69090
    int  Ef30(int id);                 // 0xc68f30
    int  F1e0(int id);                 // 0xc691e0
    cSpatial* Spatial() { return (cSpatial*)((char*)this + 0x34); }
};

// The local fixed_vector<Vector3,128> built by Update().
struct FixedVec3 {
    Vector3* mpBegin;                  // +0x00
    Vector3* mpEnd;                    // +0x04
    Vector3* mpCapacity;               // +0x08
    Vector3* mpHeapBase;               // +0x0c (block to free if moved off-stack)
    Vector3* mpInline;                 // +0x10
    int      mPad14;                   // +0x14
    Vector3  mBuf[128];                // +0x18
    void F_00c67560(Vector3* pos, int n, Vector3* last); // 0x00c67560
    void DoAssignValues(Vector3* pos, Vector3* val);     // 0x00ac4720
    void push_back(Vector3* v) {
        Vector3* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e != 0) { e->x = v->x; e->y = v->y; e->z = v->z; }
        } else {
            DoAssignValues(e, v);
        }
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};

// ---------------------------------------------------------------------------
// External helpers
// ---------------------------------------------------------------------------
void __cdecl ClearVector(Vec* v);                 // 0xc687e0
char __cdecl FUN_00c649b0(Vec* dst, Vector3Vec* v);  // 0xc649b0
void __cdecl FUN_00ebb720(void* p, unsigned int flags);
void __cdecl FUN_00c63f90(COrn* p);
void __cdecl FUN_00c64460(COrn* p);
int* __cdecl FUN_00b3d300();                      // SP::NounManager
// Interface-query helpers are thiscall-shaped: self in ecx, id on the stack, callee pops.
struct IQuery {
    int QI(int id);   // 0xb18460
    int QJ(int id);   // 0xc884f0
    int QK(int id);   // 0xc41d00
    int QL(int id);   // 0xbfc380
    int QM(int id);   // 0xabf740
};
void* __cdecl FUN_0067ddd0();                     // SP::EffectsManager
void* __cdecl FUN_00b3d260();                     // SP::BehaviorManager
struct cGameNounManager {
    int* CreateNoun(int tag);                     // 0x00b20c60
    void RemoveNoun(int* noun);                   // 0x00b225d0
};
void* __cdecl FUN_00f473a0(unsigned int size, const char* name, int a, int b, int c, int d); // 0xf473a0
void  __cdecl FUN_00f47380(void* p);              // 0xf47380

// static-local guard data for 0xc69110
extern int g_guard1693e00;       // 0x1693e00
extern int g_data1693dec[3];     // 0x1693dec
extern char g_byte1693d70;       // 0x1693d70
extern "C" void __cdecl FUN_013c4150();

// ===========================================================================
// @ 0x00c68280  Rebuild the position/segment list from the current spatial pos.
// ===========================================================================
void COrn::Update()
{
    if (mVec134 == 0)
        return;
    unsigned cnt = (unsigned)mCount130;
    if (cnt >= 0x80)
        cnt = 0x80;
    if (cnt < 4)
        cnt = 3;
    float scale = mF12c;
    float* p = Spatial()->GetPosition();
    float dx = p[0] - mPosX;
    float dy = p[1] - mPosY;
    float dz = p[2] - mPosZ;
    float dist = sqrtf(dz * dz + dy * dy + dx * dx);
    if (0.0f < scale) {
        if (scale * 3.0f <= dist) {
            if (dist <= scale * 128.0f) {
                double t = (double)dist / (double)scale;
                cnt = (unsigned)(float)(__int64)(t + 0.5) + 1;
            } else {
                scale = dist * 0.0078125f;
                cnt = 0x80;
            }
        } else {
            scale = dist * 0.33333334f;
            cnt = 3;
        }
    } else {
        scale = dist / (float)cnt;
    }
    float* q = Spatial()->GetPosition();
    float ddx = q[0] - mPosX;
    float ddy = q[1] - mPosY;
    float ddz = q[2] - mPosZ;
    float inv = 1.0f / sqrtf(ddy * ddy + (ddz * ddz + ddx * ddx) + 1e-8f);
    float vx = (ddx * inv) * scale;
    float vy = (ddy * inv) * scale;
    float vz = (ddz * inv) * scale;
    FixedVec3 seg;
    seg.mpHeapBase = 0;
    seg.mpEnd = seg.mpBegin = seg.mBuf;
    seg.mpInline = seg.mBuf;
    seg.mpCapacity = seg.mBuf + 128;
    for (unsigned i = 0; i < cnt; ++i) {
        float fi = (float)(int)i;
        Vector3 pt;
        pt.x = mPosX + vx * fi;
        pt.y = mPosY + vy * fi;
        pt.z = mPosZ + vz * fi;
        seg.push_back(&pt);
    }
    Vector3* last = seg.mpEnd - 1;
    float* r = Spatial()->GetPosition();
    if (last->x != r[0] || last->y != r[1] || last->z != r[2]) {
        float* s = Spatial()->GetPosition();
        Vector3 tail;
        tail.x = s[0];
        tail.y = s[1];
        tail.z = s[2];
        seg.push_back(&tail);
    }
    if (g_byte1693d70 == 0) {
        Vector3 box;
        int ok = ((TFi_ip)VTSLOT(mVec134, 0x50))(mVec134, 0xd, &box);
        if (ok != 0 && box.x != (float)seg.size()) {
            char c = ((TFc_v)VTSLOT(mVec134, 0x10))(mVec134);
            if (c != 0)
                ((TFv_i)VTSLOT(mVec134, 0x0c))(mVec134, 1);
            void* eff = FUN_0067ddd0();
            int* old = mVec134;
            if (old != 0) {
                mVec134 = 0;
                ((TFv_v)VTSLOT(old, 4))(old);
            }
            ((TFc_iii)VTSLOT(eff, 0x2c))(eff, mKey128, 0, &mVec134);
            if (c != 0)
                ((TFv_i)VTSLOT(mVec134, 8))(mVec134, 1);
        }
    } else {
        seg.F_00c67560(seg.mpEnd, 0x80 - seg.size(), seg.mpEnd - 1);
    }
    ((TFv_ipii)VTSLOT(mVec134, 0x40))(mVec134, 0xd, seg.mpBegin, seg.size());
    if (seg.mpHeapBase != 0 && seg.mpHeapBase != seg.mpEnd)
        FUN_00f47380(seg.mpHeapBase);
}

// ===========================================================================
// A run-info vector owner (its +0x30 holds the 16-byte-element vector).
// ===========================================================================
struct CTexRun {
    char  pad00[0x30];
    Vec16 mVec;                       // +0x30
    void Build(unsigned count, float* pts, float* angles); // 0x00c686d0
};

// ===========================================================================
// @ 0x00c686d0  Build a run-info vector from a point/angle stream.
// ===========================================================================
void CTexRun::Build(unsigned count, float* pts, float* angles)
{
    Elem16* last = mVec.mpEnd;
    Elem16* first = mVec.mpBegin;
    FUN_00705250(last, last, first);
    mVec.mpEnd = (Elem16*)((char*)last + (int)(last - first) * -16);
    mVec.Resize(count);
    for (unsigned i = 0; i < count; ++i) {
        Elem16* e = mVec.mpEnd;
        if (e < mVec.mpCapacity) {
            mVec.mpEnd = e + 1;
        } else {
            Elem16 tmp;
            mVec.Grow(e, &tmp);
        }
        Elem16* w = mVec.mpEnd;
        float* pf = pts + i * 3;
        float a = pf[0];
        float b = pf[1];
        float c = pf[2];
        float inv = 1.0f / sqrtf(((a * a + b * b) + c * c) + 1e-8f);
        w[-1].x = a * inv;
        w[-1].y = inv * b;
        w[-1].z = c * inv;
        w[-1].w = (float)cos((double)angles[i] * 0.017453292);
    }
}

// ===========================================================================
// @ 0x00c687e0  (cdecl) clear a vector of noun refs
// ===========================================================================
void __cdecl ClearVector(Vec* v)
{
    for (int i = 0; i < (int)(v->end - v->begin); ++i) {
        int* noun = v->begin[i];
        ((TFv_i)VTSLOT(noun, 0x54))(noun, 0);
        ((cGameNounManager*)FUN_00b3d300())->RemoveNoun(v->begin[i]);
    }
    v->erase(v->begin, v->end);
}

// ===========================================================================
// @ 0x00c68840
// ===========================================================================
void __fastcall F68840(COrn* o)
{
    ClearVector((Vec*)((char*)o + 4));
}

// ===========================================================================
// @ 0x00c68850
// ===========================================================================
void COrn::E850(int* noun)
{
    if (noun == 0) {
        ClearVector((Vec*)((char*)this + 4));
        return;
    }
    int* first = mVec4.begin[0];
    float* p = ((cSpatial*)noun)->GetPosition();
    int* dst = (int*)((char*)first + 0x118);
    dst[0] = ((int*)p)[0];
    dst[1] = ((int*)p)[1];
    dst[2] = ((int*)p)[2];
    H4460(0);
}

// ===========================================================================
// @ 0x00c688a0  Collect the spatial positions of every element into a vector.
// ===========================================================================
void COrnList::Collect(Vector3Vec* dst, char* out)
{
    dst->erase(dst->mpBegin, dst->mpEnd);
    int i = 0;
    if ((int)(mVec.end - mVec.begin) > 0) {
        do {
            CObject* o = (CObject*)mVec.begin[i];
            float* p = o->mSpatial.GetPosition();
            Vector3 v;
            v.x = p[0];
            v.y = p[1];
            v.z = p[2];
            dst->push_back(&v);
            ++i;
        } while (i < (int)(mVec.end - mVec.begin));
    }
    *out = mFlag0;
}

// ===========================================================================
// @ 0x00c68930
// ===========================================================================
void COrn::E930()
{
    H3f90();
    Update();
    if (mVec134 != 0) {
        int* v = mVec134;
        if (((TFc_v)VTSLOT(v, 0x10))(v) == 0)
            ((TFv_i)VTSLOT(mVec134, 8))(mVec134, 0);
    }
    if (mpModel != 0) {
        int* m = mpModel;
        ((CModelHead*)m)->mFlags |= 1;
    }
}

// ===========================================================================
// @ 0x00c68980  view enter/leave position update
// ===========================================================================
void COrn::E980(void* view)
{
    if (mpModel != 0) {
        if (view == 0) {
            ((CModelHead*)mpModel)->mFlags &= ~1u;
            goto lab;
        }
        ((CModelHead*)mpModel)->mFlags |= 1;
    }
    if (view != 0) {
        float* p = ((cSpatial*)view)->GetPosition();
        if (mPosX != p[0] || mPosY != p[1] || mPosZ != p[2]) {
            mPosX = p[0]; mPosY = p[1]; mPosZ = p[2];
            H3f90();
            Update();
        }
        if (mVec134 != 0) {
            char c = ((TFc_v)VTSLOT(mVec134, 0x10))(mVec134);
            if (c == 0)
                ((TFv_i)VTSLOT(mVec134, 8))(mVec134, 0);
        }
        return;
    }
lab:
    if (mVec134 != 0) {
        char c = ((TFc_v)VTSLOT(mVec134, 0x10))(mVec134);
        if (c != 0)
            ((TFv_i)VTSLOT(mVec134, 0x0c))(mVec134, 0);
    }
}

// ===========================================================================
// @ 0x00c68aa0
// ===========================================================================
void COrn::Eaa0()
{
    cSpatial* sp = Spatial();
    if (mFlag124 != 0)
        FUN_00ebb720(sp, 0x1707u);
    else
        FUN_00ebb720(sp, 0x705u);
    H3f90();
    Update();
}

// ===========================================================================
// @ 0x00c68ae0
// ===========================================================================
void COrn::Eae0(float* p)
{
    float* cur = Spatial()->GetPosition();
    if (cur[0] != p[0] || cur[1] != p[1] || cur[2] != p[2]) {
        Spatial()->SetPosition(p);
        H3f90();
        Update();
    }
}

// ===========================================================================
// @ 0x00c68b40  key change: release the old effect, ask the EffectsManager.
// ===========================================================================
void COrn::Eb40(int key)
{
    if (mKey128 == key)
        return;
    if (mVec134 != 0) {
        ((TFv_i)VTSLOT(mVec134, 0x0c))(mVec134, 0);
        int* p = mVec134;
        if (p != 0) {
            mVec134 = 0;
            ((TFv_v)VTSLOT(p, 4))(p);
        }
    }
    mKey128 = key;
    void* eff = FUN_0067ddd0();
    int* old = mVec134;
    if (old != 0) {
        mVec134 = 0;
        ((TFv_v)VTSLOT(old, 4))(old);
    }
    if (((TFc_iii)VTSLOT(eff, 0x2c))(eff, mKey128, 0, &mVec134) != 0)
        Update();
}

// ===========================================================================
// @ 0x00c68bd0
// ===========================================================================
void COrn::Ebd0(float v)
{
    if (mF12c != v) {
        mF12c = v;
        Update();
    }
}

// ===========================================================================
// @ 0x00c68c00  (cdecl) create a noun and register it in refVec
// ===========================================================================
COrn* __cdecl FUN_00c68c00(Vec* refVec, Vector3* pos, int index)
{
    cGameNounManager* mgr = (cGameNounManager*)FUN_00b3d300();
    COrn* noun = (COrn*)mgr->CreateNoun(0x76f6e64);
    if (noun != 0)
        noun = (COrn*)((TFp_i)VTSLOT(noun, 0x0c))(noun, 0x76c67df);
    else
        noun = 0;
    noun->Eb40(0x7553f996);
    if (noun->mF12c != 2.0f) {
        noun->mF12c = 2.0f;
        noun->Update();
    }
    noun->Spatial()->SetPosition(pos);
    noun->mFlag124 = 1;
    if (index == -1 || index == (int)(refVec->end - refVec->begin)) {
        ((TFi_v)VTSLOT(noun, 0))(noun);
        int** e = refVec->end;
        if (e < refVec->cap) {
            refVec->end = e + 1;
            if (e != 0) {
                *e = (int*)noun;
                ((TFi_v)VTSLOT(noun, 0))(noun);
            }
        } else {
            refVec->DoInsertPtr(e, (int**)&noun);
        }
    } else {
        ((TFi_v)VTSLOT(noun, 0))(noun);
        refVec->F_00b05b40(refVec->begin + index, (int**)&noun);
    }
    if (noun != 0)
        ((TFv_v)VTSLOT(noun, 4))(noun);
    return noun;
}

// ===========================================================================
// @ 0x00c68d20
// ===========================================================================
char COrn::Ed20(int* noun)
{
    int i = 0;
    int n = (int)(mVec4.end - mVec4.begin);
    if (n > 0) {
        for (; i < n; ++i) {
            if (mVec4.begin[i] == noun)
                goto found;
        }
        i = 0;
    }
found:
    float* p = ((cSpatial*)((char*)noun + 0x34))->GetPositionI(i);
    FUN_00c68c00(&mVec4, (Vector3*)p, i);
    return 1;
}

// ===========================================================================
// @ 0x00c68d70
// ===========================================================================
void COrn::Ed70(Vector3* pos, Vector3Vec* v)
{
    if (FUN_00c649b0(&mVec4, v) != 0) {
        ClearVector(&mVec4);
        int i = 0;
        if ((int)(v->mpEnd - v->mpBegin) > 0) {
            do {
                FUN_00c68c00(&mVec4, &v->mpBegin[i], -1);
                ++i;
            } while (i < (int)(v->mpEnd - v->mpBegin));
        }
        int* first = mVec4.begin[0];
        int* dst = (int*)((char*)first + 0x118);
        dst[0] = ((int*)pos)[0];
        dst[1] = ((int*)pos)[1];
        dst[2] = ((int*)pos)[2];
        H4460(0);
    }
}

// ===========================================================================
// @ 0x00c68e30  SP::cMovableDestructibleOrnament::cMovableDestructibleOrnament
// ===========================================================================
cMovableDestructibleOrnament::cMovableDestructibleOrnament()
{
    mLoco.mVt = (void*)0x1471598;
    mVt0 = (void*)0x1471540;
    mVt4 = (void*)0x1471530;
    mLoco.mVtD4 = (void*)0x1471528;
    mSub.mVt = (void*)0x14714c0;
    mCombatant.mVt = (void*)0x1471458;
}

// ===========================================================================
// @ 0x00c68ed0  SP::cMovableDestructibleOrnament::~cMovableDestructibleOrnament
// ===========================================================================
cMovableDestructibleOrnament::~cMovableDestructibleOrnament()
{
    mVt0 = (void*)0x1471540;
    mVt4 = (void*)0x1471530;
    mLoco.mVt = (void*)0x1471598;
    mLoco.mVtD4 = (void*)0x1471528;
    mCombatant.mVt = (void*)0x1471458;
    mSub.mVt = (void*)0x14714c0;
}

// ===========================================================================
// @ 0x00c68f30  interface query
// ===========================================================================
int COrn::Ef30(int id)
{
    if (id == 0x283d961)
        return (int)this;
    int r = ((IQuery*)&mSpatial)->QK(id);
    if (r == 0) {
        r = ((IQuery*)((char*)this + 0x508))->QL(id);
        if (r == 0) {
            r = ((IQuery*)this)->QI(id);
            if (r == 0)
                r = ((IQuery*)((char*)this + 0x5d0))->QM(id);
        }
    }
    return r;
}

// ===========================================================================
// @ 0x00c69030  shutdown: tear down the combatant/loco/tail sub-objects
// ===========================================================================
void COrn::F030()
{
    mCombatant.F_00bfc720();
    mSpatial.Shutdown();
    mTail.F_00abf710();
    int* p = mp2c;
    if (p != 0) {
        mp2c = 0;
        ((TFv_v)VTSLOT(p, 4))(p);
    }
}

// ===========================================================================
// @ 0x00c69090  allocate the cGroundLocomotion object and register it
// ===========================================================================
struct cGroundLoco { void* mVt0; void* mVt4; void* mVt8; void* mVtC; };

void COrn::F090()
{
    cGroundLoco* o = (cGroundLoco*)FUN_00f473a0(0x10, "Simulator/cGroundLocomotion", 0, 0, 0, 0);
    if (o != 0) {
        o->mVt8 = (void*)0x13ec458;
        o->mVtC = 0;
        o->mVt0 = (void*)0x146a34c;
        o->mVt8 = (void*)0x1475114;
    }
    mSpatial.F_00c421b0(o);
    void* mgr = FUN_00b3d260();
    if (mgr != 0) {
        void* arg = (void*)&mTail.mVt;
        void* m2 = FUN_00b3d260();
        ((TFv_p)VTSLOT(m2, 0x38))(m2, arg);
    }
}

// ===========================================================================
// @ 0x00c69110  static-local accessor
// ===========================================================================
void* FUN_00c69110()
{
    if ((g_guard1693e00 & 1) == 0) {
        g_guard1693e00 |= 1;
        g_data1693dec[0] = 0;
        g_data1693dec[1] = 0;
        g_data1693dec[2] = 0;
        atexit(FUN_013c4150);
    }
    return g_data1693dec;
}

// ===========================================================================
// @ 0x00c69150  Simulator::cNanoDrone::cNanoDrone
// ===========================================================================
cNanoDrone::cNanoDrone()
{
    mSpatial.mVt = (void*)0x1471780;
    mVt0 = (void*)0x1471728;
    mVt4 = (void*)0x1471718;
    mp1d0 = 0;
    m1d4 = -1;
    mCombatant.mVt = (void*)0x14716b0;
}

// ===========================================================================
// @ 0x00c691e0  interface query
// ===========================================================================
int COrn::F1e0(int id)
{
    int r;
    if (id != 0x6ef0ec9) {
        r = ((IQuery*)this)->QI(id);
        if (r == 0) {
            r = ((IQuery*)&mSpatial)->QJ(id);
            if (r == 0)
                return ((IQuery*)((char*)this + 0x108))->QL(id);
        }
    } else {
        r = (int)this;
    }
    return r;
}

// ===========================================================================
// @ 0x00c69290  SP::cNanoDrone::~cNanoDrone
// ===========================================================================
cNanoDrone::~cNanoDrone()
{
    void* p = mp1d0;
    mVt0 = (void*)0x1471728;
    mVt4 = (void*)0x1471718;
    mSpatial.mVt = (void*)0x1471780;
    mCombatant.mVt = (void*)0x14716b0;
    if (p != 0) {
        ((cAgentOrderManager*)p)->F_00bcae90();
        FUN_00f47380(p);
        mp1d0 = 0;
    }
}