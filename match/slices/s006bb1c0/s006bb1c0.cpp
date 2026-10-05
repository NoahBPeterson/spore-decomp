// Slice s006bb1c0: Win32 drag/drop + ResourceMan::DatabasePackedFile helpers.
// Same module family: /O2 /MD /Gy /GS- /EHsc /TP /arch:SSE.
#include "types.h"

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
}
void __cdecl EASTL_dealloc(void*);
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
    long* pc = (long*)((char*)self + 0x14);
    long n = InterlockedDecrement(pc);
    if (n == 0 && self) ((void(__thiscall*)(void*, int))(*(void***)self)[0])(self, 1);
    return n;
}

// ---------------------------------------------------------------------------
// remaining functions (partial)
// ---------------------------------------------------------------------------
void __cdecl FUN_006bb1c0(void* self) { (void)self; }
void __cdecl FUN_006bb4b0(void* self) { (void)self; }
void __cdecl FUN_006bb6c0(void* self) { (void)self; }
// @ 0x006bb690 / @ 0x006bb760  DebugMessage destructors
struct AppMsgBase { void* vtbl; virtual ~AppMsgBase() { } };
struct DebugMessage : AppMsgBase {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    virtual ~DebugMessage();
};
DebugMessage::~DebugMessage()
{
    if ((((char*)mpCapacity - (char*)mpBegin) & 0xfffffffe) > 2 && mpBegin) EASTL_dealloc(mpBegin);
}
void __cdecl FUN_006bb8e0(void* self) { (void)self; }
void __cdecl FUN_006bb9b0(void* self) { (void)self; }
void __cdecl FUN_006bba70(void* self) { (void)self; }
void __cdecl FUN_006bbb60(void* self) { (void)self; }
void __cdecl FUN_006bbbf0(void* self) { (void)self; }
void __cdecl FUN_006bbc90(void* self) { (void)self; }
void __cdecl FUN_006bbd80(void* self) { (void)self; }
void __cdecl FUN_006bbde0(void* self) { (void)self; }
void __cdecl FUN_006bbe80(void* self) { (void)self; }
void __cdecl FUN_006bbf10(void* self) { (void)self; }
void __cdecl FUN_006bbfa0(void* self) { (void)self; }
void __cdecl FUN_006bc020(void* self) { (void)self; }
void __cdecl FUN_006bc0a0(void* self) { (void)self; }
void __cdecl FUN_006bc0f0(void* self) { (void)self; }
void __cdecl FUN_006bc130(void* self) { (void)self; }
void __cdecl FUN_006bb830(void* self) { (void)self; }
// @ 0x006bb7b0  GUID equality (library inline) - stub
bool __cdecl FUN_006bb7b0(const void* a, const void* b) { (void)a; (void)b; return false; }
