// Editor block-data export: DumpBlockDescriptions(group, instance).
// Loads/creates "Editors_BlockData.package" and dumps every block-data resource of 6 resource types to
// "<dir>0x<type>!0x<instance>.blockdata", skipping the keys the (group, instance) property list already names.
// Unoptimized module (/Od /Ob1). Complete behavioural reconstruction; not byte-exact (see nonmatching.txt).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

// ---- small helper types ----------------------------------------------------------------------------
struct ResKey3 { uint32_t mInstance, mGroup, mType; };      // 12-byte key in the property array

struct IRefObj { virtual void v0(); virtual void Release(); virtual void v2(); };   // slot 1 = +4

struct IPropertyList {                       // vtable only needs Release at +4
    virtual void v0();
    virtual void Release();
};
struct PropListPtr {                         // EA::AutoRefCount<PropertyList>
    IPropertyList* mp;
    void** AsPPVoidParam();                  // 0x0041d870
};
struct IPropertyManager {                    // SP::PropertyManager() 0x0067de30
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropertyList(int instance, int group, void** out);       // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual void GetPropertyIDs(uint32_t typeID, void* idsVec);             // +0x48
};
IPropertyManager* PropertyManager();         // 0x0067de30

// std-like set of ResKey3 (eastl::rbtree), 0x1c bytes
struct KeySet {
    uint32_t mAlloc;
    void* mpEnd;                             // +4  (header node)
    void* mpBegin;                           // +8  (leftmost)
    void* mpRoot;                            // +0xc
    uint32_t pad[3];
    KeySet(const uint8_t* tag);              // 0x004b5980
    void Insert(void* outPair, ResKey3* key, bool b);   // 0x004290c0 DoInsertValue_unique
    void Find(void* outIter, ResKey3* key);              // 0x00422b00
    void DoNuke(void* root);                             // 0x004e8a30
};
struct KeyIter {
    void* mpNode;
    KeyIter(void* node);                     // 0x00566c50
    KeyIter& operator++();                   // 0x00422c50
    ResKey3& operator*();                    // 0x00564f50
};

struct AuxAlloc { uint32_t a, b; AuxAlloc(const uint8_t* tag); };   // 0x00429360
struct IdVec {                               // SimpleVector<uint32_t>
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    AuxAlloc mAlloc;
    IdVec(const uint8_t* tag) : mAlloc(tag) { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    void erase(uint32_t* first, uint32_t* last);   // 0x004769b0
    void FreeAll();                                // 0x00425990
};

struct WideBufA { uint32_t mpData; uint32_t pad[0x85]; WideBufA(); void ReleaseHeap(); };  // 0x0041d660 / 0x004292a0
struct WideBufB { uint32_t mpData; uint32_t pad[0x107]; WideBufB(); void ReleaseHeap(); }; // 0x0041d6c0 / 0x004292a0
struct ByteBuf  { uint32_t mpData; uint32_t pad[0x87]; ByteBuf(); void ReleaseHeap(); };   // 0x0041d720 / 0x00429300

// ---- resource-side interfaces ------------------------------------------------------------------------
struct IStream { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                 virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                 virtual void v10(); virtual void v11(); virtual void v12();
                 virtual void Write(const void* data, uint32_t size); };       // +0x38
struct IRecord { virtual void v0(); virtual void v1(); virtual void Release();   // +8
                 virtual void v3(); virtual void v4(); virtual void v5();
                 virtual IStream* GetStream();                                   // +0x18
                 virtual void v7(); virtual void v8();
                 virtual void Close(); };                                        // +0x24
struct ResKeyRec { uint32_t mInstance, mType, mGroup; };    // key passed to OpenRecord, 0x10 bytes incl. pad
struct IRecordCounted { char pad[0x40]; int mRefCount; void Release(); };       // Counted::Release 0x0040f360
struct IDatabaseDir {                                                           // Baker()->vcall(0x60)
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual IRecordCounted* GetRecord(uint32_t id, uint32_t type, int mode);    // +0xc
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21();
    virtual void Process(IRecordCounted* rec);                                  // +0x58
};
struct IBakerLike {                                                             // Baker() 0x00401010
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual IDatabaseDir* GetDatabaseDir();                                     // +0x60
};
IBakerLike* Baker();                                                            // 0x00401010

struct IPkgSecondary { virtual void AddRef(); virtual void Release(); };         // sub-object at +4
struct IPkgPrimary {
    virtual void v0(); virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Open(int mode, int access, int flags);                          // +0x18
    virtual void Close();                                                        // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void SetPath(const wchar_t* path);                                   // +0x2c
    virtual void v12();
    virtual bool OpenRecord(ResKeyRec* key, IRecord** out, int a, int b, int c, int d);   // +0x34
};
struct DatabasePackedFile : IPkgPrimary, IPkgSecondary {
    char pad[0x380];
    DatabasePackedFile(const wchar_t* path, void* alloc);                        // 0x008d9f80
    bool SetHoleUse(int mode, float f);                                          // 0x008d8530
};

struct MemoryStream {
    uint32_t pad[9];
    MemoryStream(void* a, void* b, const char* name);       // 0x0093c270
    void AddRef();                                          // 0x0083f5d0
    void SetOption(int opt, float v);                       // 0x0093bb40
    void SetSize(int n);                                    // 0x0093c370
    bool SetPosition(int off, int type);                    // 0x0093c0c0
    uint32_t GetSize();                                     // 0x00fc7e50
    void* GetData();                                        // 0x0093ba70
    void Destroy();                                         // 0x0093bde0
};
struct FileStream {
    uint32_t pad[0x8c];
    FileStream(const wchar_t* path);                        // 0x00931e10
    bool Open(int a, int b, int c, int d);                  // 0x009318f0
    void Write(const void* data, uint32_t size);            // 0x00931d30
    void Close();                                           // 0x00931a70
    ~FileStream();                                          // 0x00931e70
};
struct Transform { uint32_t pad[0x16]; Transform(); };      // 0x00409930
struct XfSlot { uint32_t mHead; Transform mXf; };           // 0x5c bytes

// ---- free functions ----------------------------------------------------------------------------------
void  FormatPath(void* wideBuf, const wchar_t* fmt, ...);   // 0x004c0530 (cdecl)
const wchar_t* GetBasePath();                               // 0x00688cf0
void* ZoneObject_new(int size, const char* name, int a, int b, int c, int d);   // 0x00926020
void  CreateDirectoryPath(const wchar_t* path);             // 0x00932960
bool  GetArrayProperty(IPropertyList* list, uint32_t id, int* count, ResKey3** arr);  // 0x006a0ae0 (cdecl)
bool  CollectAndDestroy(IRecordCounted* rec, MemoryStream* ms);   // 0x0041aa40 (cdecl)
extern uint32_t g_ResType0, g_ResType1, g_ResType2, g_ResType3, g_ResType4, g_ResType5;   // 0x015d13b8,0x15d117c,0x15d1248,0x15d1174,0x15d1254,0x15d132c

// @ 0x0041c1d0
void DumpBlockDescriptions(int group, int instance)
{
    uint8_t tag;
    KeySet seen(&tag);
    bool haveList = group != 0;
    if (haveList) {
        PropListPtr list;
        list.mp = 0;
        PropertyManager()->GetPropertyList(instance, group, list.AsPPVoidParam());
        if (list.mp) {
            int count;
            ResKey3* arr;
            GetArrayProperty(list.mp, 0x53878d0, &count, &arr);
            for (int i = 0; i < count; ++i) {
                arr[i].mGroup = 0;
                ResKey3* key = &arr[i];
                uint8_t dup = 0;
                char outPair[8];
                seen.Insert(outPair, key, dup != 0);
            }
            KeyIter it(seen.mpBegin);
            for (;;) {
                KeyIter e(seen.mpEnd);
                if (!(it.mpNode != e.mpNode)) break;
                ResKey3 copy = *it;
                ++it;
            }
            if (list.mp) list.mp->Release();
        }
    }

    uint8_t tag2;
    IdVec ids(&tag2);
    WideBufA dirPath;
    FormatPath(&dirPath, L"%lsEditors_BlockData.package", GetBasePath());

    DatabasePackedFile* pkg;
    void* mem = ZoneObject_new(0x388, "Editor", 0, 0, 0, 0);
    if (mem) pkg = new (mem) DatabasePackedFile(0, 0);
    else pkg = 0;
    if (pkg) ((IPkgSecondary*)pkg)->AddRef();
    pkg->SetPath(dirPath.mpData ? (const wchar_t*)dirPath.mpData : 0);
    pkg->SetHoleUse(5, -1.0f);
    ((IPkgPrimary*)pkg)->Release();
    pkg->Open(2, 2, 0);
    FormatPath(&dirPath, L"%lsBlockData/", GetBasePath());
    CreateDirectoryPath((const wchar_t*)dirPath.mpData);
    IDatabaseDir* dbdir = Baker()->GetDatabaseDir();

    XfSlot slots[32];
    WideBufB filePath;
    ByteBuf scratch;
    uint32_t types[6];
    types[0] = g_ResType0; types[1] = g_ResType1; types[2] = g_ResType2;
    types[3] = g_ResType3; types[4] = g_ResType4; types[5] = g_ResType5;

    MemoryStream ms(0, 0, "UTF/MemoryStream");
    ms.AddRef();
    ms.SetOption(1, 1.0f);
    ms.SetOption(2, 2.0f);

    for (unsigned t = 0; t < 6; ++t) {
        ids.erase(ids.mpBegin, ids.mpEnd);
        PropertyManager()->GetPropertyIDs(types[t], &ids);
        for (int i = 0; i < (int)(ids.mpEnd - ids.mpBegin); ++i) {
            if (haveList) {
                ResKey3 probe;
                probe.mInstance = ids.mpBegin[i];
                probe.mGroup = 0;
                probe.mType = types[t];
                KeyIter found(0);
                seen.Find(&found, &probe);
                KeyIter e(seen.mpEnd);
                if (found.mpNode == e.mpNode)
                    continue;
            }
            uint32_t* elem = &ids.mpBegin[i];
            IRecordCounted* rec = dbdir->GetRecord(*elem, types[t], 4);
            if (rec)
                rec->mRefCount = rec->mRefCount + 1;
            if (!rec) {
                continue;
            }
            dbdir->Process(rec);
            ms.SetSize(0);
            ms.SetPosition(0, 0);
            if (!CollectAndDestroy(rec, &ms)) {
                rec->Release();
                continue;
            }
            ResKeyRec key;
            key.mInstance = ids.mpBegin[i];
            key.mType = 0x5caa5e28;
            key.mGroup = types[t];
            IRecord* out = 0;
            if (out) {
                IRecord* o = out;
                out = 0;
                o->Release();
            }
            if (pkg->OpenRecord(&key, &out, 2, 2, 1, 0)) {
                IStream* st = out->GetStream();
                st->Write(ms.GetData(), ms.GetSize());
                out->Close();
            }
            uint32_t* elem2 = &ids.mpBegin[i];
            FormatPath(&filePath, L"%s0x%08x!0x%08x.blockdata", (const wchar_t*)dirPath.mpData, types[t], *elem2);
            FileStream fs((const wchar_t*)filePath.mpData);
            if (fs.Open(2, 2, 0, 0)) {
                fs.Write(ms.GetData(), ms.GetSize());
                fs.Close();
            }
            if (out)
                out->Release();
            rec->Release();
        }
    }
    pkg->Close();
    ms.Destroy();
    scratch.ReleaseHeap();
    filePath.ReleaseHeap();
    if (pkg)
        ((IPkgSecondary*)pkg)->Release();
    dirPath.ReleaseHeap();
    for (uint32_t* p = ids.mpBegin; p < ids.mpEnd; ++p) {
    }
    ids.FreeAll();
    seen.DoNuke(seen.mpRoot);
}
