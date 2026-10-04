// Shared declarations for the PlayMode movie / YouTube module (retail layout).
#pragma once
#include "types.h"
#include <string.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
void* operator new(size_t size, int align, const char* name, void* alloc);   // 0x009512D0
void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0x00F473A0 (EASTL allocator_allocate)
void operator delete(void* p);                                                  // 0x00F47380
inline void* operator new(size_t, void* p) { return p; }

namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
struct allocator {
    void deallocate(void* p) { operator delete[](p); }
};
template <typename T, typename Allocator = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;
}

namespace EA { eastl::string16 ConvertToString16(const char* p, int length = -1); }   // 0x0093C5A0

// ref-counted COM-like base
struct IRefCounted { virtual int AddRef(); virtual int Release(); virtual void s2(); virtual void Stop(int a); };
struct IRangeTarget { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
    virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46();
    virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60();
    virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
    virtual void s68(); virtual void s69(); virtual void s70();
    virtual void SetRange(const uint64_t* a, const uint64_t* b, int mode);   // +0x11C
};
template <class T>
struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

struct IWindow {   // UTFWin window (slots used by this module)
    virtual int AddRef();
    virtual int Release();
    virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual uint32_t GetControlID();   // +0x1C
    virtual void s08(); virtual void s09(); virtual uint32_t GetFlags(); virtual void s11();   // GetFlags +0x28
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void SetFlag(int flag, int on);                    // +0x7C
    virtual void SetCaption(const wchar_t* text);              // +0x80
    virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42();
    virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
    virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59();
    virtual IWindow* FindWindowByID(uint32_t id, bool recurse);   // +0xF0
    virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
    virtual void RemoveWinProc(void* proc);                       // +0x108
};

struct cSPUILayout {   // 0x18 bytes (retail)
    uint32_t pad[6];
    IWindow* FindWindowByID(uint32_t id, bool recurse);   // 0x008105B0
    void Shutdown(bool b);                                // 0x00811AD0
    cSPUILayout();                                        // 0x00810000
};

struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
};
IMessageServer* GetMessageServer();   // 0x0067DCC0

struct cSPVector4 { float x, y, z, w; cSPVector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };

float GetElapsedSeconds();                          // 0x00805080
void  BeginModal(IWindow* w, int a, int b);         // 0x008099A0 (cdecl)
void  EndModal(IWindow* w, int a, int b);           // 0x00809C50 (cdecl)

// UTFWin custom window proc base (+0 IWinProc, +4 ISerializable, +8 refcount)
struct IWinProc {
    virtual int AddRef(); virtual int Release();
    virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual void s07(); virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
};
struct ISerializable { virtual int s0(); virtual int s1(); };
struct CustomWinProc : IWinProc, ISerializable {
    int mRefCount;
    CustomWinProc() : mRefCount(0) {}
};

// ---------------------------------------------------------------------------------------------
// EA::Stopwatch (0x18 bytes). GetElapsedTime is out of line (0x0093A3A0); the float conversion is inline.
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)

struct Stopwatch {
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfCoeff;
    Stopwatch(int units, bool start);                 // 0x0093A560 (out of line)
    uint64_t GetElapsedTime() const;                  // 0x0093A3A0
    float GetElapsedTimeFloat() const { return (float)(int64_t)GetElapsedTime() * mfCoeff; }
    void Stop();                                      // 0x0093A2E0
    void Restart();                                   // 0x00571E80
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    void Start()
    {
        if (!mnStartTime) {
            if (mnUnits == 1)
                mnStartTime = __rdtsc();
            else {
                int64_t t;
                QueryPerformanceCounter(&t);
                mnStartTime = t;
            }
        }
    }
};

struct cProfScope { void End(); };                       // 0x0067C420
cProfScope* __stdcall BeginProfScope(int a, int b);      // 0x0067CAC0

struct cString {   // 0x14 bytes (retail)
    uint32_t pad[5];
    cString();                                                       // 0x006B5060
    ~cString();                                                      // 0x006B5240
};

struct cSPPlayModeUI {   // retail layout (partial)
    uint32_t pad0[0x44 / 4];
    bool mbLayoutInit;                              // +0x44
    void FUN_00635350(int a, int b);                // 0x00635350
    IWindow* FindEditorUIWindow(uint32_t id);       // 0x00634E40
    bool GetItemVisible(uint32_t id);               // 0x00634E60
    bool IsCheckButtonSelected(uint32_t id);        // 0x00635850
    void SetSelected(uint32_t id, bool b);          // 0x00634EC0
    bool IsUIGroupEnabled(uint32_t id);             // 0x00635890
    void SetUIGroupVisible(uint32_t id, bool on);   // 0x00635760
    void SetEditorUIGroupVisible(uint32_t id, bool on);   // 0x00635790
    void SetEnableTakePictureButton(bool b);        // 0x00635600
    void SetEnableRecordMovieButton(bool b);        // 0x00635680
    void SetEnableNewCreatureButton(bool b);        // 0x00635580
    const wchar_t* GetPhotoName(wchar_t* buf, int n);   // 0x00634E50 (original: caller cleans the 2 args)
};

struct IMovieSystemObj { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void s11(); virtual bool IsRecording(); };    // +0x30
IMovieSystemObj* GetMovieSystem();                         // 0x0067CB10

struct ISaveArea { virtual void s0(); virtual void s1(); virtual void s2(); virtual uint32_t GetTypeID();   // +0xC
                   virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
                   virtual const wchar_t* GetPath(); };   // +0x28
ISaveArea* GetSaveArea(uint32_t id);                       // 0x006B1F90 (cdecl)

void ShowMessageBoxEx(const void* a, const void* b);       // 0x00809DB0 (cdecl)
extern char gMsgA[];   // 0x01524C60
extern char gDialogText[];   // 0x013EC468

void RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);   // 0x00571DB0 (cdecl)
struct cAutoHandler {
    uint32_t a, b, c, d, e;
    cAutoHandler() : a(0), b(0), c(0), d(0), e(0) {}
    ~cAutoHandler()
    {
        if (a) {
            uint32_t ta = a, tb = b, tc = c, td = d, te = e;
            a = 0;
            RemoveHandler(ta, tb, tc, td, te);
        }
    }
};

struct cSPPlayModeSubModeBase { virtual ~cSPPlayModeSubModeBase() {} virtual void b1(); uint32_t pad[4];
    void Init(void* arg);   // 0x0063B270
};
struct IHandler { virtual ~IHandler() {} virtual int h1(); };

struct cSPPlayModePhotoBrowser {   // 0xEC0 bytes
    uint32_t pad[0xec0 / 4];
    cSPPlayModePhotoBrowser();            // 0x00630A50
    ~cSPPlayModePhotoBrowser();           // 0x00630930
    void Init(cSPPlayModeUI* ui);         // 0x006339E0
    void Shutdown();                      // 0x00632F30
    void ShowImageThumbnail();            // 0x00633CC0
    void UpdatePhotoCountText();          // 0x00630D10
    void FUN_00630580(uint32_t dt);          // 0x00630580
    bool FUN_006304e0();                  // 0x006304E0
    void FUN_006303a0();                  // 0x006303A0
    void FUN_00631df0(void* p);           // 0x00631DF0
};
