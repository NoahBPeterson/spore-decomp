// Slice s00f32880: SP::cTerrainSphere::SetPlayerColorIDs-like (0x00f32d10, 2155 bytes).
// Pushes the sphere's terrain/colour/ID arrays and scalars into the property bus at this+0xc
// (vtable slot 5 = SetProperty(id, Variant*), slot 6 = RemoveProperty(id)).
#include "types.h"
#include <xmmintrin.h>

struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant()
    {
        if (mFlags & 4)
            Destruct(0);
    }
    void Destruct(int b);                                           // 0x0093DB80
    void SetType(int type, int a, const void* p, int size, int n);  // 0x0093DD80
    Variant& SetVec31(const void* p);   // 0x006A3570
    Variant& SetInt(const void* p);     // 0x00427FD0
    Variant& SetChar(const void* p);    // 0x00422E20
    Variant& SetVec12(const void* p);   // 0x00422F40
    Variant& SetFloat(const void* p);   // 0x00428060
};

struct E12 { char b[12]; };
struct E56 { char b[56]; };
template <class T> struct Vec {
    T* mpBegin; T* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    T* begin() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};

struct IPropertyBus {
    virtual void AddRef();                               // slot 0
    virtual void Release();                              // slot 1
    virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void SetProperty(uint32_t id, Variant* v);   // slot 5
    virtual void RemoveProperty(uint32_t id);            // slot 6
    virtual void _v7(); virtual void _v8();
    virtual bool GetProperty(uint32_t id, Variant** out); // slot 9
    virtual void _v10();
    virtual void SetSource(void* p);                     // slot 11
    void SetParent(void* parent);                        // 0x006A1710
};

struct PlanetRecord {
    char pad0[0xbc];
    Vec<E12> vBC;
    char pad1[0xf8 - 0xc4];
    Vec<uint32_t> vF8;
    char pad2[0x10c - 0x100];
    float m10c;
    Vec<uint32_t> v110;
};

PlanetRecord* GetActivePlanetRecord();   // 0x010212A0
void SetVec3Array(IPropertyBus* bus, uint32_t id, int n, const void* p);   // 0x006A0EE0
void SetIntArray(IPropertyBus* bus, uint32_t id, int n, const void* p);    // 0x006A0D30
void SetFloatArray(IPropertyBus* bus, uint32_t id, int n, const void* p);  // 0x006A0DC0

struct cRefObj {
    virtual void AddRef();   // +0x00
    virtual void Release();  // +0x04
    virtual void _v2();      // +0x08
};

struct cIndexEntry {
    int mValue;              // +0x00
    int mId;                 // +0x04
    int m8;                  // +0x08
    int mC;                  // +0x0c
};

struct cResettable;
struct cScenarioNode;
struct cSphereSource;
struct cPlanetInfo;

struct cSphere {
    void* mpVtbl0;           // +0x00
    void* mpVtbl1;           // +0x04
    char pad08[4];           // +0x08
    IPropertyBus* mpBus;     // +0x0c
    void* mp10Alloc;         // +0x10
    Vec<E12> v14;
    char pad1[8];            // +0x1c
    cRefObj* mp24;           // +0x24
    Vec<E56> v28;
    char pad2[0x3c - 0x30];
    Vec<uint32_t> v3c;
    char pad3[0x50 - 0x44];
    Vec<uint32_t> v50;
    char pad4[0x64 - 0x58];
    Vec<uint32_t> v64;
    char pad5[0x8c - 0x6c];
    Vec<uint32_t> v8c;
    char pad6[0xa0 - 0x94];
    Vec<E12> vA0;
    char padA[0xb4 - 0xa8];
    Vec<E56> vB4;
    char padB[0xc8 - 0xbc];
    float mC8[3]; float mD4[3]; float mE0[3];
    int mEC; int mF0;
    union {
        char mF4[12];
        int mEffectHandle;   // +0xf4
    };
    void* mpInstance;        // +0x100
    char m104; char pad7[3];
    Vec<E12> v108;
    char pad8[0x11c - 0x110];
    Vec<uint32_t> v11c;
    char pad9[0x130 - 0x124];
    char m130[12]; char m13c[12]; char m148[12]; char m154[12];
    int m160;
    char pad10[0x18d - 0x164];
    char m18d;
    char pad11[0x190 - 0x18e];
    cResettable* mp190;      // +0x190
    char pad12[4];
    cScenarioNode* mp198;    // +0x198
    cIndexEntry* mp19c;      // +0x19c  begin
    cIndexEntry* mp1a0;      // +0x1a0  end
    char pad13[0x1b9 - 0x1a4];
    char m1b9;               // +0x1b9
    char m1ba;               // +0x1ba

    void Publish();
    void Update(int flag);   // 0x00f32440
    void FreeResources();
    void SetScale(float value);
    void SetEnabled(bool enabled);
    void RefreshScenario();
    void DestroyEffect();
    void SetSourceObject(cSphereSource* p);
    cIndexEntry* FindEntry(int id);
    void OnPlanetEvent(cPlanetInfo* info);
};

void cSphere::Publish()
{
    { Variant v; v.SetVec31(mC8);  mpBus->SetProperty(0x03a23f98, &v); }
    { Variant v; v.SetVec31(mD4);  mpBus->SetProperty(0x0b208b41, &v); }
    { Variant v; v.SetVec31(mE0);  mpBus->SetProperty(0x03a23f99, &v); }
    { Variant v; v.SetInt(&mEC);   mpBus->SetProperty(0x0536250d, &v); }
    { Variant v; v.SetInt(&mF0);   mpBus->SetProperty(0x0536250c, &v); }
    Variant vX;
    vX.SetType(0xd, 0x98, v11c.begin(), 4, v11c.size());
    Variant vY;
    vY.SetType(0x31, 0x98, v108.begin(), 0xc, v108.size());
    { Variant v; v.SetChar(&m104); mpBus->SetProperty(0x07b18058, &v); }
    mpBus->SetProperty(0xb6929c92, &vX);
    mpBus->SetProperty(0xb6929c93, &vY);
    { Variant v; v.SetVec31(m130); mpBus->SetProperty(0xb6929c95, &v); }
    { Variant v; v.SetVec31(m13c); mpBus->SetProperty(0xb6929c94, &v); }
    { Variant v; v.SetVec31(m148); mpBus->SetProperty(0x968c496a, &v); }
    { Variant v; v.SetVec31(m154); mpBus->SetProperty(0x968c496b, &v); }
    Variant vC;
    vC.SetType(0x20, 0x98, v14.begin(), 0xc, v14.size());
    Variant vD;
    vD.SetType(0x38, 0x98, v28.begin(), 0x38, v28.size());
    Variant vE;
    vE.SetType(0xd, 0x98, v50.begin(), 4, v50.size());
    Variant vF;
    vF.SetType(0xa, 0x98, v64.begin(), 4, v64.size());
    Variant vG;
    vG.SetType(0xd, 0x98, v3c.begin(), 4, v3c.size());
    Variant vH;
    vH.SetType(0xd, 0x98, v8c.begin(), 4, v8c.size());
    mpBus->SetProperty(0x02a907b5, &vC);
    mpBus->SetProperty(0x02a907b6, &vD);
    mpBus->SetProperty(0x03a23f97, &vE);
    mpBus->SetProperty(0x03dd8e59, &vF);
    mpBus->SetProperty(0x03dd8e5a, &vG);
    mpBus->SetProperty(0x7a6aa70b, &vH);
    { Variant v; v.SetVec12(mF4); mpBus->SetProperty(0x48c74c5c, &v); }
    { Variant v; v.SetInt(&m160); mpBus->SetProperty(0x56b14f05, &v); }
    PlanetRecord* rec = GetActivePlanetRecord();
    SetVec3Array(mpBus, 0x04e13cb7, rec->vBC.size(), rec->vBC.begin());
    SetIntArray(mpBus, 0x073154e0, rec->vF8.size(), rec->vF8.begin());
    { Variant v; v.SetFloat(&rec->m10c); mpBus->SetProperty(0x073137bb, &v); }
    SetFloatArray(mpBus, 0x072bec91, rec->v110.size(), rec->v110.begin());
    if (!vA0.empty()) {
        Variant vP;
        vP.SetType(0x20, 0x98, vA0.begin(), 0xc, vA0.size());
        Variant vQ;
        vQ.SetType(0x38, 0x98, vB4.begin(), 0x38, vB4.size());
        mpBus->SetProperty(0x03a90c57, &vP);
        mpBus->SetProperty(0x03a90c5f, &vQ);
    } else {
        mpBus->RemoveProperty(0x03a90c57);
        mpBus->RemoveProperty(0x03a90c5f);
    }
    { Variant v; v.SetChar(&m18d); mpBus->SetProperty(0x8e390196, &v); }
}

// ---------------------------------------------------------------------------------------------------
// Gameplay/terrain sphere helpers that follow the Publish block in the same class (0x00f32440..).
// ---------------------------------------------------------------------------------------------------

struct cGameWorld {
    char pad0[0x74];
    cScenarioNode* mpNode;   // +0x74
    char pad1[0xd0 - 0x78];
    int mD0;                 // +0xd0
};
extern cGameWorld* g_pGameWorld;            // 0x016c7aa4
extern void* g_vtblSphereA[];               // 0x013eb938
extern void* g_vtblSphereB[];               // 0x013ec458

void FreeBlock(void* p);                    // 0x00f47380
int __stdcall FUN_00f32790(int id);         // 0x00f32790

struct BlockHeader { int mOwner; };
static inline bool OwnedBlock(const void* p) { return ((const BlockHeader*)p)[-1].mOwner != 0; }

struct cResettable {
    void Reset();                           // 0x00fa92f0
};

struct cScenarioNode {
    void BeginFrame(int flag);              // 0x00f3e3b0
    void RefreshAll();                      // 0x00f401a0
    void Finalize();                        // 0x00f427c0
    void* Resolve(void* src);               // 0x00f3d780
};

struct cPlanetModel {
    void ComputeContinents();               // 0x00b87dc0
};
cPlanetModel* SP_PlanetModel();             // 0x00b3d350

struct cChildElem {
    cRefObj* mpObj;    // +0x00
    int mValue0;       // +0x04
    int mValue1;       // +0x08
    float mWeight;     // +0x0c
};

// @ 0x00f33620
bool __stdcall HasSomething(int id)
{
    return FUN_00f32790(id) != 0;
}

// @ 0x00f33580
void cSphere::SetScale(float value)
{
    float v = _mm_cvtss_f32(_mm_min_ss(_mm_max_ss(_mm_set_ss(value), _mm_setzero_ps()),
                                       _mm_set_ss(1.0f)));
    mD4[0] = v;
    Update(1);
}

// @ 0x00f335e0
void cSphere::SetEnabled(bool enabled)
{
    mD4[2] = enabled ? 1.0f : 0.0f;
    Update(1);
}

// @ 0x00f32b90
void cSphere::FreeResources()
{
    if (v28.mpBegin && OwnedBlock(v28.mpBegin))
        FreeBlock(v28.mpBegin);
    if (mp24)
        mp24->Release();
    if (mp10Alloc && OwnedBlock(mp10Alloc))
        FreeBlock(mp10Alloc);
    if (mpBus)
        mpBus->Release();
    mpVtbl1 = (void*)g_vtblSphereB;
    mpVtbl0 = (void*)g_vtblSphereA;
}

// @ 0x00f32ac0
cChildElem* __cdecl CopyChildElems(const cChildElem* first, const cChildElem* last, cChildElem* dst)
{
    if (first != last) {
        do {
            if (dst) {
                cRefObj* obj = first->mpObj;
                dst->mpObj = obj;
                if (obj)
                    obj->AddRef();
                dst->mValue0 = first->mValue0;
                dst->mValue1 = first->mValue1;
                dst->mWeight = first->mWeight;
            }
            first++;
            dst++;
        } while (first != last);
    }
    return dst;
}

// @ 0x00f33710
void cSphere::RefreshScenario()
{
    if (mp190)
        mp190->Reset();
    mp198 = g_pGameWorld->mpNode;
    mp198->BeginFrame(0);
    SP_PlanetModel()->ComputeContinents();
    mp198->RefreshAll();
    mp198->Finalize();
}

// ---------------------------------------------------------------------------------------------------
// Object/quirk helpers used by the shipped gameplay functions below.
// ---------------------------------------------------------------------------------------------------

struct cToolSub {
    virtual void _v00(); virtual void _v01(); virtual void _v02(); virtual void _v03();
    virtual void _v04(); virtual void _v05(); virtual void _v06(); virtual void _v07();
    virtual void _v08(); virtual void _v09(); virtual void _v10(); virtual void _v11();
    virtual void _v12(); virtual void _v13(); virtual void _v14(); virtual void _v15();
    virtual void _v16(); virtual void _v17(); virtual void _v18(); virtual void _v19();
    virtual void _v20(); virtual void _v21(); virtual void _v22(); virtual void _v23();
    virtual void _v24(); virtual void _v25(); virtual void _v26(); virtual void _v27();
    virtual void _v28(); virtual void _v29(); virtual void _v30(); virtual void _v31();
    virtual void _v32(); virtual void _v33(); virtual void _v34(); virtual void _v35();
    virtual void _v36();
    virtual void SetOwner(void* owner);   // +0x94 = slot 37
};

struct cToolObject {
    char pad0[0x34];
    cToolSub mSub;                        // vptr at +0x34
    char pad1[0xda - 0x38];
    char mDA;                             // +0xda
    char pad2[0x114 - 0xdb];
    char m114;                            // +0x114
    void EnableFlag(int flag);            // 0x00c64b50
};

struct cGameNoun {
    virtual void _v0(); virtual void _v1(); virtual void _v2();
    virtual cToolObject* CreateTool(uint32_t id);   // +0x0c = slot 3
};

struct cGameNounManager {
    cGameNoun* CreateNoun(uint32_t id);   // 0x00b20c60
};

struct cFieldSrc {
    virtual void _v00(); virtual void _v01(); virtual void _v02(); virtual void _v03();
    virtual void _v04(); virtual void _v05(); virtual void _v06(); virtual void _v07();
    virtual void _v08(); virtual void _v09(); virtual void _v10();
    virtual int GetA();                   // +0x2c = slot 11
    virtual int GetB();                   // +0x30 = slot 12
    virtual float GetC();                 // +0x34 = slot 13
};

struct cFieldDst {
    virtual void _v00(); virtual void _v01(); virtual void _v02(); virtual void _v03();
    virtual void _v04(); virtual void _v05(); virtual void _v06(); virtual void _v07();
    virtual void _v08(); virtual void _v09(); virtual void _v10(); virtual void _v11();
    virtual void _v12(); virtual void _v13();
    virtual void SetA(int a);             // +0x38 = slot 14
    virtual void SetB(int b);             // +0x3c = slot 15
    virtual void SetC(float c);           // +0x40 = slot 16
};

struct cEffectInstance {
    virtual void _v0();
    virtual void Release();               // +0x04 = slot 1
    virtual void Stop(int now);           // +0x08 = slot 2
};

struct cEffectsManager {
    virtual void _v00(); virtual void _v01(); virtual void _v02(); virtual void _v03();
    virtual void _v04(); virtual void _v05(); virtual void _v06(); virtual void _v07();
    virtual void _v08(); virtual void _v09(); virtual void _v10();
    virtual void ReleaseEffect(int handle, int mode, void** out);   // +0x2c = slot 11
};

struct cSphereSource {
    char pad0[8];
    int m08;                              // +0x08
    char pad1[0x30 - 0x0c];
    void* mp30;                           // +0x30
};

struct cPlanetInfo {
    int mId;                              // +0x00
    char pad0[0x21c];
    float mRadius;                        // +0x220
    volatile uint32_t mFlags;             // +0x224
};

struct cMsg {
    virtual void _v0();
    uint32_t mId;                         // +0x04
    bool Check();                         // 0x00f256a0
};

struct cPropHolder {
    char pad0[0x90];
    void* mpProps;                        // +0x90
};

struct cNotifyTarget {
    virtual void _v00(); virtual void _v01(); virtual void _v02(); virtual void _v03();
    virtual void _v04(); virtual void _v05(); virtual void _v06(); virtual void _v07();
    virtual void _v08(); virtual void _v09(); virtual void _v10(); virtual void _v11();
    virtual void _v12(); virtual void _v13(); virtual void _v14(); virtual void _v15();
    virtual void _v16(); virtual void _v17(); virtual void _v18(); virtual void _v19();
    virtual void _v20(); virtual void _v21(); virtual void _v22(); virtual void _v23();
    virtual void _v24(); virtual void _v25(); virtual void _v26(); virtual void _v27();
    virtual void _v28(); virtual void _v29(); virtual void _v30(); virtual void _v31();
    virtual void _v32(); virtual void _v33(); virtual void _v34(); virtual void _v35();
    virtual void _v36(); virtual void _v37(); virtual void _v38(); virtual void _v39();
    virtual void _v40(); virtual void _v41(); virtual void _v42();
    virtual cPropHolder* GetHolder();     // +0xac = slot 43
};

struct Elem38 {
    uint16_t mA;                          // +0x00
    uint16_t mB;                          // +0x02
    float mC;                             // +0x04
    float mD;                             // +0x08
    float mE;                             // +0x0c
    float mF;                             // +0x10
    float mG[9];                          // +0x14 .. +0x34
};

cGameNounManager* SP_NounManager();       // 0x00b3d300
cEffectsManager* SP_EffectsManager();     // 0x0067ddd0
void* ResolveObject(void* id);            // 0x00b18e00
bool GetPropertyTInt(void* obj, uint32_t id, int* out);  // 0x0040cf10
cMsg* __stdcall LookupMessage(int id);    // 0x00f3e8a0
extern int g_lastIndex;                   // 0x015b0194

cToolObject* __stdcall CreateToolObject(int owner);
int __stdcall CopyToolSettings(int* p);

// 0x00f33640: create the game noun for a tribe tool and point its interaction sub-object at the owner.
// @ 0x00f33640
cToolObject* __stdcall CreateToolObject(int owner)
{
    cGameNounManager* mgr = SP_NounManager();
    cGameNoun* noun = mgr->CreateNoun(0x7a30a12);
    cToolObject* obj;
    if (noun != 0)
        obj = noun->CreateTool(0x7a309fb);
    else
        obj = 0;
    obj->mSub.SetOwner((void*)(owner + 0x48));
    obj->m114 = 0;
    obj->EnableFlag(0);
    obj->mDA = 0;
    return obj;
}

// 0x00f336a0: copy the three shared settings from the source object onto the newly created one.
// @ 0x00f336a0
int __stdcall CopyToolSettings(int* p)
{
    int srcId = p[0];
    int ownerId = p[1];
    cToolObject* created = CreateToolObject(ownerId);
    cFieldDst* dst = (cFieldDst*)ResolveObject(created);
    cFieldSrc* src = (cFieldSrc*)ResolveObject((void*)srcId);
    dst->SetA(src->GetA());
    dst->SetB(src->GetB());
    dst->SetC(src->GetC());
    return (int)created;
}

// 0x00f32cb0: drop the effect instance owned by this sphere.
// @ 0x00f32cb0
void cSphere::DestroyEffect()
{
    if (mEffectHandle) {
        cEffectsManager* mgr = SP_EffectsManager();
        cEffectInstance* inst = (cEffectInstance*)mpInstance;
        if (inst) {
            mpInstance = 0;
            inst->Release();
        }
        mgr->ReleaseEffect(mEffectHandle, 0, &mpInstance);
        inst = (cEffectInstance*)mpInstance;
        if (inst)
            inst->Stop(1);
    }
}

// 0x00f32bf0: connect the sphere's property bus to a new source object.
// @ 0x00f32bf0
void cSphere::SetSourceObject(cSphereSource* p)
{
    int value;
    if (g_pGameWorld->mD0 != 2) {
        if (mpBus != (IPropertyBus*)p) {
            mpBus->SetSource(p);
            mpBus->SetParent(p->mp30);
        }
    }
    bool have = false;
    if (mpBus != 0) {
        Variant* out;
        have = mpBus->GetProperty(0x02a907b7, &out) && out->mTypeId == 0xa;
    }
    if (!have) {
        value = p->m08;
        IPropertyBus* bus = mpBus;
        Variant var;
        var.SetInt(&value);
        bus->SetProperty(0x02a907b7, &var);
    }
    m1ba = 1;
}

// 0x00f329e0: cached linear search of the 16-byte index entries.
// @ 0x00f329e0
cIndexEntry* cSphere::FindEntry(int id)
{
    if (mp19c == mp1a0) {
        g_lastIndex = -1;
        return 0;
    }
    int idx = g_lastIndex;
    if (idx >= 0) {
        if (idx >= (int)(mp1a0 - mp19c) || mp19c[idx].mId != id)
            idx = -1;
    }
    unsigned start = idx + 1;
    int found = -1;
    if (start < (unsigned)(mp1a0 - mp19c)) {
        unsigned i = start;
        do {
            if (mp19c[i].mId == id) {
                found = (int)i;
                break;
            }
            i++;
        } while (i < (unsigned)(mp1a0 - mp19c));
    }
    if (found >= 0)
        goto done;
    {
        unsigned j = 0;
        if (j < start) {
            do {
                if (mp19c[j].mId == id) {
                    found = (int)j;
                    break;
                }
                j++;
            } while (j < start);
        }
    }
done:
    g_lastIndex = found;
    if (found < 0)
        return 0;
    return &mp19c[found];
}

// 0x00f32880: react to a planet-change notification.
// @ 0x00f32880
void cSphere::OnPlanetEvent(cPlanetInfo* info)
{
    int tmp;
    mp198 = g_pGameWorld->mpNode;
    cMsg* msg = LookupMessage(info->mId);
    if (msg == 0)
        return;
    switch (msg->mId) {
    case 0x2b978c46:
        return;
    case 0x2399be55: {
        bool now = info->mRadius < 5.0f;
        uint8_t old = (uint8_t)((info->mFlags >> 3) & 1);
        if (now)
            info->mFlags |= 8;
        else
            info->mFlags &= ~8u;
        if (old != 0 || now)
            m1b9 = 1;
        return;
    }
    case 0x24682294:
        if (!msg->Check())
            return;
        info->mFlags |= 8;
        m1b9 = 1;
        return;
    case 0x438f6347:
        return;
    case 0x476a98c7:
        return;
    }
    cNotifyTarget* target = (cNotifyTarget*)ResolveObject(mp198->Resolve(info));
    cPropHolder* holder;
    if (target)
        holder = target->GetHolder();
    else
        holder = 0;
    bool found = false;
    if (holder != 0 && holder->mpProps != 0) {
        if (GetPropertyTInt(holder->mpProps, 0x49b71de, &tmp))
            found = true;
    }
    uint8_t old = (uint8_t)((info->mFlags >> 3) & 1);
    if (found)
        info->mFlags |= 8;
    else
        info->mFlags &= ~8u;
    if (old != 0 || found)
        m1b9 = 1;
}

// 0x00f337a0: copy-construct a run of 0x38-byte elements, storing the running output iterator.
// @ 0x00f337a0
void __cdecl CopyElems38(Elem38** pOut, const Elem38* first, const Elem38* last, Elem38* dst)
{
    *pOut = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->mA = first->mA;
                dst->mB = first->mB;
                dst->mC = first->mC;
                dst->mD = first->mD;
                dst->mE = first->mE;
                dst->mF = first->mF;
                for (int i = 0; i < 9; i++)
                    dst->mG[i] = first->mG[i];
            }
            first++;
            dst++;
        } while (first != last);
        *pOut = dst;
    }
}
