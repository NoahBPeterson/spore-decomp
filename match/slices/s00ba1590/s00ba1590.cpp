// Slice s00ba1590 -- FUN_00ba1590: creature-stage planet setup (1737 bytes, __cdecl, no args).
//
// Sibling of FUN_00b9caa0 (tribe stage, slice s00b9caa0), whose type stubs this file follows.
// Loads the creature-setup property list for the current terrain kind (0x0302a1c9 group), then
// for every gameplay marker (0x36be27e) with definition 0xc012ae1f (state 4, flag 0) walks the
// linked chain of markers (+0x19c), path-finds between consecutive markers over the planet grid
// and appends the grid nodes to one creature "route" (cCreatureModeStrategy +0x4c) whose points
// are projected onto the surface and stamped into the grid (FUN_00b922c0).  Afterwards it spawns
// the species archetype's spawn definitions (0xdb9bfc2c) for every city-site noun (0x91fe517b)
// on the avatar's continent, plays the list's effect properties and runs FUN_00b9c830.
//
// Built with /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: RAII locals but no EH frame).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void operator delete[](void* p);                                            // 0x00f47380
void* operator new(size_t, const char*, int, unsigned, const char*, int);   // 0x00f473a0

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
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
    uint16_t mnType;   // +0x12
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

float GetPropertyFloatDefault(PropertyList* list, uint32_t id, float def);              // 0x004e1c70 SP::GetPropertyT<float>
bool  GetPropertyAsUint32Array(PropertyList* list, uint32_t id, int* count, uint32_t** out);   // 0x006a0840

// ---------------------------------------------------------------------------------------
// Game data
#define VPAD4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();

class cSpatialObject {   // cGameData + 0x34
public:
    VPAD4(a) VPAD4(b)
    virtual void c0(); virtual void c1(); virtual void c2();
    virtual const Vector3* GetPosition();                          // 0x2c
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
    uint32_t pad114[2];
    int      mFlag11c;         // +0x11c
    float    mWidth;           // +0x120
    int      mState;           // +0x124
    uint32_t pad128[(0x19c - 0x128) / 4];
    cGameData* mpNext;         // +0x19c
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

// eastl::intrusive_ptr<cGameData>
struct GameDataPtr {
    cGameData* mp;
    __forceinline ~GameDataPtr() { if (mp) mp->Release(); }
};

// Planet-grid path node (60 bytes, position first).
struct GridNode {
    Vector3  mPos;
    float    mW;            // +0xc
    uint32_t m10;           // +0x10
    uint32_t pad14[9];
    uint8_t  m3c;           // +0x38
    uint8_t  pad39[3];
    GridNode() {}
    GridNode(const GridNode& o);                                  // 0x00ac1ff0
};

struct GridNodeVector {
    GridNode* mpBegin;
    GridNode* mpEnd;
    GridNode* mpCapacity;
    uint32_t  mAllocator;

    __forceinline GridNodeVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~GridNodeVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
};

// eastl::fixed_vector<GridNode, 32>
struct FixedGridVector {
    GridNode* mpBegin;
    GridNode* mpEnd;
    GridNode* mpCapacity;
    uint32_t  mAllocatorPad[2];
    uint32_t  mOverflow;              // checked by the dtor through mpBegin[-1]
    GridNode  mBuffer[32];

    __forceinline FixedGridVector()
    {
        mOverflow = 0;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 32;
    }
    __forceinline ~FixedGridVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
    void DoInsertValue(GridNode* pos, const GridNode& value);                          // 0x00ac45e0
    void FUN_00b96360(GridNode* where, GridNode* first, GridNode* last, uint32_t continent);   // append path nodes
    __forceinline void push_back(const GridNode& value)
    {
        if (mpEnd < mpCapacity) {
            GridNode* p = mpEnd++;
            if (p) new(p) GridNode(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
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

// One creature route (0x18 bytes): width followed by the point path.
struct CreatureRoute {
    float     mWidth;
    TribePath mPath;
};

struct CreatureRouteVector {
    CreatureRoute* mpBegin;
    CreatureRoute* mpEnd;
    CreatureRoute* mpCapacity;

    void clear();                // 0x00ba06a0
    void push_back();            // 0x00ba0640
    __forceinline CreatureRoute& back() { return mpEnd[-1]; }
};

class cCreatureModeStrategy {
public:
    uint32_t            pad00[0x13];
    CreatureRouteVector mRoutes;    // +0x4c
    static cCreatureModeStrategy* Instance();   // 0x00d38840
};

void FUN_00b922c0(TribePath* path, float halfWidth);   // stamp path into the planet grid

// ---------------------------------------------------------------------------------------
// Managers
struct cTerrainInfo {
    int FUN_00c75420();      // terrain kind
};

class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* create, void* f2, void* filter, void* f4, uint32_t typeID);  // 0x00b21340
    cTerrainInfo*    GetCurrentTerrainSphere();                                                          // 0x00f67d90
    void*            GetAvatar();                                                                        // 0x00b1fdb0
};

class cPlanetModel {
public:
    Vector3 DirectionToSurfacePosition(const Vector3& dir);   // 0x00b815a0
    uint32_t GetContinent(const Vector3& pos);             // 0x00b88590
};

struct cCubeGrid {
    void FUN_00b90ea0(const Vector3* pos, float a, float b, float c);   // clear marker area
};
extern cCubeGrid g_PlanetGrid;   // 0x0156c060

class cPathFinder {
public:
    bool FUN_00ac6960(void* grid, const Vector3* start, const Vector3* end, GridNodeVector* out,
                      float a, float b);
};
extern char g_1565b18[];   // path-finder grid object

struct cSpeciesArchetype {
    uint32_t pad00[4];
    uint32_t mListID;                      // +0x10
    uint32_t pad14[(0x308 - 0x14) / 4];
    float    mClearA;                      // +0x308
    float    mClearB;                      // +0x30c
    float    mClearC;                      // +0x310
    uint32_t pad314[(0x3b0 - 0x314) / 4];
    uint32_t* mpDefsBegin;                 // +0x3b0
    uint32_t* mpDefsEnd;                   // +0x3b4
    uint32_t pad3b8[(0x43c - 0x3b8) / 4];
    PropertyList* mpProps;                 // +0x43c
};
class cEditorSpeciesManager {
public:
    cSpeciesArchetype* GetSpeciesArchetype(uint32_t key, int generation);   // 0x004e0050
};

// Position of the avatar (Vector3*) from the avatar noun.
struct cAvatarInfo {
    void* FUN_00c04590();                  // thiscall
};
struct cAvatarPos {
    const Vector3* FUN_00c6acc0();         // thiscall
};
struct cAvatarNoun {
    cAvatarPos* FUN_00c04590();            // 0x00c04590
};

extern const uint32_t g_CreatureSetupLists[];   // 0x0146598c, indexed by terrain kind + 3

cGameNounManager*      NounManager();       // 0x00b3d300
IPropManager*          PropertyManager();   // 0x0067de30
cPlanetModel*          PlanetModel();       // 0x00b3d350
cPathFinder*           FUN_00b3d290();
cEditorSpeciesManager* FUN_00401090();
int  FUN_00b9b090(const Vector3* pos, const uint32_t* ids, int count, uint32_t a, int b);
void FUN_00b9aa10(const Vector3* pos, const uint32_t* ids, int count, uint32_t groupID);
void FUN_00b9c830(PropertyList* list, const Vector3* pos, float radiusSq, uint32_t a, uint32_t b);
void FUN_00829110(GameDataPtr** pOut, cGameData** first, cGameData** last, GameDataPtr* dst, uint32_t continent);

// GetGameDataVector callbacks
void FUN_00cd7d10();
void FUN_00d3d420();
void FUN_00ace070();
void FUN_00b1e500();

// @ 0x00ba1590
void FUN_00ba1590(void)
{
    cGameNounManager* nouns = NounManager();
    cEditorSpeciesManager* species = FUN_00401090();
    cPlanetModel* planet = PlanetModel();
    cAvatarNoun* avatar = (cAvatarNoun*)nouns->GetAvatar();
    if (!avatar)
        return;

    IPropManager* pm = PropertyManager();
    PropertyListPtr list;
    uint32_t listID = g_CreatureSetupLists[NounManager()->GetCurrentTerrainSphere()->FUN_00c75420() + 3];
    GetPropList(pm, listID, 0x0302a1c9, list);

    const Vector3* avatarPos = avatar->FUN_00c04590()->FUN_00c6acc0();
    uint32_t continent = planet->GetContinent(*avatarPos);
    float halfWidth = GetPropertyFloatDefault(list.get(), 0x1d92aa9d, 1.0f) * 0.5f;

    cCreatureModeStrategy::Instance()->mRoutes.clear();

    {
        cGameNounManager* nm = NounManager();
        GameDataPtrVector& markers = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                           (void*)FUN_00ace070, (void*)FUN_00b1e500,
                                                           0x036be27e)->mData;
        for (cGameData** it = markers.mpBegin, **itEnd = markers.mpEnd; it != itEnd; ++it) {
            cGameData* gd = *it;
            if (gd->mDefinitionID == 0xc012ae1f && gd->mState == 4 && gd->mFlag11c == 0) {
                FixedGridVector chain;
                cGameData* cur = gd;
                cGameData* next = gd->mpNext;
                while (next) {
                    GridNodeVector path;
                    const Vector3* p0 = cur->mSpatial.GetPosition();
                    const Vector3* p1 = next->mSpatial.GetPosition();
                    if (!FUN_00b3d290()->FUN_00ac6960(g_1565b18, p0, p1, &path, 0.0f, 1.0f))
                        break;
                    if (cur == gd) {
                        GridNode n;
                        n.mPos.x = p0->x;
                        n.mPos.y = p0->y;
                        n.mPos.z = p0->z;
                        n.mW = 1.0f;
                        n.m10 = 0;
                        n.m3c = 0;
                        chain.push_back(n);
                    }
                    chain.FUN_00b96360(chain.mpEnd, path.mpBegin, path.mpEnd, continent);
                    cur = next;
                    next = next->mpNext;
                }
                if (chain.mpBegin != chain.mpEnd) {
                    cCreatureModeStrategy::Instance()->mRoutes.push_back();
                    CreatureRoute* route = &cCreatureModeStrategy::Instance()->mRoutes.back();
                    float width = gd->mWidth;
                    route->mWidth = width;
                    if (width < 1.52587890625e-05f)
                        route->mWidth = 1.0f;
                    TribePath* path = &route->mPath;
                    path->mPoints.reserve((int)(chain.mpEnd - chain.mpBegin));
                    for (GridNode* g = chain.mpBegin, *gEnd = chain.mpEnd; g != gEnd; ++g)
                        path->mPoints.push_back(planet->DirectionToSurfacePosition(g->mPos));
                    FUN_00b922c0(path, halfWidth);
                }
            }
        }
    }

    {
        cGameNounManager* nm = NounManager();
        tGameDataVector* all = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                     (void*)FUN_00ace070, (void*)FUN_00b1e500,
                                                     0x036be27e);
        int n = (int)(all->mData.mpEnd - all->mData.mpBegin);
        GameDataPtr* buf;
        if (n)
            buf = (GameDataPtr*)operator new(n * 4, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        else
            buf = 0;
        GameDataPtr* bufEnd;
        FUN_00829110(&bufEnd, all->mData.mpBegin, all->mData.mpEnd, buf, continent);

        for (GameDataPtr* q = buf; q != bufEnd; ++q) {
            cGameData* gd = q->mp;
            if (gd->mDefinitionID != 0x91fe517b)
                continue;
            cSpeciesArchetype* arch = species->GetSpeciesArchetype(gd->mSubType, 0);
            if (arch && arch->mpProps) {
                const Vector3* pos = gd->mSpatial.GetPosition();
                if (planet->GetContinent(*pos) == continent) {
                    g_PlanetGrid.FUN_00b90ea0(pos, arch->mClearA, arch->mClearB, arch->mClearC);
                    int count = 0;
                    uint32_t* ids = 0;
                    if (GetPropertyAsUint32Array(arch->mpProps, 0xdb9bfc2c, &count, &ids) && count > 0)
                        FUN_00b9b090(pos, ids, count, arch->mListID, 0);
                    int defs = (int)(arch->mpDefsEnd - arch->mpDefsBegin);
                    if (defs > 0)
                        FUN_00b9aa10(pos, arch->mpDefsBegin, defs, arch->mListID);
                }
            }
        }
        for (GameDataPtr* q = buf; q < bufEnd; ++q)
            q->~GameDataPtr();
        if (buf && ((int*)buf)[-1])
            operator delete[](buf);
    }

    if (list.get()) {
        if (list->HasProperty(0xa1d6248e)) {
            Property* p = list->GetPropertyObject(0xa1d6248e);
            FUN_00b9aa10(avatarPos, PropertyItems(p), PropertyItemCount(p), listID);
        }
        if (list->HasProperty(0xf7084224)) {
            Property* p = list->GetPropertyObject(0xf7084224);
            FUN_00b9b090(avatarPos, PropertyItems(p), PropertyItemCount(p), listID, 0);
        }
    }
    FUN_00b9c830(list.get(), avatarPos, 3.402823466e+38F, 0x204e6edd, 0x73cc6df5);
}
