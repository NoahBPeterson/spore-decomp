// src/game/SPEngine/SPGraphicsModelUtilities.cpp -- migrated from slice(s) s007571a0, s00756280, s0042dee0, s004298f0, s007553c0, s00754310, s00753270, s00430ca0, s00430320, s0042d560, s004103c0 by tools/migrate/rewrite.py
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
#include <string.h>
#include <stddef.h>

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
extern "C" char GetPropertyAsFloatArray_ar(void* obj, int key, int* count, float** out); // 0x006a08b0
extern "C" char GetPropertyAsIntArray_ar(void* obj, int key, int* count, void** out);    // 0x006a07d0
extern "C" void* FUN_0072d5a0(void* a, int b, int c, int d, void* e);       // 0x0072d5a0
extern "C" void* FUN_00762250(void* a, void* b);                            // 0x00762250
extern "C" unsigned FUN_006c24b0_kd(void* a, void* b, void* c, int d,
                                        void* e, int f, const char* g);     // 0x006c24b0
extern "C" char SetCachingType_kd(int a, void* b);                      // 0x006ac040
extern "C" void __stdcall eh_vec_ctor_kd(void* p, unsigned sz, int n, void* ctor, void* dtor); // 0x011e0b85
extern "C" void __stdcall eh_vec_dtor_kd(void* p, unsigned sz, int n, void* dtor);             // 0x011e0b22
extern "C" void  BaseResourceDescriptor_ctor_kd(void* p);               // 0x006c0fa0
extern "C" void  ReadText_dtor_kd(void* p);                             // 0x00c2e4e0
void FUN_007387f0(void*);
void FUN_007389c0(void*, int);
void FUN_00738900(void*);
void FUN_006b4b60(void*, void*, int, int);
char FUN_0071ded0(int, int, void*, void*, void*, void*, int);
void FUN_00738610(int, int, void*);
void FUN_0093dd80_754250(int, int, int, int, int);
void* __cdecl operator_new_753d10(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
struct ARec_ar {
  float  f0;    // +0x00
  uint8_t m4;   // +0x04
  uint8_t m5;   // +0x05
  uint8_t m6;   // +0x06
  char   pad7;  // +0x07
};
struct RC_00753fc0 {
  void* p;
  volatile int n;
};
typedef void* (__thiscall* Fn762250_kd)(void* self, void* arg0);        // 0x00762250
struct KDTreeForeign_kd {
  virtual void kv0();
  virtual void kv1();
};
class Stub_754110 {
 public:
  char pad_0[0x64];
  void* m064;
  void* m068;
  bool FUN_00754110(int arg);
};
struct S_754250 {
  char pad_0[0x10];
  uint16_t m10;
  uint16_t m12;
  S_754250* FUN_00754250(int param_2);
};
typedef void (__thiscall* ConstructVariantFn)(void* self, int, int, int, int, int);
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
char FUN_007559a0(int, int, char);
void* GetManager_755d40();
void FUN_007553b0();
void FUN_00755560();
void FUN_00429e00(int, unsigned int, int);
int FUN_006df700(int, int, int);
void __stdcall FUN_0059c410(int, int);
void FUN_0041f320(void*, void*);
void FUN_007552e0(void*, void*);
char FUN_00754310(void*, int, int);
int FUN_00fc7e50(void*);
char FUN_0068f9f0(void*, void*, void*);   // cJob::Continuation
void FUN_006913c0(void*, void*);          // cJob::AddWeakDependency
void* FUN_007004d0(void*);
void FUN_0072c100(int, void*, int, int);
void* operator_new_f473a0(unsigned, const char*, int, int, int, int);
void operator_delete_f47380(void*);
struct Callee {
  void  v0();
  void  v1(void* a);
  void  v2(void* a, void* b);
  void  v3(void* a, void* b, void* c);
  void  v5(void* a, void* b, void* c, void* d, void* e);
  void  v8(void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h);
  void* p0();
  void* p1(void* a);
  char  c2(void* a, void* b);
  char  c3(void* a, void* b, void* c);
  char  c5(void* a, void* b, void* c, void* d, void* e);
  char  c6(void* a, void* b, void* c, void* d, void* e, void* f);
};
#define VTSLOT(p, off) ((*(void***)(p))[((off) / 4)])
struct TC1 { void FUN_0041f320(void* a); void FUN_007552e0(void* a); };
typedef void (__thiscall *PFN_v)(void*);
static inline void Add0(void* o) { if (o) ((PFN_v)(*(void***)o)[0])(o); }
static inline void Rel0(void* o) { if (o) ((PFN_v)(*(void***)o)[1])(o); }
static inline void Add4(void* o) { if (o) { void* b = (char*)o + 4; ((PFN_v)(*(void***)b)[0])(b); } }
static inline void Rel4(void* o) { if (o) { void* b = (char*)o + 4; ((PFN_v)(*(void***)b)[1])(b); } }
static inline void RefReleaseCore(void* o) {
  if (!o) return;
  volatile long* rc = (volatile long*)((char*)o + 4);
  long old = _InterlockedExchangeAdd(rc, -1);
  if (old == 1) {
    _InterlockedExchange(rc, 1);
    ((void(__thiscall*)(void*, int))(*(void***)o)[0])(o, 1);
  }
}
static inline void ClearRefVec(void** pBegin, void** pEnd) {
  void* r = (void*)FUN_006df700((int)*pEnd, (int)*pEnd, (int)*pBegin);
  FUN_0059c410((int)r, (int)*pEnd);
  *pEnd = *pBegin;
}
static inline void FreeBuffer(void* p) {
  if (p && *(int*)((char*)p - 4) != 0) operator_delete_f47380(p);
}
struct CS553 {
  void* mpV0;         // +0x00
  void* mpV1;         // +0x04
  int   mAtom;        // +0x08
  void* mpBegin;      // +0x0c
  void* mpEnd;        // +0x10
  void* mpCap;        // +0x14
  void* m18;          // +0x18
  void* m1c;          // +0x1c
  void* m20;          // +0x20
  void* mInline[16];  // +0x24 .. +0x63
  void* m64;          // +0x64
  void* m68;          // +0x68

  void ctor553(void* a1, void* a2);
  void dtor554();
  void f55c80(void* job);
};
class IFoo_755d40 {
 public:
  virtual void a0();
  virtual void a1();
  virtual void a2();
  virtual int a3(unsigned int id);
  virtual void a4();
  virtual void a5();
  virtual void a6();
  virtual void a7();
  virtual void a8(void*, int, int, int, int);
};
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
class S_755fe0 {
 public:
  char pad_0[0x104];
  IFoo_755d40* m104;  // +0x104
  int m108;           // +0x108
  void FUN_00755fe0(void* arg);
};
struct CMdl {
  uint32_t pad00[6];    // +0x00 .. +0x17
  void* m18;            // +0x18
  void* m1c;            // +0x1c
  uint32_t pad20[0x11]; // +0x20 .. +0x63
  void* m64;            // +0x64
  void* m68;            // +0x68
  uint32_t pad6c[0x1d]; // +0x6c .. +0xdf
  void* mE0;            // +0xe0
  uint32_t pade4[4];    // +0xe4 .. +0xf3
  void* mF4;            // +0xf4
  void* mF8;            // +0xf8
  uint32_t padfc[3];    // +0xfc .. +0x107
  void* m108;           // +0x108
  uint32_t pad10c[0xc]; // +0x10c .. +0x13b
  int   m13c;           // +0x13c
};
// ---- items of slice s007553c0 end

// ---- items of slice s004298f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedIncrement)
struct Alloc_s0042_98f0 { int unused; };
void* __cdecl AllocatorAllocate(Alloc_s0042_98f0* a, unsigned size, unsigned align, unsigned off);
struct tag { tag() {} };
struct Rec56 {
    uint32_t d[14];
    Rec56() {}
    Rec56(const Rec56& o) throw();            // 0x40ce80
    Rec56& operator=(const Rec56& o) throw(); // 0x537dc0
};
struct GIt {
    Rec56* mIterator;
    GIt(Rec56* const& x) : mIterator(x) {}
    Rec56& operator*() const { return *mIterator; }
    GIt& operator++() { ++mIterator; return *this; }
};
inline bool operator!=(GIt a, GIt b) { return a.mIterator != b.mIterator; }
void __cdecl FillN56(GIt first, unsigned n, const Rec56* value, tag);          // 0x42e680
Rec56* __cdecl UninitCopyA56(Rec56* first, Rec56* last, Rec56* dest);               // 0x42e510
inline void uninitialized_fill_n56(Rec56* first, uint32_t n, const Rec56& value)
{
    FillN56(GIt(first), n, &value, tag());
}
GIt __cdecl UninitCopyIt56(GIt first, GIt last, GIt dest, tag);  // 0x00429d80 (defined below; used by a stub's inline body)
inline void uninitialized_copy_it56(Rec56* first, Rec56* last, Rec56* result)
{
    const GIt i(UninitCopyIt56(GIt(first), GIt(last), GIt(result), tag()));
}
inline Rec56* copy_backward_impl56(Rec56* first, Rec56* last, Rec56* resultEnd)
{
    while (last != first) {
        --last;
        --resultEnd;
        *resultEnd = *last;
    }
    return resultEnd;
}
inline Rec56* copy_backward56(Rec56* first, Rec56* last, Rec56* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl56(first, last, resultEnd);
}
inline void fill56(Rec56* first, Rec56* last, const Rec56& value)
{
    for (; first != last; ++first)
        *first = value;
}
struct Vec56 {
    Rec56* mpBegin; Rec56* mpEnd; Rec56* mpCapacity; Alloc_s0042_98f0 mAllocator;
    inline Rec56* DoAllocate(uint32_t n) {
        return n ? (Rec56*)AllocatorAllocate(&mAllocator, n * sizeof(Rec56), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (((uint32_t*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); }
    }
    inline void DoFree(Rec56* p, uint32_t n) { if (p) deallocate(p, n * sizeof(Rec56)); }
    void DoInsertValues(Rec56* position, uint32_t n, const Rec56& value);
};
struct ThreadedObject_s0042_98f0 {
    void* vtable; volatile long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();
};
struct Ref_s0042_98f0 {
    ThreadedObject_s0042_98f0* p;
    Ref_s0042_98f0(const Ref_s0042_98f0& o) : p(o.p) { if (p) p->AddRef(); }
    ~Ref_s0042_98f0() { if (p) p->Release(); }
    Ref_s0042_98f0& operator=(ThreadedObject_s0042_98f0* x);       // 0x41d8b0
};
struct GRef {
    Ref_s0042_98f0* mIterator;
    GRef(Ref_s0042_98f0* const& x) : mIterator(x) {}
};
GRef __cdecl UninitMoveRef(GRef first, GRef last, GRef dest, tag);       // 0x47c800
void __cdecl FillNRef(GRef first, unsigned n, Ref_s0042_98f0* value, tag);          // 0x42e7e0
Ref_s0042_98f0* __cdecl UninitCopyRefs(Ref_s0042_98f0* first, Ref_s0042_98f0* last, Ref_s0042_98f0* dest);           // 0x423f50
void __cdecl FillRef(Ref_s0042_98f0* first, Ref_s0042_98f0* last, Ref_s0042_98f0* value);                  // 0x42d430
inline void uninitialized_copy_it(Ref_s0042_98f0* first, Ref_s0042_98f0* last, Ref_s0042_98f0* result)
{
    UninitMoveRef(GRef(first), GRef(last), GRef(result), tag());
}
inline void uninitialized_fill_n_ref(Ref_s0042_98f0* first, uint32_t n, Ref_s0042_98f0* value)
{
    FillNRef(GRef(first), n, value, tag());
}
inline Ref_s0042_98f0* copy_backward_impl(Ref_s0042_98f0* first, Ref_s0042_98f0* last, Ref_s0042_98f0* resultEnd)
{
    while (last != first) {
        --last;
        --resultEnd;
        *resultEnd = last->p;
    }
    return resultEnd;
}
inline Ref_s0042_98f0* copy_backward_r(Ref_s0042_98f0* first, Ref_s0042_98f0* last, Ref_s0042_98f0* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}
inline Ref_s0042_98f0* copy_memcpy(Ref_s0042_98f0* first, Ref_s0042_98f0* last, Ref_s0042_98f0* result)
{
    return (Ref_s0042_98f0*)memcpy(result, first, (uint32_t)((char*)last - (char*)first)) + (last - first);
}
inline Ref_s0042_98f0* uninitialized_copy_ptr(Ref_s0042_98f0* first, Ref_s0042_98f0* last, Ref_s0042_98f0* result)
{
    const bool bA = true;
    Ref_s0042_98f0* p = copy_memcpy(first, last, result);
    const bool bB = true;
    return p;
}
struct RefVector {
    Ref_s0042_98f0* mpBegin; Ref_s0042_98f0* mpEnd; Ref_s0042_98f0* mpCapacity; Alloc_s0042_98f0 mAllocator;
    inline Ref_s0042_98f0* DoAllocate(uint32_t n) {
        return n ? (Ref_s0042_98f0*)AllocatorAllocate(&mAllocator, n * sizeof(Ref_s0042_98f0), 4, 0) : 0;
    }
    inline void deallocate(void* p, uint32_t n) {
        if (((uint32_t*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); }
    }
    inline void DoFree(Ref_s0042_98f0* p, uint32_t n) { if (p) deallocate(p, n * sizeof(Ref_s0042_98f0)); }
    void DoInsertN(Ref_s0042_98f0* position, uint32_t n, Ref_s0042_98f0* value);
};
// ---- items of slice s004298f0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
Rec56* __cdecl UninitCopy56(Rec56* first, Rec56* last, Rec56* dest);  // 0x00429ce0 (stays in the slice: not this object's)

// ---- items of slice s0042dee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static const char kEastlAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
void* __cdecl EASTL_allocator_allocate(size_t n, const char* name, int flags, int a, const char* file, int line);        // 0x00F473A0
void* __cdecl EASTL_allocator_allocate_aligned(size_t n, size_t align, size_t off, const char* name, int flags, int a, const char* file, int line); // 0x00F473D0
struct Elem12 { uint32_t a, b, c; };
struct Elem12List {
    uint32_t pad[6];
    uint32_t allocator;               // +0x18
    struct Node { uint32_t links[4]; Elem12 value; };   // 0x1C bytes
    Node* AllocateNode(const Elem12& v);
};
// ---- items of slice s0042dee0 end

// ---- items of slice s00756280 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd)
void* operator new(unsigned int, const char*, int, unsigned int, unsigned int, int);   // 0x00f473a0
int   FUN_0071ddc0(void* self, int a, int b, int c, int d);
int   FUN_0071dd80(void* self, int a);
void  FUN_00720190(int n, int sz, void* out);
void* FUN_0072c0a0(void* a, void* b, int c, void* d);
char  FUN_006ac040(int a, void* b);            // SP::SetCachingType
char  FUN_006acfe0(unsigned int* s, char* obj);
void* FUN_006df700(void* a, void* b, void* c);
void  FUN_00753dc0(void* holder, int flags);
void  FUN_00753fe0(void** dst, void* src);
struct Ext {
  void   FUN_0041ee90(unsigned int);           // RefVector::resize
  void   FUN_006df280(void*);                  // RefPtr::AssignRefPtr
  void   FUN_0041d8b0(void*);
  void** FUN_00742f60(void const*);            // Map8::GetOrAdd
  void*  FUN_011edcf0(int);                    // D3D9GetShaderData
  void   FUN_00755570(unsigned int, int);      // V_755570::FUN_00755570
  void   FUN_0041f320(void*);                  // Vec_Elem7c_operator_assign
  void*  FUN_007552e0(void*);                  // GlyphVec::Assign
  void   FUN_0041f7d0(void*);                  // Vec_Elem20_push_back
  void*  FUN_004728e0(void*);
  void   FUN_00424f70(void*);                  // Handle_Assign
  int    FUN_00690120();                       // cJob::Release
  int    FUN_0068f950();                       // cJob::AddRef
  int    FUN_006909b0();                       // cJob::GetStatus
  int    FUN_00768530();                       // CB24::AddRef (refcount at +8)
  int    FUN_0067da30();                       // CB24::Release
  int    FUN_00432be0();                       // Obj140::AddRef (refcount at +4)
  int    FUN_00763250();                       // Obj140::Release
  void   FUN_0068f9b0(void*);                  // cJob::sub_68f9b0
  void   FUN_006913c0(void*);                  // cJob::AddWeakDependency
  bool   FUN_0068f9f0(void*, void*);           // cJob::Continuation
  void   FUN_0059c410(void*, void*);           // ReleaseAutoRefRange (ecx = &range)
};
struct IObject_s0075_6280 {
  virtual int AddRef();
  virtual int Release();
};
struct PartHolder {
  virtual void vfunc(int);
  int mRefCount;                        // +0x04
  char pad_08[0x58 - 8];
  PartHolder(PartHolder const* other);  // 0x0040f070
};
struct cJobRef;
struct cJob_s0075_6280 {
  void (*mpCallback)(void*);    // +0x00
  void* mpCallbackData;         // +0x04
  char pad_08[0x10];
  int mFlags;                   // +0x18
  int mSlot;                    // +0x1c
};
struct cJobRef {
  cJob_s0075_6280* p;
  cJobRef() : p(0) {}
  cJobRef(cJobRef const& o) {
    p = o.p;
    if (p) ((Ext*)p)->FUN_0068f950();
  }
  ~cJobRef() { if (p) ((Ext*)p)->FUN_00690120(); }
  cJobRef& operator=(const cJobRef& o) {
    cJob_s0075_6280* t = o.p;
    if (t != p) {
      if (t) ((Ext*)t)->FUN_0068f950();
      cJob_s0075_6280* old = p;
      p = t;
      if (old) ((Ext*)old)->FUN_00690120();
    }
    return *this;
  }
};
class X_7565a0 {
 public:
  virtual void a0();
  virtual void a1();
  virtual void a2(int);
  char pad_0[0x6c - 4];
  X_7565a0(int, int);
  bool FUN_007564b0(cJobRef* out);
};
struct CModelRegion {
  char pad_00[0x0c];
  int  mField0c;          // +0x0c
  char pad_10[0x04];
  int  mSlotInt;          // +0x14  (array, stride 4)
  char pad_18[0x0c];
  float mSlotFloat;       // +0x24  (array, stride 4)
  char pad_28[0x0c];
  int  mSlotFlags;        // +0x34  (array, stride 4)
  char pad_38[0x0c];
  void* mSlotJob;         // +0x44  (array of IObject*, stride 4)
  char pad_48[0x0c];
  char mMeshCtx;          // +0x54
  char pad_55[0x2f];      // -> +0x84
  void** mpPtr84;         // +0x84
  char pad_88[0x10];      // -> +0x98
  int  mField98;          // +0x98
  char pad_9c[0x14];      // -> +0xb0
  char mFieldB0;          // +0xb0
  char pad_b1[0x03];
  void* mSlotHolder;      // +0xb4  (array of PartHolder*, stride 4)
  char pad_b8[0x0c];      // -> +0xc4
  char mFieldC4;          // +0xc4
  char mFieldC5;          // +0xc5
  char pad_c6[0x02];
  char mVecC8;            // +0xc8
  char pad_c9[0x13];      // -> +0xdc
  char mGlyphDC;          // +0xdc
  char pad_dd[0x03];      // -> +0xe0
  char mGlyphE0;          // +0xe0
  char pad_e1[0x13];      // -> +0xf4
  char mVecF4;            // +0xf4
  char pad_f5[0x0b];      // -> +0x100
  void* mp100;            // +0x100
  void* mField108;        // +0x108

  bool FUN_00756a20(cJob_s0075_6280* job);
  bool FUN_00756b50(cJob_s0075_6280* job);
  bool FUN_00756c70(cJob_s0075_6280* job);
  bool FUN_00756d80(cJob_s0075_6280* job);
};
struct Obj140 {
  void* mpVtbl;               // +0x00  (0x0140c464)
  int   mRefCount;            // +0x04
  char pad_08[0x18 - 8];
  void* mVecBegin18;          // +0x18
  void* mVecEnd1c;            // +0x1c
  char pad_20[0xf4 - 0x20];
  char mVecF4;                // +0xf4
  char pad_f5[0x13];          // -> +0x108
  char mVec108;               // +0x108
  char pad_109[0x37];         // -> +0x140
  Obj140* FUN_007004d0();     // 0x007004d0
};
struct VObj {
  virtual void AddRef();
  virtual void Release();
};
struct Obj140Ref {
  Obj140* p;
  Obj140Ref(Obj140* o) : p(o) { if (p) ((VObj*)p)->AddRef(); }
  ~Obj140Ref() { if (p) ((VObj*)p)->Release(); }
};
struct Tmp56280 {
  int   a;      // +0x00
  int   b;      // +0x04
  int   c;      // +0x08
  int   d;      // +0x0c
  int   e;      // +0x10
  void* base;   // +0x14
  uint16_t g;   // +0x18
  uint16_t stride;  // +0x1a
  void* p;      // +0x1c
};
struct Slot7562 {
  int   m10;       // +0x00
  int   m14;       // +0x04
  uint16_t m18;    // +0x08
  uint16_t m1a;    // +0x0a
  IObject_s0075_6280* mpRef;  // +0x0c
};
struct F3 {
  int a;   // +0
  int b;   // +4
  int c;   // +8
  F3& operator=(F3 const& o) { a = o.a; b = o.b; c = o.c; return *this; }
};
struct IntVecObj {
  IntVecObj(int a, int const* b);       // 0x00723720
};
// ---- items of slice s00756280 end

// ---- items of slice s007571a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl eh_vec_ctor_006c0fa0(void* p, unsigned sz, unsigned n, void* ctor);
extern "C" void  __cdecl eh_vec_dtor(void* p, unsigned sz, unsigned n, void* dtor);
extern char FUN_00757390, FUN_00754fe0, FUN_007564a0, FUN_00757170, FUN_00757180, FUN_00757190, FUN_00754c00, FUN_00756b40;
struct RCObj;
struct RCObj { void* vptr; long refcount; };
static inline void RCAddRef(RCObj* p) {
    if (p) _InterlockedIncrement(&p->refcount);
}
struct Arena {
    int  GetNumExportedObjects();
    void GetExportedObjectByIndex(int i, void* out);
};
struct ArenaHolder { char pad[0x18]; Arena* pArena; };
typedef unsigned int u32;
void* operator new(unsigned size, const char* name, int flags, unsigned dbg, const char* file, int line);   // 0x00f473a0
struct MeshJob;
struct cJob_s0075_71a0 {
    void* mpCallback;       // +0x00
    void* mpCallbackData;   // +0x04
    char  pad08[0x10];
    u32   mThreadAffinity;  // +0x18
    int   mSlot;            // +0x1c
    u32   pad20[2];
    void AddRef();                  // 0x0068f950
    void Release();                 // 0x00690120
    void SetExtra(void* obj);       // 0x0068f9b0 (ret 4)
    void After(cJob_s0075_71a0* prev);         // 0x00691380 (ret 4)
    void Submit();                  // 0x006909b0
};
struct JobRef {
    cJob_s0075_71a0* p;
    JobRef() : p(0) {}
    JobRef(cJob_s0075_71a0* q) : p(q) { if (p) p->AddRef(); }
    ~JobRef() { if (p) p->Release(); }
    JobRef& operator=(const JobRef& o)
    {
        if (o.p != p) {
            cJob_s0075_71a0* old = p;
            if (o.p) o.p->AddRef();
            p = o.p;
            if (old) old->Release();
        }
        return *this;
    }
    cJob_s0075_71a0** operator&() { if (p) { cJob_s0075_71a0* o = p; p = 0; o->Release(); } return &p; }
    cJob_s0075_71a0* operator->() const { return p; }
};
struct Property {
    void* data;             // +0x00 (inline value or pointer)
    u32   pad04[3];
    u32   flags;            // +0x10
    short type;             // +0x12 is the high half of flags
};
struct PropList {
    virtual void AddRef();
    virtual void Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual bool GetProperty(u32 id, Property** out);   // 0x24
    void SetParent(PropList* parent);                    // 0x006a1710 (ret 4)
};
struct cPropertyList_s0075_71a0 : PropList {
    u32 pad04[13];                                       // sizeof == 0x38
    cPropertyList_s0075_71a0();                                     // 0x006a1c40
};
struct PropMgr {
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
    virtual bool GetPropList(u32 a, u32 b, PropList** out);       // 0x2c
    virtual void v30();
    virtual void RegisterPropList(PropList* l, u32 a, u32 b);     // 0x34
};
PropMgr* GetPropMgr();      // 0x0067de30
extern PropList* g_AppProperties;   // 0x015fd918
struct JobMgr {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual bool CreateJob(cJob_s0075_71a0** out);     // 0x10
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void Begin();                   // 0x20
    virtual void End();                     // 0x24
};
JobMgr* GetJobMgr();        // 0x0068f4d0
template <class T> struct ARC {
    T* p;
    ARC(T* q) : p(q) { if (p) p->AddRef(); }
    ~ARC() { if (p) p->Release(); }
    T** operator&() { if (p) { T* o = p; p = 0; o->Release(); } return &p; }
    T* operator->() const { return p; }
    ARC& operator=(T* q)
    {
        T* old = p;
        if (q != old) {
            if (q) q->AddRef();
            p = q;
            if (old) old->Release();
        }
        return *this;
    }
};
struct VecA {
    void Assign(const VecA* src);   // 0x0041ebe0 (ret 4)
};
struct VecB {
    void Assign(const void* src);   // 0x0041f320 (ret 4)
};
struct VecC {
    void Assign(const void* src);   // 0x007552e0 (ret 4)
};
void CopyProps6(PropList* list, void* dst, int n);    // 0x00753e00 (cdecl)
struct Sub4 { void* vptr; };   // second base at +4 of the arg10 object
struct SubRef {
    Sub4* p;
    SubRef& operator=(Sub4* q)
    {
        Sub4* old = p;
        if (q != old) {
            if (q) ((void(__thiscall*)(void*))(*(void***)((char*)q + 4))[0])((char*)q + 4);
            p = q;
            if (old) ((void(__thiscall*)(void*))(*(void***)((char*)old + 4))[1])((char*)old + 4);
        }
        return *this;
    }
};
static inline void RCRelease2(RCObj* p) {
    if (p && _InterlockedDecrement(&p->refcount) == 0) {
        _InterlockedExchange(&p->refcount, 1);
        ((void (__thiscall*)(RCObj*, int))(*(void***)p)[0])(p, 1);
    }
}
struct MeshJob {
    virtual void AddRef();
    virtual void Release();
    void* vptr2;            // +0x04
    char  pad08[4];
    u32   mId3;             // +0x0c
    u32   mId4;             // +0x10
    u32   mIds[4];          // +0x14
    float mSlotWeight[4];   // +0x24
    int   mSlotInt[4];      // +0x34
    char  pad44[0x10];
    u32   mProps[6];        // +0x54
    char  pad6c[0x84 - 0x6c];
    VecA  mVec84;           // +0x84
    char  pad85[0x14 - 1];
    RCObj* mp98;            // +0x98
    VecA  mVec9c;           // +0x9c
    char  pad9d[0x14 - 1];
    bool  mbB0;             // +0xb0
    char  padB1[0xc4 - 0xb1];
    bool  mbC4;             // +0xc4
    bool  mbC5;             // +0xc5
    char  padC6[2];
    VecB  mVecC8;           // +0xc8
    char  padC9[0x14 - 1];
    VecC  mVecDc;           // +0xdc
    char  padDd[0x14 - 1];
    bool  mbF0;             // +0xf0
    char  padF1[3];
    u32   mKey[3];          // +0xf4
    char  padOth[0x104 - 0x100];
    PropList* mpList;       // +0x104
    SubRef mSub108;         // +0x108
    MeshJob();              // 0x00755070 (thiscall, returns this)
};
struct Key12 { u32 a, b, c; };
// ---- items of slice s007571a0 end

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

// @ 0x004298f0
void Vec56::DoInsertValues(Rec56* position, uint32_t n, const Rec56& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Rec56 temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Rec56* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_it56(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward56(position, pEnd - n, pEnd);
                fill56(position, position + n, temp);
            } else {
                uninitialized_fill_n56(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                UninitCopyA56(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill56(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Rec56* const pNewData = DoAllocate(nNewSize);
        Rec56* pNewEnd = UninitCopy56(mpBegin, position, pNewData);
        uninitialized_fill_n56(pNewEnd, n, value);
        pNewEnd = UninitCopy56(position, mpEnd, pNewEnd + n);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00429e00
void RefVector::DoInsertN(Ref_s0042_98f0* position, uint32_t n, Ref_s0042_98f0* value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Ref_s0042_98f0 temp(*value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            Ref_s0042_98f0* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_it(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_r(position, pEnd - n, pEnd);
                FillRef(position, position + n, (Ref_s0042_98f0*)&temp);
            } else {
                uninitialized_fill_n_ref(mpEnd, n - nExtra, (Ref_s0042_98f0*)&temp);
                mpEnd += n - nExtra;
                UninitCopyRefs(position, pEnd, mpEnd);
                mpEnd += nExtra;
                FillRef(position, pEnd, (Ref_s0042_98f0*)&temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Ref_s0042_98f0* const pNewData = DoAllocate(nNewSize);
        Ref_s0042_98f0* pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        uninitialized_fill_n_ref(pNewEnd, n, value);
        pNewEnd = uninitialized_copy_ptr(position, mpEnd, pNewEnd + n);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
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

// @ 0x0042dee0
void* EASTL_Allocate(void* /*allocator*/, size_t n, size_t align, size_t offset)
{
    void* p;
    void* q;
    if (align <= 8) {
        p = EASTL_allocator_allocate(n, "Editor", 0, 0, kEastlAllocatorFile, 0xd1);
        return p;
    }
    q = EASTL_allocator_allocate_aligned(n, align, offset, "Editor", 0, 0, kEastlAllocatorFile, 0xe5);
    return q;
}

// @ 0x0042e290
Elem12List::Node* Elem12List::AllocateNode(const Elem12& v)
{
    Node* node = (Node*)EASTL_Allocate(&allocator, 0x1c, 4, 0);
    ::new(&node->value) Elem12(v);
    return node;
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

// @ 0x00753dc0
void FUN_00753dc0(int param_1, unsigned char param_2)
{
  if ((param_2 & 2) != 0) {
    FUN_007387f0((void*)param_1);
  } else if ((param_2 & 4) != 0) {
    FUN_007389c0((void*)param_1, 1);
  }
  if ((param_2 & 8) != 0) {
    FUN_00738900((void*)param_1);
  }
}

// @ 0x00753e00
void FUN_00753e00(void* propSet, ARec_ar* dst, int n)
{
  {
    int    count;
    float* src;
    if (GetPropertyAsFloatArray_ar(propSet, 0x61b99cd, &count, &src)) {
      if (n < count)
        count = n;
      for (int i = 0; i < count; ++i)
        dst[i].f0 = src[i];
      for (int i = count; i < n; ++i)   // fill remainder from src[0]
        dst[i].f0 = src[0];
    }
  }
  {
    int    count;
    void*  src;
    if (GetPropertyAsIntArray_ar(propSet, 0x61b99ce, &count, &src)) {
      if (n < count)
        count = n;
      for (int i = 0; i < count; ++i)
        dst[i].m5 = *(uint8_t*)((char*)src + i * 4);
      for (int i = count; i < n; ++i)
        dst[i].m5 = *(uint8_t*)src;
    }
  }
  {
    int    count;
    void*  src;
    if (GetPropertyAsIntArray_ar(propSet, 0x61b99cf, &count, &src)) {
      if (n < count)
        count = n;
      for (int i = 0; i < count; ++i) {
        const int v = *(int*)((char*)src + i * 4);
        dst[i].m4 = (uint8_t)(v >> 3);
        dst[i].m6 = (uint8_t)(v & 7);
      }
      for (int i = count; i < n; ++i) {
        const int v = *(int*)src;
        dst[i].m4 = (uint8_t)(v >> 3);
        dst[i].m6 = (uint8_t)(v & 7);
      }
    }
  }
}

// @ 0x00753fc0
void FUN_00753fc0(RC_00753fc0* param_1)
{
  int n = (param_1->n += -1);
  if (n == 0) {
    param_1->n = 1;
    // vtable slot 0 (deleting dtor) called thiscall on the record itself: the original's `ecx`
    // at the call is `this`, not a register-allocation choice (hybrid 2026-10-12).
    typedef void(__thiscall *Fn)(RC_00753fc0*, int);
    Fn fn = *(Fn*)param_1->p;
    fn(param_1, 1);
  }
}

// @ 0x00753fe0
void FUN_00753fe0(void* param_1, void* param_2)
{
  // The original zeroes the first six dwords with individual stores; MSVC folds
  // any zero-init here into a memset whose stack cleanup it then mis-emits, so
  // leave the scratch block uninitialised and let the EH vector ctor below fill
  // the descriptor array at +0x18.
  char local[0x44];
  void* const arg_dst = param_1;   // snapshot args before any frame-shifting call
  void* const arg_src = param_2;

  eh_vec_ctor_kd((char*)local + 0x18, 8, 4, (void*)BaseResourceDescriptor_ctor_kd,
                     (void*)ReadText_dtor_kd);

  char* loc = (char*)local;
  void* res = (void*)FUN_0072d5a0(arg_src, 0, 0, 0x10, loc);
  if (res != 0) {
    void* mem = operator_new_753d10(0x4c, "Graphics", 0, 0, 0, 0);
    KDTreeForeign_kd* kd = 0;
    if (mem != 0)
      kd = (KDTreeForeign_kd*)((Fn762250_kd)FUN_00762250)((void*)mem, loc);
    if (kd != 0)
      (*(void(__thiscall**)(KDTreeForeign_kd*))(*(void***)kd)[0])(kd);

    FUN_006c24b0_kd(arg_dst, kd, loc, 1, loc, 1, "RenderAsset/KDTree");
    SetCachingType_kd(2, *(void**)arg_dst);
    if (kd != 0)
      (*(void(__thiscall**)(KDTreeForeign_kd*))(*(void***)kd)[1])(kd);
  }

  eh_vec_dtor_kd(loc + 0x18, 8, 4, (void*)ReadText_dtor_kd);
}

// @ 0x00754110
bool Stub_754110::FUN_00754110(int arg)
{
  FUN_006b4b60(m068, m064, 0, 0);
  return true;
}

// @ 0x007541b0
void FUN_007541b0(int param_1, int param_2, int param_3)
{
  int found[2] = { -1, -1 };
  int limits[2] = { 2, 2 };
  int keys[2] = { param_2, param_3 };
  int span[2] = { 8, 8 };
  char c = (char)FUN_0071ded0(param_1, 2, found, span, keys, limits, 0);
  if (c != 0) {
    *(int*)(found[1] * 0x20 + 4 + *(int*)(param_1 + 8)) = param_2;
    FUN_00738610(param_1, 1, found);
    return;
  }
  if (found[1] >= 0) {
    *(int*)(found[1] * 0x20 + 4 + *(int*)(param_1 + 8)) = param_2;
  }
}

// @ 0x00754250
S_754250* S_754250::FUN_00754250(int param_2)
{
  m10 = 2;
  m12 = 0x39;
  ((ConstructVariantFn)FUN_0093dd80_754250)(this, 0x39, 0, param_2, 0x18, 1);
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
void CS553::ctor553(void* a1, void* a2)
{
  mpV0 = (void*)0x13f1ab0;
  mpV1 = (void*)0x13ef094;
  _InterlockedExchange((volatile long*)&mAtom, 0);
  mpV0 = (void*)0x140d9d8;
  mpV1 = (void*)0x140d9d4;
  void* base = &mInline[0];
  mpBegin = base;
  mpEnd = base;
  m20 = 0;
  mpCap = (void*)((char*)this + 0x64);
  m64 = a2;
  Add4(a2);
  m68 = a1;
  Add0(a1);
}

// @ 0x00755470
void CS553::dtor554()
{
  Rel0(m68);
  Rel4(m64);
  ((Callee*)&mpBegin)->v2(mpBegin, mpEnd);
  FreeBuffer(mpBegin);
  mpV1 = (void*)0x13ef094;
  mpV0 = (void*)0x13eb938;
}

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
  unsigned int uVar3 = (unsigned int)((iVar2 - *param_1) >> 2);
  if (uVar3 < param_2) {
    ((void (__thiscall*)(void*, int, unsigned int, int))FUN_00429e00)(this, iVar2, param_2 - uVar3, param_3);
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

// @ 0x00755810
char FUN_00755810(int a1, int a2, int a3, void* a4, int a5, int a6)
{
  CMdl* obj = 0;
  void* mem = operator_new_f473a0(0x140, "Graphics", 0, 0, 0, 0);
  if (mem) obj = (CMdl*)FUN_007004d0(mem);
  Add0(obj);
  FUN_0072c100(a1, obj, -1, 0);
  if (a4) {
    ClearRefVec(&obj->mF4, &obj->mF8);
    void* ref = a4;
    _InterlockedExchangeAdd((volatile long*)((char*)ref + 4), 1);
    int cnt = (int)(((char*)obj->m1c - (char*)obj->m18) >> 2);
    ((V_755570*)((char*)obj + 0xf4))->FUN_00755570((unsigned)cnt, (int)ref);
    RefReleaseCore(ref);
  }
  if (a5) ((TC1*)((char*)obj + 0x108))->FUN_0041f320((void*)a5);
  if (a6) ((TC1*)((char*)obj + 0xe0))->FUN_007552e0((void*)a6);
  char r = FUN_00754310(obj, a2, a3);
  Rel0(obj);
  return r;
}

// @ 0x00755c80
void CS553::f55c80(void* job)
{
  void* mgr = GetManager_755d40();
  if (m20) { void* p = m20; m20 = 0; Rel0(p); }
  if (m1c) { void* p = m1c; m1c = 0; Rel0(p); }
  ((void(__thiscall*)(void*, void*, void*, void*, void*, void*, void*, void*, void*))VTSLOT(mgr, 0x10))
      (mgr, &mpBegin, &m1c, &m20, 0, 0, 0, 0, 0);
  void* r = m1c;
  if (r) {
    void* n = ((void*(__thiscall*)(void*, void*))VTSLOT(r, 0xc))(r, (void*)0x3a212ac);
    if (n) {
      int t = FUN_00fc7e50(n);
      FUN_006913c0(job, (void*)t);
    }
  }
  *(int*)((char*)job + 0x18) = 1;
  FUN_0068f9f0(job, (void*)FUN_00755560, this);
}

// @ 0x00755fe0
void S_755fe0::FUN_00755fe0(void* arg)
{
  (void)arg;
  GetManager_755d40();
  int uVar1 = m108;
  IFoo_755d40* piVar2 = m104;
  if (piVar2 != 0) {
    int iVar3 = piVar2->a3(0xe6bce5);
    if (iVar3 != 0) {
      FUN_007559a0(iVar3, uVar1, 1);
      return;
    }
  }
  FUN_006b4b60(piVar2, (void*)uVar1, 0, 0);
}

// @ 0x00756280
void FUN_00756280(int* self, uint32_t value)
{
  int idx = FUN_0071ddc0(self, 0x15, 0, 6, 8);
  if (idx < 0) {
    int n = FUN_0071dd80(self, 8);
    if (n == 0) {
      int cnt = (*(int*)((char*)self + 0x34) - *(int*)((char*)self + 0x30)) / 0x14;
      n = 0;
      if (cnt > 0) {
        int* p = (int*)(*(int*)((char*)self + 0x30) + 0x10);
        do {
          if (n < *p) n = *p;
          p = (int*)((char*)p + 0x14);
          cnt--;
        } while (cnt != 0);
      }
      n = n + 1;
    }
    Tmp56280 tmp;
    tmp.a = 0x15; tmp.b = 0; tmp.c = 6; tmp.d = 8;
    tmp.e = 0; tmp.base = 0; tmp.g = 0; tmp.stride = 0; tmp.p = 0;
    FUN_00720190(n, 4, &tmp.e);
    for (int i = 0; i < n; i++) {
      int off = (uint32_t)tmp.stride * i;
      *(uint32_t*)(off + (int)tmp.base) = value;
    }
    ((Ext*)((char*)self + 8))->FUN_0041f7d0(&tmp);   // vector push_back
    if (tmp.p) ((IObject_s0075_6280*)tmp.p)->Release();
  } else {
    char* rec = (char*)(*(int*)((char*)self + 8)) + idx * 0x20;
    int f10 = *(int*)(rec + 0x10);
    IObject_s0075_6280* ref = *(IObject_s0075_6280**)(rec + 0x1c);
    if (ref) ref->AddRef();
    uint32_t v = value;
    IntVecObj* iv = new ("Graphics", 0, 0, 0, 0) IntVecObj(f10, (int const*)&v);
    Slot7562 buf;
    ((Ext*)iv)->FUN_004728e0(&buf);
    ((Ext*)(rec + 0x10))->FUN_00424f70(&buf);
    if (buf.mpRef) buf.mpRef->Release();
    if (ref) ref->Release();
  }
}

// @ 0x007565a0
bool FUN_007565a0(int param_1, int param_2, cJobRef* param_3)
{
  if (param_1 != 0 && param_2 != 0) {
    X_7565a0* p = new ("Graphics", 0, 0, 0, 0) X_7565a0(param_1, param_2);
    if (p != 0) {
      if (p->FUN_007564b0(param_3)) {
        return 1;
      }
      p->a2(1);
    }
  }
  return 0;
}

// @ 0x00756c70
bool CModelRegion::FUN_00756c70(cJob_s0075_6280* job)
{
  int slot = job->mSlot;
  void** pslot = (void**)((char*)this + 0xb4 + slot * 4);
  void* cur = *pslot;
  if (cur == 0) {
    if (*(int*)((char*)this + 0x34 + slot * 4) == 0) {
      ((Ext*)pslot)->FUN_006df280(*(void**)((char*)this + 0x84));
    } else {
      PartHolder* ph = new ("Graphics", 0, 0, 0, 0)
          PartHolder(*(PartHolder**)*(void**)((char*)this + 0x84));
      ((Ext*)pslot)->FUN_0041d8b0(ph);
      FUN_00753dc0(*pslot, *(int*)((char*)this + 0x34 + slot * 4));
    }
  }
  void* h = *pslot;
  void** p100 = (void**)((char*)this + 0x100);
  if (*p100) {
    IObject_s0075_6280* t = (IObject_s0075_6280*)*p100;
    *p100 = 0;
    t->Release();
  }
  FUN_00753fe0(p100, h);
  void* d = *p100;
  if (d) {
    *(F3*)((char*)d + 8) = *(F3*)((char*)this + 0xf4);
  }
  return true;
}

// @ 0x00756d80
bool CModelRegion::FUN_00756d80(cJob_s0075_6280* job)
{
  Obj140* p = 0;
  void** pslot = (void**)((char*)this + 0xb4 + job->mSlot * 4);
  if (*pslot == 0) {
    if (*(int*)((char*)this + 0x34 + job->mSlot * 4) == 0) {
      ((Ext*)pslot)->FUN_006df280(*(void**)((char*)this + 0x84));
    } else {
      void* P = *(void**)((char*)this + 0x84);
      PartHolder* ph = new ("Graphics", 0, 0, 0, 0) PartHolder(*(PartHolder**)P);
      ((Ext*)pslot)->FUN_0041d8b0(ph);
      FUN_00753dc0(*pslot, *(int*)((char*)this + 0x34 + job->mSlot * 4));
    }
  }
  p = new ("Graphics", 0, 0, 0, 0) Obj140;
  if (p) p = p->FUN_007004d0();
  Obj140Ref obj(p);
  FUN_006ac040(4, obj.p);
  void* ctx;
  if (mFieldB0 == 0) ctx = 0;
  else ctx = (char*)this + 0x9c;
  FUN_0072c0a0(*pslot, obj.p, -1, ctx);
  if (mField98 != 0) {
    int a = *(int*)((char*)obj.p + 0xf4);
    int b = *(int*)((char*)obj.p + 0xf8);
    void* cp = FUN_006df700((void*)b, (void*)b, (void*)a);
    ((Ext*)((char*)obj.p + 0xf4))->FUN_0059c410(cp, *(void**)((char*)obj.p + 0xf8));
    *(int*)((char*)obj.p + 0xf8) = *(int*)((char*)obj.p + 0xf8) + ((b - a) >> 2) * -4;
    ((Ext*)((char*)obj.p + 0xf4))->FUN_00755570(
        (unsigned int)((*(int*)((char*)obj.p + 0x1c) - *(int*)((char*)obj.p + 0x18)) >> 2),
        (int)((char*)this + 0x98));
  }
  if ((*(int*)((char*)this + 0x34 + job->mSlot * 4) & 2) == 0) {
    if (mFieldC4 != 0) {
      ((Ext*)((char*)obj.p + 0x108))->FUN_0041f320((void*)((char*)this + 0xc8));
    }
    if (mFieldC5 != 0) {
      ((Ext*)((char*)obj.p + 0xe0))->FUN_007552e0((void*)((char*)this + 0xdc));
    }
  }
  void* old = *(void**)((char*)this + 0x44 + job->mSlot * 4);
  if ((void*)obj.p != old) {
    if (obj.p) ((VObj*)obj.p)->AddRef();
    *(void**)((char*)this + 0x44 + job->mSlot * 4) = obj.p;
    if (old) ((VObj*)old)->Release();
  }
  unsigned int arr[3];
  arr[0] = *(unsigned int*)((char*)this + 0x0c);
  arr[1] = 0xe6bce5;
  arr[2] = *(unsigned int*)((char*)this + 0x14 + job->mSlot * 4);
  FUN_006acfe0(arr, (char*)obj.p);
  return true;
}

// @ 0x007573a0
bool __cdecl FUN_007573a0(cJob_s0075_71a0** pJob, VecA* vecSrc, u32 id3, u32 id4, RCObj* rc5, VecA* vec6, PropList* listArg, VecB* arg8, VecC* arg9, Sub4* arg10, Key12* key, cJob_s0075_71a0* chain)
{
    ARC<PropList> list(listArg);
    if (!list.p) {
        PropMgr* pm = GetPropMgr();
        pm->GetPropList(id3, id4, &list);
        if (!list.p) {
            list = new ("Graphics", 0, 0, 0, 0) cPropertyList_s0075_71a0;
            ARC<PropList> parent(0);
            PropMgr* pm2 = GetPropMgr();
            if (pm2->GetPropList(0xabf001c6, 0x44a7f6af, &parent))
                list.p->SetParent(parent.p);
            GetPropMgr()->RegisterPropList(list.p, id3, id4);
        }
    }

    ARC<MeshJob> obj(new ("Graphics", 0, 0, 0, 0) MeshJob);
    obj->mVec84.Assign(vecSrc);
    {
        RCObj* old = obj->mp98;
        if (rc5 != old) {
            RCAddRef(rc5);
            obj->mp98 = rc5;
            RCRelease2(old);
        }
    }
    obj->mbB0 = false;
    if (vec6) {
        obj->mVec9c.Assign(vec6);
        obj->mbB0 = true;
    }
    obj->mSub108 = arg10;
    obj->mbC4 = false;
    obj->mbC5 = false;
    if (key) {
        obj->mbF0 = true;
        obj->mKey[0] = key->a;
        obj->mKey[1] = key->b;
        obj->mKey[2] = key->c;
        obj->mKey[1] = 0x2f4e681b;
    } else {
        obj->mbF0 = false;
    }
    if (arg8) {
        obj->mVecC8.Assign(arg8);
        obj->mbC4 = true;
    }
    if (arg9) {
        obj->mVecDc.Assign(arg9);
        obj->mbC5 = true;
    }
    obj->mId3 = id3;
    obj->mId4 = id4;
    u32 base = id4 & 0xffffff00;
    obj->mIds[0] = base;
    base = (base & 0xffffff01) | 1;
    obj->mIds[1] = base;
    base = (base & 0xffffff02) | 2;
    obj->mIds[2] = base;
    base = (base & 0xffffff03) | 3;
    obj->mIds[3] = base;
    obj->mSlotWeight[0] = -1.0f;
    obj->mSlotWeight[1] = 0.0f;
    obj->mSlotWeight[2] = 0.0f;
    obj->mSlotWeight[3] = 0.0f;

    bool found = false;
    for (int i = 0; i < 4; ++i) {
        if (list.p) {
            Property* prop;
            if (list->GetProperty(0x2e765cf + i, &prop) && prop->type == 0xd) {
                float* v = (float*)prop;
                if (prop->flags & 0x30) v = *(float**)prop;
                found = true;
                obj->mSlotWeight[i] = *v;
            }
            if (list.p) {
                Property* prop2;
                if (list->GetProperty(0x452027c + i, &prop2) && prop2->type == 0xa) {
                    int* v2 = (int*)prop2;
                    if (prop2->flags & 0x30) v2 = *(int**)prop2;
                    obj->mSlotInt[i] = *v2;
                }
            }
        }
    }
    if (!found) {
        int i = 0;
        do {
            Property* prop3;
            if (g_AppProperties && g_AppProperties->GetProperty(0x2e765cf + i, &prop3) && prop3->type == 0xd) {
                float* v = (float*)prop3;
                if (prop3->flags & 0x30) v = *(float**)prop3;
                obj->mSlotWeight[i] = *v;
            }
            ++i;
        } while (i < 4);
    }
    CopyProps6(list.p, obj->mProps, 6);
    {
        PropList* old = obj->mpList;
        if (list.p != old) {
            if (list.p) list.p->AddRef();
            obj->mpList = list.p;
            if (old) old->Release();
        }
    }

    JobMgr* jm = GetJobMgr();
    jm->Begin();
    if (jm->CreateJob(pJob)) {
        (*pJob)->mpCallback = &FUN_00757390;
        (*pJob)->mpCallbackData = obj.p;
        (*pJob)->mThreadAffinity = 0x80000000;
        (*pJob)->SetExtra(obj.p);
        JobRef jobA;
        jm->CreateJob(&jobA.p);
        jobA->mpCallback = &FUN_00754fe0;
        jobA->mpCallbackData = obj.p;
        jobA->SetExtra(obj.p);
        jobA->mThreadAffinity = 1;
        JobRef jobB;
        if (arg9) {
            jm->CreateJob(&jobB.p);
            jobB->mpCallback = &FUN_007564a0;
            jobB->mpCallbackData = obj.p;
            jobB->mThreadAffinity = 1;
            jobB->SetExtra(obj.p);
        }
        JobRef jobC;
        JobRef jobD;
        for (int i = 0; i < 4; ++i) {
            JobRef prev(*pJob);
            JobRef jobE;
            if (0.0f < obj->mSlotWeight[i]) {
                jm->CreateJob(&jobE.p);
                jobE->mpCallback = &FUN_00757170;
                jobE->mpCallbackData = obj.p;
                jobE->mSlot = i;
                jobE->mThreadAffinity = 0x80000000;
                jobE->After(prev.p);
                jobE->SetExtra(obj.p);
                jobE->Submit();
                prev = jobE;
            }
            if (obj->mSlotWeight[i] != 0.0f) {
                if (i == 2 && obj->mbF0) {
                    jm->CreateJob(&jobC);
                    jobC->mpCallback = &FUN_00757180;
                    jobC->mpCallbackData = obj.p;
                    jobC->mSlot = 2;
                    jobC->mThreadAffinity = 0x80000000;
                    jobC->SetExtra(obj.p);
                    jobC->After(prev.p);
                    jobC->Submit();
                    prev = jobC;
                }
                JobRef jobF;
                jm->CreateJob(&jobF.p);
                jobF->mpCallback = &FUN_00757190;
                jobF->mpCallbackData = obj.p;
                jobF->mSlot = i;
                jobF->mThreadAffinity = 1;
                jobF->SetExtra(obj.p);
                jobF->After(prev.p);
                jobF->Submit();
                prev = jobF;
                if (i == 0 && obj->mbF0) {
                    jm->CreateJob(&jobD);
                    jobD->mpCallback = &FUN_00754c00;
                    jobD->mpCallbackData = obj.p;
                    jobD->mSlot = 0;
                    jobD->mThreadAffinity = 0x80000000;
                    jobD->SetExtra(obj.p);
                    jobD->After(prev.p);
                    prev = jobD;
                }
                if (jobB.p) {
                    JobRef jobG;
                    jm->CreateJob(&jobG.p);
                    jobG->mpCallback = &FUN_00756b40;
                    jobG->mpCallbackData = obj.p;
                    jobG->mSlot = i;
                    jobG->mThreadAffinity = 1;
                    jobG->SetExtra(obj.p);
                    jobG->After(prev.p);
                    jobG->Submit();
                    jobB->After(jobG.p);
                }
                jobA->After(prev.p);
            }
        }
        if (jobD.p) {
            jobD->After(jobC.p);
            jobD->Submit();
        }
        jobA->Submit();
        if (jobB.p) {
            jobB->After(jobA.p);
            jobB->Submit();
            if (chain) chain->After(jobB.p);
        } else if (chain) {
            chain->After(jobA.p);
        }
    }
    jm->End();
    return true;
}

// @ 0x00757d20
int __cdecl FUN_00757d20(ArenaHolder* h)
{
    Arena* a = *(Arena**)((char*)h + 0x18);
    int n = a->GetNumExportedObjects();
    if (n <= 0) return 0;
    for (int i = 0; i < n; ++i) {
        char buf[0x38];
        *(int*)(buf + 0) = 0;
        *(int*)(buf + 4) = 0;
        *(int*)(buf + 0xc) = 0;
        *(int*)(buf + 0x10) = 0;
        *(int*)(buf + 0x14) = 0;
        *(int*)(buf + 8) = 0;
        eh_vec_ctor_006c0fa0(buf + 0x18, 8, 4, (void*)0);
        *(int*)(buf + 0x18) = 0;
        *(int*)(buf + 0x1c) = 1;
        a->GetExportedObjectByIndex(i, buf);
        bool hit = (*(int*)buf == 0x200af);
        eh_vec_dtor(buf + 0x18, 8, 4, (void*)0);
        if (hit) return 1;
    }
    return 0;
}
