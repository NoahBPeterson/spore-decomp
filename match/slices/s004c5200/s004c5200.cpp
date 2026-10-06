// Slice s004c5200: editor skin holder + texture-debug helpers (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
// Local names matter at /Od (frame slot order is a hash of the names). Where noted, slots were fitted by name search.
#include "types.h"
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement)
inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}
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
void __cdecl operator_delete__(void*);
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
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
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
struct TexFlags {
    uint32_t v;
    TexFlags() { v = 0; }
};
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
// ---- skin update (0x4c5200) types ----
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
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropList(uint32_t type, uint32_t group, IPropList** out); };
struct SkinMgrA { void RemoveSkin(SkinObj* s); };                 // @ 0x522a40
struct SkinMgrB { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
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
extern uint32_t gPropGroup;                     // @ 0x15d8de8
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
// @ 0x004c58b0
bool Ed::Check58b0() {
    return Skin() && !Skin()->f6b && !Skin()->f6c;
}
// @ 0x004c5910
void Ed::Get5910(Tex** a, Tex** b) {
    if (a) { *a = Diffuse(); AddRefA(*a); }
    if (b) { *b = Normal(); AddRefA(*b); }
}
// @ 0x004c5980
void Ed::Diag5980(const wchar_t* dir, const wchar_t* name) {
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
// @ 0x004c5d50
void EPtr::Dtor5d50() { if (p) p->ref.Release(); }
// @ 0x004c5d80
EPtr& EPtr::Assign5d80(EObj* np) {
    if (np != p) { EObj* old = p; if (np) np->ref.AddRef(); p = np; if (old) old->ref.Release(); }
    return *this;
}
// @ 0x004c5f40
__forceinline void DestructRange(Pair* first, Pair* last) { for (; first < last; ++first) first->~Pair(); }
void PairVec::Dtor5f40() {
    DestructRange(mpBegin, mpEnd);
    ScratchSlots<3>();
    Base45daf0();
}
// @ 0x004c5fc0
void PairVec::PushBack5fc0(const Pair& v) {
    if (mpEnd < mpCapacity) { new (mpEnd++) Pair(v); }
    else DoInsertValue(mpEnd, v);
}
// @ 0x004c6070
void PairVec::PopBack6070() { --mpEnd; mpEnd->~Pair(); }
// @ 0x004c6150
EPtr* EPtr::Copy6150(EPtr* o) { p = o->p; if (p) p->ref.AddRef(); return this; }

struct Transform { uint32_t d[14]; Transform(); };
struct TVec {
    Transform* mpBegin; Transform* mpEnd; Transform* mpCapacity;
    void EmplaceBack5eb0();
    void DoInsertValue(Transform* pos, const Transform& v);
};
// @ 0x004c5eb0
void TVec::EmplaceBack5eb0() {
    if (mpEnd < mpCapacity) { new (mpEnd++) Transform(); }
    else DoInsertValue(mpEnd, Transform());
    ScratchSlots<26>();
}

// @ 0x004c5200  local names (p4, t28, ...) are fitted to the original /Od frame slot order
bool Ed::Update5200(SkinDesc* desc) {
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

// @ 0x004c60e0  PARTIAL: vector resize helper (105B); not part of this pass.
void Editor_Erase60e0(void* self) { (void)self; }
