// src/game/UTFSpore_Win32/ealog_imp.cpp -- migrated from slice(s) s009245b0, s009234f0, s00922500, s00696c80 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ealog_imp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/Trace/Server.h"
#include <string.h>
#include "EA/Trace/LogFilterGroupLevels.h"
#include "EASemaphoreData.h"
#include "EAThreadDynamicData.h"
#include "EA/Thread/Semaphore.h"
#include "EA/Thread/Thread.h"
#include <intrin.h>
#include <windows.h>
#include "EA/Trace/LogReporter.h"
#include "EA/Trace/ILogFilter.h"
#include "EA/Trace/ILogFormatter.h"
#include "EA/Trace/ILogReporter.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "EA/Trace/LogFormatterSimple.h"
#include "EA/Trace/ITracer.h"
#include <new>
#include "EA/Trace/LogFormatterFancy.h"
#include "EAMutexData.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Trace/IServer.h"
#include "EA/Stopwatch.h"
#include "EA/Trace/TraceHelper.h"
#include <stddef.h>
#include <stdio.h>
#include <time.h>

// ---- items of slice s00696c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Trace {
class Server_s0069_6c80 {
 public:
  char pad0[0x94];
  bool mEnabled;                             // +0x94
  bool IsFiltered(unsigned int category);    // 0x923930
  int ShouldLog(unsigned int category);      // 0x697b80
};  // namespace Trace
}  // namespace EA
}
// ---- items of slice s00696c80 end

// ---- items of slice s00922500 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Trace {
void* GetTracer();               // 0x009250f0
}
}
namespace EA {
namespace Trace {
void* GetTraceHelperTable();     // 0x009250e0
}
}
namespace EA {
namespace Trace {
void* GetServer();
}
}
namespace EA {
namespace Trace {
void  UpdateLogFilters();
}
}
struct C233e0 { char pad[0x21c]; unsigned short v; void Set(unsigned short); };
struct C233f0 { void** vtbl; void Call(void* arg); };
// ---- items of slice s00922500 end

// ---- items of slice s009234f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_timeoutP;  // 0x0143dc78
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
extern "C" void  EA_operator_delete(void* p);                                   // 0xf47380
extern "C" void* EA_operator_new(unsigned size, const char* name, int f1, int f2, int f3, int f4); // 0xf473a0
extern "C" void* EA_GetDefaultAllocator();                                      // 0x925cb0
extern "C" size_t strlen(const char*);
namespace EA {
namespace Thread {
struct Mutex_s0092_34f0 {
    unsigned __int64 mData[4];  // +0
    int  mnLockCount;           // +0x20
    bool mbIntraProcess;        // +0x24
    void* mThreadId;            // +0x28
    void Lock(unsigned* pTimeout);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    int  Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
    Mutex_s0092_34f0() {}
    Mutex_s0092_34f0(int name, int intraProcess);
};
}
}
extern "C" int   Vsnprintf8(char* buf, size_t n, const char* fmt, void* ap);    // 0x938400
void EA_DisplayTraceDialog(const char* title, void* msg);            // 0x925100
struct EaStringInit {
    void FUN_0057cc10(const char* s);   // 0x57cc10 (basic_string(const char*) init)
};
struct VaString {
    void FUN_0091a530(const char* fmt, char* ap);   // 0x91a530 (string append_sprintf_va_list)
};
struct SimpleStringOps { void assign(const char* first, const char* last); }; // 0x942e50
struct FancyStringOps {
    void assign(const char* first, const char* last);   // 0x60a150
};
struct Stopwatch_s0092_34f0 {
    void* Stopwatch_ctor(int units, int start);   // 0x93a560 (EA::Stopwatch::Stopwatch, thiscall)
};
void* eastl_RBTreeIncrement(void* node);                             // 0x921580 (returns node)
void eastl_RBTreeErase(void* z, void* anchor);                       // 0x921880
void eastl_RBTreeInsert(void* node, void* parent, void* anchor, int color); // 0x9216a0
void* eastl_RBTreeDecrement(void* node);                             // 0x9215c0
void eastl_copy_impl(void* first, void* last, void* dest);           // 0x6782c0
struct EaStringOps { void assign(const char* first, const char* last); };       // 0x454cb0
namespace EA {
namespace Trace {
struct IUnknown32 {
    virtual ~IUnknown32() {}
    virtual void AddRef() {}
    virtual void Release() {}
    virtual void QueryInterface() {}
};
}
}
namespace EA {
namespace Trace {
struct ILogFilter_s0092_34f0 : IUnknown32 {
    virtual void f2() {}
    virtual void f3() {}
    virtual int  IsFiltered(void* rec) { (void)rec; return 0; }  // +0x14
};
}
}
namespace EA {
namespace Trace {
struct ILogFormatter_s0092_34f0 : IUnknown32 {
    virtual void f2() {}
    virtual void f3() {}
    virtual void f4() {}
    virtual void f5() {}
    virtual void f6() {}
};
}
}
namespace EA {
namespace Trace {
struct ILogReporter_s0092_34f0 : IUnknown32 {
    virtual void r2() {}
    virtual void r3() {}
    virtual void r4() {}
    virtual void r5() {}
    virtual const char* GetName() { return 0; }   // +0x1c
};
}
}
namespace EA {
namespace Trace {
template <class T> struct AutoRefCount {
    T* mpObject;   // +0
};
}
}
namespace EA {
namespace Trace {
struct EaString {
    char* mpBegin;     // +0
    char* mpEnd;       // +4
    char* mpCapacity;  // +8
    void* mAllocator;  // +0xc
};
}
}
namespace EA {
namespace Trace {
struct FixedString512 {
    char* mpBegin;     // +0
    char* mpEnd;       // +4
    char* mpCapacity;  // +8
    void* mpAlloc;     // +0xc
    void* mpPool;      // +0x10
    char buffer[512];  // +0x14
};
}
}
namespace EA {
namespace Trace {
struct FixedString2048 {
    char* mpBegin;     // +0
    char* mpEnd;       // +4
    char* mpCapacity;  // +8
    void* mpAlloc;     // +0xc
    void* mpPool;      // +0x10
    char buffer[2048]; // +0x14
};
}
}
namespace EA {
namespace Trace {
struct RBNodeBase {
    RBNodeBase* mpLeft;    // +0
    RBNodeBase* mpRight;   // +4
    RBNodeBase* mpParent;  // +8
    char mColor;           // +0xc
};
}
}
namespace EA {
namespace Trace {
struct RBNode {
    RBNode* mpLeft;        // +0
    RBNode* mpRight;       // +4
    RBNode* mpParent;      // +8
    char mColor;           // +0xc
    char pad[3];
    const char* mpKey;     // +0x10
    int mnValue;           // +0x14
};
}
}
namespace EA {
namespace Trace {
struct RBTreeMap {
    void* mpPool;          // +0
    RBNodeBase mAnchor;    // +4
    int mnSize;            // +0x14
    void* mpAllocator;     // +0x18
    void* mpAllocator2;    // +0x1c

    void  DeallocNode(RBNode* node);
    void  DoNukeSubtree(RBNode* node);
    RBNode** find(RBNode** out, const char** key);
    RBNode** erase(RBNode** outNext, RBNode* pos);
    void  DoInsertValueImpl(RBNode** out, RBNode* parent, const void* value, char hasParent);
    void  DoInsertValue(RBNode** out, const void* value);
};
}
}
namespace EA {
namespace Trace {
struct LogReporter_s0092_34f0 : ILogReporter_s0092_34f0 {
    AutoRefCount<ILogFilter_s0092_34f0>    mFilter;    // +4
    AutoRefCount<ILogFormatter_s0092_34f0> mFormatter; // +8
    bool mIsEnabled;                        // +0xc
    char pad0[3];
    int  mnRefCount;                        // +0x10
    EaString mName;                         // +0x14

    LogReporter_s0092_34f0(const char* name);
    virtual ~LogReporter_s0092_34f0();
    void SetName(const char* name);  // 0x00923fe0 (EA::Trace::LogReporter::SetName)

    int  FilterEnabled(void* rec);          // @ 0x923700
    int  FilterEnabled2(void* rec);         // @ 0x923740
    void ShowAlert(void* rec);              // @ 0x923a60
    int  DebugPrint(void* rec);             // @ 0x923aa0
    int  SkipFilter1(void* rec);            // @ 0x924270
    int  SkipFilter2(void* rec);            // @ 0x9242b0
    int  SkipFilter3(void* rec);            // @ 0x924350
    int  SkipFilter4(void* rec);            // @ 0x924390
    void* ScalarDeletingDtor(char flags);   // @ 0x9242f0
};
}
}
namespace EA {
namespace Trace {
struct LogFilterGroupLevels_s0092_34f0 : ILogFilter_s0092_34f0 {
    int      mnRefCount;     // +4
    EaString mName;          // +8
    int      mGlobalLevel;   // +0x18
    RBTreeMap mGroupLevelMap;// +0x1c

    LogFilterGroupLevels_s0092_34f0(void* cfg);  // 0x00923f30 (EA::Trace::LogFilterGroupLevels::LogFilterGroupLevels_s0092_34f0)
    virtual ~LogFilterGroupLevels_s0092_34f0();  // 0x00923f30 (EA::Trace::LogFilterGroupLevels::LogFilterGroupLevels_s0092_34f0)
    void SetName(const char* name);  // 0x00923fe0 (EA::Trace::LogFilterGroupLevels::SetName)
    bool RemoveGroupLevel(const char* name);  // 0x00923bc0 (EA::Trace::LogFilterGroupLevels::RemoveGroupLevel)
    bool IsFiltered2(void* rec);  // 0x00923c90 (EA::Trace::LogFilterGroupLevels::IsFiltered2)
};
}
}
namespace EA {
namespace Trace {
struct LogFormatterSimple_s0092_34f0 : ILogFormatter_s0092_34f0 {
    int  mnRefCount;             // +4
    FixedString2048 mName;       // +0x8  (0x814 bytes)
    FixedString2048 mLine;       // +0x81c

    LogFormatterSimple_s0092_34f0(const char* name);  // 0x009243d0 (EA::Trace::LogFormatterSimple::LogFormatterSimple_s0092_34f0)
    virtual ~LogFormatterSimple_s0092_34f0();  // 0x009243d0 (EA::Trace::LogFormatterSimple::LogFormatterSimple_s0092_34f0)
    void SetName(const char* name);  // 0x00924450 (EA::Trace::LogFormatterSimple::SetName)
    void* Clone();  // 0x00924490 (EA::Trace::LogFormatterSimple::Clone)
};
}
}
namespace EA {
namespace Trace {
struct LogFormatterFancy_s0092_34f0 : ILogFormatter_s0092_34f0 {
    int  mnRefCount;             // +4
    FixedString512 mName;        // +0x8
    unsigned short mnFlags;      // +0x21c
    char pad0[2];
    int  mnFileInfoLevel;        // +0x220
    char pad1[4];
    char mTimer[0x18];           // +0x228 Stopwatch
    FixedString2048 mLine;       // +0x240

    LogFormatterFancy_s0092_34f0(const char* name);  // 0x009244d0 (EA::Trace::LogFormatterFancy::LogFormatterFancy_s0092_34f0)
    virtual ~LogFormatterFancy_s0092_34f0();  // 0x009244d0 (EA::Trace::LogFormatterFancy::LogFormatterFancy_s0092_34f0)
    void SetName(const char* name);  // 0x00924570 (EA::Trace::LogFormatterFancy::SetName)
};
}
}
namespace EA {
namespace Trace {
struct IServer_s0092_34f0 {
    virtual void s0();  // 0x009236c0
    virtual void s1();  // 0x009236d0
    virtual void s2();  // 0x00924cf0
    virtual void s3();  // 0x00923680
    virtual void s4();  // 0x007f30d0
    virtual void s5();  // 0x00924790
    virtual void s6();  // 0x009234e0
    virtual void s7();  // 0x009248f0
    virtual void s8();  // 0x009241f0
    virtual void s9();  // 0x00924a50
    virtual void s10();  // 0x00923840
    virtual void s11();  // 0x009237c0
    virtual void s12();  // 0x00924a80
    virtual void s13();  // 0x009238b0
    virtual void s14();  // 0x009238f0
};
}
}
namespace EA {
namespace Trace {
struct ITracer_s0092_34f0 {
    virtual void t0();  // 0x00697eb0
    virtual void t1();  // 0x00697ed0
    virtual void t2();  // 0x00923db0
    virtual void t3();  // 0x00697ec0
    virtual void t4();  // 0x00923990
    virtual void t5();  // 0x009234f0
    virtual void t6();  // 0x00923930
};
}
}
namespace EA {
namespace Trace {
struct Server_s0092_34f0 : IServer_s0092_34f0, ITracer_s0092_34f0 {
    bool mbIsReporting;      // +0x8
    char pad0[3];
    char* mpHeapBuffer;      // +0xc
    int   mnHeapBufferSize;  // +0x10
    int   mLogRecordCounter; // +0x14
    void* mpVecBegin;        // +0x18
    void* mpVecEnd;          // +0x1c
    void* mpVecCapacity;     // +0x20
    char pad1[4];
    void* mDefaultFilter;    // +0x28
    void* mDefaultFormatter; // +0x2c
    int   mUnknown30;        // +0x30
    int   mnRefCount;        // +0x34
    EA::Thread::Mutex_s0092_34f0 mMutex;// +0x38

    Server_s0092_34f0();  // 0x00923d40 (EA::Trace::Server::Server_s0092_34f0)
    ~Server_s0092_34f0();  // 0x00923d40 (EA::Trace::Server::Server_s0092_34f0)
    const char* GetLevelName(int level);  // 0x00923630 (EA::Trace::Server::GetLevelName)
    Server_s0092_34f0* AsInterface(int id);  // 0x00923680 (EA::Trace::Server::AsInterface)
    int Release();  // 0x009236d0 (EA::Trace::Server::Release)
    bool GetLogReporter(char* name, int* out);  // 0x009237c0 (EA::Trace::Server::GetLogReporter)
    unsigned EnumerateLogReporters(void** out, unsigned max);  // 0x00923840 (EA::Trace::Server::EnumerateLogReporters)
    bool RemoveLogReporter(ILogReporter_s0092_34f0* p);  // 0x009241f0 (EA::Trace::Server::RemoveLogReporter)
};
}
}
namespace EA {
namespace Trace {
struct IReporterView {
    virtual void a0() = 0;
    virtual void a1() = 0;
    virtual void a2() = 0;
    virtual void a3() = 0;
    virtual bool Skips(void* rec) = 0;              // +0x10
    virtual bool IsFiltered(void* rec) = 0;         // +0x14
    virtual unsigned Report(void* rec) = 0;         // +0x18
};
}
}
namespace EA {
namespace Trace {
struct TraceRecord {                                 // 0x18 bytes, vtable 0x143dc7c
    virtual void rv0() {}
    int         mnZero;                              // +4
    int         mnCounter;                           // +8
    void*       mpSender;                            // +0xc
    const char* mpMessage;                           // +0x10
    const char* mpLevelName;                         // +0x14
};
}
}
namespace EA {
namespace Trace {
struct ServerTracer {
    virtual void t0() = 0;
    virtual void t1() = 0;
    virtual void t2() = 0;
    virtual void t3() = 0;
    virtual unsigned TraceString(void* sender, const char* msg) = 0;   // +0x10
    bool  mbIsReporting;           // +4
    char  pad5[3];
    char* mpHeapBuffer;            // +8
    int   mnHeapBufferSize;        // +0xc
    int   mLogRecordCounter;       // +0x10
    IReporterView** mpReportersBegin;   // +0x14
    IReporterView** mpReportersEnd;     // +0x18
    IReporterView** mpReportersCap;     // +0x1c
    char  pad6[4];                      // +0x20
    void* mDefaultFilter;               // +0x24
    void* mDefaultFormatter;            // +0x28
    int   mUnknown2c;                   // +0x2c
    int   mnRefCount;                   // +0x30
    char  mMutex[0x2c];                 // +0x34 EA::Thread::Mutex (raw: its 8-byte alignment would pad the vfptr)
    EA::Thread::Mutex_s0092_34f0* M() { return (EA::Thread::Mutex_s0092_34f0*)mMutex; }

    unsigned TraceVaList(void* sender, const char* fmt, void* ap);     // original 0x9234f0
    unsigned Trace(void* sender, const char* msg);                     // original 0x923990
    bool IsFiltered(void* rec);                                        // original 0x923930 (Server::IsFiltered, ITracer side)
};
}
}
extern "C" char DAT_01667bac;
// ---- items of slice s009234f0 end

// ---- items of slice s009245b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_timeout_143dc78;
namespace EA {
namespace Thread {
struct EAMutexData { unsigned __int64 mData[4]; int mnLockCount; bool mbIntraProcess; void* mThreadId; };
}
}
namespace EA {
namespace Thread {
class Mutex_s0092_45b0 {
public:
    EAMutexData mMutexData;
    void Lock(unsigned* pTimeout);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    int  Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
    ~Mutex_s0092_45b0();
};
}
}
extern "C" void* __cdecl eanew6(int size, const char* name, int a, int b, int c, int d);
namespace EA {
namespace Trace {
struct IObj {                       // IRefCount-style: AddRef, Release, ?, Cast
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    virtual void v2();              // +0x08
    virtual void* Cast(unsigned id); // +0x0c
};
}
}
namespace EA {
namespace Trace {
struct ILogFilter_s0092_45b0 : IObj {
    virtual void v4();
    virtual void v5();
    virtual void SetName(const char*);   // +0x18
    virtual const char* GetName();       // +0x1c
    virtual ILogFilter_s0092_45b0* Clone();         // +0x20
};
}
}
namespace EA {
namespace Trace {
struct ILogFormatter_s0092_45b0 : IObj {
    virtual void v4();
    virtual void SetName(const char*);   // +0x14
    virtual void v6();
    virtual ILogFormatter_s0092_45b0* Clone();      // +0x1c
};
}
}
namespace EA {
namespace Trace {
struct ILogReporter_s0092_45b0 : IObj {
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual const char* GetName();             // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void SetFilter(ILogFilter_s0092_45b0*);       // +0x2c
    virtual ILogFilter_s0092_45b0* GetFilter();           // +0x30
    virtual void SetFormatter(ILogFormatter_s0092_45b0*); // +0x34
    virtual ILogFormatter_s0092_45b0* GetFormatter();     // +0x38
};
}
}
namespace EA {
namespace Trace {
struct LogRecordInfo { int pad0[3]; int level; const char* group; const char* file; int line; const char* func; };
}
}
namespace EA {
namespace Trace {
struct ILogRecord {
    virtual void v0(); virtual void v1();
    virtual const char* GetGroup();   // +0x08
    virtual const char* GetText();    // +0x0c
    int pad4, pad8;
    LogRecordInfo* mpInfo;            // +0x0c (object field)
};
}
}
namespace EA {
namespace Trace {
struct FString {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void push_back(char c);                              // 0x00924c60
    void append(const char* b, const char* e);           // 0x00942e50 / 0x009199c0
    void reserve(unsigned n);                            // 0x00887090
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
}
}
namespace EA {
namespace Trace {
void __cdecl FormatInto(FString* s, const char* fmt, ...);  // 0x00923dc0
}
}
namespace EA {
namespace Trace {
inline unsigned CharStrlen(const char* p) { const char* q = p; const char* b = p + 1; while (*q++) {} return (unsigned)(q - b); }
}
}
namespace EA {
namespace Trace {
#define cstrend(p) ((p) + CharStrlen(p))
}
}
namespace EA {
namespace Trace {
struct Stopwatch {
    int pad[6];
    unsigned __int64 GetElapsedTime();   // 0x0093a5e0
    void Restart();                      // 0x00571e80
};
}
}
namespace EA {
namespace Trace {
struct LogFormatterFancy_s0092_45b0 : ILogFormatter_s0092_45b0 {
    int mnRefCount;
    char mName[0x21c - 8];
    unsigned short mnFlags;              // +0x21c
    char pad21e[2];
    int mnFileInfoLevel;                 // +0x220
    int pad224;
    Stopwatch mTimer;                    // +0x228
    FString mLine;                       // +0x240
    LogFormatterFancy_s0092_45b0(const char* name); // 0x009244d0
    ILogFormatter_s0092_45b0* Clone();  // 0x009245b0 (EA::Trace::LogFormatterFancy::Clone)
    const char* FormatRecord(ILogRecord* r);  // 0x00924d90 (EA::Trace::LogFormatterFancy::FormatRecord)
};
}
}
namespace EA {
namespace Trace {
struct LogFormatterSimple_s0092_45b0 : ILogFormatter_s0092_45b0 {
    char pad[0x81c - 4];
    FString mLine;                       // +0x81c
    LogFormatterSimple_s0092_45b0(const char* name); // 0x009243d0
    const char* FormatRecord(ILogRecord* r);  // 0x00924d10 (EA::Trace::LogFormatterSimple::FormatRecord)
};
}
}
namespace EA {
namespace Trace {
struct RBNodeBase_s0092_45b0 { RBNodeBase_s0092_45b0* mpNodeRight; RBNodeBase_s0092_45b0* mpNodeLeft; RBNodeBase_s0092_45b0* mpNodeParent; int mColor; };
}
}
namespace EA {
namespace Trace {
struct RBNode_s0092_45b0 : RBNodeBase_s0092_45b0 { const char* key; int value; };
}
}
namespace EA {
namespace Trace {
struct RBIter { RBNode_s0092_45b0* mpNode; };
}
}
namespace EA {
namespace Trace {
struct GroupLevelMap {                   // eastl::map<const char*, int, KeyLess, EASTLCoreAllocator>
    void find(RBIter* out, const char** key);                 // 0x00923ac0
    void DoInsertValue(void* out, void* val, int flag);       // 0x00924060
};
}
}
namespace EA {
namespace Trace {
RBNodeBase_s0092_45b0* __cdecl RBTreeIncrement(RBNodeBase_s0092_45b0* n);                   // 0x00921580
}
}
namespace EA {
namespace Trace {
struct ICoreAllocator { static ICoreAllocator* GetDefaultAllocator(); };  // 0x00925cb0
}
}
namespace EA {
namespace Trace {
struct LogFilterGroupLevels_s0092_45b0 : ILogFilter_s0092_45b0 {
    int mnRefCount;                      // +0x04
    char* mNameBegin;                    // +0x08
    char* mNameEnd;                      // +0x0c
    char* mNameCap;                      // +0x10
    int pad14;
    int mGlobalLevel;                    // +0x18
    int mapBase;                         // +0x1c: GroupLevelMap object
    RBNodeBase_s0092_45b0 mAnchor;                  // +0x20
    int mnSize;                          // +0x30
    ICoreAllocator* mAllocator;          // +0x34
    int mnFlags;                         // +0x38
    LogFilterGroupLevels_s0092_45b0(const char* name);   // 0x00923f30
    __declspec(noinline) void AddGroupLevel(const char* group, int level);  // 0x00924600 (EA::Trace::LogFilterGroupLevels::AddGroupLevel)
    void RemoveGroupLevel(const char* group);                 // 0x00923bc0
    ILogFilter_s0092_45b0* Clone();  // 0x009246c0 (EA::Trace::LogFilterGroupLevels::Clone)
};
}
}
namespace EA {
namespace Trace {
extern char g_empty_01667bac[];
}
}
namespace EA {
namespace Trace {
extern char g_vtbl_LogFilterGroupLevels[];  // 0x0143dd9c
}
}
namespace EA {
namespace Trace {
template<class T> struct AutoRef { T* p; ~AutoRef() { if (p) p->Release(); } };
}
}
namespace EA {
namespace Trace {
struct ILogReporterVec {
    ILogReporter_s0092_45b0** mpBegin; ILogReporter_s0092_45b0** mpEnd; ILogReporter_s0092_45b0** mpCapacity;
    void erase(ILogReporter_s0092_45b0** first, ILogReporter_s0092_45b0** last);   // 0x00e25bd0
    void DoInsertValue(ILogReporter_s0092_45b0** pos, ILogReporter_s0092_45b0** v); // 0x00a0a360
    ~ILogReporterVec();                                       // 0x00ae6970
};
}
}
namespace EA {
namespace Trace {
struct IServer_s0092_45b0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void ApplyReporters();                              // +0x18
    virtual bool AddLogReporter(ILogReporter_s0092_45b0* r);               // +0x1c
    virtual void RemoveReporter(ILogReporter_s0092_45b0* r);               // +0x20
    virtual void v9(); virtual void v10();
    virtual bool FindReporter(const char* name, ILogReporter_s0092_45b0** out);  // +0x2c
    ~IServer_s0092_45b0() {}
};
}
}
namespace EA {
namespace Trace {
struct ITracerBase { virtual void t0(); ~ITracerBase() {} };
}
}
namespace EA {
namespace Trace {
struct Server_s0092_45b0 : IServer_s0092_45b0, ITracerBase {
    int pad8;
    char* mpHeapBuffer;                   // +0x0c
    int pad10, pad14;
    ILogReporterVec mLogReporters;        // +0x18
    int pad24, pad28;
    AutoRef<ILogFilter_s0092_45b0> mpFilter;         // +0x2c
    AutoRef<ILogFormatter_s0092_45b0> mpFormatter;   // +0x30
    int pad34;
    EA::Thread::Mutex_s0092_45b0 mMutex;             // +0x38
    void Init();  // 0x00924790 (EA::Trace::Server::Init)
    virtual bool AddLogReporter(ILogReporter_s0092_45b0* r);  // 0x009248f0 (EA::Trace::Server::AddLogReporter)
    bool SetOutputLevel(const char* name, const char* group, int level);
    ~Server_s0092_45b0();
    void RemoveAllLogReporters();  // 0x00924a50 (EA::Trace::Server::RemoveAllLogReporters)
};
}
}
namespace EA {
namespace Trace {
struct LogReporter_s0092_45b0 { LogReporter_s0092_45b0(const char* name); };      // 0x00924170
}
}
namespace EA {
namespace Trace {
extern char g_vtbl_ReporterDebugger[], g_vtbl_ReporterDialog[], g_vtbl_Server_b[], g_vtbl_base[];
}
}
// ---- items of slice s009245b0 end

// @ 0x00697b80
namespace EA { namespace Trace {
int Server_s0069_6c80::ShouldLog(unsigned int category)
{
  if (mEnabled) {
    if (!IsFiltered(category)) return 0;
  }
  return 1;
}
}}  // namespace EA::Trace

// @ 0x009233e0
void C233e0::Set(unsigned short x)
{
    v = x;
}

// @ 0x009233f0
void C233f0::Call(void* arg)
{
    void* v = *(void**)((char*)arg + 0xc);
    (*(void(__thiscall**)(void*, void*))((char*)vtbl + 0x14))(this, v);
}

// @ 0x00923440
int __fastcall FUN_00923440(void* self)
{
    int n = *(int*)((char*)self + 4);
    if (n > 1) {
        *(int*)((char*)self + 4) = n - 1;
        return n - 1;
    }
    (*(void(__thiscall**)(void*, int))((char*)*(void**)self + 8))(self, 1);
    return 0;
}

// @ 0x009234a0
int __fastcall FUN_009234a0(void* self)
{
    int n = *(int*)((char*)self + 0x10);
    if (n > 1) {
        *(int*)((char*)self + 0x10) = n - 1;
        return n - 1;
    }
    (*(void(__thiscall**)(void*, int))((char*)*(void**)self + 8))(self, 1);
    return 0;
}

// @ 0x009234c0
void* EA::Trace::GetServer()
{
    void* p = EA::Trace::GetTracer();
    if (p != 0)
        return (*(void*(__thiscall**)(void*, int))((char*)*(void**)p + 0xc))(p, 0x23ab34a1);
    return 0;
}

// @ 0x009234e0
void EA::Trace::UpdateLogFilters()
{
    void* p = EA::Trace::GetTraceHelperTable();
    (*(void(__thiscall**)(void*))((char*)*(void**)p + 0x14))(p);
}

// @ 0x009234f0
unsigned EA::Trace::ServerTracer::TraceVaList(void* sender, const char* fmt, void* ap)
{
    char buf[256];
    if (fmt == 0) {
        return 0;
    }
    EA::Thread::Mutex_s0092_34f0* m = (EA::Thread::Mutex_s0092_34f0*)((char*)this + 0x34);
    m->Lock((unsigned*)&g_timeoutP);
    if (mbIsReporting) {
        m->Unlock();
        return 0;
    }
    unsigned r;
    int n = Vsnprintf8(buf, 0x100, fmt, ap);
    buf[255] = 0;
    if (n >= -1) {
        if (n >= 0) {
            if (n < 0x100) {
                r = TraceString(sender, buf);
                goto done;
            }
            int sz = mnHeapBufferSize;
            if (sz <= n) {
                if (sz < n) {
                    do {
                        sz = mnHeapBufferSize * 2;
                        mnHeapBufferSize = sz;
                    } while (sz < n);
                }
                EA_operator_delete(mpHeapBuffer);
                mpHeapBuffer = (char*)EA_operator_new((unsigned)mnHeapBufferSize, "EATrace/Server/HeapBuffer/char[]", 0, 0, 0, 0);
            }
        }
        n = Vsnprintf8(mpHeapBuffer, (size_t)mnHeapBufferSize, fmt, ap);
        mpHeapBuffer[mnHeapBufferSize - 1] = 0;
        if (n >= -1) {
            r = TraceString(sender, mpHeapBuffer);
            goto done;
        }
    }
    r = 0;
done:
    m->Unlock();
    return r;
}

// @ 0x00923630
char const * EA::Trace::Server::GetLevelName(int level) const
{
    if (level <= 0xa)  return "Private";
    if (level <= 0x19) return "Debug";
    if (level <= 0x32) return "Info";
    if (level <= 0x64) return "Warn";
    if (level <= 0x96) return "Error";
    return "Fatal";
}

// @ 0x00923680
void * EA::Trace::Server::AsInterface(EA::COM::InterfaceId id)
{
    Server* self = this;
    if (id == 0x23ab34a1)
        return self;
    if (id != 0x6c7ca8e4)
        return (id == (int)0xee3f516e) ? self : 0;
    if (self)
        return (Server*)((char*)self + 4);
    return 0;
}

// @ 0x009236d0
int EA::Trace::Server::Release()
{
    int n = _InterlockedExchangeAdd((volatile long*)&mnRefCount.mValue, -1);
    --n;
    if (n == 0) {
        _InterlockedExchange((volatile long*)&mnRefCount.mValue, 1);
        if (this)
            ((void(__thiscall*)(void*, int))(*(void***)this)[2])(this, 1);
        return 0;
    }
    return n;
}

// @ 0x00923700
int EA::Trace::LogReporter_s0092_34f0::FilterEnabled(void* rec)
{
    EA::Trace::LogReporter_s0092_34f0* self = this;
    if (self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool r = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[5])(self->mFilter.mpObject, rec);
        if (!r)
            return 0;
    }
    return 1;
}

// @ 0x00923740
int EA::Trace::LogReporter_s0092_34f0::FilterEnabled2(void* rec)
{
    EA::Trace::LogReporter_s0092_34f0* self = this;
    if (self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool r = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[4])(self->mFilter.mpObject, rec);
        if (!r)
            return 0;
    }
    return 1;
}

// @ 0x009237c0
bool EA::Trace::Server_s0092_34f0::GetLogReporter(char* name, int* out)
{
    mMutex.Lock((unsigned*)&g_timeoutP);
    *out = 0;
    void** it = (void**)mpVecBegin;
    void** end = (void**)mpVecEnd;
    while (it != end) {
        EA::Trace::ILogReporter_s0092_34f0* p = *(EA::Trace::ILogReporter_s0092_34f0**)*it;
        const char* s = ((const char*(__thiscall*)(void*))(*(void***)p)[7])(p);
        if (_stricmp(s, name) == 0) {
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            *out = (int)p;
            break;
        }
        ++it;
    }
    bool r = *out != 0;
    mMutex.Unlock();
    return r;
}

// @ 0x00923840
unsigned EA::Trace::Server_s0092_34f0::EnumerateLogReporters(void** out, unsigned max)
{
    mMutex.Lock((unsigned*)&g_timeoutP);
    unsigned n = 0;
    if (out != 0) {
        void** it = (void**)mpVecBegin;
        void** end = (void**)mpVecEnd;
        while (it != end) {
            if (n >= max)
                break;
            EA::Trace::ILogReporter_s0092_34f0* p = (EA::Trace::ILogReporter_s0092_34f0*)*it;
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            out[n] = p;
            ++it;
            ++n;
        }
    }
    mMutex.Unlock();
    return n;
}

// @ 0x00923930
bool EA::Trace::ServerTracer::IsFiltered(void* rec)
{
    M()->Lock((unsigned*)&g_timeoutP);
    EA::Trace::IReporterView** it = mpReportersBegin;
    EA::Trace::IReporterView** end = mpReportersEnd;
    while (it != end) {
        if (!(*it)->IsFiltered(rec)) {
            M()->Unlock();
            return false;
        }
        ++it;
    }
    M()->Unlock();
    return true;
}

// @ 0x00923990
unsigned EA::Trace::ServerTracer::Trace(void* sender, const char* msg)
{
    unsigned flags = 0;
    if (msg != 0) {
        EA::Thread::Mutex_s0092_34f0* m = (EA::Thread::Mutex_s0092_34f0*)((char*)this + 0x34);
        m->Lock((unsigned*)&g_timeoutP);
        if (!mbIsReporting) {
            EA::Trace::TraceRecord rec;
            rec.mnCounter = mLogRecordCounter++;
            mbIsReporting = true;
            rec.mpSender = sender;
            rec.mnZero = 0;
            rec.mpMessage = msg;
            rec.mpLevelName = ((EA::Trace::Server_s0092_34f0*)((char*)this - 4))->GetLevelName(*(int*)((char*)sender + 0xc));
            EA::Trace::IReporterView** p = mpReportersBegin;
            EA::Trace::IReporterView** end = mpReportersEnd;
            for (; p != end; ++p) {
                EA::Trace::IReporterView* rep = *p;
                if (!rep->Skips(&rec)) {
                    flags |= rep->Report(&rec);
                }
            }
            mbIsReporting = false;
        }
        m->Unlock();
    }
    return flags;
}

// @ 0x00923a60
void EA::Trace::LogReporter_s0092_34f0::ShowAlert(void* rec)
{
    void* fmt = ((void*(__thiscall*)(void*, void*))(*(void***)mFormatter.mpObject)[4])(mFormatter.mpObject, rec);
    const char* name = ((const char*(__thiscall*)(void*))(*(void***)rec)[2])(rec);
    if (name == 0)
        name = "Alert";
    EA_DisplayTraceDialog(name, fmt);
}

// @ 0x00923aa0
int EA::Trace::LogReporter_s0092_34f0::DebugPrint(void* rec)
{
    const char* s = ((const char*(__thiscall*)(void*, void*))(*(void***)mFormatter.mpObject)[4])(mFormatter.mpObject, rec);
    OutputDebugStringA(s);
    return 0;
}

// @ 0x00923ac0
EA::Trace::RBNode** EA::Trace::RBTreeMap::find(EA::Trace::RBNode** out, const char** key)
{
    EA::Trace::RBNode* end = (EA::Trace::RBNode*)&mAnchor;
    EA::Trace::RBNode* candidate = end;
    EA::Trace::RBNode* node = (EA::Trace::RBNode*)mAnchor.mpParent;
    while (node) {
        if (!(_stricmp(node->mpKey, *key) < 0)) {
            candidate = node;
            node = node->mpRight;
        } else {
            node = node->mpLeft;
        }
    }
    if (candidate != end && !(_stricmp(*key, candidate->mpKey) < 0)) {
        *out = candidate;
        return out;
    }
    *out = end;
    return out;
}

// @ 0x00923b40
void EA::Trace::RBTreeMap::DoNukeSubtree(EA::Trace::RBNode* node)
{
    while (node) {
        DoNukeSubtree(node->mpLeft);
        EA::Trace::RBNode* next = node->mpRight;
        ((void(__thiscall*)(void*, EA::Trace::RBNode*, int))(*(void***)mpAllocator)[3])(mpAllocator, node, 0x18);
        node = next;
    }
}

// @ 0x00923b80
EA::Trace::RBNode** EA::Trace::RBTreeMap::erase(EA::Trace::RBNode** outNext, EA::Trace::RBNode* pos)
{
    mnSize--;
    EA::Trace::RBNode* next = (EA::Trace::RBNode*)eastl_RBTreeIncrement(pos);
    eastl_RBTreeErase(pos, &mAnchor);
    ((void(__thiscall*)(void*, EA::Trace::RBNode*, int))(*(void***)mpAllocator)[3])(mpAllocator, pos, 0x18);
    *outNext = next;
    return outNext;
}

// @ 0x00923bc0
bool EA::Trace::LogFilterGroupLevels_s0092_34f0::RemoveGroupLevel(const char* name)
{
    if (name == 0 || *name == 0) {
        EA::Trace::RBNodeBase* end = &mGroupLevelMap.mAnchor;
        for (EA::Trace::RBNode* n = (EA::Trace::RBNode*)end->mpLeft; n != (EA::Trace::RBNode*)end; n = (EA::Trace::RBNode*)eastl_RBTreeIncrement(n))
            EA_operator_delete((void*)n->mpKey);
        EA::Trace::RBNodeBase* root = (EA::Trace::RBNodeBase*)end->mpParent;
        while (root) {
            mGroupLevelMap.DoNukeSubtree((EA::Trace::RBNode*)((EA::Trace::RBNode*)root)->mpRight);
            EA::Trace::RBNodeBase* next = root->mpLeft;
            ((void(__thiscall*)(void*, EA::Trace::RBNodeBase*, int))(*(void***)mGroupLevelMap.mpAllocator)[3])(mGroupLevelMap.mpAllocator, root, 0x18);
            root = next;
        }
        end->mpLeft = end;
        end->mpRight = end;
        end->mpParent = 0;
        end->mColor = 0;
        mGroupLevelMap.mnSize = 0;
        return false;
    }
    EA::Trace::RBNode* found = 0;
    mGroupLevelMap.find(&found, &name);
    if (found != (EA::Trace::RBNode*)&mGroupLevelMap.mAnchor) {
        EA_operator_delete((void*)found->mpKey);
        EA::Trace::RBNode* next = 0;
        mGroupLevelMap.erase(&next, found);
        return true;
    }
    return false;
}

// @ 0x00923c90
bool EA::Trace::LogFilterGroupLevels_s0092_34f0::IsFiltered2(void* rec)
{
    char* name = *(char**)((char*)rec + 0x10);
    if (name != 0 && *name != 0) {
        EA::Trace::RBNode* it;
        EA::Trace::RBNode* found = *mGroupLevelMap.find(&it, (const char**)&name);
        if (found != (EA::Trace::RBNode*)&mGroupLevelMap.mAnchor)
            return *(int*)((char*)rec + 0xc) < found->mnValue;
    }
    return *(int*)((char*)rec + 0xc) < mGlobalLevel;
}

// @ 0x00923cf0
EA::Trace::LogReporter_s0092_34f0::~LogReporter_s0092_34f0()
{
    _ReadWriteBarrier();
    if ((mName.mpCapacity - mName.mpBegin) > 1 && mName.mpBegin != 0)
        EA_operator_delete(mName.mpBegin);
    if (mFormatter.mpObject)
        ((void(__thiscall*)(void*))(*(void***)mFormatter.mpObject)[1])(mFormatter.mpObject);
    if (mFilter.mpObject)
        ((void(__thiscall*)(void*))(*(void***)mFilter.mpObject)[1])(mFilter.mpObject);
}

// @ 0x00923d40
EA::Trace::Server_s0092_34f0::Server_s0092_34f0()
{
    mbIsReporting = 0;
    mpHeapBuffer = (char*)EA_operator_new(0x1000, "EATrace/Server/HeapBuffer/char[]", 0, 0, 0, 0);
    mnHeapBufferSize = 0x1000;
    mLogRecordCounter = 0;
    mpVecBegin = 0;
    mpVecEnd = 0;
    mpVecCapacity = 0;
    // +0x28 (mDefaultFilter) is left uninitialised by the original
    mDefaultFormatter = 0;
    mUnknown30 = 0;
    _InterlockedExchange((volatile long*)&mnRefCount, 0);
    new (&mMutex) EA::Thread::Mutex_s0092_34f0(0, 1);
}

// @ 0x00923dc0
void* FUN_00923dc0(void* out, const char* fmt, ...)
{
    char* ap = (char*)&fmt + sizeof(fmt);
    ((VaString*)out)->FUN_0091a530(fmt, ap);
    return out;
}

// @ 0x00923de0
void EA::Trace::RBTreeMap::DoInsertValueImpl(EA::Trace::RBNode** out, EA::Trace::RBNode* parent, const void* value, char hasParent)
{
    char color = 0;
    if (!hasParent && parent != (EA::Trace::RBNode*)&mAnchor) {
        const char* k = *(const char**)value;
        if (_stricmp(k, parent->mpKey) >= 0)
            color = 1;
    }
    EA::Trace::RBNode* node = (EA::Trace::RBNode*)((void*(__thiscall*)(void*, int, int, int))(*(void***)mpAllocator)[2])(mpAllocator, 0x18, 0, (int)mpAllocator2);
    if (node) {
        node->mpKey = *(const char**)value;
        node->mnValue = *(int*)((char*)value + 4);
    }
    eastl_RBTreeInsert(node, parent, &mAnchor, color);
    mnSize++;
    if (out) *out = node;
}

// @ 0x00923e70
EA::Trace::LogFormatterSimple_s0092_34f0::~LogFormatterSimple_s0092_34f0()
{
    EA::Trace::FixedString2048* line = &mLine;
    if ((line->mpCapacity - line->mpBegin) > 1 && line->mpBegin != 0 && line->mpBegin != line->mpPool)
        EA_operator_delete(line->mpBegin);
    EA::Trace::FixedString2048* nm = &mName;
    if ((nm->mpCapacity - nm->mpBegin) > 1 && nm->mpBegin != 0 && nm->mpBegin != nm->mpPool)
        EA_operator_delete(nm->mpBegin);
}

// @ 0x00923ed0
EA::Trace::LogFormatterFancy_s0092_34f0::~LogFormatterFancy_s0092_34f0()
{
    EA::Trace::FixedString2048* line = &mLine;
    if ((line->mpCapacity - line->mpBegin) > 1 && line->mpBegin != 0 && line->mpBegin != line->mpPool)
        EA_operator_delete(line->mpBegin);
    EA::Trace::FixedString512* nm = &mName;
    if ((nm->mpCapacity - nm->mpBegin) > 1 && nm->mpBegin != 0 && nm->mpBegin != nm->mpPool)
        EA_operator_delete(nm->mpBegin);
}

// @ 0x00923f30
EA::Trace::LogFilterGroupLevels_s0092_34f0::LogFilterGroupLevels_s0092_34f0(void* cfg)
{
    mnRefCount = 0;
    mName.mpBegin = 0;
    mName.mpEnd = 0;
    mName.mpCapacity = 0;
    ((EaStringInit*)&mName)->FUN_0057cc10((const char*)cfg);
    mGlobalLevel = 1;
    void* alloc = EA_GetDefaultAllocator();
    EA::Trace::RBNodeBase* anchor = &mGroupLevelMap.mAnchor;
    // the original zeroes anchor dwords +4..+0xc (color and its padding as one dword) first
    struct Zero3 { int a, b, c; };
    *(Zero3*)((int*)anchor + 1) = Zero3();
    mGroupLevelMap.mpAllocator = alloc;
    mGroupLevelMap.mpAllocator2 = 0;
    anchor->mpParent = 0;
    anchor->mColor = 0;
    mGroupLevelMap.mnSize = 0;
    anchor->mpRight = anchor;
    anchor->mpLeft = anchor;
}

// @ 0x00923f90
EA::Trace::LogFilterGroupLevels_s0092_34f0::~LogFilterGroupLevels_s0092_34f0()
{
    _ReadWriteBarrier();
    mGlobalLevel = 1;
    char dummy = 0;
    RemoveGroupLevel(&dummy);
    EA::Trace::RBNode* root = (EA::Trace::RBNode*)mGroupLevelMap.mAnchor.mpParent;
    mGroupLevelMap.DoNukeSubtree(root);
    if ((mName.mpCapacity - mName.mpBegin) > 1 && mName.mpBegin != 0)
        EA_operator_delete(mName.mpBegin);
}

// @ 0x00923fe0
void EA::Trace::LogFilterGroupLevels_s0092_34f0::SetName(const char* name)
{
    ((EaStringOps*)&mName)->assign(name, name + strlen(name));
}

// @ 0x00924060
void EA::Trace::RBTreeMap::DoInsertValue(EA::Trace::RBNode** out, const void* value)
{
    EA::Trace::RBNode* node = (EA::Trace::RBNode*)mAnchor.mpParent;
    EA::Trace::RBNode* parent = (EA::Trace::RBNode*)&mAnchor;
    char less = 1;
    while (node) {
        int c = _stricmp(*(const char**)value, node->mpKey);
        less = c < 0;
        parent = node;
        if (less) node = node->mpRight;
        else      node = node->mpLeft;
    }
    EA::Trace::RBNode* spot = parent;
    if (less) {
        if (parent == (EA::Trace::RBNode*)mAnchor.mpRight) {
            DoInsertValueImpl(out, parent, value, 0);
            return;
        }
        spot = (EA::Trace::RBNode*)eastl_RBTreeDecrement(parent);
    }
    if (_stricmp(spot->mpKey, *(const char**)value) < 0) {
        DoInsertValueImpl(out, parent, value, 0);
    } else {
        if (out) *out = spot;
    }
}

// @ 0x00924170
EA::Trace::LogReporter::LogReporter(char const * name)
{
    mFilter.mpObject = 0;
    mFormatter.mpObject = 0;
    mIsEnabled = true;
    mnRefCount = 0;
    mName.mpBegin = (char*)&DAT_01667bac;
    mName.mpEnd = (char*)&DAT_01667bac;
    mName.mpCapacity = (char*)&DAT_01667bac + 1;
    ((EaStringOps*)&mName)->assign(name, name + strlen(name));
    if (mFilter.mpObject)
        ((void(__thiscall*)(void*, const char*))(*(void***)mFilter.mpObject)[6])(mFilter.mpObject, name);
    if (mFormatter.mpObject)
        ((void(__thiscall*)(void*, const char*))(*(void***)mFormatter.mpObject)[5])(mFormatter.mpObject, name);
}

// @ 0x009241f0
bool EA::Trace::Server_s0092_34f0::RemoveLogReporter(EA::Trace::ILogReporter_s0092_34f0* p)
{
    mMutex.Lock((unsigned*)&g_timeoutP);
    void** it = (void**)mpVecBegin;
    while (it != (void**)mpVecEnd) {
        if (*it == p)
            break;
        ++it;
    }
    if (it == (void**)mpVecEnd) {
        mMutex.Unlock();
        return false;
    }
    if ((char*)it + 4 < (char*)mpVecEnd) {
        eastl_copy_impl((char*)it + 4, mpVecEnd, it);
    }
    mpVecEnd = (char*)mpVecEnd - 4;
    EA::Trace::ILogReporter_s0092_34f0* last = *(EA::Trace::ILogReporter_s0092_34f0**)mpVecEnd;
    if (last)
        ((void(__thiscall*)(void*))(*(void***)last)[1])(last);
    mMutex.Unlock();
    return true;
}

// @ 0x00924270
int EA::Trace::LogReporter_s0092_34f0::SkipFilter1(void* rec)
{
    void* r = rec;
    EA::Trace::LogReporter_s0092_34f0* self = this;
    if ((*(unsigned char*)((char*)r + 8) & 1) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[5])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x009242b0
int EA::Trace::LogReporter_s0092_34f0::SkipFilter2(void* rec)
{
    void* r = rec;
    EA::Trace::LogReporter_s0092_34f0* self = this;
    if ((*(unsigned char*)(*(char**)((char*)r + 0xc) + 8) & 1) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[4])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x00924350
int EA::Trace::LogReporter_s0092_34f0::SkipFilter3(void* rec)
{
    void* r = rec;
    EA::Trace::LogReporter_s0092_34f0* self = this;
    if ((*(unsigned char*)((char*)r + 8) & 2) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[5])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x00924390
int EA::Trace::LogReporter_s0092_34f0::SkipFilter4(void* rec)
{
    void* r = rec;
    EA::Trace::LogReporter_s0092_34f0* self = this;
    if ((*(unsigned char*)(*(char**)((char*)r + 0xc) + 8) & 2) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[4])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x009243d0
EA::Trace::LogFormatterSimple_s0092_34f0::LogFormatterSimple_s0092_34f0(const char* name)
{
    EA::Trace::FixedString2048* b = &mName;
    mnRefCount = 0;
    b->mpPool = b->buffer;
    b->mpEnd = b->buffer;
    b->mpBegin = b->buffer;
    b->mpCapacity = b->buffer + 0x800;
    b->buffer[0] = 0;
    ((SimpleStringOps*)&mName)->assign(name, name + strlen(name));
    EA::Trace::FixedString2048* l = &mLine;
    l->mpPool = l->buffer;
    l->mpEnd = l->buffer;
    l->mpBegin = l->buffer;
    l->mpCapacity = l->buffer + 0x800;
    l->buffer[0] = 0;
}

// @ 0x00924450
void EA::Trace::LogFormatterSimple_s0092_34f0::SetName(const char* name)
{
    EA::Trace::FixedString2048* s = &mName;
    char* p = s->mpBegin;
    if (p != name) {
        if (p != s->mpEnd) {
            *p = 0;
            s->mpEnd = s->mpBegin;
        }
        ((SimpleStringOps*)s)->assign(name, name + strlen(name));
    }
}

// @ 0x00924490
void* EA::Trace::LogFormatterSimple_s0092_34f0::Clone()
{
    EA::Trace::LogFormatterSimple_s0092_34f0* p = (EA::Trace::LogFormatterSimple_s0092_34f0*)EA_operator_new(0x1030, "EATrace/LogFormatterSimple/LogFormatterSimple", 0, 0, 0, 0);
    if (p != 0)
        return new (p) EA::Trace::LogFormatterSimple_s0092_34f0(mName.mpBegin);
    return 0;
}

// @ 0x009244d0
EA::Trace::LogFormatterFancy_s0092_34f0::LogFormatterFancy_s0092_34f0(const char* name)
{
    EA::Trace::FixedString512* b = &mName;
    mnRefCount = 0;
    b->mpPool = b->buffer;
    b->mpEnd = b->buffer;
    b->mpBegin = b->buffer;
    b->mpCapacity = b->buffer + 0x200;
    b->buffer[0] = 0;
    ((FancyStringOps*)&mName)->assign(name, name + strlen(name));
    mnFlags = 0;
    mnFileInfoLevel = 100;
    ((Stopwatch_s0092_34f0*)&mTimer)->Stopwatch_ctor(4, 1);
    EA::Trace::FixedString2048* l = &mLine;
    l->mpPool = l->buffer;
    l->mpEnd = l->buffer;
    l->mpBegin = l->buffer;
    l->mpCapacity = l->buffer + 0x800;
    l->buffer[0] = 0;
}

// @ 0x00924570
void EA::Trace::LogFormatterFancy_s0092_34f0::SetName(const char* name)
{
    EA::Trace::FixedString512* s = &mName;
    char* p = s->mpBegin;
    if (p != name) {
        if (p != s->mpEnd) {
            *p = 0;
            s->mpEnd = s->mpBegin;
        }
        ((FancyStringOps*)s)->assign(name, name + strlen(name));
    }
}

// @ 0x009245b0
EA::Trace::ILogFormatter * EA::Trace::LogFormatterFancy::Clone()
{
    void* m = eanew6(0xa58, "EATrace/LogFormatterFancy/LogFormatterFancy", 0, 0, 0, 0);
    LogFormatterFancy* r = m ? new (m) LogFormatterFancy(*(const char**)((char*)this + 8)) : 0;
    r->mnFlags = mnFlags;
    r->mnFileInfoLevel = mnFileInfoLevel;
    return r;
}

// @ 0x00924600
namespace EA { namespace Trace {
void LogFilterGroupLevels_s0092_45b0::AddGroupLevel(const char* group, int level)
{
    if (group && *group) {
        RBIter it;
        const char* key = group;
        ((GroupLevelMap*)&mapBase)->find(&it, &key);
        if ((RBNodeBase_s0092_45b0*)it.mpNode == &mAnchor) {
            size_t n = strlen(group) + 1;
            char* copy = (char*)eanew6((int)n, "EATrace/LogFilterGroupLevels/GroupContainer/char[]", 0, 0, 0, 0);
            int off = (int)(copy - group);
            const char* s = group;
            char c;
            do { c = *s; ((char*)s)[off] = c; ++s; } while (c != 0);
            struct { const char* k; int v; } val = { copy, level };
            char out[8];
            ((GroupLevelMap*)&mapBase)->DoInsertValue(out, &val, 0);
        } else {
            it.mpNode->value = level;
        }
    } else {
        mGlobalLevel = level;
    }
}
}}  // namespace EA::Trace

// @ 0x009246c0
namespace EA { namespace Trace {
ILogFilter_s0092_45b0* LogFilterGroupLevels_s0092_45b0::Clone()
{
    LogFilterGroupLevels_s0092_45b0* p = (LogFilterGroupLevels_s0092_45b0*)eanew6(0x3c, "EATrace/LogFilterGroupLevels/LogFilterGroupLevels", 0, 0, 0, 0);
    if (p) {
        *(void**)p = g_vtbl_LogFilterGroupLevels;
        p->mnRefCount = 0;
        p->mNameBegin = g_empty_01667bac;
        p->mNameEnd = g_empty_01667bac;
        p->mNameCap = g_empty_01667bac + 1;
        p->mGlobalLevel = 1;
        ICoreAllocator* a = ICoreAllocator::GetDefaultAllocator();
        RBNodeBase_s0092_45b0* an = &p->mAnchor;
        an->mpNodeLeft = 0;
        an->mpNodeParent = 0;
        an->mColor = 0;
        p->mAllocator = a;
        p->mnFlags = 0;
        an->mpNodeRight = an;
        an->mpNodeLeft = an;
        an->mpNodeParent = 0;
        *(char*)&an->mColor = 0;
        p->mnSize = 0;
    }
    LogFilterGroupLevels_s0092_45b0* r = p ? p : 0;
    r->SetName(GetName());
    char nul = 0;
    r->AddGroupLevel(&nul, mGlobalLevel);
    RBNodeBase_s0092_45b0* n = mAnchor.mpNodeLeft;
    while (n != &mAnchor) {
        r->AddGroupLevel(((RBNode_s0092_45b0*)n)->key, ((RBNode_s0092_45b0*)n)->value);
        n = RBTreeIncrement(n);
    }
    return r;
}
}}  // namespace EA::Trace

// @ 0x00924790
namespace EA { namespace Trace {
void Server_s0092_45b0::Init()
{
    mMutex.Lock(&g_timeout_143dc78);
    if (!mpFilter.p) {
        void* m = eanew6(0x3c, "EATrace/Server/DefaultFilter/LogFilterGroupLevels", 0, 0, 0, 0);
        ILogFilter_s0092_45b0* f = m ? (ILogFilter_s0092_45b0*)new (m) LogFilterGroupLevels_s0092_45b0("DefaultFilter") : 0;
        ILogFilter_s0092_45b0* old = mpFilter.p;
        if (f != old) {
            if (f) f->AddRef();
            mpFilter.p = f;
            if (old) old->Release();
        }
    }
    if (!mpFormatter.p) {
        void* m = eanew6(0x1030, "EATrace/Server/DefaultFormatter/LogFormatterSimple", 0, 0, 0, 0);
        ILogFormatter_s0092_45b0* f = m ? (ILogFormatter_s0092_45b0*)new (m) LogFormatterSimple_s0092_45b0("DefaultFormatter") : 0;
        ILogFormatter_s0092_45b0* old = mpFormatter.p;
        if (f != old) {
            if (f) f->AddRef();
            mpFormatter.p = f;
            if (old) old->Release();
        }
    }
    if (mLogReporters.mpBegin == mLogReporters.mpEnd) {
        ILogReporter_s0092_45b0* r;
        void* m = eanew6(0x24, "EATrace/Server/LogReporterDebugger", 0, 0, 0, 0);
        if (m) { new (m) LogReporter_s0092_45b0("AppDebugger"); *(void**)m = g_vtbl_ReporterDebugger; r = (ILogReporter_s0092_45b0*)m; } else r = 0;
        AddLogReporter(r);
        m = eanew6(0x24, "EATrace/Server/LogReporterDialog", 0, 0, 0, 0);
        if (m) { new (m) LogReporter_s0092_45b0("AppAlertDialog"); *(void**)m = g_vtbl_ReporterDialog; r = (ILogReporter_s0092_45b0*)m; } else r = 0;
        AddLogReporter(r);
    }
    ApplyReporters();
    mMutex.Unlock();
}
}}  // namespace EA::Trace

// @ 0x009248f0
namespace EA { namespace Trace {
bool Server_s0092_45b0::AddLogReporter(ILogReporter_s0092_45b0* rep)
{
    EA::Thread::Mutex_s0092_45b0* mtx = &mMutex;
    mtx->Lock(&g_timeout_143dc78);
    ILogReporter_s0092_45b0* existing = 0;
    if (FindReporter(rep->GetName(), &existing)) {
        if (existing == rep) goto done;
        RemoveReporter(existing);
        if (existing) { ILogReporter_s0092_45b0* e = existing; existing = 0; e->Release(); }
    }
    if (!rep->GetFormatter() && mpFormatter.p) {
        ILogFormatter_s0092_45b0* f = mpFormatter.p->Clone();
        f->SetName(rep->GetName());
        rep->SetFormatter(f);
    }
    if (!rep->GetFilter() && mpFilter.p) {
        ILogFilter_s0092_45b0* f = mpFilter.p->Clone();
        f->SetName(rep->GetName());
        rep->SetFilter(f);
    }
    {
        ILogReporter_s0092_45b0* tmp = rep;
        rep->AddRef();
        if (mLogReporters.mpEnd < mLogReporters.mpCapacity) {
            ILogReporter_s0092_45b0** p = mLogReporters.mpEnd;
            mLogReporters.mpEnd = p + 1;
            if (p) { *p = tmp; tmp->AddRef(); }
        } else {
            mLogReporters.DoInsertValue(mLogReporters.mpEnd, &tmp);
        }
        if (tmp) tmp->Release();
    }
done:
    if (existing) existing->Release();
    mtx->Unlock();
    return true;
}
}}  // namespace EA::Trace

// @ 0x00924a50
void EA::Trace::Server::RemoveAllLogReporters()
{
    mMutex.Lock(g_timeout_143dc78);
    mLogReporters.erase(mLogReporters.mpBegin, mLogReporters.mpEnd);
    mMutex.Unlock();
}

// @ 0x00924a80
namespace EA { namespace Trace {
bool Server_s0092_45b0::SetOutputLevel(const char* name, const char* group, int level)
{
    mMutex.Lock(&g_timeout_143dc78);
    bool ok = true;
    if (name) {
        ILogReporter_s0092_45b0* rep = 0;
        if (FindReporter(name, &rep)) {
            ILogFilter_s0092_45b0* f = rep->GetFilter();
            if (f) {
                LogFilterGroupLevels_s0092_45b0* lg = (LogFilterGroupLevels_s0092_45b0*)f->Cast(0x2e9e25fe);
                if (lg) {
                    if (level == 0) lg->RemoveGroupLevel(group);
                    else lg->AddGroupLevel(group, level);
                }
            }
        } else {
            ok = false;
        }
        if (rep) rep->Release();
    } else {
        ILogFilter_s0092_45b0* df = mpFilter.p;
        if (df) {
            LogFilterGroupLevels_s0092_45b0* lg = (LogFilterGroupLevels_s0092_45b0*)df->Cast(0x2e9e25fe);
            if (lg) {
                if (level == 0) lg->RemoveGroupLevel(group);
                else lg->AddGroupLevel(group, level);
            }
        }
        ILogReporter_s0092_45b0** it = mLogReporters.mpBegin;
        ILogReporter_s0092_45b0** end = mLogReporters.mpEnd;
        for (; it != end; ++it) {
            ILogFilter_s0092_45b0* f = (*it)->GetFilter();
            if (f) {
                LogFilterGroupLevels_s0092_45b0* lg = (LogFilterGroupLevels_s0092_45b0*)f->Cast(0x2e9e25fe);
                if (lg) {
                    if (level == 0) lg->RemoveGroupLevel(group);
                    else lg->AddGroupLevel(group, level);
                }
            }
        }
    }
    mMutex.Unlock();
    return ok;
}
}}  // namespace EA::Trace

// @ 0x00924c60
namespace EA { namespace Trace {
void FString::push_back(char c)
{
    if (mpEnd + 1 == mpCapacity) {
        unsigned nSize = mpEnd - mpBegin;
        unsigned nCap = mpCapacity - mpBegin;
        unsigned a = (nCap - 1 > 8) ? (nCap - 1) * 2 : 8;
        unsigned b = nSize + 1;
        const unsigned& m1 = (a < b) ? b : a;
        a = m1;
        unsigned s2 = nSize;
        const unsigned& m2 = (s2 < a) ? a : s2;
        unsigned want = m2 + 1;
        if (want > nCap) reserve(want);
    }
    *mpEnd = c;
    ++mpEnd;
    *mpEnd = 0;
}
}}  // namespace EA::Trace

// @ 0x00924d10
namespace EA { namespace Trace {
const char* LogFormatterSimple_s0092_45b0::FormatRecord(ILogRecord* r)
{
    const char* text = r->GetText();
    mLine.append(text, cstrend(text));
    unsigned n = mLine.size();
    if (n == 0 || mLine.mpBegin[n - 1] != '\n') mLine.push_back('\n');
    LogRecordInfo* info = r->mpInfo;
    if (info->level >= 100) FormatInto(&mLine, "%s(%d): %s\n", info->file, info->line, info->func);
    return mLine.mpBegin;
}
}}  // namespace EA::Trace

// @ 0x00924d90
namespace EA { namespace Trace {
const char* LogFormatterFancy_s0092_45b0::FormatRecord(ILogRecord* r)
{
    LogRecordInfo* info = r->mpInfo;
    const char* text = r->GetText();
    if (mnFlags != 0 || info->level >= mnFileInfoLevel) {
        if (mLine.mpBegin != mLine.mpEnd) { *mLine.mpBegin = 0; mLine.mpEnd = mLine.mpBegin; }
        if (mnFlags & 3) {
            unsigned __int64 t = mTimer.GetElapsedTime();
            __time64_t secs = (__time64_t)(t / 1000);
            unsigned ms = (unsigned)(t % 1000);
            struct tm* tmv = _gmtime64(&secs);
            char buf[32];
            if (mnFlags & 4) {
                size_t n = strftime(buf, 32, "%H:%M:%S", tmv);
                sprintf(buf + n, ":%03d ", ms);
            } else {
                strftime(buf, 32, "%H:%M:%S ", tmv);
            }
            mLine.append(buf, cstrend(buf));
            if (mnFlags & 2) mTimer.Restart();
        }
        if (mnFlags & 8) {
            __time64_t now = _time64(0);
            struct tm* tmv = _localtime64(&now);
            char buf[32];
            strftime(buf, 32, "%b %d %H:%M:%S ", tmv);
            mLine.append(buf, cstrend(buf));
        }
        if (mnFlags & 0x10) {
            const char* g = info->group;
            mLine.append(g, cstrend(g));
            mLine.push_back(' ');
        }
        if (mnFlags & 0x20) {
            const char* g = r->GetGroup();
            mLine.append(g, cstrend(g));
            mLine.push_back(' ');
        }
        mLine.append(text, cstrend(text));
        unsigned n = mLine.size();
        if (n == 0 || mLine.mpBegin[n - 1] != '\n') mLine.push_back('\n');
        if (info->level >= mnFileInfoLevel)
            FormatInto(&mLine, "%s(%d): %s\n", info->file, info->line, info->func);
        text = mLine.mpBegin;
    }
    return text;
}
}}  // namespace EA::Trace
