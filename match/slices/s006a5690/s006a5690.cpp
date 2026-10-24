// Slice s006a5690: EA::ArgScript command-variant helpers (type names, property
// lookup, hashtable/vector instantiation helpers). /O2, /arch:SSE.
#include "../../include/types.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static const char kAllocPath[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
extern "C" void* EA_Alloc(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  EA_Dealloc(void* p);                                                                 // 0x00f47380

// The key the name-keyed hashtables look up with: an eastl string object, only
// its {begin, end, capacity} triple being built by this slice.
struct NameString {
    const char* mpBegin;    // +0x00
    const char* mpEnd;      // +0x04
    const char* mpCapacity; // +0x08
};

struct Variant {
    uint32_t d0, d1, d2, d3;
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12
};

struct String {
    void*   mpBegin;    // +0
    void*   mpEnd;      // +4
    void*   mpCapacity; // +8
    void*   mAlloc;     // +0xc
    String& assign(const char* p);
    void    append(const char* pBegin, const char* pEnd);
};

namespace EA { namespace ArgScript {
// Fills *pDst (a name-string member of the manager) with the case-insensitive
// spelling of src, allocating a buffer the first time.
void MakeCaseInsensitive(const char* src, NameString* pDst);    // 0x00840cc0
}}

// hashtable / hash_map helpers (external, thiscall)
struct HashTable {
    void Find(void* out, const void* key);              // 0x007e2ea0
    void Find2(void* out, const void* key);             // 0x0041fb20
};
struct HashMapKey8 {
    void* operator[](const void* key);                 // 0x0041cd60
};
extern "C" int  DoInsertValue(void* dst, const void* src, int n);           // 0x011e0744
extern "C" void UninitFillN56(void* dst, int n, const void* value, const void* m);  // 0x0042e680
extern "C" void UninitFillN16(void* dst, int n, const void* value, const void* m);  // 0x00555b40
struct Vector3 { float x, y, z; };
struct cSPMatrix3 {
    float m[9];
    void Assign(const float* src);                                          // 0x0041cb40
};
extern const Vector3 kDefaultVector3;                                       // 0x016029d0
extern const float   g_01485720;                                            // 0x01485720 (1.0f)
extern const float   g_01602b10[9];                                         // 0x01602b10 (zero matrix)
extern "C" void VariantRelease(int* p);                                     // 0x006ad050
extern "C" void VariantHold(int* p);                                        // 0x006ad010

// ---------------------------------------------------------------------------
//  Shared layout of the EA::ArgScript expression manager.
// ---------------------------------------------------------------------------

// The manager's opaque expression-function object; slots are named by their
// vtable byte offset (only the ones this slice calls are given parameters).
class cExprMgr {
public:
    virtual void* v000();                                                   // +0x00
    virtual void* v004();                                                   // +0x04
    virtual void* v008();                                                   // +0x08
    virtual char  v00c(const void* pValue, void* pOut, uint32_t a, uint32_t b,
                       uint32_t c, uint32_t d);                             // +0x0c
    virtual void* v010();                                                   // +0x10
    virtual char  v014(const void* pKey, void** ppHeld);                    // +0x14
};

// SP::MessageServer(); only vtable slots 0x14 and 0x18 are called here.
class cMessageServer {
public:
    virtual void* v000();
    virtual void* v004();
    virtual void* v008();
    virtual void* v00c();
    virtual void* v010();
    virtual void  v014(uint32_t id, const void* pValue, uint32_t a);        // +0x14
    virtual void  v018(uint32_t id, const void* pValue, uint32_t a, uint32_t b);  // +0x18
};

// Reference-counted object: slot 0 holds, slot 1 releases.  mField04 keeps the
// data members of the derived objects at the offsets the game uses (the vtable
// pointer occupies the first four bytes).
class cRefObj {
public:
    uint32_t mField04;                                                      // +0x04
    virtual void Hold();                                                    // +0x00
    virtual void Release();                                                 // +0x04
};

// A reference-counted expression function; only the {id, type, key} triple at
// +0x08..+0x10 is touched by this slice.
struct cExprFunction : cRefObj {
    uint32_t mId;                                                           // +0x08
    uint32_t mTypeId;                                                       // +0x0c
    uint32_t mKey;                                                          // +0x10
};

// The 12-byte {id, type, key} triple copied onto the stack for the manager.
struct ArgKey12 {
    uint32_t mId;                                                           // +0x00
    uint32_t mTypeId;                                                       // +0x04
    uint32_t mKey;                                                          // +0x08
};

// The command-variant argument block handed to the message handler.
struct ArgScriptValue {
    uint32_t mField00;                                                      // +0x00
    uint32_t mField04;                                                      // +0x04
    uint32_t mTypeId;                                                       // +0x08
    uint32_t mField0c;                                                      // +0x0c
    uint32_t mField10;                                                      // +0x10
    uint32_t mField14;                                                      // +0x14
    uint32_t mField18;                                                      // +0x18
};

// 64-bit composite key of the manager's hash_map.
struct Key8 {
    uint32_t mA;                                                            // +0x00
    uint32_t mB;                                                            // +0x04
};

// The iterator handed back by the map lookups (node + bucket slot).
struct MapIter {
    void* mpNode;                                                           // +0x00
    void* mpBucket;                                                         // +0x04
};

// A node of the Key8 hash_map: only the mapped handle at +0x08 is read.
struct Key8Node {
    uint8_t  pad00[8];
    uint32_t mHandle;                                                       // +0x08
};

// A node of the name-keyed hashtable: id at +0x10, chain link at +0x14.
struct NameNode {
    uint8_t  pad00[0x10];
    uint32_t mId;                                                           // +0x10
    void*    mpNext;                                                        // +0x14
};

// Result slot written by hashtable::DoInsertValue.
struct InsertResult {
    void*    mpNode;                                                        // +0x00
    void*    mpBucket;                                                      // +0x04
    uint8_t  mInserted;                                                     // +0x08
};

// Result of the rehash policy query.
struct RehashInfo {
    uint8_t  mRehash;                                                       // +0x00
    uint8_t  pad01[3];
    uint32_t mNewBucketCount;                                               // +0x04
};

// eastl::hash_map<Key8, H>.  end() is the slot just past the bucket array.
struct HashKey8 {
    uint32_t mField00;                                                      // +0x00
    void**   mpBucket;                                                      // +0x04
    uint32_t mnBucket;                                                      // +0x08
    void     find(MapIter* pIter, const Key8* pKey);                        // 0x0041fb20
    void**   operator[](const Key8* pKey);                                  // 0x0041cd60
    void     Insert(const Key8* pKey);                                      // 0x006a43b0
    void*    end() const { return mpBucket[mnBucket]; }
};

// Rehash policy sub-object of the name hashtable (four bytes, at +0x10).
struct HashPolicy {
    uint32_t mField00;                                                      // +0x00
    void GetNextBucketCount(void* pOut, uint32_t a, uint32_t b, int c);     // 0x00921440
};

// eastl hashtable keyed by a NUL-terminated name.
struct HashName {
    uint32_t   mField00;                                                    // +0x00
    void**     mpBucket;                                                    // +0x04
    uint32_t   mnBucket;                                                    // +0x08
    uint32_t   mnElement;                                                   // +0x0c
    HashPolicy mPolicy;                                                     // +0x10
    void       find(MapIter* pIter, const NameString* pKey);                // 0x007e2ea0
    void       DoInsertValue(InsertResult* pOut, const char* const* ppKey); // 0x006a5c50
    void       DoRehash(uint32_t n);                                        // 0x006a3fd0
    void*      AllocNode(const char* pKey);                                 // 0x006a4850
    void*      end() const { return mpBucket[mnBucket]; }
};

struct ArgMgr;

// ---------------------------------------------------------------------------
//  ArgMgr: the property-list manager that owns the maps.  Every method below
//  receives the manager itself; 006a58a0 instead receives the manager's
//  registered +0x0c view, modelled by ArgMgrView.
// ---------------------------------------------------------------------------
struct ArgMgr {
    uint8_t   pad00[0x18];                                                  // +0x00
    cExprMgr* mpExprMgr;                                                    // +0x18
    uint8_t   pad1c[0x58];                                                  // +0x1c .. +0x73
    HashKey8  mMap;                                                         // +0x74
    uint8_t   pad80[0x14];                                                  // +0x80 .. +0x93
    HashName  mExprMap;                                                     // +0x94
    uint8_t   padA8[0x2c];                                                  // +0xa8 .. +0xd3
    HashName  mPropMap;                                                     // +0xd4
    uint8_t   padE8[0x40];                                                  // +0xe8 .. +0x127
    HashName  mEnumMap;                                                     // +0x128
    uint8_t   pad13c[0x2c];                                                 // +0x13c .. +0x167
    NameString mNameBuf;                                                    // +0x168 (case-insensitive name)

    void RemoveHandle(int handle);                                          // 0x006a3dd0

    void FUN_006a59f0(ArgScriptValue* v);                                   // 0x006a59f0
    void FUN_006a5a90(int unused, int count, int* p);                       // 0x006a5a90
    void FUN_006a5b80(int count, int* p);                                   // 0x006a5b80
    bool FUN_006a5f70(const char* name, uint32_t* out);                     // 0x006a5f70
    bool FUN_006a5fd0(const char* name, uint32_t* out);                     // 0x006a5fd0
    bool FUN_006a60b0(int a, int b, void** out);                            // 0x006a60b0
    void SetArgument(cExprFunction* pValue, int a, int b);                   // 0x006a61c0
    bool FUN_006a6240(const char* name, uint32_t* out);                     // 0x006a6240
};

// The +0x0c view of ArgMgr that carries the message handler 006a58a0: its hash
// map is at +0x68 of this view (== ArgMgr + 0x74).  The handler re-derives the
// enclosing manager with the same -0x0c adjustment the original emits.
static const unsigned kArgMgrViewOffset = 0x0c;

struct ArgMgrView {
    uint8_t  pad00[0x0c];                                                   // +0x00
    uint8_t  pad0c[0x5c];                                                   // +0x0c .. +0x67
    HashKey8 mMap;                                                          // +0x68

    bool OnMessage(int msg, ArgScriptValue* v);                             // 0x006a58a0
    ArgMgr* owner() const;                                                  // the enclosing manager
};

inline ArgMgr* ArgMgrView::owner() const
{
    return (ArgMgr*)((char*)this - kArgMgrViewOffset);
}

extern "C" void* __cdecl SP_MessageServer();                                // 0x0067dcc0
extern "C" char  __cdecl FUN_00554fb0(const char* pKey, const void* pNode); // 0x00554fb0
extern "C" void  __cdecl FUN_006a4450(void* a, void* b, void* c);           // 0x006a4450

// ---------------------------------------------------------------------------
// 006a5690  void GetVariantTypeDescription(const Variant& v, String& out)
// ---------------------------------------------------------------------------
void GetVariantTypeDescription(const Variant& v, String& out)
{
    switch (v.mTypeId) {
    case 0x00: out.assign("unknown"); break;
    case 0x01: out.assign("bool"); break;
    case 0x02: out.assign("char8"); break;
    case 0x03: out.assign("char16"); break;
    case 0x05: out.assign("int8"); break;
    case 0x06: out.assign("uint8"); break;
    case 0x07: out.assign("int16"); break;
    case 0x08: out.assign("uint16"); break;
    case 0x09: out.assign("int32"); break;
    case 0x0a: out.assign("uint32"); break;
    case 0x0b: out.assign("int64"); break;
    case 0x0c: out.assign("uint64"); break;
    case 0x0d: out.assign("float"); break;
    case 0x0e: out.assign("double"); break;
    case 0x0f: out.assign("void*"); break;
    case 0x10: out.assign("void"); break;
    case 0x11: out.assign("IUnknownRC"); break;
    case 0x12: out.assign("string8"); break;
    case 0x13: out.assign("string16"); break;
    case 0x20: out.assign("key"); break;
    case 0x21: out.assign("flags"); break;
    case 0x22: out.assign("text"); break;
    case 0x30: out.assign("vector2"); break;
    case 0x31: out.assign("vector3"); break;
    case 0x32: out.assign("colorRGB"); break;
    case 0x33: out.assign("vector4"); break;
    case 0x34: out.assign("colorRGBA"); break;
    case 0x35: out.assign("matrix2"); break;
    case 0x36: out.assign("matrix3"); break;
    case 0x37: out.assign("matrix4"); break;
    case 0x38: out.assign("transform"); break;
    case 0x39: out.assign("bbox"); break;
    default: goto append_array;
    }
append_array:
    if (v.mFlags & 0x80)
        out.append(" array", "");
}

// ---------------------------------------------------------------------------
// @ 0x006a58a0
// ---------------------------------------------------------------------------
bool ArgMgrView::OnMessage(int msg, ArgScriptValue* v)
{
    cMessageServer* server = (cMessageServer*)SP_MessageServer();

    if (msg != 0x0f62ade)
        return false;

    if (v->mTypeId == 0x00b1b104) {
        Key8 key;
        key.mA = v->mField18;
        key.mB = v->mField10;

        MapIter iter;                       // the original leaves this unset too
        mMap.find(&iter, &key);
        if (iter.mpNode != mMap.end()) {
            uint32_t handle = ((Key8Node*)iter.mpNode)->mHandle;
            if (handle != 0)
                owner()->RemoveHandle((int)handle);
            else
                FUN_006a4450(&iter, iter.mpNode, iter.mpBucket);
        }
        server->v014(0x00f62def, v, 0);
        server->v018(0x016af8d8, v, 0, 0);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006a59f0
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a59f0(ArgScriptValue* v)
{
    void*     held = 0;
    uint32_t* pv   = &v->mTypeId;
    if (mpExprMgr->v014(pv, &held))
        VariantRelease((int*)held);

    Key8 key;
    key.mA = pv[0];
    key.mB = pv[2];
    mMap.Insert(&key);

    if (held)
        ((cRefObj*)held)->Release();
}

// ---------------------------------------------------------------------------
// @ 0x006a5a90
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a5a90(int unused, int count, int* p)
{
    (void)unused;
    void* held = 0;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            int val = p[i];
            if (held) {
                void* h = held;
                held = 0;
                ((cRefObj*)h)->Release();
            }
            char ok = mpExprMgr->v014(&val, &held);
            if (ok)
                VariantRelease((int*)held);

            Key8 key;
            key.mA = (uint32_t)val;
            key.mB = 0x00b1b104;
            mMap.Insert(&key);
        }
    }
    if (held)
        ((cRefObj*)held)->Release();
}

// ---------------------------------------------------------------------------
// @ 0x006a5b80
// ---------------------------------------------------------------------------
void ArgMgr::FUN_006a5b80(int count, int* p)
{
    void* held = 0;
    if (count > 0) {
        do {
            if (held) {
                void* h = held;
                held = 0;
                ((cRefObj*)h)->Release();
            }
            char ok = mpExprMgr->v014(p, &held);
            if (ok)
                VariantRelease((int*)held);

            Key8 key;
            key.mA = (uint32_t)p[0];
            key.mB = (uint32_t)p[2];
            mMap.Insert(&key);

            p += 3;
        } while (--count);
    }
    if (held)
        ((cRefObj*)held)->Release();
}

// ---------------------------------------------------------------------------
// 006a5c50  hashtable<basic_string, ...>::DoInsertValue
// ---------------------------------------------------------------------------
// @ 0x006a5c50
void HashName::DoInsertValue(InsertResult* pOut, const char* const* ppKey)
{
    uint32_t hash = 0x811c9dc5;
    const char* p = *ppKey;
    uint8_t c = (uint8_t)*p;
    while (c != 0) {
        p++;
        hash = hash * 0x1000193 ^ c;
        c = (uint8_t)*p;
    }

    uint32_t idx  = hash % mnBucket;
    void*    node = mpBucket[idx];
    void**   slot = &mpBucket[idx];

    while (node != 0) {
        if (FUN_00554fb0(*ppKey, node)) {
            if (node != 0) {
                pOut->mpNode     = node;
                pOut->mpBucket   = slot;
                pOut->mInserted  = 0;
                return;
            }
            break;
        }
        node = ((NameNode*)node)->mpNext;
    }

    RehashInfo info;
    mPolicy.GetNextBucketCount(&info, mnBucket, mnElement, 1);
    node = AllocNode(*ppKey);
    if (info.mRehash) {
        idx = hash % info.mNewBucketCount;
        DoRehash(info.mNewBucketCount);
    }

    ((NameNode*)node)->mpNext = mpBucket[idx];
    mpBucket[idx]             = node;
    mnElement++;

    pOut->mpNode    = node;
    pOut->mpBucket  = &mpBucket[idx];
    pOut->mInserted = 1;
}

// ---------------------------------------------------------------------------
// @ 0x006a5f70
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a5f70(const char* name, uint32_t* out)
{
    EA::ArgScript::MakeCaseInsensitive(name, &mNameBuf);

    MapIter iter;
    mExprMap.find(&iter, &mNameBuf);
    if (iter.mpNode != mExprMap.end()) {
        *out = ((NameNode*)iter.mpNode)->mId;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x006a5fd0
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a5fd0(const char* name, uint32_t* out)
{
    unsigned n = (unsigned)(strlen(name) + 1);
    char*    p;
    char*    end;
    if (n < 2) {
        p   = (char*)0x01667bac;
        end = (char*)0x01667bad;
    } else {
        p   = (char*)EA_Alloc(n, "App", 0, 0, kAllocPath, 0xd1);
        end = p + n;
    }
    NameString key;
    key.mpBegin    = p;
    key.mpEnd      = p + strlen(name);
    key.mpCapacity = end;

    DoInsertValue(p, name, (int)strlen(name));
    p[strlen(name)] = 0;

    MapIter iter;
    mPropMap.find(&iter, &key);
    if (1 < (int)(end - p) && p != 0)
        EA_Dealloc(p);

    if (iter.mpNode != mPropMap.end()) {
        *out = ((NameNode*)iter.mpNode)->mId;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x006a60b0
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a60b0(int a, int b, void** out)
{
    Key8 key;
    key.mA = (uint32_t)a;
    key.mB = (uint32_t)b;

    ArgKey12 value;
    value.mId     = (uint32_t)a;
    value.mTypeId = 0x00b1b104;
    value.mKey    = (uint32_t)b;

    MapIter iter;
    mMap.find(&iter, &key);

    char ok = 0;
    if (iter.mpNode == mMap.end()) {
        ok = mpExprMgr->v00c(&value, out, 0, 0, 0, 0);
        if (ok) {
            RemoveHandle((int)*out);
            cExprFunction* fresh = (cExprFunction*)*out;
            void**          slot  = mMap[&key];
            cExprFunction*  old   = (cExprFunction*)*slot;
            if (fresh != old) {
                if (fresh)
                    fresh->Hold();
                *slot = fresh;
                if (old)
                    old->Release();
            }
        } else {
            void**          slot = mMap[&key];
            cExprFunction*  old  = (cExprFunction*)*slot;
            if (old) {
                *slot = 0;
                old->Release();
            }
        }
    } else {
        uint32_t handle = ((Key8Node*)iter.mpNode)->mHandle;
        if (handle != 0) {
            *out = (void*)handle;
            ((cRefObj*)handle)->Hold();
            ok = 1;
        }
    }
    return ok != 0;
}

// ---------------------------------------------------------------------------
// @ 0x006a61c0
// ---------------------------------------------------------------------------
void ArgMgr::SetArgument(cExprFunction* pValue, int a, int b)
{
    pValue->mId     = (uint32_t)a;
    pValue->mTypeId = 0x00b1b104;
    pValue->mKey    = (uint32_t)b;
    VariantHold((int*)pValue);

    Key8 key;
    key.mA = (uint32_t)a;
    key.mB = (uint32_t)b;
    void**          slot = mMap[&key];
    cExprFunction*  old  = (cExprFunction*)*slot;
    if (pValue != old) {
        pValue->Hold();
        *slot = pValue;
        if (old)
            old->Release();
    }
}

// ---------------------------------------------------------------------------
// @ 0x006a6240
// ---------------------------------------------------------------------------
bool ArgMgr::FUN_006a6240(const char* name, uint32_t* out)
{
    EA::ArgScript::MakeCaseInsensitive(name, &mNameBuf);

    if (isdigit((unsigned char)*name)) {
        *out = (uint32_t)strtoul(name, 0, 0);
        return true;
    }

    MapIter iter;
    mEnumMap.find(&iter, &mNameBuf);
    if (iter.mpNode != mEnumMap.end()) {
        *out = ((NameNode*)iter.mpNode)->mId;
        return true;
    }

    mExprMap.find(&iter, &mNameBuf);
    if (iter.mpNode != mExprMap.end()) {
        *out = ((NameNode*)iter.mpNode)->mId;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006a5e10  vector<basic_string>: element 0x10
// ---------------------------------------------------------------------------
struct Vec10s {
    void* begin; void* end; void* cap;
    Vec10s* Init(unsigned n, const void* value);
    void Alloc(unsigned n, const void* value);   // 0x007c7a40
};
// @ 0x006a5e10
Vec10s* Vec10s::Init(unsigned n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    tmp[0] = 0x01667bac;
    tmp[1] = 0x01667bac;
    tmp[2] = 0x01667bad;
    tmp[3] = 0;
    UninitFillN16(begin, n, tmp, value);
    end = (char*)begin + n * 0x10;
    return this;
}

// ---------------------------------------------------------------------------
// 006a5ea0  vector<0x38>: element 0x38
// ---------------------------------------------------------------------------
struct Vec38b {
    void* begin; void* end; void* cap;
    Vec38b* Init(unsigned n, const void* value);
    void Alloc(unsigned n, const void* value);   // 0x006a4130
};
// @ 0x006a5ea0
struct Fill38 {
    uint16_t   mZero0;      // +0x00
    uint16_t   mZero2;      // +0x02
    Vector3    mPosition;   // +0x04
    float      mOne;        // +0x10
    cSPMatrix3 mMatrix;     // +0x14
};
Vec38b* Vec38b::Init(unsigned n, const void* value)
{
    Alloc(n, value);
    Fill38 tmp;
    tmp.mZero0 = 0;
    tmp.mZero2 = 0;
    tmp.mPosition = kDefaultVector3;
    tmp.mOne = g_01485720;
    tmp.mMatrix.Assign(g_01602b10);
    UninitFillN56(begin, n, &tmp, value);
    end = (char*)begin + n * 0x38;
    return this;
}

// ---------------------------------------------------------------------------
// 006a6310  vector<uint32_t>: element 4
// ---------------------------------------------------------------------------
struct VecU32 {
    void* begin; void* end; void* cap;
    VecU32* Init(unsigned n, const void* alloc);
    void Alloc(unsigned n, const void* alloc);   // 0x004aa350
};
VecU32* VecU32::Init(unsigned n, const void* alloc)
{
    Alloc(n, alloc);
    uint32_t* p = (uint32_t*)begin;
    for (unsigned i = 0; i < n; i++)
        p[i] = 0;
    end = (void*)((uint32_t)begin + n * 4);
    return this;
}