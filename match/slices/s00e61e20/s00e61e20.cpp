// Slice s00e61e20 -- Spore Simulator cell-game "attach the selected creature"
// cluster.
//
//   * 0x00e61e20  sCellOrientToward  (blend the current orientation toward the
//                                   desired one at a rate, then set it)
//   * 0x00e62120  cCellParts-helpers texture/name resolver for the tray window
//   * 0x00e62200  SP::sFindOrCreateUI (find-or-create the tray window record)
//   * 0x00e62380  SP::sAttach wrapper (attach a model to a part transform)
//   * 0x00e62440  SP::sGotoCreature_End (close the modal, spawn the end effect)
//   * 0x00e624b0  cCellGame parts-cache eraser
//   * 0x00e62500  the per-frame "selected part follows the cursor" tick
//   * 0x00e629a0  UI::BehaviorMessage "App" allocator + message-server post
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
#include <string.h>
#include <math.h>
#include <intrin.h>
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    i8;
typedef short          i16;
typedef int            i32;
typedef __int64        i64;
typedef unsigned __int64 u64;

// ------------------------------------------------------------------ thiscall thunks
typedef void  (__thiscall *TC_v0)(void*);
typedef void* (__thiscall *TC_p0)(void*);
typedef float (__thiscall *TC_f0)(void*);
typedef int   (__thiscall *TC_i0)(void*);
typedef char  (__thiscall *TC_c0)(void*);
typedef void  (__thiscall *TC_i1)(void*, int);
typedef void* (__thiscall *TC_pi)(void*, int);
typedef void  (__thiscall *TC_pc)(void*, char);
typedef void  (__thiscall *TC_pi1)(void*, int, int);
typedef void  (__thiscall *TC_iiiii)(void*, int, void*, int, int);
typedef void* (__thiscall *TC_pi11)(void*, int, int);
typedef char  (__thiscall *TC_i2)(void*, int, int);

// virtual-slot call: VFN(obj, byte-offset, thunk-type)
#define VFN(obj, off, T) ((T)(*(void***)(obj))[((off) >> 2)])

// ------------------------------------------------------------------ engine globals
extern "C" void* gspCellGame;        // 0x016b3c04  (SP::cCellGame*)
extern "C" void* gspCellGfx;         // 0x016b3c0c  (SP::cCellGfx*)

// ------------------------------------------------------------------ engine callees
extern "C" void* __cdecl SP_App();                                   // 0x0067dd10
extern "C" void* __cdecl MessageServer();                            // 0x0067dcc0
extern "C" void* __stdcall GetTriggerMgr(int flag);                  // 0x00b3d4d0
extern "C" void  __cdecl Screen_setModal();                           // 0x00ad7e40
typedef void (__thiscall *SetModalThunk)(void*);
extern "C" void  __cdecl FUN_00e61140();                             // 0x00e61140
extern "C" void  __cdecl CreateEffectSafe(void* world, u32 effectID, void* pos, void** out); // 0x00628450
extern "C" void* __cdecl sCellSetOrientation(void* cell, const void* quat); // 0x00e5e850
extern "C" void* __cdecl QuaternionFromMatrix33(float* out, const float* m, float eps); // 0x00472b80
extern "C" float* __cdecl FUN_007dcb00(float* out, const float* a, const float* b); // 0x007dcb00
extern "C" void* __cdecl FUN_00743b50();                             // 0x00743b50  cModelWorld::VecClear
extern "C" void  __cdecl FUN_007c4900(void* a, void* b, void* c);    // 0x007c4900
extern "C" void* __cdecl FUN_00e4cc40(void* handle, void* out);      // 0x00e4cc40
extern "C" char  __cdecl cString_Load(void* self, u32 id, u32 a, int b); // 0x006b54b0
extern "C" u16*  __cdecl cString_GetText(void* self);                // 0x006b55c0
extern "C" void  __cdecl eastl_wstring_assign(void* self, const u16* first, const u16* last); // 0x00423650
extern "C" void  __cdecl eastl_wstring_append(void* self, const u16* s); // 0x005c3d90
extern "C" char  __cdecl FUN_00e84510(int a, void* b);               // 0x00e84510
extern "C" void  __cdecl FUN_00e82130(void* self);                   // 0x00e82130
extern "C" void* __cdecl FUN_00b72230(int key);                      // 0x00b72230
extern "C" void* __cdecl FUN_00b72160();                             // 0x00b72160
extern "C" void* __cdecl FUN_00b72210(int key);                      // 0x00b72210
extern "C" void* __cdecl FUN_00e54050(int flag);                     // 0x00e54050
extern "C" int   __cdecl FUN_00e87200(u32 cell, void* a, void* b, int* out, int cap, float maxd); // 0x00e87200
extern "C" void  __cdecl FUN_00e50590(int* a, u32* b, int* c, int n); // 0x00e50590
extern "C" char  __cdecl FUN_00e505f0(int* a, u32 b, int c);         // 0x00e505f0
extern "C" void* __cdecl FUN_00b721d0(int a);                        // 0x00b721d0
extern "C" void  __cdecl Matrix3_Assign(void* dst, const void* src); // 0x0041cb40
extern "C" void  __cdecl FUN_0040efa0(void* self);                   // 0x0040efa0  cSPTransform::Invert
extern "C" void  __cdecl ComposeTransforms(void* a, void* b);        // 0x0040ccb0
extern "C" void* __cdecl SP_sAttach(void* a, void* b, void* c, void* d, int e); // 0x00e5f450
extern "C" float  __cdecl FUN_011e08c8(float x);                     // 0x011e08c8  acos
extern "C" double _cdecl _CIacos(double x);                          // acos intrinsic
extern "C" void* __cdecl operator_new(u32 size, void* name, int a, int b, int c, int d); // 0x00f473a0
extern "C" void* __cdecl eastl_rbtree_find0(int* out, int* key);     // 0x00e39fb0

// ------------------------------------------------------------------ vtables / literals
extern char  VT_013eb90c[];   // 0x013eb90c  ??_7RefBaseA22@@6B@
extern char  VT_013eb844[];   // 0x013eb844  PTR_FUN_013eb844
extern char  S_App[];         // 0x013ebc58  "App"
extern float KF_13eb8b0;      // 0x013eb8b0  sign-mask
extern float KF_13eb1bc;      // 0x013eb1bc  -1.0f
extern float KF_14851ec;      // 0x014851ec  quat-length epsilon
extern float KF_015a7c24;     // 0x015a7c24  two-pi
extern float KF_016b3dd0;     // 0x016b3dd0  two-pi
extern float KF_13ec488;      // 0x013ec488  half-rate scale
extern float KF_1485720;      // 0x01485720  1.0f
extern float KF_1471064;      // 0x01471064  0.5f
extern float KF_13eb8a0;      // 0x013eb8a0  0.25f
extern float KF_14851e8;      // 0x014851e8  3.4e38f
extern float KF_14853e0;      // 0x014853e0  0.25f
extern float KF_1440f84;      // 0x01440f84  1/6

// ------------------------------------------------------------------ object model
// SP::cCellGame (retail offsets used here):
//   +0x1c  mGridSquares pool (its own +0x24 is the pool free list head)
//   +0x70  mPartsCache (eastl::map<int, cCreatureDefinition>)
//   +0x74  mPartsCache end node
//   +0x40fc  midPlayerCell
//   +0x411c  mCurrentWorld
//   +0x5169  inGoldyCinematic byte
struct cCellGame {
    u8   m_pad00[0x411c];
    int  mMidPlayerCell;     // +0x40fc
    u8   m_pad4100[0x1c];
    void* mCurrentWorld;     // +0x411c
    u8   m_pad4120[0x1049];
    u8   mInGoldyCinematic;  // +0x5169
};

// SP::cCellGfx (retail offsets used here):
//   +0x24    cfg  (the DebugOptions-ish block: +0x24 flag, +0x26 flag)
//   +0xfc    the currently-selected part id
//   +0x100   the pending-parts vector (int, fixed 512)
//   +0x900   count of pending parts
//   +0x904   accumulated cursor-follow timer
//   +0x910   SP::cString (part name)
//   +0x920   SP::cString (part description)
//   +0x936   "ended" flag
//   +0x161c8 a world handle (SP::cCellGfx member near the end)
struct cCellGfx {
    u8   m_pad00[0xfc];
    int  mSelectedPart;      // +0xfc
    int  m_pending[512];     // +0x100
    u8   m_pad900[0];        // (kept for readability)
};
// The remaining cCellGfx fields are at large offsets; access them through a
// byte view so the slice stays readable.

// SP::cSPCell layout used by 0x00e61e20 / 0x00e62120 / 0x00e62380:
//   +0x14   mDesiredOrientation (cSPQuaternion)
//   +0x24   mDeformationMatrix  (cSPMatrix3, ends at +0x48)
//   +0x48   mTransform          (cSPTransform: flags/rev/translation/scale/rotation)
//   +0x5c   mTransform.mRotation (cSPMatrix3)
//   +0xec   mNoRepel
//   +0xf0   mEyeLookatState
//   +0x108  mModelWorld handle (cIModelWorld*)
//   +0x112  the "no icon" byte
//   +0x168  the attached-model handle
//   +0x244  mGfxID
struct cSPCell {
    u32  mWorld;                    // +0x00  the world the cell belongs to
    u8   m_pad04[0x10];
    float mDesiredOrientation[4];   // +0x14
    u8   m_pad24[0x24];
    u8   mTransform[0x38];          // +0x48
    u8   m_pad80[0x88];
    void* mModelWorld;              // +0x108
    u8   m_pad10c[6];
    u8   mNoIcon;                   // +0x112
    u8   m_pad113[0x55];
    void* mAttachedModel;           // +0x168
    u8   m_pad16c[0xd8];
    int  mGfxID;                    // +0x244
};

// ------------------------------------------------------------------ free functions
// @ 0x00e61e20
void sCellOrientToward(cSPCell* cell, float rate, float dt)
{
    float* cur = (float*)cell;
    float q[4];
    QuaternionFromMatrix33(q, (const float*)((u8*)cell + 0x5c), 0.0f);

    float qx = q[0], qy = q[1], qz = q[2], qw = q[3];
    float dx = cell->mDesiredOrientation[0];
    float dy = cell->mDesiredOrientation[1];
    float dz = cell->mDesiredOrientation[2];
    float dw = cell->mDesiredOrientation[3];

    // desired^-1 crossed with q, all in the -1 fold the original uses
    float px = dw * qx + (dz * -1.0f * dy * -1.0f) - (dx * -1.0f * qw);
    float py = dw * qy + (dx * -1.0f * qz - dz * -1.0f * qw);
    float pz = dw * qz + (dy * -1.0f * qw - dx * -1.0f * qx);
    float pw = dw * qw - (dz * -1.0f * qx + dz * -1.0f * qx + dy * -1.0f * qy + dx * -1.0f * qz);

    if (pw < 0.0f) {
        px = -px; py = -py; pz = -pz; pw = -pw;
    }

    float len2 = pz * pz + py * py + px * px;
    if (0.0000152587890625f <= len2) {
        float ang = (float)_CIacos((double)pw) * 2.0f;
        if (ang > KF_015a7c24) ang -= KF_016b3dd0;
        (void)ang;
        if (rate * dt > 0.0f) {
            float inv = 1.0f / (float)sqrt((double)len2);
            float half = (rate * dt) * -0.5f;
            float s = (float)sin((double)half);
            float c = (float)cos((double)half);
            float rr[4];
            rr[0] = px * inv * s;
            rr[1] = py * inv * s;
            rr[2] = pz * inv * s;
            rr[3] = c;
            float res[4];
            FUN_007dcb00(res, q, rr);
            sCellSetOrientation(cell, res);
            return;
        }
    }
    sCellSetOrientation(cell, cell->mDesiredOrientation);
    (void)cur;
}

// @ 0x00e62120
char sResolvePartName(void* cell, void* outStr)
{
    u16  buf[4];
    FUN_00743b50();

    void* def = FUN_00e4cc40(*(void**)((u8*)cell + 0x108), buf);
    u8* gfx = (u8*)gspCellGfx;
    char ok = cString_Load(gfx + 0x920, 0x4dc2f94, *(u32*)((u8*)def + 0xa4), 0);
    if (ok) {
        u16* text = cString_GetText(gfx + 0x920);
        u16* end = text;
        while (*end != 0) ++end;
        eastl_wstring_assign(outStr, text, text + (end - text));
        FUN_00e82130(buf);
        return 1;
    }
    u16* alt = (u16*)((u8*)def + 4);
    if (alt != 0 && *alt != 0) {
        eastl_wstring_append(outStr, alt);
        FUN_00e82130(buf);
        return 1;
    }
    char r = FUN_00e84510((int)((u8*)cell + 0xfc), outStr);
    FUN_00e82130(buf);
    return r;
}

// ------------------------------------------------------------------ UI records
// Fixed-stride handle pool: records are addressed by a (slot << 16 | serial)
// handle that the pool hands out, validates and resolves.
struct cHandlePool {
    void* mpData;        // +0x00  slot storage
    u32   mFreeHead;     // +0x04  first free slot (or 0xffffffff)
    u32   mSlotCount;    // +0x08  number of slots handed out so far
    u32   mFreeCount;    // +0x0c
    u32   mNextSlot;     // +0x10  slot used by the next Alloc
    u32   mStride;       // +0x14  slot size
    u32   mCapacity;     // +0x18

    u32   Alloc();               // 0x00b72160
    bool  IsValid(u32 handle);   // 0x00b721d0
    void* Get(u32 handle);       // 0x00b72210  handle -> record
    void* Next(int* iter);       // 0x00b72230  iterator step, 0 at the end
    int   Begin();               // 0x00e31100  iterator start
};

// Text buffer of a cString (eastl::basic_string<wchar_t> layout).
struct cWString {
    u16*  mpBegin;      // +0x00
    u16*  mpEnd;        // +0x04
    u16*  mpCapacity;   // +0x08
    void* mpAllocator;  // +0x0c
};

// The layout object of a record (its own calls are not virtual).
struct cSPUILayout {
    void* FindWindowByID(u32 id, int flag);   // 0x008105b0
    void  SetVisibility(int visible);         // 0x00810590
};

// One part's UI record.  +0x08/+0x14/+0x1c are the targets of the three eased
// channels and +0x10/+0x18/+0x20 the values they are eased from.
struct cPartUIRecord {
    u32   mSerial;    // +0x00
    int   mPartID;    // +0x04
    float mTargetA;   // +0x08
    float mPad0c;     // +0x0c
    float mCurA;      // +0x10
    float mTargetB;   // +0x14
    float mCurB;      // +0x18
    float mTargetC;   // +0x1c
    float mCurC;      // +0x20
    float mRate;      // +0x24
    float mScale;     // +0x28
    float mTimer;     // +0x2c
    u8    mbNamed;        // +0x30
    u8    mPad31[3];
    cSPUILayout* mpLayout; // +0x34
};

// The parts of cCellGfx these two routines touch.
struct cCellGfxView {
    u8          mPad00[0x24];
    u8          mCfgFlag24;        // +0x24
    u8          mPad25;
    u8          mCfgFlag26;        // +0x26
    u8          mPad27[0x9c - 0x27];
    cHandlePool mUIRecords;        // +0x9c
    u8          mPad0b8[0xfc - 0xb8];
    u32         mSelectedPart;     // +0xfc
    int         mPendingIDs[512];  // +0x100
    u32         mPendingCount;     // +0x900
    float       mCursorTimer;      // +0x904
    u8          mPad908[8];        // +0x908
    cWString    mPartName;         // +0x910
};

// The parts of cCellGame these two routines touch.
struct cCellGameView {
    u8          mPad00[0x1c];
    cHandlePool mCells;            // +0x1c
    u8          mPad38[0x40fc - 0x38];
    u32         mMidPlayerCell;    // +0x40fc
    u8          mPad4100[0x411c - 0x4100];
    u32         mCurrentWorld;     // +0x411c
    u8          mPad4120[0x5169 - 0x4120];
    u8          mInGoldyCinematic; // +0x5169
};

// @ 0x00e62200
void* sFindOrCreateUI(int partID, float a)
{
    // 0x00b72230 walks the record pool; 0x00e31100 yields the start index.
    int it = ((cCellGfxView*)gspCellGfx)->mUIRecords.Begin();
    for (;;) {
        cPartUIRecord* found =
            (cPartUIRecord*)((cCellGfxView*)gspCellGfx)->mUIRecords.Next(&it);
        if (found == 0)
            break;
        if (found->mPartID != partID)
            continue;
        return found;
    }

    u32 handle = ((cCellGfxView*)gspCellGfx)->mUIRecords.Alloc();
    if (handle == 0)
        return 0;
    cPartUIRecord* rec =
        (cPartUIRecord*)((cCellGfxView*)gspCellGfx)->mUIRecords.Get(handle);
    rec->mPartID  = partID;
    rec->mTargetA = a;
    rec->mTargetC = a;
    rec->mTargetB = a;
    rec->mCurA    = 0.0f;
    rec->mRate    = 0.5f;
    rec->mCurB    = 0.0f;
    rec->mCurC    = 0.0f;
    rec->mScale   = 0.25f;
    rec->mTimer   = 0.0f;

    cSPUILayout* layout = (cSPUILayout*)FUN_00e54050(0);
    layout->SetVisibility(1);
    rec->mpLayout = layout;

    cCellGameView* game = (cCellGameView*)gspCellGame;
    if (partID != (int)game->mCurrentWorld) {
        cSPCell* cell = (cSPCell*)game->mCells.Get((u32)partID);
        if (sResolvePartName(cell, &((cCellGfxView*)gspCellGfx)->mPartName)) {
            void* win = rec->mpLayout->FindWindowByID(0x31e94d0, 1);
            ((TC_i1)(*(void***)win)[0x20])(
                win, (int)(size_t)((cCellGfxView*)gspCellGfx)->mPartName.mpBegin);
            rec->mbNamed = 1;
            return rec;
        }
        rec->mbNamed = 0;
    }
    return rec;
}

// @ 0x00e62380
void sAttachPart(u32* out, u32 param_2, u32* param_3, u8* param_4)
{
    void* game = gspCellGame;
    if (FUN_00b721d0(*(int*)((u8*)out + 0x168)) != 0) return;

    u8 tr[0x38];
    u16 f0 = *(u16*)param_4;
    u16 f2 = *(u16*)(param_4 + 2);
    *(u32*)(tr + 4)  = *(u32*)(param_4 + 4);
    *(u32*)(tr + 8)  = *(u32*)(param_4 + 8);
    *(u32*)(tr + 0xc) = *(u32*)(param_4 + 0xc);
    *(u32*)(tr + 0x10) = *(u32*)(param_4 + 0x10);
    Matrix3_Assign(tr + 0x14, param_4 + 0x14);
    *(u16*)(tr + 0) = f0;
    *(u16*)(tr + 2) = f2;
    FUN_0040efa0(tr);
    (void)game;

    u8 tmp[0x38];
    ComposeTransforms(tmp, (u8*)param_3 + 0x48);
    void* attached = SP_sAttach((void*)(size_t)*out, (void*)(size_t)param_2, (void*)(size_t)*param_3, tmp, 0);
    *(void**)((u8*)out + 0x168) = attached;
}

// @ 0x00e62440
void sGotoCreatureEnd()
{
    void* mgr = GetTriggerMgr(0);
    ((SetModalThunk)Screen_setModal)(mgr);
    FUN_00e61140();

    void* local = 0;
    void* gfx = gspCellGfx;
    CreateEffectSafe(*(void**)((u8*)gfx + 0x161c8), 0xa1b0293d, 0, &local);
    if (local != 0) {
        ((TC_i1)(*(void***)local)[2])(local, 0);
    }
    *(u8*)((u8*)gspCellGfx + 0x936) = 1;
    if (local != 0) {
        ((TC_v0)(*(void***)local)[1])(local);
    }
}

// @ 0x00e624b0
typedef void* (__thiscall *MapFindThunk)(void*, int*, int*);
typedef void  (__thiscall *EraseCacheThunk)(void*, int*);
extern "C" void* FUN_00e39fb0();                     // 0x00e39fb0  eastl rbtree find
extern "C" void  FUN_00b36360();                     // 0x00b36360  map erase-by-key
void sErasePartsCacheEntry(int partID)
{
    void* game = gspCellGame;
    int out;
    int key = partID;
    int* node = (int*)((MapFindThunk)FUN_00e39fb0)((u8*)game + 0x70, &out, &key);
    if (*node != (int)((u8*)game + 0x74)) {
        int key2 = partID;
        ((EraseCacheThunk)FUN_00b36360)((u8*)game + 0x70, &key2);
    }
}

// ------------------------------------------------------------------ trigger manager
// 0x00b3d4d0 is the zero-argument accessor behind both call shapes in this
// cluster (0x00e62440 happens to pass a spare dword on the stack).
struct cTriggerMgr {
    u8  mPad00[0x2c];
    int mState;      // +0x2c
};
extern "C" void* __cdecl GetTriggerManager();   // 0x00b3d4d0

// The screen-space sampler App slot 0x16 returns; it fills two positions.
struct cPosSample {
    void GetPos(void* first, void* second);   // 0x007c4900
};

// @ 0x00e62500
void sTickSelectedPart(float dt)
{
    float t = dt + ((cCellGfxView*)gspCellGfx)->mCursorTimer;
    ((cCellGfxView*)gspCellGfx)->mCursorTimer = t;
    if (t > 1.0f)
        ((cCellGfxView*)gspCellGfx)->mPendingCount = 0;

    if (((cCellGameView*)gspCellGame)->mInGoldyCinematic != 0)
        return;
    cTriggerMgr* mgr = (cTriggerMgr*)GetTriggerManager();
    if (mgr->mState == 1 || mgr->mState == 2)
        return;

    void* app = SP_App();
    cPosSample* sample = (cPosSample*)((TC_p0)(*(void***)app)[0x16])(app);
    u8 posA[12];
    u8 posB[12];
    sample->GetPos(posA, posB);

    int ids[512];
    int n = FUN_00e87200(((cCellGameView*)gspCellGame)->mMidPlayerCell,
                         posA, posB, ids, 512, 3.4e38f);
    FUN_00e50590(((cCellGfxView*)gspCellGfx)->mPendingIDs,
                 &((cCellGfxView*)gspCellGfx)->mPendingCount, ids, n);

    for (int i = 0; i < n; ++i) {
        cSPCell* cell = (cSPCell*)
            ((cCellGameView*)gspCellGame)->mCells.Get((u32)ids[i]);
        if (cell->mWorld == ((cCellGameView*)gspCellGame)->mCurrentWorld)
            break;
        if (cell->mNoIcon != 0)
            continue;
        if (((cCellGfxView*)gspCellGfx)->mSelectedPart != cell->mWorld &&
            ((cCellGfxView*)gspCellGfx)->mCfgFlag24 != 0)
            continue;
        if (((cCellGfxView*)gspCellGfx)->mCfgFlag26 != 0)
            continue;
        if (FUN_00e505f0(((cCellGfxView*)gspCellGfx)->mPendingIDs,
                         ((cCellGfxView*)gspCellGfx)->mPendingCount,
                         (int)cell->mWorld) != 0)
            continue;
        if (sResolvePartName(cell, &((cCellGfxView*)gspCellGfx)->mPartName) == 0)
            continue;

        float scale = (float)cell->mGfxID / 6.0f;
        cPartUIRecord* rec = (cPartUIRecord*)sFindOrCreateUI((int)cell->mWorld, scale);
        rec->mTimer = dt * 4.0f + 1.0f;
        rec->mScale = 0.0f;
        rec->mCurC  = 1.0f;
        rec->mRate  = 0.0f;
        ((cCellGfxView*)gspCellGfx)->mSelectedPart = cell->mWorld;
        ((cCellGfxView*)gspCellGfx)->mSelectedPart = 0;
        break;
    }
}

// @ 0x00e629a0
extern char gAppNameTag;   // 0x01654c05  (DAT_01654c05)
void sPostBehaviorMessage()
{
    u8* raw = (u8*)operator_new(0x40, S_App, 0, 0, 0, 0);
    u8* msg = raw;
    if (raw) {
        *(u32*)(raw + 0x30) = 0;
        *(void**)raw = VT_013eb90c;
        _InterlockedExchange((volatile long*)(raw + 4), 0);
        *(void**)raw = VT_013eb844;
        *(u32*)(raw + 0x38) = 0;
        ((TC_v0)(*(void***)raw)[1])(raw);
    }
    *(u32*)(msg + 0x30) = 0xe11332;
    *(void**)(msg + 8) = &gAppNameTag;
    void* server = MessageServer();
    ((TC_iiiii)(*(void***)server)[6])(server, *(int*)(msg + 0x30), msg, 0, 0);
    ((TC_v0)(*(void***)msg)[2])(msg);
}
