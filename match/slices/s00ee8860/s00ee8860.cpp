// Slice s00ee8860: the scenario "Sculpt" palette tool (C40) and its four child
// tool-page objects (OBJ64/OBJ174/OBJ28/OBJ14), plus the palette record editor
// add/remove/update flow.  (0xee8860-0xee983b)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (NO /EHsc: 0xee0000-0xf10000 contains no
//   `mov eax,fs:[0]` C++-EH prologue at all, and /EHsc adds one to C40::C40, breaking it)
#include "types.h"

struct IWindow;
struct cSPUILayout;
struct cSPPalette;
struct OBJ174;
struct OBJ14;
struct LayoutRecord;
struct cSPPaletteInfo;
struct UIEditor;
struct EffectsHandle;
struct TutorialsUI;

#define PV(n) virtual void _pv##n();

// ----------------------------------------------------------------- math types
struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[9]; };

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// A dummy polymorphic class: the vcall helpers only need a complete class type
// to form the member-function pointer.
struct VObj { void* mpVtbl; };

// ------------------------------------------------------------ UTFWin::IWindow
// Only the slots this slice reaches are named; the dummy virtuals keep the
// offsets right. 0x0c AsInterface, 0x10 GetHost, 0x1c, 0x28, 0x30 counter,
// 0x38 box, 0x70 one-float position, 0x7c command, 0xf0 get-child,
// 0x104 Show.
struct IWindow {
    virtual void   V00();
    virtual void   V04();
    virtual void   V08();
    virtual void*  AsInterface(uint32_t id);        // 0x0c
    virtual void*  V10();                           // 0x10
    virtual void   V14();
    virtual void   V18();
    virtual void   V1c(int a);                      // 0x1c
    virtual void   V20();
    virtual void   V24();
    virtual void   V28(int a, int b);               // 0x28
    virtual void   V2c();
    virtual int    V30(int a);                      // 0x30
    virtual void   V34();
    virtual float* V38();                           // 0x38
    PV(3c) PV(40) PV(44) PV(48) PV(4c) PV(50) PV(54) PV(58)
    PV(5c) PV(60) PV(64) PV(68) PV(6c)
    virtual void   V70(float f);                    // 0x70
    PV(74) PV(78)
    virtual void   V7c(int a, int b);               // 0x7c
    PV(80) PV(84) PV(88) PV(8c) PV(90) PV(94) PV(98) PV(9c)
    PV(a0) PV(a4) PV(a8) PV(ac) PV(b0) PV(b4) PV(b8) PV(bc)
    PV(c0) PV(c4) PV(c8) PV(cc) PV(d0) PV(d4) PV(d8) PV(dc)
    PV(e0) PV(e4) PV(e8) PV(ec)
    virtual void*  Vf0(uint32_t id, int a);         // 0xf0
    PV(f4) PV(f8) PV(fc) PV(100)
    virtual void   V104(void* pOwner);              // 0x104
};

// -------------------------------------------------------------------- EA base
namespace EA {
template <class T>
class RefCountVTemplate {
 public:
    RefCountVTemplate() : mRefCount(0) {}
    virtual ~RefCountVTemplate();                  // 0x00
    virtual int AddRef();                          // 0x04
    virtual int Release();                         // 0x08
    virtual int GetRefCount();                     // 0x0c
    T mRefCount;
};
}  // namespace EA

// A ref-counted object whose AddRef/Release are plain inline header methods
// (the compiler inlines the +/- of the counter at, and the release call).
struct RefCountInt {
    virtual void _dtor(int flag);                  // 0x00
    int mRefCount;                                 // 0x04
    int AddRef() { return ++mRefCount; }
    int Release() {
        int r = --mRefCount;
        if (r == 0) {
            mRefCount = 1;
            (*(void(__thiscall**)(int)) * (void**)this)(1);
        }
        return r;
    }
};

// A ref-counted object whose AddRef is virtual at +0x00 and Release at +0x04.
struct RefCount04 {
    virtual void AddRef();
    virtual void Release();
};

// The other interface C40/OBJ28/OBJ174 also implement (vtable 0x13eb394).
struct IMsgHandler {
    virtual uint8_t Msg0(void* sender, void* msg);  // 0x00
    virtual uint8_t Msg1(void* sender, void* msg);  // 0x04
};

// A UTFWin message dispatcher (EA::Messaging): 0x24 registers a handler.
struct IMsgDispatcher {
    PV(00) PV(04) PV(08) PV(0c) PV(10) PV(14) PV(18) PV(1c) PV(20)
    virtual void AddHandler(void* handler, void* msgType);  // 0x24
};

// 0x14 Send(id, msg, extra).
struct IMsgServer {
    PV(00) PV(04) PV(08) PV(0c) PV(10)
    virtual void Send(uint32_t id, void* msg, void* extra);  // 0x14
};

// ----------------------------------------------------------- ref-count helper
template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) {}
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

// --------------------------------------------------------------- resource key
namespace EA {
namespace ResourceMan {
struct Key {
    uint32_t instanceID;  // +0x00
    uint32_t typeID;      // +0x04
    uint32_t groupID;     // +0x08
};
}  // namespace ResourceMan
}  // namespace EA

// --------------------------------------------------------------- cSPUILayout
struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recurse);      // 0x8105b0
    uint8_t  SetVisibility(bool visible);                    // 0x810590
};

struct cSPUILayoutManager {
    IWindow* GetWorldMainWindow(uint32_t id);                // 0x810620
};

namespace SPUIHelpers {
cSPUILayoutManager* GetLayoutManager();                      // 0x805070
void SetWindowImage(IWindow* w, const EA::ResourceMan::Key* key, int a);  // 0x807bb0
}  // namespace SPUIHelpers

// ------------------------------------------------------------- SP palette UI
struct cSPPalettePageUI {
    uint8_t pad00[0x10];
    void*   m10;                                             // +0x10
};

struct cSPPaletteCategoryUI {
    cSPPalettePageUI* GetPageUI(int index);                  // 0x5c2e50
};

struct cSPPaletteUI {
    cSPPaletteUI();                                          // 0x5cb3b0
    virtual int  AddRef();                                   // 0x00
    virtual int  Release();                                  // 0x04
    void Init(cSPPalette*, IWindow* pOwner, int a, cSPPaletteInfo* pInfo);  // 0x5cb5a0
    void SetVisible(uint8_t visible);                        // 0x5cb180
    void SetCurrentCategoryIndex(int index);                 // 0x5cb240
    void SetFlag(uint8_t v);                                 // 0x5ca900
    int  FindCategoryIndex();                                // 0x5ca9c0
    cSPPaletteCategoryUI* GetSubCategory(int index);         // 0x5cae30
    uint8_t pad04[0x6c - 0x04];                              // sizeof == 0x6c
};

struct cSPPalette : EA::RefCountVTemplate<int> {
    cSPPalette();                                            // 0x5c5e30
    bool Init(const EA::ResourceMan::Key& key, int modelType, int a, int b,
              int c, int d, int e);                          // 0x5c6340
    uint8_t pad08[0x40 - 0x08];                              // sizeof == 0x40
};

// A palette entry record: vptr/refcount, an inline-refcounted object at +8,
// a raw pointer released at slot +4 at +0x10, an AutoRefCount<UIEditor> at
// +0x14 and a uint16 tag at +0x18.
struct cSPPaletteInfo : EA::RefCountVTemplate<int> {
    cSPPaletteInfo();                                        // 0x5c64e0
    AutoRefCount<RefCountInt> m08;                           // +0x08
    uint32_t     m0c;                                        // +0x0c
    RefCount04*  m10;                                        // +0x10
    AutoRefCount<UIEditor> m14;                              // +0x14
    uint16_t     m18;                                        // +0x18
    uint8_t      pad1a[0x34 - 0x1a];                         // sizeof == 0x34
};

struct UIEditor {
    UIEditor();                                              // 0xeccaf0
    virtual void AddRef();                                   // 0x00
    virtual void Release();                                  // 0x04
    PV(08) PV(0c) PV(10) PV(14) PV(18)
    virtual void F1c();                                      // 0x1c
    uint8_t pad04[0xd0 - 0x04];                              // sizeof == 0xd0
};

// ------------------------------------------------------------- child objects
struct OBJ64 : EA::RefCountVTemplate<int> {
    OBJ64();                                                 // 0xf3a470
    virtual uint8_t F4(void* p);                             // 0x10
    PV(14) PV(18)
    uint8_t pad08[0x40 - 0x08];                              // sizeof == 0x40
    void Fn3b0c0();                                          // 0xf3b0c0
};

struct OBJ28 : EA::RefCountVTemplate<int>, IMsgHandler {
    OBJ28() : m0c(0), m10(0), m14(0), m18(0), m1c(0), m20(0), m24(0) {}
    virtual uint8_t F4();                                    // 0x10 (0xb1fbf0)
    virtual void    F5();                                    // 0x14 (0xc2e4e0)
    virtual void    SetVisible(bool visible);                // 0x18 (0xee85e0)
    virtual void    F7(int a);                               // 0x1c (0xee9350)
    uint8_t Msg0(void* sender, void* msg);
    uint8_t Msg1(void* sender, void* msg);

    uint32_t m0c, m10, m14, m18, m1c, m20;
    AutoRefCount<EffectsHandle> m24;                         // +0x24
};

// The value handed to the effect handle's +0x14 call: a status header plus the
// object's position and a rotation matrix.
struct EffectPose {
    uint16_t flags;    // +0x00  ORed 4 then 2 by the caller
    uint16_t refs;     // +0x02  bumped three times
    float    pos[3];   // +0x04
    float    f;        // +0x10
    Matrix3  mat;      // +0x14
};

struct EffectsHandle {
    virtual void V00();
    virtual void Release();                                  // +0x04
    virtual void V08(int a);                                 // +0x08
    virtual void V0c(int a);                                 // +0x0c
    virtual void V10();
    virtual void V14(EffectPose* p);                         // +0x14
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30(bool a);                                // +0x30
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual void V40();
    virtual void V44(int a, float* b, int c);                // +0x44
};

// SP::EffectsManager: slot 0x2c makes a handle and stores it into an
// AutoRefCount<EffectsHandle>* out-parameter.
struct EffectsManager {
    PV(00) PV(04) PV(08) PV(0c) PV(10) PV(14) PV(18) PV(1c) PV(20) PV(24) PV(28)
    virtual void V2c(int a, int b, AutoRefCount<EffectsHandle>* pOut);  // 0x2c
};

// What Space::F32790 returns and Space+0x1b0 holds: the selected object, its
// owner, and two float accessors.
struct EffectSlot {
    void* mpObject;   // +0x00
    void* mpOwner;    // +0x04
    float Fn1ff0();   // 0xf31ff0
    float Fn1b70();   // 0xf31b70
};

// The +0x10 object of an OBJ14: SetVisible is vtable slot 7 (0x1c).
struct Obj10 {
    virtual void V0();                                       // 0x00
    virtual void V4();                                       // 0x04
    virtual void V8();                                       // 0x08
    virtual void Release();                                  // 0x0c
    virtual void V10();                                      // 0x10
    virtual void V14();                                      // 0x14
    virtual void V18();                                      // 0x18
    virtual void SetVisible(uint8_t visible);                // 0x1c
    void Fn6bd0();                                           // 0xee6bd0
};

// The +0x0c object of an OBJ14: Release is vtable slot 1 (0x04).
struct ObjC {
    virtual void AddRef();                                   // 0x00
    virtual void Release();                                  // 0x04
    PV(08)
    void* field10;                                           // +0x10
};

struct OBJ14 : EA::RefCountVTemplate<int> {
    OBJ14() : mpC(0), mp10(0) {}
    virtual uint8_t F4();                                    // 0x10
    virtual uint8_t F5(void* p);                             // 0x14
    virtual void    F6();                                    // 0x18
    virtual void    F7();                                    // 0x1c
    virtual void    SetVisible(uint8_t visible);             // 0x20 (0xee9130)
    uint32_t m08;                                            // +0x08 (untouched)
    ObjC*    mpC;                                            // +0x0c
    Obj10*   mp10;                                           // +0x10
    OBJ14*   ScalarDeletingDtor(unsigned char flags);        // 0xee90e0
};

// ------------------------------------------------------------- record editor
struct Vec12 {
    EA::ResourceMan::Key* mBegin;   // +0x00
    EA::ResourceMan::Key* mEnd;     // +0x04
    EA::ResourceMan::Key* mCap;     // +0x08
    void erase(EA::ResourceMan::Key* pos);                   // 0xeeee40
    void DoInsertValue(EA::ResourceMan::Key* pos, const EA::ResourceMan::Key& v);  // 0x4e3e10
    void push_back(const EA::ResourceMan::Key& v) {
        if (mEnd < mCap) {
            EA::ResourceMan::Key* p = mEnd;
            mEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(mEnd, v);
        }
    }
};

struct VecU32 {
    uint32_t* mBegin;   // +0x00
    uint32_t* mEnd;     // +0x04
    uint32_t* mCap;     // +0x08
    void DoInsertValue(uint32_t* pos, const uint32_t& v);    // 0x4558a0
};

struct VecF32 {
    float* mBegin;      // +0x00
    float* mEnd;        // +0x04
    float* mCap;        // +0x08
    void DoInsertValue(float* pos, const float& v);          // 0x455660
};

struct PlanetRecord {
    uint8_t  pad00[0xbc];
    Vec12    mBc;          // +0xbc  vector<Key>
    uint8_t  padC8[0xf8 - 0xc8];
    VecU32   mF8;          // +0xf8  vector<uint32>
    uint8_t  pad104[0x10c - 0x104];
    float    m10c;         // +0x10c
    VecF32   m110;         // +0x110  vector<float>
};

// The "entry" object managed by the add/remove flow.
struct LayoutRecord {
    virtual void V00();                                      // 0x00
    virtual int  Release();                                  // 0x04
    PV(08) PV(0c) PV(10) PV(14) PV(18)
    virtual uint32_t Fn1c();                                 // 0x1c
};

// 4th base of OBJ174 (vtable 0x148abf0); its subobject lives at OBJ174 + 0x10.
struct OBJ174Ifc4 {
    virtual void Fn(int* arg);                               // 0xee97f0
    uint8_t pad04[0x160 - 0x04];
    LayoutRecord* m170;                                      // subobject + 0x160
};

struct OBJ174 : EA::RefCountVTemplate<int>, IMsgHandler {
    OBJ174();                                                // 0xee7da0
    virtual uint8_t F4(void* p);                             // 0x10 (0xee7f00)
    virtual uint8_t F5(void* p);                             // 0x14 (0xee8110)
    virtual void    SetVisible(bool visible);               // 0x18 (0xee92b0)

    uint32_t mBase3;                                         // +0x0c (3rd base vptr)
    uint32_t mBase4;                                         // +0x10 (4th base vptr)
    uint8_t  pad14[0x160 - 0x14];
    LayoutRecord* mEntry;                                    // +0x160
    uint32_t      m164;                                      // +0x164
    cSPUILayout*  mLayout;                                   // +0x168
    uint32_t      m16c;                                      // +0x16c
    LayoutRecord* m170;                                      // +0x170

    uint8_t Msg0(void* sender, void* msg);
    uint8_t Msg1(void* sender, void* msg);

    void Update();                                           // 0xee8d80
    void AddEntry(LayoutRecord* e);                          // 0xee95a0
    void SetEntry(LayoutRecord* e, EA::ResourceMan::Key* arg);  // 0xee9690
    void Fn8460(IWindow* w);                                 // 0xee8460
    void Fn7910(LayoutRecord* e, int* pIdx, uint8_t* pFlag); // 0xee7910
};

// The bigger "space" object reached through *(0x16c7aa4)+0x18.
struct Space {
    uint8_t pad00[0x10];
    RefCountInt* m10;                                        // +0x10
    uint8_t pad14[0x160 - 0x14];
    LayoutRecord* m160;                                      // +0x160
    uint8_t pad164[0x168 - 0x164];
    cSPUILayout* m168;                                       // +0x168
    uint8_t pad16c[0x1b0 - 0x16c];
    void* m1b0;                                              // +0x1b0
    void  F33BF0();                                          // 0xf33bf0
    void  F34560();                                          // 0xf34560
    void* F32790(void* p);                                   // 0xf32790
    void  FnC2E4E0();                                        // 0xc2e4e0
};

// The "Sculpt" palette tool.
struct C40 : EA::RefCountVTemplate<int>, IMsgHandler {
    virtual uint8_t Setup(int a);                            // 0x10 (0xee8860)
    virtual void    F5fn();                                  // 0x14
    virtual void    SetVisible(uint8_t visible);             // 0x18 (0xee8cb0)
    virtual void    F7fn();                                  // 0x1c

    uint8_t Msg0(void* sender, void* msg);
    uint8_t Msg1(void* sender, void* msg);

    AutoRefCount<OBJ14>        mObj14;       // +0x0c
    AutoRefCount<OBJ28>        mObj28;       // +0x10
    AutoRefCount<OBJ64>        mObj64;       // +0x14
    AutoRefCount<OBJ174>       mObj174;      // +0x18
    AutoRefCount<cSPPalette>   mPalette;     // +0x1c
    AutoRefCount<cSPPaletteUI> mPalUI;       // +0x20
    AutoRefCount<UIEditor>     mEditor;      // +0x24
    int   mState;                            // +0x28
    void* mC2c;                              // +0x2c
    void* mC30;                              // +0x30
    void* mC34;                              // +0x34
    void* mC38;                              // +0x38
    void* mC3c;                              // +0x3c

    C40();                                                   // 0xee9180
    void Update();                                           // 0xee9260
    void Fn7b40(int idx, uint8_t visible);                   // 0xee7b40
};

// ------------------------------------------------------------------- callees
void* operator new(unsigned int size, const char* pName, int flags,
                   unsigned debugFlags, const char* file, int line);  // 0xf473a0
void  operator delete(void* p);                             // 0xf47380
void* EAAllocate(uint32_t size, const char* pName, int a, int b, int c, int d);  // 0xf473a0
void* MessageServer();                                      // 0x67dcc0
void* EffectsManagerPtr();                                  // 0x67ddd0
void  RemoveHandler(void* h, void* a, void* b, void* c, void* d);  // 0x571db0
int   FUN_00ee7cb0(uint32_t key, int* a, int* b);           // 0xee7cb0
void* GetActivePlanet();                                    // 0x1021260
void* GetActivePlanetRecord();                              // 0x10212a0
// Three __thiscall thunks reached through the planet record: their single
// argument arrives in ECX.
struct EAThunk {
    void* Fn414c0();                                        // 0x8414c0
    void  FnC2f80();                                        // 0xc82f80
    void  Fn2bbe0();                                        // 0xb2bbe0
};
void* FUN_00b3d3b0();                                       // 0xb3d3b0
void  FUN_00f33bf0(void* p);                                // 0xf33bf0
void  FUN_00f34560(void* p);                                // 0xf34560
void  FUN_00f32790(void* p, void* q);                       // 0xf32790
void* FUN_00efe5b0();                                       // 0xefe5b0
void* FUN_00b18e00(void* p);                                // 0xb18e00
void  FUN_00f31ff0(void* p);                                // 0xf31ff0
void  FUN_00f31b70(void* p);                                // 0xf31b70
void  eastl_move(void* dst, const void* src, uint32_t n);   // 0x11e0744
void  Matrix3_AssignFrom(void* self, const void* q);        // 0x41cb40
void* Matrix3FromQuaternion(void* out, void* q);            // 0x59c190
void  cRegNode_Construct(void* p, void* arg);               // 0x692f60
uint8_t cRegNode_Flag(void* p);                             // 0xab30c0
void  cRegNode_Fallback(void* p);                           // 0x692850
int   atexit(void (*fn)());                                 // 0x11e07ef
double floor(double x);                                     // 0x11e0906

// The 0x16c7820 / 0x16c780c static registration nodes of C40::C40.
struct cRegNode {
    void  Construct(void* arg);                             // 0x692f60
    uint8_t Flag();                                         // 0xab30c0
    void  Fallback();                                       // 0x692850
};
extern void FUN_013c8a60();                                 // 0x13c8a60 atexit callback
extern void FUN_013c8a50();                                 // 0x13c8a50 atexit callback
extern uint32_t gRegFlags;                                  // 0x16c7820 registration guard

extern float gVec3X;       // 0x16c7894
extern float gVec3Y;       // 0x16c7898
extern float gVec3Z;       // 0x16c789c
extern void* gTableA[15];  // 0x148aac0
extern void* gTableB[15];  // 0x148aafc
extern void* gSelObject;   // 0x16c7824

struct TutorialsUI {
    void ToggleHint(int a, int b);      // 0xefbbe0
    void ClearPending();                // 0xef72b0
};

static inline TutorialsUI* GetTutorialsUI() {
    return *(TutorialsUI**)(*(int*)0x16c7aa4 + 0xd4);
}
static inline void* GetSpacePtr() {
    return *(void**)(*(int*)0x16c7aa4 + 0x18);
}

// --------------------------------------------------------------- vtable glue
template <class T, int Off>
static inline void vcallv(T* p) {
    typedef void (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)();
}
template <class T, int Off, class A>
static inline void vcallA(T* p, A a) {
    typedef void (T::*PMF)(A);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)(a);
}
template <class T, int Off, class A, class B, class C>
static inline void vcallABC(T* p, A a, B b, C c) {
    typedef void (T::*PMF)(A, B, C);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; (p->*f)(a, b, c);
}
template <class R, class T, int Off>
static inline R vcallR(T* p) {
    typedef R (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn; return (p->*f)();
}

// ================================================================= functions

// @ 0x00ee8860
uint8_t C40::Setup(int a)
{
    (void)a;
    mState = -1;

    cSPPalette* pal = new ("Simulator/Scenario/SculptUI", 0, 0, 0, 0) cSPPalette();
    mPalette = pal;

    cSPPaletteUI* palUI = new ("Simulator/Scenario/SculptUI", 0, 0, 0, 0) cSPPaletteUI();
    mPalUI = palUI;

    UIEditor* ed = new ("Editor", 0, 0, 0, 0) UIEditor();
    mEditor = ed;
    mEditor->F1c();

    EA::ResourceMan::Key key;
    key.instanceID = 0xdc;
    key.typeID = 0xb1b104;
    key.groupID = 0x406b6a00;
    if (mPalette->Init(key, -1, 0, 0, 0, 0, 0)) {
        AutoRefCount<cSPPaletteInfo> info =
            new ("Editor", 0, 0, 0, 0) cSPPaletteInfo();
        info->m08 = (RefCountInt*)((Space*)GetSpacePtr())->m10;
        info->m14 = mEditor.mpObject;
        if (info->m10) {
            RefCount04* p = info->m10;
            info->m10 = 0;
            p->Release();
        }
        info->m18 = 0x268a;
        mPalUI->Init(mPalette.mpObject,
                     SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x8d0f4fb),
                     0, info);
        mPalUI->SetCurrentCategoryIndex(0);
        mPalUI->SetFlag(1);
    }

    OBJ64* o64 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ64();
    mObj64 = o64;
    if (!mObj64->F4(mPalUI->GetSubCategory(3)->GetPageUI(0)->m10)) {
        mObj64 = 0;
    }

    OBJ174* o174 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ174();
    mObj174 = o174;
    if (!mObj174->F4(mPalUI->GetSubCategory(2)->GetPageUI(0)->m10)) {
        mObj174 = 0;
    }

    OBJ28* o28 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ28();
    mObj28 = o28;
    if (!mObj28->F4()) {
        mObj28 = 0;
    }

    OBJ14* o14 = new ((const char*)0x13f6b3c, 0, 0, 0, 0) OBJ14();
    mObj14 = o14;
    if (!mObj14->F5(mPalUI->GetSubCategory(1)->GetPageUI(0)->m10)) {
        mObj14 = 0;
    }
    return 1;
}

// @ 0x00ee8cb0
void C40::SetVisible(uint8_t visible)
{
    if (mPalUI) mPalUI->SetVisible(visible);
    if (visible) {
        uint8_t* p = (uint8_t*)this + 8;
        void* h = MessageServer();
        mC2c = h;
        mC30 = p;
        mC34 = (void*)0x15ac73c;
        mC38 = (void*)1;
        mC3c = 0;
        if (h && p) {
            ((IMsgDispatcher*)h)->AddHandler(p, *(void**)0x15ac73c);
        }
        mPalUI->FindCategoryIndex();
    } else {
        if (mC2c) {
            RemoveHandler(mC2c, mC30, mC34, mC38, mC3c);
            mC2c = 0;
        }
    }
    Fn7b40(mPalUI->FindCategoryIndex(), visible);
}

// @ 0x00ee8d80
void OBJ174::Update()
{
    PlanetRecord* rec = (PlanetRecord*)GetActivePlanetRecord();

    {
        IWindow* w = mLayout->FindWindowByID(0x72bfdfd, 1);
        if (w) {
            IWindow* c = (IWindow*)w->AsInterface(0xf00a8a0);
            if (c) {
                int n = c->V30(0);
                c->V1c((int)((float)n * rec->m10c));
            }
        }
    }

    uint32_t id = 0x72c2820;
    for (int k = 9; k != 0; --k) {
        IWindow* w = mLayout->FindWindowByID(id, 1);
        if (w) {
            int idx = FUN_00ee7cb0(id, 0, 0);
            bool found = (idx != -1);
            IWindow* c = (IWindow*)w->Vf0(0x73d54a0, 1);
            if (c) c->V7c(1, found ? 0 : 1);
            IWindow* c2 = (IWindow*)w->Vf0(0x4a1cb6e, 1);
            if (c2) c2->V7c(1, *(uint32_t*)&rec->m10c);
            if (found) {
                EA::ResourceMan::Key k;
                k.instanceID = rec->mBc.mBegin[idx].instanceID;
                k.typeID = 0x2f7d0004;
                k.groupID = rec->mBc.mBegin[idx].groupID;
                SPUIHelpers::SetWindowImage(w, &k, -1);
            }
            Fn8460(w);
        }
        ++id;
    }

    if (!mLayout) return;
    void* space = GetSpacePtr();
    if (!space) return;
    LayoutRecord* e = ((Space*)space)->m160;
    int idx = -1;
    uint8_t flag = 0;
    Fn7910(e, &idx, &flag);

    for (uint32_t i = 0; i < 0xf; i++) {
        IWindow* w = mLayout->FindWindowByID(0x16b18090 + i, 1);
        if (w) {
            IWindow* q = (IWindow*)w->AsInterface(0x8ed27e7a);
            if (q) q->V28(4, i == (uint32_t)idx);
        }
    }

    IWindow* last = mLayout->FindWindowByID(0x16b1858d, 1);
    if (last) {
        int i1 = -1;
        int i2 = i1 - 1;
        for (int i = 0; i < 0xf; i++) { if (gTableB[i] == e) { i1 = i; break; } }
        for (int i = 0; i < 0xf; i++) { if (gTableA[i] == e) { i2 = i; break; } }
        bool diff = (i2 != i1);
        bool on = flag ? diff : false;
        IWindow* q = (IWindow*)last->AsInterface(0x8ed27e7a);
        if (q) q->V28(4, on);
        last->V7c(2, diff);
    }

    IWindow* tw = mLayout->FindWindowByID(0x7d61ff2, 1);
    if (tw && tw->V10()) {
        float* hp = ((IWindow*)tw->V10())->V38();
        float a0 = hp[0];
        float a2 = hp[2];
        float* tp = tw->V38();
        float c0 = tp[0];
        float c2 = tp[2];
        tw->V70((float)floor((double)(a0 + ((a2 - a0) - (c2 - c0)) * 0.5f)));
    }
}

// @ 0x00ee90e0
OBJ14* OBJ14::ScalarDeletingDtor(unsigned char flags)
{
    *(void**)this = (void*)0x148ac5c;
    _ReadWriteBarrier();
    if (mp10) mp10->Release();
    if (mpC) mpC->Release();
    *(void**)this = (void*)0x13ec458;
    if (flags & 1) operator delete(this);
    return this;
}

// @ 0x00ee9130
void OBJ14::SetVisible(uint8_t visible)
{
    if (visible) {
        GetTutorialsUI()->ToggleHint(0x8f, 0x90);
        Obj10* p = mp10;
        if (p) p->Fn6bd0();
    }
    Obj10* p10 = mp10;
    if (p10) p10->SetVisible(visible);
}

// @ 0x00ee9180
C40::C40()
    : mObj14(0), mObj28(0), mObj64(0), mObj174(0), mPalette(0), mPalUI(0), mEditor(0)
{
    mC2c = 0;
    mC30 = 0;
    mC34 = 0;
    mC38 = 0;
    mC3c = 0;
    if ((gRegFlags & 1) == 0) {
        gRegFlags |= 1;
        ((cRegNode*)0x16c780c)->Construct(0);
        *(void**)0x16c780c = (void*)0x148aba8;
        atexit(FUN_013c8a60);
    }
    if (((cRegNode*)0x16c780c)->Flag() == 0)
        ((cRegNode*)0x16c780c)->Fallback();
    if ((gRegFlags & 2) == 0) {
        gRegFlags |= 2;
        ((cRegNode*)0x16c77f8)->Construct(0);
        *(void**)0x16c77f8 = (void*)0x148abb8;
        atexit(FUN_013c8a50);
    }
    if (((cRegNode*)0x16c77f8)->Flag() == 0)
        ((cRegNode*)0x16c77f8)->Fallback();
}

// @ 0x00ee9260
void C40::Update()
{
    switch (mState) {
        case 1:
            {
                OBJ14* p = mObj14.mpObject;
                Obj10* q = p->mp10;
                if (q) q->Fn6bd0();
            }
            break;
        case 2:
            mObj174->Update();
            break;
        case 3:
            mObj64->Fn3b0c0();
            break;
    }
    ((IMsgServer*)MessageServer())->Send(0x743b6fa, 0, 0);
}

// @ 0x00ee92b0
void OBJ174::SetVisible(bool visible)
{
    if (mLayout) mLayout->SetVisibility(visible);
    if (visible) {
        uint32_t i = 0;
        do {
            IWindow* w = mLayout->FindWindowByID(0x16b18090 + i, 1);
            if (w) {
                uint8_t* p = (uint8_t*)this + 8;
                w->V104(p);
            }
            ++i;
        } while (i < 0xf);
        IWindow* w = mLayout->FindWindowByID(0x16b1858d, 1);
        if (w) {
            uint8_t* p = (uint8_t*)this + 8;
            w->V104(p);
        }
        Update();
        GetTutorialsUI()->ToggleHint(0x9b, 0x9c);
    }
}

// @ 0x00ee9350
void OBJ28::F7(int a)
{
    (void)a;
    Space* space = (Space*)GetSpacePtr();
    EffectSlot* slot = (EffectSlot*)space->F32790(FUN_00efe5b0());
    EffectSlot* cur = (EffectSlot*)space->m1b0;
    bool created;
    if (cur == slot || slot == 0) {
        created = true;
    } else {
        created = false;
        cur = slot;
    }
    void* obj = cur ? cur->mpObject : 0;
    void* owner = cur ? cur->mpOwner : 0;

    if (gSelObject != obj) {
        if (m24.mpObject) {
            m24.mpObject->V0c(0);
            if (m24.mpObject) {
                EffectsHandle* p = m24.mpObject;
                m24.mpObject = 0;
                p->Release();
            }
        }
        gSelObject = obj;
        if (obj) {
            EffectsManager* em = (EffectsManager*)EffectsManagerPtr();
            if (m24.mpObject) {
                EffectsHandle* p = m24.mpObject;
                m24.mpObject = 0;
                p->Release();
            }
            em->V2c(*(int*)((uint8_t*)owner + 0x3c), 0, &m24);
            if (m24.mpObject) m24.mpObject->V08(0);
        }
    }

    if (m24.mpObject) {
        uint8_t* t = (uint8_t*)FUN_00b18e00(obj);
        uint8_t c = t[0x6e];

        EffectPose pose;
        pose.flags = 0;
        pose.refs = 0;
        pose.pos[0] = gVec3X;
        pose.pos[1] = gVec3Y;
        pose.pos[2] = gVec3Z;
        pose.f = 1.0f;
        Matrix3_AssignFrom(&pose.mat, (const void*)0x16c7870);

        float* v = vcallR<float*, VObj, 0x2c>((VObj*)t);
        pose.pos[0] = v[0];
        pose.pos[1] = v[1];
        pose.pos[2] = v[2];
        pose.flags |= 4;
        ++pose.refs;

        void* qq = vcallR<void*, VObj, 0x30>((VObj*)t);
        Matrix3 tmp;
        float* r = (float*)Matrix3FromQuaternion(&tmp, qq);
        for (int i = 0; i < 9; ++i) pose.mat.m[i] = r[i];
        pose.flags |= 2;
        ++pose.refs;

        pose.f = cur->Fn1ff0();
        ++pose.refs;
        m24.mpObject->V14(&pose);

        float f = cur->Fn1b70();
        if (!created) f *= 0.25f;
        m24.mpObject->V44(4, &f, 1);
        m24.mpObject->V30(c != 0);
    }
    space->FnC2E4E0();
}

// @ 0x00ee95a0
void OBJ174::AddEntry(LayoutRecord* e)
{
    void* planet = GetActivePlanet();
    PlanetRecord* rec = (PlanetRecord*)GetActivePlanetRecord();
    int idx = FUN_00ee7cb0(e->Fn1c(), 0, 0);
    if (idx == -1) return;

    Space* space = (Space*)GetSpacePtr();
    space->F33BF0();

    rec->mBc.erase(rec->mBc.mBegin + idx);
    {
        uint32_t* p = rec->mF8.mBegin + idx;
        uint32_t* q = p + 1;
        if (q < rec->mF8.mEnd) {
            eastl_move(p, q, (uint32_t)((uint8_t*)rec->mF8.mEnd - (uint8_t*)q));
        }
        rec->mF8.mEnd--;
    }
    {
        float* p = rec->m110.mBegin + idx;
        float* q = p + 1;
        if (q < rec->m110.mEnd) {
            eastl_move(p, q, (uint32_t)((uint8_t*)rec->m110.mEnd - (uint8_t*)q));
        }
        rec->m110.mEnd--;
    }
    ((EAThunk*)((EAThunk*)planet)->Fn414c0())->FnC2f80();
    ((EAThunk*)FUN_00b3d3b0())->Fn2bbe0();
    space->F34560();
    Update();
}

// @ 0x00ee9690
void OBJ174::SetEntry(LayoutRecord* e, EA::ResourceMan::Key* arg)
{
    void* planet = GetActivePlanet();
    PlanetRecord* rec = (PlanetRecord*)GetActivePlanetRecord();
    int a, b;
    int idx = FUN_00ee7cb0(e->Fn1c(), &a, &b);

    Space* space = (Space*)GetSpacePtr();
    space->F33BF0();

    if (idx == -1) {
        rec->mBc.push_back(*arg);
        if (rec->mF8.mEnd < rec->mF8.mCap) {
            *rec->mF8.mEnd++ = b;
        } else {
            rec->mF8.DoInsertValue(rec->mF8.mEnd, b);
        }
        if (rec->m110.mEnd < rec->m110.mCap) {
            *rec->m110.mEnd++ = 1.0f;
        } else {
            rec->m110.DoInsertValue(rec->m110.mEnd, 1.0f);
        }
    } else {
        rec->mBc.mBegin[idx] = *arg;
    }
    ((EAThunk*)((EAThunk*)planet)->Fn414c0())->FnC2f80();
    ((EAThunk*)FUN_00b3d3b0())->Fn2bbe0();
    space->F34560();
    Update();
}

// @ 0x00ee97f0
void OBJ174Ifc4::Fn(int* arg)
{
    if (*arg) {
        ((OBJ174*)((uint8_t*)this - 0x10))->SetEntry(m170, (EA::ResourceMan::Key*)arg);
    }
    if (m170) {
        LayoutRecord* e = m170;
        m170 = 0;
        e->Release();
    }
    GetTutorialsUI()->ClearPending();
}
