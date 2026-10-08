// Slice s00b6baf0: tooltip/UI text-variable resolver. Given an object, switches on its variable id
// (obj->vt[0x38]) and builds a cBuildXHTMLDetokenizer::cVar from the matching string (species and
// nest names, empire/city names, a per-civilization string table keyed by id).
// Flags: /O2 /MD /Gy /TP (no /EHsc in this module).
#include "types.h"

void  EAFree(void* p);                                                    // 0x00F47380

extern const wchar_t gEmptyStr[];       // 0x013EC468 (L"")
extern void* gEmptyRep;                 // 0x01667BAC (shared empty string rep)

// ---------------------------------------------------------------------------
// text variable (wide-string inline buffer); 0x006743F0 takes the source text
// ---------------------------------------------------------------------------
struct cVar {
    uint32_t mData[0x58 / 4];
    cVar(const wchar_t* psz);            // 0x006743F0
};

// 12-byte eastl wide string with the shared empty rep (dtor frees a heap buffer)
struct Str12 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacityEnd;
    Str12() {
        mpBegin = (wchar_t*)&gEmptyRep;
        mpEnd = (wchar_t*)&gEmptyRep;
        mpCapacityEnd = (wchar_t*)((char*)&gEmptyRep + 2);
    }
    ~Str12() {
        if ((((int)((char*)mpCapacityEnd - (char*)mpBegin)) & -2) > 2 && mpBegin)
            EAFree(mpBegin);
    }
};

class cString {
public:
    cString();                                                                  // 0x006B5060
    cString(uint32_t tableID, int instanceID, const wchar_t* defaultText);      // 0x006B5770
    ~cString();                                                                 // 0x006B5240
    bool Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006B54B0
    const wchar_t* GetText();                                                   // 0x006B55C0
private:
    uint32_t mData[5];
};

// ---------------------------------------------------------------------------
// objects (only the vtable slots / fields used here)
// ---------------------------------------------------------------------------
struct NameSub {                         // sub-object with a vtable at +0x34 of "named" things
    virtual void n0();
    virtual const wchar_t* GetName();    // +0x04
};
struct Named {
    char pad[0x34];
    NameSub sub;
};

struct City;
struct VObj {                            // generic interface object
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual VObj* Cast(uint32_t id);     // +0x0c
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0A(); virtual void s0B();
    virtual void s0C(); virtual void s0D();
    virtual int GetVarID();              // +0x38
    virtual void s0F(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual int GetID();                 // +0x4c
    virtual void s14(); virtual void s15();
    virtual int GetIndex();              // +0x58
    virtual Named* GetNamed();           // +0x5c
    virtual void s18(); virtual void s19(); virtual void s1A(); virtual void s1B();
    virtual void s1C();
    virtual const wchar_t* GetText();    // +0x74
    virtual void s1E(); virtual void s1F(); virtual void s20();
    virtual void* Get84();               // +0x84 (a City* or a Named*, depending on the object)
    City* GetCityMember();               // 0x00BCE5C0
};

struct Civ {                             // civilization (vtable object with a name and a string table)
    virtual void c0(); virtual void c1(); virtual void c2();
    virtual struct TableOwner* Cast(uint32_t id);   // +0x0c
    char pad[0x38 - 4 - 12 + 0];
    const wchar_t* mpName;               // +0x3c
    const wchar_t** GetNamePtr();        // 0x005C65E0 (returns &mpName)
};
struct StarMgr {
    Civ* GetEmpireByID(int id);                 // 0x00BA9370
};
StarMgr* StarManager();                                         // 0x00B3D2A0

struct StrNode {
    char pad[0x14]; const wchar_t* value;       // key at +0x10, value at +0x14
};
struct StrIter { StrNode* node; StrIter() {} StrIter(const StrIter& o) { node = o.node; } };
struct StrMap {
    StrIter find(const uint32_t& key);                          // 0x00E5C780
};
struct TableOwner {
    char pad[8];
    StrMap map;
};

struct Species {
    char pad[0x51c]; const wchar_t* mpName;
};

struct Herd {
    char pad[0x84];
    uint8_t b84;
    char pad2[0x1f];
    Species* ma4;                         // +0xa4
};
struct Creature {
    char pad0[0x124];
    uint8_t b124;
    char pad2[3];
    Herd* m128;
    char pad3[0x714 - 0x12c];
    int m714;
};

struct SpeciesMgr {
    Species* GetAvatarProfile();             // 0x004DF420
};
SpeciesMgr* GetSetting9();                                      // 0x00401090

struct Terrain {
    bool Check(uint32_t id, uint32_t* out);     // 0x00C77380
};
struct NounMgr {
    Terrain* GetTerrain();                                      // 0x00F67D90
    Named* FindNamed(int id);                                   // 0x00B25F40
};
NounMgr* NounManager();                                         // 0x00B3D300

struct City {
    Civ* GetCivilization();                        // 0x00BD9BF0
};

struct Rec {
    bool Get(Str12* out);                           // 0x00F28B80
};
struct RecMgr {
    Rec* Find(VObj* obj);                        // 0x00F3E900
};
struct Globals {
    char pad[0x74]; RecMgr* m74;
};
extern Globals* gGlobals16c7aa4;                                // 0x016C7AA4

struct TableRow {
    char pad[0x68]; cString str;
};
TableRow* LookupRow(int idx);                                   // 0x00C9CEC0

struct Planet {
    int GetState();                              // 0x00C70E00
};
struct UniCtx;
int GetCurrentGameMode();                                       // 0x00B5B800
UniCtx* GetUniverseContext();                                   // 0x01021080
Planet* GetActivePlanet();                                      // 0x01021260
Herd* GetDesiredAvatarHerd(bool b);                             // 0x00D40B40

// helper casts / siblings (cdecl)
VObj*   CastB033(VObj* obj);                                    // 0x00B67740
VObj*   CastEE02(VObj* obj);                                    // 0x00B676E0
VObj*   CastE9CB(VObj* obj);                                    // 0x00B67720
Creature* CastB92(VObj* obj);                                   // 0x00B1FC00
Named*  CastEE9B(VObj* obj);                                    // 0x00AC86D0
Named*  CheckType(VObj* obj, uint32_t type);                    // 0x00AC80D0
cVar    ResolveRollover(VObj* obj);                             // 0x00B6B4C0
cVar    ResolveB6BA50(VObj* obj);                               // 0x00B6BA50
cVar    ResolveB6B810(VObj* obj);                               // 0x00B6B810
VObj*   CityOf(VObj* obj);                                      // 0x00BCE5C0

// @ 0x00B6BAF0
cVar ResolveVar(VObj* obj)
{
    if (GetCurrentGameMode() == 0x1654c10)
    {
        Rec* rec = gGlobals16c7aa4->m74->Find(obj);
        Str12 v;
        if (rec && rec->Get(&v))
            return cVar(v.mpBegin);
    }

    Named* x;
    int key;
    switch (obj->GetVarID())
    {
        case 0xd0036e08:
            return ResolveRollover(obj);

        case 0xb033b403:
        {
            VObj* p = CastB033(obj);
            int id = p->GetID();
            Civ* e = StarManager()->GetEmpireByID(id);
            if (e)
                return cVar(*e->GetNamePtr());
            cString s;
            if ((((Creature*)p)->m714 == 0xb && s.Load(0x2db6dad3, 0x6749c10, 0)) ||
                s.Load(0x2db6dad3, 0x678cddf, 0))
                return cVar(s.GetText());
            return cVar(gEmptyStr);
        }

        case 0xee9b2232:
            x = CastEE9B(obj);
            goto chk;

        case 0xee02c7:
            x = CastEE02(obj)->GetNamed();
            goto chk;

        case 0x116d858:
        {
            VObj* a = obj->Cast(0x116d858);
            TableRow* r = LookupRow(a->GetIndex());
            return cVar(r->str.GetText());
        }

        case 0x137e8e0:
        {
            int id = obj->GetID();
            Named* n = NounManager()->FindNamed(id);
            obj->Cast(0x137e8e0);
            if (n)
                return cVar(n->sub.GetName());
            goto dflt;
        }

        case 0x1a55e4d:
            key = 9;
            goto lookup;

        case 0x1b92b27:
        {
            Creature* c = CastB92(obj);
            if (!c) goto dflt;
            Herd* h = c->m128;
            if (!h) goto dflt;
            if (h->ma4 == GetSetting9()->GetAvatarProfile())
            {
                uint32_t k;
                if (NounManager()->GetTerrain()->Check(0x514a219, &k))
                {
                    if (GetDesiredAvatarHerd(false) == c->m128)
                        return cVar(cString(0xad56080c, 0x658f2d1, L"~New Nest").GetText());
                    if (c->m128->b84)
                        return cVar(cString(0xad56080c, 0x658f2d2, L"~Old Nest").GetText());
                }
                else if (c->m128->b84)
                    return cVar(cString(0xad56080c, 0x658f2d0, L"~Home Nest").GetText());
            }
            if (!(c->b124 & 1))
                return cVar(cString(0xad56080c, 0x658f2d3, L"~Unknown Species").GetText());
            return cVar(c->m128->ma4->mpName);
        }

        case 0x436f315:
            key = 0xa;
            goto lookup;

        case 0x4e3faaf:
            return ResolveB6BA50(obj);

        case 0x70704db:
        {
            VObj* p = CastE9CB(obj);
            if (!p) goto dflt;
            return cVar(p->GetText());
        }

        case 0xff10521:
            key = 7;
            goto lookup;

        case 0xecade42:
            key = 8;
            goto lookup;

        case 0x1007ae63:
            if (GetCurrentGameMode() == 0x1654c05)
            {
                VObj* a = obj->Cast(0x1007ae63);
                if (a)
                {
                    x = (Named*)a->Get84();
                    goto nochk;
                }
                key = 0xc;
            }
            else
                key = 6;
            goto lookup;

        case 0x4f176642:
            return ResolveB6B810(obj);

        case 0x4f396a66:
            x = CheckType(obj, 0x18c6d19);
            goto chk;

        default:
            goto dflt;
    }

chk:
    if (!x) goto dflt;
nochk:
    return cVar(x->sub.GetName());

lookup:
    {
        VObj* bld = obj->Cast(0xe9cb8ba);
        VObj* oth = obj->Cast(0x436f315);
        int mode = GetCurrentGameMode();
        Civ* civ = 0;
        City* city;
        switch (mode)
        {
            case 4:
            cityPath:
                if (bld)
                    city = (City*)bld->Get84();
                else if (oth)
                    city = oth->GetCityMember();
                else
                    break;
                civ = city->GetCivilization();
                break;
            case 5:
            {
                if (!GetUniverseContext() && GetActivePlanet()->GetState() == 4)
                    goto cityPath;
                int id = -1;
                if (bld)
                    id = bld->GetID();
                else if (oth)
                    id = oth->GetID();
                civ = StarManager()->GetEmpireByID(id);
                break;
            }
            default:
                __assume(0);
        }
        bool bNoCiv = (civ == 0);
        TableOwner* t = civ ? civ->Cast(0x5593a1a) : 0;
        const wchar_t* text;
        if (bNoCiv)
            text = gEmptyStr;
        else
        {
            uint32_t k = key;
            text = t->map.find(k).node->value;
        }
        return cVar(text);
    }

dflt:
    return cVar(gEmptyStr);
}
