// Slice s01079260: SP::cSPUISpace message handler (space-game toolbar buttons / hover glow).
// Optimized module: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"

typedef unsigned int uint;

struct IWindow;                              // UTfWin::IWindow (opaque)

// ---------------------------------------------------------------------------
// Stub types (offsets / vtable slots recovered from 0x01079260)
// ---------------------------------------------------------------------------
struct Image { char pad[0x1c]; int width; int height; };                       // +0x1c / +0x20

struct RenderContext {
    uint Begin2D(int flags);                                                    // 0x0095bc10 (ret 4)
    void End2D();                                                               // 0x0095bb20
};

struct IObj {                                                                   // generic UI object
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IObj* Query(uint id);                                               // slot 3 (+0xc)
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual uint GetFlags();                                                    // slot 8 (+0x20)
    virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15();
    virtual bool CheckFlag();                                                   // slot 16 (+0x40)
};

struct IWin {                                                                   // window (arg1)
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IObj* Query(uint id);                                               // slot 3 (+0xc)
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual uint Get30();                                                       // slot 12 (+0x30)
    virtual void s13();
    virtual const float* GetRect();                                             // slot 14 (+0x38)
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38();
    virtual void s39(); virtual void s40();
    virtual uint GetA4();                                                       // slot 41 (+0xa4)
    virtual uint GetA8();                                                       // slot 42 (+0xa8)
    virtual void s43(); virtual void s44();
    virtual IObj* QueryB4(uint id);                                             // slot 45 (+0xb4)
};

struct Msg {                                                                    // message
    IObj* src;                                                                  // +0
    int pad4;
    uint type;                                                                  // +8
    char pad[0xc];
    RenderContext* ctx;                                                         // +0x18
};

struct ImageSource {                                                            // secondary base at +0xc of Painter
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual Image* GetImage(int which);                                         // slot 4 (+0x10)
};

struct DrawParams { uint a; uint b; uint c; uint d; };

struct Painter {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void Prepare(RenderContext* ctx, const float* rect, const DrawParams* p);   // slot 4 (+0x10)
    int pad4[2];
    ImageSource src;                                                            // +0xc
    float* A830c90(float* tmp, int n);                                          // 0x00830c90 ret 8
    float* A830cc0(float* tmp, int n);                                          // 0x00830cc0 ret 8
    uint   A830c80(int n);                                                      // 0x00830c80 ret 4
    Image* A830cf0(int n);                                                      // 0x00830cf0 ret 4
    float* A830d30(float* tmp, int n);                                          // 0x00830d30 ret 8
    float* A830d60(float* tmp, int n);                                          // 0x00830d60 ret 8
    uint   A830d10(int n);                                                      // 0x00830d10 ret 4
};

struct Item {
    float F1050a60();                                                           // 0x01050a60
    bool  F104feb0();                                                           // 0x0104feb0
    float F0ce6920();                                                           // 0x00ce6920 (fld [ecx+0x1a8])
};
struct Inventory {
    Item* F00ff3fb0(IObj* o);    // 0x00ff3fb0 ret 4
};
struct Game {
    Inventory* GetPlayerInventory();    // 0x00a1ad60
};
struct Comm {
    bool F0ae9390();    // 0x00ae9390
};
struct Marker {
    void F106dcd0(uint id);    // 0x0106dcd0 ret 4
};
struct TSphere {
    bool F00c772c0(uint id);                                                    // 0x00c772c0 ret 4
    void F00c77bf0(uint id);                                                    // 0x00c77bf0 ret 4
};
struct NounMgr {
    TSphere* GetCurrentTerrainSphere();    // 0x00f67d90
};

Game*    SpaceGameGet();                      // 0x01002bd0
Comm*    CommManager();                       // 0x00b3d4a0
NounMgr* NounManager();                       // 0x00b3d300
Marker*  F010666a0();                         // 0x010666a0 (cdecl, no args)
IObj*    F01077b40(IObj* src);                // 0x01077b40 (cdecl)
Painter* F0059ed00(uint v);                   // 0x0059ed00 (cdecl)
uint     GetRecorderState();                  // 0x00435e90
void     KillSetiEffects(uint id, uint arg);  // 0x00435ed0
void     EA_Messaging_RemoveHandler(void* h, uint a, uint b, uint c, uint d);  // 0x00571db0
IObj*    GetSystemAT();                       // 0x00a206f0 (returns global)

// eastl cVector<UICell> relocation primitives (cdecl, element pointers)
int  __cdecl FUN_01077fb0(int dst, int src, int last);   // uninitialised move fwd
void __cdecl FUN_010779a0(int a, int b, int c);
void __cdecl FUN_01077f70(int a, int b, int c, int d);
void __cdecl FUN_01077f10(int a, int b, int c, int d, int e);
void __cdecl FUN_01078060(int a, int b, int c);
void __cdecl FUN_01078d30(int a, int b, int c);
void* __cdecl operator_new_eastl(uint size, const char* file, int line, int a,
                                 const char* allocator, int b);              // 0x00f473a0
void __cdecl operator_delete_eastl(int p);                                   // 0x00f47380

// callees used by the toolbar-cell / connection-dialog paths (cdecl / thiscall)
void*    __cdecl FUN_01077ae0(IWin* win);           // 0x01077ae0 (ret 4)
void     __cdecl FUN_01079040(uint index);          // 0x01079040
void     __cdecl FUN_010799d0(void* buf, const char* fmt, uint n);   // 0x010799d0

// callees used by the connection-dialog path
void*    __cdecl FUN_010666a0();                    // 0x010666a0
void*    __fastcall FUN_0106edc0(void* self, void* dummy);   // 0x0106edc0 (thiscall)
void*    __fastcall FUN_00ff3fb0(void* self, void* dummy);   // 0x00ff3fb0 (thiscall)
uint8_t  __fastcall FUN_0104ccf0(void* self, void* dummy);   // 0x0104ccf0 (thiscall)
uint8_t  __fastcall FUN_0104feb0(void* self, void* dummy);   // 0x0104feb0 (thiscall)
uint8_t  __fastcall FUN_0104ccd0(void* self, void* dummy);   // 0x0104ccd0 (thiscall)
uint8_t  __cdecl FUN_00807c70(void* node, uint a, int idx, int b);  // 0x00807c70
uint8_t  __cdecl FUN_00806b20(void* node, int a, int b);            // 0x00806b20
void*    __fastcall cConnectionDialog_ctor(void* self, void* dummy);  // 0x00810000

// The window object (arg to 0107a070): +0x24 holds the remembered row index.
struct ISpaceWin {
    char pad00[0x24];
    int  mSel24;                                // +0x24
};
int      __cdecl FUN_0107a300(void);                // placeholder (unused)
void*    __cdecl FUN_0107a070(void);                // placeholder (unused)
void F00805bb0(uint ctxToken, float a, float b, float c, float d, uint e, uint f,
               float g, float h, Image* img, float i);                          // 0x00805bb0 (cdecl, 11 args)

extern float g_UIGlowScale;                   // 0x016e339c

// Minimal ref-counted object interface (slots +0x04 = add-ref, +0x08 = release).
struct IRefObj {
    virtual void v00();
    virtual void v01();
    virtual void v02();
};

// cSPUILayout: the window/layout object (ctor 0x00810000, Init 0x008120d0).
struct cSPUILayout {
    bool Init(const void* key, uint a, uint b);                    // 0x008120d0 (ret 0xc)
    bool SetParentWin(IWin* parent, uint a, uint b, uint key);      // 0x008121b0 (ret 0x10)
};

// The UI node/widget interface reached from the cells.  Slot names encode the
// vtable byte offset so the mapping to the retail disassembly stays obvious.
struct INode {
    virtual void     v000();
    virtual void     v004();     // add-ref
    virtual void     v008();     // release
    virtual void     v00c();
    virtual void     v010();
    virtual void     v014();
    virtual void     v018();
    virtual void     v01c();
    virtual uint8_t  v020();     // "is enabled" predicate
    virtual void     v024();
    virtual void     v028();
    virtual void     v02c();
    virtual void     v030(void* out);
    virtual uint8_t  v034(void* a, void* b);
    virtual void     v038();
    virtual void     v03c();
    virtual void     v040();
    virtual void     v044();
    virtual void     v048();
    virtual void     v04c();
    virtual void     v050(void* a);
    virtual void     v054(uint a);
    virtual void     v058();
    virtual void     v05c(uint a);
    virtual void     v060();
    virtual void     v064();
    virtual void     v068();
    virtual void     v06c();
    virtual void     v070(float x, float y);
    virtual void     v074(float x, float y);
    virtual void     v078();
    virtual void     v07c(uint a, uint8_t b);
    virtual void     v080(void* text);
    virtual void     v084();
    virtual void     v088();
    virtual void     v08c();
    virtual void     v090();
    virtual void     v094();
    virtual void     v098();
    virtual void     v09c();
    virtual void     v0a0();
    virtual void     v0a4();
    virtual void     v0a8();
    virtual void     v0ac();
    virtual void     v0b0();
    virtual void     v0b4();
    virtual void     v0b8(uint a, void* b);
    virtual void     v0bc();
    virtual void     v0c0();
    virtual void     v0c4();
    virtual void     v0c8();
    virtual void     v0cc();
    virtual void     v0d0();
    virtual void     v0d4();
    virtual void     v0d8();
    virtual void     v0dc();
    virtual void     v0e0();
    virtual void     v0e4();
    virtual void     v0e8();
    virtual void     v0ec();
    virtual void*    v0f0(uint a, uint b);
    virtual void     v0f4();
    virtual void     v0f8();
    virtual void     v0fc();
    virtual void     v100();
    virtual void     v104(void* a);
};

extern uint8_t g_alloc_13ebb38[];      // 0x013ebb38 eastl allocator tag
extern char    g_str_Simulator[];      // 0x013f09b4 "Simulator"
extern char    g_fmt_013f01bc[];       // 0x013f01bc digit format string
extern uint8_t g_key_13f6b3c[];        // 0x013f6b3c heap tag for the dialog object

// The 12-byte cell stored in the vector at +0x30:
//   +0 : cSPUILayout* (owned, ref-counted; null until built)
//   +4 : float position
//   +8 : uint8_t  dirty / needs-build flag
struct UICell {
    void*   mNode;      // +0
    float   mPos;       // +4
    uint8_t mFlag;      // +8
};

// The cell vector's control block (begin/end/cap), at UISpace+0x30.
struct CellVec {
    UICell* begin;      // +0
    UICell* end;        // +4
    UICell* cap;        // +8
    void F10799f0(UICell* first, UICell* last);   // 0x010799f0 (ret 8)
    void F1079ff0(uint n);                        // 0x01079ff0 (ret 4)
    void F1079a60(UICell* pos, uint n, const UICell* val);  // 0x01079a60 (ret 0xc)
};

struct UISpace {
    char pad[0x24];
    IWin* mpCurrent;                          // +0x24
    char pad28[0x4];
    void* mp2c;                               // +0x2c
    CellVec mCells;                           // +0x30
    char pad3c[0x8];                          // +0x3c
    uint mKey44;                              // +0x44
    uint mKey48;                              // +0x48
    void* mp4c;                               // +0x4c
    uint mKey50;                              // +0x50
    uint mKey54;                              // +0x54
    void* mp58;                               // +0x58
    uint mKey5c;                              // +0x5c
    uint mKey60;                              // +0x60
    void* mp64;                               // +0x64
    uint mKey68;                              // +0x68
    uint mKey6c;                              // +0x6c
    void* mp70;                               // +0x70
    void* mp74;                               // +0x74  layout init key
    char pad78[0x8];                          // +0x78
    uint  mFlags80;                           // +0x80  layout kind
    char pad84[0x4];                          // +0x84
    int   mCols88;                            // +0x88
    int   mRows8c;                            // +0x8c
    int   mSel90;                             // +0x90
    float mX94;                               // +0x94
    float mY98;                               // +0x98
    char  mFlag9c;                            // +0x9c
    char pad9d[0xb];                          // +0x9d
    uint  mKeyA8;                             // +0xa8
    char padac[0x8];                          // +0xac
    float mSpacingB4;                         // +0xb4
    float mSpacingB8;                         // +0xb8
    float mScaleBc;                           // +0xbc
    float mScaleC0;                           // +0xc0
    char padC4[0x24];                         // +0xc4
    char  mTeardownE8;                        // +0xe8
    char  mFlagE9;                            // +0xe9
    char padEa[0x2a];                         // +0xea
    void* mpHandler114;                       // +0x114
    uint  mHandler118;                        // +0x118
    uint  mHandler11c;                        // +0x11c
    uint  mHandler120;                        // +0x120
    uint  mHandler124;                        // +0x124
    void F1078ec0();                          // 0x01078ec0
    void F1078fa0();                          // 0x01078fa0
    void F1079040(uint index);                // 0x01079040 (ret 4)
    bool F1077900(IObj* o);                   // 0x01077900 (ret 4)
    bool HandleMessage(IWin* win, Msg* msg);  // 0x01079260 (ret 8)
    bool F1077b70(uint a, uint* out);         // 0x01077b70 (ret 8)
    void F1079890(uint index);                // 0x01079890 (ret 4)
    void F1079f90();                          // 0x01079f90 (ret 0)
    INode* F1079d10(IWin* parent, uint index);   // 0x01079d10 (ret 8)
    void   F107a070(ISpaceWin* win);          // 0x0107a070 (ret 4)
    void   F107a300();                        // 0x0107a300 (ret 0)
    void F1077d30();                          // 0x01077d30
    void F1077bf0(void* arg);                 // 0x01077bf0 (ret 4)
    void F1077e20();                          // 0x01077e20
};

// @ 0x01079260
bool UISpace::HandleMessage(IWin* win, Msg* msg)
{
    bool result = false;
    if (msg->type == 0xd) {
        if (mpCurrent != win) {
            IObj* a = win ? win->Query(0x8ed27e7a) : 0;
            IObj* o2 = win->QueryB4(0x600db9c);
            IObj* b = o2 ? o2->Query(0x707459dd) : 0;
            Inventory* inv = SpaceGameGet()->GetPlayerInventory();
            if (a && inv && b) {
                float f = inv->F00ff3fb0(b)->F1050a60() * 0.95f + 0.05f;
                uint8_t flag = (uint8_t)(a->GetFlags() >> 2);
                flag &= 1;
                RenderContext* ctx = msg->ctx;
                Painter* p = F0059ed00(win->GetA8());
                const float* r = win->GetRect();
                float rect[4];
                rect[0] = 0.0f; rect[1] = 0.0f;
                rect[2] = r[2] - r[0]; rect[3] = r[3] - r[1];
                uint v30 = win->Get30();
                DrawParams dp;
                dp.a = 1; dp.b = 0; dp.c = win->GetA4(); dp.d = v30;
                p->Prepare(ctx, rect, &dp);
                float u0, u1;
                if (flag) {
                    u0 = 1.5707964f;
                    u1 = 1.5707964f - g_UIGlowScale * f;
                } else {
                    u1 = 1.5707964f - g_UIGlowScale;
                    u0 = 1.5707964f - g_UIGlowScale * f;
                }
                float hw = (rect[2] - rect[0]) * 0.5f;
                float hh = (rect[3] - rect[1]) * 0.5f;
                ImageSource* is = &p->src;
                Image* img = is->GetImage(4);
                if (img) {
                    float w = (float)img->width;
                    float h = (float)img->height;
                    float t0[2], t1[2];
                    float* q0 = p->A830c90(t0, 4);
                    float x0 = q0[0], y0 = q0[1];
                    float* q1 = p->A830cc0(t1, 4);
                    float x1 = q1[0], y1 = q1[1];
                    uint c = p->A830c80(4);
                    uint tok = ctx->Begin2D(0);
                    F00805bb0(tok, x1 + hw, y1 + hh, x0 * w, y0 * h, c, c, u1, u0, img, 0.05f);
                    ctx->End2D();
                }
                img = p->A830cf0(0);
                if (img) {
                    float w = (float)img->width;
                    float h = (float)img->height;
                    float t0[2], t1[2];
                    float* q0 = p->A830d30(t0, 4);
                    float x0 = q0[0], y0 = q0[1];
                    float* q1 = p->A830d60(t1, 4);
                    float x1 = q1[0], y1 = q1[1];
                    uint c = p->A830d10(4);
                    uint tok = ctx->Begin2D(0);
                    F00805bb0(tok, x1 + hw, y1 + hh, x0 * w, y0 * h, c, c, u1, u0, img, 0.05f);
                    ctx->End2D();
                }
                result = true;
            }
        }
    } else if (msg->type == 0x287259f6) {
        uint id = msg->src->GetFlags();
        switch (id) {
        case 0x5f72d7c:
            F1078ec0();
            KillSetiEffects(0xa25c8861, GetRecorderState());
            return true;
        case 0x5f72d8a: {
            F1078fa0();
            IObj* at = GetSystemAT();
            KillSetiEffects(0xa25c8861, at ? at->GetFlags() : 0);
            return true;
        }
        case 0x34ef68d:
        case 0x70648eae: {
            IObj* o = F01077b40(msg->src);
            bool ok = F1077900(o);
            IObj* at = GetSystemAT();
            uint v = at ? at->GetFlags() : 0;
            KillSetiEffects(ok ? 0xa9c4342u : 0x42f52773u, v);
            result = true;
            if (ok && o && o->CheckFlag() && !CommManager()->F0ae9390()) {
                Inventory* inv = SpaceGameGet()->GetPlayerInventory();
                if (inv) {
                    Item* it = inv->F00ff3fb0(o);
                    if (it && !it->F104feb0()) {
                        TSphere* ts = NounManager()->GetCurrentTerrainSphere();
                        if (ts && !ts->F00c772c0(0x65fef10)) {
                            ts->F00c77bf0(0x65fef10);
                            F010666a0()->F106dcd0(0x34235299);
                        }
                        if (it->F0ce6920() > 0.0f && ts && !ts->F00c772c0(0x6788f1c)) {
                            ts->F00c77bf0(0x6788f1c);
                            F010666a0()->F106dcd0(0xb396e5bb);
                        }
                    }
                }
            }
            return result;
        }
        default:
            if (id - 0x5f72da0u <= 9u) {
                F1079040(id - 0x5f72da0u);
                KillSetiEffects(0xa25c8861, GetRecorderState());
                return true;
            }
            return false;
        }
    }
    return result;
}

// ===========================================================================
// 0x01079890 - select a toolbar cell by linear index: validate it, then map
// the index to a subdivision of the (rows*cols) grid and forward it.
// ===========================================================================
// @ 0x01079890
void UISpace::F1079890(uint index)
{
    if (F1077b70(index, &index))
        F1079040(index / (uint)(mRows8c * mCols88));
}

// ===========================================================================
// 0x01079f90 - teardown: free the cell vector, drop the messaging handler,
// clear the "built" byte and run the base destructor tail.
// ===========================================================================
// @ 0x01079f90
void UISpace::F1079f90()
{
    mCells.F10799f0(mCells.begin, mCells.end);
    if (mpHandler114)
    {
        void* h = mpHandler114;
        mpHandler114 = 0;
        EA_Messaging_RemoveHandler(h, mHandler118, mHandler11c, mHandler120, mHandler124);
    }
    mTeardownE8 = 0;
    return F1077d30();
}

// ===========================================================================
// 0x01079ff0 - resize the cell vector to n elements (grow by appending
// default cells, shrink by destroying the tail).
// ===========================================================================
// @ 0x01079ff0
void CellVec::F1079ff0(uint n)
{
    UICell* first = begin;
    UICell* last  = end;
    if ((uint)((last - first) / 0xc) < n)
    {
        UICell val;
        val.mNode = 0;
        val.mPos  = 0.0f;
        val.mFlag = 1;
        F1079a60(last, n - (uint)((last - first) / 0xc), &val);
    }
    else
    {
        F10799f0(first + n, last);
    }
}

// ===========================================================================
// 0x01079a60 - append n default/val cells at `pos`, reallocating when the
// spare capacity cannot hold them.
// ===========================================================================
// @ 0x01079a60
void CellVec::F1079a60(UICell* pos, uint n, const UICell* val)
{
    if ((uint)((cap - end) / 0xc) < n)
    {
        int size = (int)((end - begin) / 0xc);
        uint newcap = (uint)(size * 2);
        if (size == 0)
            newcap = 1;
        uint room = n + (uint)size;
        if (room < newcap)
            room = newcap;
        UICell* buf = 0;
        if (room != 0)
            buf = (UICell*)operator_new_eastl(room * 0xc, g_str_Simulator, 0, 0,
                                              (const char*)g_alloc_13ebb38, 0xd1);
        UICell* endpos = pos;
        UICell* oldbegin = begin;
        UICell* p = (UICell*)FUN_01077fb0((int)oldbegin, (int)pos, (int)buf);
        FUN_010779a0((int)oldbegin, (int)endpos, (int)buf);
        FUN_01077f70((int)p, n, (int)val, (int)p);
        UICell* mid = (UICell*)((char*)p + n * 0xc);
        UICell* oldend = end;
        UICell* r = (UICell*)FUN_01077fb0((int)endpos, (int)oldend, (int)mid);
        FUN_010779a0((int)endpos, (int)oldend, (int)mid);
        if (begin != 0 && ((int*)begin)[-1] != 0)
            operator_delete_eastl((int)begin);
        begin = buf;
        end   = r;
        cap   = (UICell*)((char*)buf + room * 0xc);
    }
    else if (n != 0)
    {
        UICell tmp;
        tmp.mNode = val->mNode;
        if (tmp.mNode != 0)
            ((IRefObj*)tmp.mNode)->v01();
        tmp.mPos  = val->mPos;
        tmp.mFlag = val->mFlag;
        UICell* oldend = end;
        uint avail = (uint)((end - pos) / 0xc);
        if (n < avail)
        {
            UICell* moveto = (UICell*)((char*)oldend - n * 0xc);
            FUN_01077f10((int)&val, (int)moveto, (int)oldend, (int)oldend, (int)pos);
            end = (UICell*)((char*)end + n * 0xc);
            FUN_01078060((int)pos, (int)moveto, (int)oldend);
            FUN_01078d30((int)pos, (int)((char*)pos + n * 0xc), (int)&tmp);
        }
        else
        {
            FUN_01077f70((int)oldend, n - avail, (int)&tmp, (int)pos);
            end = (UICell*)((char*)end + (n - avail) * 0xc);
            FUN_01077f10((int)&pos, (int)pos, (int)oldend, (int)end, (int)pos);
            end = (UICell*)((char*)end + avail * 0xc);
            FUN_01078d30((int)pos, (int)oldend, (int)&tmp);
        }
        if (tmp.mNode != 0)
            ((IRefObj*)tmp.mNode)->v02();
    }
}

// ===========================================================================
// 0x01079d10 - build the toolbar cell at `index`: create the widget, place it
// on the grid, then fill in its label / state.
// ===========================================================================
// @ 0x01079d10
INode* UISpace::F1079d10(IWin* parent, uint index)
{
    INode* node = (INode*)FUN_01077ae0(parent);
    if (node == 0)
        return node;

    cSPUILayout* layout = (cSPUILayout*)node;
    layout->SetParentWin(parent, (uint)mp2c, 0, 0x5b598fa);

    float fx, fy;
    if (mFlags80 == 0x120ad1fb)
    {
        uint col = index % (uint)mCols88;
        uint row = index / (uint)mCols88;
        fx = (float)(int)col * (mSpacingB4 + mX94);
        fy = (float)(int)row * (mSpacingB8 + mY98);
    }
    else
    {
        uint col = index % (uint)mRows8c;
        uint row = index / (uint)mRows8c;
        fx = (float)(int)row * (mSpacingB4 + mX94);
        fy = (float)(int)col * (mSpacingB8 + mY98);
    }
    node->v070(fx, fy);

    INode* child = (INode*)node->v0f0(0x62840d8, 0);
    if (child != 0)
    {
        wchar_t buf[8] = {0};
        uint rem = index % (uint)(mRows8c * mCols88);
        if (rem < 10)
            FUN_010799d0(&buf, g_fmt_013f01bc, (rem + 1) % 10);
        child->v080(buf);
        child->v05c(mKeyA8);
        child->v07c(1, mFlagE9);
    }
    return (INode*)layout;
}

// ===========================================================================
// 0x0107a300 - rebuild the toolbar: grow the cell vector to a whole number of
// rows, build the missing cells, then push the resulting range to the host.
// ===========================================================================
// @ 0x0107a300
void UISpace::F107a300()
{
    uint perRow = (uint)(mRows8c * mCols88);
    uint cells  = (uint)((mCells.end - mCells.begin) / 0xc);

    uint top = cells;
    uint one = 1;
    uint* pick = (one < top) ? &top : &one;
    uint lastUsed = 0;
    uint u = *pick - 1;
    if (u != 0)
    {
        UICell* pc = (UICell*)((char*)mCells.begin + 8 + u * 0xc);
        do
        {
            if (pc->mFlag == 0)
                break;
            u -= 1;
            pc = (UICell*)((char*)pc - 0xc);
        } while (u != 0);
        lastUsed = u;
    }

    uint total;
    if (mSel90 == -1)
        total = (lastUsed / perRow + 1) * perRow;
    else if ((uint)mSel90 < lastUsed + 1)
        total = lastUsed + 1;
    else
        total = (uint)mSel90;
    if (mSel90 != -1 && total < lastUsed + 1)
        total = lastUsed + 1;

    uint n = total;
    mCells.F1079ff0(n);

    for (uint i = 0; i < n; ++i)
    {
        UICell* cell = mCells.begin + i;
        if (cell->mFlag != 0 && cell->mNode == 0 && mp74 != 0)
        {
            cSPUILayout* node = (cSPUILayout*)operator_new_eastl(0x18, (const char*)g_key_13f6b3c,
                                                                 0, 0, 0, 0);
            if (node == 0)
            {
                cell->mNode = 0;
            }
            else
            {
                cSPUILayout* made = (cSPUILayout*)node->Init(&mp74, 0, 0x5b598fa);
                (void)made;
                cell->mNode = node;
                node->Init(&mp74, 0, 0x5b598fa);
                F1079d10(0, i);
            }
        }
    }

    uint rows = (n - 1) / perRow + 1;
    if (mFlags80 == 0x120ad1fb)
        ((INode*)mp2c)->v074((float)(int)rows * mScaleBc, mScaleC0);
    else
        ((INode*)mp2c)->v074(mScaleBc, (float)(int)rows * mScaleC0);
    F1077e20();
}

// ===========================================================================
// 0x0107a070 - open the connection dialog for the selected toolbar cell:
// resolve the selection, build the cell if needed, then wire it into the host
// layout.
// ===========================================================================
// @ 0x0107a070
void UISpace::F107a070(ISpaceWin* win)
{
    int sel;
    if (mFlag9c == 0 || (sel = win->mSel24) == -1)
    {
        sel = 0;
        UICell* c = mCells.begin;
        UICell* e = mCells.end;
        while (c != e && c->mFlag == 0)
        {
            c += 1;
            ++sel;
        }
    }

    if ((int)((mCells.end - mCells.begin) / 0xc) <= sel)
        mCells.F1079ff0((uint)(sel + 1));

    UICell* cell = mCells.begin + sel;
    if (cell->mFlag != 0)
    {
        uint k44 = mKey44, k48 = mKey48;
        void* p4c = mp4c;
        void* sg = FUN_010666a0();
        void* game = SpaceGameGet();
        void* inv = FUN_0106edc0(game, 0);
        Item* it = (Item*)FUN_00ff3fb0(inv, 0);
        if (it != 0)
        {
            if (FUN_0104ccf0(it, 0))
            {
                k44 = mKey68; k48 = mKey6c; p4c = mp70;
            }
            else if (FUN_0104feb0(it, 0))
            {
                k44 = mKey5c; k48 = mKey60; p4c = mp64;
            }
            else if (FUN_0104ccd0(it, 0))
            {
                k44 = mKey50; k48 = mKey54; p4c = mp58;
            }
        }
        (void)sg;

        struct Key { uint a; uint b; void* c; } key;
        key.a = k44; key.b = k48; key.c = p4c;

        cSPUILayout* node = (cSPUILayout*)operator_new_eastl(0x18, (const char*)g_key_13f6b3c,
                                                             0, 0, 0, 0);
        if (node == 0)
            node = 0;
        else
            node = (cSPUILayout*)cConnectionDialog_ctor(node, 0);

        cSPUILayout* old = (cSPUILayout*)cell->mNode;
        if (node != old)
        {
            if (node != 0)
                ((IRefObj*)node)->v01();
            cell->mNode = node;
            if (old != 0)
                ((IRefObj*)old)->v02();
        }

        cSPUILayout* cur = (cSPUILayout*)cell->mNode;
        if (!cur->Init(&key, 0, 0x5b598fa))
        {
            cSPUILayout* bad = (cSPUILayout*)cell->mNode;
            if (bad != 0)
            {
                cell->mNode = 0;
                ((IRefObj*)bad)->v02();
            }
        }
        else
        {
            INode* n2 = F1079d10(0, (uint)sel);
            if (n2 != 0)
            {
                void* sg2 = FUN_010666a0();
                INode* sp = (INode*)FUN_0106edc0(sg2, 0);
                n2->v050(sp);
                uint en = ((INode*)win)->v020();
                n2->v054((-(uint)(en != 0) & 0x92ea67df) + 0x70648eae);
                n2->v0b8(0x600db9c, (char*)cell + 0xc);
                n2->v104(FUN_010666a0());
                void* host = p4c;
                ((INode*)host)->v030(&cell->mNode);
                void* sg3 = FUN_010666a0();
                FUN_00807c70(n2, *(uint*)((char*)sg3 + 0x254), sel, -1);
                if (((INode*)host)->v034(&node, (char*)&node - 0xc))
                    FUN_00806b20(n2, cell->mNode ? 0 : 0, 0);
                F1077bf0(host);
                cell->mFlag = 0;
            }
        }
    }

    if (mFlag9c != 0)
        win->mSel24 = sel;
}
