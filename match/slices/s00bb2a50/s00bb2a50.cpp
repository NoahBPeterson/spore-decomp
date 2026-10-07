// s00bb2a50: Simulator::cStarManager::GenerateSolSystem (ModAPI StarManager.h: "Generates the Sol
// system with the Earth and the rest of the planets; this does not create a new star record, instead
// it modifies the star closest to the (257.34799, 257.34799) position").
//
// mSol is cStarManager+0x148 (ModAPI layout). The function takes the closest yellow (star type 0x10)
// star, makes it mSol, renames it from the locale table 0x2db6dad3 and rebuilds its 12 planet
// records (Earth+Moon, Mercury, Venus, Mars, the asteroid belt, Jupiter+moon, Saturn+moon, Uranus,
// Neptune; names are locale ids 0x03f5a0b0..0x03f5a0bb). Each record is created with
// cPlanetRecord::Create (0x00ba61b0, writes a raw AddRef'ed pointer) and released at the end.
// Callees outside this slice are declared by address.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the cString/string16 temps have no EH frame).

#include "types.h"


namespace eastl {

// eastl::basic_string<wchar_t> (16 bytes: begin, end, capacity, allocator)
struct string16
{
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAllocator;

    string16(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~string16() { DeallocateSelf(); }

    void RangeInitialize(const wchar_t* p);                       // 0x00579a90
    string16& assign(const wchar_t* pBegin, const wchar_t* pEnd); // 0x00423650

    static size_t CharStrlen(const wchar_t* p)
    {
        const wchar_t* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return (size_t)(pCurrent - p);
    }
    string16& operator=(const string16& x)
    {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    string16& operator=(const wchar_t* p)
    {
        return assign(p, p + CharStrlen(p));
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(wchar_t* p)
    {
        if (p)
            delete[] (char*)p;
    }
};

template <typename T> class intrusive_ptr
{
public:
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject)
        {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

}  // namespace eastl

namespace SP {
// SP::cString: localized string (table id, instance id)
class cString
{
public:
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* pPlaceholder);   // 0x006b5770
    ~cString();                                                                     // 0x006b5240
    const wchar_t* GetText();                                                       // 0x006b55c0
    uint32_t pad[6];
};
}

struct ResourceKey
{
    uint32_t instanceID, typeID, groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
void operator delete(void* p, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

namespace SP {
void __cdecl SetCachingType(int type, void* obj);   // 0x006ac040
void __cdecl sub_6ad010(void* obj);                 // 0x006ad010
}

namespace Math {
struct Vector3
{
    float x, y, z;
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
}

namespace Simulator {

typedef uint32_t StarID;
typedef uint32_t PlanetID;

class cEllipticalOrbit { public: uint32_t pad[0x1a]; };

class cPlanetRecord
{
public:
    virtual int AddRef();
    virtual int Release();

    static void Create(PlanetID planetId, cPlanetRecord*& dst);   // 0x00ba61b0

    cPlanetRecord();                                              // 0x00b8e180
    void SetID(PlanetID id);                                      // 0x00b8da80
    void SetModelKey(const ResourceKey& key, int arg);           // 0x00b8dde0
    int GetSomething(uint32_t a, uint32_t b);                     // 0x00b8d8e0

    /* 04h */ uint32_t pad_04;
    /* 08h */ ResourceKey mRecordKey;   // {planet id, 0x05220cb8, 1}
    /* 14h */ uint32_t pad_14;
    /* 18h */ eastl::string16 mName;
    /* 28h */ int mType;
    /* 2Ch */ int mFlags;
    /* 30h */ cEllipticalOrbit mOrbit;
    /* 98h */ uint32_t pad_98[5];
    /* ACh */ int8_t mPlanetRing;
    /* ADh */ char field_AD;
    /* AEh */ uint8_t pad_AE[0x194 - 0xae];
    /* 194h */ int mTechLevel;
};

class cStarRecord
{
public:
    virtual int AddRef();
    virtual int Release();

    void sub_bb9ad0(int v);                        // 0x00bb9ad0
    void sub_bb9b90(const ResourceKey& key);       // 0x00bb9b90
    void sub_a16a30(int v);                        // 0x00a16a30
    void sub_bbac80(int a, int b);                 // 0x00bbac80
    void sub_a16a90(int v);                        // 0x00a16a90
    void sub_bb9c10(int v);                        // 0x00bb9c10

    /* 04h */ uint32_t pad_04[0x17];
    /* 60h */ eastl::string16 mName;
    /* 70h */ StarID mKey;
    /* 74h */ uint32_t pad_74[0xe];
    /* ACh */ uint8_t mPlanetCount;
};

struct StarRequestFilter
{
    /* 00h */ int starTypes;
    /* 04h */ int techLevels;
    /* 08h */ int flags;
    /* 0Ch */ float minDistance;
    /* 10h */ float maxDistance;
    /* 14h */ float field_14;
    /* 18h */ int field_18;
    StarRequestFilter()
        : starTypes(0x1fff), techLevels(0x3f), flags(0), minDistance(-1.0f), maxDistance(-1.0f),
          field_14(-1.0f), field_18(0) {}
};

// 0x0067de60 returns this interface; slot 1 generates a key
class IKeyGenerator
{
public:
    virtual void Slot0();
    virtual void GenerateKey(ResourceKey& dst, uint32_t a, int b, int c, int d, int e);
};
IKeyGenerator* GetKeyGenerator();   // 0x0067de60

// 0x00f48a80 returns this interface; slot 4 takes the planet's value
class IPlanetRegistry
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Add(int value);
};
IPlanetRegistry* GetPlanetRegistry();   // 0x00f48a80

class cStarManager
{
public:
    cStarRecord* FindClosestStar(const Math::Vector3& coords, const StarRequestFilter& filter);   // 0x00bb0e90
    void GenerateEllipticalOrbit(cStarRecord* pStarRecord, cEllipticalOrbit& dst, float minDistance,
                                 float maxDistance, cPlanetRecord* pOrbitAroundPlanet);            // 0x00ba8c40
    void AddPlanet(cPlanetRecord* pPlanet, cStarRecord* pStar, cPlanetRecord* pParent);           // 0x00ba64a0

    void GenerateSolSystem();

    /* 000h */ uint32_t pad_000[0x148 / 4];
    /* 148h */ eastl::intrusive_ptr<cStarRecord> mSol;
};

// @ 0x00ba61b0 (outside this slice; its real body is given here so cl knows it only writes dst,
// the way the LTCG-built original treats it). Not part of the manifest.
__declspec(noinline) void cPlanetRecord::Create(PlanetID planetId, cPlanetRecord*& dst)
{
    dst = new("Simulator/cPlanetRecord", 0, 0, 0, 0) cPlanetRecord();
    dst->SetID(planetId);
    dst->mRecordKey = ResourceKey(planetId, 0x05220cb8, 1);
    dst->AddRef();
    SP::SetCachingType(1, dst);
    SP::sub_6ad010(dst);
}

static inline PlanetID NextPlanetID(cStarRecord* pStar)
{
    return pStar->mKey + (pStar->mPlanetCount << 24);
}

// @ 0x00bb2a50
void cStarManager::GenerateSolSystem()
{
    Math::Vector3 solPosition(257.34799f, 257.34799f, 0.0f);
    {
        StarRequestFilter filter;
        filter.starTypes = 0x10;
        mSol = FindClosestStar(solPosition, filter);
    }
    if (mSol)
    {
        mSol->sub_bb9ad0(1);
        mSol->sub_bb9b90(ResourceKey());
        mSol->mName = eastl::string16(SP::cString(0x2db6dad3, 0x03f5a0b0, 0).GetText());
        mSol->sub_a16a30(0);
        mSol->sub_bbac80(0, 0);
        mSol->sub_a16a90(-1);
        mSol->mPlanetCount = 0;
        mSol->sub_bb9c10(1);

        // Earth
        cPlanetRecord* pEarth = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pEarth);
        mSol->mPlanetCount++;
        pEarth->mName = SP::cString(0x2db6dad3, 0x03f5a0b3, 0).GetText();
        pEarth->mFlags = 0;
        pEarth->mType = 6;
        pEarth->mTechLevel = 1;
        GenerateEllipticalOrbit(mSol, pEarth->mOrbit, 129.0f, 131.0f, 0);
        ResourceKey key;
        GetKeyGenerator()->GenerateKey(key, 0x00b1b104, 0x84, 0, 0xaf, 0);
        pEarth->SetModelKey(key, 0);
        GetPlanetRegistry()->Add(pEarth->GetSomething(0xdf617463, 0x4184af00));
        AddPlanet(pEarth, mSol, 0);

        // Moon
        cPlanetRecord* pMoon = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pMoon);
        mSol->mPlanetCount++;
        pMoon->mName = SP::cString(0x2db6dad3, 0x03f5a0b4, 0).GetText();
        pMoon->mFlags = 4;
        pMoon->mType = 6;
        pMoon->mTechLevel = 1;
        GenerateEllipticalOrbit(mSol, pMoon->mOrbit, 13.0f, 15.0f, pEarth);
        GetKeyGenerator()->GenerateKey(key, 0x00b1b104, 0x84, 0, 0xaf, 0);
        pMoon->SetModelKey(key, 0);
        GetPlanetRegistry()->Add(pMoon->GetSomething(0xba7b60b2, 0x4184af00));
        AddPlanet(pMoon, mSol, pEarth);

        // Mercury
        cPlanetRecord* pMercury = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pMercury);
        mSol->mPlanetCount++;
        pMercury->mName = SP::cString(0x2db6dad3, 0x03f5a0b1, 0).GetText();
        pMercury->mFlags = 0;
        pMercury->mType = 6;
        pMercury->mTechLevel = 1;
        GenerateEllipticalOrbit(mSol, pMercury->mOrbit, 64.0f, 66.0f, 0);
        GetKeyGenerator()->GenerateKey(key, 0x00b1b104, 0x84, 0, 0xaf, 0);
        pMercury->SetModelKey(key, 0);
        GetPlanetRegistry()->Add(pMercury->GetSomething(0x4b18ad98, 0x4184af00));
        AddPlanet(pMercury, mSol, 0);

        // Venus
        cPlanetRecord* pVenus = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pVenus);
        mSol->mPlanetCount++;
        pVenus->mName = SP::cString(0x2db6dad3, 0x03f5a0b2, 0).GetText();
        pVenus->mFlags = 0;
        pVenus->mType = 6;
        pVenus->mTechLevel = 1;
        GenerateEllipticalOrbit(mSol, pVenus->mOrbit, 99.0f, 101.0f, 0);
        GetKeyGenerator()->GenerateKey(key, 0x00b1b104, 0x84, 0, 0xaf, 0);
        pVenus->SetModelKey(key, 0);
        GetPlanetRegistry()->Add(pVenus->GetSomething(0xe6bbd7c8, 0x4184af00));
        AddPlanet(pVenus, mSol, 0);

        // Mars (mFlags left as Create initialized it)
        cPlanetRecord* pMars = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pMars);
        mSol->mPlanetCount++;
        pMars->mName = SP::cString(0x2db6dad3, 0x03f5a0b5, 0).GetText();
        pMars->mType = 6;
        pMars->mTechLevel = 1;
        GenerateEllipticalOrbit(mSol, pMars->mOrbit, 159.0f, 161.0f, 0);
        GetKeyGenerator()->GenerateKey(key, 0x00b1b104, 0x84, 0, 0xaf, 0);
        pMars->SetModelKey(key, 0);
        GetPlanetRegistry()->Add(pMars->GetSomething(0xa776c5b6, 0x4184af00));
        AddPlanet(pMars, mSol, 0);

        // asteroid belt (no name, no model)
        cPlanetRecord* pBelt = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pBelt);
        mSol->mPlanetCount++;
        pBelt->mFlags = 0;
        pBelt->mType = 0;
        pBelt->mTechLevel = 0;
        GenerateEllipticalOrbit(mSol, pBelt->mOrbit, 180.0f, 180.0f, 0);
        AddPlanet(pBelt, mSol, 0);

        // Jupiter
        cPlanetRecord* pJupiter = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pJupiter);
        mSol->mPlanetCount++;
        pJupiter->mName = SP::cString(0x2db6dad3, 0x03f5a0b6, 0).GetText();
        pJupiter->mFlags = 0;
        pJupiter->mType = 1;
        pJupiter->mTechLevel = 0;
        GenerateEllipticalOrbit(mSol, pJupiter->mOrbit, 219.0f, 221.0f, 0);
        pJupiter->field_AD = 0;
        AddPlanet(pJupiter, mSol, 0);

        // moon of Jupiter
        cPlanetRecord* pJupiterMoon = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pJupiterMoon);
        mSol->mPlanetCount++;
        pJupiterMoon->mName = SP::cString(0x2db6dad3, 0x03f5a0b7, 0).GetText();
        pJupiterMoon->mFlags = 4;
        pJupiterMoon->mType = 2;
        pJupiterMoon->mTechLevel = 1;
        GenerateEllipticalOrbit(mSol, pJupiterMoon->mOrbit, 29.0f, 31.0f, pJupiter);
        AddPlanet(pJupiterMoon, mSol, pJupiter);

        // Saturn (rings)
        cPlanetRecord* pSaturn = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pSaturn);
        mSol->mPlanetCount++;
        pSaturn->mName = SP::cString(0x2db6dad3, 0x03f5a0b8, 0).GetText();
        pSaturn->mFlags = 2;
        pSaturn->mType = 1;
        pSaturn->mTechLevel = 0;
        GenerateEllipticalOrbit(mSol, pSaturn->mOrbit, 269.0f, 271.0f, 0);
        pSaturn->field_AD = 4;
        pSaturn->mPlanetRing = 1;
        AddPlanet(pSaturn, mSol, 0);

        // moon of Saturn
        cPlanetRecord* pSaturnMoon = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pSaturnMoon);
        mSol->mPlanetCount++;
        pSaturnMoon->mName = SP::cString(0x2db6dad3, 0x03f5a0b9, 0).GetText();
        pSaturnMoon->mFlags = 4;
        pSaturnMoon->mType = 2;
        pSaturnMoon->mTechLevel = 1;
        GenerateEllipticalOrbit(mSol, pSaturnMoon->mOrbit, 29.0f, 31.0f, pSaturn);
        AddPlanet(pSaturnMoon, mSol, pSaturn);

        // Uranus
        cPlanetRecord* pUranus = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pUranus);
        mSol->mPlanetCount++;
        pUranus->mName = SP::cString(0x2db6dad3, 0x03f5a0ba, 0).GetText();
        pUranus->mFlags = 0;
        pUranus->mType = 1;
        pUranus->mTechLevel = 0;
        GenerateEllipticalOrbit(mSol, pUranus->mOrbit, 319.0f, 321.0f, 0);
        pUranus->field_AD = 3;
        AddPlanet(pUranus, mSol, 0);

        // Neptune
        cPlanetRecord* pNeptune = 0;
        cPlanetRecord::Create(NextPlanetID(mSol), pNeptune);
        mSol->mPlanetCount++;
        pNeptune->mName = SP::cString(0x2db6dad3, 0x03f5a0bb, 0).GetText();
        pNeptune->mFlags = 0;
        pNeptune->mType = 1;
        pNeptune->mTechLevel = 0;
        GenerateEllipticalOrbit(mSol, pNeptune->mOrbit, 398.0f, 400.0f, 0);
        pNeptune->field_AD = 1;
        AddPlanet(pNeptune, mSol, 0);

        pNeptune->Release();
        pUranus->Release();
        pSaturnMoon->Release();
        pSaturn->Release();
        pJupiterMoon->Release();
        pJupiter->Release();
        pBelt->Release();
        pMars->Release();
        pVenus->Release();
        pMercury->Release();
        pMoon->Release();
        pEarth->Release();
    }
}

}  // namespace Simulator
