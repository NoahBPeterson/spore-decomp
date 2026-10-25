// w1g1 slice s004f1ff0 -- editor validity float metric helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

float FUN_004f1ff0(int a);
bool  FUN_004f21e0(int a, int b);

// ---------------------------------------------------------------------------
// Property-engine types (see src/game/SPBake/SPEditorBlock.cpp, SPEditorBaker.cpp).
// ---------------------------------------------------------------------------

struct Property;                                             // opaque property record

struct PropertyList;                                         // reference-counted list

// 0x0067de30 -- SP::PropertyManager() singleton.
void* PropertyManager_s004f();                               // 0x67de30

// 0x0067dd60 -- ValueManager singleton (model-type config source).
void* ValueManager_s004f();                                  // 0x67dd60

// 0x00410370 -- TryGetUIntProperty(list, id, uint32_t& out) -> bool.
bool TryGetUIntProperty(PropertyList* list, uint32_t id, uint32_t& value);   // 0x410370

// 0x0040cf10 -- SP::GetPropertyT<int>(list, id, int& out) -> int*.
int* SP_GetPropertyT_int(PropertyList* list, uint32_t id, int& value);       // 0x40cf10

// 0x00432f10 -- SP::Editor::RemapTypeId(int id) -> int.
int RemapTypeId(int id);                                     // 0x432f10

// 0x00432e60 -- SP::Editor::GetConfigFromModelType(int id, void* mgr, void** out).
int GetConfigFromModelType(int id, void* mgr, void** out);   // 0x432e60

// 0x0041d870 -- EA::AutoRefCount<PropertyList>::AsPPVoidParam() (thiscall on &list).
void** AutoRefCount_AsPPVoidParam(PropertyList** p);         // 0x41d870

// 0x0041e990 -- Property::GetInt() -> int const*.
const int* Property_GetInt(Property* self);                  // 0x41e990

// PropertyList vtable: [0]=dtor, [4]=Release, [0x24]=GetProperty(id, Property**), [0x2c]=GetPropertyList.
// Property vtable offset +0x12 holds the type tag (9 == int).
struct PropertyFields_s004f {
    uint32_t mPad00[0x12 / 4];                               // vtable + bookkeeping
    uint16_t mType;                                          // +0x12 (9 == Int)
};
struct PropertyListFields_s004f {
    uint32_t mPad00[2];                                      // vtable ptr + refcount
};

// ---------------------------------------------------------------------------
// The editor model object: a vector of 0x1d8-byte entries at +0x98 and a
// 32-bit type id at +0x18.  Only the entry's +0x0c group index matters here.
// ---------------------------------------------------------------------------
struct ModelEntry_s004f {                                    // 0x1d8 bytes
    uint32_t mPad00[3];
    int      mGroupIndex;                                    // +0x0c
    uint8_t  mPad10[0x1d8 - 0x10];
    void CopyCtor(const ModelEntry_s004f* src);              // 0x4721e0 (thiscall)
};

struct ModelVec_s004f {                                      // [begin,end)
    ModelEntry_s004f* mBegin;                                // +0x00
    ModelEntry_s004f* mEnd;                                  // +0x04
};

struct Model_s004f {                                         // editor model object
    uint8_t           mPad00[0x18];
    uint32_t          mTypeId;                               // +0x18
    uint8_t           mPad1c[0x98 - 0x1c];
    ModelVec_s004f    mEntries;                              // +0x98
};

// 0x004721e0 -- in-place copy ctor for a 0x1d8-byte model entry
// (thiscall: ecx = destination, one stack argument = source).
void ModelEntry_Copy_s004f(ModelEntry_s004f* self, const ModelEntry_s004f* src);  // 0x4721e0
#pragma optimize("", off)
void ModelEntry_s004f::CopyCtor(const ModelEntry_s004f* src)
{
    ModelEntry_Copy_s004f(this, src);
}
#pragma optimize("", on)

// vcall helpers: read a vtable slot from an object pointer.
static inline uint32_t VtSlot_s004f(const void* obj, int off)
{
    return *(const uint32_t*)(*(const uint32_t*)obj + off);
}
static inline void Vcall0_s004f(const void* obj, int off)
{
    ((void (__thiscall*)(const void*))VtSlot_s004f(obj, off))(obj);
}

// ===========================================================================
// @ 0x004f21e0  (complete; not byte-exact)
// True when the metric of `a` is <= `b`.  cl emits a double-width comisd here
// where the original used a single-precision comiss.
// ===========================================================================
bool FUN_004f21e0(int a, int b)
{
    float f = FUN_004f1ff0(a);
    if (f <= (float)b)
        return true;
    return false;
}

// ===========================================================================
// @ 0x004f1ff0  (complete)
// Weighted metric over model->mEntries: each 0x1d8-byte entry contributes its
// integer value property (key 0x2166464), scaled by 0.5 when the entry's
// +0x0c group index points inside the vector and by 1.0 otherwise.
// ===========================================================================
float FUN_004f1ff0(int a)
{
    ModelVec_s004f* vec   = &((Model_s004f*)a)->mEntries;   // [ebp-8]
    float  acc   = 0.0f;                                     // [ebp-0xc]  _HK_REAL_ZERO
    int    value = 0;                                        // [ebp-4]
    int    count = (int)((vec->mEnd - vec->mBegin) / 0x1d8); // [ebp-0x10]
    int    i     = 0;                                        // [ebp-0x14]
    for (; i < count; ++i) {
        ModelEntry_s004f staged;
        staged.CopyCtor(&vec->mBegin[i]);

        PropertyList* list = 0;
        void* mgr = PropertyManager_s004f();
        if (list != 0)
            Vcall0_s004f(list, 4);                           // Release stale list
        ((void (__thiscall*)(void*, int, int, void**))VtSlot_s004f(mgr, 0x2c))(
            mgr, (int)vec->mBegin, (int)vec->mEnd, (void**)&list);

        bool have = false;
        if (list != 0) {
            Property* prop = 0;
            if ((*(bool (__thiscall**)(PropertyList*, uint32_t, Property**))
                 VtSlot_s004f(list, 0x24))(list, 0x2166464u, &prop) &&
                prop != 0 && ((PropertyFields_s004f*)prop)->mType == 9) {
                value = *Property_GetInt(prop);
                have = true;
            }
        }
        if (have) {
            int   idx   = vec->mBegin[i].mGroupIndex;
            float scale = (idx < 0 || count <= idx) ? 1.0f : 0.5f;
            acc = (float)value * scale + acc;
        }
        if (list != 0)
            Vcall0_s004f(list, 4);                           // Release list
    }
    return acc;
}

// ===========================================================================
// @ 0x004f2210  (complete)
// Type-id gate plus budget test.  Only the listed model type ids are budgeted;
// for those the model's "budget" integer property (key 0xb1b76a19) is read from
// the type's property list and compared with the model metric.  Bit 1 of
// *flags is kept clear while the model is within budget and set otherwise.
// ===========================================================================
bool FUN_004f2210(int a, uint32_t* flags)
{
    Model_s004f* model = (Model_s004f*)a;
    uint32_t typeId = model->mTypeId;
    uint8_t  gated  = 0;
    if (typeId == 0x1a4e0708 || typeId == 0xbc1041e6 || typeId == 0x99e92f05 ||
        typeId == 0x8f963dcb || typeId == 0x98e03c0d || typeId == 0x9ad7d4aa ||
        typeId == 0xc15695da || typeId == 0xbdd15f3d || typeId == 0xc0b74287 ||
        typeId == 0xf670aa43 || typeId == 0x449c040f || typeId == 0x2a5147a9 ||
        typeId == 0x1f2a25b6 || typeId == 0x2090a11b || typeId == 0x441cd3e6 ||
        typeId == 0x72c49181 || typeId == 0x47c10953 || typeId == 0x4e3f7777 ||
        typeId == 0x7d433fad)
        gated = 1;
    if (!gated) {
        if (flags != 0)
            *flags &= ~2u;                                   // clear budget-dirty bit
        return true;
    }

    int value = 0;
    PropertyList* list = 0;
    void* mgr = PropertyManager_s004f();
    if (list != 0)
        Vcall0_s004f(list, 4);                               // Release stale list
    int typeRemapped = RemapTypeId(typeId);
    (*(void (__thiscall**)(void*, int, void**))(*(uint32_t*)mgr + 0x2c))(
        mgr, typeRemapped, (void**)&list);

    if (list != 0) {
        Property* prop = 0;
        if ((*(bool (__thiscall**)(PropertyList*, uint32_t, Property**))
             VtSlot_s004f(list, 0x24))(list, 0xb1b76a19u, &prop) &&
            prop != 0 && ((PropertyFields_s004f*)prop)->mType == 9)
            value = *Property_GetInt(prop);
    }
    if (!FUN_004f21e0(a, value)) {
        if (flags != 0)
            *flags |= 2u;                                    // mark over-budget
        if (list != 0)
            Vcall0_s004f(list, 4);
        return false;
    }
    if (flags != 0)
        *flags &= ~2u;
    if (list != 0)
        Vcall0_s004f(list, 4);
    return true;
}

// ===========================================================================
// @ 0x004f2610  (complete)
// Entry stub: the 0x4f2610 entry point returns true immediately and jumps over
// the real body, which is entered separately at 0x4f2620.
// ===========================================================================
bool FUN_004f2610(int a, uint32_t* flags)
{
    (void)a; (void)flags;
    return true;
}

// ===========================================================================
// @ 0x004f2620  (complete)
// Weighted three-axis metric over the model's entry vector: each entry
// contributes its x/y/z integer properties (keys 0x11b78a71/72/70), weighted
// by 0.5 when the entry's +0x0c group index is inside the vector and 1.0
// otherwise.  The totals are clamped to the model's maximum (key 0x5596301)
// and the sum is compared with the model's minimum (key 0x55962f7).  Bit 0xc
// of *flags is cleared while in range and set otherwise.
// ===========================================================================
bool FUN_004f2620(int a, uint32_t* flags)
{
    Model_s004f* model = (Model_s004f*)a;
    uint32_t typeId = model->mTypeId;
    uint8_t  gated  = 0;
    if (typeId == 0x1f2a25b6 || typeId == 0xc0b74287 || typeId == 0x8f963dcb ||
        typeId == 0x9ad7d4aa || typeId == 0xf670aa43 || typeId == 0x1a4e0708 ||
        typeId == 0x449c040f || typeId == 0x2a5147a9 || typeId == 0x441cd3e6 ||
        typeId == 0x7d433fad)
        gated = 1;
    if (!gated) {
        if (flags != 0)
            *flags &= ~0xcu;                                 // clear vehicle-range bit
        return true;
    }

    ModelVec_s004f* vec = &model->mEntries;
    float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
    int   count = (int)((vec->mEnd - vec->mBegin) / 0x1d8);
    for (int i = 0; i < count; ++i) {
        PropertyList* list = 0;
        void* mgr = PropertyManager_s004f();
        if (list != 0)
            Vcall0_s004f(list, 4);                           // Release stale list
        void** pp = AutoRefCount_AsPPVoidParam(&list);
        (*(void (__thiscall**)(void*, int, int, void**))(*(uint32_t*)mgr + 0x2c))(
            mgr, (int)vec->mBegin, (int)vec->mEnd, pp);

        if (list != 0) {
            int idx = vec->mBegin[i].mGroupIndex;
            float scale = (idx < 0 || count <= idx) ? 1.0f : 0.5f;
            uint32_t v = 0;
            if (TryGetUIntProperty(list, 0x11b78a71u, v))
                sumX = (float)v * scale + sumX;
            if (TryGetUIntProperty(list, 0x11b78a72u, v))
                sumY = (float)v * scale + sumY;
            if (TryGetUIntProperty(list, 0x11b78a70u, v))
                sumZ = (float)v * scale + sumZ;
        }
        if (list != 0)
            Vcall0_s004f(list, 4);                           // Release list
    }

    int minSum = 0;                                          // key 0x55962f7
    int maxSum = 0;                                          // key 0x5596301
    PropertyList* list = 0;
    void* mgr = PropertyManager_s004f();
    if (list != 0)
        Vcall0_s004f(list, 4);
    if ((*(bool (__thiscall**)(void*, uint32_t, void**))(*(uint32_t*)mgr + 0x30))(
            mgr, 0xb6a5c63du, (void**)&list)) {
        SP_GetPropertyT_int(list, 0x55962f7u, minSum);
        SP_GetPropertyT_int(list, 0x5596301u, maxSum);

        sumX = sumX < 0.0f ? 0.0f : (sumX > (float)maxSum ? (float)maxSum : sumX);
        sumY = sumY < 0.0f ? 0.0f : (sumY > (float)maxSum ? (float)maxSum : sumY);
        sumZ = sumZ < 0.0f ? 0.0f : (sumZ > (float)maxSum ? (float)maxSum : sumZ);

        if (sumX + sumY + sumZ > (float)minSum) {
            if (flags != 0)
                *flags |= 0xcu;                              // out of range
            if (list != 0)
                Vcall0_s004f(list, 4);
            return false;
        }
    }
    if (flags != 0)
        *flags &= ~0xcu;
    if (list != 0)
        Vcall0_s004f(list, 4);
    return true;
}
