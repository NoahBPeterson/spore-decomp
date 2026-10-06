// w1g1 slice s004f56f0 -- editor validity string/key/bitset helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    unsigned int find(wchar_t c, unsigned int pos);
    void reserve(unsigned int n);        // 0x0042e610 (WString_reserve)
    void push_back(wchar_t c);           // 0x004f6510
};
extern wstring g_15da7d4;

struct Key { int a; int pad; int c; };
struct Obj {
    int f0;
    int f1;
    Obj(uint32_t a, uint32_t b) : f0(a), f1(b) {}
    bool Compare(const Key* k);
};
struct Bits {
    uint32_t w[4];
    Bits* Flip();
};

// ===========================================================================
// @ 0x004f56f0  (complete; not byte-exact)
// True when `c` is absent from the global validity string.
// ===========================================================================
bool FUN_004f56f0(wchar_t c)
{
    if (g_15da7d4.find(c, 0) != (unsigned int)-1)
        return false;
    return true;
}

// ===========================================================================
// @ 0x004f64d0  (complete; not byte-exact)
// Key comparison: k->c against f0 and k->a against f1.
// ===========================================================================
bool Obj::Compare(const Key* k)
{
    return k->c == f0 && k->a == f1;
}

// ===========================================================================
// @ 0x004f65d0  (complete; not byte-exact)
// Bitwise-NOT of all four words, returning the object.
// ===========================================================================
Bits* Bits::Flip()
{
    unsigned int i;
    for (i = 0; i < 4; i++)
        w[i] = ~w[i];
    return this;
}

// ===========================================================================
// @ 0x004f6510  eastl::basic_string<wchar_t>::push_back
// ===========================================================================
inline unsigned int GetNewCapacity(unsigned int currentCapacity)
{
    return (currentCapacity > 8) ? (2 * currentCapacity) : 8;
}
inline const unsigned int& max_alt(const unsigned int& a, const unsigned int& b)
{
    return (a < b) ? b : a;
}

void wstring::push_back(wchar_t c)
{
    if ((mpEnd + 1) == mpCapacity) {
        const unsigned int nLen = (unsigned int)(mpEnd - mpBegin) + 1;
        const unsigned int n2 = (unsigned int)(mpCapacity - mpBegin) - 1;
        const unsigned int nNeed = (n2 > 8) ? (2 * n2) : 8;
        reserve(max_alt(nNeed, nLen));
    }
    *mpEnd++ = c;
    *mpEnd = 0;
}

// ---------------------------------------------------------------------------
// Shared declarations for the model-validity helpers below.
// ---------------------------------------------------------------------------
struct Property {
    char pad[0x12];
    unsigned short mType;
    bool* GetBool();                       // 0x0041e920
};
struct PropertyList {
    virtual int Release_();                // 0
    virtual int Release();                 // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
struct PropListRef {
    PropertyList* mp;
    PropListRef() : mp(0) { if (mp) mp->Release_(); }
    ~PropListRef() { if (mp) mp->Release(); }
    PropListRef* operator&();              // 0x0041d870
};
struct PropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyListV(uint32_t type, uint32_t group, PropListRef* out);   // +0x2c
    inline bool GetPropertyList(uint32_t modelType, PropListRef* out);
};
uint32_t RemapTypeId(uint32_t type);               // 0x00432f10
extern uint32_t g_ModelGroup;              // 0x015daa00
inline bool PropertyManager::GetPropertyList(uint32_t modelType, PropListRef* out)
{
    return GetPropertyListV(RemapTypeId(modelType), g_ModelGroup, out);
}
struct LimbEntry {                         // 0x1d8 bytes
    uint32_t group;                        // +0x00
    uint32_t instance;                     // +0x04
    char pad0[0xd4 - 8];
    int nIds;                              // +0xd4
    char pad1[0xf8 - 0xd8];
    uint32_t ids[1];                       // +0xf8
    char pad2[0x1d8 - 0xfc];
    uint32_t GetId(int i) const { return ids[i]; }
};
struct LimbVec {
    LimbEntry* mpBegin;
    LimbEntry* mpEnd;
};
struct Model {
    virtual int AddRef_();
    virtual int Release();
    char pad0[0x18 - 4];
    uint32_t modelType;                    // +0x18
    char pad1[4];
    uint32_t slots[3];                     // +0x20
    char pad2[0x98 - 0x2c];
    LimbVec mLimbs;                        // +0x98
    uint32_t GetSlot(int i) const { return slots[i]; }
};
struct ModelRef {
    Model* mp;
    ModelRef() : mp(0) { if (mp) mp->AddRef_(); }
    ~ModelRef() { if (mp) mp->Release(); }
    ModelRef* operator&();                 // 0x0041d870 (same shape)
};
struct ResourceManager {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const Key* key, ModelRef* out, int, int, int, int);   // +0x0c
};
struct Elem16 : Key { uint32_t d; };       // 16 bytes
struct Elem16Vec {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCap;
    Elem16* begin() { return mpBegin; }
    Elem16* end() { return mpEnd; }
    bool GetResourceTypeFromModelType();   // 0x00526430
};
struct KeyMap { Elem16Vec* operator[](const uint32_t& k); };   // 0x004f6720 (thiscall, ret 4)
extern KeyMap g_Map1;                      // 0x015da960
extern KeyMap g_Map2;                      // 0x015da884
extern uint32_t kGroupEditorPaints;        // 0x015da880
struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    uint32_t* begin() { return mpBegin; }
    uint32_t* end() { return mpEnd; }
    void erase(uint32_t* b, uint32_t* e);          // 0x004769b0
    void push_back(const uint32_t& v);             // 0x00454860
};
struct KeyVec {
    Key* mpBegin;
    Key* mpEnd;
    Key* mpCap;
    Key* begin() { return mpBegin; }
    Key* end() { return mpEnd; }
    void erase(Key* b, Key* e);                    // 0x0050f740 (copy_impl do_copy, ecx=this)
    void DoInsertValue(const Key& v);              // 0x004e19a0
};
struct KeyPred {
    uint32_t f0, f1;
    bool operator()(const Key* k) const { return k->c == f0 && k->a == f1; }
};
PropertyManager* PropertyManager_Get();            // 0x0067de30
ResourceManager* ResourceManager_Get();            // 0x0067dcd0
uint32_t RemapTypeId(uint32_t type);               // 0x00432f10
void GetPropertyAsKeyInstance(PropertyList* pl, uint32_t id, uint32_t* out);   // 0x006a12a0
int FindKeyIndex(Elem16* b, Elem16* e, Obj k);     // 0x004f68f0
int FindIdIndex(Elem16* b, Elem16* e, uint32_t v); // 0x004f69e0

inline void GetBoolInline(PropertyList* pl, uint32_t id, bool& dst)
{
    if (pl) {
        Property* p;
        if (pl->GetProperty(id, p) && p->mType == 1)
            dst = *p->GetBool();
    }
}
inline uint32_t* FindU32(uint32_t* first, uint32_t* last, const uint32_t& v)
{
    while (first != last && *first != v) ++first;
    return first;
}
inline Elem16* FindElem(Elem16* first, Elem16* last, const uint32_t& v)
{
    while (first != last && first->a != v) ++first;
    return first;
}
inline Key* FindKeyA(Key* first, Key* last, const uint32_t& v)
{
    while (first != last && first->a != v) ++first;
    return first;
}
inline Elem16* FindIfObj(Elem16* first, Elem16* last, Obj pred)
{
    while (first != last && !pred.Compare(first)) ++first;
    return first;
}
inline Key* FindIfPred(Key* first, Key* last, KeyPred pred)
{
    while (first != last && !pred(first)) ++first;
    return first;
}

// ===========================================================================
// @ 0x004f5720  collect ids of unknown parts/paints of a model into a vector
// ===========================================================================
bool FUN_004f5720(Model* model, UIntVec* out)
{
    out->erase(out->mpBegin, out->mpEnd);
    if (model) {
        uint32_t type = model->modelType;
        PropListRef cfg;
        if (model) {
            PropertyManager* pm = PropertyManager_Get();
            if (pm->GetPropertyList(model->modelType, &cfg)) {
                uint32_t k1 = 0, k2 = 0;
                bool flag = false;
                GetPropertyAsKeyInstance(cfg.mp, 0xf5cbe065, &k1);
                GetPropertyAsKeyInstance(cfg.mp, 0x7a926123, &k2);
                GetBoolInline(cfg.mp, 0x300de90b, flag);
                Elem16Vec* v1 = g_Map1[k1];
                Elem16Vec* v2 = g_Map2[k2];
                if (v2->GetResourceTypeFromModelType() || v1->GetResourceTypeFromModelType())
                    return false;
                LimbVec* limbs = &model->mLimbs;
                LimbEntry* limb = 0;
                int i = 0;
                int count = (int)(limbs->mpEnd - limbs->mpBegin);
                for (; i < count; i++) {
                    limb = &limbs->mpBegin[i];
                    Obj key(limb->group, limb->instance);
                    uint32_t idx = FindKeyIndex(v1->begin(), v1->end(), key);
                    if (idx != -1) {
                        uint32_t* it = FindU32(out->begin(), out->end(), idx);
                        if (it == out->end())
                            out->push_back(idx);
                    }
                }
                if (flag) {
                    for (int s = 0; s < 3; s++) {
                        if (model->slots[s] != 0) {
                            uint32_t id = model->GetSlot(s);
                            uint32_t idx = FindIdIndex(v2->begin(), v2->end(), id);
                            if (idx != -1) {
                                uint32_t* it = FindU32(out->begin(), out->end(), idx);
                                if (it == out->end())
                                    out->push_back(idx);
                            }
                        }
                    }
                } else {
                    LimbVec* l2 = &model->mLimbs;
                    LimbEntry* e = 0;
                    int j = 0;
                    int n2 = (int)(l2->mpEnd - l2->mpBegin);
                    for (; j < n2; j++) {
                        e = &l2->mpBegin[j];
                        for (int m = 0; m < e->nIds; m++) {
                            uint32_t id = e->GetId(m);
                            uint32_t idx = FindIdIndex(v2->begin(), v2->end(), id);
                            if (idx != -1) {
                                uint32_t* it = FindU32(out->begin(), out->end(), idx);
                                if (it == out->end())
                                    out->push_back(idx);
                            }
                        }
                    }
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

// ===========================================================================
// @ 0x004f5c60  SP::cSPEditorModelValidity::GetListOfUnknownPartsAndPaints
// ===========================================================================
bool GetListOfUnknownPartsAndPaints(const Key* modelKey, KeyVec* parts, KeyVec* paints)
{
    parts->erase(parts->mpBegin, parts->mpEnd);
    paints->erase(paints->mpBegin, paints->mpEnd);
    ModelRef ref;
    if (ResourceManager_Get()->GetResource(modelKey, &ref, 0, 0, 0, 0)) {
        Model* model = ref.mp;
        if (model) {
            uint32_t type = model->modelType;
            PropListRef cfg;
            if (model) {
                PropertyManager* pm = PropertyManager_Get();
            if (pm->GetPropertyList(model->modelType, &cfg)) {
                    uint32_t k1 = 0, k2 = 0;
                    bool flag = false;
                    GetPropertyAsKeyInstance(cfg.mp, 0xf5cbe065, &k1);
                    GetPropertyAsKeyInstance(cfg.mp, 0x7a926123, &k2);
                    GetBoolInline(cfg.mp, 0x300de90b, flag);
                    Elem16Vec* v1 = g_Map1[k1];
                    Elem16Vec* v2 = g_Map2[k2];
                    if (v2->GetResourceTypeFromModelType() || v1->GetResourceTypeFromModelType())
                        return false;
                    LimbVec* limbs = &model->mLimbs;
                    LimbEntry* limb = 0;
                    int i = 0;
                    int count = (int)(limbs->mpEnd - limbs->mpBegin);
                    for (; i < count; i++) {
                        limb = &limbs->mpBegin[i];
                        Obj key(limb->group, limb->instance);
                        Elem16* it = FindIfObj(v1->begin(), v1->end(), key);
                        if (it == v1->end()) {
                            Obj key2(limb->group, limb->instance);
                            KeyPred pred;
                            pred.f0 = key2.f0;
                            pred.f1 = key2.f1;
                            Key* p = FindIfPred(parts->begin(), parts->end(), pred);
                            if (p == parts->end()) {
                                Key k;
                                k.a = limb->instance;
                                k.pad = 0xb1b104;
                                k.c = limb->group;
                                parts->DoInsertValue(k);
                            }
                        }
                    }
                    if (flag) {
                        for (int s = 0; s < 3; s++) {
                            if (model->slots[s] != 0) {
                                uint32_t id = model->GetSlot(s);
                                Elem16* it = FindElem(v2->begin(), v2->end(), id);
                                if (it == v2->end()) {
                                    uint32_t id2 = model->GetSlot(s);
                                    if (FindKeyA(paints->begin(), paints->end(), id2) == paints->end()) {
                                        Key k;
                                        k.a = model->GetSlot(s);
                                        k.pad = 0xb1b104;
                                        k.c = kGroupEditorPaints;
                                        paints->DoInsertValue(k);
                                    }
                                }
                            }
                        }
                    } else {
                        LimbVec* l2 = &model->mLimbs;
                        LimbEntry* e = 0;
                        int j = 0;
                        int n2 = (int)(l2->mpEnd - l2->mpBegin);
                        for (; j < n2; j++) {
                            e = &l2->mpBegin[j];
                            for (int m = 0; m < e->nIds; m++) {
                                uint32_t id = e->GetId(m);
                                Elem16* it = FindElem(v2->begin(), v2->end(), id);
                                if (it == v2->end()) {
                                    uint32_t id2 = e->GetId(m);
                                    if (FindKeyA(paints->begin(), paints->end(), id2) == paints->end()) {
                                        Key k;
                                        k.a = e->GetId(m);
                                        k.pad = 0xb1b104;
                                        k.c = kGroupEditorPaints;
                                        paints->DoInsertValue(k);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
