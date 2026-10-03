// Quantized-bounds sampler and its property-list helpers.
//
// A BoundsHeader is a blob with the bounding box of a mesh/brick (min, max), a quantization
// step, up to 8 per-axis subdivision counts (bytes) and then one packed cell record per
// leaf (3 bytes: high nibble = offset below min, low nibble = offset above max, in steps).
// BoundsSampler walks the subdivision levels for a set of [0,1] weights, producing the
// interpolated min/max corners of the selected cell.
//
// Built without optimization: /Od /Ob1 /arch:SSE /fp:fast (frame pointer, movss, nothing
// kept in registers; only inline-marked/in-class functions are expanded).
#include "types.h"

struct Vector3 {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};

// Temporary built from three components (the plain Vector3 stays an aggregate).
struct Vector3Init : Vector3 {
    Vector3Init(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};

struct Cell { uint8_t b[3]; };

struct BoundsHeader {
    Vector3 minv;         // +0x00
    Vector3 maxv;         // +0x0C
    float   cell;         // +0x18  quantization step
    uint8_t dims[8];      // +0x1C  subdivision count per level (0 terminates)
    Cell    cells[1];     // +0x24
};

struct IntPair {
    int first, second;
};

// Per-level cell range inside the sampler: zero-initialised by its constructor.
struct Range : IntPair {
    Range() { first = 0; second = 0; }
    Range& operator=(const IntPair& p) { first = p.first; second = p.second; return *this; }
};

// 0x00413CC0: Vector3* Lerp(out, a, b, t) (cdecl; returns out)
Vector3* Lerp(Vector3* out, Vector3& a, Vector3& b, float t);

struct BoundsSampler {
    BoundsHeader* data;       // +0x00
    int           levels;     // +0x04
    Range         range[8];   // +0x08
    float         weight[8];  // +0x48
    unsigned int  total;      // +0x68

    IntPair* CellRange(IntPair* out, int axis, int stride, float t, float* frac);
    void     Collect(unsigned int cell, int level, Vector3* mn, Vector3* mx);
    void     CellBounds(unsigned int cell, Vector3& mn, Vector3& mx);
    void     Init(BoundsHeader* hdr, float* weights, int nWeights, Vector3* mn, Vector3* mx);
};

// @ 0x00415230
IntPair* BoundsSampler::CellRange(IntPair* out, int axis, int stride, float t, float* frac)
{
    int last;
    int idx;
    float scaled;
    int offset;
    last = data->dims[axis] - 1;
    if (last < 1) {
        IntPair r;
        r.second = 0;
        r.first = 0;
        out->first = r.first;
        out->second = r.second;
        return out;
    }
    scaled = (float)last * t;
    idx = (int)scaled;
    *frac = scaled - (float)idx;
    offset = idx * stride;
    if (*frac > 0.0f && idx < last) {
        int nx = offset + stride;
        out->first = offset;
        out->second = nx;
        return out;
    } else {
        out->first = offset;
        out->second = offset;
    }
    return out;
}

// @ 0x004154B0
void BoundsSampler::CellBounds(unsigned int cell, Vector3& mn, Vector3& mx)
{
    uint8_t* c = data->cells[cell].b;
    mn[0] = data->minv[0] - data->cell * (float)(c[0] >> 4);
    mn[1] = data->minv[1] - data->cell * (float)(c[1] >> 4);
    mn[2] = data->minv[2] - data->cell * (float)(c[2] >> 4);
    mx[0] = data->cell * (float)(c[0] & 0xF) + data->maxv[0];
    mx[1] = data->cell * (float)(c[1] & 0xF) + data->maxv[1];
    mx[2] = data->cell * (float)(c[2] & 0xF) + data->maxv[2];
}

// @ 0x00415310
void BoundsSampler::Collect(unsigned int cell, int level, Vector3* mn, Vector3* mx)
{
    if (cell >= total) {
        mn->x = -0.1f; mn->y = -0.1f; mn->z = -0.1f;
        mx->x = 0.1f; mx->y = 0.1f; mx->z = 0.1f;
        return;
    }
    if (level >= levels) {
        CellBounds(cell, *mn, *mx);
        return;
    }
    Collect(cell + range[level].first, level + 1, mn, mx);
    if (range[level].first != range[level].second) {
        Vector3 mn2, mx2;
        Vector3 tmp1, tmp2;
        Collect(cell + range[level].second, level + 1, &mn2, &mx2);
        *mn = *Lerp(&tmp1, *mn, mn2, weight[level]);
        *mx = *Lerp(&tmp2, *mx, mx2, weight[level]);
        uint32_t u1[7];   // dead locals of the original inlined helpers (frame size only)
        uint32_t u2[7];
        uint32_t u3[15];
    }
}

inline float Clamp01(float v, float lo, float hi)
{
    v = (lo > v) ? lo : v;
    v = (v < hi) ? v : hi;
    return v;
}

// @ 0x00415030
void BoundsSampler::Init(BoundsHeader* hdr, float* weights, int nWeights, Vector3* mn, Vector3* mx)
{
    int n;
    n = 0;
    while (n < 8 && hdr->dims[n] > 0)
        n++;
    total = 1;
    for (int i = 0; i < n; i++)
        total = hdr->dims[i] * total;
    if (n > 0) {
        data = hdr;
        levels = n;
        for (int j = 0; j < n; j++) {
            int stride = 1;
            for (int k = j + 1; k < n; k++)
                stride = hdr->dims[k] * stride;
            float w;
            if (j < nWeights)
                w = Clamp01(weights[j], 0.0f, 1.0f);
            else
                w = 0.0f;
            IntPair tmp;
            range[j] = *CellRange(&tmp, j, stride, w, &weight[j]);
        }
        Collect(0, 0, mn, mx);
    } else {
        *mn = hdr->minv;
        *mx = hdr->maxv;
    }
}

// ---------------------------------------------------------------------------------------
// Library of bounds blobs keyed by a 64-bit id, and property-list lookup helpers.

struct BoundsNode {          // hash node: key at +0, value at +8
    BoundsNode*   next;      // (layout of the first words is not exercised here)
    uint32_t      keyPad;
    BoundsHeader* value;
};
struct BoundsIter { BoundsNode* node; BoundsNode** bucket; };

struct BoundsTable {         // lives at BoundsLibrary+0x30
    uint32_t       pad0;
    BoundsNode**   buckets;  // +0x04
    unsigned int   bucketCount;  // +0x08
    // 0x0041FB20: find(out iterator, key)
    BoundsIter* Find(BoundsIter* out, const uint64_t* key);

    BoundsIter End() {
        BoundsIter it;
        it.bucket = buckets + bucketCount;
        it.node = *it.bucket;
        return it;
    }
};
inline bool operator!=(const BoundsIter& a, const BoundsIter& b) { return a.node != b.node; }

struct BoundsLibrary {
    uint32_t    pad[12];     // +0x00
    BoundsTable table;       // +0x30

    bool Query(unsigned int idLo, unsigned int idHi, float* weights, int nWeights, Vector3* mn, Vector3* mx);
};

// @ 0x00414E30
bool BoundsLibrary::Query(unsigned int idLo, unsigned int idHi, float* weights, int nWeights, Vector3* mn, Vector3* mx)
{
    uint64_t key = idLo | ((uint64_t)idHi << 32);
    BoundsIter it;
    table.Find(&it, &key);
    if (it != table.End()) {
        if (mn) {
            BoundsSampler sampler;
            sampler.Init(it.node->value, weights, nWeights, mn, mx);
        }
        if (!mn || (*mn)[0] < (*mx)[0])
            return true;
    }
    if (mn) {
        *mn = Vector3Init(-0.1f, -0.1f, -0.1f);
        *mx = Vector3Init(0.1f, 0.1f, 0.1f);
    }
    return false;
}

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};

struct RefCounted {
    virtual int AddRef();
    virtual int Release();
};

template <class T>
struct intrusive_ptr {
    T* mpObject;
    T* get() const { return mpObject; }
    T** AsPointer() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct PropertyList : RefCounted {};
typedef intrusive_ptr<PropertyList> PropertyListPtr;

struct PropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(unsigned int instanceID, unsigned int groupID, PropertyList** dst);  // +0x2C
};
PropManager* GetPropManager();  // 0x0067DE30

struct PropertyListMap {
    // 0x0041CD60: operator[](key) -> slot
    PropertyListPtr* Slot(const uint64_t* key);
};

struct PropertyListCache {
    uint32_t        pad[4];
    PropertyListMap map;     // +0x10

    PropertyList* Get(unsigned int instanceID, unsigned int groupID);
};

// @ 0x00415660
PropertyList* PropertyListCache::Get(unsigned int instanceID, unsigned int groupID)
{
    uint64_t key = instanceID | ((uint64_t)groupID << 32);
    PropertyListPtr* slot = map.Slot(&key);
    uint32_t deadA[2];   // dead locals of the original inlined map lookup (frame size only)
    uint32_t deadB[25];
    if (slot->get() == 0) {
        GetPropManager()->GetPropertyList(instanceID, groupID, slot->AsPointer());
    }
    return slot->get();
}

// External helpers (0x006A1250, 0x0068C6D0, 0x0067DCD0)
bool GetKeyValue(PropertyList* pList, unsigned int propertyID, ResourceKey* dst);
void ConvertKeyType(ResourceKey* key, unsigned int typeID, int flags);

struct ResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54();
    virtual int ResourceExists(ResourceKey* key);  // +0x58
};
ResourceManager* GetResourceManager();  // 0x0067DCD0

struct ConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54();
    virtual PropertyList* FindPropertyList(unsigned int instanceID, unsigned int groupID);  // +0x58

    bool FindModelKey(unsigned int instanceID, unsigned int groupID, ResourceKey* dst);
};

// @ 0x00415730
bool ConfigManager::FindModelKey(unsigned int instanceID, unsigned int groupID, ResourceKey* dst)
{
    ResourceKey key;
    if (GetKeyValue(FindPropertyList(instanceID, groupID), 0xF9EFBB, &key)) {
        ConvertKeyType(&key, 0x61, 0);
        if (GetResourceManager()->ResourceExists(&key)) {
            *dst = key;
            return true;
        }
    }
    return false;
}
