// s00d49b60.cpp - reconstructed slice
// Compiler: MSVC 2008 SP1 (x86)
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
// ---------------------------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------------------------
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef int                i32;
typedef float              f32;

// ---------------------------------------------------------------------------------------------
// Opaque extern callees / data referenced by absolute address.
// ---------------------------------------------------------------------------------------------
void* __cdecl GetLocaleManager();                              // 0x0067de40
u8    __cdecl Locale_IsFrench(void* node, const wchar_t* tag);   // 0x006ab760

static inline void* VT_14_0(void* p)
{
    void** vt = *(void***)p;
    return ((void* (__thiscall*)(void*))vt[5])(p);
}

// Button-record object: type tag at +0xc, localized id at +0x38.
struct cButtonRec {
    u8  mPad00[0x0c];
    i32 mField0c;                       // 0x0c (type)
    u8  mPad10[0x38 - 0x10];
    i32 mField38;                       // 0x38 (localized button id)
};

// @ 0x00d49ee0
// Returns the localized button id, mapping 0x5a to 0x57 under a language override.
extern "C" i32 __cdecl LocalizeButtonId(cButtonRec* rec)
{
    if (Locale_IsFrench(VT_14_0(GetLocaleManager()), L"fr-fr")
        && rec->mField38 == 0x5a)
        return 0x57;
    return rec->mField38;
}

// @ 0x00d49f20
// Picks a button-record sub-field based on the record type tag.
struct cButtonRec2 {
    u8  mPad00[0x0c];
    i32 mField0c;                       // 0x0c (type)
    u8  mPad10[0x38 - 0x10];
    i32 mField38;                       // 0x38
};

extern "C" i32* __cdecl PickButtonField(cButtonRec2* rec, char* base)
{
    switch (rec->mField0c) {
    case 2:
    case 3:
        if (Locale_IsFrench(VT_14_0(GetLocaleManager()), L"fr-fr")
            && rec->mField38 == 0x5a)
            return (i32*)0x57;
        return (i32*)rec->mField38;
    case 4:
        return (i32*)(base + 0x70);
    default:
        break;
    }
    return (i32*)(base + 0x31);
}
