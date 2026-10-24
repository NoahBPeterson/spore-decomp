// Slice s00d15440 (worker 9) -- the game-edit input strategy block at 0x00D15440.
//   SP::cGameEditInputStrategy::FUN_00d15440 (target direction/quaternion snapshot),
//   ::FUN_00d15550 (Deactivate), ::FUN_00d15600, ::FUN_00d15630
//   (AddGameplayMarkerLabel), ::FUN_00d15780 (build combo box),
//   ::FUN_00d15980, ::FUN_00d15a10, ::StartSelection, ::FUN_00d15af0,
//   SP::`anonymous namespace'::GetGameplayMarkerClassId, FUN_00d15c00
//   (marker placement update) and ::GetGameplayMarkerTypeFromUI.
//
// Only StartSelection, GetGameplayMarkerClassId and GetGameplayMarkerTypeFromUI
// carry real PDB names; the others are FUN_ / caller-scored candidates.  These
// routines are members of SP::cGameEditInputStrategy (this in ecx) except the two
// plain __cdecl helpers (GetGameplayMarkerClassId, FUN_00d15c00).  Engine entry
// points are modelled as named collaborators; vftable dispatch goes through the
// VTSLOT macro (slot dispatch is the accepted convention here).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;

struct Vec3 { float x, y, z; };
struct Obj;

#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pi)(void*, int);
typedef void  (__thiscall *Fn_v_pii)(void*, int, int);
typedef void  (__thiscall *Fn_v_piii)(void*, int, int, int);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_ppi)(void*, int, void*);
typedef void  (__thiscall *Fn_v_ppb)(void*, bool, void*);
typedef void  (__thiscall *Fn_v_ppf)(void*, void*, float);
typedef void  (__thiscall *Fn_v_pff)(void*, float, float);
typedef void  (__thiscall *Fn_v_pppp)(void*, void*, void*, void*);
typedef Obj* (__thiscall *Fn_p_p)(void*);
typedef Obj* (__thiscall *Fn_p_pi)(void*, int);
typedef Obj* (__thiscall *Fn_p_pp)(void*, void*);
typedef bool  (__thiscall *Fn_b_p)(void*);
typedef bool  (__thiscall *Fn_b_pui)(void*, u32, void**);

// ---- engine data globals ----------------------------------------------------
extern "C" u8    DAT_01186577 = 0;                 // 0x01186577  object key
extern "C" float DAT_0169dc28 = 0.0f;              // 0x0169dc28  selection anchor (x)
extern "C" float DAT_0169dc2c = 0.0f;              // 0x0169dc2c  selection anchor (y)
extern "C" float DAT_0169dc30 = 0.0f;              // 0x0169dc30  selection anchor (z)
extern "C" void* DAT_0169dc64 = 0;                 // 0x0169dc64  current marker owner
extern "C" int*  DAT_0169dc68 = 0;                 // 0x0169dc68  marker entry vector begin
extern "C" int*  DAT_0169dc6c = 0;                 // 0x0169dc6c  marker entry vector end
extern "C" float DAT_013f4fd0 = 4294967296.0f;     // 0x013f4fd0  2^32 (negative-int fixup)
extern "C" float DAT_013ec4b8 = 1e-08f;            // 0x013ec4b8  normalisation epsilon
extern "C" float DAT_013eb1bc = -1.0f;             // 0x013eb1bc  negative spin direction
extern "C" float DAT_013ec478 = 0.05f;             // 0x013ec478  spin step (radians)
extern "C" float DAT_01485720 = 1.0f;              // 0x01485720  HK_REAL_ONE
extern "C" float DAT_01470f1c = 2.0f;              // 0x01470f1c  squared-scale constant
extern "C" float DAT_014763b8 = 0.0f;              // 0x014763b8  label area (w)
extern "C" float DAT_013ebc4c = 0.0f;              // 0x013ebc4c  label area (h)
extern "C" float DAT_013f08e8 = 160.0f;            // 0x013f08e8  label x advance
extern "C" float DAT_01486ebc = 250.0f;            // 0x01486ebc  combo box width
extern "C" float DAT_013eecd8 = 20.0f;             // 0x013eecd8  combo box height
extern "C" float DAT_01479c0c = 270.0f;            // 0x01479c0c  combo box y advance
extern "C" wchar_t DAT_01479b30[] = L"LevelEditor";// 0x01479b30  tuning set name
extern "C" char DAT_01479c38[] = "UI/ComboBoxDrawable";    // 0x01479c38
extern "C" char DAT_01479c20[] = "UI/ScrollbarDrawable";   // 0x01479c20
extern "C" char DAT_01479c10[] = "UI/WinComboBox";         // 0x01479c10

// ---- collaborator objects ---------------------------------------------------
// Obj stands in for every engine object whose class is not declared here; each
// member is named after its retail entry point.
struct Obj {
    void* m_slot30();                       // vftable slot 0x30
    Vec3* m_position();                     // vftable slot 0x2c
};

// The layout block embedded at cGameEditInputStrategy+0xe0.
struct cSPUILayout {
    u8    mPad00[0x24];
    Obj*  FindWindowByID(int id, int flag); // 0x008105b0
    void  SetVisibility(int v);             // 0x00810590
};

struct cGameNounManager {
    void RemoveNoun(Obj* p);                // 0x00b225d0
};

// ---- engine entry points ----------------------------------------------------
Obj*  __cdecl SP_PlanetModel();                       // 0x00b3d350
Obj*  __cdecl SP_PropertyManager();                   // 0x0067de30
Obj*  __cdecl SP_GetGameTerrainCursor();              // 0x00b30d70
cGameNounManager* __cdecl SP_NounManager(void* pNoun); // 0x00b3d300
void* __cdecl FUN_00d1bf00();                         // 0x00d1bf00  GetEditSelection
u32   __cdecl EA_Hash_FNV1_String16(const wchar_t* p, u32 seed, int flag); // 0x00932f30
void  __cdecl EA_Messaging_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
void  __cdecl FUN_00ba1280();                         // 0x00ba1280
void* __cdecl FUN_009512c0();                         // 0x009512c0
void* __cdecl FUN_009512d0(int size, int align, const char* name, void* pPool); // 0x009512d0
Obj*  __cdecl WinText_CreateDefault(int a, u32 b);    // 0x00989130  WinText::CreateDefault
Obj*  __cdecl ComboBoxDrawable_ctor(Obj* pThis);      // 0x00969000  UI::ComboBoxDrawable::c
Obj*  __cdecl ScrollbarDrawable_ctor(Obj* pThis);     // 0x009838a0  UI::ScrollbarDrawable::c
Obj*  __cdecl WinComboBox_ctor(Obj* pThis);           // 0x00969450  WinComboBox::c
// 0x00b815a0 SP::cPlanetModel::DirectionToSurfacePosition
extern "C" void* SP_cPlanetModel_DirectionToSurfacePosition(void* pModel, void* pOut, void* pDir);
// 0x00b7f190 SP::cPlanetModel::BuildSurfaceOrientation
extern "C" void* SP_cPlanetModel_BuildSurfaceOrientation(void* pModel, void* pOut, void* pPos);

namespace SP {

// The edit-mode input strategy.  Field offsets recovered from this slice.
struct cGameEditInputStrategy {
    u8    mPad00[0x40];
    u8    mSub40[0x0c];              // +0x040  sub-object handed to window slot 0x108
    void* mpField4C;                 // +0x04c
    u8    mPad50[0x54 - 0x50];
    void* mpNoun;                    // +0x054  noun (vftable slot 0x58 query)
    u8    mPad58[0x88 - 0x58];
    void* mpField88;                 // +0x088  slot 0x1c0 target
    u8    mPad8c[0xa4 - 0x8c];
    void* mpFieldA4;                 // +0x0a4
    void* mpFieldA8;                 // +0x0a8  slot 0xd8 marker-list owner
    u8    mPadAc[0xc4 - 0xac];
    Vec3  mVecC4;                    // +0x0c4
    float mQuatD0[4];                // +0x0d0
    cSPUILayout mLayout;             // +0x0e0
    void* mpHandler;                 // +0x104
    void* mHandlerArgs[6];           // +0x108

    void  FUN_00d15440(Vec3* pTarget);
    void  FUN_00d15550();
    void  FUN_00d15600();
    void  FUN_00d15630(void* a1, float* pX, float* pY);
    float FUN_00d15780(void* a1, float* pX, float* pY);
    void  FUN_00d15980(void* a1, void* pObj);
    void  FUN_00d15a10(void* p);
    u32   StartSelection(void* p, u8 flag, u32 a3);
    u32   FUN_00d15af0(void* p, u8 flag, u32 a3);
    u32   GetGameplayMarkerTypeFromUI();
};

// The selection object returned by FUN_00d1bf00: a vector of noun refs at
// +0x40 (begin) / +0x44 (end).
struct cEditSelection {
    u8    mPad00[0x40];
    void** mBegin;                   // +0x040
    void** mEnd;                     // +0x044
};

}  // namespace SP

// 0x00d15b30  SP::`anonymous namespace'::GetGameplayMarkerClassId.
u32 __cdecl GetGameplayMarkerClassId(u32 classId);

// ============================================================================
// @ 0x00d15440 SP::cGameEditInputStrategy::FUN_00d15440
// Snapshot of the normalised direction to pTarget plus the noun's orientation.
// ============================================================================
void SP::cGameEditInputStrategy::FUN_00d15440(Vec3* pTarget)
{
    void* o = ((Fn_p_p)VTSLOT(mpNoun, 0x58))(mpNoun);
    if (o == 0)
        return;

    void* o2 = ((Fn_p_p)VTSLOT(mpNoun, 0x58))(mpNoun);
    Vec3* p = ((Obj*)o2)->m_position();
    float dx = pTarget->x - p->x;
    float dy = pTarget->y - p->y;
    float dz = pTarget->z - p->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    mVecC4.x = inv * dx;
    mVecC4.y = inv * dy;
    mVecC4.z = inv * dz;

    void* o3 = ((Fn_p_p)VTSLOT(mpNoun, 0x58))(mpNoun);
    float* q = (float*)((Obj*)o3)->m_slot30();
    mQuatD0[0] = q[0];
    mQuatD0[1] = q[1];
    mQuatD0[2] = q[2];
    mQuatD0[3] = q[3];
}

// ============================================================================
// @ 0x00d15550 SP::cGameEditInputStrategy::FUN_00d15550   (candidate: Deactivate)
// ============================================================================
void SP::cGameEditInputStrategy::FUN_00d15550()
{
    Obj* w = mLayout.FindWindowByID(0x30170d2c, 1);
    if (w != 0) {
        ((Fn_v_p)VTSLOT(w, 0))(w);
        void* pSub = (this != 0) ? (void*)&mSub40 : (void*)0;
        ((Fn_v_pp)VTSLOT(w, 0x108))(w, pSub);
    }

    if (mpNoun != 0) {
        cGameNounManager* m = SP_NounManager(mpNoun);
        m->RemoveNoun((Obj*)mpNoun);
        mpNoun = 0;
    }

    mLayout.SetVisibility(0);

    if (mpHandler != 0) {
        void* h = mpHandler;
        mpHandler = 0;
        EA_Messaging_RemoveHandler(h, mHandlerArgs[0], mHandlerArgs[1],
                                   mHandlerArgs[2], mHandlerArgs[3]);
    }

    if (w != 0)
        ((Fn_v_p)VTSLOT(w, 4))(w);
}

// ============================================================================
// @ 0x00d15600 SP::cGameEditInputStrategy::FUN_00d15600
// ============================================================================
void SP::cGameEditInputStrategy::FUN_00d15600()
{
    ((Fn_v_pii)VTSLOT(mpFieldA4, 0x7c))(mpFieldA4, 1, 0);
    ((Fn_v_p)VTSLOT(mpFieldA8, 0xe4))(mpFieldA8);
}

// ============================================================================
// @ 0x00d15630 SP::cGameEditInputStrategy::FUN_00d15630
// (candidate: AddGameplayMarkerLabel) -- builds the floating marker label.
// ============================================================================
void SP::cGameEditInputStrategy::FUN_00d15630(void* a1, float* pX, float* pY)
{
    Obj* label = WinText_CreateDefault(-1, 0xacbf4564);
    if (label != 0)
        ((Fn_v_p)VTSLOT(label, 0))(label);

    float area[4];
    area[0] = 0.0f;
    area[1] = 0.0f;
    area[2] = DAT_014763b8;
    area[3] = DAT_013ebc4c;

    Obj* c;
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0x84))(c, 1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pp)VTSLOT(c, 0x60))(c, area);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0xac))(c, (int)0xffbac1b3);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0x5c))(c, -1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0x80))(c, (int)a1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_p)VTSLOT(c, 0x90))(c);
    ((Fn_v_pi)VTSLOT(label, 0x14))(label, 1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pff)VTSLOT(c, 0x64))(c, *pX, *pY);

    *pX += DAT_013f08e8;

    void* owner = mpFieldA8;
    Obj* t = ((Fn_p_p)VTSLOT(label, 0x10))(label);
    ((Fn_v_pp)VTSLOT(owner, 0xd8))(owner, t);

    ((Fn_v_p)VTSLOT(label, 4))(label);
}

// ============================================================================
// @ 0x00d15780 SP::cGameEditInputStrategy::FUN_00d15780
// Builds the marker combo box (a WinComboBox with a combo-box drawable and a
// scrollbar drawable) and attaches it to the marker-list owner; returns the
// label row's bottom edge.
// ============================================================================
float SP::cGameEditInputStrategy::FUN_00d15780(void* a1, float* pX, float* pY)
{
    Obj* comboDrawable = 0;
    Obj* scrollbar = 0;
    Obj* combo = 0;

    // Each drawable is allocated through the factory (pool, alignment, class name,
    // pool handle) and then placement-constructed; a +0xc / +0x20c offset yields the
    // window sub-object, which is add-ref'd immediately.
    {
        Obj* p = (Obj*)FUN_009512d0(0x1c, 4, "UI/ComboBoxDrawable", FUN_009512c0());
        if (p != 0) {
            p = ComboBoxDrawable_ctor(p);
            if (p != 0) {
                comboDrawable = (Obj*)((char*)p + 0xc);
                if (comboDrawable != 0)
                    ((Fn_v_p)VTSLOT(comboDrawable, 0))(comboDrawable);
            }
        }
    }
    {
        Obj* p = (Obj*)FUN_009512d0(0x2c, 4, "UI/ScrollbarDrawable", FUN_009512c0());
        if (p != 0) {
            p = ScrollbarDrawable_ctor(p);
            if (p != 0) {
                scrollbar = (Obj*)((char*)p + 0xc);
                if (scrollbar != 0)
                    ((Fn_v_p)VTSLOT(scrollbar, 0))(scrollbar);
            }
        }
    }
    {
        Obj* p = (Obj*)FUN_009512d0(0x2b8, 4, "UI/WinComboBox", FUN_009512c0());
        if (p != 0) {
            p = WinComboBox_ctor(p);
            if (p != 0) {
                combo = (Obj*)((char*)p + 0x20c);
                if (combo != 0)
                    ((Fn_v_p)VTSLOT(combo, 0))(combo);
            }
        }
    }

    ((Fn_v_pp)VTSLOT(combo, 0x68))(combo, comboDrawable);
    ((Fn_v_pp)VTSLOT(combo, 0x60))(combo, scrollbar);
    ((Fn_v_pi)VTSLOT(combo, 0x18))(combo, 1);
    ((Fn_v_pi)VTSLOT(combo, 0x50))(combo, 0xf);

    Obj* c;
    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pp)VTSLOT(c, 0x54))(c, a1);
    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pp)VTSLOT(c, 0x50))(c, a1);
    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pii)VTSLOT(c, 0x7c))(c, 1, 1);

    float rect[4];
    rect[0] = *pX;
    rect[1] = *pY;
    rect[2] = *pX + DAT_01486ebc;
    rect[3] = *pY + DAT_013eecd8;

    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pp)VTSLOT(c, 0x60))(c, rect);

    *pX += DAT_01479c0c;

    Obj* t = ((Fn_p_p)VTSLOT(combo, 0x10))(combo);
    ((Fn_v_pp)VTSLOT(mpFieldA8, 0xd8))(mpFieldA8, t);

    ((Fn_v_p)VTSLOT(combo, 4))(combo);
    if (scrollbar != 0)
        ((Fn_v_p)VTSLOT(scrollbar, 4))(scrollbar);
    if (comboDrawable != 0)
        ((Fn_v_p)VTSLOT(comboDrawable, 4))(comboDrawable);

    return rect[1];
}

// ============================================================================
// @ 0x00d15980 SP::cGameEditInputStrategy::FUN_00d15980
// Removes the object selected through pObj from the noun manager.
// ============================================================================
void SP::cGameEditInputStrategy::FUN_00d15980(void* a1, void* pObj)
{
    (void)a1;

    Obj* o1 = (Obj*)((Fn_p_p)VTSLOT(pObj, 0x10))(pObj);
    Obj* o2 = (Obj*)((Fn_p_pi)VTSLOT(o1, 0x1c))(o1, 0);

    Obj* p;
    if ((*(u32*)((char*)o2 + 0x10) & 0x30) != 0)
        p = *(Obj**)o2;
    else if (*(u16*)((char*)o2 + 0x12) == 0)
        return;
    else
        p = o2;

    if (p == 0)
        return;

    Obj* q = (Obj*)((Fn_p_pi)VTSLOT(p, 0xc))(p, 0x17f243b);
    if (q != 0) {
        void* id = ((Fn_p_pi)VTSLOT(q, 0xc))(q, (int)0x01186577);
        if (id == mpField4C) {
            Obj* f = (Obj*)mpField4C;
            if (f != 0) {
                mpField4C = 0;
                ((Fn_v_p)VTSLOT(f, 0xc0))(f);
            }
        }
        SP_NounManager(q)->RemoveNoun(q);
        FUN_00ba1280();
    }
}

// ============================================================================
// @ 0x00d15a10 SP::cGameEditInputStrategy::FUN_00d15a10
// ============================================================================
void SP::cGameEditInputStrategy::FUN_00d15a10(void* p)
{
    void* g = DAT_0169dc64;
    if (g != 0) {
        Obj* q = (Obj*)((Fn_p_pi)VTSLOT(g, 0xc))(g, (int)0x01186577);
        if (q != 0)
            ((Fn_v_pp)VTSLOT(q, 0x94))(q, p);
    }

    int* it = DAT_0169dc68;
    int i = 0;
    if (it != DAT_0169dc6c) {
        do {
            ((Fn_v_piii)VTSLOT(mpField88, 0x1c0))(mpField88, 0, i, 0);
            it += 3;
            ++i;
        } while (it != DAT_0169dc6c);
    }

    void* g2 = DAT_0169dc64;
    if (g2 != 0) {
        DAT_0169dc64 = 0;
        ((Fn_v_p)VTSLOT(g2, 4))(g2);
    }
}

// ============================================================================
// @ 0x00d15ab0 SP::cGameEditInputStrategy::StartSelection
// ============================================================================
u32 SP::cGameEditInputStrategy::StartSelection(void* p, u8 flag, u32 a3)
{
    (void)a3;
    Obj* cursor = SP_GetGameTerrainCursor();
    void* key;
    if (p != 0)
        key = (void*)((Fn_p_pi)VTSLOT(p, 0xc))(p, (int)0x01186577);
    else
        key = (void*)0;
    ((Fn_v_ppb)VTSLOT(cursor, 0x9c))(cursor, flag & 1, key);
    return 0;
}

// ============================================================================
// @ 0x00d15af0 SP::cGameEditInputStrategy::FUN_00d15af0
// ============================================================================
u32 SP::cGameEditInputStrategy::FUN_00d15af0(void* p, u8 flag, u32 a3)
{
    (void)a3;
    Obj* cursor = SP_GetGameTerrainCursor();
    void* key;
    if (p != 0)
        key = (void*)((Fn_p_pi)VTSLOT(p, 0xc))(p, (int)0x01186577);
    else
        key = (void*)0;
    ((Fn_v_ppb)VTSLOT(cursor, 0xa0))(cursor, flag & 1, key);
    return 0;
}

// ============================================================================
// @ 0x00d15b30 GetGameplayMarkerClassId
// SP::`anonymous namespace'::GetGameplayMarkerClassId -- looks up classId in the
// class-id pair table stored under the "LevelEditor" tuning key and returns the
// matching value (0 when absent).
// ============================================================================
u32 __cdecl GetGameplayMarkerClassId(u32 classId)
{
    void* prop = 0;
    Obj* pm = SP_PropertyManager();
    (void)pm;

    u32 h = EA_Hash_FNV1_String16(DAT_01479b30, 0x811c9dc5, 1);

    if (((Fn_b_pui)VTSLOT(pm, 0x30))(pm, h, &prop)) {
        Obj* table = (Obj*)((Fn_p_pi)VTSLOT(prop, 0x28))(prop, 0x69623444);

        void* base;
        u32 count;
        if ((*(u32*)((char*)table + 0x10) & 0x30) != 0) {
            base = *(void**)table;
            count = *(u32*)((char*)table + 0x08);
        } else {
            count = (u32)(*(u16*)((char*)table + 0x12) != 0);
            base = (*(u16*)((char*)table + 0x12) != 0) ? (void*)table : (void*)0;
        }

        for (u32 i = 0; i < count; i += 2) {
            void* key = *(void**)((char*)base + i * 4);
            u32 val = *(u32*)((char*)base + i * 4 + 4);
            if ((void*)classId == key) {
                if (prop != 0)
                    ((Fn_v_p)VTSLOT(prop, 4))(prop);
                return val;
            }
        }
    }

    if (prop != 0)
        ((Fn_v_p)VTSLOT(prop, 4))(prop);
    return 0;
}

// ============================================================================
// @ 0x00d15c00 FUN_00d15c00  (__cdecl) -- marker placement update
// Averages the position of every selected marker, builds the spin orientation
// and re-seats every marker on the planet surface.
// ============================================================================
extern "C" void __cdecl FUN_00d15c00(char bForward)
{
    Vec3 avg;
    avg.x = DAT_0169dc28;
    avg.y = DAT_0169dc2c;
    avg.z = DAT_0169dc30;
    int count = 0;

    void* selRaw = FUN_00d1bf00();
    void** begin = *(void***)((char*)selRaw + 0x40);
    void** end = *(void***)((char*)selRaw + 0x44);

    for (void** it = begin; it != end; ++it) {
        if (*it != 0) {
            Obj* m = (Obj*)((Fn_p_pi)VTSLOT(*it, 0xb8))(*it, 0x36be278);
            if (m != 0) {
                Obj* sub = (Obj*)((char*)m + 0x34);
                if (((Fn_b_p)VTSLOT(sub, 0x50))(sub)) {
                    Vec3* p = sub->m_position();
                    avg.x += p->x;
                    avg.y += p->y;
                    avg.z += p->z;
                    ++count;
                }
            }
        }
    }

    float inv = 1.0f / (float)count;
    float spin = bForward ? 1.0f : -1.0f;
    float s = sinf(spin * DAT_013ec478);
    float c = cosf(spin * DAT_013ec478);

    Vec3 dir;
    dir.x = inv * avg.x;
    dir.y = inv * avg.y;
    dir.z = inv * avg.z;

    float n = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + DAT_013ec4b8);
    float qx = n * dir.x;
    float qy = n * dir.y;
    float qz = n * dir.z;

    // rotation components (the original synthesises a quaternion from the spin)
    float r0 = c;
    float r1 = s * qx;
    float r2 = s * qy;
    float r3 = s * qz;

    for (void** it = begin; it != end; ++it) {
        if (*it != 0) {
            Obj* m = (Obj*)((Fn_p_pi)VTSLOT(*it, 0xb8))(*it, 0x36be278);
            if (m != 0) {
                Obj* sub = (Obj*)((char*)m + 0x34);
                if (((Fn_b_p)VTSLOT(sub, 0x50))(sub)) {
                    Vec3* p = sub->m_position();
                    Vec3 out;
                    out.x = (1.0f - (r2 * r2 + r3 * r3) * DAT_01470f1c) * p->x
                          + (r1 * r2 - r0 * r3) * DAT_01470f1c * p->y
                          + (r0 * r2 + r1 * r3) * DAT_01470f1c * p->z;
                    out.y = (r1 * r2 + r0 * r3) * DAT_01470f1c * p->x
                          + (1.0f - (r1 * r1 + r3 * r3) * DAT_01470f1c) * p->y
                          + (r2 * r3 - r0 * r1) * DAT_01470f1c * p->z;
                    out.z = (r1 * r3 - r0 * r2) * DAT_01470f1c * p->x
                          + (r2 * r3 + r0 * r1) * DAT_01470f1c * p->y
                          + (1.0f - (r1 * r1 + r2 * r2) * DAT_01470f1c) * p->z;

                    void* surf = SP_cPlanetModel_DirectionToSurfacePosition(
                        SP_PlanetModel(), &out, &avg);
                    ((Fn_v_pp)VTSLOT(sub, 0x38))(sub, surf);

                    void* orient = SP_cPlanetModel_BuildSurfaceOrientation(
                        SP_PlanetModel(), &avg, sub->m_position());
                    ((Fn_v_pp)VTSLOT(sub, 0x3c))(sub, orient);
                }
            }
        }
    }
}

// ============================================================================
// @ 0x00d15fb0 SP::cGameEditInputStrategy::GetGameplayMarkerTypeFromUI
// Returns the marker type selected in the edit-mode combo box.
// ============================================================================
u32 SP::cGameEditInputStrategy::GetGameplayMarkerTypeFromUI()
{
    void* prop = 0;
    Obj* pm = SP_PropertyManager();
    (void)pm;

    u32 h = EA_Hash_FNV1_String16(DAT_01479b30, 0x811c9dc5, 1);

    if (((Fn_b_pui)VTSLOT(pm, 0x30))(pm, h, &prop)) {
        Obj* win = mLayout.FindWindowByID((int)0xabc0fff8, 1);
        if (win != 0) {
            Obj* combo = (Obj*)((Fn_p_pi)VTSLOT(win, 0xc))(win, 0x2f5528d9);
            if (combo != 0) {
                ((Fn_v_p)VTSLOT(combo, 0))(combo);

                Obj* table = (Obj*)((Fn_p_pi)VTSLOT(prop, 0x28))(prop, 0x185a7a14);
                u32 idx = (u32)((Fn_p_p)VTSLOT(combo, 0x40))(combo);

                void* base;
                if ((*(u32*)((char*)table + 0x10) & 0x30) != 0)
                    base = *(void**)table;
                else
                    base = (*(u16*)((char*)table + 0x12) != 0) ? (void*)table : (void*)0;

                const wchar_t* label = *(const wchar_t**)((char*)base + idx * 16);
                u32 h2 = EA_Hash_FNV1_String16(label, 0x811c9dc5, 1);

                ((Fn_v_p)VTSLOT(combo, 4))(combo);
                if (prop != 0)
                    ((Fn_v_p)VTSLOT(prop, 4))(prop);
                return h2;
            }
        }
    }

    if (prop != 0)
        ((Fn_v_p)VTSLOT(prop, 4))(prop);
    return 0;
}