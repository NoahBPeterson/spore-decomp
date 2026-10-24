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

// ===============================================================================================
// G7: cGonzagoSubsystem-derived key-list owner (0x00ba1c60 .. 0x00ba2400).
//
// The object is 0x44 bytes: two vtable pointers (+0x0, +0x4), three intrusive circular lists
// (+0x1c, +0x28, +0x34) of 12-byte nodes {next, prev, key} and two flag bytes (+0x40 staging,
// +0x41 committing).  Keys are COM-like refcounted objects: first vtable at +0x0 (AddRef +4,
// Release +8), a second interface vtable at +0x8 (slots +0xc/+0x1c/+0x20) and three flag bytes
// at +0xc..+0xe used by the commit notification pass.
namespace G7
{
    typedef unsigned int  u32;
    typedef unsigned char u8;

#define G7NOINLINE __declspec(noinline)

    struct Obj
    {
        void* pVtbl0;       // +0x0  first interface (AddRef +4, Release +8)
        void* pUnk04;       // +0x4
        void* pVtbl1;       // +0x8  second interface (GetId +0x20, Prepare +0xc, Notify +0x1c)
        char  mNotifyMode;  // +0xc  written from the commit flag
        char  m0d;          // +0xd
        char  m0e;          // +0xe
    };

    struct Node
    {
        Node* pNext;        // +0x0
        Node* pPrev;        // +0x4
        Obj*  pObj;         // +0x8
    };

    // A list base is itself a node (the sentinel); its value slot is unused.
    struct List
    {
        Node* pNext;        // +0x0  sentinel next
        Node* pPrev;        // +0x4  sentinel prev
        Obj*  pUnused;      // +0x8  sentinel value slot

        void DoClear();                             // 0x0060c4a0
        __forceinline void Init() { pNext = (Node*)this; pPrev = (Node*)this; }
    };

    // First parameter of FUN_00ba1fa0: version/build pair at +0xc/+0x10.
    struct VersionArg
    {
        u32 mPad00[3];      // +0x0
        u32 mVersion;       // +0xc
        u32 mBuild;         // +0x10
    };

    struct Owner
    {
        void* pVtbl0;       // +0x0
        void* pVtbl1;       // +0x4
        u32   mPad08[5];    // +0x8 .. +0x1b
        List  mActive;      // +0x1c
        List  mPending;     // +0x28
        List  mScratch;     // +0x34
        u8    m40;          // +0x40
        u8    mCommitted;   // +0x41
        u8    mPad42[2];

        void BaseCtor();    // 0x00b5b960
        void BaseDtor();    // 0x00b5b9a0

        void Notify5c(void* unused, void* value);                 // 0x00ba1d80 (ret 8)
        void ReadFrom(void* stream);                              // 0x00ba1f30
        void NotifyAndPrune(VersionArg* arg);                     // 0x00ba1fa0
        void RemoveKey(Obj* key);                                 // 0x00ba2070
        void ClearActive();                                       // 0x00ba20f0
        Owner* Ctor();                                            // 0x00ba2250
        Owner* Dtor(u8 flags);                                    // 0x00ba2290
        void AddKey(Obj* key);                                    // 0x00ba22e0
        void CommitPending(void* a, void* b, char flag);          // 0x00ba2400 (ret 0xc)
    };

    struct SimCtx
    {
        int GetStage();     // 0x00c70e00
    };

    // Planet grid object whose Rebuild (0x00b9a630) runs after a stage switch.
    struct Grid
    {
        void Rebuild();     // 0x00b9a630
    };

    // Variable-list serializer built on the stack by FUN_00ba1f30.
    struct VarListSerializer
    {
        u8 mData[0xa14];
        void Ctor(void* owner, void* name, int id);   // 0x00692f90 (ret 0xc)
        void Read(void* stream);                      // 0x00693e10
    };

    // Stage ids passed to FUN_00ba0770.
    extern char DAT_01654c01;
    extern char DAT_01654c02;
    extern char DAT_01654c04;
    extern char DAT_01654c05;

    void G7SetupSpots(void* stage, int on);         // 0x00ba0770
    void G7NounManager();                           // 0x00b3d300
    void G7CreatureStage();                         // 0x00ba1590
    void G7TribeStage();                            // 0x00b9caa0
    void G7SpaceStage();                            // 0x00b9d820
    void G7AfterSpawn();                            // 0x00b99420
    void G7Stage2(void* ctx);                       // 0x00b9bed0
    void G7Stage4(void* ctx);                       // 0x00b9ff80
    void G7Stage5(void* ctx);                       // 0x00ba0080
    void G7WriteUint32(void* stream, void* data, int count, int flags);   // 0x0093aa70
    void G7ReadInt32(void* stream, void* data, int count, int flags);     // 0x0093a780

    __forceinline void* VSlot(void* p, int off)
    {
        return *(void**)((char*)(*(void**)(p)) + off);
    }
    __forceinline void* ObjSub(Obj* o) { return &o->pVtbl1; }
    __forceinline void ObjAddRef(Obj* o)  { ((void (__thiscall*)(Obj*))VSlot(o, 4))(o); }
    __forceinline void ObjRelease(Obj* o) { ((void (__thiscall*)(Obj*))VSlot(o, 8))(o); }

    void* G7NewNode()
    {
        return operator new(0xc, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
    }

    __forceinline void InsertNode(List* list, Obj* obj)
    {
        if (obj)
            ObjAddRef(obj);
        Node* n = (Node*)G7NewNode();
        if (&n->pObj) {
            n->pObj = obj;
            if (obj)
                ObjAddRef(obj);
        }
        n->pNext = (Node*)list;
        n->pPrev = list->pPrev;
        list->pPrev->pNext = n;
        list->pPrev = n;
        if (obj)
            ObjRelease(obj);
    }

// @ 0x00ba1c60
    void StageChangeHandler(u32 stage)
    {
        G7NounManager();
        switch (stage) {
        case 0x1654c04:
            G7SetupSpots(&DAT_01654c04, 1);
            G7SpaceStage();
            break;
        case 0x1654c02:
            G7SetupSpots(&DAT_01654c02, 1);
            G7TribeStage();
            G7AfterSpawn();
            break;
        case 0x1654c01:
            G7SetupSpots(&DAT_01654c01, 1);
            G7CreatureStage();
            G7AfterSpawn();
            break;
        }
        ((Grid*)0x156c060)->Rebuild();
    }

// @ 0x00ba1ce0
    void SimCtxStageHandler(SimCtx* ctx)
    {
        switch (ctx->GetStage()) {
        case 5:
            G7SetupSpots(&DAT_01654c05, 0);
            G7Stage5(ctx);
            break;
        case 4:
            G7SetupSpots(&DAT_01654c04, 0);
            G7Stage4(ctx);
            break;
        case 2:
            G7SetupSpots(&DAT_01654c02, 0);
            G7Stage2(ctx);
            break;
        }
    }

// @ 0x00ba1d80
    void Owner::Notify5c(void* unused, void* value)
    {
        ((void (__thiscall*)(Owner*, void*, int, int))VSlot(this, 0x5c))(this, value, 0, 0);
    }

// @ 0x00ba1da0
    bool NotifyAll(void* arg, List* list)
    {
        for (Node* n = list->pNext; n != (Node*)list; n = n->pNext) {
            Obj* o = n->pObj;
            if (o)
                ((void (__thiscall*)(void*, void*))VSlot(ObjSub(o), 0x1c))(ObjSub(o), arg);
        }
        return true;
    }

    void __stdcall EraseIt(Node** out, Node* it);

// @ 0x00ba1ea0
    void SerializeList(Owner* owner, List* list)
    {
        u32 count = 0;
        Node* p = list->pNext;
        while (p != (Node*)list) {
            p = p->pNext;
            ++count;
        }
        void* a = ((void* (__thiscall*)(Owner*))VSlot(owner, 0x20))(owner);
        void* b = ((void* (__thiscall*)(void*))VSlot(a, 0x18))(a);
        u32 num = count;
        G7WriteUint32(b, &num, 1, 0);
        for (Node* n = list->pNext; n != (Node*)list; n = n->pNext) {
            void* r = 0;
            if (n->pObj)
                r = ((void* (__thiscall*)(void*, int))VSlot(ObjSub(n->pObj), 0xc))(ObjSub(n->pObj), 0x179c807);
            ((void (__thiscall*)(Owner*, void*))VSlot(owner, 0x2c))(owner, r);
        }
        ((void (__thiscall*)(Owner*))VSlot(owner, 0x1c))(owner);
    }

// @ 0x00ba1f30
    void Owner::ReadFrom(void* stream)
    {
        mActive.DoClear();
        mActive.Init();
        mPending.DoClear();
        mPending.Init();
        mScratch.DoClear();
        mScratch.Init();

        VarListSerializer ser;
        ser.Ctor(this, (void*)0x156c0b8, 0x1a80d26);
        ser.Read(stream);
    }

// @ 0x00ba1fa0
    void Owner::NotifyAndPrune(VersionArg* arg)
    {
        for (Node* n = mActive.pNext; n != (Node*)&mActive; n = n->pNext)
            ((void (__thiscall*)(Obj*, VersionArg*))VSlot(n->pObj, 0x18))(n->pObj, arg);

        if ((u32)((arg->mVersion << 16) | arg->mBuild) >= 0x220000)
            return;

        Node* end = (Node*)&mActive;
        Node* n = mActive.pNext;
        while (n != end) {
            u32 id = ((u32 (__thiscall*)(void*))VSlot(ObjSub(n->pObj), 0x20))(ObjSub(n->pObj));
            n = n->pNext;
            if (id == 0x12326f68) {
                Node* node = n->pPrev;
                node->pPrev->pNext = node->pNext;
                node->pNext->pPrev = node->pPrev;
                if (node->pObj)
                    ObjRelease(node->pObj);
                operator delete[](node);
                return;
            }
        }
    }
// @ 0x00ba2070
    void Owner::RemoveKey(Obj* key)
    {
        for (Node* n = mActive.pNext; n != (Node*)&mActive; n = n->pNext) {
            if (n->pObj == key) {
                if (n != (Node*)&mActive) {
                    if (mCommitted) {
                        ((void (__thiscall*)(Owner*, Obj*))VSlot(this, 0x60))(this, key);
                    } else {
                        EraseIt((Node**)&key, n);
                    }
                    return;
                }
                break;
            }
        }
        for (Node* n = mPending.pNext; n != (Node*)&mPending; n = n->pNext) {
            if (n->pObj == key) {
                if (n != (Node*)&mPending)
                    EraseIt((Node**)&key, n);
                break;
            }
        }
    }

// @ 0x00ba20f0
    void Owner::ClearActive()
    {
        List* l = &mActive;
        l->DoClear();
        l->Init();
    }

    void CopyRange(Node** out, Node* first, Node* last, Node* dst, Obj** skip);
    void __stdcall EraseRange(Node** out, Node* first, Node* last);

// @ 0x00ba2170
    void DeserializeList(Owner* owner, List* list)
    {
        list->DoClear();
        list->Init();

        void* fnA = VSlot(owner, 0x20);
        void* a = ((void* (__thiscall*)(Owner*))fnA)(owner);
        u32 count = 0;
        void* fnB = VSlot(a, 0x18);
        void* b = ((void* (__thiscall*)(void*))fnB)(a);
        G7ReadInt32(b, &count, 1, 0);

        for (u32 i = 0; i < count; ++i) {
            Obj* obj = 0;
            void* fnC = VSlot(owner, 0x28);
            ((void (__thiscall*)(Owner*, int, Obj**, int))fnC)(owner, 0x11416b8, &obj, 0);
            Node* n = (Node*)G7NewNode();
            if (&n->pObj) {
                n->pObj = obj;
                if (obj)
                    ObjAddRef(obj);
            }
            n->pNext = (Node*)list;
            n->pPrev = list->pPrev;
            list->pPrev->pNext = n;
            list->pPrev = n;
            if (obj)
                ObjRelease(obj);
        }
        ((void (__thiscall*)(Owner*))VSlot(owner, 0x1c))(owner);
    }

// @ 0x00ba2250
    Owner* Owner::Ctor()
    {
        BaseCtor();
        pVtbl0 = (void*)0x1465c40;
        pVtbl1 = (void*)0x1465c3c;
        mActive.Init();
        mPending.Init();
        mScratch.Init();
        m40 = 0;
        mCommitted = 0;
        return this;
    }

// @ 0x00ba2290
    Owner* Owner::Dtor(u8 flags)
    {
        pVtbl0 = (void*)0x1465c40;
        pVtbl1 = (void*)0x1465c3c;
        mScratch.DoClear();
        mPending.DoClear();
        mActive.DoClear();
        BaseDtor();
        if (flags & 1)
            operator delete[](this);
        return this;
    }

// @ 0x00ba22e0
    void Owner::AddKey(Obj* key)
    {
        for (Node* n = mActive.pNext; n != (Node*)&mActive; n = n->pNext) {
            if (n->pObj == key) {
                if (n != (Node*)&mActive)
                    return;
                break;
            }
        }
        for (Node* n = mPending.pNext; n != (Node*)&mPending; n = n->pNext) {
            if (n->pObj == key) {
                if (n != (Node*)&mPending)
                    return;
                break;
            }
        }
        if (mCommitted)
            InsertNode(&mPending, key);
        else
            InsertNode(&mActive, key);
    }

// @ 0x00ba2400
    void Owner::CommitPending(void* a, void* b, char flag)
    {
        if (mScratch.pNext != (Node*)&mScratch) {
            for (Node* s = mScratch.pNext; s != (Node*)&mScratch; s = s->pNext) {
                Obj* key = s->pObj;
                Node* n = mActive.pNext;
                while (n != (Node*)&mActive && n->pObj != key)
                    n = n->pNext;
                n = n->pNext;
                Node* node = n->pPrev;
                node->pPrev->pNext = node->pNext;
                node->pNext->pPrev = node->pPrev;
                if (node->pObj)
                    ObjRelease(node->pObj);
                operator delete[](node);
            }
            Node* s = mScratch.pNext;
            while (s != (Node*)&mScratch) {
                Node* next = s->pNext;
                if (s->pObj)
                    ObjRelease(s->pObj);
                operator delete[](s);
                s = next;
            }
            mScratch.Init();
        }

        u32 count = 0;
        for (Node* n = mPending.pNext; n != (Node*)&mPending; n = n->pNext)
            ++count;
        if (count > 0) {
            Node* first = mPending.pNext;
            if (first != (Node*)&mPending) {
                mPending.pPrev->pNext = (Node*)&mActive;
                first->pPrev->pNext = (Node*)&mPending;
                mActive.pPrev->pNext = first;
                Node* old = mActive.pPrev;
                mActive.pPrev = mPending.pPrev;
                mPending.pPrev = first->pPrev;
                first->pPrev = old;
            }
        }

        mCommitted = 1;
        Node* end = (Node*)&mActive;
        for (Node* n = mActive.pNext; n != end; n = n->pNext) {
            Obj* o = n->pObj;
            if (!o)
                continue;
            o->mNotifyMode = flag;
            if (o->m0e)
                continue;
            if (flag && !o->m0d)
                continue;
            ((void (__thiscall*)(Obj*, void*, void*))VSlot(o, 0x10))(o, a, b);
        }

        Obj* none = 0;
        Node* n = mActive.pNext;
        while (n != end && n->pObj != 0)
            n = n->pNext;
        if (n != end) {
            Node* dst = n;
            CopyRange(&dst, n->pNext, end, n, &none);
            Node* dummy = 0;
            EraseRange(&dummy, dst, end);
        }
        mCommitted = 0;
    }

// @ 0x00ba1dd0
    G7NOINLINE void CopyRange(Node** out, Node* first, Node* last, Node* dst, Obj** skip)
    {
        if (first == last) {
            *out = dst;
            return;
        }
        do {
            Obj* obj = first->pObj;
            if (obj != *skip) {
                Obj* old = dst->pObj;
                if (obj != old) {
                    if (obj)
                        ObjAddRef(obj);
                    dst->pObj = obj;
                    if (old)
                        ObjRelease(old);
                }
                dst = dst->pNext;
            }
            first = first->pNext;
        } while (first != last);
        *out = dst;
    }

// @ 0x00ba1e50
    G7NOINLINE void __stdcall EraseIt(Node** out, Node* it)
    {
        it = it->pNext;
        Node* node = it->pPrev;
        node->pPrev->pNext = node->pNext;
        node->pNext->pPrev = node->pPrev;
        if (node->pObj)
            ObjRelease(node->pObj);
        operator delete[](node);
        *out = it;
    }

// @ 0x00ba2110
    G7NOINLINE void __stdcall EraseRange(Node** out, Node* first, Node* last)
    {
        if (first != last) {
            do {
                first = first->pNext;
                Node* node = first->pPrev;
                node->pPrev->pNext = node->pNext;
                node->pNext->pPrev = node->pPrev;
                if (node->pObj)
                    ObjRelease(node->pObj);
                operator delete[](node);
            } while (first != last);
        }
        *out = last;
    }
}
