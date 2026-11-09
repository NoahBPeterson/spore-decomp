// src/game/UTFSpore_Win32/_at_008d0000.cpp -- migrated from slice(s) s008dd0d0, s008dc1a0, s008d62f0, s008d5340, s008d4520, s008d35d0, s008d2590, s008d1b30 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_008d0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <math.h>
#include <string.h>
#include "EA/IO/FileStream.h"
#include "EA/Thread/Mutex.h"
#include <new>
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/ResourceMan/Key.h"
#include "EA/IO/MemoryStream.h"
#include "EA/ResourceMan/PFIndexModifiable.h"
#include "EA/ResourceMan/PFRecordInfo.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "EA/ResourceMan/PFRecordWrite.h"
#include "EA/ResourceMan/Record.h"
#include "EA/SharedLibrary.h"

// ---- items of slice s008d1b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct DeviceInfo {
    int type;
    int unused;
    unsigned index;
    wchar_t name[32];
};
struct IDirectInput8W_ {
    virtual long __stdcall QueryInterface(void*, void**);
    virtual long __stdcall AddRef();
    virtual unsigned long __stdcall Release();                                            // +0x08
    virtual long __stdcall CreateDevice(const void* guid, void** dev, void* outer);        // +0x0c
    virtual long __stdcall s4();
    virtual long __stdcall EnumDevices(unsigned type, void* cb, void* ctx, unsigned flags); // +0x14
    virtual long __stdcall s6();
    virtual long __stdcall s7();
    virtual long __stdcall s8();
    virtual long __stdcall s9();
    virtual long __stdcall s10();
    virtual long __stdcall s11();
    virtual long __stdcall s12();
    virtual long __stdcall s13();
    virtual long __stdcall s14();
    virtual long __stdcall s15();
};
struct IDirectInputDevice8W_ {
    virtual long __stdcall QueryInterface(void*, void**);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual long __stdcall GetCapabilities(void* caps);                   // +0x0c
    virtual long __stdcall s4();
    virtual long __stdcall s5();
    virtual long __stdcall s6();
    virtual long __stdcall Acquire();                                     // +0x1c
    virtual long __stdcall Unacquire();
    virtual long __stdcall GetDeviceState(unsigned long cb, void* data);  // +0x24
    virtual long __stdcall s10();
    virtual long __stdcall s11();
    virtual long __stdcall s12();
    virtual long __stdcall s13();
    virtual long __stdcall SetDataFormat(const void* fmt);                // +0x38
    virtual long __stdcall s15();
    virtual long __stdcall s16();
    virtual long __stdcall s17();
    virtual long __stdcall SetProperty(const void* guid, const void* hdr); // +0x2c
    virtual long __stdcall s19();
    virtual long __stdcall s20();
    virtual long __stdcall s21();
    virtual long __stdcall s22();
    virtual long __stdcall s23();
    virtual long __stdcall s24();
    virtual long __stdcall Poll();                                        // +0x64
};
namespace EA {
namespace Input {
class InputMan;
}
}
namespace EA {
namespace Input {
class Device { public:
    virtual ~Device() {}
    virtual bool GetDeviceState(unsigned long cb, void* data) { return false; }
    virtual void Unacquire() {}
    virtual void Acquire() {}
    virtual bool Poll() { return false; }
};
}
}
namespace EA {
namespace Input {
class Controller : public Device { public:
    InputMan* mpInputMan;               // +0x04
    unsigned mnIndex;                   // +0x08
    unsigned short mRepeatCount[24];    // +0x0c
    float mState[24];                   // +0x3c
    bool mbAvailable;                   // +0x9c
    unsigned mnLastEventTime;           // +0xa0
    bool mbXInputDevice;                // +0xa4
    unsigned mnXInputIndex;             // +0xa8
    IDirectInputDevice8W_* mpDIController; // +0xac
    int mAxisMapping[4];                // +0xb0

    void GetDeviceInfo(DeviceInfo* info);
    float GetControlValue(unsigned id, bool bBinary);
    bool GetControlButton(unsigned id, bool bPressed);
    bool GetControlStates(float* out, bool bBinary);
};
}
}
namespace EA {
namespace Input {
class Keyboard : public Device { public:
    InputMan* mpInputMan;               // +0x04
    unsigned mnIndex;                   // +0x08
    bool mbAvailable;                   // +0x0c
};
}
}
namespace EA {
namespace Input {
class Mouse : public Device { public:
    InputMan* mpInputMan;               // +0x04
    unsigned mnIndex;                   // +0x08
    bool mbAvailable;                   // +0x0c
    int mXMin, mYMin, mXMax, mYMax;     // +0x10
};
}
}
namespace EA {
namespace Input {
class InputMan { public:
    virtual ~InputMan();                                                  // +0x00
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void OnControllerAvailability(Controller* c, bool bAvailable); // +0x20

    void* mpDeviceChangeCallback;          // +0x04
    void* mpDeviceChangeCallbackContext;   // +0x08
    void* mpPollCompletionCallback;        // +0x0c
    void* mpPollCompletionCallbackContext; // +0x10
    void* mpEventCallback;                 // +0x14
    void* mpEventCallbackContext;          // +0x18
    unsigned mnEventCallbackDeviceTypeMask;// +0x1c
    bool mbInitialized;                    // +0x20
    float mfNoiseThreshold;                // +0x24
    float mfBinaryThreshold;               // +0x28
    float mfAutomaticPollingRateMS;        // +0x2c
    int mnLogLevel;                        // +0x30
    Controller mController[4];             // +0x34
    Keyboard mKeyboard;                    // +0x334
    Mouse mMouse;                          // +0x344
    IDirectInput8W_* mpDI;                 // +0x364
    unsigned mnDIEnumCount;                // +0x368
    IDirectInputDevice8W_* mpDIEnumControllers[4]; // +0x36c

    InputMan();
    void GetControllerDeviceInfo(unsigned idx, DeviceInfo* info);          // 0x8d2330
    bool UpdateControl(Controller* c, int idx, float v, char bNormalized, unsigned dt); // 0x8d24e0
    void UpdateController(unsigned idx);
    void PollAll();
    bool Init();                                                           // 0x8d1df0
    bool Shutdown();                                                       // 0x8d20c0
    void SetConfig(int id, float v);                                       // 0x8d2110
    unsigned EnumDevices(void* out, unsigned count);                       // 0x8d21a0
    void* GetDeviceByType(int type, unsigned idx);                         // 0x8d2250
    void* SetDeviceChangeCallback(void* cb, int unused, void* ctx);        // 0x8d2290
    void FireDeviceChangeCallback(int a, int b);                           // 0x8d22b0
    void* SetPollCompletionCallback(void* cb, int unused, void* ctx);      // 0x8d22d0
    void* SetEventCallback(unsigned mask, void* cb, void* ctx);            // 0x8d22f0
    void FireEventCallback(void* p);                                       // 0x8d2310
};
}
}
// ---- items of slice s008d1b30 end

// ---- items of slice s008d2590 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct InputEvent {
    int a, b, c, d, e, f;
    char g, h;
    InputEvent();
    InputEvent(int d_, int e_, int f_, char g_, int c_, char h_);
};
struct Binding {
    int f0, f4, f8, fc, f10;
    signed char c14, c15;
    unsigned short s16;
    int f18;
};
struct BindingTable {
    char pad[8];
    Binding b[32];
    unsigned count;

    Binding* FindBinding(int fc, int c14, int c15);
    Binding* FindBindingMasked(int f4, int c14, int c15, unsigned mask);
};
// ---- items of slice s008d2590 end

// ---- items of slice s008d35d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00c7ea30(void* first, void* last, void* dest);
extern "C" void  FUN_00edba80(void* first, void* last, void* dest);
extern "C" char  PTR_FUN_01435990;
extern "C" char  PTR_FUN_01435980;
struct TSI;
struct OwnerNode;
struct RunRec {
    OwnerNode*     mpOwner;   // +0x00
    int            mKey4;     // +0x04
    int            mKey8;     // +0x08
    int            mKeyC;     // +0x0c
    float          mf10;      // +0x10
    signed char    mb14;      // +0x14
    signed char    mb15;      // +0x15
    unsigned short mFlags16;  // +0x16
    unsigned short mDup18;    // +0x18
};
typedef void (*RunNotifyFn)(int, RunRec*, void*);
struct IRunProvider {
    virtual void* slot0();
    virtual void* slot4(void* key, void* a, void* b);   // vtable +0x04
    virtual void* slot8();
    virtual char  slotC(void* data, void* container);   // vtable +0x0c
};
struct OwnerNode {
    OwnerNode*    mpNext;   // +0x00
    OwnerNode*    mpPrev;   // +0x04
    int           mKey8;    // +0x08
    IRunProvider* mpIface;  // +0x0c
    RunNotifyFn   mpFn;     // +0x10
    void*         mpData;   // +0x14
    unsigned char mFlag;    // +0x18
};
struct VAlloc {
    virtual void  s0();
    virtual void  s4();
    virtual void* allocate(unsigned n, int a, void* name);
    virtual void  deallocate(void* p, unsigned n);
};
struct VecCore {
    void*   begin;   // +0x00
    void*   end;     // +0x04
    void*   cap;     // +0x08
    VAlloc* alloc;   // +0x0c
    void*   name;    // +0x10
    void grow(void* p, void* value);   // 0x008d4400
};
struct TSI {
    union {
        struct {
            TSI*   mpNext;        // +0x000
            TSI*   mpPrev;        // +0x004
            RunRec mRuns[0x20];   // +0x008 (stride 0x1c)
            int    mCount;        // +0x388
            char   mFlag;         // +0x38c
        };
        struct {
            void*   mVtbl;        // +0x00
            VecCore mKeys;        // +0x04 (0x10-byte entries)
            VecCore mRects;       // +0x18 (0x14-byte entries)
            char    mDirty;       // +0x2c
        };
    };

    void       FUN_008d35d0(RunRec* rec, int arg);                      // 0x008d35d0
    void       FUN_008d3690(RunRec* rec);                               // 0x008d3690
    char       FUN_008d36f0(int a, int b, int c);                       // 0x008d36f0
    RunRec*    FUN_008d3530(int key, int b14, int b15);                 // 0x008d3530
    RunRec*    FUN_008d3580(int key, int b14, int b15, unsigned mask);  // 0x008d3580
    int        FUN_008d3ad0(int i);                                     // 0x008d3ad0
    int        FUN_008d3ae0(int key);                                   // 0x008d3ae0
    void       FUN_008d3b10(OwnerNode* node);                           // 0x008d3b10
    TSI*       FUN_008d3c60(VAlloc* alloc);                             // 0x008d3c60
    void       FUN_008d3ca0();                                          // 0x008d3ca0
    bool       FUN_008d3d30(int key, TSI* container);                   // 0x008d3d30
    TSI*       FUN_008d3da0();                                          // 0x008d3da0
    OwnerNode* FUN_008d3dc0(void* key, int* pOut, void* a4, void* a5);  // 0x008d3dc0
    void       FUN_008d3e30(RunRec* rec, unsigned flags);               // 0x008d3e30
    void       FUN_008d41b0(OwnerNode* node);                           // 0x008d41b0
};
void      FUN_008d3750(unsigned* a, unsigned* b);
void      FUN_008d3820(unsigned* a, unsigned* b);
unsigned* FUN_008d38d0(unsigned* a, unsigned* b, unsigned* c);
void*     FUN_008d3a10(int base, int start, int idx, unsigned k0, unsigned k1,
                       unsigned k2, unsigned k3);
void      FUN_008d3b70(int a, int b, int c, int d, unsigned e, unsigned f,
                       unsigned g, unsigned h, int i);
void* FUN_008d4040(void** pOut, void* head, void* tail, void* key, void* unused);
void      FUN_008d40b0(int a, int b, int c);
void      FUN_008d4110(unsigned* a, int b, int c);
void      FUN_008d4250(unsigned* a, unsigned* b, unsigned c, unsigned d, unsigned e);
void      FUN_008d4320(unsigned* a, unsigned* b, unsigned* c, int d);
// ---- items of slice s008d35d0 end

// ---- items of slice s008d4520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00c50ad0(int* dst, int* srcEnd, int* cur);   // 0x00c50ad0
extern "C" int* FUN_00951bb0(int* begin, int* out, int* val);    // 0x00951bb0
extern "C" void  FUN_008d4730(void* begin, void* end, int* key);              // 0x008d4730
extern "C" void* FUN_00e23ee0(void* begin, void* end, void* key, void* obj);  // 0x00e23ee0
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;
struct VAlloc_s008d_4520 {
    virtual void* slot0();                                   // vtable +0x00
    virtual void* slot4();                                   // vtable +0x04
    virtual void* allocate(unsigned n, int a, void* name);   // vtable +0x08
    virtual void  deallocate(void* p, unsigned n);           // vtable +0x0c
};
struct Rect20Vec {
    int*   begin;   // 0x00
    int*   end;     // 0x04
    int*   cap;     // 0x08
    VAlloc_s008d_4520* alloc;  // 0x0c
    void*  name;    // 0x10

    void  push_back(int* out, int* value);       // 0x008d4520
};
struct SortedTable {
    char   pad00[0x04];
    void*  begin;   // 0x04
    void*  end;     // 0x08
    char   pad0c[0x2c - 0x0c];
    uint8  dirty;   // 0x2c

    int lookupFlags(int* key, uint* outFlags, int* outExtra);   // 0x008d47b0
    int lookup400(int* key, uint* outFlags);                    // 0x008d4850
};
// ---- items of slice s008d4520 end

// ---- items of slice s008d5340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVtbl14366c8;                                             // 0x014366c8
extern void* gVtbl1436678;                                             // 0x01436678
extern void* gVtbl13effb8;                                             // 0x013effb8
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
void* RBTreeIncrement(void* pNode);                                   // 0x00921580
void  ZoneObjectDelete(void* pObject);                                // 0x00926060
inline void** VtableOf(void* pObject) { return *reinterpret_cast<void***>(pObject); }
namespace EA {
namespace Thread {
class Mutex_s008d_5340 {
public:
    int Lock(void* pCaller);                                          // 0x009221b0
    int Unlock();                                                     // 0x00922270
private:
    unsigned int mImpl[0x2c / 4];                                     // 0x00
};
}
}
namespace EA {
namespace IO {
bool DirectoryExists(const wchar_t* pPath);                           // 0x009322b0
}
}
namespace EA {
namespace IO {
bool DirectoryCreatePath(const wchar_t* pPath);                       // 0x00932960
}
}
namespace EA {
namespace IO {
bool DirectoryRemoveRecursive(const wchar_t* pPath, bool bRecursive); // 0x00932890
}
}
namespace EA {
namespace IO {
class FileStream_s008d_5340 {
public:
    void Construct(const char* pPath);                                // 0x00931da0 (in-place FileStream construction)
    ~FileStream_s008d_5340();                                                    // 0x00931e70
    void* mpVtbl;                                                     // +0x00
};
}
}
namespace EA {
namespace ResourceMan {
struct Key_s008d_5340 {
    unsigned int mnTypeID;        // +0x00
    unsigned int mnGroupID;       // +0x04
    unsigned int mnInstanceID;    // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct String16 {
    const wchar_t* mpBegin;       // +0x00
    const wchar_t* mpEnd;         // +0x04
    const wchar_t* mpCapacity;    // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct RBNode {
    RBNode* mpLeft;               // +0x00
    RBNode* mpRight;              // +0x04
    RBNode* mpParent;             // +0x08
    unsigned int mnColor;         // +0x0c
    // payload follows
};
}
}
namespace EA {
namespace ResourceMan {
struct RBTree {
    void* mpAllocator;            // +0x00
    RBNode* mpAnchor;             // +0x04 self-referential header node
    RBNode* mpBegin;              // +0x08 left-most node
    RBNode* mpRoot;               // +0x0c
    unsigned int mnUnknown10;     // +0x10
    unsigned int mnCount;         // +0x14
    void* mpAllocIface;           // +0x18
    unsigned int mnAllocName;     // +0x1c
};
}
}
namespace EA {
namespace ResourceMan {
inline RBNode* TreeAnchor(RBTree* pTree) { return reinterpret_cast<RBNode*>(reinterpret_cast<char*>(pTree) + 4); }
}
}
namespace EA {
namespace ResourceMan {
inline String16* NodeExtKey(RBNode* pNode) { return reinterpret_cast<String16*>(reinterpret_cast<char*>(pNode) + 0x10); }
}
}
namespace EA {
namespace ResourceMan {
inline unsigned int* NodeExtValue(RBNode* pNode) { return reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(pNode) + 0x20); }
}
}
namespace EA {
namespace ResourceMan {
struct RecordOpenResult {
    unsigned int mStatus;         // +0x00
    int          mHandle;         // +0x04
    unsigned int mGroupId;        // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
typedef bool (__cdecl* FileNameToKeyFn)(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult);
}
}
namespace EA {
namespace ResourceMan {
class DatabaseDirectoryFiles {
public:
    bool FUN_008d5d80();                                              // 0x008d5d80
    void* Cast(unsigned int nInterfaceId);                            // 0x008d5da0
    void SetMutexLocked(bool bLock);                                  // 0x008d5de0
    bool OpenRecord(void* pKey, void* pName, void* pContext, RecordOpenResult* pResult);  // 0x008d5e10
    bool OpenRecordFromPath(const wchar_t* pPath, void* pResult);     // 0x008d5ea0
    bool SetLocation(unsigned int nFlags, int nType);                 // 0x008d5fe0
    int  GetTypeByExtension(const wchar_t* pExtension);               // 0x008d61e0
    const wchar_t* GetExtensionByType(unsigned int nType);            // 0x008d6290

    // ---- retail layout (0x168 bytes, two vtable pointers) ----
    void*  mpVtbl0;                    // 0x000
    void*  mpVtbl1;                    // 0x004
    int    mnRefCount;                 // 0x008
    bool   mbInitialized;              // 0x00c
    unsigned char mPad0d[3];           // 0x00d

    void*  mpAllocator;                // 0x010
    bool   mbRequireDirectoryExists;   // 0x014
    bool   mbRecursive;                // 0x015
    unsigned char mPad16[2];           // 0x016

    unsigned int mnAccessFlags;        // 0x018
    String16 msDirectory;              // 0x01c
    unsigned int mDirectoryAllocator;  // 0x028

    unsigned char mExtensionPool[0x20];// 0x02c
    unsigned char mRecordPool[0x20];   // 0x04c

    RBTree mExtensionToTypeMap;        // 0x06c
    RBTree mRecordDataMap;             // 0x08c

    unsigned int mDefaultGroupId;      // 0x0ac
    void*  mpManager;                  // 0x0b0
    FileNameToKeyFn mpFileNameToKeyConverter;  // 0x0b4

    unsigned int mKnownTypesBits[0x20];// 0x0b8

    EA::Thread::Mutex_s008d_5340 mMutex;          // 0x138
};
}
}
namespace EA {
namespace ResourceMan {
class StreamInterface {
public:
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c();
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
};
}
}
namespace EA {
namespace ResourceMan {
struct DirectoryCloseInterface {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();       // +0x1c
};
}
}
class BackgroundRecordLoad {
public:
    void* Initialize(void* pOwner, const EA::ResourceMan::Key_s008d_5340* pKey);  // 0x008d60d0
    void* Destroy(unsigned int nFlags);                                // 0x008d6140
    bool  AddRef();                                                    // 0x008d5f70
    bool  Release();                                                   // 0x008d5fa0

    void* mpVtbl;                          // +0x000
    volatile long mnBusy04;                // +0x004
    EA::IO::FileStream_s008d_5340 mStream;            // +0x008
    unsigned char mStreamTail[0x234 - 0x008 - sizeof(EA::IO::FileStream_s008d_5340)];
    EA::ResourceMan::Key_s008d_5340 mKey;             // +0x234
    void* mpOwner;                         // +0x240
    volatile long mnRefCount;              // +0x244
};
// ---- items of slice s008d5340 end

// ---- items of slice s008d62f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace ResourceMan {
 struct RBNode_s008d_62f0; 
}
}
void** RbTreeFind(void* pTree, void** ppOut, const void* pKey);          // 0x00a21dc0 (ret 8)
namespace EA {
namespace Thread {
class Mutex_s008d_62f0
{
public:
    Mutex_s008d_62f0() {}
    Mutex_s008d_62f0(int nSpinCount, int nType);
    ~Mutex_s008d_62f0();
    int Lock(void* pCaller);   // 0x009221b0 (EA::Thread::Mutex::Lock)
    int Unlock();              // 0x00922270 (EA::Thread::Mutex::Unlock)
private:
    uint32_t mpImpl[0x2c / 4];
};
}
}
namespace EA {
namespace Allocator {
class ICoreAllocator_s008d_62f0
{
public:
    virtual void* Allocate(unsigned int nSize, const char* pName, unsigned int nFlags); // vtbl +0x08
    virtual void  Free(void* p, unsigned int nSize);                                    // vtbl +0x0c
    static ICoreAllocator_s008d_62f0* GetDefaultAllocator();   // 0x00925cb0
};
}
}
namespace EA {
namespace IO {
class FileStream_s008d_62f0
{
public:
    FileStream_s008d_62f0(const wchar_t* pPath);    // 0x00931e10
    ~FileStream_s008d_62f0();                       // 0x00931e70
    bool Open(unsigned int nMode, unsigned int nAccess, unsigned int nShare, unsigned int nFlags); // 0x009318f0
    bool Close();                                   // 0x00931a70
    void AddRef();                                  // 0x009317b0
};
}
}
namespace EA {
namespace ResourceMan {
struct Key_s008d_62f0
{
    uint32_t mnTypeID;      // 0x00
    uint32_t mnGroupID;     // 0x04
    uint32_t mnInstanceID;  // 0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct ListAnchor
{
    void* mpNext;   // 0x00
    void* mpPrev;   // 0x04
};
}
}
namespace EA {
namespace ResourceMan {
struct DDFRecordListData
{
    String16   mName;         // +0x00
    uint32_t   mnUnknown0c;   // +0x0c
    uint32_t   mnValue10;     // +0x10
    uint32_t   mnValue14;     // +0x14
    ListAnchor mRecords;      // +0x18  list<AutoRefCount<DDFRecord>>
};  // 0x20
}
}
namespace EA {
namespace ResourceMan {
struct RBNode_s008d_62f0
{
    RBNode_s008d_62f0* mpLeft;    // 0x00
    RBNode_s008d_62f0* mpRight;   // 0x04
    RBNode_s008d_62f0* mpParent;  // 0x08
    uint32_t mnColor;  // 0x0c
    // payload follows
};
}
}
namespace EA {
namespace ResourceMan {
struct RBTree_s008d_62f0
{
    void*   mpAllocator;  // +0x00
    RBNode_s008d_62f0* mpAnchor;     // +0x04 self-referential header node
    RBNode_s008d_62f0* mpBegin;      // +0x08 left-most node
    RBNode_s008d_62f0* mpRoot;       // +0x0c
    uint32_t mnUnknown10; // +0x10
    uint32_t mnCount;     // +0x14
    void*   mpAllocIface; // +0x18 ICoreAllocator*
    uint32_t mnAllocName; // +0x1c
};
}
}
namespace EA {
namespace ResourceMan {
class DDFRecord;
}
}
namespace EA {
namespace ResourceMan {
inline RBNode_s008d_62f0* Anchor(RBTree_s008d_62f0* pTree) { return reinterpret_cast<RBNode_s008d_62f0*>(reinterpret_cast<uint8_t*>(pTree) + 4); }
}
}
namespace EA {
namespace ResourceMan {
inline DDFRecordListData* NodeValue(RBNode_s008d_62f0* pNode) { return reinterpret_cast<DDFRecordListData*>(reinterpret_cast<uint8_t*>(pNode) + 0x20); }
}
}
namespace EA {
namespace ResourceMan {
inline const Key_s008d_62f0* NodeKey(RBNode_s008d_62f0* pNode) { return reinterpret_cast<const Key_s008d_62f0*>(reinterpret_cast<uint8_t*>(pNode) + 0x10); }
}
}
namespace EA {
namespace ResourceMan {
class IRecordStream
{
public:
    virtual void v00();                  // +0x00
    virtual void v04();                  // +0x04
    virtual void v08();                  // +0x08
    virtual void v0c();                  // +0x0c
    virtual int  GetFlags();             // +0x10
    virtual void v14();                  // +0x14
    virtual void v18();                  // +0x18
    virtual void v1c();                  // +0x1c
    virtual void v20();                  // +0x20
    virtual void v24();                  // +0x24
    virtual void v28();                  // +0x28
    virtual void v2c();                  // +0x2c
    virtual void v30();                  // +0x30
    virtual void Close();                // +0x34
};
}
}
namespace EA {
namespace ResourceMan {
class DDFRecord
{
public:
    virtual void  v00();                                 // +0x00
    virtual void  AddRef();                              // +0x04
    virtual void  Release();                             // +0x08
    virtual void  v0c();                                 // +0x0c
    virtual const Key_s008d_62f0* GetKey();              // +0x10
    virtual void  v14();                                 // +0x14
    virtual IRecordStream* GetStream();                  // +0x18
    virtual void  v1c();                                 // +0x1c

    EA::IO::FileStream_s008d_62f0 mStream;               // +0x08
    uint32_t mnPad;                                      // ...
    uint32_t mnOpenFlag;                                 // +0x244 (atomics)
};
}
}
namespace EA {
namespace ResourceMan {
class Manager_s008d_62f0;
}
}
namespace EA {
namespace ResourceMan {
class DatabaseDirectoryFiles_s008d_62f0
{
public:
    bool SetManager(bool bAttach, Manager_s008d_62f0* pManager, void* pContext);        // 0x008d62f0
    bool CloseUnreferencedRecords();                                         // 0x008d6410
    int  GetRecordCount(const Key_s008d_62f0& key);                          // 0x008d64a0
    bool GetRecordName(const Key_s008d_62f0& key, wchar_t* pName);           // 0x008d6510
    bool SetLocation(const wchar_t* pLocation);                              // 0x008d6650
    bool RemoveRecord(DDFRecord* pRecord);                                   // 0x008d66a0
    void CloseOpenRecords();                                                 // 0x008d6770
    int  GetKeyList(void* pKeyVector, void* pFilter);                        // 0x008d6b20
    bool AddExtensionMapping(const wchar_t* pExtension, uint32_t nValue);     // 0x008d6c40
    bool ReadExtensionToTypeMapFile();                                       // 0x008d6ed0

    // ---- retail layout (0x168 bytes, two vtable pointers) ----
    void*  mpVtbl0;                    // 0x000
    void*  mpVtbl1;                    // 0x004
    int    mnRefCount;                 // 0x008
    bool   mbInitialized;              // 0x00c
    uint8_t mPad0d[3];

    EA::Allocator::ICoreAllocator_s008d_62f0* mpAllocator;  // 0x010
    bool   mbRequireDirectoryExists;   // 0x014
    bool   mbRecursive;                // 0x015
    uint8_t mPad16[2];

    uint32_t mnAccessFlags;            // 0x018
    String16 msDirectory;              // 0x01c
    uint32_t mDirectoryAllocator;      // 0x028

    uint8_t  mExtensionPool[0x20];     // 0x02c
    uint8_t  mRecordPool[0x20];        // 0x04c

    RBTree_s008d_62f0 mExtensionToTypeMap;        // 0x06c
    RBTree_s008d_62f0 mRecordDataMap;             // 0x08c

    uint32_t mDefaultGroupId;          // 0x0ac
    Manager_s008d_62f0* mpManager;                // 0x0b0
    void*    mpFileNameToKeyConverter; // 0x0b4

    uint32_t mKnownTypesBits[0x20];    // 0x0b8

    EA::Thread::Mutex_s008d_62f0 mMutex;  // 0x138

    void SetSource(void* pArg0, Manager_s008d_62f0* pOld, void* pContext);  // vtable +0x44
};
}
}
// ---- items of slice s008d62f0 end

// ---- items of slice s008dc1a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_ZoneObject_PFRecordRead[];   // 0x13effa8
extern char vtbl_PFRecordRead_base[];         // 0x140a2e0
extern char vtbl_IStream_default[];           // 0x13f3a68
extern char vtbl_PFRecordWrite[];             // 0x1436968
extern char vtbl_PFRecordWrite_IStream[];     // 0x143692c
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _InterlockedExchange)
typedef unsigned int   uint32;
struct Key { uint32 mInstance; uint32 mType; uint32 mGroup; };   // 0xc
struct IAllocator {
    virtual void a0();                          // +0x00
    virtual void a1();                          // +0x04
    virtual void* Alloc(unsigned size, const char* name, unsigned flags); // +0x08
    virtual void  Free(void* p, unsigned size);                           // +0x0c
    virtual void a4();                          // +0x10
};
struct DatabasePackedFile {                     // 0x384
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual IAllocator* GetAllocator();         // +0x48
    bool ReadFileSpan(void* dst, unsigned offset, int size);            // 0x8d9050
    bool WriteFileSpan(const void* src, unsigned offset, int size);     // 0x8d90e0
    bool DecompressRecord(uint16 type, unsigned src, unsigned a, unsigned b, void* out); // 0x8d9320
};
struct MemStreamW {
virtual void w00();
virtual void w01();
virtual void w02();
virtual void w03();
virtual void w04();
virtual void w05();
virtual void w06();
    virtual int  GetSize();                          // +0x1c
    virtual void SetSize(int n);                     // +0x20
    virtual void w09();                              // +0x24
    virtual void SetPosition(int delta, int mode);   // +0x28
    virtual void Flush();                            // +0x2c
    virtual int  Read(void* buf, int len);           // +0x30
    bool  SetData(void* data, unsigned size, unsigned a, unsigned b, void* alloc);
    void* GetData();
    void  SetOption(int option, float value);
    void  Construct(const char* name);
    void  Destroy();
    int   Attach(void* a, unsigned b);
};
struct FileStream {
virtual void f00();
virtual void f01();
virtual void f02();
virtual void f03();
    virtual int  IsOpen();                      // +0x10
    virtual void f05();                         // +0x14
    virtual bool Close();                       // +0x18
    virtual void f07();                         // +0x1c
    virtual bool f08(int n);                    // +0x20
    virtual int  f09();                         // +0x24
    virtual void f10(int a, int b);             // +0x28
    virtual void f11();                         // +0x2c
    virtual int  f12();                         // +0x30
    virtual void f13();                         // +0x34
    virtual bool f14();                         // +0x38
    virtual void f15();                         // +0x3c
    virtual void f16();                         // +0x40
    virtual int  GetPath(void* buf, int n);     // +0x44
    virtual void f18();                         // +0x48
    virtual bool Open(int mode, int a, int b, int c); // +0x4c
    void Construct(const char* path);           // 0x931da0
};
struct PFRecordWrite {
    char raw[0x27c];
    char  OpenTempFile();                        // 0x8dc600
    void  DeleteTempFile();                      // 0x8dc740
    char  WriteRecordToParent(void* data, unsigned size);  // 0x8dc890
    void  IStreamDestroy();                      // 0x8dcbf0
    bool  IStreamAddRef();                       // 0x8dcc50
    PFRecordWrite(unsigned access, unsigned size, const Key& key, DatabasePackedFile* parent); // 0x8dcea0
};
// ---- items of slice s008dc1a0 end

// ---- items of slice s008dd0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b, const char* file, int line);
extern "C" void* __cdecl operator_new_arr(void* p, int a, int n);          // 0x11e073e
extern "C" void* __cdecl operator_delete__(void* p);                        // 0xf47380
extern void* g_pMemAlloc;                           // 0x16c8b44
extern "C" void* __cdecl FUN_0093bd50(const char* name);                    // 0x93bd50
extern "C" void  __cdecl FUN_0093bb40(int a, float b);                      // 0x93bb40
extern "C" void  __cdecl FUN_0093be30(void* self, void* a, void* b, int c, int d, void* e); // 0x93be30
extern "C" void* __cdecl FUN_0093bde0(void* self);                          // 0x93bde0
extern "C" void* __cdecl FUN_00931da0(void* self, int a);                   // 0x931da0
extern "C" void* __cdecl FUN_00931e70(void* self);                          // 0x931e70 FileStream dtor
extern "C" char  __cdecl FUN_009318f0(void* self, int a, int b, int c, int d); // 0x9318f0 Open
extern "C" void  __cdecl FUN_00931810(void* self, const wchar_t* p);        // 0x931810 SetPath
extern "C" unsigned __cdecl FUN_00931ce0(void* self, void* buf, unsigned n);// 0x931ce0 Read
extern "C" void* __cdecl FUN_00931a70(void* self);                          // 0x931a70 GetStream
extern "C" void* __cdecl FUN_00931b70(void* self);                          // 0x931b70 GetDatabase
extern "C" void* __cdecl FUN_00609d90(void* a, void* b, void* c, void* d);  // 0x609d90 eastl::search
extern "C" void* __cdecl FUN_008dcbf0(void* self);                          // 0x8dcbf0
extern "C" char  __cdecl FUN_0093a780(void* a, void* out, int n, void* b);  // 0x93a780
extern "C" void*    __cdecl memmove(void* d, const void* s, unsigned n);
extern "C" unsigned int __cdecl wcslen(const wchar_t*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedIncrement)
#pragma intrinsic(wcslen)
struct MemAlloc {
    void  Free(void* p);                            // 0x9276c0
    void* Alloc(int size, int a, int b, int c, int d, int e); // 0x9289f0 LockedAlloc
};
struct PFRecordWrite_s008d_d0d0 {
    void** vtbl;                 // +0x00
    int    mRefCount;            // +0x04
    int    mField08;             // +0x08
    int    mKey[3];              // +0x0c
    void*  mpDatabase;           // +0x18
    int    mField1c;             // +0x1c
    void** vtbl20;               // +0x20
    char   mMemStream[0x24];     // +0x24 (MemoryStream)
    char   mFileStream[0x22c];   // +0x48 (FileStream)

    void* ctor(int a2, int a3, int a4, void* a5, int a6);   // 0x8dd0d0
    void* _virtual_dtor(int flags);                          // 0x8dd1f0
};
struct EditorResource {
    void** vtbl;        // +0x00
    char   d[0x10];     // +0x04
    void*  mpData;      // +0x14
    int    mSize;       // +0x18
    void   dtor();      // 0x8dde10
    void*  deleting_dtor(int flags); // 0x8ddfb0
};
// ---- items of slice s008dd0d0 end

// @ 0x008d1da0
bool __stdcall EnumDeviceCallback(void* instanceGuid, void* userData)
{
    EA::Input::InputMan* man = (EA::Input::InputMan*)userData;
    if (instanceGuid && man->mnDIEnumCount < 4) {
        int r = man->mpDI->CreateDevice((char*)instanceGuid + 4,
                                        (void**)&man->mpDIEnumControllers[man->mnDIEnumCount], 0);
        if (r >= 0)
            man->mnDIEnumCount++;
    }
    return man->mnDIEnumCount < 4;
}

// @ 0x008d34d0
InputEvent::InputEvent()
{
    b = 0;
    a = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    g = 0;
    h = (char)0xfe;
}

// @ 0x008d34f0
InputEvent::InputEvent(int d_, int e_, int f_, char g_, int c_, char h_)
{
    c = c_;
    d = d_;
    e = e_;
    f = f_;
    b = 0;
    a = 0;
    g = g_;
    h = h_;
}

// @ 0x008d3530
Binding* BindingTable::FindBinding(int key, int c14, int c15)
{
    for (unsigned i = 0; i < count; ++i) {
        Binding* e = &b[i];
        if (e->fc == key && e->c14 == c14 && e->c15 == c15)
            return e;
    }
    return 0;
}

// @ 0x008d3580
Binding* BindingTable::FindBindingMasked(int key, int c14, int c15, unsigned mask)
{
    for (unsigned i = 0; i < count; ++i) {
        Binding* e = &b[i];
        if (e->f4 == key && e->c14 == c14 && e->c15 == c15 && (mask & e->s16))
            return e;
    }
    return 0;
}

// @ 0x008d35d0
void TSI::FUN_008d35d0(RunRec* rec, int arg)
{
    RunRec local = *rec;
    --mCount;
    RunRec* last = &mRuns[mCount];
    if ((unsigned)last > (unsigned)rec)
        *rec = *last;

    OwnerNode* owner = local.mpOwner;
    if (owner != 0) {
        if (owner->mpFn != 0 && (local.mFlags16 & 0x2000) == 0)
            owner->mpFn(arg, &local, owner->mpData);
    }
    if (local.mKey8 != 0 && (local.mFlags16 & 0x1000) == 0) {
        RunRec* r = FUN_008d3580(local.mKey8, local.mb14, local.mb15, 0x1000);
        if (r != 0)
            FUN_008d35d0(r, arg);
    }
}

// @ 0x008d3690
void TSI::FUN_008d3690(RunRec* rec)
{
    unsigned c = 0;
    int n = mCount;
    if (n != 0) {
        RunRec* p = mRuns;
        do {
            if (p->mKey4 == rec->mKey4 && p->mpOwner == rec->mpOwner &&
                p->mKeyC == rec->mKeyC)
                c++;
            p++;
            n--;
        } while (n != 0);
    }
    rec->mDup18 = (unsigned short)(1 < c);
    FUN_008d35d0(rec, 0x5ece0001);
}

// @ 0x008d36f0
char TSI::FUN_008d36f0(int param_2, int param_3, int param_4)
{
    if (param_2 != 0) {
        unsigned u = 0;
        unsigned cnt = (unsigned)mCount;
        if (u < cnt) {
            RunRec* p = mRuns;
            do {
                if (p->mKey4 == param_2 && (param_3 == -2 || param_3 == p->mb15) &&
                    (param_4 == 7 || param_4 == p->mb14))
                    return 1;
                u++;
                p++;
            } while (u < cnt);
        }
    }
    return 0;
}

// @ 0x008d3750
void FUN_008d3750(unsigned* param_1, unsigned* param_2)
{
    unsigned u1, u2, u3, u4;
    unsigned *p5, *p6, *p7, *p8;
    bool b;
    unsigned short us;
    p6 = param_1;
    if (param_1 != param_2) {
        while ((p6 = p6 + 4) != param_2) {
            u1 = p6[1]; u2 = p6[3]; u3 = p6[2]; u4 = *p6;
            p7 = p6;
            if (p6 != param_1) {
                us = (unsigned short)(u3 >> 0x10);
                p5 = p6;
                do {
                    p8 = p5 - 4;
                    b = u4 < *p8;
                    if (u4 == *p8) {
                        b = *(unsigned short*)((int)p5 - 6) <= us;
                        if (us == *(unsigned short*)((int)p5 - 6)) {
                            if ((unsigned short)u3 == (unsigned short)p5[-2])
                                b = u1 < p5[-3];
                            else
                                b = (unsigned short)p5[-2] < (unsigned short)u3;
                        }
                    }
                    if (!b) break;
                    *p7 = *p8; p7[1] = p5[-3]; p7[2] = p5[-2]; p7[3] = p5[-1];
                    p7 = p7 - 4;
                    p5 = p8;
                } while (p7 != param_1);
            }
            *p7 = u4; p7[1] = u1; p7[2] = u3; p7[3] = u2;
        }
    }
}

// @ 0x008d3820
void FUN_008d3820(unsigned* param_1, unsigned* param_2)
{
    unsigned u1, u2, u3, u4;
    unsigned *p5, *p6, *p7;
    bool b;
    unsigned short us;
    for (; param_1 != param_2; param_1 = param_1 + 4) {
        u1 = param_1[1]; u2 = param_1[2]; u3 = param_1[3]; u4 = *param_1;
        us = (unsigned short)(u2 >> 0x10);
        p7 = param_1;
        p5 = param_1;
        while (true) {
            p6 = p5 - 4;
            b = u4 < *p6;
            if (u4 == *p6) {
                b = *(unsigned short*)((int)p5 - 6) <= us;
                if (us == *(unsigned short*)((int)p5 - 6)) {
                    if ((unsigned short)u2 == (unsigned short)p5[-2])
                        b = u1 < p5[-3];
                    else
                        b = (unsigned short)p5[-2] < (unsigned short)u2;
                }
            }
            if (!b) break;
            *p7 = *p6; p7[1] = p5[-3]; p7[2] = p5[-2]; p7[3] = p5[-1];
            p7 = p7 - 4;
            p5 = p6;
        }
        *p7 = u4; p7[1] = u1; p7[2] = u2; p7[3] = u3;
    }
}

// @ 0x008d38d0
unsigned* FUN_008d38d0(unsigned* param_1, unsigned* param_2, unsigned* param_3)
{
    unsigned u1, u2, u3;
    bool b;
    u1 = *param_1;
    u2 = *param_2;
    b = u1 < u2;
    if (u1 == u2) {
        b = *(unsigned short*)((int)param_2 + 10) <= *(unsigned short*)((int)param_1 + 10);
        if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_2 + 10)) {
            b = (unsigned short)param_2[2] <= (unsigned short)param_1[2];
            if ((unsigned short)param_1[2] == (unsigned short)param_2[2])
                b = param_1[1] < param_2[1];
        }
    }
    u3 = *param_3;
    if (b) {
        b = u2 < u3;
        if (u2 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_2 + 10);
            if (*(unsigned short*)((int)param_2 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_2[2];
                if ((unsigned short)param_2[2] == (unsigned short)param_3[2])
                    b = param_2[1] < param_3[1];
            }
        }
        if (!b) {
            b = u1 < u3;
            if (u1 == u3) {
                b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_1 + 10);
                if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                    b = (unsigned short)param_3[2] <= (unsigned short)param_1[2];
                    if ((unsigned short)param_1[2] == (unsigned short)param_3[2])
                        b = param_1[1] < param_3[1];
                }
            }
            if (!b) return param_1;
            return param_3;
        }
    } else {
        b = u1 < u3;
        if (u1 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_1 + 10);
            if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_1[2];
                if ((unsigned short)param_1[2] == (unsigned short)param_3[2])
                    b = param_1[1] < param_3[1];
            }
        }
        if (b) return param_1;
        b = *param_2 < u3;
        if (*param_2 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_2 + 10);
            if (*(unsigned short*)((int)param_2 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_2[2];
                if ((unsigned short)param_2[2] == (unsigned short)param_3[2])
                    b = param_2[1] < param_3[1];
            }
        }
        if (b) return param_3;
    }
    return param_2;
}

// @ 0x008d3a10
void* FUN_008d3a10(int base, int start, int idx, unsigned k0, unsigned k1, unsigned k2, unsigned k3)
{
    while (start < idx) {
        int parent = (idx - 1) >> 1;
        unsigned* p = (unsigned*)((char*)base + parent * 0x10);
        unsigned p0 = p[0];
        bool less = p0 < k0;
        if (p0 == k0) {
            less = (unsigned short)(k2 >> 0x10) <= *(unsigned short*)((char*)p + 0xa);
            if (*(unsigned short*)((char*)p + 0xa) == (unsigned short)(k2 >> 0x10)) {
                less = (unsigned short)k2 <= (unsigned short)p[2];
                if ((unsigned short)p[2] == (unsigned short)k2)
                    less = p[1] < k1;
            }
        }
        if (!less)
            break;
        unsigned* dst = (unsigned*)((char*)base + idx * 0x10);
        dst[0] = p[0]; dst[1] = p[1]; dst[2] = p[2]; dst[3] = p[3];
        idx = parent;
    }
    unsigned* dst = (unsigned*)((char*)base + idx * 0x10);
    dst[0] = k0; dst[1] = k1; dst[2] = k2; dst[3] = k3;
    return dst;
}

// @ 0x008d3ad0
int TSI::FUN_008d3ad0(int param_2)
{
    return param_2 * 0x10 + (int)mKeys.begin;
}

// @ 0x008d3ae0
int TSI::FUN_008d3ae0(int param_2)
{
    int p = (int)mKeys.begin;
    int e = (int)mKeys.end;
    while (true) {
        if (p == e)
            return 0;
        if (*(int*)(p + 4) == param_2) break;
        p = p + 0x10;
    }
    return p;
}

// @ 0x008d3b10
void TSI::FUN_008d3b10(OwnerNode* node)
{
    OwnerNode* p = (OwnerNode*)mpNext;
    for (;;) {
        if (p == (OwnerNode*)this)
            break;
        if (p == node) {
            OwnerNode* pv = node->mpPrev;
            OwnerNode* nx = node->mpNext;
            pv->mpNext = nx;
            nx->mpPrev = pv;
            node->mpNext = 0;
            node->mpPrev = 0;
            break;
        }
        p = p->mpNext;
    }

    unsigned u = 0;
    if ((unsigned)mCount > 0) {
        RunRec* r = mRuns;
        do {
            if ((OwnerNode*)r->mpOwner == node)
                FUN_008d35d0(r, 0x5ece0002);
            else {
                u++;
                r++;
            }
        } while (u < (unsigned)mCount);
    }
}

// @ 0x008d3b70
void FUN_008d3b70(int param_1, int param_2, int param_3, int param_4, unsigned param_5, unsigned param_6, unsigned param_7, unsigned param_8, int param_9)
{
    unsigned u;
    int i2, i3, i4, i6;
    unsigned* p;
    bool b;
    (void)param_9;
    while (true) {
        i4 = param_4 * 2;
        i6 = i4 + 2;
        if (param_3 <= i6) break;
        i2 = i6 * 0x10;
        u = *(unsigned*)(i2 - 0x10 + param_1);
        i3 = i2 + param_1;
        b = *(unsigned*)(i2 + param_1) < u;
        if (*(unsigned*)(i2 + param_1) == u) {
            b = *(unsigned short*)(i3 - 6) <= *(unsigned short*)(i3 + 10);
            if (*(unsigned short*)(i3 + 10) == *(unsigned short*)(i3 - 6)) {
                b = *(unsigned short*)(i3 - 8) <= *(unsigned short*)(i3 + 8);
                if (*(unsigned short*)(i3 + 8) == *(unsigned short*)(i3 - 8))
                    b = *(unsigned*)(i3 + 4) < *(unsigned*)(i3 - 0xc);
            }
        }
        if (b) i6 = i4 + 1;
        i4 = i6 * 0x10 + param_1;
        p = (unsigned*)(param_4 * 0x10 + param_1);
        p[0] = *(unsigned*)(i6 * 0x10 + param_1);
        p[1] = *(unsigned*)(i4 + 4);
        p[2] = *(unsigned*)(i4 + 8);
        p[3] = *(unsigned*)(i4 + 0xc);
        param_4 = i6;
    }
    if (i6 == param_3) {
        p = (unsigned*)(i6 * 0x10 - 0x10 + param_1);
        *(unsigned*)(param_4 * 0x10 + param_1) = p[0];
        i6 = param_4 * 0x10 + param_1;
        *(unsigned*)(i6 + 4) = p[1];
        *(unsigned*)(i6 + 8) = p[2];
        *(unsigned*)(i6 + 0xc) = p[3];
        param_4 = i4 + 1;
    }
    FUN_008d3a10(param_1, param_2, param_4, param_5, param_6, param_7, param_8);
}

// @ 0x008d3c60
TSI* TSI::FUN_008d3c60(VAlloc* alloc)
{
    mVtbl = (void**)0x1435990;
    mKeys.begin = 0;
    mKeys.end = 0;
    mKeys.cap = 0;
    mKeys.alloc = alloc;
    mKeys.name = 0;
    mRects.begin = 0;
    mRects.end = 0;
    mRects.cap = 0;
    mRects.alloc = alloc;
    mRects.name = 0;
    mDirty = 0;
    return this;
}

// @ 0x008d3ca0
void TSI::FUN_008d3ca0()
{
    mVtbl = &PTR_FUN_01435990;
    if (mRects.begin != 0)
        mRects.alloc->deallocate(mRects.begin,
            (unsigned)((((int)mRects.cap - (int)mRects.begin) / 0x14) * 0x14));
    if (mKeys.begin != 0)
        mKeys.alloc->deallocate(mKeys.begin,
            (unsigned)((((int)mKeys.cap - (int)mKeys.begin) >> 4) << 4));
    mVtbl = &PTR_FUN_01435980;
}

// @ 0x008d3d30
bool TSI::FUN_008d3d30(int param_2, TSI* param_3)
{
    int* r = (int*)mRects.begin;
    int* e = (int*)mRects.end;
    if (r == e)
        return false;
    do {
        if (*r == param_2)
            break;
        r += 5;
    } while (r != e);
    if (r == e)
        return false;

    unsigned u = 0;
    int* field = r + 1;
    do {
        int v = *field;
        if (v != 0) {
            if ((unsigned)param_3->mCount == 0)
                return false;
            unsigned i = 0;
            int* k = &param_3->mRuns[0].mKey4;
            while (*k != v) {
                i++;
                k += 7;
                if ((unsigned)param_3->mCount <= i)
                    return false;
            }
        }
        u++;
        field++;
    } while (u < 4);
    return true;
}

// @ 0x008d3da0
TSI* TSI::FUN_008d3da0()
{
    mpPrev = this;
    mpNext = this;
    mCount = 0;
    mFlag = 1;
    return this;
}

// @ 0x008d3dc0
OwnerNode* TSI::FUN_008d3dc0(void* key, int* pOut, void* a4, void* a5)
{
    OwnerNode* first = (OwnerNode*)mpNext;
    if ((OwnerNode*)this == first)
        return 0;
    OwnerNode* p = (OwnerNode*)this;
    for (;;) {
        OwnerNode* node = p->mpPrev;
        if (node->mpIface != 0) {
            void* r = node->mpIface->slot4(key, a4, a5);
            *pOut = (int)r;
            if (r != 0)
                return node;
        }
        if (node->mFlag & 1)
            return 0;
        p = p->mpPrev;
        if (p == first)
            return 0;
    }
}

// @ 0x008d3e30
void TSI::FUN_008d3e30(RunRec* rec, unsigned flags)
{
    if ((char)flags == 0) {
        RunRec* r = FUN_008d3530(rec->mKeyC, rec->mb14, rec->mb15);
        if (r != 0) {
            FUN_008d3690(r);
            return;
        }
    } else if ((unsigned)mCount < 0x20) {
        int local_24 = rec->mKey8;
        OwnerNode* i4 = rec->mpOwner;
        int local_20 = rec->mKey4;
        flags = rec->mFlags16;
        if (i4 == 0 || local_20 == 0)
            i4 = FUN_008d3dc0(rec, &local_20, &flags, &local_24);
        if (i4 != 0 && i4->mpFn != 0) {
            RunRec* dst = &mRuns[mCount];
            *dst = *rec;
            dst->mDup18 = 0;

            unsigned u = 0;
            if (mCount != 0) {
                RunRec* p = mRuns;
                do {
                    if (rec->mKeyC == p->mKeyC && rec->mb14 == p->mb14 &&
                        rec->mb15 == p->mb15)
                        return;
                    if (p->mKey4 == local_20 && p->mpOwner == i4 &&
                        p->mb14 == rec->mb14 && p->mb15 == rec->mb15)
                        dst->mDup18 = 1;
                    u++;
                    p++;
                } while (u < (unsigned)mCount);
            }

            dst->mpOwner = i4;
            dst->mKey4 = local_20;
            dst->mKey8 = local_24;
            dst->mFlags16 = (unsigned short)flags;
            if (flags & 0x800)
                dst->mf10 = -dst->mf10;
            mCount++;
            if ((flags & 0x2000) == 0)
                i4->mpFn(0x5ece0000, dst, i4->mpData);
            if (local_24 != 0 && (flags & 0x1000) == 0) {
                char c = i4->mpIface->slotC((void*)local_24, this);
                if (c != 0) {
                    RunRec tmp;
                    tmp.mpOwner = i4;
                    tmp.mKey4 = local_24;
                    tmp.mKey8 = local_24;
                    tmp.mKeyC = 0;
                    tmp.mf10 = 0.0f;
                    tmp.mb14 = dst->mb14;
                    tmp.mb15 = dst->mb15;
                    tmp.mFlags16 = 0x1000;
                    tmp.mDup18 = 0;
                    FUN_008d3e30(&tmp, 1);
                }
            }
        }
    }
}

// @ 0x008d4040
void* FUN_008d4040(void** pOut, void* head, void* tail, void* key, void* unused)
{
    int n = 0;
    for (void* p = head; p != tail; p = *(void**)p)
        n++;
    if (n > 0) {
        int half;
        do {
            half = n >> 1;
            int i = half;
            void* p = head;
            if (half < 0) {
                i = -half;
                do {
                    i--;
                    p = *((void**)p + 1);
                } while (i != 0);
            } else {
                for (; i != 0; i--)
                    p = *(void**)p;
            }
            if (*(int*)((char*)p + 8) <= *(int*)((char*)key + 8)) {
                head = *(void**)p;
                half = n + (-1 - half);
            }
            n = half;
        } while (half > 0);
    }
    *pOut = head;
    (void)unused;
    return pOut;
}

// @ 0x008d40b0
void FUN_008d40b0(int param_1, int param_2, int param_3)
{
    int i1, i2, i3;
    i1 = param_2 - param_1 >> 4;
    if (2 <= i1) {
        i3 = (i1 - 2 >> 1) + 1;
        i2 = i3 * 0x10 + param_1;
        do {
            i3 = i3 - 1;
            FUN_008d3b70(param_1, i3, i1, i3,
                         *(unsigned*)(i2 - 0x10), *(unsigned*)(i2 - 0xc),
                         *(unsigned*)(i2 - 8), *(unsigned*)(i2 - 4), param_3);
            i2 = i2 - 0x10;
        } while (i3 != 0);
    }
}

// @ 0x008d4110
void FUN_008d4110(unsigned* param_1, int param_2, int param_3)
{
    unsigned u1, u2, u3, u4;
    int i5;
    unsigned* p6;
    i5 = param_2 - (int)param_1 >> 4;
    if (1 < i5) {
        p6 = (unsigned*)(param_2 - 0x10);
        do {
            u1 = p6[3]; u2 = p6[0]; u3 = p6[1]; u4 = p6[2];
            p6[0] = param_1[0]; p6[1] = param_1[1]; p6[2] = param_1[2]; p6[3] = param_1[3];
            FUN_008d3b70((int)param_1, 0, i5 - 1, 0, u2, u3, u4, u1, param_3);
            p6 = p6 - 4;
            i5 = (0x10 - (int)param_1) + (int)p6 >> 4;
        } while (1 < i5);
    }
}

// @ 0x008d41b0
void TSI::FUN_008d41b0(OwnerNode* node)
{
    OwnerNode* orig = node;
    FUN_008d4040((void**)&node, (void*)mpNext, (void*)this, (void*)orig, (void*)orig);

    OwnerNode* ins = node;
    OwnerNode* pv = ins->mpPrev;
    ins->mpPrev = orig;
    pv->mpNext = orig;
    orig->mpPrev = pv;
    orig->mpNext = ins;

    unsigned u = 0;
    if (mCount != 0) {
        RunRec* r = mRuns;
        do {
            int localA, localB;
            OwnerNode* found = FUN_008d3dc0(r, (int*)&node, &localA, &localB);
            if ((OwnerNode*)r->mpOwner == found && (OwnerNode*)r->mKey4 == node) {
                u++;
                r++;
            } else {
                FUN_008d35d0(r, 0x5ece0002);
            }
        } while (u < (unsigned)mCount);
    }
}

// @ 0x008d4250
void FUN_008d4250(unsigned* param_1, unsigned* param_2, unsigned param_3, unsigned param_4, unsigned param_5)
{
    unsigned u1, u2, u3, u4;
    unsigned* p5;
    unsigned short u6;
    bool b;
    while (true) {
        while (true) {
            b = *param_1 < param_3;
            u6 = (unsigned short)param_5;
            if (*param_1 == param_3) {
                b = (unsigned short)(param_5 >> 0x10) <= *(unsigned short*)((int)param_1 + 10);
                if (*(unsigned short*)((int)param_1 + 10) == (unsigned short)(param_5 >> 0x10)) {
                    b = u6 <= (unsigned short)param_1[2];
                    if ((unsigned short)param_1[2] == u6)
                        b = param_1[1] < param_4;
                }
            }
            if (!b) break;
            param_1 = param_1 + 4;
        }
        do {
            p5 = param_2;
            param_2 = p5 - 4;
            b = param_3 < p5[-4];
            if (param_3 == p5[-4]) {
                b = *(unsigned short*)((int)p5 - 6) <= (unsigned short)(param_5 >> 0x10);
                if ((unsigned short)(param_5 >> 0x10) == *(unsigned short*)((int)p5 - 6)) {
                    if (u6 == (unsigned short)p5[-2])
                        b = param_4 < p5[-3];
                    else
                        b = (unsigned short)p5[-2] < u6;
                }
            }
        } while (b);
        if (param_2 <= param_1) break;
        u1 = *param_1; u2 = param_1[1]; u3 = param_1[2]; u4 = param_1[3];
        *param_1 = *param_2;
        param_1[1] = p5[-3]; param_1[2] = p5[-2]; param_1[3] = p5[-1];
        *param_2 = u1;
        p5[-3] = u2; p5[-2] = u3; p5[-1] = u4;
        param_1 = param_1 + 4;
    }
}

// @ 0x008d4320
void FUN_008d4320(unsigned* param_1, unsigned* param_2, unsigned* param_3, int param_4)
{
    unsigned u1, u2, u3, u4;
    unsigned* p5;
    bool b;
    FUN_008d40b0((int)param_1, (int)param_2, param_4);
    for (p5 = param_2; p5 < param_3; p5 = p5 + 4) {
        b = *p5 < *param_1;
        if (*p5 == *param_1) {
            b = *(unsigned short*)((int)param_1 + 10) <= *(unsigned short*)((int)p5 + 10);
            if (*(unsigned short*)((int)p5 + 10) == *(unsigned short*)((int)param_1 + 10)) {
                b = (unsigned short)param_1[2] <= (unsigned short)p5[2];
                if ((unsigned short)p5[2] == (unsigned short)param_1[2])
                    b = p5[1] < param_1[1];
            }
        }
        if (b) {
            u1 = *p5; u2 = p5[1]; u3 = p5[2]; u4 = p5[3];
            *p5 = *param_1;
            p5[1] = param_1[1]; p5[2] = param_1[2]; p5[3] = param_1[3];
            FUN_008d3b70((int)param_1, 0, ((int)param_2 - (int)param_1) >> 4, 0, u1, u2, u3, u4,
                         param_4);
        }
    }
    FUN_008d4110(param_1, (int)param_2, param_4);
}

// @ 0x008d4400
void VecCore::grow(void* p, void* value)
{
    void* e = end;
    if (e != cap) {
        if (p <= value && value < e)
            value = (char*)value + 0x10;
        if (e != 0) {
            ((int*)e)[0] = ((int*)e)[-4];
            ((int*)e)[1] = ((int*)e)[-3];
            ((int*)e)[2] = ((int*)e)[-2];
            ((int*)e)[3] = ((int*)e)[-1];
        }
        FUN_00edba80(p, (char*)end - 0x10, end);
        ((int*)p)[0] = ((int*)value)[0];
        ((int*)p)[1] = ((int*)value)[1];
        ((int*)p)[2] = ((int*)value)[2];
        ((int*)p)[3] = ((int*)value)[3];
        end = (char*)end + 0x10;
        return;
    }

    int n = (int)((char*)e - (char*)begin) >> 4;
    int cap2;
    if (n == 0) {
        n = 1;
        cap2 = (int)alloc->allocate((unsigned)(n << 4), 0, name);
    } else {
        n = n * 2;
        if (n == 0)
            cap2 = 0;
        else
            cap2 = (int)alloc->allocate((unsigned)(n << 4), 0, name);
    }
    void* dst = FUN_00c7ea30(begin, p, (void*)cap2);
    if (dst != 0) {
        ((int*)dst)[0] = ((int*)value)[0];
        ((int*)dst)[1] = ((int*)value)[1];
        ((int*)dst)[2] = ((int*)value)[2];
        ((int*)dst)[3] = ((int*)value)[3];
    }
    void* ne = FUN_00c7ea30(p, end, (char*)dst + 0x10);
    if (begin != 0)
        alloc->deallocate(begin, (unsigned)((((int)cap - (int)begin) >> 4) << 4));
    end = ne;
    cap = (char*)cap2 + (n << 4);
    begin = (void*)cap2;
}

// @ 0x008d4520
void Rect20Vec::push_back(int* out, int* value)
{
    int* e = end;
    if (e != cap) {
        if (out <= value && value < e)
            value += 5;
        if (e != 0) {
            e[0] = e[-5]; e[1] = e[-4]; e[2] = e[-3]; e[3] = e[-2]; e[4] = e[-1];
        }
        FUN_00c50ad0(out, end - 5, end);
        out[0] = value[0]; out[1] = value[1]; out[2] = value[2];
        out[3] = value[3]; out[4] = value[4];
        end += 5;
        return;
    }

    int n = (int)(((char*)e - (char*)begin) / 0x14);
    int capacity = n;
    int* p;
    if (capacity == 0) {
        capacity = 1;
    } else {
        capacity = capacity * 2;
    }
    if (capacity == 0)
        p = 0;
    else
        p = (int*)alloc->allocate((unsigned)(capacity * 0x14), 0, name);

    {
        int* r = FUN_00951bb0(begin, out, p);
        if (r != 0) {
            r[0] = value[0]; r[1] = value[1]; r[2] = value[2];
            r[3] = value[3]; r[4] = value[4];
        }
        int* ne = FUN_00951bb0(out, end, r + 5);
        int* b = begin;
        if (b != 0)
            alloc->deallocate(b, (unsigned)(((char*)cap - (char*)b) / 0x14 * 0x14));
        begin = p;
        end = ne;
        cap = (int*)((char*)p + capacity * 0x14);
    }
}

// @ 0x008d47b0
int SortedTable::lookupFlags(int* key, uint* outFlags, int* outExtra)
{
    if (dirty != 0) {
        FUN_008d4730(begin, end, key);
        dirty = 0;
    }
    int* last = (int*)end;
    int* e = (int*)FUN_00e23ee0(begin, end, (char*)key + 0xc, key);
    if (e != last) {
        do {
            if (*e != *(int*)((char*)key + 0xc))
                return 0;
            if ((((*(uint16*)((char*)e + 0xa) & *(uint16*)((char*)key + 0x16)) ==
                  *(uint16*)((char*)e + 8)) ||
                 (*(uint16*)((char*)e + 0xa) == 0x3ff)) &&
                ((*(uint16*)((char*)key + 0x16) & 0x2000) == 0)) {
                *outFlags = *(uint16*)((char*)e + 8);
                *outExtra = *(int*)((char*)e + 0xc);
                return *(int*)((char*)e + 4);
            }
            e += 4;
        } while (e != (int*)end);
    }
    return 0;
}

// @ 0x008d4850
int SortedTable::lookup400(int* key, uint* outFlags)
{
    if (dirty != 0) {
        FUN_008d4730(begin, end, key);
        dirty = 0;
    }
    int* last = (int*)end;
    int* e = (int*)FUN_00e23ee0(begin, end, (char*)key + 0xc, key);
    if (e != last) {
        do {
            if (*e != *(int*)((char*)key + 0xc))
                return 0;
            if ((*(uint16*)((char*)e + 8) & 0x400) != 0) {
                *outFlags = *(uint16*)((char*)e + 8);
                return *(int*)((char*)e + 4);
            }
            e += 4;
        } while (e != last);
    }
    return 0;
}

// @ 0x008d5d70
namespace EA { namespace ResourceMan {
void* __fastcall FUN_008d5d70(void* pSubObject, void* /*unused*/)
{
    StreamInterface* pPrimary = reinterpret_cast<StreamInterface*>(static_cast<char*>(pSubObject) - 8);
    return pPrimary->v24();
}
}}  // namespace EA::ResourceMan

// @ 0x008d5d80
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles::FUN_008d5d80()
{
    if (mbInitialized) {
        mbInitialized = false;
        reinterpret_cast<DirectoryCloseInterface*>(this)->v1c();
    }
    return true;
}
}}  // namespace EA::ResourceMan

// @ 0x008d5f70
bool BackgroundRecordLoad::AddRef()
{
    if (_InterlockedExchangeAdd(&mnRefCount, 0) == 0)
        return false;
    _InterlockedExchangeAdd(&mnRefCount, 1);
    return true;
}

// @ 0x008d5fa0
bool BackgroundRecordLoad::Release()
{
    if (_InterlockedExchangeAdd(&mnRefCount, 0) == 0)
        return false;
    if (_InterlockedDecrement(&mnRefCount) == 0) {
        void* pOwner = mpOwner;
        return reinterpret_cast<bool (__thiscall*)(void*, void*)>(VtableOf(pOwner)[0x3c / 4])(pOwner, this);
    }
    return true;
}

// @ 0x008d5fe0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles::SetLocation(unsigned int nFlags, int nType)
{
    if (!mbInitialized)
        return false;
    if (nType == 6)
        nType = ((nFlags & 2) != 0) ? 4 : 3;
    if ((nFlags & 2) == 0 && nType != 3)
        return false;

    bool bExists = EA::IO::DirectoryExists(msDirectory.mpBegin);
    switch (nType) {
    case 1:
        if (bExists)
            return false;
        if (!EA::IO::DirectoryCreatePath(msDirectory.mpBegin))
            return false;
        break;
    case 2:
    case 4:
        if (!bExists && !EA::IO::DirectoryCreatePath(msDirectory.mpBegin))
            return false;
        break;
    case 3:
        if (!bExists)
            return false;
        break;
    case 5:
        if (!bExists)
            return false;
        if (!EA::IO::DirectoryRemoveRecursive(msDirectory.mpBegin, true))
            return false;
        if (!EA::IO::DirectoryCreatePath(msDirectory.mpBegin))
            return false;
        break;
    default:
        return false;
    }

    bool bOk = mbRequireDirectoryExists ? EA::IO::DirectoryExists(msDirectory.mpBegin) : true;
    if (nFlags == 0 || !bOk)
        return false;
    if (mnAccessFlags != 0 && mnAccessFlags != nFlags)
        return false;
    mnAccessFlags = nFlags;
    reinterpret_cast<void (__thiscall*)(void*, unsigned int)>(VtableOf(this)[0x58 / 4])(this, 0);
    return true;
}
}}  // namespace EA::ResourceMan

// @ 0x008d6140
void* BackgroundRecordLoad::Destroy(unsigned int nFlags)
{
    mpVtbl = &gVtbl14366c8;
    mStream.mpVtbl = &gVtbl1436678;
    if (_InterlockedExchangeAdd(&mnRefCount, 0) != 0) {
        void* pOwner = mpOwner;
        reinterpret_cast<void (__thiscall*)(void*, void*)>(VtableOf(pOwner)[0x3c / 4])(pOwner, this);
    }
    mStream.~FileStream_s008d_5340();
    mpVtbl = &gVtbl13effb8;
    if (nFlags & 1)
        ZoneObjectDelete(this);
    return this;
}

// @ 0x008d6290
namespace EA { namespace ResourceMan {
const wchar_t* DatabaseDirectoryFiles::GetExtensionByType(unsigned int nType)
{
    EA::Thread::Mutex_s008d_5340* pMutex = &mMutex;
    pMutex->Lock(reinterpret_cast<void*>(0x01436624));

    RBNode* pEnd = TreeAnchor(&mExtensionToTypeMap);
    for (RBNode* pNode = mExtensionToTypeMap.mpBegin; pNode != pEnd;
         pNode = static_cast<RBNode*>(RBTreeIncrement(pNode))) {
        if (*NodeExtValue(pNode) == nType) {
            const wchar_t* pExtension = NodeExtKey(pNode)->mpBegin;
            pMutex->Unlock();
            return pExtension;
        }
    }
    pMutex->Unlock();
    return 0;
}
}}  // namespace EA::ResourceMan

// @ 0x008d62f0
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_62f0::SetManager(bool bAttach, Manager_s008d_62f0* pManager, void* pContext)
{
    if (bAttach)
    {
        Manager_s008d_62f0* pOld = mpManager;
        if (pOld != 0 && pManager != pOld)
            SetSource(0, pOld, pContext);

        if (pManager == 0)
            return false;

        if (pContext == 0)
        {
            typedef bool (__thiscall *SetManagerFn)(Manager_s008d_62f0*, int, DatabaseDirectoryFiles_s008d_62f0*, void*);
            SetManagerFn pfn = *reinterpret_cast<SetManagerFn*>(*reinterpret_cast<uint8_t**>(pManager) + 0x50);
            return pfn(pManager, 1, this, 0);
        }

        mpManager = pManager;

        RBNode_s008d_62f0* pEnd = Anchor(&mRecordDataMap);
        for (RBNode_s008d_62f0* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode_s008d_62f0*>(RBTreeIncrement(pNode)))
        {
            typedef void (__thiscall *AddRecursiveFn)(Manager_s008d_62f0*, const Key_s008d_62f0*, const wchar_t*);
            AddRecursiveFn pfn = *reinterpret_cast<AddRecursiveFn*>(*reinterpret_cast<uint8_t**>(mpManager) + 0x80);
            pfn(mpManager, NodeKey(pNode), NodeValue(pNode)->mName.mpBegin);
        }
        return true;
    }

    if (pManager != 0 && pManager != mpManager)
        return false;

    if (pContext != 0)
    {
        mpManager = 0;
        return true;
    }

    typedef bool (__thiscall *SetManagerFn)(Manager_s008d_62f0*, int, DatabaseDirectoryFiles_s008d_62f0*, void*);
    SetManagerFn pfn = *reinterpret_cast<SetManagerFn*>(*reinterpret_cast<uint8_t**>(mpManager) + 0x50);
    return pfn(mpManager, 0, this, 0);
}
}}  // namespace EA::ResourceMan

// @ 0x008d6410
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_62f0::CloseUnreferencedRecords()
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode_s008d_62f0* pEnd = Anchor(&mRecordDataMap);
    for (RBNode_s008d_62f0* pNode = mRecordDataMap.mpBegin; pNode != pEnd; pNode = reinterpret_cast<RBNode_s008d_62f0*>(RBTreeIncrement(pNode)))
    {
        ListAnchor* pList = &NodeValue(pNode)->mRecords;
        int nCount = 0;
        for (void* p = pList->mpNext; p != pList; p = *reinterpret_cast<void**>(p))
            ++nCount;

        if (nCount == 1)
        {
            DDFRecord* pRecord = *reinterpret_cast<DDFRecord**>(reinterpret_cast<uint8_t*>(pList->mpNext) + 8);
            IRecordStream* pStream = pRecord->GetStream();
            if (pStream->GetFlags() & 2)
                pStream->Close();
        }
    }

    mMutex.Unlock();
    return true;
}
}}  // namespace EA::ResourceMan

// @ 0x008d64a0
namespace EA { namespace ResourceMan {
int DatabaseDirectoryFiles_s008d_62f0::GetRecordCount(const Key_s008d_62f0& key)
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode_s008d_62f0* pNode = 0;
    RbTreeFind(&mRecordDataMap, reinterpret_cast<void**>(&pNode), &key);

    if (pNode == Anchor(&mRecordDataMap))
    {
        mMutex.Unlock();
        return 0;
    }

    ListAnchor* pList = &NodeValue(pNode)->mRecords;
    int nCount = 0;
    for (void* p = pList->mpNext; p != pList; p = *reinterpret_cast<void**>(p))
        ++nCount;

    mMutex.Unlock();
    return nCount;
}
}}  // namespace EA::ResourceMan

// @ 0x008d6510
namespace EA { namespace ResourceMan {
bool DatabaseDirectoryFiles_s008d_62f0::GetRecordName(const Key_s008d_62f0& key, wchar_t* pName)
{
    mMutex.Lock(reinterpret_cast<void*>(0x1436624));

    RBNode_s008d_62f0* pNode = 0;
    RbTreeFind(&mRecordDataMap, reinterpret_cast<void**>(&pNode), &key);

    if (pNode == Anchor(&mRecordDataMap))
    {
        mMutex.Unlock();
        return false;
    }

    if (pName != 0)
    {
        const wchar_t* pSrc = NodeValue(pNode)->mName.mpBegin;
        wchar_t c;
        do
        {
            c = *pSrc++;
            *pName++ = c;
        } while (c != 0);
    }

    mMutex.Unlock();
    return true;
}
}}  // namespace EA::ResourceMan

// @ 0x008dcea0
PFRecordWrite::PFRecordWrite(unsigned access, unsigned size, const Key& key, DatabasePackedFile* parent)
{
    *(void**)raw = vtbl_ZoneObject_PFRecordRead;
    _InterlockedExchange((volatile long*)(raw + 4), 0);
    *(void**)raw = vtbl_PFRecordRead_base;
    *(unsigned*)(raw + 8) = 0x12e4a892;                 // kPFRecordTypeWrite
    *(uint32*)(raw + 0xc) = key.mInstance;
    *(uint32*)(raw + 0x10) = key.mType;
    *(uint32*)(raw + 0x14) = key.mGroup;
    *(void**)(raw + 0x18) = parent;
    *(unsigned*)(raw + 0x1c) = 3;
    *(void**)(raw + 0x20) = vtbl_IStream_default;
    *(void**)raw = vtbl_PFRecordWrite;
    *(void**)(raw + 0x20) = vtbl_PFRecordWrite_IStream;
    MemStreamW* ms = (MemStreamW*)(raw + 0x24);
    ms->Construct("ResourceMan/PFRecordWrite");
    FileStream* fs = (FileStream*)(raw + 0x48);
    fs->Construct(0);
    *(unsigned char*)(raw + 0x274) = 0;
    _InterlockedExchange((volatile long*)(raw + 0x278), 1);
    ms->w01();
    fs->f01();
    ms->SetOption(1, 1.0f);
    ms->SetOption(2, 1.5f);
    ms->SetOption(3, 1024.0f);
    if (size == 0)
        return;
    if (size <= 0x1e8480 || *(unsigned char*)(raw + 0x274) != 0)
        goto tail;
    *(unsigned char*)(raw + 0x274) = 1;
    if (!OpenTempFile())
        goto tail;
    {
        IAllocator* alloc = ((DatabasePackedFile*)*(void**)(raw + 0x18))->GetAllocator();
        void* buf = alloc->Alloc(0x4000, "Resource/Raw", 0);
        if (buf == 0)
            goto deltemp;
        unsigned done = 0;
        char ok = 1;
        while (done < size && ok) {
            unsigned chunk = size - done;
            if (chunk > 0x4000)
                chunk = 0x4000;
            ok = ((DatabasePackedFile*)*(void**)(raw + 0x18))->ReadFileSpan(
                     buf, done, (int)chunk) ? 1 : 0;
            if (ok) {
                ok = fs->f14() ? 1 : 0;
                done += chunk;
            }
        }
        if (ok)
            fs->f10(0, 0);
        alloc->Free(buf, 0);
        if (ok)
            return;
    }
deltemp:
    DeleteTempFile();
tail:
    {
        IAllocator* alloc = ((DatabasePackedFile*)*(void**)(raw + 0x18))->GetAllocator();
        if (ms->SetData(0, size, 0, 1, alloc))
            ((DatabasePackedFile*)*(void**)(raw + 0x18))->WriteFileSpan(ms->GetData(), 0, (int)size);
    }
    (void)access;
}

// @ 0x008dd0d0
void* PFRecordWrite_s008d_d0d0::ctor(int a2, int a3, int a4, void* a5, int a6)
{
    vtbl = (void**)0x13effa8;
    _InterlockedExchange((volatile long*)&mRefCount, 0);
    vtbl = (void**)0x140a2e0;
    mField08 = (int)0x12e4a892;
    int* k = (int*)a5;
    mKey[0] = k[0];
    mKey[1] = k[1];
    mKey[2] = k[2];
    mpDatabase = (void*)a6;
    mField1c = 3;
    vtbl20 = (void**)0x13f3a68;
    vtbl = (void**)0x1436968;
    vtbl20 = (void**)0x143692c;
    vtbl = (void**)0x1436968;
    vtbl20 = (void**)0x143692c;
    ((void* (__thiscall*)(void*, void*))FUN_0093bd50)(mMemStream, (void*)0x140a390);
    ((void* (__thiscall*)(void*, int))FUN_00931da0)(mFileStream, 0);
    *((char*)this + 0x274) = 0;
    _InterlockedExchange((volatile long*)((char*)this + 0x278), 1);
    ((void (__thiscall*)(void*))(((void**)*(void**)mMemStream)[1]))(mMemStream);
    ((void (__thiscall*)(void*))(((void**)*(void**)mFileStream)[1]))(mFileStream);
    ((void (__thiscall*)(void*, int, float))FUN_0093bb40)(mMemStream, 1, 1.0f);
    void* db = mpDatabase;
    int u = ((int (__thiscall*)(void*))(((void**)*(void**)db)[0x48 / 4]))(db);
    ((void (__thiscall*)(void*, void*, void*, int, int, void*))FUN_0093be30)(
        mMemStream, (void*)a2, (void*)a3, a4, 1, (void*)u);
    return this;
}

// @ 0x008dd1f0
void* PFRecordWrite_s008d_d0d0::_virtual_dtor(int flags)
{
    vtbl = (void**)0x1436968;
    vtbl20 = (void**)0x143692c;
    if (mField1c != 0) {
        void* db = mpDatabase;
        ((void (__thiscall*)(void*, void*))(((void**)*(void**)db)[0x3c / 4]))(db, this);
    }
    FUN_008dcbf0(this);
    FUN_00931e70(mFileStream);
    FUN_0093bde0(mMemStream);
    vtbl20 = (void**)0x13f3a68;
    vtbl = (void**)0x13effb8;
    if (flags & 1)
        operator_delete__(this);
    return this;
}

// @ 0x008dd510
extern "C" int FUN_008dd510(const wchar_t* path)
{
    char fs[0x22c];
    FUN_00931da0(fs, 0);
    FUN_00931810(fs, path);
    if (!FUN_009318f0(fs, 1, 6, 1, 0)) {
        FUN_00931e70(fs);
        return -1;
    }
    unsigned total = (unsigned)FUN_00931b70(fs);
    unsigned* buf = (unsigned*)operator_new(0x201, "EASTL", 0, 0, "", 0xd1);
    operator_new_arr(buf, 0, 0x200);
    *((char*)buf + 0x200) = 0;
    unsigned char* pat = (unsigned char*)operator_new(0x11, "EASTL", 0, 0, "", 0xd1);
    pat[0] = 0x7f; pat[1] = 0x9d; pat[2] = 0x88; pat[3] = 0xec;
    pat[4] = 0x8f; pat[5] = 0x24; pat[6] = 3;   pat[7] = 0x6c;
    pat[8] = 0xc9; pat[9] = 0xa6; pat[10] = 0x31; pat[11] = 0x56;
    pat[12] = 0x5b; pat[13] = 0xcf; pat[14] = 0x77; pat[15] = 0x20;
    pat[16] = 0;
    pat[0] = (unsigned char)~pat[0];
    int found = -1;
    unsigned filled = 0;
    if (total != 0) {
        unsigned patLen = (unsigned)(pat + 0x10 - pat);
        do {
            unsigned got = FUN_00931ce0(fs, (char*)buf + filled, 0x200 - filled);
            unsigned r = FUN_00609d90(buf, buf + 0x80, pat, pat + patLen) == buf + 0x80
                             ? (unsigned)((char*)buf + patLen - (char*)buf)
                             : 0xffffffff;
            if (r != 0xffffffff) {
                found = got - 0x10 < r ? -1 : (int)(r + 0x10 + filled);
                break;
            }
            memmove(buf, (char*)buf + 0x1f1, 0xf);
            filled += 0x1f1;
            if (filled >= total)
                break;
        } while (true);
    }
    FUN_00931a70(fs);
    operator_delete__(pat);
    if (buf != 0)
        operator_delete__(buf);
    FUN_00931e70(fs);
    return found;
}

// @ 0x008ddde0
extern "C" int FUN_008ddde0(void* a1, void* a2)
{
    int local;
    if (FUN_0093a780(a1, &local, 1, a2))
        return local;
    return -1;
}

// @ 0x008dde10
void EditorResource::dtor()
{
    void* p = mpData;
    vtbl = (void**)0x1436a00;
    if (p != 0)
        ((MemAlloc*)g_pMemAlloc)->Free(p);
    vtbl = (void**)0x13eb938;
}
