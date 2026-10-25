// w1g1 slice s004e6c60 -- a small /O2 colour-scale helper, a percent normaliser and the
// /Od verb-icon data builder that drives both.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE for the float helper.

typedef unsigned int uint32_t;

// math.h with a plain (non-dllimport) floor(): calls go through the local CRT thunk 0x011e0906.
#define _CRTIMP
#include <math.h>

// @ 0x004e7460
// Scales an RGB triple for a colour-variation "kind" (0/1/2).  Each output is
// initialised to 1.0 and then combined with the input channels using per-kind
// multipliers.
void ScaleColorForKind(int kind, float r, float g, float b,
                       float* pR, float* pG, float* pB)
{
    *pR = 1.0f;
    *pG = 1.0f;
    *pB = 1.0f;

    if (kind == 0) {
        *pR = *pR * 10.0f + r * 20.0f;
        *pG = *pG * 150.0f + g * 300.0f;
        *pB = *pB * 5.0f + b * 20.0f;
    }
    if (kind == 1) {
        *pR = *pR * 15.0f + r * 30.0f;
        *pG = *pG * 200.0f + g * 400.0f;
        *pB = *pB * 5.0f + b * 20.0f;
    }
    if (kind == 2) {
        *pR = *pR * 10.0f + r * 20.0f;
        *pG = *pG * 150.0f + g * 300.0f;
        *pB = *pB * 10.0f + b * 40.0f;
    }
}

// @ 0x004e6c60
// Normalises three non-negative amounts to integer percentages that sum to exactly 100.
// pct = v / max(total, 20) * 100; then (unless the total was clamped up to 20) the floors are
// summed and the 0..3 missing points go to the entries with the largest fractional remainders.
struct PctItem {
    char  pad[0x18];
    float amount;     // +0x18
    float pad2;
    float pct;        // +0x20
};

// NB: the odd local names (n5, v33, ...) are chosen so the /Od hash-ordered frame slots match.
// Roles: n5=amountA, v33=amountB, obj=amountC, nSize=minTotal(20), begin=total, p19=clamped,
//        n22=floor sum, p22/left/t38 = fractional remainders of a/b/c.
void NormalizePercents(PctItem* a, PctItem* b, PctItem* c)
{
    float n5 = a->amount;
    float v33 = b->amount;
    float obj = c->amount;
    float nSize = 20.0f;
    float begin = n5 + v33 + obj;
    bool p19 = false;
    if (nSize > begin) {
        begin = nSize;
        p19 = true;
    }
    a->pct = n5 / begin * 100.0f;
    b->pct = v33 / begin * 100.0f;
    c->pct = obj / begin * 100.0f;
    if (!p19) {
    float n22 = floor(a->pct) + floor(b->pct) + floor(c->pct);
    float p22 = a->pct - floor(a->pct);
    float left = b->pct - floor(b->pct);
    float t38 = c->pct - floor(c->pct);

    if (n22 == 100.0f) {
        a->pct = floor(a->pct);
        b->pct = floor(b->pct);
        c->pct = floor(c->pct);
    } else if (n22 == 99.0f) {
        if (p22 >= left && p22 >= t38) {
            a->pct = 1.0f + floor(a->pct);
            b->pct = floor(b->pct);
            c->pct = floor(c->pct);
        } else if (left >= p22 && left >= t38) {
            b->pct = 1.0f + floor(b->pct);
            a->pct = floor(a->pct);
            c->pct = floor(c->pct);
        } else {
            c->pct = 1.0f + floor(c->pct);
            b->pct = floor(b->pct);
            a->pct = floor(a->pct);
        }
    } else if (n22 == 98.0f) {
        if (left >= t38 && p22 >= t38) {
            a->pct = 1.0f + floor(a->pct);
            b->pct = 1.0f + floor(b->pct);
            c->pct = floor(c->pct);
        } else if (p22 >= left && t38 >= left) {
            b->pct = floor(b->pct);
            a->pct = 1.0f + floor(a->pct);
            c->pct = 1.0f + floor(c->pct);
        } else {
            c->pct = 1.0f + floor(c->pct);
            b->pct = 1.0f + floor(b->pct);
            a->pct = floor(a->pct);
        }
    } else {
        c->pct = 1.0f + floor(c->pct);
        b->pct = 1.0f + floor(b->pct);
        a->pct = 1.0f + floor(a->pct);
    }
    }
}

// ---------------------------------------------------------------------------
// 0x004e7610: verb-icon data builder.  The editor-side structures it uses live in other
// slices; only what this function touches is declared here.

void* __cdecl operator new(unsigned int size, const char* tag, int a, int b, int c, int d) throw();  // 0x00f473a0

extern const float kZero;   // 0x01485378

// Refcounted interface: vtable +0 AddRef, +4 Release.
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};

// Reference-counting smart pointer (0x0041d870 is its out-of-line GetAddress).
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** GetAddress()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

// SP::cSPEditorVerbIconData (0xc4 bytes): the per-property icon record.
struct cSPEditorVerbIconData : IRefObj {
    virtual void v02();
    virtual void v03();
    virtual void SetIcon(IRefObj* icon);     // vtable +0x10
    char mPad04[0x18 - 4];                   // +0x04
    float mValue;                            // +0x18
    float mMax;                              // +0x1c
    uint32_t mPad20;                         // +0x20
    uint32_t mKind;                          // +0x24
    char mPad28[0x4d - 0x28];                // +0x28
    bool mClamp;                             // +0x4d
    char mPad4e[0xc4 - 0x4e];                // +0x4e
    cSPEditorVerbIconData();                 // 0x005e5a70
};

// A 12-byte EASTL vector of refcounted icons (plus two allocator dwords).
struct RefVec {
    AutoRefCount<cSPEditorVerbIconData>* mBegin;   // +0
    AutoRefCount<cSPEditorVerbIconData>* mEnd;     // +4
    AutoRefCount<cSPEditorVerbIconData>* mCap;     // +8
    uint32_t mAlloc[2];
    void push_back(const AutoRefCount<cSPEditorVerbIconData>& r);   // 0x004b54b0
};

// SP::PropertyManager's object interface (GetProperty is vtable +0x2c).
struct IPropertyManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void GetProperty(uint32_t propId, uint32_t typeId, IRefObj** out);   // vtable +0x2c
};
IPropertyManager* __cdecl PropertyManager();   // 0x0067de30

struct CapabilityManager {
    static uint32_t GetPropIDForAbility(uint32_t abilityId, int flag);   // 0x00459370
};

// Property-list entry: ability id plus its amount.
struct Entry8 {
    uint32_t mID;        // +0
    float mAmount;       // +4
};
struct EntryVec {
    Entry8* mBegin;      // +0
    Entry8* mEnd;        // +4
    Entry8* mCap;        // +8
    uint32_t mAlloc[2];
};

void FillRefVec18(RefVec* out, uint32_t key);   // 0x004e7990

// @ 0x004e7610
// Builds one verb-icon record per property-list entry, clamps its value, keeps the three
// records that match the neutral/land/sea property kinds, normalises and scales their values
// by the vehicle kind, then appends the kind's own property icon.
void BuildVerbIcons(EntryVec* entries, RefVec* out, int key)
{
    int nCount = (int)(entries->mEnd - entries->mBegin);
    cSPEditorVerbIconData* a = 0;
    cSPEditorVerbIconData* b = 0;
    cSPEditorVerbIconData* c = 0;
    uint32_t nMatch = CapabilityManager::GetPropIDForAbility(key, 0);
    for (int i = 0; i < nCount; ++i) {
        AutoRefCount<IRefObj> prop(0);
        const Entry8& entry = entries->mBegin[i];
        uint32_t propID = CapabilityManager::GetPropIDForAbility(entry.mID, 0);
        IPropertyManager* pManager = PropertyManager();
        pManager->GetProperty(propID, 0x1b68db4, prop.GetAddress());
        cSPEditorVerbIconData* pIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
        pIcon->SetIcon(prop.mpObject);
        pIcon->mValue = entries->mBegin[i].mAmount;
        if (pIcon->mClamp && pIcon->mValue > pIcon->mMax)
            pIcon->mValue = pIcon->mMax;
        if (pIcon->mKind == nMatch)
            a = pIcon;
        else if (pIcon->mKind == 0x34d6bd1e)
            b = pIcon;
        else if (pIcon->mKind == 0x5979cecb)
            c = pIcon;
        out->push_back(AutoRefCount<cSPEditorVerbIconData>(pIcon));
    }
    NormalizePercents((PctItem*)a, (PctItem*)b, (PctItem*)c);
    int nKind = 0;
    switch (key) {
    case 0xbc1041e6:    // Colony_Land
    case 0x9ad7d4aa:    // Religious_Land
    case 0xf670aa43:    // Economic_Land
    case 0x7d433fad:    // Military_Land
        nKind = 0;
        break;
    case 0x8f963dcb:    // Military_Sea
    case 0xc15695da:    // Colony_Sea
    case 0x1f2a25b6:    // Religious_Sea
    case 0x2a5147a9:    // Economic_Sea
        nKind = 1;
        break;
    case 0x1a4e0708:    // Economic_Air
    case 0x98e03c0d:    // UFO
    case 0x441cd3e6:    // Military_Air
    case 0x2090a11b:    // Colony_Air
    case 0x449c040f:    // Religious_Air
        nKind = 2;
        break;
    }
    float fR = kZero;
    float fG = kZero;
    float fB = kZero;
    ScaleColorForKind(nKind, a->mValue * 0.1f, b->mValue * 0.1f, c->mValue * 0.1f,
                      &fR, &fG, &fB);
    a->mValue = fR;
    b->mValue = fG;
    c->mValue = fB;
    FillRefVec18(out, key);
}
