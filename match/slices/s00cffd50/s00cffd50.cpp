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

// ------------------------------------------------------------------ token translator
// SP::cCivTokenTranslator::TranslateToken: FNV-1 hash dispatch over the civilization-communication
// token names.  Numeric tokens print a struct field through the locale number formatter; name tokens
// forward a cast game object's display name; the b7c9a88x family asks FindTargetCity for a kind and
// prints that city's name; 0x6d2ddc32/0xf314632d print the planet spice value (space game mode) or a
// plain city value (other modes).

extern const wchar_t g_wstrEmpty_013ec468[];   // 0x013ec468 (empty wide string / number prefix)
extern float g_147256c;                        // 0x0147256c (900.0f)

struct WString2
{
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08

    WString2& assign(const wchar_t* s);                          // 0x005c3d90 (ret 4)
    WString2& assign(const wchar_t* first, const wchar_t* last); // 0x00423650 (ret 8)
};

uint32_t __cdecl FNV1_String16(const wchar_t* s, uint32_t seed, int fold);   // 0x00932f30
void __cdecl SetNumberString(int64_t value, wchar_t* buf, int cch);          // 0x00881ae0
void __cdecl FormatNumberDouble(double value, wchar_t* buf, int cch, int flags); // 0x00881ea0

void __cdecl FUN_00cfe9c0(void* source, void** civ, void** city);            // 0x00cfe9c0
int  __cdecl FUN_00c6fe00(int type);                                         // 0x00c6fe00
float __cdecl FUN_00c71f00(float m, float b, float maxSpice, char home,
                           char player, char param7, float param8, int planet,
                           char param10);                                    // 0x00c71f00
float __cdecl FUN_00c72030(void* civ);                                       // 0x00c72030
void* __cdecl GetActivePlanet();                                             // 0x01021260
void* __cdecl GetPlayerEmpire();                                             // 0x01021300

namespace SP {

class cGameData;
class cCity;
class cPlanet;
class cPlanetStar;
class cEmpire;

class cGameTokenTranslator
{
public:
    virtual ~cGameTokenTranslator();
    virtual int AddRef();
    virtual int Release();
    virtual int GetRefCount() const;
    virtual bool TranslateToken(const wchar_t* token, WString2* out);   // 0x00b324f0
    virtual void OnLocaleChange();
    unsigned int mPad04[2];        // +0x04 .. +0x0b
};

class cCivTokenTranslator : public cGameTokenTranslator
{
public:
    cGameData* mpSource;           // +0x0c
    cCity* mpTargetCity;           // +0x10
    int mOffers[5];                // +0x14 .. +0x27
    int mCurrencyNumber;           // +0x28

    bool TranslateToken(const wchar_t* token, WString2* out);
};

class cNameProvider            // embedded display-name interface at object + 0x34
{
public:
    virtual void v00();
    virtual const wchar_t* GetName();   // +0x04
};

class cRbTree                  // eastl::rbtree<unsigned, ...>
{
public:
    void** find(void** out, const unsigned int* key);   // 0x00e5c780
};

class cEconTuning
{
public:
    float FUN_0102f8c0(int index);                      // 0x0102f8c0 (ret 4)
};
cEconTuning* FUN_0102f810();                            // 0x0102f810

class cSPGameDataUFO
{
public:
    int AddRef();                                       // 0x00801920
};

class cCivData
{
public:
    float FUN_00bf6fa0(int a);                          // 0x00bf6fa0 (ret 4)
};

class cPlanetStar            // planet + 0x13c
{
public:
    void* GetBannerOwner();                             // 0x00b8de30
    void* GetChild(int index);                          // 0x00b8dec0 (ret 4)
    int mField15c;                                      // +0x15c
    int mField160;                                      // +0x160
    unsigned char mField184[4];                         // +0x184
};

class cPlanet
{
public:
    unsigned char mPad000[0x13c];
    cPlanetStar* mpStar;                                // +0x13c

    void* GetEmpire();                                  // 0x00c71e30
};

class cEmpire
{
public:
    cPlanetStar* GetHomePlanet();                       // 0x00c31730
};

class cCity
{
public:
    unsigned char mPad000[0x34];
    cNameProvider mName;                                // +0x34

    int WealthAmount();                                 // 0x00bd8b80
};

cCity* FindTargetCity(int kind, cGameData* source);     // 0x00cfee00

}  // namespace SP

static __forceinline bool SetNumberToken(int value, wchar_t* buf, WString2* out)
{
    SetNumberString((int64_t)value, buf, 0x40);
    buf[0x3f] = 0;
    const wchar_t* end = buf;
    while (*end != 0)
        ++end;
    out->assign(buf, end);
    return true;
}

static __forceinline bool SetFloatToken(float value, wchar_t* buf, WString2* out)
{
    out->assign(g_wstrEmpty_013ec468);
    FormatNumberDouble((double)value, buf, 0x40, 0);
    buf[0x3f] = 0;
    out->assign(buf);
    return true;
}

static __forceinline bool CivNameToken(void* source, int offset, WString2* out)
{
    void* civ = 0;
    void* city = 0;
    FUN_00cfe9c0(source, &civ, &city);
    SP::cNameProvider* p =
        (SP::cNameProvider*)((char*)*(void**)((char*)civ + offset) + 0x34);
    out->assign(p->GetName());
    return true;
}

static __forceinline bool FindCityToken(int kind, void* source, WString2* out)
{
    void* civ = 0;
    void* city = 0;
    FUN_00cfe9c0(source, &civ, &city);
    SP::cCity* target = SP::FindTargetCity(kind, (SP::cGameData*)civ);
    if (target != 0)
        out->assign(((SP::cNameProvider*)((char*)target + 0x34))->GetName());
    return true;
}

// @ 0x00cffd50
bool SP::cCivTokenTranslator::TranslateToken(const wchar_t* token, WString2* out)
{
    wchar_t buf[64];
    int number = 0;
    switch (FNV1_String16(token, 0x811c9dc5, 1))
    {
    case 0x29f73bf5: {
        void* civ = 0;
        void* city = 0;
        FUN_00cfe9c0(mpSource, &civ, &city);
        unsigned int key = 1;
        void* slot;
        void** found = ((SP::cRbTree*)((char*)civ + 0x44))->find(&slot, &key);
        out->assign(*(const wchar_t**)((char*)*found + 0x14));
        return true;
    }

    case 0x3dd91065:
        return CivNameToken(mpSource, 0x2ac, out);

    case 0x41d1ce62:
        if (mpTargetCity == 0)
            return true;
        out->assign(mpTargetCity->mName.GetName());
        return true;

    case 0x4b8bb638:
        number = mOffers[3];
        break;

    case 0x4b8bb639:
        number = mOffers[4];
        break;

    case 0x4b8bb63d:
        number = mOffers[0];
        break;

    case 0x4b8bb63e:
        number = mOffers[1];
        break;

    case 0x4b8bb63f:
        number = mOffers[2];
        break;

    case 0x6d2ddc32: {
        void* civ = 0;
        void* cityRaw = 0;
        FUN_00cfe9c0(mpSource, &civ, &cityRaw);
        SP::cCity* city = (SP::cCity*)cityRaw;
        if (city == 0)
            return true;
        if (GetCurrentGameMode() != 0x1654c05)
        {
            number = city->WealthAmount();
            break;
        }

        SP::cPlanet* planet = (SP::cPlanet*)GetActivePlanet();
        void* sortRes = planet->mpStar->GetBannerOwner();
        int arch = ((SP::cSPGameDataUFO*)sortRes)->AddRef();
        int cls = FUN_00c6fe00(arch);
        float value = FUN_0102f810()->FUN_0102f8c0(cls);

        SP::cEmpire* empire = (SP::cEmpire*)planet->GetEmpire();
        bool isPlayer = (empire == (SP::cEmpire*)GetPlayerEmpire());
        bool isHome = false;
        if (isPlayer) {
            if (planet->mpStar == empire->GetHomePlanet())
                isHome = true;
        }

        SP::cPlanetStar* star = planet->mpStar;
        int count = 1;
        if (star->mField15c != star->mField160) {
            void* e = star->GetChild(0);
            count = (*(int*)((char*)e + 0x40) - *(int*)((char*)e + 0x3c)) >> 2;
        }

        float result = FUN_00c71f00((float)city->WealthAmount(), 0.0f, g_147256c,
                                    (char)isHome, (char)isPlayer, 0, value, count, 1);
        return SetFloatToken(result, buf, out);
    }

    case 0x807555b7:
        return CivNameToken(mpSource, 0x2f8, out);

    case 0xa36d8feb:
        return CivNameToken(mpSource, 0x2d0, out);

    case 0xb0554dd4:
        number = mCurrencyNumber;
        break;
    case 0xb7c9a880:
        return FindCityToken(2, mpSource, out);

    case 0xb7c9a881:
        return FindCityToken(1, mpSource, out);

    case 0xb7c9a882:
        return FindCityToken(0, mpSource, out);

    case 0xb7c9a884:
        return FindCityToken(6, mpSource, out);

    case 0xb7c9a885:
        return FindCityToken(5, mpSource, out);

    case 0xb7c9a886:
        return FindCityToken(4, mpSource, out);

    case 0xb7c9a887:
        return FindCityToken(3, mpSource, out);

    case 0xb7c9a88a:
        return FindCityToken(8, mpSource, out);

    case 0xb7c9a88b:
        return FindCityToken(7, mpSource, out);

    case 0xd4744496:
        return FindCityToken(9, mpSource, out);

    case 0xee3981ea: {
        void* civ = 0;
        void* cityRaw = 0;
        FUN_00cfe9c0(mpSource, &civ, &cityRaw);
        SP::cCity* city = (SP::cCity*)cityRaw;
        out->assign(city->mName.GetName());
        return true;
    }

    case 0xf314632d: {
        void* civ = 0;
        void* city = 0;
        FUN_00cfe9c0(mpSource, &civ, &city);
        if (civ == 0)
            return true;
        if (GetCurrentGameMode() == 0x1654c05)
            return SetFloatToken(FUN_00c72030(civ), buf, out);
        number = (int)((SP::cCivData*)civ)->FUN_00bf6fa0(0);
        break;
    }

    default:
        return cGameTokenTranslator::TranslateToken(token, out);
    }

    SetNumberToken(number, buf, out);
    return true;
}
