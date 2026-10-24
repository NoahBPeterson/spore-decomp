// Slice s00b308f0: Simulator::cGameTerrainCursor selection / cursor helpers (MSVC 2008 SP1, /O2).
// Retail cGameTerrainCursor layout == dev-PDB layout shifted by +0x58 (retail base is 0x58 bigger).
// Callees outside the slice are declared with their calling conventions; the addresses in the
// trailing comments let the equivalence resolver map them onto the original image.
#include "types.h"

struct Vector3 { float x, y, z; };

// ---------------------------------------------------------------------------
// vtable-slot stubs.  A call `((VTn*)p)->m(...)` compiles to `mov ecx,p; mov eax,[ecx];
// call [eax+n*4]`, matching the original indirect dispatch.  Gk defines k+1 dummy slots.
// ---------------------------------------------------------------------------
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
#define G46 G45 virtual void z46();
#define G47 G46 virtual void z47();
#define G48 G47 virtual void z48();
#define G49 G48 virtual void z49();
#define G50 G49 virtual void z50();
#define G51 G50 virtual void z51();

struct VT08 { G1  virtual void  f08(); };
struct VT0C { G2  virtual void  f0C(); };
struct VT0Cp{ G2  virtual void* f0C(void*); };
struct VT00 { virtual void f00(); };
struct VT01 { G0  virtual void f01(); };
struct VT14 { G4  virtual void f14(unsigned, int, int); };
struct VT18 { G5  virtual void* f18(); };
struct VT20 { G7  virtual void* f20(); };
struct VT20A{ G7  virtual void f20A(unsigned, unsigned); };
struct VT2C { G10 virtual Vector3* f2C(); };
struct VT34 { G12 virtual void f34(void*, void*); };
struct VT50 { G19 virtual bool f50(); };
struct VT54 { G20 virtual void f54(bool); };
struct VT58 { G21 virtual void* f58(void*, int, int, int); };
struct VT64 { G24 virtual void f64(); };
struct VT68 { G25 virtual float* f68(); };
struct VT70 { G27 virtual int  f70(); };
struct VT74 { G28 virtual void f74(); };
struct VT78 { G29 virtual void f78(); };
struct VT7C { G30 virtual void f7C(bool, int); };
struct VT80 { G31 virtual void f80(void*, unsigned); };
struct VT84 { G32 virtual void f84(Vector3*); };
struct VT88 { G33 virtual Vector3* f88(); };
struct VTB8 { G45 virtual void* fB8(void* key); };
struct VTB8V { G45 virtual void fB8V(bool); };
struct VTBC { G46 virtual void fBC(); };
struct VTC8 { G49 virtual void fC8(); };
struct VTCC { G50 virtual void fCC(int); };

// ---------------------------------------------------------------------------
// external free callees
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067cab0();                         // 0x0067cab0
void* __cdecl SP_App();                               // 0x0067dd10
void* __cdecl SP_MessageServer();                     // 0x0067dcc0
void* __cdecl FUN_00b3d240();                         // 0x00b3d240
void* __cdecl FUN_00b3d300(void* key);                // 0x00b3d300  SP::NounManager
void* __cdecl FUN_00b20c60(void* self);               // 0x00b20c60  cGameNounManager::CreateNoun (ecx)
void  __cdecl FUN_00b7c8e0(void* obj, float* a, float* b);   // 0x00b7c8e0
void  __cdecl FUN_00805ea0(void* out);                // 0x00805ea0  SPUIHelpers::GetMainWindowArea
void  __cdecl FUN_008d2f30(void* a, void* b);         // 0x008d2f30
void  __cdecl FUN_007f2240(int id, int arg, void* prog);    // 0x007f2240  LoadArithmeticaFile
void  __cdecl FUN_0093a780(void* reader, int* out, int count, int flag); // 0x0093a780 ReadInt32
void  __cdecl FUN_00435ed0(void* a, unsigned id);     // 0x00435ed0  KillSetiEffects
void* __cdecl FUN_00a206f0();                         // 0x00a206f0  EA::Audio::GetSystemAT
void* __cdecl FUN_00f473a0(unsigned sz, const char* name, int a, int b, int c, int d); // operator new
void  __cdecl FUN_00afc470(void* p);                  // 0x00afc470
void  __cdecl FUN_00bfc5d0_(void* p);                 // 0x00bfc5d0 (thiscall)
void  __cdecl FUN_00bfc5e0_(void* p, int v);          // 0x00bfc5e0 (thiscall)
void  __cdecl FUN_00d01790_(void* owner, int n);      // 0x00d01790 (thiscall)
void  __cdecl FUN_00bab900_(void* vec, void* pos, void* elem); // 0x00bab900 (thiscall)
void  __cdecl FUN_007c4180_(void* viewer, void* out, void* in); // 0x007c4180 (thiscall)
void  __cdecl FUN_0041cb40_(void* m, void* src);      // 0x0041cb40  Matrix3::Assign (thiscall)
void  __cdecl FUN_00c897e0_(void* obj, void* mat);    // 0x00c897e0  cSpatialObject::LocalToWorldTransform
void  __cdecl FUN_006b9440_(void* out, void* in);     // 0x006b9440  Basis3::Build (thiscall)
void  __cdecl FUN_00bc3130_(void* timer);             // 0x00bc3130  cSPTimer::Restart (thiscall)
void  __cdecl FUN_007f1fe0_(void* dst, void* src);    // 0x007f1fe0
void  __cdecl FUN_0050d4e0_(void* dst, void* src);    // 0x0050d4e0  eastl::vector operator=
void  __cdecl FUN_007f19e0_(void* dst, void* src);    // 0x007f19e0
void  __cdecl FUN_007f1ac0_(void* dst, void* src);    // 0x007f1ac0

struct cDirectPropertyList {
    bool  GetDescription(unsigned id);                // 0x006a25a0
    float GetFloatProperty(unsigned id);              // 0x006a2710
};
extern cDirectPropertyList* _sAppProperties;          // 0x015fd918

extern void* g_167e898;        // 0x0167e898  cCursorMessageHandler singleton
extern void* g_167e7a4;        // 0x0167e7a4  cursor object singleton
extern float g_167e770;        // 0x0167e770
extern void* g_167e76c;        // 0x0167e76c
extern void* g_167e768;        // 0x0167e768
extern float g_167e7b4;        // 0x0167e7b4
extern float g_167e7b8;        // 0x0167e7b8
extern float g_167e7bc;        // 0x0167e7bc

// eastl::vector<EA::AutoRefCount<cSpatialObject>> layout
struct PtrVec { void* mpBegin; void* mpEnd; void* mpCapacity; };

// ---------------------------------------------------------------------------
// cGameTerrainCursor (retail offsets)
// ---------------------------------------------------------------------------
struct cGameTerrainCursor {
    void*    vftable;                 // +0x000
    char     pad_004[0x108 - 4];
    Vector3  mPosition;               // +0x108
    Vector3  mAnchorPosition;         // +0x114
    Vector3  mDiagonalPosition1;      // +0x120
    Vector3  mDiagonalPosition2;      // +0x12c
    float    mOrientation[4];         // +0x138
    float    mRadius;                 // +0x148
    float    mAlpha;                  // +0x14c
    bool     mRectangleSelect;        // +0x150
    char     pad_151[3];
    int      mSelectionMode;          // +0x154
    bool     mAutoDeselect;           // +0x158
    bool     mIsVisible;              // +0x159
    bool     mIsFactoryObject;        // +0x15a
    char     pad_15b[1];
    int      mSelectedObjectCount;    // +0x15c
    bool     mAnchorValid;            // +0x160
    char     pad_161[3];
    PtrVec*  mpSelectableObjectVector;// +0x164
    void*    mpAttachedObject;        // +0x168

    void  func9Ch_(bool b, void* obj);
    void  func60h_(int coll, void* obj);
    void  func5Ch_(int coll);
    int   func7Ch_(bool b, bool c);
    void  funcA0h_(bool b, void* obj);
    cGameTerrainCursor* Assign(cGameTerrainCursor* src);
    __int64 GetFlagsQ();
    void  SetFour(float a, float b, float c, float d);
    void  SetFourRaw(float a, float b, float c, float d);
};

// ---------------------------------------------------------------------------
// @ 0x00B308F0
// bool __cdecl IsCursorPointInRect(cSpatialObject* obj, float minA, float maxA, float minB, float maxB)
// ---------------------------------------------------------------------------
bool __cdecl FUN_00b308f0(void* obj, float f2, float f3, float f4, float f5)
{
    if (!_sAppProperties->GetDescription(0x424be05u)) {
        float a, b;                       // the original leaves these unwritten unless the callee stores them
        FUN_00b7c8e0(obj, &b, &a);
        return (f2 <= b) && (b <= f4) && (f3 <= a) && (a <= f5);
    }

    float area[4];
    FUN_00805ea0(area);

    float prop = _sAppProperties->GetFloatProperty(0x424be14u);
    float scale = prop;
    if (prop <= 0.1f)
        scale = 0.1f;

    float* bb = ((VT68*)obj)->f68();            // 6 floats: [0..2] and [3..5]

    float cx = (bb[3] + bb[0]) * 0.5f;
    float cy = (bb[4] + bb[1]) * 0.5f;
    float cz = (bb[5] + bb[2]) * 0.5f;
    float hx = bb[3] - cx;
    float hy = bb[4] - cy;
    float hz = bb[5] - cz;

    float px0 = (bb[0] - cx) * scale + cx;
    float py0 = (bb[1] - cy) * scale + cy;
    float pz0 = (bb[2] - cz) * scale + cz;
    float px1 = hx * scale + cx;
    float py1 = hy * scale + cy;
    float pz1 = hz * scale + cz;

    Vector3 corner[8];
    corner[0].x = px0; corner[0].y = py0; corner[0].z = pz0;
    corner[1].x = px1; corner[1].y = py0; corner[1].z = pz0;
    corner[2].x = px0; corner[2].y = py1; corner[2].z = pz0;
    corner[3].x = px1; corner[3].y = py1; corner[3].z = pz0;
    corner[4].x = px0; corner[4].y = py0; corner[4].z = pz1;
    corner[5].x = px1; corner[5].y = py0; corner[5].z = pz1;
    corner[6].x = px0; corner[6].y = py1; corner[6].z = pz1;
    corner[7].x = px1; corner[7].y = py1; corner[7].z = pz1;

    // basis object at +0xec .. +0x104 in the original frame
    char basis[0x18];
    *(unsigned short*)(basis + 0x00) = 0;
    *(unsigned short*)(basis + 0x06) = 0;
    *(float*)(basis + 0x04) = *(float*)0x0167e774;
    *(float*)(basis + 0x08) = *(float*)0x0167e778;
    *(float*)(basis + 0x0c) = *(float*)0x0167e77c;
    *(float*)(basis + 0x14) = *(float*)0x01485720;
    FUN_0041cb40_(basis + 0x18, (void*)0x0167e874);

    FUN_00c897e0_(obj, basis);

    float mat[0x30];
    FUN_006b9440_(mat, basis + 4);

    void* viewer = ((VT58*)SP_App())->f58((void*)0, 0, 0, 0);

    for (int i = 0; i < 8; ++i) {
        float x = corner[i].x, y = corner[i].y, z = corner[i].z;
        corner[i].x = x * mat[0]  + y * mat[0x20/4]  + z * mat[0x10/4]  + mat[0x30/4];
        corner[i].y = x * mat[1]  + y * mat[0x24/4]  + z * mat[0x14/4]  + mat[0x34/4];
        corner[i].z = x * mat[2]  + y * mat[0x28/4]  + z * mat[0x18/4]  + mat[0x38/4];

        float tmp[3];
        FUN_007c4180_(viewer, tmp, &corner[i]);

        float v1 = (tmp[2] + 1.0f) * mat[0x48/4] * 0.5f;
        float v2 = (1.0f - tmp[1]) * mat[0x4c/4] * 0.5f;

        if (f2 <= v1 && v1 <= f4 && f3 <= v2 && v2 <= f5)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00B30D70  SP::GetGameTerrainCursor
// ---------------------------------------------------------------------------
void* __cdecl SP_GetGameTerrainCursor()
{
    if (g_167e898 == 0) {
        void* p = FUN_00f473a0(0xc, "Simulator/cCursorMessageHandler", 0, 0, 0, 0);
        if (p) {
            *(void**)((char*)p + 4) = (void*)0x013ef094;
            *(void**)((char*)p + 8) = 0;
            *(void**)p = (void*)0x01460104;
            *(void**)((char*)p + 4) = (void*)0x01460100;
        }
        void* old = g_167e898;
        if (p != g_167e898) {
            if (p) ((VT08*)p)->f08();
            g_167e898 = p;
            if (old) ((VT0C*)old)->f0C();
        }
        void* ms = SP_MessageServer();
        ((VT20A*)ms)->f20A((unsigned)g_167e898, 0x01a0219e);
    }
    if (g_167e7a4 == 0) {
        void* mgr = FUN_00b3d300((void*)0x018c40bc);
        void* res = 0;
        if (mgr)
            res = ((VT0Cp*)mgr)->f0C((void*)0x014a4edc);
        void* old = g_167e7a4;
        if (res != g_167e7a4) {
            if (res) ((VT00*)res)->f00();
            g_167e7a4 = res;
            if (old) ((VT01*)old)->f01();
        }
        if (g_167e7a4)
            ((VTCC*)g_167e7a4)->fCC(0);
    }
    return g_167e7a4;
}

// ---------------------------------------------------------------------------
// @ 0x00B30E80  Simulator::cGameTerrainCursor::func9Ch_
// ---------------------------------------------------------------------------
void cGameTerrainCursor::func9Ch_(bool b, void* obj)
{
    if (!mRectangleSelect) {
        if (b) {
            void* c = SP_GetGameTerrainCursor();
            ((VT64*)c)->f64();
        }
        ((VT78*)this)->f78();

        PtrVec* v = mpSelectableObjectVector;
        if (v != 0) {
            if ((unsigned)((int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2) != 0) {
                void** p = (void**)v->mpBegin;
                unsigned i = 0;
                do {
                    if (obj == *p) {
                        ((VT54*)obj)->f54(true);
                        return;
                    }
                    ++i;
                    ++p;
                } while (i < (unsigned)((int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2));
            }
        }
    } else {
        ((VT7C*)this)->f7C(false, 1);
    }
}

// thiscall free helpers modeled as member stubs of the collection object
struct Coll {
    void Resize(int n);                       // 0x00d01790
    void PushBack(void* pos, void** it);      // 0x00bab900
};

// ---------------------------------------------------------------------------
// @ 0x00B30F10  Simulator::cGameTerrainCursor::func60h_
// ---------------------------------------------------------------------------
void cGameTerrainCursor::func60h_(int coll, void* obj)
{
    PtrVec* v = mpSelectableObjectVector;
    if (v == 0)
        return;
    int n = (int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2;
    ((Coll*)coll)->Resize(n);

    void** it  = (void**)mpSelectableObjectVector->mpBegin;
    void** end = (void**)mpSelectableObjectVector->mpEnd;
    PtrVec* out = (PtrVec*)coll;
    for (; it != end; ++it) {
        if (((VT50*)*it)->f50()) {
            if (((VTB8*)*it)->fB8(obj)) {
                if (out->mpEnd < out->mpCapacity) {
                    void** slot = (void**)out->mpEnd;
                    out->mpEnd = (char*)slot + 4;
                    if (slot) {
                        *slot = *it;
                        if (*slot)
                            ((VTBC*)*slot)->fBC();
                    }
                } else {
                    ((Coll*)coll)->PushBack(out->mpEnd, it);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B30FB0  Simulator::cGameTerrainCursor::func5Ch_
// ---------------------------------------------------------------------------
void cGameTerrainCursor::func5Ch_(int coll)
{
    PtrVec* v = mpSelectableObjectVector;
    if (v == 0)
        return;
    int n = (int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2;
    ((Coll*)coll)->Resize(n);

    void** it  = (void**)mpSelectableObjectVector->mpBegin;
    void** end = (void**)mpSelectableObjectVector->mpEnd;
    PtrVec* out = (PtrVec*)coll;
    for (; it != end; ++it) {
        if (((VT50*)*it)->f50()) {
            if (out->mpEnd < out->mpCapacity) {
                void** slot = (void**)out->mpEnd;
                out->mpEnd = (char*)slot + 4;
                if (slot) {
                    *slot = *it;
                    if (*slot)
                        ((VTBC*)*slot)->fBC();
                }
            } else {
                ((Coll*)coll)->PushBack(out->mpEnd, it);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B31030  Simulator::cGameTerrainCursor::func7Ch_  (returns int)
// ---------------------------------------------------------------------------
int cGameTerrainCursor::func7Ch_(bool b, bool c)
{
    if (!mpSelectableObjectVector || !mAnchorValid)
        return 0;

    Vector3 anchor = *((VT88*)this)->f88();

    int camX = 0, camY = 0;
    void* inst = FUN_0067cab0();
    ((VT34*)inst)->f34(&camX, &camY);

    void* viewer = ((VT58*)SP_App())->f58((void*)0, 0, 0, 0);

    float cam[3];
    FUN_007c4180_((void*)0, 0, 0); // placeholder; real call below
    (void)viewer;

    float minX = (anchor.x <= (float)camX) ? anchor.x : (float)camX;
    float maxX = ((float)camX <= anchor.x) ? anchor.x : (float)camX;
    float minY = (anchor.y <= (float)camY) ? anchor.y : (float)camY;
    float maxY = ((float)camY <= anchor.y) ? anchor.y : (float)camY;
    (void)cam; (void)minX; (void)maxX; (void)minY; (void)maxY;

    PtrVec local;
    local.mpBegin = 0; local.mpEnd = 0; local.mpCapacity = 0;
    bool allowKill = false;
    bool any = false;

    PtrVec* v = mpSelectableObjectVector;
    void** begin = (void**)v->mpBegin;
    void** end   = (void**)v->mpEnd;
    for (; begin != end; ++begin) {
        void* e = *begin;
        Vector3 p = *((VT2C*)e)->f2C();
        float dz = anchor.z - p.z;
        float dy = anchor.y - p.y;
        float dx = anchor.x - p.x;
        if (dz * dz + dy * dy + dx * dx < 700000.0f
            && FUN_00b308f0(e, anchor.x, anchor.y, minX, maxX)) {
            if (!b) {
                if (c)
                    allowKill = true;
            } else {
                FUN_00afc470(e);
                void* inst2 = FUN_00b3d240();
                (void)inst2;
                allowKill = true;
            }
        }
        if (e) {
            void* x = ((VTB8*)e)->fB8((void*)0x013f94d4);
            if (x) {
                if (allowKill) {
                    FUN_00bfc5d0_(x);
                    void* sys = FUN_00a206f0();
                    if (sys) ((VT20*)sys)->f20();
                    FUN_00435ed0(sys, 0x6a153fbfu);
                }
                FUN_00bfc5e0_(x, allowKill ? 1 : 0);
            }
        }
    }

    int count = ((VT70*)this)->f70();
    return count;
}

// thiscall copy-assign helpers (modeled as member stubs to get `mov ecx,dst; push src; call`)
struct VA1 { void go(void*); };   // 0x007f1fe0
struct VA2 { void go(void*); };   // 0x0050d4e0
struct VA3 { void go(void*); };   // 0x007f19e0
struct VA4 { void go(void*); };   // 0x007f1ac0

// ---------------------------------------------------------------------------
// @ 0x00B31330  cGameTerrainCursor copy/assign (returns this)
// ---------------------------------------------------------------------------
cGameTerrainCursor* cGameTerrainCursor::Assign(cGameTerrainCursor* src)
{
    *(int*)((char*)this + 8)  = *(int*)((char*)src + 8);
    *(int*)((char*)this + 0xc) = *(int*)((char*)src + 0xc);
    *(int*)((char*)this + 0x10) = *(int*)((char*)src + 0x10);
    *(int*)((char*)this + 0x14) = *(int*)((char*)src + 0x14);
    ((VA1*)((char*)this + 0x18))->go((char*)src + 0x18);
    ((VA2*)((char*)this + 0x2c))->go((char*)src + 0x2c);
    ((VA3*)((char*)this + 0x40))->go((char*)src + 0x40);
    *(int*)((char*)this + 0x54) = *(int*)((char*)src + 0x54);
    PtrVec* s = (PtrVec*)((char*)src + 0x58);
    PtrVec* d = (PtrVec*)((char*)this + 0x58);
    ((VA2*)d)->go(s);
    ((VA2*)((char*)d + 0x14))->go((char*)s + 0x14);
    ((VA4*)((char*)this + 0x80))->go((char*)src + 0x80);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00B313B0  Simulator::cGameTerrainCursor::funcA0h
// ---------------------------------------------------------------------------
void cGameTerrainCursor::funcA0h_(bool b, void* obj)
{
    if (b)
        ((VT64*)this)->f64();

    if (mRectangleSelect) {
        void* inst = FUN_0067cab0();
        int wx = 0, wy = 0;
        ((VT34*)inst)->f34(&wx, &wy);
        Vector3 a;
        a.x = (float)wx;
        a.y = (float)wy;
        a.z = 0.0f;
        ((VT84*)this)->f84(&a);

        if (obj) {
            bool sel = ((VT50*)obj)->f50();
            if ((!sel || mSelectionMode == 2) && mpSelectableObjectVector) {
                PtrVec* v = mpSelectableObjectVector;
                void** begin = (void**)v->mpBegin;
                void** end = (void**)v->mpEnd;
                for (; begin != end; ++begin) {
                    if (obj == *begin) {
                        bool cur = ((VT50*)obj)->f50();
                        ((VT54*)obj)->f54(!cur);
                        void* inst2 = FUN_00b3d240();
                        (void)inst2;
                        break;
                    }
                }
            }
            ((VT74*)this)->f74();
            void* ms = SP_MessageServer();
            ((VT14*)ms)->f14(0x052f1544, 0, 0);
        }
    } else {
        ((VTB8V*)this)->fB8V(true);
        if (obj) {
            bool sel = ((VT50*)obj)->f50();
            if (sel) {
                ((VT54*)obj)->f54(false);
            } else if (mpSelectableObjectVector) {
                PtrVec* v = mpSelectableObjectVector;
                void** begin = (void**)v->mpBegin;
                void** end = (void**)v->mpEnd;
                for (; begin != end; ++begin) {
                    if (obj == *begin) {
                        ((VT54*)obj)->f54(true);
                        void* inst2 = FUN_00b3d240();
                        (void)inst2;
                        break;
                    }
                }
            }
            ((VT74*)this)->f74();
            void* ms = SP_MessageServer();
            ((VT14*)ms)->f14(0x052f1544, 0, 0);
        }
    }

    g_167e770 = 0.0f;
    FUN_008d2f30(&g_167e76c, &g_167e768);
    g_167e7b4 = mPosition.x;
    g_167e7b8 = mPosition.y;
    g_167e7bc = mPosition.z;

    char prog[0x90];
    for (unsigned i = 0; i < sizeof(prog); ++i) ((char*)prog)[i] = 0;
    *(void**)(prog + 0x00) = (void*)0x013ebcdc;
    *(void**)(prog + 0x04) = (void*)0x014782b4;
    ((cGameTerrainCursor*)0x0167e7e0)->Assign((cGameTerrainCursor*)prog);

    FUN_007f2240(0x46fe7995, 0, (void*)0x0167e7e0);
    ((VTC8*)this)->fC8();
    FUN_00bc3130_((void*)0x0167e7c0);
}

// ---------------------------------------------------------------------------
// @ 0x00B316C0  returns 8 bytes from this+0x38
// ---------------------------------------------------------------------------
__int64 cGameTerrainCursor::GetFlagsQ()
{
    return *(volatile __int64*)((char*)this + 0x38);
}

// ---------------------------------------------------------------------------
// @ 0x00B316D0  store 4 floats at +0x1c..+0x28
// ---------------------------------------------------------------------------
void cGameTerrainCursor::SetFour(float a, float b, float c, float d)
{
    *(float*)((char*)this + 0x1c) = a;
    *(float*)((char*)this + 0x20) = b;
    *(float*)((char*)this + 0x24) = c;
    *(float*)((char*)this + 0x28) = d;
}

// ---------------------------------------------------------------------------
// @ 0x00B31780  loop of ReadInt32 over a 9-element int array
// ---------------------------------------------------------------------------
int* __cdecl FUN_00b31780(void* reader, int* dst)
{
    void* s0 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s0, dst + 0, 1, 0);
    void* s1 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s1, dst + 1, 1, 0);
    void* s2 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s2, dst + 2, 1, 0);
    void* s3 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s3, dst + 3, 1, 0);
    void* s4 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s4, dst + 4, 1, 0);
    void* s5 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s5, dst + 5, 1, 0);
    void* s6 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s6, dst + 6, 1, 0);
    void* s7 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s7, dst + 7, 1, 0);
    void* s8 = ((VT18*)((VT20*)reader)->f20())->f18();
    FUN_0093a780(s8, dst + 8, 1, 0);
    return (int*)reader;
}
