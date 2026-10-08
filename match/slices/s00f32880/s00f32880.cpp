// Slice s00f32880: SP::cTerrainSphere::SetPlayerColorIDs-like (0x00f32d10, 2155 bytes).
// Pushes the sphere's terrain/colour/ID arrays and scalars into the property bus at this+0xc
// (vtable slot 5 = SetProperty(id, Variant*), slot 6 = RemoveProperty(id)).
#include "types.h"

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
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void SetProperty(uint32_t id, Variant* v);   // slot 5
    virtual void RemoveProperty(uint32_t id);            // slot 6
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

struct cSphere {
    char pad0[0xc];
    IPropertyBus* mpBus;     // +0x0c
    char pad_bus[4];
    Vec<E12> v14;
    char pad1[0x28 - 0x1c];
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
    char mC8[12]; char mD4[12]; char mE0[12];
    int mEC; int mF0; char mF4[12];
    char m100[4]; char m104; char pad7[3];
    Vec<E12> v108;
    char pad8[0x11c - 0x110];
    Vec<uint32_t> v11c;
    char pad9[0x130 - 0x124];
    char m130[12]; char m13c[12]; char m148[12]; char m154[12];
    int m160;
    char pad10[0x18d - 0x164];
    char m18d;

    void Publish();
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
