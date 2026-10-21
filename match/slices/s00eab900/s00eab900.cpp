// Slice s00eab900 -- Simulator::cPlaceableSound (0x00eab900..0x00eac51e).
//
// 0x00eab900 CommitAllProperties      0x00eaba90 SetVolume
// 0x00eabb10 SetPitch                  0x00eabb50 GetVolumeScaled
// 0x00eabba0 ctor                      0x00eabe10 Shutdown
// 0x00eabe90 LoadModel                 0x00eabf30 Update
// 0x00eac310 SetPosition               0x00eac360 Write
// 0x00eac4c0 destructor
//
// cPlaceableSound : cGameData (at +0x00), cSpatialObject (at +0x34).  It is the
// "sound placed in the world" noun (noun id 0x74e0069); the record states live in
// the EA audio recorder (RecordEvent4) and are committed lazily.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

struct Vec3 { float x, y, z; };

// ------------------------------------------------------------------ extern types
struct RefObj {
    virtual void v0();
    virtual void v1();
};

// Generic game-object view (vtable with >22 slots).
struct VObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void* v18(); virtual void v1c();
    virtual void* v20(); virtual void v24(); virtual void v28(); virtual void* v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(float f); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
};

// EA audio-system handle interface (slots 0x20/0x38/0x3c/0x40/0x58 are used).
struct AudioSysAT {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int  v20();
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void v38(uint32_t id);
    virtual void v3c(uint32_t id, float value);
    virtual void v40(uint32_t id, void* value);
    virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void v58();
};

// Model-manager view (slot 0x28 used).
struct ModelMgr {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24();
    virtual uint32_t m28(uint32_t id, int arg);
};

// cObeyable/cSpatialObject view for the sub-object at +0x34.
struct SpatialView {
    void ctor();
    bool LoadModel(int name);
    void f00c8ad30(int a, int b);
    void f00c8b2e0();
    void f00c8a420();
    bool Write(void* stream);
};

// cGameNounManager view.
struct cGameNounManager { void* GetAvatar(); };

// cSpatialObject (sub-object at outer+0x34); the functions below whose `this`
// is this type address the outer cPlaceableSound through (char*)this - 0x34.
struct cSpatialObject {
    void* vtbl;             // +0x00
    float x;                // +0x04  (outer +0x38)
    float y;                // +0x08  (outer +0x3c)
    float z;                // +0x0c  (outer +0x40)
    uint8_t pad10[0x40];    // +0x10
    uint32_t flags;         // +0x50  (outer +0x84)
    uint8_t pad54[0x48];    // +0x54
    void* model;            // +0x9c  (outer +0xd0)

    bool f00c8a550(int name);   // 0x00c8a550
    bool LoadModel(int name);};

// cCommunity view (base method called by SetPosition).
struct CommunityView { void func54h(const Vec3* p); };

// cGameData view (base ctor/dtor/write).
struct GameDataView {
    void ctor();
    void dtor();
    bool Write(void* stream);
};

// Output stream for the serializer.
struct OutStream { virtual void v00(); virtual void v1c(); };

// cVarListSerializer (0xa14 bytes on the stack; ctor takes ecx = destination).
struct cVarListSerializer {
    void Construct(void* owner, void* fieldName, uint32_t id);   // 0x00692f90
    bool Serialize(void* stream);                                // 0x00692900
    uint8_t mData[0xa14];
};

// ---------------------------------------------------------------- extern globals
extern void* gVtblPlaceableSound;   // 0x014883a0
extern void* gVtblPlaceableSound2;  // 0x0148838c
extern void* gVtblSpatial;          // 0x014882c8
extern float gVecA0;                // 0x016c71ac
extern float gVecA1;                // 0x016c71b0
extern float gVecA2;                // 0x016c71b4
extern float gVecB0;                // 0x016c71dc
extern float gVecB1;                // 0x016c71e0
extern float gVecB2;                // 0x016c71e4
extern void* gScenarioState;        // 0x016c7aa4

// ------------------------------------------------------------- extern functions
extern "C" void* FUN_006c0200();                              // 0x006c0200
extern "C" AudioSysAT* Audio_GetSystemAT();                   // 0x00a206f0
extern "C" void FUN_00657240(int a, int handle, const Vec3* pos);  // 0x00657240
extern "C" void RecordEvent4(uint32_t handle, uint32_t event, float value, uint32_t flag);  // 0x00435f40
extern "C" void FUN_00572020(void* p, int v);                 // 0x00572020
extern "C" void SetGlobalProperty(uint32_t id, float v);      // 0x005ca880
extern "C" bool __stdcall FUN_00c88940(int v);                // 0x00c88940
extern "C" uint32_t GetRecorderState();                       // 0x00435e90
extern "C" void* SP_ModelManager();                           // 0x0067dd80
extern "C" cGameNounManager* SP_NounManager();                // 0x00b3d300
extern "C" void* ScenarioTutorials_GetObject0();              // 0x00efc910
extern "C" void* ScenarioTutorials_GetObject1();              // 0x00efc8f0
extern "C" void AudioSetListener3(void* s, float x, float y, float z);  // 0x009fbc50
extern "C" int* FUN_00eedba0(void* out, void* in);            // 0x00eedba0
extern "C" float __cdecl sqrtf(float);
void operator delete(void* p);

namespace EA { namespace IO {
    bool WriteUint32(void* stream, const uint32_t* value, uint32_t count, int endian);  // 0x0093aa70
}}

// --------------------------------------------------------------------- the class
struct cPlaceableSound {
    void* mVtbl;            // +0x000
    void* mVtbl2;           // +0x004
    uint8_t pad008[0x0c];   // +0x008
    void* m14;              // +0x014
    uint8_t pad018[0x14];   // +0x018
    void* m2c;              // +0x02c
    uint8_t pad030[0x04];   // +0x030
    void* mSpatVtbl;        // +0x034
    float mSpatX;           // +0x038
    float mSpatY;           // +0x03c
    float mSpatZ;           // +0x040
    uint8_t pad044[0x0c];   // +0x044
    uint32_t mFlags50;      // +0x050
    uint8_t pad054[0x0c];   // +0x054
    float m60;              // +0x060
    float m64;              // +0x064
    uint8_t pad068[0x0c];   // +0x068
    uint8_t m74;            // +0x074
    uint8_t pad075[0x07];   // +0x075
    float m7c;              // +0x07c
    uint8_t pad080[0x18];   // +0x080
    float m98;              // +0x098
    void* m9c;              // +0x09c
    uint8_t pad0a0[0x0c];   // +0x0a0
    uint8_t mAc;            // +0x0ac
    uint8_t pad0ad[0x23];   // +0x0ad
    void* mD0;              // +0x0d0
    uint8_t pad0d4[0x0c];   // +0x0d4
    int mE0;                // +0x0e0
    uint8_t pad0e4[0x0c];   // +0x0e4
    uint8_t mF0;            // +0x0f0
    uint8_t pad0f1[0x07];   // +0x0f1
    float mF8;              // +0x0f8
    float mFc;              // +0x0fc
    uint8_t pad100[0x08];   // +0x100
    void* m108;             // +0x108
    void* m10c;             // +0x10c
    void* m110;             // +0x110
    int m114;               // +0x114
    int m118;               // +0x118
    void* m11c;             // +0x11c
    uint8_t m120;           // +0x120
    uint8_t m121;           // +0x121
    uint8_t m122;           // +0x122
    uint8_t m123;           // +0x123
    uint8_t m124;           // +0x124
    uint8_t m125;           // +0x125
    uint8_t m126;           // +0x126
    uint8_t m127;           // +0x127
    uint8_t m128;           // +0x128
    uint8_t m129;           // +0x129
    uint8_t m12a;           // +0x12a
    uint8_t m12b;           // +0x12b
    float m12c;             // +0x12c
    float m130;             // +0x130
    float m134;             // +0x134
    float m138;             // +0x138
    float m13c;             // +0x13c
    float m140;             // +0x140
    float m144;             // +0x144
    float m148;             // +0x148
    float m14c;             // +0x14c
    float m150;             // +0x150
    float m154;             // +0x154
    uint8_t pad158[0x0c];   // +0x158
    float m164;             // +0x164
    float m168;             // +0x168
    float m16c;             // +0x16c
    float m170;             // +0x170
    float m174;             // +0x174
    float m178;             // +0x178
    float m17c;             // +0x17c
    float m180;             // +0x180
    float m184;             // +0x184
    float m188;             // +0x188
    float m18c;             // +0x18c
    float m190;             // +0x190
    float m194;             // +0x194
    float m198;             // +0x198
    float m19c;             // +0x19c
    float m1a0;             // +0x1a0
    void* m1a4;             // +0x1a4
    void* m1a8;             // +0x1a8

    void ctorGameData();
    void f00c8a020(int a, float v);     // cSpatialObject helper on this
    void f00eab860(int v);              // 0x00eab860

    cPlaceableSound* Construct();
    void CommitAllProperties();
    void SetVolume(float v);
    void SetPitch(float v);
    float GetVolumeScaled();
    void Shutdown();
    void Update();
    void SetPosition(const Vec3* p);
    bool Write(void* stream);
    cPlaceableSound* Destroy(uint8_t flags);
};

// @ 0x00eab900
void cPlaceableSound::CommitAllProperties()
{
    float level1 = 1.0f;
    float level0 = 1.0f;
    void* p = FUN_006c0200();
    if (p) {
        level1 = *(float*)((char*)p + 0x1e4);
        level0 = *(float*)((char*)p + 0x1e0);
    }
    AudioSysAT* at = Audio_GetSystemAT();
    int handle = at ? at->v20() : 0;
    m114 = handle;
    FUN_00657240(m118, handle, (const Vec3*)&mSpatX);
    RecordEvent4((uint32_t)m114, 0xc57f4567, m98, 0);
    RecordEvent4((uint32_t)m114, 0x25df0108, level1, 0);
    if (m121 != 0) {
        RecordEvent4((uint32_t)m114, 0x12d2a4d4, 1.0f, 0);
        RecordEvent4((uint32_t)m114, 0x66ef9aba, level0, 0);
        RecordEvent4((uint32_t)m114, 0xe4dd1818, m13c, 0);
        RecordEvent4((uint32_t)m114, 0x0cd928a9, m140, 0);
    } else {
        RecordEvent4((uint32_t)m114, 0x71bc3009, level0, 0);
    }
    int h = m114;
    AudioSysAT* at2 = Audio_GetSystemAT();
    if (at2) {
        at2->v38(0x3475365);
        at2->v40(0x3475385, (void*)h);
        at2->v58();
    }
}

// @ 0x00eaba90
void cPlaceableSound::SetVolume(float v)
{
    m64 = v;
    m7c = v;
    if (mF8 != 0.0f) {
        if (FUN_00c88940(1))
            f00c8a020(1, mFc * m64);
    }
    if (mE0 != 0)
        RecordEvent4((uint32_t)mE0, 0xc57f4567, m64, 0);
}

// @ 0x00eabb10
void cPlaceableSound::SetPitch(float v)
{
    m164 = v;
    if (m114 != 0)
        RecordEvent4((uint32_t)m114, 0x25df0108, v, 0);
}

// @ 0x00eabb50
float cPlaceableSound::GetVolumeScaled()
{
    return m154 * m60;
}

// @ 0x00eabba0
cPlaceableSound* cPlaceableSound::Construct()
{
    ctorGameData();
    ((SpatialView*)((char*)this + 0x34))->ctor();
    mVtbl = &gVtblPlaceableSound;
    mVtbl2 = &gVtblPlaceableSound2;
    mSpatVtbl = &gVtblSpatial;
    _ReadWriteBarrier();  // keep the original store groups in source order
    m108 = 0;
    m10c = 0;
    m110 = 0;
    m114 = 0;
    m118 = 0;
    m11c = 0;
    _ReadWriteBarrier();
    m144 = 60.0f;
    m148 = 90.0f;
    m14c = -1.0f;
    m150 = 0.1f;
    m154 = 2.0f;
    m16c = 2.0f;
    _ReadWriteBarrier();
    m120 = 0;
    m121 = 0;
    m122 = 0;
    m123 = 0;
    m124 = 0;
    m126 = 0;
    m127 = 0;
    m128 = 0;
    m129 = 0;
    m12a = 0;
    m12b = 0;
    _ReadWriteBarrier();
    m130 = 0.0f;
    m134 = 0.0f;
    m138 = 0.0f;
    m13c = 0.0f;
    m140 = 0.0f;
    _ReadWriteBarrier();
    m164 = 1.0f;
    m168 = 0.0f;
    m170 = 1.0f;
    m174 = 1.0f;
    m178 = 0.0f;
    m17c = 5.0f;
    m180 = 0.0f;
    m184 = 5.0f;
    m188 = 1.0f;
    _ReadWriteBarrier();
    m125 = 1;
    _ReadWriteBarrier();
    m18c = gVecB0 * 7.0f;
    m190 = gVecB1 * 7.0f;
    m194 = gVecB2 * 7.0f;
    _ReadWriteBarrier();
    m198 = gVecA0;
    m19c = gVecA1;
    m1a0 = gVecA2;
    m1a4 = 0;
    m1a8 = 0;
    return this;
}

// @ 0x00eabe10
void cPlaceableSound::Shutdown()
{
    if (m114 != 0) {
        FUN_00572020((void*)m114, 0);
        m114 = 0;
    }
    if (m129 != 0) {
        SetGlobalProperty(0x8dff6314, 0.0f);
        m129 = 0;
    }
    if (m126 != 0) {
        m126 = 0;
        ((SpatialView*)((char*)this + 0x34))->f00c8ad30(1, 0);
    }
    if (m2c != 0) {
        void* p = m2c;
        m2c = 0;
        ((RefObj*)p)->v1();
    }
    ((SpatialView*)((char*)this + 0x34))->f00c8b2e0();
}

// @ 0x00eabe90
bool cSpatialObject::LoadModel(int name)
{
    flags |= 8;
    bool ok = f00c8a550(name);
    if (model != 0) {
        ModelMgr* mgr = (ModelMgr*)SP_ModelManager();
        int m = (int)model;
        uint32_t id = mgr->m28(0x6669387, 0);
        if (id < 0x40) {
            uint32_t* p = (uint32_t*)(m + 0x44 + (id >> 5) * 4);
            *p |= 1u << (id & 0x1f);
        }
        *(uint32_t*)((int)model + 4) |= 2;
        int m2 = (int)model;
        int tmp[3];
        int* r = FUN_00eedba0(tmp, (char*)this - 0x34);
        *(int*)(m2 + 0x4c) = r[0];
        *(int*)(m2 + 0x50) = r[1];
        *(int*)(m2 + 0x54) = r[2];
    }
    return ok;
}

// @ 0x00eabf30
void cPlaceableSound::Update()
{
    int state = *(int*)((char*)gScenarioState + 0xcc);
    if (state == 2 && mD0 != 0)
        *(uint32_t*)((char*)mD0 + 4) &= ~1u;

    void* obj = FUN_006c0200();
    if (!obj)
        return;
    if (m14 == 0)
        return;
    ((VObj*)m14)->v14();

    int model = (int)mD0;
    int tmp[3];
    FUN_00eedba0(tmp, this);
    *(int*)(model + 0x4c) = tmp[0];
    *(int*)(model + 0x50) = tmp[1];
    *(int*)(model + 0x54) = tmp[2];

    if (m98 != *(float*)((char*)obj + 0x20))
        ((VObj*)((char*)this + 0x34))->v40(*(float*)((char*)obj + 0x20));

    float f = *(float*)((char*)obj + 0x1e4);
    if (m164 != f)
        SetPitch(f);

    uint8_t selected = (uint8_t)(mAc == 0);
    if (m125 == 0 && selected)
        m122 = 0;
    m125 = selected;

    uint8_t isTutorial = 0;
    uint8_t isScenario = 0;
    if (state == 1) {
        isTutorial = (uint8_t)(ScenarioTutorials_GetObject0() == obj);
        isScenario = (uint8_t)(ScenarioTutorials_GetObject1() == obj);
    }
    uint8_t wasSelected = m125;

    if (m129 != isTutorial) {
        m129 = isTutorial;
        SetGlobalProperty(0x8dff6314, isTutorial ? 1.0f : 0.0f);
    }

    bool skip = false;
    if (m127 == 0) {
        if (m120 != 0) {
            if (isTutorial && m12a == 0) {
                if (m12c != 0.0f && state == 1)
                    CommitAllProperties();
            }
        } else {
            skip = true;
        }
    }
    if (!skip && m120 != 0) {
        if (state == 2) {
            cGameNounManager* mgr = SP_NounManager();
            void* avatar = mgr->GetAvatar();
            if (avatar) {
                Vec3* pos = (Vec3*)((VObj*)((char*)avatar + 0xc0))->v2c();
                float dx = pos->x - mSpatX;
                float dy = pos->y - mSpatY;
                float dz = pos->z - mSpatZ;
                float dist = sqrtf(dz * dz + (dy * dy + dx * dx));
                if (m12c * m98 > dist) {
                    if (m125 != 0 && m122 == 0) {
                        m122 = 1;
                        CommitAllProperties();
                    }
                } else {
                    if (m122 != 0 && m123 != 0) {
                        FUN_00572020((void*)m114, 0);
                        m114 = 0;
                    }
                }
            }
        }
    }
    if (m120 == 0) {
        if (m124 != 0 && wasSelected != 0 && m118 != 0 && m114 == 0) {
            m114 = (int)GetRecorderState();
            AudioSysAT* at = Audio_GetSystemAT();
            if (at) {
                at->v38(0x3475365);
                at->v40(0x3475381, (void*)m118);
                at->v40(0x3475385, (void*)m114);
                at->v3c(0x3475391, mSpatX);
                at->v3c(0x3475395, mSpatY);
                at->v3c(0x3475398, mSpatZ);
                at->v3c(0xc57f4567, m98);
                at->v3c(0x25df0108, *(float*)((char*)obj + 0x1e4));
                at->v3c(0x71bc3009, *(float*)((char*)obj + 0x1e0));
                at->v58();
            }
        }
    }

    f00eab860((isScenario || isTutorial) ? 1 : 0);
    if (m114 != 0 && wasSelected == 0) {
        FUN_00572020((void*)m114, 0);
        m114 = 0;
    }
    m12a = isTutorial;
}

// @ 0x00eac310
void cPlaceableSound::SetPosition(const Vec3* p)
{
    ((CommunityView*)this)->func54h(p);
    uint8_t wasActive = m74;
    mF0 = 1;
    if (wasActive != 0 && mE0 != 0)
        AudioSetListener3((void*)mE0, p->x, p->y, p->z);
}

// @ 0x00eac360
bool cPlaceableSound::Write(void* stream)
{
    void* a = ((VObj*)stream)->v20();
    void* out = ((VObj*)a)->v18();
    uint32_t id = 0x74e0069;
    _ReadWriteBarrier();  // the original keeps the id store ahead of the argument pushes
    EA::IO::WriteUint32(out, &id, 1, 0);
    bool ok = ((GameDataView*)this)->Write(stream)
           && ((SpatialView*)((char*)this + 0x34))->Write(stream);
    cVarListSerializer ser;
    ser.Construct(this, (void*)0x15a912c, 0x1a80d26);
    if (ok && ser.Serialize(stream))
        return true;
    return false;
}
// @ 0x00eac4c0
cPlaceableSound* cPlaceableSound::Destroy(uint8_t flags)
{
    mVtbl = &gVtblPlaceableSound;
    mVtbl2 = &gVtblPlaceableSound2;
    mSpatVtbl = &gVtblSpatial;
    _ReadWriteBarrier();  // the original keeps the m1a8 load after the vtable stores
    RefObj* p = (RefObj*)m1a8;
    if (p != 0) {
        p->v1();
    }
    if (m11c != 0) {
        RefObj* q = (RefObj*)m11c;
        q->v1();
    }
    ((SpatialView*)((char*)this + 0x34))->f00c8a420();
    ((GameDataView*)this)->dtor();
    if (flags & 1)
        operator delete(this);
    return this;
}
