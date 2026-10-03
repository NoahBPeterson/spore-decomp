// Slice s00419780: a time-budgeted per-frame update over the scene's model records, and a small
// request dispatcher that follows it.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (frame pointer, all locals in memory; no EH frame).
#include "types.h"

union LARGE_INTEGER {
    struct { uint32_t LowPart; int32_t HighPart; } u;
    int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount);
extern "C" long _InterlockedIncrement(long volatile* addend);
#pragma intrinsic(_InterlockedIncrement)

// ---------------------------------------------------------------------------
// Reference-counted resource object (refcount at +4).
// ---------------------------------------------------------------------------
struct ThreadedObject {
    void* vtbl;
    long  refCount;
    void AddRef() { _InterlockedIncrement(&refCount); }
    void Release();          // Resource::ThreadedObject::Release @ 0x00404F90
};

struct DefaultRefCounted { void Release(); };   // @ 0x00453540

// Smart pointer to a ThreadedObject (assignment inlined in the original).
struct ObjectRef {
    ThreadedObject* p;
    ObjectRef& operator=(const ObjectRef& o) {
        if (o.p != p) {
            ThreadedObject* old = p;
            if (o.p) o.p->AddRef();
            p = o.p;
            if (old) old->Release();
        }
        return *this;
    }
};

// Pointer to a COM-like object with AddRef/Release in vtable slots 0/1.
struct IRefObject {
    virtual void AddRef();
    virtual void Release();
};

// Return list of resource references (16-bit-capacity array head + size).
struct ResultList {
    ObjectRef* items;
    int        count;
    ResultList(unsigned char* tag);      // @ 0x00540470
    void Destroy();                      // @ 0x0041EB80
    void Assign(ObjectRef* items, int count);  // @ 0x00426280
    bool IsEmpty();                      // @ 0x00526430
    void Release2(ObjectRef* items, int count); // @ 0x004243E0
    void Free();                         // @ 0x00425990
    ObjectRef* begin() { return items + 0; }
};

// Time budget (deadline is a 64-bit performance-counter value at +0x18).
struct TimeBudget {
    uint32_t pad[6];
    int64_t deadline;
    TimeBudget(int a, int b);            // @ 0x0093A560
    void Start(int a, int b);            // @ 0x0093A480
    bool Expired() {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        int64_t t = now.QuadPart;
        return deadline - t < 0;
    }
};

struct Transform { Transform(); };       // @ 0x00409930
struct Accumulator { uint32_t data[0x38 / 4]; void Add(void* v); };   // @ 0x00537DC0
struct Modifier : Accumulator { void AccumulateScaled(void* v); };    // @ 0x0040CD80

// ---------------------------------------------------------------------------
// Model behaviour (vtable slot index = offset / 4).
// ---------------------------------------------------------------------------
struct ModelBehavior {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void Prepare(void* e, int id, int mode, float f, int z);
    virtual void SetValue(void* e, int id, float v, int z);
    virtual void SetExtra(void* e, int id, float v, int z);
    virtual void v1f();
    virtual bool GetRange(void* e, int id, float* lo, float* hi, int z);
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v2a();
    virtual void v2b();
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v3a();
    virtual void v3b();
    virtual void v3c();
    virtual void QueryResults(void* e, ResultList* out);
    virtual void v3e();
    virtual void v3f();
    virtual bool Evaluate(void* e, ResultList* list, int a, int b, Transform* t);
    virtual void v41();
    virtual int  GetBaseWeight(void* e);
};

// ---------------------------------------------------------------------------
// Scene data
// ---------------------------------------------------------------------------
struct ModelRecord {          // sizeof == 0x8c
    char     pad0[8];
    uint16_t flags;           // +8   (bit0: skip, bit3: already evaluated)
    uint8_t  hasAnimation;    // +0xa
    char     pad1[0x8c - 0xb];
};

struct ModelRecordVector {    // at model+0x98
    ModelRecord* begin;
    ModelRecord* end;
    int size() const { return (int)(end - begin); }
};

struct ModelData {
    char pad0[0x98];
    ModelRecordVector records;      // +0x98
};

struct SceneRegistry { void Register(void* arrays); };   // 0x0041EBE0

struct Scene {
    char          pad0[8];
    ModelData*    model;            // +8
    char          pad0c[0xa4 - 0x0c];
    SceneRegistry registry;         // +0xa4
};

void SubmitScene(Scene* s, void* a, void* b, uint32_t x, uint32_t y, void* cb);   // 0x00469BB0 cdecl

struct PropertyList;                // opaque
// property lookup (id list + count) @ 0x006A0840 (ints) / 0x006A08B0 (floats)
int  GetIntProperty(PropertyList* p, uint32_t key, int* count, int** values);      // 0x006A0840 cdecl
int  GetFloatProperty(PropertyList* p, uint32_t key, int* count, float** values);  // 0x006A08B0 cdecl

struct Entity {                      // per-model runtime entry (table element)
    ModelBehavior* behavior;         // +0
    char     pad4[4];
    char     transformSlot[0x88];    // +8   (inline modifier data)
    PropertyList* props;             // +0x90
};

struct IntSlot   { void Set(void* p); };             // 0x0041D8B0
struct ObjSlot   { void Set(void* p); };             // 0x004535D0
struct TargetPtr { void operator=(void* p); };       // 0x0041CC60

// Smart pointers returning the stored pointer (inline getters of the original).
struct BehaviorRef  { IRefObject* p;      void* Get(); void* GetOther(); };  // 0x0041D870
struct CounterRef   { DefaultRefCounted* p; void* Get(); };                  // 0x0041D900

int  Evaluate5(void* obj, int mode);          // 0x0071DD80 cdecl
bool IsValidResource(void* obj);              // 0x00418440 cdecl
void BindResource(IRefObject* a, void* b);    // 0x006C1AE0 cdecl

struct RequestState;                          // forward

// Per-system arrays hanging off the updater at +0x30.
struct ArrayBlock {
    ObjectRef*   refs;               // +0x00
    char         pad04[0x24];
    Accumulator* weights;            // +0x28 (0x38-byte elements)
    char         pad2c[0x0c];
    Modifier*    modifiers;          // +0x3c (0x38-byte elements)
    char         pad40[0x10];
    IntSlot*     intSlots;           // +0x50
    char         pad54[0x0c];
    ObjSlot*     objSlots;           // +0x64
    char         pad68[0x0c];
    TargetPtr*   targets;            // +0x78
};

struct Updater;
struct RequestState {
    char pad0[0x1c];
    int  resumeIndex;                       // +0x1c
    bool Finish(Updater* u);                // 0x00422A70
    bool Abort(Updater* u);                 // 0x00422A50
    void Queue(Updater* u);                 // 0x00422A90
};

struct Updater {
    char        pad0[0x18];
    uint32_t    flags18;                    // +0x18
    char        pad1c[4];
    uint16_t    flags20;                    // +0x20
    char        pad22[2];
    Scene*      scene;                      // +0x24
    char        pad28[4];
    int         budget;                     // +0x2c
    ArrayBlock* arrays() { return (ArrayBlock*)((char*)this + 0x30); }
    char        pad30[0xbc - 0x30];
    Entity**    entities;                   // +0xbc
    bool UpdateModels(RequestState* st);    // 0x00419780
    void Dispatch(void* cb);                // 0x00419FF0
};

inline uint32_t SetByte1(uint32_t v, uint32_t b) {
    return (v & 0xffff00ffu) | ((b & 0xffu) << 8);
}

template<class T> inline T ClampF(T v, T lo, T hi) {
    T r = lo;
    if (lo <= v) r = v;
    if (hi <= r) r = hi;
    return r;
}
inline float Lerp(float a, float b, float t) { return (b - a) * t + a; }

// @ 0x00419780
bool Updater::UpdateModels(RequestState* st)
{
    uint32_t pendingTemp = 0;
    int limit = 0x80;
    Scene* sc = scene;
    ArrayBlock* arr = arrays();
    ModelData* model = sc->model;
    ModelRecord* recs = model->records.begin;
    int count = model->records.size();
    Entity** table = &entities[0];

    unsigned char tag;
    ResultList list(&tag);
    TimeBudget budget(4, 0);
    budget.Start(1, 1);

    for (int i = st->resumeIndex; i < count; ++i) {
        if (budget.Expired()) {
            st->resumeIndex = i;
            bool r = st->Abort(this);
            list.Release2(list.items, list.count);
            list.Free();
            return r;
        }
        ModelRecord* rec = &recs[i];
        if (table[i] != 0 && !(rec->flags & 1)) {
            ModelBehavior* beh = table[i]->behavior;
            if (rec->hasAnimation && !(rec->flags & 8)) {
                list.Assign(list.items, list.count);
                IRefObject* animObj = 0;
                DefaultRefCounted* counter = 0;
                void* cnt = ((CounterRef*)&counter)->Get();
                void* anim = ((BehaviorRef*)&animObj)->Get();
                Transform xf;
                if (!beh->Evaluate(table[i], &list, (int)anim, (int)cnt, &xf)) {
                    list.Assign(list.items, list.count);
                }
                if (!list.IsEmpty() && IsValidResource(list.begin()->p)) {
                    this->budget += Evaluate5(list.begin()->p, 5);
                    if (this->budget <= limit) {
                        IRefObject* hold = animObj;
                        if (hold) hold->AddRef();
                        BindResource(hold, ((BehaviorRef*)&animObj)->GetOther());
                        arr->weights[i].Add((void*)beh->GetBaseWeight(table[i]));
                        arr->modifiers[i].Add(&arr->weights[i]);
                        arr->modifiers[i].AccumulateScaled(&table[i]->transformSlot);
                        arr->intSlots[i].Set(list.begin()->p);
                        arr->objSlots[i].Set(animObj);
                        arr->targets[i] = counter;
                        if (hold) hold->Release();
                    }
                }
                if (counter) counter->Release();
                if (animObj) animObj->Release();
            }

            int*   ids = 0;     int nIds = 0;
            float* weights = 0; int nWeights = 0;
            float* targets = 0; int nTargets = 0;
            GetIntProperty(table[i]->props, 0x59348b4, &nIds, &ids);
            GetFloatProperty(table[i]->props, 0x59348b5, &nWeights, &weights);
            GetFloatProperty(table[i]->props, 0x6861c1e, &nTargets, &targets);

            for (int j = 0; j < nIds && j < nWeights && j < nTargets; ++j) {
                float lo = 0.0f, hi = 1.0f;
                if (beh->GetRange(table[i], ids[j], &lo, &hi, 0)) {
                    beh->Prepare(table[i], ids[j], 3, 0.0f, 0);
                    float t = ClampF(weights[j], 0.0f, 1.0f);
                    beh->SetValue(table[i], ids[j], Lerp(lo, hi, t), 0);
                    beh->SetExtra(table[i], ids[j], targets[j], 0);
                }
            }

            list.Assign(list.items, list.count);
            beh->QueryResults(table[i], &list);
            ObjectRef* src;
            ObjectRef  empty = { 0 };
            if (list.IsEmpty()) {
                pendingTemp |= 1;
                src = &empty;
            } else {
                src = list.begin();
            }
            arr->refs[i] = *src;
            if (pendingTemp & 1) {
                pendingTemp &= ~1u;
                if (empty.p) empty.p->Release();
            }
        }
    }
    bool r = st->Finish(this);
    list.Destroy();
    return r;
}

// @ 0x00419FF0
void Updater::Dispatch(void* cb)
{
    uint32_t a; uint32_t y; Scene* s2; uint32_t b; uint32_t x; Scene* s1;   // order drives /Od slots
    a = flags18;
    a = SetByte1(a, 0x71);
    x = a;
    b = flags18;
    b = SetByte1(b, 0x62);
    y = b;
    if (flags20 & 0x10)
        x = 0;
    s1 = scene;
    s1->registry.Register(arrays());
    s2 = scene;
    SubmitScene(s2, (char*)this + 0x10, arrays(), x, y, cb);
    ((RequestState*)cb)->Queue(this);
}
