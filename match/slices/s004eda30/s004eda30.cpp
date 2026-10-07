// w1g1 slice s004eda30 -- editor validity resource-entry accessors.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

#include <string.h>
#include <wchar.h>
typedef unsigned int uint32_t;

struct Manager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual void* Find(int a, int b); // +0x58
};
void* GetMgr401010();

// ===========================================================================
// @ 0x004ee930  (MATCH)
// Looks up the model-type key pair of entry `index` in a resource's entry
// vector (stride 0x1d8); returns 0 when out of range.
// ===========================================================================
int FUN_004ee930(unsigned int index, int res)
{
    int p12, p15, v18, n35;
    p15 = res + 0x98;
    if (index >= (unsigned int)((*(int*)(p15 + 4) - *(int*)p15) / 0x1d8))
        return 0;
    n35 = (int)GetMgr401010();
    p12 = *(int*)p15 + (int)index * 0x1d8;
    v18 = *(int*)p15 + (int)index * 0x1d8;
    return (int)((Manager*)n35)->Find(*(int*)(v18 + 4), *(int*)p12);
}

// ---- 128-bit validity flag word (eastl::bitset<128>), unoptimized module ----------------------
struct Flags128 {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t i, bool value) {
        if (i < 128) {
            if (value) DoGetWord(i) |= 1u << (i % 32);
            else DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
};

// ===========================================================================
// @ 0x004edeb0  (complete; clears flag bit 16)
// ===========================================================================
bool FUN_004edeb0(int unused, Flags128* flags)
{
    (void)unused;
    if (flags)
        flags->set(16, false);
    return true;
}

// ---- resource entry vector (stride 0x1d8) at res+0x98 -----------------------------------------
struct EntryVec { char* mpBegin; char* mpEnd; };
struct IRef {
    virtual void AddRef();     // +0
    virtual void Release();    // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Has(uint32_t id);                     // +0x1c
    virtual void v8();
    virtual bool Get(uint32_t id, void** ppProp);      // +0x24
};
struct ResPtr {
    IRef* mp;
    ResPtr(IRef* p) : mp(p) { if (mp) mp->AddRef(); }
    ~ResPtr() { if (mp) mp->Release(); }
    IRef** GetAddr();          // 0x41d870
    IRef** operator&() { return GetAddr(); }
};
struct ResEntry { int a; int b; uint32_t rest[(0x1d8 - 8) / 4]; ResEntry(const ResEntry& src); };   // 0x4721e0 copy ctor
struct PropMgr {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10();
    virtual int GetResource(int b, int a, IRef** out);    // +0x2c
};
PropMgr* PropertyManager();     // 0x67de30
bool GetBoolProperty(IRef* p, uint32_t id, bool* out);   // 0x407190
struct PropVal {
    char pad[0x12]; unsigned short type;
    float* GetFloat();   // 0x41ea70
};

// ===========================================================================
// @ 0x004eda30  (validity of resource entries)
// ===========================================================================
bool FUN_004eda30(char* res, int need, Flags128* flags)
{
    int key = *(int*)(res + 0x18);
    bool isSingleType = false;
    switch (key) {
    case 0x372e2c04: case (int)0x9ea3031a: case (int)0xccc35c46: case (int)0xdfad9f51:
    case 0x4178b8e8: case 0x65672ade:
        isSingleType = true;
        break;
    }
    if (isSingleType) {
        int good = 0;
        EntryVec* p15 = (EntryVec*)(res + 0x98);
        int iEntry = 0;
        int size = (int)(p15->mpEnd - p15->mpBegin) / 0x1d8;
        for (; iEntry < size; iEntry++) {
            ResEntry entry(*(ResEntry*)(p15->mpBegin + iEntry * 0x1d8));
            ResPtr p(0);
            PropertyManager()->GetResource(entry.b, entry.a, &p);
            if (!p.mp) {
                if (flags) flags->set(2, true);
                return false;
            }
            bool b = false;
            if (p.mp) GetBoolProperty(p.mp, 0xafff3a14, &b);
            if (b) good++;
        }
        if (good < 2) {
            if (flags) flags->set(2, true);
            return false;
        }
        return true;
    }
    EntryVec* v2 = (EntryVec*)(res + 0x98);
    if ((int)(v2->mpEnd - v2->mpBegin) / 0x1d8 < need) {
        if (flags) flags->set(2, true);
        return false;
    }
    if (flags) flags->set(2, false);
    return true;
}

// ---- string helpers for FUN_004edf40 ----------------------------------------------------------
#pragma intrinsic(wcscmp)
extern const wchar_t kReservedName[];     // 0x13ec468
struct WString { unsigned find(unsigned short c, unsigned pos) const; };   // 0x4f6ab0
extern WString gBadChars;                         // 0x15da7d4

// ===========================================================================
// @ 0x004edf40  (name validity: reserved name / forbidden characters)
// ===========================================================================
bool FUN_004edf40(const wchar_t* name, Flags128* flags)
{
    wchar_t ch = *name;
    if (wcscmp(name, kReservedName) == 0) {
        if (flags) {
            flags->set(20, true);
            flags->set(4, true);
        }
        return false;
    }
    for (int i = 0; i < 0x100 && ch != 0 && ch != 0; i++) {
        ch = name[i];
        if (gBadChars.find(ch, 0) != 0xffffffff) {
            if (flags) {
                flags->set(21, true);
                flags->set(4, true);
            }
            return false;
        }
    }
    if (flags) {
        flags->set(21, false);
        flags->set(20, false);
        flags->set(4, false);
    }
    return true;
}

// ===========================================================================
// @ 0x004ee3b0  (every entry resolves)
// ===========================================================================
bool FUN_004ee3b0(char* res, Flags128* flags)
{
    EntryVec* p15 = (EntryVec*)(res + 0x98);
    int iEntry = 0;
    int size = (int)(p15->mpEnd - p15->mpBegin) / 0x1d8;
    for (; iEntry < size; iEntry++) {
        Manager* n35 = (Manager*)GetMgr401010();
        char* p12 = p15->mpBegin + iEntry * 0x1d8;
        char* v18 = p15->mpBegin + iEntry * 0x1d8;
        if (!n35->Find(*(int*)(v18 + 4), *(int*)p12)) {
            if (flags) flags->set(14, true);
            return false;
        }
    }
    if (flags) flags->set(14, false);
    return true;
}

// ===========================================================================
// @ 0x004ee560  SP::cSPEditorModelValidity::TestScales
// ===========================================================================
struct PVSlot { int pad; PropVal* p; };
bool FUN_004ee560(char* res, Flags128* flags)
{
    EntryVec* p15 = (EntryVec*)(res + 0x98);
    int iEntry = 0;
    int size = (int)(p15->mpEnd - p15->mpBegin) / 0x1d8;
    for (; iEntry < size; iEntry++) {
        Manager* mgr = (Manager*)GetMgr401010();
        char* p12 = p15->mpBegin + iEntry * 0x1d8;
        char* v18 = p15->mpBegin + iEntry * 0x1d8;
        IRef* prop = (IRef*)mgr->Find(*(int*)(v18 + 4), *(int*)p12);
        float lo, hi;
        if (!prop) {
            if (flags) flags->set(7, true);
            return false;
        }
        if (prop->Has(0xf023ed73)) {
            PVSlot pv1;
            if (prop && prop->Get(0xf023ed73, (void**)&pv1.p) && pv1.p->type == 0xd)
                lo = *pv1.p->GetFloat();
            if (*(float*)(p15->mpBegin + iEntry * 0x1d8 + 0x10) < lo - 1.5258789e-05f) {
                if (flags) flags->set(7, true);
                return false;
            }
        }
        if (prop->Has(0xf023ed79)) {
            PVSlot pv2;
            if (prop && prop->Get(0xf023ed79, (void**)&pv2.p) && pv2.p->type == 0xd)
                hi = *pv2.p->GetFloat();
            if (hi + 1.5258789e-05f < *(float*)(p15->mpBegin + iEntry * 0x1d8 + 0x10)) {
                if (flags) flags->set(7, true);
                return false;
            }
        }
    }
    if (flags) flags->set(7, false);
    return true;
}
