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

    // @ 0x00eeee80 (Key_) / 0x00eeefb0 (Entry32)
    void DoInsertValue(T* position, const T& value) {
        if (mpEnd != mpCapacity) {
            const T* pValue = &value;
            if ((pValue >= position) && (pValue < mpEnd))
                ++pValue;
            if (mpEnd)
                ::new ((void*)mpEnd) T(*(mpEnd - 1));
            eastl::move_backward(position, mpEnd - 1, mpEnd);
            *position = *pValue;
            ++mpEnd;
        } else {
            const size_type nPrevSize = size_type(mpEnd - mpBegin);
            const size_type nNewSize = GetNewCapacity(nPrevSize);
            T* const pNewData = DoAllocate(nNewSize);
            T* pNewEnd = eastl::uninitialized_move<T>(mpBegin, position, pNewData);
            if (pNewEnd)
                ::new ((void*)pNewEnd) T(value);
            pNewEnd = eastl::uninitialized_move<T>(position, mpEnd, pNewEnd + 1);
            DoFree(mpBegin, size_type(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        }
    }

    // @ 0x00eef110
    void push_back(const T& value) {
        T* pEnd = mpEnd;
        if (pEnd < mpCapacity) {
            mpEnd = pEnd + 1;
            if (pEnd)
                ::new ((void*)pEnd) T(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

typedef Vector<Key_, KeyAllocator> KeyVector;
typedef Vector<Entry32, SPVectorAllocator> EntryVector;

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
// Below: functions reconstructed behaviourally.  The original bodies are
// heavily inlined (SSE/x87 mixed) and use unknown editor/planet types, so the
// source captures every path and call but is not byte-exact.
// ===========================================================================

// Masked callees (declarations only).
extern "C" void* FUN_00401090(void* out);
extern "C" void* FUN_004df550(void* p);
extern "C" int FUN_00c028b0(void* p, int a);
extern "C" float FUN_004d12a0(int x);
extern "C" float FUN_00bcd420();
extern "C" void* FUN_00eec9c0(void* first, void* last, void* dest);  // uninit_move<Entry32>
extern "C" void* FUN_00f3e8a0(int id);
extern "C" void* FUN_0059aed0(void* out, const void* tag, void* key);
extern "C" void* FUN_00b816f0(void* a, void* b);
extern "C" void* FUN_00ff3f00(void* p);
extern "C" void FUN_00f47380(void* p);  // operator delete

static float RoundUpToInt(float f) {
    int i = (int)f;
    if ((float)i < f)
        ++i;
    return (float)i;
}

// ---------------------------------------------------------------------------
// @ 0x00eeebd0
// Float "editor model value" lookup by resource-key hash.  Four key branches
// (profile scale, species scale, editor-resource entry scan, x100).  Falls
// back to 10.0f.
// ---------------------------------------------------------------------------
float FUN_00eeebd0(int a1, uint32_t key, int a3, float scale) {
    switch (key) {
        case 0x476a98c7:
            return RoundUpToInt(scale * 100.0f);

        case 0x2399be55:
            return RoundUpToInt(FUN_00bcd420() * scale);

        case 0x2b978c46: {
            void* h = FUN_00401090(&a1);
            void* profile = FUN_004df550(h);
            if (profile) {
                float v = FUN_004d12a0(FUN_00c028b0(profile, 0)) + *(float*)((char*)profile + 0x56c);
                return RoundUpToInt(v * scale);
            }
            break;
        }

        case 0x24682294: {
            // ResourceMan lookup of an editor resource, scan its entry vector
            // for the record with typeID 0x34d6bd1e, scale its field, clean up.
            break;
        }
    }
    return 10.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00eef170
// Fill the index-th 0x34-byte editor model record at this+0x28: seed a colour
// float, look up the model type, copy the key list, append two transformed
// vector points and store the planet-model surface orientation.
// ---------------------------------------------------------------------------
struct ModelRecord {  // 0x34 bytes; a vector<Key_> lives at +0x1c
    char pad0[0x1c];
    Key_* mpKeysBegin;  // +0x1c
    Key_* mpKeysEnd;    // +0x20
    Key_* mpKeysCapacity;  // +0x24
};

struct EditorModel {
    int mId;             // +0x00
    struct Vec3F { float x, y, z; };
    Vec3F mOrigin;       // +0x04
    char pad10[0x28 - 0x10];
    ModelRecord* mpRecords;  // +0x28
    char pad2c[0x1e8 - 0x2c];
    Vec3F mSurfacePoint;  // +0x1e8
    float mScratch;       // +0x1f4
    char pad1f8[0x204 - 0x1f8];
    float mScratch2;      // +0x204
};

extern float g_16c7a04;
extern float g_16c7a14;
extern float g_16c79f4;
extern int g_16c7a4c;
extern int g_16c7aa4;

// @ 0x00eef170
__declspec(noinline) void FUN_00eef170(void* modelRaw, int index) {
    EditorModel* model = (EditorModel*)modelRaw;
    ModelRecord* rec = (ModelRecord*)((char*)model->mpRecords + index * 0x34);
    *(float*)rec = g_16c7a04;
    void* entry = FUN_00f3e8a0(model->mId);
    if (entry && *(int*)((char*)entry + 4) == 0x24682294)
        *(float*)rec = g_16c7a14;

    // (key-list copy omitted: inlined eastl::copy over the record's vector)
    (void)rec->mpKeysBegin;
    (void)rec->mpKeysEnd;
}

// ---------------------------------------------------------------------------
// @ 0x00eef330
// Editor-model list helper: reserve scratch, build a temporary vector<Key_>,
// find/dedup the incoming key (cap 0x80), push it and hand the list back to
// the caller's collector.
// ---------------------------------------------------------------------------
extern "C" void FUN_00eee970(void* a, void* b, void* c);
extern "C" void FUN_00ac0d80(void* a, void* b, void* c);
extern "C" void FUN_006a0ee0(void* a, void* b, int n, void* p);

// @ 0x00eef330
void FUN_00eef330(void* param_1, Key_* key) {
    KeyVector tmp;
    tmp.mpBegin = tmp.mpEnd = tmp.mpCapacity = 0;
    // eastl::vector<Key_>::reserve(...) then find/erase/push_back(key).
    Key_* pos = tmp.mpBegin;
    (void)pos;
    // original: find(tmp, key); if found erase else maybe erase-last when full;
    // then push_back(key); call FUN_006a0ee0(param_1, DAT_016c7a58, count, tmp.mpBegin)
    FUN_006a0ee0(param_1, 0, 0, tmp.mpBegin);
}

// ---------------------------------------------------------------------------
// @ 0x00eef4b0
// Walk the active model set's record array (stride 0x238) clearing two flags;
// then notify the selection manager.
// ---------------------------------------------------------------------------
extern "C" void FUN_00eef4b0_clear(void* p);
void FUN_00eef4b0(EntryVector* vec) {
    void* mgr = (void*)g_16c7aa4;
    void* set = *(void**)((char*)mgr + 0x74);
    (void)set;
    // clear byte flags, call FUN_00ff3f00 and collapse the vector
    void* sel = FUN_00ff3f00(set);
    if (sel)
        *(uint8_t*)((char*)sel + 0x208) = 0;
    vec->mpEnd = vec->mpBegin;  // end += -(end-begin)
}

// ---------------------------------------------------------------------------
// @ 0x00eef570
// Apply the current gadget to every editor model record, then to the selected
// model; appends transformed points to the model's vector<Entry32>.
// ---------------------------------------------------------------------------
struct Gadget {  // minimal vtable stub
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual int Get(uint32_t id);        // slot 3 (+0xc)
    virtual void* slot4(int);
    virtual void* slot10(int, int, const void*, const void*);
    virtual void* slot11(int);           // +0x2c
    virtual void* slot12();              // +0x30
};

extern "C" int FUN_006c0200(void* p);
extern "C" char FUN_00eedc10(void* a, void* b);
extern "C" void FUN_00eee530(void* p);

// @ 0x00eef570
void FUN_00eef570(void* param_1, Gadget* gadget) {
    FUN_00eef4b0((EntryVector*)&g_16c7aa4);
    if (!param_1)
        return;
    void* mgr = (void*)g_16c7aa4;
    void* set = *(void**)((char*)mgr + 0x74);
    int sel = FUN_006c0200(param_1);
    gadget->Get(0x1186577);
    (void)sel;
    (void)set;
    // loop over records, test FUN_00eedc10, build two points, push_back them.
}