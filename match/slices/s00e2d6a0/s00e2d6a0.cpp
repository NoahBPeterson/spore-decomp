// cSPUIRolloverCivRelationship::ShowRelationshipRollover: fills and positions the civ-relationship rollover.
// All callees are external (masked relocations); types below are layout stubs.
#include "types.h"

struct Vector2 { float x, y; };

struct WStr {  // eastl::basic_string<wchar_t> (begin, end, capacity-end)
    wchar_t *b, *e, *cap;
    void RangeInitialize(const wchar_t* s);
};

struct Variant {  // EA::Variant
    char data[0x10];
    unsigned short mFlags;
    unsigned short mTypeId;
    void Set(int type, int kind, void* p, int size, int copy);
    void Destruct(int);
};

struct cString { char d[0x14]; const wchar_t* GetText(); };

struct IWindow {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual IWindow* QueryChild(unsigned id);                 // 0x0c
    virtual void v10();
    virtual void SetFlag14(int on);                           // 0x14
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void SetColor(unsigned argb);                     // 0x28
    virtual void v2c(); virtual void v30();
    virtual float* GetArea();                                 // 0x34
    virtual float* GetParentArea();                           // 0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c();
    virtual void SetArea(const float* r);                     // 0x60
    virtual void SetOffset(float x, float y);                 // 0x64
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetVisible(int a, int b);                    // 0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void GetPos(Vector2* out, float x, float y);      // 0xc0
    virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindow(unsigned id, int recurse);    // 0xf0
};

struct Civ { int Index(); };            // FUN_00bf0f40

struct Sphere { bool Check(); };        // FUN_00c75650

struct Owner { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
               virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
               virtual void va(); virtual void vb(); virtual void vc(); virtual void vd(); virtual void ve();
               virtual void vf(); virtual void v10(); virtual void v11(); virtual void v12();
               virtual int GetEmpireId(); };  // 0x4c

struct cGameNounManager {
    Civ* GetPlayerCivilization();       // SP::cGameNounManager::GetPlayerCivilization
    Owner* GetPlayerTribe();            // 0xbfc5f0
    Civ* FindCivById(int id);           // FUN_00b25f40
    Sphere* GetCurrentTerrainSphere();  // 0xf67d90
};
struct cStarManager { void* GetEmpireByID(int id); };
struct cRelationshipManager {
    float CalculateRelationshipAbsolute(int a, int b, int c);
    float CalculateRelationshipPersonality(Civ* a, Civ* b);
    float Relation2(Civ* a, Civ* b);       // FUN_00d007f0
    float CalculateRelationshipCityProximity(Civ* a, Civ* b);
    float Relation4(Civ* a, Civ* b);       // FUN_00d00b40
    int   GetLevel(int a, int b, int c);   // FUN_00d00a70
    void  GetThresholds(float* a, float* b, float* c, float* d);  // FUN_00d00750
};

extern char kGameModeA, kGameModeB, kGameModeC;   // 0x1654c02 / 0x1654c04 / 0x1654c05
const void* GetCurrentGameMode();
cGameNounManager* NounManager();
cStarManager* StarManager();
cRelationshipManager* RelationshipManager();
int GetPlayerEmpireOrMinus1();

struct Events { unsigned *b, *e, *c; char alloc; };
Events* GetRelationshipEvents();

struct U32Vec {
    unsigned *b, *e, *c;
    void Init(int n, void* alloc);      // FUN_00b93c60
    void Truncate(int n);               // FUN_00b98ea0
};
void* CopyBytes(void* dst, const void* src, unsigned bytes);   // eastl DoInsertValue (uninitialized copy)

struct RelMap {   // 28-byte scored-event map / comparator
    unsigned a, b, c;
    void* root;
    unsigned d, e, f;
    RelMap() {}
    RelMap(const RelMap& o) { CopyFrom(&o); }
    ~RelMap() { DoNukeSubtree(root); }
    void Build(int emp, int myEmp);     // FUN_00e2cce0
    void CopyFrom(const RelMap* o);     // FUN_00d01a40
    float* Find(unsigned* key);         // FUN_00be0790
    void DoNukeSubtree(void* n);
};
void SortEvents(unsigned* b, unsigned* e, RelMap cmp);        // FUN_00e2d5f0

void* op_new(unsigned n, const char* name, int a, unsigned b, const char* file, int line);
void op_delete(void* p);
extern wchar_t gEmptyW[2];
void SetNumberString(long long v, wchar_t* buf, int n);
void FUN_00808b20(IWindow* a, IWindow* b, int c);

struct cSPUIPropertyLayout {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Vf1c();
    virtual void Vf20();
    IWindow* GetRootWindow();
    char pad[0x74];
};

struct cSPUIRolloverCivRelationship : cSPUIPropertyLayout {
    cString mTooManyCities;       // +0x78
    cString mTooClose;            // +0x8c
    cString mNemesis;             // +0xa0
    cString mTerrain;             // +0xb4
    cString* mPersonality;        // +0xc8
    char pad2[0x10];
    char mStringMap;              // +0xdc (map<uint, cString>)
    char pad3[0x1b];
    int mMaxRows;                 // +0xf8

    cString* LookupString(unsigned* key);   // FUN_00e2cb00 on +0xdc
    void SetProp(unsigned id, Variant* v, int a, int b);   // FUN_00828c30
    void ShowRelationshipRollover(IWindow* anchor, int empireId, int anchorMode);
};

void SetValueTextForRollover(cSPUIRolloverCivRelationship* t, unsigned id, float v);

static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// Inline-constructed wstring from a zero-terminated buffer (eastl RangeInitialize inlined).
static inline void MakeWStr(WStr& s, const wchar_t* p) {
    s.b = s.e = s.cap = 0;
    const wchar_t* q = p;
    while (*q) ++q;
    unsigned n = (unsigned)(q - p);
    unsigned sz = n + 1;
    wchar_t* buf;
    if (sz > 1) {
        buf = (wchar_t*)op_new(sz * 2, "Simulator", 0, 0, kEastlFile, 0xd1);
        s.b = buf; s.cap = (wchar_t*)((char*)buf + sz * 2);
    } else {
        buf = gEmptyW; s.b = gEmptyW; s.cap = gEmptyW + 1;
    }
    s.e = buf;
    CopyBytes(buf, p, n * 2);
    s.e = buf + n;
    *s.e = 0;
}

static __forceinline void SendText(cSPUIRolloverCivRelationship* t, int row, WStr& s, float value) {
    Variant v;
    v.mFlags = 0; v.mTypeId = 0;
    v.Set(0x13, 9, &s, 0x10, 1);
    t->SetProp(row + 0x4d186b0, &v, 1, 0);
    if (v.mFlags & 4) v.Destruct(0);
    if ((int)(((char*)s.cap - (char*)s.b) & ~1) > 2 && s.b) op_delete(s.b);
    SetValueTextForRollover(t, row + 0x4d18700, value);
}

// Out-of-line constructed variant (RangeInitialize call).
static __forceinline void AddRow(cSPUIRolloverCivRelationship* t, int row, const wchar_t* text, float value) {
    WStr s; s.b = s.e = s.cap = 0;
    s.RangeInitialize(text);
    SendText(t, row, s, value);
}

// @ 0x00e2d6a0
void cSPUIRolloverCivRelationship::ShowRelationshipRollover(IWindow* anchor, int empireId, int anchorMode) {
    const void* mode = GetCurrentGameMode();
    Civ* playerCiv = 0;
    if (mode == &kGameModeB) playerCiv = NounManager()->GetPlayerCivilization();
    Civ* otherCiv = 0;
    if (!StarManager()->GetEmpireByID(empireId)) otherCiv = NounManager()->FindCivById(empireId);

    Vector2 anchorPos;
    anchor->GetPos(&anchorPos, 0.0f, 0.0f);
    Vf1c();
    IWindow* root = GetRootWindow();
    int rows = 0;

    int myEmpire;
    cGameNounManager* nm = NounManager();
    if (mode == &kGameModeA) myEmpire = nm->GetPlayerTribe()->GetEmpireId();
    else myEmpire = GetPlayerEmpireOrMinus1();

    float rel;
    if (empireId == myEmpire) rel = 10.0f;
    else rel = RelationshipManager()->CalculateRelationshipAbsolute(empireId, myEmpire, 0);

    int n = 0;
    if (mode == &kGameModeB) {
        if (otherCiv && otherCiv != playerCiv) {
            float f = RelationshipManager()->CalculateRelationshipPersonality(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n = 1;
            f = RelationshipManager()->Relation2(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n++;
            f = RelationshipManager()->CalculateRelationshipCityProximity(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n++;
            f = RelationshipManager()->Relation4(otherCiv, playerCiv);
            if (f >= 0.1f || f <= -0.1f) n++;
        }
    } else if (mode == &kGameModeC) {
        if (empireId != myEmpire && rel < 0.0f) {
            if (NounManager()->GetCurrentTerrainSphere()->Check()) n = 1;
        }
    }

    Events* ev = GetRelationshipEvents();
    U32Vec tmp;
    tmp.Init((int)(ev->e - ev->b), &ev->alloc);
    unsigned bytes = (unsigned)((char*)ev->e - (char*)ev->b);
    void* r = CopyBytes(tmp.b, ev->b, bytes);
    tmp.e = (unsigned*)r + (bytes >> 2);

    RelMap scores;
    scores.Build(empireId, myEmpire);
    {
        RelMap cmp(scores);
        SortEvents(tmp.b, tmp.e, cmp);
    }
    int limit = mMaxRows - n;
    if ((int)(tmp.e - tmp.b) > limit) tmp.Truncate(limit);

    int pass = 0;
    do {
        if (mode == &kGameModeB && otherCiv && otherCiv != playerCiv) {
            float f = RelationshipManager()->CalculateRelationshipPersonality(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mPersonality[playerCiv->Index()].GetText(), f);
                rows++;
            }
            f = RelationshipManager()->Relation2(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mTooManyCities.GetText(), f);
                rows++;
            }
            f = RelationshipManager()->CalculateRelationshipCityProximity(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mTooClose.GetText(), f);
                rows++;
            }
            f = RelationshipManager()->Relation4(otherCiv, playerCiv);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                AddRow(this, rows, mNemesis.GetText(), f);
                rows++;
            }
        }
        if (pass == 0 && mode == &kGameModeC) {
            if (empireId == myEmpire) goto next_pass;
            if (rel < 0.0f && NounManager()->GetCurrentTerrainSphere()->Check()) {
                AddRow(this, rows, mTerrain.GetText(), -rel);
                rows++;
            }
        }
        if (empireId == myEmpire) goto next_pass;
        for (unsigned* it = tmp.b; it != tmp.e; ++it) {
            unsigned id = *it;
            float f = *scores.Find(&id);
            if (pass == 0 ? (f >= 0.1f) : (f <= -0.1f)) {
                id = *it;
                WStr s;
                MakeWStr(s, LookupString(&id)->GetText());
                SendText(this, rows, s, f);
                rows++;
            }
        }
    next_pass:
        pass++;
    } while (pass < 2);

    wchar_t numbuf[64];
    SetNumberString((long long)(rel * 10.0f), numbuf, 0x40);
    {
        WStr s;
        MakeWStr(s, numbuf);
        Variant v;
        v.mFlags = 0; v.mTypeId = 0;
        v.Set(0x13, 9, &s, 0x10, 1);
        SetProp(0x4d3f26b, &v, 1, 0);
        if (v.mFlags & 4) v.Destruct(0);
        if ((int)(((char*)s.cap - (char*)s.b) & ~1) > 2 && s.b) op_delete(s.b);
    }

    IWindow* title = root->FindWindow(0x4d3f26b, 1);
    IWindow* colorObj = 0;
    if (title) colorObj = (IWindow*)((IWindow*)title)->QueryChild(0xf15f4bd);

    int level;
    if (empireId == myEmpire) level = 4;
    else level = RelationshipManager()->GetLevel(empireId, myEmpire, 1);

    float t0 = 0, t1 = 0, t2 = 0, t3 = 0;
    float lo = 0, range = 0, base = 0;
    RelationshipManager()->GetThresholds(&t0, &t1, &t2, &t3);
    t0 += 10.0f; t1 += 10.0f; t2 += 10.0f; t3 += 10.0f;
    switch (level) {
    case 4: colorObj->SetColor(0xff00ff00); base = 4.0f; lo = t3; range = 20.0f - t3; break;
    case 3: colorObj->SetColor(0xff77e700); base = 3.0f; lo = t2; range = t3 - t2; break;
    case 2: colorObj->SetColor(0xffeed000); base = 2.0f; lo = t1; range = t2 - t1; break;
    case 1: colorObj->SetColor(0xfff66800); base = 1.0f; lo = t0; range = t1 - t0; break;
    case 0: colorObj->SetColor(0xffff0000); base = 0.0f; lo = 0.0f; range = t0; break;
    }

    for (unsigned i = 0; i < 5; i++) {
        IWindow* w = root->FindWindow(i + 0x4b47d00, 1);
        IWindow* c = w->QueryChild(0x105a93d);
        if (c) c->SetFlag14(1);
    }
    IWindow* sel = root->FindWindow(level + 0x4b47d00, 1);
    sel->SetVisible(1, 1);
    sel->QueryChild(0x105a93d)->SetFlag14(0);

    float pos = ((rel + 10.0f - lo) / range + base) * 0.2f;
    float lim = 1.0f;
    if (pos < 0.0f) pos = 0.0f;
    if (pos > lim) pos = lim;

    IWindow* bar = root->FindWindow(0x66b72e6, 1);
    bar->SetOffset(pos * 126.0f + 8.0f, 25.0f);

    Vf20();
    float* a = root->GetArea();
    float rect[4];
    rect[0] = a[0];
    rect[1] = a[1];
    rect[2] = a[2];
    rect[3] = (float)(rows * 0x15 + 0x3b) + a[1];
    root->SetArea(rect);

    IWindow* target;
    if (anchorMode == 0) {
        FUN_00808b20(anchor, root, 0);
        target = root;
    } else {
        float x, y;
        if (anchorMode == 1) {
            float* pr = anchor->GetParentArea();
            x = anchorPos.x;
            y = (pr[3] - pr[1]) + anchorPos.y;
        } else {
            float* pr = anchor->GetParentArea();
            x = (pr[2] - pr[0]) + anchorPos.x;
            y = anchorPos.y;
        }
        target = root;
        target->SetOffset(x, y);
    }
    target->SetVisible(1, 1);
}
