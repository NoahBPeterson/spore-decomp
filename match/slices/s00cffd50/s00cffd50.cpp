// 0x00cffd50: SP mission-manager family (Gonzago subsystem cloners, cSPCivMissionManager
// save/load, relationship manager classification + clamping, empire relation scoring) plus the
// property-driven threshold loader.  All field offsets are retail layout.
#include "types.h"

#define PV(n) virtual void s##n();

// ------------------------------------------------------------------ externs
extern char g_vtbl_01478c10[];
extern char g_vtbl_01478c08[];
extern char g_vtbl_01478cc4[];
extern char g_vtbl_01478ca0[];
extern char g_vtbl_01478c90[];
extern char g_str_01581ec8[];
extern char g_str_01582008[];
extern const wchar_t g_wstr_01478d94[];
extern void* g_169d3cc;
extern float g_1470f1c;                 // 2.0f

void __cdecl op_delete(void* p);
void __fastcall base_ctor_00b70820(void* p);
void __fastcall base_dtor_00b705a0(void* p);
void __fastcall gonzago_dtor(void* p);
void* __cdecl RBTreeIncrement(void* node);

// ------------------------------------------------------------------ classes
class cStarRecordVector {
public:
    void* mpBegin;                    // +0x00
    void* mpEnd;                      // +0x04
    void* mpCap;                      // +0x08
    ~cStarRecordVector();
    void* erase(void* first, void* last);
};

class cGonzagoMissionSubsystem {
public:
    void* mVtbl0;                     // +0x00
    void* mVtbl1;                     // +0x04
    unsigned char mPad0[0x14];        // +0x08
    cStarRecordVector mVec;           // +0x1c
    cGonzagoMissionSubsystem* Destroy(unsigned char flags);
};

class cMissionManagerFactory {
public:
    void* mVtbl0;                     // +0x00
    void* mVtbl1;                     // +0x04
    void* mVtbl2;                     // +0x08
    void* mVtbl3;                     // +0x0c
    void* mVtbl4;                     // +0x10
    cMissionManagerFactory* Construct();
    cMissionManagerFactory* Destroy(unsigned char flags);
};

class cSPCreatureMissionManager {
public:
    void* AsInterface(unsigned id);
};

class cMissionTicker {
public:
    unsigned char mPad0[0x70];
    bool mFlag70;                     // +0x70
    void OnTick();                    // 0xb6f7d0
    void Apply(void* a, void* b);     // 0xb6f650
    void FUN_00d00560(void* a, void* b);
};

class cSaveStreamObject {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void* GetStream();        // +0x18
};

class cSaveStream {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual cSaveStreamObject* GetWriter();   // +0x20
};

namespace EA { namespace IO {
    bool WriteUint32(void* stream, const void* value, int count, int flags);
    bool ReadInt32(void* stream, void* value, int count, int flags);
}}

class cVarListSerializer {
public:
    int mData[0xa14 / 4];
    cVarListSerializer(void* object, const char* fieldName, unsigned id);
    bool Serialize(void* stream);
    bool Read(void* stream);
    void SerializeNode(void* data, const char* fieldName, const wchar_t* typeName);
};

class cSPMissionManagerBase {
public:
    virtual bool Write(void* stream);      // 0xb6f570
    virtual bool Read(void* stream);       // 0xb6f5e0
};

class cSPCivMissionManager : public cSPMissionManagerBase {
public:
    bool Write(void* stream);
    bool Read(void* stream);
};

class cTerrainSphere {
public:
    int GetType();                    // 0xc75420
};

class cNounManager {
public:
    cTerrainSphere* GetCurrentTerrainSphere();   // 0xf67d90
    int GetPlayerEmpireOrMinus1();               // 0xb1f9d0
};

cNounManager* NounManager();                    // 0xb3d300
int GetCurrentGameMode();                       // 0xb5b800
int GetPlayerEmpireID();                        // 0x1021090
bool IsPlayerEmpire(int empire);                // 0xba6650

class cEmpire {
public:
    unsigned char mPad0[0x89];
    bool mFlag89;                     // +0x89
    bool mFlag8a;                     // +0x8a
    unsigned char mPad1[0x46c - 0x8b];
    int mId46c;                       // +0x46c
    int GetIndex();                   // 0xbf01e0
    int GetCommunityScore();          // 0xbf7150
    int GetStance();                  // 0xbf0f40
};

class cInterface;

class cRelationshipManager {
public:
    unsigned char mPad0[0x10];
    float mMin;                       // +0x10
    float mLow;                       // +0x14
    float mMid;                       // +0x18
    float mHigh;                      // +0x1c
    float CalculateRelationshipAbsolute(void* a, void* b, void* c);  // 0xd05a20
    int Classify(float x);
    float ClampRelationship(void* a, void* b, void* c);
    int ClampClassify(void* a, void* b, void* c);
    float RelationshipBetween(cInterface* a, cInterface* b, void* c);
    void LoadProperties();
};

cRelationshipManager* SP_RelationshipManager();   // 0xb3d2c0

class cInterface {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual unsigned GetId();          // +0x4c
};

class cRBMap {
public:
    void* mpUnk0;                      // +0x00
    void* mpHead;                      // +0x04
    void* mpRoot;                      // +0x08
};

class Property {
public:
    unsigned char mPad0[0x12];         // +0x04..+0x11
    short mType;                       // +0x12
    float* GetFloat();                 // 0x41ea70
};

class cPropertySet {
public:
    PV(0)
    virtual void Release();            // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(unsigned id, Property** out);   // +0x24
};

class cPropertyManager {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual bool FindSet(unsigned id, cPropertySet** out);   // +0x30
};

cPropertyManager* PropertyManager();   // 0x67de30

class cPropRef {
public:
    cPropertySet* mp;                  // +0x00
    cPropRef() { mp = 0; }
    cPropRef& operator=(cPropertySet* p) {
        cPropertySet* old = mp;
        mp = p;
        if (old)
            old->Release();
        return *this;
    }
};

// ------------------------------------------------------------------ code
// @ 0x00d00460
cGonzagoMissionSubsystem* cGonzagoMissionSubsystem::Destroy(unsigned char flags)
{
    cStarRecordVector* v = &mVec;
    mVtbl0 = g_vtbl_01478c10;
    mVtbl1 = g_vtbl_01478c08;
    v->erase(v->mpBegin, v->mpEnd);
    v->~cStarRecordVector();
    gonzago_dtor(this);
    if (flags & 1)
        op_delete(this);
    return this;
}

// @ 0x00d004c0
cMissionManagerFactory* cMissionManagerFactory::Construct()
{
    base_ctor_00b70820(this);
    mVtbl0 = g_vtbl_01478cc4;
    mVtbl2 = g_vtbl_01478ca0;
    mVtbl4 = g_vtbl_01478c90;
    g_169d3cc = this;
    return this;
}

// @ 0x00d00510
void* cSPCreatureMissionManager::AsInterface(unsigned id)
{
    switch (id) {
    case 0x179c807:
        return ((char*)this - 8) != 0 ? (void*)this : 0;
    case 0x54361546:
    case 0x11416b8:
        return (char*)this - 8;
    case 0xee3f516e:
        return ((char*)this - 8) != 0 ? (void*)this : 0;
    default:
        return 0;
    }
}

// @ 0x00d00560
void cMissionTicker::FUN_00d00560(void* a, void* b)
{
    OnTick();
    if (mFlag70) {
        Apply(a, b);
        mFlag70 = 0;
    }
}

// @ 0x00d005c0
cMissionManagerFactory* cMissionManagerFactory::Destroy(unsigned char flags)
{
    mVtbl0 = g_vtbl_01478cc4;
    mVtbl2 = g_vtbl_01478ca0;
    mVtbl4 = g_vtbl_01478c90;
    g_169d3cc = 0;
    base_dtor_00b705a0(this);
    if (flags & 1)
        op_delete(this);
    return this;
}

// @ 0x00d00600
bool cSPCivMissionManager::Write(void* stream)
{
    cSaveStreamObject* w = ((cSaveStream*)stream)->GetWriter();
    unsigned value = 0x58b3212;
    void* s = w->GetStream();
    EA::IO::WriteUint32(s, &value, 1, 0);
    bool ok = cSPMissionManagerBase::Write(stream);
    cVarListSerializer ser((char*)this - 8, g_str_01581ec8, 0x1a80d26);
    if (ok && ser.Serialize(stream))
        return true;
    return false;
}

// @ 0x00d00690
bool cSPCivMissionManager::Read(void* stream)
{
    cSaveStreamObject* w = ((cSaveStream*)stream)->GetWriter();
    void* s = w->GetStream();
    int value;
    EA::IO::ReadInt32(s, &value, 1, 0);
    bool ok = cSPMissionManagerBase::Read(stream);
    cVarListSerializer ser((char*)this - 8, g_str_01581ec8, 0x1a80d26);
    if (ok && ser.Read(stream))
        return true;
    return false;
}

// @ 0x00d00780
int cRelationshipManager::Classify(float x)
{
    if (x > mLow && mMid > x)
        return 2;
    if (x >= mMid && mHigh > x)
        return 3;
    if (x >= mHigh)
        return 4;
    if (mLow >= x && x > mMin)
        return 1;
    return 0;
}

// @ 0x00d007f0
float __stdcall FUN_00d007f0(cEmpire* a, cEmpire* b)
{
    if (a->mFlag8a || b->mFlag8a)
        return 0.0f;
    float v = -((float)(b->GetIndex() - 1) * 0.4f);
    if (b->GetIndex() > 1)
        v = v - (float)b->GetCommunityScore() * 0.2f;
    if (!a->mFlag89 && !b->mFlag89)
        v = v - 3.0f;
    if (!b->mFlag89)
        return v;
    cTerrainSphere* sph = NounManager()->GetCurrentTerrainSphere();
    switch (sph->GetType()) {
    case 2:
        v = v * 1.5f;
        break;
    case 0:
        v = v * 0.33f;
        break;
    }
    return v;
}

// @ 0x00d009a0
void FUN_00d009a0(int* a, int* b)
{
    switch (GetCurrentGameMode()) {
    case 0x1654c05: {
        int e = GetPlayerEmpireID();
        if (*a == e && IsPlayerEmpire(*a) && IsPlayerEmpire(*b)) {
            int t = *a;
            *a = *b;
            *b = t;
        }
        break;
    }
    case 0x1654c02: {
        int e = NounManager()->GetPlayerEmpireOrMinus1();
        if (*a == e) {
            int t = *a;
            *a = *b;
            *b = t;
        }
        break;
    }
    }
}

// @ 0x00d00a10
float cRelationshipManager::ClampRelationship(void* a, void* b, void* c)
{
    float v = CalculateRelationshipAbsolute(a, b, c);
    float lo = -10.0f;
    float hi = 10.0f;
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

// @ 0x00d00a70
int cRelationshipManager::ClampClassify(void* a, void* b, void* c)
{
    float v = CalculateRelationshipAbsolute(a, b, c);
    float lo = -10.0f;
    float hi = 10.0f;
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss v, xmm0
    }
    if (v > mLow && mMid > v)
        return 2;
    if (v >= mMid && mHigh > v)
        return 3;
    if (v >= mHigh)
        return 4;
    if (mLow >= v && v > mMin)
        return 1;
    return 0;
}

// @ 0x00d00b40
float __stdcall FUN_00d00b40(int id, cEmpire* p)
{
    float v = 0.0f;
    if (p->mId46c == id) {
        switch (p->GetStance()) {
        case 2:
            v = -3.0f;
            break;
        case 1:
            v = -2.0f;
            break;
        case 0:
            v = -4.0f;
            break;
        }
    }
    if (p->mFlag89) {
        cTerrainSphere* sph = NounManager()->GetCurrentTerrainSphere();
        if (sph->GetType() >= 2) {
            v = v * 2.0f;
        } else {
            sph = NounManager()->GetCurrentTerrainSphere();
            if (sph->GetType() >= 1)
                v = v * 1.5f;
        }
    }
    return v;
}

// @ 0x00d00c00
bool FUN_00d00c00(cVarListSerializer* ser, cRBMap* map)
{
    for (void* node = map->mpRoot; node != &map->mpHead; node = RBTreeIncrement(node)) {
        char* data = (char*)node + 0x18;
        if (data)
            ser->SerializeNode(data, g_str_01582008, g_wstr_01478d94);
    }
    return true;
}

// @ 0x00d00d00
float FUN_00d00d00(void* a, void* b)
{
    switch (SP_RelationshipManager()->ClampClassify(a, b, (void*)1)) {
    case 0:
        return 10.0f;
    case 1:
        return 30.0f;
    case 3:
        return 50.0f;
    case 4:
        return 80.0f;
    default:
        return 100.0f;
    }
}

// @ 0x00d00d60
float cRelationshipManager::RelationshipBetween(cInterface* a, cInterface* b, void* c)
{
    if (a == 0 || b == 0)
        return 0.0f;
    unsigned ia = a->GetId();
    unsigned ib = b->GetId();
    return ClampRelationship((void*)ia, (void*)ib, c);
}

// @ 0x00d00db0
void cRelationshipManager::LoadProperties()
{
    cPropRef ref;
    cPropertyManager* pm = PropertyManager();
    ref = 0;
    if (!pm->FindSet(0x5c770db7, &ref.mp))
        goto release;
    {
        Property* p;
        if (!ref.mp)
            return;
        if (ref.mp->GetProperty(0x1d379fa, &p) && p->mType == 0xd)
            mMin = *p->GetFloat();
        if (!ref.mp)
            return;
        if (ref.mp->GetProperty(0x1d37be0, &p) && p->mType == 0xd)
            mLow = *p->GetFloat();
        if (!ref.mp)
            return;
        if (ref.mp->GetProperty(0x1d37a06, &p) && p->mType == 0xd)
            mMid = *p->GetFloat();
        if (!ref.mp)
            return;
        if (ref.mp->GetProperty(0x1d37a0c, &p) && p->mType == 0xd)
            mHigh = *p->GetFloat();
    }
release:
    if (ref.mp)
        ref.mp->Release();
}
