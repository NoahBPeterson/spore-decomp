// src/game/Swarm/EffectsWorld.cpp -- migrated from slice(s) s00a71a00, s00a70f70, s00a6ff50, s01300280 by tools/migrate/rewrite.py
// Object file: Swarm/EffectsWorld.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Swarm/cVisualEffect.h"
#include "EA/Swarm/cEffectParams.h"
#include "cSPTransform.h"

// ---- items of slice s00a6ff50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete__(void* p);                                    // 0xf47380
extern "C" void* EAAllocate(unsigned size, const char* file, int a, int b, int c, int d); // 0xf473a0
extern "C" void* __cdecl memmove_nd(void* dst, const void* src, unsigned n);    // 0x11e0744
extern int  gEmptyString16;      // 0x1667bac
extern int  gGmeRefCountVtbl;    // 0x13ef094
extern int  gWorldVtblA;         // 0x1455fb8
extern int  gWorldVtblB;         // 0x1455fb4
extern float gDescF4;      // 0x1676b2c
extern float gDescF8;      // 0x1676b30
extern float gDescFC;      // 0x1676b34
struct M33 {
    float m[9];
    void Assign(const void* src);    // 0x41cb40
};
struct Vec3 { float x, y, z; };
struct IVEBase {
    virtual void AddRef();            // 0x00
    virtual void ReleasePrimary();    // 0x04
    virtual void v08();               // 0x08
    virtual void Stop(int code);      // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
};
struct IVERef {
    virtual void Init(void* world, void* manager, int flags);   // 0x00
    virtual void Release();                                     // 0x04
virtual void v08();
virtual void v0c();
};
struct cVisualEffect : IVEBase, IVERef {
    int   m08;        // +0x08
    int   m0c;        // +0x0c
    int   m10;        // +0x10 state
    int   m14;        // +0x14
    int   m18;        // +0x18
    int   m1c;        // +0x1c
    int   m20;        // +0x20
    int   m24;        // +0x24
    int   m28;        // +0x28
    int   mFlags;     // +0x2c
    cVisualEffect* Ctor();                          // 0xa83c00
    bool  CheckIfStopped();                         // 0xa82430
    void  SetDescription(const void* desc);         // 0xa82370
};
struct IntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    void DoInsertValue(int* pos, const int& v);     // 0x4558a0
    void CtorGrow(int count, const int* fill);      // 0x4aa350
    void Add(const int& v)
    {
        if (mpEnd < mpCap) {
            int* e = mpEnd;
            mpEnd = e + 1;
            if (e) *e = v;
        }
        else {
            DoInsertValue(mpEnd, v);
        }
    }
    void EraseAdd(int* first, int* last)
    {
        memmove_nd(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= last - first;
    }
};
struct VEVec {
    cVisualEffect** mpBegin;
    cVisualEffect** mpEnd;
    cVisualEffect** mpCap;
    void DoInsertValue(cVisualEffect** pos, cVisualEffect* const& v);   // 0xa0a360
    void Dtor();                                                      // 0xae6970
    void erase(cVisualEffect** first, cVisualEffect** last);          // 0xe25bd0
    void Add(cVisualEffect* const& v)
    {
        if (mpEnd < mpCap) {
            cVisualEffect** e = mpEnd;
            mpEnd = e + 1;
            if (e) *e = v;
        }
        else {
            DoInsertValue(mpEnd, v);
        }
    }
};
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
};
struct GmeRefCount {
    virtual void AddRef();
    virtual void Release();
    int mnRefCount;
    GmeRefCount() : mnRefCount(0) {}
};
struct IWorldVtbl {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(int code);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c(void*, void*, int);
};
struct LODWorld {
    char pad[0x40];
    unsigned char mBase;   // +0x40
    unsigned char pad41[3];
    Vec3* mpPoints;        // +0x44
    Vec3* mpPointsEnd;     // +0x48
};
struct LODComponent {
    char pad[0x38];
    void* mpRenderer;      // +0x38
};
struct cEffectsWorld : public IWorldVtbl, public GmeRefCount {
    bool   mInitialized;        // +0x0c
    unsigned char pad0d[3];
    int    m10;                 // +0x10
    void*  mManager;            // +0x14
    void*  mGlobalParams;       // +0x18
    void*  mpRenderer;          // +0x1c
    int    m20;                 // +0x20
    bool   mUpdating;           // +0x24
    unsigned char pad25[3];
    int    mState;              // +0x28
    int    m2c;                 // +0x2c
    VEVec  mVE;                 // +0x30
    int    m3c;                 // +0x3c
    int    m40;                 // +0x40
    IntVec mFree;               // +0x44
    int    m50;                 // +0x50
    int    m54;                 // +0x54
    IntVec mActive;             // +0x58
    int    m64;                 // +0x64
    int    m68;                 // +0x68
    IntVec mNew;                // +0x6c
    int    m78;                 // +0x78
    int    m7c;                 // +0x7c
    int    m80;                 // +0x80
    int    m84;                 // +0x84
    float  m88;                 // +0x88
    int    m8c;                 // +0x8c
    int    m90;                 // +0x90
    EString mDebugName;         // +0x94

    void StopStopped();                                  // 0x00a70330
    void ForEachActive(void (*fn)(cVisualEffect*, void*), void* user, int mode); // 00a70370
    cVisualEffect* NewVisualEffect();                    // 00a70bb0
    void DeactivateUnusedVisualEffects();                // 00a70a40
    void DeactivateAll();                                // 00a70af0
    bool Teardown();                                     // 00a709e0
    void SetRenderer(void* renderer);                    // 00a70da0
    static void __stdcall UpdateComponentLODs(LODWorld* self, void* h, int index);  // 00a70400
    void* CreateInternalEffect(unsigned a, unsigned b, const void* params); // 00a70ec0
    cEffectsWorld(unsigned flags, const void* params);   // 00a70780
    ~cEffectsWorld();                                    // 00a70870
};
struct ParamElem;
struct IParamRef {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
    virtual void s30();
    virtual void AddRefI();    // slot 13 (0x34)
    virtual void ReleaseI();   // slot 14 (0x38)
};
struct ParamElem {
    unsigned short f00;    // +0x00
    unsigned short f02;    // +0x02
    float f04;             // +0x04
    float f08;             // +0x08
    float f0c;             // +0x0c
    float f10;             // +0x10
    M33   m14;             // +0x14
    IParamRef* mp38;       // +0x38
    int   f3c;             // +0x3c
    float f40;             // +0x40
    int   f44;             // +0x44
    IntVec vec;            // +0x48
    int   f54;             // +0x54
    int   f58;             // +0x58
};
struct Desc58 {
    unsigned short f0;     // +0x00
    unsigned short f2;     // +0x02
    float f4;              // +0x04
    float f8;              // +0x08
    float fc;              // +0x0c
    float f10;             // +0x10
    M33   m14;             // +0x14
    int   f38;             // +0x38
    int   f3c;             // +0x3c
    int   f40;             // +0x40
    int   f44;             // +0x44
    int   f48;             // +0x48
    int   f4c;             // +0x4c
    int   f50;             // +0x50
    int   f54;             // +0x54
    Desc58* Ctor();        // 00a70910
};
extern M33   gDescM33;     // 0x1676bd8
struct cEffectsManagerRef {
    int GetEffectIndex(unsigned a, unsigned b);   // 0xa6d7b0
};
struct EffectParams {
    EffectParams* Clone(const EffectParams* src);   // 0x00a70df0
};
struct cGlobalParams;
cGlobalParams* CreateGlobalParams(void* mem, const void* params);   // 0x00a704b0
// ---- items of slice s00a6ff50 end

// ---- items of slice s00a70f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, size_t n);
extern char gEmptyString;            // 0x01667BAC
extern char gEmptyStringCap;         // 0x01667BAD
struct cSPTransform_s00a7_0f70;
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
void  operator delete(void* p);
struct EffectParamsBlock {
    void* Init(void* params);                     // 0x00A70DF0
};
void  __stdcall FUN_00a70cc0(cSPTransform_s00a7_0f70* p);    // 0x00A70CC0  cSPTransform dtor
void* FUN_00a70d60(void* first, void* last, void* dst);     // 0x00A70D60
void  FUN_00a70730(void* first, void* last, void* dst);     // 0x00A70730
void  FUN_00a69b20(void* dst);                    // 0x00A69B20  copy-construct element
void  FUN_00a6b150(void* pos, void* src);         // 0x00A6B150  grow-and-insert element
bool WildcardMatch(const char* text, const char* pattern, bool ignoreCase);   // 0x0093D5D0
void EastlSprintf(void* str, const char* fmt, ...);                          // 0x00472FE0
struct RefCountedXform {
    virtual void v00();
    virtual void v04();                 // +0x04
    virtual void v08();
    virtual void v0c(int);              // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
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
struct cSPTransform_s00a7_0f70 : cSPTransformOps {
    RefCountedXform* mpAttachment;      // +0x38
    int              mField3c;          // +0x3c
    float            mField40;          // +0x40
    int              mField44;          // +0x44
    FloatVector      mFloats;           // +0x48

    cSPTransform_s00a7_0f70* CopyFrom(const cSPTransform_s00a7_0f70* src);   // 0x00A70F70
};
struct TransformVector;                 // fwd
struct TransformVector {
    cSPTransform_s00a7_0f70* mpBegin;              // +0x00
    cSPTransform_s00a7_0f70* mpEnd;                // +0x04
    cSPTransform_s00a7_0f70* mpCapacity;           // +0x08

    void Insert(cSPTransform_s00a7_0f70* pos, const cSPTransform_s00a7_0f70* value);   // 0x00A717D0
    void DestroyRange(cSPTransform_s00a7_0f70* first, cSPTransform_s00a7_0f70* last);  // 0x00A70980
};
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
namespace EA {
namespace Swarm {
struct cEffectsWorld_s00a7_0f70;
}
}
namespace EA {
namespace Swarm {
struct IComponent {
    virtual void Init(cEffectsWorld_s00a7_0f70* world, void* params, void* arg);  // +0x00
    virtual void v04();                 // +0x04
    virtual void v08();                 // +0x08
    virtual void v0c(int);              // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void ReceiveOwner(void* owner);   // +0x2c
    virtual void v30();
    virtual int  AddRef();              // +0x34
    virtual int  Release();             // +0x38
};
}
}
namespace EA {
namespace Swarm {
struct NamePair {                       // 8-byte entry in the name-pair table
    int mFirst;                         // +0x00
    int mSecond;                        // +0x04
};
}
}
namespace EA {
namespace Swarm {
struct EffectDescTable {
    virtual bool UseCollision(unsigned int index, EastlString* out);   // slot 0
    char  mPad04[0x34 - 0x04];          // +0x04
    char* mpRecords;                    // +0x34  (base of 0x58-stride records)
    char  mPad38[0x88 - 0x38];          // +0x38
    NamePair* mpNamePairs;              // +0x88
};
}
}
namespace EA {
namespace Swarm {
struct cEffectParams_s00a7_0f70 {                  // object at cEffectsWorld::+0x14
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void* Resolve(int type, int name, int page);            // +0x70
    int ResolveName(int type, int name);                            // 0x00A6D7B0
    char mPad04[0x2c - 0x04];           // +0x04
    EffectDescTable** mpTables;         // +0x2c
};
}
}
namespace EA {
namespace Swarm {
struct cVisualEffect_s00a7_0f70 {
    virtual int  AddRef();              // +0x00 0x00923490
    virtual int  Release();             // +0x04 0x00a81d80
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
}
}
namespace EA {
namespace Swarm {
inline IComponent* Component(cVisualEffect_s00a7_0f70* e) { return (IComponent*)((char*)e + 4); }
}
}
namespace EA {
namespace Swarm {
inline IComponent* Component(const cVisualEffect_s00a7_0f70* e) { return (IComponent*)((char*)e + 4); }
}
}
namespace EA {
namespace Swarm {
struct EffectSlot {
    char        mHead[0x38];            // +0x00
    IComponent* mpComponent;            // +0x38
    char        mPad3c[0x44 - 0x3c];    // +0x3c
    int         mResolvedID;            // +0x44
};
}
}
namespace EA {
namespace Swarm {
struct EffectTypeEntry {                // array at 0x01675EB8, stride 0x20
    void* mpFactory;                    // +0x00  (resolved, page)
    char  mPad04[0x20 - 0x04];
};
}
}
namespace EA {
namespace Swarm {
struct cEffectsWorld_s00a7_0f70 {
    char           mHead[0x14];         // +0x00
    cEffectParams_s00a7_0f70* mpParams;            // +0x14
    int            mField18;            // +0x18
    int            mField1c;            // +0x1c
    int            mField20;            // +0x20
    char           mbField24;           // +0x24
    char           mPad25[0x30 - 0x25]; // +0x25
    cVisualEffect_s00a7_0f70** mpEffects;          // +0x30  (indexed by effect id)
    char           mPad34[0x44 - 0x34]; // +0x34
    IntVector      mPending;            // +0x44  (pending effect indices)
    char           mPad50[0x58 - 0x50]; // +0x50
    IntVector      mActive;             // +0x58

    cVisualEffect_s00a7_0f70* NewVisualEffect();                                 // 0x00A70BB0
    void CreateComponentFromDescription(int* desc, EffectSlot* slot, IComponent** out,
                                        int arg5, unsigned int name); // 0x00A70FD0
    void AppendPendingToActive(int tag);                              // 0x00A711C0
    bool CreateEffectForDescription(int type, void* name, cVisualEffect_s00a7_0f70** out); // 0x00A71360
    cVisualEffect_s00a7_0f70* CreateInternalEffect(unsigned int name, int page, void* params); // 0x00A71410
    void* ResolveEffect(int type, int name, int page, void* params);  // 0x00A714F0
    void GetActiveEffectInfo(EffectInfoVector* out, const char* filter, int level); // 0x00A71580
    void ReleaseEffectInfo(cVisualEffect_s00a7_0f70* effect);                    // 0x00A71910
    void SelectEffects(int type);                                     // 0x00A719C0
};
}
}
using EA::Swarm::cEffectsWorld_s00a7_0f70;
using EA::Swarm::cVisualEffect_s00a7_0f70;
using EA::Swarm::EffectSlot;
using EA::Swarm::IComponent;
using EA::Swarm::EffectDescTable;
struct ActiveEffectInfo {               // 0x24-byte push_back element
    EastlString  mText;                 // +0x00
    EastlString  mLabel;                // +0x10
    cVisualEffect_s00a7_0f70* mpEffect;            // +0x20
};
extern EA::Swarm::EffectTypeEntry gEffectTypes[];   // 0x01675EB8
// ---- items of slice s00a70f70 end

// ---- items of slice s00a71a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_sRandom;                                            // 0x016778dc
struct cSPTransform_s00a7_1a00 { unsigned int mData[0x0e]; };
struct cVECompDef {
    char           pad00[0x04];
    unsigned int   mFlags;          // +0x04
    char           pad08[0x38];
    unsigned char  mLODMin;         // +0x40
    unsigned char  mLODMax;         // +0x41
    char           pad42[0x2e];
    unsigned int   mMaskA;          // +0x70
    unsigned int   mMaskB;          // +0x74
    unsigned short mProbThreshold;  // +0x78
    unsigned short mProbStep;       // +0x7a
    float          mBlend;          // +0x7c
    int            m80;             // +0x80
};
struct cVECompRec {
    char           pad00[0x38];
    void*          mComponent;      // +0x38
    int            mDefIndex;       // +0x3c
    char           pad40[0x04];
    unsigned int   mFlags;          // +0x44
    unsigned int*  mIdxBegin;       // +0x48
    unsigned int*  mIdxEnd;         // +0x4c
    unsigned int*  mIdxCap;         // +0x50
    char           pad54[0x08];
};
struct cVEDescription {
    unsigned int   mFlags;          // +0x00
    char           pad04[0x40];
    cVECompDef*    mpCompDefs;      // +0x44
    cVECompDef*    mpCompDefsEnd;   // +0x48
};
struct cVECreateOut {
    int            mOut;            // +0x00
    cSPTransform_s00a7_1a00   mXform;          // +0x04
    void*          mComponent;      // +0x3c
    char           pad40[0x0c];
    void*          mBuffer;         // +0x4c
};
struct cVisualEffect_s00a7_1a00 {
    char pad00[0x18];
    int  m18;                     // +0x18
    int  m1c;                     // +0x1c
    union {
        int m20;                                          // +0x20 packed effect handle
        struct { char _pad20[3]; signed char mComponentType; };   // +0x23
    };
    char pad24[0x04];
    int  m28;                     // +0x28 description pointer
    unsigned int m2c;             // +0x2c flags
    char pad30[0x18];
    int  m48;                     // +0x48 current LOD
    float m4c;                    // +0x4c LOD blend
    char pad50[0x84];
    cSPTransform_s00a7_1a00 mD4;             // +0xd4
    cSPTransform_s00a7_1a00 m10c;            // +0x10c
    cVECompRec* mRecBegin;        // +0x144
    cVECompRec* mRecEnd;          // +0x148
    cVECompRec* mRecCap;          // +0x14c
    char pad150[0x2c];
    int  m17c;                    // +0x17c

    void UpdateDescription(void* desc);   // 0x00a823e0
};
struct EffectsManager {
    char  pad00[0x2c];
    void** mTables;    // +0x2c array of description-table pointers
    char  pad30[0x1c];
    int   m4c;         // +0x4c
    char  pad50[0x18];
    int   m68;         // +0x68
    int   ResolveEffectName(int a, int b);   // 0x00a6d7b0
};
struct cEffectsWorld_s00a7_1a00 {
    char             pad00[0x14];
    EffectsManager*  mManager;     // +0x14
    char             pad18[0x08];
    int              mState;       // +0x20
    char             pad24[0x08];
    unsigned int     mFlags;       // +0x2c
    cVisualEffect_s00a7_1a00**  mVE;          // +0x30 begin
    cVisualEffect_s00a7_1a00**  mVEend;       // +0x34 end
    cVisualEffect_s00a7_1a00**  mVEcap;       // +0x38 cap
    char             pad3c[0x1c];
    int*             mActive;      // +0x58 begin
    int*             mActiveEnd;   // +0x5c end
    int*             mActiveCap;   // +0x60 cap

    void ResetVisualEffectDescription(cVisualEffect_s00a7_1a00* effect);      // 0x00a71f90
    void FUN_00a71910(cVisualEffect_s00a7_1a00* effect);                      // 0x00a71910
    void FUN_00a711c0(int arg);                                    // 0x00a711c0
    void ResetVisualEffectDescriptions(int type);                  // 0x00a72010
    void FUN_00a72060(int type);                                   // 0x00a72060
    void SetState(int state);                                      // 0x00a720b0
    void UpdateVisualEffect(cVisualEffect_s00a7_1a00* effect, int a, int b);  // 0x00a71a00
    void DeactivateAll();                                          // 0x00a70af0
    void DeactivateUnusedVisualEffects();                          // 0x00a70a40
    static void __stdcall UpdateComponentLODs(void* def, void* rec, int lod);  // 0x00a70400
    void CreateComponentFromDescription(void* def, cSPTransform_s00a7_1a00* pXform, int* pOut,
                                        int a, int b);             // 0x00a70fd0
};
void __stdcall FUN_00a70f70(void* dst, void* src);                // 0x00a70f70
void* __cdecl FUN_00a71260(void* a, void* b, void* c);            // 0x00a71260
void __stdcall FUN_00a70980(void* a, void* b);                    // 0x00a70980
void __stdcall FUN_00a70910(cSPTransform_s00a7_1a00* self);                  // 0x00a70910
void __stdcall FUN_00a70cc0(void* p);                             // 0x00a70cc0
void __stdcall FUN_00a717d0(void* self, void* a, void* b);        // 0x00a717d0
void __stdcall FUN_00a828a0();                                    // 0x00a828a0
void* __stdcall FUN_007d5590(void* result, void* a, void* b, void* c);   // 0x007d5590
void* __stdcall cSPTransformOps_Assign(void* dst, void* src);     // 0x00537dc0
void __stdcall DoInsertValue_SI(void* vec, unsigned int* p, const unsigned int* v);  // 0x004558a0
unsigned int __stdcall RandomUint32Uniform(void* rng, unsigned int range);   // 0x00a68fb0
// ---- items of slice s00a71a00 end

// @ 0x00a70330
void cEffectsWorld::StopStopped()
{
    mUpdating = true;
    int* it = mActive.mpBegin;
    if (it != mActive.mpEnd) {
        do {
            cVisualEffect* ve = mVE.mpBegin[*it];
            if (ve->m10 == 1)
                ve->Stop(1);
            ++it;
        } while (it != mActive.mpEnd);
    }
    mUpdating = false;
}

// @ 0x00a70370
void cEffectsWorld::ForEachActive(void (*fn)(cVisualEffect*, void*), void* user, int mode)
{
    int count = (int)(mActive.mpEnd - mActive.mpBegin);
    unsigned i = 0;
    if (count != 0) {
        do {
            int id = mActive.mpBegin[i];
            if (mode < 2 && ((mVE.mpBegin[id]->mFlags >> 5) & 1))
                goto next;
            if (mode < 1 && ((mVE.mpBegin[id]->mFlags >> 6) & 1))
                goto next;
            if (mode < 2 && !((mVE.mpBegin[id]->mFlags >> 9) & 1))
                goto next;
            {
                cVisualEffect* ve = mVE.mpBegin[id];
                if (ve->m20 >= 0)
                    fn(ve, user);
            }
        next:
            ++i;
        } while (i < (unsigned)count);
    }
}

// @ 0x00a70400
void __stdcall cEffectsWorld::UpdateComponentLODs(LODWorld* self, void* h, int index)
{
    if (self->mpPoints == self->mpPointsEnd)
        return;
    int i0, i1;
    if ((int)(self->mpPointsEnd - self->mpPoints) == 1) {
        i0 = 0;
        i1 = 0;
    }
    else {
        i0 = index - self->mBase;
        i1 = i0 + 1;
    }
    float pts[6];
    pts[0] = self->mpPoints[i0].x;
    pts[1] = self->mpPoints[i0].y;
    pts[2] = self->mpPoints[i0].z;
    pts[3] = self->mpPoints[i1].x;
    pts[4] = self->mpPoints[i1].y;
    pts[5] = self->mpPoints[i1].z;
    ((IWorldVtbl*)((LODComponent*)h)->mpRenderer)->v1c((void*)0x101, pts, 6);
}

// @ 0x00a70730
ParamElem* CopyRange(ParamElem* first, ParamElem* last, ParamElem* dest)
{
    if (first != last) {
        do {
            int* buf = first->vec.mpBegin;
            if (buf != 0 && *(buf - 1) != 0)
                operator_delete__(buf);
            IParamRef* r = first->mp38;
            if (r != 0)
                r->ReleaseI();
            ++first;
            ++dest;
        } while (first != last);
    }
    return dest;
}

// @ 0x00a70780
cEffectsWorld::cEffectsWorld(unsigned flags, const void* params)
{
    mInitialized = false;
    m10 = 0;
    mManager = (void*)flags;
    void* mem = EAAllocate(0x120, "Swarm", 0, 0, 0, 0);
    mGlobalParams = mem != 0 ? (void*)CreateGlobalParams(mem, params) : 0;
    mpRenderer = 0;
    m20 = 0;
    mUpdating = false;
    m2c = 0;
    mState = 1;
    mVE.mpBegin = 0;
    mVE.mpEnd = 0;
    mVE.mpCap = 0;
    mFree.mpBegin = 0;
    mFree.mpEnd = 0;
    mFree.mpCap = 0;
    mActive.mpBegin = 0;
    mActive.mpEnd = 0;
    mActive.mpCap = 0;
    mNew.mpBegin = 0;
    mNew.mpEnd = 0;
    mNew.mpCap = 0;
    m80 = 1;
    m84 = 1;
    m90 = 0;
    m88 = 1.0f;
    mDebugName.mpBegin = (char*)&gEmptyString16;
    mDebugName.mpEnd = (char*)&gEmptyString16;
    mDebugName.mpCap = (char*)&gEmptyString16 + 1;
}

// @ 0x00a70870
cEffectsWorld::~cEffectsWorld()
{
    *(int*)((char*)this + 0) = (int)&gWorldVtblA;
    *(int*)((char*)this + 4) = (int)&gWorldVtblB;
    operator_delete__(mGlobalParams);
    if ((int)(mDebugName.mpCap - mDebugName.mpBegin) > 1 && mDebugName.mpBegin)
        operator_delete__(mDebugName.mpBegin);
    {
        int* p = mNew.mpBegin;
        if (p != 0 && *(p - 1) != 0)
            operator_delete__(p);
    }
    {
        int* p = mActive.mpBegin;
        if (p != 0 && *(p - 1) != 0)
            operator_delete__(p);
    }
    {
        int* p = mFree.mpBegin;
        if (p != 0 && *(p - 1) != 0)
            operator_delete__(p);
    }
    mVE.Dtor();
    if (mpRenderer != 0)
        ((GmeRefCount*)mpRenderer)->Release();
    *(int*)((char*)this + 4) = (int)&gGmeRefCountVtbl;
}

// @ 0x00a70910
Desc58* Desc58::Ctor()
{
    f0 = 0;
    f2 = 0;
    f4 = gDescF4;
    f8 = gDescF8;
    fc = gDescFC;
    f10 = 1.0f;
    m14.Assign(&gDescM33);
    f38 = 0;
    f44 = 0;
    f48 = 0;
    f4c = 0;
    f50 = 0;
    return this;
}

// @ 0x00a70980
void __stdcall DestroyRange(ParamElem* first, ParamElem* last)
{
    for (; first < last; first += 1) {
        int* buf = first->vec.mpBegin;
        if (buf != 0 && *(buf - 1) != 0)
            operator_delete__(buf);
        IParamRef* r = first->mp38;
        if (r != 0)
            r->ReleaseI();
    }
}

// @ 0x00a709e0
bool cEffectsWorld::Teardown()
{
    if (!mInitialized)
        return true;
    v0c(5);
    mInitialized = false;
    cVisualEffect** it = mVE.mpBegin;
    if (it != mVE.mpEnd) {
        do {
            cVisualEffect* ve = *it;
            ve->Release();
            if (ve) {
                *it = 0;
                ve->ReleasePrimary();
            }
            ++it;
        } while (it != mVE.mpEnd);
    }
    mVE.erase(mVE.mpBegin, mVE.mpEnd);
    return true;
}

// @ 0x00a70a40
void cEffectsWorld::DeactivateUnusedVisualEffects()
{
    int* src = mActive.mpBegin;
    int* dst = src;
    m90 = 0;
    mUpdating = true;
    if (src != mActive.mpEnd) {
        do {
            int id = *src;
            if (mVE.mpBegin[id]->CheckIfStopped() && mVE.mpBegin[id]->m10 == 1) {
                mVE.mpBegin[id]->Release();
                mNew.Add(*src);
            }
            else {
                m90 = m90 + 1;
                *dst = *src;
                ++dst;
            }
            ++src;
        } while (src != mActive.mpEnd);
    }
    mActive.EraseAdd(dst, mActive.mpEnd);
    mUpdating = false;
}

// @ 0x00a70af0
void cEffectsWorld::DeactivateAll()
{
    cVisualEffect** it = mVE.mpBegin;
    if (it != mVE.mpEnd) {
        do {
            cVisualEffect* ve = *it;
            ve->Stop(1);
            ve->Release();
            if (ve) {
                *it = 0;
                ve->ReleasePrimary();
            }
            ++it;
        } while (it != mVE.mpEnd);
    }
    mActive.EraseAdd(mActive.mpBegin, mActive.mpEnd);
    mNew.EraseAdd(mNew.mpBegin, mNew.mpEnd);
    mVE.erase(mVE.mpBegin, mVE.mpEnd);
    mFree.EraseAdd(mFree.mpBegin, mFree.mpEnd);
}

// @ 0x00a70bb0
cVisualEffect* cEffectsWorld::NewVisualEffect()
{
    if (mNew.mpBegin != mNew.mpEnd) {
        mFree.Add(*(mNew.mpEnd - 1));
        --mNew.mpEnd;
        return mVE.mpBegin[*(mFree.mpEnd - 1)];
    }
    cVisualEffect* ve = 0;
    void* mem = EAAllocate(0x188, "Swarm/VisualEffect", 0, 0, 0, 0);
    if (mem != 0)
        ve = ((cVisualEffect*)mem)->Ctor();
    mFree.Add((int)(mVE.mpEnd - mVE.mpBegin));
    if (ve)
        ve->AddRef();
    mVE.Add(ve);
    if (ve)
        ve->ReleasePrimary();
    return ve;
}

// @ 0x00a70da0
void cEffectsWorld::SetRenderer(void* renderer)
{
    if (mpRenderer != 0)
        DeactivateAll();
    void* old = mpRenderer;
    if ((cVisualEffect*)renderer != (cVisualEffect*)old) {
        if (renderer != 0)
            ((GmeRefCount*)renderer)->AddRef();
        mpRenderer = renderer;
        if (old != 0)
            ((GmeRefCount*)old)->Release();
    }
}

// @ 0x00a70ec0
void* cEffectsWorld::CreateInternalEffect(unsigned a, unsigned b, const void* params)
{
    int index = ((cEffectsManagerRef*)mManager)->GetEffectIndex(a, b);
    if (index < 0)
        return 0;
    cVisualEffect* ve = NewVisualEffect();
    ve->Init(this, mManager, 0);
    ve->mFlags |= 0x40;
    if (params != 0) {
        EffectParams* mem = (EffectParams*)EAAllocate(0xd8, "Swarm/EffectParams", 0, 0, 0, 0);
        EffectParams* copy = 0;
        if (mem != 0)
            copy = mem->Clone((const EffectParams*)params);
        *(EffectParams**)((char*)ve + 0x17c) = copy;
    }
    ve->m20 = index;
    {
        int idx = index;
        char* desc = *(char**)(*(char**)((char*)mManager + 0x2c) + ((idx >> 24) * 4));
        ve->SetDescription(*(char**)(desc + 0x34) + (idx & 0xffffff) * 0x58);
    }
    return ve;
}

// @ 0x00a70f70
cSPTransform_s00a7_0f70* cSPTransform_s00a7_0f70::CopyFrom(const cSPTransform_s00a7_0f70* src)
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

// @ 0x00a70fd0
void EA::Swarm::cEffectsWorld_s00a7_0f70::CreateComponentFromDescription(int* desc, EffectSlot* slot, IComponent** out, int arg5, unsigned int name)
{
    const int type = desc[0];
    const int page = (int)name >> 24;
    if (type == 0) {
        cVisualEffect_s00a7_0f70* const effect = NewVisualEffect();
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

// @ 0x00a711c0
void EA::Swarm::cEffectsWorld_s00a7_0f70::AppendPendingToActive(int tag)
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

// @ 0x00a71260
cSPTransform_s00a7_0f70* CopyTransformRange(cSPTransform_s00a7_0f70* first, cSPTransform_s00a7_0f70* last, cSPTransform_s00a7_0f70* dst)
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

// @ 0x00a712e0
cSPTransform_s00a7_0f70* CopyTransformBackward(cSPTransform_s00a7_0f70* first, cSPTransform_s00a7_0f70* last, cSPTransform_s00a7_0f70* dstEnd)
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

// @ 0x00a71360
bool EA::Swarm::cEffectsWorld_s00a7_0f70::CreateEffectForDescription(int type, void* name, cVisualEffect_s00a7_0f70** out)
{
    if (out == 0 || mField20 == 5)
        return false;
    const int resolved = mpParams->ResolveName(type, (int)name);
    if (resolved < 0)
        return false;
    cVisualEffect_s00a7_0f70* const effect = NewVisualEffect();
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

// @ 0x00a71410
EA::Swarm::cVisualEffect_s00a7_0f70* EA::Swarm::cEffectsWorld_s00a7_0f70::CreateInternalEffect(unsigned int name, int page, void* params)
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

    cVisualEffect_s00a7_0f70* const effect = NewVisualEffect();
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

// @ 0x00a714f0
void* EA::Swarm::cEffectsWorld_s00a7_0f70::ResolveEffect(int type, int name, int page, void* params)
{
    if (type == 0) {
        cVisualEffect_s00a7_0f70* const effect = CreateInternalEffect((unsigned int)name, page, params);
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

// @ 0x00a71580
void EA::Swarm::cEffectsWorld_s00a7_0f70::GetActiveEffectInfo(EffectInfoVector* out, const char* filter, int level)
{
    EastlString name;
    name.Init();

    const unsigned int count = (unsigned int)(mActive.mpEnd - mActive.mpBegin);
    for (unsigned int i = 0; i < count; ++i) {
        cVisualEffect_s00a7_0f70* const effect = mpEffects[mActive.mpBegin[i]];
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

        cVisualEffect_s00a7_0f70* const old = info.mpEffect;
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

// @ 0x00a717d0
void TransformVector::Insert(cSPTransform_s00a7_0f70* pos, const cSPTransform_s00a7_0f70* value)
{
    if (mpEnd != mpCapacity) {
        if ((unsigned int)pos <= (unsigned int)value && (unsigned int)value < (unsigned int)mpEnd)
            value = (const cSPTransform_s00a7_0f70*)((const char*)value + 0x5c);
        if (mpEnd)
            FUN_00a70cc0(mpEnd - 1);
        CopyTransformBackward(pos, mpEnd - 1, mpEnd);
        pos->CopyFrom(value);
        mpEnd = (cSPTransform_s00a7_0f70*)((char*)mpEnd + 0x5c);
        return;
    }

    int n = (int)((char*)mpEnd - (char*)mpBegin) / 0x5c;
    cSPTransform_s00a7_0f70* mem;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
        if (n == 0) {
            mem = 0;
            goto have_memory;
        }
    }
    mem = (cSPTransform_s00a7_0f70*)::operator new(n * 0x5c, "EASTL", 0, 0,
                                        "EASTL/allocator.h", 0xd1);
have_memory:
    cSPTransform_s00a7_0f70* const oldBegin = mpBegin;
    cSPTransform_s00a7_0f70* const first = (cSPTransform_s00a7_0f70*)FUN_00a70d60(oldBegin, pos, mem);
    FUN_00a70730(oldBegin, pos, mem);
    if (first)
        FUN_00a70cc0((cSPTransform_s00a7_0f70*)value);
    cSPTransform_s00a7_0f70* const oldEnd = mpEnd;
    cSPTransform_s00a7_0f70* const newEnd = (cSPTransform_s00a7_0f70*)FUN_00a70d60(pos, oldEnd, (char*)first + 0x5c);
    FUN_00a70730(pos, oldEnd, (char*)first + 0x5c);
    if (oldBegin && *(int*)((char*)oldBegin - 4) != 0)
        ::operator delete(oldBegin);
    mpBegin = mem;
    mpEnd = newEnd;
    mpCapacity = (cSPTransform_s00a7_0f70*)((char*)mem + n * 0x5c);
}

// @ 0x00a71910
void EA::Swarm::cEffectsWorld_s00a7_0f70::ReleaseEffectInfo(cVisualEffect_s00a7_0f70* effect)
{
    TransformVector* const vec = &effect->mTransforms;
    int count = (int)((char*)vec->mpEnd - (char*)vec->mpBegin) / 0x5c;
    if (count != 0) {
        char* offset = (char*)vec->mpBegin;
        do {
            cSPTransform_s00a7_0f70* const t = (cSPTransform_s00a7_0f70*)offset;
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
    cSPTransform_s00a7_0f70* const begin = vec->mpBegin;
    cSPTransform_s00a7_0f70* const end = vec->mpEnd;
    cSPTransform_s00a7_0f70* const dst = CopyTransformRange(end, end, begin);
    vec->DestroyRange(dst, end);
    const int bytes = (int)((char*)end - (char*)begin);
    vec->mpEnd = (cSPTransform_s00a7_0f70*)((char*)vec->mpEnd + bytes / -0x5c * 0x5c);
}

// @ 0x00a719c0
void EA::Swarm::cEffectsWorld_s00a7_0f70::SelectEffects(int type)
{
    int* it = mActive.mpBegin;
    if (it == mActive.mpEnd)
        return;
    do {
        cVisualEffect_s00a7_0f70* const effect = mpEffects[*it];
        if (type < 0 || type == (signed char)effect->mIDBytes[3])
            ReleaseEffectInfo(effect);
        ++it;
    } while (it != mActive.mpEnd);
}

// @ 0x00a71a00
void cEffectsWorld_s00a7_1a00::UpdateVisualEffect(cVisualEffect_s00a7_1a00* effect, int lod, int flag)
{
    char* eff = (char*)effect;
    unsigned int handle = *(unsigned int*)(eff + 0x20);
    if ((int)handle >= 0) {
        // ---- pass 1: prune the live-component vector ----
        if (*(int*)(eff + 0x144) != *(int*)(eff + 0x148)) {
            cVECompRec** recBegin = (cVECompRec**)(eff + 0x144);
            cVEDescription* desc = (cVEDescription*)((handle & 0xffffff) * 0x58 +
                *(int*)((char*)mManager->mTables[(int)handle >> 0x18] + 0x34));
            unsigned int count = (*(int*)(eff + 0x148) - *(int*)(eff + 0x144)) / 0x5c;
            unsigned int kept = 0;
            unsigned int i = 0;
            unsigned int recOff = 0;
            unsigned int keepOff = 0;
            if (count != 0) {
                do {
                    cVECompRec* rec = (cVECompRec*)((char*)*recBegin + recOff);
                    cVECompDef* def = (cVECompDef*)(rec->mDefIndex * 0x84 + (char*)desc->mpCompDefs);
                    if (lod < (int)def->mLODMin || (int)def->mLODMax <= lod ||
                        (mManager->m68 & (int)def->mMaskB) != (int)def->mMaskA ||
                        ((rec->mFlags >> 7) & 1) != 0) {
                        int v = mManager->m4c;
                        unsigned int df = desc->mFlags;
                        if (((df >> 5) & 1) || ((df >> 0x14) & 1))
                            v = 1;
                        else if ((df >> 0x15) & 1)
                            v = 0;
                        (*(void(__thiscall**)(void*, int))(*(int*)rec->mComponent + 0xc))(rec->mComponent, v);
                        if (v == 0) {
                            char r = (*(char(__thiscall**)(void*))(*(int*)rec->mComponent + 0x10))(rec->mComponent);
                            if (r != 0) {
                                if (((rec->mFlags >> 7) & 1) == 0) {
                                    rec->mFlags |= 0x80;
                                    if (0.5f <= *(float*)(eff + 0x4c))
                                        rec->mFlags |= 0x100;
                                    else
                                        rec->mFlags &= ~0x100u;
                                }
                                goto keep1;
                            }
                        }
                        (*(void(__thiscall**)(void*))(*(int*)rec->mComponent + 4))(rec->mComponent);
                        if (rec->mComponent != 0) {
                            void* comp = rec->mComponent;
                            rec->mComponent = 0;
                            (*(void(__thiscall**)(void*))(*(int*)comp + 0x38))(comp);
                        }
                        goto next1;
                    }
                    if (lod != *(int*)(eff + 0x48))
                        UpdateComponentLODs(def, rec, lod);
                keep1:
                    if (i != kept)
                        FUN_00a70f70((char*)*recBegin + keepOff, rec);
                    ++kept;
                    keepOff += 0x5c;
                next1:
                    recOff += 0x5c;
                    ++i;
                } while (i < count);
            }
            // erase the dropped tail of the vector
            {
                int end = *(int*)(eff + 0x148);
                int newEnd = (int)kept * 0x5c + (int)*recBegin;
                void* res = FUN_00a71260((void*)end, (void*)end, (void*)newEnd);
                FUN_00a70980(res, (void*)end);
                *(int*)(eff + 0x148) = end + ((end - newEnd) / 0x5c) * 0x5c;
            }
        }

        // ---- pass 2: instantiate the components the new LOD needs ----
        {
            unsigned int h2 = *(unsigned int*)(eff + 0x20);
            cVEDescription* desc2 = (cVEDescription*)((h2 & 0xffffff) * 0x58 +
                *(int*)((char*)mManager->mTables[(int)h2 >> 0x18] + 0x34));
            unsigned int defCount = (*(int*)((char*)desc2 + 0x48) - *(int*)((char*)desc2 + 0x44)) / 0x84;
            unsigned int prevThresh = 0;
            unsigned int probAcc = 0;
            unsigned int randThresh = 0;
            unsigned char alreadyCreated = 0;
            unsigned char anyCreated = 0;
            unsigned int idx = 0;
            if (defCount != 0) {
                do {
                    cVECompDef* def = (cVECompDef*)(idx * 0x84 + *(int*)((char*)desc2 + 0x44));
                    bool lodOk = !(lod < (int)def->mLODMin || (int)def->mLODMax <= lod ||
                                   (mManager->m68 & (int)def->mMaskB) != (int)def->mMaskA);
                    bool curOk = !(*(int*)(eff + 0x48) < (int)def->mLODMin ||
                                   (int)def->mLODMax <= *(int*)(eff + 0x48) ||
                                   (mFlags & def->mMaskB) != def->mMaskA);
                    if (def->m80 >= 0 && !curOk && lodOk) {
                        if (def->mProbThreshold != 0) {
                            if (def->mProbThreshold != prevThresh) {
                                randThresh = RandomUint32Uniform(&g_sRandom, 0x10000);
                                probAcc = 0;
                            }
                            probAcc += def->mProbStep;
                            prevThresh = def->mProbThreshold;
                            if (probAcc < randThresh)
                                goto nextDef;
                            randThresh = 0x10000;
                        } else {
                            prevThresh = def->mProbThreshold;
                        }
                        bool bit3 = ((def->mFlags >> 3) & 1) != 0;
                        anyCreated = 1;
                        if (alreadyCreated == 0) {
                            cVECreateOut out;
                            FUN_00a70910(&out.mXform);
                            CreateComponentFromDescription(def, &out.mXform, &out.mOut,
                                *(int*)(eff + 0x17c), (int)h2);
                            void* component = out.mComponent;
                            if (component != 0) {
                                UpdateComponentLODs(def, &out.mXform, lod);
                                cSPTransformOps_Assign(&out.mXform, (char*)def + 8);
                                float blend = def->mBlend;
                                (void)blend;
                                cSPTransform_s00a7_1a00 tr;
                                void* p = FUN_007d5590(&tr, (char*)def + 8, eff + 0x10c, eff + 0xd4);
                                (*(void(__thiscall**)(void*, void*))(*(int*)component + 0x18))(component, p);
                                if ((mFlags >> 1) & 1)
                                    (*(void(__thiscall**)(void*, int))(*(int*)component + 0x28))(component, 0);
                                if (((mFlags >> 9) & 1) && !((mFlags >> 0xa) & 1)) {
                                    (*(void(__thiscall**)(void*, int))(*(int*)component + 8))(component, flag);
                                    if (flag == 1)
                                        mFlags |= 0x100;
                                }
                                if (*(int*)(eff + 0x148) < *(int*)(eff + 0x14c)) {
                                    void* slot = (void*)*(int*)(eff + 0x148);
                                    *(int*)(eff + 0x148) = (int)slot + 0x5c;
                                    if (slot != 0)
                                        FUN_00a70cc0(&out.mXform);
                                } else {
                                    FUN_00a717d0((void*)*(int*)(eff + 0x144),
                                        (void*)*(int*)(eff + 0x148), &out.mXform);
                                }
                            }
                            if (out.mBuffer != 0 && *(int*)((char*)out.mBuffer - 4) != 0)
                                operator_delete__(out.mBuffer);
                            if (out.mComponent != 0)
                                (*(void(__thiscall**)(void*))(*(int*)out.mComponent + 0x38))(out.mComponent);
                        }
                        if (bit3) {
                            char* v = (char*)*(int*)(eff + 0x148) - 0x14;
                            unsigned int* e = *(unsigned int**)(v + 4);
                            if (e < *(unsigned int**)(v + 8)) {
                                *(unsigned int**)(v + 4) = e + 1;
                                if (e != 0)
                                    *e = idx;
                            } else {
                                DoInsertValue_SI(v, e, &idx);
                            }
                            alreadyCreated = ((def->mFlags >> 4) & 1) == 0;
                        }
                    }
                nextDef:
                    ++idx;
                } while (idx < defCount);
                if (anyCreated)
                    FUN_00a828a0();
            }
        }
    }
    *(int*)(eff + 0x48) = lod;
}

// @ 0x00a71f90
void cEffectsWorld_s00a7_1a00::ResetVisualEffectDescription(cVisualEffect_s00a7_1a00* effect)
{
    int a = effect->m18;
    int b = effect->m1c;
    effect->m20 = -1;
    if ((a & b) != -1)
        effect->m20 = mManager->ResolveEffectName(a, b);

    if (effect->m20 >= 0) {
        int handle = effect->m20;
        void** tables = mManager->mTables;
        effect->UpdateDescription((void*)((handle & 0xffffff) * 0x58 +
            *(int*)((char*)tables[handle >> 0x18] + 0x34)));
    } else {
        effect->m28 = 0;
    }

    int old = effect->m48;
    effect->m48 = 0;
    UpdateVisualEffect(effect, old, 1);
}

// @ 0x00a72010
void cEffectsWorld_s00a7_1a00::ResetVisualEffectDescriptions(int type)
{
    int* p = mActive;
    if (p != mActiveEnd) {
        do {
            cVisualEffect_s00a7_1a00* effect = mVE[*p];
            if (type < 0 || type == effect->mComponentType)
                ResetVisualEffectDescription(effect);
            ++p;
        } while (p != mActiveEnd);
    }
    FUN_00a711c0(1);
}

// @ 0x00a72060
void cEffectsWorld_s00a7_1a00::FUN_00a72060(int type)
{
    int* p = mActive;
    if (p != mActiveEnd) {
        do {
            cVisualEffect_s00a7_1a00* effect = mVE[*p];
            if (type < 0 || type == effect->mComponentType) {
                FUN_00a71910(effect);
                ResetVisualEffectDescription(effect);
            }
            ++p;
        } while (p != mActiveEnd);
    }
    FUN_00a711c0(1);
}

// @ 0x00a720b0
void cEffectsWorld_s00a7_1a00::SetState(int state)
{
    if (state == mState)
        return;
    if (state == 5) {
        DeactivateAll();
        mState = 5;
        return;
    }

    if (state == 2) {
        for (int* p = mActive; p != mActiveEnd; ++p)
            FUN_00a71910(mVE[*p]);
    } else {
        if (mState == 2)
            ResetVisualEffectDescriptions(-1);
    }
    if (state == 3 || mState == 3) {
        bool bVar3 = (state == 3);
        if (bVar3)
            DeactivateUnusedVisualEffects();
        for (cVisualEffect_s00a7_1a00** v = mVE; v != mVEend; ++v) {
            (*(void(__thiscall**)(cVisualEffect_s00a7_1a00*, int))(*(int*)*v + 0x30))(*v, bVar3);
            (*(void(__thiscall**)(cVisualEffect_s00a7_1a00*, int))(*(int*)*v + 0x2c))(*v, bVar3);
        }
    }
    if (state == 1 || mState == 1) {
        bool b = (state == 1);
        for (cVisualEffect_s00a7_1a00** v = mVE; v != mVEend; ++v)
            (*(void(__thiscall**)(cVisualEffect_s00a7_1a00*, int))(*(int*)*v + 0x2c))(*v, b);
    }
    mState = state;
}

// @ 0x01308d20
void init_1676bfc()
{
    *(int*)0x1676bfc = (int)0xffffff00;
    *(int*)0x1676c00 = (int)0xffff00ff;
    *(int*)0x1676c04 = (int)0xff0000ff;
    *(int*)0x1676c08 = (int)0xff000000;
}
