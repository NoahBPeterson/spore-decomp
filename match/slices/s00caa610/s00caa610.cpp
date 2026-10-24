// Slice s00caa610 -- SP::cVehicle unit-disband / serialization support.
//
//   00caa610  SP::cVehicle::DisbandUnit              (this = cVehicle base)
//   00caa900  FUN_00caa900                            (this = cVehicle base; clears the
//                                                     behavior stimuli + the 24-byte slot
//                                                     vector at +0xb68 and releases +0xb7c)
//   00caa980  SP::cVehicle::ReadWeaponsFromPropList   (this = cVehicle base)
//   00cab0e0  cVehicle weapon-slot serializer read     (arg1 = serializer, arg2 = 24-byte vector)
//   00cab360  SP::cVehicle::LoadModel                 (this = cVehicle + 0x34, i.e. the embedded
//                                                     cSpatialObject sub-object)
//
// The retail cVehicle is larger than any single previous slice exposed, so the object is modelled
// locally with role-named members and explicit padding for the gaps that are never touched here.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef int            i32;
typedef unsigned short u16;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- small helpers

// x87 sqrt (matches the original, which uses fld/fsqrt/fstp and 1/sqrt).
inline float fsqrt_(float x)
{
    float r;
    __asm {
        fld  x
        fsqrt
        fstp r
    }
    return r;
}

// Ref-counted object used by the 24-byte slot vector (Release lives in slot +0x04).
class cRefObj24 {
public:
    virtual void v000();                                 // +0x00
    virtual void v004();                                 // +0x04
    virtual void Release();                              // +0x08
};

// One 24-byte slot: payload pointer plus a small inline record.
struct tSlot24 {
    cRefObj24* mpObj;                                    // +0x00
    float      mF0;                                      // +0x04
    float      mF1;                                      // +0x08
    float      mF2;                                      // +0x0c
    u32        mI0;                                      // +0x10
    u32        mI1;                                      // +0x14
};

// Overlay view of the first bytes of a 24-byte slot when a raw weapon record is written.
struct tWeaponRec {
    u32 m_id;                                            // +0x00
    u32 m_parts;                                         // +0x04
    u8  m_flags;                                         // +0x08
};

// Vector of 24-byte slots (erase helper at 0x00ca9b00).
class cSlotVector24 {
public:
    tSlot24* Erase(tSlot24* pFirst, tSlot24* pLast);     // 0x00ca9b00
    void     Insert(tSlot24* pWhere, tSlot24* pValue);   // 0x00ca9b70

    tSlot24* mpBegin;                                    // +0x00
    tSlot24* mpEnd;                                      // +0x04
    tSlot24* mpCapacity;                                 // +0x08
};

// Ref-counted object used by the 16-byte slot vector (Release lives in slot +0x08).
class cRefObj16 {
public:
    virtual void v000();                                 // +0x00
    virtual void v004();                                 // +0x04
    virtual void Release();                              // +0x08
};

struct tSlot16 {
    cRefObj16* mpObj;                                    // +0x00
    u8         pad004[0x0c];                             // +0x04 .. +0x0f
};

// Vector of 16-byte slots (erase helper at 0x00ca9cc0).
class cSlotVector16 {
public:
    tSlot16* Erase(tSlot16* pFirst, tSlot16* pLast);     // 0x00ca9cc0

    tSlot16* mpBegin;                                    // +0x00
    tSlot16* mpEnd;                                      // +0x04
    tSlot16* mpCapacity;                                 // +0x08
};

// Object whose Release lives in vtable slot +0xc0 (used for the +0xb7c pointer).
class cRefObjC0 {
public:
    virtual void v000();                                 // +0x00
    virtual void v0c0();                                 // +0xc0
};

// Ref-counted object whose Release is in vtable slot +0x04 (held by the property holder).
class cRefObj04 {
public:
    virtual void v000();                                 // +0x00
    virtual void Release();                              // +0x04
};

// ---------------------------------------------------------------- property machinery

// A resolved property: only the type tag at +0x12 is inspected.
struct Property {
    u8   pad000[0x12];                                   // +0x00 .. +0x11
    u16  mType;                                          // +0x12
    float*  GetFloat();                                  // 0x0041ea70
    u32*    GetUInt();                                   // 0x0041ea00
};

// The property list bound to a game object.  HasProperty is vtable slot +0x24.
class cPropertyList {
public:
    virtual void v000();
    virtual void v004();
    virtual void v008();
    virtual void v00c();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01c();
    virtual void v020();
    virtual char HasProperty(u32 key, Property** out);   // +0x24
};

// Holder hanging off a game object; the live property list sits at +0x90.
struct cPropHolder {
    u8             pad000[0x04];                         // +0x00 .. +0x03
    u32            m_flags004;                           // +0x04
    u8             pad008[0x4c - 0x08];                  // +0x08 .. +0x4b
    float          m_scaleC4;                            // +0x4c
    float          m_scaleC8;                            // +0x50
    float          m_scaleCC;                            // +0x54
    u8             pad058[0x90 - 0x58];                  // +0x58 .. +0x8f
    cPropertyList* mpPropertyList;                       // +0x90
};

// eastl::basic_string<wchar_t> (only ever passed by address).
struct WString {
    u8 mData[0x1c];
};

// The editor serializer handed to FUN_00cab0e0 (and used by the cVarListSerializer ctor).
class ISerializer {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018();
    virtual void EndItem();                              // +0x1c
    virtual void* GetWriter();                           // +0x20
    virtual void v024();
};
class ISerializerStream {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014();
    virtual void* GetStream();                           // +0x18
};

// SP::cVarListSerializer (0xa14 bytes); ctor 0x00692f90, Read 0x00693e10.
struct cVarListSerializer {
    u8 mData[0xa14];
    cVarListSerializer() {}
    cVarListSerializer(void* pObject, void* pList, u32 signature);   // 0x00692f90
    char Read(void* pStream);                                        // 0x00693e10
};

// ---------------------------------------------------------------- cVehicle

// Target record returned by the spatial vtable +0x68 / +0x14 accessor (radius at +0x14).
struct cSpatialTarget {
    u8    pad000[0x14];                                  // +0x00 .. +0x13
    float m_radius;                                      // +0x14
};

// The embedded spatial sub-object at cVehicle+0x34 (only the slots used here are named).
struct cVehicleSpatial {
    void** mpVtbl;                                       // +0x00
};

inline void* VSpatialCall(cVehicleSpatial* s, int off) { return s->mpVtbl[off / 4]; }

// Behaviour-stimuli sub-object (ClearAll at 0x00bc98f0).
class cBehaviorStimuli {
public:
    void ClearAll(u32 nMask, int nValue);                // 0x00bc98f0
};

// The vehicle as seen by these functions.
struct cVehicle {
    void**          m_vtbl;                              // +0x000
    u8              m_pad004[0x34 - 0x04];               // +0x004
    cVehicleSpatial m_spatial;                           // +0x034
    u8              m_pad038[0xd0 - 0x38];               // +0x038
    cPropHolder*    m_pPropHolder;                       // +0x0d0
    u8              m_padD4[0x218 - 0xd4];               // +0x0d4
    float           m_field218;                          // +0x218
    u8              m_pad21c[0x224 - 0x21c];             // +0x21c
    u32             m_field224;                          // +0x224
    u8              m_pad228[0x508 - 0x228];             // +0x228
    u8              m_weapon508[0x14];                   // +0x508
    u8              m_pad51c[0x534 - 0x51c];             // +0x51c
    float           m_field534;                          // +0x534
    u8              m_pad538[0x540 - 0x538];             // +0x538
    float           m_field540;                          // +0x540
    u8              m_pad544[0x5d0 - 0x544];             // +0x544
    u32             m_behaviorHandle;                    // +0x5d0
    u8              m_pad5d4[0xaf0 - 0x5d4];             // +0x5d4
    void*           m_pBehaviorTree;                     // +0xaf0
    u8              m_padAf4[0xaf8 - 0xaf4];             // +0xaf4
    u32             m_fieldAf8;                          // +0xaf8
    u8              m_padAfc[0xb18 - 0xafc];             // +0xafc
    float           m_fieldB18;                          // +0xb18
    u32             m_factionB1c;                        // +0xb1c
    u32             m_modelB20;                          // +0xb20
    u8              m_padB24[0xb68 - 0xb24];             // +0xb24
    cSlotVector24   m_slotsB68;                          // +0xb68
    u8              m_padB74[0xb7c - 0xb74];             // +0xb74
    cRefObjC0*      m_ptrB7c;                            // +0xb7c
    u8              m_padB80[0xbd0 - 0xb80];             // +0xb80
    u8              m_fieldBd0;                          // +0xbd0
    u8              m_padBd1[0xc50 - 0xbd1];             // +0xbd1
    float           m_fieldC50;                          // +0xc50
    float           m_fieldC54;                          // +0xc54
    float           m_fieldC58;                          // +0xc58
    float           m_fieldC5c;                          // +0xc5c
    float           m_fieldC60;                          // +0xc60
    cSlotVector16   m_slotsC64;                          // +0xc64
    u8              m_padC70[0xcc8 - 0xc70];             // +0xc70
    WString         m_nameCC8;                           // +0xcc8
    u8              m_padCe4[0xd08 - 0xce4];             // +0xce4
    void*           m_ptrD08;                            // +0xd08
    void*           m_ptrD0c;                            // +0xd0c
    u8              m_fieldD10;                          // +0xd10
    u8              m_padD11[0xd64 - 0xd11];             // +0xd11
    u32             m_fieldD64;                          // +0xd64
    float           m_fieldD68;                          // +0xd68
};

// The property-holder pointer lives at +0x0d0 (mPropD0 in the sibling slices).
inline cPropHolder* propHolder(cVehicle* v) { return v->m_pPropHolder; }

// Same object seen through the embedded spatial sub-object pointer (cVehicle+0x34):
// the register-arg ABI hands this base to cVehicle::LoadModel.
struct cVehicleSpatialView {
    void**         mpVtbl;                               // +0x000
    u8             pad004[0x9c - 0x04];                  // +0x004 .. +0x09b
    cPropHolder*   m_pPropHolder;                        // +0x09c  (cVehicle+0x0d0)
    u8             padA0[0xae8 - 0xa0];                  // +0x0a0 .. +0x0ae7
    u32            m_faction;                            // +0x0ae8  (cVehicle+0x0b1c)
    u8             padAEC[0xcdc - 0xaec];                // +0x0aec .. +0x0cdb
    u8             m_fieldD10;                           // +0x0cdc  (cVehicle+0x0d10)
};

// ---------------------------------------------------------------- externals

// Free helper functions are declared without a calling convention and reached through an
// explicit cast at the call site (MSVC rejects __thiscall on free functions).
extern "C" {
    void* SP_NounManager();                                 // 0x00b3d300
    void* FUN_00b25f40(void* mgr, int id);                  // 0x00b25f40
    void* FUN_00b3d240();                                   // 0x00b3d240
    void* FUN_00b3d260();                                   // 0x00b3d260  BehaviorManager
    void  FUN_00befd80(float fRadius, int a);               // 0x00befd80  civic_radius_accum
    void  FUN_00ff1ff0(void* p);                            // 0x00ff1ff0
    void  FUN_00bf3c50(void* p);                            // 0x00bf3c50
    void  FUN_00b225d0();                                   // 0x00b225d0  RemoveNoun
    void  FUN_00c9e7c0();                                   // 0x00c9e7c0
    void  FUN_00c9f250();                                   // 0x00c9f250
    void  FUN_00c9f7c0();                                   // 0x00c9f7c0
    void* FUN_00ca10a0();                                   // 0x00ca10a0  Vec3*
    void* FUN_00ca1130();                                   // 0x00ca1130  Vec3*
    void  FUN_00ca8860();                                   // 0x00ca8860
    void  FUN_00ca7710();                                   // 0x00ca7710
    void  FUN_00ca2ae0();                                   // 0x00ca2ae0  CreateDefaultTool
    void  FUN_00caa360();                                   // 0x00caa360  DestroyVehicle
    void  FUN_00692f90();                                   // 0x00692f90  cVarListSerializer ctor
    char  FUN_00693e10();                                   // 0x00693e10  cVarListSerializer::Read
    void  FUN_0093a780(void* pStream, void* pValue, int nCount, int nZero);
    void  FUN_006a1400();                                   // 0x006a1400  GetPropertyAsString16
    char  FUN_006a07d0();                                   // 0x006a07d0  GetPropertyAsIntArray
    char  FUN_006a0ae0();                                   // 0x006a0ae0  reserve
    void  FUN_0040cf10();                                   // 0x0040cf10  GetPropertyT<int>
    void  FUN_00423650();                                   // 0x00423650  eastl wstring assign
    int   FUN_0067dcd0();                                   // 0x0067dcd0  GetManager
    void* FUN_0067de30();                                   // 0x0067de30  PropertyManager
    u32   FUN_00b5b800();                                   // 0x00b5b800  GetCurrentGameMode
    void* FUN_00b3d390(void* a, void* b);                   // 0x00b3d390  vector erase
    void  FUN_0104e340();                                   // 0x0104e340  CreateToolFromToolID
    void  FUN_00ceec10();                                   // 0x00ceec10
    void  FUN_00c893f0();                                   // 0x00c893f0  cSpatialObject::func93F0
    void  FUN_00c8a550();                                   // 0x00c8a550  cSpatialObject::LoadModel
    void  FUN_00c9f650();                                   // 0x00c9f650
    void  FUN_006a0ca0();                                   // 0x006a0ca0  SetProperty<bool>
    extern float DAT_0157c714;                              // 0x0157c714  1.0f
    extern float DAT_0157c718;                              // 0x0157c718  1.0f
    extern float DAT_0157c71c;                              // 0x0157c71c  1.0f
}

// Convenience call shims with the real conventions.
inline void  CallB225d0(void* mgr, void* noun) { ((void (__thiscall*)(void*, void*))FUN_00b225d0)(mgr, noun); }
inline void  CallC9e7c0(void* self)            { ((void (__thiscall*)(void*))FUN_00c9e7c0)(self); }
inline void  CallC9f250(void* self)            { ((void (__thiscall*)(void*))FUN_00c9f250)(self); }
inline void  CallC9f7c0(void* self)            { ((void (__thiscall*)(void*))FUN_00c9f7c0)(self); }
inline void  CallCa8860(void* vec, int n)      { ((void (__thiscall*)(void*, int))FUN_00ca8860)(vec, n); }
inline void  CallCa2ae0(void* self)            { ((void (__thiscall*)(void*))FUN_00ca2ae0)(self); }
inline void  CallCaa360(void* self, int a, int b) { ((void (__thiscall*)(void*, int, int))FUN_00caa360)(self, a, b); }
inline void  Call692f90(cVarListSerializer* s, void* obj, void* list, u32 sig) {
    ((void (__thiscall*)(cVarListSerializer*, void*, void*, u32))FUN_00692f90)(s, obj, list, sig);
}
inline char  Call693e10(cVarListSerializer* s, void* stream) {
    return ((char (__thiscall*)(cVarListSerializer*, void*))FUN_00693e10)(s, stream);
}
inline void  Call6a1400(void* pl, u32 key, WString* out) {
    ((void (__thiscall*)(void*, u32, WString*))FUN_006a1400)(pl, key, out);
}
inline char  Call6a07d0(void* pl, u32 key, int* count, int** out) {
    return ((char (__thiscall*)(void*, u32, int*, int**))FUN_006a07d0)(pl, key, count, out);
}
inline char  Call6a0ae0(void* pl, u32 key, void* a, void* b) {
    return ((char (__thiscall*)(void*, u32, void*, void*))FUN_006a0ae0)(pl, key, a, b);
}
inline void  Call40cf10(void* pl, u32 key, void* out) {
    ((void (__thiscall*)(void*, u32, void*))FUN_0040cf10)(pl, key, out);
}
inline void  Call423650(WString* s, const wchar_t* first, const wchar_t* last) {
    ((void (__thiscall*)(WString*, const wchar_t*, const wchar_t*))FUN_00423650)(s, first, last);
}
inline void  CallC893f0(void* self, Vec3* a, Vec3* b) {
    ((void (__thiscall*)(void*, Vec3*, Vec3*))FUN_00c893f0)(self, a, b);
}
inline void  CallC9f650(void* self, Vec3* out) {
    ((void (__thiscall*)(void*, Vec3*))FUN_00c9f650)(self, out);
}
inline char  CallC8a550(void* self, int modelType) {
    return ((char (__thiscall*)(void*, int))FUN_00c8a550)(self, modelType);
}
inline void  CallCeec10(void* a1, float a2, float a3, float a4, void* a5, void* a6, void* a7, void* a8) {
    ((void (__thiscall*)(void*, float, float, float, void*, void*, void*, void*))FUN_00ceec10)
        (a1, a2, a3, a4, a5, a6, a7, a8);
}
inline void  Call6a0ca0(void* pl, u32 key, int n, void* v) {
    ((void (__thiscall*)(void*, u32, int, void*))FUN_006a0ca0)(pl, key, n, v);
}
inline void  Call104e340(void* mgr, u32 toolID) {
    ((void (__thiscall*)(void*, u32))FUN_0104e340)(mgr, toolID);
}

// Vtable dispatch helpers.
#define VFN(o)  (*(void***)(o))
#define VCALL0(Ret, o, off)                 ((Ret (__thiscall*)(void*))VFN(o)[(off) / 4])(o)
#define VCALL1(Ret, o, off, A)              ((Ret (__thiscall*)(void*, A))VFN(o)[(off) / 4])(o, a1_)

// Weapon-part lookup tables.
extern const u32 kWeaponTable[];                  // 0x01474968
extern const u32 kWeaponParts[];                  // 0x0169a1a8

// ---------------------------------------------------------------- function bodies
// @ 0x00caa610 SP::cVehicle::DisbandUnit
void __fastcall SP_cVehicle_DisbandUnit(cVehicle* this_, char param_2)
{
    int polID = ((int (__thiscall*)(cVehicle*))this_->m_vtbl[0x4c / 4])(this_);
    void* nounMgr = SP_NounManager();
    FUN_00b25f40(nounMgr, polID);

    if (param_2 != 0) {
        CallC9e7c0(this_);
        float r;
        __asm { fstp r }
        FUN_00befd80(r, 0);
    }

    cVehicleSpatial* sp = &this_->m_spatial;
    this_->m_fieldBd0 = 1;

    cSpatialTarget* tgt = ((cSpatialTarget* (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x68 / 4])(sp);
    float radius = tgt->m_radius;

    Vec3 offset;
    {
        Vec3* pos = ((Vec3* (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x2c / 4])(sp);
        float nx = pos->x, ny = pos->y, nz = pos->z;
        float il = 1.0f / fsqrt_((nx * nx + ny * ny + nz * nz) + 1.0e-8f);
        offset.x = radius * (nx * il);
        offset.y = radius * (ny * il);
        offset.z = radius * (nz * il);
    }

    void* resMgr = FUN_00b3d240();
    Vec3 base;
    ((void (__thiscall*)(cVehicleSpatial*, Vec3*))sp->mpVtbl[0x5c / 4])(sp, &base);
    Vec3 world;
    {
        Vec3* pos = ((Vec3* (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x2c / 4])(sp);
        world.x = pos->x + offset.x;
        world.y = pos->y + offset.y;
        world.z = pos->z + offset.z;
    }
    ((void (__thiscall*)(void*, u32, Vec3*, Vec3*))VFN(resMgr)[0x60 / 4])
        (resMgr, 0x042a3491, &world, &base);

    char occupied = ((char (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x58 / 4])(sp);
    if (occupied != 0 && param_2 != 0) {
        void* tgt2 = ((void* (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x68 / 4])(sp);
        float mid = *(float*)((char*)tgt2 + 0x14);
        ((void (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x68 / 4])(sp);

        Vec3 offset2;
        {
            Vec3* pos = ((Vec3* (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x2c / 4])(sp);
            float nx = pos->x, ny = pos->y, nz = pos->z;
            float il = 1.0f / fsqrt_((nx * nx + ny * ny + nz * nz) + 1.0e-8f);
            offset2.x = mid * (nx * il);
            offset2.y = mid * (ny * il);
            offset2.z = mid * (nz * il);
        }

        void* resMgr2 = FUN_00b3d240();
        CallC9e7c0(this_);
        float rr;
        __asm { fstp rr }
        int ir = (int)rr;

        Vec3 base2;
        ((void (__thiscall*)(cVehicleSpatial*, Vec3*))sp->mpVtbl[0x5c / 4])(sp, &base2);
        Vec3 world2;
        {
            Vec3* pos = ((Vec3* (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0x2c / 4])(sp);
            world2.x = pos->x + offset2.x;
            world2.y = pos->y + offset2.y;
            world2.z = pos->z + offset2.z;
        }
        ((void (__thiscall*)(void*, u32, Vec3*, Vec3*, int, int, int))VFN(resMgr2)[0x5c / 4])
            (resMgr2, 0x064bf470, &world2, &base2, ir, -1, 0x3f800000);
    }

    CallCaa360(this_, 0, -1);

    void* behMgr = FUN_00b3d260();
    ((void (__thiscall*)(void*, void*))VFN(behMgr)[0x3c / 4])(behMgr, &this_->m_behaviorHandle);

    if (this_->m_ptrD08 != 0) {
        FUN_00ff1ff0(this_->m_ptrD0c);
        this_->m_ptrD0c = 0;
    }

    polID = ((int (__thiscall*)(cVehicle*))this_->m_vtbl[0x4c / 4])(this_);
    nounMgr = SP_NounManager();
    void* obj = FUN_00b25f40(nounMgr, polID);
    if (obj != 0) {
        FUN_00bf3c50(this_);
        return;
    }
    nounMgr = SP_NounManager();
    CallB225d0(nounMgr, this_);
}

// @ 0x00caa900 FUN_00caa900
void __fastcall FUN_00caa900(cVehicle* this_)
{
    cBehaviorStimuli* stimuli = (cBehaviorStimuli*)((char*)this_->m_pBehaviorTree + 8);
    stimuli->ClearAll(0x4ff6, 0);

    cSlotVector24* vec = &this_->m_slotsB68;
    tSlot24* p = vec->mpBegin;
    if (p != vec->mpEnd) {
        cRefObj24* obj = p->mpObj;
        if (obj != 0) {
            p->mpObj = 0;
            obj->v004();
        }
    }
    vec->Erase(vec->mpBegin, vec->mpEnd);

    cRefObjC0* r = this_->m_ptrB7c;
    if (r != 0) {
        this_->m_ptrB7c = 0;
        ((void (__thiscall*)(void*))(*(void***)r)[0xc0 / 4])(r);
    }
}

// @ 0x00caa980 SP::cVehicle::ReadWeaponsFromPropList
void __fastcall SP_cVehicle_ReadWeaponsFromPropList(cVehicle* this_)
{
    CallC9f250(this_);
    this_->m_slotsC64.Erase(this_->m_slotsC64.mpBegin, this_->m_slotsC64.mpEnd);

    cPropHolder* holder = propHolder(this_);
    if (holder->mpPropertyList == 0)
        return;

    void* resMgr = (void*)FUN_0067dcd0();

    // Resolve the named weapon; otherwise read the name property into the string at +0xcc8.
    {
        void* holder0 = 0;
        u32 tag = 0x30bdee3;
        char found = ((char (__thiscall*)(void*, void**, u32*))VFN(resMgr)[0x0c / 4])
            (resMgr, &holder0, &tag);
        void* named = 0;
        if (found != 0 && holder0 != 0)
            named = (void*)((void* (__thiscall*)(void*, u32))VFN(holder0)[0x0c / 4])(holder0, 0x30bdee3);
        if (found != 0 && holder0 != 0 && named != 0) {
            ((void (__thiscall*)(void*))VFN(named)[0])(named);
            wchar_t* name = (wchar_t*)((void* (__thiscall*)(void*))VFN(named)[0x0c / 4])(named);
            const wchar_t* end = name;
            while (*end != 0)
                ++end;
            Call423650(&this_->m_nameCC8, name, end);
        } else {
            Call6a1400(holder->mpPropertyList, 0x043afa7e, &this_->m_nameCC8);
        }
    }

    cPropertyList* pl = holder->mpPropertyList;

    Property* prop;
    prop = 0;
    if (pl != 0 && pl->HasProperty(0x720be500, &prop) && prop->mType == 0x0d)
        this_->m_fieldC58 = *prop->GetFloat();
    prop = 0;
    if (pl != 0 && pl->HasProperty(0x720be501, &prop) && prop->mType == 0x0d)
        this_->m_fieldC50 = *prop->GetFloat();
    prop = 0;
    if (pl != 0 && pl->HasProperty(0x720be502, &prop) && prop->mType == 0x0d)
        this_->m_fieldC54 = *prop->GetFloat();
    prop = 0;
    if (pl != 0 && pl->HasProperty(0x46d0560, &prop) && prop->mType == 0x0a)
        this_->m_fieldD64 = *prop->GetUInt();
    prop = 0;
    if (pl != 0 && pl->HasProperty(0x46d0572, &prop) && prop->mType == 0x0d)
        this_->m_fieldD68 = *prop->GetFloat();
    prop = 0;
    if (pl != 0 && pl->HasProperty(0x5b567d1, &prop) && prop->mType == 0x0a)
        this_->m_fieldAf8 = *prop->GetUInt();

    if (this_->m_factionB1c == 0) {
        this_->m_field224 = ((((u32)(u8)this_->m_fieldAf8) & 4) | 10) >> 1;
    }

    Vec3 mount;
    CallCeec10(this_, this_->m_fieldC50, this_->m_fieldC54, this_->m_fieldC58,
               &mount, 0, 0, 0);

    cVehicleSpatial* sp = &this_->m_spatial;
    this_->m_fieldC5c = mount.x;

    float face = ((float (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0xc8 / 4])(sp);
    if (face == this_->m_field218) {
        float cur = ((float (__thiscall*)(cVehicleSpatial*))sp->mpVtbl[0xc8 / 4])(sp);
        if (mount.y > cur)
            ((void (__thiscall*)(cVehicleSpatial*, float, int))sp->mpVtbl[0xc4 / 4])(sp, mount.y, 0);
    }
    this_->m_field218 = mount.y;

    if ((u32)FUN_00b5b800() == 0x01654c10u) {
        this_->m_field218 = this_->m_field218 * 1.0f;
    }

    {
        float f540 = this_->m_field540;
        float f534 = this_->m_field534;
        this_->m_field534 = mount.z;
        this_->m_fieldB18 = mount.z;
        if (f540 == -1.0f) {
        doClamp:
            this_->m_field540 = ((float (__thiscall*)(void*))VFN(&this_->m_weapon508)[0x58 / 4])
                (&this_->m_weapon508);
        } else {
            float denom = f534;
            if (denom <= 0.0f)
                denom = 1.0f;
            float nv = (f540 / denom) * mount.z;
            this_->m_field540 = nv;
            if (nv > mount.z)
                goto doClamp;
        }
    }

    // Behaviour-tree-driven part selection.
    {
        void* pm = FUN_0067de30();
        int bee = 0;
        char ok = ((char (__thiscall*)(void*, u32, void*))VFN(pm)[0x30 / 4])(pm, 0xa4c2f6bd, &bee);
        if (ok != 0) {
            u32 key = 0;
            switch (this_->m_factionB1c) {
            case 0: key = 0x97e02ab9; break;
            case 1: key = 0xc930af25; break;
            case 2: key = 0xc9ce9128; break;
            default: break;
            }
            if (this_->m_factionB1c <= 2)
                Call40cf10((void*)bee, key, &bee);
        }
        this_->m_fieldC60 = *(float*)&bee;
    }

    // Weapon list: reserve, read the int array, then append a 24-byte slot per entry.
    {
        Vec3 scratch;
        int count = 0;
        int* array = 0;
        char ok = Call6a0ae0(pl, 0xf1fae962u, &scratch, 0);
        if (ok != 0) {
            if (Call6a07d0(pl, 0x04caccce, &count, &array) == 0)
                count = 0;

            int nIter = (this_->m_modelB20 != 0) ? 1 : 0;
            if (nIter == 0)
                nIter = count;
            for (int i = 0; i < nIter; ++i) {
                u32 weaponID = (i < count) ? (u32)array[i] : 0;
                u32 parts[3];
                parts[0] = 0; parts[1] = 0; parts[2] = 0;
                if (this_->m_modelB20 == 0) {
                    for (int slot = 0; slot < 4; ++slot) {
                        for (int j = 0; j < 4; ++j) {
                            u32 idx = kWeaponTable[j + slot * 4];
                            const u32* rec = &kWeaponParts[idx * 3];
                            if (rec[0] == weaponID && rec[1] == 0 && rec[2] == 0) {
                                parts[0] = rec[0];
                                parts[1] = rec[1];
                                parts[2] = rec[2];
                                goto haveParts;
                            }
                        }
                    }
                    {
                        const u32* rec = &kWeaponParts[kWeaponTable[this_->m_factionB1c * 4] * 3];
                        parts[0] = rec[0];
                        parts[1] = rec[1];
                        parts[2] = rec[2];
                    }
                } else {
                    const u32* rec = &kWeaponParts[kWeaponTable[i + this_->m_factionB1c * 4] * 3];
                    parts[0] = rec[0];
                    parts[1] = rec[1];
                    parts[2] = rec[2];
                }
            haveParts:
                tSlot24* dst = this_->m_slotsB68.mpEnd;
                if (dst < this_->m_slotsB68.mpCapacity) {
                    this_->m_slotsB68.mpEnd = dst + 1;
                    if (dst != 0)
                        dst->mpObj = 0;
                } else {
                    tSlot24 tmp;
                    tmp.mpObj = 0;
                    this_->m_slotsB68.Insert(dst, &tmp);
                }
                {
                    tWeaponRec* rec = (tWeaponRec*)(this_->m_slotsB68.mpEnd - 1);
                    rec->m_id = (u32)i;
                    rec->m_parts = (i < count) ? parts[0] : 0xffffffffu;
                    rec->m_flags = 0;
                }
                if (array != 0) {
                    u32 toolID = parts[0];
                    void* mgr = FUN_00b3d390(&toolID, &toolID);
                    Call104e340(mgr, toolID);
                }
            }
        }
    }

    CallCa2ae0(this_);
}

// @ 0x00cab0e0 FUN_00cab0e0
void __cdecl FUN_00cab0e0(ISerializer* pSerializer, cSlotVector24* pSlots)
{
    pSlots->Erase(pSlots->mpBegin, pSlots->mpEnd);

    int count = 0;
    ISerializerStream* holder = (ISerializerStream*)pSerializer->GetWriter();
    void* stream = holder->GetStream();
    FUN_0093a780(stream, &count, 1, 0);
    CallCa8860(pSlots, count);

    u32 done = 0;
    if (count != 0) {
        do {
            tSlot24 value;
            value.mpObj = 0;

            cVarListSerializer serializer;
            Call692f90(&serializer, &value, (void*)0x0157c920, 0x1a80d26);
            Call693e10(&serializer, pSerializer);

            tSlot24* dst = pSlots->mpEnd;
            if (dst < pSlots->mpCapacity) {
                pSlots->mpEnd = dst + 1;
                if (dst != 0) {
                    dst->mpObj = value.mpObj;
                    if (value.mpObj != 0)
                        ((void (__thiscall*)(void*))VFN(value.mpObj)[0])(value.mpObj);
                    dst->mF0 = value.mF0;
                    dst->mF1 = value.mF1;
                    dst->mF2 = value.mF2;
                    dst->mI0 = value.mI0;
                    dst->mI1 = value.mI1;
                }
            } else {
                pSlots->Insert(dst, &value);
            }
            if (value.mpObj != 0)
                ((void (__thiscall*)(void*))VFN(value.mpObj)[1])(value.mpObj);

            done += 1;
        } while (done < (u32)count);
    }
    pSerializer->EndItem();
}

// @ 0x00cab360 SP::cVehicle::LoadModel
char __fastcall SP_cVehicle_LoadModel(cVehicle* pVehicle, int modelType)
{
    cVehicleSpatialView* self = (cVehicleSpatialView*)pVehicle;
    if (CallC8a550(self, modelType) == 0)
        return 0;

    if (FUN_00b5b800() != 0x01654c10u) {
        Vec3 a = *(Vec3*)FUN_00ca10a0();
        Vec3 b = *(Vec3*)FUN_00ca1130();
        CallC893f0(self, &b, &a);
    }

    cPropHolder* holder = self->m_pPropHolder;
    holder->m_flags004 |= 4;

    if (FUN_00b5b800() == 0x01654c10u) {
        self->m_pPropHolder->m_flags004 &= 0xfffff7ffu;
        self->m_pPropHolder->m_flags004 &= 0xfffffffb;
        cPropHolder* h = self->m_pPropHolder;
        h->m_scaleC4 = DAT_0157c714;
        h->m_scaleC8 = DAT_0157c718;
        h->m_scaleCC = DAT_0157c71c;
    } else {
        char occupied = ((char (__thiscall*)(cVehicleSpatialView*))self->mpVtbl[0x58 / 4])(self);
        if (occupied != 0) {
            self->m_pPropHolder->m_flags004 &= 0xfffff7ffu;
            self->m_pPropHolder->m_flags004 |= 4;
        } else {
            self->m_pPropHolder->m_flags004 |= 0x800u;
            self->m_pPropHolder->m_flags004 |= 4;
        }
        cPropHolder* h = self->m_pPropHolder;
        Vec3 out;
        CallC9f650((cVehicle*)((char*)pVehicle - 0x34), &out);
        h->m_scaleC4 = out.x;
        h->m_scaleC8 = out.y;
        h->m_scaleCC = out.z;
    }

    if (holder->mpPropertyList != 0) {
        u8 bit = (self->m_faction == 1) ? 1 : 0;
        Call6a0ca0(self->m_pPropHolder->mpPropertyList, 0x4e5f251c, 1, &bit);
        u8 bit2 = (bit == 0) ? 1 : 0;
        Call6a0ca0(self->m_pPropHolder->mpPropertyList, 0xd4b5ed03, 1, &bit2);
    }

    u32 w = self->m_pPropHolder->m_flags004;
    self->m_fieldD10 = (u8)((~(w >> 0x12)) & 1);

    cVehicle* veh = (cVehicle*)((char*)pVehicle - 0x34);
    SP_cVehicle_ReadWeaponsFromPropList(veh);
    CallC9f7c0(veh);
    return 1;
}
