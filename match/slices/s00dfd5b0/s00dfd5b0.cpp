// Slice s00dfd5b0 -- editor mission UI helpers (continuation of s00dfa5c0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

void  operator_delete_(void* p);            // 0x00f47380
struct Lay   { void* FindWindowByID(int id, int a); };  // 0x008105b0 thiscall ret8
void  FUN_d3a0(void* self, void* p);        // 0x00dfd3a0 (__thiscall ret4, see TFun2)
void  FUN_e0e0(void* self, void* p);        // 0x00dfdfe0 (__thiscall ret4, see TFun2)
// Both helpers are __thiscall (ecx = the sub-object, one stack word, callee pops
// it).  MSVC 2008 refuses an explicit __thiscall on a free function, so the calls
// go through thiscall function pointers instead.
typedef void (__thiscall* TFun2)(void* self, void* p);
struct F28 { void M(); };                   // 0x00f280f0 thiscall
struct VecC { void F(unsigned a, unsigned b); }; // 0x00dfc600 thiscall ret8
struct Obj4 { void F_bba0(); };             // 0x00dfbba0 thiscall
struct VecB { void F_b850(unsigned a, unsigned b); }; // 0x00dfb850 thiscall ret8
struct UI2 {
    void M_d8a0();              // 0x00dfd8a0 thiscall
    void F_de90();              // 0xdfde90
    void* F_e170(int* p);       // 0xdfe170
    UI2(const UI2& s);          // 0x00dfdfe0 thiscall ret4
};

// ---- externals / globals used by the mission-UI helpers ----------------------
void* ObjectTemplateDB();                        // 0x0067cb40
void* GetManager_67dcd0();                       // 0x0067dcd0 ResourceManager
void* AppSystem_67dd00();                        // 0x0067dd00 SP::AppSystem
int   GetAssetState_552300(const void* key);     // 0x00552300 (caller pops)
void __fastcall Vec34_assign_dfcee0(void* self, void* d, const void* src);  // 0x00dfcee0 ret4
void __fastcall PtrVecBase_4aa350(void* self, void* d, unsigned n, const void* allocTag); // 0x004aa350 ret8

// a query-result vector holds POD elements: tearing it down releases the allocation only
static inline void freeQuery(void* p) {
    if (p != 0 && ((int*)p)[-1] != 0)
        operator_delete_(p);
}
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern unsigned g_16a1058;                       // 0x016a1058 mission-field id
extern unsigned g_147ebe0[3];                    // 0x0147ebe0 slot window ids
extern unsigned g_147ebec[3];                    // 0x0147ebec slot label ids
extern void*    g_16a1344;                       // 0x016a1344 kGUI_PanelIDs

// ---- SP::FunctionalMatch constraint machinery --------------------------------
namespace SP { namespace FunctionalMatch { struct Constraint; struct CVec; } }

void __fastcall Constraint_copyCtor_606880(SP::FunctionalMatch::Constraint* self, void* d,
                                           const SP::FunctionalMatch::Constraint* src); // 0x00606880

namespace SP { namespace FunctionalMatch {

struct CVec {                                   // vector of Constraint, 0x14 bytes
    Constraint* mpBegin;                        // +0x00
    Constraint* mpEnd;                          // +0x04
    Constraint* mpCapacity;                     // +0x08
    const char* mpName;                         // +0x0c
    unsigned    mFlags;                         // +0x10
    CVec() : mpBegin(0), mpEnd(0), mpCapacity(0), mpName(0), mFlags(0) {}
    CVec(const CVec& x);                                       // 0x004e38d0
    void DoDestroyValues(Constraint* first, Constraint* last); // 0x004e39a0
    void DoInsertValue(Constraint* pos, const Constraint& v);  // 0x004e39d0
    void push_back(const Constraint& v);
    void destroy();
};

struct Constraint {                             // 0x24 bytes
    unsigned mParameter;                        // +0x00
    unsigned mType;                             // +0x04
    unsigned mValueMin;                         // +0x08
    unsigned mValueMax;                         // +0x0c
    CVec     mConstraints;                      // +0x10 (0x14 bytes)
};

inline void CVec::push_back(const Constraint& v) {
    if (mpEnd < mpCapacity) {
        Constraint* slot = mpEnd;
        mpEnd = (Constraint*)((char*)mpEnd + 0x24);
        if (slot != 0)
            Constraint_copyCtor_606880(slot, 0, &v);
    } else {
        DoInsertValue(mpEnd, v);
    }
}

inline void CVec::destroy() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
        operator_delete_(mpBegin);
}

}  // namespace FunctionalMatch
}  // namespace SP

void __fastcall Constraint_ctorEqual_558960(SP::FunctionalMatch::Constraint* self, void* d,
                                            unsigned id, int op, int val);   // 0x00558960
void __fastcall Constraint_ctorNotEq_558a20(SP::FunctionalMatch::Constraint* self, void* d,
                                            unsigned id, int op, int val);   // 0x00558a20
void __fastcall Constraint_ctorAny_558ae0 (SP::FunctionalMatch::Constraint* self, void* d,
                                            int any, SP::FunctionalMatch::CVec vec); // 0x00558ae0

// ObjectTemplateDB()->vtable[0x38](&results, &query) -- constrain a template query.
static inline void DBFindTemplates(void* out, void* query) {
    void* db = ObjectTemplateDB();
    ((void(__fastcall*)(void*, void*, void*, void*))(*(void***)db)[0x38 / 4])(db, 0, out, query);
}

// ---- random ------------------------------------------------------------------
namespace EA { namespace Random {
struct RandomLinearCongruential { unsigned RandomUint32Uniform(unsigned n); };  // 0x00a68fb0
}}
extern EA::Random::RandomLinearCongruential cRandomGlobal;      // 0x01601760

// ---- Simulator UI objects ----------------------------------------------------
struct Slot {                                   // 0x38-byte window slot entry
    int  x;                                     // +0x00
    int  y;                                     // +0x04
    int  z;                                     // +0x08
    char pad0c[0x14];                           // +0x0c..+0x1f
    char state;                                 // +0x20
    char pad21[0x17];                           // +0x21..+0x37
};
struct PropKey {                                // selection key, 0x18 bytes
    int type;                                   // +0x00
    int a1;                                     // +0x04
    int a2;                                     // +0x08
    int a3;                                     // +0x0c
    int a4;                                     // +0x10
    int a5;                                     // +0x14
};
struct WString {                                // eastl::basic_string<wchar_t>, 0x10 bytes
    void* mpBegin;                              // +0x00
    void* mpEnd;                                // +0x04
    void* mpCap;                                // +0x08
    void* mpName;                               // +0x0c
    void Assign(const unsigned short* b, const unsigned short* e);   // 0x00423650
};
struct GGUI {                                   // Simulator UI base (cf. slice s00df9650)
    void*    mVftable;                          // +0x000
    char     pad004[0x08];                      // +0x004..+0x00b
    void*    mItem;                             // +0x00c Item*: [0]=id, [0x20]=state
    char     pad010[0x10];                      // +0x010..+0x01f
    unsigned mTimer20;                          // +0x020
    char     pad024[0x08];                      // +0x024..+0x02b
    int      mIndex;                            // +0x02c
    unsigned mCount;                            // +0x030
    int      mCur;                              // +0x034
    char     pad038[0x10];                      // +0x038..+0x047
    char     mLayout[0x18];                     // +0x048 (SPUILayout; only &mLayout is used)
    char     pad060[0x1c];                      // +0x060..+0x07b
    char     m7c;                               // +0x07c
    char     m7d;                               // +0x07d
    char     m7e;                               // +0x07e
    char     m7f;                               // +0x07f
    char     pad080[0x0c];                      // +0x080..+0x08b
    PropKey  m8c;                               // +0x08c..+0x0a3
    int      mA4;                               // +0x0a4
    int      mA8;                               // +0x0a8
    int      mAC;                               // +0x0ac
    char     mB0[0x10];                         // +0x0b0..+0x0bf
    Slot     mSlots[3];                         // +0x0c0..+0x167
    WString  mName;                             // +0x168..+0x177
    void FUN_00df97e0_GGUI();                   // 0x00df97e0
    void FUN_00df9c80_GGUI(unsigned id);        // 0x00df9c80
    void FUN_00df9b30_GGUI(int a);              // 0x00df9b30
    void FUN_00df9ef0_GGUI();                   // 0x00df9ef0
};
namespace Simulator {
struct cEditorModeUI : GGUI {                   // editor-mode template panel
    void Setup();                               // 0x00dfd5b0
    void RebuildPanel();                        // 0x00dfd8a0
    void Setup2();                              // 0x00dfdc50
};
}
namespace SP {
struct cSPUIMissions : GGUI {                   // mission-fields panel
    int* QueryMissionFields(void* out);         // 0x00dfda50
    void UpdateMissionFieldsSpace();            // 0x00dfe220
};
}

// @ 0x00dfde90
void UI2::F_de90()
{
    char* base = (char*)this + 0xe0;
    for (unsigned int i = 0; i < 3; ++i) {
        if (base[i * 0x38] == 0) {
            *(int*)((char*)this + 0x34) = i;
            M_d8a0();
        }
    }
    *(unsigned char*)((char*)this + 0x7e) = 1;
    // The "was any slot empty" flag: retail keeps it in a single byte (mov byte
    // [esp+0x10],0 / ,1) and pushes that byte's stack dword to the window.
    bool local = false;
    if (*(int*)((char*)this + 0x30) != 0) {
        char* p = base;
        int n = *(int*)((char*)this + 0x30);
        do {
            if (*p == 0) local = true;
            p += 0x38;
            --n;
        } while (n != 0);
    }
    void* w = ((Lay*)((char*)this + 0x48))->FindWindowByID(0x7ccc115, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, bool))(*(void***)w)[0x7c / 4])(w, 2, local);
}

// @ 0x00dfdf10
void __stdcall F_df10(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x534) {
        ((VecC*)(a + 0x84))->F(*(unsigned*)(a + 0x84), *(unsigned*)(a + 0x88));
        int p = *(int*)(a + 0x84);
        if (p != 0 && *(int*)(p - 4) != 0)
            operator_delete_((void*)p);
        ((F28*)(a + 0x3c))->M();
        ((F28*)a)->M();
    }
}

// @ 0x00dfdf70
void __stdcall F_df70(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x27e0) {
        ((F28*)(a + 0x2788))->M();
        unsigned end = *(unsigned*)(a + 0x74);
        for (unsigned p = *(unsigned*)(a + 0x70); p < end; p += 0x4e0)
            ((Obj4*)p)->F_bba0();
        int q = *(int*)(a + 0x70);
        if (q != 0 && *(int*)(q - 4) != 0)
            operator_delete_((void*)q);
    }
}

// @ 0x00dfe170
void* UI2::F_e170(int* p)
{
    if ((*p < 0) && (-1 < *(int*)this)) {
        int v = *(int*)((char*)this + 0x210);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_delete_((void*)v);
        ((VecB*)((char*)this + 0x2c))->F_b850(*(unsigned*)((char*)this + 0x2c), *(unsigned*)((char*)this + 0x30));
        int w = *(int*)((char*)this + 0x2c);
        if (w != 0 && *(int*)(w - 4) != 0) {
            operator_delete_((void*)w);
            *(int*)this = *p;
            return this;
        }
    } else if (-1 < *p) {
        if (*(int*)this < 0) {
            if (this != (UI2*)0xfffffffc) {
                ((TFun2)FUN_e0e0)((char*)this + 4, p + 1);
                *(int*)this = *p;
                return this;
            }
        } else {
            ((TFun2)FUN_d3a0)((char*)this + 4, p + 1);
        }
    }
    *(int*)this = *p;
    return this;
}

// ---- editor / mission-field template helpers ---------------------------------
// @ 0x00dfd5b0
void Simulator::cEditorModeUI::Setup()
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint* c = (Constraint*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x2b978c46);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec sub;
    Constraint_ctorEqual_558960(c, 0, 0xec2942cd, 0, 1);
    sub.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorNotEq_558a20(c, 0, 0x2dc9d1e, 0, 0x4178b8e8);
    sub.push_back(*c);
    c->mConstraints.destroy();

    char abuf[0x24];
    Constraint* any = (Constraint*)abuf;
    Constraint_ctorAny_558ae0(any, 0, 0, sub);
    constraints.push_back(*any);
    any->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);
    if (templates.mpBegin != templates.mpEnd) {
        unsigned n = (unsigned)((char*)templates.mpEnd - (char*)templates.mpBegin) / 0xc;
        unsigned i = cRandomGlobal.RandomUint32Uniform(n);
        unsigned* e = (unsigned*)((char*)templates.mpBegin + i * 0xc);
        unsigned elem[3];
        elem[0] = e[0];
        elem[1] = e[1];
        elem[2] = e[2];
        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, elem);
    }
    freeQuery(templates.mpBegin);
    sub.destroy();
    constraints.destroy();
}

// @ 0x00dfd8a0
void Simulator::cEditorModeUI::RebuildPanel()
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint* c = (Constraint*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x2b978c46);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);
    if (templates.mpBegin != templates.mpEnd) {
        unsigned n = (unsigned)((char*)templates.mpEnd - (char*)templates.mpBegin) / 0xc;
        unsigned i = cRandomGlobal.RandomUint32Uniform(n);
        unsigned* e = (unsigned*)((char*)templates.mpBegin + i * 0xc);
        unsigned elem[3];
        elem[0] = e[0];
        elem[1] = e[1];
        elem[2] = e[2];
        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, elem);
    }
    freeQuery(templates.mpBegin);
    constraints.destroy();
}

// @ 0x00dfda50
int* SP::cSPUIMissions::QueryMissionFields(void* outPtr)
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint* c = (Constraint*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x366a930d);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);

    unsigned* out = (unsigned*)outPtr;
    unsigned* p = (unsigned*)templates.mpBegin;
    unsigned* last = (unsigned*)templates.mpEnd;
    while (p != last) {
        unsigned elem[3];
        elem[0] = p[0];
        elem[1] = p[1];
        elem[2] = p[2];
        int state = GetAssetState_552300(elem);
        if (state == 0 && elem[0] == g_16a1058) {
            out[0] = elem[0];
            out[1] = elem[1];
            out[2] = elem[2];
            freeQuery(templates.mpBegin);
            constraints.destroy();
            return (int*)out;
        }
        p += 3;
    }
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    freeQuery(templates.mpBegin);
    constraints.destroy();
    return (int*)out;
}

// @ 0x00dfdc50
void Simulator::cEditorModeUI::Setup2()
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint* c = (Constraint*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x366a930d);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);

    char* tbl = (char*)templates.mpBegin;
    unsigned n = (tbl != (char*)templates.mpEnd)
               ? (unsigned)((char*)templates.mpEnd - tbl) / 0xc : 0;
    if (n != 0) {
        unsigned elem[3];
        bool done;
        void* ref;
        do {
            unsigned i = cRandomGlobal.RandomUint32Uniform(n - 1);
            unsigned* e = (unsigned*)(tbl + i * 0xc);
            elem[0] = e[0];
            elem[1] = e[1];
            elem[2] = e[2];

            ref = 0;
            void* mgr = GetManager_67dcd0();
            char ok = ((char(__thiscall*)(void*, void*, void*, void*, void*, void*, void*))
                       (*(void***)mgr)[0xc / 4])(mgr, elem, &ref, 0, 0, 0, 0);

            if (ref != 0) {
                void* r = ref;
                ref = 0;
                ((void(__thiscall*)(void*, void*))(*(void***)r)[4 / 4])(r, 0);
            }

            done = (ok != 0)
                && !((unsigned)m8c.type == elem[0]
                  && (unsigned)m8c.a1 == elem[1]
                  && (unsigned)m8c.a2 == elem[2]);
        } while (!done);

        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, elem);
        mTimer20 = 1;
    }
    freeQuery(templates.mpBegin);
    constraints.destroy();
}

// @ 0x00dfdfe0
UI2::UI2(const UI2& s)
{
    char* d = (char*)this;
    char* src = (char*)&s;

    for (int i = 0; i < 10; ++i)
        ((unsigned*)d)[i] = ((const unsigned*)src)[i];

    *(void**)(d + 0x28) = d + 0x40;
    *(void**)(d + 0x2c) = d + 0x40;
    *(void**)(d + 0x30) = d + 0x40 + 0x1a0;
    *(unsigned*)(d + 0x3c) = 0;
    Vec34_assign_dfcee0(d + 0x28, 0, src + 0x28);

    for (int i = 0; i < 10; ++i)
        ((unsigned*)d)[0x78 + i] = ((const unsigned*)src)[0x78 + i];
    d[0x208] = src[0x208];
    d[0x209] = src[0x209];

    unsigned nbytes = *(unsigned*)(src + 0x210) - *(unsigned*)(src + 0x20c);
    PtrVecBase_4aa350(d + 0x20c, 0, nbytes >> 2, src + 0x218);
    unsigned* dst = *(unsigned**)(d + 0x20c);
    memcpy(dst, *(const void**)(src + 0x20c), nbytes);
    *(unsigned**)(d + 0x210) = (unsigned*)((char*)dst + (nbytes >> 2) * 4);

    *(unsigned*)(d + 0x220) = *(unsigned*)(src + 0x220);
    *(unsigned*)(d + 0x224) = *(unsigned*)(src + 0x224);
    *(unsigned*)(d + 0x228) = *(unsigned*)(src + 0x228);
    *(unsigned*)(d + 0x22c) = *(unsigned*)(src + 0x22c);
    *(unsigned*)(d + 0x230) = *(unsigned*)(src + 0x230);
}

// @ 0x00dfe220
void SP::cSPUIMissions::UpdateMissionFieldsSpace()
{
    FUN_00df97e0_GGUI();

    mIndex = 0;
    mCount = 0;
    mCur = 0;
    m7f = 0;

    char* item = (char*)mItem;
    FUN_00df9c80_GGUI(*(unsigned*)item);
    mTimer20 = *(unsigned*)(item + 0x20);
    m7c = 1;

    mName.Assign((const unsigned short*)0x13ec468, (const unsigned short*)0x13ec468);

    m8c.type = 0;
    m8c.a1 = 0;
    m8c.a2 = 0;
    m8c.a3 = 0;
    m8c.a4 = 0;
    m8c.a5 = 0;
    mA4 = 0;
    mA8 = 0;
    mAC = 0;
    *(unsigned*)&mB0[0] = 0;
    *(unsigned*)&mB0[4] = 0;
    *(unsigned*)&mB0[8] = 0;

    unsigned table[8] = { 0x7ca16b4, 0, 0x7bfce80, 1, 0x7ca3288, 0, 0x7ca46c1, 0 };

    char* lay = mLayout;
    for (int i = 0; i < 3; ++i) {
        Slot& sl = mSlots[i];
        sl.x = 0;
        sl.y = 0;
        sl.z = 0;
        sl.state = 0;

        void* win = ((Lay*)lay)->FindWindowByID((int)g_147ebe0[i], 1);
        if (win != 0) {
            void* box = ((void*(__thiscall*)(void*, unsigned))(*(void***)win)[0xc / 4])
                          (win, 0x8ed27e7a);
            if (box != 0) {
                ((void(__thiscall*)(void*, int, int))(*(void***)box)[0x28 / 4])(box, 4, 0);
                void* panel = ((void*(__thiscall*)(void*))(*(void***)box)[0x10 / 4])(box);
                ((void(__thiscall*)(void*, int, int))(*(void***)panel)[0x7c / 4])(panel, 0x10, 1);
            }
        }
        win = ((Lay*)lay)->FindWindowByID((int)g_147ebec[i], 1);
        if (win != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)win)[0x7c / 4])(win, 2, 1);
    }

    for (int i = 0; i < 8; i += 2) {
        void* win = ((Lay*)lay)->FindWindowByID((int)table[i], 1);
        ((void(__thiscall*)(void*, int, int))(*(void***)win)[0x7c / 4])
            (win, 1, table[i + 1] != 0);
    }

    void* win = ((Lay*)lay)->FindWindowByID(0x7ccdc3b, 1);
    if (win != 0)
        ((void(__thiscall*)(void*, unsigned))(*(void***)win)[0x80 / 4])(win, 0x13ec468);

    win = ((Lay*)lay)->FindWindowByID(0x7e0bb68, 1);
    if (win != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)win)[0x7c / 4])(win, 1, 0);

    FUN_00df9b30_GGUI(0);
    m7e = 1;

    void* app = AppSystem_67dd00();
    char active = ((char(__thiscall*)(void*))(*(void***)app)[0x54 / 4])(app);
    if (active == 0 && *(unsigned*)((char*)g_16a1344 + 0x1f8) == 0) {
        unsigned qmf[3];
        QueryMissionFields(qmf);
        if (qmf[0] != 0) {
            ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, qmf);
            FUN_00df9ef0_GGUI();
        }
    }
}