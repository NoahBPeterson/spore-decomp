// Slice s00bed920 - SP Simulator::cCityWalls construction / style / transform helpers
//  00bedb70  Simulator::cCityWalls::cCityWalls  (constructor, returns this)
//  00bede60  cCityWalls::ApplyStyle(int)        (guarded reload of the style property block)
//  00bee150  transform mGates -> mGatesTransformed            (this = cCityWalls)
//  00bee200  transform mTurrets/... -> *Transformed blocks    (this = cCityWalls)
//  00bed920  free helper: build + apply a cPropertyList on the Gonzago model world
//
// Toolchain: VS2008 SP1 (cl 15.00) Spore game code; flags /O2 /MD /Gy /EHsc /TP.
// The cCityWalls object is a flat struct with 20-byte SpVector<Vector3> members
// {begin,end,capacity} plus 8 untouched bytes (the vector's allocator/context slots).
#include "types.h"

namespace SP {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

// 20-byte vector of Vector3 (0xc-byte elements); only the first three pointers are
// touched by the constructor and by count()/resize.
struct SpVector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint8_t  mAlloc[8];
    void     resize(int n);                          // 0x00473810  ?resize@?$SpVector@UVector3@@@@QAEXH@Z
    void     FUN_004548d0(int n);                    // 0x004548d0
    Vector3* FUN_00479330(Vector3* pos, int n, Vector3* val);   // 0x00479330 (insert/grow)
    Vector3* erase(Vector3* first, Vector3* last);   // 0x0050f740  ?erase@?$SpVector@UVector3@@@@QAEPAUVector3@@PAU2@0@Z
};

struct cGameData     { void ctor(); };               // 0x00b18660
struct cSpatialObject{ void ctor(); };               // 0x00c89630

// --- misc engine stubs used by the helpers ---
void* __cdecl PropertyManager();                     // 0x0067de30
void  __cdecl GetPropertyAsKey(int prop, uint32_t key, void* dest);   // 0x006a1250
void  __cdecl FUN_00bed3e0(void* keys, int n);       // 0x00bed3e0
void  __cdecl FUN_011e073e(void* dest, int val, uint32_t size);       // 0x011e073e
void* __cdecl GonzagoModelWorld();                   // 0x00b3d520
struct GonzagoWorld { void v18(void* propList, uint32_t arg); };      // vtable slot 0x18

struct cPropertyList {
    void ctor();                                     // 0x006a1c40  ??0cPropertyList@SP@@QAE@XZ
    void SetProperty(uint32_t key, void* variant);   // 0x006a2e20
};
struct Variant {
    uint32_t raw[8];
    void ctor();                                     // implicit
    bool Construct(uint32_t a, uint32_t b, void* data, uint32_t elem, uint32_t n);  // 0x0093dd80
    void Destruct(int flag);                         // 0x0093db80
};
struct PropManager {
    char Resolve(uint32_t prop, uint32_t key, void** out);   // vtable slot 0x2c
};

struct Combatant { int GetDamageState(); };          // 0x008e7f80  ([this+0x34])

// ---------------------------------------------------------------------------
// 0x00bedb70  Simulator::cCityWalls::cCityWalls
// ---------------------------------------------------------------------------
struct CityWalls {
    void*    vtbl_a;             // 0x000  (0x014690b0)
    void*    vtbl_b;             // 0x004  (0x0146909c)
    uint8_t  pad_08[0x2c];       // 0x008..0x033 (cGameData base)
    void*    vtbl_spatial;       // 0x034  (0x01468fd8, cSpatialObject vtable)
    uint8_t  pad_38[0x108 - 0x38];
    uint8_t  field_108;          // 0x108
    uint8_t  pad_109[3];
    uint32_t field_10c;          // 0x10c
    SpVector mDockSlots;         // 0x110
    SpVector field_124;          // 0x124
    Vector3  field_138;          // 0x138
    Vector3  field_144;          // 0x144
    Vector3  field_150;          // 0x150
    SpVector field_15c;          // 0x15c
    SpVector field_170;          // 0x170
    SpVector field_184;          // 0x184
    SpVector field_198;          // 0x198
    SpVector field_1ac;          // 0x1ac
    SpVector field_1c0;          // 0x1c0
    SpVector field_1d4;          // 0x1d4
    SpVector field_1e8;          // 0x1e8
    SpVector field_1fc;          // 0x1fc
    SpVector field_210;          // 0x210
    Vector3  field_224;          // 0x224
    Vector3  field_230;          // 0x230
    Vector3  field_23c;          // 0x23c
    Vector3  field_248;          // 0x248
    uint32_t field_254;          // 0x254
    float    mInnerRadius;       // 0x258
    float    mOuterRadius;       // 0x25c
    float    field_260;          // 0x260
    uint32_t field_264;          // 0x264  (cCity*)
    Vector3  field_268;          // 0x268
    uint8_t  mBuildingLinks[0xc4];   // 0x274..0x337
    uint8_t  pad_338[0xc];       // 0x338..0x343
    uint32_t mStyle;             // 0x344
    uint32_t field_348;          // 0x348
    uint32_t field_34c;          // 0x34c
    uint8_t  field_350;          // 0x350
    uint8_t  pad_351[3];
    uint32_t field_354;          // 0x354

    CityWalls* ctor();                       // 0x00bedb70
    void   FUN_00bede60(int style);          // 0x00bede60
    void   FUN_00bee150();                   // 0x00bee150
    void   FUN_00bee200();                   // 0x00bee200
    void   FUN_00bec790(int a);              // 0x00bec790
    Vector3* FUN_00becb10(Vector3* out, Vector3* src);   // 0x00becb10
};

struct City {
    void FUN_00bd94a0(void* vec);            // 0x00bd94a0
    void FUN_00be5280(void* vec);            // 0x00be5280
    void FUN_00bd9620(void* vec);            // 0x00bd9620
    void FUN_00be5320(void* vec);            // 0x00be5320
    void FUN_00be5700(void* out);            // 0x00be5700
};

extern float gF_0168c420, gF_0168c424, gF_0168c428;   // default position triple
extern float gF_01466190;                             // 29.0f (inner radius)
extern float gF_01469148;                             // 37.0f (outer radius)
extern float gF_0156f530, gF_0156f534, gF_0156f538;

// @ 0x00bedb70
CityWalls* CityWalls::ctor()
{
    ((cGameData*)this)->ctor();
    ((cSpatialObject*)((char*)this + 0x34))->ctor();
    *(void**)((char*)this + 0x34) = (void*)0x1468fd8;
    vtbl_a = (void*)0x14690b0;
    vtbl_b = (void*)0x146909c;
    field_108 = 0;
    field_10c = 0;
    mDockSlots.mpBegin = 0; mDockSlots.mpEnd = 0; mDockSlots.mpCapacity = 0;
    field_124.mpBegin = 0;  field_124.mpEnd = 0;  field_124.mpCapacity = 0;
    field_138.x = field_138.y = field_138.z = 0.0f;
    field_144.x = field_144.y = field_144.z = 0.0f;
    field_150.x = field_150.y = field_150.z = 0.0f;
    field_15c.mpBegin = 0; field_15c.mpEnd = 0; field_15c.mpCapacity = 0;
    field_170.mpBegin = 0; field_170.mpEnd = 0; field_170.mpCapacity = 0;
    field_184.mpBegin = 0; field_184.mpEnd = 0; field_184.mpCapacity = 0;
    field_198.mpBegin = 0; field_198.mpEnd = 0; field_198.mpCapacity = 0;
    field_1ac.mpBegin = 0; field_1ac.mpEnd = 0; field_1ac.mpCapacity = 0;
    field_1c0.mpBegin = 0; field_1c0.mpEnd = 0; field_1c0.mpCapacity = 0;
    field_1d4.mpBegin = 0; field_1d4.mpEnd = 0; field_1d4.mpCapacity = 0;
    field_1e8.mpBegin = 0; field_1e8.mpEnd = 0; field_1e8.mpCapacity = 0;
    field_1fc.mpBegin = 0; field_1fc.mpEnd = 0; field_1fc.mpCapacity = 0;
    field_210.mpBegin = 0; field_210.mpEnd = 0; field_210.mpCapacity = 0;
    field_224.x = gF_0168c420; field_224.y = gF_0168c424; field_224.z = gF_0168c428;
    field_230.x = gF_0168c420; field_230.y = gF_0168c424; field_230.z = gF_0168c428;
    field_23c.x = gF_0168c420; field_23c.y = gF_0168c424; field_23c.z = gF_0168c428;
    field_248.x = gF_0168c420; field_248.y = gF_0168c424; field_248.z = gF_0168c428;
    mInnerRadius = gF_01466190;
    mOuterRadius = gF_01469148;
    field_254 = 0;
    field_260 = 0.0f;
    field_264 = 0;
    field_268.x = gF_0156f530; field_268.y = gF_0156f534; field_268.z = gF_0156f538;
    mStyle = 0x9181a194;
    field_348 = 0;
    field_34c = 0;
    field_350 = 0;
    field_354 = 0;
    field_198.resize(6);
    field_184.resize(6);
    mDockSlots.FUN_004548d0(4);
    field_124.FUN_004548d0(4);
    FUN_011e073e(mBuildingLinks, 0, 0xc4);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00bede60  cCityWalls::ApplyStyle(int style)   (__thiscall, ret 4)
// ---------------------------------------------------------------------------
struct PtrVec { void** mpBegin; void** mpEnd; void** mpCapacity; };

// @ 0x00bede60
void CityWalls::FUN_00bede60(int style)
{
    if (mStyle == style) return;

    if ((int)((char*)mDockSlots.mpEnd - (char*)mDockSlots.mpBegin) / 0xc != 4)
        mDockSlots.FUN_004548d0(4);
    if ((int)((char*)field_124.mpEnd - (char*)field_124.mpBegin) / 0xc != 4)
        field_124.FUN_004548d0(4);

    void* propObj = 0;
    PropManager* mgr = (PropManager*)PropertyManager();
    if (propObj) {
        void* p = propObj; propObj = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    if (mgr->Resolve(style, 0x2e4b4cc, &propObj)) {
        mStyle = style;
        GetPropertyAsKey((int)propObj, 0x44449ba, &mDockSlots.mpBegin[0]);
        GetPropertyAsKey((int)propObj, 0x44449bb, &mDockSlots.mpBegin[1]);
        GetPropertyAsKey((int)propObj, 0x44449bc, &mDockSlots.mpBegin[2]);
        GetPropertyAsKey((int)propObj, 0x44449bd, &mDockSlots.mpBegin[3]);
        GetPropertyAsKey((int)propObj, 0x653e65e, &field_124.mpBegin[0]);
        GetPropertyAsKey((int)propObj, 0x653e66a, &field_124.mpBegin[1]);
        GetPropertyAsKey((int)propObj, 0x653e65e, &field_124.mpBegin[2]);
        GetPropertyAsKey((int)propObj, 0x653e66a, &field_124.mpBegin[3]);
        GetPropertyAsKey((int)propObj, 0x44449be, &field_138);
        GetPropertyAsKey((int)propObj, 0x4d83d74, &field_144);
        GetPropertyAsKey((int)propObj, 0x44449bf, &field_150);

        for (int o = 0; o < 0x30; o += 0xc) {
            *(uint32_t*)((char*)mDockSlots.mpBegin + o + 8) = 0x40828100;
            *(uint32_t*)((char*)field_124.mpBegin + o + 8) = 0x40828100;
        }

        ((void(__thiscall*)(void*, void*))(*(void***)((char*)this + 0x34))[0x94 / 4])(
            (char*)this + 0x34, (char*)mDockSlots.mpBegin + field_254 * 0xc);
        if (field_254 == 2 || field_254 == 3)
            FUN_00bec790(field_254);

        // gather the city's combatants and hand each one the dock/gate transform vectors
        uint8_t listbuf[0x80];
        PtrVec list;
        list.mpBegin = (void**)listbuf;
        list.mpEnd = (void**)listbuf;
        list.mpCapacity = (void**)(listbuf + 0x80);
        ((City*)(field_264))->FUN_00be5700(&list);

        for (void** it = list.mpBegin; it != list.mpEnd; ++it) {
            void* item = *it;
            if (item) ((void(__thiscall*)(void*))(*(void***)item)[0])(item);
            if (((Combatant*)((char*)item + 0x588))->GetDamageState() == 2)
                ((void(__thiscall*)(void*, void*))(*(void***)((char*)item + 0x34))[0x94 / 4])(
                    (char*)item + 0x34, &field_150);
            else
                ((void(__thiscall*)(void*, void*))(*(void***)((char*)item + 0x34))[0x94 / 4])(
                    (char*)item + 0x34, &field_138);
            ((void(__thiscall*)(void*))(*(void***)item)[1])(item);
        }
        for (void** it = list.mpBegin; it != list.mpEnd; ++it) {
            void* item = *it;
            if (item) ((void(__thiscall*)(void*))(*(void***)item)[1])(item);
        }
        if (list.mpBegin && list.mpBegin != (void**)listbuf)
            ::operator delete(list.mpBegin);
    }
    if (propObj) {
        void* p = propObj; propObj = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
}

// ---------------------------------------------------------------------------
// 0x00bee150  cCityWalls::TransformGates  (__thiscall, ret 0)
// ---------------------------------------------------------------------------
// @ 0x00bee150
void CityWalls::FUN_00bee150()
{
    int n = (int)((char*)field_15c.mpEnd - (char*)field_15c.mpBegin) / 0xc;
    field_170.resize(n);
    n = (int)((char*)field_15c.mpEnd - (char*)field_15c.mpBegin) / 0xc;
    if (n > 0) {
        int off = 0;
        do {
            Vector3 tmp;
            Vector3* r = FUN_00becb10(&tmp, (Vector3*)((char*)field_15c.mpBegin + off));
            Vector3* dst = (Vector3*)((char*)field_170.mpBegin + off);
            *dst = *r;
            off += 0xc;
            --n;
        } while (n);
    }
    ((City*)(field_264))->FUN_00bd94a0(&field_170);
}

// ---------------------------------------------------------------------------
// 0x00bee200  cCityWalls::TransformAll  (__thiscall, ret 0)
// ---------------------------------------------------------------------------
// @ 0x00bee200
void CityWalls::FUN_00bee200()
{
    if (field_1ac.mpBegin != field_1ac.mpEnd) {
        int n = (int)((char*)field_1ac.mpEnd - (char*)field_1ac.mpBegin) / 0xc;
        field_1c0.resize(n);
        n = (int)((char*)field_1ac.mpEnd - (char*)field_1ac.mpBegin) / 0xc;
        if (n > 0) {
            int off = 0;
            do {
                Vector3 tmp;
                Vector3* r = FUN_00becb10(&tmp, (Vector3*)((char*)field_1ac.mpBegin + off));
                Vector3* dst = (Vector3*)((char*)field_1c0.mpBegin + off);
                *dst = *r;
                off += 0xc;
                --n;
            } while (n);
        }
        ((City*)(field_264))->FUN_00be5280(&field_1c0);
    }

    if (field_1fc.mpBegin != field_1fc.mpEnd) {
        int n = (int)((char*)field_1fc.mpEnd - (char*)field_1fc.mpBegin) / 0xc;
        field_210.resize(n);
        n = (int)((char*)field_1fc.mpEnd - (char*)field_1fc.mpBegin) / 0xc;
        if (n > 0) {
            int off = 0;
            do {
                Vector3 tmp;
                Vector3* r = FUN_00becb10(&tmp, (Vector3*)((char*)field_1fc.mpBegin + off));
                Vector3* dst = (Vector3*)((char*)field_210.mpBegin + off);
                *dst = *r;
                off += 0xc;
                --n;
            } while (n);
        }
        ((City*)(field_264))->FUN_00bd9620(&field_210);
    }

    if (field_1d4.mpBegin != field_1d4.mpEnd) {
        int srcN = (int)((char*)field_1e8.mpEnd - (char*)field_1e8.mpBegin) / 0xc;
        int n    = (int)((char*)field_1d4.mpEnd - (char*)field_1d4.mpBegin) / 0xc;
        if (srcN < n) {
            Vector3 tmp;
            field_1e8.FUN_00479330(field_1e8.mpEnd, n - srcN, &tmp);
        } else {
            field_1e8.erase((Vector3*)((char*)field_1e8.mpBegin + n * 0xc), field_1e8.mpEnd);
        }
        n = (int)((char*)field_1d4.mpEnd - (char*)field_1d4.mpBegin) / 0xc;
        if (n > 0) {
            int off = 0;
            do {
                Vector3 tmp;
                Vector3* r = FUN_00becb10(&tmp, (Vector3*)((char*)field_1d4.mpBegin + off));
                *(Vector3*)((char*)field_1e8.mpBegin + off) = *r;
                off += 0xc;
                --n;
            } while (n);
        }
        ((City*)(field_264))->FUN_00be5320(&field_1e8);
    }
}

// ---------------------------------------------------------------------------
// 0x00bed920  free helper (__cdecl, 1 arg)
// ---------------------------------------------------------------------------
struct Key { uint32_t k0, k1, k2; };

// @ 0x00bed920
void FUN_00bed920(uint32_t prop)
{
    void* propObj = 0;
    PropManager* mgr = (PropManager*)PropertyManager();
    if (propObj) {
        void* p = propObj; propObj = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    if (mgr->Resolve(prop, 0x2e4b4cc, &propObj)) {
        Key keys[6];
        FUN_00bed3e0(keys, 6);
        GetPropertyAsKey((int)propObj, 0x44449ba, &keys[0]);
        GetPropertyAsKey((int)propObj, 0x44449bb, &keys[1]);
        GetPropertyAsKey((int)propObj, 0x44449bc, &keys[2]);
        GetPropertyAsKey((int)propObj, 0x44449bd, &keys[3]);
        GetPropertyAsKey((int)propObj, 0x653e65e, &keys[4]);
        GetPropertyAsKey((int)propObj, 0x653e66a, &keys[5]);
        for (int i = 0; i < 6; ++i) keys[i].k2 = 0x40828100;

        cPropertyList list;
        list.ctor();
        Variant var;
        var.Construct(0x20, 0x98, keys, 0xc, 6);
        list.SetProperty(0x49b48ee, &var);
        ((GonzagoWorld*)GonzagoModelWorld())->v18(&list, prop);
        if ((var.raw[4] & 4) != 0) var.Destruct(0);
    }
    if (propObj) {
        void* p = propObj; propObj = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
}

} // namespace SP
