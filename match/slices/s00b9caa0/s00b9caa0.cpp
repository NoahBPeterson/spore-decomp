// Slice s00b9caa0 -- FUN_00b9caa0: tribe-stage planet setup (2969 bytes, __cdecl, no args).
//
// Loads the tribe-setup property list for the current terrain kind (0x0302a1c9 group), finds the
// player's start position (FUN_00b99070, else the planet's default spot), optionally clears the
// gameplay-marker area around it (list 0x03d7f90a), creates the player tribe there, spawns up to
// `count` start effects, then (when the debug property 0x04d8f5e6 is on) builds up to N paths from
// the start towards the nearest 0x57f09e5e site nouns (path-finding over the planet grid; each
// path is stored in cTribeModeStrategy and stamped into the cube grid), plays the list's effect
// properties, and finally runs FUN_00b9c830 once for the start continent and once for every other
// continent that holds a city site (0x91fe517b / 0xaed08dd4 | 0xd8c67022).
//
// PDB name candidate (caller-scored) SP::cCommandGameplayMarkerTemplate::Execute does not fit
// the body; the function is left unnamed. Sibling of FUN_00b9d820 (civ city setup, slice
// s00b9d820), whose type stubs this file follows.
//
// Built with /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: RAII locals but no EH frame).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void operator delete[](void* p);                                     // 0x00f47380

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------------------
// Math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3 Normalized() const {
        float inv = (float)(1.0f / sqrt(x * x + y * y + z * z + 1e-08f));
        return Vector3(x * inv, y * inv, z * inv);
    }
};

// ---------------------------------------------------------------------------------------
// Ref-counted pointer (AddRef = slot 0, Release = slot 1).
template<class T> struct RefPtr {
    T* mp;
    __forceinline RefPtr() : mp(0) {}
    __forceinline ~RefPtr() { if (mp) mp->Release(); }
    __forceinline void reset() { if (mp) { T* t = mp; mp = 0; t->Release(); } }
    __forceinline T* get() const { return mp; }
    __forceinline T* operator->() const { return mp; }
};

// ---------------------------------------------------------------------------------------
// Properties
struct Property {
    void*    mpData;   // +0x0  (array/pointer storage when mnFlags & 0x30)
    uint32_t pad04;
    int      mnCount;  // +0x8
    uint32_t pad0c;
    uint16_t mnFlags;  // +0x10
    uint16_t mnType;   // +0x12  (0xa = uint32, 0xd = float)

    uint32_t* GetUInt();   // 0x0041ea00
};

__forceinline int PropertyItemCount(const Property* p)
{
    return (p->mnFlags & 0x30) ? p->mnCount : (p->mnType != 0);
}
__forceinline const uint32_t* PropertyItems(const Property* p)
{
    return (const uint32_t*)((p->mnFlags & 0x30) ? p->mpData : (p->mnType ? p : 0));
}

class PropertyList {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);       // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};
typedef RefPtr<PropertyList> PropertyListPtr;

class IPropManager {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);  // 0x2c
};

__forceinline bool GetPropList(IPropManager* pm, uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst)
{
    dst.reset();
    return pm->GetPropertyList(instanceID, groupID, dst);
}

__forceinline bool GetPropertyUInt(PropertyList* list, uint32_t id, uint32_t& value)
{
    Property* p;
    if (list && list->GetProperty(id, p) && p->mnType == 0xa) {
        value = *p->GetUInt();
        return true;
    }
    return false;
}

__forceinline bool GetPropertyFloat(PropertyList* list, uint32_t id, float& value)
{
    Property* p;
    if (list && list->GetProperty(id, p) && p->mnType == 0xd) {
        value = *(const float*)((p->mnFlags & 0x30) ? p->mpData : p);
        return true;
    }
    return false;
}

bool     GetFloatProperty(PropertyList* list, uint32_t id, float* out);                 // 0x0040cf10
float    GetPropertyFloatDefault(PropertyList* list, uint32_t id, float def);           // 0x004e1c70 SP::GetPropertyT<float>
uint32_t GetPropertyIntDefault(PropertyList* list, uint32_t id, uint32_t def);          // 0x00ac8fa0

class cDirectPropertyList {
public:
    bool GetBool(uint32_t id);   // 0x006a25a0
};
extern cDirectPropertyList* g_DebugProperties;   // 0x015fd918

// ---------------------------------------------------------------------------------------
// Game data
#define VPAD4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();

class cSpatialObject {   // cGameData + 0x34
public:
    VPAD4(a) VPAD4(b)
    virtual void c0(); virtual void c1(); virtual void c2();
    virtual const Vector3* GetPosition();                          // 0x2c
    VPAD4(d) VPAD4(e) VPAD4(f) VPAD4(g) VPAD4(h) VPAD4(i) VPAD4(j) VPAD4(k)
    virtual void l0(); virtual void l1(); virtual void l2();
    virtual int AddRef();                                          // 0xbc
    virtual int Release();                                         // 0xc0
};

class cGameData {
public:
    virtual int   AddRef();
    virtual int   Release();
    uint32_t pad04[0xc];
    cSpatialObject mSpatial;   // +0x34
    uint32_t pad38[0x34];
    uint32_t mDefinitionID;    // +0x108
    uint32_t mNounID;          // +0x10c
    uint32_t mSubType;         // +0x110
};

struct GameDataPtrVector {
    cGameData** mpBegin;
    cGameData** mpEnd;
    cGameData** mpCapacity;
    const char* mpAllocName;
};

struct tGameDataVector {
    bool              mbDirty;   // +0x0
    GameDataPtrVector mData;     // +0x4
};

// eastl::intrusive_ptr<cSpatialObject>
struct SpatialPtr {
    cSpatialObject* mp;
    __forceinline SpatialPtr(cSpatialObject* p) : mp(p) { if (mp) mp->AddRef(); }
    __forceinline SpatialPtr(const SpatialPtr& x) : mp(x.mp) { if (mp) mp->AddRef(); }
    __forceinline ~SpatialPtr() { if (mp) mp->Release(); }
    __forceinline cSpatialObject* operator->() const { return mp; }
};

// eastl::vector<intrusive_ptr<cSpatialObject>>
struct SpatialPtrVector {
    SpatialPtr* mpBegin;
    SpatialPtr* mpEnd;
    SpatialPtr* mpCapacity;
    uint32_t    mAllocator;

    __forceinline SpatialPtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~SpatialPtrVector()
    {
        for (SpatialPtr* p = mpBegin; p < mpEnd; ++p)
            p->~SpatialPtr();
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);                                    // 0x00d01790
    void DoInsertValue(SpatialPtr* pos, const SpatialPtr& value);  // 0x00bab900
    __forceinline void push_back(const SpatialPtr& value)
    {
        if (mpEnd < mpCapacity) {
            SpatialPtr* p = mpEnd++;
            if (p) new(p) SpatialPtr(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

// Sorts sites by distance to the start position (comparator held by value).
struct DistanceLess {
    Vector3 mPos;
    __forceinline DistanceLess(const Vector3& p) : mPos(p) {}
};
void FUN_00b95fe0(SpatialPtr* first, SpatialPtr* middle, SpatialPtr* last, DistanceLess compare);  // partial_sort

// Planet-grid path node returned by the path finder (60 bytes, position first).
struct GridNode {
    Vector3  mPos;
    uint32_t pad[12];
};

struct GridNodeVector {
    GridNode* mpBegin;
    GridNode* mpEnd;
    GridNode* mpCapacity;
    uint32_t  mAllocator;

    __forceinline GridNodeVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~GridNodeVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    GridNode* erase(GridNode* first, GridNode* last);   // 0x00ac4570
    __forceinline void clear() { erase(mpBegin, mpEnd); }
};

struct Vector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;

    void reserve(int n);                                     // 0x00473890
    void DoInsertValue(Vector3* pos, const Vector3& value);  // 0x004b5ad0
    __forceinline void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity) {
            Vector3* p = mpEnd++;
            if (p) new(p) Vector3(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

struct TribePath {   // 20 bytes
    Vector3Vector mPoints;
    uint32_t      mField10;
};
TribePath* FUN_00b969a0(TribePath* first, TribePath* last, TribePath* dest);   // eastl::copy

struct TribePathVector {
    TribePath* mpBegin;
    TribePath* mpEnd;
    TribePath* mpCapacity;

    void DestroyRange(TribePath* first, TribePath* last);   // 0x01023030
    void reserve(uint32_t n);                               // 0x00c77a00
    void push_back();                                       // 0x00b89770
    __forceinline TribePath* erase(TribePath* first, TribePath* last)
    {
        TribePath* const pNewEnd = FUN_00b969a0(last, mpEnd, first);
        DestroyRange(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void clear() { erase(mpBegin, mpEnd); }
    __forceinline TribePath& back() { return mpEnd[-1]; }
};

class cTribeModeStrategy {
public:
    uint32_t        pad00[0xb];
    TribePathVector mPaths;    // +0x2c
    static cTribeModeStrategy* Instance();   // 0x00cd40b0
};

void FUN_00b922c0(TribePath* path, float halfWidth);   // stamp path into the planet grid

// ---------------------------------------------------------------------------------------
// eastl::fixed_set<uint32_t, 8> (rbtree + fixed_node_allocator with overflow)
namespace eastl {
struct Link { Link* mpNext; };

struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    __forceinline fixed_pool_base() : mpHead(0) {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment,
              uint32_t alignmentOffset);   // 0x00921260
};

struct fixed_pool_with_overflow : fixed_pool_base {
    void*    mpPoolBegin;   // +8
    void*    mpPoolEnd;     // +0xc
    uint32_t mnNodeSize;    // +0x10
    __forceinline fixed_pool_with_overflow(void* pMemory, uint32_t memorySize, uint32_t nodeSize,
                                           uint32_t alignment, uint32_t alignmentOffset)
    {
        init(pMemory, memorySize, nodeSize, alignment, alignmentOffset);
        mpPoolBegin = pMemory;
        mpPoolEnd = (char*)pMemory + memorySize;
        mnNodeSize = nodeSize;
    }
};

struct fixed_node_allocator {
    fixed_pool_with_overflow mPool;
    __forceinline fixed_node_allocator(void* pNodeBuffer) : mPool(pNodeBuffer, 0xa0, 0x14, 4, 0) {}
    __forceinline fixed_node_allocator(const fixed_node_allocator& x) : mPool(x.mPool.mpHead, 0xa0, 0x14, 4, 0) {}
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};
struct rbtree_node : rbtree_node_base {
    uint32_t mValue;
};

struct true_type {};

struct insert_result {
    rbtree_node* first;
    bool         second;
    insert_result() {}
};

struct less { };

struct rbtree_uint {
    less                 mCompare;     // +0x0
    rbtree_node_base     mAnchor;      // +0x4
    uint32_t             mnSize;       // +0x14
    fixed_node_allocator mAllocator;   // +0x18

    __forceinline rbtree_uint(const fixed_node_allocator& allocator)
        : mAnchor(), mnSize(0), mAllocator(allocator) { reset(); }
    __forceinline ~rbtree_uint() { DoNukeSubtree((rbtree_node*)mAnchor.mpNodeParent); }
    __forceinline void reset()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(rbtree_node* pNode);                                           // 0x00d3b370
    insert_result DoInsertValue(const uint32_t& value, true_type);                    // 0x00b971b0
    __forceinline insert_result insert(const uint32_t& value) { return DoInsertValue(value, true_type()); }
    __forceinline rbtree_node_base* end() { return &mAnchor; }
    __forceinline rbtree_node_base* find(const uint32_t& key)
    {
        rbtree_node_base* pRangeEnd = &mAnchor;
        rbtree_node* pCurrent = (rbtree_node*)mAnchor.mpNodeParent;
        while (pCurrent) {
            if (!(pCurrent->mValue < key)) {
                pRangeEnd = pCurrent;
                pCurrent = (rbtree_node*)pCurrent->mpNodeLeft;
            } else {
                pCurrent = (rbtree_node*)pCurrent->mpNodeRight;
            }
        }
        if (pRangeEnd != &mAnchor && !(key < ((rbtree_node*)pRangeEnd)->mValue))
            return pRangeEnd;
        return &mAnchor;
    }
};

struct fixed_set_uint8 : rbtree_uint {
    uint32_t mBuffer[0x28];            // +0x2c (8 nodes of 0x14 bytes)
    __forceinline fixed_set_uint8() : rbtree_uint(fixed_node_allocator(mBuffer)) {}
};

template <class T> __forceinline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}  // namespace eastl

// ---------------------------------------------------------------------------------------
// Managers
struct cTerrainInfo {
    int FUN_00c75420();      // terrain kind
};

class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* create, void* f2, void* filter, void* f4, uint32_t typeID);  // 0x00b21340
    cTerrainInfo*    GetCurrentTerrainSphere();                                                          // 0x00f67d90
};

class cPlanetModel {
public:
    Vector3 FUN_00b81720();                                // default start position
    Vector3 DirectionToSurfacePosition(const Vector3& dir);   // 0x00b815a0
    uint32_t GetContinent(const Vector3& pos);             // 0x00b88590
};

struct cCubeGrid {
    void FUN_00b90ea0(const Vector3* pos, float a, float b, float c);   // clear marker area
};
extern cCubeGrid g_PlanetGrid;   // 0x0156c060

struct cGameModeState {   // 0x01581208
    uint32_t Get178();    // 0x0104c100
    uint32_t Get17c();    // 0x0104bd80
};
extern cGameModeState g_GameModeState;

class cPathFinder {
public:
    bool FUN_00ac6960(void* grid, const Vector3& start, const Vector3& end, GridNodeVector* out,
                      float a, float b);
};
extern char g_1565b18[];   // path-finder grid object

extern const uint32_t g_TribeSetupLists[];   // 0x0146598c, indexed by terrain kind + 3

cGameNounManager* NounManager();       // 0x00b3d300
IPropManager*     PropertyManager();   // 0x0067de30
cPlanetModel*     PlanetModel();       // 0x00b3d350
cPathFinder*      FUN_00b3d290();
bool FUN_00b99070(Vector3* pos, bool* flag);
void FUN_00b992c0();
void FUN_00c99dc0(const Vector3* pos, uint32_t a, uint32_t b, int c);   // CreatePlayerTribe
int  FUN_00b9b090(const Vector3* pos, const uint32_t* ids, int count, uint32_t a, int b);
void FUN_00b9aa10(const Vector3* pos, const uint32_t* ids, int count, uint32_t groupID);
void FUN_00b9c830(PropertyList* list, const Vector3* pos, float radiusSq, uint32_t a, uint32_t b);

// GetGameDataVector callbacks
void FUN_00cd7d10();
void FUN_00d3d420();
void FUN_00ace070();
void FUN_00b1e500();

// @ 0x00b9caa0
void FUN_00b9caa0(void)
{
    NounManager();
    IPropManager* pm = PropertyManager();
    PropertyListPtr list;
    uint32_t listID = g_TribeSetupLists[NounManager()->GetCurrentTerrainSphere()->FUN_00c75420() + 3];
    if (GetPropList(pm, listID, 0x0302a1c9, list)) {
    cPlanetModel* planet = PlanetModel();
    Vector3 pos;
    bool flag;
    bool found = FUN_00b99070(&pos, &flag);
    FUN_00b992c0();
    if (found) {
        PropertyListPtr markers;
        if (pm->GetPropertyList(0x03d7f90a, 0x0302a1c9, markers)) {
            float a = 0.0f;
            float b = 0.0f;
            float c = 0.0f;
            GetFloatProperty(markers.get(), 0x24a02634, &a);
            GetFloatProperty(markers.get(), 0xcbb8d102, &b);
            GetFloatProperty(markers.get(), 0x561c98ac, &c);
            g_PlanetGrid.FUN_00b90ea0(&pos, a, b, c);
            if (markers->HasProperty(0xbb64b481)) {
                Property* p = markers->GetPropertyObject(0xbb64b481);
                FUN_00b9aa10(&pos, PropertyItems(p), PropertyItemCount(p), 0x03d7f90a);
            }
        }
    } else {
        pos = planet->FUN_00b81720();
    }

    FUN_00c99dc0(&pos, g_GameModeState.Get17c(), g_GameModeState.Get178(), 0);

    uint32_t placed = 0;
    uint32_t effects[4] = { 0xe45c5bbb, 0x631674df, 0xf2659f20, 0x99945d8d };
    uint32_t count = 6;
    GetPropertyUInt(list.get(), 0xa6df0147, count);
    uint32_t idx = 0;
    while (placed < count) {
        if (idx >= 4)
            break;
        uint32_t id = effects[idx];
        int n = FUN_00b9b090(&pos, &id, 1, id, 1);
        if (n == 0)
            idx++;
        else
            placed += n;
    }

    bool buildPaths = g_DebugProperties->GetBool(0x04d8f5e6);
    uint32_t maxPaths = GetPropertyIntDefault(list.get(), 0xd914eed2, 3);
    float halfWidth = GetPropertyFloatDefault(list.get(), 0x1d92aa9d, 1.0f) * 0.5f;
    float range = GetPropertyFloatDefault(list.get(), 0x7f8d0f30, 250.0f);
    float rangeSq = range * range;
    float step = GetPropertyFloatDefault(list.get(), 0x78044a34, 30.0f);
    if (buildPaths && maxPaths > 0) {
        SpatialPtrVector sites;
        sites.reserve(placed);
        GameDataPtrVector& data = NounManager()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                        (void*)FUN_00ace070, (void*)FUN_00b1e500,
                                                        0x036be27e)->mData;
        for (cGameData** it = data.mpBegin, **itEnd = data.mpEnd; it != itEnd; ++it) {
            cGameData* gd = *it;
            if (gd->mDefinitionID == 0x57f09e5e)
                sites.push_back(SpatialPtr(&gd->mSpatial));
        }

        uint32_t numSites = sites.size();
        uint32_t n = eastl::min(numSites, maxPaths);
        FUN_00b95fe0(sites.mpBegin, sites.mpBegin + n, sites.mpEnd, DistanceLess(pos));

        cTribeModeStrategy* strategy = cTribeModeStrategy::Instance();
        strategy->mPaths.clear();
        strategy->mPaths.reserve(n);

        GridNodeVector gridPath;
        for (uint32_t i = 0; i < n; i++) {
            const Vector3* p = sites.mpBegin[i]->GetPosition();
            Vector3 d = pos - *p;
            if (!((d.x * d.x + d.z * d.z) + d.y * d.y < rangeSq))
                break;
            gridPath.clear();
            Vector3 off = (*p - pos).Normalized() * step;
            Vector3 start = planet->DirectionToSurfacePosition(pos + off);
            Vector3 end = planet->DirectionToSurfacePosition(*p - off);
            if (FUN_00b3d290()->FUN_00ac6960(g_1565b18, start, end, &gridPath, 0.0f, 1.0f)) {
                strategy->mPaths.push_back();
                TribePath& path = strategy->mPaths.back();
                path.mPoints.reserve(gridPath.size() + 1);
                path.mPoints.push_back(start);
                for (GridNode* g = gridPath.mpBegin, *gEnd = gridPath.mpEnd; g != gEnd; ++g)
                    path.mPoints.push_back(planet->DirectionToSurfacePosition(g->mPos));
                FUN_00b922c0(&path, halfWidth);
            }
        }
    }

    if (list->HasProperty(0xa1d6248e)) {
        Property* p = list->GetPropertyObject(0xa1d6248e);
        FUN_00b9aa10(&pos, PropertyItems(p), PropertyItemCount(p), listID);
    }
    if (list->HasProperty(0xf7084224)) {
        Property* p = list->GetPropertyObject(0xf7084224);
        FUN_00b9b090(&pos, PropertyItems(p), PropertyItemCount(p), 0, 1);
    }

    float radiusSq = 40000.0f;
    float radius;
    if (GetPropertyFloat(list.get(), 0xf64f11be, radius))
        radiusSq = radius * radius;
    FUN_00b9c830(list.get(), &pos, radiusSq, 0x204e6edd, 0x73cc6df5);

    eastl::fixed_set_uint8 continents;
    uint32_t continent = planet->GetContinent(pos);
    continents.insert(continent);
    GameDataPtrVector& sites = NounManager()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                                (void*)FUN_00ace070, (void*)FUN_00b1e500,
                                                                0x036be27e)->mData;
    for (cGameData** it = sites.mpBegin, **itEnd = sites.mpEnd; it != itEnd; ++it) {
        cGameData* gd = *it;
        if (gd->mDefinitionID == 0x91fe517b &&
            (gd->mSubType == 0xaed08dd4 || gd->mSubType == 0xd8c67022)) {
            const Vector3* p = gd->mSpatial.GetPosition();
            continent = planet->GetContinent(*p);
            if (continents.find(continent) == continents.end()) {
                continents.insert(continent);
                FUN_00b9c830(list.get(), p, 3.402823466e+38F, 0x84f2454a, 0x242811c2);
            }
        }
    }
    }
}
