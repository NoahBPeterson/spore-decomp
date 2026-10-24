// slice s00e4ba40 = 0x00e4ba40..0x00e4c8c0
// SP Simulator app-data runtime: the "magic command" context stack, the app-data
// globals (field map / tag map), the .cel catalog reader and the ArgScript field
// parsing helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Notation: `// @ 0x<va>` markers above each function; helper declarations carry
// the retail address of the callee.

typedef unsigned int   uint;
typedef unsigned char  u8;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// allocator / low-level services
// ---------------------------------------------------------------------------
extern char g_allocName[];   // 0x013ebb38  allocation category string
extern char g_allocSim[];    // 0x013f09b4  "Simulator"
extern char g_allocEASTL[];  // 0x013f2150  ".../EASTL/allocator.h"
extern char g_emptyStr[];    // 0x01667bac  ?gEmptyString16@eastl@@3PA_WA  (shared empty)
extern char g_emptyStr1[];   // 0x01667bad  &g_emptyStr + 1
extern char g_fmtPctS[];     // 0x013fc850

void* EAAllocate(uint size, const char* cat, int a, int b, const char* file, int line); // 0x00f473a0
void  operator_delete_array(void* p);      // 0x00f47380
void  memcpy_(void* d, const void* s, uint n);   // 0x011e0744
void  memset_(void* d, int v, uint n);           // 0x011e073e
uint  FNVHash(const void* s, uint seed, int mode); // 0x00932e80
void  DoInsertCell(void* at, void* v);           // 0x00a80dd0  SimpleVector<CellData*>::DoInsertValue
void* NewMapNode(void* map, void* pos, int key); // 0x00b1c3e0  map<int,string>::node alloc/insert
int   atoi_(const char* s);                      // 0x011e0e4e
char* strchr_(const char* s, int c);             // 0x011e0f2c
void  FUN_00e82280(void);                        // 0x00e82280
void  FUN_00e82490(void);                        // 0x00e82490
char  FUN_00e4b870(void);                        // 0x00e4b870
void* ZoneObjectNew(int size, const char* name, int a, int b, int c, int d); // 0x00926020
void  FUN_00e4b390(void* h);                     // 0x00e4b390  SP::sFileInfo
void* FUN_00b1c220(void);                        // 0x00b1c220  map<string,int>::operator[]
void  FUN_00a80dd0(void* a, void* b);            // 0x00a80dd0
void  FUN_00e4a8a0(void);                        // 0x00e4a8a0
void* FUN_009289f0(uint a, uint b, uint c, uint d, uint e, uint f); // 0x009289f0  cSPMemPool::LockedAlloc
void* FUN_00b721d0(uint key);                    // 0x00b721d0
void  NukeTagMap(void* root);                    // 0x00e84940  map<string,cSPUILayout*>::DoNukeSubtree

// ---------------------------------------------------------------------------
// eastl::basic_string<char>  (begin/end/capacity)
// ---------------------------------------------------------------------------
struct EaString {
    char* mpBegin_00;    // +0x00
    char* mpEnd_04;      // +0x04
    char* mpCap_08;      // +0x08
    void  sprintf_(const char* fmt, ...);       // 0x00472fe0
    void  assign(const void* first, const void* last); // 0x00454cb0
    void  SetEmpty(void) { mpBegin_00 = g_emptyStr; mpEnd_04 = g_emptyStr; mpCap_08 = g_emptyStr1; }
    // free the owned buffer when it is not the shared empty sentinel
    void  FreeIfOwned(void) {
        if (mpCap_08 - mpBegin_00 > 1 && mpBegin_00 != 0)
            operator_delete_array(mpBegin_00);
    }
};

struct EaStringW {                     // eastl::basic_string<wchar_t>
    u16* mpBegin_00;
    u16* mpEnd_04;
    u16* mpCap_08;
    void  sprintf_w(const u16* fmt, ...);       // 0x0041e050  WStr_Format
    void  FreeIfOwned(void) {
        if (mpEnd_04 - mpBegin_00 > 2 && mpBegin_00 != 0)
            operator_delete_array(mpBegin_00);
    }
};

// ---------------------------------------------------------------------------
// the app-data globals block  (0x016ad060 holds the pointer)
// ---------------------------------------------------------------------------
struct MapBase {                        // rbtree map initialised at +4
    uint mData_00[7];               // +0x00 .. +0x1b
    void  init(uint a, uint b);         // 0x00b72080
    void* find(uint key);               // 0x00b721d0
};

struct MapStrInt {                      // eastl::map<eastl::string,int>
    void*    mpvptr_00;                 // +0x00
    void*    mAnchorL_04;               // +0x04
    void*    mAnchorR_08;               // +0x08
    void*    mRoot_0c;                  // +0x0c  anchor.parent
    u8       mColor_10;                 // +0x10
    u8       mPad_11[3];                // +0x11
    int      mnSize_14;                 // +0x14
    uint     mPad_18;                   // +0x18
    int*  at(const EaString* key);          // 0x00b1c220  operator[]
    void* find(void** out, const void* key); // 0x00b20930  ?Find@MapStrFind
    void  NukeSubtree(void* root);          // 0x00e84940  DoNukeSubtree
};

struct SimpleVec {                      // SimpleVector<void*> (begin/end/capacity)
    void** mpBegin_00;                  // +0x00
    void** mpEnd_04;                    // +0x04
    void** mpCap_08;                    // +0x08
    void   clear(void);                 // 0x00743b50  ?VecClear@cModelWorld
};

struct cSPAppDataGlobals {
    void*      mpResource_00;           // +0x00
    MapBase    mMap_04;                 // +0x04
    void*      mpParser_20;             // +0x20
    void*      mpArg_24;                // +0x24
    MapStrInt  mFieldMap_28;            // +0x28
    uint   mPad_44;                 // +0x44
    SimpleVec  mPoolList_48;            // +0x48
    uint   mTail_54;
};

extern cSPAppDataGlobals* gspAppDataGlobals;   // 0x016ad060

// a pointer vector used by the runtime-global app-data list
extern void** g_appDataBegin;   // 0x016ad100
extern void** g_appDataEnd;     // 0x016ad104
extern void** g_appDataCap;     // 0x016ad108
extern void** g_appDataList;    // 0x016ad100

// ---------------------------------------------------------------------------
// Simulator object graph
// ---------------------------------------------------------------------------
struct TypeDesc;
struct FieldRec {                       // 0x28-byte field descriptor inside a TypeDesc
    uint mHash_00;                  // +0x00
    uint mNameHash_04;              // +0x04
    int      mOffset_08;                // +0x08  sentinel -1 terminates the list
    uint mFlags_0c;                 // +0x0c
    uint mPad_10[2];                // +0x10
    uint mPad_18[4];                // +0x18
};
struct TypeDesc {
    uint  mId_00;                   // +0x00
    FieldRec* mpFields_04;              // +0x04
    uint  mPad_08[2];               // +0x08
};
struct Ctx {
    uint  mPad_00[4];               // +0x00
    TypeDesc* mpType_10;                // +0x10
    uint  mPad_14[9];               // +0x14
};

struct cCtxVec {
    void** mpBegin_04;
    void** mpEnd_08;
    void** mpCap_0c;
};

struct CtxVec {
    void** mpBegin_00;
    void** mpEnd_04;
    void** mpCap_08;
    void   DoInsertValue(void** pEnd, void* const& v);  // 0x00a80dd0  SimpleVector::DoInsertValue
};

struct cResourceWriteLock {
    void* mpHandle_00;                  // +0x00
    void  Release(void);                // 0x00e4b170
};

struct cMyMagicCommand {
    void*  mpVptr_00;                   // +0x00
    void** mpVecBegin_04;               // +0x04
    void** mpVecEnd_08;                 // +0x08
    void** mpVecCap_0c;                 // +0x0c
    uint mPad_10[3];                // +0x10 .. +0x1b
    cResourceWriteLock mLock_1c;        // +0x1c
    uint mPad_20[31];               // +0x20 .. +0x9b
    uint mFlag_9c;                  // +0x9c
    cMyMagicCommand* Command(void* field);   // 0x00e4ba40
    void* Destroy(uint flags);               // 0x00e4bad0  scalar deleting dtor
    void  Execute(void* args);               // 0x00e4c730
};

struct SimObj;
struct mCellData;

// ===========================================================================
// @ 0x00e4ba40  thiscall: push the field descriptor for the current context's type
// ===========================================================================
cMyMagicCommand* cMyMagicCommand::Command(void* field)
{
    Ctx* top = (Ctx*)this->mpVecEnd_08[-1];
    FieldRec* rec = top->mpType_10->mpFields_04;
    uint hash = FNVHash(field, 0x811c9dc5, 1);
    FieldRec* found = 0;
    if (rec->mOffset_08 != -1) {
        for (;;) {
            if (rec->mNameHash_04 == hash) { found = rec; break; }
            rec = (FieldRec*)((char*)rec + 0x28);
            if (rec->mOffset_08 == -1) { found = 0; break; }
        }
    }
    if (found == 0) return 0;
    CtxVec* v = (CtxVec*)((char*)this + 4);
    if (v->mpEnd_04 < v->mpCap_08) {
        void** e = v->mpEnd_04;
        v->mpEnd_04 = e + 1;
        if (e) *e = found;
    } else {
        v->DoInsertValue(v->mpEnd_04, found);
    }
    return this;
}

// ===========================================================================
// @ 0x00e4bad0  thiscall: scalar deleting destructor of cMyMagicCommand
// ===========================================================================
void* cMyMagicCommand::Destroy(uint flags)
{
    this->mpVptr_00 = (void*)0x148256c;
    this->mLock_1c.Release();
    void* buf = this->mpVecBegin_04;
    if (buf != 0 && *(int*)((char*)buf - 4) != 0)
        operator_delete_array(buf);
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// ===========================================================================
// @ 0x00e4bb10  free every pooled object in the global app-data list
// ===========================================================================
void FUN_00e4bb10(void)
{
    void** begin = g_appDataBegin;
    void** end = g_appDataEnd;
    if (begin != end) {
        do {
            void* obj = *begin;
            void** b = *(void***)((char*)obj + 4);
            while (b != *(void***)((char*)obj + 8)) {
                operator_delete_array(*b);
                ++b;
            }
            *(uint*)((char*)obj + 0x9c) = 0;
            (*(void(__thiscall**)(void*, int))(*(int*)obj + 0x20))(obj, 1);
            ++begin;
            end = g_appDataEnd;
        } while (begin != end);
        begin = g_appDataBegin;
    }
    memcpy_(begin, end, 0);
    int n = (int)(end - begin);
    g_appDataEnd = end - n;
}

// ===========================================================================
// @ 0x00e4bc70  clear the global tag map (string -> cSPUILayout*)
// ===========================================================================
void FUN_00e4bc70(void)
{
    cSPAppDataGlobals* g = gspAppDataGlobals;
    MapStrInt* map = &g->mFieldMap_28;
    map->NukeSubtree(map->mRoot_0c);
    map->mAnchorR_08 = &map->mAnchorL_04;
    map->mAnchorL_04 = &map->mAnchorL_04;
    map->mRoot_0c    = 0;
    map->mColor_10   = 0;
    map->mnSize_14   = 0;
}

// ===========================================================================
// @ 0x00e4bca0  build a CellData for the current context and push it
// ===========================================================================
void FUN_00e4bca0(void* param_1, void* param_2)
{
    cMyMagicCommand* cmd = (cMyMagicCommand*)EAAllocate(0xa0, g_allocSim, 0, 0, 0, 0);
    if (cmd != 0) {
        cmd->mpVptr_00     = (void*)0x148256c;
        cmd->mpVecBegin_04 = 0;
        cmd->mpVecEnd_08   = 0;
        cmd->mpVecCap_0c   = 0;
        cmd->mFlag_9c      = 0;
    } else {
        cmd = 0;
    }
    void* item = EAAllocate(0x28, g_allocSim, 0, 0, 0, 0);
    *(void**)((char*)item + 0x10) = param_2;
    *(uint*)((char*)item + 0x14) = 0;
    *(uint*)((char*)item + 0x08) = 0;
    void** end = cmd->mpVecEnd_08;
    if (end < cmd->mpVecCap_0c) {
        cmd->mpVecEnd_08 = end + 1;
        if (end) *end = item;
    } else {
        DoInsertCell(&cmd->mpVecEnd_08, &item);
    }
    (*(void(__thiscall**)(void*, void*, void*))(*(int*)param_1 + 0x14))(param_1, *(void**)param_2, cmd);
    if (g_appDataEnd < g_appDataCap) {
        void** slot = g_appDataEnd;
        g_appDataEnd = slot + 1;
        if (slot) *slot = cmd;
    } else {
        DoInsertCell(&g_appDataEnd, &cmd);
        g_appDataEnd = g_appDataEnd;
    }
}

// ===========================================================================
// @ 0x00e4bd70  walk the global app-data list and reset each entry
// ===========================================================================
void FUN_00e4bd70(void)
{
    void* p = *(void**)0x16ad064;
    while (p != 0) {
        void** list = *(void***)0x16ad060;
        FUN_00e4bca0(list[8], p);
        p = *(void**)((char*)p + 0x28);
    }
}

// ===========================================================================
// @ 0x00e4bda0  thiscall: eastl::map<int,string>::operator[]
// ===========================================================================
int* MapStrInt::at(const EaString* key)
{
    void** head = &this->mAnchorL_04;
    void** pos  = head;
    void** root = this->mRoot_0c ? (void**)this->mRoot_0c : 0;
    (void)root;
    u8* node = (u8*)this->mRoot_0c;
    int k = *(int*)key;
    while (node) {
        if (*(int*)(node + 0x10) < k) {
            node = *(u8**)node;
        } else {
            pos = (void**)node;
            node = *(u8**)(node + 4);
        }
    }
    if (pos == head || k < *(int*)((char*)pos + 0x10)) {
        EaString tmp;
        tmp.SetEmpty();
        void* v = FUN_00b1c220();
        (void)v;
        u8* n = (u8*)NewMapNode(this, pos, k);
        pos = (void**)n;
    }
    return (int*)((char*)pos + 0x14);
}

// ===========================================================================
// @ 0x00e4be50  intern a C string into the global string table
// ===========================================================================
void* FUN_00e4be50(const char* s)
{
    if (s == 0) return 0;
    uint hash = FNVHash(s, 0x811c9dc5, 1);
    const char* p = s;
    const char* q = s + 1;
    do { char c = *p; ++p; } while (*(p - 1) != 0);
    uint len = (uint)(p - q);
    char* dst;
    if (len + 1 > 1) {
        dst = (char*)EAAllocate(len + 1, g_allocEASTL, 0, 0, g_allocName, 0xd1);
    } else {
        dst = g_emptyStr;
    }
    memcpy_(dst, s, len);
    char* endp = dst + len;
    *endp = 0;
    EaString key;
    key.mpBegin_00 = dst;
    key.mpEnd_04 = endp;
    key.mpCap_08 = 0;
    int* slot = gspAppDataGlobals->mFieldMap_28.at(&key);
    (void)hash;
    if (slot != (int*)((char*)&g_emptyStr)) {
        // assign the key into the map node's string
        ((EaString*)((char*)slot))->assign(dst, endp);
    }
    if (len + 1 > 1 && dst != 0) operator_delete_array(dst);
    return (void*)hash;
}

// ===========================================================================
// @ 0x00e4bf30  SP::DebugNameFromSPID
// ===========================================================================
const char* DebugNameFromSPID(int spid)
{
    if (spid == 0) {
        memcpy_((void*)0x16acf60, "<null key>", 0xc);
    }
    void* out;
    void* found = gspAppDataGlobals->mFieldMap_28.find(&out, &spid);
    if (*(void**)found == (void*)((char*)gspAppDataGlobals + 0x2c)) {
        memcpy_((void*)0x16acf60, "<unknown key>", 0xe);
        return (const char*)0x16acf60;
    }
    EaString* v = (EaString*)gspAppDataGlobals->mFieldMap_28.at((const EaString*)&spid);
    char* src = v->mpBegin_00;
    char* dst = (char*)0x16acf60;
    char c;
    do { c = *src; *dst++ = c; ++src; } while (c != 0);
    return (const char*)0x16acf60;
}

// ===========================================================================
// @ 0x00e4bff0  store an int under a formatted key in the field map
// ===========================================================================
void FUN_00e4bff0(const char* key, int value)
{
    struct { EaString s; uint pad_0c; } frame;
    EaString& s = frame.s;
    s.SetEmpty();
    s.sprintf_(g_fmtPctS, key);
    int* slot = gspAppDataGlobals->mFieldMap_28.at(&s);
    *slot = value;
    s.FreeIfOwned();
}

// ===========================================================================
// @ 0x00e4c060  SP::sAppDataCompile
// ===========================================================================
char SP_sAppDataCompile(void* layout, void* arg)
{
    cSPAppDataGlobals* g = gspAppDataGlobals;
    void* parser = g->mpParser_20;
    (*(void(__thiscall**)(void*, int))(*(int*)parser + 0x10))(parser, 0);
    EaString s;
    s.SetEmpty();
    s.sprintf_("%S%S", (char*)layout + 0x200, (void*)0);
    g->mpArg_24 = arg;
    char ok = (*(char(__thiscall**)(void*, const char*))(*(int*)parser + 0x48))(parser, g_emptyStr);
    g->mpArg_24 = 0;
    if (!ok) {
        s.FreeIfOwned();
        return 0;
    }
    FUN_00e4bff0((char*)layout + 0x200, *(int*)((char*)layout + 0x600));
    s.FreeIfOwned();
    return 1;
}

// ===========================================================================
// @ 0x00e4c130  SP::sReadAppDataResource (catalog reader)
// ===========================================================================
struct FileStream {
    char  mData_00[0x154];
    void  ctor(const char* a);          // 0x00931da0
    void  SetPath16(const u16* p);      // 0x00931810
    char  Open(uint a, uint b, uint c, uint d); // 0x009318f0
    void  AddRef(void);                 // 0x009317b0
    void  Close(void);                  // 0x00931a70
    void  dtor(void);                   // 0x00931e70
};
struct StreamBuffer {
    char mData_00[0x140];
    void ctor(void* owner, uint a, uint b);  // 0x0093b530
    void dtor(void);                         // 0x0093b5a0
};
uint ReadLine(void* sb, char* buf, uint n);  // 0x0093a8b0

void SP_sReadAppDataResource(const char* dir, int threshold)
{
    EaStringW path;
    path.mpBegin_00 = (u16*)g_emptyStr;
    path.mpEnd_04   = (u16*)g_emptyStr;
    path.mpCap_08   = (u16*)0x1667bae;
    path.sprintf_w((const u16*)L"%s%s", dir, *(void**)0x15a5c20);

    FileStream fs;
    fs.ctor(0);
    fs.SetPath16(path.mpBegin_00);
    fs.Open(1, 4, 1, 0);
    fs.AddRef();
    StreamBuffer sb;
    sb.ctor(&fs, 0x2000, 0);
    char line[0x100];
    uint n = ReadLine(&sb, line, 0x100);
    if (n < 0xfffffffe && atoi_(line) < threshold) {
        fs.Close();
        sb.dtor();
        fs.dtor();
    } else {
        n = ReadLine(&sb, line, 0x100);
        while (n < 0xfffffffe) {
            EaString fld;
            fld.SetEmpty();
            char* sp = strchr_(line, 0x20);
            if (sp) {
                fld.assign(line, sp);
                int v = atoi_(sp);
                int* slot = gspAppDataGlobals->mFieldMap_28.at(&fld);
                *slot = v;
            }
            fld.FreeIfOwned();
            n = ReadLine(&sb, line, 0x100);
        }
        fs.Close();
        sb.dtor();
        fs.dtor();
    }
    path.FreeIfOwned();
}

// ===========================================================================
// @ 0x00e4c330  SP::sHandlePostedFileChangeMessage
// ===========================================================================
char FUN_00e4c330(void* obj)
{
    FUN_00e82280();
    void* node = gspAppDataGlobals->mMap_04.find(*(uint*)((char*)obj + 0x60c));
    if (node) {
        SP_sAppDataCompile((char*)obj + 8, *(void**)((char*)node + 0xc));
    }
    return 1;
}

// ===========================================================================
// @ 0x00e4c370  SP::sIsUpToDate
// ===========================================================================
char SP_sIsUpToDate(void* obj)
{
    EaString key;
    key.SetEmpty();
    key.sprintf_(g_fmtPctS, (char*)obj + 0x200);
    void* out;
    void* node = gspAppDataGlobals->mFieldMap_28.find(&out, &key);
    uint stamp;
    if (*(void**)node == (void*)((char*)gspAppDataGlobals + 0x2c)) {
        key.FreeIfOwned();
        return 0;
    }
    int* v = gspAppDataGlobals->mFieldMap_28.at(&key);
    stamp = (uint)*v;
    if (*(uint*)((char*)obj + 0x600) > stamp) {
        key.FreeIfOwned();
        return 1;
    }
    key.FreeIfOwned();
    return 0;
}

// ===========================================================================
// @ 0x00e4c440  SP::sCellResourceCompileAll
// ===========================================================================
void* FindFirst(const void* dir, const u16* pat, uint a, uint b);  // 0x0092e730
void* FindNext(void* h, uint a);                                   // 0x0092e8e0
void  FindFinish(void* h);                                         // 0x0092e9b0
int   wcscmp_(const u16* a, const u16* b);

void SP_sCellResourceCompileAll(const char* dir, void* arg)
{
    void* h = FindFirst(dir, (const u16*)L"*.cel", 0, 0);
    if (h == 0) return;
    char more = 1;
    while (more) {
        if (*(u8*)((char*)h + 0x208) == 0) {
            u16 ext[0x102];
            FUN_00e4b390(h);
            if (wcscmp_((const u16*)((char*)h + 0x20a), (const u16*)L".cel") == 0) {
                if (!SP_sIsUpToDate(h)) {
                    SP_sAppDataCompile((char*)h + 8, arg);
                }
            }
        }
        more = FindNext(h, 0) != 0;
    }
    FindFinish(h);
}

// ===========================================================================
// @ 0x00e4c520  SP::sAppendData
// ===========================================================================
extern char g_zero2[];    // 0x016ad068
extern char g_zero9[];    // 0x016ad174
extern char g_def3v[];    // 0x016ad070  default 3-vector

struct FieldDefArg {
    uint  mPad_00[3];
    uint  mFieldOff_0c;       // +0x0c  element size / field offset
    uint  mType_10;           // +0x10  data type id
};
struct FieldDefFull {
    uint mPad_00[3];
    uint mPad_0c;
    uint mType_10;
    uint mPad_14;
    uint mPad_18;
    uint mPad_1c;
    uint mFlags_20;
};

void SP_sAppendData(void* objBase, void* value, FieldDefArg* fd)
{
    char* dst = (char*)objBase + fd->mFieldOff_0c;
    switch (fd->mType_10) {
    case 0: case 4:
        return;
    case 1:
        *(void**)dst = value; return;
    case 2:
        *(void**)dst = value; return;
    case 5:
        *(uint*)dst = (uint)value; return;
    case 6:
        *(u8*)dst = value != 0; return;
    case 3:
        if (value == 0) { *(uint*)dst = 0; return; }
        *(void**)dst = FUN_00e4be50((const char*)value); return;
    case 7:
        *(void**)dst = FUN_00e4be50((const char*)value); return;
    case 8:
        if (value != 0) { ((uint*)dst)[0] = ((uint*)value)[0]; ((uint*)dst)[1] = ((uint*)value)[1]; ((uint*)dst)[2] = ((uint*)value)[2]; return; }
        memcpy_(dst, g_def3v, 12); return;
    case 9:
        memcpy_(dst, value ? value : g_zero9, 0x24); return;
    case 10:
        if (value != 0) { FUN_00e4a8a0(); return; }
        *(u16*)dst = 0; return;
    case 11:
        if (value != 0) { ((uint*)dst)[0] = ((uint*)value)[0]; ((uint*)dst)[1] = ((uint*)value)[1]; return; }
        memcpy_(dst, g_zero2, 8); return;
    default:
        if (value == 0) { memset_(dst, 0, fd->mFieldOff_0c); return; }
        memcpy_(dst, value, fd->mFieldOff_0c); return;
    }
}

// ===========================================================================
// @ 0x00e4c670  SP::sParseField
// ===========================================================================
uint MainArguments(void* args, int* count, int a, int b);       // 0x00838020
uint OptionArguments(void* args, const char* name, int* count, int a, int b); // 0x00838130
void* sStringToData(void* s, void* fd);                         // 0x00e4aad0

void SP_sParseField(FieldDefFull* fd, void* args, void* out)
{
    uint flags = fd->mFlags_20;
    void* value = (void*)*(uint*)((char*)fd + 0x1c);
    if ((flags & 8) == 0 && args != 0) {
        int count = -1;
        uint ok;
        if ((flags & 2) != 0 && (flags & 4) == 0) {
            if (*(uint*)((char*)fd + 0x10) == 6) {
                ok = OptionArguments(args, (const char*)*(uint*)fd, &count, 0, 1);
                if (ok == 0) goto append;
                if (count != 0) {
                    if ((int)count > *(int*)((char*)fd + 0x18))
                        value = sStringToData((void*)*(uint*)(ok + *(int*)((char*)fd + 0x18) * 4), fd);
                } else {
                    SP_sAppendData(out, (void*)1, (FieldDefArg*)fd);
                    return;
                }
            } else {
                ok = OptionArguments(args, (const char*)*(uint*)fd, &count, 0, 0x7fffffff);
                if (ok != 0 && count > *(int*)((char*)fd + 0x18))
                    value = sStringToData((void*)*(uint*)(ok + *(int*)((char*)fd + 0x18) * 4), fd);
            }
        } else {
            ok = MainArguments(args, &count, 0, 0x7fffffff);
            if (ok != 0 && count > *(int*)((char*)fd + 0x18))
                value = sStringToData((void*)*(uint*)(ok + *(int*)((char*)fd + 0x18) * 4), fd);
        }
    }
append:
    SP_sAppendData(out, value, (FieldDefArg*)fd);
}

// ===========================================================================
// @ 0x00e4c730  thiscall: cMyMagicCommand::Execute
// ===========================================================================
void* sAssetCreate(void* a, void* b, void* c);      // 0x00e4b730
void  MemPoolLockedAlloc();                         // 0x009289f0
void  sParseField_(void*, void*, void*);            // 0x00e4c670
void  sAppendData_(void*, void*, void*);            // 0x00e4c520
void  World_SetArgState();                          // 0x00e4a8a0

void cMyMagicCommand::Execute(void* args)
{
    u8* ctx = (u8*)this->mpVecEnd_08[-1];
    uint type = *(uint*)(ctx + 0x10);
    uint typeId = type;
    if ((int)type < 0xc) {
        SP_sParseField((FieldDefFull*)ctx, args, (void*)*(uint*)((char*)this + 0x18));
        *(uint*)((char*)this + 8) -= 4;
        return;
    }
    if ((*(u8*)(type + 0x10) & 1) != 0) {
        int local;
        MainArguments(args, &local, 1, 0x7fffffff);
        *(void**)((char*)this + 0x18) = sAssetCreate((void*)*(uint*)&local, (void*)type, (char*)this + 0x1c);
    }
    void* dst;
    if (*(uint*)(ctx + 0x14) == 4) {
        FUN_00e4a8a0();
        uint size = 0;
        uint* cnt = (uint*)(*(uint*)(ctx + 0xc) + *(uint*)((char*)this + 0x18));
        uint* base = (uint*)(*(uint*)(ctx + 8) + *(uint*)((char*)this + 0x18));
        if (*cnt == 0) {
            void* p = (void*)FUN_009289f0(size, 0, 0, 0, 0, 0);
            *base = (uint)p;
            cSPAppDataGlobals* g = gspAppDataGlobals;
            void** slot = g->mPoolList_48.mpEnd_04;
            if (slot < g->mPoolList_48.mpCap_08) {
                g->mPoolList_48.mpEnd_04 = slot + 1;
                if (slot) *slot = p;
            } else {
                DoInsertCell(&g->mPoolList_48.mpEnd_04, &p);
            }
            dst = p;
        } else {
            dst = (void*)((char*)*base + *cnt * size);
        }
        memset_(dst, 0, size);
        *cnt += 1;
        type = typeId;
    } else {
        dst = (void*)(*(uint*)(ctx + 8) + *(uint*)((char*)this + 0x18));
    }
    u8* f = (u8*)*(uint*)(type + 4);
    char appended = 0;
    if (*(int*)(f + 8) != -1) {
        uint off = 0;
        do {
            if ((*(uint*)(f + 0x20) & 4) == 0) {
                SP_sParseField((FieldDefFull*)f, args, dst);
            } else {
                if ((*(uint*)(f + 0x20) & 2) != 0)
                    SP_sAppendData(dst, (void*)*(uint*)(f + 0x1c), (FieldDefArg*)f);
                appended = 1;
            }
            off += 0x28;
            f = (u8*)(*(uint*)(type + 4) + off);
        } while (*(int*)(f + 8) != -1);
        if (appended) {
            void* p = gspAppDataGlobals->mpParser_20;
            (*(void(__thiscall**)(void*, void*))(*(int*)p + 0x8c))(p, this);
            return;
        }
    }
    *(uint*)((char*)this + 8) -= 4;
}

// ===========================================================================
// @ 0x00e4c8c0  initialise the global app-data state
// ===========================================================================
void* CreateParser(void);                          // 0x008408d0
void* MessageServer(void);                         // 0x0067dcc0

void FUN_00e4c8c0(void)
{
    cSPAppDataGlobals* g = (cSPAppDataGlobals*)EAAllocate(0x58, g_allocSim, 0, 0, 0, 0);
    if (g != 0) {
        g->mPoolList_48.clear();
        g->mFieldMap_28.mAnchorL_04 = &g->mFieldMap_28.mAnchorL_04;
        g->mFieldMap_28.mAnchorR_08 = &g->mFieldMap_28.mAnchorL_04;
        g->mFieldMap_28.mRoot_0c   = 0;
        g->mFieldMap_28.mColor_10  = 0;
        g->mFieldMap_28.mnSize_14  = 0;
        g->mPad_44 = 0;
        g->mPoolList_48.mpBegin_00 = 0;
        g->mPoolList_48.mpEnd_04   = 0;
        g->mPoolList_48.mpCap_08   = 0;
    } else {
        g = 0;
    }
    gspAppDataGlobals = g;
    g->mpParser_20 = 0;
    (void)ZoneObjectNew(8, "App", 0, 0, 0, 0);
    void* ps = CreateParser();
    g->mpParser_20 = ps;
    (*(void(__thiscall**)(void*))(*(int*)ps))(ps);
    (*(void(__thiscall**)(void*))(*(int*)ps + 8))(ps);
    (*(void(__thiscall**)(void*, int))(*(int*)ps + 0x10))(ps, 0);
    FUN_00e4bd70();
    void* ms = MessageServer();
    (*(void(__thiscall**)(void*, void*, int, int, int))(*(int*)ms + 0x28))(ms, (void*)FUN_00e4c330, 0, 0x4a4e97f, 0);
    FUN_00e82490();
}