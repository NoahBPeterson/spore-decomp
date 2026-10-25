// w1g1 slice s004e5050 -- editor verb-icon helpers around 0x4e5050.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

// An object exposing a property test virtual at vtable offset 0x1c.
struct VerbObject {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual bool HasCategory(int key); // +0x1c
};

bool GetPropertyAsKeyInstance(VerbObject* p, int key, int* out); // 0x006a12a0, cdecl

// @ 0x004e58c0
// SP::EditorUtils::GetVerbCategory: if the object advertises the category key,
// read it back as a key instance and return it, else 0.
int GetVerbCategory(VerbObject* p)
{
    if (p->HasCategory(0x4abbb0d)) {
        int local = 0;
        if (GetPropertyAsKeyInstance(p, 0x4abbb0d, &local))
            return local;
    }
    return 0;
}

// @ 0x004e5910
// SP::EditorUtils::IsDietCategory: true for a fixed set of category hashes.
bool IsDietCategory(int id)
{
    return (id == (int)0xa28a67e8 || id == 0x2dfb4f9f || id == (int)0xdfa0d6bf ||
            id == (int)0xd9bcb9f0 || id == 0x521a15d5);
}

// ---------------------------------------------------------------------------
// Skeletons for the remaining /Od bodies.
// ---------------------------------------------------------------------------

// --- shared helpers / types used by the five /Od bodies ---------------------
struct RefCounted {                     // EA::RefCounted base: vtbl[1] = Release
    virtual void v0();
    virtual void Release();
};
// A refcounted pointer wrapper: "prepare as out-param" clears the old pointer and
// releases it (inlined at /Od).
struct AutoRef {
    void* mp;
    void** Prepare()
    {
        if (mp != 0) {
            void* tmp = mp;
            mp = 0;
            ((RefCounted*)tmp)->Release();
        }
        return &mp;
    }
};

extern "C" int   __cdecl Editor_GetConfigFromModelType(int modelType);       // 0x432f10
extern "C" void* __cdecl GetPropertyManager67de30();                         // 0x67de30
extern "C" void* __cdecl ResourceMan_GetManager();                           // 0x67dcd0
extern "C" char  __cdecl GetPropertyAsKey(void* list, uint32_t id, void* out);        // 0x6a1250
extern "C" char  __cdecl GetPropertyAsKeyInstance(void* list, uint32_t id, void* out); // 0x6a12a0
extern "C" char  __cdecl GetPropertyArray(void* list, uint32_t id, int* count, void** data); // 0x6a0ae0
extern "C" void  __cdecl Elem7990(void* out, uint32_t id);                   // 0x4e7990  build {id,0,0}
extern "C" void  __cdecl Func4b5440(void* vec);                              // 0x4b5440  destroy 3-word vec
extern "C" int   __cdecl Func421eb0(void** ref);                             // 0x421eb0  interface_cast
extern "C" char  __cdecl Func4bafc0(void* a, void* b);                       // 0x4bafc0  name compare
extern "C" int   __cdecl Func4d1370(uint32_t id);                            // 0x4d1370
extern "C" char  __cdecl Func44c030(void* self);                             // 0x44c030
extern "C" void* __cdecl AllocEditor(uint32_t size);                         // operator new(...,"Editor")
extern uint32_t  DAT_015d9ed8;

// ---------------------------------------------------------------------------

// @ 0x004e5050
// SP::EditorUtils::GetVerbIconKeyForModelType: build the {key0,key1,key2} icon key for a model type.
struct Key3 { uint32_t w[3]; };
struct PropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropertyList(uint32_t id, uint32_t req, void** out);   // +0x2c
};
Key3* GetVerbIconKeyForModelType(Key3* out, int modelType)
{
    int config = Editor_GetConfigFromModelType(modelType);
    if (config == -1) {
        out->w[0] = 0;
        out->w[1] = 0;
        out->w[2] = 0;
    } else {
        AutoRef prop;
        prop.mp = 0;
        PropList* mgr = (PropList*)GetPropertyManager67de30();
        void** pp = prop.Prepare();
        mgr->GetPropertyList(config, DAT_015d9ed8, pp);
        if (prop.mp != 0) {
            Key3 local;
            local.w[0] = 0;
            local.w[1] = 0;
            local.w[2] = 0;
            if (GetPropertyAsKey(prop.mp, 0x4aa3989, &local)) {
                out->w[0] = local.w[0];
                out->w[1] = local.w[1];
                out->w[2] = local.w[2];
                if (prop.mp != 0)
                    ((RefCounted*)prop.mp)->Release();
                return out;
            }
        }
        out->w[0] = 0;
        out->w[1] = 0;
        out->w[2] = 0;
        if (prop.mp != 0)
            ((RefCounted*)prop.mp)->Release();
    }
    return out;
}

// Host object that accumulates a rank->icon-key map (opaque layout here).
struct VerbHost5180;

// A refcounted list built and destroyed with the 3-word {id,0,0} pattern.
struct RefList3 { uint32_t w[3]; };

// EA::AutoRefCount manipulators (out-param prepare / release).
extern "C" void* __cdecl ReserveAutoRef(void* list, uint32_t id, int* count, void** data); // 0x6a0ae0
 
// A container exposing mBegin/mEnd at [0]/[4] (words, stride 4).
struct PtrVector {
    int* mpBegin;                       // +0x0
    int* mpEnd;                         // +0x4
    int  mCapacity;                     // +0x8
};

// Manager that maps a model type onto an icon key: test id 0x4aa3838 yields a
// vector of model types; each entry's 0xaf028f41 list holds the icon keys.
extern "C" void* __cdecl GetPropertyManager();                            // 0x67de30
extern "C" void* __cdecl Func4e8850(void* self);                          // 0x4e8850
extern "C" int*  __cdecl Func4e88a0(void* self, void* key);               // 0x4e88a0

// @ 0x004e5180
// SP::EditorUtils::ComputeCategoryRankImageMap: for every model type in the
// requested category, emit {rank,key0,key1,key2} records into the host.
bool ComputeCategoryRankImageMap(VerbHost5180* self, int category, int modelType)
{
    Key3 key;
    GetVerbIconKeyForModelType(&key, modelType);
    if (key.w[0] == 0)
        return false;
    Func4e8850(self);
    AutoRef list;
    list.mp = 0;
    PropList* mgr = (PropList*)GetPropertyManager();
    if (list.mp != 0) {
        void* tmp = list.mp;
        list.mp = 0;
        ((RefCounted*)tmp)->Release();
    }
    mgr->GetPropertyList(key.w[0], key.w[2], (void**)&list.mp);

    int count = 0;
    char ok = 0;
    PtrVector* models = 0;
    ok = (char)ReserveAutoRef(list.mp, 0x4aa3838, &count, (void**)&models);
    if (count > 0 && ok) {
        int rank = 0;
        for (int i = 0; i < count; ++i) {
            AutoRef inner;
            inner.mp = 0;
            PropList* mgr2 = (PropList*)GetPropertyManager();
            if (inner.mp != 0) {
                void* tmp = inner.mp;
                inner.mp = 0;
                ((RefCounted*)tmp)->Release();
            }
            mgr2->GetPropertyList(models->mpBegin[i * 3], 0xaf028f41, (void**)&inner.mp);

            Key3 iconKey;
            GetPropertyAsKeyInstance(inner.mp, 0x6286814, &iconKey);

            Key3 outKey;
            outKey.w[0] = 0;
            outKey.w[1] = 0;
            outKey.w[2] = 0;
            GetPropertyAsKey(inner.mp, 0x4a20fe7, &outKey);
            outKey.w[2] = 0x40464100;
            outKey.w[1] = 0x510a95b;

            int subCount = 0;
            PtrVector* subVec = 0;
            ReserveAutoRef(inner.mp, 0x4a20feb, &subCount, (void**)&subVec);
            for (int j = 0; j < subCount; ++j) {
                int rec[4];
                rec[0] = rank;
                rec[1] = outKey.w[0];
                rec[2] = outKey.w[1];
                rec[3] = outKey.w[2];
                void* entry = (void*)subVec->mpBegin[j * 3];
                int* slot = Func4e88a0(self, &entry);
                slot[0] = rec[0];
                slot[1] = rec[1];
                slot[2] = rec[2];
                slot[3] = rec[3];
                ++rank;
            }
            if (inner.mp != 0)
                ((RefCounted*)inner.mp)->Release();
        }
    }
    if (list.mp != 0)
        ((RefCounted*)list.mp)->Release();
    return true;
}

// @ 0x004e5410
// SP::EditorUtils::ComputeVerbIconData: dispatch a verb id onto the icon builder
// that understands it.  Returns true when the host accepted the icon record.
extern "C" void* __cdecl PrepareRef(void* ref);                                 // 0x41d870  releases old, returns ref
extern "C" char  __cdecl NameCompare(void* key, void* cfg);                     // 0x4bafc0
extern "C" int   __cdecl VerbIdToIconParam(int id);                             // 0x4d1370
extern "C" void  __cdecl BuildNamedIcon(void* ref, int* host, int param, float rate); // 0x4e87f0
extern "C" void  __cdecl Emit7990(RefList3* out, int id);                        // 0x4e7990
extern "C" void  __cdecl Func4b5440v(RefList3* v);                              // 0x4b5440
extern "C" void  __cdecl Emit7da0(int res, int* host);                          // 0x4e7da0
extern "C" void  __cdecl Emit6c10(int res, int* host);                          // 0x4e6c10
extern "C" int   __cdecl InterfaceCastEditor(void** ref);                       // 0x421eb0
extern "C" void* __cdecl ResourceMan_GetManager2();                             // 0x67dcd0

// A COM resource-manager host (vtbl[3] = GetResource).
struct ResMan {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual char GetResource(void* key, void** out, int a, int b, int c, int d); // +0xc
};

// A host object exposing vtbl[5] = AcceptIconRecord.
struct IconSink {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void AcceptIconRecord(RefList3* rec);   // +0x14
};

char ComputeVerbIconData(Key3 key, uint32_t verbId, int* host, float rate)
{
    switch ((int)verbId) {
    // --- named-icon path: match the config name, then build by id -------------
    case 0x4178b8e8:
    case 0x372e2c04:
    case 0x65672ade:
    case (int)0x9ea3031a:
    case (int)0xccc35c46:
    {
        AutoRef cfg;
        cfg.mp = 0;
        void* cfgPtr = PrepareRef(&cfg);
        char same = NameCompare(&key, cfgPtr);
        if (same) {
            int param = VerbIdToIconParam((int)verbId);
            BuildNamedIcon(cfg.mp, host, param, rate);
            if (cfg.mp != 0)
                ((RefCounted*)cfg.mp)->Release();
            return 1;
        }
        if (cfg.mp != 0)
            ((RefCounted*)cfg.mp)->Release();
        return 0;
    }
    // --- resource path (Emit7da0), most verb ids ------------------------------
    case 0x1a4e0708:
    case (int)0xc0b74287:
    case 0x2a5147a9:
    case 0x1f2a25b6:
    case 0x2090a11b:
    case 0x441cd3e6:
    case 0x449c040f:
    case 0x7d433fad:
    case (int)0x8f963dcb:
    case (int)0x9ad7d4aa:
    case (int)0xbc1041e6:
    case (int)0xc15695da:
    case (int)0xf670aa43:
    {
        AutoRef res;
        res.mp = 0;
        ResMan* rm = (ResMan*)ResourceMan_GetManager2();
        if (res.mp != 0) {
            void* tmp = res.mp;
            res.mp = 0;
            ((RefCounted*)tmp)->Release();
        }
        if (!rm->GetResource(&key, &res.mp, 0, 0, 0, 0)) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        int editor = InterfaceCastEditor(&res.mp);
        if (editor == 0) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        Emit7da0(editor, host);
        if (res.mp != 0)
            ((RefCounted*)res.mp)->Release();
        return 1;
    }
    // --- resource path (Emit6c10) --------------------------------------------
    case (int)0xdfad9f51:
    {
        AutoRef res;
        res.mp = 0;
        ResMan* rm = (ResMan*)ResourceMan_GetManager2();
        if (res.mp != 0) {
            void* tmp = res.mp;
            res.mp = 0;
            ((RefCounted*)tmp)->Release();
        }
        if (!rm->GetResource(&key, &res.mp, 0, 0, 0, 0)) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        int editor = InterfaceCastEditor(&res.mp);
        if (editor == 0) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        Emit6c10(editor, host);
        if (res.mp != 0)
            ((RefCounted*)res.mp)->Release();
        return 1;
    }
    // --- default: emit a plain {id,0,0} record --------------------------------
    default:
    {
        RefList3 rec;
        rec.w[0] = 0;
        rec.w[1] = 0;
        rec.w[2] = 0;
        Emit7990(&rec, (int)verbId);
        ((IconSink*)host)->AcceptIconRecord(&rec);
        Func4b5440v(&rec);
        return 0;
    }
    }
}

// EA bitset living at host+0xdc8; 60 bits spread across 32-bit words.
struct BitSet60 {
    uint32_t mWords[2];
    bool test(uint32_t idx)
    {
        if (idx >= 60)
            return false;
        uint32_t word = mWords[idx / 32];
        return (word & (1u << (idx % 32))) != 0;
    }
};
struct VerbHost {
    char      pad0[0xdc8];
    BitSet60  mDisabled;                // +0xdc8
    bool      IsAvailable();            // 0x44c030
};

// @ 0x004e57f0
// SP::EditorUtils::IsCreatureVerbEnabled: available, and neither the diet bit
// (1) nor bit 2 set in the host's disabled-verb bitset.
bool IsCreatureVerbEnabled(VerbHost* self)
{
    if (self && self->IsAvailable() && !self->mDisabled.test(1) && !self->mDisabled.test(2))
        return true;
    return false;
}

// @ 0x004e5960
// SP::EditorUtils::AccumulateVerbIconData: walk every verb of the host's verb
// resource and fold each one's icon priority into the built icon data list,
// setting diet/behaviour bits in *flags along the way.
void* __cdecl Func5a9050(void* id);                        // 0x5a9050
int   __cdecl VerbIconWeight(int id);                      // 0x4e6920
void  __cdecl Func4b54b0v(void** vec, int* value);         // 0x4b54b0
extern "C" int* __cdecl FNV1_String8(int* str);            // 0x41e990

struct VerbIconList {                   // eastl vector of verb object ptrs
    int* mpBegin;                       // +0x0
    int* mpEnd;                         // +0x4
};
struct VerbObject2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual char Lookup(int iconId, int* out);  // +0x24
};
struct VerbIconData {                   // cSPEditorVerbIconData
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void SetId(int id);         // +0x10 (idx 4)
};
struct SinkVec {                        // homes the built VerbIconData
    void** mpBegin;                     // +0x0
    void** mpEnd;                       // +0x4
};

struct VerbIconWeightEntry {            // {id, ...}
    int   mId;                          // +0x0
    int   mPad;                         // +0x4
    float mWeight;                      // +0x18
    float mCap;                         // +0x1c
    char  mClamped;                     // +0x4d
};

extern "C" void* __cdecl OperatorNewEditor(uint32_t size, const char* tag, int a, int b, int c, int d); // 0xf473a0
void* __cdecl CtorVerbIconData(void* self);         // 0x5e5a70
void* __cdecl NewVerbIconData();

void AccumulateVerbIconData(VerbObject2* host, int* existing, uint32_t* flags)
{
    int resId = ((int*)host)[2];        // host[2]
    int* list = (int*)Func5a9050((void*)resId);
    if (list == 0)
        return;

    int total = (list[1] - list[0]) >> 2;
    for (int i = 0; i < total; ++i) {
        int* verbPtr = (int*)(list[0] + i * 4);
        int verb = *verbPtr;
        int category = GetVerbCategory((VerbObject*)verb);
        char isDiet = IsDietCategory(category);
        if (isDiet) {
            if (category == (int)0xdfa0d6bf)
                *flags |= 1;
            else if (category == (int)0xd9bcb9f0)
                *flags |= 2;
            else if (category == 0x521a15d5)
                *flags |= 4;
        } else {
            VerbIconWeightEntry* data = 0;
            int count = (existing[1] - existing[0]) >> 2;
            for (int j = 0; j < count; ++j) {
                int* slot = (int*)(existing[0] + j * 4);
                int cand = *slot;
                int candId = *(int*)(cand + 0xc0);
                if (candId == verb) {
                    int* slot2 = (int*)(existing[0] + j * 4);
                    data = (VerbIconWeightEntry*)*slot2;
                }
            }
            if (data == 0) {
                data = (VerbIconWeightEntry*)NewVerbIconData();
                ((VerbIconData*)data)->SetId(verb);
                data->mWeight = 0.0f;
                void* keep = data;
                if (data != 0)
                    (*(void(**)(void))data)();
                Func4b54b0v((void**)existing, (int*)&keep);
                if (keep != 0)
                    ((RefCounted*)keep)->Release();
            }
            int iconId = VerbIconWeight(*(int*)(verb + 8));
            if (iconId != 0) {
                int hash = 0;
                int found = 0;
                if (host != 0 &&
                    host->Lookup(iconId, &found) &&
                    *(short*)(found + 0x12) == 9) {
                    int* p = FNV1_String8((int*)found);
                    hash = *p;
                }
                data->mWeight = (float)hash + data->mWeight;
                if (data->mClamped && data->mWeight > data->mCap) {
                    data->mWeight = data->mCap;
                }
            }
        }
    }
}

// Allocate and construct a cSPEditorVerbIconData (0xc4 bytes) for the icon list.
void* __cdecl NewVerbIconData()
{
    void* mem = OperatorNewEditor(0xc4, "Editor", 0, 0, 0, 0);
    if (mem == 0)
        return 0;
    return CtorVerbIconData(mem);
}
