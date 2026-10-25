// Slice s00a70f70: EA::Swarm::cEffectsWorld effect/component routines, plus the
// cSPTransform copy helpers used for the per-effect transform lists.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------------------
// Out-of-line helpers referenced by this slice.
// ---------------------------------------------------------------------------
struct cSPTransform;

void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
void  operator delete(void* p);
extern "C" void* __cdecl memcpy(void* dst, const void* src, size_t n);

int   FUN_00a6d7b0(int a, int b);                 // 0x00A6D7B0 (unused)// The 0xd8-byte parameter block allocated by CreateInternalEffect; its
// constructor returns `this`.
struct EffectParamsBlock {
    void* Init(void* params);                     // 0x00A70DF0
};
void  __stdcall FUN_00a70cc0(cSPTransform* p);    // 0x00A70CC0  cSPTransform dtor
void* FUN_00a70d60(void* first, void* last, void* dst);     // 0x00A70D60
void  FUN_00a70730(void* first, void* last, void* dst);     // 0x00A70730
void  FUN_00a69b20(void* dst);                    // 0x00A69B20  copy-construct element
void  FUN_00a6b150(void* pos, void* src);         // 0x00A6B150  grow-and-insert element

bool WildcardMatch(const char* text, const char* pattern, bool ignoreCase);   // 0x0093D5D0
void EastlSprintf(void* str, const char* fmt, ...);                          // 0x00472FE0

extern char gEmptyString;            // 0x01667BAC
extern char gEmptyStringCap;         // 0x01667BAD

// ---------------------------------------------------------------------------
// cSPTransform: 0x5C bytes.  The first 0x38 bytes are the cSPTransformOps
// payload, copied wholesale by Assign.
// ---------------------------------------------------------------------------
struct RefCountedXform {
    virtual void v00();
    virtual void v04();                 // +0x04
    virtual void v08();
    virtual void v0c(int);              // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual int  AddRef();              // +0x34
    virtual int  Release();             // +0x38
};

struct FloatVector {                    // eastl::vector<float>
    float* mpBegin;                     // +0x00
    float* mpEnd;                       // +0x04
    float* mpCapacity;                  // +0x08
    int    mAlloc0;                     // +0x0c
    int    mAlloc1;                     // +0x10
    FloatVector& operator=(const FloatVector& rhs);   // 0x0050D4E0
};

struct cSPTransformOps {
    cSPTransformOps* Assign(const void* src);         // 0x00537DC0
    char mData[0x38];                                 // +0x00
};

struct cSPTransform : cSPTransformOps {
    RefCountedXform* mpAttachment;      // +0x38
    int              mField3c;          // +0x3c
    float            mField40;          // +0x40
    int              mField44;          // +0x44
    FloatVector      mFloats;           // +0x48

    cSPTransform* CopyFrom(const cSPTransform* src);   // 0x00A70F70
};

struct TransformVector;                 // fwd

// @ 0x00a70f70  Copy one cSPTransform: the operator payload, the ref-counted
// attachment (AddRef new / Release old), the three scalar fields and the float
// vector.
cSPTransform* cSPTransform::CopyFrom(const cSPTransform* src)
{
    Assign(src);
    RefCountedXform* const p = src->mpAttachment;
    RefCountedXform* const old = mpAttachment;
    if (p != old) {
        if (p) p->AddRef();
        mpAttachment = p;
        if (old) old->Release();
    }
    mField3c = src->mField3c;
    mField40 = src->mField40;
    mField44 = src->mField44;
    mFloats = src->mFloats;
    return this;
}

// @ 0x00a71260  Copy [first, last) forwards into dst, returning dst advanced.
cSPTransform* CopyTransformRange(cSPTransform* first, cSPTransform* last, cSPTransform* dst)
{
    if (first != last) {
        do {
            dst->Assign(first);
            RefCountedXform* const p = first->mpAttachment;
            RefCountedXform* const old = dst->mpAttachment;
            if (p != old) {
                if (p) p->AddRef();
                dst->mpAttachment = p;
                if (old) old->Release();
            }
            dst->mField3c = first->mField3c;
            dst->mField40 = first->mField40;
            dst->mField44 = first->mField44;
            dst->mFloats = first->mFloats;
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// @ 0x00a712e0  Copy [first, last) backwards into the range ending at dstEnd,
// returning the lowest written element.
cSPTransform* CopyTransformBackward(cSPTransform* first, cSPTransform* last, cSPTransform* dstEnd)
{
    if (last != first) {
        do {
            --last;
            --dstEnd;
            dstEnd->Assign(last);
            RefCountedXform* const p = last->mpAttachment;
            RefCountedXform* const old = dstEnd->mpAttachment;
            if (p != old) {
                if (p) p->AddRef();
                dstEnd->mpAttachment = p;
                if (old) old->Release();
            }
            dstEnd->mField3c = last->mField3c;
            dstEnd->mField40 = last->mField40;
            dstEnd->mField44 = last->mField44;
            dstEnd->mFloats = last->mFloats;
        } while (last != first);
        return dstEnd;
    }
    return dstEnd;
}

// eastl::vector<cSPTransform>; element stride 0x5C.
struct TransformVector {
    cSPTransform* mpBegin;              // +0x00
    cSPTransform* mpEnd;                // +0x04
    cSPTransform* mpCapacity;           // +0x08

    void Insert(cSPTransform* pos, const cSPTransform* value);   // 0x00A717D0
    void DestroyRange(cSPTransform* first, cSPTransform* last);  // 0x00A70980
};

// ---------------------------------------------------------------------------
// eastl containers used by cEffectsWorld.
// ---------------------------------------------------------------------------
struct IntVector {                      // eastl::vector<int>
    int* mpBegin;                       // +0x00
    int* mpEnd;                         // +0x04
    int* mpCapacity;                    // +0x08
    void DoInsertFromIterator(int* pos, int* first, int* last, int tag);  // 0x0042B9E0

    // eastl::vector<int>::erase(begin, end), inlined: the empty tail is copied
    // down over the erased range and the end pointer is rewound by the element
    // distance (truncating).
    void Clear()
    {
        int* const first = mpBegin;
        int* const last = mpEnd;
        int* const tail = mpEnd;
        memcpy(first, last, (size_t)((char*)tail - (char*)last));
        mpEnd = (int*)((char*)mpEnd - (int)((char*)mpEnd - (char*)first) / 4 * 4);
    }
};

struct EastlString {                    // eastl::basic_string<char>
    char* mpBegin;                      // +0x00
    char* mpEnd;                        // +0x04
    char* mpCapacity;                   // +0x08
    int   mAlloc0;                      // +0x0c

    void Init() { mpBegin = &gEmptyString; mpEnd = &gEmptyString; mpCapacity = &gEmptyStringCap; }
    void Reset() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void Destroy() { if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin); }
    void Assign(const char* first, const char* last);   // 0x00454CB0
};

struct ActiveEffectInfo;                // 0x24-byte vector element

struct EffectInfoVector {               // eastl::vector<ActiveEffectInfo>
    ActiveEffectInfo* mpBegin;          // +0x00
    ActiveEffectInfo* mpEnd;            // +0x04
    ActiveEffectInfo* mpCapacity;       // +0x08
};

namespace EA { namespace Swarm {

struct cEffectsWorld;

// cVisualEffect's component subobject (at +0x04): slot 0 initialises the
// component, slot 11 receives its owning component, slots 13/14 are the
// intrusive AddRef/Release pair.
struct IComponent {
    virtual void Init(cEffectsWorld* world, void* params, void* arg);  // +0x00
    virtual void v04();                 // +0x04
    virtual void v08();                 // +0x08
    virtual void v0c(int);              // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void ReceiveOwner(void* owner);   // +0x2c
    virtual void v30();
    virtual int  AddRef();              // +0x34
    virtual int  Release();             // +0x38
};

struct NamePair {                       // 8-byte entry in the name-pair table
    int mFirst;                         // +0x00
    int mSecond;                        // +0x04
};

// Description table for one effect page: the record array at +0x34 is indexed
// by the low 24 bits of a packed name; +0x88 holds the {a,b} name pairs.
struct EffectDescTable {
    virtual bool UseCollision(unsigned int index, EastlString* out);   // slot 0
    char  mPad04[0x34 - 0x04];          // +0x04
    char* mpRecords;                    // +0x34  (base of 0x58-stride records)
    char  mPad38[0x88 - 0x38];          // +0x38
    NamePair* mpNamePairs;              // +0x88
};

struct cEffectParams {                  // object at cEffectsWorld::+0x14
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void* Resolve(int type, int name, int page);            // +0x70
    int ResolveName(int type, int name);                            // 0x00A6D7B0
    char mPad04[0x2c - 0x04];           // +0x04
    EffectDescTable** mpTables;         // +0x2c
};

struct cVisualEffect {
    virtual int  AddRef();              // +0x00
    virtual int  Release();             // +0x04
    void* mpComponentVtable;            // +0x04  (IComponent vptr)
    char  mPad08[0x18 - 0x08];          // +0x08
    int   mField18;                     // +0x18
    int   mField1c;                     // +0x1c
    union {
        int   mEffectID;                // +0x20
        char  mIDBytes[4];              // +0x20, mIDBytes[3] is the page byte
    };
    int   mField24;                     // +0x24
    int   mField28;                     // +0x28
    int   mField2c;                     // +0x2c  (flags)
    char  mPad30[0x144 - 0x30];         // +0x30
    TransformVector mTransforms;        // +0x144
    char  mPad150[0x17c - 0x150];       // +0x150
    void* mpParams;                     // +0x17c

    void SetDescription(const void* desc);   // 0x00A82370
};

inline IComponent* Component(cVisualEffect* e) { return (IComponent*)((char*)e + 4); }
inline IComponent* Component(const cVisualEffect* e) { return (IComponent*)((char*)e + 4); }

// Slot holding an effect component plus the resolved id it was built from.
struct EffectSlot {
    char        mHead[0x38];            // +0x00
    IComponent* mpComponent;            // +0x38
    char        mPad3c[0x44 - 0x3c];    // +0x3c
    int         mResolvedID;            // +0x44
};

struct EffectTypeEntry {                // array at 0x01675EB8, stride 0x20
    void* mpFactory;                    // +0x00  (resolved, page)
    char  mPad04[0x20 - 0x04];
};

struct cEffectsWorld {
    char           mHead[0x14];         // +0x00
    cEffectParams* mpParams;            // +0x14
    int            mField18;            // +0x18
    int            mField1c;            // +0x1c
    int            mField20;            // +0x20
    char           mbField24;           // +0x24
    char           mPad25[0x30 - 0x25]; // +0x25
    cVisualEffect** mpEffects;          // +0x30  (indexed by effect id)
    char           mPad34[0x44 - 0x34]; // +0x34
    IntVector      mPending;            // +0x44  (pending effect indices)
    char           mPad50[0x58 - 0x50]; // +0x50
    IntVector      mActive;             // +0x58

    cVisualEffect* NewVisualEffect();                                 // 0x00A70BB0
    void CreateComponentFromDescription(int* desc, EffectSlot* slot, IComponent** out,
                                        int arg5, unsigned int name); // 0x00A70FD0
    void AppendPendingToActive(int tag);                              // 0x00A711C0
    bool CreateEffectForDescription(int type, void* name, cVisualEffect** out); // 0x00A71360
    cVisualEffect* CreateInternalEffect(unsigned int name, int page, void* params); // 0x00A71410
    void* ResolveEffect(int type, int name, int page, void* params);  // 0x00A714F0
    void GetActiveEffectInfo(EffectInfoVector* out, const char* filter, int level); // 0x00A71580
    void ReleaseEffectInfo(cVisualEffect* effect);                    // 0x00A71910
    void SelectEffects(int type);                                     // 0x00A719C0
};

}}  // namespace EA::Swarm

using EA::Swarm::cEffectsWorld;
using EA::Swarm::cVisualEffect;
using EA::Swarm::EffectSlot;
using EA::Swarm::IComponent;
using EA::Swarm::EffectDescTable;

struct ActiveEffectInfo {               // 0x24-byte push_back element
    EastlString  mText;                 // +0x00
    EastlString  mLabel;                // +0x10
    cVisualEffect* mpEffect;            // +0x20
};

extern EA::Swarm::EffectTypeEntry gEffectTypes[];   // 0x01675EB8

// @ 0x00a70fd0  Build the component for one effect description.  When the
// description carries no type a fresh visual effect is created and its name is
// resolved (either through the 0x7f****** name table or from the id itself);
// otherwise the existing component-table entry is resolved through the
// effect-type factory.  The component is stored into the slot and the slot's
// resolved id is updated.
void cEffectsWorld::CreateComponentFromDescription(int* desc, EffectSlot* slot, IComponent** out,
                                                   int arg5, unsigned int name)
{
    const int type = desc[0];
    const int page = (int)name >> 24;
    if (type == 0) {
        cVisualEffect* const effect = NewVisualEffect();
        IComponent* const comp = Component(effect);
        comp->Init(this, mpParams, (void*)arg5);
        const unsigned int id = (unsigned int)desc[0x20];
        if ((int)id >= 0) {
            if ((id & 0xff000000) == 0x7f000000) {
                NamePair* const pairs = mpParams->mpTables[page]->mpNamePairs;
                effect->mEffectID = mpParams->ResolveName(pairs[id & 0xffffff].mFirst,
                                                          pairs[id & 0xffffff].mSecond);
            } else {
                effect->mEffectID = (int)((name & 0xff000000) | id);
            }
            const int resolved = effect->mEffectID;
            effect->SetDescription(mpParams->mpTables[resolved >> 24]->mpRecords
                                   + (resolved & 0xffffff) * 0x58);
        }
        effect->mField2c |= 0x20;

        IComponent* const old = slot->mpComponent;
        if (comp != old) {
            if (comp) comp->AddRef();
            slot->mpComponent = comp;
            if (old) old->Release();
        }
    } else {
        if (gEffectTypes[type].mpFactory != 0) {
            void* const resolved = mpParams->Resolve(type, desc[0x20], page);
            IComponent* const created =
                (IComponent*)((void* (*)(void*, int))gEffectTypes[type].mpFactory)(resolved, page);
            IComponent* const old = slot->mpComponent;
            if (created != old) {
                if (created) created->AddRef();
                slot->mpComponent = created;
                if (old) old->Release();
            }
        }
        if (slot->mpComponent != 0) {
            slot->mpComponent->Init(this, mpParams, (void*)arg5);
            if (((unsigned int)desc[1] >> 1 & 1) != 0) {
                if (*out != 0)
                    (*out)->ReceiveOwner(slot->mpComponent);
                if (((unsigned int)desc[1] >> 2 & 1) != 0) {
                    *out = 0;
                    slot->mResolvedID = desc[1];
                    return;
                }
                *out = slot->mpComponent;
                slot->mResolvedID = desc[1];
                return;
            }
            *out = 0;
        }
    }
    slot->mResolvedID = desc[1];
}

// @ 0x00a711c0  Append the pending index range to the active-index vector
// (at most ten rounds), then clear the pending range.
void cEffectsWorld::AppendPendingToActive(int tag)
{
    if (mbField24)
        return;
    int n = 10;
    if (mPending.mpBegin != mPending.mpEnd) {
        do {
            if (n < 1)
                break;
            mActive.DoInsertFromIterator(mActive.mpEnd, mPending.mpBegin, mPending.mpEnd, tag);
            --n;
            mPending.Clear();
        } while (mPending.mpBegin != mPending.mpEnd);
    }
    mPending.Clear();
}

// @ 0x00a71360  Resolve the description name, create a visual effect for it and
// hand its component back through `out`.  Returns false when effects are
// filtered out or the name is unknown.
bool cEffectsWorld::CreateEffectForDescription(int type, void* name, cVisualEffect** out)
{
    if (out == 0 || mField20 == 5)
        return false;
    const int resolved = mpParams->ResolveName(type, (int)name);
    if (resolved < 0)
        return false;
    cVisualEffect* const effect = NewVisualEffect();
    Component(effect)->Init(this, mpParams, 0);
    effect->mField18 = type;
    effect->mField1c = (int)name;
    effect->mEffectID = resolved;
    effect->SetDescription(mpParams->mpTables[resolved >> 24]->mpRecords
                           + (resolved & 0xffffff) * 0x58);
    AppendPendingToActive(0);
    *out = effect;
    effect->AddRef();
    return true;
}

// @ 0x00a71410  Create an internal effect from a packed name: 0x7f****** names
// are resolved through the description table, everything else keeps the page in
// the top byte.  Optionally attaches fresh effect parameters.
cVisualEffect* cEffectsWorld::CreateInternalEffect(unsigned int name, int page, void* params)
{
    int resolved;
    if ((name & 0xff000000) == 0x7f000000) {
        NamePair* const pairs = mpParams->mpTables[page]->mpNamePairs;
        resolved = mpParams->ResolveName(pairs[name & 0xffffff].mFirst,
                                         pairs[name & 0xffffff].mSecond);
        if (resolved < 0)
            return 0;
    } else {
        resolved = (int)(name | ((unsigned int)page << 24));
    }

    cVisualEffect* const effect = NewVisualEffect();
    Component(effect)->Init(this, mpParams, 0);
    effect->mField2c |= 0x40;
    if (params != 0) {
        void* const mem = ::operator new(0xd8, "Swarm/EffectParams", 0, 0, 0, 0);
        effect->mpParams = mem ? ((EffectParamsBlock*)mem)->Init(params) : 0;
    }
    effect->mEffectID = resolved;
    if (resolved >= 0) {
        effect->SetDescription(mpParams->mpTables[resolved >> 24]->mpRecords
                               + (resolved & 0xffffff) * 0x58);
    }
    return effect;
}

// @ 0x00a714f0  Resolve an effect by type; type 0 creates an internal effect.
// Returns the component subobject pointer.
void* cEffectsWorld::ResolveEffect(int type, int name, int page, void* params)
{
    if (type == 0) {
        cVisualEffect* const effect = CreateInternalEffect((unsigned int)name, page, params);
        return effect ? (void*)((char*)effect + 4) : 0;
    }
    IComponent* found = 0;
    if (gEffectTypes[type].mpFactory != 0) {
        void* const resolved = mpParams->Resolve(type, name, page);
        found = (IComponent*)((void* (*)(void*, int))gEffectTypes[type].mpFactory)(resolved, page);
        if (found)
            found->Init(this, mpParams, params);
    }
    return found;
}

// @ 0x00a71580  Collect every active effect that passes the level filters and
// the wildcard, formatting its id text when the drawable has none.
void cEffectsWorld::GetActiveEffectInfo(EffectInfoVector* out, const char* filter, int level)
{
    EastlString name;
    name.Init();

    const unsigned int count = (unsigned int)(mActive.mpEnd - mActive.mpBegin);
    for (unsigned int i = 0; i < count; ++i) {
        cVisualEffect* const effect = mpEffects[mActive.mpBegin[i]];
        if (level < 2 && ((unsigned int)effect->mField2c >> 5 & 1) != 0)
            continue;
        if (level < 1 && ((unsigned int)effect->mField2c >> 6 & 1) != 0)
            continue;
        if (level < 2 && ((unsigned int)effect->mField2c >> 9 & 1) == 0)
            continue;
        if (effect->mEffectID < 0)
            continue;

        name.Reset();
        if (!mpParams->mpTables[effect->mEffectID >> 24]->UseCollision(
                (unsigned int)effect->mEffectID & 0xffffff, &name)) {
            EastlSprintf(&name, "0x%08x", effect->mField18, effect->mField1c);
        }
        if (filter != 0 && !WildcardMatch(name.mpBegin, filter, false))
            continue;

        ActiveEffectInfo info;
        info.mText.Init();
        info.mLabel.Init();
        info.mpEffect = 0;
        info.mText.Assign(name.mpBegin, name.mpEnd);

        cVisualEffect* const old = info.mpEffect;
        if (effect != old) {
            if (effect) effect->AddRef();
            info.mpEffect = effect;
            if (old) old->Release();
        }

        if (out->mpEnd < out->mpCapacity) {
            ActiveEffectInfo* const slot = out->mpEnd;
            out->mpEnd = slot + 1;
            if (slot) FUN_00a69b20(slot);
        } else {
            FUN_00a6b150(out->mpEnd, &info);
        }
        if (info.mpEffect) info.mpEffect->Release();
        info.mLabel.Destroy();
        info.mText.Destroy();
    }
    name.Destroy();
}

// @ 0x00a71910  Drop every component held by the given effect's transform
// list, then compact the list.
void cEffectsWorld::ReleaseEffectInfo(cVisualEffect* effect)
{
    TransformVector* const vec = &effect->mTransforms;
    int count = (int)((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x5c;
    if (count != 0) {
        char* offset = (char*)vec->mpBegin;
        do {
            cSPTransform* const t = (cSPTransform*)offset;
            t->mpAttachment->v0c(1);
            t->mpAttachment->v04();
            if (t->mpAttachment) {
                RefCountedXform* const old = t->mpAttachment;
                t->mpAttachment = 0;
                old->Release();
            }
            offset += 0x5c;
        } while (--count != 0);
    }
    cSPTransform* const begin = vec->mpBegin;
    cSPTransform* const end = vec->mpEnd;
    cSPTransform* const dst = CopyTransformRange(end, end, begin);
    vec->DestroyRange(dst, end);
    const int bytes = (int)((char*)end - (char*)begin);
    vec->mpEnd = (cSPTransform*)((char*)vec->mpEnd + bytes / -0x5c * 0x5c);
}

// @ 0x00a719c0  Release the transforms of every active effect whose type byte
// matches `type`, or of every active effect when type < 0.
void cEffectsWorld::SelectEffects(int type)
{
    int* it = mActive.mpBegin;
    if (it == mActive.mpEnd)
        return;
    do {
        cVisualEffect* const effect = mpEffects[*it];
        if (type < 0 || type == (signed char)effect->mIDBytes[3])
            ReleaseEffectInfo(effect);
        ++it;
    } while (it != mActive.mpEnd);
}

// @ 0x00a717d0  Insert a copy of `value` before `pos`, growing the buffer by
// doubling when it is full.
void TransformVector::Insert(cSPTransform* pos, const cSPTransform* value)
{
    if (mpEnd != mpCapacity) {
        if ((unsigned int)pos <= (unsigned int)value && (unsigned int)value < (unsigned int)mpEnd)
            value = (const cSPTransform*)((const char*)value + 0x5c);
        if (mpEnd)
            FUN_00a70cc0(mpEnd - 1);
        CopyTransformBackward(pos, mpEnd - 1, mpEnd);
        pos->CopyFrom(value);
        mpEnd = (cSPTransform*)((char*)mpEnd + 0x5c);
        return;
    }

    int n = (int)((char*)mpEnd - (char*)mpBegin) / 0x5c;
    cSPTransform* mem;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0) {
            mem = 0;
            goto have_memory;
        }
    }
    mem = (cSPTransform*)::operator new(n * 0x5c, "EASTL", 0, 0,
                                        "EASTL/allocator.h", 0xd1);
have_memory:
    cSPTransform* const oldBegin = mpBegin;
    cSPTransform* const first = (cSPTransform*)FUN_00a70d60(oldBegin, pos, mem);
    FUN_00a70730(oldBegin, pos, mem);
    if (first)
        FUN_00a70cc0((cSPTransform*)value);
    cSPTransform* const oldEnd = mpEnd;
    cSPTransform* const newEnd = (cSPTransform*)FUN_00a70d60(pos, oldEnd, (char*)first + 0x5c);
    FUN_00a70730(pos, oldEnd, (char*)first + 0x5c);
    if (oldBegin && *(int*)((char*)oldBegin - 4) != 0)
        ::operator delete(oldBegin);
    mpBegin = mem;
    mpEnd = newEnd;
    mpCapacity = (cSPTransform*)((char*)mem + n * 0x5c);
}
