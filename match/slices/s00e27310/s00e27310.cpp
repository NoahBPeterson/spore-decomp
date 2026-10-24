// s00e27310 -- SP::cSPUIPosseItem / cSPUIPosse and derived posee items.

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef signed int         i32;

#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))

static inline void AddRefI(void* p)  { ((void (__thiscall*)(void*))VT(p)[0])(p); }
static inline void ReleaseI(void* p) { ((void (__thiscall*)(void*))VT(p)[1])(p); }

// ---------------------------------------------------------------------------
// plain (non-ecx) callees
// ---------------------------------------------------------------------------
void* __cdecl FUN_00f473a0(u32 size, void* file, int a, int b, int c, int d); // 0x00f473a0
void* __cdecl FUN_00b5b800();                              // 0x00b5b800
void* __cdecl FUN_0067dcc0();                              // 0x0067dcc0
float __cdecl FUN_00805080();                              // 0x00805080
void* __cdecl FUN_007f81d0(void* out, void* win, float scale, float t, float k, int z); // 0x007f81d0
void* __cdecl FUN_00cd40b0();                              // 0x00cd40b0
void  __cdecl FUN_00435ed0(u32 a, void* b);                // 0x00435ed0
void* __cdecl FUN_00a206f0();                              // 0x00a206f0
void* __cdecl FUN_00e24290(void* a, void* b, void* c);     // 0x00e24290
void  __cdecl FUN_00e26de0(void* a, void* b, void* fn);    // 0x00e26de0
u8    __stdcall FUN_00950ef0(u32 a, void* b);              // 0x00950ef0
void  __cdecl FUN_00e22760();                              // 0x00e22760

// ---------------------------------------------------------------------------
// callees invoked with ecx == an arbitrary object
// ---------------------------------------------------------------------------
struct COps
{
    void FUN_00e26680();                     // 0x00e26680
    void FUN_00cca0a0();                     // 0x00cca0a0
    u8   FUN_00cca090();                     // 0x00cca090
    u8   FUN_00e27be0(u32 a, void* obj);     // 0x00e27be0
};

// ---------------------------------------------------------------------------
// supporting types
// ---------------------------------------------------------------------------
class cSPUILayout
{
public:
    bool  Init(const void* key, bool a, u32 b);       // 0x008120d0
    void* FindWindowByID(u32 id, bool recurse);       // 0x008105b0
    u8    pad[0x18];
};

struct cRefPair
{
    void* mpFirst;                                     // +0x00
    void* mpSecond;                                    // +0x04
};

struct cBarList
{
    cRefPair* mpBegin;                                 // +0x00
    cRefPair* mpEnd;                                   // +0x04
    void* FUN_00e23870(void* a, void* b);              // 0x00e23870
    void  FUN_00e25bd0(void* a, void* b);              // 0x00e25bd0
};

struct cRefList
{
    void* mpBegin;                                     // +0x00
    void* mpEnd;                                       // +0x04
    void  FUN_00e25bd0(void* a, void* b);              // 0x00e25bd0
};

struct cWindowVec
{
    void* mpBegin;                                     // +0x00
    void* mpEnd;                                       // +0x04
    void  FUN_00e25c30(void* pos, u32 n, void* value); // 0x00e25c30
    void  FUN_00e25bd0(void* a, void* b);              // 0x00e25bd0
};

struct cWindowArray
{
    void** mpData;                                     // +0x00
    void   FUN_00e26ba0(int n);                        // 0x00e26ba0
};

struct cWString
{
    u8 pad[0x10];
    void assign(const u16* first, const u16* last);    // 0x00423650
};

struct cVec8;

// ---------------------------------------------------------------------------
// SP::cSPUIPosseItem
// ---------------------------------------------------------------------------
class cSPUIPosse;

class cSPUIPosseItem
{
public:
    u8          pad00[0x0c];                 // +0x00
    cRefList    mRefs;                       // +0x0c
    u8          pad14[0x3c];                 // +0x14
    void*       mpField50;                   // +0x50
    u8          mKey[0x28];                  // +0x54
    cSPUILayout mLayout;                     // +0x7c
    i32         mState;                      // +0x94
    u8          pad98[0x04];                 // +0x98
    cSPUIPosse* mpPosse;                     // +0x9c
    u8          padA0;                       // +0xa0
    u8          mStateSwap;                  // +0xa1
    u8          padA2[0x02];                 // +0xa2
    cBarList    mBars;                       // +0xa4
    void*       mpFieldAC;                   // +0xac
    float       mBlinkerStart;               // +0xb0
    u8          padB4[0x20];                 // +0xb4
    cWindowArray mWindows;                   // +0xd4
    u8          padD8[0x28];                 // +0xd8
    cWindowVec  mColorWindows;               // +0x100
    u8          pad108[0x1c];                // +0x108
    u8*         mControlValuesBegin;         // +0x124
    u8*         mControlValuesEnd;           // +0x128
    u8          pad12c[0x10];                // +0x12c
    void*       mpStateRootWindow;           // +0x13c
    u8          pad140[0x0c];                // +0x140
    float       mControlValue01;             // +0x14c
    u8          pad150[0x84];                // +0x150
    u8          mFlag1d4;                    // +0x1d4
    u8          pad1d5[0x1b];                // +0x1d5
    u32         mField1f0;                   // +0x1f0
    u32         mField1f4;                   // +0x1f4
    cWString    mCaption;                    // +0x1f8

    u8   init(cSPUIPosse* posse);                                  // 0x00e277b0
    __declspec(noinline) void SetStateWithoutNotification(u32 state); // 0x00e27310
    void SetState_BlinkGuard(u32 state);                           // 0x00e27df0
    void SetState_SpaceGuard(u32 state);                           // 0x00e27f60
    void SetState_Skip24(u32 state);                               // 0x00e27fa0
    void SetState_Only1(u32 state);                                // 0x00e28010
    void SetState_Skip234(u32 state);                              // 0x00e28030
    void FUN_00e281a0(u8 flag);                                    // 0x00e281a0
    void FUN_00e28230();                                           // 0x00e28230
    u8   SetControlValue(u32 id, float value, u32 a, u32 b);       // 0x00e27230
    void update_control_value(u32 id);                             // 0x00e25fa0
    void motive_bars_and_background_reposition(u32 a);             // 0x00e21f30
    void motive_bars_and_background_collect_initial_metrics();     // 0x00e22270
    void FUN_00e27c30(u32 a, u32 b);                               // 0x00e27c30
};

// ---------------------------------------------------------------------------
// SP::cSPUIPosse
// ---------------------------------------------------------------------------
class cSPUIPosse
{
public:
    u8          pad00[0xa4];                 // +0x00
    void*       mpBarBegin;                  // +0xa4
    void*       mpBarEnd;                    // +0xa8
    u8          padAC[0x110];                // +0xac
    cSPUILayout mLayout;                     // +0x1bc
    u8          pad1d4[0x24];                // +0x1d4
    cWString    mCaption;                    // +0x1f8
    void*       mpAnimator;                  // +0x208

    void FUN_00e23de0();                     // 0x00e23de0
    void toggle_select_all();                // 0x00e23d50
    i32  FUN_00e23250();                     // 0x00e23250
    u8   OnCtrlActivated(void* ctrl, u32 a2, u32 id, u32 a4);  // 0x00e27b20
    void SetCaptionText(const u16* text);                      // 0x00e27c50
};

struct cSPUIAnimator
{
    void AddAnimation(void* target, void* win, u32 id);   // 0x007f8d10
};

// ---------------------------------------------------------------------------
// derived posee items
// ---------------------------------------------------------------------------
class cSPUIPosseItemTribeBaby : public cSPUIPosseItem
{
public:
    u8 init(cSPUIPosse* posse);                                        // 0x00e27c90
    u8 SetControlValue(u32 id, float value, u32 a, u32 b);             // 0x00e27d30
};

class cSPUIPosseItemTribe : public cSPUIPosseItem
{
public:
    u8 init(cSPUIPosse* posse);                                        // 0x00e27e20
};

class cSPUIPosseItemSpace : public cSPUIPosseItem
{
public:
    u8 init(cSPUIPosse* posse);                                        // 0x00e27ef0
};

class cSPUIPosseItemCreature : public cSPUIPosseItem
{
public:
    u8 init(cSPUIPosse* posse);                                        // 0x00e27fc0
};

class cSPUIPosseItemPlot : public cSPUIPosseItem
{
public:
    u8 init(cSPUIPosse* posse);                                        // 0x00e28050
};

struct cVec8
{
    cRefPair* mpBegin;                                 // +0x00
    cRefPair* mpEnd;                                   // +0x04
    cRefPair* mpCap;                                   // +0x08
    void* FUN_00e23870(void* a, void* b);              // 0x00e23870
    void  FUN_00e26e50(void* pos, u32 n, void* value); // 0x00e26e50
    void  FUN_00e26c80(void* pos, cRefPair* value);    // 0x00e26c80
    void  push_back(cRefPair* src);                    // 0x00e280e0
    void  resize(u32 n);                               // 0x00e28250
};

struct AnimOut
{
    u32  mValue0;      // +0x00
    u32  mValue1;      // +0x04
    u32  mValue2;      // +0x08
    void* mpRef;       // +0x0c
    u8   mRest[0x34];  // +0x10
};

// ===========================================================================
// 0x00e27310
// ===========================================================================
// @ 0x00e27310
void cSPUIPosseItem::SetStateWithoutNotification(u32 state)
{
    if (state == (u32)mState)
        return;

    if ((state == 3 || state == 4) && mStateSwap != 0)
    {
        if (state == 3)
            state = 1;
        else if (state == 4)
            state = 2;
    }

    mState = (i32)state;
    mpPosse->FUN_00e23de0();

    u8 flagC = 0;
    u8 flag8 = 0;
    u8 flag4 = 0;
    switch (state)
    {
    case 4:
        flagC = 1;
    case 2:
        flag4 = 1;
    case 1:
        flag8 = 1;
        break;
    case 3:
        flagC = 1;
        flag8 = 1;
        break;
    }

    void* coll = mWindows.mpData[4];
    u32 ids[3] = { 0x3d99162, 0x3d99184, 0 };
    for (u32* idp = ids; *idp != 0; ++idp)
    {
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, *idp, 1);
        if (w != 0)
        {
            ((void (__thiscall*)(void*, int, u32))VT(w)[0x7c / 4])(w, 1, flag8);
            void* w2 = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x56bd1b8, 1);
            if (w2 != 0)
                ((void (__thiscall*)(void*, int, u32))VT(w2)[0x7c / 4])(w2, 1, flagC);
        }
    }

    void* w3 = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x4f656e8, 1);
    if (w3 != 0)
        ((void (__thiscall*)(void*, int, u32))VT(w3)[0x7c / 4])(w3, 1, flag4);

    float scale = 1.0f;
    if (mpPosse != 0 && mState != 4 && mState != 3)
        scale = ((float (__thiscall*)(void*))VT(mpPosse)[0xc8 / 4])(mpPosse);

    AnimOut out;
    FUN_007f81d0(&out, mpStateRootWindow, scale, FUN_00805080(), *(float*)0x1480574, 0);
    ((cSPUIAnimator*)mpPosse->mpAnimator)->AddAnimation(&out, mpStateRootWindow, 0x4f7b5dd);

    if (((u8 (__thiscall*)(void*))VT(this)[0xb0 / 4])(this) != 0)
    {
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x4acfcaf, 1);
        if (w != 0)
        {
            u8 mine = ((u8 (__thiscall*)(void*))VT(this)[0xac / 4])(this);
            u8 theirs = ((u8 (__thiscall*)(void*))VT(w)[0x28 / 4])(w);
            if (mine != (theirs & 1))
            {
                ((void (__thiscall*)(void*, int, u8))VT(w)[0x7c / 4])(w, 1, mine);

                float scale2 = 1.0f;
                if (mpPosse != 0 && mState != 4 && mState != 3)
                    scale2 = ((float (__thiscall*)(void*))VT(mpPosse)[0xc8 / 4])(mpPosse);

                AnimOut out2;
                FUN_007f81d0(&out2, w, scale2, FUN_00805080() + 0.075f, *(float*)0x1480574, 0);
                ((cSPUIAnimator*)mpPosse->mpAnimator)->AddAnimation(&out2, w, 0x4f7c3d1);
                if (out2.mpRef != 0)
                    ReleaseI(out2.mpRef);
            }
        }
    }

    ((void (__thiscall*)(void*, int, void*))VT(this)[0x84 / 4])(this, 0, mBars.mpEnd);
    if (((u8 (__thiscall*)(void*))VT(this)[0xb4 / 4])(this) != 0)
        ((void (__thiscall*)(void*, int, void*))VT(this)[0x84 / 4])(this, 1, mpFieldAC);

    for (u8* p = mControlValuesBegin; p != mControlValuesEnd; p += 0x10)
        update_control_value(*(u32*)p);

    motive_bars_and_background_reposition((mState == 3 || mState == 4) ? 1u : 0u);

    cSPUIPosse* posse = mpPosse;
    if (FUN_00b5b800() == (void*)0x1654c02)
    {
        void* strat = FUN_00cd40b0();
        void* r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
        if (r != 0)
        {
            strat = FUN_00cd40b0();
            r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
            MOPS(r)->FUN_00cca0a0();
            goto cleanup;
        }
    }

    {
        void* w = posse->mLayout.FindWindowByID(0x3dae412, true);
        if (w == 0)
            goto cleanup;
        void* f = ((void* (__thiscall*)(void*, u32))VT(w)[0xc / 4])(w, 0x8ed27e7a);
        if (f == 0)
            goto cleanup;

        u8 c;
        if (FUN_00b5b800() == (void*)0x1654c02)
        {
            void* strat = FUN_00cd40b0();
            void* r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
            if (r == 0)
                goto check2;
            strat = FUN_00cd40b0();
            r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
            c = MOPS(r)->FUN_00cca090();
        }
        else
        {
            u32 n = (u32)((u8*)posse->mpBarEnd - (u8*)posse->mpBarBegin) >> 3;
            c = (posse->FUN_00e23250() == (i32)n) ? 1 : 0;
        }

        if (c == 0)
            goto check2;
        if ((((u8 (__thiscall*)(void*))VT(f)[0x20 / 4])(f) & 4) != 0)
            goto cleanup;
        ((void (__thiscall*)(void*, u32, u32))VT(f)[0x28 / 4])(f, 4, 1);
        MOPS(posse)->FUN_00e26680();
        goto cleanup;

    check2:
        if ((((u8 (__thiscall*)(void*))VT(f)[0x20 / 4])(f) & 4) == 0)
            goto cleanup;
        ((void (__thiscall*)(void*, u32, u32))VT(f)[0x28 / 4])(f, 4, 0);
        MOPS(posse)->FUN_00e26680();
    }

cleanup:
    if (out.mpRef != 0)
        ReleaseI(out.mpRef);
}

// ===========================================================================
// 0x00e277b0
// ===========================================================================
// @ 0x00e277b0
u8 cSPUIPosseItem::init(cSPUIPosse* posse)
{
    if (posse == 0)
        return 0;

    cSPUIPosse* old = mpPosse;
    if (posse != old)
    {
        AddRefI(posse);
        mpPosse = posse;
        if (old != 0)
            ReleaseI(old);
    }

    ((void (__thiscall*)(void*))VT(mpPosse)[0x8c / 4])(mpPosse);

    if (!mLayout.Init(&mKey, false, 0x5b598fa))
        return 0;

    mWindows.FUN_00e26ba0(5);

    for (int i = 1; i < 5; ++i)
    {
        void* w = mLayout.FindWindowByID((u32)(i + 0x3d98300), true);
        void* prev = mWindows.mpData[i];
        if (w != prev)
        {
            if (w != 0)
                AddRefI(w);
            mWindows.mpData[i] = w;
            if (prev != 0)
                ReleaseI(prev);
        }
        if (w != 0)
        {
            ((void (__thiscall*)(void*, float, float))VT(w)[0x70 / 4])(w, 0.0f, 0.0f);
            ((void (__thiscall*)(void*, int))VT(w)[0xac / 4])(w, 0);
            ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, (i == 4) ? 1 : 0);

            void* c = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x3d99141, 1);
            if (c != 0)
                ((void (__thiscall*)(void*, int))VT(c)[0xac / 4])(c, 0);
            c = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x3d99151, 1);
            if (c != 0)
                ((void (__thiscall*)(void*, int))VT(c)[0xac / 4])(c, 0);
            c = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x4acfcaf, 1);
            if (c != 0)
                ((void (__thiscall*)(void*, int, int))VT(c)[0x7c / 4])(c, 1, 0);
        }
    }

    void* p = mLayout.FindWindowByID(0x3d98299, true);
    void* prev = mpStateRootWindow;
    if (p != prev)
    {
        if (p != 0)
            AddRefI(p);
        mpStateRootWindow = p;
        if (prev != 0)
            ReleaseI(prev);
    }

    ((void (__thiscall*)(void*, int))VT(p)[0xac / 4])(p, 0);
    ((void (__thiscall*)(void*, void*))VT(p)[0x104 / 4])(p, this);

    u32 v = ((u32 (__thiscall*)(void*, u32))VT(this)[0xc / 4])(this, 0xee3f516e);
    ((void (__thiscall*)(void*, u32, u32))VT(p)[0xb8 / 4])(p, 0x3e43b66, v);

    if (FUN_0067dcc0() != 0)
    {
        void* server = FUN_0067dcc0();
        ((void (__thiscall*)(void*, void*, u32))VT(server)[0x20 / 4])(server, &mRefs, 0x3e41916);
    }

    u32* cwBegin = (u32*)mColorWindows.mpBegin;
    u32* cwEnd = (u32*)mColorWindows.mpEnd;
    u32 have = (u32)(cwEnd - cwBegin);
    if (have < 3)
    {
        u32 zero = 0;
        mColorWindows.FUN_00e25c30(cwEnd, 3 - have, &zero);
    }
    else
    {
        mColorWindows.FUN_00e25bd0(cwBegin + 3, cwEnd);
    }

    u32* slots = (u32*)mColorWindows.mpBegin;
    for (int i = 0; i < 3; ++i)
    {
        void* w = mLayout.FindWindowByID((u32)(i + 0x3df0885), true);
        void* prev = (void*)slots[i];
        if (w != prev)
        {
            if (w != 0)
                AddRefI(w);
            slots[i] = (u32)w;
            if (prev != 0)
                ReleaseI(prev);
        }
        ((void (__thiscall*)(void*, int, int))VT((void*)slots[i])[0x7c / 4])((void*)slots[i], 1, 0);
    }

    motive_bars_and_background_collect_initial_metrics();
    ((void (__thiscall*)(void*, int))VT(this)[0xb8 / 4])(this, 1);
    u8 more = ((u8 (__thiscall*)(void*))VT(this)[0xb4 / 4])(this);

    u32 ids[3] = { 0x3d99162, more ? 0x3d99184u : 0u, 0 };
    for (u32* idp = ids; *idp != 0; ++idp)
    {
        void* w = mLayout.FindWindowByID(*idp + 1, true);
        if (w != 0)
            ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, 0);
    }

    return 1;
}

// ===========================================================================
// 0x00e27b20
// ===========================================================================
// @ 0x00e27b20
u8 cSPUIPosse::OnCtrlActivated(void* ctrl, u32 a2, u32 id, u32 a4)
{
    u32 v = ((u32 (__thiscall*)(void*))VT(ctrl)[0x1c / 4])(ctrl);
    if (v != 0x3d98298)
        return 0;
    if (id != 0x3dae412)
        return 0;

    void* mode = FUN_00b5b800();
    if (mode != (void*)0x1654c02 && mode != (void*)0x1654c04)
    {
        toggle_select_all();
        MOPS(this)->FUN_00e26680();
        return 0;
    }

    void* obj = FUN_00f473a0(0x40, (void*)0x13f6b3c, 0, 0, 0, 0);
    if (obj != 0)
    {
        *(u32*)((char*)obj + 0x30) = 0x61ed580;
        *(void**)obj = (void*)0x13eb90c;
        *(u32*)((char*)obj + 4) = 0;
        *(void**)obj = (void*)0x13eb844;
        *(u32*)((char*)obj + 0x38) = 0;
    }
    *(void**)((char*)obj + 8) = this;

    void* server = FUN_0067dcc0();
    ((void (__thiscall*)(void*, u32, void*, int, int))VT(server)[0x18 / 4])(server, 0x61ed580, obj, 0, 0);
    MOPS(this)->FUN_00e26680();
    return 0;
}

// ===========================================================================
// 0x00e27be0
// ===========================================================================
// @ 0x00e27be0
u8 COps::FUN_00e27be0(u32 a, void* obj)
{
    if (!FUN_00950ef0(a, obj))
    {
        if (*(u32*)((char*)obj + 8) == 0x13)
        {
            void* p = *(void**)obj;
            if (p != 0)
            {
                if (((u32 (__thiscall*)(void*))VT(p)[0x1c / 4])(p) == 0x3dae412)
                    FUN_00e26680();
            }
        }
        return 0;
    }
    return 1;
}

// ===========================================================================
// 0x00e27c30
// ===========================================================================
// @ 0x00e27c30
void cSPUIPosseItem::FUN_00e27c30(u32 a, u32 b)
{
    mField1f0 = b;
    mField1f4 = a;
    MOPS(this)->FUN_00e26680();
}

// ===========================================================================
// 0x00e27c50
// ===========================================================================
// @ 0x00e27c50
void cSPUIPosse::SetCaptionText(const u16* text)
{
    const u16* p = text;
    while (*p != 0)
        ++p;
    mCaption.assign(text, text + (p - text));
    MOPS(this)->FUN_00e26680();
}

// ===========================================================================
// 0x00e27c90
// ===========================================================================
// @ 0x00e27c90
u8 cSPUIPosseItemTribeBaby::init(cSPUIPosse* posse)
{
    if (cSPUIPosseItem::init(posse))
    {
        void* coll = mWindows.mpData[4];
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3dea7f0, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, 1);
        ((void (__thiscall*)(void*))VT(w)[0x90 / 4])(w);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, this);

        void* sys = FUN_00a206f0();
        void* r = sys != 0 ? ((void* (__thiscall*)(void*))VT(sys)[0x20 / 4])(sys) : 0;

        FUN_00435ed0(*(u32*)0x16ac2c8, r);
        mBlinkerStart = FUN_00805080();
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00e27d30
// ===========================================================================
// @ 0x00e27d30
u8 cSPUIPosseItemTribeBaby::SetControlValue(u32 id, float value, u32 a, u32 b)
{
    if (id == 0x3dea7f0)
    {
        float v = value;
        if (v < 0.0f)
            v = 0.0f;
        if (v > 100.0f)
            v = 100.0f;
        mControlValue01 = v * 0.01f;

        void* coll = mWindows.mpData[4];
        if (coll != 0)
        {
            void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3dea7f0, 1);
            if (w != 0)
                ((void (__thiscall*)(void*))VT(w)[0x90 / 4])(w);
        }
        return 1;
    }
    return cSPUIPosseItem::SetControlValue(id, value, a, b);
}

// ===========================================================================
// 0x00e27df0
// ===========================================================================
// @ 0x00e27df0
void cSPUIPosseItem::SetState_BlinkGuard(u32 state)
{
    if (mControlValue01 < 1.0f && (state == 2 || state == 4 || state == 3))
        return;
    SetStateWithoutNotification(state);
}

// ===========================================================================
// 0x00e27e20
// ===========================================================================
// @ 0x00e27e20
u8 cSPUIPosseItemTribe::init(cSPUIPosse* posse)
{
    if (cSPUIPosseItem::init(posse))
    {
        void* coll = mWindows.mpData[4];
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3dea7f0, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, 1);
        ((void (__thiscall*)(void*))VT(w)[0x90 / 4])(w);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, this);

        void* w2 = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3d99141, 1);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 1, 0);

        void* w3 = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w3)[0x7c / 4])(w3, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w3)[0x7c / 4])(w3, 2, 0);
        ((void (__thiscall*)(void*, int, int))VT(w3)[0x7c / 4])(w3, 1, 0);
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00e27ef0
// ===========================================================================
// @ 0x00e27ef0
u8 cSPUIPosseItemSpace::init(cSPUIPosse* posse)
{
    u8 r = cSPUIPosseItem::init(posse);
    if (r != 0)
    {
        if (mpField50 != 0)
        {
            ((void (__thiscall*)(void*, int))VT(this)[0xb8 / 4])(this, 2);
            return r;
        }

        void* w = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 2, 0);
    }
    return r;
}

// ===========================================================================
// 0x00e27f60
// ===========================================================================
// @ 0x00e27f60
void cSPUIPosseItem::SetState_SpaceGuard(u32 state)
{
    if (mpField50 != 0)
    {
        if (state == 2 || state == 4)
            return;
        SetStateWithoutNotification(state);
    }
    else if (state == 1)
    {
        SetStateWithoutNotification(1);
    }
}

// ===========================================================================
// 0x00e27fa0
// ===========================================================================
// @ 0x00e27fa0
void cSPUIPosseItem::SetState_Skip24(u32 state)
{
    if (state != 2 && state != 4)
        SetStateWithoutNotification(state);
}

// ===========================================================================
// 0x00e27fc0
// ===========================================================================
// @ 0x00e27fc0
u8 cSPUIPosseItemCreature::init(cSPUIPosse* posse)
{
    if (cSPUIPosseItem::init(posse))
    {
        void* w = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 2, 0);
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00e28010
// ===========================================================================
// @ 0x00e28010
void cSPUIPosseItem::SetState_Only1(u32 state)
{
    if (state == 1)
        SetStateWithoutNotification(1);
}

// ===========================================================================
// 0x00e28030
// ===========================================================================
// @ 0x00e28030
void cSPUIPosseItem::SetState_Skip234(u32 state)
{
    if (state != 2 && state != 4 && state != 3)
        SetStateWithoutNotification(state);
}

// ===========================================================================
// 0x00e28050
// ===========================================================================
// @ 0x00e28050
u8 cSPUIPosseItemPlot::init(cSPUIPosse* posse)
{
    if (cSPUIPosseItem::init(posse))
    {
        void* coll = mWindows.mpData[4];
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x614a0c4, 1);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, this);

        void* w2 = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 2, 0);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 1, 0);
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00e280e0
// ===========================================================================
// @ 0x00e280e0
void cVec8::push_back(cRefPair* src)
{
    cRefPair* p = mpEnd;
    if (p < mpCap)
    {
        mpEnd = p + 1;
        if (p != 0)
        {
            p->mpFirst = src->mpFirst;
            if (p->mpFirst != 0)
                AddRefI(p->mpFirst);

            p->mpSecond = src->mpSecond;
            if (p->mpSecond != 0)
            {
                AddRefI(p->mpSecond);
                return;
            }
        }
    }
    else
    {
        FUN_00e26c80(p, src);
    }
}

// ===========================================================================
// 0x00e281a0
// ===========================================================================
// @ 0x00e281a0
void cSPUIPosseItem::FUN_00e281a0(u8 flag)
{
    if (flag != 0)
    {
        cRefPair* begin = mBars.mpBegin;
        cRefPair* end = mBars.mpEnd;
        for (cRefPair* p = begin; p != end; ++p)
        {
            void* o = p->mpSecond;
            ((void (__thiscall*)(void*))VT(o)[0xcc / 4])(o);
        }
    }

    cRefPair* begin = mBars.mpBegin;
    cRefPair* end = mBars.mpEnd;
    void* mid = FUN_00e24290(end, end, begin);
    mBars.FUN_00e23870(mid, (void*)mBars.mpEnd);
    mBars.mpEnd += begin - end;

    mRefs.FUN_00e25bd0(mRefs.mpBegin, mRefs.mpEnd);
    mFlag1d4 = 1;
}

// ===========================================================================
// 0x00e28230
// ===========================================================================
// @ 0x00e28230
void cSPUIPosseItem::FUN_00e28230()
{
    FUN_00e26de0(mRefs.mpBegin, mRefs.mpEnd, (void*)0x00e22760);
}

// ===========================================================================
// 0x00e28250
// ===========================================================================
// @ 0x00e28250
void cVec8::resize(u32 n)
{
    cRefPair* end = mpEnd;
    cRefPair* begin = mpBegin;
    i32 have = (i32)(end - begin);
    if (n > (u32)have)
    {
        cRefPair tmp;
        tmp.mpFirst = 0;
        tmp.mpSecond = 0;
        FUN_00e26e50(end, n - (u32)have, &tmp);
        return;
    }

    cRefPair* target = begin + n;
    void* r = FUN_00e24290(end, end, target);
    FUN_00e23870(r, (void*)mpEnd);
    mpEnd -= end - target;
}
