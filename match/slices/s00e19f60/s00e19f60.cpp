// @ 0x00e19f60
// match/slices/s00e19f60/s00e19f60.cpp
//
// Ordering predicate for two "key" objects (cleans its own arguments).  Each
// side is asked through a virtual slot for a record, that record's owning
// empire is looked up (0xc451e0), and the two empires are ordered as
//   1. the local player's empire first,
//   2. then by the empire name (wide-character compare: -1 / 0 / 1).
// A missing side sorts last.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- external callees -------------------------------------------------------
void* __fastcall FUN_00c451e0(void* record);   // 0xc451e0 owner empire of record
void* __fastcall FUN_005c65e0(void* empire);   // 0x5c65e0 -> &empire->mName (+0x3c)
u32   __cdecl    FUN_01021090();               // 0x1021090 local player empire id

// ---- stub object types ------------------------------------------------------
// Object handed to the predicate: its third virtual slot maps a record key to
// the record.
struct KeyObject_s00e19f60 {
    virtual void* GetSlot0();
    virtual void* GetSlot1();
    virtual void* GetSlot2();
    virtual void* GetRecord(u32 key);          // vtable + 0xc
};

// Empire side: the empire id sits at +0x84.
struct Empire_s00e19f60 {
    u8  mUnknown000[0x84];
    u32 mEmpireID;                             // +0x84
};

// What 0x5c65e0 points at: the name pointer sits first.
struct Name_s00e19f60 {
    const wchar_t* mpName;                     // +0x0
};

// The trailing wide-character compare is the CRT's wcscmp, expanded inline by
// the compiler (two characters per pass, sbb-based -1/0/1 result).
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
#pragma intrinsic(wcscmp)

bool __stdcall CompareWString(void* pa, void* pb)
{
    KeyObject_s00e19f60* a = (KeyObject_s00e19f60*)pa;
    KeyObject_s00e19f60* b = (KeyObject_s00e19f60*)pb;

    void* recA = a ? a->GetRecord(0x2aa5ada) : 0;
    void* recB = b ? b->GetRecord(0x2aa5ada) : 0;

    Empire_s00e19f60* ea = (Empire_s00e19f60*)FUN_00c451e0(recA);
    Empire_s00e19f60* eb = (Empire_s00e19f60*)FUN_00c451e0(recB);

    if (!ea)
        return false;
    if (!eb)
        return true;

    u32 playerEmpire = FUN_01021090();

    if (ea->mEmpireID == playerEmpire && eb->mEmpireID != playerEmpire)
        return true;
    if (ea->mEmpireID != playerEmpire && eb->mEmpireID == playerEmpire)
        return false;

    const wchar_t* nameB = ((Name_s00e19f60*)FUN_005c65e0(eb))->mpName;
    const wchar_t* nameA = ((Name_s00e19f60*)FUN_005c65e0(ea))->mpName;
    return wcscmp(nameA, nameB) < 0;
}
