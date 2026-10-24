// Slice s00eccaf0 -- cSPPaletteItemRollover-style info-line rollover update (0x00ecd0c0).
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc: the function has no EH frame).
//
// The function fills the "info line tray" of a palette-item rollover. It builds, on the stack, three
// info-line descriptors (a name hash, two or three specialised 0x28-byte elements and an array of
// default 0x28-byte elements), hands each to the tray, then pushes the two formatting arguments
// (two strings in the error case, two ints in the creature-stance case) to the rollover window.
#include "types.h"


// ---------------------------------------------------------------- 0x28-byte descriptor element
// Default state (inlined ctor, out-of-line copy at 0x00ecc920 is used by the array ctor iterator).
struct Elem28 {
    uint32_t d0;      // +0x00 text id
    uint32_t d4;      // +0x04 getter function pointer (or 0)
    uint32_t d8;      // +0x08 text id (second)
    union {
        uint32_t d0c; // +0x0c flags
        struct { uint16_t w0c; uint16_t w0e; };
    };
    uint32_t d10;     // +0x10
    float f14;        // +0x14
    float f18;        // +0x18
    uint32_t d1c;     // +0x1c limit
    uint32_t d20;     // +0x20
    uint32_t d24;     // +0x24

    Elem28()
    {
        d0 = 0;
        d4 = 0;
        d8 = 0;
        d0c = 0;
        w0e = 0;
        d10 = 0;
        f14 = 0.0f;
        f18 = 0.0f;
        d1c = 0xfffff;
        d20 = 0xffffffff;
        d24 = 0xffffffff;
    }
};

// Array elements are default-constructed by the compiler-generated vector constructor iterator
// (0x00401930, stdcall) calling the out-of-line Elem28 ctor at 0x00ecc920 (fastcall-shaped thiscall).
struct Elem28Raw { uint32_t d[10]; };
extern "C" void __stdcall vector_constructor_iterator(void* p, unsigned size, int count, void* ctor);   // 0x00401930
extern "C" void __fastcall Elem28_ctor(void* self);   // 0x00ecc920
#define CONSTRUCT_ARRAY(a, n) vector_constructor_iterator((a), sizeof(Elem28Raw), (n), (void*)&Elem28_ctor)

namespace EA { namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t nInitialValue, int charCase);   // 0x00932e80
} }

static __forceinline uint32_t HashName(const char* name)
{
    return EA::Hash::FNV1_String8(name, 0x811c9dc5, 1);
}

// Descriptor with one specialised element, one default element and nine array elements (0x1c0 bytes).
struct InfoDesc9 {
    uint32_t mUnused;
    uint32_t mHash;
    Elem28 e0;
    Elem28 e1;
    Elem28Raw arr[9];

    __forceinline InfoDesc9(const char* name) : mUnused(0), mHash(HashName(name)) {}
    __forceinline void Set0(uint32_t key, uint32_t getter, uint32_t key2, uint32_t flags)
    {
        e0.d0 = key;
        e0.d4 = getter;
        e0.d8 = key2;
        e0.d0c = flags;
        e0.d1c = 0xffffffff;
    }
    __forceinline void InitArray() { CONSTRUCT_ARRAY(arr, 9); }
};

// Descriptor with two specialised elements, one default element and eight array elements (0x1c0 bytes).
struct InfoDesc8 {
    uint32_t mUnused;
    uint32_t mHash;
    Elem28 e0;
    Elem28 e1;
    Elem28 e2;
    Elem28Raw arr[8];

    __forceinline InfoDesc8(const char* name) : mUnused(0), mHash(HashName(name)) {}
    __forceinline void Set0(uint32_t key, uint32_t getter, uint32_t key2, uint32_t flags)
    {
        e0.d0 = key;
        e0.d4 = getter;
        e0.d8 = key2;
        e0.d0c = flags;
        e0.d1c = 0xffffffff;
    }
    __forceinline void Set1(uint32_t key, uint32_t getter, uint32_t key2, uint32_t flags)
    {
        e1.d0 = key;
        e1.d4 = getter;
        e1.d8 = key2;
        e1.d0c = flags;
        e1.d1c = 0xffffffff;
    }
    __forceinline void InitArray() { CONSTRUCT_ARRAY(arr, 8); }
};

// ---------------------------------------------------------------- getter callbacks stored in the descriptors
extern "C" void FUN_00eccb70();   // 0x00eccb70 (getter used for the error texts)
extern "C" void FUN_00eccce0();   // 0x00eccce0 (getter used for the item texts)
#define GETTER_ERR ((uint32_t)&FUN_00eccb70)
#define GETTER_ITEM ((uint32_t)&FUN_00eccce0)

// ---------------------------------------------------------------- strings
namespace SP {
class cString { public:
    uint32_t pad[5];
    cString();                    // 0x006b5060
    ~cString();                   // 0x006b5240
    const wchar_t* GetText();     // 0x006b55c0
};
}

// two cStrings plus a few extra fields (ctor 0x005a7810)
struct StrPair {
    SP::cString first;            // +0x00
    SP::cString second;           // +0x14 (gap after the 0x1c-byte cString)
    uint32_t pad[3];
    StrPair();                    // 0x005a7810
};

// ---------------------------------------------------------------- tray and rollover
struct InfoTray {
    void Clear();                                                 // 0x0080cdd0
    void AddLine(const void* desc);                               // 0x0080ce20
    void Show(void* window, float a, float b, uint32_t* args);    // 0x0080c5d0
};

struct ArgSource {
    void* Get();                                                  // 0x01137690
};
struct AllocLookup {
    void* Find(void* allocator);                                  // 0x00f3e8a0
};
struct TypeProvider {
    void* GetAllocator();                                         // 0x007f54d0
};

struct Globals { char pad[0x74]; AllocLookup* lookup; };
extern Globals* g_globals;                                        // 0x016c7aa4

extern const float g_rollWidth;                                   // 0x013f1f04
extern const float g_rollHeight;                                  // 0x01489528
int __cdecl ScenarioTutorials_GetActive(void);                    // 0xefc520

struct Query { int pad[2]; void* sink; };

struct Rollover {
    char pad0[0x78];
    void* mWinPrice;                                              // +0x78
    char pad1[0xc8 - 0x7c];
    InfoTray* mTray;                                              // +0xc8

    void Reset();                                                 // 0x005ed650
    bool Init();                                                  // 0x005ed420 (cSPPaletteItemRollover::Init)
    void Select(uint32_t keyA, uint32_t keyB);                    // 0x00827fa0
    void SetFlag(int f);                                          // 0x00828020
    void ForceVisibleLocation();                                  // 0x00828110

    void Update(ArgSource* src, void* ctx, Query* q);             // 0x00ecd0c0
};

typedef void* (__thiscall *VFn0)(void*);
typedef void* (__thiscall *VFn1)(void*, uint32_t);
typedef void* (__thiscall *VFn2)(void*, uint32_t, void*);

static __forceinline void** VT(void* o) { return *(void***)o; }

// @ 0x00ecd0c0
void Rollover::Update(ArgSource* src, void* ctx, Query* q)
{
    StrPair strs;
    int result = 1;
    if (q->sink)
        result = (int)((VFn2)VT(q->sink)[0x10 / 4])(q->sink, (uint32_t)ctx, &strs);
    Reset();
    if (result != 1) {
        Select(0x958a1c94, 0x40464100);
        if (!Init())
            return;
        InfoDesc9 header("RO_CastPalErrorHeader");
        header.Set0(0x440b6b8, GETTER_ERR, 0x440b6b8, 0x411);
        header.InitArray();
        InfoDesc9 icon("RO_CastPalErrorComplexityIcon");
        icon.Set0(0x64a7e23, 0, 0, 0x811);
        icon.InitArray();
        InfoDesc9 desc("RO_CastPalErrorDescription");
        desc.Set0(0x64a8a82, GETTER_ERR, 0x64a8a82, 0x420);
        desc.InitArray();

        mTray->Clear();
        mTray->AddLine(&header);
        mTray->AddLine(&icon);
        mTray->AddLine(&desc);
        uint32_t args[2];
        args[0] = (uint32_t)strs.second.GetText();
        args[1] = (uint32_t)strs.first.GetText();
        mTray->Show(mWinPrice, g_rollWidth, g_rollHeight, args);
    
    } else {
        Select(0x614888df, 0x40464100);
        if (!Init())
            return;
        void* obj = src->Get();
        void* prov;
        if (obj)
            prov = ((VFn1)VT(obj)[0xc / 4])(obj, 0x722de52);
        else
            prov = 0;
        int type = (int)((VFn0)VT(prov)[0x28 / 4])(prov);
        if (type != (int)0xb10e526f && type != (int)0xe34e8a60 && type != 0x5b3d1d0d)
            return;

        InfoDesc8 stance("RO_CastPalItemStance");
        stance.Set0(0x64a8a82, GETTER_ITEM, 0x64a8a82, 0x411);
        stance.Set1(0x7971b38, GETTER_ITEM, 0x7971b38, 0x809);
        stance.InitArray();
        InfoDesc8 team1("RO_CastPalItemTeam");
        team1.Set0(0x7a02ed0, GETTER_ITEM, 0x7a02ed0, 0x411);
        team1.Set1(0x7a02ee0, GETTER_ITEM, 0x7a02ee0, 0x809);
        team1.InitArray();
        InfoDesc8 team2("RO_CastPalItemTeam");
        team2.Set0(0x7a02ed0, GETTER_ITEM, 0x7a02ed0, 0x411);
        team2.Set1(0x7a02ee0, 0, 0, 0x901);
        team2.InitArray();

        mTray->Clear();
        void* alloc = ((TypeProvider*)prov)->GetAllocator();
        char* rec = (char*)g_globals->lookup->Find(alloc);
        rec = *(char**)(rec + 0x70) + ScenarioTutorials_GetActive() * 0x4e0;
        if (type == (int)0xe34e8a60 || type == 0x5b3d1d0d)
            mTray->AddLine(&stance);
        if (*(int*)(rec + 0x4a8) == 1)
            mTray->AddLine(&team2);
        else
            mTray->AddLine(&team1);
        uint32_t args[2];
        if (*(char*)(rec + 0x4c8))
            args[0] = 6;
        else
            args[0] = *(uint32_t*)(rec + 0x4ac);
        args[1] = *(uint32_t*)(rec + 0x4a8);
        mTray->Show(mWinPrice, g_rollWidth, g_rollHeight, args);
    }
    SetFlag(1);
    {
        void* parent = ((VFn0)VT(mWinPrice)[0x10 / 4])(mWinPrice);
        if (parent)
            ((VFn1)VT(parent)[0xe8 / 4])(parent, (uint32_t)mWinPrice);
    }
    ForceVisibleLocation();
}

// ===========================================================================
// 00eccaf0 / 00eccb20 -- palette-item rollover ctor / scalar deleting dtor
// ===========================================================================
extern "C" char g_vtblRolloverIWinProc[];                     // 0x014894c0
extern "C" char g_vtblRolloverRefCount[];                      // 0x014894b0

struct CPLBase {
    void Dtor();                                               // 0x00828670  ??1CPL
};

// Object whose vtable releases at +0x08.
struct IObj3 {
    virtual void f0();                                         // +0x00
    virtual void f4();                                         // +0x04
    virtual void Release();                                    // +0x08
};

struct RolloverBase {
    void Ctor(bool flag);                                      // 0x005ed360
};

struct RolloverItem {
    void** volatile mVtblIWinProc;                             // +0x00
    void** volatile mVtblRefCount;                             // +0x04
    char pad08[0xa8];                                          // +0x08 .. +0xaf
    IObj3* mObjB0;                                             // +0xb0
    IObj3* mObjB4;                                             // +0xb4
    char padB8[0x10];                                          // +0xb8 .. +0xc7
    void* mTray;                                               // +0xc8

    RolloverItem();
    RolloverItem* Delete(int flags);
};

// @ 0x00eccaf0
RolloverItem::RolloverItem()
{
    ((RolloverBase*)this)->Ctor(false);
    mVtblIWinProc = (void**)&g_vtblRolloverIWinProc;
    mVtblRefCount = (void**)&g_vtblRolloverRefCount;
    mTray = 0;
}

// @ 0x00eccb20
RolloverItem* RolloverItem::Delete(int flags)
{
    mVtblIWinProc = (void**)&g_vtblRolloverIWinProc;
    mVtblRefCount = (void**)&g_vtblRolloverRefCount;
    if (mObjB4)
        mObjB4->Release();
    if (mObjB0)
        mObjB0->Release();
    ((CPLBase*)this)->Dtor();
    if (flags & 1)
        operator delete(this);
    return this;
}

// ===========================================================================
// 00eccb70 / 00eccbf0 -- Variant getters of the palette item info line
// ===========================================================================
namespace EA {
struct Variant {
    char mData[0x10];                                          // +0x00 storage
    uint16_t mFlags;                                           // +0x10
    uint16_t mTypeId;                                          // +0x12

    Variant() : mFlags(0), mTypeId(0) {}
    Variant& operator=(const Variant& x);                      // 0x00542b80
    void Destruct(bool bReconstruct);                          // 0x0093db80
    void Construct(unsigned short typeId, unsigned short flags, const void* pData, unsigned int nSize,
                   unsigned int nCount);                       // 0x0093dd80
};
}

// In-place filler of a Variant (0x00ecc8b0: thiscall, one value argument).
struct VariantFill {
    void Set(uint32_t value);                                  // 0x00ecc8b0
};

// Property record: the dispatch key word lives at +0x0c.
struct PropKey {
    char pad00[0xc];                                           // +0x00 .. +0x0b
    uint32_t mKind;                                            // +0x0c
};

// @ 0x00eccb70
EA::Variant* __cdecl FUN_00eccb70(EA::Variant* ret, const PropKey* prop, const uint32_t* args)
{
    EA::Variant tmp;
    if (prop->mKind != 0x440b6b8) {
        if (prop->mKind != 0x64a8a82)
            goto after;
        ((VariantFill*)&tmp)->Set(args[0]);
    } else {
        ((VariantFill*)&tmp)->Set(args[1]);
    }
after:
    ret->mFlags = 0;
    ret->mTypeId = 0;
    *ret = tmp;
    if (tmp.mFlags & 4)
        tmp.Destruct(false);
    return ret;
}

namespace SP {
// EA::EString (0x54 bytes): begin/end/capacity, an owning stack buffer at +0x14.
struct EString {
    wchar_t* mpBegin;                                          // +0x00
    wchar_t* mpEnd;                                            // +0x04
    wchar_t* mpCapacity;                                       // +0x08
    char pad0c[4];                                             // +0x0c
    wchar_t* mpStack;                                          // +0x10
    wchar_t mStack[0x20];                                      // +0x14

    EString* Construct(const wchar_t* text);                   // 0x006743f0
    EString* AssignFrom(EString* other);                       // 0x00672880
    void InitEmpty() {
        mpStack = mStack;
        mpBegin = mStack;
        mpEnd = mStack;
        mpCapacity = mStack + 0x20;
        mStack[0] = 0;
    }
    ~EString() {
        if ((((char*)mpEnd - (char*)mpBegin) & ~1) > 2 && mpBegin && mpBegin != mpStack)
            operator delete(mpBegin);
    }
};

// 3-argument cString ctor variant (same 0x14-byte layout as cString).
struct cString3 {
    uint32_t pad[5];
    cString3(uint32_t id, uint32_t textId, const wchar_t* text);   // 0x006b5770
    const wchar_t* GetText();                                      // 0x006b55c0
    ~cString3();                                                   // 0x006b5240
};
}

struct IValueSet {
    virtual void f0();                                         // +0x00
    virtual void Release();                                    // +0x04
};

// One property record of the manager's value list (12 bytes).
struct PropEntry {
    uint32_t mId;                                              // +0x00
    uint32_t mPad04;                                           // +0x04
    uint32_t mTextId;                                          // +0x08
};

struct PropManager {
    virtual bool GetRange(uint32_t a, uint32_t b, IValueSet** out);   // vtable +0x2c
};

extern "C" PropManager* __cdecl GetPropertyManager();          // 0x0067de30
extern "C" uint32_t g_propKeyA;                                // 0x015abed8
extern "C" uint32_t g_propKeyB;                                // 0x015abee0
extern "C" bool __cdecl CollectValues(IValueSet* set, uint32_t key, uint32_t* count, PropEntry** entries);   // 0x006a0ae0

// @ 0x00eccbf0
SP::EString* __cdecl FUN_00eccbf0(SP::EString* ret, uint32_t key, uint32_t index)
{
    IValueSet* set = 0;
    bool built = false;
    PropManager* mgr = GetPropertyManager();
    if (set) {
        set = 0;
        set->Release();
    }
    if (mgr->GetRange(g_propKeyA, g_propKeyB, &set) && set) {
        PropEntry* entries;
        uint32_t count;
        CollectValues(set, key, &count, &entries);
        if (index < count) {
            SP::cString3 text(entries[index].mId, entries[index].mTextId, 0);
            ret->Construct(text.GetText());
            text.~cString3();
            built = true;
        }
    }
    if (!built)
        ret->InitEmpty();
    if (set)
        set->Release();
    return ret;
}

// ===========================================================================
// 00eccce0 -- Variant getter of the palette item info line (kind dispatch)
// ===========================================================================
struct IObject {
    virtual void AddRef();                                     // +0x00
    virtual void Release();                                    // +0x04
    virtual void _pv08();                                      // +0x08
    virtual void* GetByKey(uint32_t key);                      // +0x0c
};

// Data tail of the object reachable from the getter (extent in grid units).
struct ObjExtent {
    char pad00[0x1c];                                          // +0x00 .. +0x1b
    int mWidth;                                                // +0x1c
    int mHeight;                                               // +0x20
};

struct IWindow {
    virtual void AddRef();                                     // +0x00
    virtual void Release();                                    // +0x04
    virtual void _pv08();                                      // +0x08
    virtual void* GetByKey(uint32_t key);                      // +0x0c
    virtual void _pv10(); virtual void _pv14(); virtual void _pv18(); virtual void _pv1c();
    virtual void _pv20(); virtual void _pv24(); virtual void _pv28(); virtual void _pv2c();
    virtual void _pv30(); virtual void _pv34(); virtual void _pv38(); virtual void _pv3c();
    virtual void _pv40(); virtual void _pv44(); virtual void _pv48(); virtual void _pv4c();
    virtual void _pv50(); virtual void _pv54(); virtual void _pv58();
    virtual void SetImage(uint32_t image);                     // +0x5c
    virtual void _pv60(); virtual void _pv64(); virtual void _pv68(); virtual void _pv6c();
    virtual void SetRange(float a, float b);                   // +0x70
    virtual void SetSize(float w, float h);                    // +0x74
};

struct WindowCtor {
    void Init();                                               // 0x00962a10
};

extern "C" void* __cdecl GetWindowFactory();                                                       // 0x009512c0
extern "C" void* __cdecl AllocWindow(int size, int align, const char* name, void* factory);          // 0x009512d0
extern "C" char g_vtblWindowAddRef[];                                                              // 0x01414b10
extern "C" char g_vtblWindowIWindow[];                                                             // 0x014431f8
extern "C" char __cdecl FUN_008068d0(void* wnd, void* obj, int arg);                              // 0x008068d0
extern "C" void* __cdecl FUN_00ecca30(uint32_t key, uint32_t value);                              // 0x00ecca30
extern "C" IObject** __cdecl FUN_00ecc960(IObject** ret, uint32_t key, uint32_t value);           // 0x00ecc960
extern "C" void* __cdecl FUN_00ac9480(void* value);                                               // 0x00ac9480
extern "C" void* __cdecl FUN_00b199c0(void* value);                                               // 0x00b199c0

// @ 0x00eccce0
EA::Variant* __cdecl FUN_00eccce0(EA::Variant* ret, const PropKey* prop, const uint32_t* args)
{
    SP::EString line;
    EA::Variant result;
    IObject* obj = 0;
    IWindow* win = 0;
    bool haveResult = false;

    switch (prop->mKind) {
    case 0x7971b38: {
        IObject** tmp = FUN_00ecc960(0, 0xcbe904b9, args[0]);
        FUN_00ac9480(tmp);
        IObject* o = *tmp;
        if (o) {
            o->AddRef();
            obj = o;
        }
        (void)FUN_00b199c0(obj ? obj->GetByKey(0xee3f516e) : 0);
        break;
    }
    case 0x64a8a82: {
        SP::EString tmp;
        line.AssignFrom(FUN_00eccbf0(&tmp, 0x63a708f3, args[0]));
        tmp.~EString();
        EA::Variant v;
        ((VariantFill*)&v)->Set((uint32_t)line.mpBegin);
        result = v;
        haveResult = true;
        if (v.mFlags & 4)
            v.Destruct(false);
        break;
    }
    case 0x7a02ed0: {
        SP::EString tmp;
        SP::EString* src = FUN_00eccbf0(&tmp, 0x34862a2e, args[1]);
        if (&line != src) {
            if (line.mpBegin != line.mpEnd) {
                *line.mpBegin = 0;
                line.mpEnd = line.mpBegin;
            }
            line.AssignFrom(src);
        }
        tmp.~EString();
        EA::Variant v;
        ((VariantFill*)&v)->Set((uint32_t)line.mpBegin);
        result = v;
        haveResult = true;
        if (v.mFlags & 4)
            v.Destruct(false);
        break;
    }
    case 0x7a02ee0: {
        IObject** tmp = FUN_00ecc960(0, 0x60df46a8, args[1]);
        IObject* o = *tmp;
        if (o) {
            o->AddRef();
            obj = o;
        }
        void* icon = FUN_00ecca30(0xdd13cc12, args[1]);
        WindowCtor* w = (WindowCtor*)AllocWindow(0x20c, 4, "CastROTeamIcon", GetWindowFactory());
        uint32_t built = 0;
        if (w) {
            w->Init();
            *(void**)w = (void*)&g_vtblWindowAddRef;
            IWindow* iw = (IWindow*)((char*)w + 4);
            *(void**)iw = (void*)&g_vtblWindowIWindow;
            iw->AddRef();
            if (obj) {
                iw->SetRange(0.0f, 0.0f);
                iw->SetSize((float)((ObjExtent*)obj)->mWidth, (float)((ObjExtent*)obj)->mHeight);
                iw->SetImage((uint32_t)icon);
                FUN_008068d0(iw, obj, -1);
            }
            built = (uint32_t)iw->GetByKey(0xee3f516e);
            win = iw;
        }
        if (result.mFlags & 4)
            result.Destruct(true);
        result.Construct(0x11, 0x29, (const void*)built, 4, 1);
        haveResult = true;
        break;
    }
    default:
        break;
    }
    (void)haveResult;

    ret->mFlags = 0;
    ret->mTypeId = 0;
    *ret = result;
    if (win)
        win->Release();
    if (obj)
        obj->Release();
    if (result.mFlags & 4)
        result.Destruct(false);
    return ret;
}

// ===========================================================================
// 00ecda00 -- palette item kind classifier
// ===========================================================================
struct VariantTyped {
    char pad00[0x18];                                          // +0x00 .. +0x17
    uint32_t mTypeId;                                          // +0x18

    int Classify() const;
};

// @ 0x00ecda00
int VariantTyped::Classify() const
{
    switch (mTypeId) {
    case 0x1a4e0708:
    case 0x2090a11b:
    case 0x441cd3e6:
    case 0x449c040f:
        return 1;
    case 0x1f2a25b6:
    case 0x2a5147a9:
    case 0x8f963dcb:
    case 0xc15695da:
        return 2;
    case 0x7d433fad:
    case 0x9ad7d4aa:
    case 0xbc1041e6:
    case 0xf670aa43:
        return 3;
    default:
        return 0;
    }
}
