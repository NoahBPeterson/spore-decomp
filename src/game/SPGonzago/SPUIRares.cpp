// src/game/SPGonzago/SPUIRares.cpp -- migrated from slice(s) s01064990 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIRares.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s01064990 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int   (__thiscall *TcRi)(void*);
typedef void* (__thiscall *TcRp)(void*);
#define VTS(o, off) (*(void**)((char*)*(void**)(o) + (off)))
void*  FUN_00b3d3f0();
void   KillSetiEffects_435ed0(void* a, int id);
void*  GetSystemAT_a206f0();
class SimSlot
{
public:
    char  mPad00[0x5c];
    void* mpE30;        // +0x5c
};
class E30Obj
{
public:
    void Method_e30a60(int v);
};
class CLayout
{
public:
    void* FindWindowByID(int id, int flag);
};
class CFeedItem
{
public:
    void  Reserve_666630(int a, int b);
    void  Refresh_6666c0(const wchar_t* text);
    void  FUN_00666660(int a);
    bool  CheckFlag_666680(int a);
    void  Release();
};
class CFeedList
{
public:
    void  FUN_006628d0();
    void  FUN_00662920(int on);
    void* FUN_00662a20(int a);
    void  FUN_00662c10(void* item);
    void  FUN_00663350(int a);
    unsigned FUN_00664600();
    void* FUN_00664610(unsigned idx);
};
class cEmpire;
struct Sub48
{
    void  Init_00e0a390();
    void  FUN_00e0a5c0();
    void  FUN_00e0a400();
    bool  FUN_00e0a780(int a, void* b);
    void* FUN_00e09c90(int a, int b, int c);
    char  mBody[0x70];
};
struct FilterNode
{
    FilterNode* mpNext;    // +0
    void*       mpPrev;    // +4
    void*       mpKey;     // +8
};
class cEmpire
{
public:
    void*       mpVtbl0;        // +0x00
    char        mPad04[4];      // +0x04
    void*       mpVtbl1;        // +0x08
    void*       mpVtbl2;        // +0x0c
    char        mPad10[4];      // +0x10
    int         m14;            // +0x14
    CLayout*    mpLayout;       // +0x18
    char        mPad1c[0x34 - 0x1c];
    FilterNode  mFilterHead;    // +0x34
    char        mb40;           // +0x40
    char        mPad41[3];
    void*       m44;            // +0x44
    Sub48       m48;            // +0x48
    void*       mpSFV;          // +0xb8
    void*       mpMsgServer;    // +0xbc
    void*       mpIdentity;     // +0xc0
    int         mMsgId;         // +0xc4
    int         mC8;            // +0xc8
    int         mCC;            // +0xcc
    CFeedList*  mpFeedList;     // +0xd0
    CFeedItem*  mpSelected;     // +0xd4

    void InitBase_00e18bb0();
    void OnWinProcAdd_010829f0(int arg);
    void BaseDestroy_00e18810();
    void BaseDestroy2_00e18980();
    void Show_00e18860(int arg);
    void SetText_00e18890(void* text);

    cEmpire();
    ~cEmpire();

    void Destroy_01064990();
    void OnWinProcAdd_01064a00(int arg);
    void PopulateLeft_01064b60();
    void Init_01064fd0();
    void PopulateFeed_010655a0();
    void Show_01065900(int arg);
};
class cEmpireB
{
public:
    void* mpVtblB;        // this+0x00 = outer+0x08
    char  mPad04[0x38];   // this+0x04 .. this+0x3b
    void* m44;            // this+0x3c = outer+0x44
    bool DefineLeftScroll_01064f00(int id, void* ev);
};
static inline cEmpire* empireFromB(void* p) { return (cEmpire*)((char*)p - 0x08); }
struct CEvent
{
    void*    mpObj;     // +0
    void*    mpUnk4;    // +4
    uint32_t mId;       // +8
    char     pad0c[4];
    void*    mpData;    // +0x10
};
// ---- items of slice s01064990 end

// @ 0x01064f00
bool cEmpireB::DefineLeftScroll_01064f00(int id, void* ev)
{
    CEvent* e = (CEvent*)ev;

    if (e->mId == 0x1b)
    {
        void* obj = e->mpObj;
        int t = ((TcRi)VTS(obj, 0x20))(obj);
        if (t == 0x51aff90)
        {
            void* sys = GetSystemAT_a206f0();
            if (sys != 0)
                sys = ((TcRp)VTS(sys, 0x20))(sys);
            KillSetiEffects_435ed0(sys, 0x8821b509);
            return false;
        }
    }
    else if (e->mId == 0x287259f6)
    {
        void* obj = e->mpObj;
        int t = ((TcRi)VTS(obj, 0x20))(obj);
        if (t == 0x51aff90)
        {
            int v = ((TcRi)VTS(obj, 0x1c))(obj);
            m44 = (void*)v;
            void* sys = GetSystemAT_a206f0();
            if (sys != 0)
                sys = ((TcRp)VTS(sys, 0x20))(sys);
            KillSetiEffects_435ed0(sys, 0x806318da);
            empireFromB(this)->PopulateLeft_01064b60();
            void* sim = FUN_00b3d3f0();
            ((E30Obj*)((SimSlot*)sim)->mpE30)->Method_e30a60(v);
        }
    }
    return false;
}
