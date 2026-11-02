// src/game/SPBake/_at_004c0000.cpp -- migrated from slice(s) s004cd1b0, s004cb340, s004ca6e0, s004ca430, s004c6df0, s004c6190, s004c5200, s004c4650, s004c38e0 by tools/migrate/rewrite.py
// Object file: SPBake/_at_004c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorSkinPart.h"
#include "SP/cRuntimeCreatureResource.h"
#include "SP/cSkinObject.h"
#include <intrin.h>
#include "rw/graphics/EmbeddedState.h"
#include "SP/cDirectPropertyList.h"

// unnamed retail callees and globals (address in the comment)
extern "C" const char kEditorAllocName[];   // 0x013eb430 ?kEditorAllocName@@3QBDB
#pragma pack(push, 4)

// ---- items of slice s004c38e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(unsigned int size, const char* name, int, int, int, int);
extern "C" const char kEditorAllocName[];   // 0x013eb430 ?kEditorAllocName@@3QBDB
namespace eastl {
template <int N> class bitset {
public:
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWordValue(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWordValue(i) & (1 << (i % 32))) != 0;
        return false;
    }
};  // namespace eastl
}
namespace SP {
class cSPEditorBlock_s004c_38e0;
}
namespace SP {
class cSPEditorModel_s004c_38e0;
}
namespace SP {
class cSPEditorSkinPart_s004c_38e0;
}
namespace SP {
class cIModelWorld_s004c_38e0;
}
namespace SP {
class cPaintRequest;
}
namespace SP {
struct SkinElem;
}
namespace SP {
struct SkinModel;
}
namespace SP {
bool CollectPartsRec(cSPEditorBlock_s004c_38e0* block, void* parts);        // 0x0048ccf0
}
namespace SP {
void FUN_00425990();                                             // free (vector teardown)
}
namespace SP {
class SimpleVec {
public:
    void push_back(const uint32_t& v);                           // 0x00454860
    ~SimpleVec() { for (uint32_t* p = mpBegin; p < mpEnd; ++p) {} FUN_00425990(); }
    void FUN_00425990();                                         // 0x00425990
    uint32_t* mpBegin;                                           // +0x00
    uint32_t* mpEnd;                                             // +0x04
    uint32_t* mpCapacity;                                        // +0x08
};
}
namespace SP {
struct SkinElem {
    uint32_t mPad0;                                              // +0x00
    uint16_t mType;                                              // +0x04 (0x210 = texture slot)
    uint16_t mPad6;                                              // +0x06
    void*    mData;                                              // +0x08
};
}
namespace SP {
struct SkinElemVector {
    SkinElem** mpBegin;                                          // +0x00
    SkinElem** mpEnd;                                            // +0x04
    SkinElem** mpCapacity;                                       // +0x08
    bool empty();                                                // 0x00526430
};
}
namespace SP {
struct SkinModel {
    uint32_t mPad0;                                              // +0x00
    uint32_t mPad4;                                              // +0x04
    SkinElemVector mElems;                                       // +0x08
};
}
namespace SP {
struct SkinResource {
    uint32_t mPad0[6];                                           // +0x00
    uint32_t mModelType;                                         // +0x18
};
}
namespace SP {
class cPaintRequest {
public:
    uint8_t mPad0[0x70];
    float   mA;                                                  // +0x70
    float   mB;                                                  // +0x74
    float   mC;                                                  // +0x78
};
}
namespace SP {
class cSPEditorSkinPart_s004c_38e0 {
public:
    cSPEditorSkinPart_s004c_38e0();                                         // 0x004cc190
    // The second (dynamic-draw) vtable lives at +0xbc; ref-counting goes through it.
    struct DrawBase {
        virtual int AddRef();
        virtual int Release();
    };

    void SetDrawMaterial(uint32_t id);                           // 0x004cd020
    void SetModel(uint32_t instance, uint32_t group, bool allowHighQuality); // 0x004cc470
    void SetSkinResolution(float realtime, float highQuality);   // 0x004cd060
    void Update(uint32_t* blocks, bool forceHighQuality);        // 0x004cc540
    void UpdateSceneObject(cIModelWorld_s004c_38e0* world);                 // 0x004cc7d0
    bool IsHighQualityPending();                                 // 0x004cc760
    void RestartQualityTimer();                                  // 0x004cc6f0
    void SetVisible(bool visible);                               // 0x004cca40
    void* GetSceneObject() { return mModel; }
    void AddDrawRef() { mDraw.AddRef(); }
    void DrawRelease() { mDraw.Release(); }

    uint8_t mPad0[8];
    SkinResource* mResource;                                     // +0x08
    uint8_t mPad1[0xb8 - 0x0c];
    SkinModel* mSkinModel;                                       // +0xb8
    DrawBase mDraw;                                              // +0xbc (vptr)
    uint8_t mPadDraw[0xe0 - 0xc0];
    void* mModel;                                                // +0xe0
    void* mMatBegin;                                             // +0xe4
    void* mMatEnd;                                               // +0xe8
    void* mMatCapacity;                                          // +0xec
    uint8_t mPadEnd[0x130 - 0xf0];
};
}
namespace SP {
template <class T> class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* const& p) : mpObject(p) { if (mpObject) mpObject->AddDrawRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) {
        if (mpObject) mpObject->AddDrawRef();
    }
    ~AutoRefCount() { if (mpObject) mpObject->DrawRelease(); }
    AutoRefCount& operator=(T* const& p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddDrawRef();
            mpObject = p;
            if (old) old->DrawRelease();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    T* mpObject;
};
}
namespace SP {
struct PaintRequestSlot {
    cPaintRequest* mpObject;
    cPaintRequest* operator->() const { return mpObject; }
};
}
namespace SP {
struct LimbPair {
    cSPEditorBlock_s004c_38e0* first;                                       // +0x00
    AutoRefCount<cSPEditorSkinPart_s004c_38e0> second;                      // +0x04
};
}
namespace SP {
struct LimbVector {
    LimbPair* mpBegin;                                           // +0x00
    LimbPair* mpEnd;                                             // +0x04
    LimbPair* mpCapacity;                                        // +0x08
    uint32_t  mAllocName;                                        // +0x0c
    uint32_t  mAllocFlags;                                       // +0x10
    void push_back(const LimbPair& v);                           // 0x004c5fc0
    int size() const { return (int)(mpEnd - mpBegin); }
    LimbPair& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
class cSPEditorBlock_s004c_38e0 {
public:
    bool Paint();                                                // 0x0044c030
    bool HasAnyBlockFlag();                                      // 0x00435d40
    void SetFlag(int flag, bool value);                          // 0x00435a10
    uint8_t mPad0[0x33c];
    void*   mField33c;                                           // +0x33c
    uint8_t mPad1[0xdc8 - 0x340];
    eastl::bitset<60> mFlags;                                    // +0xdc8
};
}
namespace SP {
class cSPEditorModel_s004c_38e0 {
public:
    uint32_t GetBlockCount() const;                              // 0x004accf0
    uint8_t mPad0[0x18];
    cSPEditorBlock_s004c_38e0** mpBlockList;                                // +0x18
    uint8_t mPad1[0x50 - 0x1c];
    bool mFlag50;                                                // +0x50
    uint8_t mPad2[0x58 - 0x51];
    uint32_t mName58;                                            // +0x58
};
}
namespace SP {
class cSPEditorSkinManager_s004c_38e0 {
public:
    void UpdateTorso(uint32_t flags, int value);                 // 0x004c3230
    void Update(uint32_t unused, bool paintAll, uint32_t p4, uint32_t p5); // 0x004c38e0
    void UpdatePaintedSkin();                                    // 0x004c4290
    cSPEditorSkinPart_s004c_38e0* CreateSkinObject(cSPEditorBlock_s004c_38e0* block, uint32_t instance); // 0x004c44c0
    void* GetSceneObject(uint32_t which);                        // 0x004c45d0

    uint8_t mPad0[0x10];
    cSPEditorModel_s004c_38e0* mModel;                                      // +0x10
    cIModelWorld_s004c_38e0*   mSceneObjectModelWorld;                      // +0x14
    AutoRefCount<cSPEditorSkinPart_s004c_38e0> mTorsoSkin;                  // +0x18
    AutoRefCount<cSPEditorSkinPart_s004c_38e0> mCompleteSkin;               // +0x1c
    uint8_t mPad20[0x48 - 0x20];                                 // +0x20 transforms/pointers
    LimbVector mLimbSkins;                                       // +0x48
    PaintRequestSlot mPaintRequest;                              // +0x5c
    uint32_t mDefaultMaterial;                                   // +0x60
    uint8_t  mTextureKey[0x70 - 0x64];                           // +0x64
    void*    mDiffuseTex;                                        // +0x70
    void*    mNormalTex;                                         // +0x74
    float    mPaintResolution;                                   // +0x78
    float    mRealtimeResolution;                                // +0x7c
    float    mHighQualityResolution;                             // +0x80
    bool     mPaintEnabled;                                      // +0x84
    bool     mHairEnabled;                                       // +0x85
};
}
// ---- items of slice s004c38e0 end

// ---- items of slice s004c4650 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    cSPVector3& operator=(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
}
namespace SP {
class cSPEditorBlock_s004c_4650;
}
namespace SP {
template <class T> class AutoRefCount_s004c_4650 {
public:
    AutoRefCount_s004c_4650() : mpObject(0) {}
    AutoRefCount_s004c_4650(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s004c_4650(const AutoRefCount_s004c_4650& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004c_4650() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s004c_4650& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount_s004c_4650& operator=(const AutoRefCount_s004c_4650& o) { return operator=(o.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* get() const { return mpObject; }
    T* mpObject;
};
}
namespace SP {
struct RefVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void ctorRef(void* p);                              // 0x429360
    void eraseRange(void* first, void* last);           // 0x426280
    void resize(int n);                                 // 0x41ee90
    void dtorRef();                                     // 0x41eb80
    bool emptyRef() const;                              // 0x526430
};
}
namespace SP {
struct DeformRecord {
    char pad[0x8c];
};
}
namespace SP {
class cRuntimeCreatureResource_s004c_4650 {
public:
    char pad0[0x98];
    DeformRecord* mDeformBegin;     // +0x98
    DeformRecord* mDeformEnd;       // +0x9c
};
}
namespace SP {
class cSkinObject_s004c_4650 {
public:
    char pad0[8];
    AutoRefCount_s004c_4650<cRuntimeCreatureResource_s004c_4650> mResource;   // +0x8
};
}
namespace SP {
class cSPEditorSkinPart_s004c_4650 : public cSkinObject_s004c_4650 {
public:
    char pad9c[0xa4 - 0xc];
    RefVec mOrderedBlocks;        // +0xa4 (erase/resize through RefVec)
    char padac[0xc0 - 0xb0];
    void** mBlockMatInfosBegin;   // +0xc0
    void** mBlockMatInfosEnd;     // +0xc4
    char padc8[0xd0 - 0xc8];
    uint32_t mDrawMaterial;       // +0xd0
    uint32_t mInstance;           // +0xd4
    char padd8[0xfc - 0xd8];
    void* mDiffuseTex;            // +0xfc
    void* mNormalTex;             // +0x100
    char pad104[0x120 - 0x104];
    float mSkinResolutionRealtime;    // +0x120
    float mSkinResolutionHighQuality; // +0x124
    float mSkinResolution;            // +0x128

    void AddRef() { _InterlockedIncrement((long*)((char*)this + 4)); }
    void Release() { if (_InterlockedDecrement((long*)((char*)this + 4)) == 0) Destroy(); }
    void Destroy();

    bool BuildSkeleton();                              // 0x4ca6e0
    void RebuildSkinA();                               // 0x4cb340
    void RebuildSkinB();                               // 0x4cb820
    void Shutdown();                                   // 0x4cced0
    cSPEditorBlock_s004c_4650* GetBlockOnSkin(cSPVector3 pos);    // 0x4ccb70
    void SetDefaultMaterial(uint32_t id);              // 0x4cd020
    void SetSkinResolutions(float realtime, float highQuality);  // 0x4cd060
    bool PickSkinPart(cSPVector3 lod, cSPVector3 dir, cSPVector3* outPos,
                      cSPVector3* outNormal, float* outDist, char flag);  // 0x4ccae0
};
}
namespace SP {
class cSPEditorSkinManager_s004c_4650 {
public:
    char pad0[0x10];
    void* mModel;                        // +0x10
    void* mSceneObjectModelWorld;        // +0x14
    AutoRefCount_s004c_4650<cSPEditorSkinPart_s004c_4650> mTorsoSkin;    // +0x18
    AutoRefCount_s004c_4650<cSPEditorSkinPart_s004c_4650> mCompleteSkin; // +0x1c
    char pad20[0x48 - 0x20];
    struct BlockPart { void* block; AutoRefCount_s004c_4650<cSPEditorSkinPart_s004c_4650> part; };
    struct BlockVec {
        BlockPart* mpBegin;              // +0x48
        BlockPart* mpEnd;                // +0x4c
        int Size() { return (int)(mpEnd - mpBegin); }
        bool Empty() { return mpEnd == mpBegin; }
        BlockPart& Back() { return mpEnd[-1]; }
        void PopBack();                  // 0x4c6070
    };
    BlockVec mBlockTransforms;           // +0x48
    char pad50[0x5c - 0x50];
    AutoRefCount_s004c_4650<struct cPaintRequest_s004c_4650> mPaintRequest;   // +0x5c
    uint32_t mDefaultMaterial;           // +0x60
    char pad64[0x78 - 0x64];
    float mPaintResolution;              // +0x78
    float mRealtimeResolution;           // +0x7c
    float mHighQualityResolution;        // +0x80
    uint8_t mPaintEnabled;               // +0x84

    bool CheckPaint() const;             // 0x4c58b0
    void* GetSkin(uint32_t which);
    void Update(uint32_t p2, char p3, uint32_t p4, uint32_t p5);   // 0x4c38e0
    void EnablePaint(char enable);                                 // 0x4c4650
    bool PickSkin(uint32_t which, cSPVector3 lod, cSPVector3 dir,
                  cSPVector3* outPos, cSPVector3* outNormal, float* outDist, char flag);
    cSPEditorBlock_s004c_4650* GetBlockOnSkin(uint32_t which, cSPVector3 pos);
    void DetachSkinParts();                                        // 0x4c4eb0
    void SetDefaultMaterial(uint32_t id);
    void SetDefaultMaterialToDetachedLimb(uint32_t id, const void* block);
    void SetSkinResolutions(float realtime, float highQuality);
};
}
namespace SP {
class cPaintRequest_s004c_4650 {
public:
    void AddRef() {}
    void Release();                      // 0x453540
};
}
namespace SP {
cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b); // 0x41db10
}
// ---- items of slice s004c4650 end

// ---- items of slice s004c5200 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gPropGroup;                     // @ 0x15d8de8
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
inline void* operator new(unsigned, void* p) { return p; }
struct IRef { virtual void AddRef(); virtual void Release(); };
struct EObj { char pad[0xbc]; IRef ref; };
struct EPtr {
    EObj* p;
    EPtr() {}
    EPtr(const EPtr& o) : p(o.p) { if (p) p->ref.AddRef(); }
    EPtr& operator=(EObj* np) {
        if (np != p) { EObj* old = p; if (np) np->ref.AddRef(); p = np; if (old) old->ref.Release(); }
        return *this;
    }
    ~EPtr() { if (p) p->ref.Release(); }
    void Dtor5d50();
    EPtr& Assign5d80(EObj* np);
    EPtr* Copy6150(EPtr* o);
};
struct Pair { int key; EPtr ptr; };
struct PairVec {
    Pair* mpBegin; Pair* mpEnd; Pair* mpCapacity;
    void Dtor5f40();
    void PushBack5fc0(const Pair& v);
    void PopBack6070();
    void DoInsertValue(Pair* pos, const Pair& v);
    void Base45daf0();
};
struct TexData { int format; int pad4; int pad8; uint16_t w; uint16_t h; };
struct Tex {
    TexData* mpData; uint8_t mFlags; uint8_t mPad[3]; long mnRefCount;
    void Release();                             // AtomicRefCounted::Release @ 0x402420
};
inline void AddRefA(Tex* p) { _InterlockedIncrement(&p->mnRefCount); }
struct ARef {
    Tex* mp;
    ARef() : mp(0) {}
    ~ARef() { if (mp) mp->Release(); }
    ARef& operator=(Tex* p) {
        if (p != mp) { Tex* old = mp; if (p) AddRefA(p); mp = p; if (old) old->Release(); }
        return *this;
    }
    void Reset(Tex* np) { Tex* old = mp; if (np) AddRefA(np); mp = np; if (old) old->Release(); }
    Tex** Addr();                               // @ 0x472b00
    Tex** AddrI() { return Addr(); }
};
struct ARefArg { Tex* mp; ARefArg(const ARef& o) : mp(o.mp) { if (mp) AddRefA(mp); } };
struct TexFlagsB;
struct TexMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void Load(Tex* t);
    virtual void v14();
    virtual Tex* CreateTexture(uint32_t hash, uint32_t flags, uint32_t w, uint32_t h, int a, int b, int c, int d); };
TexMgr* __cdecl GetTexMgr();                    // @ 0x67dd60
struct Str {
    char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAlloc;
    Str() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; Init(); }
    ~Str();                                     // @ 0x530670
    void Init();                                // @ 0x4b5540
    void __cdecl sprintf(const char* fmt, ...); // @ 0x472fe0
};
void __cdecl SaveTga7b2380(const char* name, TexData* data);
bool __cdecl Check7af8b0(ARefArg a, ARefArg b);
inline TexData* DataOf(Tex* t) {
    if (!(t->mFlags & 1)) GetTexMgr()->Load(t);
    return t->mpData;
}
inline uint16_t WidthOf(TexData* d) { return d->w; }
inline uint16_t HeightOf(TexData* d) { return d->h; }
struct TexFlagsB {
    uint32_t fa : 8;
    uint32_t fb : 8;
    uint32_t fc : 8;
    uint32_t fd : 6;
    uint32_t fe : 2;
    TexFlagsB() { *(uint32_t*)this = 0; }
    void SetB(uint32_t v) { fb = v; }
    void SetC(uint32_t v) { fc = v; }
};
__forceinline uint32_t MakeKey() {
    TexFlagsB f;
    f.fe = 1;
    f.SetC(0x62);
    f.SetB(0x21);
    return *(uint32_t*)&f;
}
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags, int a, int b) throw();
struct ThrObj {                                 // Resource::ThreadedObject: atomic count at +4
    void* vt; long mnRefCount;
    void Release();                             // @ 0x404f90
};
struct ThrRef {
    ThrObj* mp;
    ThrRef& operator=(ThrObj* p) {
        if (p != mp) { ThrObj* old = mp; if (p) _InterlockedIncrement(&p->mnRefCount); mp = p; if (old) old->Release(); }
        return *this;
    }
};
struct SkinKey { uint32_t a, b, c; };
struct SkinObj;
struct SkinRef {
    SkinObj* mp;
    SkinRef& operator=(SkinObj* p);
    SkinRef& AssignA(SkinObj* p);               // operator= with the extra frame hole of the failure-path expansion
};
struct Vec3 { float x, y, z; };
struct SkinObj {
    void* vt; int mnRefCount; ThrRef mpThr; SkinKey mKey;
    uint32_t mAbil[3]; uint32_t m24; uint32_t m28[3]; uint32_t pad34; Vec3 mPos[3];
    int m5c; int m60; uint8_t pad64; bool f65, f66, f67, f68, f69, f6a, f6b, f6c; uint8_t pad6d[3]; uint32_t pad70[5];
    SkinObj();                                  // @ 0x51df40
    int AddRef() { return mnRefCount++ + 1; }
    void Release();                             // EA::RefCountTemplate<int>::Release @ 0x453540
};
inline SkinRef& SkinRef::operator=(SkinObj* p) {
    if (p != mp) { SkinObj* old = mp; if (p) p->AddRef(); mp = p; if (old) old->Release(); }
    return *this;
}
inline SkinRef& SkinRef::AssignA(SkinObj* p) {
    if (p != mp) { SkinObj* old = mp; ScratchSlots<3>(); if (p) p->AddRef(); mp = p; if (old) old->Release(); }
    return *this;
}
struct IPropList { virtual void AddRef(); virtual void Release(); };
struct IPropPtr {
    IPropList* mp;
    IPropPtr() : mp(0) {}
    ~IPropPtr() { if (mp) mp->Release(); }
    void Reset() { if (mp) { IPropList* t = mp; mp = 0; t->Release(); } }
    IPropList* Get() { return mp; }
    IPropList** ResetAddr() { Reset(); return &mp; }
};
struct PropMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual bool GetPropList(uint32_t type, uint32_t group, IPropList** out); };
struct SkinMgrA { void RemoveSkin(SkinObj* s); };                 // @ 0x522a40
struct SkinMgrB { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
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
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
    virtual bool Register(SkinObj* s); };
SkinMgrA* __cdecl GetSkinMgrA();                // @ 0x401080
SkinMgrB* __cdecl GetSkinMgrB();                // @ 0x401010
PropMgr* __cdecl GetPropMgr();                  // @ 0x67de30
uint32_t __cdecl RemapTypeId(uint32_t t);       // @ 0x432f10
struct AppProps {
    int GetIntProperty(uint32_t id);            // @ 0x6a2660
    bool GetDescription(uint32_t id);           // @ 0x6a25a0
};
extern AppProps* sAppProperties;                // @ 0x15fd918
inline AppProps* AppProp() { return sAppProperties; }
bool __cdecl GetPropertyAsUint32Array(IPropList* l, uint32_t id, uint32_t* count, uint32_t** arr);   // @ 0x6a0840
void __cdecl Sub4615e0(uint32_t a, uint32_t b, int c, int d, const Vec3& v);
struct SkinDesc {                               // the descriptor passed to the update
    char pad[0x10]; uint32_t mId; char pad2[0x44]; uint32_t mModelType;
    char pad3[0x30]; uint32_t mAbilA[3]; uint32_t mAbilB[3]; Vec3 mPos[3];
    Vec3 GetPos(int i);                         // @ 0x4adca0 (sret)
    uint32_t GetAbilA(int i);                   // @ 0x4adc60
    uint32_t GetAbilB(int i);                   // @ 0x4adc80
    uint32_t ModelType() { return mModelType; }
};
template<class T> inline const T& MaxRef(const T& a, const T& b) { return (a < b) ? b : a; }
struct Ed {
    char pad[0x1c]; ThrObj* m1c; char pad1c[0x3c]; SkinRef mpSkin; char pad60[4]; SkinKey mKey; Tex* m70; Tex* m74; char pad3[0x0c]; uint8_t mActive;
    SkinObj* Skin() { return mpSkin.mp; }
    ThrObj* Thr() { return m1c; }
    Tex* Diffuse() { return m70; }
    Tex* Normal() { return m74; }
    bool Check58b0();
    bool Update5200(SkinDesc* desc);
    void Get5910(Tex** a, Tex** b);
    void Diag5980(const wchar_t* dir, const wchar_t* name);
};
// ---- items of slice s004c5200 end

// ---- items of slice s004c6190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void H_42dee0();   // 0x0042DEE0 EASTL allocate(alloc,size,align,flags)
extern "C" void H_429360();   // 0x00429360 sub-object init (thiscall, 1 stack arg)
extern "C" void H_4c5d80();   // 0x004C5D80 smart-pointer assign (thiscall, 1 stack arg)
extern "C" void H_11e073e();  // 0x011E073E uninitialized_fill_n(first,value,count)
extern "C" void H_11e0744();  // 0x011E0744 vector<bool>::DoInsertValue(dst,first,n)
void  __cdecl operator delete(void*);                       // 0x00F47380
void* __cdecl memmove(void*, const void*, size_t);
typedef void (__thiscall *TC1)(void*, void*);
struct RefObj { virtual void AddRef(); virtual void Release(); };
inline RefObj* RC(void* p) { return (RefObj*)((char*)p + 0xbc); }
struct Elem { int val; void* obj; };
struct Vec8 { Elem* mpBegin; Elem* mpEnd; Elem* mpCap; char alloc[4]; void* mpBuffer; };
// ---- items of slice s004c6190 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
Elem* __cdecl FUN_004c6520(Elem* first, Elem* last, Elem* dst);   // defined at 0x004c6520, called earlier in the TU
Elem* __cdecl FUN_004c69b0(Elem* first, Elem* last, Elem* dst);   // defined at 0x004c69b0, called earlier in the TU
Elem* __cdecl FUN_004c69e0(Elem* first, Elem* last, Elem* dst);   // defined at 0x004c69e0, called earlier in the TU
Elem* __cdecl FUN_004c6a70(Elem* first, Elem* last, Elem* dst);   // defined at 0x004c6a70, called earlier in the TU
int* __cdecl FUN_004c6b30(int* out, void* first, void* last, void* dst);   // defined at 0x004c6b30, called earlier in the TU

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int* __cdecl FUN_004c6ae0(int* out, char* first, int count, char* value);  // 0x004c6ae0 (stays in the slice: not this object's)

// ---- items of slice s004c6df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchange)
struct AllocTag { AllocTag() {} };
struct Cnt {
    volatile long n;
    Cnt() { _InterlockedExchange(&n, 0); }
};
class IRefCounted {
public:
    virtual int AddRef();
    virtual int Release();
};
struct CBlock {                     // 0x8c cRuntimeCreatureBlock
    char pad0[8];
    uint16_t flags;                 // +0x08
    char padA[0x84 - 0x0a];
    uint32_t group;                 // +0x84
    uint32_t instance;              // +0x88
    char pad8c[0x8c - 0x8c];
};
struct BlockArray {
    CBlock* mpBegin;
    CBlock* mpEnd;
    char pad[0xc];
    int size() { return (int)(mpEnd - mpBegin); }
};
struct Res : IRefCounted {
    char pad04[0x98 - 4];
    BlockArray mBlocks;             // +0x98
};
template <class T> struct AutoRef {
    T* mp;
    AutoRef(T* p = 0) : mp(p)
    {
        if (mp)
            mp->AddRef();
    }
    ~AutoRef()
    {
        if (mp)
            mp->Release();
    }
    T* get() const { return mp; }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};
struct PropRef {                    // AutoRefCount<PropertyList>: one pointer
    PropertyList* mp;
    void** AsPPVoidParam();         // 0x0041D870
};
class PropertyManager {
public:
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
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, void* out); // 0x2c
};
PropertyManager* GetPropertyManager();  // 0x0067DE30
struct VecAlloc {
    uint32_t a, b;
    VecAlloc(const AllocTag& tag = AllocTag());   // 0x00429360
};
struct BlockVec {
    PropRef* mpBegin;
    PropRef* mpEnd;
    PropRef* mpCapacity;
    VecAlloc alloc;
    BlockVec(const AllocTag& tag = AllocTag());   // 0x00540470
    ~BlockVec();                                   // 0x004B5440
    void resize(unsigned n);                       // 0x00421BF0
    PropRef& operator[](int i) { return mpBegin[i]; }
};
struct NodeVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    VecAlloc alloc;
    NodeVec(const AllocTag& tag = AllocTag());    // 0x00540470
    ~NodeVec();                                    // 0x0041E5D0
    void resize(unsigned n);                       // 0x004C0410
    uint8_t& operator[](int i) { return mpBegin[i]; }
};
class cTribePlanner {
public:
    void Destroy();                                // 0x00453540
};
struct PlannerPtr {
    cTribePlanner* mp;
    PlannerPtr() : mp(0) {}
    ~PlannerPtr()
    {
        cTribePlanner** self = &mp;
        {
            uint32_t dead[3];      // inline-expansion frame of the retail dtor
        }
        if (*self)
            (*self)->Destroy();
    }
};
struct Vec40 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec40() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec40();                                      // 0x004CD530
};
struct Vec54 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec54() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec54();                                      // 0x004CDDD0
};
struct Vec68 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec68() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec68();                                      // 0x0041E090
};
struct Vec7c {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec7c() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec7c();                                      // 0x00454970
};
struct VecA4 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    VecA4() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VecA4();                                      // 0x0041EB80
};
struct ThreadedObj {
    void Release();                                // 0x00404F90
};
struct ThreadedPtr {
    ThreadedObj* mp;
    ThreadedPtr() : mp(0) {}
    ~ThreadedPtr()
    {
        ThreadedObj** self = &mp;
        {
            uint32_t dead[11];     // inline-expansion frame of the retail dtor
        }
        if (*self)
            (*self)->Release();
    }
};
struct RectF {
    float left, top, right, bottom;
    RectF(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
};
struct RectVec {
    RectF* mpBegin;
    RectF* mpEnd;
    RectF* mpCapacity;
    VecAlloc alloc;
    RectVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~RectVec();                                    // 0x004748C0
    void resize(unsigned n, const RectF& value);   // 0x004CD710
};
struct RefBase {
    void* mVtbl;                      // +0x00
    Cnt cnt;                          // +0x04
    RefBase() : mVtbl((void*)0x13EF094u) {}
    ~RefBase() { mVtbl = (void*)0x13EF094u; }
};
struct SkinVtblBase : RefBase {
    SkinVtblBase() { mVtbl = (void*)0x13F05A8u; }
};
struct SkinObj_s004c_6df0 : SkinVtblBase {
    AutoRef<Res> mResource;           // +0x08
    BlockVec mBlockProps;             // +0x0c
    NodeVec mNodeBlockMap;            // +0x20
    PlannerPtr mPlannerA;             // +0x34
    PlannerPtr mPlannerB;             // +0x38
    float mFloat;                     // +0x3c
    Vec40 mNodes;                     // +0x40
    Vec54 mBones;                     // +0x54
    Vec68 mBoneTransforms;            // +0x68
    Vec7c mVertexWeights;             // +0x7c
    RectVec mTextureSubRects;         // +0x90
    VecA4 mExtra;                     // +0xa4
    ThreadedPtr mThreaded;            // +0xb8

    SkinObj_s004c_6df0(Res* pResource);
    ~SkinObj_s004c_6df0();
};
// ---- items of slice s004c6df0 end

// ---- items of slice s004ca430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pArchive;                       // DAT_015d9354
template <int N> inline void ScratchSlots_s004c_a430() { uint32_t s[N]; }
struct RefCounted {
    virtual void Unused(); // vptr at +0x0
    int   mnRefCount;      // +0x4
    int AddRef() {
        // double load, as emitted at /Od for this refcount template
        int n = mnRefCount + 1;
        mnRefCount = mnRefCount + 1;
        return n;
    }
    void Release();        // out of line (masked: 0x00453540)
};
class BigAbility : public RefCounted {
public:
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d);
    static void operator delete(void*, size_t);
    BigAbility();
    uint32_t mPad[0x1c8 / 4];      // total size 0x1d0
};
class AbilityData : public RefCounted {
public:
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d);
    static void operator delete(void*, size_t);
    AbilityData(float value);
    uint32_t mPad[0xf0 / 4];       // total size 0xf8
};
template <class T> class AutoRefCount_s004c_a430 {
public:
    AutoRefCount_s004c_a430() : mpObject(0) {}
    AutoRefCount_s004c_a430& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            ScratchSlots_s004c_a430<2>();
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* mpObject;
};
class IEditorManager {
public:
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
    virtual void Apply(void* pOwner, float value);   // +0x68
};
class IPropertyManager {
public:
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
    virtual bool Find(uint32_t key, void* pArchive, void** ppOut);   // +0x2c
};
class IPropertyList {
public:
    virtual void v00();
    virtual void Release();                                          // +0x4
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual bool GetProperty(uint32_t key, void** ppOut);            // +0x24
};
struct Property;   // opaque; the word at +0x12 is the property type
float* GetPropertyAsFloat(Property* p);
uint32_t InitVerbCollection(uint32_t key);
class EditorObject {
public:
    char pad00[8];
    void* mpOwner;                  // +0x8; +0x18 holds a resource key
    char pad0c[0x34 - 0xc];
    AutoRefCount_s004c_a430<BigAbility>  mPrimary;   // +0x34
    AutoRefCount_s004c_a430<AbilityData> mSecondary; // +0x38

    void Update(float value);
};
extern IEditorManager* g_pEditorManager;
extern IPropertyManager* g_pPropertyManager;   // 0x15fd8a8, via SP::PropertyManager()
// ---- items of slice s004ca430 end

// ---- items of slice s004ca6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(pop)
struct cSPVector3_s004c_a6e0 {
    float x, y, z;
    cSPVector3_s004c_a6e0() {}
    cSPVector3_s004c_a6e0(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
struct cSPMatrix3_s004c_a6e0 {
    float m[3][3];
};
cSPVector3_s004c_a6e0 operator+(const cSPVector3_s004c_a6e0& a, const cSPVector3_s004c_a6e0& b);              // 0x0041DC10
cSPVector3_s004c_a6e0 operator*(const cSPVector3_s004c_a6e0& v, const float& s);                   // 0x0041DCA0
cSPVector3_s004c_a6e0 RotateVector(const cSPVector3_s004c_a6e0& v, const cSPMatrix3_s004c_a6e0& m);           // 0x0041DAF0
cSPVector3_s004c_a6e0& operator+=(cSPVector3_s004c_a6e0& a, const cSPVector3_s004c_a6e0& b);                  // 0x0041DDB0
static inline void AssignVector(cSPVector3_s004c_a6e0* pDst, const cSPVector3_s004c_a6e0& src)
{
    pDst->x = src.x;
    pDst->y = src.y;
    pDst->z = src.z;
}
struct cSPTransform_s004c_a6e0 {  // size 0x38
    unsigned short mFlags;              // +0x0
    unsigned short mModificationCount;  // +0x2
    cSPVector3_s004c_a6e0 mTranslation;            // +0x4
    float mScale;                       // +0x10
    cSPMatrix3_s004c_a6e0 mRotation;               // +0x14

    void SetRotation(const cSPMatrix3_s004c_a6e0& m)
    {
        mRotation = m;
        mFlags |= 2;
        mModificationCount++;
    }
    void SetTranslation(const cSPVector3_s004c_a6e0& v)
    {
        mTranslation = v;
        mFlags |= 4;
        mModificationCount++;
    }
};
struct IndexMap {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    uint32_t mAllocator[3];
    int mBuffer[64];

    IndexMap(int n, int value);         // 0x00422740
    void DestroyBase();                 // 0x004C0B80 (VectorBase dtor)
    ~IndexMap()
    {
        for (int* p = mpBegin; p < mpEnd; ++p) {
        }
        DestroyBase();
    }
};
struct BoneIndexList {  // eastl::fixed_vector<unsigned int, 4>
    void push_back(const int& value);   // 0x00422380
    uint32_t mData[10];
};
struct SkinNode {  // pair<cSPVector3, fixed_vector<uint,4>>, 0x34 bytes
    cSPVector3_s004c_a6e0 mPosition;               // +0x0
    BoneIndexList mBoneIndices;         // +0xc
};
struct SkinBone {  // pair<uint,uint>
    int mParentNode;
    int mChildNode;
};
struct NodeVector {
    SkinNode* mpBegin; SkinNode* mpEnd; SkinNode* mpCapacity; uint32_t mAlloc;
    void erase(SkinNode* first, SkinNode* last);        // 0x004CE110
    void resize(int n);                                 // 0x004CD5B0
    void clear() { erase(mpBegin, mpEnd); }
    SkinNode* begin() { return mpBegin; }
};
struct BoneVector {
    SkinBone* mpBegin; SkinBone* mpEnd; SkinBone* mpCapacity; uint32_t mAlloc;
    void erase(SkinBone* first, SkinBone* last);        // 0x00530C80
    void resize(int n);                                 // 0x004CD440
    void clear() { erase(mpBegin, mpEnd); }
    SkinBone* begin() { return mpBegin; }
};
struct TransformVector {
    cSPTransform_s004c_a6e0* mpBegin; cSPTransform_s004c_a6e0* mpEnd; cSPTransform_s004c_a6e0* mpCapacity; uint32_t mAlloc;
    void erase(cSPTransform_s004c_a6e0* first, cSPTransform_s004c_a6e0* last); // 0x004238C0
    void resize(int n);                                  // 0x0041E3B0
    void clear() { erase(mpBegin, mpEnd); }
    cSPTransform_s004c_a6e0* begin() { return mpBegin; }
};
struct RectVector {
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAlloc;
    void erase(void* first, void* last);                 // 0x00455AE0
    void clear() { erase(mpBegin, mpEnd); }
};
struct cRuntimeCreatureBlock_s004c_a6e0 {  // retail size 0x8c
    short mBlockIndex;          // +0x0
    short mNodeIndex;           // +0x2
    short mParentIndex;         // +0x4
    short mSymmetricIndex;      // +0x6
    unsigned short mFlags;      // +0x8
    unsigned char mSubmeshId;   // +0xa
    unsigned char mBlockType;   // +0xb
    uint32_t pad0c[(0x30 - 0x0c) / 4];
    cSPMatrix3_s004c_a6e0 mRotation;       // +0x30
    cSPVector3_s004c_a6e0 mTranslation;    // +0x54
    uint32_t pad60[(0x70 - 0x60) / 4];
    float mJointLength;         // +0x70
    uint32_t pad74[(0x8c - 0x74) / 4];
};
struct BlockVector {
    cRuntimeCreatureBlock_s004c_a6e0* mpBegin; cRuntimeCreatureBlock_s004c_a6e0* mpEnd; cRuntimeCreatureBlock_s004c_a6e0* mpCapacity; uint32_t mAlloc;
    int size() { return (int)(mpEnd - mpBegin); }
};
struct cRuntimeCreatureResource_s004c_a6e0 {
    uint32_t pad00[0x98 / 4];
    BlockVector mBlocks;        // +0x98 (retail)
};
namespace SP {
class cSkinObject_s004c_a6e0 {
public:
    uint32_t pad00[2];
    cRuntimeCreatureResource_s004c_a6e0* mResource;    // +0x08
    uint32_t pad0c[(0x40 - 0x0c) / 4];
    NodeVector mNodes;                      // +0x40
    uint32_t pad50;
    BoneVector mBones;                      // +0x54
    uint32_t pad64;
    TransformVector mBoneTransforms;        // +0x68
    uint32_t pad78;
    RectVector mTextureSubRects;            // +0x7c

    cRuntimeCreatureResource_s004c_a6e0* GetResource() { return mResource; }
    bool BuildSkeleton();
};  // namespace SP
}
// ---- items of slice s004ca6e0 end

// ---- items of slice s004cb340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*    FUN_00f473a0(uint32_t size, const char* name,
                                 int, int, int, int);                    // 0x00f473a0 operator new (editor)
extern const char   kEditorAllocName[];                                  // 0x013eb430 ?kEditorAllocName@@3QBDB
extern float g_014854c8;                                                 // 0x014854c8
extern float g_013ec434;                                                 // 0x013ec434
extern float g_013ef550;                                                 // 0x013ef550
extern float g_013f059c;                                                 // 0x013f059c
extern "C" void     FUN_00921df0(const int* pTime);                      // 0x921df0 EA::Thread::ThreadSleep
extern uint32_t     g_01600778;                                          // 0x1600778 render-thread TEB id
extern "C" uint32_t FUN_004bb860(uint32_t workid);   // 0x004bb860 ?FUN_004bb860@@YAII@Z
extern "C" void FUN_0052b340(void* p1, void* p2, void* p3, void* p4, void* vs,
                             uint32_t a6, uint32_t a7, uint32_t a8, int a9, float a10);
extern float g_01485378;                             // 0x01485378 _HK_REAL_ZERO
extern "C" void      FUN_00777bf0(void);                        // pushShaderDataNull
extern "C" void      FUN_00777c10(void);                        // shader
extern "C" void      FUN_011fd7d0(void);                        // StateCacheClearCount
extern "C" void      FUN_011fd820(void);                        // StateCacheEnd
extern "C" int       FUN_004cdd70(int, void*);                  // vertex-chunk allocator
extern float g_013f05ac;                                        // 0x013f05ac part draw scale
template <int N> inline void ScratchSlots_s004c_b340() { uint32_t s[N]; }
struct NodeWeightAllocator {
    NodeWeightAllocator(const AllocTag& tag);        // 0x00429360
    uint32_t pad[2];
};
struct NodeWeightVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    NodeWeightAllocator mAllocator;
    NodeWeightVector() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(AllocTag()) { ScratchSlots_s004c_b340<1>(); }
};
struct PlainVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    uint32_t mAlloc[2];
    PlainVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
struct SkinBuildData {
    uint32_t mIndex;          // +0x00 (mesh-element index)
    uint32_t mf04;            // +0x04
    NodeWeightVector v1;      // +8
    PlainVector v2;           // +0x1c
    PlainVector v3;           // +0x30
    PlainVector v4;           // +0x44
    float    mf58;            // +0x58
    float    mf5c;            // +0x5c
    float    mf60;            // +0x60
    float    mf64;            // +0x64
    uint32_t mf68;            // +0x68
    PlainVector v5;           // +0x6c
    PlainVector v6;           // +0x80
    SkinBuildData();
};
template <class T> struct VectorT {                  // eastl::vector<T> (0x14 bytes)
    T* mpBegin; T* mpEnd; T* mpCapacity;
    uint32_t mAllocator[2];
    void FUN_00422740(int n, int fill);              // 0x00422740  resize(n, fill)
    void FUN_004c0b80();                             // 0x004c0b80  dtor
};
struct Alloc { uint32_t pad[3]; };
struct Vector3 { float x; float y; float z; };
extern "C" Vector3* FUN_0041db10(Vector3* out, Vector3* a, Vector3* b);  // 0x0041db10 a - b
extern "C" float    FUN_0040ae50(Vector3* v);                            // 0x0040ae50 VectorLength
static inline void RenderThreadYield() {
    if (g_01600778 != __readfsdword(0x18)) {
        int zero = 0;
        FUN_00921df0(&zero);
    }
}
struct VectorU32 {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity;
    bool empty();                                    // 0x00526430
};
struct VSet {
    int* mpBegin;                                    // +0x00
    int* mpEnd;                                      // +0x04
    uint32_t mPad[3];                                // +0x08
    VSet(const Alloc& a);                            // 0x00540470
    void FUN_004c5e30();                             // 0x004c5e30
    void FUN_004b0560(int n, int flags);             // 0x004b0560
    void FUN_00425990();                             // 0x00425990
};
struct BoneEntry { uint32_t f0; uint32_t f4; };      // 8-byte mBones element
struct MeshElement {                                 // 0x8c-byte skin-mesh element
    uint16_t f00;                                    // +0x00
    int16_t  mParent;                                // +0x02
    int16_t  mNext;                                  // +0x04
    uint16_t f06;                                    // +0x06
    uint16_t mFlags;                                 // +0x08
    uint8_t  f0a;                                    // +0x0a
    uint8_t  mKind;                                  // +0x0b (1 = follow mNext)
    uint16_t mf0c;                                   // +0x0c  cap-code range begin
    uint8_t  mf0e;                                   // +0x0e
    uint8_t  mf0f;                                   // +0x0f
    uint8_t  mf10;                                   // +0x10  cap-code range length
    uint8_t  f11[3];                                 // +0x11
    Vector3  mPosA;                                  // +0x14
    Vector3  mPosB;                                  // +0x20
    float    mf2c;                                   // +0x2c
    uint8_t  f30[0x8c - 0x30];                       // +0x30
};
struct BoneWeightBuilder {                           // cSkinObject +0x7c
    uint32_t mPad[5];                                // +0x00 .. +0x13
    void FUN_004cd690(int count);                    // 0x004cd690
};
namespace SP {
struct cDirectPropertyList_s004c_b340 {
    float GetFloatProperty(uint32_t key);            // 0x006a2710
    int   GetIntProperty(uint32_t key);              // 0x006a2660
};
}
namespace SP {
extern cDirectPropertyList_s004c_b340* g_015fd918;              // 0x015fd918  SP::sAppProperties
}
namespace SP {
struct cRuntimeCreatureResource_s004c_b340 {
    uint8_t   pad00[0x18];                           // +0x00
    uint32_t  mf18;                                  // +0x18
    uint8_t   pad1c[0x98 - 0x1c];                    // +0x1c
    uint8_t*  mpElements;                            // +0x98  MeshElement array (0x8c bytes each)
    uint8_t*  mpElementsEnd;                         // +0x9c
    uint8_t   padA0[0xac - 0xa0];                    // +0xa0
    uint32_t* mpCapCodes;                            // +0xac  cap-code words (bone-weight keys)
};
}
namespace SP {
struct PairIF;
}
namespace SP {
struct VectorIF {
    void* mpBegin;                                   // +0x00
    void* mpEnd;                                     // +0x04
    void* mpCapacity;                                // +0x08
    uint32_t mAllocator[2];                          // +0x0c
    PairIF* FUN_00530c80(PairIF* first, PairIF* last);// 0x00530c80 erase(first, last)
};
}
namespace SP {
struct SimpleVectorU {
    uint32_t* mpBegin;                               // +0x00
    uint32_t* mpEnd;                                 // +0x04
    uint32_t* mpCapacity;                            // +0x08
    uint32_t  mAlloc[2];                             // +0x0c
    void FUN_00454860(void* v);                      // 0x00454860 push_back(const uint&)
};
}
namespace SP {
struct MeshPaintTarget {                             // cSkinObject +0x34 (paint/mesh holder)
    uint32_t  f00;                                   // +0x00
    uint32_t  f04;                                   // +0x04
    uint8_t*  mpPartBegin;                           // +0x08  0xc-byte part elements
    uint8_t*  mpPartEnd;                             // +0x0c
    uint8_t   pad10[0x30 - 0x10];                    // +0x10
    VectorIF  mVec30;                                // +0x30
    uint8_t   pad44[0x58 - 0x44];                    // +0x44
    VectorU32 mVec58;                                // +0x58
    uint8_t   pad64[0x90 - 0x64];                    // +0x64
    uint32_t* mpOut90;                               // +0x90  bone-weight output records (0x10 bytes each)
    VectorU32 mVertexList;                           // +0x94
    uint8_t   padA0[0xbc - 0xa0];                    // +0xa0
    VectorU32 mIndexList;                            // +0xbc
    uint8_t   padC8[0xe4 - 0xc8];                    // +0xc8
    SimpleVectorU mParts;                            // +0xe4  built SkinBuildData* list
    uint8_t   padF8[0x124 - 0xf8];                   // +0xf8
    VectorIF  mVec124;                               // +0x124
    uint8_t   pad138[0x1cc - 0x138];                 // +0x138
    uint32_t  mState;                                // +0x1cc
    void FUN_00509450();                             // 0x00509450
    void FUN_005098a0();                             // 0x005098a0
    void FUN_00509b20();                             // 0x00509b20
    void FUN_0050a0a0();                             // 0x0050a0a0
    void FUN_0050aac0(float f);                      // 0x0050aac0
    void FUN_00508fd0();                             // 0x00508fd0
    void FUN_005087b0();                             // 0x005087b0 TangentBuilder::BuildTangents
};
}
namespace SP {
struct cSkinObject_s004c_b340 {
    uint8_t   pad00[8];                              // +0x00
    cRuntimeCreatureResource_s004c_b340* mResource;             // +0x08
    uint8_t   pad0c[0x34 - 0x0c];                    // +0x0c
    MeshPaintTarget* mMesh;                          // +0x34
    uint32_t  mf38;                                  // +0x38
    uint8_t   pad3c[0x40 - 0x3c];                    // +0x3c
    VectorT<uint32_t> mVec40;                        // +0x40
    VectorT<BoneEntry> mBones;                       // +0x54
    VectorT<uint32_t> mVec68;                        // +0x68
    BoneWeightBuilder mBuilder;                      // +0x7c
    uint32_t* mBoneWeights90;                        // +0x90  per-element bone-weight records (0x10 bytes)

    bool BuildMesh();                                // 0x004cb340
    int  BuildBones();                               // 0x004cb820
};
}
struct EmbeddedState {
    uint32_t SetVertexDescriptor();                  // 0x011EDCD0  ?SetVertexDescriptor@EmbeddedState@graphics@rw@@QAEIXZ
};
struct PartStateLink {
    uint32_t        f0;                              // +0x00
    EmbeddedState*  mpEmbedded;                      // +0x04
};
struct SkinPartArrays {
    uint32_t  f00;                                   // +0x00
    uint32_t  f04;                                   // +0x04
    Vector3*  mpRestPos;                             // +0x08  rest positions, indexed by mpIndexA[]
    uint32_t  f0c;                                   // +0x0c
    uint32_t  f10;                                   // +0x10
    uint32_t  f14;                                   // +0x14
    uint32_t  f18;                                   // +0x18
    Vector3*  mpBonePos;                             // +0x1c  bone positions, indexed by mpIndexB[]
    uint32_t  f20[14];                               // +0x20 .. +0x57
    int*      mpIndexA;                              // +0x58
    int*      mpIndexAEnd;                           // +0x5c
    uint32_t  f60;                                   // +0x60
    uint32_t  f64;                                   // +0x64
    uint32_t  f68;                                   // +0x68
    int*      mpIndexB;                              // +0x6c
};
struct SkinPartOwner {
    SkinPartArrays* mpPartArrays;                    // +0x00
    uint8_t         mPad[0x84];                      // +0x04 .. +0x87
};
struct PartCtx {
    uint32_t  mPad[8];                               // +0x00 .. +0x1f
    uint32_t  mVertexBase;                           // +0x20  running vertex count
    uint32_t  mPad24;                                // +0x24
    uint32_t  mPartCount;                            // +0x28  running part count
};
extern "C" void      FUN_00777b50(EmbeddedState*);              // 0x00777b50 SP::SetShaderData
extern "C" void      FUN_011fd7b0(EmbeddedState*, uint32_t*);   // StateCacheDispatch
extern "C" int       FUN_011fd790(EmbeddedState*);              // StateCacheVertexStride
extern "C" Vector3*  FUN_0041de40(Vector3*, float*, Vector3*);  // 0x0041de40 Vector3_Scale
extern "C" Vector3*  FUN_0041dc10(Vector3*, Vector3*, Vector3*);// 0x0041dc10 combine rest+bone
struct SkinPartBuilder {
    uint32_t        mPad[6];                         // +0x00 .. +0x17
    PartStateLink*  mpState;                         // +0x18
    uint32_t        mPad1c[21];                      // +0x1c .. +0x6f
    uint8_t         mGate;                           // +0x70
    void FUN_004cbf00(void*, void*, PartCtx*);
};
// ---- items of slice s004cb340 end

// ---- items of slice s004cd1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s004c_d1b0() { uint32_t s[N]; }
void EASTLFree(void* p);                                             // 0x00F47380
namespace eastl {
extern void* gpEmptyBucketArray[2];                  // 0x0154DF28
}
namespace eastl {
struct Link { Link* mpNext; };
}
namespace eastl {
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};
}
namespace eastl {
class fixed_pool_with_overflow : public fixed_pool_base { public:
    void* mpPoolBegin;
    void* mpCapacity;
    uint32_t mnNodeSize;
    __forceinline fixed_pool_with_overflow(void* pMemory) {
        mpHead = 0;
        init(pMemory, 0x100, 0x10, 4, 0);
        mpPoolBegin = pMemory;
        mpCapacity = (char*)pMemory + 0x100;
        mnNodeSize = 0x10;
    }
    void deallocate(void* p) {
        if ((p >= mpPoolBegin) && (p < mpCapacity)) {
            ((Link*)p)->mpNext = mpHead;
            mpHead = (Link*)p;
        } else
            OverflowFree(p, mnNodeSize);
    }
    static void OverflowFree(void* p, uint32_t n) { (void)&n; void* const pMemory = p; EASTLFree(pMemory); }
};
}
namespace eastl {
class fixed_hashtable_allocator { public:
    fixed_pool_with_overflow mPool;
    void* mpBucketBuffer;
    fixed_hashtable_allocator(void* pNodeBuffer, void* pBucketBuffer) : mPool(pNodeBuffer), mpBucketBuffer(pBucketBuffer) {}
    fixed_hashtable_allocator(const fixed_hashtable_allocator& x);
    void deallocate(void* p, uint32_t) {
        if (p != mpBucketBuffer) {
            if ((p >= mPool.mpPoolBegin) && (p < mPool.mpCapacity)) {
                ((Link*)p)->mpNext = mPool.mpHead;
                mPool.mpHead = (Link*)p;
            } else
                fixed_pool_with_overflow::OverflowFree(p, mPool.mnNodeSize);
        }
    }
};
}
namespace eastl {
struct MappedPair {
    int mIndex;
    float mWeight;
    MappedPair() : mIndex(-1), mWeight(-1.0f) {}
};
}
namespace eastl {
struct HashNode {
    uint32_t mKey;
    MappedPair mValue;
    HashNode* mpNext;
};
}
namespace eastl {
template <class T> struct hash_s004c_d1b0 { uint32_t operator()(T val) const { return (uint32_t)val; } };
}
namespace eastl {
template <class T> struct equal_to_s004c_d1b0 { bool operator()(const T& a, const T& b) const { return a == b; } };
}
namespace eastl {
struct mod_range_hashing { uint32_t operator()(uint32_t r, uint32_t n) const { return r % n; } };
}
namespace eastl {
struct default_ranged_hash {};
}
namespace eastl {
template <class P> struct use_first_s004c_d1b0 {};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct prime_rehash_policy_s004c_d1b0 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy_s004c_d1b0(float fMaxLoadFactor = 1.f) : mfMaxLoadFactor(fMaxLoadFactor), mfGrowthFactor(2.f), mnNextResize(0) {}
    static uint32_t GetPrevBucketCountOnly(uint32_t nBucketCountHint);   // 0x00921340
    uint32_t GetNextBucketCount(uint32_t nBucketCountHint) const;        // 0x00921360
    uint32_t GetBucketCount(uint32_t nElementCount) const;               // 0x009213C0
};
}
namespace eastl {
struct hashtable_iterator_base {
    HashNode* mpNode;
    HashNode** mpBucket;
    hashtable_iterator_base(HashNode* pNode, HashNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
}
namespace eastl {
struct hashtable_iterator : public hashtable_iterator_base {
    hashtable_iterator(HashNode* pNode = 0, HashNode** pBucket = 0) : hashtable_iterator_base(pNode, pBucket) {}
    hashtable_iterator(HashNode** pBucket) : hashtable_iterator_base(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base(x.mpNode, x.mpBucket) {}
    bool operator!=(const hashtable_iterator& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
struct insert_return_type {
    hashtable_iterator first;
    bool second;
};
}
namespace eastl {
struct value_pair {
    uint32_t first;
    MappedPair second;
    value_pair(const uint32_t& x, const MappedPair& y) : first(x), second(y) {}
};
}
namespace eastl {
class hashtable_s004c_d1b0 {
public:
    typedef hashtable_iterator iterator;

    hashtable_s004c_d1b0(uint32_t nBucketCount, const hash_s004c_d1b0<uint32_t>& h1, const mod_range_hashing& h2, const default_ranged_hash& h,
              const equal_to_s004c_d1b0<uint32_t>& eq, const use_first_s004c_d1b0<value_pair>& ek, const fixed_hashtable_allocator& allocator);
    ~hashtable_s004c_d1b0();

    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const uint32_t& k);
    insert_return_type DoInsertValue(const value_pair& value, true_type);    // 0x004CDBD0
    insert_return_type insert(const value_pair& value) { return DoInsertValue(value, true_type()); }
    void set_max_load_factor(float fMaxLoadFactor);
    void rehash_policy(const prime_rehash_policy_s004c_d1b0& rehashPolicy) {
        mRehashPolicy = rehashPolicy;
        const uint32_t nBuckets = rehashPolicy.GetBucketCount((uint32_t)mnElementCount);
        if (nBuckets > mnBucketCount)
            DoRehash(nBuckets);
    }

    void reset() {
        ScratchSlots_s004c_d1b0<1>();
        mnBucketCount = 1;
        mpBucketArray = (HashNode**)&gpEmptyBucketArray[0];
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    void clear() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    void DoFreeBuckets(HashNode** pBucketArray, uint32_t n) {
        if (n > 1)
            mAllocator.deallocate(pBucketArray, (n + 1) * sizeof(HashNode*));
    }
    void DoFreeNodes(HashNode** pBucketArray, uint32_t n);   // 0x004D0430
    HashNode** DoAllocateBuckets(uint32_t n);                 // 0x004CE7E0
    void DoRehash(uint32_t nBucketCount);                     // 0x004CE8B0
    uint32_t get_hash_code(const uint32_t& key) const { return (uint32_t)m_h1(key); }
    uint32_t bucket_index(const uint32_t&, uint32_t c, uint32_t n) const { return (uint32_t)m_h2(c, n); }
    bool compare(const uint32_t& k, uint32_t, HashNode* pNode) const { return m_equal(k, pNode->mKey); }
    HashNode* DoFindNode(HashNode* pNode, const uint32_t& k, uint32_t c) const {
        for (; pNode; pNode = pNode->mpNext) {
            if (compare(k, c, pNode))
                return pNode;
        }
        return 0;
    }

    use_first_s004c_d1b0<value_pair> m_extract;                 // 0x00 (hash_code_base: empty functors)
    equal_to_s004c_d1b0<uint32_t> m_equal;                      // 0x01
    hash_s004c_d1b0<uint32_t> m_h1;                             // 0x02
    mod_range_hashing m_h2;                          // 0x03
    HashNode** mpBucketArray;                        // 0x04
    uint32_t mnBucketCount;                          // 0x08
    uint32_t mnElementCount;                         // 0x0C
    prime_rehash_policy_s004c_d1b0 mRehashPolicy;               // 0x10
    fixed_hashtable_allocator mAllocator;            // 0x1C
};
}
namespace eastl {
class hash_map_s004c_d1b0 : public hashtable_s004c_d1b0 {
public:
    hash_map_s004c_d1b0(uint32_t nBucketCount, const hash_s004c_d1b0<uint32_t>& hashFunction, const equal_to_s004c_d1b0<uint32_t>& predicate,
             const fixed_hashtable_allocator& allocator);
    MappedPair& operator[](const uint32_t& key);
};
}
namespace eastl {
class fixed_hash_map : public hash_map_s004c_d1b0 {
public:
    fixed_hash_map(const hash_s004c_d1b0<uint32_t>& hashFunction, const equal_to_s004c_d1b0<uint32_t>& predicate);
    void* mBucketBuffer[18];                         // 0x34
    char mNodeBuffer[0x100];                         // 0x7C
};
}
// ---- items of slice s004cd1b0 end

// @ 0x004c44c0
namespace SP {
cSPEditorSkinPart_s004c_38e0* cSPEditorSkinManager_s004c_38e0::CreateSkinObject(cSPEditorBlock_s004c_38e0* block, uint32_t instance)
{
    cSPEditorSkinPart_s004c_38e0* part = new (kEditorAllocName, 0, 0, 0, 0) cSPEditorSkinPart_s004c_38e0;
    part->SetDrawMaterial(0xca9bb36f);
    part->SetModel(instance, 0xefeb80ec, false);
    part->SetSkinResolution(mRealtimeResolution, mHighQualityResolution);

    SimpleVec blocks;
    blocks.mpBegin = 0;
    blocks.mpEnd = 0;
    blocks.mpCapacity = 0;
    blocks.push_back((uint32_t&)block);
    CollectPartsRec(block, &blocks);
    part->Update((uint32_t*)&blocks, false);
    cIModelWorld_s004c_38e0* world = *(cIModelWorld_s004c_38e0**)((char*)block + 0x18);
    part->UpdateSceneObject(world);
    return part;
}
}  // namespace SP

// @ 0x004c45d0
namespace SP {
void* cSPEditorSkinManager_s004c_38e0::GetSceneObject(uint32_t which)
{
    switch (which) {
    case 0:
        return mTorsoSkin->GetSceneObject();
        break;
    case 1:
        return mCompleteSkin->GetSceneObject();
        break;
    }
    return 0;
}
}  // namespace SP

// @ 0x004c49e0
namespace SP {
void* cSPEditorSkinManager_s004c_4650::GetSkin(uint32_t which)
{
    switch (which) {
    case 0: {
        cSPEditorSkinPart_s004c_4650* p = mTorsoSkin;
        return p;
    }
    case 1: {
        cSPEditorSkinPart_s004c_4650* p = mCompleteSkin;
        return p;
    }
    }
    return 0;
}
}  // namespace SP

// @ 0x004c4a30
namespace SP {
bool cSPEditorSkinManager_s004c_4650::PickSkin(uint32_t which, cSPVector3 lod, cSPVector3 dir, cSPVector3* outPos, cSPVector3* outNormal, float* outDist, char flag)
{
    if (which == 0) {
        return mTorsoSkin->PickSkinPart(lod, dir, outPos, outNormal, outDist, flag);
    }
    if (which == 1) {
        return mCompleteSkin->PickSkinPart(lod, dir, outPos, outNormal, outDist, flag);
    }
    if (which == 2) {
        char found = 0;
        float bestDist = 0.0f;
        cSPVector3 bestPos;
        cSPVector3 bestNormal;
        BlockVec* vec = &mBlockTransforms;
        int n = vec->Size();
        for (int i = 0; i < n; ++i) {
            if (vec->mpBegin[i].block != 0) {
                cSPVector3 pos;
                cSPVector3 normal;
                float dist;
                if (vec->mpBegin[i].part->PickSkinPart(lod, dir, &pos, &normal, &dist, flag)) {
                    if (found && bestDist <= dist) {
                        continue;
                    }
                    bestDist = dist;
                    bestPos = pos;
                    bestNormal = normal;
                    found = 1;
                }
            }
        }
        if (found) {
            *outPos = bestPos;
            *outNormal = bestNormal;
            *outDist = bestDist;
            return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x004c4d30
namespace SP {
cSPEditorBlock_s004c_4650* cSPEditorSkinManager_s004c_4650::GetBlockOnSkin(uint32_t which, cSPVector3 pos)
{
    if (which == 0) {
        return mTorsoSkin->GetBlockOnSkin(pos);
    }
    if (which == 1) {
        return mCompleteSkin->GetBlockOnSkin(pos);
    }
    if (which == 2) {
        cSPEditorBlock_s004c_4650* result = 0;
        BlockVec* vec = &mBlockTransforms;
        int n = vec->Size();
        for (int i = 0; result == 0 && i < n; ++i) {
            if (vec->mpBegin[i].block != 0) {
                result = vec->mpBegin[i].part->GetBlockOnSkin(pos);
            }
        }
        return result;
    }
    return 0;
}
}  // namespace SP

// @ 0x004c4eb0
namespace SP {
void cSPEditorSkinManager_s004c_4650::DetachSkinParts()
{
    EnablePaint(0);
    mModel = 0;
    mSceneObjectModelWorld = 0;
    if (mTorsoSkin != 0) {
        mTorsoSkin->Shutdown();
    }
    if (mCompleteSkin != 0) {
        mCompleteSkin->Shutdown();
    }
    while (!mBlockTransforms.Empty()) {
        cSPEditorSkinPart_s004c_4650* last = mBlockTransforms.Back().part;
        last->Shutdown();
        mBlockTransforms.PopBack();
    }
}
}  // namespace SP

// @ 0x004c4f60
namespace SP {
void cSPEditorSkinManager_s004c_4650::SetDefaultMaterial(uint32_t id)
{
    mDefaultMaterial = id;
    if (mTorsoSkin != 0) {
        mTorsoSkin->SetDefaultMaterial(mDefaultMaterial);
    }
    if (mCompleteSkin != 0) {
        mCompleteSkin->SetDefaultMaterial(mDefaultMaterial);
    }
    int n = mBlockTransforms.Size();
    for (int i = 0; i < n; ++i) {
        mBlockTransforms.mpBegin[i].part->SetDefaultMaterial(mDefaultMaterial);
    }
}
}  // namespace SP

// @ 0x004c5030
namespace SP {
void cSPEditorSkinManager_s004c_4650::SetDefaultMaterialToDetachedLimb(uint32_t id, const void* block)
{
    BlockVec* vec = &mBlockTransforms;
    int n = vec->Size();
    for (int i = 0; i < n; ++i) {
        if (vec->mpBegin[i].block != 0) {
            cSPEditorSkinPart_s004c_4650* part = vec->mpBegin[i].part;
            void** begin = part->mBlockMatInfosBegin;
            void** end = part->mBlockMatInfosEnd;
            void** it = begin;
            while (it != end && *it != block) {
                ++it;
            }
            if (it != end) {
                part->SetDefaultMaterial(id);
                return;
            }
        }
    }
}
}  // namespace SP

// @ 0x004c5100
namespace SP {
void cSPEditorSkinManager_s004c_4650::SetSkinResolutions(float realtime, float highQuality)
{
    mPaintResolution = highQuality;
    mRealtimeResolution = realtime;
    mHighQualityResolution = highQuality;
    if (mTorsoSkin != 0) {
        mTorsoSkin->SetSkinResolutions(highQuality, highQuality);
    }
    if (mCompleteSkin != 0) {
        mCompleteSkin->SetSkinResolutions(realtime, highQuality);
    }
    BlockVec* vec = &mBlockTransforms;
    int n = vec->Size();
    for (int i = 0; i < n; ++i) {
        vec->mpBegin[i].part->SetSkinResolutions(realtime, highQuality);
    }
}
}  // namespace SP

// @ 0x004c5200
bool Ed::Update5200(SkinDesc* desc)
{
    if (mActive) {
        if (Skin() && Check58b0()) {
            GetSkinMgrA()->RemoveSkin(Skin());
            mpSkin = 0;
        }
        Sub4615e0(mKey.a, mKey.c, 0, 0, desc->GetPos(0));
        mpSkin = new("Editor", 0, 0, 0, 0) SkinObj();
        Skin()->mpThr = Thr();
        Skin()->mKey = mKey;
        Skin()->m5c = MaxRef(AppProp()->GetIntProperty(0xb8864eac), 0x40);
        Skin()->m60 = -1;
        Skin()->f65 = (desc->mId != 0x3d97a8e4 && AppProp()->GetDescription(0x2853e342)) ? 1 : 0;
        Skin()->f66 = desc->mId != 0x438f6347;
        Skin()->f67 = true;
        Skin()->f68 = false;
        Skin()->f69 = false;
        Skin()->f6a = true;
        for (int t28 = 0; t28 < 3; t28++) {
            Skin()->mPos[t28] = desc->GetPos(t28);
            Skin()->mAbil[t28] = desc->GetAbilA(t28);
            Skin()->m28[t28] = desc->GetAbilB(t28);
        }
        IPropPtr p4;
        if (GetPropMgr()->GetPropList(RemapTypeId(desc->ModelType()), gPropGroup, p4.ResetAddr())) {
            uint32_t n4 = 0;
            uint32_t n24 = 0x5e68c2e;
            uint32_t* t4;
            if (GetPropertyAsUint32Array(p4.Get(), 0x5e68c2e, &n4, &t4)) {
                for (int t15 = 0; t15 < 3 && t15 < (int)n4; t15++) {
                    if (Skin()->mAbil[t15] == 0) Skin()->mAbil[t15] = t4[t15];
                }
            }
        }
        if (desc->mId == 0x2b978c46) Skin()->m24 = 0xd723b947;
        if (desc->mId == 0x3d97a8e4) {
            Skin()->m24 = 0;
            Skin()->mAbil[2] = 0;
            Skin()->mAbil[1] = 0;
        }
        bool p11 = GetSkinMgrB()->Register(Skin());
        if (!p11) {
            mpSkin.AssignA(0);
            return false;
        }
        return true;
    }
    return false;
}

// @ 0x004c5910
void Ed::Get5910(Tex** a, Tex** b)
{
    if (a) { *a = Diffuse(); AddRefA(*a); }
    if (b) { *b = Normal(); AddRefA(*b); }
}

// @ 0x004c5980
void Ed::Diag5980(const wchar_t* dir, const wchar_t* name)
{
    ARef base;
    ARef num;
    ARef item;
    uint32_t node;
    Get5910(base.Addr(), num.AddrI());
    Str fl;
    fl.sprintf("%ls/%ls__diffuse.tga", dir, name);
    SaveTga7b2380(fl.mpBegin, DataOf(base.mp));
    fl.sprintf("%ls/%ls__normal.tga", dir, name);
    SaveTga7b2380(fl.mpBegin, DataOf(num.mp));
    uint32_t y = MakeKey();
    item = GetTexMgr()->CreateTexture(0x5e097c66, y, WidthOf(DataOf(num.mp)), HeightOf(DataOf(num.mp)), 1, 8, 0x1c, 0);
    if (Check7af8b0(num, item)) {
        fl.sprintf("%ls/%ls__specular.tga", dir, name);
        SaveTga7b2380(fl.mpBegin, DataOf(item.mp));
    }
    if (item.mp) item.Reset(0);
    ScratchSlots<3>();
}

// @ 0x004c6070
void PairVec::PopBack6070()
{ --mpEnd; mpEnd->~Pair(); }

// @ 0x004c6190
Elem* __fastcall FUN_004c6190(Vec8* self, int edx, Elem* pos, Elem* value)
{
    if (self->mpEnd == self->mpCap) {
        int nElem = (int)((char*)self->mpEnd - (char*)self->mpBegin) >> 3;
        int newCap = nElem > 0 ? nElem * 2 : 1;
        Elem* newData = newCap != 0
            ? (Elem*)((void*(__cdecl*)(void*, int, int, int))H_42dee0)
                         ((void*)((char*)self + 0xc), newCap * 8, 4, 0)
            : 0;
        Elem* p = FUN_004c6520(self->mpBegin, pos, newData);
        if (p != 0) {
            p->val = value->val;
            void** pobj = &p->obj;
            *pobj = value->obj;
            if (*pobj != 0)
                RC(*pobj)->AddRef();
        }
        Elem* newEnd = FUN_004c69b0(pos, self->mpEnd, (Elem*)((char*)p + 8));
        FUN_004c6a70(pos, self->mpEnd, (Elem*)((char*)p + 8));
        Elem* oldData = self->mpBegin;
        if (oldData != 0 && *(int*)((char*)oldData - 4) != 0)
            operator delete(oldData);
        self->mpBegin = newData;
        self->mpEnd = newEnd;
        self->mpCap = (Elem*)((char*)newData + newCap * 8);
    } else {
        Elem* v = value;
        if (pos <= value && value < self->mpEnd)
            v = (Elem*)((char*)value + 8);
        Elem* e = self->mpEnd;
        if (e != 0) {
            Elem* last = (Elem*)((char*)self->mpEnd - 8);
            e->val = last->val;
            void** pobj = &e->obj;
            *pobj = last->obj;
            if (*pobj != 0)
                RC(*pobj)->AddRef();
        }
        Elem* dst = self->mpEnd;
        Elem* src = (Elem*)((char*)self->mpEnd - 8);
        while (src != pos) {
            dst = (Elem*)((char*)dst - 8);
            Elem* prev = (Elem*)((char*)src - 8);
            dst->val = prev->val;
            ((TC1)H_4c5d80)(&dst->obj, prev->obj);
            src = prev;
        }
        pos->val = v->val;
        ((TC1)H_4c5d80)(&pos->obj, v->obj);
        self->mpEnd = (Elem*)((char*)self->mpEnd + 8);
    }
    return pos;
}

// @ 0x004c6520
Elem* __cdecl FUN_004c6520(Elem* first, Elem* last, Elem* dst)
{
    bool flag1 = false;
    Elem* r = FUN_004c69e0(first, last, dst);
    bool flag2 = false;
    FUN_004c6a70(first, last, dst);
    (void)flag1; (void)flag2;
    return r;
}

// @ 0x004c6560
void __fastcall FUN_004c6560(char* self, int edx, char* pos, unsigned count, char* value)
{
    if ((unsigned)(*(int*)(self + 8) - *(int*)(self + 4)) < count) {
        int curSize = *(int*)(self + 4) - *(int*)self;
        unsigned newCap = curSize == 0 ? 1 : (unsigned)curSize * 2;
        unsigned need = (unsigned)curSize + count;
        unsigned cap = newCap > need ? newCap : need;
        char* newData = cap != 0
            ? (char*)((void*(__cdecl*)(void*, unsigned, int, int))H_42dee0)
                         ((void*)(self + 0xc), cap, 1, 0)
            : 0;
        char* oldBegin = *(char**)self;
        int off = (int)pos - (int)oldBegin;
        void* r1 = ((void*(__cdecl*)(void*, void*, int))H_11e0744)(newData, oldBegin, off);
        char* p = (char*)r1 + off;
        FUN_004c6ae0((int*)&p, p, (int)count, value);
        int oldEnd = *(int*)(self + 4);
        int tail = oldEnd - (int)pos;
        void* r2 = ((void*(__cdecl*)(void*, void*, int))H_11e0744)(p + count, pos, tail);
        p = (char*)r2 + tail;
        char* ob = *(char**)self;
        if (ob != 0 && ob != *(char**)(self + 0x10))
            operator delete(ob);
        *(char**)self = newData;
        *(char**)(self + 4) = p;
        *(char**)(self + 8) = newData + cap;
    } else if (count != 0) {
        char v = *value;
        int tail = *(int*)(self + 4) - (int)pos;
        char* end = *(char**)(self + 4);
        if (count < (unsigned)tail) {
            int out1;
            FUN_004c6b30(&out1, end - count, end, end);
            *(char**)(self + 4) = *(char**)(self + 4) + count;
            int n = (int)end - (int)count;
            memmove(pos + count, pos, (unsigned)(n - (int)pos));
            ((void(__cdecl*)(void*, int, unsigned))H_11e073e)(pos, (int)v, count);
        } else {
            char* p3 = end;
            FUN_004c6ae0((int*)&p3, p3, (int)(count - (unsigned)tail), &v);
            *(char**)(self + 4) = *(char**)(self + 4) + (count - (unsigned)tail);
            char* newEnd = *(char**)(self + 4);
            int out2;
            FUN_004c6b30(&out2, pos, end, newEnd);
            *(char**)(self + 4) = *(char**)(self + 4) + tail;
            ((void(__cdecl*)(void*, int, int))H_11e073e)(pos, (int)v, (int)end - (int)pos);
        }
    }
}

// @ 0x004c69b0
Elem* __cdecl FUN_004c69b0(Elem* first, Elem* last, Elem* dst)
{
    bool flag = false;
    (void)flag;
    return FUN_004c69e0(first, last, dst);
}

// @ 0x004c69e0
Elem* __cdecl FUN_004c69e0(Elem* first, Elem* last, Elem* dst)
{
    for (; first != last;
         first = (Elem*)((char*)first + 8), dst = (Elem*)((char*)dst + 8)) {
        Elem* p = dst;
        void** pobj;
        Elem* q;
        if (p != 0) {
            p->val = first->val;
            pobj = &p->obj;
            *pobj = first->obj;
            if (*pobj != 0)
                ((RefObj*)((char*)*pobj + 0xbc))->AddRef();
            q = p;
        } else {
            q = 0;
        }
        (void)q;
    }
    return dst;
}

// @ 0x004c6a70
Elem* __cdecl FUN_004c6a70(Elem* first, Elem* last, Elem* dst)
{
    for (; first != last;
         first = (Elem*)((char*)first + 8), dst = (Elem*)((char*)dst + 8)) {
        void** pobj = &first->obj;
        if (*pobj != 0)
            ((RefObj*)((char*)*pobj + 0xbc))->Release();
    }
    return dst;
}

// @ 0x004c6b30
int* __cdecl FUN_004c6b30(int* out, void* first, void* last, void* dst)
{
    void* a = dst;
    void* b = last;
    void* c = first;
    char flag = 1;
    (void)flag;
    void* r = (char*)((void*(__cdecl*)(void*, void*, int))H_11e0744)(a, c, (char*)b - (char*)c)
              + ((char*)b - (char*)c);
    *out = (int)r;
    return out;
}

// @ 0x004c6ba0
void* __fastcall FUN_004c6ba0(char* self, int edx)
{
    *(unsigned*)self = 0x13ef094u;
    _InterlockedExchange((volatile long*)(self + 4), 0);
    *(unsigned*)self = 0x13f05a8u;
    *(int*)(self + 8) = 0;

    char t1; char t2; char t3; char t4; char t5; char t6;

    *(int*)(self + 0x0c) = 0; *(int*)(self + 0x10) = 0; *(int*)(self + 0x14) = 0;
    ((TC1)H_429360)((void*)(self + 0x18), &t1);
    *(int*)(self + 0x20) = 0; *(int*)(self + 0x24) = 0; *(int*)(self + 0x28) = 0;
    ((TC1)H_429360)((void*)(self + 0x2c), &t2);
    *(int*)(self + 0x34) = 0;
    *(int*)(self + 0x38) = 0;
    *(float*)(self + 0x3c) = *(float*)0x01485378;
    *(int*)(self + 0x40) = 0; *(int*)(self + 0x44) = 0; *(int*)(self + 0x48) = 0;
    ((TC1)H_429360)((void*)(self + 0x4c), &t3);
    *(int*)(self + 0x54) = 0; *(int*)(self + 0x58) = 0; *(int*)(self + 0x5c) = 0;
    ((TC1)H_429360)((void*)(self + 0x60), &t4);
    *(int*)(self + 0x68) = 0; *(int*)(self + 0x6c) = 0; *(int*)(self + 0x70) = 0;
    ((TC1)H_429360)((void*)(self + 0x74), &t5);
    *(int*)(self + 0x7c) = 0; *(int*)(self + 0x80) = 0; *(int*)(self + 0x84) = 0;
    ((TC1)H_429360)((void*)(self + 0x88), &t6);
    *(int*)(self + 0x90) = 0; *(int*)(self + 0x94) = 0; *(int*)(self + 0x98) = 0;
    *(int*)(self + 0xa4) = 0; *(int*)(self + 0xa8) = 0; *(int*)(self + 0xac) = 0;
    *(int*)(self + 0xb8) = 0;
    return self;
}

// @ 0x004c6df0
SkinObj_s004c_6df0::SkinObj_s004c_6df0(Res* pResource)
: mResource(pResource), mFloat(0.0f)
{
    CBlock* blocks = pResource->mBlocks.mpBegin;
    int nBlocks = pResource->mBlocks.size();
    mBlockProps.resize(nBlocks);
    for (int i = 0; i < nBlocks; i++) {
        PropertyManager* pm = GetPropertyManager();
        void* pv = mBlockProps[i].AsPPVoidParam();
        if (!pm->GetPropertyList(blocks[i].instance, blocks[i].group, pv)) {
            PropertyManager* pm2 = GetPropertyManager();
            PropRef* slot = &mBlockProps[i];
            if (slot->mp) {
                PropertyList* old = slot->mp;
                slot->mp = 0;
                old->Release();
            }
            pm2->GetPropertyList(0x4f5f8ce, gPropGroup, slot);
        }
    }

    int nodeCount = 0;
    for (int j = 0; j < nBlocks; j++)
        nodeCount += 1 + ((blocks[j].flags & 2) != 0);
    mNodeBlockMap.resize(nodeCount);

    int node = 0;
    for (int k = 0; k < nBlocks; k++) {
        if (blocks[k].flags & 2) {
            mNodeBlockMap[node] = (uint8_t)k;
            node++;
        }
        mNodeBlockMap[node] = (uint8_t)k;
        node++;
    }

    float bottom = 1.0f;
    float right = 1.0f;
    float top = 0.0f;
    float left = 0.0f;
    RectF rect(left, top, right, bottom);
    mTextureSubRects.resize(nBlocks, rect);
}

// @ 0x004c72f0
SkinObj_s004c_6df0::~SkinObj_s004c_6df0()
{
    *(void**)this = (void*)0x13F05A8u;
}
#pragma pack(pop)

// @ 0x004ca430
void EditorObject::Update(float value)
{
    if (mPrimary.mpObject == 0) {
        mPrimary = new ("Editor", 0, 0, 0, 0) BigAbility();
    }

    if (mSecondary.mpObject == 0) {
        mSecondary = new ("Editor", 0, 0, 0, 0) AbilityData(0.01f);
    }

    if (value == -1.0f) {
        uint32_t key = 0;
        void* pOwner = mpOwner;
        uint32_t id = InitVerbCollection(*(uint32_t*)((char*)pOwner + 0x18));
        if (id == 0x438f6347)
            key = 0x1c7eca95;
        else if (id == 0x3d97a8e4)
            key = 0x3615a30b;
        else if (id == 0x2b978c46)
            key = 0x465c50ba;

        value = 0.028f;
        if (key != 0) {
            uint32_t propertyId = 0x711306ce;
            IPropertyList* pList = 0;

            IPropertyManager* pMgr = g_pPropertyManager;
            if (pList != 0)
                pList->Release();

            if (pMgr->Find(key, g_pArchive, (void**)&pList)) {
                if (pList != 0) {
                    Property* pProp = 0;
                    if (pList->GetProperty(propertyId, (void**)&pProp)) {
                        if (*(uint16_t*)((char*)pProp + 0x12) == 0xd) {
                            value = *GetPropertyAsFloat(pProp);
                        }
                    }
                    pList->Release();
                }
            }
        }
    }

    IEditorManager* pManager = g_pEditorManager;
    pManager->Apply(this, value);
}

// @ 0x004ca6e0
bool SP::cSkinObject_s004c_a6e0::BuildSkeleton()
{
    SP::cSkinObject_s004c_a6e0* self = this;
    cRuntimeCreatureBlock_s004c_a6e0* blocks = self->GetResource()->mBlocks.mpBegin;
    int nBlocks = self->GetResource()->mBlocks.size();
    self->mTextureSubRects.clear();
    if (nBlocks == 0)
        return false;

    int i;
    for (i = 0; i < nBlocks && blocks[i].mBlockType == 5; i++) {
    }
    int nSpine = i;
    int nExtraBones = 0;
    if (nSpine > 0) {
        for (; i < nBlocks && blocks[i].mBlockType == 3; i++) {
            if (blocks[i].mFlags & 2)
                nExtraBones++;
        }
    } else {
        for (; i < nBlocks && blocks[i].mBlockType == 3; i++) {
        }
    }
    int limbEnd = i;
    int nRemaining = nBlocks - i;
    int firstType4 = -1;
    if (i < nBlocks && blocks[i].mBlockType == 4)
        firstType4 = i;

    int nNodes = blocks[nBlocks - 1].mNodeIndex + 1;
    int nBones = nBlocks + nExtraBones;
    self->mNodes.clear();
    self->mBones.clear();
    self->mBoneTransforms.clear();
    self->mNodes.resize(nNodes);
    self->mBones.resize(nBones);
    self->mBoneTransforms.resize(nBones);
    SkinNode* nodes = self->mNodes.begin();
    SkinBone* bones = self->mBones.begin();
    cSPTransform_s004c_a6e0* transforms = self->mBoneTransforms.begin();

    IndexMap nodeBlocks(nNodes, -1);
    for (i = 0; i < nBlocks; i++) {
        if (blocks[i].mFlags & 2)
            nodeBlocks.mpBegin[blocks[i].mNodeIndex - 1] = i;
        nodeBlocks.mpBegin[blocks[i].mNodeIndex] = i;
    }

    for (i = 0; i < nNodes; i++) {
        cRuntimeCreatureBlock_s004c_a6e0* pBlock = &blocks[nodeBlocks.mpBegin[i]];
        if (pBlock->mBlockType == 5) {
            if (i == 0 || i == nSpine) {
                nodes[i].mPosition = pBlock->mTranslation;
            } else {
                cRuntimeCreatureBlock_s004c_a6e0* pNext = &blocks[nodeBlocks.mpBegin[i] + 1];
                AssignVector(&nodes[i].mPosition, (pBlock->mTranslation + pNext->mTranslation) * 0.5f);
            }
        } else if (pBlock->mBlockType == 3) {
            if (i == pBlock->mNodeIndex) {
                cSPVector3_s004c_a6e0 pos(0.0f, -pBlock->mJointLength, 0.0f);
                pos = RotateVector(pos, pBlock->mRotation);
                pos += pBlock->mTranslation;
                nodes[i].mPosition = pos;
            } else {
                nodes[i].mPosition = pBlock->mTranslation;
            }
        } else {
            nodes[i].mPosition = pBlock->mTranslation;
        }
    }

    i = 0;
    if (nSpine != 0) {
        for (i = 0; i < nSpine; i++) {
            bones[i].mParentNode = i;
            bones[i].mChildNode = i + 1;
            transforms[i].SetRotation(blocks[i].mRotation);
            transforms[i].SetTranslation(blocks[i].mTranslation);
        }
    }
    for (; i < nBlocks && blocks[i].mBlockType == 3; i++) {
        if (blocks[i].mFlags & 2)
            bones[i].mParentNode = blocks[i].mNodeIndex - 1;
        else
            bones[i].mParentNode = blocks[blocks[i].mParentIndex].mNodeIndex;
        bones[i].mChildNode = blocks[i].mNodeIndex;
        transforms[i].SetRotation(blocks[i].mRotation);
        transforms[i].SetTranslation(blocks[i].mTranslation);
    }
    for (; i < nBlocks; i++) {
        if (nSpine != 0) {
            if (blocks[i].mParentIndex < nSpine / 2)
                bones[i].mParentNode = bones[blocks[i].mParentIndex].mParentNode;
            else
                bones[i].mParentNode = bones[blocks[i].mParentIndex].mChildNode;
        } else if (blocks[i].mFlags & 2) {
            bones[i].mParentNode = blocks[i].mNodeIndex - 1;
        } else {
            bones[i].mParentNode = blocks[blocks[i].mParentIndex].mNodeIndex;
        }
        bones[i].mChildNode = blocks[i].mNodeIndex;
        transforms[i].SetRotation(blocks[i].mRotation);
        transforms[i].SetTranslation(blocks[i].mTranslation);
    }

    int nExtra = 0;
    if (nSpine > 0) {
        for (i = nSpine; i < limbEnd; i++) {
            if (blocks[i].mFlags & 2) {
                int bone = nBlocks + nExtra;
                bones[bone].mParentNode = bones[blocks[i].mParentIndex].mChildNode;
                bones[bone].mChildNode = blocks[i].mNodeIndex - 1;
                transforms[bone].SetRotation(blocks[blocks[i].mParentIndex].mRotation);
                transforms[bone].SetTranslation(blocks[blocks[i].mParentIndex].mTranslation);
                nExtra++;
            }
        }
    }

    for (i = 0; i < nBones; i++) {
        int boneIndex = i;
        nodes[bones[i].mParentNode].mBoneIndices.push_back(boneIndex);
        int boneIndex2 = i;
        nodes[bones[i].mChildNode].mBoneIndices.push_back(boneIndex2);
    }
    (void)nRemaining;
    (void)firstType4;
    return true;
}

// @ 0x004cb340
namespace SP {
bool cSkinObject_s004c_b340::BuildMesh()
{
    cRuntimeCreatureResource_s004c_b340* res = mResource;
    MeshElement* elems = (MeshElement*)res->mpElements;
    int count = (int)(res->mpElementsEnd - res->mpElements) / 0x8c;
    if (count == 0)
        return false;

    cDirectPropertyList_s004c_b340* props = g_015fd918;
    float fScale = props->GetFloatProperty(0xa0304059u);
    int   prop   = props->GetIntProperty(0x4f6a84fdu);
    int   boneCount = (int)(mBones.mpEnd - mBones.mpBegin) >> 3;
    int   maxIdx = elems[count - 1].mParent + 1;

    VectorT<int> map;
    map.FUN_00422740(maxIdx, -1);
    int* mapArr = map.mpBegin;
    for (int i = 0; i < count; ++i) {
        if (elems[i].mParent != -1) {
            if ((elems[i].mFlags & 2) != 0)
                mapArr[elems[i].mParent - 1] = i;
            mapArr[elems[i].mParent] = i;
        }
    }

    Alloc alloc;
    VSet vs(alloc);
    vs.FUN_004c5e30();
    vs.FUN_004b0560(boneCount, 0);
    int* out = vs.mpBegin;
    for (int i = 0; i < count; ++i) {
        int j = i;
        while (elems[j].mKind == 1)
            j = elems[j].mNext;
        out[i] = j;
    }
    for (int k = count; k < boneCount; ++k) {
        int j = elems[mapArr[mBones.mpBegin[k].f4]].mNext;
        while (elems[j].mKind == 1)
            j = elems[j].mNext;
        out[k] = j;
    }

    MeshPaintTarget* mesh = mMesh;
    if (mesh->mVertexList.empty())
        mesh->FUN_00509450();
    if (mesh->mIndexList.empty())
        mesh->FUN_005098a0();

    bool useScale = (FUN_004bb860(res->mf18) == 0x2b978c46u);
    int  meshCount = (int)(mesh->mpPartEnd - mesh->mpPartBegin) / 0xc;
    mBuilder.FUN_004cd690(meshCount);
    float param = useScale ? fScale : g_01485378;
    FUN_0052b340(&mBuilder, &mVec40, &mBones, &mVec68, &vs, mf38,
                 (uint32_t)mesh, (uint32_t)res, prop, param);
    for (int* p = vs.mpBegin; p < vs.mpEnd; ++p) {}
    vs.FUN_00425990();
    for (int* p = map.mpBegin; p < map.mpEnd; ++p) {}
    map.FUN_004c0b80();
    return true;
}
}  // namespace SP

// @ 0x004cb820
int SP::cSkinObject_s004c_b340::BuildBones()
{
    MeshPaintTarget* mesh = mMesh;
    if (mesh->mVertexList.empty())
        mesh->FUN_00509450();
    if (mesh->mIndexList.empty())
        mesh->FUN_005098a0();
    RenderThreadYield();

    mesh->FUN_00509b20();

    cRuntimeCreatureResource_s004c_b340* res = mResource;
    MeshElement* elems = (MeshElement*)res->mpElements;
    int count = (int)(res->mpElementsEnd - res->mpElements) / 0x8c;
    uint32_t* capCodes = res->mpCapCodes;

    int partCount = 0;
    for (int i = 0; i < count; ++i) {
        MeshElement& e = elems[i];
        if ((e.mFlags & 1) != 0)
            continue;

        Vector3 diff;
        FUN_0041db10(&diff, &e.mPosA, &e.mPosB);      // posA - posB
        float len = FUN_0040ae50(&diff);
        float d = len * e.mf2c;

        int jEnd = (int)e.mf0c + (int)e.mf10;
        for (int j = (int)e.mf0c; j < jEnd; ++j) {
            if (capCodes[j] == 0x74756f6du) {         // "mout"
                d *= g_014854c8;
                break;
            }
        }
        d = d * g_013ec434 + g_013ef550;

        SkinBuildData* p = (SkinBuildData*)FUN_00f473a0(0x94, kEditorAllocName, 0, 0, 0, 0);
        if (p != 0)
            p->SkinBuildData::SkinBuildData();
        p->mIndex = (uint32_t)partCount;
        p->mf04 = 0;
        p->mf60 = g_01485378;
        p->mf58 = g_01485378;
        p->mf64 = d;
        p->mf5c = d;
        p->mf68 = 0;
        mesh->mParts.FUN_00454860(&p);
        ++partCount;
    }

    mesh->mVec30.FUN_00530c80((PairIF*)mesh->mVec30.mpBegin, (PairIF*)mesh->mVec30.mpEnd);
    mesh->mVec124.FUN_00530c80((PairIF*)mesh->mVec124.mpBegin, (PairIF*)mesh->mVec124.mpEnd);

    if (!mesh->mVec58.empty()) {
        mesh->mState = 2;
        mesh->FUN_0050a0a0();
        mesh->mState = 0;
    }
    RenderThreadYield();

    mesh->FUN_0050aac0(g_013f059c);
    RenderThreadYield();
    mesh->FUN_005087b0();                             // TangentBuilder::BuildTangents
    RenderThreadYield();
    mesh->mState = 3;
    mesh->FUN_00508fd0();
    mesh->mState = 0;

    int idx = 0;
    for (int k = 0; k < count; ++k) {
        MeshElement& e = elems[k];
        if ((e.mFlags & 1) != 0)
            continue;
        SkinBuildData* sb = (SkinBuildData*)mesh->mParts.mpBegin[idx];
        float* out = (float*)((uint8_t*)mBoneWeights90 + k * 0x10);
        out[0] = sb->mf58;
        out[1] = sb->mf60;
        out[2] = sb->mf5c;
        out[3] = sb->mf64;
        ++idx;
    }
    return 1;
}

// @ 0x004cbdf0
SkinBuildData::SkinBuildData()
{}

// @ 0x004cbf00
void SkinPartBuilder::FUN_004cbf00(void* a2, void* a3, PartCtx* ctx)
{
    (void)a2; (void)a3;
    // the owner begins 0x88 bytes before this subobject
    SkinPartArrays* src = ((SkinPartOwner*)((uint8_t*)this - 0x88))->mpPartArrays;
    if (this->mpState == 0 || src == 0)
        return;

    EmbeddedState* es = this->mpState->mpEmbedded;
    uint8_t* vd = (uint8_t*)es->SetVertexDescriptor();
    if (vd[0xf] != 0x18)
        return;

    FUN_00777bf0();
    FUN_00777b50(es);
    uint32_t dispatchSlot;
    FUN_011fd7b0(es, &dispatchSlot);
    int stride = FUN_011fd790(es);
    int count  = (int)(src->mpIndexAEnd - src->mpIndexA);
    int idx = 0;
    stride -= stride % 3;
    float scale = (this->mGate != 0) ? g_013f05ac : g_01485378;
    int*     indexA  = src->mpIndexA;
    int*     indexB  = src->mpIndexB;
    Vector3* restPos = src->mpRestPos;
    Vector3* bonePos = src->mpBonePos;
    ctx->mVertexBase += (uint32_t)count;

    while (count > 0) {
        int chunk = (count < stride) ? count : stride;
        struct Chunk { int mCount; int mPad; Vector3* mpOut; } rec;
        rec.mCount = chunk;
        rec.mPad = 0;
        rec.mpOut = 0;
        if (FUN_004cdd70(chunk, &rec)) {
            int end = idx + chunk;
            Vector3* w = rec.mpOut;
            for (int i = idx; i < end; ++i) {
                Vector3 scaled;
                Vector3* s = FUN_0041de40(&scaled, &scale, &bonePos[indexB[i]]);
                Vector3 res;
                Vector3* r = FUN_0041dc10(&res, &restPos[indexA[i]], s);
                *w = *r; ++w;
                *w = bonePos[indexB[i]]; ++w;
            }
            rec.mpOut = w;
            FUN_011fd820();
            ctx->mPartCount += 1;
        }
        idx += chunk;
        count -= chunk;
    }
    FUN_011fd7d0();
    FUN_00777c10();
}

// @ 0x004cd1b0
namespace eastl {
fixed_hash_map::fixed_hash_map(const hash_s004c_d1b0<uint32_t>& hashFunction, const equal_to_s004c_d1b0<uint32_t>& predicate)
: hash_map_s004c_d1b0(prime_rehash_policy_s004c_d1b0::GetPrevBucketCountOnly(17), hashFunction, predicate,
               fixed_hashtable_allocator(mNodeBuffer, mBucketBuffer))
{
    ScratchSlots_s004c_d1b0<6>();
    set_max_load_factor(10000.f);
}
}  // namespace eastl
