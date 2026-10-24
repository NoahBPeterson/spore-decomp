// src/game/SPEngine/SPGraphicsModelUtilities.cpp -- migrated from slice(s) s007553c0, s00754310, s00753270, s00430ca0, s00430320, s0042d560, s004103c0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsModelUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" extern void* vtbl_Editor_cEditorResource[];
extern "C" extern void* vtbl_Graphics_BakeSprites[];
extern "C" extern void* vtbl_Simulator_cCreatureAbility[];
extern "C" extern void* vtbl_BakeJob_Final0[];   // 0x013eb928
extern "C" extern void* vtbl_BakeJob_Final1[];   // 0x013eb924
extern uint32_t    GetBakeContext(uint32_t id);           // 0x006b1f90
extern void        BakeOne(uint32_t item, uint32_t flag); // 0x00756280
extern void*       __fastcall GetRefSlot(void* ref);      // 0x0041d940
extern void        __fastcall QueueSubmit(void* ref, void* job);   // 0x004223f0
extern void        __fastcall QueueSubmit2(void* ref, void* job);  // 0x0068f9b0
extern void        __fastcall ReleaseRef(void* p);        // 0x00690120
extern void        __fastcall FlushRef(void* p);          // 0x006909b0
extern void        __fastcall AssignRef(void* dst, void* src);   // 0x0041cd10
extern void        Publish(void* x);                      // 0x00430900
extern bool        RunBake(void** outRef, void* list, uint32_t a, uint32_t b, void* c, void* d,
                           uint32_t e, void* f, uint32_t g, uint32_t h, void* i, void* j);  // 0x007573a0
extern void* ThreadedObjectNew();                         // ctor 0x0077d1d0
extern void* PropertyListNew();                           // ctor 0x006a1c40
extern void* AllocateGraphics(uint32_t sz, const char* tag, int, int, int, int);
#include <intrin.h>
#include <new>
#include "SP/cModelInstance.h"
#include "EA/Variant.h"
#include "SP/cJob.h"
#include "SP/cPropertyList.h"

// ---- items of slice s004103c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern void* vtbl_Editor_cEditorResource[];
extern "C" extern void* vtbl_Graphics_BakeSprites[];
extern "C" extern void* vtbl_Simulator_cCreatureAbility[];
extern "C" extern void* vtbl_BakeJob_Final0[];   // 0x013eb928
extern "C" extern void* vtbl_BakeJob_Final1[];   // 0x013eb924
struct ThreadedObject {
    void** vptr; volatile long mnRefCount;
    void Release();
};
struct PtrVector { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; };
struct RC { volatile long n; RC() { _InterlockedExchange(&n, 0); } };
struct SubBase { void** vp; SubBase() { vp = vtbl_Simulator_cCreatureAbility; } };
struct SubIface : SubBase { RC rc; };
struct JobBase0 { void** vp; JobBase0() { vp = vtbl_Editor_cEditorResource; } };
struct JobBase1 : JobBase0 { JobBase1() { vp = vtbl_Graphics_BakeSprites; } };
struct BakeJob : JobBase1 {
    SubIface iface;           // +4 (vptr), +8 (refcount)
    bool     mbDone;          // +0xC
    uint32_t mKeyLow;         // +0x10
    uint32_t mKeyHigh;        // +0x14
    BakeJob(uint32_t keyLow, uint32_t keyHigh);
};
struct Interface { virtual void v0(); virtual void v1(); };  // slot 0 = AddRef, slot 1 = Release
struct Queue {              // vtable slots used: 0x10, 0x20, 0x24
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(uint32_t arg);       // +0x10
    virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8();                   // +0x20
    virtual void q9();                   // +0x24
};
struct PropertyList { virtual void AddRef(); virtual void Release(); };
struct EditorMgr {          // vtable slots 0x2c, 0x34
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void e10();
    virtual void RegisterProperties(uint32_t id, uint32_t key, void* ref);   // +0x2c
    virtual void e12();
    virtual void SetPropertyList(PropertyList* pl, uint32_t a, uint32_t b);  // +0x34
};
struct ServiceHub { virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3();
                    virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7();
                    virtual void h8(); virtual void h9(); virtual void Prepare(); /* +0x28 */ };
extern ServiceHub* GetServiceHub();                       // 0x0067dd40
extern EditorMgr*  GetEditorMgr();                        // 0x0067de30
extern uint32_t    GetBakeContext(uint32_t id);           // 0x006b1f90
extern void        BakeOne(uint32_t item, uint32_t flag); // 0x00756280
extern void        InitThreadedObject(ThreadedObject* o, uint32_t a, uint32_t b);   // 0x00430450
extern Queue*      GetQueue();                            // 0x0068f4d0
extern void*       __fastcall GetRefSlot(void* ref);      // 0x0041d940
extern void        __fastcall QueueSubmit(void* ref, void* job);   // 0x004223f0
extern void        __fastcall QueueSubmit2(void* ref, void* job);  // 0x0068f9b0
extern void        __fastcall ReleaseRef(void* p);        // 0x00690120
extern void        __fastcall FlushRef(void* p);          // 0x006909b0
extern void        __fastcall AssignRef(void* dst, void* src);   // 0x0041cd10
extern void        Publish(void* x);                      // 0x00430900
extern bool        RunBake(void** outRef, void* list, uint32_t a, uint32_t b, void* c, void* d,
                           uint32_t e, void* f, uint32_t g, uint32_t h, void* i, void* j);  // 0x007573a0
extern void* ThreadedObjectNew();                         // ctor 0x0077d1d0
extern void* PropertyListNew();                           // ctor 0x006a1c40
extern void* AllocateGraphics(uint32_t sz, const char* tag, int, int, int, int);
struct BakeRequest {
    char pad0[0x228];
    uint32_t mKeyLow;            // +0x228
    uint32_t pad1;
    uint32_t mKeyHigh;           // +0x230
    uint32_t pad2;
    uint16_t mFlags;             // +0x238
    char pad3[0x338 - 0x23A];
    PtrVector mMainList;         // +0x338
    PtrVector mEditorList;       // +0x34c
    char pad4[0x388 - 0x360];
    uint32_t mOptions;           // +0x388
    char pad5[0x3dc - 0x38c];
    uint32_t mEditorOptions;     // +0x3dc
    char pad6[0x424 - 0x3e0];
    bool mbPrepared;             // +0x424
    bool mbPublishMain;          // +0x425

    bool Bake();
};
// ---- items of slice s004103c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern ServiceHub* GetServiceHub();                       // 0x0067dd40
extern EditorMgr*  GetEditorMgr();                        // 0x0067de30
extern void        InitThreadedObject(ThreadedObject* o, uint32_t a, uint32_t b);   // 0x00430450
extern Queue*      GetQueue();                            // 0x0068f4d0

// ---- items of slice s0042d560 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void PadN() { uint32_t s[N]; }
struct KeyPair { int key; void* value; };
inline bool LessInt(const int& a, const int& b) { return a < b; }
// ---- items of slice s0042d560 end

// ---- items of slice s00430320 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchange)
void EASTL_allocator_deallocate(void* p);                                       // 0x00F47380
void* operator new(unsigned int, const char*, int, int, int, int);              // 0x00F473A0
struct Object {
    virtual int AddRef();
    virtual int Release();
};
struct PropertyListValue {
    uint32_t pad00[4];
    uint16_t pad10;
    uint16_t type;   // +0x12 (0xd = float)
    float* GetFloat();   // 0x0041EA70
};
struct PropertyList_s0043_0320 : Object {
virtual void v08();
virtual void v0C();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
virtual void v20();
    virtual bool GetProperty(uint32_t id, PropertyListValue** dst);   // +0x24
};
struct PropertyListPtr {
    PropertyList_s0043_0320* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList_s0043_0320** OutImpl();    // 0x0041D870
    PropertyList_s0043_0320** Out() { return OutImpl(); }
    PropertyList_s0043_0320** AsPointer() {
        if (mpObject) {
            PropertyList_s0043_0320* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct GroupKey {
    uint32_t slot : 8;
    uint32_t kind : 8;
    uint32_t rest : 16;
};
inline GroupKey MakeGroupKey(GroupKey base, uint8_t kind, uint8_t slot)
{
    base.kind = kind;
    base.slot = slot;
    return base;
}
struct PropManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0C();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList_s0043_0320** dst);   // +0x2C
    static PropManager* GetImpl();   // 0x0067DE30
};
bool TryGetUIntProperty(PropertyList_s0043_0320* list, uint32_t propId, int* out);   // 0x00410370
struct TextureHandle;
struct TextureManager {   // 0x0067DD60
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0C();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
    virtual TextureHandle* GetTexture(uint32_t instanceID, uint32_t groupID, int flags);   // +0x20
    static TextureManager* GetImpl();
};
void* GetUnusedManagerA();   // 0x0067DDA0
void* GetUnusedManagerB();   // 0x0067DD40
struct Material {
    uint32_t pad[28];
    Material();   // 0x0040D010 (size 0x70)
    void SetTexture(int stage, TextureHandle* tex);   // 0x0077CB10
    void SetFilterA(int stage, int mode);             // 0x00777A60
    void SetFilterB(int stage, int mode);             // 0x00777A80
    void SetFilterC(int stage, int mode);             // 0x00777AA0
};
struct MaterialParams {
    uint32_t pad[3];
    uint8_t flag;      // +0x0C
    float a;           // +0x10
    float b;           // +0x14
    float c;           // +0x18
    MaterialParams();  // 0x00432CF0 (size 0x20)
};
struct MaterialList {
    uint32_t pad[2];
    void** mpBegin;    // +8
    void resize(unsigned n);                // 0x004CD3C0
    void push_back(Material* const& m);     // 0x00454860
};
struct Alloc { const char* name; uint32_t flags; };
struct ResKey2 { uint32_t a, b; ResKey2() : a(0xffffffff), b(0xffffffff) {} };
struct KeyProvider {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0C();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3C();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4C();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5C();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6C();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7C();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8C();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9C();
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAC();
virtual void vB0();
virtual void vB4();
virtual void vB8();
    virtual void FillKey(ResKey2* key);   // +0xBC
    static KeyProvider* Get();   // 0x0067DD40
};
struct Notifier {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0C();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
virtual void v30();
virtual void v34();
virtual void v38();
    virtual void Post(ResKey2* key, uint32_t a, uint32_t b, uint32_t evt, uint32_t c, uint8_t d);   // +0x3C
    static Notifier* Get();   // 0x0067DDB0
};
struct RefCountedAbility {
    RefCountedAbility() : mRefCount(0) {}
    virtual ~RefCountedAbility() {}
    int mRefCount;   // +4
};
struct SimpleAbility : RefCountedAbility {
    SimpleAbility();
    int mKind;       // +8
};
struct EmptyTag { EmptyTag() {} };
struct RcObject {
    uint32_t vtbl;
    int mRefCount;     // +4
    int AddRef() { return mRefCount++ + 1; }
    void Release();    // 0x00453540
};
struct RcPtr {
    RcObject* mp;
    RcPtr(RcObject* p) : mp(p) { if (mp) mp->AddRef(); }
    ~RcPtr() { if (mp) mp->Release(); }
};
struct OwnedVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap; Alloc a;
    OwnedVec(const EmptyTag& = EmptyTag());   // 0x00540470
    ~OwnedVec();                     // 0x00432D60
    void push_back(const RcPtr& p); // 0x004E0E80
};
struct VecAbility : SimpleAbility {
    OwnedVec mVec;    // +0x0C
    static void operator delete(void* p) { int u0, u1, u2, u3, u4, u5, u6, u7; EASTL_allocator_deallocate(p); }
};
struct Item8 { uint32_t a, b; };
struct ItemVec {            // 20 bytes
    Item8* mpBegin; Item8* mpEnd; Item8* mpCap; Alloc a;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct ItemVecVec {
    ItemVec* mpBegin; ItemVec* mpEnd; ItemVec* mpCap; Alloc a;
    ItemVecVec(const EmptyTag&);   // 0x00540470
    ~ItemVecVec();                 // 0x00432DE0
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct HandleRef { uint32_t v; };
struct HandleVec {
    HandleRef* mpBegin; HandleRef* mpEnd; HandleRef* mpCap; Alloc a;
    HandleVec(const EmptyTag& = EmptyTag());    // 0x00540470
    ~HandleVec();                  // 0x0041EB80
    void push_back(const Item8& v);   // 0x0041EF20
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    HandleRef& back() { return mpBegin[size() - 1]; }
};
void RegisterHandle(HandleRef h, uint32_t id);   // 0x00756280 (cdecl)
struct AbilityBuilder {
    void Collect(uint32_t instanceID, ItemVecVec& out);   // 0x007A0EE0
};
RcObject* CreateRcObject(int a, int b, float* data, int size);   // 0x0079AB90 (cdecl)
void FinishBuild(void* out, HandleVec* refs, uint32_t a, uint32_t b, uint32_t c, int, int, int, int,
                 uint32_t d, int, uint32_t e);   // 0x007573A0 (cdecl)
// ---- items of slice s00430320 end

// ---- items of slice s00430ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned size, const char* name, int, int, int, int);
struct IObject {
    virtual void Destroy();
    virtual void Release();
};
struct Service {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Begin();   // +0x20
    virtual void End();     // +0x24
};
struct ObjectHeader {       // first base: vptr + 8 bytes
    virtual void AddRef();
    virtual void Release();
    int pad[2];
};
struct PtrVec {
    IObject** begin;
    IObject** end;
    IObject** cap;
    void __thiscall resize(int n);
    int size() { return (int)(end - begin); }
    IObject** at(int i) { return begin + i; }
};
struct BakeTarget : ObjectHeader, PtrVec {   // PtrVec at +0x0c
};
struct Graphics_BakeSprites : ObjectHeader, PtrVec {
    int pad2[2];
    Graphics_BakeSprites();
};
Service* GetServiceHost();
void Resolve(void* out, PtrVec* vec, int, int);
void BakeOne(void* src, void* slot, int level, int arg, int, int);
struct ServiceRef {
    Service* s;
    void Init(Service* x) { s = x; }
    void Begin() { s->Begin(); }
    void End() { s->End(); }
};
struct BakerRef {
    Graphics_BakeSprites* p;
    void AddRef() { p->AddRef(); }
    void Release() { p->Release(); }
};
// ---- items of slice s00430ca0 end

// ---- items of slice s00753270 begin (TODO(rewrite): local stubs, replace by canonical classes)
void FUN_0093dd80_754250(int, int, int, int, int);
struct S_754250 {
  char pad_0[0x10];
  uint16_t m10;
  uint16_t m12;
  S_754250* FUN_00754250(int param_2);
};
// ---- items of slice s00753270 end

// ---- items of slice s00754310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_BehaviorMessage[];  // 0x13eb90c
extern char vtbl_MessageBasicRC5[];  // 0x13eb844
bool FUN_00754960(void*, void*, void*);
void FUN_006acfe0(void*, void*);
void FUN_0067dd60();
class RefT_007545b0 {
 public:
  virtual int AddRef();
  virtual int Release();
};
typedef int(__thiscall* VF0)(void*);
typedef int(__thiscall* VF1)(void*, int);
typedef int(__thiscall* VF2)(void*, int, int);
typedef int(__thiscall* VF3)(void*, int, int, int);
typedef int(__thiscall* VF6)(void*, int, int, int, int, int, int);
#define VSLOT(o, off) ((*(void***)(o))[(off) / 4])
static inline int vc0(void* o, int off) { return ((VF0)VSLOT(o, off))(o); }
static inline int vc1(void* o, int off, int a) { return ((VF1)VSLOT(o, off))(o, a); }
static inline int vc2(void* o, int off, int a, int b) { return ((VF2)VSLOT(o, off))(o, a, b); }
static inline int vc3(void* o, int off, int a, int b, int c) { return ((VF3)VSLOT(o, off))(o, a, b, c); }
static inline int vc6(void* o, int off, int a, int b, int c, int d, int e, int f) {
  return ((VF6)VSLOT(o, off))(o, a, b, c, d, e, f);
}
struct Ref {
  void* p;
  Ref() : p(0) {}
  explicit Ref(void* q) : p(q) {
    if (p) vc0(p, 0);
  }
  ~Ref() {
    if (p) vc0(p, 4);
  }
  void reset() {
    void* o = p;
    if (o) {
      p = 0;
      vc0(o, 4);
    }
  }
};
void operator delete(void*, const char*, int, int, int, int);
struct Key {
  uint32_t a, b, c;
};
struct Variant {
  uint32_t data[4];
  uint16_t mFlags;
  uint16_t mTypeId;
  Variant() : mFlags(0), mTypeId(0) {}
  ~Variant() {
    if (mFlags & 4) Destruct(0);
  }
  void SetKey(const Key* k);  // 0x422f40 operator=<Key>
  void Destruct(int a);  // 0x93db80
  void Set(int type, int a, const void* src, int n, int m);  // 0x93dd80
};
struct Res {
  virtual void Destroy(int flag);
  int rc;
  char pad[0x100 - 8];
  Res();  // 0x740e90
  void Attach(void* ref);  // 0x742b30
  bool Load(void* ref);  // 0x741a40
  void ReleaseOut();  // 0x73a820
};
struct ResPtr {
  Res* p;
  explicit ResPtr(Res* q) : p(q) {
    if (p) p->rc++;
  }
  ~ResPtr() {
    if (p) {
      if (--p->rc == 0) {
        p->rc = 1;
        p->Destroy(1);
      }
    }
  }
};
void* __cdecl PropertyManager();  // 0x67de30
void* __cdecl GetManager();  // 0x67dcd0 (EA::ResourceMan)
void* __cdecl MessageServer();  // 0x67dcc0
bool __cdecl GetPropertyAsKey(void* list, uint32_t id, Key* out);  // 0x6a1250
bool __cdecl FUN_006ad030(const Key* k);
bool __cdecl FUN_006acfe0_k(const Key* k, void* res);  // 0x6acfe0
bool __cdecl GetRwModelAsGameMeshesNoCache(void* obj);  // 0x757d20
void* __cdecl FUN_00759280(void* obj);
void __cdecl SetCachingType(int type, void* obj);  // 0x6ac040
bool __cdecl FUN_007542b0(void* out, Res* r);
class cPropertyList {
 public:
  cPropertyList();  // 0x6a1c40
  void SetParent(void* parent);  // 0x6a1710
};
struct cJob {
  char pad[0x18];
  uint32_t m18;
  uint32_t mSlot;  // +0x1c
  void Continuation(void* fn, void* arg);  // 0x68f9f0
  void FUN_006913c0(int v);
};
struct S_007544e0 {
  char pad_11c[0x11c];
  char m11c[0x18];  // +0x11c .. 0x134
  char m134[4];
  void* m138;  // +0x138 (counted)
  char pad_13c[4];
  S_007544e0();  // FUN_007004d0
};
struct S_007545b0 {
  char pad_0[0x44];
  void* m044;  // +0x44
  char pad_48[0x100 - 0x48];
  RefT_007545b0* m100;  // +0x100
  bool FUN_007545b0(int param_2);
};
struct S_00754770 {
  uint32_t m00, m04, m08;
  uint32_t m0c;
  uint32_t m10;
  uint32_t m14;
  uint32_t m18;
  void* m1c;
  void* m20;
  bool FUN_00754770(void* out);
};
struct S_00754c20 {
  char pad[0xc];
  uint32_t* mpBegin;  // +0xc
  uint32_t* mpEnd;  // +0x10
  char pad14[0x64 - 0x14];
  void* m64;  // +0x64
  void FUN_00754c20(cJob* job);
};
struct Msg {
  void* vtbl;  // +0
  volatile long rc;  // +4
  uint32_t f08, f0c, f10, f14, f18, f1c;
  uint32_t pad20[4];
  uint32_t id;  // +0x30
  uint32_t pad34;
  uint32_t f38;  // +0x38
  void Destruct();  // 0x421cf0
};
struct S_00754ca0 {
  char pad0[0xc];
  uint32_t m0c;  // +0xc
  uint32_t pad10;
  uint32_t m14[4];  // +0x14: per-slot key instance
  float m24[4];  // +0x24: per-slot weights
  char pad34[0x44 - 0x34];
  char* m44;  // +0x44 model data
  char pad48[0x104 - 0x48];
  void* m104;  // +0x104 property list
  bool FUN_00754ca0(int unused);
};
struct Mask5 {
  uint32_t d[4];
  uint32_t z;
};
struct GlyphInfo {
  uint32_t a, b;
};
GlyphInfo* __cdecl do_copy(GlyphInfo* first, GlyphInfo* last, GlyphInfo* dest);  // 0xac4440
void* __cdecl eastl_copy(void* sret, GlyphInfo* first, GlyphInfo* last, GlyphInfo* dest, const void* tag);  // 0x76ffd0
struct GlyphVec {
  GlyphInfo* mpBegin;
  GlyphInfo* mpEnd;
  GlyphInfo* mpCapacity;
  GlyphInfo* DoRealloc(unsigned n, GlyphInfo* first, GlyphInfo* last);  // 0x754f80
  GlyphVec& Assign(const GlyphVec& x);  // the original operator=; named so the checker can find it
};
// ---- items of slice s00754310 end

// ---- items of slice s007553c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void FUN_007553b0();
void FUN_00429e00(int, unsigned int, int);
int FUN_006df700(int, int, int);
void FUN_0059c410(int, int);
struct cJob_755520 {
  char pad_0[0x18];
  int mThreadAffinity;  // +0x18
  bool Continuation(void* fn, void* arg);
};
struct X_755520 {
  bool FUN_00754770(cJob_755520* job);
  bool FUN_00755520(cJob_755520* job);
};
struct V_755570 {
  int* mBegin;
  int* mEnd;
  void FUN_00755570(unsigned int param_2, int param_3);
};
// ---- items of slice s007553c0 end

// @ 0x004103c0
bool BakeRequest::Bake()
{
    if (!mbPrepared)
        GetServiceHub()->Prepare();

    bool hasEditor = (mFlags & 0x100) != 0;
    uint32_t keyLow = mKeyLow;
    uint32_t keyHigh = mKeyHigh;
    void* result = 0;
    uint32_t ctx = GetBakeContext(0x11ac1ac);

    unsigned n = (unsigned)(mMainList.mpEnd - mMainList.mpBegin);
    for (unsigned i = 0; i < n; ++i)
        BakeOne(mMainList.mpBegin[i], 0x9cff27c);

    if (hasEditor) {
        unsigned m = (unsigned)(mEditorList.mpEnd - mEditorList.mpBegin);
        for (unsigned i = 0; i < m; ++i)
            BakeOne(mEditorList.mpBegin[i], 0x9cff27c);
    }

    ThreadedObject* threaded = 0;
    void* mem = AllocateGraphics(0x1c, "Graphics", 0, 0, 0, 0);
    ThreadedObject* created = mem ? (ThreadedObject*)ThreadedObjectNew() : 0;
    if (created != threaded) {
        ThreadedObject* old = threaded;
        if (created)
            _InterlockedExchangeAdd(&created->mnRefCount, 1);
        threaded = created;
        if (old)
            old->Release();
    }
    InitThreadedObject(threaded, keyLow, keyHigh);

    Queue* queue = GetQueue();
    void* mem2 = AllocateGraphics(0x18, "Graphics", 0, 0, 0, 0);
    BakeJob* job = mem2 ? new (mem2) BakeJob(keyLow, keyHigh) : 0;
    if (job)
        ((Interface*)job)->v0();
    queue->q8();
    queue->q4((uint32_t)GetRefSlot(&result));
    QueueSubmit(result, job);
    QueueSubmit2(result, job);
    *(uint32_t*)((char*)result + 0x18) = 1;
    queue->q9();

    if (mbPublishMain) {
        void* tmp = 0;
        uint32_t flags = (keyHigh & 0xffff00ff) | (0x7e << 8);
        Publish(RunBake /* placeholder: see nonmatching.txt */ ? GetRefSlot(&tmp) : 0);
        if (tmp) {
            FlushRef(result);
            AssignRef(&result, tmp);
        }
        if (tmp)
            ReleaseRef(tmp);
        (void)flags;
    }

    if (hasEditor) {
        void* tmp = 0;
        PropertyList* props = 0;
        uint32_t flags = (keyHigh & 0xffff00ff) | (0x71 << 8);
        EditorMgr* ed = GetEditorMgr();
        ed->RegisterProperties(0x4529f96f, flags, GetRefSlot(&tmp));
        void* pm = AllocateGraphics(0x38, "Editor", 0, 0, 0, 0);
        PropertyList* newProps = pm ? (PropertyList*)PropertyListNew() : 0;
        if (newProps != props) {
            PropertyList* old = props;
            if (newProps)
                newProps->AddRef();
            props = newProps;
            if (old)
                old->Release();
        }
        ed = GetEditorMgr();
        ed->SetPropertyList(props, keyLow, flags);
        queue->q8();
        queue->q4((uint32_t)GetRefSlot(&result));
        QueueSubmit(result, job);
        QueueSubmit2(result, job);
        queue->q9();
        if (tmp)
            ReleaseRef(tmp);
        void* out = 0;
        if (!RunBake(&out, &mEditorList, keyLow, flags, 0, &mEditorOptions, 0, &mOptions, 0, ctx, 0, result)) {
            if (props)
                props->Release();
            if (out)
                ReleaseRef(out);
            if (job)
                ((Interface*)job)->v1();
            if (threaded)
                threaded->Release();
            if (result)
                ReleaseRef(result);
            return false;
        }
        FlushRef(out);
        AssignRef(&out, out);
        if (props)
            props->Release();
        if (out)
            ReleaseRef(out);
    }

    uint32_t flags2 = (keyHigh & 0xffff00ff) | (0x71 << 8);
    uint32_t unusedKey = keyLow;
    void* out2 = 0;
    (void)flags2; (void)unusedKey;
    bool ok = RunBake(&out2, &mMainList, keyLow, keyHigh, threaded, 0, 0, &mOptions, 0, ctx, &unusedKey, result);
    if (!ok) {
        if (out2)
            ReleaseRef(out2);
        if (job)
            ((Interface*)job)->v1();
        if (threaded)
            threaded->Release();
        if (result)
            ReleaseRef(result);
        return false;
    }
    FlushRef(out2);
    if (out2 != result) {
        void* old = result;
        if (out2)
            ReleaseRef(out2);   // stands in for AddRef (FUN_0068f950)
        result = out2;
        if (old)
            ReleaseRef(old);
    }
    FlushRef(out2);
    if (out2)
        ReleaseRef(out2);
    if (job)
        ((Interface*)job)->v1();
    if (threaded)
        threaded->Release();
    if (result)
        ReleaseRef(result);
    return true;
}

// @ 0x00410cc0
BakeJob::BakeJob(uint32_t keyLow, uint32_t keyHigh)
{
    vp = vtbl_BakeJob_Final0;
    iface.vp = vtbl_BakeJob_Final1;
    mbDone = false;
    mKeyLow = keyLow;
    mKeyHigh = keyHigh;
}

// @ 0x0042dd00
KeyPair* LowerBound(KeyPair* first, KeyPair* last, const KeyPair& value)
{
    int n = last - first;
    while (n > 0) {
        KeyPair* mid = first;
        int half = n >> 1;
        mid += half;
        if (LessInt(mid->key, value.key)) { ++mid; first = mid; n = n - (half + 1); }
        else n = half;
    }
    PadN<1>();
    return first;
}

// @ 0x004303e0
void PostEditorEvent(uint32_t a, uint32_t b, uint32_t c, uint8_t d)
{
    Notifier* pNotifier = Notifier::Get();
    ResKey2 key;
    KeyProvider::Get()->FillKey(&key);
    pNotifier->Post(&key, b, a, 0x245801e, c, d);
}

// @ 0x00430450
void BuildMaterials(MaterialList* pList, uint32_t instanceID, GroupKey baseKey)
{
    extern uint32_t g_Unused015FD918;
    uint32_t savedGlobal = g_Unused015FD918;
    int variant = 0;
    PropertyListPtr pProps;
    bool ok;
    if (PropManager::GetImpl()->GetPropertyList(instanceID, *(uint32_t*)&baseKey, pProps.AsPointer())) {
        ok = TryGetUIntProperty(pProps.mpObject, 0x4c6ba3c, &variant);
    }
    GroupKey key0 = MakeGroupKey(baseKey, 0x29, 0);
    GroupKey key1 = MakeGroupKey(baseKey, 0x29, 1);
    GroupKey key2 = MakeGroupKey(baseKey, 0x29, 2);
    TextureManager* pTexMgr = TextureManager::GetImpl();
    void* unusedA = GetUnusedManagerA();
    void* unusedB = GetUnusedManagerB();
    Material* pMaterial = new ("Graphics", 0, 0, 0, 0) Material;
    TextureHandle* tex0 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key0, 0);
    pMaterial->SetTexture(0, tex0);
    pMaterial->SetFilterA(0, 1);
    pMaterial->SetFilterA(0, 1);
    pMaterial->SetFilterB(0, 2);
    pMaterial->SetFilterC(0, 2);
    if (variant == 1) {
        TextureHandle* tex1 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key1, 0);
        pMaterial->SetTexture(1, tex1);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterB(1, 2);
        pMaterial->SetFilterC(1, 2);
        MaterialParams* pParams = new ("Graphics", 0, 0, 0, 0) MaterialParams;
        pParams->flag = 0;
        pParams->a = 60.0f;
        pParams->b = 1.0f;
        pParams->c = 1.0f;
        pList->resize(2);
        pList->mpBegin[0] = pMaterial;
        pList->mpBegin[1] = pParams;
    } else if (variant == 2) {
        TextureHandle* tex1 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key1, 0);
        TextureHandle* tex2 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key2, 0);
        pMaterial->SetTexture(1, tex1);
        pMaterial->SetTexture(2, tex2);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterB(1, 2);
        pMaterial->SetFilterC(1, 2);
        pMaterial->SetFilterA(2, 1);
        pMaterial->SetFilterA(2, 1);
        pMaterial->SetFilterB(2, 2);
        pMaterial->SetFilterC(2, 2);
        MaterialParams* pParams = new ("Graphics", 0, 0, 0, 0) MaterialParams;
        pParams->flag = 1;
        pParams->a = 60.0f;
        pParams->b = 1.0f;
        pParams->c = 1.0f;
        pList->resize(2);
        pList->mpBegin[0] = pMaterial;
        pList->mpBegin[1] = pParams;
    } else {
        Material* tmp = pMaterial;
        pList->push_back(tmp);
    }
}

// @ 0x00430900
void BuildAbility(void* pOut, uint32_t instanceID, uint32_t propInstance, uint32_t propGroup, uint32_t p5, uint32_t p6, uint32_t p7, uint32_t p8)
{
    float radius = 25.0f;
    PropertyListPtr pProps;
    if (PropManager::GetImpl()->GetPropertyList(propInstance, propGroup, pProps.Out())) {
        PropertyList_s0043_0320* pList = pProps.mpObject;
        PropertyListValue* pValue;
        if (pList && pList->GetProperty(0xf9efb9, &pValue) && pValue->type == 0xd)
            radius = *pValue->GetFloat();
    }
    float r = radius - radius / 5.0f;
    HandleVec refs((EmptyTag()));
    float data[4];
    data[0] = 0.0f;
    data[1] = 2.0f;
    data[2] = 1.2f * r;
    data[3] = r * r;
    VecAbility* pAbility = new ("App", 0, 0, 0, 0) VecAbility;
    {
        RcPtr rc(CreateRcObject(0, 1, data, 4));
        pAbility->mVec.push_back(rc);
    }
    ItemVecVec items((EmptyTag()));
    ((AbilityBuilder*)pAbility)->Collect(instanceID, items);
    for (unsigned i = 0, n = (unsigned)items.size(); i < n; ++i) {
        for (unsigned j = 0, m = (unsigned)items.mpBegin[i].size(); j < m; ++j) {
            refs.push_back(items.mpBegin[i].mpBegin[j]);
            RegisterHandle(refs.back(), 0x407dfddb);
        }
    }
    FinishBuild(pOut, &refs, propInstance, p5, p6, 0, 0, 0, 0, p8, 0, p7);
}

// @ 0x00430c20
SimpleAbility::SimpleAbility()
: mKind(4) {}

// @ 0x00430ca0
void BakeSpriteTextureMips(void* out, int level, int arg, BakeTarget* target)
{
    ServiceRef svc;
    BakerRef baker;
    int n, i;
    if (level >= 0) {
        svc.Init(GetServiceHost());
        svc.Begin();
        baker.p = new ("Graphics/SpriteTextureMIPs", 0, 0, 0, 0) Graphics_BakeSprites();
        if (baker.p) baker.AddRef();
        Resolve(out, baker.p, 0, 0);
        target->resize(baker.p->size());
        for (i = 0, n = target->size(); i < n; ++i) {
            IObject** slot = target->at(i);
            if (*slot) {
                IObject* old = *slot;
                *slot = 0;
                old->Release();
            }
            BakeOne(*baker.p->at(i), slot, level, arg, 0, 0);
        }
        if (baker.p) baker.Release();
        svc.End();
    } else {
        Resolve(out, target, 0, 0);
    }
}

// @ 0x00754250
typedef void (__thiscall* ConstructVariantFn_754250)(void* self, int, int, int, int, int);
S_754250* S_754250::FUN_00754250(int param_2)
{
  m10 = 2;
  m12 = 0x39;
  ((ConstructVariantFn_754250)FUN_0093dd80_754250)(this, 0x39, 0, param_2, 0x18, 1);
  return this;
}

// @ 0x007542b0
bool FUN_007542b0(int param_1, int param_2)
{
  void (FUN_00753fc0)(void*);
  if (param_2 != 0) {
    ++*(int*)(param_2 + 4);
    void* fn = *(void**)(param_1 + 0x24);
    void* a = *(void**)(param_1 + 0x20);
    *(int*)(param_1 + 0x20) = param_2;
    *(void**)(param_1 + 0x24) = (void*)&FUN_00753fc0;
    if (fn != 0) {
      ((void(__cdecl*)(void*))fn)(a);
    }
  } else {
    void* fn = *(void**)(param_1 + 0x24);
    void* a = *(void**)(param_1 + 0x20);
    *(void**)(param_1 + 0x20) = 0;
    *(void**)(param_1 + 0x24) = 0;
    if (fn != 0) {
      ((void(__cdecl*)(void*))fn)(a);
      return true;
    }
  }
  return true;
}

// @ 0x00754310
bool SP_RegisterModel_00754310(void* self, uint32_t id, uint32_t instance)
{
  Key key;
  key.a = id;
  key.b = 0xe6bce5;
  key.c = instance;
  Ref list;
  void* pm = PropertyManager();
  list.reset();
  if (!(char)vc3(pm, 0x2c, 0xf5895eae, 0x44a7f6af, (int)&list.p)) return false;
  if (!FUN_006acfe0_k(&key, self)) return false;
  Ref plr(new ("Graphics", 0, 0, 0, 0) cPropertyList());
  cPropertyList* pl = (cPropertyList*)plr.p;
  pl->SetParent(list.p);
  {
    Variant v;
    v.SetKey(&key);
    vc2(pl, 0x14, 0xf9efbb, (int)&v);
  }
  vc3(PropertyManager(), 0x34, (int)pl, id, instance);
  return true;
}

// @ 0x007544e0
void FUN_007544e0(void* src, uint32_t id, uint32_t instance)
{
  S_007544e0* m = new ("Graphics", 0, 0, 0, 0) S_007544e0();
  void* old = m->m138;
  if (src != old) {
    if (src) vc0(src, 0);
    m->m138 = src;
    if (old) vc0(old, 4);
  }
  vc2(src, 0x14, (int)m->m11c, (int)m->m134);
  SP_RegisterModel_00754310(m, id, instance);
}

// @ 0x007545b0
bool S_007545b0::FUN_007545b0(int param_2)
{
  int v = *(int*)(param_2 + 0x1c);
  if (v == 0) {
    if (m100 != 0) {
      FUN_006acfe0((char*)this + 0xf4, m100);
      int* slot = (int*)(*(int*)((char*)this + 0x44) + 0x13c);
      RefT_007545b0* piVar2 = m100;
      RefT_007545b0* piVar3 = (RefT_007545b0*)*slot;
      if (piVar2 != piVar3) {
        if (piVar2 != 0) piVar2->AddRef();
        *slot = (int)piVar2;
        if (piVar3 != 0) piVar3->Release();
      }
    }
  }
  return true;
}

// @ 0x00754620
bool FUN_00754620(uint32_t id, uint32_t instance)
{
  Ref list;
  void* pm = PropertyManager();
  list.reset();
  if ((char)vc3(pm, 0x2c, id, instance, (int)&list.p)) {
    void* pm2 = PropertyManager();
    vc1(pm2, 0x38, (int)list.p);
    Key k;
    k.a = 0;
    k.b = 0;
    k.c = 0;
    for (int i = 0; i < 4; i++) {
      if (GetPropertyAsKey(list.p, 0xf9efbb + i, &k)) FUN_006ad030(&k);
    }
    return true;
  }
  Key key;
  key.a = id;
  key.b = 0xe6bce5;
  key.c = instance;
  return FUN_006ad030(&key);
}

// @ 0x00754770
bool S_00754770::FUN_00754770(void* out)
{
  void* prov = m1c;
  if (prov && !m20) {
    Ref* r = (Ref*)&m20;
    r->reset();
    vc1(prov, 0x14, (int)&m20);
  }
  if (!m20) return false;
  ResPtr res(new ("Graphics", 0, 0, 0, 0) Res());
  bool ok;
  if (m10 == 0xe6bce5) {
    res.p->Attach(m20);
    ok = FUN_007542b0(out, res.p);
  } else if (m10 == 0x2f4e681b) {
    void* obj = m20;
    if (!(m18 & 1) && GetRwModelAsGameMeshesNoCache(obj)) {
      void* x = FUN_00759280(obj);
      Key k;
      k.a = m0c;
      k.b = m10;
      k.c = m14;
      k.b = 0xe6bce5;
      FUN_006acfe0_k(&k, x);
      SetCachingType(2, obj);
      SetCachingType(4, x);
      res.p->Attach(x);
      ok = FUN_007542b0(out, res.p);
    } else {
      SetCachingType(4, obj);
      if (!res.p->Load(obj)) return false;
      ok = FUN_007542b0(out, res.p);
    }
  } else {
    return false;
  }
  return ok;
}

// @ 0x00754960
bool FUN_00754960_impl(Key* key, Res** out, uint32_t flags)
{
  Ref ref;
  void* mgr = GetManager();
  ref.reset();
  if (!(char)vc6(mgr, 0x0c, (int)key, (int)&ref.p, 0, 0, 0, 0)) return false;
  ResPtr res(new ("Graphics", 0, 0, 0, 0) Res());
  if (key->b == 0xe6bce5) {
    res.p->Attach(ref.p);
  } else if (key->b == 0x2f4e681b) {
    void* obj = ref.p;
    if (!(flags & 1) && GetRwModelAsGameMeshesNoCache(obj)) {
      void* x = FUN_00759280(obj);
      Key k = *key;
      k.b = 0xe6bce5;
      FUN_006acfe0_k(&k, x);
      SetCachingType(2, obj);
      SetCachingType(4, x);
      res.p->Attach(x);
    } else {
      SetCachingType(4, obj);
      if (!res.p->Load(obj)) return false;
    }
  } else {
    return false;
  }
  *out = res.p;
  res.p->rc++;
  return true;
}

// @ 0x00754ba0
namespace SP {
bool CreateModelInstance(unsigned int a1, unsigned int a2, cModelInstance ** a3, unsigned int a4)
{
    int a3_v = (int)a3;
  struct K {
    int a;
    int b;
    int c;
  } k;
  k.a = a1;
  k.b = 0xe6bce5;
  k.c = a2;
  if (FUN_00754960(&k, (void*)a3_v, (void*)a4)) {
    return true;
  }
  k.b = 0x2f4e681b;
  return FUN_00754960(&k, (void*)a3_v, (void*)a4);
}
}  // namespace SP

// @ 0x00754c20
void S_00754c20::FUN_00754c20(cJob* job)
{
  uint32_t slot = job->mSlot;
  uint32_t n = (uint32_t)(mpEnd - mpBegin);
  if (slot < n) {
    void* srv = (void*)((void* (__cdecl*)())FUN_0067dd60)();
    if (!(m64 && srv) || (char)vc3(srv, 0x44, (int)mpBegin[slot], (int)m64, 1)) {
      job->mSlot = slot + 1;
      job->Continuation((void*)0x753fa0, this);
    }
  } else {
    job->Continuation((void*)0x754300, this);
  }
}

// @ 0x00754ca0
bool S_00754ca0::FUN_00754ca0(int)
{
  for (int i = 0; i < 4; i++) {
    if (m24[i] != 0.0f) {
      Key k;
      k.a = m0c;
      k.b = 0xe6bce5;
      k.c = m14[i];
      Variant v;
      v.data[0] = k.a;
      v.data[1] = k.b;
      v.data[2] = k.c;
      v.mTypeId = 0x20;
      v.mFlags = 0;
      vc2(m104, 0x14, 0xf9efbb + i, (int)&v);
    }
  }
  char* model = m44;
  if (model) {
    void* p = m104;
    {
      Variant tmp;
      Variant* r = ((Variant * (__thiscall*)(Variant*, void*)) 0x754250)(&tmp, model + 0x11c);
      vc2(p, 0x14, 0xf9efba, (int)r);
    }
    {
      Variant f;
      *(float*)&f.data[0] = *(float*)(model + 0x134);
      f.mTypeId = 0xd;
      f.mFlags = 2;
      vc2(m104, 0x14, 0xf9efb9, (int)&f);
    }
  }
  Mask5 mask;
  mask.d[0] = mask.d[1] = mask.d[2] = mask.d[3] = 0;
  mask.z = 0;
  for (int i = 0; i < 4; i++) {
    uint32_t bits = 0;
    Variant* pv;
    if (m104 && (char)vc2(m104, 0x24, 0x452027c + i, (int)&pv) && pv->mTypeId == 0xa) {
      uint32_t* q = (uint32_t*)pv;
      if (pv->mFlags & 0x30) q = *(uint32_t**)pv;
      bits = *q;
    }
    if (bits & 2) mask.d[i] = 0xffffffff;
  }
  Variant out;
  out.Set(9, 0x98, &mask, 4, 5);
  vc2(m104, 0x14, 0x60cbbef, (int)&out);
  Msg msg;
  msg.id = 0xf62def;
  msg.vtbl = vtbl_BehaviorMessage;
  msg.rc = 0;
  msg.vtbl = vtbl_MessageBasicRC5;
  msg.f38 = 0;
  char* plc = (char*)m104;
  msg.f08 = *(uint32_t*)(plc + 0xc);
  msg.f18 = *(uint32_t*)(plc + 8);
  msg.f10 = *(uint32_t*)(plc + 0x10);
  vc3(MessageServer(), 0x14, 0xf62def, (int)&msg, 0);
  msg.Destruct();
  return true;
}

// @ 0x007552e0
GlyphVec& GlyphVec::Assign(const GlyphVec& x)
{
  if (&x != this) {
    const unsigned nNewSize = (unsigned)(x.mpEnd - x.mpBegin);
    if (nNewSize > (unsigned)(mpCapacity - mpBegin)) {
      GlyphInfo* pNewData = DoRealloc(nNewSize, x.mpBegin, x.mpEnd);
      if (mpBegin && ((int*)mpBegin)[-1] != 0) delete[] mpBegin;
      mpBegin = pNewData;
      mpCapacity = pNewData + nNewSize;
      mpEnd = pNewData + nNewSize;
    } else if (nNewSize > (unsigned)(mpEnd - mpBegin)) {
      do_copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
      char sret[4];
      eastl_copy(sret, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, &x);
      mpEnd = mpBegin + nNewSize;
    } else {
      do_copy(x.mpBegin, x.mpEnd, mpBegin);
      mpEnd = mpBegin + nNewSize;
    }
  }
  return *this;
}

// @ 0x007553c0
void FUN_007553c0(void* self)
{ (void)self; }

// @ 0x00755470
void FUN_00755470(void* self)
{ (void)self; }

// @ 0x00755520
bool X_755520::FUN_00755520(cJob_755520* job)
{
  if (FUN_00754770(job)) {
    return true;
  }
  job->mThreadAffinity = 0x80000000;
  return job->Continuation((void*)&FUN_007553b0, this);
}

// @ 0x00755570
void V_755570::FUN_00755570(unsigned int param_2, int param_3)
{
  int* param_1 = (int*)this;
  int iVar2 = param_1[1];
  unsigned int uVar3 = (unsigned int)(iVar2 - *param_1) >> 2;
  if (uVar3 < param_2) {
    FUN_00429e00(iVar2, param_2 - uVar3, param_3);
    return;
  }
  int iVar1 = *param_1 + param_2 * 4;
  int uVar4 = FUN_006df700(iVar2, iVar2, iVar1);
  FUN_0059c410(uVar4, param_1[1]);
  param_1[1] = param_1[1] + ((iVar2 - iVar1 >> 2) * -4);
}

// @ 0x007555d0
void FUN_007555d0(void* self)
{ (void)self; }
