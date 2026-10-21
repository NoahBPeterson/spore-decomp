// Slice s00f94660 -- 0x00f94660 .. 0x00f95540 (17 functions).
//
// Swarm / terrain-script cluster:
//   * SP::cTerrainResourceManager::SavePlanetDefinitions and its DatabasePackedFile
//     helper FUN_00f94660,
//   * Swarm::MapDescription serialization (FUN_00f94c50/cb0/d60) and the terrain
//     script arg-command,
//   * a GmeRefCount-derived component (cSequenceEffect/transform ops ctor/dtor and
//     the asset list management helpers 00f94f50..00f95540).
//
// Flags: /O2 /MD /Gy /TP

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef unsigned short wchar16;
typedef unsigned int   uintptr_t;

typedef void  (__thiscall *FnV)(void*);
typedef int   (__thiscall *FnI)(void*, int);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPI)(void*, int);
typedef void* (__thiscall *FnPII)(void*, int, int);
typedef int   (__thiscall *FnII)(void*, int, int);
typedef int   (__thiscall *FnIII)(void*, int, int, int);
typedef void  (__thiscall *FnVI)(void*, int);
typedef void  (__thiscall *FnVII)(void*, int, int);
typedef void  (__thiscall *FnVIII)(void*, int, int, int);
typedef int   (__thiscall *FnIV)(void*, int, int, int, int);
typedef int   (__thiscall *FnIV5)(void*, int, int, int, int, int);
typedef int   (__thiscall *FnIII3)(void*, int, int, int);
typedef int   (__thiscall *FnIIII)(void*, int, int, int);
typedef void  (__thiscall *FnVIII4)(void*, int, int, int);
typedef void* (__thiscall *FnPV)(void*, void*);
typedef void  (__thiscall *FnVV)(void*, void*);
typedef void  (__thiscall *FnVVV)(void*, void*, void*);

// ---------------------------------------------------------------------------
// externals (addresses in the trailing comment; declarations set conventions)
// ---------------------------------------------------------------------------
extern "C" void  FUN_006b4840();                       // 0x006b4840  async-save preamble
extern "C" void* FUN_0067dcd0();                       // 0x0067dcd0  ResourceMan::GetManager
extern "C" void* FUN_006b1f90(uint32_t);               // 0x006b1f90  SP_GetSaveArea
extern "C" void* FUN_0041e050(void*, const wchar16*, ...); // 0x0041e050  WStr_Format
extern "C" void* FUN_00926020(int, int, int, int, int, int); // 0x00926020  ZoneObject_new
extern "C" void* FUN_008d9f80(void*, int, int);              // 0x008d9f80  DatabasePackedFile ctor
extern "C" void  FUN_00f47380(void*);                  // 0x00f47380  operator delete
extern "C" void* FUN_00f473a0(uint32_t, const char*, int, int, int, int); // 0x00f473a0  EAAllocate
extern "C" void  FUN_00931fd0(const wchar16*);         // 0x00931fd0  EA::IO::File::Remove
extern "C" int   FUN_00931ff0(const wchar16*, const wchar16*, int); // 0x00931ff0  EA::IO::File::Move
extern "C" void* FUN_004c0410(void*, int);             // 0x004c0410  eastl string resize
extern "C" void  FUN_0093a780(void*, void*, int, int); // 0x0093a780  EA::IO::ReadInt32
extern "C" void  FUN_0093aa70(void*, const void*, int, int); // 0x0093aa70  EA::IO::WriteUint32
extern "C" void* __fastcall FUN_0083c800(void*);        // 0x0083c800  cCommandBase ctor (thiscall)
extern "C" void* FUN_00838320(void*, int);             // 0x00838320  cArguments::MainArguments
extern "C" int   FUN_008380b0(void*, const char*);     // 0x008380b0  cArguments::HasFlag
extern "C" void* FUN_0068d840(void*, const wchar16*, int, int); // 0x0068d840  SPKeyFromName
extern "C" void  FUN_00a6fd40(void*, void*, int, void*, int);   // 0x00a6fd40  cEffectsParser::AddAnonDescription
extern "C" int   FUN_0013cc50c(const wchar16*, const wchar16*); // 0x13cc50c  msvcr90!_wcsicmp
extern "C" void* FUN_0067de30();                       // 0x0067de30  SP::PropertyManager
extern "C" int   FUN_006237a0(void*);                  // 0x006237a0  cPropertyList::GetModificationCount
extern "C" int   FUN_006a0ae0(void*, int, void*, void*);   // 0x006a0ae0  eastl vector reserve
extern "C" void  FUN_006a0c30(void*, int, void*, void*);   // 0x006a0c30  GetPropertyAsTransformArray
extern "C" void  FUN_006a08b0(void*, int, void*, void*);   // 0x006a08b0  GetPropertyAsFloatArray
extern "C" void  FUN_006a0840(void*, int, void*, void*);   // 0x006a0840  GetPropertyAsUint32Array
extern "C" void* __fastcall FUN_00537dc0(void*, int, const void*); // 0x00537dc0  cSPTransformOps::Assign
extern "C" void  FUN_00533500(void*, void*);           // 0x00533500  eastl vector free range
extern "C" void  FUN_004b5440(void*);                  // 0x004b5440  sub-object dtor
extern "C" void  FUN_0041cb40(void*, void*);           // 0x0041cb40  Matrix3::Assign
extern "C" void  FUN_013cc50c();                       // placeholder (unused)

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern wchar16* gEmptyString16;                 // 0x01667bac  eastl::gEmptyString16
extern void*    gTerrainScriptName;             // 0x015b0fec  PTR_s_terrainScript

// ===========================================================================
// 0x00f94660 -- write one resource/database pair (transform + merge) into the
// packed file, driving the IO streams via their vtables.
// ===========================================================================
// @ 0x00f94660
extern "C" int FUN_00f94660(int self, void* db, int asset, int mode, int listArg)
{
    uint8_t local6 = 0;
    int local8 = 0;
    int localc = 0;
    if (!((FnIV5)(*(void***)db)[0x34 / 4])(db, asset, (int)&localc, 6, 1, mode))
        return 0;
    void* r = (void*)((FnP)(*(void***)localc)[0x18 / 4])((void*)localc);
    int ok = 0;
    if (r) {
        void* io = (void*)((FnP)(*(void***)r)[0x1c / 4])(r);
        FUN_004c0410(io, 0x20);
        if (io) {
            void* w = (void*)((FnP)(*(void***)localc)[0x18 / 4])((void*)localc);
            int wr = 0;
            if (w != 0)
                wr = ((FnIIII)(*(void***)w)[0x30 / 4])(w, 0, (int)(*(uint32_t*)io), 0);
            if (w == 0 || !wr)
                goto fail;
        }
        if (listArg) {
            ((FnV)(*(void***)listArg)[4 / 4])((void*)listArg);
        }
        // common finish: write the stream then read it back
        ((FnV)(*(void***)localc)[0x24 / 4])((void*)localc);
        if (localc) {
            void* t = (void*)localc;
            localc = 0;
            ((FnV)(*(void***)t)[8 / 4])(t);
        }
        if (!((FnIV5)(*(void***)db)[0x34 / 4])(db, asset, (int)&localc, 2, 1, 1))
            goto fail;
        void* r2 = (void*)((FnP)(*(void***)localc)[0x18 / 4])((void*)localc);
        ok = 0;
        if (!r2)
            goto fail;
        ((FnVV)(*(void***)r2)[0x38 / 4])(r2, (void*)(*(uint32_t*)io));
        ((FnV)(*(void***)localc)[0x24 / 4])((void*)localc);
        ok = 1;
    }
fail:
    if (localc)
        ((FnV)(*(void***)localc)[8 / 4])((void*)localc);
    return ok;
}

// ===========================================================================
// 0x00f94820 -- SP::cTerrainResourceManager::SavePlanetDefinitions
// ===========================================================================
// @ 0x00f94820
extern "C" uint8_t __fastcall FUN_00f94820(void* self, int, void* pathArg)
{
    struct Ctx {
        void*  mVecA[3];   //  0..0xb   (eastl vector<pair>?)
        void*  mVecB[3];   // 0xc..0x17
        void*  mVtbl;      // 0x18  = 0x1490124
        void*  mVtbl2;     // 0x1c
        void*  mWStrA[3];  // 0x20  (basic_string<wchar16>)
        void*  mWStrB[3];  // 0x2c
        void*  mWStrC[3];  // 0x38
        void*  pDb;        // 0x44  DatabasePackedFile*
    };
    Ctx* c = (Ctx*)((char*)self - 0x3c);   // real object base
    (void)c;

    FUN_006b4840();
    void* mgr = FUN_0067dcd0();
    void* saveArea = FUN_006b1f90(0x4729a47);
    void* stream = (void*)((FnP)(*(void***)saveArea)[0x28 / 4])(saveArea);

    void* mVecA[3] = { 0, 0, 0 };
    void* mVecB[3] = { 0, 0, 0 };
    void* mVtbl = (void*)0x1490124;
    void* handle = (void*)((FnPV)(*(void***)mgr)[0x38 / 4])(mgr, mVecB);
    (void)mVtbl;

    void* strA[3];
    strA[0] = gEmptyString16; strA[1] = gEmptyString16; strA[2] = (void*)0x1667bae;
    FUN_0041e050(strA, (const wchar16*)0x1490258, stream);  // L"%lstemp.pld"

    void* dbf = (void*)FUN_00926020(0x388, (int)"Terrain/ResourceManager/DatabasePackedFile", 0, 0, 0, 0);
    void* db;
    if (!dbf) {
        db = 0;
    } else {
        db = FUN_008d9f80(dbf, 0, 0);
        if (db)
            ((FnV)(*(void***)*(void**)((char*)db + 4))[0 / 4])((void*)db);
    }
    (void)handle;

    ((FnV)(*(void***)db)[4 / 4])(db);
    ((FnVV)(*(void***)db)[0x2c / 4])(db, strA[0]);
    ((FnVIII)(*(void***)db)[0x18 / 4])(db, 2, 2, 0);

    int n = (int)((FnIV)(*(void***)mgr)[0x48 / 4])(mgr, 0xb1b104, -1, 0, 0);
    int good = 0;
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            void* res = (void*)((FnPI)(*(void***)db)[0xc / 4])(db, *(uint32_t*)((char*)mVecB[0] + i * 4));
            void* cmp = (void*)((FnPI)(*(void***)db)[0xc / 4])(db, i);
            int mode = 0;
            if ((int)((FnP)(*(void***)db)[0xc / 4]) == (int)cmp || 1) {
                // best-effort: pick the smaller key
                mode = 0;
            }
            if (!FUN_00f94660((int)res, db, (int)cmp, mode, (int)mVecA))
                ++good;
        }
    }
    ((FnV)(*(void***)db)[0x1c / 4])(db);
    ((FnV)(*(void***)db)[8 / 4])(db);

    if (good != 0) {
        if (mVecA[0] && *(uint32_t*)((char*)mVecA[0] - 4))
            FUN_00f47380(mVecA[0]);
        ((FnV)(*(void***)*(void**)((char*)db + 4))[4 / 4])((void*)db);
        if (mVecB[0])
            FUN_00f47380(mVecB[0]);
        if (strA[0])
            FUN_00f47380(strA[0]);
        return 0;
    }

    void* strB[3];
    strB[0] = gEmptyString16; strB[1] = gEmptyString16; strB[2] = (void*)0x1667bae;
    FUN_0041e050(strB, (const wchar16*)0x1490238, (void*)(uintptr_t)0); // L"%lslastSave.pld"
    void* strC[3];
    strC[0] = gEmptyString16; strC[1] = gEmptyString16; strC[2] = (void*)0x1667bae;
    FUN_0041e050(strC, (const wchar16*)0x14901e4, strB[0], mVecA[2]);   // L"%ls%ls.pld"

    void* mine = (void*)((char*)self + 0x64 - 0x3c);
    (void)mine;
    void* seed = *(void**)((char*)self + 0x64);
    if (seed) {
        const wchar16* s1 = (const wchar16*)((FnP)(*(void***)seed)[0x28 / 4])(seed);
        if (FUN_0013cc50c(s1, gEmptyString16) == 0) {
            ((FnVIII)(*(void***)db)[0x50 / 4])(db, 0, (int)seed, 0);
            ((FnV)(*(void***)seed)[0x1c / 4])(seed);
            ((FnV)(*(void***)seed)[8 / 4])(seed);
            if (seed) {
                *(void**)((char*)self + 0x64) = 0;
                ((FnV)(*(void***)((char*)seed + 4))[4 / 4])((char*)seed + 4);
            }
        }
    }
    FUN_00931fd0((const wchar16*)strB[0]);
    int mv1 = FUN_00931ff0((const wchar16*)strB[0], (const wchar16*)mVecA[2], 1);
    uint8_t mv2 = (uint8_t)FUN_00931ff0((const wchar16*)strB[0], (const wchar16*)mVecA[2], 1);
    (void)mv1;
    if (!*(void**)((char*)self + 0x64))
        ((FnVI)(*(void***)self)[0x1c / 4])(self, (int)mVecA[2]);

    if (strA[0] && strA[0] != (void*)0x1667bac)
        FUN_00f47380(strA[0]);
    if (strB[0] && strB[0] != (void*)0x1667bac)
        FUN_00f47380(strB[0]);
    if (strC[0])
        FUN_00f47380(strC[0]);
    if (mVecA[0] && *(uint32_t*)((char*)mVecA[0] - 4))
        FUN_00f47380(mVecA[0]);
    ((FnV)(*(void***)*(void**)((char*)db + 4))[4 / 4])((void*)db);
    if (mVecB[0])
        FUN_00f47380(mVecB[0]);
    return mv2;
}

// ===========================================================================
// 0x00f94c50 -- read a Swarm::MapDescription from the stream.
// ===========================================================================
// @ 0x00f94c50
extern "C" void FUN_00f94c50(void* stream, void* p2, char* desc)
{
    uint32_t v;
    FUN_0093a780(stream, &v, 1, 0);
    *(uint32_t*)(desc + 8) = v & 0xf;
    FUN_0093a780(stream, desc + 0x10, 1, 0);
    FUN_0093a780(stream, desc + 0x14, 1, 0);
    FUN_0093a780(stream, desc + 0xc, 1, 0);
    (void)p2;
}

// ===========================================================================
// 0x00f94cb0 -- create + populate a Swarm::MapDescription.
// ===========================================================================
// @ 0x00f94cb0
extern "C" void* FUN_00f94cb0(void* stream, void* p2)
{
    char* d = (char*)FUN_00f473a0(0x18, (const char*)0x13f1fdc, 0, 0, 0, 0);
    char* r = 0;
    if (d) {
        void* volatile* p = (void* volatile*)d;
        p[1] = 0;
        p[0] = (void*)0x1453948;   // vtbl_Swarm::MapDescription
        p[2] = 0;
        p[3] = 0;
        p[4] = 0;
        p[5] = 0;
        r = d;
    }
    FUN_00f94c50(stream, p2, r);
    return r;
}

// ===========================================================================
// 0x00f94d00 -- SWARM_TerrainScriptAddCommands
// ===========================================================================
// @ 0x00f94d00
extern "C" void FUN_00f94d00(void* script)
{
    void* cmd = FUN_00f473a0(0x10, (const char*)0x14902b8, 0, 0, 0, 0);
    if (cmd) {
        FUN_0083c800(cmd);
        *(void**)((char*)cmd + 0) = (void*)0x14902a0;
        ((FnVVV)(*(void***)script)[0x18 / 4])(script, *(void**)0x15b0fec, cmd);
        return;
    }
    ((FnVVV)(*(void***)script)[0x18 / 4])(script, *(void**)0x15b0fec, 0);
}

// ===========================================================================
// 0x00f94d60 -- write a Swarm::MapDescription to the stream.
// ===========================================================================
// @ 0x00f94d60
extern "C" void FUN_00f94d60(void* stream, char* desc)
{
    uint32_t v;
    v = *(uint32_t*)(desc + 8);
    FUN_0093aa70(stream, &v, 1, 0);
    v = *(uint32_t*)(desc + 0x10);
    FUN_0093aa70(stream, &v, 1, 0);
    v = *(uint32_t*)(desc + 0x14);
    FUN_0093aa70(stream, &v, 1, 0);
    v = *(uint32_t*)(desc + 0xc);
    FUN_0093aa70(stream, &v, 1, 0);
}

// ===========================================================================
// 0x00f94df0 -- cSequenceEffectCommand::Execute
// ===========================================================================
// @ 0x00f94df0
extern "C" void __fastcall FUN_00f94df0(void* self, int, void* args)
{
    void* mainArgs = FUN_00838320(args, 1);

    char* d = (char*)FUN_00f473a0(0x18, "Swarm", 0, 0, 0, 0);
    char* desc = 0;
    if (d) {
        *(uint32_t*)(d + 4) = 0;
        *(void**)(d + 0) = (void*)0x1453948;
        *(uint32_t*)(d + 8) = 0;
        *(uint32_t*)(d + 0xc) = 0;
        *(uint32_t*)(d + 0x10) = 0;
        *(uint32_t*)(d + 0x14) = 0;
        ++*(uint32_t*)(d + 4);
        desc = d;
    }

    void* str[3];
    str[0] = gEmptyString16; str[1] = gEmptyString16; str[2] = (void*)0x1667bae;
    FUN_0041e050(str, (const wchar16*)0x13f3da0, *(void**)mainArgs);
    FUN_0068d840(desc + 0xc, (const wchar16*)str[0], 0, 0);

    if (FUN_008380b0(args, "loop"))
        *(uint32_t*)(desc + 8) |= 1;
    if (FUN_008380b0(args, "noOverlap"))
        *(uint32_t*)(desc + 8) |= 4;
    if (FUN_008380b0(args, "hardStop"))
        *(uint32_t*)(desc + 8) |= 4;
    if (FUN_008380b0(args, "hardStart"))
        *(uint32_t*)(desc + 8) |= 2;
    if (FUN_008380b0(args, "noStop"))
        *(uint32_t*)(desc + 8) |= 8;
    if (FUN_008380b0(args, "overlap"))
        *(uint32_t*)(desc + 8) |= 8;

    FUN_00a6fd40(*(void**)((char*)self + 0xc), args, 0x21, desc, 0);

    if (str[0] && str[0] != (void*)0x1667bac)
        FUN_00f47380(str[0]);
    if (desc) {
        if (--*(uint32_t*)(desc + 4) == 0) {
            *(uint32_t*)(desc + 4) = 1;
            ((FnVI)(*(void***)desc)[0 / 4])(desc, 1);
        }
    }
}

// ===========================================================================
// 0x00f94f50 -- set/clear an anim flag with optional reset.
// ===========================================================================
// @ 0x00f94f50
extern "C" void __fastcall FUN_00f94f50(char* self, int, int reset)
{
    if (*(uint8_t*)(self + 0x18) == 0) {
        *(uint8_t*)(self + 0x18) = 1;
        if (reset == 0 || *(uint8_t*)(self + 0x19) != 0) {
            *(float*)(self + 0x1c) = 0.0f;
            *(uint32_t*)(self + 0x20) = 0;
        }
        *(uint8_t*)(self + 0x19) = 0;
        return;
    }
    *(uint8_t*)(self + 0x18) = 0;
}

// ===========================================================================
// 0x00f94f80 -- has-pending-changes predicate.
// ===========================================================================
// @ 0x00f94f80
extern "C" int __fastcall FUN_00f94f80(int self, int)
{
    if (*(uint8_t*)(self + 0x18) == 0 && *(int*)(self + 0xa8) == *(int*)(self + 0xac))
        return 0;
    return 1;
}

// ===========================================================================
// 0x00f94fa0 -- refresh the property-derived arrays from the model.
// ===========================================================================
// @ 0x00f94fa0
extern "C" void __fastcall FUN_00f94fa0(int* self, int)
{
    int model = self[0x2f];
    int* vecHead = self + 0x31;
    self[0x32] = 0;
    *vecHead = 0;
    self[0x33] = 0;
    self[0x34] = 0;
    self[0x35] = 0;
    self[0x36] = 0;
    self[0x37] = 0;

    int mc = 0;
    if (*(int*)(model + 0x30))
        mc = FUN_006237a0(*(void**)(model + 0x30));
    self[0x30] = *(int*)(model + 0x34) + mc;

    int off = self[0x38] * 0x18;
    int* table = (int*)((char*)0x15b1028 + off);
    FUN_006a0ae0((void*)model, table[0], vecHead, self + 0x32);

    int* local = self;
    local = (int*)0;
    FUN_006a0c30((void*)self[0x2f], table[1], &local, self + 0x33);
    if (local != (int*)*vecHead)
        self[0x33] = 0;

    FUN_006a08b0((void*)self[0x2f], table[2], &local, self + 0x34);
    if (local != (int*)*vecHead)
        self[0x34] = 0;

    FUN_006a0840((void*)self[0x2f], table[3], &local, self + 0x35);
    if (local != (int*)*vecHead)
        self[0x35] = 0;

    FUN_006a08b0((void*)self[0x2f], table[4], &local, self + 0x36);
    if (local != (int*)*vecHead)
        self[0x36] = 0;

    if (self[0x38] == 0) {
        FUN_006a08b0((void*)self[0x2f], table[5], &local, self + 0x37);
        if (local != (int*)*vecHead)
            self[0x37] = 0;
    }

    if (self[8] != 0 && (int)*vecHead <= self[8])
        ((FnVI)(*(void***)self)[0xc / 4])(self, 1);
}

// ===========================================================================
// 0x00f95150 -- reload the property list from the model and refresh.
// ===========================================================================
// @ 0x00f95150
extern "C" void __fastcall FUN_00f95150(char* self, int, int a2, int a3, int a4)
{
    if ((*(uint32_t*)(*(int*)(self + 0xc) + 8) >> 1 & 1) != 0)
        *(uint32_t*)(self + 0x9c) = 1;
    if ((*(uint32_t*)(*(int*)(self + 0xc) + 8) >> 2 & 1) != 0)
        *(uint32_t*)(self + 0xa0) = 1;
    *(int*)(self + 0x10) = a2;
    *(int*)(self + 0x14) = a4;

    void* pm = FUN_0067de30();
    char* slot = self + 0xbc;
    int old = *(int*)slot;
    if (old) {
        *(int*)slot = 0;
        ((FnV)(*(void***)old)[4 / 4])((void*)old);
    }
    int ok = ((FnIV)(*(void***)pm)[0x2c / 4])(pm,
                 *(int*)(*(int*)(self + 0xc) + 0xc),
                 *(int*)(*(int*)(self + 0xc) + 0x14),
                 (int)slot, 0);
    if (ok)
        FUN_00f94fa0((int*)self, 0);
}

// ===========================================================================
// 0x00f951e0 -- assign the two transform ops and refresh them.
// ===========================================================================
// @ 0x00f951e0
extern "C" void __fastcall FUN_00f951e0(char* self, int, int a2, int a3)
{
    char* op1 = self + 0x2c;
    char* op2 = self + 0x64;
    FUN_00537dc0(op1, 0, (const void*)a2);
    FUN_00537dc0(op2, 0, (const void*)a3);
    int ud = *(int*)(self + 0xa4);
    if (ud) {
        ((FnVV)(*(void***)ud)[0x18 / 4])((void*)ud, op1);
        ((FnVV)(*(void***)ud)[0x14 / 4])((void*)ud, op2);
    }
}

// ===========================================================================
// 0x00f95230 -- reload from an args descriptor (opcode 6).
// ===========================================================================
// @ 0x00f95230
extern "C" int __fastcall FUN_00f95230(char* self, int, int code, int* desc)
{
    if (code != 6)
        return 0;
    *(uint32_t*)(self + 0xc4) = 0;
    *(int*)(self + 0xe0) = desc[2];

    void* pm = FUN_0067de30();
    char* slot = self + 0xbc;
    int old = *(int*)slot;
    if (old) {
        *(int*)slot = 0;
        ((FnV)(*(void***)old)[4 / 4])((void*)old);
    }
    int ok = ((FnIV)(*(void***)pm)[0x2c / 4])(pm, desc[0], desc[1], (int)slot, 0);
    if (ok)
        FUN_00f94fa0((int*)self, 0);
    return 1;
}

// ===========================================================================
// 0x00f952b0 -- constructor of the GmeRefCount-derived component.
// ===========================================================================
// @ 0x00f952b0
extern "C" void* __fastcall FUN_00f952b0(char* self, int, int a2)
{
    *(void**)(self + 4) = (void*)0x13ef094;
    *(uint32_t*)(self + 8) = 0;
    *(int*)(self + 0xc) = a2;
    *(uint32_t*)(self + 0x1c) = 0;
    *(uint32_t*)(self + 0x24) = 0;
    *(void**)(self + 0) = (void*)0x1490308;
    *(void**)(self + 4) = (void*)0x1490304;
    *(uint32_t*)(self + 0x10) = 0;
    *(uint32_t*)(self + 0x14) = 0;
    *(uint8_t*)(self + 0x18) = 0;
    *(uint32_t*)(self + 0x20) = 0;
    *(uint8_t*)(self + 0x19) = 1;
    *(uint8_t*)(self + 0x28) = 1;
    *(uint16_t*)(self + 0x2c) = 0;
    *(uint16_t*)(self + 0x2e) = 0;
    *(uint32_t*)(self + 0x30) = *(uint32_t*)0x16c9da4;
    *(uint32_t*)(self + 0x34) = *(uint32_t*)0x16c9da8;
    *(uint32_t*)(self + 0x38) = *(uint32_t*)0x16c9dac;
    *(uint32_t*)(self + 0x3c) = *(uint32_t*)0x1485720;
    FUN_0041cb40(self + 0x40, (void*)0x16c9db0);
    *(uint16_t*)(self + 0x66) = 0;
    *(uint16_t*)(self + 0x64) = 0;
    *(uint32_t*)(self + 0x68) = *(uint32_t*)0x16c9da4;
    *(uint32_t*)(self + 0x6c) = *(uint32_t*)0x16c9da8;
    *(uint32_t*)(self + 0x70) = *(uint32_t*)0x16c9dac;
    *(uint32_t*)(self + 0x74) = *(uint32_t*)0x1485720;
    FUN_0041cb40(self + 0x78, (void*)0x16c9db0);
    *(uint32_t*)(self + 0x9c) = 0;
    *(uint32_t*)(self + 0xa0) = 0;
    *(uint32_t*)(self + 0xa4) = 0;
    *(uint32_t*)(self + 0xa8) = 0;
    *(uint32_t*)(self + 0xac) = 0;
    *(uint32_t*)(self + 0xb0) = 0;
    *(uint32_t*)(self + 0xbc) = 0;
    *(uint32_t*)(self + 0xc0) = 0;
    *(uint32_t*)(self + 0xc4) = 0;
    *(uint32_t*)(self + 0xc8) = 0;
    *(uint32_t*)(self + 0xcc) = 0;
    *(uint32_t*)(self + 0xd0) = 0;
    *(uint32_t*)(self + 0xd4) = 0;
    *(uint32_t*)(self + 0xd8) = 0;
    *(uint32_t*)(self + 0xe0) = 0;
    return self;
}

// ===========================================================================
// 0x00f95430 -- destructor of the GmeRefCount-derived component.
// ===========================================================================
// @ 0x00f95430
extern "C" void* __fastcall FUN_00f95430(char* self, int, uint8_t freeFlag)
{
    *(void**)(self + 0) = (void*)0x1490308;
    *(void**)(self + 4) = (void*)0x1490304;
    int p = *(int*)(self + 0xbc);
    if (p) {
        ((FnV)(*(void***)p)[4 / 4])((void*)p);
    }
    FUN_004b5440(self + 0xa8);
    int q = *(int*)(self + 0xa4);
    if (q) {
        ((FnV)(*(void***)q)[4 / 4])((void*)q);
    }
    *(void**)(self + 0) = (void*)0x13f21d4;
    *(void**)(self + 4) = (void*)0x13ef094;
    if (freeFlag & 1)
        FUN_00f47380(self);
    return self;
}

// ===========================================================================
// 0x00f95490 -- swap/attach the user-data component and notify list members.
// ===========================================================================
// @ 0x00f95490
extern "C" void __fastcall FUN_00f95490(char* self, int, int newUd)
{
    int ud = *(int*)(self + 0xa4);
    if (ud) {
        ((FnVI)(*(void***)ud)[0xc / 4])((void*)ud, newUd);
        int cur = *(int*)(self + 0xa4);
        if (cur) {
            *(uint32_t*)(self + 0xa4) = 0;
            ((FnV)(*(void***)cur)[4 / 4])((void*)cur);
        }
    }
    if (newUd) {
        char* vec = self + 0xa8;
        if (*(int*)vec != *(int*)(self + 0xac)) {
            unsigned n = (unsigned)(*(int*)(self + 0xac) - *(int*)vec) >> 2;
            for (unsigned i = 0; i < n; ++i) {
                int el = *(int*)(*(int*)vec + i * 4);
                if (((FnI)(*(void***)el)[0x10 / 4])((void*)el, newUd))
                    ((FnVI)(*(void***)el)[0xc / 4])((void*)el, newUd);
            }
            FUN_00533500((void*)*(int*)vec, (void*)*(int*)(self + 0xac));
        }
    }
    *(uint8_t*)(self + 0x18) = 0;
}

// ===========================================================================
// 0x00f95540 -- compact the list, keeping only the "ready" members.
// ===========================================================================
// @ 0x00f95540
extern "C" void __fastcall FUN_00f95540(char* self, int)
{
    char* vec = self + 0xa8;
    unsigned n = (unsigned)(*(int*)(self + 0xac) - *(int*)vec) >> 2;
    unsigned w = 0;
    for (unsigned i = 0; i < n; ++i) {
        int el = *(int*)(*(int*)vec + i * 4);
        if (((FnI)(*(void***)el)[0x10 / 4])((void*)el, 0)) {
            if (w < i) {
                int* arr = *(int**)vec;
                int cur = arr[i];
                int old = arr[w];
                if (cur != old) {
                    if (cur)
                        ((FnV)(*(void***)cur)[0 / 4])((void*)cur);
                    arr[w] = cur;
                    if (old)
                        ((FnV)(*(void***)old)[4 / 4])((void*)old);
                }
            }
            ++w;
        }
    }
    FUN_00533500((void*)(*(int*)vec + w * 4), (void*)*(int*)(self + 0xac));
}
