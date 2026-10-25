// Slice s00eeebd0 — Simulator/creator-editor EASTL helpers.
// Ten functions @ 0x00eeebd0..0x00eef7d0: a resource-hash dispatcher, EASTL
// vector<Key_>/vector<Entry32> operations (erase/DoInsertValue/push_back), an
// editor-model refresh, a planet-model placement pass and a loop driver.
#include "types.h"

typedef unsigned int size_type;

// ---------------------------------------------------------------------------
// Masked externals (callees / globals are relocations, so any matching
// convention works).  These are declared, never defined.
// ---------------------------------------------------------------------------
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void operator delete(void* p);
inline void* operator new(unsigned int, void* p) { return p; }

namespace eastl {
template <typename T>
T* uninitialized_move(T* first, T* last, T* dest);
template <typename T>
__forceinline T* move_backward(T* first, T* last, T* dest) {
    while (last != first)
        *--dest = *--last;
    return dest;
}
}  // namespace eastl

static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---------------------------------------------------------------------------
// Element types.
// ---------------------------------------------------------------------------
struct Key_ {  // EA::ResourceMan::Key_ — 12 bytes
    uint32_t mType;
    uint32_t mIdLo;
    uint32_t mIdHi;
};

struct Vec3 {  // float triple with a user copy ctor (fld/fstp flavour)
    float x;
    float y;
    float z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Entry32 {  // 32 bytes: int + 7 floats, user copy ctor / trivial operator=
    uint32_t mA;
    float mB;
    float mC;
    float mD;
    float mE;
    float mF;
    float mG;
    float mH;
    Entry32() {}
    __forceinline Entry32(const Entry32& x) {
        mB = x.mB;
        mA = x.mA;
        mC = x.mC;
        mD = x.mD;
        mE = x.mE;
        mF = x.mF;
        mG = x.mG;
        mH = x.mH;
    }
};

// ---------------------------------------------------------------------------
// Allocators.
// ---------------------------------------------------------------------------
struct KeyAllocator {  // deallocate compares the block against a pool word
    void* mData[2];
    void deallocate(void* p, size_type) {
        if (p != mData[1])
            ::operator delete(p);
    }
};

struct SPVectorAllocator {  // SP's header-tracked allocator
    void* mData[2];
    void deallocate(void* p, size_type) {
        if (((uint32_t*)p)[-1])
            ::operator delete(p);
    }
};

template <typename T, typename A>
struct Vector;
template <typename T, typename A>
void VectorDoInsertValue(Vector<T, A>* v, T* position, const T& value);

template <typename T, typename A>
struct Vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    size_type GetNewCapacity(size_type currentCapacity) {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
    T* DoAllocate(size_type n) {
        return n ? (T*)::operator new(n * sizeof(T), "Simulator", 0, 0, kAllocFile, 0xd1) : 0;
    }
    void DoFree(T* p, size_type n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }

    // @ 0x00eeee40
    T* erase(T* position) {
        T* const pEnd = mpEnd;
        if (position + 1 < pEnd) {
            T* dest = position;
            T* src = position + 1;
            do {
                *dest = *src;
                ++src;
                ++dest;
            } while (src != pEnd);
        }
        --mpEnd;
        return position;
    }

    // @ 0x00eef110
    void push_back(const T& value) {
        T* pEnd = mpEnd;
        if (pEnd < mpCapacity) {
            mpEnd = pEnd + 1;
            if (pEnd)
                ::new ((void*)pEnd) T(value);
        } else {
            VectorDoInsertValue(this, mpEnd, value);
        }
    }
};

typedef Vector<Key_, KeyAllocator> KeyVector;
typedef Vector<Entry32, SPVectorAllocator> EntryVector;

// Shared body of the two DoInsertValue specializations.  The marker above each
// wrapper below binds one VA to one emitted symbol (a single templated
// definition would carry two VAs on one line and the resolver would map both
// instantiations to the first address).
template <typename T, typename A>
void VectorDoInsertValue(Vector<T, A>* v, T* position, const T& value) {
    if (v->mpEnd != v->mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < v->mpEnd))
            ++pValue;
        if (v->mpEnd)
            ::new ((void*)v->mpEnd) T(*(v->mpEnd - 1));
        eastl::move_backward(position, v->mpEnd - 1, v->mpEnd);
        *position = *pValue;
        ++v->mpEnd;
    } else {
        const size_type nPrevSize = size_type(v->mpEnd - v->mpBegin);
        const size_type nNewSize = v->GetNewCapacity(nPrevSize);
        T* const pNewData = v->DoAllocate(nNewSize);
        T* pNewEnd = eastl::uninitialized_move<T>(v->mpBegin, position, pNewData);
        if (pNewEnd)
            ::new ((void*)pNewEnd) T(value);
        pNewEnd = eastl::uninitialized_move<T>(position, v->mpEnd, pNewEnd + 1);
        v->DoFree(v->mpBegin, size_type(v->mpCapacity - v->mpBegin));
        v->mpBegin = pNewData;
        v->mpEnd = pNewEnd;
        v->mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00eeee80
void DoInsertValue_Key(KeyVector* v, Key_* position, const Key_& value) {
    VectorDoInsertValue(v, position, value);
}

// @ 0x00eeefb0
void DoInsertValue_Entry32(EntryVector* v, Entry32* position, const Entry32& value) {
    VectorDoInsertValue(v, position, value);
}

// Force the four instantiations.
template struct Vector<Key_, KeyAllocator>;
template struct Vector<Entry32, SPVectorAllocator>;

// ---------------------------------------------------------------------------
// @ 0x00eef7d0
// ---------------------------------------------------------------------------
struct EditorModelList {
    char pad0[0x28];
    int mBegin;  // +0x28
    int mEnd;    // +0x2c
};

struct EditorModel;
extern void FUN_00eef170(void* model, int index);

// @ 0x00eef7d0
void FUN_00eef7d0(EditorModelList* list) {
    const int n = (list->mEnd - list->mBegin) / 0x34;
    for (int i = 0; i < n; ++i)
        FUN_00eef170(list, i);
}

// ===========================================================================
// Behavioural reconstructions of the five remaining slice functions.  The
// original bodies are heavily inlined (SSE/x87 mixed) EASTL/editor code; the
// names below were recovered from the instruction stream and every touched
// field/global is named, but the code is not byte-exact.
// ===========================================================================

// ---- shared editor / resource types ---------------------------------------
struct Vec3List {          // 12-byte elements, full EASTL vector layout
    Vec3* mpBegin;         // +0x00
    Vec3* mpEnd;           // +0x04
    Vec3* mpCapacity;      // +0x08
    void* mAllocData[2];   // +0x0c
    uint32_t mExtra;       // +0x14
    void PushBack(const Vec3& v) {
        if (mpEnd >= mpCapacity) {
            // full: the original calls the vector's out-of-line DoInsertValue
            ((void(__thiscall*)(Vec3List*, Vec3*, const Vec3*))0x4b5ad0)(
                this, mpEnd, &v);
        } else {
            Vec3* slot = mpEnd;
            mpEnd = (Vec3*)((char*)slot + 12);
            if (slot)
                *slot = v;
        }
    }
};

struct ModelRecord {       // 0x34 bytes per editor model
    float mColor;          // +0x00
    char pad04[0x1c - 0x04];
    Vec3List mPoints;      // +0x1c
};

struct EditorModel {
    int mId;               // +0x00
    Vec3 mBase;            // +0x04
    Vec3 mDir;             // +0x10
    char pad1c[0x20 - 0x1c];
    float mField20;        // +0x20
    char pad24[0x28 - 0x24];
    ModelRecord* mpRecords;// +0x28
    char pad2c[0x1e8 - 0x2c];
    Vec3 mSurfacePoint;    // +0x1e8
    float mSurface1;       // +0x1f4
    float mSurface2;       // +0x1f8
    float mSurface3;       // +0x1fc
    float mSurface4;       // +0x200
    float mField204;       // +0x204
};

// Type table entry returned by the resource manager.
struct EditorResEntry {
    char pad0[0x18];
    float mScale;          // +0x18
    char pad1c[0x24 - 0x1c];
    uint32_t mTypeId;      // +0x24
};

struct ResEntryVec {
    void** mpBegin;        // +0x00
    void** mpEnd;          // +0x04
    void** mpCapacity;     // +0x08
};

struct ResourceHandle {
    void* mpObj;           // +0x00
};

struct ResourceMgr18 {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void Lookup(const void* key, ResourceHandle* out,
                        int a, int b, int c, int d);  // +0x0c
};

struct Profile18 {
    char pad0[0x56c];
    float mField56c;       // +0x56c
};

struct PlanetSurface18 {
    Vec3* BuildPoint(Vec3* out, const Vec3* pos);   // 0x00b816f0 (ret 8)
    float* BuildFrame(Vec3* out, const Vec3* pos);  // 0x00b7f190 (ret 8)
};

// ---- editor model set (0x238-byte records) --------------------------------
struct ModelSelection {
    unsigned mFlags0;       // +0x00
    Vec3 mPos;              // +0x04
    Vec3 mDir;              // +0x10
    char pad1c[0x208 - 0x1c];
    unsigned char mbFlag208;// +0x208
};

struct ModelRec238 {
    unsigned mFlags0;       // +0x00
    Vec3 mPos;              // +0x04
    Vec3 mDir;              // +0x10
    char pad1c[0x208 - 0x1c];
    unsigned char mbFlag208;// +0x208
    char pad209[0x20c - 0x209];
    unsigned char mbFlag20c;// +0x20c
    char pad20d[0x238 - 0x20d];
};

struct ModelSetColl {
    char pad0[0x2c10];
    ModelRec238* mpBegin;   // +0x2c10
    ModelRec238* mpEnd;     // +0x2c14
    char pad18[0x2c24 - 0x2c18];
    unsigned mIndex;        // +0x2c24
};

struct ModelSet {
    char pad0[0x10];
    ModelSetColl* mpColl;   // +0x10
};

typedef void* (__thiscall* ModelLookupFn)(void*, int);       // 0x00f3e8a0
typedef void* (__thiscall* GetSelectionFn)(void*);           // 0x00ff3f00

struct ModelMgr {
    char pad0[0x74];
    ModelSet* mpSet;        // +0x74
};

static ModelRec238* RecordBegin(ModelSetColl* coll) {
    if (coll->mIndex < 0x3fffffffu)
        return coll->mpBegin + coll->mIndex;
    return coll->mpEnd;
}

// Advance the record iterator; records tagged bit31 are skipped without being
// touched, and bit30 of the record just left ends the skip run.
static ModelRec238* NextRecord(ModelRec238* r) {
    for (;;) {
        unsigned f = r->mFlags0;
        ++r;
        if (f & 0x40000000u)
            return r;
        if (r->mFlags0 & 0x80000000u)
            continue;
        return r;
    }
}

// Masked callees (declarations only).
extern "C" void* FUN_00401090(void* out);
extern "C" void* FUN_004df550(void* p);
extern "C" int FUN_00c028b0(void* p, int a);
extern "C" float FUN_004d12a0(int x);
extern "C" float FUN_00bcd420();
extern "C" void* FUN_0067dcd0();               // resource manager getter
extern "C" void* FUN_00421eb0(ResourceHandle* h);
extern "C" void FUN_00433210(void* entry, ResEntryVec* out);
extern "C" void FUN_004e7610(ResEntryVec* in, ResEntryVec* out, float field18);
extern "C" void* FUN_00eec9c0(void* first, void* last, void* dest);  // uninit_move<Entry32>
extern "C" Vec3* FUN_0059aed0(Vec3* out, const int* tag, const Vec3* dir);
extern "C" PlanetSurface18* FUN_00b3d350();   // planet-model getter
extern "C" void FUN_00f47380(void* p);  // operator delete

static float RoundUpToInt(float f) {
    int i = (int)f;
    if ((float)i < f)
        ++i;
    return (float)i;
}

extern float g_16c7a04;
extern float g_16c7a14;
extern float g_16c79f4;
extern int g_16c7a4c;
extern int g_16c7aa4;
extern int g_16c7a58;

// @ 0x00eeebd0
// Float "editor model value" lookup by resource-key hash.  Four key branches
// (x100, species scale, profile scale, editor-resource entry scan); falls back
// to 10.0f.
float FUN_00eeebd0(int a1, uint32_t key, int a3, float scale) {
    (void)a3;
    switch (key) {
        case 0x476a98c7:
            return RoundUpToInt(scale * 100.0f);

        case 0x2399be55:
            return RoundUpToInt(FUN_00bcd420() * scale);

        case 0x2b978c46: {
            void* h = FUN_00401090(&a1);
            Profile18* profile = (Profile18*)FUN_004df550(h);
            if (profile) {
                float v = FUN_004d12a0(FUN_00c028b0(profile, 0)) + profile->mField56c;
                return RoundUpToInt(v * scale);
            }
            break;
        }

        case 0x24682294: {
            // ResourceMan lookup of an editor resource, scan its entry vector
            // for the record with typeID 0x34d6bd1e and scale its field.
            ResourceMgr18* mgr = (ResourceMgr18*)FUN_0067dcd0();
            ResourceHandle handle = {0};
            mgr->Lookup(&a1, &handle, 0, 0, 0, 0);
            if (!handle.mpObj)
                break;

            EditorResEntry* entry = (EditorResEntry*)FUN_00421eb0(&handle);
            float result = 10.0f;
            if (entry) {
                ResEntryVec vec1 = {0, 0, 0};
                FUN_00433210(entry, &vec1);
                ResEntryVec vec2 = {0, 0, 0};
                FUN_004e7610(&vec1, &vec2, entry->mScale);
                int count = int(vec2.mpEnd - vec2.mpBegin);
                for (int i = 0; i < count; ++i) {
                    EditorResEntry* e = (EditorResEntry*)vec2.mpBegin[i];
                    if (e && e->mTypeId == 0x34d6bd1e) {
                        result = RoundUpToInt(e->mScale * scale);
                        break;
                    }
                }
                ((void(__thiscall*)(void*))0x4b5440)(&vec2);
                ((void(__thiscall*)(void*))0x4cddd0)(&vec1);
            }
            // drop the handle's reference
            void** vt = *(void***)handle.mpObj;
            ((void(__thiscall*)(void*))vt[1])(handle.mpObj);
            return result;
        }
    }
    return 10.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00eef170
// Fill the index-th 0x34-byte editor model record: seed the colour, look up
// the model type, refresh the point list, append the transformed point and
// store the planet-surface orientation and frame.
__declspec(noinline) void FUN_00eef170(void* modelRaw, int index) {
    EditorModel* model = (EditorModel*)modelRaw;
    ModelRecord* rec = (ModelRecord*)((char*)model->mpRecords + index * 0x34);
    rec->mColor = g_16c7a04;

    ModelMgr* mgr = (ModelMgr*)g_16c7aa4;
    EditorResEntry* type = (EditorResEntry*)((ModelLookupFn)0x00f3e8a0)(
        mgr->mpSet, model->mId);
    if (type && type->mTypeId == 0x24682294)
        rec->mColor = g_16c7a14;

    // refresh the record's point list (inlined eastl copy over its own range)
    ((void(__thiscall*)(Vec3List*, Vec3*, Vec3*))0x50f740)(
        &rec->mPoints, rec->mPoints.mpBegin, rec->mPoints.mpEnd);

    const float s = g_16c79f4;
    Vec3 tmp;
    Vec3* d = FUN_0059aed0(&tmp, &g_16c7a4c, &model->mDir);
    Vec3 p;
    p.x = model->mBase.x + d->x * s;
    p.y = model->mBase.y + d->y * s;
    p.z = model->mBase.z + d->z * s;
    rec->mPoints.PushBack(p);

    d = FUN_0059aed0(&tmp, &g_16c7a4c, &model->mDir);
    Vec3 p2;
    p2.x = model->mBase.x + d->x * s;
    p2.y = model->mBase.y + d->y * s;
    p2.z = model->mBase.z + d->z * s;
    model->mSurfacePoint = p2;

    // The getter takes no arguments; the two pushed values are the arguments
    // for the following thiscall (which pops them with ret 8).
    Vec3 out;
    PlanetSurface18* surf = FUN_00b3d350();
    surf->BuildPoint(&out, &model->mSurfacePoint);
    model->mSurfacePoint = out;
    surf = FUN_00b3d350();
    float* frame = surf->BuildFrame(&out, &model->mSurfacePoint);
    model->mSurface1 = frame[0];
    model->mSurface2 = frame[1];
    model->mSurface3 = frame[2];
    model->mSurface4 = frame[3];
    model->mField204 = model->mField20;
}

// ---------------------------------------------------------------------------
// @ 0x00eef330
// Editor-model list helper: gather the current key range, build a temporary
// vector<Key_>, find/dedup the incoming key (cap 0x80), push it and hand the
// list back to the caller's collector.
// ---------------------------------------------------------------------------
extern "C" void FUN_006a0ae0(void* a, void* b, Key_** outBegin, unsigned* outCount);
extern "C" void* FUN_00ac0d80(void* first, void* last, void* key);
extern "C" void FUN_006a0ee0(void* a, void* b, int n, void* p);

void FUN_00eef330(void* param_1, Key_* key) {
    Key_* begin = 0;
    unsigned count = 0;
    FUN_006a0ae0(param_1, (void*)g_16c7a58, &begin, &count);

    KeyVector tmp;
    tmp.mpBegin = tmp.mpEnd = tmp.mpCapacity = 0;
    tmp.mAllocator.mData[0] = tmp.mAllocator.mData[1] = 0;
    ((void(__thiscall*)(KeyVector*, Key_*, Key_*, Key_*))0xeee970)(
        &tmp, begin, begin + count, begin);

    Key_* found = (Key_*)FUN_00ac0d80(tmp.mpBegin, tmp.mpEnd, key);
    if (found != tmp.mpEnd)
        tmp.erase(found);
    else if (size_type(tmp.mpEnd - tmp.mpBegin) == 0x80)
        tmp.erase(tmp.mpBegin);

    if (tmp.mpEnd < tmp.mpCapacity)
        *tmp.mpEnd++ = *key;
    else
        VectorDoInsertValue(&tmp, tmp.mpEnd, *key);

    FUN_006a0ee0(param_1, (void*)g_16c7a58,
                 int(tmp.mpEnd - tmp.mpBegin), tmp.mpBegin);
    tmp.DoFree(tmp.mpBegin, size_type(tmp.mpCapacity - tmp.mpBegin));
}

// ---------------------------------------------------------------------------
// @ 0x00eef4b0
// Walk the active model set's record array (stride 0x238) clearing the per
// record flag, then clear the selection flag and empty the output vector.
void FUN_00eef4b0(EntryVector* vec) {
    ModelMgr* mgr = (ModelMgr*)g_16c7aa4;
    ModelSet* set = mgr->mpSet;
    ModelSetColl* coll = set->mpColl;

    ModelRec238* begin = RecordBegin(coll);
    ModelRec238* end = coll->mpEnd;
    if (begin != end) {
        ModelRec238* r = begin;
        for (;;) {
            r->mbFlag20c = 0;
            r = NextRecord(r);
            if (r == end)
                break;
        }
    }

    if (((GetSelectionFn)0x00ff3f00)(set))
        ((ModelSelection*)((GetSelectionFn)0x00ff3f00)(set))->mbFlag208 = 0;

    // Collapse the output vector by whole 32-byte entries (the original
    // computes a byte count, truncates to elements and subtracts it).
    int bytes = int((char*)vec->mpEnd - (char*)vec->mpBegin);
    vec->mpEnd = (Entry32*)((char*)vec->mpEnd - ((bytes >> 5) << 5));
}

// ---------------------------------------------------------------------------
// Apply the current gadget to every editor model record, then to the selected
// model; appends transformed entry records to the output vector.
// ---------------------------------------------------------------------------
struct Gadget {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void* Get(uint32_t id);           // +0x0c
    virtual void* s4(int);
    virtual void* s5(int);
    virtual void* s6(int);
    virtual void* s7(int);
    virtual void* s8(int);
    virtual void* s9(int);
    virtual void* s10(int);
    virtual void* Select(void* x);            // +0x2c
    virtual void* Build(void* a, void* b, void* c, void* d);  // +0x30
    char pad0[0x4c];                          // vptr occupies +0x00
    unsigned mFlags50;                        // +0x50
};

typedef int (__thiscall* ModelReadyFn)(void*);   // 0x006c0200
extern "C" char FUN_00eedc10(void* a, void* b);
extern "C" void FUN_00eee530(void* a, void* b);
extern float g_16c78cc, g_16c78d0, g_16c78d4;
extern float g_15ac960, g_15ac964, g_15ac968, g_15ac96c;

typedef void* (__thiscall* GetGadgetFn)(void*, int);

// @ 0x00eef570
void FUN_00eef570(void* modelRaw, EntryVector* vec) {
    FUN_00eef4b0(vec);

    ModelMgr* mgr = (ModelMgr*)g_16c7aa4;
    ModelSet* set = mgr->mpSet;
    ModelSetColl* coll = set->mpColl;
    if (!modelRaw)
        return;

    int ok = ((ModelReadyFn)0x006c0200)(modelRaw);
    void** vt = *(void***)modelRaw;
    Gadget* gadget = (Gadget*)((GetGadgetFn)vt[3])(modelRaw, 0x1186577);
    if (!ok || !(gadget->mFlags50 & 0x2000))
        return;

    Vec3 a;
    a.x = g_16c78cc;
    a.y = g_16c78d0;
    a.z = g_16c78d4;
    float b[4] = {g_15ac960, g_15ac964, g_15ac968, g_15ac96c};

    ModelRec238* begin = RecordBegin(coll);
    ModelRec238* end = coll->mpEnd;
    for (ModelRec238* r = begin; r != end; r = NextRecord(r)) {
        if (!FUN_00eedc10(&r->mPos, gadget))
            continue;
        void* built = gadget->Build(&r->mPos, &r->mDir, &a, b);
        FUN_00eee530(gadget->Select(built), built);
        Entry32 e;
        e.mA = (uint32_t)&r->mPos;
        e.mB = g_16c78cc;
        e.mC = g_16c78d0;
        e.mD = g_16c78d4;
        e.mE = g_15ac960;
        e.mF = g_15ac964;
        e.mG = g_15ac968;
        e.mH = g_15ac96c;
        vec->push_back(e);
        r->mbFlag208 = 1;
    }

    if (((GetSelectionFn)0x00ff3f00)(set)) {
        ModelSelection* sel = (ModelSelection*)((GetSelectionFn)0x00ff3f00)(set);
        if (!FUN_00eedc10(sel, gadget))
            return;
        void* built = gadget->Build(&sel->mPos, &sel->mDir, &a, b);
        FUN_00eee530(gadget->Select(built), built);
        Entry32 e;
        e.mA = (uint32_t)sel;
        e.mB = g_16c78cc;
        e.mC = g_16c78d0;
        e.mD = g_16c78d4;
        e.mE = g_15ac960;
        e.mF = g_15ac964;
        e.mG = g_15ac968;
        e.mH = g_15ac96c;
        vec->push_back(e);
        sel->mbFlag208 = 1;
    }
}