// Slice s00ba0770 -- planet "spot" setup (cdecl, called with the planet-type IDs 0x1654c01..05).
// Clears the global spot list and the continent multimap, collects one spot per placed object
// whose property list has radius values (0x254cf89 / 0x4ee9f45), reads the per-planet-type
// spot tuning property list (group 0x302a1c9), feeds every spot, every flagged planet-record
// entry and (optionally) every valid sphere of the B3D440 manager into the global grid object
// at 0x156c060, and finally (bFillRegions) flood-fills the 6 x 128 x 128 face grid into regions.
// Built /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no EH frame for the property-list smart pointer).
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

inline void* operator new(unsigned, void* p) throw() { return p; }

struct Vector3 { float x, y, z; };

// ---- property lists ------------------------------------------------------------------
struct Property {
    void*  mpData;      // +0x00 (value inline, or pointer when flags & 0x30)
    u32    pad04[3];
    u16    mnFlags;     // +0x10
    u16    mnType;      // +0x12
    bool* GetValueBool();   // 0x41e920

    void* Value() { return (mnFlags & 0x30) ? mpData : (void*)this; }
};
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5();
    virtual void p6(); virtual void p7(); virtual void p8();
    virtual bool GetProperty(u32 id, Property*& out);   // 0x24
};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList** operator&() {
        if (mpObject) {
            PropertyList* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    PropertyList* operator->() const { return mpObject; }
    operator PropertyList*() const { return mpObject; }
};
struct cPropertyManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10();
    virtual bool GetPropertyList(u32 instanceID, u32 groupID, PropertyList** dst);   // 0x2c
};

inline bool GetFloat(PropertyList* pl, u32 id, float& out) {
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 0xd) {
        out = *(float*)p->Value();
        return true;
    }
    return false;
}
inline bool GetBool(PropertyList* pl, u32 id, bool& out) {
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 1) {
        out = *(bool*)p->Value();
        return true;
    }
    return false;
}

// ---- planet model --------------------------------------------------------------------
struct ResourceKey { u32 instanceID, typeID, groupID; };
struct cPlacedObject { u32 pad0; Vector3 mPosition; u32 pad10[10]; };   // size 0x38
struct cPlanetObjects {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual int GetSeed();                                                  // 0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44();
    virtual int GetObjects(const ResourceKey** keys, const cPlacedObject** objects);   // 0xb4
};
struct cSpot {                 // size 0x34
    Vector3 mPosition;         // +0x00
    float   mRadius;           // +0x0c
    bool    mbClustered;       // +0x10
    u32     mContinent;        // +0x14
    u32     pad18[7];
};
struct cPlanetModel {
    u32 pad00[9];
    cPlanetObjects* mpObjects;          // +0x24
    u32 GetContinent(const cSpot* spot);   // 0xb88590
};

struct cTerrainSphere { int GetType(); };                  // 0xc75420
struct cTerrainSphereOwner { cTerrainSphere* GetCurrentTerrainSphere(); };   // 0xf67d90

struct cRecordEntry { u32 pad0; Vector3 mPosition; u32 pad10[6]; u8 mFlags; u8 pad29[3]; };   // 0x2c
template <class T> struct Vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    u32 mAllocator;
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
};
struct cPlanetRecord {
    u32 pad[0x134 / 4];
    Vec<cRecordEntry> mEntries;   // +0x134
};

struct Sphere { Vector3 mCenter; float mRadius; };
struct cSphereOwner { u32 pad[2]; Sphere mSphere; u32 rest[(0x19a8 - 0x18) / 4]; };   // 0x19a8
struct cSphereManager {
    u32 pad[0x1e5f0 / 4];
    Vec<cSphereOwner> mOwners;   // +0x1e5f0
};

namespace SP {
cPlanetModel* __cdecl PlanetModel();                       // 0xb3d350
cPropertyManager* __cdecl PropertyManager();               // 0x67de30
cTerrainSphereOwner* __cdecl TerrainSphereOwner();         // 0xb3d300
cSphereManager* __cdecl SphereManager();                   // 0xb3d440
namespace cSPLivingUniverse { cPlanetRecord* __cdecl GetActivePlanetRecord(); }   // 0x10212a0
}

inline bool IsValid(float f) {
    u32 u = *(u32*)&f;
    return (u & 0x7fffffff) == 0 || ((u - 0x800000) & 0x7f800000) < 0x7f000000;
}

template <class T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }

// ---- global spot vector (eastl::vector<cSpot> at 0x16888ec) ---------------------------
cSpot* __cdecl CopySpots(cSpot* first, cSpot* last, cSpot* dest);   // 0xb97540 (eastl::copy)
struct SpotVector {
    cSpot* mpBegin;
    cSpot* mpEnd;
    cSpot* mpCapacity;
    void DestroyRange(cSpot* first, cSpot* last);   // 0xb970f0
    void push_back();                               // 0xba06f0
    cSpot& back() { return *(mpEnd - 1); }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSpot* erase(cSpot* first, cSpot* last) {
        cSpot* const position = CopySpots(last, mpEnd, first);
        DestroyRange(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

// ---- continent multimap (eastl::multimap<u32,int> at 0x156c040) -----------------------
struct false_type {};
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};
struct ContinentPair {
    u32 first;
    int second;
    ContinentPair(const u32& a, const int& b) : first(a), second(b) {}
};
struct rbtree_iterator {
    rbtree_node_base* mpNode;
    rbtree_iterator() : mpNode(0) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
};
struct ContinentMap {
    u32 mCompare;
    rbtree_node_base mAnchor;
    u32 mnSize;
    void DoNukeSubtree(rbtree_node_base* pNode);                                // 0x9a9600
    rbtree_iterator DoInsertValue(const ContinentPair& value, false_type);       // 0xb96180
    void reset() {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void clear() { DoNukeSubtree(mAnchor.mpNodeParent); reset(); }
    rbtree_iterator insert(const ContinentPair& value) { return DoInsertValue(value, false_type()); }
};

// ---- the spot grid (static object at 0x156c060) ---------------------------------------
struct cRegion {               // size 0x18
    u8    mbDone;              // +0x00
    char  mFace;               // +0x01
    u16   pad02[3];
    short mEndX;               // +0x08
    u16   pad0a[7];
};
struct cCell { cRegion* mpRegion; u32 pad[2]; };   // size 0xc
struct GridCoord { int x, y, face; };
struct RegionVector {
    const cRegion** mpBegin;
    const cRegion** mpEnd;
    const cRegion** mpCapacity;
    void DoInsertValue(const cRegion** position, const cRegion* const& value);   // 0xb96600
    void push_back(const cRegion* const& value) {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) const cRegion*(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct cSpotGrid {
    u32 pad00[2];
    RegionVector mRegionList;   // +0x08
    u32 pad14[4];
    int mnSize;                 // +0x24
    u32 pad28[3];
    cCell* mpCells;             // +0x34
    u32 pad38[6];
    int mnRegions;              // +0x50
    cRegion* mpRegions;         // +0x54

    void Read(int seed, int count, float spacing);                        // 0xb9c630
    void AddSpot(const Vector3* pos, float radius, int kind);              // 0xb91320
    void AddRings(const Vector3* pos, float r0, float r1, float r2);       // 0xb90ea0
    bool StartRegion(int index, int face, int x, int y);                   // 0xb907f0
    void FillRegion(GridCoord* coord, cRegion* region);                    // 0xb91810
    void FinishRegions();                                                  // 0xb983b0

    cRegion* AllocRegion() {
        cRegion* region = &mpRegions[mnRegions++];
        region->mbDone = 0;
        return region;
    }
};

extern SpotVector   g_Spots;           // 0x16888ec
extern ContinentMap g_ContinentSpots;  // 0x156c040
extern cSpotGrid    g_SpotGrid;        // 0x156c060
static const float kEpsilon = 1.5258789e-05f;
extern bool         g_bFillRegions;    // 0x168888c
extern const u32    kSpotPropertyIDs[5][3];   // 0x146598c

void __cdecl ResetSpotState();         // 0xb95500

// @ 0x00ba0770
void __cdecl SetupPlanetSpots(u32 planetType, bool bFillRegions)
{
    ResetSpotState();
    g_Spots.clear();
    g_ContinentSpots.clear();

    cPlanetModel* planet = SP::PlanetModel();
    if (planet) {
        cPropertyManager* propManager = SP::PropertyManager();
        const ResourceKey* keys = 0;
        const cPlacedObject* objects = 0;
        cPlanetObjects* planetObjects = planet->mpObjects;
        int seed = planetObjects->GetSeed();
        int count = planetObjects->GetObjects(&keys, &objects);
        int numClustered = 0;
        for (int i = 0; i < count; i++) {
            PropertyListPtr propList;
            if (propManager->GetPropertyList(keys[i].instanceID, keys[i].groupID, &propList)) {
                float radius0 = 0.0f;
                bool has0 = GetFloat(propList, 0x254cf89, radius0);
                float radius1 = 0.0f;
                bool has1 = GetFloat(propList, 0x4ee9f45, radius1);
                if (!has0 && !has1)
                    continue;
                bool bClustered = false;
                Property* prop;
                if (propList && propList->GetProperty(0x3f6d22a, prop) && prop->mnType == 1)
                    bClustered = *prop->GetValueBool();
                const float& radius = max_(radius0, radius1);
                g_Spots.push_back();
                cSpot& spot = g_Spots.back();
                spot.mPosition = objects[i].mPosition;
                spot.mRadius = radius;
                spot.mbClustered = bClustered;
                spot.mContinent = planet->GetContinent(&spot);
                if (bClustered) {
                    g_ContinentSpots.insert(ContinentPair(spot.mContinent, numClustered++));
                }
            }
        }

        float spacing = 32.0f;
        float ringA0 = 0.0f;
        float ringA1 = 0.0f;
        float ringA2 = 0.0f;
        float minRadius = 56.0f;
        bool bSphereRings = false;
        float ringB0 = 0.0f;
        float ringB1 = 0.0f;
        float ringB2 = 0.0f;
        g_bFillRegions = bFillRegions;

        u32 tuningID;
        if (planetType >= 0x1654c01 && planetType <= 0x1654c05)
            tuningID = kSpotPropertyIDs[planetType - 0x1654c01]
                [SP::TerrainSphereOwner()->GetCurrentTerrainSphere()->GetType()];
        else
            tuningID = 0;

        PropertyListPtr tuning;
        cPropertyManager* pm = SP::PropertyManager();
        switch (planetType) {
        case 0x1654c01:
            pm->GetPropertyList(tuningID, 0x302a1c9, &tuning);
            break;
        case 0x1654c02:
            ringA0 = 16.0f;
            ringA1 = 32.0f;
            ringA2 = 96.0f;
            bSphereRings = true;
            ringB1 = 16.0f;
            pm->GetPropertyList(tuningID, 0x302a1c9, &tuning);
            break;
        case 0x1654c04:
        case 0x1654c05:
            ringA0 = 16.0f;
            ringA1 = 32.0f;
            ringA2 = 96.0f;
            pm->GetPropertyList(tuningID, 0x302a1c9, &tuning);
            spacing = 90.0f;
            break;
        }

        GetFloat(tuning, 0xb0111ed1, ringA0);
        GetFloat(tuning, 0x87ddd867, ringA1);
        GetFloat(tuning, 0x2f508b9, ringA2);
        GetFloat(tuning, 0x231eb8cd, minRadius);
        GetBool(tuning, 0x4cfe50d0, bSphereRings);
        GetFloat(tuning, 0xa63177bd, ringB0);
        GetFloat(tuning, 0xea319a1b, ringB1);
        GetFloat(tuning, 0x15d94435, ringB2);
        GetFloat(tuning, 0xfbc81b2, spacing);

        g_SpotGrid.Read(seed, 0x80, spacing);

        int numSpots = g_Spots.size();
        for (int i = 0; i < numSpots; i++) {
            cSpot& spot = g_Spots.mpBegin[i];
            float radius = spot.mRadius;
            if (spot.mbClustered)
                radius = max_(spot.mRadius, minRadius);
            g_SpotGrid.AddSpot(&spot.mPosition, radius, 4);
            if (ringA0 > kEpsilon || ringA1 > kEpsilon || ringA2 > kEpsilon)
                g_SpotGrid.AddRings(&spot.mPosition,
                                    ringA0 > kEpsilon ? radius + ringA0 : 0.0f,
                                    ringA1 > kEpsilon ? radius + ringA1 : 0.0f,
                                    ringA2 > kEpsilon ? radius + ringA2 : 0.0f);
        }

        cPlanetRecord* record = SP::cSPLivingUniverse::GetActivePlanetRecord();
        Vec<cRecordEntry>& entries = record->mEntries;
        for (cRecordEntry* it = entries.begin(), *end = entries.end(); it != end; ++it) {
            if (it->mFlags & 0x80)
                g_SpotGrid.AddSpot(&it->mPosition, minRadius, 4);
        }

        if (bSphereRings && (ringB0 > kEpsilon || ringB1 > kEpsilon || ringB2 > kEpsilon)) {
            cSphereManager* spheres = SP::SphereManager();
            Vec<cSphereOwner>& owners = spheres->mOwners;
            for (cSphereOwner* it = owners.begin(), *end = owners.end(); it != end; ++it) {
                Sphere& s = it->mSphere;
                if (IsValid(s.mCenter.x) && IsValid(s.mCenter.y) && IsValid(s.mCenter.z) &&
                    IsValid(s.mRadius)) {
                    float r = s.mRadius;
                    g_SpotGrid.AddRings(&s.mCenter,
                                        ringB0 > kEpsilon ? r + ringB0 : 0.0f,
                                        ringB1 > kEpsilon ? r + ringB1 : 0.0f,
                                        ringB2 > kEpsilon ? r + ringB2 : 0.0f);
                }
            }
        }

        if (g_bFillRegions) {
            GridCoord coord;
            for (int face = 0; face < 6; face++) {
                coord.face = face;
                for (int y = 0; y < 0x80; y++) {
                    coord.y = y;
                    for (int x = 0; x < 0x80; ) {
                        int index = (face * g_SpotGrid.mnSize + y) * g_SpotGrid.mnSize + x;
                        cRegion* region = g_SpotGrid.mpCells[index].mpRegion;
                        coord.x = x;
                        x++;
                        if (!region) {
                            if (!g_SpotGrid.StartRegion(index, face, x, y))
                                continue;
                            do {
                                cRegion* newRegion = g_SpotGrid.AllocRegion();
                                g_SpotGrid.mRegionList.push_back(newRegion);
                                newRegion->mbDone = 0;
                                region = newRegion;
                                g_SpotGrid.FillRegion(&coord, region);
                            } while (!g_SpotGrid.mpCells[index].mpRegion);
                        }
                        if (face == region->mFace)
                            x = region->mEndX + 1;
                    }
                }
            }
            g_SpotGrid.FinishRegions();
        }
    }
}
