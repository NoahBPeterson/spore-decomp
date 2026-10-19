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
    bool FUN_006bc4d0(uint32 p2, int p3, int p4); // 0x6bc4d0
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
    bool DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e); // 0x6bccb0
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
namespace EA {
namespace Thread {
struct Mutex_s006b_d150 {
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
struct FileStream_s006b_d150 {
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
void* __cdecl RBTreeIncrement(void* node);   // 0x921580
struct CompressionRefpack_s006b_d150 {
    virtual void vfunc();
    char   pad[8];
    uint32 field_c;
    bool   IsValidHeader(const void* p, uint32 n);                       // 0x92cad0
    int    Decompress(const void* p, uint32 n, void* d, uint32 dn, int f);// 0x92ca60
    int    FUN_0092c9f0(const void* p, uint32 n, void* d, uint32 dn, int f); // 0x92c9f0
};
void __cdecl sub_11E0744(void* dst, const void* src, uint32 n);   // 0x11e0744
struct WStringAssign {
    char data[0x10];
    void assign(const wchar_t* first, const wchar_t* last);
};
struct DatabasePackedFile_s006b_d150 {
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
    EA::IO::FileStream_s006b_d150 mFile; // 0x030
    uint32  mnFileStartingOffset; // 0x464
    void*   mpCurrentStream;  // 0x468
    void*   mpDataBuffer;     // 0x46c
    uint32  mnBufferSize;     // 0x470
    uint32  mnBufferOffset;   // 0x474
    EA::Thread::Mutex_s006b_d150 mIndexMutex;   // 0x478
    EA::Thread::Mutex_s006b_d150 mReadWriteMutex; // 0x4a8
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
    bool FUN_006bc4d0(uint32 p2, int p3, int p4); // 0x6bc4d0
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
    bool DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e); // 0x6bccb0
    bool FUN_006bcd30();                      // 0x6bcd30
    bool FUN_006bcd70(uint32 key);            // 0x6bcd70
    bool FUN_006bcea0();                      // 0x6bcea0
    void FUN_006bd070();                      // 0x6bd070

    // Slice s006bd150
    bool FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags);  // 0x006bd150 (DatabasePackedFile::FUN_006bd150)
    void FUN_006bd300();  // 0x006bd300 (DatabasePackedFile::FUN_006bd300)
    char FUN_006bd430(char p2);  // 0x006bd430 (DatabasePackedFile::FUN_006bd430)
    int  FUN_006bd4d0(Key* key);  // 0x006bd4d0 (DatabasePackedFile::FUN_006bd4d0)
    bool FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6);  // 0x006bd580 (DatabasePackedFile::FUN_006bd580)
    bool SetLocation(const wchar_t* p);  // 0x006bd650 (DatabasePackedFile::SetLocation)
    bool FUN_006bd690(void* p2);  // 0x006bd690 (DatabasePackedFile::FUN_006bd690)
    void* FUN_006bdc50(const wchar_t* p2, int p3);

    // Slice s006bde30
    bool OpenRecord(void* key, void** ppRecord, uint32 desiredAccess, int createDisposition,
                    char flag, void* pInfo);
    bool FUN_006be1d0();
    bool FUN_006be350();
};
// ---- items of slice s006bd150 end

// ---- items of slice s006bde30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
struct Mutex_s006b_de30 {
    int Lock(const void* p);   // 0x9221b0
    int Unlock();              // 0x922270
    char pad00[0x30];
};
}
}
namespace EA {
namespace IO {
struct FileStream_s006b_de30 {
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
struct DatabasePackedFile_s006b_de30 {
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
    EA::IO::FileStream_s006b_de30 mFile; // 0x030
    uint32  mnFileStartingOffset; // 0x464
    void*   mpCurrentStream;  // 0x468
    void*   mpDataBuffer;     // 0x46c
    uint32  mnBufferSize;     // 0x470
    uint32  mnBufferOffset;   // 0x474
    EA::Thread::Mutex_s006b_de30 mIndexMutex;   // 0x478
    EA::Thread::Mutex_s006b_de30 mReadWriteMutex; // 0x4a8
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
    bool FUN_006bc4d0(uint32 p2, int p3, int p4); // 0x6bc4d0
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
    bool DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 e); // 0x6bccb0
    bool FUN_006bcd30();                      // 0x6bcd30
    bool FUN_006bcd70(uint32 key);            // 0x6bcd70
    bool FUN_006bcea0();                      // 0x6bcea0
    void FUN_006bd070();                      // 0x6bd070

    // Slice s006bd150
    bool FUN_006bd150(void* src, uint32 n, void** ppMem, uint32* pSize, uint16* pFlags);  // 0x006bd150 (DatabasePackedFile::FUN_006bd150)
    void FUN_006bd300();  // 0x006bd300 (DatabasePackedFile::FUN_006bd300)
    char FUN_006bd430(char p2);  // 0x006bd430 (DatabasePackedFile::FUN_006bd430)
    int  FUN_006bd4d0(Key* key);  // 0x006bd4d0 (DatabasePackedFile::FUN_006bd4d0)
    bool FUN_006bd580(uint32 p2, int p3, void** p4, uint32* p5, uint32 p6);  // 0x006bd580 (DatabasePackedFile::FUN_006bd580)
    bool SetLocation(const wchar_t* p);  // 0x006bd650 (DatabasePackedFile::SetLocation)
    bool FUN_006bd690(void* p2);  // 0x006bd690 (DatabasePackedFile::FUN_006bd690)
    void* FUN_006bdc50(const wchar_t* p2, int p3);

    // Slice s006bde30
    bool OpenRecord(void* key, void** ppRecord, uint32 desiredAccess, int createDisposition,
                    char flag, void* pInfo);
    bool FUN_006be1d0();
    bool FUN_006be350();
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
        if ((field_544 & 0x10) != 0 && p6 == 0)
            mHoleTable1.FUN_006bfda0(p2, p3, p4, p5);
        else
            mHoleTable0.FUN_006bfda0(p2, p3, p4, p5);
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
bool DatabasePackedFile::FUN_006bc4d0(uint32 desiredAccess, int createDisposition, int bAutoOpen)
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
    if (!refpack.IsValidHeader((const void*)a, b))
        return false;
    int n = refpack.Decompress((const void*)a, b, 0, 0, 1);
    if (n == (int)c) {
        if (b != 0 && n != 0) {
            if (refpack.Decompress((const void*)a, b, (void*)e, d, 1) == 0)
                return false;
        }
        return true;
    }
    return false;
}

// @ 0x006bccb0
bool DatabasePackedFile::DecompressRecord(uint32 a, uint32 b, uint32 c, uint32 d, uint32 name)
{
    bool result = false;
    if (b != 0 || c != 0) {
        void* buf = ((void*(__thiscall*)(void*, uint32, const char*, int))(*(void***)mpAllocator)[8 / 4])
            (mpAllocator, name, "Resource/Raw", 0);
        if (buf != 0) {
            if (ReadFileSpan((uint32)buf, a, b, c)) {
                result = DecompressData((uint32)buf, name, d, c, b);
            }
            ((void(__thiscall*)(void*, void*, int))(*(void***)mpAllocator)[0xc / 4])(mpAllocator, buf, 0);
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
    *pFlags = 0xffff;
    CompressionRefpack_s006b_d150 refpack;
    if (n - 1 < 39999999) {
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
    // TODO(partial): full destructor (eastl multimap/hole-table/allocator teardown + vtable reset).
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
int DatabasePackedFile_s006b_d150::FUN_006bd4d0(Key* key)
{
    EA::Thread::AutoLock_s006b_d150 lock(mIndexMutex, &g_mutexParam);
    int count = 0;
    if (mnAccessFlags != 0) {
        void* out = 0;
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
    if (!FUN_006bd150((void*)p2, (uint32)p3, p4, p5, (uint16*)&p6))
        return false;
    float a = (float)*p5;
    if ((int)*p5 < 0)
        a += 4294967296.0f;
    float b = (float)p3;
    if (p3 < 0)
        b += 4294967296.0f;
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
    // TODO(partial): OpenRecord — open-record multimap lookup, decompress and index update.
    return false;
}

// @ 0x006bde30
bool DatabasePackedFile_s006b_de30::OpenRecord(void* key, void** ppRecord, uint32 desiredAccess, int createDisposition, char flag, void* pInfo)
{
    // TODO(partial): full OpenRecord (open-record multimap, decompress, record factory).
    return false;
}

// @ 0x006be1d0
bool DatabasePackedFile_s006b_de30::FUN_006be1d0()
{
    // TODO(partial): read/rebuild index record.
    return false;
}
