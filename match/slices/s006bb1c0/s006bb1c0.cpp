// Slice s006bb1c0: Win32 drag/drop + ResourceMan::DatabasePackedFile helpers.
// Same module family: /O2 /MD /Gy /GS- /EHsc /TP /arch:SSE.
#include "types.h"
#include <intrin.h>

typedef unsigned int UINT;
typedef void* HWND;
typedef void* HANDLE;
typedef unsigned long DWORD;

struct IUnknownStub { void** vtbl; };

extern "C" {
    __declspec(dllimport) void __stdcall ReleaseStgMedium(void*);
    __declspec(dllimport) long __stdcall InterlockedIncrement(long*);
    __declspec(dllimport) long __stdcall InterlockedDecrement(long*);
    __declspec(dllimport) int  __stdcall RevokeDragDrop(HWND);
    __declspec(dllimport) int  __stdcall CoLockObjectExternal(void*, int, int);
    __declspec(dllimport) void __stdcall OleUninitialize(void);
    __declspec(dllimport) int  __stdcall OleInitialize(void*);
    __declspec(dllimport) unsigned __stdcall DragQueryFileW(void* hdrop, unsigned iFile, wchar_t* buf, unsigned cch);
}
void __cdecl EASTL_dealloc(void*) throw();
void __cdecl FUN_00688dd0(void*);

// ---------------------------------------------------------------------------
// @ 0x006bb820  release stg medium member
// ---------------------------------------------------------------------------
struct HasStg { char pad[0x1c]; void* mpStg; void Release(); };
void HasStg::Release()
{
    if (mpStg) ReleaseStgMedium(mpStg);
}

// ---------------------------------------------------------------------------
// @ 0x006bb890  argument-adjusting thunk to InterlockedIncrement
// ---------------------------------------------------------------------------
long __stdcall FUN_006bb890(long* p)
{
    return InterlockedIncrement(p + 1);
}

// ---------------------------------------------------------------------------
// @ 0x006bb8b0  refcount release
// ---------------------------------------------------------------------------
struct RefObj { void** vtbl; long mRefCount; };
long __stdcall FUN_006bb8b0(RefObj* p)
{
    long n = InterlockedDecrement(&p->mRefCount);
    if (n == 0) {
        if (p) ((void(__thiscall*)(RefObj*, int))p->vtbl[7])(p, 1);
        n = 0;
    }
    return n;
}

// ---------------------------------------------------------------------------
// @ 0x006bbdd0  lazy init flag
// ---------------------------------------------------------------------------
struct DBPF { char pad[0xc]; bool mb0c; bool Init(); void Shutdown(); void* AsInterface(uint32_t id); };
bool DBPF::Init()
{
    if (!mb0c) mb0c = true;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006bbe20  AsInterface
// ---------------------------------------------------------------------------
void* DBPF::AsInterface(uint32_t id)
{
    if (id == 0x6492c5f) return (char*)this - 4;
    if (id != 0xee3f516e) return 0;
    return (void*)((uint32_t)(-((int)((char*)this - 4 != 0))) & (uint32_t)this);
}

// ---------------------------------------------------------------------------
// @ 0x006bba40  clear a stg medium member
// ---------------------------------------------------------------------------
int __stdcall FUN_006bba40(void* p)
{
    char* c = (char*)p;
    if (c[0xc]) {
        FUN_00688dd0(c + 0x24);
        ReleaseStgMedium(c + 0x24);
        c[0xc] = 0;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bbb10  tear down drag/drop
// ---------------------------------------------------------------------------
void __stdcall FUN_006bbb10(HWND hwnd, IUnknownStub* p)
{
    RevokeDragDrop(hwnd);
    CoLockObjectExternal(p, 0, 1);
    ((void(__stdcall*)(IUnknownStub*))p->vtbl[2])(p);
    OleUninitialize();
}

// ---------------------------------------------------------------------------
// @ 0x006bbe50  mutex lock/unlock
// ---------------------------------------------------------------------------
struct Mutex { void Lock(const char* name); void Unlock(); };
struct MutexOwner { char pad[0x478]; Mutex mMutex; void LockOrUnlock(bool lock); };
void MutexOwner::LockOrUnlock(bool lock)
{
    if (lock) mMutex.Lock("App");
    else      mMutex.Unlock();
}

// ---------------------------------------------------------------------------
// @ 0x006bb670  refcount release (secondary layout)
// ---------------------------------------------------------------------------
int __fastcall FUN_006bb670(void* self)
{
    int obj = (int)(size_t)self;
    long* pc = (long*)((char*)obj + 0x14);
    long n = _InterlockedDecrement((volatile long*)pc);
    if (n == 0 && obj) ((void(__thiscall*)(int, int))(*(int**)obj)[0])(obj, 1);
    return n;
}

// ===========================================================================
// Helpers, imports and imported data for the config / drag-drop functions.
// ===========================================================================
typedef wchar_t wchar16;

extern "C" int   __cdecl memcmp(const void*, const void*, size_t);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
#pragma intrinsic(memcmp)
extern "C" long  __cdecl _InterlockedExchange(volatile long*, long);

int   __cdecl Sprintf8(char* buf, const char* fmt, ...);                            // 0x00938470
bool  __cdecl SPKeyFromName(void* key, const char* name, unsigned t, unsigned g);   // 0x0068d5a0
void* __cdecl EA_ConvertToString16Impl(void* dst, const char* src, unsigned len);   // 0x0093c5a0
void  __cdecl FUN_006bb0b0(const wchar16* text, unsigned a, unsigned b);            // 0x006bb0b0
bool  __cdecl WideSearchEnvironmentPath(const wchar16* p, wchar16* buf, int);       // 0x00935e00
int   __cdecl WideSpawn(wchar16* buf, const void* argv, int);                       // 0x00935d60
void  __cdecl VecWStrInsert(void* end, const void* val);                            // 0x00690c90
wchar16* __cdecl eastl_search_w(wchar16* f, wchar16* l, const wchar16* sf, const wchar16* sl); // 0x005e8ff0
void  __cdecl EA_Free2(void* p);                                                    // 0x00f47380
void* __cdecl EA_New6(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  __cdecl FUN_00688d50(void* p);                                                // 0x00688d50
void  __cdecl FUN_00688e50(void* p);                                                // 0x00688e50

struct Win32Point { long x, y; };
__declspec(dllimport) void* __stdcall SetFocus(void*);
__declspec(dllimport) int   __stdcall ScreenToClient(void*, Win32Point*);
__declspec(dllimport) long  __stdcall SendMessageA(void*, unsigned, unsigned, long);
__declspec(dllimport) int   __stdcall RegisterDragDrop(void*, void*);
__declspec(dllimport) char* __cdecl strstr(const char*, const char*);

extern unsigned char g_guid_014dd504[16];  // 0x014dd504 IID
extern unsigned char g_guid_014dd514[16];  // 0x014dd514 IID
extern void*         g_vtbl_140a05c;       // 0x0140a05c cFileDropWin32 vtable
extern char          g_emptyStr_1667bac[]; // 0x01667bac empty string16 sentinel

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t> (string16) and the SP::cString resource string.
// ---------------------------------------------------------------------------
struct CWStr {
    wchar16* mpBegin;
    wchar16* mpEnd;
    wchar16* mpCapacity;
    void RangeInitialize(const wchar16* psz);                                   // 0x00579a90
    void replace(wchar16* f1, wchar16* l1, const wchar16* f2, const wchar16* l2); // 0x005f8400
    ~CWStr()
    {
        if ((((int)((char*)mpCapacity - (char*)mpBegin)) & -2) > 2 && mpBegin) EA_Free2(mpBegin);
    }
};

namespace SP {
struct string16 { wchar16* mpBegin; wchar16* mpEnd; wchar16* mpCapacity; int mAllocator; };
struct IRefCounted {
    virtual void AddRef();  virtual void Release();
    virtual void v2();  virtual void v3();  virtual void v4();  virtual void v5();
    virtual void v6();  virtual void v7();  virtual void v8();  virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19();
};
struct AutoRefCount {
    IRefCounted* mpObject;
    explicit AutoRefCount(IRefCounted* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
class cString { public:
    AutoRefCount   mpTableResource;   // +0x00
    string16*      mpLocalString;     // +0x04
    const wchar16* mpSourceCStr;      // +0x08
    unsigned       mPlaceholderId;    // +0x0c
    bool           mbHasTokens;       // +0x10
    bool           mField11;          // +0x11
    unsigned       mTableId;          // +0x14
    unsigned       mInstanceId;       // +0x18
    cString();                                                    // 0x006b5060
    ~cString();                                                   // 0x006b5240
    bool Load(unsigned tableID, unsigned instanceID, int group); // 0x006b54b0
    const wchar16* GetText();                                     // 0x006b55c0
};
}

struct BaseA2 { virtual ~BaseA2() {} };
struct WStr16 {            // eastl::basic_string<wchar_t>: begin, end, capacity + allocator word
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAlloc;
    void AllocateSelf(int n);                                   // 0x00429760
    ~WStr16()
    {
        if ((int)(((char*)mpCapacity - (char*)mpBegin) & 0xfffffffe) > 2 && mpBegin) EASTL_dealloc(mpBegin);
    }
};
class DebugMessage : public BaseA2 { public:
    WStr16 mText;
    long   mRef;
    DebugMessage() : mRef(0) {}
    DebugMessage(const wchar_t* src, int count);
// @ 0x006bb690
// @ 0x006bb760
    virtual ~DebugMessage() {}   // ~DebugMessage 0x6bb690; its ??_G 0x6bb760 is compiler generated from it
};
// Constructing one in this unit makes it emit DebugMessage's vtable and with it ??_G.
inline void* operator new(size_t, void* p) { return p; }
DebugMessage* ConstructDebugMessage(void* mem)
{
    DebugMessage* m = new (mem) DebugMessage;
    m->mText.mpBegin = 0; m->mText.mpEnd = 0; m->mText.mpCapacity = 0;
    return m;
}

// ---------------------------------------------------------------------------
// @ 0x006bb6c0  DebugMessage::DebugMessage(const wchar_t* src, int count)
// ---------------------------------------------------------------------------
DebugMessage::DebugMessage(const wchar_t* src, int count)
{
    mText.mpBegin = 0;
    mText.mpEnd = 0;
    mText.mpCapacity = 0;
    mText.AllocateSelf(count + 1);
    memcpy(mText.mpBegin, src, (size_t)(count * 2));
    mText.mpEnd = (wchar_t*)((char*)mText.mpBegin + count * 2);
    *mText.mpEnd = 0;
    _InterlockedExchange(&mRef, 0);
}

// ---------------------------------------------------------------------------
// @ 0x006bb7b0  GUID equality (inlined memcmp of 16 bytes)
// ---------------------------------------------------------------------------
int __cdecl FUN_006bb7b0(const void* a, const void* b)
{
    return memcmp(a, b, 16) == 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bb830  cFileDropWin32::QueryInterface
// ---------------------------------------------------------------------------
long __stdcall FUN_006bb830(void* obj, const void* riid, void** ppv)
{
    if (FUN_006bb7b0(riid, g_guid_014dd514) || FUN_006bb7b0(riid, g_guid_014dd504)) {
        ((void(__stdcall*)(void*))((IUnknownStub*)obj)->vtbl[1])(obj);
        *ppv = obj;
        return 0;
    }
    *ppv = 0;
    return (long)0x80004002;
}

// ---------------------------------------------------------------------------
// @ 0x006bb8e0  IDropTarget::DragEnter
// ---------------------------------------------------------------------------
long __stdcall FUN_006bb8e0(void* pThis, IUnknownStub* pUnk, unsigned arg2,
                            unsigned x, unsigned y, unsigned* pOut)
{
    char* self = (char*)pThis;
    int r = ((int(__stdcall*)(IUnknownStub*, void*))pUnk->vtbl[5])(pUnk, self + 0x10);
    self[0xc] = (char)(r == 0);
    if (r == 0) {
        *pOut = 1;
        void* h = *(void**)(self + 8);
        SetFocus(h);
        Win32Point pt; pt.x = (long)x; pt.y = (long)y;
        ScreenToClient(h, &pt);
        unsigned short m = (unsigned short)SendMessageA(h, 0xd7, 0,
            (long)(((unsigned)(unsigned short)pt.y << 16) | (unsigned short)pt.x));
        SendMessageA(h, 0xb1, m, m);
        r = ((int(__stdcall*)(IUnknownStub*, void*, void*))pUnk->vtbl[3])(pUnk, self + 0x10, self + 0x24);
        self[0xc] = (char)(r == 0);
        if (r == 0) FUN_00688d50(self + 0x24);
    } else {
        *pOut = 0;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bb9b0  IDropTarget::DragOver
// ---------------------------------------------------------------------------
long __stdcall FUN_006bb9b0(void* pThis, unsigned arg1, unsigned x, unsigned y, unsigned* pOut)
{
    char* self = (char*)pThis;
    if (self[0xc] != 0) {
        Win32Point pt;
        pt.x = (long)x;
        *pOut = 1;
        void* h = *(void**)(self + 8);
        pt.y = (long)y;
        ScreenToClient(h, &pt);
        unsigned short r = (unsigned short)SendMessageA(h, 0xd7, 0,
            (long)(((unsigned)(unsigned short)pt.y << 16) | (unsigned short)pt.x));
        SendMessageA(h, 0xb1, r, r);
        return 0;
    }
    *pOut = 0;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bba70  IDropTarget::Drop
// ---------------------------------------------------------------------------
long __stdcall FUN_006bba70(void* pThis, unsigned arg1, unsigned arg2,
                            unsigned x, unsigned y, unsigned* pOut)
{
    char* self = (char*)pThis;
    void* h = *(void**)(self + 8);
    Win32Point pt; pt.x = (long)x; pt.y = (long)y;
    ScreenToClient(h, &pt);
    unsigned short r = (unsigned short)SendMessageA(h, 0xd7, 0,
        (long)(((unsigned)(unsigned short)pt.y << 16) | (unsigned short)pt.x));
    SendMessageA(h, 0xb1, r, r);
    if (self[0xc] != 0) {
        FUN_00688e50(self + 0x24);
        self[0xc] = 0;
        *pOut = 2;
        return 0;
    }
    *pOut = 0;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bbb60  create + register the drag/drop target
// ---------------------------------------------------------------------------
void __cdecl FUN_006bbb60(void* hwnd, void** ppOut)
{
    OleInitialize(0);
    char* p = (char*)EA_New6(0x30, "App", 0, 0, 0, 0);
    if (p) {
        *(void**)(p + 0x00)         = &g_vtbl_140a05c;
        *(void**)(p + 0x04)         = 0;
        *(void**)(p + 0x08)         = hwnd;
        *(unsigned char*)(p + 0x0c) = 0;
        *(unsigned short*)(p + 0x10) = 0x000f;
        *(unsigned*)(p + 0x14)      = 0;
        *(unsigned*)(p + 0x18)      = 1;
        *(unsigned*)(p + 0x1c)      = 0xffffffff;
        *(unsigned*)(p + 0x20)      = 1;
    }
    ((void(__stdcall*)(void*))((IUnknownStub*)p)->vtbl[1])(p);
    CoLockObjectExternal(p, 1, 0);
    RegisterDragDrop(hwnd, p);
    *ppOut = p;
}

// ---------------------------------------------------------------------------
// @ 0x006bbbf0  push a default (empty) string16 onto a vector<string16>
// ---------------------------------------------------------------------------
struct Str16 {
    wchar16* mpBegin;
    wchar16* mpEnd;
    wchar16* mpCapacity;
    int mAlloc;
    void assign(const wchar16* first, const wchar16* last);          // 0x00423650
    Str16()
    {
        mpBegin    = (wchar16*)g_emptyStr_1667bac;
        mpEnd      = (wchar16*)g_emptyStr_1667bac;
        mpCapacity = (wchar16*)(g_emptyStr_1667bac + 2);
    }
};
struct Str16Vec {
    Str16* mpBegin;
    Str16* mpEnd;
    Str16* mpCapacity;
    void Reserve(unsigned count);                                   // 0x006953b0
    void DoDestroyValues(Str16* first, Str16* last);                // 0x0084aad0
    void push_back()
    {
        if (mpEnd < mpCapacity) {
            Str16* e = mpEnd;
            mpEnd = e + 1;
            if (e) {
                e->mpBegin    = (wchar16*)g_emptyStr_1667bac;
                e->mpEnd      = (wchar16*)g_emptyStr_1667bac;
                e->mpCapacity = (wchar16*)(g_emptyStr_1667bac + 2);
            }
        } else {
            Str16 tmp;
            VecWStrInsert(mpEnd, &tmp);
        }
    }
};
__declspec(noinline) void __fastcall FUN_006bbbf0(Str16Vec* vec)
{
    vec->push_back();
}

// ---------------------------------------------------------------------------
// @ 0x006bb4b0  resolve an executable path and spawn it with a NULL-terminated
//               wide-string argument vector.
// ---------------------------------------------------------------------------
bool __cdecl FUN_006bb4b0(unsigned a, unsigned b, const wchar16* path, ...)
{
    (void)a; (void)b;
    wchar16 buf[130];
    if (!WideSearchEnvironmentPath(path, buf, 0))
        return false;

    const wchar16* args[65];
    int n = 0;
    args[n++] = path;
    const wchar16** ap = (const wchar16**)&path + 1;
    const wchar16* v;
    while ((v = *ap++) != 0) {
        if (n < 64) args[n++] = v;
        else        VecWStrInsert(&args[n], &v);
    }
    args[n] = 0;

    int r = WideSpawn(buf, args, 0);
    return r == 0;
}

// ---------------------------------------------------------------------------
// @ 0x006bb1c0  build an "AppConfig!..." resource name, resolve its localized
//               text (with ~br~ / newline fixup) and hand it to FUN_006bb0b0.
// ---------------------------------------------------------------------------
void __cdecl FUN_006bb1c0(const char* src, unsigned id, unsigned arg2, const char* name)
{
    char buf[128];
    const char* pName = name;
    if (name == 0) {
        Sprintf8(buf, "AppConfig!0x%08x", id);
        pName = buf;
    } else if (strstr(name, "!") == 0) {
        Sprintf8(buf, "AppConfig!%hs", name);
        pName = buf;
    }

    unsigned key[3] = { 0, 0, 0 };
    SPKeyFromName(key, pName, 0, 0);

    char conv[12];
    void* r = EA_ConvertToString16Impl(conv, src, 0xffffffff);
    CWStr wstr;
    wstr.RangeInitialize(*(const wchar16**)r);

    // replace every L"\n" with L"~br~".
    while (true) {
        unsigned hayLen = (unsigned)(wstr.mpEnd - wstr.mpBegin);
        unsigned nLen = 1;
        if (hayLen < nLen) break;
        wchar16* m = eastl_search_w(wstr.mpBegin, wstr.mpEnd, L"\n", L"\n" + nLen);
        if (m == wstr.mpEnd && nLen != 0) break;
        long pos = (long)(m - wstr.mpBegin);
        if (pos == -1) break;
        unsigned remaining = hayLen - (unsigned)pos;
        unsigned take = remaining < nLen ? remaining : nLen;
        wstr.replace(wstr.mpBegin + pos, wstr.mpBegin + pos + take, L"~br~", L"~br~" + 4);
    }

    SP::cString str;
    bool ok = str.Load(key[2], key[0], 0);
    if (!ok) {
        // fallback: replace every L"~br~" with L"\n".
        while (true) {
            unsigned hayLen = (unsigned)(wstr.mpEnd - wstr.mpBegin);
            unsigned nLen = 4;
            if (hayLen < nLen) break;
            wchar16* m = eastl_search_w(wstr.mpBegin, wstr.mpEnd, L"~br~", L"~br~" + nLen);
            if (m == wstr.mpEnd && nLen != 0) break;
            long pos = (long)(m - wstr.mpBegin);
            if (pos == -1) break;
            unsigned remaining = hayLen - (unsigned)pos;
            unsigned take = remaining < nLen ? remaining : nLen;
            wstr.replace(wstr.mpBegin + pos, wstr.mpBegin + pos + take, L"\n", L"\n" + 1);
        }
        FUN_006bb0b0(wstr.mpBegin, id, arg2);
    } else {
        FUN_006bb0b0(str.GetText(), id, arg2);
    }
}

// ---------------------------------------------------------------------------
// Drag/drop file-list message, DBPF record factories and drive-mount queries.
// ---------------------------------------------------------------------------
struct DropSource {
    void*  mpUnknown0;      // +0x00
    void*  mHDrop;          // +0x04
};

struct VecBlockPrefix { uint32_t mField0; };  // EA sp_vector block header word

struct FileVec : Str16Vec {
    FileVec() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~FileVec();
};

FileVec::~FileVec()
{
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin && ((VecBlockPrefix*)mpBegin)[-1].mField0 != 0)
        EA_Free2(mpBegin);
}

struct FileListMsg {
    void*    mpVtable;      // +0x00
    FileVec  mFiles;        // +0x04
    void*    mpField10;     // +0x10
    void*    mpField14;     // +0x14
    unsigned mField18;      // +0x18
    void*    mpField1c;     // +0x1c
    FileListMsg(DropSource* src);       // 0x006bbc90
    FileListMsg* Destroy(char flags);   // 0x006bbd80
};

extern void* g_vtbl_140a07c;     // 0x0140a07c FileListMsg vtable
extern void* g_vtbl_13eb918;     // 0x013eb918 BaseA2 vtable

// @ 0x006bbc90  drag/drop file-list message constructor
FileListMsg::FileListMsg(DropSource* src) : mpVtable(&g_vtbl_140a07c)
{
    mField18 = 0;
    mpField1c = src;
    wchar16 buf[260];
    unsigned count = DragQueryFileW(src->mHDrop, 0xffffffff, buf, 0x208);
    mFiles.Reserve(count);
    for (unsigned i = 0; i < count; ++i) {
        DragQueryFileW(src->mHDrop, i, buf, 0x208);
        FUN_006bbbf0(&mFiles);
        const wchar16* p = buf;
        while (*p)
            ++p;
        (mFiles.mpEnd - 1)->assign(buf, p);
    }
}

// @ 0x006bbd80  drag/drop file-list message deleting destructor
FileListMsg* FileListMsg::Destroy(char flags)
{
    mFiles.DoDestroyValues(mFiles.mpBegin, mFiles.mpEnd);
    if (mFiles.mpBegin && ((VecBlockPrefix*)mFiles.mpBegin)[-1].mField0 != 0)
        EA_Free2(mFiles.mpBegin);
    mpVtable = &g_vtbl_13eb918;
    if (flags & 1)
        EA_Free2(this);
    return this;
}

// ---------------------------------------------------------------------------
// Drive-session state (DBPF shutdown / mount queries). Vtable +0x00,
// +0x0c flag byte, +0x14 flags word, +0x18 mount object, +0x4d8 mount handle.
// ---------------------------------------------------------------------------
struct Session {
    void*    mpVtable;          // +0x000
    uint32_t pad004[2];         // +0x004
    uint8_t  mField0c;          // +0x00c
    uint8_t  pad00d[7];         // +0x00d
    uint32_t mField14;          // +0x014
    void*    mpField18;         // +0x018
    uint32_t pad01c[303];       // +0x01c .. +0x4d7
    void*    mpField4d8;        // +0x4d8
    char Shutdown();            // 0x006bbde0
    char CheckMount();          // 0x006bc0a0
    char EnsureMounted();       // 0x006bc0f0
};

// @ 0x006bbde0  DatabasePackedFile shutdown
char Session::Shutdown()
{
    if (mField0c) {
        if (mField14)
            (*(void(__thiscall**)(Session*))((char*)mpVtable + 0x1c))(this);
        (*(void(__thiscall**)(Session*, void*))((char*)mpVtable + 0x80))(this, mpField4d8);
        mpField4d8 = 0;
        mField0c = 0;
    }
    return 1;
}

// @ 0x006bc0a0  drive-mount state query
char Session::CheckMount()
{
    if (mField14 == 0) {
        if (!mpField18)
            return 0;
        char c = (*(char(__thiscall**)(Session*, void*, int, int))((char*)mpVtable + 0x18))(this, mpField18, 0, 0);
        if (c)
            return c;
        if ((mField14 & 3) == 3)
            return (*(char(__thiscall**)(Session*, int, int, int))((char*)mpVtable + 0x18))(this, 1, 0, 0);
        return 0;
    }
    return 1;
}

// @ 0x006bc0f0  drive-mount helper
char Session::EnsureMounted()
{
    if (!(*(char(__thiscall**)(Session*))((char*)mpVtable + 0x60))(this)) {
        if (!mpField4d8)
            mpField4d8 = (*(void*(__thiscall**)(Session*, int))((char*)mpVtable + 0x7c))(this, 3);
        return 0;
    }
    return (*(char(__thiscall**)(Session*))((char*)mpVtable + 0x70))(this) != 0;
}

// ---------------------------------------------------------------------------
// DatabasePackedFile record/index factories. Allocator at +0x10.
// ---------------------------------------------------------------------------
struct PFRecordWrite {
    void* Construct(void* a, void* b, void* c, void* d, void* owner);     // 0x006c0c40
};
struct PFRecordWriteShared {
    void* Construct(void* a, void* b, int one, void* c, void* owner);     // 0x006c0db0
};
struct PFRecordRead {
    void* Construct(void* a, void* b, void* owner);                        // 0x006c09c0
};
struct PFRecordReadShared {
    void* Construct(void* a, void* b, void* owner);                        // 0x006c0b20
};
struct PFIndexModifiable {
    void* Ctor(void* alloc);                                              // 0x006bf370
};

void* __cdecl ZoneAlloc_Named(int size, void* alloc, const char* name);   // 0x00925fe0

struct ZoneFactory {
    uint32_t pad000[4];     // +0x00
    void*    mpAlloc;       // +0x10
    void* CreateRecordWrite(unsigned char flags, void* a, void* b, void* c, void* d);   // 0x006bbe80
    void* CreateRecordWriteShared(unsigned char flags, void* a, void* b, void* c);      // 0x006bbf10
    void* CreateRecordRead(void* unused, void* a, void* b);                             // 0x006bbfa0
    void* CreateRecordReadShared(void* unused, void* a, void* b);                       // 0x006bc020
    void* CreateIndex(unsigned unused);                                                 // 0x006bc130
};

// @ 0x006bbe80  allocate + construct a PFRecordWrite
void* ZoneFactory::CreateRecordWrite(unsigned char flags, void* a, void* b, void* c, void* d)
{
    if (flags & 2) {
        void* mem = ZoneAlloc_Named(0x27c, mpAlloc, "Resource/PFRecordWrite");
        if (mem)
            return ((PFRecordWrite*)mem)->Construct(a, b, c, d, this);
    }
    return 0;
}

// @ 0x006bbf10  allocate + construct a shared PFRecordWrite
void* ZoneFactory::CreateRecordWriteShared(unsigned char flags, void* a, void* b, void* c)
{
    if (flags & 2) {
        void* mem = ZoneAlloc_Named(0x27c, mpAlloc, "Resource/PFRecordWrite");
        if (mem)
            return ((PFRecordWriteShared*)mem)->Construct(a, b, 1, c, this);
    }
    return 0;
}

// @ 0x006bbfa0  allocate + construct a PFRecordRead
void* ZoneFactory::CreateRecordRead(void* unused, void* a, void* b)
{
    (void)unused;
    void* mem = ZoneAlloc_Named(0x78, mpAlloc, "Resource/PFRecordRead");
    if (mem)
        return ((PFRecordRead*)mem)->Construct(a, b, this);
    return 0;
}

// @ 0x006bc020  allocate + construct a shared PFRecordRead
void* ZoneFactory::CreateRecordReadShared(void* unused, void* a, void* b)
{
    (void)unused;
    void* mem = ZoneAlloc_Named(0x78, mpAlloc, "Resource/PFRecordRead");
    if (mem)
        return ((PFRecordReadShared*)mem)->Construct(a, b, this);
    return 0;
}

// @ 0x006bc130  allocate + construct a modifiable PFIndex
void* ZoneFactory::CreateIndex(unsigned unused)
{
    (void)unused;
    void* mem = ZoneAlloc_Named(0x4c, mpAlloc, "Resource/PFIndexModifiable");
    if (mem)
        return ((PFIndexModifiable*)mem)->Ctor(mpAlloc);
    return 0;
}
