// Slice s00b27ee0 -- saved-game ".old" backup/restore helpers
// (planetRecords.pkp / planetscripts.pld / stars.db / GGEUserData.dat set).
//
// Reconstructed from the annotated disassembly + decompiles in
// work/match/scratch_s00b27ee0_cards.txt; MSVC 2008 /O2, thiscall members of the
// saved-game manager object (self in ecx).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

void operator delete(void*);

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);

// ---- globals ---------------------------------------------------------------
extern u8  DAT_015689ac;                    // 0x015689ac
extern const wchar_t* DAT_015689a8;         // 0x015689a8  -> L"*.spo"
extern u8  DAT_01654c08;                    // 0x01654c08
extern char DAT_013ec468[];                 // 0x013ec468  eastl::wstring
extern char DAT_0167df60[];                 // 0x0167df60  eastl::wstring

// ---- eastl::basic_string<wchar_t, eastl::allocator> (3 pointers) ------------
struct WStr {
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    u32      mAllocator;    // +0x0c  (stateless allocator kept as a member: object is 16 bytes)

    void AllocateSelf(i32 n);                                 // 0x00429760
    void RangeInitialize(const wchar_t* s);                   // 0x00579a90
    void CopyInit(const WStr& src);                           // 0x0056e2d0
    void Assign(const wchar_t* first, const wchar_t* last);    // 0x00423650
    void Substr(WStr* out, i32 pos, i32 n) const;             // 0x00453d20 (ret 0xc)

    WStr() {}

    WStr(const wchar_t* p) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        RangeInitialize(p);
    }

    WStr(const wchar_t* pBegin, const wchar_t* pEnd) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        i32 n = (i32)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, (unsigned)n * 2);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }

    ~WStr() throw() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin != 0) operator delete(mpBegin);
    }
};

extern WStr gDefaultSavedGameFilename;      // 0x0167df50

// ---- thiscall callbacks on engine singletons -------------------------------
struct StarManager {
    bool FUN_00ba9bc0();                    // 0x00ba9bc0 (0 args, ret)
    void FUN_00bb5640(const void* name);    // 0x00bb5640 (ret 4)
};

struct ModeObj {
    u8  mPad[0x20];
    void* mField20;
    void FUN_00b1e410(const void* p);       // 0x00b1e410 (ret 4)
};

// ---- engine / EAPd helpers -------------------------------------------------
extern "C" WStr* __cdecl PathJoin(WStr* out, const WStr* a, const wchar_t* b);  // 0x0057cba0
extern "C" WStr* __cdecl PathPick(WStr* out, const WStr* a, const WStr* b);     // 0x00688f00

extern "C" bool __cdecl EA_IO_File_Exists(const wchar_t* p);   // 0x00931fa0
extern "C" bool __cdecl EA_IO_File_Remove(const wchar_t* p);   // 0x00931fd0
extern "C" bool __cdecl EA_IO_File_Copy(const void* a, const void* b, bool overwrite);  // 0x00932030
extern "C" bool __cdecl EA_IO_File_Copy4(const wchar_t* a, const wchar_t* b, int c, int d);  // 0x00932b20
extern "C" u8   __cdecl EA_IO_File_Touch(const wchar_t* p, int flag);      // 0x00931f20
extern "C" bool __cdecl EA_IO_Dir_Exists(const wchar_t* p);                // 0x009322b0
extern "C" void __cdecl EA_IO_Dir_Remove(const wchar_t* p, int rec);       // 0x00932890
extern "C" void __cdecl EA_IO_Dir_Create(const wchar_t* p);                // 0x00932960
extern "C" void* __cdecl EA_IO_EntryFindFirst(const wchar_t* dir, const wchar_t* pat, int a, int b);  // 0x0092e730
extern "C" void* __cdecl EA_IO_EntryFindNext(void* h, int a);              // 0x0092e8e0
extern "C" void  __cdecl EA_IO_EntryFindFinish(void* h);                   // 0x0092e9b0

extern "C" void* __cdecl SP_StarManager();                        // 0x00b3d2a0 (0 args, ret)
extern "C" void* __cdecl FUN_00b3d320_n();                        // 0x00b3d320 (0 args, ret)
extern "C" void* __stdcall FUN_00b3d320(const void* p);           // 0x00b3d320 (ret 4 overload)
extern "C" void  __fastcall FUN_00b1e410(void* p);                // 0x00b1e410 (arg in ecx)
extern "C" int   __cdecl SP_GetCurrentGameMode();                 // 0x00b5b800

// ---- the saved-game manager ------------------------------------------------
struct GameModeSave {
    u8 mPad[0x48];                          // +0x00 .. +0x47 (0x44/0x47 used)

    void  GetPath(WStr* out);               // 0x00b27540
    void  FUN_00b279e0(const wchar_t* name);    // 0x00b279e0 (thiscall ret 4)

    void  FUN_00b27ee0(const wchar_t* name);    // 0x00b27ee0
    int   FUN_00b28070();                       // 0x00b28070
    u8    FUN_00b282e0();                       // 0x00b282e0
    u8    FUN_00b28750();                       // 0x00b28750
    void  FUN_00b28850(const WStr* name);       // 0x00b28850
    void  FUN_00b28990();                       // 0x00b28990
    u8    FUN_00b289e0();                       // 0x00b289e0
    int   FUN_00b28c20();                       // 0x00b28c20
};

// Copy of `path` with its last character (the trailing separator) dropped.
static void TrimTrailingSep(WStr& out, const WStr& path) {
    i32 n = (i32)(path.mpEnd - path.mpBegin);
    i32 m = n - 1;
    if ((u32)m < (u32)n)
        path.Substr(&out, 0, m);
    else
        out.CopyInit(path);
}

// =============================================================================
// @ 0x00b27ee0
void GameModeSave::FUN_00b27ee0(const wchar_t* name) {
    DAT_015689ac = 1;

    WStr nameStr(name);
    ((WStr*)&DAT_0167df60)->Assign(nameStr.mpBegin, nameStr.mpEnd);

    WStr path;
    GetPath(&path);

    WStr copy(path.mpBegin, path.mpEnd);
    WStr out;
    WStr* r = PathPick(&out, &copy, &nameStr);
    if (r != &copy)
        copy.Assign(r->mpBegin, r->mpEnd);

    if (EA_IO_File_Exists(copy.mpBegin)) {
        const wchar_t* e = name;
        while (*e != 0) ++e;
        gDefaultSavedGameFilename.Assign(name, e);
        ((ModeObj*)FUN_00b3d320_n())->FUN_00b1e410(&DAT_01654c08);
    }
}

// =============================================================================
// @ 0x00b28070
int GameModeSave::FUN_00b28070() {
    WStr path;
    GetPath(&path);

    StarManager* sm = (StarManager*)SP_StarManager();
    if (!sm->FUN_00ba9bc0())
        return 2;

    bool exists;
    {
        WStr base;
        TrimTrailingSep(base, path);
        WStr out;
        exists = EA_IO_Dir_Exists(PathJoin(&out, &base, L".old\\")->mpBegin);
    }
    if (!exists)
        return 0;

    {
        WStr base;
        TrimTrailingSep(base, path);
        WStr out;
        exists = EA_IO_File_Exists(PathJoin(&out, &base, L".old\\complete")->mpBegin);
    }
    if (exists)
        return 0;

    {
        WStr base;
        TrimTrailingSep(base, path);
        WStr out;
        exists = EA_IO_File_Exists(PathJoin(&out, &base, L".old\\valid")->mpBegin);
    }
    if (exists)
        return 2;
    return 1;
}

// =============================================================================
// @ 0x00b282e0
u8 GameModeSave::FUN_00b282e0() {
    WStr path;
    GetPath(&path);

    WStr oldDir;
    {
        WStr base;
        TrimTrailingSep(base, path);
        PathJoin(&oldDir, &base, L".old\\");
    }

    EA_IO_Dir_Remove(oldDir.mpBegin, 1);
    EA_IO_Dir_Create(oldDir.mpBegin);

    bool ok;
    {
        WStr dst;
        WStr src;
        ok = EA_IO_File_Copy(PathJoin(&src, &path, L"planetRecords.pkp")->mpBegin,
                             PathJoin(&dst, &oldDir, L"planetRecords.pkp")->mpBegin, true);
    }
    if (ok) {
        WStr dst;
        WStr src;
        ok = EA_IO_File_Copy(PathJoin(&src, &path, L"planetscripts.pld")->mpBegin,
                             PathJoin(&dst, &oldDir, L"planetscripts.pld")->mpBegin, true);
    }
    if (ok) {
        WStr dst;
        WStr src;
        ok = EA_IO_File_Copy(PathJoin(&src, &path, L"stars.db")->mpBegin,
                             PathJoin(&dst, &oldDir, L"stars.db")->mpBegin, true);
    }
    if (ok) {
        WStr dst;
        WStr src;
        ok = EA_IO_File_Copy(PathJoin(&src, &path, L"GGEUserData.dat")->mpBegin,
                             PathJoin(&dst, &oldDir, L"GGEUserData.dat")->mpBegin, true);
    }

    void* find = EA_IO_EntryFindFirst(path.mpBegin, L"*.spo", 0, 0);
    const wchar_t* entry = (const wchar_t*)find;
    while (entry != 0) {
        if (ok) {
            WStr dst;
            WStr src;
            ok = EA_IO_File_Copy(PathJoin(&src, &path, entry)->mpBegin,
                                 PathJoin(&dst, &oldDir, entry)->mpBegin, true);
        }
        entry = (const wchar_t*)EA_IO_EntryFindNext(find, 0);
    }
    EA_IO_EntryFindFinish(find);

    if (ok) {
        WStr marker;
        ok = EA_IO_File_Touch(PathJoin(&marker, &oldDir, L"valid")->mpBegin, 1) != 0;
    }
    return ok;
}

// =============================================================================
// @ 0x00b28750
u8 GameModeSave::FUN_00b28750() {
    WStr path;
    GetPath(&path);

    WStr dir;
    {
        WStr base;
        TrimTrailingSep(base, path);
        PathJoin(&dir, &base, L".old\\");
    }

    WStr marker;
    return EA_IO_File_Touch(PathJoin(&marker, &dir, L"complete")->mpBegin, 1);
}

// =============================================================================
// @ 0x00b28850
void GameModeSave::FUN_00b28850(const WStr* name) {
    WStr path;
    GetPath(&path);

    WStr sub;
    PathJoin(&sub, name, DAT_015689a8);

    WStr copy(sub.mpBegin, sub.mpEnd);
    WStr out;
    WStr* r = PathPick(&out, &path, &copy);
    if (r != &path)
        path.Assign(r->mpBegin, r->mpEnd);

    ((StarManager*)SP_StarManager())->FUN_00bb5640(name);

    if (EA_IO_File_Exists(path.mpBegin))
        EA_IO_File_Remove(path.mpBegin);
}

// =============================================================================
// @ 0x00b28990
void GameModeSave::FUN_00b28990() {
    FUN_00b279e0(gDefaultSavedGameFilename.mpBegin);

    int mode = SP_GetCurrentGameMode();

    void* p = FUN_00b3d320_n();
    *(void**)((char*)p + 0x20) = &DAT_01654c08;

    FUN_00b1e410(FUN_00b3d320((const void*)mode));

    gDefaultSavedGameFilename.Assign((const wchar_t*)&DAT_013ec468, (const wchar_t*)&DAT_013ec468);
    mPad[0x44] = 0;
}

// =============================================================================
// @ 0x00b289e0
u8 GameModeSave::FUN_00b289e0() {
    WStr path;
    GetPath(&path);

    EA_IO_Dir_Remove(path.mpBegin, 1);
    if (EA_IO_Dir_Exists(path.mpBegin))
        return 0;

    u8 result = 1;
    WStr oldDir;
    {
        WStr base;
        TrimTrailingSep(base, path);
        PathJoin(&oldDir, &base, L".old\\");
    }

    if (EA_IO_Dir_Exists(oldDir.mpBegin)) {
        WStr base;
        TrimTrailingSep(base, path);
        WStr tree;
        bool copied = EA_IO_File_Copy4(PathJoin(&tree, &base, L".old\\")->mpBegin,
                                       path.mpBegin, 1, 1);

        WStr marker;
        PathJoin(&marker, &path, L"dbreadinitiated");
        EA_IO_File_Remove(marker.mpBegin);

        WStr tmp;
        WStr* r = PathJoin(&tmp, &path, L"dbreadcompleted");
        if (r != &marker)
            marker.Assign(r->mpBegin, r->mpEnd);
        EA_IO_File_Remove(marker.mpBegin);

        result = copied && FUN_00b28750();
    } else {
        EA_IO_Dir_Create(path.mpBegin);
    }
    return result;
}

// =============================================================================
// @ 0x00b28c20
int GameModeSave::FUN_00b28c20() {
    int state = FUN_00b28070();

    WStr path;
    GetPath(&path);

    switch (state) {
    case 0:
        return 0;
    case 1:
        mPad[0x47] = 1;
        {
            WStr base;
            TrimTrailingSep(base, path);
            WStr dir;
            EA_IO_Dir_Remove(PathJoin(&dir, &base, L".old\\")->mpBegin, 1);
        }
        return 1;
    case 2:
        mPad[0x47] = 1;
        if (FUN_00b289e0())
            return 1;
        break;
    }
    return 2;
}
