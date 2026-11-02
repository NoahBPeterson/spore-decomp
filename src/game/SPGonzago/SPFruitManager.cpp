// src/game/SPGonzago/SPFruitManager.cpp -- migrated from slice(s) s01317d30, s0089d3b0, s005f4310, s00b01690, s00437b00, s0040fe00, s0040f4a0, s0040eb70, s0040ccb0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPFruitManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <intrin.h>
#include <new>
#include "EA/Messaging/IHandler.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Messaging/Server.h"
#include "EA/Stopwatch.h"
#include "SP/cICameraController.h"
#include "SP/cICameraManager.h"
#include "SP/cModelWorld.h"
#include "SP/cSPEditorEconomy.h"
#include "SP/cSPOLDPaletteItemUIDragAndBuy.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "cSPUILayeredObject.h"
#include <math.h>
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/LineLayout.h"
#include "EA/Text/TextStyle.h"

// ---- items of slice s0040ccb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    void Transform(const struct Matrix3& m);
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Matrix3 {
    struct Data { float f[9]; } d;
    Matrix3& operator=(const Matrix3& o) { d = o.d; return *this; }
    Matrix3() {}
    Matrix3(const Matrix3& o);   // 0x0041cb40 (out of line copy ctor)
};
Vector3 operator*(const Vector3& v, const float& s);           // 0x0041dca0
Vector3 operator*(const Vector3& v, const Matrix3& m);         // 0x0041daf0
Matrix3 operator*(const Matrix3& a, const Matrix3& b);         // 0x0041de20
Vector3& operator+=(Vector3& a, const Vector3& b);             // 0x0041ddb0
Vector3& operator*=(Vector3& a, const float& s);               // 0x0041dba0
inline void Vector3::Transform(const Matrix3& m) { *this = *this * m; }
struct Modifier {
    uint16_t flags;     // +0x00
    uint16_t count;     // +0x02
    Vector3 pos;        // +0x04
    float scale;        // +0x10
    Matrix3 rot;        // +0x14

    void Accumulate(const Modifier& o);
    void AccumulateScaled(const Modifier& o);
    Modifier(const Modifier& o);
};
// ---- items of slice s0040ccb0 end

// ---- items of slice s0040eb70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VS1(p) virtual void p##_a();
#define VS2(p) VS1(p##0) VS1(p##1)
#define VS4(p) VS2(p##0) VS2(p##1)
#define VS8(p) VS4(p##0) VS4(p##1)
#define VS16(p) VS8(p##0) VS8(p##1)
#define VS32(p) VS16(p##0) VS16(p##1)
#define VS64(p) VS32(p##0) VS32(p##1)
struct Counted;
struct CountedOwner {
    VS64(a) VS16(b) VS8(c) VS4(d)             // 92 slots
    virtual void SetBit(Counted* obj, bool bit);  // slot 92 (+0x170)
};
struct Bits32 {
    uint32_t mWord;
    bool Test(unsigned n) const {
        if (n < 32) {
            uint32_t w = mWord;
            return (w & (1u << (n % 32))) != 0;
        }
        return false;
    }
};
struct Counted {
    CountedOwner* mpOwner;
    Bits32 mBits;
    uint32_t pad[(0x40 - 8) / 4];
    int mRefCount;  // +0x40, plain (non-atomic)

    int Release();
};
struct KeyId {
    int a, b;
};
struct SelService {
    VS32(a) VS8(b) VS4(c) VS2(d) VS1(e)                      // 47 slots
    virtual void QueryAlt(KeyId* out);                       // slot 47 (+0xBC)
    VS2(f)                                                   // 48,49
    virtual void QueryPrimary(KeyId* out);                   // slot 50 (+0xC8)
};
struct FactoryService {
    VS4(a) VS2(b) VS1(c)                                     // 7 slots
    virtual int Create(int a, int b, int c, int d, int e);   // slot 7 (+0x1C)
};
struct SinkService {
    VS16(a) VS4(b) VS2(c) VS1(d)                             // 23 slots
    virtual void Accept(int h);                              // slot 23 (+0x5C)
};
struct Settings {
    bool Has(unsigned id);                                   // 0x006A25A0
};
extern Settings* g_pSettings;                                // 0x015FD918
SelService* GetSelService();         // 0x0067DD40
FactoryService* GetFactory();        // 0x0067DDA0
SinkService* GetSink();              // 0x0067DD60
struct SelectCommand {
    bool Execute(int unused);        // 0x0040F3F0
};
// ---- items of slice s0040eb70 end

// ---- items of slice s0040f4a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtMsgBase[];      // 0x013EB918  (base message class vtable)
extern void* vtMsgRef[];       // 0x013EB90C  (refcounted message vtable)
extern void* vtMsgOut[];       // 0x013EB844  (concrete 0x40-byte message vtable)
#pragma intrinsic(_InterlockedExchange)
void* __cdecl operator new(size_t size, const char* tag, int, int, int, int) throw();  // EASTL_allocator_allocate
void  __cdecl FreeBlock(void* p);                                                  // EASTL_allocator_deallocate
struct Variant { uint32_t value; uint32_t tag; };       // 8-byte argument slot
struct ArgList {
    Variant v[1];
    void Set(int i, uint32_t x) { v[i].value = x; }
};
struct MsgIn {
    void* vptr;
    long refs;
    Variant args[4];
    uint32_t Arg(int i) { return args[i].value; }
};
struct MsgIdBlock {                                     // embedded id holder at +8
    char pad[0x28];
    uint32_t id;                                        // msg + 0x30
    void Set(uint32_t x) { id = x; }
};
struct MsgRefInit { void** vptr; long refs; MsgRefInit* Ctor(); };
struct MsgCore {
    void** vptr;
    long refs;                                          // +4
    ArgList args;                                       // +8
    char argsPad[0x30 - 0x08 - sizeof(ArgList)];
    uint32_t id;                                        // +0x30
    uint32_t pad34;
    MsgCore(uint32_t id);                               // FUN_00423110
};
struct MsgOut : MsgCore {                               // 0x40 bytes
    uint32_t f38;                                       // +0x38
    uint32_t pad3c;
    MsgOut(uint32_t i) : MsgCore(i) { vptr = vtMsgOut; f38 = 0; }
    void AddRef()  { ((void (__thiscall*)(MsgOut*))vptr[1])(this); }
    void Release() { ((void (__thiscall*)(MsgOut*))vptr[2])(this); }
};
struct MsgOutInl {
    void** vptr;
    long refs;
    ArgList args;
    char argsPad[0x30 - 0x08 - sizeof(ArgList)];
    uint32_t id;
    uint32_t pad34;
    uint32_t f38;
    uint32_t pad3c;
    MsgOutInl(uint32_t newId) {
        MsgIdBlock* h = (MsgIdBlock*)((char*)this + 8);
        h->Set(newId);
        ((MsgRefInit*)this)->Ctor();
        vptr = vtMsgRef;
        vptr = vtMsgOut;
        f38 = 0;
    }
    void AddRef()  { ((void (__thiscall*)(MsgOutInl*))vptr[1])(this); }
    void Release() { ((void (__thiscall*)(MsgOutInl*))vptr[2])(this); }
};
struct SpriteItem;
int __fastcall LookupOffset(SpriteItem* elem);          // FUN_0041d870 (ecx = element)
struct SpriteItem {
    uint32_t v;
    operator uint32_t() { return v; }
    int Offset() { return LookupOffset(this); }
};
struct SpriteList {                                     // begin/end of a pointer vector at +0xC
    SpriteItem* begin;
    SpriteItem* end;
    int Size() { return (int)(end - begin); }
    SpriteItem& operator[](int i) { return begin[i]; }
    void Prepare(int n);                                // FUN_00421bf0
};
struct BakeSprites {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04;
    uint32_t pad08;
    SpriteList list;                                    // +0xC
    uint32_t pad14, pad18, pad1c;
    BakeSprites();                                      // Graphics::BakeSprites::BakeSprites (0x7B00F0)
};
template <class T>
struct RefPtr {
    T* p;
    RefPtr(T* x) : p(x) { if (p) p->AddRef(); }
    RefPtr(const RefPtr& o) : p(o.p) { if (p) p->AddRef(); }
    ~RefPtr() { if (p) p->Release(); }
    T* operator->() { return p; }
    T* get() { return p; }
    void Assign(T* x) {
        if (x != p) {
            T* old = p;
            if (x) x->AddRef();
            p = x;
            if (old) old->Release();
        }
    }
};
struct IMsg {                                           // refcounted message interface
    virtual void v0();
    virtual void AddRef();                              // slot 1
    virtual void Release();                             // slot 2
};
struct MsgPtr {                                         // intrusive ptr to a message
    IMsg* p;
    IMsg* get() { return p; }
    MsgPtr(IMsg* x) : p(x) { if (p) p->AddRef(); }
    ~MsgPtr() { if (p) p->Release(); }
    IMsg* operator->() { return p; }
};
struct Dispatcher {                                     // FUN_0067dcc0() result
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Post(uint32_t id, void* msg, int flag);  // slot 5 (0x14)
};
struct SpriteService {                                  // FUN_0068f4d0() result
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void AddRef();                              // slot 8 (0x20)
    virtual void Release();                             // slot 9 (0x24)
};
struct SvcRef {                                         // non-null-checked reference holder
    SpriteService* p;
    SvcRef(SpriteService* x) : p(x) { uint32_t scratch[3]; p->AddRef(); }
    ~SvcRef() { p->Release(); }
};
struct Prop {
    char pad[0x12];
    uint16_t type;
    int* AsInt();                                       // FUN_0041e990
    bool* AsBool();                                     // FUN_0041e920
};
struct Provider {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProp(uint32_t id, Prop** out);      // slot 9 (0x24)
};
Dispatcher* GetDispatcher();                            // FUN_0067dcc0
SpriteService* GetSpriteService();                      // FUN_0068f4d0
void __cdecl BakeOne(uint32_t item, int off, int kind, int index, uint32_t msgId, void* msg);   // FUN_007b06c0
struct PtrHolder {
    void* p;
    void* get() { return p; }
};
struct Obj {
    char p0[0x23c];
    PtrHolder holder23c;
    char p1[0x24c - 0x240];
    Provider* provider;                                 // 0x24c
    char p2[0x259 - 0x250];
    bool flag259;
    char p3[0x117c - 0x25a];
    RefPtr<BakeSprites> bake;                                       // 0x117c
    uint8_t counter;                                    // 0x1180

    // Reads an integer property of the given type through the provider (inlined helper).
    inline bool ReadIntProp(uint32_t id, int type, int* out)
    {
        Provider* pr = provider;
        Prop* q;
        if (pr) {
            if (pr->GetProp(id, &q) && q->type == type) {
                *out = *q->AsInt();
                return true;
            }
        }
        return false;
    }

    // Reads a boolean property through the provider (inlined helper).
    inline void ReadBoolProp(uint32_t id, int type, bool* out)
    {
        Provider* pr = provider;
        Prop* q;
        if (pr) {
            if (pr->GetProp(id, &q) && q->type == type)
                *out = *q->AsBool();
        }
    }

    bool Fn40f4a0(MsgIn* in);
    bool Fn40f820(MsgIn* in);
    bool Fn40fc00(MsgIn* in);
};
struct MsgDel {
    void** vptr;
    MsgDel* DelBase(uint32_t flags);
    MsgDel* DelRef(uint32_t flags);
};
// ---- items of slice s0040f4a0 end

// ---- items of slice s0040fe00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKeyPair { uint32_t a, b; };
struct AtomicRefCounted {
    void* vftable;
    uint32_t mField4;
    volatile long mnRefCount;
    int Release();      // 0x00402420
};
struct SimplePtr {      // smart pointer to an AtomicRefCounted
    AtomicRefCounted* mpObject;
    SimplePtr() : mpObject(0) {}
    ~SimplePtr() {
        if (mpObject)
            mpObject->Release();
    }
    AtomicRefCounted** GetAddressForWrite() {
        if (mpObject) {
            AtomicRefCounted* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct ObjectHolder {
    AtomicRefCounted* mpObject;
    uint32_t mField4;
    uint32_t mField8;
};
struct IEditorRegistry {
virtual void r0();
virtual void r1();
virtual void r2();
virtual void r3();
virtual void r4();
virtual void r5();
virtual void r6();
virtual void r7();
virtual void r8();
virtual void r9();
virtual void r10();
virtual void r11();
virtual void r12();
virtual void r13();
virtual void r14();
virtual void r15();
virtual void r16();
virtual void r17();
virtual void r18();
virtual void r19();
virtual void r20();
virtual void r21();
virtual void r22();
virtual void r23();
virtual void r24();
virtual void r25();
virtual void r26();
virtual void r27();
virtual void r28();
virtual void r29();
virtual void r30();
virtual void r31();
virtual void r32();
virtual void r33();
virtual void r34();
virtual void r35();
virtual void r36();
virtual void r37();
virtual void r38();
virtual void r39();
virtual void r40();
virtual void r41();
virtual void r42();
virtual void r43();
virtual void r44();
    virtual void GetPartKey(ResourceKeyPair* out);      // slot 45 (+0xb4)
    virtual void GetPaintKey(ResourceKeyPair* out);     // slot 46 (+0xb8)
    virtual void GetModelKey(ResourceKeyPair* out);     // slot 47 (+0xbc)
virtual void r48();
virtual void r49();
virtual void r50();
virtual void r51();
virtual void r52();
virtual void r53();
virtual void r54();
virtual void r55();
virtual void r56();
virtual void r57();
virtual void r58();
    virtual void GetObject(int which, ObjectHolder* out);   // slot 59 (+0xec)
};
struct IKeyResolver {
virtual void k0();
virtual void k1();
virtual void k2();
virtual void k3();
virtual void k4();
virtual void k5();
virtual void k6();
    virtual uint32_t Resolve(uint32_t a, uint32_t b);   // slot 7 (+0x1c)
};
struct IActionSink {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
    virtual void SetTarget(AtomicRefCounted* obj, int flag);    // slot 21 (+0x54)
    virtual void s22();
    virtual void Perform(uint32_t id, int a, int b, int c);     // slot 23 (+0x5c)
};
struct INotifier {
virtual void n0();
virtual void n1();
virtual void n2();
virtual void n3();
virtual void n4();
    virtual void Notify(uint32_t id, int a, int b);     // slot 5 (+0x14)
};
struct IPropertyEntry;
struct IPropertyMap {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool Find(uint32_t key, IPropertyEntry** ppEntry);   // slot 9 (+0x24)
};
struct IPropertyEntry {
    uint8_t pad[0x12];
    uint16_t mType;
    uint32_t* GetValue();    // 0x0041e990
};
struct RefCountedBase {
    virtual int AddRef();
    virtual int Release();      // slot 1 (+4)
    uint32_t mField4;
    uint32_t mField8;
};
struct EditorSink {
    virtual void v0();
};
struct EditorOwner : RefCountedBase, EditorSink {};
template <class T> struct intrusive_ptr {
    T* mpObject;

    intrusive_ptr() : mpObject(0) {}
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    intrusive_ptr& operator=(T* pNew)
    {
        if (mpObject != pNew) {
            T* const pTemp = mpObject;
            if (pNew)
                pNew->AddRef();
            mpObject = pNew;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
struct IdFlags {
    uint32_t state : 8;
    uint32_t kind : 8;
    uint32_t rest : 16;
    void SetKind(int v) { kind = v; }
    void SetState(int v) { state = v; }
};
struct EditorMessage {
    uint32_t pad[2];
    struct { uint32_t a, b; } args[2];
    uint32_t GetArg(int idx) { return args[idx].a; }
};
struct ILogger {
    bool IsEnabled(uint32_t id);        // 0x006a25a0
};
extern ILogger* g_pLogger;              // 0x015fd918
inline ILogger* GetLogger() { ILogger* l = g_pLogger; return l; }
struct ResourceRef {
    uint32_t instance;
    uint32_t type;
    IdFlags flags;
};
inline void InitRef(ResourceRef* r, uint64_t inst, uint32_t type, const IdFlags& group)
{
    r->instance = (uint32_t)inst;
    r->type = type;
    r->flags = group;
}
IEditorRegistry* GetEditorRegistry();   // 0x0067dd40
IKeyResolver* GetKeyResolver();         // 0x0067dda0
IActionSink* GetActionSink();           // 0x0067dd60
INotifier* GetNotifier();               // 0x0067dcc0
void FindObject(EditorSink* base, uint32_t id, IdFlags flags, AtomicRefCounted** out);    // 0x007aff00
uint32_t LookupString(uint32_t hash);     // 0x006b1f90
void LogResource(EditorSink* base, ResourceRef* ref, uint32_t str, int flag);   // 0x007b10d0
struct EditorHandler {
    uint8_t pad0[0x228];
    uint32_t mTargetId;                 // +0x228
    uint32_t mPad22c;
    IdFlags mFlags;                     // +0x230
    uint8_t pad1[0x24c - 0x234];
    IPropertyMap* mpProperties;         // +0x24c
    uint8_t pad2[0x117c - 0x250];
    intrusive_ptr<EditorOwner> mpOwner; // +0x117c

    IPropertyMap* GetProperties()
    {
        return mpProperties;
    }

    IdFlags MakeFlags(int kind, int state)
    {
        uint32_t reserved[3];
        IdFlags result = mFlags;
        result.SetKind(kind);
        result.SetState(state);
        return result;
    }

    bool HandleMessage(EditorMessage* msg);
};
// ---- items of slice s0040fe00 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
bool TryGetUIntProperty(IPropertyMap* map, uint32_t key, uint32_t* out);   // defined at 0x00410370, called earlier in the TU

// ---- items of slice s00437b00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Bits32_s0043_7b00 {
    uint32_t v;
    uint32_t& _Getword(unsigned pos) { return v; }
    bool test(unsigned pos) const {
        if (pos < 32) {
            uint32_t word = v;
            return (word & (1u << (pos % 32))) != 0;
        }
        return false;
    }
    void set(unsigned pos, bool val) {
        if (pos < 32) {
            if (val) _Getword(pos) |= (1u << (pos % 32));
            else     _Getword(pos) &= ~(1u << (pos % 32));
        }
    }
};
struct Model {
    char pad0[4];
    Bits32_s0043_7b00 flags;       // 4
    char pad1[8];
    void SetFlag(bool v);   // 0x00437f70
    bool GetFlag() { return flags.test(0); }
};
// ---- items of slice s00437b00 end

// ---- items of slice s00b01690 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef float              f32;
struct CMatrix3Ops { void Assign(const void* src); };                    // 0x0041cb40
#define M3(p) ((CMatrix3Ops*)(p))
struct CTransformAssignOps {
    void* Assign(const void* src);                    // 0x00537dc0
};
static f32 g_167af5c = 0.0f;             // 0x0167af5c
static f32 g_167af60 = 0.0f;             // 0x0167af60
static f32 g_167af64 = 0.0f;             // 0x0167af64
// ---- items of slice s00b01690 end

// ---- items of slice s005f4310 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005f_4310 {
 public:
  T* mpObject;
  AutoRefCount_s005f_4310() : mpObject(0) {}
  AutoRefCount_s005f_4310(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005f_4310(const AutoRefCount_s005f_4310& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005f_4310() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005f_4310& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  AutoRefCount_s005f_4310& operator=(const AutoRefCount_s005f_4310& x) { return operator=(x.mpObject); }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
using EA::AutoRefCount_s005f_4310;
namespace SP {
class cModelWorld_s005f_4310 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  virtual int GetEffectCount(struct cMWModel_s005f_4310* model);  // +0x64
  PV(26) PV(27)
  virtual void StartEffect(cMWModel_s005f_4310* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
  PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69) PV(70)
  PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79) PV(80) PV(81) PV(82) PV(83) PV(84)
  PV(85) PV(86) PV(87) PV(88) PV(89) PV(90) PV(91)
  virtual void DestroyModel(struct cMWModel_s005f_4310* model, bool immediate);  // +0x170
};
}
namespace SP {
struct cMWModel_s005f_4310 { private:
 public:
  cModelWorld_s005f_4310* mpWorld;  // +0x0
  uint32_t mFlags;       // +0x4
  uint32_t pad8[14];
  int mRefCount;         // +0x40
  void AddRef() { mRefCount++; }
  void Release();
};
}
namespace SP {
inline void cMWModel_s005f_4310::Release() {
  if (mRefCount > 1)
    mRefCount--;
  else
    mpWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
struct Blob38 {
  unsigned short mFlags;             // +0x00
  unsigned short mModificationCount; // +0x02
  float mTranslation[3];             // +0x04
  float mScale;                      // +0x10
  float mRotation[9];                // +0x14
  Blob38& operator=(const Blob38& o);
};
}
namespace SP {
inline Blob38& Blob38::operator=(const Blob38& o) {
  mFlags = o.mFlags;
  mModificationCount = o.mModificationCount;
  for (int i = 0; i < 3; ++i)
    mTranslation[i] = o.mTranslation[i];
  mScale = o.mScale;
  for (int i = 0; i < 9; ++i)
    mRotation[i] = o.mRotation[i];
  return *this;
}
}
// ---- items of slice s005f4310 end

// ---- items of slice s01317d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0131_7d30; 
}
typedef eastl::string8_s0131_7d30 string8_s0131_7d30;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0131_7d30&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute
{
    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Record with a default value: the store of the default (GetDefaultValue<T>()) is part of the
    // record's construction and sits just before the offset store.
    template<typename Store>
    __forceinline Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault, const Store& storeDefault)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        storeDefault();
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream*, void*);   // Vector3
}
namespace Simulator {
bool Read_00572810(ISerializerReadStream*, void*);   // raw 4 bytes
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream*, void*);   // ResourceKey
}
namespace Simulator {
bool Read_00b04d20(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Read_00b0a310(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00aca730(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00b00390(ISerializerWriteStream*, void*);
}
namespace Simulator {
void ReadText_006930f0(const string8_s0131_7d30&, void*);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0131_7d30&, void*);
}
namespace Simulator {
void ReadText_00693090(const string8_s0131_7d30&, void*);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0131_7d30&, void*);
}
namespace Simulator {
void ReadText_00693150(const string8_s0131_7d30&, void*);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0131_7d30&, void*);
}
namespace Simulator {
void WriteText_00695010(char*, void*);
}
namespace Simulator {
void WriteText_00694fc0(char*, void*);
}
namespace Simulator {
void WriteText_00694f00(char*, void*);
}
namespace Simulator {
void WriteText_00694ee0(char*, void*);
}
namespace Simulator {
void WriteText_00695080(char*, void*);
}
namespace Simulator {
void WriteText_00692fb0(char*, void*);
}
namespace Simulator {
bool Validate_00b1fbf0();
}
namespace Simulator {
bool Validate_00b6f860();
}
namespace Simulator {
bool Validate_00b00400();
}
namespace Simulator {
bool ToXml_00acbba0(void*, const char*, int);
}
namespace Simulator {
bool ToXml_00acbb80(void*, const char*, int);
}
namespace Simulator {
bool ToXml_00675ca0(void*, const char*, int);
}
namespace Simulator {
bool ToXml_0057cde0(void*, const char*, int);
}
namespace Simulator {
bool ToXml_00ae5720(void*, const char*, int);
}
namespace Simulator {
bool ToXml_00c6c390(void*, const char*, int);
}
namespace Simulator {
bool ToXml_00b03fd0(void*, const char*, int);
}
namespace Simulator {
#define VEC3_ATTR  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, Validate_00b1fbf0, ToXml_00acbba0
}
namespace Simulator {
#define FLOAT_ATTR Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Validate_00b1fbf0, ToXml_00acbb80
}
namespace Simulator {
#define UINT_ATTR  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00, Validate_00b1fbf0, ToXml_00675ca0
}
namespace Simulator {
#define INT_ATTR   Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, Validate_00b1fbf0, ToXml_0057cde0
}
namespace Simulator {
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, Validate_00b1fbf0, ToXml_00ae5720
}
namespace Simulator {
#define TREES_ATTR Read_00b04d20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define DEPR_ATTR  Read_00b0a310, Write_00b00390, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b00400, ToXml_00b03fd0
}
namespace Simulator {
bool Read_00b00430(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Read_00aff7e0(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Read_00b02540(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Read_00b06e10(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Read_00b04e00(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Write_00b02570(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00aff810(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00b00450(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Write_00c761c0(ISerializerWriteStream*, void*);
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool ToXml_00ac8050(void*, const char*, int);
}
namespace Simulator {
bool ToXml_00f29b90(void*, const char*, int);
}
namespace Simulator {
bool ToXml_00eafe40(void*, const char*, int);
}
namespace Simulator {
void SetDefault_00b02610(Attribute*);
}
namespace Simulator {
struct Tag_mFlags;
}
namespace Simulator {
struct Tag_mFruitIdx;
}
namespace Simulator {
struct Tag_mElapsedOnGroundTime;
}
namespace Simulator {
struct Tag_mTreeSpeciesBracket;
}
namespace Simulator {
struct Tag_mTreeSeqID;
}
namespace Simulator {
struct Tag_mTreeDistSequenceIdx;
}
namespace Simulator {
struct Tag_mState;
}
namespace Simulator {
struct Tag_sFruitCount;
}
namespace Simulator {
struct Tag_ValidCommon;      // rows 1..7 and the static row share their validate symbol
}
namespace Simulator {
struct Tag_mSeqID;
}
namespace Simulator {
struct Tag_mSpeciesBracket2;
}
namespace Simulator {
struct Tag_mDistSequenceIdx;
}
namespace Simulator {
struct Tag_mSpeciesKey;
}
namespace Simulator {
struct Tag_mTransform;
}
namespace Simulator {
struct Tag_mFlags2;
}
namespace Simulator {
struct Tag_mFruitTransforms;
}
namespace Simulator {
struct Tag_mFruitDistEffectIdxs;
}
namespace Simulator {
struct Tag_ValidSeq;         // mSeqID + mDistSequenceIdx share their validate symbol
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream*, void*);
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream*, void*);
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0131_7d30&, void*);
}
namespace Simulator {
template<typename T> bool ToXmlUInt(void*, const char*, int);
}
namespace Simulator {
template<typename T> bool ToXmlInt(void*, const char*, int);
}
namespace Simulator {
template<typename T> bool AlwaysValid();
}
namespace Simulator {
extern AttrSlot cTreeFruit_sAttributes[8];   // 0x01567860
}
namespace Simulator {
extern AttrSlot cFruit_sAttributes[10];      // 0x0167b858
}
namespace Simulator {
#define ADD_TF(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cTreeFruit_sAttributes[IDX] = a; }
}
namespace Simulator {
#define ADD_FR(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cFruit_sAttributes[IDX] = a; }
}
namespace Simulator {
#define UINT_ROW(T)   Read4<T>, Write4<T>, ReadTextInt<T>, WriteText_00694f00, AlwaysValid<Tag_ValidCommon>, ToXmlUInt<T>
}
namespace Simulator {
#define INT_ROW(T)    Read4<T>, Write4<T>, ReadTextInt<T>, WriteText_00694ee0, AlwaysValid<T>, ToXmlInt<T>
}
namespace Simulator {
#define STATIC_ROW(T) Read4<T>, Write4<T>, ReadTextInt<T>, WriteText_00694f00, AlwaysValid<Tag_ValidCommon>
}
namespace Simulator {
struct Vector3_s0131_7d30 { float x, y, z; Vector3_s0131_7d30(const Vector3_s0131_7d30& v) : x(v.x), y(v.y), z(v.z) {} };
}
namespace Simulator {
struct Matrix3_s0131_7d30 {
    float m[3][3];
    Matrix3_s0131_7d30& Assign(const Matrix3_s0131_7d30& other);        // 0x0041cb40
};
}
namespace Simulator {
extern const Vector3_s0131_7d30 kDefaultOffset;              // 0x0167af5c (this module's zero vector)
}
namespace Simulator {
extern const Matrix3_s0131_7d30 kDefaultRotation;            // 0x0167b554 (this module's identity)
}
namespace Simulator {
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3_s0131_7d30  mOffset;
    float    mScale;
    Matrix3_s0131_7d30  mRotation;
    cSPTransform() : mFlags(0), mModificationCount(0), mOffset(kDefaultOffset), mScale(1.0f)
    {
        mRotation.Assign(kDefaultRotation);
    }
    cSPTransform& operator=(const cSPTransform& other);   // 0x00537dc0
};
}
namespace Simulator {
cSPTransform& GetDefaultTransform();              // 0x00b02590 (SP::GetDefaultValue<cSPTransform;79537323>)
}
namespace Simulator {
struct StoreTransform { const cSPTransform& v; StoreTransform(const cSPTransform& x) : v(x) {} void operator()() const { GetDefaultTransform() = v; } };
}
// ---- items of slice s01317d30 end

// @ 0x0040ccb0
void Modifier::Accumulate(const Modifier& o)
{
    pos += (o.pos * scale) * rot;
    rot = o.rot * rot;
    scale *= o.scale;
    flags |= o.flags;
    count++;
}

// @ 0x0040f360
int Counted::Release()
{
    if (mRefCount > 1) {
        --mRefCount;
        return mRefCount;
    }
    mpOwner->SetBit(this, mBits.Test(31));
    return 0;
}

// @ 0x0040f3f0
bool SelectCommand::Execute(int unused)
{
    KeyId id;
    id.a = -1;
    id.b = -1;
    Settings* s = g_pSettings;
    if (s->Has(0x1A91189C))
        GetSelService()->QueryPrimary(&id);
    else
        GetSelService()->QueryAlt(&id);
    GetSink()->Accept(GetFactory()->Create(id.a, id.b, 0, 1, 0));
    return true;
}

// @ 0x0040f820
bool Obj::Fn40f820(MsgIn* in)
{
    MsgIn* m = in;
    uint32_t kind = m->Arg(1);
    MsgPtr msg((IMsg*)new ("Graphics", 0, 0, 0, 0) MsgOut(0x5302B02));
    ((MsgOut*)msg.p)->args.Set(1, kind);
    int val;
    if (ReadIntProp(0x52F7B17, 9, &val)) {
        int cat = -1;
        int idx = -1;
        if (val >= 500) {
            cat = 6;
            idx = val - 500;
        } else if (val >= 300) {
            cat = 5;
            idx = val - 300;
        } else if (val >= 100) {
            cat = 4;
            idx = val - 100;
        }
        if (idx >= 0 && idx < 100) {
            RefPtr<BakeSprites> bs(bake);
            bake.Assign(new ("Graphics", 0, 0, 0, 0) BakeSprites());
            bake->list.Prepare(bs->list.Size());
            SvcRef svc(GetSpriteService());
            for (int i = 0, n = bake->list.Size(); i < n; i++) {
                BakeOne(bs->list[i], bake->list[i].Offset(), cat, idx, 0x5302B02, msg.get());
            }
            return true;
        }
    }
    GetDispatcher()->Post(0x530781E, msg.p, 0);
    return true;
}

// @ 0x0040fc00
bool Obj::Fn40fc00(MsgIn* in)
{
    counter++;
    if (counter == bake->list.Size()) {
        counter = 0;
        MsgIn* m = in;
        uint32_t kind = m->Arg(1);
        MsgPtr msg((IMsg*)new ("Graphics", 0, 0, 0, 0) MsgOutInl(0x530781E));
        ((MsgOutInl*)msg.p)->args.Set(1, kind);
        GetDispatcher()->Post(0x530781E, msg.p, 0);
    }
    return true;
}

// @ 0x0040fd50
MsgRefInit* MsgRefInit::Ctor()
{
    vptr = vtMsgBase;
    vptr = vtMsgRef;
    volatile long* p = &refs;
    _InterlockedExchange(p, 0);
    return this;
}

// @ 0x0040fd90
MsgDel* MsgDel::DelBase(uint32_t flags)
{
    vptr = vtMsgBase;
    if (flags & 1) FreeBlock(this);
    return this;
}

// @ 0x0040fdc0
MsgDel* MsgDel::DelRef(uint32_t flags)
{
    vptr = vtMsgRef;
    vptr = vtMsgBase;
    if (flags & 1) FreeBlock(this);
    return this;
}

// @ 0x0040fe00
bool EditorHandler::HandleMessage(EditorMessage* msg)
{
    EditorMessage* event = msg;
    uint32_t hovered = event->GetArg(1);
    uint32_t code = 0;
    TryGetUIntProperty(GetProperties(), 0x4c6ba3c, &code);

    ResourceKeyPair keyOne = { 0xffffffff, 0xffffffff };
    ResourceKeyPair toolKey = { 0xffffffff, 0xffffffff };
    ResourceKeyPair categoryKey = { 0xffffffff, 0xffffffff };
    GetEditorRegistry()->GetModelKey(&keyOne);
    uint32_t paintResult = GetKeyResolver()->Resolve(keyOne.a, keyOne.b);
    GetEditorRegistry()->GetPaintKey(&toolKey);
    uint32_t uiAction = GetKeyResolver()->Resolve(toolKey.a, toolKey.b);
    GetEditorRegistry()->GetPartKey(&categoryKey);
    uint32_t value = GetKeyResolver()->Resolve(categoryKey.a, categoryKey.b);

    ObjectHolder editHolder = { 0, 0, 0 };
    ObjectHolder paintHolder = { 0, 0, 0 };
    ObjectHolder modelHolder = { 0, 0, 0 };
    GetEditorRegistry()->GetObject(2, &editHolder);
    GetEditorRegistry()->GetObject(4, &paintHolder);
    GetEditorRegistry()->GetObject(3, &modelHolder);
    AtomicRefCounted* modelObj = editHolder.mpObject;
    AtomicRefCounted* object = paintHolder.mpObject;
    AtomicRefCounted* tool = modelHolder.mpObject;

    uint32_t mode = 0;
    if ((AtomicRefCounted*)hovered == object)
        mode = 1;
    else if ((AtomicRefCounted*)hovered == tool)
        mode = 2;

    IdFlags uiFlags = MakeFlags(0x29, mode);

    SimplePtr obj;
    FindObject(mpOwner.get(), mTargetId, uiFlags, obj.GetAddressForWrite());
    if (obj.mpObject && GetLogger()->IsEnabled(0x26cd3c9)) {
        ResourceRef ref;
        InitRef(&ref, mTargetId, 0x2f4e681c, uiFlags);
        LogResource(mpOwner.get(), &ref, LookupString(0x11ac1ac), 1);
        GetActionSink()->SetTarget(obj.mpObject, 0);
    }
    mpOwner = 0;

    if ((code == 1 || code == 2) && (AtomicRefCounted*)hovered == modelObj) {
        GetActionSink()->Perform(uiAction, 0, 1, 0);
    } else if (code == 2 && (AtomicRefCounted*)hovered == object) {
        GetActionSink()->Perform(value, 0, 1, 0);
    } else if ((code == 0 && (AtomicRefCounted*)hovered == modelObj) ||
               (code == 1 && (AtomicRefCounted*)hovered == object) ||
               (code == 2 && (AtomicRefCounted*)hovered == tool)) {
        GetNotifier()->Notify(0x52deb9e, 0, 0);
    }
    return true;
}

// @ 0x00410370
bool TryGetUIntProperty(IPropertyMap* map, uint32_t key, uint32_t* out)
{
    if (map) {
        uint32_t dead[1];
        IPropertyEntry* entry;
        if (map->Find(key, &entry) && entry->mType == 9) {
            *out = *entry->GetValue();
            return true;
        }
    }
    return false;
}

// @ 0x00437f70
void Model::SetFlag(bool v)
{
    flags.set(0, v);
}

// @ 0x005f4e10
namespace SP {
AutoRefCount_s005f_4310<SP::cMWModel_s005f_4310>* copy_refs(AutoRefCount_s005f_4310<SP::cMWModel_s005f_4310>* first, AutoRefCount_s005f_4310<SP::cMWModel_s005f_4310>* last, AutoRefCount_s005f_4310<SP::cMWModel_s005f_4310>* out)
{
  for (; first != last; ++first, ++out)
    *out = *first;
  return out;
}
}  // namespace SP

// @ 0x0089e040
namespace EA { namespace Text {
int GetSpaceProperties(wchar_t c)
{
    switch ((unsigned short)c) {
    case 9: return 0x15;
    case 10: case 11: case 12: case 13: return 0x14;
    case 0x20: case 0x2000: case 0x2001: case 0x2002: case 0x2003: case 0x2004: case 0x2005: case 0x2006:
    case 0x2008: case 0x2009: case 0x200a: case 0x3000: return 5;
    case 0xa0: case 0x2007: return 9;
    case 0x200b: case 0x200c: return 6;
    case 0x200d: case 0x2060: case 0xfeff: return 10;
    }
    return 0;
}
}}  // namespace EA::Text

// @ 0x0089e0e0
namespace EA { namespace Text {
bool IsSpace(wchar_t c, int mask, bool all)
{
    int p = GetSpaceProperties(c);
    if (all)
        return (p & mask) == mask;
    return (p & mask) != 0;
}
}}  // namespace EA::Text

// @ 0x00b02590
void* GetDefaultValue_B(void)
{
    if ((*(volatile u32*)0x0167bbc4 & 1) == 0) {
        *(volatile u32*)0x0167bbc4 |= 1;
        *(f32*)0x0167bb90 = g_167af5c;
        *(f32*)0x0167bb94 = g_167af60;
        *(u16*)0x0167bb8e = 0;
        *(f32*)0x0167bb98 = g_167af64;
        *(u16*)0x0167bb8c = 0;
        *(f32*)0x0167bb9c = 1.0f;
        M3((void*)0x0167bba0)->Assign((const void*)0x0167b554);
    }
    return (void*)0x0167bb8c;
}

// @ 0x00b02610
void FUN_00b02610(void* obj)
{
    void* t = (*(void*(*)(void*))(*(void**)((char*)obj + 0x20)))(obj);
    void* d = GetDefaultValue_B();
    ((CTransformAssignOps*)t)->Assign(d);
}

// @ 0x013184d0
namespace Simulator {
void InitTreeFruitAttributes()
{
    ADD_TF(0, "mFlags", 0x3fe7ec0, 0x148, Read_00b00430, Write_00b02570, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFlags>, ToXml_00ac8050)
    ADD_TF(1, "mFruitIdx", 0x410d8c8, 0x164, UINT_ROW(Tag_mFruitIdx))
    ADD_TF(2, "mElapsedOnGroundTime", 0x410d8fe, 0x168, UINT_ROW(Tag_mElapsedOnGroundTime))
    ADD_TF(3, "mTreeSpeciesBracket", 0x67ddca4, 0x158, INT_ROW(Tag_mTreeSpeciesBracket))
    ADD_TF(4, "mTreeSeqID", 0x67ddca8, 0x15c, UINT_ROW(Tag_mTreeSeqID))
    ADD_TF(5, "mTreeDistSequenceIdx", 0x67ddcab, 0x160, UINT_ROW(Tag_mTreeDistSequenceIdx))
    ADD_TF(6, "mState", 0x420798f, 0x16c, INT_ROW(Tag_mState))
    ADD_TF(7, "sFruitCount", 0x410d9be, (void*)0x167af58, STATIC_ROW(Tag_sFruitCount))
}
}  // namespace Simulator

// @ 0x01318800
namespace Simulator {
void InitFruitAttributes()
{
    ADD_FR(0, "mSeqID", 0x4bda4a8, 0x4c, Read4<Tag_mSeqID>, Write4<Tag_mSeqID>, ReadTextInt<Tag_mSeqID>, WriteText_00694f00, AlwaysValid<Tag_ValidSeq>, ToXml_00675ca0)
    ADD_FR(1, "mSpeciesBracket", 0x4bda4af, 0x50, Read4<Tag_mSpeciesBracket2>, Write4<Tag_mSpeciesBracket2>, ReadTextInt<Tag_mSpeciesBracket2>, WriteText_00694ee0, AlwaysValid<Tag_mSpeciesBracket2>, ToXml_0057cde0)
    ADD_FR(2, "mDistSequenceIdx", 0x4bda4aa, 0x54, Read4<Tag_mDistSequenceIdx>, Write4<Tag_mDistSequenceIdx>, ReadTextInt<Tag_mDistSequenceIdx>, WriteText_00694f00, AlwaysValid<Tag_ValidSeq>, ToXml_00675ca0)
    cSPTransform defaultTransform;
    ADD_FR(3, "mTransform", 0x4bda4ab, 0x58, Read_00aff7e0, Write_00aff810, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mTransform>, ToXml_00ac8050, SetDefault_00b02610, StoreTransform(defaultTransform))
    ADD_FR(4, "mFlags", 0x4bda4ac, 0x90, Read_00b00430, Write_00b02570, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFlags2>, ToXml_00ac8050)
    ADD_FR(5, "mSpeciesKey", 0x4bda4ad, 0x94, Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<Tag_mSpeciesKey>, ToXml_00ae5720)
    ADD_FR(6, "mpInteractingWith", 0x410d913, 0xa0, Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD_FR(7, "mFruitTransforms", 0x62073d2, 0xa4, Read_00b06e10, Write_00b00450, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFruitTransforms>, ToXml_00f29b90)
    ADD_FR(8, "mFruitDistEffectIdxs", 0x62073d8, 0x19c, Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFruitDistEffectIdxs>, ToXml_00eafe40)
    // "field_name" sentinel: a static record (id -1, no callbacks) built in place at table slot 9.
    new (&cFruit_sAttributes[9]) Attribute("field_name", 0xffffffff, (void*)0, 0, 0, 0, 0, 0);
}
}  // namespace Simulator
