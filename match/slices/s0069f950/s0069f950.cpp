// Slice s0069f950: SP::cCOMSerializer (object-stream writer/reader), the cObjectDatabase ctor,
// SP::GetPropertyAs* property getters and eastl::map<uint, cClassInfo>::operator[].
// Region is /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <intrin.h>

void* operator new(unsigned int size, const char* pName, int flags = 0, unsigned debugFlags = 0, const char* pFile = 0, int line = 0); // 0xf473a0
void __cdecl operator_delete_array(void* p);   // 0x00f47380 (operator delete[])

// ===========================================================================
// SP::GetPropertyAsVector2 / 3 / 4 and the Vector2 array getter
// ===========================================================================
struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// App::Property (0x14 bytes): value or {data, itemSize, itemCount}, flags (+0x10), type (+0x12).
struct Property {
    union { char raw[0x10]; struct { void* mpData; uint32_t mnItemSize; uint32_t mnItemCount; }; };
    short mnFlags;
    unsigned short mnType;
    Vec2* GetValueVector2();   // 0x006a0f70
    Vec3* GetValueVector3();   // 0x00cce910
    Vec4* GetValueVector4();   // 0x006a0fa0
};
struct PropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};

namespace SP {

// @ 0x006a10c0
bool GetPropertyAsVector2(PropertyList* list, uint32_t id, Vec2* dst)
{
    Property* p;
    if (list && list->GetProperty(id, &p) && p->mnType == 0x30) {
        *dst = *p->GetValueVector2();
        return true;
    }
    return false;
}

// @ 0x006a1110
bool GetPropertyAsVector3(PropertyList* list, uint32_t id, Vec3* dst)
{
    Property* p;
    if (list && list->GetProperty(id, &p) && p->mnType == 0x31) {
        *dst = *p->GetValueVector3();
        return true;
    }
    return false;
}

// @ 0x006a1160
bool GetPropertyAsVector4(PropertyList* list, uint32_t id, Vec4* dst)
{
    Property* p;
    if (list && list->GetProperty(id, &p) && p->mnType == 0x33) {
        *dst = *p->GetValueVector4();
        return true;
    }
    return false;
}

// @ 0x006a0920
// Property::GetArrayVector2: item count and data pointer of a Vector2 array property.
bool GetPropertyArrayVector2(PropertyList* list, uint32_t id, uint32_t* count, Vec2** data)
{
    Property* p;
    if (list && list->GetProperty(id, &p) && p->mnType == 0x30 && (p->mnFlags & 0x10)) {
        *count = (p->mnFlags & 0x30) ? p->mnItemCount : 1;
        *data = (p->mnFlags & 0x30) ? (Vec2*)p->mpData : (p->mnType ? (Vec2*)p : 0);
        return true;
    }
    return false;
}

} // namespace SP

// ===========================================================================
// Interfaces used by the serializer (vtable slots read off the disassembly)
// ===========================================================================
struct ISerializable {                       // the objects being written/read
    virtual void AddRef();                   // +0
    virtual void Release();                  // +4
    virtual void v2(); virtual void v3();
    virtual bool Write(struct SerStream* s); // +0x10
    virtual bool Read(struct SerStream* s);  // +0x14
    virtual void v6();
    virtual void v7();
    virtual uint32_t GetClassID();           // +0x20
};
struct RawStream {                           // low-level stream (position/size)
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual int  GetSize();                  // +0x1c
    virtual void v8();
    virtual int  GetPosition(int type);      // +0x24
    virtual void SetPosition(int pos, int mode); // +0x28
};
struct StreamIO {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5();
    virtual RawStream* GetRaw();             // +0x18
};
struct SerStream {                           // record stream handed out by the database
    virtual void v0();
    virtual void Release();                  // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Flush();                    // +0x1c
    virtual StreamIO* GetIO();               // +0x20
};
struct StreamKey {                           // {type tag, id, flags}
    const void* mpType;
    uint32_t mId;
    uint32_t mFlags;
};
extern char g_179d304[];                     // 0x0179d304
extern char g_179d310[];                     // 0x0179d310
struct ClassMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void RegisterClass(struct StreamKey* key);   // +0x40
};
struct SerDatabase {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual struct ClassMgr* GetMgr();       // +0x10
    virtual void v5();
    virtual bool OpenRead(StreamKey* key, SerStream** out);   // +0x18
    virtual bool CloseRead(SerStream* s);    // +0x1c
    virtual void v8();
    virtual bool OpenWrite(StreamKey* key, SerStream** out, int mode); // +0x24
    virtual bool CloseWrite(SerStream* s);   // +0x28
    virtual void v11();
    virtual bool HasKey(StreamKey* key);     // +0x30
    virtual void v13();
    virtual void SetProgress(float pct);     // +0x38
};

namespace EA { namespace IO {
void __cdecl ReadInt32(RawStream* s, int* pData, uint32_t count, int endian);        // 0x0093a780
void __cdecl WriteUint32(RawStream* s, const uint32_t* pData, uint32_t count, int endian); // 0x0093aa70
} }
void __cdecl WriteVarUint(SerStream* s, const uint32_t* pData);   // 0x00571f40
extern uint32_t kMaxCRCDataLength;   // 0x014084ec (1000000)

// EA::AutoRefCount with the AddRef/Release virtuals at slots 0/1.
template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    ~AutoRefCount() { if (mp) mp->Release(); }
    T** AsPPVoidParam() { if (mp) { T* t = mp; mp = 0; t->Release(); } return &mp; }
    void Assign(T* p) {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
    }
};

// ===========================================================================
// eastl::map<unsigned, T> (rbtree) pieces used by the serializer
// ===========================================================================
struct RBNodeBase {
    RBNodeBase* mpRight;     // +0
    RBNodeBase* mpLeft;      // +4
    RBNodeBase* mpParent;    // +8
    uint8_t mColor;          // +0xc
};
RBNodeBase* __cdecl RBTreeIncrement(RBNodeBase* n);             // 0x00921580
void __cdecl RBTreeErase(RBNodeBase* n, RBNodeBase* anchor);    // 0x00921880

struct RBIter {                // eastl::rbtree_iterator (user ctor: returned via hidden pointer)
    RBNodeBase* mpNode;
    RBIter() : mpNode(0) {}
    explicit RBIter(RBNodeBase* p) : mpNode(p) {}
    RBIter(const RBIter& x) : mpNode(x.mpNode) {}
};
struct RBInsertResult {        // pair<iterator, bool>
    RBNodeBase* mpNode;
    bool mbInserted;
    RBInsertResult() : mpNode(0), mbInserted(false) {}
};
struct true_type { };

struct RBMapBase {             // map header: key_compare slot, anchor, size, allocator
    uint32_t mCompare;         // +0
    RBNodeBase mAnchor;        // +4 (right = rightmost, left = leftmost, parent = root)
    uint32_t mnSize;           // +0x14
    uint32_t mAllocator;       // +0x18
    RBMapBase() : mAnchor() { mAnchor.mpRight = &mAnchor; mAnchor.mpLeft = &mAnchor; mAnchor.mpParent = 0; mAnchor.mColor = 0; mnSize = 0; }
    RBMapBase(const RBMapBase& x);                    // 0x0069e880 (map copy ctor)
    ~RBMapBase() { DoNukeSubtree(mAnchor.mpParent); }
    void DoNukeSubtree(RBNodeBase* n);                // 0x00d0c930
    RBIter find(const uint32_t& key);                 // 0x00e5c780
    RBNodeBase* begin() { return mAnchor.mpLeft; }
    RBNodeBase* end() { return &mAnchor; }
};

struct IDInfo {                // SP::cCOMSerializer::cIDInfo (4 bytes)
    AutoRefCount<ISerializable> mpSerializable;
};
struct IDPair { uint32_t first; IDInfo second; IDPair(uint32_t k) : first(k) {} };
struct IDMap : RBMapBase {
    IDMap() {}
    IDMap(const IDMap& x) : RBMapBase(x) {}
    RBInsertResult DoInsertValue(const IDPair& v, true_type);     // 0x0069e770
    IDInfo& operator[](const uint32_t& key);                       // 0x0069eb60
};
struct ClassInfo {             // SP::cCOMSerializer::cClassInfo (0x24 bytes)
    uint32_t mReadInstanceCount;   // +0
    uint32_t mInstanceCount;       // +4
    IDMap mInstanceIDMap;          // +8
};
struct ClassPair {
    uint32_t first;
    ClassInfo second;
    ClassPair(const uint32_t& k, const ClassInfo& v) : first(k), second(v) {}
};
struct ClassMap : RBMapBase {
    ClassMap& operator=(const ClassMap& x);                        // 0x0069f7b0
    RBInsertResult DoInsertValue(const ClassPair& v, true_type);   // 0x0069eea0
    RBIter DoInsertValue(RBIter hint, const ClassPair& v, true_type); // 0x0069efb0
    ClassInfo& operator[](const uint32_t& key);                    // 0x0069f950
};
struct ClassNode : RBNodeBase { ClassPair mValue; };    // value at +0x10 (key), +0x14 (ClassInfo)
struct IDNode : RBNodeBase { IDPair mValue; };

// @ 0x0069f950
ClassInfo& ClassMap::operator[](const uint32_t& key)
{
    // lower_bound
    RBNodeBase* pRangeEnd = &mAnchor;
    RBNodeBase* pCurrent = mAnchor.mpParent;
    while (pCurrent) {
        if (!(((ClassNode*)pCurrent)->mValue.first < key)) {
            pRangeEnd = pCurrent;
            pCurrent = pCurrent->mpLeft;
        } else {
            pCurrent = pCurrent->mpRight;
        }
    }
    if (pRangeEnd == &mAnchor || key < ((ClassNode*)pRangeEnd)->mValue.first) {
        ClassInfo tmp;
        ClassPair value(key, tmp);
        pRangeEnd = DoInsertValue(RBIter(pRangeEnd), value, true_type()).mpNode;
    }
    return ((ClassNode*)pRangeEnd)->mValue.second;
}

// ===========================================================================
// SP::cCOMSerializer / SP::cObjectDatabase
// ===========================================================================
struct cCOMSerializer;
// The cICOMSerializer sub-object (cCOMSerializer + 8). SaveClassObjects, WriteSerializableObject and
// ReadSerializableObject take this sub-object as `this`, so the data members that follow it are
// declared here with offsets relative to +8.
struct cICOMSerializer {
    void* vt;                           // +0 (full +8)
    bool mbBusyWritingClassObjects;     // +4 (full +0xc)
    char pad0[3];
    ClassMap mClassIDMapForWriting;     // +8 (full +0x10)
    ClassMap mClassIDMap;               // +0x24 (full +0x2c)
    int mTotalSerializableCount;        // +0x40 (full +0x48)
    uint8_t mbFlag44;                   // +0x44
    uint8_t mbClassObjectsSaved;        // +0x45
    char pad1[2];
    SerDatabase* mpDatabase;            // +0x48 (full +0x50)
    char pad2[0x14];

    bool SaveClassObjects();                                           // 0x0069fb90
    int WriteSerializableObject(SerStream* s, ISerializable* obj);    // 0x006a05f0
    int ReadSerializableObject(SerStream* s, ISerializable** out, char deep); // 0x006a06a0
};

struct cCOMSerializer {
    void* vt0;                          // +0
    int mRefCount;                      // +4
    cICOMSerializer mI;                 // +8

    cCOMSerializer(struct cObjectDatabase* owner);                     // 0x0069f840
    bool ComputeCRC(RawStream* io, uint32_t len, uint32_t* crcOut);    // 0x0069ec20
    bool onGetSPSerializable(ISerializable** out, uint32_t id, uint32_t classID); // 0x0069e9e0
    bool onSetSPSerializable(ISerializable* obj, uint32_t id, uint32_t classID);  // 0x006a0110
    bool loadSingleObject(ISerializable* obj, uint32_t id, uint32_t classID);     // 0x006a0360
};

#define FULL(p) ((cCOMSerializer*)((char*)(p) - 8))

// @ 0x006a0110
bool cCOMSerializer::onSetSPSerializable(ISerializable* obj, uint32_t id, uint32_t classID)
{
    RBIter it = mI.mClassIDMap.find(classID);
    ClassNode* classNode = (ClassNode*)it.mpNode;
    if (it.mpNode == mI.mClassIDMap.end()) {
        StreamKey key;
        key.mpType = g_179d304;
        key.mId = classID;
        key.mFlags = 0;
        if (mI.mpDatabase->HasKey(&key)) {
            mI.mpDatabase->GetMgr()->RegisterClass(&key);   // register the class with the database
        }
        ClassInfo tmp;
        ClassPair value(classID, tmp);
        RBInsertResult r = mI.mClassIDMap.DoInsertValue(value, true_type());
        classNode = (ClassNode*)r.mpNode;
        classNode->mValue.second.mReadInstanceCount = 0;
        classNode->mValue.second.mInstanceCount = 0;
    }
    ClassInfo& info = classNode->mValue.second;
    RBIter idIt = info.mInstanceIDMap.find(id);
    if (idIt.mpNode == info.mInstanceIDMap.end()) {
        IDPair idValue(id);
        RBInsertResult r2 = info.mInstanceIDMap.DoInsertValue(idValue, true_type());
        IDNode* idNode = (IDNode*)r2.mpNode;
        info.mInstanceCount++;
        mI.mTotalSerializableCount++;
        idNode->mValue.second.mpSerializable.Assign(obj);
        if (mI.mbBusyWritingClassObjects) {
            IDInfo& w = mI.mClassIDMapForWriting[classID].mInstanceIDMap[id];
            w.mpSerializable.Assign(idNode->mValue.second.mpSerializable.mp);
        }
    }
    return true;
}

// @ 0x006a0360
bool cCOMSerializer::loadSingleObject(ISerializable* obj, uint32_t id, uint32_t classID)
{
    bool ok = false;
    AutoRefCount<SerStream> stream;
    ClassInfo& info = mI.mClassIDMap[classID];
    SerDatabase* db = mI.mpDatabase;
    StreamKey key;
    key.mpType = g_179d304;
    key.mId = classID;
    key.mFlags = 0;
    if (db->OpenRead(&key, stream.AsPPVoidParam())) {
        StreamIO* io = stream.mp->GetIO();
        uint32_t remaining = info.mReadInstanceCount;
        if (remaining < 1000000) {
            while (remaining != 0) {
                --remaining;
                int pos = io->GetRaw()->GetPosition(0);
                int size;
                EA::IO::ReadInt32(stream.mp->GetIO()->GetRaw(), &size, 1, 0);
                if ((uint32_t)size > (uint32_t)(pos + io->GetRaw()->GetSize())) { ok = false; break; }
                int storedCRC;
                EA::IO::ReadInt32(stream.mp->GetIO()->GetRaw(), &storedCRC, 1, 0);
                uint32_t len = size - 8;
                uint32_t n = (len > kMaxCRCDataLength) ? kMaxCRCDataLength : len;
                uint32_t crc = 0;
                if (ComputeCRC(io->GetRaw(), n, &crc)) {
                    ok = ((uint32_t)storedCRC == crc);
                } else {
                    ok = false;
                }
                if (!ok) {
                    io->GetRaw()->SetPosition(size + pos, 0);
                    ok = false;
                    break;
                }
                int readID;
                EA::IO::ReadInt32(stream.mp->GetIO()->GetRaw(), &readID, 1, 0);
                if ((uint32_t)readID == id) {
                    ok = obj->Read(stream.mp);
                    if (ok) io->GetRaw()->GetPosition(0);
                    break;
                }
                io->GetRaw()->SetPosition(size + pos, 0);
            }
        }
        if (!mI.mpDatabase->CloseRead(stream.mp)) ok = false;
        if (info.mReadInstanceCount != info.mInstanceCount) ok = false;
    }
    return ok;
}

// @ 0x0069fb90
bool cICOMSerializer::SaveClassObjects()
{
    if (mbClassObjectsSaved) return true;
    if (!mbFlag44 && mClassIDMap.mnSize == 0) return true;

    AutoRefCount<SerStream> stream;
    mbBusyWritingClassObjects = true;
    mClassIDMapForWriting = mClassIDMap;
    int done = 0;
    uint32_t written = 0;
    if (mTotalSerializableCount != 0) {
        do {
            RBNodeBase* cn = mClassIDMapForWriting.begin();
            while (cn != mClassIDMapForWriting.end()) {
                RBNodeBase* classNext = RBTreeIncrement(cn);
                ClassNode* node = (ClassNode*)cn;
                if (node->mValue.second.mInstanceIDMap.mnSize != 0) {
                    StreamKey key;
                    key.mpType = g_179d304;
                    key.mId = node->mValue.first;
                    key.mFlags = 0;
                    SerDatabase* db = mpDatabase;
                    if (!db->OpenWrite(&key, stream.AsPPVoidParam(), 0)) return false;
                    StreamIO* io = stream.mp->GetIO();
                    IDMap& ids = node->mValue.second.mInstanceIDMap;
                    RBNodeBase* idn = ids.begin();
                    if (idn != ids.end()) {
                        do {
                            IDNode* inode = (IDNode*)idn;
                            int start = io->GetRaw()->GetPosition(0);
                            RBNodeBase* idNext = RBTreeIncrement(idn);
                            uint32_t zero = 0;
                            EA::IO::WriteUint32(stream.mp->GetIO()->GetRaw(), &zero, 1, 0);
                            zero = 0;
                            EA::IO::WriteUint32(stream.mp->GetIO()->GetRaw(), &zero, 1, 0);
                            uint32_t instID = inode->mValue.first;
                            EA::IO::WriteUint32(stream.mp->GetIO()->GetRaw(), &instID, 1, 0);
                            if (inode->mValue.second.mpSerializable.mp->Write(stream.mp)) {
                                int end = io->GetRaw()->GetPosition(0);
                                uint32_t size = end - start;
                                io->GetRaw()->SetPosition(start, 0);
                                EA::IO::WriteUint32(stream.mp->GetIO()->GetRaw(), &size, 1, 0);
                                io->GetRaw()->SetPosition(start + 8, 0);
                                uint32_t len = size - 8;
                                uint32_t n = (len > kMaxCRCDataLength) ? kMaxCRCDataLength : len;
                                uint32_t crc = 0;
                                FULL(this)->ComputeCRC(io->GetRaw(), n, &crc);
                                io->GetRaw()->SetPosition(start + 4, 0);
                                EA::IO::WriteUint32(stream.mp->GetIO()->GetRaw(), &crc, 1, 0);
                                io->GetRaw()->SetPosition(end, 0);
                                written++;
                            } else {
                                io->GetRaw()->SetPosition(start, 0);
                            }
                            done++;
                            node->mValue.second.mInstanceIDMap.mnSize--;
                            RBTreeIncrement(idn);
                            RBTreeErase(idn, &ids.mAnchor);
                            if (inode->mValue.second.mpSerializable.mp) inode->mValue.second.mpSerializable.mp->Release();
                            operator_delete_array(idn);
                            if (!stream.mp->Flush()) {
                                mpDatabase->CloseWrite(stream.mp);
                                return false;
                            }
                            idn = idNext;
                        } while (idn != ids.end());
                    }
                    if (!mpDatabase->CloseWrite(stream.mp)) return false;
                }
                cn = classNext;
            }
            mpDatabase->SetProgress((float)done * 100.0f / (float)mTotalSerializableCount);
        } while (done != mTotalSerializableCount);
    }

    mbBusyWritingClassObjects = false;
    StreamKey key2;
    key2.mpType = g_179d304;
    key2.mId = (uint32_t)g_179d310;
    key2.mFlags = 0;
    SerDatabase* db2 = mpDatabase;
    if (db2->OpenWrite(&key2, stream.AsPPVoidParam(), 1)) {
        uint32_t v = 1;
        WriteVarUint(stream.mp, &v);
        v = mClassIDMap.mnSize;
        WriteVarUint(stream.mp, &v);
        WriteVarUint(stream.mp, &written);
        for (RBNodeBase* n = mClassIDMap.begin(); n != mClassIDMap.end(); n = RBTreeIncrement(n)) {
            uint32_t classID = ((ClassNode*)n)->mValue.first;
            EA::IO::WriteUint32(stream.mp->GetIO()->GetRaw(), &classID, 1, 0);
            uint32_t count = ((ClassNode*)n)->mValue.second.mInstanceCount;
            EA::IO::WriteUint32(stream.mp->GetIO()->GetRaw(), &count, 1, 0);
        }
        if (!mpDatabase->CloseWrite(stream.mp)) return false;
        if (!stream.mp->Flush()) return false;
    }
    mbClassObjectsSaved = 1;
    return true;
}

// @ 0x006a05f0
int cICOMSerializer::WriteSerializableObject(SerStream* s, ISerializable* obj)
{
    if (mpDatabase != 0) {
        RawStream* io = s->GetIO()->GetRaw();
        uint32_t classID = obj ? obj->GetClassID() : 0;
        uint32_t idv = (uint32_t)obj;
        EA::IO::WriteUint32(io, &idv, 1, 0);
        if (obj) {
            idv = classID;
            EA::IO::WriteUint32(io, &idv, 1, 0);
            if (!FULL(this)->onSetSPSerializable(obj, (uint32_t)obj, classID)) return 0;
        }
        if (s->Flush()) return 1;
    }
    return 0;
}

// @ 0x006a06a0
int cICOMSerializer::ReadSerializableObject(SerStream* s, ISerializable** out, char deep)
{
    if (mpDatabase != 0) {
        RawStream* io = s->GetIO()->GetRaw();
        int id;
        EA::IO::ReadInt32(io, &id, 1, 0);
        if (id != 0) {
            int classID;
            EA::IO::ReadInt32(io, &classID, 1, 0);
            if (!FULL(this)->onGetSPSerializable(out, id, classID)) return 0;
            if (deep) FULL(this)->loadSingleObject(*out, id, classID);
        } else {
            *out = 0;
        }
        if (s->Flush()) return 1;
    }
    return 0;
}

// ===========================================================================
// cObjectDatabase constructor
// ===========================================================================
struct Database;
struct IUnk { virtual void AddRef(); virtual void Release(); };
extern char g_vtbl_14085f0[]; extern char g_vtbl_13f1ab0[]; extern char g_vtbl_1408500[]; extern char g_vtbl_14084f0[];
extern char g_vtbl_13ec458[]; extern char g_vtbl_14086e8[]; extern char g_vtbl_1408698[]; extern char g_vtbl_1408688[];
extern char g_vtbl_1408678[];

struct DatabaseRef {            // EA::AutoRefCount<Database>: AddRef/Release go through the +4 sub-object
    char* mp;
    DatabaseRef() : mp(0) {}
    ~DatabaseRef() { if (mp) ((IUnk*)(mp + 4))->Release(); }
    void Assign(char* p) {
        char* old = mp;
        if (p != old) {
            if (p) ((IUnk*)(p + 4))->AddRef();
            mp = p;
            if (old) ((IUnk*)(old + 4))->Release();
        }
    }
};
struct SerializerRef {          // AutoRefCount<cICOMSerializer>
    IUnk* mp;
    SerializerRef() : mp(0) {}
    ~SerializerRef() { if (mp) mp->Release(); }
    void Assign(IUnk* p) {
        IUnk* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
    }
};

struct cObjectDatabase {
    void* vt0; void* vt4; void* vt8;
    long mDbRefCount;               // +0xc  (Database::mRefCount, atomically cleared)
    void* vt10;
    int mRefCount;                  // +0x14
    DatabaseRef mpDatabase;         // +0x18
    SerializerRef mpCOMSerializer;  // +0x1c
    float mfPercentageCompletion0To100; // +0x20
    cObjectDatabase(Database* database);   // 0x0069fa60
};

// @ 0x0069fa60
cObjectDatabase::cObjectDatabase(Database* database)
{
    vt0 = g_vtbl_14085f0;
    vt8 = g_vtbl_13f1ab0;
    vt4 = g_vtbl_1408500;
    vt8 = g_vtbl_14084f0;
    _InterlockedExchange(&mDbRefCount, 0);
    vt10 = g_vtbl_13ec458;
    mRefCount = 0;
    vt0 = g_vtbl_14086e8;
    vt4 = g_vtbl_1408698;
    vt8 = g_vtbl_1408688;
    vt10 = g_vtbl_1408678;
    mfPercentageCompletion0To100 = 0.0f;
    cCOMSerializer* ser = new("App", 0, 0, 0, 0) cCOMSerializer(this);
    mpCOMSerializer.Assign(ser ? (IUnk*)&ser->mI : 0);
    mpDatabase.Assign((char*)database);
}
