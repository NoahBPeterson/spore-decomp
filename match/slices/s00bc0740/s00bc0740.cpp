// Slice s00bc0740: planet "explored area" cube map update (0x00bc08d0, 2931 bytes).
// /O2 /arch:SSE module (movss/comiss with x87 fabs/fsqrt), no /EHsc (the conditional
// PropertyListPtr temporaries are destroyed through a flag word but there is no EH frame).
//
//   void __thiscall cPlanetCoverage::Update(bool reset)   (ret 4)
//
// The coverage map is a 6 x 128 x 128 byte cube map (one byte per texel, 0xff = covered).
// Unless the game is in mode 0x1654c10 it:
//   - optionally clears the map,
//   - (not in mode 0x1654c02) rasterizes every new planet path (tracked in a set<int> of path
//     indices) by stepping along each segment and marking the cube texels it crosses,
//   - marks a disc around three kinds of game objects and every planet object with a
//     size property, and every registered extra disc (hash_map at +0x20),
//   - and asks the map owner to refresh (0xf) when any texel changed.

#include "types.h"
#include <math.h>

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    float Length() const { return sqrtf(z * z + y * y + x * x); }
};

// ---------------------------------------------------------------- properties
extern const float kDefaultFloatValue;   // 0x015d9c6c

struct Property
{
    void*    mpData;      // +0x00 (external data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = array / external data)
    uint16_t mnType;      // +0x12

    uint16_t GetType() const { return mnType; }
    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    float* GetValueFloat()
    {
        if (mnType == 13 || mnType == 0x10)
            return (float*)GetValuePtr();
        return (float*)&kDefaultFloatValue;
    }
    float* GetFloat();    // 0x0041ea70 (the same getter, called out of line)
};

class cPropertyList
{
public:
    virtual int  AddRef();                                       // 0x00
    virtual int  Release();                                      // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
};

// eastl::intrusive_ptr<cPropertyList>
struct PropertyListPtr
{
    cPropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    cPropertyList* get() const { return mpObject; }
};

// App::Property-style inline getters
inline bool GetFloatOutOfLine(cPropertyList* pl, uint32_t id, float& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 13) { v = *p->GetFloat(); return true; }
    return false;
}
inline bool GetFloat(cPropertyList* pl, uint32_t id, float& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 13) { v = *p->GetValueFloat(); return true; }
    return false;
}
inline float GetFloatDefault(cPropertyList* pl, uint32_t id, float def)
{
    Property* p;
    if (pl && pl->GetProperty(id, p))
        return *p->GetValueFloat();
    return def;
}

template <class T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }

// ---------------------------------------------------------------- game objects
class cModel
{
public:
    char pad0[0x90];
    PropertyListPtr mpPropList;    // +0x90
};

class cSpatialObject
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const Vector3& GetPosition();      // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual float GetBoundingRadius();         // +0x70
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
    virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
    virtual void s41(); virtual void s42();
    virtual cModel* GetModel();                // +0xac
};

// game data of type 0x018c43e8
class cGameObjectA
{
public:
    char pad0[0x120];
    cSpatialObject mSpatial;                   // +0x120
    char pad124[0x324 - 0x124];
    struct Holder { char pad0[0x34]; cSpatialObject mSpatial; }* mpHolder;   // +0x324
    Vector3 GetPosition();                     // 0x00bd9480
};

// game data of type 0x018c6d19
class cGameObjectB
{
public:
    char pad0[0x120];
    cSpatialObject mSpatial;                   // +0x120
    char pad124[0x2d4 - 0x124];
    cPropertyList* mpPropList;                 // +0x2d4
    struct Attachment { char pad0[0x70]; cSpatialObject mSpatial; }* GetAttachment();   // 0x00c8fed0
};

// game data of type 0x52aa6122
class cGameObjectC
{
public:
    char pad0[0x34];
    cSpatialObject mSpatial;                   // +0x34
};

struct GameDataVector { uint32_t pad0; void** mpBegin; void** mpEnd; };

void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00acdff0(); void FUN_00accbb0();
void FUN_00bbf9b0(); void FUN_00b1e500();
typedef void (*GameDataFn)();
extern char kGameDataTypeA;   // 0x018c43e8
extern char kGameDataTypeB;   // 0x018c6d19

class cGameNounManager
{
public:
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                      uint32_t type);   // 0x00b21340
};
namespace SP { cGameNounManager* NounManager(); }   // 0x00b3d300
namespace SP { uint32_t GetCurrentGameMode(); }     // 0x00b5b800

// planet objects with a model property list
struct cPlanetObject
{
    char pad0[0x0c];
    Vector3 mPosition;                         // +0x0c
    char pad18[0x90 - 0x18];
    cPropertyList* mpPropList;                 // +0x90
};

struct PlanetPath
{
    uint32_t pad0;
    char*    mpBegin;                          // +0x04 (0x24-byte points, position first)
    char*    mpEnd;                            // +0x08
};

class cPlanet
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual int GetObjects(cPlanetObject**& objects);   // +0xb0
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
    virtual PlanetPath* GetPath(int index);             // +0xc4
    virtual int GetPathCount();                         // +0xc8
};

class cPlanetModel
{
public:
    char pad0[0x24];
    cPlanet* mpPlanet;                         // +0x24
    float GetRadius();                         // 0x00b7e4d0
};
namespace SP { cPlanetModel* PlanetModel(); }   // 0x00b3d350

// the 6 x 128 x 128 coverage cube map and its owner
class cCoverageMap
{
public:
    char pad0[0x10];
    uint8_t* mpCells;                          // +0x10
    void Clear(int size, int value);           // 0x00f921d0
};

class cCoverageOwner
{
public:
    char pad0[0x38];
    cCoverageMap* mpMap;                       // +0x38
    void Refresh(int flags);                   // 0x00b2a750
};
cCoverageOwner* CoverageOwner();   // 0x00b3d3b0

bool MarkDisc(const Vector3& center, float radius, cCoverageMap* map);   // 0x00bbd2a0

// ---------------------------------------------------------------- EASTL bits
namespace eastl {
struct true_type {};
struct rbtree_node_base { rbtree_node_base* mpNodeRight; rbtree_node_base* mpNodeLeft; rbtree_node_base* mpNodeParent; char mColor; };
struct rbtree_node_s32 : rbtree_node_base { int mValue; };
struct rbtree_iterator_s32
{
    rbtree_node_s32* mpNode;
    rbtree_iterator_s32(rbtree_node_s32* p) : mpNode(p) {}
    rbtree_iterator_s32(const rbtree_iterator_s32& x) : mpNode(x.mpNode) {}
};
struct pair_iterator_bool
{
    rbtree_iterator_s32 first; bool second;
    pair_iterator_bool(const rbtree_iterator_s32& a, bool b) : first(a), second(b) {}
};

// eastl::set<int>
struct set_int
{
    typedef rbtree_iterator_s32 iterator;
    int mCompare;
    rbtree_node_base mAnchor;
    unsigned mnSize;
    uint32_t mAllocator;

    iterator find(const int& key);                                  // 0x00e39fb0 (folded)
    pair_iterator_bool DoInsertValue(const int& value, true_type);  // 0x007d0850
    unsigned erase(const int& key);                                 // 0x00b36360
    void DoNukeSubtree(rbtree_node_base* pNode);                    // 0x009a9600 (folded)

    iterator end() { return iterator((rbtree_node_s32*)&mAnchor); }
    pair_iterator_bool insert(const int& value) { return DoInsertValue(value, true_type()); }
    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear()
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
        reset();
    }
};
inline bool operator==(const rbtree_iterator_s32& a, const rbtree_iterator_s32& b) { return a.mpNode == b.mpNode; }

struct DiscEntry { Vector3 mCenter; float mRadius; };
struct hash_node_disc
{
    uint32_t first;
    DiscEntry second;
    hash_node_disc* mpNext;
};
struct hashtable_iterator_disc
{
    hash_node_disc*  mpNode;
    hash_node_disc** mpBucket;
    hashtable_iterator_disc(hash_node_disc** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    void increment_bucket()
    {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    hashtable_iterator_disc& operator++() { increment(); return *this; }
    hash_node_disc* operator->() const { return mpNode; }
};
inline bool operator!=(const hashtable_iterator_disc& a, const hashtable_iterator_disc& b) { return a.mpNode != b.mpNode; }

// eastl::hash_map<uint32_t, DiscEntry> (just the bucket array)
struct hash_map_disc
{
    hash_node_disc** mpBucketArray;
    uint32_t mnBucketCount;

    hashtable_iterator_disc begin()
    {
        hashtable_iterator_disc i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    hashtable_iterator_disc end() { return hashtable_iterator_disc(mpBucketArray + mnBucketCount); }
};
}   // namespace eastl

// ---------------------------------------------------------------- the coverage updater
// float -> int with truncation (asm helper in the original, like the module's RoundToInt).
__forceinline int TruncToInt(float f) { __asm cvttss2si eax, f }
#pragma warning(disable: 4035)

static __forceinline int CubeMapTexel(const Vector3& p)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    int u, v, face;
    if (az >= ax && az >= ay)
    {
        u = TruncToInt((x / z + 1.0f) * 64.0f);
        v = TruncToInt((y / az + 1.0f) * 64.0f);
        if (z >= 0.0f) face = 0; else face = 1;
    }
    else if (ay >= ax)
    {
        u = TruncToInt((z / y + 1.0f) * 64.0f);
        v = TruncToInt((x / ay + 1.0f) * 64.0f);
        if (y >= 0.0f) face = 4; else face = 5;
    }
    else
    {
        u = TruncToInt((y / x + 1.0f) * 64.0f);
        v = TruncToInt((z / ax + 1.0f) * 64.0f);
        face = (x >= 0.0f) ? 2 : 3;
    }
    if (u == 128) u = 127;
    if (v == 128) v = 127;
    return (face * 128 + v) * 128 + u;
}

class cPlanetCoverage
{
public:
    char pad0[0x20];
    eastl::hash_map_disc mDiscs;               // +0x20
    char pad28[0x48 - 0x28];
    eastl::set_int mRasterizedPaths;           // +0x48

    void Update(bool reset);
};

void cPlanetCoverage::Update(bool reset)
{
    if (SP::GetCurrentGameMode() == 0x1654c10)
        return;

    cCoverageMap* map = CoverageOwner()->mpMap;
    bool changed = false;
    if (reset)
        map->Clear(0x80, 0);
    cPlanet* planet = SP::PlanetModel()->mpPlanet;

    if (SP::GetCurrentGameMode() != 0x1654c02)
    {
        if (reset)
            mRasterizedPaths.clear();

        float step = SP::PlanetModel()->GetRadius() * (1.0f / 128.0f);
        uint8_t* cells = map->mpCells;
        int pathCount = planet->GetPathCount();
        for (int i = 0; i < pathCount; i++)
        {
            PlanetPath* path = planet->GetPath(i);
            if (path)
            {
                if (mRasterizedPaths.find(i) == mRasterizedPaths.end())
                {
                    mRasterizedPaths.insert(i);
                    if (path->mpBegin != path->mpEnd)
                    {
                        char* end = path->mpEnd;
                        for (char* prev = path->mpBegin, *cur = prev + 0x24; cur != end; prev = cur, cur += 0x24)
                        {
                            const Vector3& a = *(const Vector3*)prev;
                            const Vector3& b = *(const Vector3*)cur;
                            Vector3 pos = a;
                            Vector3 d = b - pos;
                            float len = d.Length();
                            if (len > 1.5258789e-05f)
                            {
                                Vector3 dir = d * (1.0f / len);
                                float t = 0.0f;
                                if (t < len)
                                {
                                    Vector3 delta = dir * step;
                                    do
                                    {
                                        int texel = CubeMapTexel(pos);
                                        pos += delta;
                                        t += step;
                                        changed |= cells[texel] != 0xff;
                                        cells[texel] = 0xff;
                                    } while (t < len);
                                }
                                int texel = CubeMapTexel(b);
                                changed |= cells[texel] != 0xff;
                                cells[texel] = 0xff;
                            }
                        }
                    }
                }
            }
            else
                mRasterizedPaths.erase(i);
        }
    }

    // objects with a radius property
    {
        cGameNounManager* nouns = SP::NounManager();
        GameDataVector* objects = nouns->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0, FUN_00b1e500, (uint32_t)&kGameDataTypeA);
        for (void** it = objects->mpBegin, **end = objects->mpEnd; it != end; ++it)
        {
            cGameObjectA* obj = (cGameObjectA*)*it;
            if (obj && obj->mpHolder)
            {
                cModel* model = obj->mpHolder->mSpatial.GetModel();
                float extra;
                if (!(model && GetFloatOutOfLine(model->mpPropList.get(), 0x5d52e51, extra)))
                    extra = 48.0f;
                changed |= MarkDisc(obj->GetPosition(), obj->mSpatial.GetBoundingRadius() + extra, map);
            }
        }
    }

    // objects with a scale property and an optional attachment
    {
        cGameNounManager* nouns = SP::NounManager();
        GameDataVector* objects = nouns->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, (uint32_t)&kGameDataTypeB);
        void** end = objects->mpEnd;
        for (void** it = objects->mpBegin; it != end; ++it)
        {
            cGameObjectB* obj = (cGameObjectB*)*it;
            changed |= MarkDisc(obj->mSpatial.GetPosition(),
                                max_alt(GetFloatDefault(obj->mpPropList, 0x49b71de, 1.0f), 1.0f), map);
            cGameObjectB::Attachment* attachment = obj->GetAttachment();
            if (attachment)
            {
                cSpatialObject* spatial = &attachment->mSpatial;
                if (spatial->GetModel())
                {
                    cModel* model = spatial->GetModel();
                    float scale = max_alt(GetFloatDefault(
                        ((model && model->mpPropList.get()) ? model->mpPropList : PropertyListPtr()).get(),
                        0x49b71de, 1.0f), 1.0f);
                    changed |= MarkDisc(spatial->GetPosition(), scale, map);
                }
            }
        }
    }

    {
        cGameNounManager* nouns = SP::NounManager();
        GameDataVector* objects = nouns->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00bbf9b0, FUN_00b1e500, 0x52aa6122);
        void** end = objects->mpEnd;
        for (void** it = objects->mpBegin; it != end; ++it)
        {
            cSpatialObject* spatial = &((cGameObjectC*)*it)->mSpatial;
            cModel* model = spatial->GetModel();
            float scale = max_alt(GetFloatDefault(
                ((model && model->mpPropList.get()) ? model->mpPropList : PropertyListPtr()).get(),
                0x49b71de, 1.0f), 1.0f);
            changed |= MarkDisc(spatial->GetPosition(), scale, map);
        }
    }

    // planet objects
    cPlanetObject** planetObjects;
    int count = planet->GetObjects(planetObjects);
    for (int i = 0; i < count; i++)
    {
        cPlanetObject* obj = planetObjects[i];
        float scale;
        if (obj && GetFloat(obj->mpPropList, 0x49b71de, scale))
            changed |= MarkDisc(obj->mPosition, max_alt(scale, 1.0f), map);
    }

    // registered discs
    for (eastl::hashtable_iterator_disc it = mDiscs.begin(), end = mDiscs.end(); it != end; ++it)
        changed |= MarkDisc(it->second.mCenter, it->second.mRadius, map);

    if (changed)
        CoverageOwner()->Refresh(0xf);
}
