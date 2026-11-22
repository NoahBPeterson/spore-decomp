// src/game/UTFSpore_Win32/DatabasePackedFile_v2.cpp -- migrated from slice(s) s006bde30, s006bd150, s006bc1b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabasePackedFile_v2.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/CompressionRefpack.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/IO/FileStream.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Thread/Mutex.h"
#include "EA/ResourceMan/PFHoleTable.h"
#include "EA/ResourceMan/PFIndexModifiable.h"
#include "EA/ResourceMan/DatabasePackedFile_v2.h"
#include "EA/IO/IStream.h"
#include "EA/ResourceMan/Record.h"
#include "EA/ResourceMan/PFRecordInfo.h"
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern char g_mutexParam;   // 0x0140a088

// ---- items of slice s006bc1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint32;
typedef unsigned short uint16;
typedef unsigned long long uint64;
namespace EA {
namespace Thread {
struct Mutex_s006b_c1b0 {
    int Lock(const void* p);   // 0x9221b0
    int Unlock();              // 0x922270
    char pad00[0x30];
};
}
}
namespace EA {
namespace Thread {
struct AutoLock {
    Mutex_s006b_c1b0* mpMutex;
    AutoLock(Mutex_s006b_c1b0& m, const void* p) : mpMutex(&m) { m.Lock(p); }
    ~AutoLock() { mpMutex->Unlock(); }
};
}
}
namespace EA {
namespace IO {
struct FileStream_s006b_c1b0 {
    int      FUN_00928f70();                        // 0x928f70
    int      GetLastError();                       // 0x928f70
    void     SetPath(const wchar_t* p);            // 0x928f80
    int64_t  FUN_00928fc0();                        // 0x928fc0  (position)
    bool     FUN_009290c0();                        // 0x9290c0
    int      FUN_00929100(const void* src, uint32 n);// 0x929100
    bool     FUN_00929470(uint32 a, int b, int c, int d); // 0x929470
    void     FUN_00929290();                        // 0x929290
    bool     FUN_009297a0(int a, int b);            // 0x9297a0
    bool     FUN_00929900(int a, int b, int c);     // 0x929900
    bool     FUN_00929a70(const void* p, uint32 n); // 0x929a70
    char data[0x434];
};  // namespace EA::IO
}
}
struct PFHoleTable {
    int   field_0;
    char  pad[0x24];
    int64_t FUN_006bfc50(uint32 a, uint32 b);       // 0x6bfc50
    void    FUN_006bff10(PFHoleTable* other);        // 0x6bff10
    bool    FUN_006bff90(uint32 a, uint32 b, int c, int d); // 0x6bff90
    void    FUN_006bef70(uint32 a, uint32 b);        // 0x6bef70
    void    FUN_006bfda0(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bfda0
    void    FUN_006bf5a0();                          // 0x6bf5a0
};
struct PFHeader {
    uint32 magic;         // 0x00
    uint32 major;         // 0x04
    uint32 minor;         // 0x08
    uint32 userMajor;     // 0x0c
    uint32 userMinor;     // 0x10
    uint32 flags;         // 0x14
    uint32 created;       // 0x18
    uint32 modified;      // 0x1c
    uint32 indexCount;    // 0x20
    uint32 indexMajor;    // 0x24
    uint32 indexSize;     // 0x28
    uint32 indexOffset;   // 0x2c
    uint32 holeCount;     // 0x30
    uint32 holeOffset;    // 0x34
    uint32 holeSize;      // 0x38
    uint32 indexMinor;    // 0x3c
    uint64 indexOffset2;  // 0x40
    uint32 reserved[13];  // 0x48
};
struct RBTreeHead {
    char data[0x20];
    void** find(void* out, const void* key);  // 0xa21dc0
};
void* __cdecl operator_new_array(void* dst, int a, unsigned n);  // 0x11e073e
struct CompressionRefpack_s006b_c1b0 {
    virtual void vfunc();
    char   pad[8];
    uint32 field_c;
    bool   IsValidHeader(const void* p, uint32 n);                       // 0x92cad0
    int    Decompress(const void* p, uint32 n, void* d, uint32 dn, int f);// 0x92ca60
    int    FUN_0092c9f0(const void* p, uint32 n, void* d, uint32 dn, int f); // 0x92c9f0
};
struct ICoreAllocator {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
};
struct PFIndexModifiable;
struct Key { uint32 type; uint32 group; uint32 instance; };
struct DatabasePackedFile {
    void*   vtbl;             // 0x000
    char    pad004[8];        // 0x004
    bool    mbInitialized;    // 0x00c
    char    pad00d[3];        // 0x00d
    ICoreAllocator* mpAllocator; // 0x010
    uint32  mnAccessFlags;    // 0x014
    uint32  mnAutoOpenAccessFlags; // 0x018
    bool    mbEnableReadOnCorruptFiles;  // 0x01c
    bool    mbEnableWriteOnCorruptFiles; // 0x01d
    char    pad01e[2];        // 0x01e
    char    mFilePath[0x10];  // 0x020 (eastl::string16)
    EA::IO::FileStream_s006b_c1b0 mFile; // 0x030
    uint32  mnFileStartingOffset; // 0x464
    void*   mpCurrentStream;  // 0x468
    void*   mpDataBuffer;     // 0x46c
    uint32  mnBufferSize;     // 0x470
    uint32  mnBufferOffset;   // 0x474
    EA::Thread::Mutex_s006b_c1b0 mIndexMutex;   // 0x478
    EA::Thread::Mutex_s006b_c1b0 mReadWriteMutex; // 0x4a8
    PFIndexModifiable* mpIndex;      // 0x4d8
    bool    field_4dc;        // 0x4dc
    char    pad04dd[3];
    uint32  field_4e0;        // 0x4e0
    uint32  field_4e4;        // 0x4e4
    bool    field_4e8;        // 0x4e8
    char    pad04e9[3];
    float   field_4ec;        // 0x4ec
    uint32  field_4f0[2];     // 0x4f0
    void*   mapRoot;          // 0x4f8
    uint32  field_4fc[2];     // 0x4fc
    uint32  mapCount;         // 0x504
    uint32  field_508[2];     // 0x508
    uint32  field_510[12];    // 0x510
    bool    field_540;        // 0x540
    char    pad0541[3];
    uint32  field_544;        // 0x544
    float   field_548;        // 0x548
    char    pad054c[4];
    PFHoleTable mHoleTable0;  // 0x550
    PFHoleTable mHoleTable1;  // 0x578
    bool    field_5a0;        // 0x5a0
    char    pad05a1[3];
    void*   field_5a4;        // 0x5a4

    // Slice functions / internal helpers.
    bool FUN_006bc0a0();      // 0x6bc0a0
    void MakeIndexModifiable();               // 0x6bc1b0
    bool FUN_006bc2d0(uint64* out, uint32 a, uint32 b);   // 0x6bc2d0
    bool FUN_006bc310(uint32 a, uint32 b, uint32 c, uint32 d, char e); // 0x6bc310
    bool FUN_006bc370(uint64* out);           // 0x6bc370
    bool FUN_006bc3a0(uint32 flags, float ratio); // 0x6bc3a0
    int  FUN_006bc3e0(uint32 a, int n);       // 0x6bc3e0
    char FUN_006bc420(char p2, void* p3, char p4); // 0x6bc420
    bool FUN_006bc4d0(uint32 p2, int p3, bool p4); // 0x6bc4d0
    bool DeleteRecord();                      // 0x6bc5f0
    void* FUN_006bc6f0(uint32 a, uint32 b);   // 0x6bc6f0
    bool FUN_006bc7a0();                      // 0x6bc7a0
    bool FUN_006bc870(const char* h);         // 0x6bc870
    void FUN_006bc8e0();                      // 0x6bc8e0
    bool FUN_006bc970();                      // 0x6bc970
    void FUN_006bca70();                      // 0x6bca70
    bool ReadFileSpan(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bca90
    bool FUN_006bcb50(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bcb50
    bool DecompressData(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e); // 0x6bcc10
    bool DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e, uint32 f); // 0x6bccb0
    bool FUN_006bcd30();                      // 0x6bcd30
    bool FUN_006bcd70(uint32 key);            // 0x6bcd70
    bool FUN_006bcea0();                      // 0x6bcea0
    void FUN_006bd070();                      // 0x6bd070

    // Slice s006bd150
    bool FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags);
    void FUN_006bd300();
    char FUN_006bd430(char p2);
    int  FUN_006bd4d0(Key* key);
    bool FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6);
    bool SetLocation(const wchar_t* p);
    bool FUN_006bd690(void* p2);
    void* FUN_006bdc50(const wchar_t* p2, int p3);

    // Slice s006bde30
    bool OpenRecord(void* key, void** ppRecord, uint32 desiredAccess, int createDisposition,
                    char flag, void* pInfo);
    bool FUN_006be1d0();
    bool FUN_006be350();
};
struct PFIndexModifiable {
    void* vtbl;                  // 0x00
    ICoreAllocator* mpAllocator; // 0x04
    char   pad08[0x24];          // 0x08 (FixedPoolAllocator)
    uint32* mapBucketArray;      // 0x2c
    uint32  mapBucketCount;      // 0x30
    char   pad34[0x18];          // 0x34

    void   SetIsSaved();         // 0x6bed90
    uint64 GetDataEnd();         // 0x6bea90
    uint64 GetTotalDiskSize();   // 0x6beb00
    bool   Write();              // 0x6beb60
    bool   CheckFilesInRange(uint32 begin, uint32 end);    // 0x6bede0
    bool   CheckFilesInSizeRange(uint32 begin, uint32 size);// 0x6beeb0

    // Slice s006bede0
    void* GetFileInfo(const Key* key);
    bool  RemoveFile(const Key* key, void* out);
    void* PutFileInfo(const Key* key, const void* info);
    void* GetFiles(void* dst, void* filter);
    void* GetAllFiles(void* dst);
    bool  Read(void* data, uint32 size, uint32 count, int flag);
    void* PFIndexModifiable_(void* allocator);
};
struct RecordInfo { uint32 f0, f4, f8, fc; uint16 f10; char f12; };
// ---- items of slice s006bc1b0 end

// ---- items of slice s006bd150 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_DBPF_140a138[];   // 0x0140a138
extern char vtbl_DBPF_140a124[];   // 0x0140a124
extern char vtbl_DBPF_1408500[];   // 0x01408500
extern char vtbl_DBPF_14084f0[];   // 0x014084f0
extern char vtbl_DBPF_13f1ab0[];   // 0x013f1ab0
extern char vtbl_DBPF_13eb938[];   // 0x013eb938
extern char vtbl_DBPF_13effb8[];   // 0x013effb8
extern wchar_t gEmptyString16[];     // 0x01667bac  eastl::gEmptyString16
extern wchar_t gEmptyString16End[];  // 0x01667bae
extern const float kRatio095;        // 0x0140a098  (0.95f, kCompressRatio)
extern const float kRatio015;        // 0x0140a094  (0.15f, kHoleRatio)
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
typedef unsigned char  uint8;
namespace EA {
namespace Thread {
class Mutex_s006b_d150 { public:
    int Lock(const void* p);   // 0x9221b0
    int Unlock();              // 0x922270
    char pad00[0x30];
};
}
}
namespace EA {
namespace Thread {
struct AutoLock_s006b_d150 {
    Mutex_s006b_d150* mpMutex;
    AutoLock_s006b_d150(Mutex_s006b_d150& m, const void* p) : mpMutex(&m) { m.Lock(p); }
    ~AutoLock_s006b_d150() { mpMutex->Unlock(); }
};
}
}
namespace EA {
namespace IO {
class FileStream_s006b_d150 { public:
    int      FUN_00928f70();                        // 0x928f70
    int      GetLastError();                       // 0x928f70
    void     SetPath(const wchar_t* p);            // 0x928f80
    int64_t  FUN_00928fc0();                        // 0x928fc0  (position)
    bool     FUN_009290c0();                        // 0x9290c0
    int      FUN_00929100(const void* src, uint32 n);// 0x929100
    bool     FUN_00929470(uint32 a, int b, int c, int d); // 0x929470
    void     FUN_00929290();                        // 0x929290
    bool     FUN_009297a0(int a, int b);            // 0x9297a0
    bool     FUN_00929900(int a, int b, int c);     // 0x929900
    bool     FUN_00929a70(const void* p, uint32 n); // 0x929a70
    char data[0x434];
};  // namespace EA::IO
}
}
struct PFHoleTable_s006b_d150 {
    int   field_0;
    char  pad[0x24];
    int64_t FUN_006bfc50(uint32 a, uint32 b);       // 0x6bfc50
    void    FUN_006bff10(PFHoleTable_s006b_d150* other);        // 0x6bff10
    bool    FUN_006bff90(uint32 a, uint32 b, int c, int d); // 0x6bff90
    void    FUN_006bef70(uint32 a, uint32 b);        // 0x6bef70
    void    FUN_006bfda0(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bfda0
    void    FUN_006bf5a0();                          // 0x6bf5a0
};
struct WStringAssign {
    char data[0x10];
    void assign(const wchar_t* first, const wchar_t* last);
};
void* __cdecl RBTreeIncrement(void* node);   // 0x921580
void  __cdecl RBTreeErase(void* a, void* b); // 0x921880
struct CompressionRefpack_s006b_d150 {
    virtual void vfunc();
    char   pad[8];
    uint32 field_c;
    bool   IsValidHeader(const void* p, uint32 n);                       // 0x92cad0
    int    Decompress(const void* p, uint32 n, void* d, uint32 dn, int f);// 0x92ca60
    int    FUN_0092c9f0(const void* p, uint32 n, void* d, uint32 dn, int f); // 0x92c9f0
};
void __cdecl sub_11E0744(void* dst, const void* src, uint32 n);   // 0x11e0744
struct ICoreAllocator_s006b_d150 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
};
struct PFIndexModifiable_s006b_d150;
struct Key_s006b_d150 { uint32 type; uint32 group; uint32 instance; };
struct DatabasePackedFile_s006b_d150 {
    void*   vtbl;             // 0x000
    char    pad004[8];        // 0x004
    bool    mbInitialized;    // 0x00c
    char    pad00d[3];        // 0x00d
    ICoreAllocator_s006b_d150* mpAllocator; // 0x010
    uint32  mnAccessFlags;    // 0x014
    uint32  mnAutoOpenAccessFlags; // 0x018
    bool    mbEnableReadOnCorruptFiles;  // 0x01c
    bool    mbEnableWriteOnCorruptFiles; // 0x01d
    char    pad01e[2];        // 0x01e
    char    mFilePath[0x10];  // 0x020 (eastl::string16)
    EA::IO::FileStream_s006b_d150 mFile; // 0x030
    uint32  mnFileStartingOffset; // 0x464
    void*   mpCurrentStream;  // 0x468
    void*   mpDataBuffer;     // 0x46c
    uint32  mnBufferSize;     // 0x470
    uint32  mnBufferOffset;   // 0x474
    EA::Thread::Mutex_s006b_d150 mIndexMutex;   // 0x478
    EA::Thread::Mutex_s006b_d150 mReadWriteMutex; // 0x4a8
    PFIndexModifiable_s006b_d150* mpIndex;      // 0x4d8
    bool    field_4dc;        // 0x4dc
    char    pad04dd[3];
    uint32  field_4e0;        // 0x4e0
    uint32  field_4e4;        // 0x4e4
    bool    field_4e8;        // 0x4e8
    char    pad04e9[3];
    float   field_4ec;        // 0x4ec
    uint32  field_4f0[2];     // 0x4f0
    void*   mapRoot;          // 0x4f8
    uint32  field_4fc[2];     // 0x4fc
    uint32  mapCount;         // 0x504
    uint32  field_508[2];     // 0x508
    uint32  field_510[12];    // 0x510
    bool    field_540;        // 0x540
    char    pad0541[3];
    uint32  field_544;        // 0x544
    float   field_548;        // 0x548
    char    pad054c[4];
    PFHoleTable_s006b_d150 mHoleTable0;  // 0x550
    PFHoleTable_s006b_d150 mHoleTable1;  // 0x578
    bool    field_5a0;        // 0x5a0
    char    pad05a1[3];
    void*   field_5a4;        // 0x5a4

    // Slice functions / internal helpers.
    bool FUN_006bc0a0();      // 0x6bc0a0
    void MakeIndexModifiable();               // 0x6bc1b0
    bool FUN_006bc2d0(uint64* out, uint32 a, uint32 b);   // 0x6bc2d0
    bool FUN_006bc310(uint32 a, uint32 b, uint32 c, uint32 d, char e); // 0x6bc310
    bool FUN_006bc370(uint64* out);           // 0x6bc370
    bool FUN_006bc3a0(uint32 flags, float ratio); // 0x6bc3a0
    int  FUN_006bc3e0(uint32 a, int n);       // 0x6bc3e0
    char FUN_006bc420(char p2, void* p3, char p4); // 0x6bc420
    bool FUN_006bc4d0(uint32 p2, int p3, bool p4); // 0x6bc4d0
    bool DeleteRecord();                      // 0x6bc5f0
    void* FUN_006bc6f0(uint32 a, uint32 b);   // 0x6bc6f0
    bool FUN_006bc7a0();                      // 0x6bc7a0
    bool FUN_006bc870(const char* h);         // 0x6bc870
    void FUN_006bc8e0();                      // 0x6bc8e0
    bool FUN_006bc970();                      // 0x6bc970
    void FUN_006bca70();                      // 0x6bca70
    bool ReadFileSpan(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bca90
    bool FUN_006bcb50(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bcb50
    bool DecompressData(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e); // 0x6bcc10
    bool DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e, uint32 f); // 0x6bccb0
    bool FUN_006bcd30();                      // 0x6bcd30
    bool FUN_006bcd70(uint32 key);            // 0x6bcd70
    bool FUN_006bcea0();                      // 0x6bcea0
    void FUN_006bd070();                      // 0x6bd070

    // Slice s006bd150
    bool FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags);  // 0x006bd150 (DatabasePackedFile::FUN_006bd150)
    void FUN_006bd300();  // 0x006bd300 (DatabasePackedFile::FUN_006bd300)
    char FUN_006bd430(char p2);  // 0x006bd430 (DatabasePackedFile::FUN_006bd430)
    int  FUN_006bd4d0(Key_s006b_d150* key);  // 0x006bd4d0 (DatabasePackedFile::FUN_006bd4d0)
    bool FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6);  // 0x006bd580 (DatabasePackedFile::FUN_006bd580)
    bool SetLocation(const wchar_t* p);  // 0x006bd650 (DatabasePackedFile::SetLocation)
    bool FUN_006bd690(void* p2);  // 0x006bd690 (DatabasePackedFile::FUN_006bd690)
    void* FUN_006bdc50(const wchar_t* p2, int p3);  // 0x006bdc50 (DatabasePackedFile::FUN_006bdc50)

    // Slice s006bde30
    bool OpenRecord(void* key, void** ppRecord, uint32 desiredAccess, int createDisposition,
                    char flag, void* pInfo);
    bool FUN_006be1d0();  // 0x006be1d0 (DatabasePackedFile::FUN_006be1d0)
    bool FUN_006be350();
};
struct PFIndexModifiable_s006b_d150 {
    void* vtbl;                  // 0x00
    ICoreAllocator_s006b_d150* mpAllocator; // 0x04
    char   pad08[0x24];          // 0x08 (FixedPoolAllocator)
    uint32* mapBucketArray;      // 0x2c
    uint32  mapBucketCount;      // 0x30
    char   pad34[0x18];          // 0x34

    void   SetIsSaved();         // 0x6bed90
    uint64 GetDataEnd();         // 0x6bea90
    uint64 GetTotalDiskSize();   // 0x6beb00
    bool   Write();              // 0x6beb60
    bool   CheckFilesInRange(uint32 begin, uint32 end);    // 0x6bede0
    bool   CheckFilesInSizeRange(uint32 begin, uint32 size);// 0x6beeb0

    // Slice s006bede0
    void* GetFileInfo(const Key_s006b_d150* key);  // 0x008db810 (PFIndexModifiable::GetFileInfo)
    bool  RemoveFile(const Key_s006b_d150* key, void* out);  // 0x008db850 (PFIndexModifiable::RemoveFile)
    void* PutFileInfo(const Key_s006b_d150* key, const void* info);  // 0x008dbeb0 (PFIndexModifiable::PutFileInfo)
    void* GetFiles(void* dst, void* filter);  // 0x008dbcf0 (PFIndexModifiable::GetFiles)
    void* GetAllFiles(void* dst);  // 0x008dbdb0 (PFIndexModifiable::GetAllFiles)
    bool  Read(void* data, uint32 size, uint32 count, int flag);  // 0x008db9b0 (PFIndexModifiable::Read)
    void* PFIndexModifiable_(void* allocator);
};
ICoreAllocator_s006b_d150* GetDefaultAllocator();     // 0x00925cb0
void* __cdecl sub_11E073E(void* dst, int val, unsigned n);   // 0x011e073e (memset)
void  __cdecl EAFree(void* p);             // 0x00f47380
struct DBPFHead {
    void* mpVtbl0;     // 0x00
    void* mpVtbl4;     // 0x04
    long  mnRefCount;  // 0x08
};
struct WString16 {
    wchar_t* mpBegin;     // 0x00
    wchar_t* mpEnd;       // 0x04
    wchar_t* mpCapacity;  // 0x08
    char     pad00c[4];
};
struct FileStreamX {
    void Construct(const void* params);   // 0x00929220
    void AddRef();                        // 0x00928e10
    void Destroy();                       // 0x00929450
};
struct MutexX {
    void Construct(const void* params, bool b);   // 0x009222a0
    void Destroy();                               // 0x00922130
};
struct HoleTableX {
    void Destroy();                               // 0x006bef60
};
struct RecNode;
struct RecMap {
    uint32          mCompare;   // 0x00  (never initialised by the ctor)
    RecNode*        mRight;     // 0x04  (anchor.right, points back at the anchor)
    RecNode*        mLeft;      // 0x08  (anchor.left)
    RecNode*        mParent;    // 0x0c  (anchor.parent = tree root)
    uint32          mColor;     // 0x10  (anchor colour, stored as a whole dword)
    uint32          mnSize;     // 0x14
    ICoreAllocator_s006b_d150* mpAlloc;    // 0x18
    uint32          mnFlags;    // 0x1c

    RecNode* Anchor() { return reinterpret_cast<RecNode*>(&mRight); }
    RecNode** Find(RecNode** out, const Key_s006b_d150* key);   // 0x00a21dc0
    void DoFreeNodes(RecNode* root);                 // 0x008de4f0
};
struct RecNode {
    RecNode* mRight;    // 0x00
    RecNode* mLeft;     // 0x04
    RecNode* mParent;   // 0x08
    int      mnColor;   // 0x0c
    Key_s006b_d150      mKey;      // 0x10
    void*    mpValue;   // 0x1c
};
struct IdxEntry {
    uint32 posLo;       // 0x00
    uint32 posHi;       // 0x04
    uint32 size;        // 0x08
    uint32 usize;       // 0x0c
    uint16 flags;       // 0x10
    uint8  compressed;  // 0x12
    char   pad013;
};
struct PFIndexVtbl {
    virtual void i00();
    virtual void i04();
    virtual void i08();
    virtual void i0c();
    virtual void i10();
    virtual void i14();
    virtual void i18();
    virtual void i1c();
    virtual void i20();
    virtual void i24();
    virtual void i28();
    virtual void SetEntry(const Key_s006b_d150* key, const IdxEntry* entry);   // +0x2c
    virtual bool GetEntry(const Key_s006b_d150* key, IdxEntry* entry);         // +0x30
};
struct IStreamX {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual int  GetSize();                         // +0x1c
    virtual void s20();
    virtual void s24();
    virtual bool SetPosition(int pos, int origin);  // +0x28
    virtual void s2c();
    virtual int  Read(void* buf, int size);         // +0x30
};
struct Record_s006b_d150 {
    virtual void r00();              // +0x00
    virtual void r04();              // +0x04
    virtual int  Release();          // +0x08
    virtual void r0c();              // +0x0c
    virtual Key_s006b_d150* GetKey();           // +0x10
    virtual void r14();              // +0x14
    virtual IStreamX* GetStream();   // +0x18
    virtual void r1c();              // +0x1c
    virtual void r20();              // +0x20
    virtual void r24();              // +0x24
    virtual void Detach();           // +0x28
    char pad04[4];                   // +0x04
    int  mnMagic;                    // +0x08
    char pad0c[0x14];                // +0x0c .. +0x1f
    IStreamX mStream;                // +0x20
    // Chunked write of this record's stream at a raw file span (0x6c05a0).
    bool DoRead(uint32 posLo, uint32 posHi, uint32 n);   // 0x006c05a0
};
inline void* AllocBlock(ICoreAllocator_s006b_d150* alloc, uint32 n, const char* name, uint32 flags)
{
    return ((void*(__thiscall*)(ICoreAllocator_s006b_d150*, uint32, const char*, uint32))
            (*(void***)alloc)[8 / 4])(alloc, n, name, flags);
}
inline void FreeBlock(ICoreAllocator_s006b_d150* alloc, void* p, uint32 n)
{
    ((void(__thiscall*)(ICoreAllocator_s006b_d150*, void*, uint32))(*(void***)alloc)[0xc / 4])(alloc, p, n);
}
// ---- items of slice s006bd150 end

// ---- items of slice s006bde30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
class Mutex_s006b_de30 { public:
    int Lock(const void* p);   // 0x9221b0
    int Unlock();              // 0x922270
    char pad00[0x30];
};
}
}
namespace EA {
namespace Thread {
struct AutoLock_s006b_de30 {
    Mutex_s006b_de30* mpMutex;
    AutoLock_s006b_de30(Mutex_s006b_de30& m, const void* p) : mpMutex(&m) { m.Lock(p); }
    ~AutoLock_s006b_de30() { mpMutex->Unlock(); }
};
}
}
namespace EA {
namespace IO {
class FileStream_s006b_de30 { public:
    int      FUN_00928f70();                        // 0x928f70
    int      GetLastError();                       // 0x928f70
    void     SetPath(const wchar_t* p);            // 0x928f80
    int64_t  FUN_00928fc0();                        // 0x928fc0  (position)
    bool     FUN_009290c0();                        // 0x9290c0
    int      FUN_00929100(const void* src, uint32 n);// 0x929100
    bool     FUN_00929470(uint32 a, int b, int c, int d); // 0x929470
    void     FUN_00929290();                        // 0x929290
    bool     FUN_009297a0(int a, int b);            // 0x9297a0
    bool     FUN_00929900(int a, int b, int c);     // 0x929900
    bool     FUN_00929a70(const void* p, uint32 n); // 0x929a70
    char data[0x434];
};  // namespace EA::IO
}
}
struct PFHoleTable_s006b_de30 {
    int   field_0;
    char  pad[0x24];
    int64_t FUN_006bfc50(uint32 a, uint32 b);       // 0x6bfc50
    void    FUN_006bff10(PFHoleTable_s006b_de30* other);        // 0x6bff10
    bool    FUN_006bff90(uint32 a, uint32 b, int c, int d); // 0x6bff90
    void    FUN_006bef70(uint32 a, uint32 b);        // 0x6bef70
    void    FUN_006bfda0(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bfda0
    void    FUN_006bf5a0();                          // 0x6bf5a0
};
struct ICoreAllocator_s006b_de30 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
};
struct PFIndexModifiable_s006b_de30;
struct Key_s006b_de30 { uint32 type; uint32 group; uint32 instance; };
struct DatabasePackedFile_s006b_de30 {
    void*   vtbl;             // 0x000
    char    pad004[8];        // 0x004
    bool    mbInitialized;    // 0x00c
    char    pad00d[3];        // 0x00d
    ICoreAllocator_s006b_de30* mpAllocator; // 0x010
    uint32  mnAccessFlags;    // 0x014
    uint32  mnAutoOpenAccessFlags; // 0x018
    bool    mbEnableReadOnCorruptFiles;  // 0x01c
    bool    mbEnableWriteOnCorruptFiles; // 0x01d
    char    pad01e[2];        // 0x01e
    char    mFilePath[0x10];  // 0x020 (eastl::string16)
    EA::IO::FileStream_s006b_de30 mFile; // 0x030
    uint32  mnFileStartingOffset; // 0x464
    void*   mpCurrentStream;  // 0x468
    void*   mpDataBuffer;     // 0x46c
    uint32  mnBufferSize;     // 0x470
    uint32  mnBufferOffset;   // 0x474
    EA::Thread::Mutex_s006b_de30 mIndexMutex;   // 0x478
    EA::Thread::Mutex_s006b_de30 mReadWriteMutex; // 0x4a8
    PFIndexModifiable_s006b_de30* mpIndex;      // 0x4d8
    bool    field_4dc;        // 0x4dc
    char    pad04dd[3];
    uint32  field_4e0;        // 0x4e0
    uint32  field_4e4;        // 0x4e4
    bool    field_4e8;        // 0x4e8
    char    pad04e9[3];
    float   field_4ec;        // 0x4ec
    uint32  field_4f0[2];     // 0x4f0
    void*   mapRoot;          // 0x4f8
    uint32  field_4fc[2];     // 0x4fc
    uint32  mapCount;         // 0x504
    uint32  field_508[2];     // 0x508
    uint32  field_510[12];    // 0x510
    bool    field_540;        // 0x540
    char    pad0541[3];
    uint32  field_544;        // 0x544
    float   field_548;        // 0x548
    char    pad054c[4];
    PFHoleTable_s006b_de30 mHoleTable0;  // 0x550
    PFHoleTable_s006b_de30 mHoleTable1;  // 0x578
    bool    field_5a0;        // 0x5a0
    char    pad05a1[3];
    void*   field_5a4;        // 0x5a4

    // Slice functions / internal helpers.
    bool FUN_006bc0a0();      // 0x6bc0a0
    void MakeIndexModifiable();               // 0x6bc1b0
    bool FUN_006bc2d0(uint64* out, uint32 a, uint32 b);   // 0x6bc2d0
    bool FUN_006bc310(uint32 a, uint32 b, uint32 c, uint32 d, char e); // 0x6bc310
    bool FUN_006bc370(uint64* out);           // 0x6bc370
    bool FUN_006bc3a0(uint32 flags, float ratio); // 0x6bc3a0
    int  FUN_006bc3e0(uint32 a, int n);       // 0x6bc3e0
    char FUN_006bc420(char p2, void* p3, char p4); // 0x6bc420
    bool FUN_006bc4d0(uint32 p2, int p3, bool p4); // 0x6bc4d0
    bool DeleteRecord();                      // 0x6bc5f0
    void* FUN_006bc6f0(uint32 a, uint32 b);   // 0x6bc6f0
    bool FUN_006bc7a0();                      // 0x6bc7a0
    bool FUN_006bc870(const char* h);         // 0x6bc870
    void FUN_006bc8e0();                      // 0x6bc8e0
    bool FUN_006bc970();                      // 0x6bc970
    void FUN_006bca70();                      // 0x6bca70
    bool ReadFileSpan(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bca90
    bool FUN_006bcb50(uint32 a, uint32 b, uint32 c, uint32 d); // 0x6bcb50
    bool DecompressData(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e); // 0x6bcc10
    bool DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e, uint32 f); // 0x6bccb0
    bool FUN_006bcd30();                      // 0x6bcd30
    bool FUN_006bcd70(uint32 key);            // 0x6bcd70
    bool FUN_006bcea0();                      // 0x6bcea0
    void FUN_006bd070();                      // 0x6bd070

    // Slice s006bd150
    bool FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags);  // 0x006bd150 (DatabasePackedFile::FUN_006bd150)
    void FUN_006bd300();  // 0x006bd300 (DatabasePackedFile::FUN_006bd300)
    char FUN_006bd430(char p2);  // 0x006bd430 (DatabasePackedFile::FUN_006bd430)
    int  FUN_006bd4d0(Key_s006b_de30* key);  // 0x006bd4d0 (DatabasePackedFile::FUN_006bd4d0)
    bool FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6);  // 0x006bd580 (DatabasePackedFile::FUN_006bd580)
    bool SetLocation(const wchar_t* p);  // 0x006bd650 (DatabasePackedFile::SetLocation)
    bool FUN_006bd690(void* p2);  // 0x006bd690 (DatabasePackedFile::FUN_006bd690)
    void* FUN_006bdc50(const wchar_t* p2, int p3);  // 0x006bdc50 (DatabasePackedFile::FUN_006bdc50)

    // Slice s006bde30
    bool OpenRecord(void* key, void** ppRecord, uint32 desiredAccess, int createDisposition,
                    char flag, void* pInfo);
    bool FUN_006be1d0();  // 0x006be1d0 (DatabasePackedFile::FUN_006be1d0)
    bool FUN_006be350();
};
struct PFIndexModifiable_s006b_de30 {
    void* vtbl;                  // 0x00
    ICoreAllocator_s006b_de30* mpAllocator; // 0x04
    char   pad08[0x24];          // 0x08 (FixedPoolAllocator)
    uint32* mapBucketArray;      // 0x2c
    uint32  mapBucketCount;      // 0x30
    char   pad34[0x18];          // 0x34

    void   SetIsSaved();         // 0x6bed90
    uint64 GetDataEnd();         // 0x6bea90
    uint64 GetTotalDiskSize();   // 0x6beb00
    bool   Write();              // 0x6beb60
    bool   CheckFilesInRange(uint32 begin, uint32 end);    // 0x6bede0
    bool   CheckFilesInSizeRange(uint32 begin, uint32 size);// 0x6beeb0

    // Slice s006bede0
    void* GetFileInfo(const Key_s006b_de30* key);  // 0x008db810 (PFIndexModifiable::GetFileInfo)
    bool  RemoveFile(const Key_s006b_de30* key, void* out);  // 0x008db850 (PFIndexModifiable::RemoveFile)
    void* PutFileInfo(const Key_s006b_de30* key, const void* info);  // 0x008dbeb0 (PFIndexModifiable::PutFileInfo)
    void* GetFiles(void* dst, void* filter);  // 0x008dbcf0 (PFIndexModifiable::GetFiles)
    void* GetAllFiles(void* dst);  // 0x008dbdb0 (PFIndexModifiable::GetAllFiles)
    bool  Read(void* data, uint32 size, uint32 count, int flag);  // 0x008db9b0 (PFIndexModifiable::Read)
    void* PFIndexModifiable_(void* allocator);
};
struct PFRecordInfo_s006b_de30 {
    uint32 mField0;       // 0x00
    uint32 mField4;       // 0x04
    uint32 mOffset;       // 0x08
    uint32 mSize;         // 0x0c
    uint16 mCompression;  // 0x10
};
struct PFRecordInfoOut {
    uint32 mUnknown;      // 0x00
    uint32 mOffset;       // 0x04
    uint32 mSize;         // 0x08
    uint32 mCompression;  // 0x0c
};
struct OpenRecordPair {
    uint32 mType;     // 0x00
    uint32 mGroup;    // 0x04
    uint32 mInstance; // 0x08
    void*  mpRecord;  // 0x0c
};
struct OpenRecordTree : RBTreeHead {
    void insert(void* access, OpenRecordPair* pair);  // 0x008da3a0
};
struct IndexReadBuffer {
    void* mpPad;   // 0x00
    void* mpData;  // 0x04
    void Read(uint32 size, char* outFlag);  // 0x00686430
};
inline uint32& IndexReadOffset(DatabasePackedFile_s006b_de30* p) { return p->field_510[8]; }  // 0x530
inline uint32& IndexReadSize(DatabasePackedFile_s006b_de30* p)   { return p->field_510[9]; }  // 0x534
inline uint32& IndexImageSize(DatabasePackedFile_s006b_de30* p)  { return p->field_510[10]; } // 0x538
inline uint32& IndexBufferSize(DatabasePackedFile_s006b_de30* p) { return p->field_510[11]; } // 0x53c
struct DBPWriteHelper {
    bool WriteRecord(DatabasePackedFile_s006b_de30* self, uint32 type, uint32 group,
                     uint32 instance, uint16 flags);
};
// ---- items of slice s006bde30 end

// @ 0x006bc2d0
bool DatabasePackedFile::FUN_006bc2d0(uint64* out, uint32 a, uint32 b)
{
    bool result = false;
    if (mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) {
        *out = mHoleTable0.FUN_006bfc50(a, b);
        result = true;
    }
    return result;
}

// @ 0x006bc310
bool DatabasePackedFile::FUN_006bc310(uint32 p2, uint32 p3, uint32 p4, uint32 p5, char p6)
{
    if ((p2 | p3) != 0 && (p4 | p5) != 0) {
        bool usePrimary = (field_544 & 0x10) == 0 || p6 != 0;
        if (usePrimary)
            mHoleTable0.FUN_006bfda0(p2, p3, p4, p5);
        else
            mHoleTable1.FUN_006bfda0(p2, p3, p4, p5);
        field_5a0 = true;
    }
    return true;
}

// @ 0x006bc370
bool DatabasePackedFile::FUN_006bc370(uint64* out)
{
    if (mpIndex != 0) {
        *out = ((int64_t(__thiscall*)(void*))(*(void***)mpIndex)[0x14 / 4])(mpIndex);
        return true;
    }
    return false;
}

// @ 0x006bc3a0
bool DatabasePackedFile::FUN_006bc3a0(uint32 flags, float ratio)
{
    field_544 = flags;
    if (ratio >= 0.0f)
        field_548 = ratio;
    return true;
}

// @ 0x006bc3e0
int DatabasePackedFile::FUN_006bc3e0(uint32 a, int n)
{
    if (field_4e8 != 0 && (uint32)(n - 0x32) <= 0xf423ce)
        return 1;
    return 0;
}

// @ 0x006bc420
char DatabasePackedFile::FUN_006bc420(char p2, void* p3, char p4)
{
    char result = 0;
    if (p2 != 0) {
        void* cur = field_5a4;
        if (cur != 0 && p3 != cur) {
            ((void(__thiscall*)(void*, int, void*, char))(*(void***)this)[0x44 / 4])
                (this, 0, cur, p4);
        }
        if (p3 != 0) {
            if (p4 != 0) {
                field_5a4 = p3;
                result = 1;
            } else {
                result = ((bool(__thiscall*)(void*, int, void*, int))(*(void***)p3)[0x50 / 4])
                    (p3, 1, this, 0);
            }
        }
    } else {
        if (p3 != 0 && p3 != field_5a4)
            return false;
        if (p4 != 0) {
            field_5a4 = 0;
            result = 1;
        } else {
            void* cur = field_5a4;
            result = ((bool(__thiscall*)(void*, int, void*, int))(*(void***)cur)[0x50 / 4])
                (cur, 0, this, 0);
        }
    }
    return result;
}

// @ 0x006bc4d0
bool DatabasePackedFile::FUN_006bc4d0(uint32 desiredAccess, int createDisposition, bool bAutoOpen)
{
    char bl = 0;
    if (bAutoOpen != 0) {
        mnAutoOpenAccessFlags = desiredAccess;
        return true;
    }
    if (!mbInitialized || mnAccessFlags != 0)
        goto fail;
    mnAccessFlags = ((desiredAccess & 2) != 0) ? 3 : 1;
    if ((desiredAccess & 2) != 0) {
        if (createDisposition == 6) createDisposition = 4;
    } else {
        if (createDisposition == 6) createDisposition = 3;
    }
    mFile.SetPath(*(const wchar_t**)&mFilePath[0]);
    if (!mFile.FUN_00929470(mnAccessFlags, createDisposition, 1, 2))
        goto fail;
    {
        uint64 pos = mFile.FUN_00928fc0();
        if (((uint32)pos | (uint32)(pos >> 32)) == 0) {
            if ((mnAccessFlags & 2) == 0) { bl = 0; goto close; }
            bl = ((bool(__thiscall*)(void*))(*(void***)this)[0x64 / 4])(this);
            if (!bl) goto close;
        }
    }
    bl = ((bool(__thiscall*)(void*))(*(void***)this)[0x5c / 4])(this);
    if (bl) goto done;
    ((void(__thiscall*)(void*))(*(void***)mpIndex)[0x10 / 4])(mpIndex);
    if (mbEnableWriteOnCorruptFiles != 0 && (mnAccessFlags & 2) != 0) {
        bl = ((bool(__thiscall*)(void*))(*(void***)this)[0x64 / 4])(this);
        if (!bl) goto close;
        ((void(__thiscall*)(void*))(*(void***)this)[0x88 / 4])(this);
        field_4dc = true;
    }
    if (bl) goto done;
close:
    mFile.FUN_00929290();
    if (bl) goto done;
fail:
    mnAccessFlags = 0;
done:
    return bl;
}

// @ 0x006bc5f0
bool DatabasePackedFile::DeleteRecord()
{
    bool result = true;
    EA::Thread::AutoLock lock1(mIndexMutex, &g_mutexParam);
    EA::Thread::AutoLock lock2(mReadWriteMutex, &g_mutexParam);
    if ((mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) &&
        (field_4dc || field_5a0 || field_540)) {
        result = ((bool(__thiscall*)(void*))(*(void***)this)[0x74 / 4])(this);
        if (result) {
            result = ((bool(__thiscall*)(void*))(*(void***)this)[0x68 / 4])(this);
            if (result) {
                result = mFile.FUN_009290c0();
                if (result) {
                    mHoleTable0.FUN_006bff10(&mHoleTable1);
                    ((void(__thiscall*)(void*))(*(void***)mpIndex)[0x3c / 4])(mpIndex);
                }
            }
        }
    }
    return result;
}

// @ 0x006bc6f0
void* DatabasePackedFile::FUN_006bc6f0(uint32 a, uint32 b)
{
    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    void* result;
    if (mnAccessFlags != 0 || FUN_006bc0a0())
        result = ((void*(__thiscall*)(void*, uint32, uint32))(*(void***)mpIndex)[0x1c / 4])
            (mpIndex, a, b);
    else
        result = 0;
    return result;
}

// @ 0x006bc7a0
bool DatabasePackedFile::FUN_006bc7a0()
{
    if (!mFile.FUN_00929900(0, 0, 0))
        return false;
    char buf[0x78];
    operator_new_array(buf, 0, 0x78);
    if (mFile.FUN_00929100(buf, 0x78) == 0)
        return false;
    *(uint32*)&field_510[0]  = *(uint32*)(buf + 0x08);
    *(uint32*)&field_510[1]  = *(uint32*)(buf + 0x0c);
    *(uint32*)&field_510[2]  = *(uint32*)(buf + 0x14);
    field_510[3] = 0;
    *(uint32*)&field_510[4]  = *(uint32*)(buf + 0x18);
    field_510[5] = 0;
    *(uint32*)&field_510[6]  = *(uint32*)(buf + 0x1c);
    *(uint32*)&field_510[8]  = *(uint32*)(buf + 0x34);
    *(uint32*)&field_510[9]  = *(uint32*)(buf + 0x38);
    *(uint32*)&field_510[10] = *(uint32*)(buf + 0x20);
    *(uint32*)&field_510[11] = *(uint32*)(buf + 0x24);
    return ((bool(__thiscall*)(void*, void*))(*(void***)this)[0x6c / 4])(this, buf);
}

// @ 0x006bc870
bool DatabasePackedFile::FUN_006bc870(const char* h)
{
    int64_t fileSize = mFile.FUN_00928fc0();
    bool valid = false;
    if (*(const uint32*)h == 0x46424244 && *(const uint32*)(h + 4) <= 2 &&
        *(const uint32*)(h + 0x24) < 0x7ffffff) {
        uint64 indexOffset = *(const uint64*)(h + 0x38);
        uint64 end = (uint64)*(const uint32*)(h + 0x28) + indexOffset;
        if (indexOffset < (uint64)fileSize && end <= (uint64)fileSize &&
            *(const uint32*)(h + 0x34) != 0)
            valid = true;
    }
    return valid;
}

// @ 0x006bc8e0
void DatabasePackedFile::FUN_006bc8e0()
{
    operator_new_array(&field_510[0], 0, 0x30);
    field_510[0] = field_4e0;
    field_510[1] = field_4e4;
    for (int i = 2; i < 12; ++i) field_510[i] = 0;
    field_540 = true;
    if (((bool(__thiscall*)(void*))(*(void***)this)[0x68 / 4])(this)) {
        mFile.FUN_009297a0(0x78, 0);
    }
}

// @ 0x006bc970
bool DatabasePackedFile::FUN_006bc970()
{
    if ((mnAccessFlags & 2) == 0)
        return false;
    if (mFile.FUN_00928f70() == -2)
        return false;
    if (!field_540)
        return true;
    if (!mFile.FUN_00929900(0, 0, 0))
        return false;
    PFHeader h;
    operator_new_array(&h, 0, 0x78);
    h.magic = 0x46424244;
    h.major = 2;
    h.minor = 0;
    h.userMajor = field_4e0;
    h.userMinor = field_4e4;
    h.flags = 0;
    h.created = 0;
    h.modified = 0;
    h.indexCount = field_510[10];
    h.indexMajor = 3;
    h.indexSize = field_510[7];
    h.indexOffset = field_510[6];
    h.holeCount = field_510[8];
    h.holeOffset = field_510[9];
    h.holeSize = field_510[11];
    h.indexMinor = 0;
    h.indexOffset2 = 0;
    if (!mFile.FUN_00929a70(&h, 0x78))
        return false;
    field_540 = false;
    return true;
}

// @ 0x006bca70
void DatabasePackedFile::FUN_006bca70()
{
    uint64 pos = mFile.FUN_00928fc0();
    uint32 lo = (uint32)pos;
    uint32 hi = (uint32)(pos >> 32);
    ((void(__thiscall*)(void*, int, int, uint32, uint32))(*(void***)mpIndex)[0x40 / 4])
        (mpIndex, 0, 0, lo, hi);
}

// @ 0x006bca90
bool DatabasePackedFile::ReadFileSpan(uint32 a, uint32 b, uint32 c, uint32 d)
{
    EA::Thread::AutoLock lock(mReadWriteMutex, &g_mutexParam);
    if (mnAccessFlags == 0)
        return false;
    if (!mFile.FUN_00929900(b, c, 0))
        return false;
    return mFile.FUN_00929100((const void*)a, d) != -1;
}

// @ 0x006bcb50
bool DatabasePackedFile::FUN_006bcb50(uint32 a, uint32 b, uint32 c, uint32 d)
{
    EA::Thread::AutoLock lock(mReadWriteMutex, &g_mutexParam);
    if (mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) {
        if (mFile.FUN_00929900(b, c, 0))
            return mFile.FUN_00929a70((const void*)a, d);
    }
    return false;
}

// @ 0x006bcc10
bool DatabasePackedFile::DecompressData(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e)
{
    CompressionRefpack_s006b_c1b0 refpack;
    refpack.field_c = 0;
    if (!refpack.IsValidHeader((const void*)b, c))
        return false;
    int n = refpack.Decompress((const void*)b, c, 0, 0, 1);
    if (n == (int)d) {
        if (c != 0 && n != 0) {
            if (refpack.Decompress((const void*)b, c, (void*)e, d, 1) == 0)
                return false;
        }
        return true;
    }
    return false;
}

struct DbpfAllocator {
    virtual void v00(); virtual void v01();
    virtual void* Alloc(uint32 size, const char* name, int flags);   // +0x08
    virtual void Free(void* p, int size);                            // +0x0c
};

// @ 0x006bccb0
bool DatabasePackedFile::DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e, uint32 f)
{
    bool result = false;
    if ((b | c) != 0) {
        void* buf = ((DbpfAllocator*)mpAllocator)->Alloc(d, "Resource/Raw", 0);
        if (buf != 0) {
            if (ReadFileSpan((uint32)buf, b, c, d)) {
                result = DecompressData(a, (uint32)buf, d, e, f);
            }
            ((DbpfAllocator*)mpAllocator)->Free(buf, 0);
        }
    }
    return result;
}

// @ 0x006bcd30
bool DatabasePackedFile::FUN_006bcd30()
{
    bool result = false;
    if (mnAccessFlags != 0) {
        while (mapCount != 0) {
            ((void(__thiscall*)(void*, void*))(*(void***)this)[0x3c / 4])
                (this, *(void**)((char*)mapRoot + 0x1c));
        }
        result = true;
    }
    return result;
}

// @ 0x006bcd70
bool DatabasePackedFile::FUN_006bcd70(uint32 key)
{
    EA::Thread::AutoLock lock(mIndexMutex, &g_mutexParam);
    bool result = false;
    if ((mnAccessFlags & 2) != 0) {
        if (mnAccessFlags == 0) {
            if (!FUN_006bc0a0())
                return false;
        }
        if (((void*(__thiscall*)(void*, uint32))(*(void***)mpIndex)[0x28 / 4])(mpIndex, key) != 0) {
            void* out = 0;
            void** it = ((RBTreeHead*)((char*)this + 0x4f0))->find(&out, &key);
            if (*it == (char*)this + 0x4f4) {
                ((void(__thiscall*)(void*))(*(void***)this)[0x84 / 4])(this);
                RecordInfo ri;
                ri.f0 = 0; ri.f4 = 0; ri.f8 = 0; ri.fc = 0; ri.f10 = 0; ri.f12 = 0;
                if (((bool(__thiscall*)(void*, uint32, RecordInfo*))(*(void***)mpIndex)[0x30 / 4])
                        (mpIndex, key, &ri)) {
                    FUN_006bc310(ri.f0, ri.f4, ri.f8, 0, ri.f12 == 0);
                    field_4dc = true;
                    result = true;
                }
            }
        }
    }
    return result;
}

// @ 0x006bcea0
bool DatabasePackedFile::FUN_006bcea0()
{
    if (mnAccessFlags == 0 || (mnAccessFlags & 2) == 0 || !field_4dc)
        return true;
    uint32 n = ((uint32(__thiscall*)(void*))(*(void***)mpIndex)[0xc / 4])(mpIndex);
    void* pData = 0;
    uint32 nSize = 0;
    if (!((bool(__thiscall*)(void*, void**, uint32*, uint32))(*(void***)mpIndex)[0x38 / 4])
            (mpIndex, &pData, &nSize, n))
        return true;
    uint32 old3c = field_510[11];
    field_540 = true;
    bool result;
    if (n == 0) {
        result = FUN_006bc310(field_510[8], field_510[9], old3c, 0, 0);
        field_510[11] = 0; field_510[9] = 0; field_510[8] = 0; field_510[10] = 0;
        if (result) field_4dc = false;
        return result;
    }
    field_510[10] = n;
    field_510[11] = old3c;
    if (old3c != n || (field_544 & 0x10) != 0) {
        result = FUN_006bc310(field_510[8], field_510[9], old3c, 0, 0);
        if (result) {
            field_510[8] = 0; field_510[9] = 0;
            result = FUN_006bc2d0((uint64*)&field_510[8], field_510[11], 0);
            field_510[8] = 0; field_510[9] = 0;
            if (!result) {
                field_510[10] = 0; field_510[8] = 0; field_510[9] = 0; field_510[11] = 0;
                return result;
            }
        }
    }
    result = FUN_006bcb50(field_510[8], field_510[9], field_510[10], old3c);
    if (!result) {
        if (field_510[8] != 0 || field_510[9] != 0) {
            FUN_006bc310(field_510[8], field_510[9], field_510[11], 0, 0);
            field_510[11] = 0; field_510[9] = 0; field_510[8] = 0; field_510[10] = 0;
            return false;
        }
        if (field_540) return false;
        field_4dc = false;
        return false;
    }
    field_4dc = false;
    return result;
}

// @ 0x006bd070
void DatabasePackedFile::FUN_006bd070()
{
    int64_t pos = mFile.FUN_00928fc0();
    uint32 lo = (uint32)pos;
    uint32 hi = (uint32)(pos >> 32);
    mHoleTable0.FUN_006bef70(lo, hi);
    mHoleTable1.FUN_006bef70(lo, hi);
    if ((field_544 & 2) != 0) {
        mHoleTable0.FUN_006bef70(0, 0);
        mHoleTable0.FUN_006bff90(0, 0, 0x78, 0);
        if ((field_544 & 8) != 0) {
            FUN_006bcb50((uint32)"BUSY", 0, 0, 4);
            field_540 = true;
            field_4dc = true;
            return;
        }
        if (mHoleTable0.FUN_006bff90(field_510[8], field_510[9], field_510[11], 0) &&
            ((bool(__thiscall*)(void*, void*, int, int, uint32))(*(void***)mpIndex)[0x24 / 4])
                (mpIndex, &mHoleTable0, 0x78, 0, lo))
            return;
        mHoleTable0.FUN_006bef70(lo, hi);
        mHoleTable1.FUN_006bef70(lo, hi);
        field_544 &= ~2;
    }
}

// @ 0x006bd150
bool DatabasePackedFile_s006b_d150::FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags)
{
    bool bWasNull = (*ppMem == 0);
    CompressionRefpack_s006b_d150 refpack;
    if (n - 1 < 39999999) {
        *pFlags = 0xffff;
        uint32 r = refpack.FUN_0092c9f0(src, n, 0, 0, 1);
        if (bWasNull && r != 0) {
            *pSize = r;
            *ppMem = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
                (mpAllocator, r, "Resource/PackedRecord", 0);
        }
        if (*ppMem != 0) {
            uint32 r2 = refpack.FUN_0092c9f0(src, n, *ppMem, *pSize, (n > 250000) + 1);
            *pSize = r2;
            if (r2 != 0xffffffff)
                return true;
            *pSize = 0;
            if (bWasNull && *ppMem != 0) {
                ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])
                    (mpAllocator, *ppMem, 0);
                *ppMem = 0;
            }
        }
        return false;
    }
    if (bWasNull) {
        *pSize = n;
        void* mem = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
            (mpAllocator, n, "Resource/PackedRecord", 0);
        *ppMem = mem;
        sub_11E0744(mem, src, n);
        return true;
    }
    if (*pSize < n) {
        *pSize = 0;
        return false;
    }
    *pSize = n;
    sub_11E0744(*ppMem, src, n);
    return true;
}

// @ 0x006bd300
void DatabasePackedFile_s006b_d150::FUN_006bd300()
{
    DBPFHead* head = reinterpret_cast<DBPFHead*>(this);
    head->mpVtbl0 = vtbl_DBPF_140a138;
    head->mpVtbl4 = vtbl_DBPF_140a124;

    if (mbInitialized) {
        if (mnAccessFlags != 0)
            ((char(__thiscall*)(void*, int))(*(void***)this)[0x1c / 4])(this, 1);
        ((void(__thiscall*)(void*, PFIndexModifiable_s006b_d150*))(*(void***)this)[0x80 / 4])(this, mpIndex);
        mpIndex = 0;
        mbInitialized = false;
    }

    reinterpret_cast<HoleTableX*>(&mHoleTable1)->Destroy();
    reinterpret_cast<HoleTableX*>(&mHoleTable0)->Destroy();

    RecMap* map = reinterpret_cast<RecMap*>(&field_4f0[0]);
    map->DoFreeNodes(map->mParent);

    reinterpret_cast<MutexX*>(&mReadWriteMutex)->Destroy();
    reinterpret_cast<MutexX*>(&mIndexMutex)->Destroy();
    reinterpret_cast<FileStreamX*>(&mFile)->Destroy();

    // The string16 teardown measures the allocated span (capacity - begin) and
    // frees the buffer unless it is the two-byte empty-string sentinel.
    WString16* str = reinterpret_cast<WString16*>(mFilePath);
    int nBytes = (int)((char*)str->mpCapacity - (char*)str->mpBegin);
    nBytes &= ~1;
    if (nBytes > 2 && str->mpBegin != 0)
        EAFree(str->mpBegin);

    head->mpVtbl4 = vtbl_DBPF_13eb938;
    head->mpVtbl0 = vtbl_DBPF_13effb8;
}

// @ 0x006bd430
char DatabasePackedFile_s006b_d150::FUN_006bd430(char p2)
{
    char bl;
    if (mnAccessFlags == 0) {
        bl = 1;
        goto done;
    }
    if ((mnAccessFlags & 2) == 0) {
        bl = 1;
    } else {
        bl = (char)FUN_006bcd30();
        if (p2 != 0 && bl != 0) {
            ((void(__thiscall*)(void*))(*(void***)this)[0x24 / 4])(this);
            mFile.FUN_00929290();
            mnAccessFlags = 0;
            goto done;
        }
    }
    mFile.FUN_00929290();
    mnAccessFlags = 0;
done:
    ((void(__thiscall*)(void*, void*))(*(void***)this)[0x80 / 4])(this, mpIndex);
    mpIndex = 0;
    mHoleTable0.FUN_006bef70(0, 0);
    mHoleTable1.FUN_006bef70(0, 0);
    return bl;
}

// @ 0x006bd4d0
int DatabasePackedFile_s006b_d150::FUN_006bd4d0(Key_s006b_d150* key)
{
    EA::Thread::AutoLock_s006b_d150 lock(mIndexMutex, &g_mutexParam);
    int count = 0;
    if (mnAccessFlags != 0) {
        void* out;
        void** it = ((RBTreeHead*)((char*)this + 0x4f0))->find(&out, key);
        char* end = (char*)this + 0x4f4;
        for (char* n = *(char**)it;
             n != end && *(uint32*)(n + 0x10) == key->type &&
             *(uint32*)(n + 0x14) == key->group && *(uint32*)(n + 0x18) == key->instance;
             n = (char*)RBTreeIncrement(n)) {
            count++;
        }
    }
    return count;
}

// @ 0x006bd580
bool DatabasePackedFile_s006b_d150::FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6)
{
    *p4 = 0;
    *p5 = 0;
    if (!FUN_006bd150((void*)p2, (uint32)p3, p4, p5, (uint16*)p6))
        return false;
    float a = (float)*p5;
    float b = (float)(uint32)p3;
    if (a / b < field_4ec)
        return true;
    if (*p4 != 0)
        ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])(mpAllocator, *p4, 0);
    *p4 = 0;
    *p5 = 0;
    return false;
}

// @ 0x006bd650
bool DatabasePackedFile_s006b_d150::SetLocation(const wchar_t* p)
{
    if (mnAccessFlags == 0) {
        const wchar_t* end = p;
        while (*end)
            ++end;
        ((WStringAssign*)((char*)this + 0x20))->assign(p, p + (end - p));
        return true;
    }
    return false;
}

// @ 0x006bd690
bool DatabasePackedFile_s006b_d150::FUN_006bd690(void* p2)
{
    Record_s006b_d150* rec = static_cast<Record_s006b_d150*>(p2);
    Key_s006b_d150 key = *rec->GetKey();

    RecMap* map = reinterpret_cast<RecMap*>(&field_4f0[0]);
    RecNode* end = map->Anchor();

    {
        EA::Thread::AutoLock_s006b_d150 lock(mIndexMutex, &g_mutexParam);
        if (mnAccessFlags == 0)
            return false;

        RecNode* found;
        RecNode* it = static_cast<RecNode*>(*map->Find(&found, &key));
        for (;;) {
            if (it == end)
                return false;
            if (it->mKey.type != key.type)
                return false;
            if (it->mKey.group != key.group)
                return false;
            if (it->mKey.instance != key.instance)
                return false;
            if (it->mpValue == rec)
                break;
            it = static_cast<RecNode*>(RBTreeIncrement(it));
        }

        if (rec->mnMagic != 0x6492fe5) {
            rec->Detach();
            rec->Release();
            --map->mnSize;
            RBTreeIncrement(it);
            RBTreeErase(it, map->Anchor());
            FreeBlock(map->mpAlloc, it, 0x20);
            return true;
        }

        if ((mnAccessFlags & 2) == 0)
            return false;

        ((void(__thiscall*)(void*))(*(void***)this)[0x84 / 4])(this);

        if (rec->GetStream()->GetSize() == 0) {
            PFIndexVtbl* idx = reinterpret_cast<PFIndexVtbl*>(mpIndex);

            IdxEntry old;
            old.posLo = 0;
            old.posHi = 0;
            old.size = 0;
            old.usize = 0;
            old.flags = 0;
            old.compressed = 0;
            if (idx->GetEntry(&key, &old))
                FUN_006bc310(old.posLo, old.posHi, old.size, 0, old.compressed == 0);

            IdxEntry empty;
            empty.posLo = 0;
            empty.posHi = 0;
            empty.size = 0;
            empty.usize = 0;
            empty.flags = 0;
            empty.compressed = 0;
            idx->SetEntry(&key, &empty);
            field_4dc = true;

            rec->Detach();
            rec->Release();
            --map->mnSize;
            RBTreeIncrement(it);
            RBTreeErase(it, map->Anchor());
            FreeBlock(map->mpAlloc, it, 0x20);
            return true;
        }
    }

    IStreamX* stream = &rec->mStream;
    int size = stream->GetSize();
    void* pCompressed = 0;
    uint32 cSize = 0;
    uint32 cFlags = 0;
    if (field_4e8 && (uint32)(size - 0x32) <= 0xf423ce) {
        char* buf = (char*)AllocBlock(mpAllocator, (uint32)(size + 0x10), "Resource/RecordData", 0);
        buf[size + 1] = 0;
        buf[size] = 0;
        if (stream->SetPosition(0, 0) && size == stream->Read(buf, size)) {
            if (!FUN_006bd580((uint32)buf, size, &pCompressed, &cSize, (uint32)&cFlags)) {
                pCompressed = 0;
                cFlags = 0;
            }
        }
        FreeBlock(mpAllocator, buf, 0);
    }

    int64_t diskPos = 0;
    uint32 storedSize = (pCompressed != 0) ? cSize : (uint32)size;
    bool bAlloc = false;
    {
        EA::Thread::AutoLock_s006b_d150 lock(mIndexMutex, &g_mutexParam);
        if (mnAccessFlags != 0 && (mnAccessFlags & 2) != 0) {
            diskPos = mHoleTable0.FUN_006bfc50(storedSize, 0);
            bAlloc = true;
        }
    }

    IdxEntry newEntry;
    newEntry.posLo = (uint32)diskPos;
    newEntry.posHi = (uint32)(diskPos >> 32);
    newEntry.size = storedSize;
    newEntry.usize = (uint32)size;
    newEntry.flags = (uint16)cFlags;
    newEntry.compressed = 0;

    bool result = false;
    if (bAlloc) {
        if (pCompressed != 0)
            result = FUN_006bcb50((uint32)pCompressed, newEntry.posLo, newEntry.posHi, cSize);
        else
            result = rec->DoRead(newEntry.posLo, newEntry.posHi, (uint32)size);
    }
    if (pCompressed != 0)
        FreeBlock(mpAllocator, pCompressed, 0);

    bool bAdded = false;
    {
        EA::Thread::AutoLock_s006b_d150 lock(mIndexMutex, &g_mutexParam);
        if (result) {
            PFIndexVtbl* idx = reinterpret_cast<PFIndexVtbl*>(mpIndex);

            IdxEntry old;
            old.posLo = 0;
            old.posHi = 0;
            old.size = 0;
            old.usize = 0;
            old.flags = 0;
            old.compressed = 0;
            if (idx->GetEntry(&key, &old))
                FUN_006bc310(old.posLo, old.posHi, old.size, 0, old.compressed == 0);

            idx->SetEntry(&key, &newEntry);
            field_4dc = true;
            bAdded = true;
        } else if (bAlloc) {
            if (diskPos != 0) {
                if (storedSize != 0) {
                    mHoleTable0.FUN_006bfda0((uint32)diskPos, (uint32)(diskPos >> 32), storedSize, 0);
                    field_5a0 = true;
                }
            }
        }

        RecNode* found2;
        RecNode* it2 = static_cast<RecNode*>(*map->Find(&found2, &key));
        for (;;) {
            if (it2 == end)
                break;
            if (it2->mKey.type != key.type)
                break;
            if (it2->mKey.group != key.group)
                break;
            if (it2->mKey.instance != key.instance)
                break;
            if (it2->mpValue == rec) {
                --map->mnSize;
                RBTreeIncrement(it2);
                RBTreeErase(it2, map->Anchor());
                FreeBlock(map->mpAlloc, it2, 0x20);
                rec->Detach();
                rec->Release();
                break;
            }
            it2 = static_cast<RecNode*>(RBTreeIncrement(it2));
        }
    }

    return bAdded;
}

// @ 0x006bdc50
void* DatabasePackedFile_s006b_d150::FUN_006bdc50(const wchar_t* p2, int p3)
{
    DBPFHead* head = reinterpret_cast<DBPFHead*>(this);
    head->mpVtbl4 = vtbl_DBPF_13f1ab0;
    head->mpVtbl0 = vtbl_DBPF_1408500;
    head->mpVtbl4 = vtbl_DBPF_14084f0;
    _InterlockedExchange(&head->mnRefCount, 0);
    head->mpVtbl0 = vtbl_DBPF_140a138;
    head->mpVtbl4 = vtbl_DBPF_140a124;

    mbInitialized = false;
    if (p3 == 0)
        mpAllocator = GetDefaultAllocator();
    else
        mpAllocator = reinterpret_cast<ICoreAllocator_s006b_d150*>(p3);
    mnAccessFlags = 0;
    mnAutoOpenAccessFlags = 0;
    mbEnableReadOnCorruptFiles = false;
    mbEnableWriteOnCorruptFiles = true;

    WString16* str = reinterpret_cast<WString16*>(mFilePath);
    str->mpBegin = gEmptyString16;
    str->mpEnd = gEmptyString16;
    str->mpCapacity = gEmptyString16End;

    reinterpret_cast<FileStreamX*>(&mFile)->Construct(0);
    reinterpret_cast<MutexX*>(&mIndexMutex)->Construct(0, true);
    reinterpret_cast<MutexX*>(&mReadWriteMutex)->Construct(0, true);

    mpIndex = 0;
    field_4dc = false;
    field_4e0 = 0;
    field_4e4 = 0;
    field_4e8 = true;
    field_4ec = kRatio095;

    RecMap* map = reinterpret_cast<RecMap*>(&field_4f0[0]);
    map->mLeft = 0;
    map->mParent = 0;
    map->mColor = 0;
    map->mpAlloc = mpAllocator;
    map->mnFlags = 0;
    map->mRight = map->Anchor();
    map->mLeft = map->Anchor();
    map->mParent = 0;
    map->mColor = 0;
    map->mnSize = 0;

    sub_11E073E(&field_510[0], 0, 0x30);

    field_540 = false;
    field_544 = 0x12;
    field_548 = kRatio015;

    mHoleTable0.FUN_006bf5a0();
    mHoleTable1.FUN_006bf5a0();

    field_5a0 = false;
    pad05a1[0] = 0;   // +0x5a1
    field_5a4 = 0;

    reinterpret_cast<FileStreamX*>(&mFile)->AddRef();

    if (p2 != 0 && mnAccessFlags == 0) {
        const wchar_t* end = p2;
        while (*end)
            ++end;
        reinterpret_cast<WStringAssign*>(mFilePath)->assign(p2, end);
    }

    return this;
}

// @ 0x006bde30
bool DatabasePackedFile_s006b_de30::OpenRecord(void* keyPtr, void** ppRecord, uint32 desiredAccess, int createDisposition, char flag, void* pInfo)
{
    Key_s006b_de30* key = (Key_s006b_de30*)keyPtr;
    void* record = 0;
    if ((desiredAccess & 3) == 0)
        return false;

    EA::Thread::AutoLock_s006b_de30 lock(mIndexMutex, &g_mutexParam);
    if (mnAccessFlags == 0) {
        if (!FUN_006bc0a0())
            return false;
    }

    PFRecordInfo_s006b_de30* rec = 0;
    if (mpIndex != 0) {
        rec = (PFRecordInfo_s006b_de30*)((void*(__thiscall*)(void*, Key_s006b_de30*))
            (*(void***)mpIndex)[0x28 / 4])(mpIndex, key);
    }
    if (rec != 0 && pInfo != 0) {
        PFRecordInfoOut* out = (PFRecordInfoOut*)pInfo;
        out->mUnknown = 0xffffffff;
        out->mOffset = rec->mOffset;
        out->mSize = rec->mSize;
        out->mCompression = rec->mCompression;
    }
    if (ppRecord == 0)
        return rec != 0;

    int disposition = createDisposition;
    if (disposition == 6)
        disposition = ((desiredAccess & 2) != 0) + 3;

    bool reject;
    if (rec != 0)
        reject = (disposition == 1);
    else {
        if (disposition == 3)
            return false;
        reject = (disposition == 5);
    }
    if (reject || (mnAccessFlags & desiredAccess) != desiredAccess)
        return false;

    bool create = false;
    if (disposition == 2 || disposition == 5)
        create = true;

    OpenRecordTree* tree = (OpenRecordTree*)((char*)this + 0x4f0);
    char* end = (char*)this + 0x4f4;

    if (rec != 0) {
        if (((desiredAccess & 2) == 0 || !create) &&
            rec->mCompression != 0 && (flag & 1) == 0)
            return false;

        if ((desiredAccess & 2) == 0) {
            void* found = 0;
            void** it = tree->find(&found, key);
            if (*(void**)*it == end) {
                record = ((void*(__thiscall*)(void*, uint32, PFRecordInfo_s006b_de30*, Key_s006b_de30*))
                    (*(void***)vtbl)[0x4c / 4])(this, desiredAccess, rec, key);
            } else {
                void* node = *(void**)*it;
                void* openInfo = *(void**)((char*)node + 0x1c);
                if (*(uint32*)((char*)openInfo + 8) != 0x6492fe4)
                    return false;
                record = ((void*(__thiscall*)(void*, uint32, void*, Key_s006b_de30*))
                    (*(void***)vtbl)[0x50 / 4])(this, desiredAccess, openInfo, key);
            }
        } else {
            void* found = 0;
            void** it = tree->find(&found, key);
            if (*(void**)*it != end)
                return false;

            if (!create) {
                if (rec->mCompression == 0) {
                    record = ((void*(__thiscall*)(void*, uint32, uint32, uint32,
                                                  Key_s006b_de30*))(*(void***)vtbl)[0x58 / 4])
                        (this, desiredAccess, rec->mField0, rec->mField4, key);
                } else {
                    void* buffer = ((void*(__thiscall*)(void*, uint32, const char*, int))
                        (*(void***)mpAllocator)[8 / 4])
                        (mpAllocator, rec->mSize, "Resource/Raw", 0);
                    if (buffer != 0) {
                        if (DecompressRecord(rec->mCompression, rec->mField0,
                                             rec->mField4, rec->mOffset,
                                             rec->mSize, (uint32)buffer)) {
                            record = ((void*(__thiscall*)(void*, uint32, void*,
                                                          uint32, Key_s006b_de30*))
                                (*(void***)vtbl)[0x54 / 4])
                                (this, desiredAccess, buffer, rec->mSize, key);
                            if (record != 0) {
                                ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
                                OpenRecordPair pair;
                                pair.mType = key->type;
                                pair.mGroup = key->group;
                                pair.mInstance = key->instance;
                                pair.mpRecord = record;
                                tree->insert(&desiredAccess, &pair);
                                ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
                                *ppRecord = record;
                                return true;
                            }
                        }
                        ((void(__thiscall*)(void*, void*, int))
                            (*(void***)mpAllocator)[0xc / 4])(mpAllocator, buffer, 0);
                    }
                }
            } else {
                record = ((void*(__thiscall*)(void*, uint32, int, int, int, Key_s006b_de30*))
                    (*(void***)vtbl)[0x58 / 4])(this, desiredAccess, 0, 0, 0, key);
                if (record != 0) {
                    ((void(__thiscall*)(void*))(*(void***)vtbl)[0x84 / 4])(this);
                    ((void(__thiscall*)(void*, Key_s006b_de30*))(*(void***)vtbl)[0x40 / 4])(this, key);
                }
            }
        }
    } else {
        record = ((void*(__thiscall*)(void*, uint32, int, int, int, Key_s006b_de30*))
            (*(void***)vtbl)[0x58 / 4])(this, desiredAccess, 0, 0, 0, key);
        if (record != 0)
            ((void(__thiscall*)(void*))(*(void***)vtbl)[0x84 / 4])(this);
    }

    if (record != 0) {
        ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
        OpenRecordPair pair;
        pair.mType = key->type;
        pair.mGroup = key->group;
        pair.mInstance = key->instance;
        pair.mpRecord = record;
        tree->insert(&desiredAccess, &pair);
    }

    if (record != 0)
        ((void(__thiscall*)(void*))(*(void***)record)[1])(record);
    *ppRecord = record;
    return record != 0;
}

// @ 0x006be1d0
bool DatabasePackedFile_s006b_de30::FUN_006be1d0()
{
    if (IndexImageSize(this) == 0) {
        if (mpIndex == 0)
            mpIndex = (PFIndexModifiable_s006b_de30*)((void*(__thiscall*)(void*, int))
                (*(void***)vtbl)[0x7c / 4])(this, 3);
        if (((int(__thiscall*)(void*))(*(void***)mpIndex)[0xc / 4])(mpIndex) == 0) {
            ((void(__thiscall*)(void*))(*(void***)vtbl)[0x88 / 4])(this);
        }
        return true;
    }

    bool result = false;
    if (!mFile.FUN_00929900((int)IndexReadOffset(this), (int)IndexReadSize(this), 0))
        return false;

    IndexReadBuffer buffer;
    char flag = 0;
    buffer.Read(IndexBufferSize(this), &flag);

    if (mFile.FUN_00929100(buffer.mpData, IndexBufferSize(this)) != 0) {
        if (mpIndex == 0)
            mpIndex = (PFIndexModifiable_s006b_de30*)((void*(__thiscall*)(void*, int))
                (*(void***)vtbl)[0x7c / 4])(this, 3);
        if (mpIndex != 0) {
            result = ((bool(__thiscall*)(void*, void*, uint32, uint32, int))
                (*(void***)mpIndex)[0x34 / 4])
                (mpIndex, buffer.mpData, IndexBufferSize(this),
                 IndexImageSize(this), 1);
        }
        bool committed = ((bool(__thiscall*)(void*))(*(void***)vtbl)[0x78 / 4])(this);
        if (!committed && !mbEnableReadOnCorruptFiles)
            result = false;
        else if (result) {
            ((void(__thiscall*)(void*))(*(void***)vtbl)[0x88 / 4])(this);
            field_4dc = false;
            result = true;
        }
    }

    if (buffer.mpData != 0)
        ::operator delete(buffer.mpData);
    return result;
}

// @ 0x006be350
bool DBPWriteHelper::WriteRecord(DatabasePackedFile_s006b_de30* self, uint32 type, uint32 group, uint32 instance, uint16 flags)
{
    Key_s006b_de30 key;
    key.type = type;
    key.group = group;
    key.instance = instance;

    EA::Thread::AutoLock_s006b_de30 lock(self->mIndexMutex, &g_mutexParam);
    if ((self->mnAccessFlags & 2) == 0)
        return false;
    if (self->mnAccessFlags == 0 && !self->FUN_006bc0a0())
        return false;

    OpenRecordTree* tree = (OpenRecordTree*)((char*)self + 0x4f0);
    char* end = (char*)self + 0x4f4;
    void* found = 0;
    void** it = tree->find(&found, &key);
    if (*(void**)*it != end)
        return false;

    void* record = ((void*(__thiscall*)(void*, uint32, int, int, int, Key_s006b_de30*))
        (*(void***)self->vtbl)[0x58 / 4])(self, 2, 0, 0, 0, &key);
    if (record == 0)
        return false;
    ((void(__thiscall*)(void*))(*(void***)record)[1])(record);

    OpenRecordPair pair;
    pair.mType = type;
    pair.mGroup = group;
    pair.mInstance = instance;
    pair.mpRecord = record;
    tree->insert(&flags, &pair);
    ((void(__thiscall*)(void*))(*(void***)self->vtbl)[0x84 / 4])(self);

    bool written = self->FUN_006bcb50(type, group, instance, (uint32)record);

    void* found2 = 0;
    void** it2 = tree->find(&found2, &key);
    if (*(void**)*it2 != end) {
        --self->mapCount;
        ((void(__thiscall*)(void*))(*(void***)record)[2])(record);
        ((void(__thiscall*)(void*, void*, int))
            (*(void***)self->mpAllocator)[0xc / 4])
            (self->mpAllocator, *(void**)*it2, 0x20);
    }
    self->field_4dc = true;
    return written;
}
