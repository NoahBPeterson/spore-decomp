// =============================================================================================
// SporeApp.exe slice s00c7c0c0  (batch part1, worker 18)
//
// 14 routines around the retail Simulator::cPlayer ban-mode list (+0x113c), the player
// ownership / serialization entry points, and SP::cRock (a cInteractableObject) helpers.
//
//   +0x113c              cBanModeVec   eastl::vector<20-byte BanModeEntry> (begin/end/cap)
//   +0x1184/+0x1198/+0x11ac  tUintVec  SPVector<unsigned int> member lists
//   +0x10e8              mpRef10E8     AutoRefCount<cCollectableItems>
//   +0x11f4              mpRef11F4     AutoRefCount<...>
//   cRock+0x34           cSpatialObject sub-object (secondary vtable 0x14731d0)
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// =============================================================================================
#include "types.h"
#include <math.h>
#include <string.h>
#include <new>

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------------------------
// image data
// ---------------------------------------------------------------------------------------------
extern float g_01694b24;                    // 0x01694b24
extern float g_01694b28;                    // 0x01694b28
extern float g_01694b2c;                    // 0x01694b2c
extern float g_014650a8;                    // 0x014650a8  (1/256)
extern void* g_0150d6dc;                    // 0x0150d6dc
extern uint32_t g_01687968;                 // 0x01687968
extern void* g_01578d18;                    // 0x01578d18

// ---------------------------------------------------------------------------------------------
// forward declarations
// ---------------------------------------------------------------------------------------------
class  cRefObj;
class  cCollectableItems;
class  cPlayer;
class  cRock;
class  cSpatialObject;
class  cSpatialObjectF;
class  cStream;
class  cGameNounManager;

// ---------------------------------------------------------------------------------------------
// allocator / generic helpers (cdecl unless noted)
// ---------------------------------------------------------------------------------------------
void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl FUN_00f47380(void* p);                                                                    // 0x00f47380
void* __cdecl FUN_00c79ae0(void* first, void* last, void* out);                                         // 0x00c79ae0
void  __cdecl FUN_00c79b20(void* first, void* last, void* out);                                         // 0x00c79b20
void* __cdecl FUN_00c7aca0(void* first, void* last, void* out);                                         // 0x00c7aca0
void  __cdecl FUN_00c7bea0(void* pos, uint32_t n, void* value);                                         // 0x00c7bea0
void  __cdecl FUN_00c7be50(void* first, void* last);                                                    // 0x00c7be50
void  __cdecl FUN_00c7b670(void* stream, void* out);                                                    // 0x00c7b670
void  __cdecl FUN_00bdaa40(void* out, void* first, void* last, void* dst, void* alloc);                 // 0x00bdaa40
void  __cdecl FUN_00ba3ca0(void* p);                                                                    // 0x00ba3ca0
void* __cdecl FUN_00ba4430(void* self, void* arg);                                                      // 0x00ba4430
void  __cdecl FUN_00b6f140(float x, float y, float z);                                                  // 0x00b6f140
bool  __cdecl FUN_0064f350(void* state, int a, int b);                                                  // 0x0064f350
void  __cdecl ReadInt32(void* io, void* dst, int count, int ver);                                       // 0x0093a780
void  __cdecl FUN_0091ff50(void* p);                                                                     // 0x0091ff50
void* __cdecl FUN_00b3d3b0();                                                                            // 0x00b3d3b0
void* __cdecl FUN_00b3d350();                                                                            // 0x00b3d350
void* __cdecl FUN_00c72540(void* first, void* last, void* key, int flag);                                // 0x00c72540

// singleton accessors (plain getters, no arguments)
void* __cdecl NounManager();                                              // 0x00b3d300
void* __cdecl PropertyManager();                                          // 0x0067de30
void* __cdecl ObjectTemplateDB();                                         // 0x0067cb40
void* __cdecl MessageServer();                                            // 0x0067dcc0

// ---------------------------------------------------------------------------------------------
// simple object stubs
// ---------------------------------------------------------------------------------------------
class cRefObj {
public:
    virtual void v00();                     // +0x00  (AutoRefCount AddRef)
    virtual void Release();                 // +0x04  (AutoRefCount Release)
};

class cCollectableItems : public cRefObj {
public:
    cCollectableItems* ctor();                                          // 0x00597e00
    void Configure(uint32_t a, uint32_t b, void* c);                    // 0x00599440
};

class cGameNounManager {
public:
    void* Find(uint32_t objType, uint32_t id);                          // 0x00b21000
    void* GetAvatar();                                                  // 0x00b1fdb0
};

class cIOObj {
public:
    virtual void i00(); virtual void i04(); virtual void i08(); virtual void i0c();
    virtual void i10(); virtual void i14();
    virtual void* v18();                                                // +0x18
};

class cStream {
public:
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
    virtual void* v20();                                                // +0x20
    virtual void c24(); virtual void c28(); virtual void c2c(); virtual void c30();
    virtual void c34(); virtual void c38();
    virtual uint32_t v3c();                                             // +0x3c
};

class cMessageServerObj {
public:
    virtual void m00();
    virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28();
    virtual void Broadcast(void* obj, uint32_t id, int32_t code);        // +0x2c
};

class cPropertyManager {
public:
    virtual void p00();
    virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28();
    virtual void GetProperty(uint32_t a, uint32_t b, void* out);         // +0x2c
};

class cObjectTemplateDB {
public:
    virtual void d00();
    virtual void d04(); virtual void d08(); virtual void d0c();
    virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c();
    virtual void d30(); virtual void d34(); virtual void d38(); virtual void d3c();
    virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void Register(void* owner);                                 // +0x50
    virtual void Unregister();                                          // +0x54
};

// object exposing slot 0x4c (used by 00c7d090)
class cKeyObj {
public:
    virtual void k00(); virtual void k04(); virtual void k08(); virtual void k0c();
    virtual void k10(); virtual void k14(); virtual void k18(); virtual void k1c();
    virtual void k20(); virtual void k24(); virtual void k28(); virtual void k2c();
    virtual void k30(); virtual void k34(); virtual void k38(); virtual void k3c();
    virtual void k40(); virtual void k44(); virtual void k48();
    virtual int  GetKey();                                              // +0x4c
};

// manager returned by FUN_00b3d3b0 (holds the feedback rbtree at +0x190)
class cFeedbackMgr {
public:
    void find(void* out, void* key);                                    // 0x00e5c780  (on +0x190)
    void FUN_00b2a2a0(void* rock, int flag);                            // 0x00b2a2a0
};

class cPlanetModel {
public:
    void FUN_00b83c40(void* model);                                     // 0x00b83c40
};

class cVarListSerializer {
public:
    void ctor(void* owner, void* varList, int id);                       // 0x00692f90
    bool Read(void* stream);                                             // 0x00693e10
};

struct cGonzagoTimer {
    void* mpBegin; void* mpEnd; void* mpCap;
    void* mExtra[5];
    void  ctor();                                                        // 0x00b63890
    void  dtor();                                                        // 0x00b638b0
};

struct cInnerVec {
    void* mpBegin; void* mpEnd; void* mpCap;
    void  dtor();                                                        // 0x00ad92d0
};

struct cBanModeEntry {
    void*    mpBegin;                        // +0x00  inner vector begin
    void*    mpEnd;                          // +0x04
    void*    mpCap;                          // +0x08
    uint32_t mField0C;                       // +0x0c
    uint32_t mField10;                       // +0x10
    cBanModeEntry() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    cBanModeEntry(const cBanModeEntry& other);                // 0x00c76fd0
    cBanModeEntry& operator=(const cBanModeEntry& other);     // 0x00db5b30
};

class cBanModeVec {
public:
    void* mpBegin;                           // +0x00
    void* mpEnd;                             // +0x04
    void* mpCap;                             // +0x08
    void* DoInsertValue(cBanModeEntry* position, const cBanModeEntry& value);  // 0x00c7c0c0
    void  resize(uint32_t n);                                                  // 0x00c7c4a0
    void  FUN_00c77ab0(void* first, void* last);                               // 0x00c77ab0
    void  FUN_00c77a00(uint32_t n);                                            // 0x00c77a00
};

struct tUintVec {
    uint32_t* mpBegin;                       // +0x00
    uint32_t* mpEnd;                         // +0x04
    uint32_t* mpCap;                         // +0x08
};

class cPlanetVec {
public:
    void* mpBegin;                           // +0x00
    void* mpEnd;                             // +0x04
    void* mpCap;                             // +0x08
    void  FUN_00c781e0(void* first, void* last);   // 0x00c781e0
    void  FUN_00ba4de0(void* iter, void* key);     // 0x00ba4de0
};

struct cSpatialObject {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual Vec3* GetPosition();                                        // +0x2c
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
    virtual void s70();
    virtual float GetDistance(int a, int b);                            // +0x74
    virtual void s78(); virtual void s7c(); virtual void s80(); virtual void s84();
    virtual void s88(); virtual void s8c(); virtual void s90(); virtual void s94();
    virtual int* GetTag();                                              // +0x98
    virtual void s9c();
    void SetLocalExtents(int a, float b);                               // 0x00c7d020
    void FUN_00c89160(int a, float b);                                  // 0x00c89160
};

// trivially-constructible placeholder for the cSpatialObject sub-object stored at cRock+0x34
struct cSpatialRef { void* mpVtbl; };

// same shape, but the +0x2c slot takes a float
struct cSpatialObjectF {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24(); virtual void f28();
    virtual void* GetModel(float r);                                    // +0x2c
};

// ---------------------------------------------------------------------------------------------
// PlayerPlanetData (0xb0) read by FUN_00c7c9b0
// ---------------------------------------------------------------------------------------------
struct PlayerPlanetData {
    void* mpVtbl;                            // +0x00
    void* pv08b; void* pv08e; void* pv08c;   // +0x08
    void* pv20b; void* pv20e; void* pv20c;   // +0x20
    void* pv38b; void* pv38e; void* pv38c;   // +0x38
    void* pv50b; void* pv50e; void* pv50c;   // +0x50
    void* pv68b; void* pv68e; void* pv68c;   // +0x68
    uint8_t mTimer[0x20];                    // +0x80
    uint8_t mA0; uint8_t mA1; uint8_t mA2; uint8_t mPad[0xd];  // +0xa0
};

// ---------------------------------------------------------------------------------------------
// cRock (SP::cRock)
// ---------------------------------------------------------------------------------------------
class cRock {
public:
    void*    mpVtbl00;                       // +0x0000
    void*    mpVtbl04;                       // +0x0004
    uint8_t  mPad08[0x28 - 0x08];            // +0x0008
    uint32_t mField28;                       // +0x0028  (definition / noun id)
    void*    mpField2C;                      // +0x002c
    uint8_t  mPad30[0x34 - 0x30];            // +0x0030
    cSpatialRef mSpatial;                    // +0x0034  (secondary vtable object)
    uint8_t  mPad38[0x84 - 0x38];            // +0x0038  (base state up to flags)
    uint32_t mFlags84;                       // +0x0084
    int      mField88;                       // +0x0088
    uint8_t  mPad8C[0xa5 - 0x8c];            // +0x008c
    bool     mBoolA5;                        // +0x00a5
    uint8_t  mPadA6[0x130 - 0xa6];           // +0x00a6
    Vec3     mOriginalPosition;              // +0x0130
    void*    mp13C;                          // +0x013c
    uint32_t mField140;                      // +0x0140

    cRock();                                                            // 0x00c7cde0
    bool InitFromDefinition(int a, int b, int c);                       // 0x00c7cce0
    void UpdateModel();                                                 // 0x00c7ce70
    void FUN_00c7cf50(void* arg);                                       // 0x00c7cf50
    bool FUN_00c7cfc0(void* arg);                                       // 0x00c7cfc0
    // base-class routines reached through ecx=this
    void FUN_00c3f9b0();                                                 // 0x00c3f9b0
    void FUN_00c3f9a0(int a);                                            // 0x00c3f9a0
    void FUN_00c3ff10(void* arg);                                        // 0x00c3ff10
    bool FUN_00c3fc80(int a, int b, int c);                              // 0x00c3fc80
    bool FUN_00b183f0(void* arg);                                        // 0x00b183f0
};

// ---------------------------------------------------------------------------------------------
// Simulator::cPlayer
// ---------------------------------------------------------------------------------------------
class cPlayer {
public:
    void*    mpVtbl00;                       // +0x0000
    void*    mpVtbl04;                       // +0x0004
    uint8_t  mPad08[0x28 - 0x08];            // +0x0008
    uint32_t mField28;                       // +0x0028
    cRefObj* mpOwner2C;                      // +0x002c  AutoRefCount owner
    uint8_t  mPad30[0x34 - 0x30];            // +0x0030
    void*    mpVtbl34;                       // +0x0034  IHandlerRC interface vtable
    uint8_t  mPad38[0x84 - 0x38];            // +0x0038
    uint32_t mFlags84;                       // +0x0084
    int      mField88;                       // +0x0088
    uint8_t  mPad8C[0xa5 - 0x8c];            // +0x008c
    bool     mBoolA5;                        // +0x00a5
    uint8_t  mPadA6[0x10e8 - 0xa6];          // +0x00a6
    cRefObj* mpRef10E8;                      // +0x10e8  AutoRefCount<cCollectableItems>
    int      mField10EC;                     // +0x10ec
    uint8_t  mPad10F0[0x10f8 - 0x10f0];      // +0x10f0
    int      mField10F8;                     // +0x10f8
    uint8_t  mPad10FC[0x113c - 0x10fc];      // +0x10fc
    cBanModeVec mBanModeTable;               // +0x113c
    uint8_t  mPad1148[0x1184 - 0x1148];      // +0x1148
    tUintVec mVec1184;                       // +0x1184
    tUintVec mVec1198;                       // +0x1198
    tUintVec mVec11AC;                       // +0x11ac
    uint8_t  mPad11B8[0x11f4 - 0x11b8];      // +0x11b8
    cRefObj* mpRef11F4;                      // +0x11f4
    uint8_t  mPad11F8[0x1244 - 0x11f8];      // +0x11f8
    void*    mp1244;                         // +0x1244

    void RemoveOwner();                                                  // 0x00c7c220
    void SetGameDataOwner(int owner);                                    // 0x00c7c6d0
    bool Read(void* stream);                                             // 0x00c7c7c0
    void FUN_00c751e0();                                                 // 0x00c751e0
    void FUN_00b18550_base(int owner);                                   // 0x00b18550
    bool FUN_00b18600_read(void* stream);                                // 0x00b18600
};

// ---------------------------------------------------------------------------------------------
// shared inline idioms
// ---------------------------------------------------------------------------------------------
static inline cCollectableItems* AllocCollectableItems()
{
    cCollectableItems* p = (cCollectableItems*)FUN_00f473a0(
        0x6dac, "Simulator/cCollectableItems", 0, 0, 0, 0);
    if (p)
        p = p->ctor();
    return p;
}

static inline void AssignAutoRef(cRefObj** slot, cRefObj* p)
{
    cRefObj* old = *slot;
    if (p != old) {
        if (p)
            p->v00();
        *slot = p;
        if (old)
            old->Release();
    }
}

static inline void StreamReadInt32(void* stream, void* dst)
{
    void* obj = ((cStream*)stream)->v20();
    void* io  = ((cIOObj*)obj)->v18();
    ReadInt32(io, dst, 1, 0);
}

// destroys the temporary inner vector of a just-read BanModeEntry
static inline void DestroyBanTemp(cBanModeEntry& temp)
{
    for (void** p = (void**)temp.mpBegin; p != (void**)temp.mpEnd; ++p) {
        if (*p != 0) {
            typedef void (__thiscall *PFN)(void*);
            ((PFN)(((void**)*p)[0xc0 / 4]))(*p);
        }
    }
    if (temp.mpBegin != 0 && ((int*)temp.mpBegin)[-1] != 0)
        FUN_00f47380(temp.mpBegin);
}

// =============================================================================================
// 0x00c7c0c0  cBanModeVec::DoInsertValue(position, value)
// =============================================================================================
// @ 0x00c7c0c0
void* cBanModeVec::DoInsertValue(cBanModeEntry* position, const cBanModeEntry& value)
{
    cBanModeEntry* pBegin = (cBanModeEntry*)mpBegin;
    cBanModeEntry* pEnd   = (cBanModeEntry*)mpEnd;
    cBanModeEntry* pCap   = (cBanModeEntry*)mpCap;

    if (pEnd != pCap) {
        const cBanModeEntry* pValue = &value;
        if (pValue >= position && pValue < pEnd)
            ++pValue;
        if (pEnd != 0)
            new (pEnd) cBanModeEntry(*(pEnd - 1));
        FUN_00c79b20(position, pEnd - 1, pEnd);
        *position = *pValue;
        mpEnd = pEnd + 1;
        return position;
    }

    uint32_t nPrevSize = (uint32_t)((uint32_t)((char*)pEnd - (char*)pBegin) / 0x14);
    uint32_t nNewSize  = nPrevSize ? nPrevSize * 2 : 1;
    cBanModeEntry* pNewData = 0;
    if (nNewSize)
        pNewData = (cBanModeEntry*)FUN_00f473a0(
            nNewSize * 0x14, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);

    uint32_t nPrefixBytes = (uint32_t)((char*)position - (char*)pBegin);
    memcpy(pNewData, pBegin, nPrefixBytes);
    uint32_t nPrefixCount = nPrefixBytes / 0x14;

    cBanModeEntry* pNewEnd = (cBanModeEntry*)((char*)pNewData + nPrefixCount * 0x14);
    if (pNewEnd != 0)
        new (pNewEnd) cBanModeEntry(value);

    uint32_t nSuffixBytes = (uint32_t)((char*)pEnd - (char*)position);
    memcpy((char*)pNewEnd + 0x14, position, nSuffixBytes);
    uint32_t nSuffixCount = nSuffixBytes / 0x14;

    cBanModeEntry* pNewMpEnd = (cBanModeEntry*)((char*)pNewEnd + 0x14 + nSuffixCount * 0x14);

    if (pBegin != 0 && ((int*)pBegin)[-1] != 0)
        FUN_00f47380(pBegin);

    mpEnd   = pNewMpEnd;
    mpBegin = pNewData;
    mpCap   = (cBanModeEntry*)((char*)pNewData + nNewSize * 0x14);
    return position;
}

// =============================================================================================
// 0x00c7c4a0  cBanModeVec::resize(n)
// =============================================================================================
// @ 0x00c7c4a0
void cBanModeVec::resize(uint32_t n)
{
    uint32_t size = (uint32_t)((uint32_t)((char*)mpEnd - (char*)mpBegin) / 0x14);
    if (size < n) {
        cInnerVec value;
        value.mpBegin = 0; value.mpEnd = 0; value.mpCap = 0;
        FUN_00c7bea0(mpEnd, n - size, &value);
        value.dtor();
        return;
    }
    FUN_00c7be50((char*)mpBegin + n * 0x14, mpEnd);
}

// =============================================================================================
// 0x00c7c220  cPlayer::RemoveOwner()
// =============================================================================================
// @ 0x00c7c220
void cPlayer::RemoveOwner()
{
    if (mpOwner2C != 0) {
        cRefObj* p = mpOwner2C;
        mpOwner2C = 0;
        p->Release();
    }
    if (mpRef10E8 != 0) {
        cRefObj* p = mpRef10E8;
        mpRef10E8 = 0;
        p->Release();
    }

    // clear the ban-mode table
    {
        void* b = mBanModeTable.mpBegin;
        void* e = mBanModeTable.mpEnd;
        void* r = FUN_00c79ae0(e, e, b);
        mBanModeTable.FUN_00c77ab0(r, e);
        mBanModeTable.mpEnd = (char*)mBanModeTable.mpEnd -
                              ((uint32_t)(((char*)e - (char*)b) / 0x14) * 0x14);
    }

    // clear the three member-id vectors (memcpy(begin,end,0); end -= size)
    {
        uint32_t* e = mVec1184.mpEnd;
        uint32_t* b = mVec1184.mpBegin;
        memcpy(b, e, 0);
        mVec1184.mpEnd = (uint32_t*)((char*)mVec1184.mpEnd + ((((char*)e - (char*)b) >> 2) * -4));
    }
    {
        uint32_t* e = mVec1198.mpEnd;
        uint32_t* b = mVec1198.mpBegin;
        memcpy(b, e, 0);
        mVec1198.mpEnd = (uint32_t*)((char*)mVec1198.mpEnd + ((((char*)e - (char*)b) >> 2) * -4));
    }
    {
        uint32_t* e = mVec11AC.mpEnd;
        uint32_t* b = mVec11AC.mpBegin;
        memcpy(b, e, 0);
        mVec11AC.mpEnd = (uint32_t*)((char*)mVec11AC.mpEnd + ((((char*)e - (char*)b) >> 2) * -4));
    }

    if (mpRef11F4 != 0) {
        cRefObj* p = mpRef11F4;
        mpRef11F4 = 0;
        p->Release();
    }

    static const uint32_t kIds[10] = {
        0x4bef1e3, 0x44f1189, 0x5e902d3, 0x6524498, 0x6526395,
        0x6667038, 0x6666683, 0x6527231, 0x6527eaf, 0x1a0219e
    };
    for (int i = 0; i < 10; ++i) {
        cMessageServerObj* ms = (cMessageServerObj*)MessageServer();
        ms->Broadcast((char*)this + 0x34, kIds[i], -9999);
    }
}

// =============================================================================================
// 0x00c7c530  load a ban-mode list from the stream  (free cdecl)
// =============================================================================================
// @ 0x00c7c530
void __cdecl FUN_00c7c530(void* stream, cBanModeVec* vec)
{
    void* b = vec->mpBegin;
    void* e = vec->mpEnd;
    void* r = FUN_00c79ae0(e, e, b);
    vec->FUN_00c77ab0(r, e);
    vec->mpEnd = (char*)vec->mpEnd - ((uint32_t)(((char*)e - (char*)b) / 0x14) * 0x14);

    uint32_t count = 0;
    StreamReadInt32(stream, &count);
    vec->FUN_00c77a00(count);

    uint32_t i = 0;
    if (count != 0) {
        do {
            cBanModeEntry temp;
            temp.mpBegin = 0; temp.mpEnd = 0; temp.mpCap = 0;
            FUN_00c7b670(stream, &temp);

            cBanModeEntry* pos = (cBanModeEntry*)vec->mpEnd;
            if (pos < (cBanModeEntry*)vec->mpCap) {
                vec->mpEnd = (char*)pos + 0x14;
                if (pos != 0) {
                    uint32_t n = (uint32_t)((char*)temp.mpEnd - (char*)temp.mpBegin) >> 2;
                    uint32_t* data = 0;
                    if (n != 0)
                        data = (uint32_t*)FUN_00f473a0(
                            n * 4, "Simulator", 0, 0,
                            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                            0xd1);
                    pos->mpBegin = data;
                    pos->mpEnd   = data;
                    pos->mpCap   = data + n;
                    uint32_t out = 0;
                    FUN_00bdaa40(&out, temp.mpBegin, temp.mpEnd, data, stream);
                    pos->mpEnd = (void*)out;
                }
            } else {
                vec->DoInsertValue(pos, temp);
            }

            DestroyBanTemp(temp);
            ++i;
        } while (i < count);
    }

    ((cStream*)stream)->c1c();
}

// =============================================================================================
// 0x00c7c6d0  cPlayer::SetGameDataOwner(owner)
// =============================================================================================
// @ 0x00c7c6d0
void cPlayer::SetGameDataOwner(int owner)
{
    FUN_00b18550_base(owner);
    FUN_0091ff50(&mField10F8);
    mBanModeTable.resize(10);
    AssignAutoRef(&mpRef10E8, (cRefObj*)AllocCollectableItems());
    if (mpRef10E8 != 0)
        ((cCollectableItems*)mpRef10E8)->Configure(0xad56080c, 0x4a5c4493, g_0150d6dc);
    mField10EC = 0;
    FUN_00c751e0();
    cPropertyManager* pm = (cPropertyManager*)PropertyManager();
    if (mpRef11F4 != 0) {
        cRefObj* p = mpRef11F4;
        mpRef11F4 = 0;
        p->Release();
    }
    pm->GetProperty(0x2ca2581, 0x2ae0c7e, &mpRef11F4);
}

// =============================================================================================
// 0x00c7c7c0  cPlayer::Read(stream)
// =============================================================================================
// @ 0x00c7c7c0
bool cPlayer::Read(void* stream)
{
    int local = 0;
    StreamReadInt32(stream, &local);

    uint32_t ver = ((cStream*)stream)->v3c();
    if (ver > 0x210010) {
        uint32_t tmp = 0;
        StreamReadInt32(stream, &tmp);
        g_01687968 = tmp;
    }

    ver = ((cStream*)stream)->v3c();
    if (ver > 0x1c0013) {
        Vec3 v;
        StreamReadInt32(stream, &v);
        FUN_00b6f140(v.x, v.y, v.z);
    }

    bool ok = FUN_00b18600_read(stream);
    cVarListSerializer ser;
    ser.ctor(this, &g_01578d18, 0x1a80d26);
    bool bl = false;
    if (ok) {
        if (ser.Read(stream))
            bl = true;
    }

    mBanModeTable.resize(10);

    if (mpRef10E8 == 0)
        AssignAutoRef(&mpRef10E8, (cRefObj*)AllocCollectableItems());

    cObjectTemplateDB* db = (cObjectTemplateDB*)ObjectTemplateDB();
    if (db != 0) {
        if (mp1244 == 0)
            db->Unregister();
        else
            db->Register(mp1244);
    }

    cPropertyManager* pm = (cPropertyManager*)PropertyManager();
    if (mpRef11F4 != 0) {
        cRefObj* p = mpRef11F4;
        mpRef11F4 = 0;
        p->Release();
    }
    pm->GetProperty(0x2ca2581, 0x2ae0c7e, &mpRef11F4);

    FUN_00c751e0();
    return bl;
}

// =============================================================================================
// 0x00c7c9b0  load a planet-data list from the stream  (free cdecl)
// =============================================================================================
// @ 0x00c7c9b0
void __cdecl FUN_00c7c9b0(void* stream, cPlanetVec* vec)
{
    void* b = vec->mpBegin;
    void* e = vec->mpEnd;
    void* r = FUN_00c7aca0(e, e, b);
    vec->FUN_00c781e0(r, e);
    vec->mpEnd = (char*)vec->mpEnd - ((uint32_t)(((char*)e - (char*)b) / 0xb0) * 0xb0);

    int32_t count = 0;
    StreamReadInt32(stream, &count);

    int32_t i = 0;
    if (count != 0) {
        do {
            PlayerPlanetData temp;
            temp.mpVtbl = (void*)0x1465d64;
            temp.pv08b = temp.pv08e = temp.pv08c = 0;
            temp.pv20b = temp.pv20e = temp.pv20c = 0;
            temp.pv38b = temp.pv38e = temp.pv38c = 0;
            temp.pv50b = temp.pv50e = temp.pv50c = 0;
            temp.pv68b = temp.pv68e = temp.pv68c = 0;
            ((cGonzagoTimer*)temp.mTimer)->ctor();
            temp.mA0 = 0xff; temp.mA1 = 0xff; temp.mA2 = 0;

            int32_t key = 0;
            StreamReadInt32(stream, &key);
            ((cStream*)stream)->c1c();
            {
                typedef void (__thiscall *PFN)(void*, void*);
                ((PFN)((void**)temp.mpVtbl)[1])(&temp, stream);
            }
            ((cStream*)stream)->c1c();

            int32_t keyCopy = key;
            FUN_00ba3ca0(&temp);
            void* iter = FUN_00c72540(vec->mpBegin, vec->mpEnd, &keyCopy, ((char*)vec)[0x14]);
            bool inserted;
            if (iter == vec->mpEnd || keyCopy < *(int32_t*)iter) {
                vec->FUN_00ba4de0(iter, &keyCopy);
                inserted = true;
            } else {
                inserted = false;
            }

            ((cGonzagoTimer*)temp.mTimer)->dtor();
            if (temp.pv68b) FUN_00f47380(temp.pv68b);
            if (temp.pv50b) FUN_00f47380(temp.pv50b);
            if (temp.pv38b) FUN_00f47380(temp.pv38b);
            if (temp.pv20b) FUN_00f47380(temp.pv20b);
            if (temp.pv08b) FUN_00f47380(temp.pv08b);
            if (!inserted)
                FUN_00ba4430((char*)iter + 8, &temp);

            ++i;
        } while (i < count);
    }

    ((cStream*)stream)->c1c();
}

// =============================================================================================
// 0x00c7cce0  cRock::InitFromDefinition(a, b, c)
// =============================================================================================
// @ 0x00c7cce0
bool cRock::InitFromDefinition(int a, int b, int c)
{
    if (FUN_00c3fc80(a, 0, 0)) {
        Vec3* p = ((cSpatialObject*)&mSpatial)->GetPosition();
        mOriginalPosition = *p;
        return true;
    }
    return false;
}

// =============================================================================================
// 0x00c7cde0  cRock::cRock()
// =============================================================================================
// @ 0x00c7cde0
cRock::cRock()
{
    FUN_00c3f9b0();
    mpVtbl00 = (void*)0x14732a8;
    mpVtbl04 = (void*)0x1473294;
    mSpatial.mpVtbl = (void*)0x14731d0;
    mOriginalPosition.x = g_01694b24;
    mOriginalPosition.y = g_01694b28;
    mOriginalPosition.z = g_01694b2c;
    mp13C = 0;
    mField140 = 0xffffffff;
    FUN_00c3f9a0(5);
    mField88 = 4;
    mBoolA5 = 0;
    mFlags84 |= 0x200;
}

// =============================================================================================
// 0x00c7ce70  cRock::UpdateModel()
// =============================================================================================
// @ 0x00c7ce70
void cRock::UpdateModel()
{
    if (!mBoolA5)
        return;

    void* noun = ((cGameNounManager*)NounManager())->Find(0x2a8fb3f, mField28);
    if (noun == 0)
        return;
    if (!FUN_0064f350(*(void**)((char*)noun + 0xc), 0x67364ba, 0))
        return;
    if (!FUN_0064f350(*(void**)((char*)noun + 0xc), 0x3d08e15, 0))
        return;

    cSpatialObject* sp = (cSpatialObject*)&mSpatial;
    Vec3* pos = sp->GetPosition();
    float r = sqrtf(pos->x * pos->x + pos->y * pos->y + pos->z * pos->z) * 0.00390625f;
    r += sp->GetDistance(0x10000000, 0);
    void* model = ((cSpatialObjectF*)sp)->GetModel(r);
    ((cPlanetModel*)FUN_00b3d350())->FUN_00b83c40(model);
}

// =============================================================================================
// 0x00c7cf50  cRock::FUN_00c7cf50()
// =============================================================================================
// @ 0x00c7cf50
void cRock::FUN_00c7cf50(void* arg)
{
    FUN_00c3ff10(arg);
    if (mp13C == 0)
        return;

    void* mgr = FUN_00b3d3b0();
    void* node = 0;
    ((cFeedbackMgr*)((char*)mgr + 0x190))->find(&node, &mp13C);
    if (node == (char*)mgr + 0x194)
        return;
    uint8_t* bits = *(uint8_t**)((char*)node + 0x14);
    if (bits == 0)
        return;
    uint32_t idx = mField140;
    ((uint32_t*)(bits + (idx >> 5) * 4))[0] |= 1u << (idx & 0x1f);
}

// =============================================================================================
// 0x00c7cfc0  cRock::FUN_00c7cfc0()
// =============================================================================================
// @ 0x00c7cfc0
bool cRock::FUN_00c7cfc0(void* arg)
{
    bool bl = FUN_00b183f0(arg);
    int* tag = ((cSpatialObject*)&mSpatial)->GetTag();
    if (*tag == (int)0xc5bba049 && (mFlags84 & 0x100) == 0) {
        ((cFeedbackMgr*)FUN_00b3d3b0())->FUN_00b2a2a0(this, 1);
        return false;
    }
    if (bl)
        UpdateModel();
    return bl;
}

// =============================================================================================
// 0x00c7d020  cSpatialObject::SetLocalExtents(a, b)   (ecx = the +0x34 sub-object)
// =============================================================================================
// @ 0x00c7d020
void cSpatialObject::SetLocalExtents(int a, float b)
{
    FUN_00c89160(a, b);
    ((cRock*)((char*)this - 0x34))->UpdateModel();
}

// =============================================================================================
// 0x00c7d090  rock selection-key comparison  (free cdecl)
// =============================================================================================
// @ 0x00c7d090
bool __cdecl FUN_00c7d090(void* p1, int32_t* p2)
{
    switch (p2[0]) {
    case 0:
        return true;
    case 1:
        return ((cKeyObj*)p1)->GetKey() == p2[1];
    case 2:
        return ((int32_t*)p1)[7] == p2[1];
    case 8:
        return p1 == ((cGameNounManager*)NounManager())->GetAvatar();
    default:
        return false;
    }
}