// src/game/SPEditors/SPEditorAnimationManager.cpp -- migrated from slice(s) s0059d300 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorAnimationManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorAnimationManager.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include <intrin.h>
#include <string.h>
#include <math.h>

// ---- items of slice s0059d300 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }
namespace EA {
template <typename T>
class RefCountVTemplate_s0059_d300 {
public:
    RefCountVTemplate_s0059_d300() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s0059_d300() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) { mnRefCount = 1; delete this; return 0; }
        return mnRefCount;
    }
protected:
    T mnRefCount;   // +0x8 when preceded by one vptr
};  // namespace EA
}
namespace SP {
struct AnimRequest;
}
namespace SP {
struct AnimResult;
}
namespace SP {
struct AnimContext;
}
namespace SP {
struct IUnknown32S {
    virtual int AddRef();
    virtual int Release();
    ~IUnknown32S() {}
};
}
namespace SP {
struct AnimVecS {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    AnimVecS() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~AnimVecS();                                      // 0x004b5440
};
}
namespace SP {
class cSPEditorAnimationManager_s0059_d300 : public EA::RefCountVTemplate_s0059_d300<int>, public IUnknown32S {
public:
    __declspec(noinline) cSPEditorAnimationManager_s0059_d300(); // 0x0059dac0
    // scalar deleting destructor ??_G is emitted from this inline destructor
    void Init();                                      // 0x0059db40
    bool GetAnimation(AnimRequest* req, AnimResult* out, AnimContext* ctx);  // 0x0059dc70
    AnimVecS mAnimations;                             // +0xc
};
}
struct RandomLinearCongruential { double RandomDoubleUniform(); };
extern RandomLinearCongruential sMathRandom;   // 0x1601760
namespace SP {
extern void* GetManagerImpl();                                    // 0x0067dcd0
}
namespace SP {
extern void* PropertyManagerImpl();                               // 0x0067de30
}
namespace SP {
extern void  DoInsertValueImpl(void* end, const void* value);     // 0x004b6000
}
namespace SP {
extern void  FreeAllocImpl(void* p);                              // 0x00f47380
}
namespace SP {
extern unsigned int kResFilterField4;   // 0x00b1b104
}
namespace SP {
extern unsigned int kResFilterGroup;    // 0x0150e79c
}
namespace SP {
class cPropertyList_s0059_d300;
}
namespace SP {
struct Key { uint32_t instance, type, group; };       // ResourceKey, 12 bytes
}
namespace SP {
bool __cdecl KeyMatches(const Key* a, const Key* b);   // 0x004a9a90 (0 in b = wildcard)
}
namespace SP {
bool GetPropertyAsKeyArray(cPropertyList_s0059_d300* list, uint32_t id, int* count, Key** keys);   // 0x006a0ae0
}
namespace SP {
bool GetPropertyAsChar8Ptr(cPropertyList_s0059_d300* list, uint32_t id, const char** value);       // 0x006a1450
}
namespace SP {
void __cdecl EASTL_allocator_deallocate(void* p);                                        // 0x00f47380
}
namespace SP {
extern const uint32_t kDefaultUIntValue;   // 0x015d1164
}
namespace SP {
extern const bool kDefaultBoolValue;       // 0x015d115d
}
namespace SP {
struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12
    int GetItemCount()
    {
        if (mnFlags & 0x30) return mnItemCount;
        else if (mnType != 0) return 1;
        return 0;
    }
    void* GetItems()
    {
        if (mnFlags & 0x30) return mpData;
        else if (mnType != 0) return this;
        return 0;
    }
    void* GetValuePtr()
    {
        if (mnFlags & 0x30) return mpData;
        return (void*)((-(int)(uint32_t)mnType >> 31) & (int)this);
    }
};
}
namespace SP {
class cPropertyList_s0059_d300 {
public:
    virtual int AddRef();
    virtual int Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c 0x006a2470
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
    virtual Property* GetPropertyObject(uint32_t id);            // +0x28
};
}
namespace SP {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
};
}
namespace SP {
template <class T> struct SpVector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p) p->~T();
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
    }
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) new (mpEnd) T(v); ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
}
namespace SP {
template <> struct SpVector<float> {
    float* mpBegin; float* mpEnd; float* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin); }
    void DoInsertValue(float* pos, const float& v);   // 0x00455660
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
}
namespace SP {
template <> struct SpVector<char> {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin); }
    void DoInsertValue(char* pos, const char& v);   // 0x00426730
    void push_back(const char& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
}
namespace SP {
struct Entity {                      // editor block
    bool HasAnyBlockFlag();          // 0x00435d40
    Key* GetKey(Key* out);           // 0x00440b90 (copies 12 bytes at +0x5f8)
    char pad0[0x28];
    struct EditorModel* mpModel;     // +0x28 (when used via the request's block)
};
}
namespace SP {
struct EditorModel {
    int GetBlockCount();             // 0x004accf0
    Entity* GetBlock(uint32_t i);    // 0x004accb0
};
}
namespace SP {
struct AnimRequest {
    char pad0[0x10];
    Entity* mpBlock;                 // +0x10
    EditorModel* mpModel;            // +0x14
    uint32_t mAnimID;                // +0x18
    char pad1c[0x28 - 0x1c];
    uint32_t mForcedAnim;            // +0x28
};
}
namespace SP {
struct AnimResult {
    uint32_t mID;                    // +0
    uint32_t mFourCC;                // +4
    bool mFlag;                      // +8
};
}
namespace SP {
struct AnimContext {
    char pad0[0x1c];
    uint32_t mKey;                   // +0x1c
    bool Matches(uint32_t v);        // 0x0059ac90
};
}
namespace SP {
struct AppPropsInner { char pad[0xdc]; int mFlag; };
}
namespace SP {
struct AppProps { char pad[0x3c]; AppPropsInner* mpInner; };
}
namespace SP {
extern AppProps* gAppProps;          // 0x015fd918
}
namespace SP {
typedef SpVector<AutoRefCount<cPropertyList_s0059_d300> > AnimListVec;
}
namespace SP {
struct AnimMgrView { char pad[0xc]; AnimListVec mAnimations; };   // +0xc
}
namespace SP {
static const uint32_t kForcedAnimID = 0x248dca26;
}
// ---- items of slice s0059d300 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern RandomLinearCongruential sMathRandom;   // 0x1601760

// @ 0x0059da80
double RandomRange(float range)
{
    double dRange = range;
    double result = sMathRandom.RandomDoubleUniform() * dRange;
    if (result >= dRange)
        return dRange;
    if (result > 0.0)
        return result;
    return 0.0;
}

// @ 0x0059dac0
SP::cSPEditorAnimationManager_s0059_d300::cSPEditorAnimationManager_s0059_d300()
{}

// @ 0x0059db40
void SP::cSPEditorAnimationManager_s0059_d300::Init()
{
    void* rm = SP::GetManagerImpl();

    // Output vector of ResourceKeys (12 bytes each) filled by the manager.
    void* outBegin = 0;
    void* outEnd = 0;
    void* outCap = 0;

    // Resource-list filter argument (vptr + two fields).
    struct ResFilter {
        void* mpVtbl;
        unsigned int m4;
        unsigned int m8;
    } filter;
    filter.m8 = SP::kResFilterGroup;
    filter.m4 = SP::kResFilterField4;
    filter.mpVtbl = (void*)&outBegin;   // placeholder; see note below

    // rm->v38(res&, filter&, 0) -- fill outBegin/outEnd.
    typedef void (__thiscall *V38)(void*, void**, void*, int);
    ((V38)(*(void***)rm)[0x38 / 4])(rm, &outBegin, &filter, 0);

    int count = (int)((char*)outEnd - (char*)outBegin) / 0x0c;
    for (int i = 0; i < count; ++i) {
        char* elem = (char*)outBegin + i * 0x0c;
        unsigned int key0 = *(unsigned int*)(elem + 0x00);
        unsigned int key2 = *(unsigned int*)(elem + 0x08);

        void* temp = 0;
        void* pm = SP::PropertyManagerImpl();
        typedef char (__thiscall *V2C)(void*, unsigned int, unsigned int, void**);
        char ok = ((V2C)(*(void***)pm)[0x2c / 4])(pm, key0, key2, &temp);
        if (ok != 0) {
            // mAnimations.push_back(AutoRefCount(temp))
            void** pend = (void**)((char*)this + 0x10);
            if (*pend < *(void**)((char*)this + 0x14)) {
                void** slot = (void**)*pend;
                *(void**)((char*)this + 0x10) =
                    (void*)((char*)slot + 4);
                if (slot != 0) {
                    *slot = temp;
                    if (temp != 0) {
                        (*(int(__thiscall**)(void*))(*(char**)temp))(temp);
                    }
                }
            } else {
                SP::DoInsertValueImpl(*pend, &temp);
            }
        }
        if (temp != 0) {
            (*(int(__thiscall**)(void*))((*(char**)temp) + 0x04))(temp);
        }
    }

    // ~SpVector: free the allocation if it owns one.
    if (outBegin != 0 && *((void**)outBegin - 1) != 0) {
        SP::FreeAllocImpl(outBegin);
    }
}

// @ 0x0059dc70
bool SP::cSPEditorAnimationManager_s0059_d300::GetAnimation(SP::AnimRequest* req, SP::AnimResult* out, SP::AnimContext* ctx)
{
    SP::AnimListVec& anims = ((SP::AnimMgrView*)this)->mAnimations;

    if ((anims.mpBegin != anims.mpEnd || req->mAnimID == SP::kForcedAnimID) && SP::gAppProps->mpInner->mFlag != 0) {
        if (req->mAnimID == SP::kForcedAnimID) {
            if (req->mForcedAnim != 0) {
                out->mID = req->mForcedAnim;
                out->mFlag = true;
                return true;
            }
        }
        else {
            SP::AnimListVec matches;
            SP::SpVector<float> weights;
            int numAnims = anims.mpEnd - anims.mpBegin;
            for (int i = 0; i < numAnims; i++) {
                SP::AutoRefCount<SP::cPropertyList_s0059_d300> list(anims.mpBegin[i]);
                if (!list->HasProperty(0xf150ffb0)) continue;
                SP::Property* prop = list->GetPropertyObject(0xf150ffb0);
                int numIDs = prop->GetItemCount();
                SP::Key* ids = (SP::Key*)prop->GetItems();
                int k = 0;
                for (; k < numIDs; k++) {
                    if (ids[k].instance == req->mAnimID) break;
                }
                if (k >= numIDs) continue;

                bool bAllRequired = true;
                int numReq; SP::Key* reqKeys;
                if (SP::GetPropertyAsKeyArray(list.mpObject, 0xff50f753, &numReq, &reqKeys) && numReq > 0) {
                    bAllRequired = false;
                    SP::SpVector<char> found;
                    for (int j = 0; j < numReq; j++) {
                        char zero = 0;
                        found.push_back(zero);
                    }
                    SP::EditorModel* model = req->mpModel;
                    if (!model && req->mpBlock) model = req->mpBlock->mpModel;
                    if (model) {
                        int numBlocks = model->GetBlockCount();
                        for (int b = 0; b < numBlocks; b++) {
                            SP::Entity* blk = model->GetBlock(b);
                            if (blk->HasAnyBlockFlag()) {
                                SP::Key bk;
                                blk->GetKey(&bk);
                                for (int j = 0; j < numReq; j++) {
                                    if (SP::KeyMatches(&bk, &reqKeys[j])) found.mpBegin[j] = 1;
                                }
                            }
                        }
                        bAllRequired = true;
                        for (int j = 0; j < numReq; j++) {
                            if (!found.mpBegin[j]) { bAllRequired = false; break; }
                        }
                    }
                }

                bool bAnyAllowed = true;
                int numAllow; SP::Key* allowKeys;
                if (SP::GetPropertyAsKeyArray(list.mpObject, 0xe99ed6ff, &numAllow, &allowKeys) && numAllow > 0 && req->mpBlock) {
                    bAnyAllowed = false;
                    for (int j = 0; j < numAllow; j++) {
                        SP::Key bk;
                        if (SP::KeyMatches(req->mpBlock->GetKey(&bk), &allowKeys[j])) { bAnyAllowed = true; break; }
                    }
                }

                if (bAllRequired && bAnyAllowed) {
                    matches.push_back(list);
                    float weight = 1.0f;
                    SP::Property* wp;
                    if (list.mpObject && list->GetProperty(0x029eb123, wp) && wp->mnType == 10) {
                        const uint32_t* pv = (const uint32_t*)wp->GetValuePtr();
                        if (ctx->Matches(*pv)) weight = 0.0f;
                    }
                    weights.push_back(weight);
                }
            }

            if (matches.mpBegin != matches.mpEnd) {
                int numWeights = weights.mpEnd - weights.mpBegin;
                float total = 0.0f;
                for (int i = 0; i < numWeights; i++) total = weights.mpBegin[i] + total;
                if (total == 0.0f && numWeights > 0) {
                    for (int i = 0; i < numWeights; i++) weights.mpBegin[i] = 1.0f;
                    for (int i = 0; i < numWeights; i++) total += 1.0f;
                }
                float r = (float)RandomRange(total);
                float acc = 0.0f;
                int idx = 0;
                for (int i = 0; i < numWeights; i++) {
                    acc = weights.mpBegin[i] + acc;
                    idx = i;
                    if (acc > r) break;
                }
                if (idx >= (int)(matches.mpEnd - matches.mpBegin) || idx < 0) idx = 0;

                SP::AutoRefCount<SP::cPropertyList_s0059_d300> chosen(matches.mpBegin[idx]);
                if (chosen->HasProperty(0x029eb123)) {
                    SP::Property* p = chosen->GetPropertyObject(0x029eb123);
                    uint16_t t = p->mnType;
                    const uint32_t* idp = (t == 10 || t == 0x10) ? (const uint32_t*)p->GetValuePtr() : &SP::kDefaultUIntValue;
                    out->mID = *idp;
                    const char* name;
                    if (SP::GetPropertyAsChar8Ptr(chosen.mpObject, 0xf711981f, &name)) {
                        char buf[4] = { 0, 0, 0, 0 };
                        strncpy(buf, name, 4);
                        out->mFourCC = ((((uint32_t)(uint8_t)buf[3] << 8 | (uint8_t)buf[2]) << 8 | (uint8_t)buf[1]) << 8) | (uint8_t)buf[0];
                    }
                    if (chosen->HasProperty(0x654234db)) {
                        SP::Property* q = chosen->GetPropertyObject(0x654234db);
                        uint16_t qt = q->mnType;
                        const bool* bp = (qt == 1 || qt == 0x10) ? (const bool*)q->GetValuePtr() : &SP::kDefaultBoolValue;
                        out->mFlag = *bp;
                    }
                    return true;
                }
            }
        }
    }
    out->mID = 0;
    return false;
}
