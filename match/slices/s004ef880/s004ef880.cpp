// w1g1 slice s004ef880 -- validity entry helpers
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od region, no /EHsc).
//
// 0x004efb20: validity test "required parts": the editor config of the model type may list
// (key 0x300de90b, a bool) that the model must use the 3 model slots (+0x20..) instead of the
// block list; every referenced resource id must appear in the per-key allowed list
// (map at 0x015da884). Failure sets validity bit 0x12.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

struct ValidityBits {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline ValidityBits& set(uint32_t i, bool value) {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};

struct RefCounted {
    virtual int AddRef();
    virtual int Release();
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T** GetAddress();               // @ 0x0041d870
    T** AsPPointer() { return GetAddress(); }
};

struct Property {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (1 = bool)
    bool* GetBool();                // @ 0x0041e920
};

struct cPropertyList : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};

struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList** ppOut);   // +0x2c
};
cPropertyManager* PropertyManager();                 // @ 0x0067de30
uint32_t GetConfigFromModelType(uint32_t modelType); // @ 0x00432f10 (RemapTypeId)
extern uint32_t kEditorConfigGroup;                  // 0x015daa00
extern void* g_ProfileTick;                          // 0x015fd918
struct ProfileScope {
    void* mTick;
    ProfileScope(void* t) : mTick(t) {}
};
inline void TouchProfileTick() { ProfileScope scope(g_ProfileTick); }   // value read, then discarded

inline void GetPropertyBool(cPropertyList* pList, uint32_t id, bool& dst) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 1)
        dst = *prop->GetBool();
}

typedef uint32_t PartPtr;
struct PartHandle {
    uint32_t mValue;
    operator uint32_t() const { return mValue; }
};
struct Elem16 {
    PartPtr mKey;
    uint32_t pad[3];
};
inline bool operator==(const Elem16& a, const PartPtr& b) { return a.mKey == b; }

struct Elem16Vec {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* begin() { return mpBegin; }
    Elem16* end() { return mpEnd; }
    bool empty() const;             // @ 0x00526430
    Elem16* Find(PartHandle id);
};

// Stands in for the reserved frame of an inline callee that cl declined (called out of line).
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Elem16Map {
    Elem16Vec& operator[](const uint32_t& key);      // @ 0x004f6720
};
extern Elem16Map g_AllowedParts;                     // 0x015da884

inline Elem16* FindElem(Elem16* first, Elem16* last, PartPtr value) {
    while (first != last && !(*first == value))
        ++first;
    return first;
}

inline Elem16* Elem16Vec::Find(PartHandle id) { return FindElem(begin(), end(), id.mValue); }

struct cEditorBlock {
    uint32_t pad0[0xd4 / 4];
    int mnPartCount;                // +0xd4
    uint32_t pad1[(0xf8 - 0xd8) / 4];
    uint32_t mPartIDs[1];           // +0xf8
    PartHandle GetPartID(int i) { PartHandle h = { mPartIDs[i] }; return h; }
    uint32_t pad2[(0x1d8 - 0xfc) / 4];
};

struct BlockVec {
    cEditorBlock* mpBegin;
    cEditorBlock* mpEnd;
};

struct cEditorModel {
    uint32_t pad0[6];
    uint32_t mModelType;            // +0x18
    uint32_t pad1;
    uint32_t mSlotIDs[3];           // +0x20
    PartHandle GetSlotID(int i) { PartHandle h = { mSlotIDs[i] }; return h; }
    uint32_t pad2[(0x98 - 0x2c) / 4];
    BlockVec mBlocks;               // +0x98
};

// @ 0x004ef880  (INCOMPLETE skeleton)
void FUN_004ef880(void* a, void* b)
{
    (void)a; (void)b;
}

// @ 0x004efb20
// Local names (p13, n23, t10, ...) are chosen to reproduce the /Od hash-ordered frame slots.
bool CheckRequiredParts(cEditorModel* model, uint32_t key, ValidityBits* validity)
{
    bool p13 = true;
    bool prev = false;
    uint32_t t10 = model->mModelType;
    AutoRefCount<cPropertyList> n23;
    int p16, n35, n29;
    BlockVec* n22;
    cEditorBlock* p11;
    int p14;
    PropertyManager()->GetPropertyList(GetConfigFromModelType(t10), kEditorConfigGroup,
                                       n23.AsPPointer());
    if (!n23) {
        if (validity)
            validity->set(0x12, true);
        return false;
    }

    if (n23)
        GetPropertyBool(n23, 0x300de90b, prev);

    ScratchSlots<17>();
    Elem16Vec* p30 = &g_AllowedParts[key];
    if (p30->empty()) {
        if (validity)
            validity->set(0x12, false);
        return true;
    }

    if (prev) {
        for (p16 = 0; p16 < 3; p16++) {
            if (model->mSlotIDs[p16]) {
                if (p30->Find(model->GetSlotID(p16)) == p30->end()) {
                    if (validity)
                        validity->set(0x12, true);
                    return false;
                }
            }
            TouchProfileTick();
        }
    } else {
        n22 = &model->mBlocks;
        p11 = 0;
        for (n35 = 0, p14 = (int)(n22->mpEnd - n22->mpBegin); n35 < p14 && p13; n35++) {
            p11 = n22->mpBegin + n35;
            for (n29 = 0; n29 < p11->mnPartCount; n29++) {
                if (p30->Find(p11->GetPartID(n29)) == p30->end()) {
                    if (validity)
                        validity->set(0x12, true);
                    return false;
                }
                TouchProfileTick();
            }
        }
    }

    if (validity)
        validity->set(0x12, !p13);
    return p13;
}
