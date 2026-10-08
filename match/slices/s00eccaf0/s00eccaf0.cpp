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
struct cString {
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
