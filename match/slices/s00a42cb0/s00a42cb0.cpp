// Slice s00a42cb0 -- SP::Audio::cSystem::ReadTuningValues (00a43a50): reads the tuning values for a resource key,
// then pushes the two float tuning values into the EAPD singleton.
// Module flags (guess, verify): /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

extern uint32_t gTuningGroupID;                 // 0x015541dc (no PDB name)

struct ResourceKey { uint32_t instanceID; uint32_t typeID; uint32_t groupID; };

// ---- vtable slot filler macros -------------------------------------------
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VD virtual void CAT(vd, __COUNTER__)();
#define V10 VD VD VD VD VD VD VD VD VD VD
#define V8  VD VD VD VD VD VD VD VD

// EA::Audio::System base of cSystemTuning -- its vtable pointer lives at this+0
struct EAAudioSystemTuning {
    virtual void vs00(); virtual void vs01(); virtual void vs02(); virtual void vs03();
    virtual void vs04(); virtual void vs05(); virtual void vs06();
    virtual bool GetSymbolList(uint32_t id, void** out);   // vtable +0x1c
    V10 V10 V10 V10 V10                                    // slots 8..57
    virtual void vfn58(uint32_t a, uint32_t b);            // vtable +0xe8
    virtual void vs59(); virtual void vs60();
    virtual uint32_t vfn61(uint32_t a);                    // vtable +0xf4
    V10 V10 V10 V10 V10 V10 V8                             // slots 62..129
    virtual void vfn130(float v, uint32_t a);              // vtable +0x208
    bool ReadTuningValues(const ResourceKey* key);         // 0x00a29be0, thiscall, ret 4
    void SysSetProperty(uint32_t id, float v);             // 0x00a30460, thiscall, ret 8
};

struct EAPDSystemTuning {                       // EA::Audio::Eapd::ISystem (singleton)
    virtual void slot0();
    virtual void Slot1();                       // vtable +0x4
    virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual void SetValue5(float v);            // vtable +0x14
    virtual void SetValue6(float v);            // vtable +0x18
    V10                                         // slots 7..16
    virtual void vfn17(uint32_t id, float v);   // vtable +0x44
    static EAPDSystemTuning* GetSingletonPtr(); // 0x00a67c60, no args
};

struct TuningReaderStub {                       // object at cSystem +0x1f8
    virtual void slot0();  virtual void slot1();  virtual void slot2();  virtual void slot3();
    virtual void slot4();  virtual void slot5();  virtual void slot6();  virtual void slot7();
    virtual void slot8();  virtual void slot9();  virtual void slot10(); virtual void slot11();
    virtual void ReadFloatById(uint32_t id, float* out);   // vtable +0x30, ret 8
    virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual bool GetValues(uint32_t key, uint32_t* count, void** data);  // vtable +0x48, ret 0xc
};

struct EventModifierTuning {
    virtual void vs0();
    virtual void Release();                                // vtable +0x4
    virtual void vfn2();                                   // vtable +0x8
    void ReadTuningValues(const ResourceKey* key);         // 0x00a39f90, thiscall, ret 4
    void Shutdown();                                       // 0x00a39c80, thiscall
};

struct AudioATSystem {                          // EA::Audio::GetSystemAT() result (slot +0x138)
    V10 V10 V10 V10 V10 V10 V10 V8                         // slots 0..77
    virtual void Lookup(uint32_t id, void** out, uint32_t groupID);   // vtable +0x138
};

struct AudioSymbolList {                        // object returned by the lookup
    virtual void vs0();
    virtual void Release();                                // vtable +0x4
    virtual void vs2(); virtual void vs3(); virtual void vs4(); virtual void vs5(); virtual void vs6();
    virtual bool GetSymbols(uint32_t id, void** out);      // vtable +0x1c
};

struct AutoSymRef {                             // RAII holder used by 0x00a43580
    AudioSymbolList* mp;
    AutoSymRef() : mp(0) {}
    ~AutoSymRef() { if (mp) mp->Release(); }
};

struct SymData {                                // symbol blob returned by GetSymbols
    uint32_t* mpData;      // +0x0
    uint32_t  m04;         // +0x4
    uint32_t  mCount;      // +0x8
    uint32_t  m0c;         // +0xc
    uint16_t  mFlags;      // +0x10
    uint16_t  mLength;     // +0x12
};

struct AudioListNode {                          // node of the intrusive list walked by 0x00a43190
    virtual void vs0(); virtual void vs1(); virtual void vs2(); virtual void vs3();
    virtual void vs4(); virtual void vs5(); virtual void vs6(); virtual void vs7();
    virtual bool Vfn8(uint32_t a, uint32_t b);             // vtable +0x20
    virtual void vs9(); virtual void vs10(); virtual void vs11(); virtual void vs12();
    virtual void vs13(); virtual void vs14(); virtual void vs15(); virtual void vs16();
    virtual uint32_t Vfn17();                              // vtable +0x44
    bool     Predicate();                                  // 0x00ef6410, thiscall
    float    ReadValueA();                                 // 0x00a1af70
    uint32_t ReadValueB();                                 // 0x00a1ad80
    uint32_t ReadValueC();                                 // 0x00a1ad90
    float    ReadValueD();                                 // 0x00a1adb0
    char            pad04[0x10 - 4];                       // +0x4..+0xf
    AudioListNode*  mpListEnd;                             // +0x10  (list head +0x157438)
    AudioListNode*  mpNext;                                // +0x14
};

struct AudioPrimitive {                         // EA::Audio::IPrimitive (value stored in the hashes)
    virtual void  vfn0(); virtual void vfn1(); virtual void vfn2(); virtual void vfn3();
    virtual void  vfn4(); virtual void vfn5(); virtual void vfn6();
    virtual float vfn7();                                  // vtable +0x1c
};

struct PrimHashNode {                           // {key, value, next} node of the glyph hash
    uint32_t        mKey;                                  // +0x0
    AudioPrimitive* mpValue;                               // +0x4
    PrimHashNode*   mpNext;                                // +0x8
};

struct PrimHashIter { PrimHashNode* mpNode; PrimHashNode** mpBucket; };

struct PrimHashTable {                          // eastl hash at cSystem +0x119bb8
    char            pad00[4];
    PrimHashNode**  mpBuckets;                             // +0x4
    uint32_t        mBucketCount;                          // +0x8
    void Begin(PrimHashIter* out);                         // 0x00594410, thiscall, ret 4
};

struct SelectParams {                           // argument of SelectAudioObject (0x00a43190)
    char      pad00[0x10];
    float     m10;      // +0x10
    uint32_t  m14;      // +0x14
    char      pad18[0xc];
    uint32_t  m24;      // +0x24
    uint32_t  m28;      // +0x28
    uint32_t  m2c;      // +0x2c
    uint32_t  m30;      // +0x30
    uint32_t  m34;      // +0x34
    uint32_t  m38;      // +0x38
    uint32_t  m3c;      // +0x3c
    uint32_t  m40;      // +0x40
    uint32_t  m44;      // +0x44
};

struct EastlHashTable {                         // eastl hashtable 'this' for 0x00a42e90
    char      pad00[4];
    void**    mpBuckets;                                   // +0x4
    uint32_t  mBucketCount;                                // +0x8
    char      pad0c[0x1c - 0xc];
    void**    mpFreeList;                                  // +0x1c
    char      pad20[0x24 - 0x20];
    void**    mpPoolBegin;                                 // +0x24
    void**    mpPoolEnd;                                   // +0x28
    char      pad2c[0x30 - 0x2c];
    void**    mpBucketEnd;                                 // +0x30
    void**    AllocBuckets(uint32_t n);                    // 0x00a42e20, thiscall, ret 4
    void      Erase(uint32_t n);                           // 0x00a42e90, thiscall, ret 4
};

struct EastlNodeAlloc {                         // eastl fixed pool allocator 'this'
    char      pad00[0x1c];
    void*     mpFreeList;                                  // +0x1c
    char      pad20[0x2c - 0x20];
    uint32_t  mNodeSize;                                   // +0x2c
    void*     AllocNode(void* src);                        // 0x00a43740, thiscall, ret 4
    void*     CopyNode30(void* src);                       // 0x00a43790, thiscall, ret 4
};

struct Node30 {                                 // 0x30-byte node copied by 0x00a43790
    uint32_t  m0;      // +0x0
    uint32_t  m4;      // +0x4
    uint32_t  m8;      // +0x8
    uint32_t  mC;      // +0xc
    double    m10;     // +0x10
    float     m18;     // +0x18
    float     m1c;     // +0x1c
    float     m20;     // +0x20
    void*     mp24;    // +0x24
    uint32_t  m28;     // +0x28
    uint32_t  m2c;     // +0x2c
};

struct AudioCommand {                           // command passed to cSystemTuning::DoCommand
    uint32_t  GetType();                                   // 0x00fc7e50, thiscall
    uint32_t  GetParent();                                 // 0x00ff0420, thiscall
    bool      GetUint32(uint32_t key, uint32_t* out);      // 0x00a0fab0, thiscall, ret 8
    bool      GetVoidPtr(uint32_t key, void** out);        // 0x00a0fb90, thiscall, ret 8
    void*     EnumParameter(uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d);  // 0x00a0f880, thiscall, ret 0x10
};

struct AudioSubObj {                            // sub-object embedded at +(cSystem+0x15bce0)+8
    virtual void vs0();
    virtual void Release();                                // vtable +0x4
    virtual void vs2(); virtual void vs3(); virtual void vs4(); virtual void vs5();
    virtual void vs6(); virtual void vs7(); virtual void vs8(); virtual void vs9();
    virtual void vs10(); virtual void vs11(); virtual void vs12();
    virtual void vfn13();                                  // vtable +0x34
};

struct SubObjHolder {
    char        pad00[8];
    AudioSubObj obj;                                       // +0x8
};

struct UtfWinWindow {                           // UTFWin::Window (cSystem +0x15bc80)
    virtual void vs0(); virtual void vs1(); virtual void vs2(); virtual void vs3();
    virtual void vs4(); virtual void vs5(); virtual void vs6(); virtual void vs7();
    virtual void vs8(); virtual void vs9();
    virtual void vfn10();                                  // vtable +0x28
    bool Initialize();                                     // 0x00b1fbf0, thiscall
};

struct Obj15bc18 {                              // cSystem +0x15bc18
    virtual void vs0(); virtual void vs1(); virtual void vs2(); virtual void vs3();
    virtual void vs4(); virtual void vs5(); virtual void vs6(); virtual void vs7();
    virtual void vs8(); virtual void vs9(); virtual void vs10(); virtual void vs11();
    virtual void Vfn12(uint32_t a, void* b);               // vtable +0x30
};

struct EapdDebugObj {                           // Eapd Debug::ObjectError() result (vtable +0x44)
    V10 VD VD VD VD VD VD VD                               // slots 0..16
    virtual void vfn17(uint32_t a, void* b, uint32_t c);   // vtable +0x44
};

extern const char gEaAllocatorFile[];           // 0x013ebb38 (eastl allocator.h path)
extern const char gEaEastlName[];               // 0x013f2150 ("EASTL")

extern "C" {
    void* __cdecl EAOperatorNew(uint32_t size, const char* name, int flags, int align, const char* file, int line);  // 0x00f473a0
    void  __cdecl EAOperatorDelete(void* p);               // 0x00f47380
    AudioATSystem* __cdecl EaAudioGetSystemAT();           // 0x00a206f0
    EapdDebugObj*  __cdecl EapdDebugObjectError();         // 0x008de1a0
}

struct cSystemTuning {                          // SP::Audio::cSystem
    EAAudioSystemTuning base;                   // +0x0 (vtable-bearing base)
    char pad0[0x1f8 - sizeof(EAAudioSystemTuning)];
    TuningReaderStub* mpTuningReader;           // +0x1f8
    bool   mFlag1fc;                            // +0x1fc
    char   pad1fd[0x200 - 0x1fd];
    uint32_t mIndex200;                         // +0x200
    char   pad204[0x210 - 0x204];
    float  mFloat210;                           // +0x210
    char   pad214[0x23e8 - 0x214];
    PrimHashNode** mpTable23e8;                     // +0x23e8
    uint32_t mTableIdx23ec;                     // +0x23ec
    char   pad23f0[0x119bb8 - 0x23f0];
    PrimHashTable mGlyphHash119bb8;             // +0x119bb8 (eastl glyph hash_map)
    char   pad119bc4[0x157428 - 0x119bc4];
    AudioListNode mList157428;                  // +0x157428 (intrusive list head)
    char   pad157440[0x157c60 - 0x157440];
    AudioListNode mObj157c60;                   // +0x157c60 .. +0x157c77 (list sentinel)
    char   pad157c78[0x158f48 - 0x157c78];
    AudioListNode* mp158f48;                     // +0x158f48
    char   pad158f4c[0x15b6b0 - 0x158f4c];
    uint32_t m15b6b0;                           // +0x15b6b0
    char   pad15b6b4[0x15bc18 - 0x15b6b4];
    Obj15bc18 mObj15bc18;                       // +0x15bc18
    char   pad15bc1c[0x15bc3c - 0x15bc1c];
    uint32_t m15bc3c;                           // +0x15bc3c
    bool   m15bc40;                             // +0x15bc40
    char   m15bc41;                             // +0x15bc41
    bool   m15bc42;                             // +0x15bc42
    char   pad15bc43[0x15bc78 - 0x15bc43];
    EventModifierTuning* mpEventModifier;       // +0x15bc78
    void*  mp15bc7c;                            // +0x15bc7c
    UtfWinWindow* mp15bc80;                     // +0x15bc80
    char   pad15bc84[0x15bc94 - 0x15bc84];
    uint32_t mPoly[16];                         // +0x15bc94 .. +0x15bcd3
    char   pad15bcd4[0x15bcd8 - 0x15bcd4];
    float  mTuneA;                              // +0x15bcd8
    float  mTuneB;                              // +0x15bcdc
    SubObjHolder* mp15bce0;                     // +0x15bce0

    void FUN_00a681e0();                        // 0x00a681e0, thiscall
    void FUN_00a31800();                        // 0x00a31800, thiscall
    void FUN_00a42830();                        // 0x00a42830, thiscall
    void FUN_00a32f20(float a, float b);        // 0x00a32f20, thiscall, ret 8
    bool SysDoCommand(AudioCommand* cmd);       // 0x00a2c6c0, thiscall, ret 4

    void ReadPolyphonyCounters();               // 0x00a42cb0
    bool AddSymbolList(uint32_t id);            // 0x00a43580
    bool ReadTuningValues(const ResourceKey* key);
    bool ShutdownAudio();                       // 0x00a43050
    void NotifyTimeChange(float a, float b);    // 0x00a43120
    bool SelectAudioObject(SelectParams* sel, void** out);   // 0x00a43190
    bool DoCommand(AudioCommand* cmd);          // 0x00a43300
    void SetProperty(uint32_t id, float v);     // 0x00a43830
    void ApplyPolyphonySettings();              // 0x00a439b0
};

// @ 0x00a43a50
bool cSystemTuning::ReadTuningValues(const ResourceKey* key) {
    if (!base.ReadTuningValues(key)) return false;
    if (key->groupID == gTuningGroupID) AddSymbolList(key->instanceID);
    if (mpEventModifier) mpEventModifier->ReadTuningValues(key);
    ReadPolyphonyCounters();
    mTuneA = 0.0f;
    mpTuningReader->ReadFloatById(0xdacee1bd, &mTuneA);
    mTuneB = 0.01f;
    mpTuningReader->ReadFloatById(0x1c05b1a7, &mTuneB);
    EAPDSystemTuning* sys = EAPDSystemTuning::GetSingletonPtr();
    if (sys) {
        sys->SetValue5(mTuneA);
        sys->SetValue6(mTuneB);
    }
    return true;
}

// ===========================================================================
// 0x00a42cb0  SP::Audio::cSystem::ReadPolyphonyCounters
// ===========================================================================
// @ 0x00a42cb0
void cSystemTuning::ReadPolyphonyCounters() {
    uint32_t count;
    void* data;
    if (mpTuningReader->GetValues(0x4f76ed4a, &count, &data) && count == 3) {
        uint32_t* p = (uint32_t*)data;
        mPoly[7] = p[0];
        mPoly[8] = p[1];
        mPoly[9] = p[2];
        mPoly[1] = p[mIndex200 - 1];
    }
    if (mpTuningReader->GetValues(0xa6c8bfcc, &count, &data) && count == 3) {
        uint32_t* p = (uint32_t*)data;
        mPoly[4] = p[0];
        mPoly[5] = p[1];
        mPoly[6] = p[2];
        mPoly[0] = p[mIndex200 - 1];
    }
    if (mpTuningReader->GetValues(0xe91c6f7e, &count, &data) && count == 3) {
        uint32_t* p = (uint32_t*)data;
        mPoly[13] = p[0];
        mPoly[14] = p[1];
        mPoly[15] = p[2];
        mPoly[3] = p[mIndex200 - 1];
    }
    if (mpTuningReader->GetValues(0x8750500d, &count, &data) && count == 3) {
        uint32_t* p = (uint32_t*)data;
        mPoly[10] = p[0];
        mPoly[11] = p[1];
        mPoly[12] = p[2];
        mPoly[2] = p[mIndex200 - 1];
    }
}

// ===========================================================================
// 0x00a42e90  eastl::hashtable<...>::erase
// ===========================================================================
// @ 0x00a42e90
void EastlHashTable::Erase(uint32_t n) {
    void** newBuckets = AllocBuckets(n);
    uint32_t i = 0;
    if (mBucketCount != 0) {
        do {
            void** node = (void**)mpBuckets[i];
            while (node != 0) {
                uint32_t bucket = *(uint32_t*)node % n;
                void** next = (void**)node[3];
                mpBuckets[i] = next;
                node[3] = newBuckets[bucket];
                newBuckets[bucket] = node;
                node = (void**)mpBuckets[i];
            }
            ++i;
        } while (i < mBucketCount);
    }
    void** old = mpBuckets;
    if (mBucketCount > 1 && old != mpBucketEnd) {
        if (old >= mpPoolBegin && old < mpPoolEnd) {
            *old = mpFreeList;
            mpFreeList = old;
            mpBuckets = newBuckets;
            mBucketCount = n;
            return;
        }
        EAOperatorDelete(old);
    }
    mpBuckets = newBuckets;
    mBucketCount = n;
}

// ===========================================================================
// 0x00a43050  SP::Audio::cSystem::ShutdownAudio
// ===========================================================================
// @ 0x00a43050
bool cSystemTuning::ShutdownAudio() {
    FUN_00a681e0();
    if (mp15bc80) {
        mp15bc80->Initialize();
        if (mp15bc80) {
            UtfWinWindow* w = mp15bc80;
            mp15bc80 = 0;
            w->vfn10();
        }
    }
    if (mpEventModifier) {
        mpEventModifier->Shutdown();
        if (mpEventModifier) {
            EventModifierTuning* m = mpEventModifier;
            mpEventModifier = 0;
            m->vfn2();
        }
    }
    if (mp15bce0) {
        mp15bce0->obj.vfn13();
        SubObjHolder* h = mp15bce0;
        if (h) {
            mp15bce0 = 0;
            h->obj.Release();
        }
    }
    FUN_00a31800();
    if (mp15bc7c) {
        FUN_00a42830();
        EapdDebugObj* dbg = EapdDebugObjectError();
        dbg->vfn17(0, mp15bc7c, 0);
    }
    return true;
}

// ===========================================================================
// 0x00a43120  SP::Audio::cSystem::NotifyTimeChange
// ===========================================================================
// @ 0x00a43120
void cSystemTuning::NotifyTimeChange(float a, float b) {
    if (mp158f48 == &mObj157c60)
        base.vfn130(a - mFloat210, m15b6b0);
    EAPDSystemTuning* sys = EAPDSystemTuning::GetSingletonPtr();
    if (sys)
        sys->Slot1();
    FUN_00a32f20(a, b);
}

// ===========================================================================
// 0x00a43190  SP::Audio::cSystem::SelectAudioObject
// ===========================================================================
// @ 0x00a43190
bool cSystemTuning::SelectAudioObject(SelectParams* sel, void** out) {
    if (out == 0) return false;
    float best = 0.0f;
    float cur = sel->m10;
    AudioListNode* found = 0;
    AudioListNode* node = &mList157428;
    AudioListNode* end = mList157428.mpListEnd;
    if (node != end) {
        do {
            node = node->mpNext;
            if (node->Predicate()) continue;
            if (node->Vfn8(0xffffffff, 0)) continue;
            if (node->ReadValueA() > sel->m10) continue;
            if (sel->m24 == 0xee8347b0 && node->Vfn17() == sel->m14) continue;
            if (!(sel->m28 < sel->m2c) && node->Vfn17() != sel->m14) continue;
            if (!(sel->m34 < sel->m38) && node->ReadValueB() != sel->m30) continue;
            if (!(sel->m40 < sel->m44) && node->ReadValueC() != sel->m3c) continue;
            float f = node->ReadValueD();
            if (f < best) {
                if (cur <= node->ReadValueA()) continue;
            } else {
                if (cur < node->ReadValueA()) {
                    if (cur <= node->ReadValueA()) continue;
                }
            }
            best = node->ReadValueD();
            cur = node->ReadValueA();
            found = node;
        } while (node != end);
    }
    if (found != 0) {
        *out = found;
        found->vs0();
        return true;
    }
    return false;
}

// ===========================================================================
// 0x00a43300  SP::Audio::cSystem::DoCommand
// ===========================================================================
// @ 0x00a43300
bool cSystemTuning::DoCommand(AudioCommand* cmd) {
    switch (cmd->GetType()) {
    case 0x435e22d: {
        uint32_t a = 0;
        void* v = 0;
        cmd->GetUint32(0x435e384, &a);
        cmd->GetVoidPtr(0x435e315, &v);
        if (a != 0 && v != 0)
            mObj15bc18.Vfn12(a, v);
        return SysDoCommand(cmd);
    }
    case 0x43390fd:
        cmd->GetUint32(0x433911b, &m15bc3c);
        return SysDoCommand(cmd);
    case 0x5c2b8a3: {
        if (cmd->GetParent() == 0) {
            ReadPolyphonyCounters();
        } else {
            uint32_t count = 0;
            uint32_t key;
            uint32_t spare;
            uint32_t kind;
            void* entry = cmd->EnumParameter(&count, &key, &spare, &kind);
            while (entry) {
                if ((kind & 0xfffffffc) == 0xc) {
                    uint32_t* p = (uint32_t*)entry;
                    switch (key) {
                    case 0x8750500d:
                        mPoly[10] = p[0]; mPoly[11] = p[1]; mPoly[12] = p[2];
                        mPoly[2] = p[mIndex200 - 1]; break;
                    case 0x4f76ed4a:
                        mPoly[7] = p[0]; mPoly[8] = p[1]; mPoly[9] = p[2];
                        mPoly[1] = p[mIndex200 - 1]; break;
                    case 0xa6c8bfcc:
                        mPoly[4] = p[0]; mPoly[5] = p[1]; mPoly[6] = p[2];
                        mPoly[0] = p[mIndex200 - 1]; break;
                    case 0xe91c6f7e:
                        mPoly[13] = p[0]; mPoly[14] = p[1]; mPoly[15] = p[2];
                        mPoly[3] = p[mIndex200 - 1]; break;
                    }
                }
                entry = cmd->EnumParameter(&count, &key, &spare, &kind);
            }
        }
        return SysDoCommand(cmd);
    }
    case 0x7f43dc0: {
        uint32_t v;
        cmd->GetUint32(0x39e3c9f, &v);
        m15bc42 = (v != 0);
        break;
    }
    }
    return SysDoCommand(cmd);
}

// ===========================================================================
// 0x00a43580  SP::Audio::cSystem::AddSymbolList
// ===========================================================================
// @ 0x00a43580
bool cSystemTuning::AddSymbolList(uint32_t id) {
    AudioATSystem* sys = EaAudioGetSystemAT();
    AutoSymRef holder;
    AudioSymbolList* prev = holder.mp;
    if (prev) {
        holder.mp = 0;
        prev->Release();
    }
    sys->Lookup(id, (void**)&holder.mp, gTuningGroupID);
    bool result = false;
    if (holder.mp) {
        SymData* str = 0;
        if (holder.mp->GetSymbols(0x4b2a3424, (void**)&str)) {
            uint32_t count;
            uint32_t* data;
            if ((str->mFlags & 0x30) == 0) {
                count = (str->mLength != 0) ? 1u : 0u;
                data = (str->mLength != 0) ? (uint32_t*)str : 0;
            } else {
                count = str->mCount;
                data = str->mpData;
            }
            while ((int)count > 0) {
                uint32_t h = base.vfn61(*data);
                base.vfn58(h, *data);
                data += 4;
                count -= 1;
            }
            result = true;
        }
    }
    return result;
}

// ===========================================================================
// 0x00a43740  eastl::fixed_pool::alloc
// ===========================================================================
// @ 0x00a43740
void* EastlNodeAlloc::AllocNode(void* src) {
    uint32_t* node = (uint32_t*)mpFreeList;
    if (node != 0) {
        mpFreeList = (void**)node[0];
    } else {
        uint32_t size = mNodeSize;
        node = (uint32_t*)EAOperatorNew(size, gEaEastlName, 0, 0, gEaAllocatorFile, 0xd1);
    }
    if (node != 0) {
        uint32_t* s = (uint32_t*)src;
        node[0] = s[0];
        node[1] = s[1];
        node[2] = s[2];
    }
    node[3] = 0;
    return node;
}

// ===========================================================================
// 0x00a43790  eastl::fixed_pool::copy
// ===========================================================================
// @ 0x00a43790
void* EastlNodeAlloc::CopyNode30(void* src) {
    Node30* p = (Node30*)EAOperatorNew(0x30, gEaEastlName, 0, 0, gEaAllocatorFile, 0xd1);
    if (p != 0) {
        Node30* s = (Node30*)src;
        p->m0 = s->m0;
        p->m8 = s->m8;
        p->m10 = s->m10;
        p->m18 = s->m18;
        p->m1c = s->m1c;
        p->m20 = s->m20;
        p->mp24 = s->mp24;
        if (p->mp24 != 0)
            (*(void (__thiscall**)(void*))*(void**)p->mp24)(p->mp24);
    }
    p->m28 = 0;
    return p;
}

// ===========================================================================
// 0x00a43830  SP::Audio::cSystem::SetProperty
// ===========================================================================
// @ 0x00a43830
void cSystemTuning::SetProperty(uint32_t id, float v) {
    EAPDSystemTuning* sys = EAPDSystemTuning::GetSingletonPtr();
    if (sys)
        sys->vfn17(id, v);
    base.SysSetProperty(id, v);
    switch (id) {
    case 0x46e5468:
        m15bc40 = (m15bc40 == 0);
        return;
    case 0x3e2c5c3: {
        PrimHashTable* hash = &mGlyphHash119bb8;
        PrimHashIter it;
        hash->Begin(&it);
        PrimHashNode* end = hash->mpBuckets[hash->mBucketCount];
        PrimHashNode* node = it.mpNode;
        if (node != end) {
            PrimHashNode** bucket = it.mpBucket;
            do {
                AudioPrimitive* p = node->mpValue;
                if (p) {
                    p->vfn0();
                    p->vfn1();
                }
                node = node->mpNext;
                while (node == 0) {
                    ++bucket;
                    node = *bucket;
                }
            } while (node != end);
        }
        return;
    }
    case 0x4837905:
        mFlag1fc = (mFlag1fc == 0);
        return;
    case 0x6df5822d: {
        uint32_t i = mIndex200;
        mPoly[1] = mPoly[6 + i];
        mPoly[0] = mPoly[3 + i];
        mPoly[3] = mPoly[12 + i];
        mPoly[2] = mPoly[9 + i];
        return;
    }
    case 0x5ac702f0:
        m15bc40 = (v != 0.0f);
        return;
    }
}

// ===========================================================================
// 0x00a439b0  SP::Audio::cSystem::ApplyPolyphonySettings
// ===========================================================================
// @ 0x00a439b0
void cSystemTuning::ApplyPolyphonySettings() {
    EAPDSystemTuning* sys = EAPDSystemTuning::GetSingletonPtr();
    if (!sys) return;
    PrimHashNode** bucket = mpTable23e8;
    PrimHashNode* node = *bucket;
    if (node == 0) {
        do {
            ++bucket;
        } while (*bucket == 0);
        node = *bucket;
    }
    PrimHashNode* end = (PrimHashNode*)mpTable23e8[mTableIdx23ec];
    while (node != end) {
        AudioPrimitive* p = node->mpValue;
        float f = p->vfn7();
        sys->vfn17(node->mKey, f);
        node = node->mpNext;
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
}

}  // namespace SP
