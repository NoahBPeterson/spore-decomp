// slice s00f62930 -- Swarm "terrain distribute" effect command
// (0x00f62930..0x00f63850).  Real PDB names: SP::cTerrainDistributeDescription,
// cTDDebugCommand, cTerrainDistributeEffectCommand, cTDEffectCommand,
// SWARM_TerrainDistributeAddCommands.  Module flags /O2 /MD /Gy /TP.
#include "types.h"

extern float kFXMaxFloat;                   // 0x015b0cb0
extern float g_1488874;                     // 0.1f constant
extern float g_1485720;                     // 1.0f constant
extern void* g_01667bac;                    // empty wide string
extern void* g_01667bad;
extern void* PTR_s_showLevels;              // "showLevels"
extern void* PTR_s_heights;                 // "heights"
extern void* PTR_s_types;                   // "types"
extern void* PTR_s_active;                  // "active"
extern void* PTR_s_debug;
extern void* PTR_s_level;
extern void* PTR_s_effect;
extern void* PTR_s_distance;
extern void* PTR_s_facing;
extern void* PTR_s_terrainDistribute;

void* __cdecl operator_new(int, const char*, int, int, int, int);
void* __cdecl operator_new(int, const char*, int, int, const char*, int);
void  __cdecl operator_del(void*);
void  __cdecl EA_IO_WriteUint32(void*, void*, int, int);
void  __cdecl FUN_00f62580(int*);
void* __cdecl SP_TerrainEditor();
void* __cdecl FUN_00b2afb0();
void  __cdecl FUN_0083c780(int, int);
void  __cdecl FUN_0089a510();
void  __cdecl FUN_007f1890(void*, void*, void*, void*, void*);
void  __cdecl FUN_0092a100(void*, void*);
float __cdecl FUN_00a6eaf0(int);
char  __cdecl EA_ParseEnum(int, void*);
int   __cdecl EA_GetPropertyAsKey(void*, int, void*);
void  __cdecl EA_cCommandBase_ctor(void*);

// ---------------------------------------------------------------------------
// image data touched by the reconstructed functions
// ---------------------------------------------------------------------------
extern int  g_013ef094;                     // 0x013ef094 hkReferencedObject vtable
extern int  g_0148f288;                     // 0x0148f288 cTerrainDistributeDescription vtable
extern int  g_0148f28c;                     // 0x0148f28c ArgScript::TerrainDistributeEffect vtable
extern int  g_0148f2b0;                     // 0x0148f2b0 cTDDebugCommand vtable
extern int  g_0148f2dc;                     // 0x0148f2dc cTDLevelCommand vtable
extern int  g_0148f300;                     // 0x0148f300 cTDEffectCommand vtable
extern int  g_0148f318;                     // 0x0148f318 cTDDistanceCommand vtable
extern int  g_0148f340;                     // 0x0148f340 cTDFacingCommand vtable
extern int  g_0148f1d4[5];                  // 0x0148f1d4 property keys
extern void* g_keyTDDebug;                  // 0x015b0c78
extern void* g_keyTDLevel;                  // 0x015b0c7c
extern void* g_keyTDEffect;                 // 0x015b0c80
extern void* g_keyTDDistance;               // 0x015b0c84
extern void* g_keyTDFacing;                 // 0x015b0c88

// ---------------------------------------------------------------------------
// ecx-receiver helpers: methods are declared but never defined, so each call
// is emitted out of line with ecx = this.
// ---------------------------------------------------------------------------
struct cArguments;
struct cCommandBaseCtor { void ctor(); };                     // 0x0083c800
struct cAppPropsFields  { void ctor(); };                     // 0x0083cdd0
struct cCommandBaseBase { void BaseOnRegister(int, int); };   // 0x0083c780
struct cTextFont        { void SetUserData(void*); };         // 0x00fd9450
struct cTDBase          { void Init(void*); };                // 0x00f62580
struct cEffectsParser   { int  MapFindA(int); };              // 0x00a6eaf0
struct cDescInstaller   { void Install(void*, int, void*); }; // 0x00a6f9c0
struct cCommandBase {                                         // vtable installed by 0x00f63190
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void AddChild(void* key, void* obj);               // +0x18
};

// cTypeInfo record (0x3c bytes, padded to the 0x40 stride used by the array).
struct cPropertyList;
struct cTypeKey { int mKey; int mValue; };
struct cTypeInfo {
    void*    mpProps;          // +0x00  property list (ref counted)
    float    mMin;             // +0x04  0.1f
    float    mMax;             // +0x08  kFXMaxFloat
    float    mHeight;          // +0x0c  1.0f
    cTypeKey mKeys[5];         // +0x10 .. +0x37 (key/value pairs)
    int      mPad38;           // +0x38
    int      mPad3c;           // +0x3c  (record stride is 0x40)
};
struct cPropertyList {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20();
    virtual char GetProperty(int key, void** out);      // +0x24
};
struct cTerrainDistributeInfo {
    int       mVtbl;           // +0x000
    int       mVtbl2;          // +0x004
    int       mPad08;          // +0x008
    cTypeInfo mTypes[9];       // +0x010 (stride 0x40)
    int       mPad250;         // +0x250
    int       mPad254;         // +0x254
    int       mPad258;         // +0x258
    void SetInfoFromProps(int idx, cPropertyList* props);   // 0x00f62ea0
};

// cTerrainDistributeDescription level block (0x28 bytes, 0x20 used).
struct cLevelInfo {
    float mActiveDist;         // +0x00
    float mChildActiveDist;    // +0x04
    float mActiveFacing;       // +0x08
    float mChildActiveFacing;  // +0x0c
    float mScale;              // +0x10
    int   mChildrenBegin;      // +0x14  eastl vector begin
    int   mChildrenEnd;        // +0x18
    int   mChildrenCap;        // +0x1c
    int   mPad20;              // +0x20
    int   mPad24;              // +0x24
};
struct cTerrainDistributeDescription {
    int        mVtbl;          // +0x000
    int        mPad04;         // +0x004
    int        mFlags08;       // +0x008
    cLevelInfo mLevel[5];      // +0x00c (stride 0x28)
};

// ArgScript::TerrainDistributeEffect command (0x124 bytes).
struct cTerrainDistributeCommand {
    int  mVtbl;                // +0x000
    int  mPad04;               // +0x004
    int  mPad08;               // +0x008
    int  mPad0c;               // +0x00c
    int  mPad10;               // +0x010
    int  mPad14;               // +0x014
    int  mPad18;               // +0x018
    int  mPad1c;               // +0x01c
    int  mPad20;               // +0x020
    int  mPad24;               // +0x024
    int  mPad28;               // +0x028
    int  mPad2c;               // +0x02c
    int  mState;               // +0x030  parser state - 0xc
    int  mHash34;              // +0x034  0x33109bb
    cTerrainDistributeDescription mDesc;   // +0x038
    int  mPad10c;              // +0x10c
    int  mInstaller;           // +0x110  copy of mState
    int* mpStrBegin;           // +0x114
    int* mpStrEnd;             // +0x118
    int* mStrCap;              // +0x11c
    int  mPad120;              // +0x120
    void OnRegister(int parser, int state);   // 0x00f633a0
    void OnEndBlock(char end);                // 0x00f63850
};

// AutoRefCount: [0] vtable, [4] count.
struct cRefVtbl { void (__thiscall* Destroy)(void*, int); };
struct cAutoRefCount { cRefVtbl* mpVtbl; int mRefCount; };

// vtables used by the terrain-distribute instance (0x00f62930).
struct cTDSphere {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual int* v0C();                                     // +0x0c -> ref holder
};
struct cTDArgsB {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10();
    virtual void* v14();                                    // +0x14 -> shape access
};
struct cTDArgsA {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void* v20();                                    // +0x20 -> installer
    virtual void v24(); virtual void v28();
    virtual int   v2C();                                    // +0x2c -> int value
};
struct cTDShapeAccess {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20();
    virtual char v24(unsigned a, unsigned b, int c);        // +0x24
};
struct cTDInstaller {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(char, void*);                          // +0x10
    virtual void v14();
    virtual void v18(void*, const void*, void*);            // +0x18
    virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2C(void*, const void*, void*);            // +0x2c
};
struct cTerrainDistributeInstance {
    char   mPad00[0x1c];       // +0x000
    int*   mpOwner;            // +0x01c  matrix/owner record
    char   mPad20[0x08];       // +0x020
    cTDArgsA* mpParam;         // +0x028
    int    mParamValue;        // +0x02c
    char   mPad30[0x70];       // +0x030
    float  mUpX, mUpY, mUpZ;   // +0x0a0
    float  mDownX, mDownY, mDownZ;   // +0x0ac
    char   mPadB8[0xf4];       // +0x0b8
    int*   mpSphere;           // +0x1ac  AutoRefCount
    char   mPad1B0[0x28];      // +0x1b0
    unsigned mBits1d8;         // +0x1d8
    unsigned mBits1dc;         // +0x1dc
    char   mPad1E0[0x50];      // +0x1e0
    int    mBuf230;            // +0x230
    int    mBuf234;            // +0x234
    int    mBuf238;            // +0x238
    unsigned char mFlags23c;   // +0x23c
    void Bind(cTDArgsA* a, cTDArgsB* b, int unused);   // 0x00f62930
};

// cTDEffectCommand (0x00f636f0): description with level blocks at +0x10.
struct cTDEntry {
    int   mId;                 // +0x00
    float mLo;                 // +0x04
    float mHi;                 // +0x08
    unsigned char mType;       // +0x0c
    unsigned char mResource;   // +0x0d
    unsigned char mOverride;   // +0x0e
    unsigned char mPad0f;      // +0x0f
};
struct cTDLevelBlock {
    float mValue;              // +0x00
    float mMin;                // +0x04
    float mMax;                // +0x08
    float mFacing;             // +0x0c
    float mFacingMax;          // +0x10
    int   mBegin;              // +0x14
    int   mEnd;                // +0x18
    int   mCap;                // +0x1c
    int   mPad20;              // +0x20
    int   mPad24;              // +0x24
};
struct cTDDistDesc {
    int   mPad00;              // +0x00
    int   mPad04;              // +0x04
    int   mPad08;              // +0x08
    int   mPad0c;              // +0x0c
    cTDLevelBlock mBlock[5];   // +0x10 (stride 0x28)
    int   mLevelIndex;         // +0xd8
    void* mpEffectsParser;     // +0xdc
};
struct cTDEffectCommand {
    int  mVtbl;                // +0x00
    void* mpConverter;         // +0x04
    int  mPad08;               // +0x08
    cTDDistDesc* mpDesc;       // +0x0c
    void Execute(cArguments* args);   // 0x00f636f0
};

// virtual call through the object's vtable: VPTR(ret, obj, byte-offset, argtypes...)(obj, args...)
#define VPTR(ret, obj, slot, ...) \
    ((ret (__thiscall*)(void*, __VA_ARGS__))((void**)*(void**)(obj))[(slot) / 4])

// thiscall cArguments
struct cArguments {
    int  MainArguments(int def);
    int* OptionArguments(const char* name, int n);
    char HasFlag(const char* name);
};
// The two overloads the terrain commands actually call (annotated instead of matched by name:
// the PDB's cArguments::MainArguments for 0x00838020 is the 3-argument internal form).
struct cArguments3 {
    int* MainArgsThree(int* out, int a, int b);   // 0x00838020 (thiscall, ret 0xc)
};
struct cArguments1 {
    int* MainArgsOne(int def);                    // 0x00838320 (thiscall, ret 4)
};
// vtables installed by the cTerrainDistributeEffectCommand constructor (0x145fd8c/0x145fd90)
extern int g_0145fd90;
extern int g_0145fd8c;

struct cTerrainEditor { void* GetCurrentTerrainSphere(); };

// ===========================================================================
// 0x00f62930 -- bind the effect instance to the current terrain sphere
// ===========================================================================
// @ 0x00f62930
void cTerrainDistributeInstance::Bind(cTDArgsA* a, cTDArgsB* b, int unused) {
    (void)unused;
    cTerrainEditor* te = (cTerrainEditor*)SP_TerrainEditor();
    cTDSphere* sphere = (cTDSphere*)te->GetCurrentTerrainSphere();

    // release the previous sphere reference
    cAutoRefCount* old = (cAutoRefCount*)mpSphere;
    if (old != 0) {
        mpSphere = 0;
        if (--old->mRefCount == 0) {
            old->mRefCount = 1;
            old->mpVtbl->Destroy(old, 1);
        }
    }
    // adopt the sphere's current reference
    if (sphere != 0) {
        int* holder = sphere->v0C();
        cAutoRefCount* neu = *(cAutoRefCount**)((char*)holder + 8);
        cAutoRefCount* prev = (cAutoRefCount*)mpSphere;
        if (neu != prev) {
            if (neu != 0) neu->mRefCount++;
            mpSphere = (int*)neu;
            if (prev != 0 && --prev->mRefCount == 0) {
                prev->mRefCount = 1;
                prev->mpVtbl->Destroy(prev, 1);
            }
        }
    }

    mpParam = a;
    mParamValue = a->v2C();

    // the two bounding corners: +fmax and -fmax
    float fmax = kFXMaxFloat;
    mUpX = fmax; mUpY = fmax; mUpZ = fmax;
    float neg = -fmax;
    mDownX = neg; mDownY = neg; mDownZ = neg;

    ((cTDBase*)((char*)this - 8))->Init(b);

    cTDShapeAccess* shape = (cTDShapeAccess*)b->v14();
    cTDInstaller* inst = (cTDInstaller*)a->v20();
    if (inst != 0) {
        int* owner = mpOwner;
        unsigned bits1 = mBits1d8;
        unsigned buf[8];
        for (int i = 0; i < 8; ++i)
            buf[i] = *(unsigned*)((char*)owner + 0x108 + i * 4);
        if ((bits1 & mBits1dc) != 0xffffffff) {
            buf[0] = bits1;
            buf[1] = mBits1dc;
        }
        unsigned char flag9 = ((unsigned char*)buf)[9];
        unsigned char flag8;
        if (((*(unsigned*)((char*)owner + 8) >> 0x15) & 1) == 0) {
            if (flag9 == 0x0f)
                flag8 = (unsigned char)shape->v24(buf[0], buf[1], 0);
            else
                flag8 = 0;
            inst->v18((char*)this - 8, buf, (char*)this + 0x234);
        } else {
            if (flag9 == 0x0f)
                flag8 = (unsigned char)shape->v24(buf[6], buf[7], 9);
            else
                flag8 = 9;
            inst->v2C((char*)this - 4, buf, (char*)this + 0x230);
        }
        inst->v10((char)flag8, (char*)this + 0x238);
        mFlags23c = 0xff;
    }
}

// ===========================================================================
// 0x00f62b70 -- cTerrainDistributeInfo default constructor
// ===========================================================================
// @ 0x00f62b70
// Constructor-shaped: original returns `this` in eax; declare a non-void return and return the
// pointer so cl keeps it live in eax instead of leaving the 0 fill value there.
unsigned __fastcall FUN_00f62b70(int* p) {
    ((float*)p)[1] = 0.1f;
    ((float*)p)[2] = kFXMaxFloat;
    p[0] = 0;
    ((float*)p)[3] = 1.0f;
    p[0xe] = 0;
    p[4] = 0; p[5] = 0; p[6] = 0; p[7] = 0; p[8] = 0; p[9] = 0;
    p[10] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0;
    return (unsigned)(size_t)p;
}

// ===========================================================================
// 0x00f62bc0 -- serialize a description (operator<<)
// ===========================================================================
// @ 0x00f62bc0
void __cdecl FUN_00f62bc0(int writer, int* d) {
    int v;
    v = d[0]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[1]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[2]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[3]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[4]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = (d[6] - d[5]) >> 4; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    int n = (d[6] - d[5]) >> 4;
    int off = 0;
    while (n > 0) {
        v = *(int*)(off + d[5]); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(int*)(d[5] + 4 + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(int*)(d[5] + 8 + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(unsigned char*)(d[5] + 0xc + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(unsigned char*)(d[5] + 0xd + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(unsigned char*)(d[5] + 0xe + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        off += 0x10; n--;
    }
}

// ===========================================================================
// 0x00f62d80 -- cTerrainDistributeEffectCommand constructor
// ===========================================================================
// @ 0x00f62d80
unsigned __fastcall FUN_00f62d80(int* p) {
    float fmax = kFXMaxFloat;
    p[1] = (int)&g_0145fd8c;      // secondary vtable
    p[2] = 0;
    p[0] = (int)&g_0145fd90;      // primary vtable
    int* q = p + 4;
    for (int i = 8; i >= 0; i--) {
        q[0] = 0;
        ((float*)q)[1] = 0.1f;
        ((float*)q)[2] = fmax;
        ((float*)q)[3] = 1.0f;
        q[0xe] = 0;
        q[4] = 0; q[5] = 0; q[6] = 0;
        q[7] = q[5]; q[8] = q[6]; q[9] = q[7]; q[10] = q[8]; q[0xb] = q[9]; q[0xc] = q[10]; q[0xd] = q[0xb];
        q += 0x10;
    }
    p[0x94] = 0; p[0x95] = 0; p[0x96] = 0;
    return (unsigned)(size_t)p;
}

// ===========================================================================
// 0x00f62e60 -- cTerrainDistributeDescription destructor
// ===========================================================================
// @ 0x00f62e60
void __fastcall FUN_00f62e60(cTerrainDistributeDescription* d) {
    int* p = (int*)((char*)d + 0xe8);          // &mLevel[5].mChildrenBegin
    for (int i = 4; i >= 0; i--) {
        int v = *(int*)((char*)p - 0x28);
        p = (int*)((char*)p - 0x28);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_del((void*)v);
    }
    d->mVtbl = (int)&g_013ef094;
}

// ===========================================================================
// 0x00f62ea0 -- cTerrainDistributeInfo::SetInfoFromProps
// ===========================================================================
// @ 0x00f62ea0
void cTerrainDistributeInfo::SetInfoFromProps(int idx, cPropertyList* props) {
    cTypeInfo* info = &mTypes[idx];

    // default cTypeInfo: {0, 0.1f, kFXMaxFloat, 1.0f, rest 0}
    cTypeInfo tmp;
    tmp.mpProps = 0;
    tmp.mMin = 0.1f;
    tmp.mMax = kFXMaxFloat;
    tmp.mHeight = 1.0f;
    tmp.mPad38 = 0;
    for (int i = 0; i < 5; ++i) {
        tmp.mKeys[i].mKey = 0;
        tmp.mKeys[i].mValue = 0;
    }
    *info = tmp;

    void* old = info->mpProps;
    if (props != old) {
        if (props != 0) props->AddRef();
        info->mpProps = props;
        if (old != 0) ((cPropertyList*)old)->Release();
    }

    int key[3] = { 0, 0, 0 };
    for (int i = 0; i < 5; ++i) {
        if (EA_GetPropertyAsKey(props, g_0148f1d4[i], key) && key[0] != 0x2ebcd6a6) {
            info->mKeys[i].mKey = key[0];
            info->mKeys[i].mValue = key[2];
        }
    }

    if (props != 0) {
        void* prop = 0;
        if (props->GetProperty(0x4057881, &prop) &&
            *(short*)((char*)prop + 0x12) == 0xd) {
            void* v = (*(unsigned char*)((char*)prop + 0x10) & 0x30) ? *(void**)prop : prop;
            info->mHeight = *(float*)v;
        }
    }
}

// ===========================================================================
// 0x00f63000 -- cTerrainDistributeDescription constructor
// ===========================================================================
// @ 0x00f63000
unsigned __fastcall FUN_00f63000(cTerrainDistributeDescription* d) {
    d->mVtbl = (int)&g_0148f288;
    d->mPad04 = 0;
    d->mFlags08 = 0;
    for (int i = 0; i < 5; ++i) {
        cLevelInfo* l = &d->mLevel[i];
        l->mChildrenBegin = 0;
        l->mChildrenEnd = 0;
        l->mChildrenCap = 0;
        l->mActiveDist = 0.0f;
        l->mChildActiveDist = 0.0f;
        l->mActiveFacing = 1.0f;
        l->mChildActiveFacing = 0.0f;
        l->mScale = 0.0f;
    }
    return (unsigned)(size_t)d;
}

// ===========================================================================
// 0x00f63120 -- SP::WriteDescription
// ===========================================================================
void __cdecl FUN_00f63120(int writer, int p) {
    int v = *(int*)(p + 8);
    EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    int q = p + 0xc;
    for (int i = 5; i != 0; i--) { FUN_00f62bc0(writer, (int*)q); q += 0x28; }
}

// ===========================================================================
// 0x00f63190 -- ArgScript::TerrainDistributeEffect constructor
// ===========================================================================
// @ 0x00f63190
unsigned __fastcall FUN_00f63190(cTerrainDistributeCommand* p) {
    ((cAppPropsFields*)p)->ctor();              // 0x0083cdd0 AppPropsFields ctor
    p->mVtbl = (int)&g_0148f28c;
    p->mHash34 = 0x33109bb;
    FUN_00f63000(&p->mDesc);
    p->mInstaller = 0;
    p->mpStrBegin = (int*)&g_01667bac;
    p->mpStrEnd = (int*)&g_01667bac;
    p->mStrCap = (int*)&g_01667bad;
    return (unsigned)(size_t)p;
}

// ===========================================================================
// 0x00f631e0 -- store a value then call a base init
// ===========================================================================
// @ 0x00f631e0
void __fastcall FUN_00f631e0(int self, int dummy, int v, int w) {
    (void)dummy; (void)w;
    *(int*)(self + 0x30) = v;
    FUN_0083c780(v, v);
}

// ===========================================================================
// 0x00f631f0 -- cTDDebugCommand::Execute
// ===========================================================================
// @ 0x00f631f0
void __fastcall FUN_00f631f0(int self, int dummy, cArguments* args) {
    (void)dummy;
    args->MainArguments(0);
    int tmp;
    args->OptionArguments("showLevels", 2);
    if (args->HasFlag("heights")) *(int*)(*(int*)(self + 0xc) + 0xc) |= 1;
    else                       *(int*)(*(int*)(self + 0xc) + 0xc) &= 0xfffffffe;
    if (args->HasFlag("types")) *(int*)(*(int*)(self + 0xc) + 0xc) |= 2;
    else                        *(int*)(*(int*)(self + 0xc) + 0xc) &= 0xfffffffd;
    (void)tmp;
    if (args->HasFlag("active")) { *(int*)(*(int*)(self + 0xc) + 0xc) |= 4; return; }
    *(int*)(*(int*)(self + 0xc) + 0xc) &= 0xfffffffb;
}

// ===========================================================================
// 0x00f63280 -- cTDLevelCommand::Execute (approximate)
// ===========================================================================
// @ 0x00f63280
void __fastcall FUN_00f63280(int self, int dummy, cArguments* args) {
    (void)dummy;
    int n = 0;
    int* a = ((cArguments3*)args)->MainArgsThree(&n, 0, 1);
    if (n > 0) {
        void* obj = *(void**)(self + 4);
        int v = VPTR(int, obj, 0x9c, int)(obj, a[0]);
        *(int*)(*(int*)(self + 0x30) + 0xd8) = v;
    } else {
        ++*(int*)(*(int*)(self + 0x30) + 0xd8);
    }
    int lvl = *(int*)(*(int*)(self + 0x30) + 0xd8);
    if (lvl >= 0 && lvl < 5) {
        void* obj = *(void**)(self + 4);
        VPTR(void, obj, 0x8c, int)(obj, self);
    }
}

// ===========================================================================
// 0x00f632f0 -- cTDDistanceCommand::Execute
// ===========================================================================
// @ 0x00f632f0
void __fastcall FUN_00f632f0(int self, int dummy, cArguments* args) {
    (void)dummy;
    int a = args->MainArguments(1);
    int d = *(int*)(self + 0xc);
    float f = (float)(*(int(__cdecl**)(int))(*(void**)((char*)*(int**)(self + 4) + 0x98)))(a);
    *(float*)(d + 0x10 + *(int*)(d + 0xd8) * 0x28) = f;
    int* o = args->OptionArguments("verticalWeight", 1);
    if (o) {
        d = *(int*)(self + 0xc);
        float g = (float)(*(int(__cdecl**)(int))(*(void**)((char*)*(int**)(self + 4) + 0x98)))(*o);
        *(float*)(d + 0x18 + *(int*)(d + 0xd8) * 0x28) = g;
    }
}

// ===========================================================================
// 0x00f63360 -- cTDFacingCommand::Execute
// ===========================================================================
// @ 0x00f63360
void __fastcall FUN_00f63360(int self, int dummy, cArguments* args) {
    (void)dummy;
    int* a = ((cArguments1*)args)->MainArgsOne(1);
    void* obj = *(void**)(self + 4);
    float f = VPTR(float, obj, 0x98, int)(obj, a[0]);
    int d = *(int*)(self + 0xc);
    *(float*)(d + *(int*)(d + 0xd8) * 0x28 + 0x1c) = f;
}

// ===========================================================================
// 0x00f633a0 -- ArgScript::TerrainDistributeEffect::OnRegister
// ===========================================================================
// @ 0x00f633a0
void cTerrainDistributeCommand::OnRegister(int parser, int state) {
    mState = (state != 0) ? (state - 0xc) : 0;
    ((cCommandBaseBase*)this)->BaseOnRegister(parser, state);   // 0x0083c780
    mInstaller = mState;
    ((cTextFont*)this)->SetUserData(&mHash34);      // 0x00fd9450 EA::Text::Font::SetUserData

    void* o;
    o = operator_new(0x10, "ArgScript/TDDebug", 0, 0, 0, 0);
    if (o != 0) {
        ((cCommandBaseCtor*)o)->ctor();
        *(int*)o = (int)&g_0148f2b0;
    } else {
        o = 0;
    }
    ((cCommandBase*)this)->AddChild(g_keyTDDebug, o);

    o = operator_new(0x34, "ArgScript/TDLevel", 0, 0, 0, 0);
    if (o != 0) {
        ((cAppPropsFields*)o)->ctor();
        *(int*)o = (int)&g_0148f2dc;
    } else {
        o = 0;
    }
    ((cCommandBase*)this)->AddChild(g_keyTDLevel, o);

    o = operator_new(0x10, "ArgScript/TDEffect", 0, 0, 0, 0);
    if (o != 0) {
        ((cCommandBaseCtor*)o)->ctor();
        *(int*)o = (int)&g_0148f300;
    } else {
        o = 0;
    }
    ((cCommandBase*)this)->AddChild(g_keyTDEffect, o);

    o = operator_new(0x10, "ArgScript/TDDistance", 0, 0, 0, 0);
    if (o != 0) {
        ((cCommandBaseCtor*)o)->ctor();
        *(int*)o = (int)&g_0148f318;
    } else {
        o = 0;
    }
    ((cCommandBase*)this)->AddChild(g_keyTDDistance, o);

    o = operator_new(0x10, "ArgScript/TDFacing", 0, 0, 0, 0);
    if (o != 0) {
        ((cCommandBaseCtor*)o)->ctor();
        *(int*)o = (int)&g_0148f340;
    } else {
        o = 0;
    }
    ((cCommandBase*)this)->AddChild(g_keyTDFacing, o);
}

// ===========================================================================
// 0x00f63650 -- SWARM_TerrainDistributeAddCommands
// ===========================================================================
// @ 0x00f63650
void __cdecl FUN_00f63650(int cmds, int* b) {
    (void)b;
    void* obj = operator_new(0x124, "ArgScript/TerrainDistributeEffect", 0, 0, 0, 0);
    
    (*(void(__cdecl**)(void*, int))(*(void**)((char*)*(void**)cmds + 0x14)))((void*)PTR_s_terrainDistribute, (int)obj);
}

// ===========================================================================
// 0x00f636f0 -- cTDEffectCommand::Execute
// ===========================================================================
// @ 0x00f636f0
void cTDEffectCommand::Execute(cArguments* args) {
    int* ma = (int*)args->MainArguments(1);
    cTDDistDesc* d = mpDesc;

    int id = ((cEffectsParser*)d->mpEffectsParser)->MapFindA(*ma);

    float lo = 0.0f;
    float hi = kFXMaxFloat;
    unsigned char type = 0xff;
    unsigned char resource = 0xff;
    unsigned char overrideSet = 0;

    int* hr = (int*)args->OptionArguments("heightRange", 2);
    if (hr != 0) {
        lo = VPTR(float, mpConverter, 0x98, int)(mpConverter, hr[0]);
        hi = VPTR(float, mpConverter, 0x98, int)(mpConverter, hr[1]);
    }
    int* tp = (int*)args->OptionArguments("type", 1);
    if (tp != 0)
        type = (unsigned char)EA_ParseEnum(*tp, (void*)0x148f1e8);
    int* rp = (int*)args->OptionArguments("resource", 1);
    if (rp != 0)
        resource = (unsigned char)EA_ParseEnum(*rp, (void*)0x148f240);
    int* op = (int*)args->OptionArguments("overrideSet", 1);
    if (op != 0)
        overrideSet = (unsigned char)VPTR(char, mpConverter, 0x9c, int)(mpConverter, *op);

    cTDEntry entry;
    entry.mId = id;
    entry.mLo = lo;
    entry.mHi = hi;
    entry.mType = type;
    entry.mResource = resource;
    entry.mOverride = overrideSet;
    entry.mPad0f = 0;

    cTDLevelBlock* blk = &d->mBlock[d->mLevelIndex];
    cTDEntry* e = (cTDEntry*)blk->mEnd;
    if (e < (cTDEntry*)blk->mCap) {
        blk->mEnd = (int)(e + 1);
        if (e != 0) *e = entry;
    } else {
        FUN_0092a100(e, &entry);
    }
}

// ===========================================================================
// 0x00f63850 -- ArgScript::TerrainDistributeEffect::OnEndBlock
// ===========================================================================
// @ 0x00f63850
void cTerrainDistributeCommand::OnEndBlock(char end) {
    if (end == 0) {
        cTerrainDistributeDescription* src = &mDesc;

        // fold level i's bounds into level i-1 (levels 4..1)
        for (int i = 4; i >= 1; --i) {
            cLevelInfo* blk = &src->mLevel[i];
            cLevelInfo* prev = &src->mLevel[i - 1];
            float a = blk->mActiveDist;
            float b = blk->mChildActiveDist;
            float m1 = (b > a) ? b : a;
            prev->mChildActiveDist = (m1 > 0.0f) ? (m1 + 100.0f) : 0.0f;
            if (prev->mActiveDist > 0.0f && prev->mChildActiveFacing == 0.0f)
                prev->mChildActiveFacing = 1.0f;
            float c = blk->mChildActiveFacing;
            float e = blk->mScale;
            float m2 = (e > c) ? e : c;
            prev->mScale = (m2 > 0.0f) ? (m2 + 0.1f) : 0.0f;
        }

        cTerrainDistributeDescription* neu =
            (cTerrainDistributeDescription*)operator_new(0xd4, "Swarm", 0, 0, 0, 0);
        if (neu != 0) {
            neu->mPad04 = 0;
            neu->mVtbl = (int)&g_0148f288;
            neu->mFlags08 = src->mFlags08;
            for (int i = 0; i < 5; ++i) {
                cLevelInfo* s = &src->mLevel[i];
                cLevelInfo* t = &neu->mLevel[i];
                t->mActiveDist = s->mActiveDist;
                t->mChildActiveDist = s->mChildActiveDist;
                t->mActiveFacing = s->mActiveFacing;
                t->mChildActiveFacing = s->mChildActiveFacing;
                t->mScale = s->mScale;
                int n = (s->mChildrenEnd - s->mChildrenBegin) >> 4;
                int p = 0;
                if (n != 0)
                    p = (int)operator_new(n << 4, "EASTL", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                        0xd1);
                t->mChildrenBegin = p;
                t->mChildrenEnd = p;
                t->mChildrenCap = p + (n << 4);
                int q = s->mChildrenBegin;
                while (q != s->mChildrenEnd) {
                    if (p != 0) {
                        *(int*)(p + 0x0) = *(int*)(q + 0x0);
                        *(int*)(p + 0x4) = *(int*)(q + 0x4);
                        *(int*)(p + 0x8) = *(int*)(q + 0x8);
                        *(int*)(p + 0xc) = *(int*)(q + 0xc);
                    }
                    p += 16;
                    q += 16;
                }
                t->mChildrenEnd = p;
            }
        }
        ((cDescInstaller*)(mState))->Install((void*)mpStrBegin, 0x2a, neu);
    }
    if (mpStrBegin != mpStrEnd) {
        *(char*)mpStrBegin = 0;
        mpStrEnd = mpStrBegin;
    }
}
