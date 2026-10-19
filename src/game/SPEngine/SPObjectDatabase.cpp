// src/game/SPEngine/SPObjectDatabase.cpp -- migrated from slice(s) s0069f950, s0069e3a0, s0069d090 by tools/migrate/rewrite.py
// Object file: SPEngine/SPObjectDatabase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Database.h"
#include "SP/cObjectDatabase.h"

// unnamed retail callees and globals (address in the comment)
extern char g_vtbl_1408550[];
extern char g_vtbl_1408598[];
extern char g_vtbl_14085dc[];
extern char g_vtbl_140862c[];
extern char g_vtbl_1408668[];
extern char g_vtbl_14085f0[];
extern char g_vtbl_13eb938[];
extern char g_vtbl_13effb8[];
extern char g_vtbl_14086e8[];
extern char g_vtbl_1408698[];
extern char g_vtbl_1408688[];
extern char g_vtbl_1408678[];
extern char g_vtbl_13ec458[];
extern "C" void __stdcall FUN_0069d2c0(void* p);
extern "C" void FUN_005766e0(void*);
#include <intrin.h>
#include "SP/cCOMSerializer.h"
#include <new>
#include "SP/CellSaveGame.h"
#include "SP/cICOMSerializer.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "EA/IO/FileStream.h"
#include "SP/cIObjectDatabaseOStream.h"
#include "cSPVector2.h"
#include "cSPVector3.h"
#include "cSPVector4.h"

// ---- items of slice s0069d090 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* VP;
extern char g_vtbl_1408550[];
extern char g_vtbl_1408598[];
extern char g_vtbl_14085dc[];
extern char g_vtbl_140862c[];
extern char g_vtbl_1408668[];
extern char g_vtbl_14085f0[];
extern char g_vtbl_13eb938[];
extern char g_vtbl_13effb8[];
extern char g_vtbl_14086e8[];
extern char g_vtbl_1408698[];
extern char g_vtbl_1408688[];
extern char g_vtbl_1408678[];
extern char g_vtbl_13ec458[];
struct C2a { char pad[4]; unsigned char flag; bool f(int, int); };
struct C2b { char pad[0xc]; unsigned char flag; bool g(int, int); };
struct C3 {
    char pad[8];
    void* stream;       // +8
    unsigned char flag; // +0xc
    bool read(int size);
};
extern "C" void __stdcall FUN_0069d2c0(void* p);
struct C5 { char pad[0x20]; float mfProgress; void setProgress(float v); };
struct C6 { VP asInterface(int iid); };
struct C7 { int Release(); };
struct Holder {
    char pad[4];
    unsigned char flag;     // +4
    char pad2[7];
    void* p0c;              // +0xc
    void* p10;              // +0x10
    bool reset();
    bool valid();
    void conditional(int, int);
};
struct C830 { char pad[4]; unsigned char flag; char pad2[7]; void* p0c; void f(int a, int b); };
struct Holder8 {
    char pad[4];
    void* p4;               // +4
    void* p8;               // +8
    unsigned char flag;     // +0xc
    bool reset();
    bool valid();
};
struct C950 { void emit(void*); };
struct C980 { char pad[8]; void* p8; unsigned char flag; int f(int p); };
int C980::f(int p)
{
    if (flag) {
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p8)[0x14 / 4])(p8);
        void* self = (this == (C980*)8) ? 0 : this;
        char c = ((char(__thiscall*)(void*, void*, int))(*(void***)pi)[0x20 / 4])(pi, self, p);
        if (c)
            return flag = 1;
    }
    int r = 0;
    flag = r;
    return r;
}
struct Cdc60 { char pad[4]; void* p4; char pad2[4]; unsigned char flag; int f(int a, int b); };
int Cdc60::f(int a, int b)
{
    if (flag) {
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p4)[0x18 / 4])(p4);
        char c = ((char(__thiscall*)(void*, int, int))(*(void***)pi)[0x38 / 4])(pi, a, b);
        if (c)
            return flag = 1;
    }
    int r = 0;
    flag = r;
    return r;
}
struct Cddc0 { char pad[0x14]; void* p14; int get(); };
struct Cdea0 { char pad[0x1c]; void* p1c; char get(); };
struct Cded0 { char pad[0x14]; void* p14; void* p18; char flush(); };
struct Cdf90 { char pad[0x14]; void* p14; void* p18; bool ok(); };
struct Cdfc0 { char pad[0x48]; void* p48; bool bind(void* p, int unused); };
bool Cdfc0::bind(void* p, int)
{
    if (p) {
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p)[0x10 / 4])(p);
        int r = ((int(__thiscall*)(void*))(*(void***)pi)[0x20 / 4])(pi);
        if (r) {
            void* old = p48;
            if (p != old) {
                ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
                p48 = p;
                if (old)
                    ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
            }
            return true;
        }
    }
    return false;
}
struct C_e040 {
    VP p0; VP p4; VP p8;
    unsigned char flag; char pad0[3];
    VP p10; VP p14; VP p18;
    C_e040* ctor();
};
struct C_e210 {
    VP p0; VP p4; VP p8; VP p0c; VP p10;
    unsigned char flag; char pad0[3];
    C_e210* ctor();
};
struct Cdf20 {
    char pad[4];
    void* p4;               // +4
    char pad2[0x10];
    void* p18;              // +0x18
    void* p1c;              // +0x1c
    float f20;              // +0x20
    bool begin(char flag);
};
struct cObjectDatabase {
    VP vt0; VP vt4; VP vt8; VP pad_c; VP vt10; VP pad14; void* p18; void* p1c; float f20;
    void dtor();
};
extern "C" void FUN_005766e0(void*);
struct S_e090 {
    VP vt0; unsigned char flag; char pad[7]; void* p0c; void* p10;
    void bind(void* p, int x);
};
void S_e090::bind(void* p, int)
{
    if (!((char(__thiscall*)(void*))(*(void***)this)[0x14 / 4])(this))
        return;
    if (p) {
        void* old = p10;
        if (p != old) {
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            p10 = p;
            if (old) ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
        }
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p10)[0x10 / 4])(p10);
        void* tmp = 0;
        if (((char(__thiscall*)(void*, int, void**, int, int, int, int))(*(void***)pi)[0x34 / 4])(pi, 0, &tmp, 1, 6, 1, 0))
            FUN_005766e0(&tmp);
        if (tmp) ((void(__thiscall*)(void*))(*(void***)tmp)[8 / 4])(tmp);
    }
    flag = (unsigned char)(p0c != 0);
}
struct S_e260 {
    VP vt0; void* p4; void* p8; unsigned char flag;
    void bind(void* p, int a, int b);
};
// ---- items of slice s0069d090 end

// ---- items of slice s0069e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned size, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void  FUN_00932da0();
extern "C" void  FUN_004c0410(int);
extern "C" void  FUN_0069e880(void*);
extern char g_vtbl_1408750[];
extern char g_vtbl_1408728[];
extern char g_vtbl_14095cc[];
extern "C" void FUN_d0c930(void* value, void* arg);
extern "C" void FUN_00e5c780(void*, int*, int*);
static const char kEastlAllocH[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct RBNode {
    RBNode* mpNodeLeft;     // +0
    RBNode* mpNodeRight;    // +4
    RBNode* mpNodeParent;   // +8
    unsigned char mColor;   // +0xc
    char pad0[3];
    // value area starts at +0x10
};
struct P550; struct P_ecc0;
struct Tree {
    void* pad0;             // +0
    RBNode* mpNodeLeft;     // +4   (anchor)
    RBNode* mpNodeRight;    // +8
    RBNode* mpNodeParent;   // +0xc
    unsigned char mColor;   // +0x10
    char pad1[3];
    unsigned int mnSize;    // +0x14
    int pad2;               // +0x18
    // rbtree member functions (receive the tree in ECX)
    RBNode* AllocA(P550* src);
    RBNode* CopyA(RBNode* pNode, RBNode* pParent);
    RBNode* AllocB(P_ecc0* src);
    RBNode* CopyB(RBNode* pNode, RBNode* pParent);
    void Nuke(RBNode* pNode);
};
struct P550 { int key; void* obj; };
struct P_ecc0 { int a; int b; int c; char rest[0x28]; };
struct CComSer {
    VP vt0;                 // +0
    int mRefCount;          // +4
    VP vt8;                 // +8
    unsigned char flag_c;   // +0xc
    char pad0[3];
    Tree mTree1;            // +0x10  (mClassIDMapForWriting)
    Tree mTree2;            // +0x2c  (mClassIDMap)
    void* p48;              // +0x48
    unsigned char b4c;      // +0x4c
    unsigned char b4d;      // +0x4d
    char pad2[2];
    void* p50;              // +0x50
    void* p54;              // +0x54
    void* p58;              // +0x58
    void* p5c;              // +0x5c
    void dtor();
    void reset();
};
struct F940 { bool f(); };
bool F940::f()
{
    ((CComSer*)((char*)this - 8))->reset();
    return true;
}
struct F_e9e0 { int f(char* a, int b, int c); };
int F_e9e0::f(char* a, int b, int c)
{
    *(int*)a = 0;
    FUN_00e5c780(this, 0, 0);
    return 0;
}
struct F_eb60 { int f(int* key); };
struct F_ec20 { bool f(int* io, unsigned index); };
CComSer* FUN_0069f840(CComSer* self, void* param);
// ---- items of slice s0069e3a0 end


// ---- items of slice s0069f950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t kMaxCRCDataLength;   // 0x014084ec (1000000)
extern char g_vtbl_14085f0[]; extern char g_vtbl_13f1ab0[]; extern char g_vtbl_1408500[]; extern char g_vtbl_14084f0[];
extern char g_vtbl_13ec458[]; extern char g_vtbl_14086e8[]; extern char g_vtbl_1408698[]; extern char g_vtbl_1408688_s0069_f950[];
void* operator new(unsigned int size, const char* pName, int flags = 0, unsigned debugFlags = 0, const char* pFile = 0, int line = 0); // 0xf473a0
void __cdecl operator_delete_array(void* p);   // 0x00f47380 (operator delete[])
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
#define g_179d304 ((char*)0x0179d304)
#define g_179d310 ((char*)0x0179d310)
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
namespace EA {
namespace IO {
void __cdecl ReadInt32(RawStream* s, int* pData, uint32_t count, int endian);        // 0x0093a780
}
}
namespace EA {
namespace IO {
void __cdecl WriteUint32(RawStream* s, const uint32_t* pData, uint32_t count, int endian); // 0x0093aa70
}
}
void __cdecl WriteVarUint(SerStream* s, const uint32_t* pData);   // 0x00571f40
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
    // eastl::map::operator[] (0x0069f950). The out-of-line body is named Subscript so the
    // equivalence checker can find it by name; operator[] just forwards to it.
    ClassInfo& Subscript(const uint32_t& key);                     // 0x0069f950
    ClassInfo& operator[](const uint32_t& key) { return Subscript(key); }
};
struct ClassNode : RBNodeBase { ClassPair mValue; };    // value at +0x10 (key), +0x14 (ClassInfo)
struct IDNode : RBNodeBase { IDPair mValue; };
struct cCOMSerializer;
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

    cCOMSerializer(struct cObjectDatabase_s0069_f950* owner);                     // 0x0069f840
    bool ComputeCRC(RawStream* io, uint32_t len, uint32_t* crcOut);    // 0x0069ec20
    bool onGetSPSerializable(ISerializable** out, uint32_t id, uint32_t classID); // 0x0069e9e0
    bool onSetSPSerializable(ISerializable* obj, uint32_t id, uint32_t classID);  // 0x006a0110
    bool loadSingleObject(ISerializable* obj, uint32_t id, uint32_t classID);     // 0x006a0360
};
#define FULL(p) ((cCOMSerializer*)((char*)(p) - 8))
struct Database;
struct IUnk { virtual void AddRef(); virtual void Release(); };
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
struct cObjectDatabase_s0069_f950 {
    void* vt0; void* vt4; void* vt8;
    long mDbRefCount;               // +0xc  (Database::mRefCount, atomically cleared)
    void* vt10;
    int mRefCount;                  // +0x14
    DatabaseRef mpDatabase;         // +0x18
    SerializerRef mpCOMSerializer;  // +0x1c
    float mfPercentageCompletion0To100; // +0x20
    cObjectDatabase_s0069_f950(Database* database);   // 0x0069fa60
};
// ---- items of slice s0069f950 end

// @ 0x0069d1d0
bool C2a::f(int, int)
{ flag = 0; return false; }




// @ 0x0069d210
bool C3::read(int size)
{
    char buffer[1024];
    if (size >= 0x400) {
        int blocks = size >> 10;
        size -= blocks << 10;
        do {
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x34 / 4])(stream, buffer, 0x400);
        } while (--blocks);
    }
    if (size > 0) {
        ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x34 / 4])(stream, buffer, size);
    }
    return flag != 0;
}




// @ 0x0069d280
bool C2b::g(int, int)
{ flag = 0; return false; }




// @ 0x0069d2c0
void __stdcall FUN_0069d2c0(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[0x14 / 4])(p);
}




// @ 0x0069d2f0
void C5::setProgress(float v)
{
    if (v < 0.0f)
        v = 0.0f;
    else if (v > 100.0f)
        v = 100.0f;
    if (v > mfProgress)
        mfProgress = v;
}




// @ 0x0069d360
VP C6::asInterface(int iid)
{
    if (iid != (int)0xee3f516e)
        return 0;
    return ((char*)this - 4) ? this : 0;
}




// @ 0x0069d3c0
int C7::Release()
{
    long* p = (long*)((char*)this + 4);
    long n = _InterlockedExchangeAdd(p, -1);
    --n;
    if (n == 0) {
        _InterlockedExchange(p, 1);
        void* owner = (void*)((char*)this - 4);
        if (owner)
            ((void(__thiscall*)(void*, int))(*(void***)owner)[0])(owner, 1);
    }
    return (int)n;
}




// @ 0x0069d3f0
int EA::ResourceMan::Database::GetRefCount()
{
    return (int)_InterlockedExchangeAdd((long*)((char*)this + 8), 0);
}




// @ 0x0069d480
bool Holder::reset()
{
    if (p10 && p0c)
        ((void(__thiscall*)(void*))(*(void***)p0c)[0x24 / 4])(p0c);
    void* q = p0c;
    if (q) {
        p0c = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[8 / 4])(q);
    }
    void* r = p10;
    if (r) {
        p10 = 0;
        ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
    }
    return flag = true;
}




// @ 0x0069d4d0
bool Holder::valid()
{
    return p0c != 0 && p10 != 0;
}




// @ 0x0069d4f0
void Holder::conditional(int a, int b)
{
    void* o = p10;
    void* pi = ((void*(__thiscall*)(void*))(*(void***)o)[0x14 / 4])(o);
    if (flag) {
        void* self = (this == (Holder*)8) ? 0 : this;
        char c = ((char(__thiscall*)(void*, void*, int, int))(*(void***)pi)[0x24 / 4])(pi, self, a, b);
        if (c) {
            flag = 1;
            return;
        }
    }
    flag = 0;
}




// @ 0x0069d830
void C830::f(int a, int b)
{
    void* pi = ((void*(__thiscall*)(void*))(*(void***)p0c)[0x18 / 4])(p0c);
    int r = ((int(__thiscall*)(void*, int, int))(*(void***)pi)[0x30 / 4])(pi, a, b);
    flag = (unsigned char)(r == b);
}




// @ 0x0069d8e0
bool Holder8::reset()
{
    if (p8 && p4)
        ((void(__thiscall*)(void*))(*(void***)p4)[0x24 / 4])(p4);
    void* q = p4;
    if (q) {
        p4 = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[8 / 4])(q);
    }
    void* r = p8;
    if (r) {
        p8 = 0;
        ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
    }
    return flag = true;
}




// @ 0x0069d930
bool Holder8::valid()
{
    return p4 != 0 && p8 != 0;
}




// @ 0x0069d950
void C950::emit(void* p)
{
    void* u = 0;
    if (p)
        u = ((void*(__thiscall*)(void*, int))(*(void***)p)[0xc / 4])(p, 0x179c807);
    ((void(__thiscall*)(void*, void*))(*(void***)this)[0x2c / 4])(this, u);
}




// @ 0x0069dca0
void cObjectDatabase::dtor()
{
    vt0 = g_vtbl_14086e8;
    vt4 = g_vtbl_1408698;
    vt8 = g_vtbl_1408688;
    vt10 = g_vtbl_1408678;
    if (p1c) {
        p1c = 0;
        ((void(__thiscall*)(void*))(*(void***)p1c)[4 / 4])(p1c);
    }
    if (p1c) {
        ((void(__thiscall*)(void*))(*(void***)p1c)[4 / 4])(p1c);
    }
    if (p18) {
        void* b = (char*)p18 + 4;
        ((void(__thiscall*)(void*))(*(void***)b)[4 / 4])(b);
    }
    vt10 = g_vtbl_13ec458;
    vt8 = g_vtbl_13eb938;
    vt4 = g_vtbl_13effb8;
    vt0 = g_vtbl_13eb938;
}




// @ 0x0069ddc0
int Cddc0::get()
{
    void* o = p14;
    if (o)
        return ((int(__thiscall*)(void*))(*(void***)o)[0x20 / 4])(o);
    return 0;
}




// @ 0x0069dea0
char Cdea0::get()
{
    void* o = p1c;
    if (o)
        return ((char(__thiscall*)(void*))(*(void***)o)[0x1c / 4])(o);
    return 0;
}




// @ 0x0069ded0
char Cded0::flush()
{
    ((void(__thiscall*)(void*))(*(void***)this)[0x1c / 4])(this);
    void* q = p18;
    if (q) {
        p18 = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[4 / 4])(q);
    }
    char r = ((char(__thiscall*)(void*))(*(void***)p14)[8 / 4])(p14);
    void* s = p14;
    if (s) {
        p14 = 0;
        void* s4 = (char*)s + 4;
        ((void(__thiscall*)(void*))(*(void***)s4)[4 / 4])(s4);
    }
    return r;
}




// @ 0x0069df20
bool Cdf20::begin(char flag)
{
    f20 = 0.0f;
    char mode = (char)((flag == 0) + 1);
    char c1 = ((char(__thiscall*)(void*, int, int, int))(*(void***)p18)[0x18 / 4])(p18, mode, 4, 0);
    if (c1) {
        if (((char(__thiscall*)(void*, void*, int))(*(void***)p1c)[0x10 / 4])(p1c, this, mode))
            return true;
    }
    if (((int(__thiscall*)(void*))(*(void***)p4)[0x20 / 4])(p4))
        ((void(__thiscall*)(void*))(*(void***)p4)[0x1c / 4])(p4);
    return false;
}




// @ 0x0069df90
bool Cdf90::ok()
{
    bool c1 = ((char(__thiscall*)(void*))(*(void***)p18)[0x14 / 4])(p18) != 0;
    if (!((char(__thiscall*)(void*))(*(void***)p14)[0x1c / 4])(p14))
        return false;
    return c1;
}




// @ 0x0069dfc0
void S_e260::bind(void* p, int a, int b)
{
    if (!((char(__thiscall*)(void*))(*(void***)this)[0x14 / 4])(this))
        return;
    if (p) {
        void* old = p8;
        if (p != old) {
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            p8 = p;
            if (old) ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
        }
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p8)[0x10 / 4])(p8);
        void* tmp = 0;
        if (((char(__thiscall*)(void*, int, void**, int, int, int, int))(*(void***)pi)[0x34 / 4])(pi, a, &tmp, 2, 4, 1, 0)) {
            FUN_005766e0(&tmp);
            int v = (b == 0) ? 0 : ((int(__thiscall*)(void*))(*(void***)(void*)p4)[0x1c / 4])(p4);
            pi = ((void*(__thiscall*)(void*))(*(void***)p4)[0x18 / 4])(p4);
            ((void(__thiscall*)(void*, int, int))(*(void***)pi)[0x28 / 4])(pi, v, 0);
        }
        if (tmp) ((void(__thiscall*)(void*))(*(void***)tmp)[8 / 4])(tmp);
    }
    flag = (unsigned char)(p4 != 0);
}




// @ 0x0069e040
C_e040* C_e040::ctor()
{
    p4 = 0;
    p8 = g_vtbl_1408550;
    _ReadWriteBarrier();
    p0 = g_vtbl_14085dc;
    p8 = g_vtbl_1408598;
    flag = 1;
    p10 = 0;
    p14 = 0;
    p18 = 0;
    return this;
}




// @ 0x0069e210
C_e210* C_e210::ctor()
{
    p4 = 0;
    p8 = g_vtbl_14085f0;
    _ReadWriteBarrier();
    p0 = g_vtbl_1408668;
    p8 = g_vtbl_140862c;
    p0c = 0;
    p10 = 0;
    flag = 1;
    return this;
}



// @ 0x0069e550
RBNode* Tree::AllocA(P550* src)
{
    RBNode* n = (RBNode*)EASTL_allocator_allocate(0x18, "App", 0, 0, kEastlAllocH, 0xd1);
    *(int*)((char*)n + 0x10) = src->key;
    void* o = src->obj;
    *(void**)((char*)n + 0x14) = o;
    if (o)
        ((void(__thiscall*)(void*))(*(void***)o)[0])(o);
    return n;
}

// @ 0x0069e6c0
RBNode* Tree::CopyA(RBNode* pNode, RBNode* pParent)
{
    RBNode* pNew = AllocA((P550*)((char*)pNode + 0x10));
    pNew->mpNodeLeft = 0;
    pNew->mpNodeRight = 0;
    pNew->mpNodeParent = pParent;
    pNew->mColor = pNode->mColor;
    if (pNode->mpNodeLeft)
        pNew->mpNodeLeft = CopyA(pNode->mpNodeLeft, pNew);
    RBNode* pPrev = pNew;
    for (RBNode* p = pNode->mpNodeRight; p; p = p->mpNodeRight) {
        RBNode* pNodeNew = AllocA((P550*)((char*)p + 0x10));
        pNodeNew->mpNodeLeft = 0;
        pNodeNew->mpNodeRight = 0;
        pNodeNew->mpNodeParent = pPrev;
        pNodeNew->mColor = p->mColor;
        pPrev->mpNodeRight = pNodeNew;
        if (p->mpNodeLeft)
            pNodeNew->mpNodeLeft = CopyA(p->mpNodeLeft, pNodeNew);
        pPrev = pNodeNew;
    }
    return pNew;
}

// @ 0x0069ec20
bool F_ec20::f(int* io, unsigned index)
{
    if (index > 0xf4240)
        return false;
    void* p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    ((void(__thiscall*)(void*, int))(*(void***)p)[0x24 / 4])(p, 0);
    FUN_004c0410(index + 1);
    p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    int r = ((int(__thiscall*)(void*, void*, unsigned))(*(void***)p)[0x30 / 4])(p, this, index);
    bool ok = r != 0;
    if (ok) {
        *(unsigned char*)((char*)this + index) = 0;
        FUN_00932da0();
    }
    p = ((void*(__thiscall*)(void*))(*(void***)io)[0x18 / 4])(io);
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x28 / 4])(p, 0, 0);
    return ok;
}

// @ 0x0069ecc0
RBNode* Tree::AllocB(P_ecc0* src)
{
    RBNode* n = (RBNode*)EASTL_allocator_allocate(0x38, "App", 0, 0, kEastlAllocH, 0xd1);
    *(int*)((char*)n + 0x10) = src->a;
    *(int*)((char*)n + 0x14) = src->b;
    *(int*)((char*)n + 0x18) = src->c;
    FUN_0069e880(src->rest);
    return n;
}

// @ 0x0069edb0
RBNode* Tree::CopyB(RBNode* pNode, RBNode* pParent)
{
    RBNode* pNew = AllocB((P_ecc0*)((char*)pNode + 0x10));
    pNew->mpNodeLeft = 0;
    pNew->mpNodeRight = 0;
    pNew->mpNodeParent = pParent;
    pNew->mColor = pNode->mColor;
    if (pNode->mpNodeLeft)
        pNew->mpNodeLeft = CopyB(pNode->mpNodeLeft, pNew);
    RBNode* pPrev = pNew;
    for (RBNode* p = pNode->mpNodeRight; p; p = p->mpNodeRight) {
        RBNode* pNodeNew = AllocB((P_ecc0*)((char*)p + 0x10));
        pNodeNew->mpNodeLeft = 0;
        pNodeNew->mpNodeRight = 0;
        pNodeNew->mpNodeParent = pPrev;
        pNodeNew->mColor = p->mColor;
        pPrev->mpNodeRight = pNodeNew;
        if (p->mpNodeLeft)
            pNodeNew->mpNodeLeft = CopyB(p->mpNodeLeft, pNodeNew);
        pPrev = pNodeNew;
    }
    return pNew;
}

// @ 0x0069ee60
void Tree::Nuke(RBNode* pNode)
{
    while (pNode) {
        Nuke(pNode->mpNodeLeft);
        RBNode* pRight = pNode->mpNodeRight;
        FUN_d0c930((char*)pNode + 0x1c, *(void**)((char*)pNode + 0x28));
        EASTL_allocator_deallocate(pNode);
        pNode = pRight;
    }
}

// @ 0x0069f0b0
void CComSer::dtor()
{
    vt0 = g_vtbl_1408750;
    vt8 = g_vtbl_1408728;
    void* a = p54;
    if (a && *(int*)((char*)a - 4))
        EASTL_allocator_deallocate(a);
    if (p50)
        ((void(__thiscall*)(void*))(*(void***)p50)[4 / 4])(p50);
    mTree2.Nuke(mTree2.mpNodeParent);
    mTree1.Nuke(mTree1.mpNodeParent);
    vt8 = g_vtbl_13eb938;
    vt0 = g_vtbl_13ec458;
}

// @ 0x0069f160
void CComSer::reset()
{
    flag_c = 0;
    mTree1.Nuke(mTree1.mpNodeParent);
    mTree1.mpNodeLeft = (RBNode*)&mTree1.mpNodeLeft;
    mTree1.mpNodeRight = (RBNode*)&mTree1.mpNodeLeft;
    mTree1.mpNodeParent = 0;
    mTree1.mColor = 0;
    mTree1.mnSize = 0;
    mTree2.Nuke(mTree2.mpNodeParent);
    mTree2.mpNodeLeft = (RBNode*)&mTree2.mpNodeLeft;
    mTree2.mpNodeRight = (RBNode*)&mTree2.mpNodeLeft;
    mTree2.mpNodeParent = 0;
    mTree2.mColor = 0;
    mTree2.mnSize = 0;
    b4c = 0;
    b4d = 0;
    void* p = p50;
    if (p) {
        p50 = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    }
}

// @ 0x0069f840
CComSer* FUN_0069f840(CComSer* self, void* param)
{
    self->mRefCount = 0;
    self->vt8 = g_vtbl_14095cc;
    self->vt0 = g_vtbl_1408750;
    self->vt8 = g_vtbl_1408728;
    self->flag_c = 0;
    // trees initialised by reset()
    self->reset();
    return self;
}

// @ 0x0069f940
int F_eb60::f(int* key)
{
    return 0;
}

// @ 0x0069f950
ClassInfo& ClassMap::Subscript(const uint32_t& key)
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


// @ 0x0069fa60
cObjectDatabase_s0069_f950::cObjectDatabase_s0069_f950(Database* database)
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
    vt8 = g_vtbl_1408688_s0069_f950;
    vt10 = g_vtbl_1408678;
    mfPercentageCompletion0To100 = 0.0f;
    cCOMSerializer* ser = new("App", 0, 0, 0, 0) cCOMSerializer(this);
    mpCOMSerializer.Assign(ser ? (IUnk*)&ser->mI : 0);
    mpDatabase.Assign((char*)database);
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
