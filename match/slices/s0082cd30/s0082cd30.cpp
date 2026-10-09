// Slice s0082cd30: UI layout (de)serialization parsers.
//   cSPUIDeserializeHelper::ProcessStream, cSPUIDeserializer::Read and the
//   cSPUISerializeHelper::ParseProp / ParseProps / ParseObject recursive-descent parser,
//   plus two eastl::map<K,V>::operator[] instantiations used by that helper.
// Module flags: /O2 /MD /Gy /TP /fp:fast /arch:SSE2 /GS- (no /EHsc).
#include "types.h"
#include <new>

extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
void __cdecl operator_delete_array(void* p);     // @ 0xf47380 (operator delete[])

// ---------------------------------------------------------------------------------------------
// eastl::map<K,V> (rbtree) pieces: node layout and operator[]
// ---------------------------------------------------------------------------------------------
struct RbNodeBase {
    RbNodeBase* mpNodeRight;    // +0x00
    RbNodeBase* mpNodeLeft;     // +0x04
    RbNodeBase* mpNodeParent;   // +0x08
    uint32_t mColor;            // +0x0c
};

template<class K, class V> struct RbNode : RbNodeBase {
    K first;                    // +0x10
    V second;                   // +0x14
};

template<class K, class V> struct RbPair {
    K first; V second;
    RbPair(const K& k, const V& v) : first(k), second() { (void)v; }
};

struct RbIterBase {
    RbNodeBase* mpNode;
    RbIterBase() : mpNode(0) {}
    RbIterBase(RbNodeBase* n) : mpNode(n) {}
    RbIterBase(const RbIterBase& o) : mpNode(o.mpNode) {}
};

struct ForceTag {
    bool mValue;
    ForceTag(bool v) : mValue(v) {}
};

// D is the concrete map type (CRTP): each instantiation's DoInsertValue is declared on D so its
// original address can be annotated per instantiation.
template<class K, class V, class D> struct RbTreeMap {
    typedef RbNode<K, V> node_type;
    typedef RbPair<K, V> value_type;
    uint32_t mAllocator;        // +0x00
    RbNodeBase mAnchor;         // +0x04 (header node; root is mAnchor.mpNodeParent)
    uint32_t mnSize;            // +0x14
    uint32_t mCompare;          // +0x18

    RbIterBase lower_bound(const K& key)
    {
        node_type* pCurrent = static_cast<node_type*>(mAnchor.mpNodeParent);
        node_type* pRangeEnd = static_cast<node_type*>(&mAnchor);
        while (pCurrent) {
            if (!(pCurrent->first < key)) {
                pRangeEnd = pCurrent;
                pCurrent = static_cast<node_type*>(pCurrent->mpNodeLeft);
            } else {
                pCurrent = static_cast<node_type*>(pCurrent->mpNodeRight);
            }
        }
        return RbIterBase(pRangeEnd);
    }

    RbIterBase end() { return RbIterBase(&mAnchor); }

    RbIterBase insert(RbIterBase position, const value_type& value)
    {
        return static_cast<D*>(this)->DoInsertValue(position, value, ForceTag(false));
    }

    __forceinline V& operator[](const K& key)     // inlined into the Index wrappers below
    {
        RbIterBase itLower(lower_bound(key));
        if (itLower.mpNode == end().mpNode || key < static_cast<node_type*>(itLower.mpNode)->first) {
            itLower = insert(itLower, value_type(key, V()));
        }
        return static_cast<node_type*>(itLower.mpNode)->second;
    }
};

struct SerObject;
// Retail's mapped type for the XML-id map is a 16-byte zero-initialised record (the temporary
// value_type is {key, 0, 0, 0, 0}).
struct Slot16 {
    uint32_t a, b, c, d;
    Slot16() : a(0), b(0), c(0), d(0) {}
};
// The out-of-line eastl::map::operator[] bodies are named Index (thiscall, like the original
// operator[]) so the equivalence checker can find them by name.
struct XmlIdMap : RbTreeMap<uint32_t, Slot16, XmlIdMap> {               // mXMLIDToObject
    // eastl::rbtree::DoInsertValue (thiscall, hidden return slot, iterator by value)
    RbIterBase DoInsertValue(RbIterBase position, const value_type& value, ForceTag bForceToLeft); // 0x0082CAC0
    Slot16& Index(const uint32_t& key);                                                            // 0x0082DAE0
};
struct ObjectBindingMap : RbTreeMap<SerObject*, int, ObjectBindingMap> { // mObjectBindings
    RbIterBase DoInsertValue(RbIterBase position, const value_type& value, ForceTag bForceToLeft); // 0x0082CB90
    int& Index(SerObject* const& key);                                                             // 0x0082DB80
};

// @ 0x0082DAE0
Slot16& XmlIdMap::Index(const uint32_t& key) { return (*this)[key]; }

// @ 0x0082DB80
int& ObjectBindingMap::Index(SerObject* const& key) { return (*this)[key]; }

// ---------------------------------------------------------------------------------------------
// cSPUISerializeHelper (anonymous namespace): XML token tree -> property list parser
// ---------------------------------------------------------------------------------------------
// EA::XML token (linked list in document order; mDepth is the nesting depth).
struct Token {
    Token* mpNext;              // +0x00
    int mType;                  // +0x04 (1 = element)
    const wchar_t* mpName;      // +0x08
    int mReserved;              // +0x0c
    int mDepth;                 // +0x10
};

struct Prop;
struct SerObject {              // Pool12 record
    const wchar_t* mpClassId;   // +0x00 "clsid"
    const wchar_t* mpAttr2;     // +0x04
    Prop* mpProps;              // +0x08
};

struct Value {                  // 0x20 bytes, allocated as an array by NewValues
    char mData[0x18];
    Prop* mpStruct;             // +0x18 (nested "struct": property list)
    SerObject* mpObject;        // +0x1c (nested "object")
};

struct Prop {                   // Pool16 record
    uint32_t mId;               // +0x00 "propid"
    uint16_t mType;             // +0x04
    uint16_t mCount;            // +0x06
    Value* mpValues;            // +0x08
    Prop* mpNext;               // +0x0c
};

extern Prop g_CommentProp;      // @ 0x164E8A8 (returned for <prop propid="Comment">)
extern Prop g_EmptyProps;       // @ 0x164E8B8 (returned for an empty <struct>)

// eastl::vector<T*, sp_vector_allocator>
template<class T> struct PtrVector {
    T* mpBegin;                 // +0x00
    T* mpEnd;                   // +0x04
    T* mpCapacity;              // +0x08
    uint32_t mAllocator;        // +0x0c
    void DoInsertValue(T* position, const T& value);        // @ 0x820BB0
    void push_back(T value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// eastl::fixed_vector<Prop*, 64> used by ParseProps (stack buffer, heap on overflow)
struct PropStackVector {
    Prop** mpBegin;
    Prop** mpEnd;
    Prop** mpCapacity;
    uint32_t mOverflowAllocator;        // fixed_vector_allocator: overflow allocator state
    Prop** mpPoolBegin;                 // fixed_vector_allocator: start of the in-object buffer
    uint32_t mPoolUsed;
    Prop* mBuffer[64];
    void DoInsertValue(Prop** position, Prop* const& value);   // @ 0x82F170
    PropStackVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 64), mpPoolBegin(mBuffer) {}
    ~PropStackVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete_array(mpBegin);
    }
    void push_back(Prop* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) Prop*(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct SerializeHelper {
    char mHead[0x50];                       // +0x00 stream, token list, temp allocator, top-level set
    PtrVector<SerObject*> mAllObjects;      // +0x50
    char mGap[4];
    PtrVector<Value*> mAllValues;           // +0x64
    char mTail[0xfc - 0x74];

    const wchar_t* GetAttribute(Token* tok, const wchar_t* name);         // @ 0x82AB40
    bool ParseValue(Value* value, const wchar_t* type, Token* tok);        // @ 0x82ACB0
    uint16_t ParseTypeName(const wchar_t* type);                           // @ 0x82AFE0
    Value* NewValues(unsigned count);                                      // @ 0x82B060
    Prop* NewProp();                                                       // @ 0x82B920
    SerObject* NewObject();                                                // @ 0x82B970

    SerObject* ParseObject(Token* tok);                                    // 0x0082D910
    Prop* ParseProp(Token* tok);                                           // 0x0082D480
    Prop* ParseProps(Token* tok);                                          // 0x0082D7B0
};

// @ 0x0082D910
SerObject* SerializeHelper::ParseObject(Token* tok)
{
    if (tok->mType == 1 && wcscmp(tok->mpName, L"object") == 0) {
        SerObject* obj = NewObject();
        obj->mpClassId = GetAttribute(tok, L"clsid");
        obj->mpAttr2 = GetAttribute(tok, L"id");
        if (obj->mpClassId == 0)
            return 0;
        obj->mpProps = ParseProps(tok);
        mAllObjects.push_back(obj);
        return obj;
    }
    return 0;
}

// @ 0x0082D7B0
Prop* SerializeHelper::ParseProps(Token* tok)
{
    PropStackVector props;
    Token* child = tok->mpNext;
    int depth = tok->mDepth;
    while (child) {
        if (child->mDepth <= depth) {
            if (props.mpBegin == props.mpEnd)
                return &g_EmptyProps;
            int n = (int)(props.mpEnd - props.mpBegin);
            for (int i = 1; i < n; ++i)
                props.mpBegin[i - 1]->mpNext = props.mpBegin[i];
            return props.mpBegin[0];
        }
        if (child->mDepth == depth + 1 && child->mType == 1) {
            Prop* prop = ParseProp(child);
            if (prop == 0)
                return 0;
            if (prop->mType != 0)
                props.push_back(prop);
        }
        child = child->mpNext;
    }
    return 0;
}

// @ 0x0082D480
Prop* SerializeHelper::ParseProp(Token* tok)
{
    if (tok->mType == 1 && wcscmp(tok->mpName, L"prop") == 0) {
    const wchar_t* propId = GetAttribute(tok, L"propid");
    const wchar_t* type = GetAttribute(tok, L"type");
    const wchar_t* count = GetAttribute(tok, L"count");
    if (propId == 0 || type == 0)
        return 0;
    if (_wcsicmp(propId, L"Comment") == 0)
        return &g_CommentProp;

    Prop* prop = NewProp();
    prop->mId = wcstoul(propId, 0, 0);
    prop->mType = ParseTypeName(type);
    unsigned n = count ? wcstoul(count, 0, 0) : 1;
    prop->mCount = (uint16_t)n;
    prop->mpValues = NewValues((uint16_t)n);

    Token* child = tok->mpNext;
    int depth = tok->mDepth;
    if (child == 0 || child->mDepth <= depth) {
        // no child elements: the value is inline (at most one)
        if (prop->mCount > 1)
            return 0;
        if (prop->mCount != 0 && !ParseValue(prop->mpValues, type, tok))
            return 0;
    } else {
        int found = 0;
        int offset = 0;
        for (; child; child = child->mpNext) {
            if (child->mDepth <= depth)
                break;
            if (child->mDepth != depth + 1 || child->mType != 1)
                continue;
            if (found >= (int)prop->mCount)
                return 0;
            const wchar_t* name = child->mpName;
            bool failed;
            if (wcscmp(name, L"value") == 0) {
                failed = !ParseValue((Value*)((char*)prop->mpValues + offset), type, child);
            } else if (wcscmp(name, L"object") == 0) {
                ((Value*)((char*)prop->mpValues + offset))->mpObject = ParseObject(child);
                failed = ((Value*)((char*)prop->mpValues + offset))->mpObject == 0;
            } else if (wcscmp(name, L"struct") == 0) {
                ((Value*)((char*)prop->mpValues + offset))->mpStruct = ParseProps(child);
                failed = ((Value*)((char*)prop->mpValues + offset))->mpStruct == 0;
            } else {
                return 0;
            }
            if (failed)
                return 0;
            ++found;
            offset += 0x20;
        }
        if (found != (int)prop->mCount)
            return 0;
    }

    // register every value of the property
    for (int i = 0, n2 = prop->mCount; i < n2; ++i) {
        Value* v = (Value*)((char*)prop->mpValues + i * 0x20);
        mAllValues.push_back(v);
    }
    return prop;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// cSPUIDeserializeHelper::ProcessStream and cSPUIDeserializer::Read
// ---------------------------------------------------------------------------------------------
// EA::IO::IStream (only the slots used here)
struct IStream {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
    virtual void s20();
    virtual int GetPosition(int whence);                 // +0x24
    virtual int SetPosition(int pos, int whence);        // +0x28
    virtual int s2C();
    virtual int Read(void* dst, int size);               // +0x30
};

struct SerTypeInfo {                                     // per-type serialization record
    char mPad[0x1c];
    void (*mpFinish)(void* instance);                    // +0x1c
};
struct SerDesc {                                         // filled by ISerializable::GetDescriptor
    const SerTypeInfo* mpType;
    void* mpInstance;
    int mReserved[4];
};

struct ISerializable;
// EA::COM::IUnknown32-style reference counted object (slot 0 = AddRef, slot 1 = Release)
struct IUnknown32 {
    virtual void AddRef();
    virtual void Release();
    virtual void* s08();
    virtual ISerializable* QueryInterface(uint32_t iid);    // +0x0c
};
struct ISerializable : IUnknown32 {
    virtual void GetDescriptor(SerDesc* out);               // +0x10
};

template<class T> struct AutoRefCount {
    T* mp;
    AutoRefCount(T* p);                                     // @ 0x572660
    ~AutoRefCount() { if (mp) mp->Release(); }
    void Set(T* p);                                         // @ 0x68F5B0 (ClsF5B0::Set)
};

// fixed_vector<AutoRefCount<IUnknown32>, 128> mObjects (+0x08) of the deserialize helper
struct ObjectList {
    AutoRefCount<IUnknown32>* mpBegin;      // +0x00
    AutoRefCount<IUnknown32>* mpEnd;        // +0x04
    void Reserve(unsigned n);                               // @ 0x82C650
    void push_back(const AutoRefCount<IUnknown32>& v);      // @ 0x82CCF0
    void push_back_null();                                  // @ 0x82CCB0
};
ISerializable* interface_cast_ISerializable(AutoRefCount<IUnknown32>* slot);   // @ 0x82B900

struct ResourceManager {
    virtual void m00(); virtual void m04(); virtual void m08();
    virtual int GetResource(void* key, IUnknown32** out, int a, int b, int c, void* desc);   // +0x0c
};
ResourceManager* GetResourceManager();                       // @ 0x67DCD0
struct ObjectFactory {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0C();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1C(); virtual void m20();
    virtual IUnknown32* CreateById(uint32_t id, int a, int b);    // +0x24
};
ObjectFactory* GetObjectFactory();                           // @ 0x920090

// EA::Allocator::StackAllocator (bookmark stack for temporary parse data)
struct Bookmark {
    Bookmark* mpPrev;       // +0x00
    char* mpAddress;        // +0x04
    char* mpObjectEnd;      // +0x08
};
struct StackAllocator {
    char mPad0[4];
    char* mpCurrentBlock;       // +0x04
    char* mpCurrentBlockEnd;    // +0x08
    char* mpObjectBegin;        // +0x0c
    char* mpObjectCursor;       // +0x10
    char mPad14[0x0c];
    Bookmark* mpTopBookmark;    // +0x20
    void AllocateNewBlock(int flags);                       // @ 0x82B0D0
    void FreeToBlock(char* address);                        // @ 0x928C40
    // Pop the top bookmark (the inlined tail used when parsing ends without a fatal error).
    bool PopBookmark()
    {
        Bookmark* bm = mpTopBookmark;
        if (bm == 0)
            return false;
        char* address = bm->mpAddress;
        char* objectEnd = bm->mpObjectEnd;
        mpTopBookmark = bm->mpPrev;
        if (mpCurrentBlock < address && address < mpCurrentBlockEnd) {
            mpObjectBegin = address;
            mpObjectCursor = address;
            mpObjectCursor = objectEnd;
            return true;
        }
        FreeToBlock(address);
        mpObjectCursor = objectEnd;
        return true;
    }
};
// Scope record over the allocator; Release() (@ 0x82AAC0) rewinds the bookmark and is called
// explicitly on the failure and success exits (the end-of-stream exit pops the bookmark inline).
struct AllocScope {
    char mPad[4];
    StackAllocator* mpAlloc;
    void Release();                                         // @ 0x82AAC0
};

// cSPUISerializationAllocator: a polymorphic wrapper whose StackAllocator base sits after the vptr.
struct AllocVBase { virtual void a0(); };
struct TempAllocator : AllocVBase, StackAllocator {};

struct ImageBinder {                                        // cSPUIImageToTextureBinder (embedded at +0x264)
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0C();
    virtual void Bind(void* desc, int kind, void* key);    // +0x10
    virtual void End();                                    // +0x14
};
struct BindDesc {
    const void* mpName;         // 0x141A134
    int* mpOut;
    int mCount;
};

// RLE hit mask (UTFWin::RLEHitMask, 0x28 bytes)
struct RLEHitMask : IUnknown32 {
    char mPad[0x24];
    RLEHitMask();                                           // @ 0x82C190
    void BuildAssign(const int* size, void* data);          // @ 0x9574C0
};
void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // @ 0xf473a0

// local uint16 buffer (eastl::vector<uint16_t> filled by 0x82CC60)
struct U16Buffer {
    uint16_t* mpData;
    char mPad[0x14];
    U16Buffer() {}
    void Resize(unsigned count, const void* fill);          // @ 0x82CC60
    ~U16Buffer();                                           // @ 0x7A41A0
};

struct SerCollection {
    void NotifyBound(IUnknown32* obj);                      // @ 0x998FC0
};

struct DeserializeHelper {
    IStream* mpStream;                      // +0x000
    SerCollection* mpOutput;                // +0x004
    ObjectList mObjects;                    // +0x008 (fixed_vector<AutoRefCount<IUnknown32>,128>)
    char mObjectsStorage[0x224 - 0x10];     // +0x010 fixed storage, error message, ...
    int mFormatVersion;                     // +0x224
    char mLocalizer[0x23c - 0x228];         // +0x228
    TempAllocator mTempAlloc;               // +0x23C (StackAllocator subobject at +0x240)
    ImageBinder mImageBinder;               // +0x264
    char mTail[0x270 - 0x268];                // retail size is 0x270

    DeserializeHelper(IStream* stream, void* output);       // @ 0x82C770 (second argument is not the output collection pointer)
    ~DeserializeHelper();                                   // @ 0x82C550
    bool ProcessStream();                                   // @ 0x82CD30
    bool ProcessProperty(SerDesc* desc);                    // @ 0x82B310
};

// @ 0x0082CD30
bool DeserializeHelper::ProcessStream()
{
    StackAllocator* const pAlloc = &mTempAlloc;
    AllocScope scope;
    scope.mpAlloc = pAlloc;
    pAlloc->AllocateNewBlock(0);
    ResourceManager* const mgr = GetResourceManager();
    ObjectFactory* const factory = GetObjectFactory();

    if (mgr == 0)
        goto endOfStream;

    uint32_t magic;
    uint32_t version;
    uint16_t countBindA, countBindB, countHit, countObjects;
    uint32_t total;
    if (factory == 0 || mpStream->Read(&magic, 4) != 4)
        goto fail;
    version = 0;
    if (mpStream->Read(&version, 2) != 2)
        goto fail;
    if (mpStream->Read(&countBindA, 2) != 2)
        goto fail;
    if (mpStream->Read(&countBindB, 2) != 2)
        goto fail;
    if (mpStream->Read(&countHit, 2) != 2)
        goto fail;
    if (mpStream->Read(&countObjects, 2) != 2)
        goto fail;
    if (magic != 0xE3FE3FB8 || (uint16_t)(version - 1) > 2)
        goto fail;

    mFormatVersion = (uint16_t)version;
    total = (uint32_t)countObjects + countHit + countBindB + countBindA;
    if (total > 0x1770)
        goto fail;
    {
        ObjectList* const objects = &mObjects;
        objects->Reserve(total);

        // first group: images (binder kind 0x3FD)
        for (int i = 0; i < (int)countBindA; ++i) {
            uint32_t key[3] = { 0, 0, 0 };
            if (mpStream->Read(key, 12) != 12)
                goto fail;
            int out = 0;
            BindDesc desc;
            desc.mpOut = &out;
            desc.mpName = (const void*)0x141A134;
            desc.mCount = 1;
            mImageBinder.Bind(&desc, 0x3FD, key);
            {
                AutoRefCount<IUnknown32> ref((IUnknown32*)out);
                objects->push_back(ref);
            }
            mImageBinder.End();
        }
        // second group: textures (binder kind 0x3FE)
        for (int i = 0; i < (int)countBindB; ++i) {
            uint32_t key[3] = { 0, 0, 0 };
            if (mpStream->Read(key, 12) != 12)
                goto fail;
            int out = 0;
            BindDesc desc;
            desc.mpOut = &out;
            desc.mpName = (const void*)0x141A134;
            desc.mCount = 1;
            mImageBinder.Bind(&desc, 0x3FE, key);
            {
                AutoRefCount<IUnknown32> ref((IUnknown32*)out);
                objects->push_back(ref);
            }
            mImageBinder.End();
        }
        // third group: hit masks
        for (int i = 0; i < (int)countHit; ++i) {
            uint8_t kind = 0;
            if (mFormatVersion >= 3) {
                if (mpStream->Read(&kind, 1) != 1)
                    goto fail;
                if (kind == 1) {
                    int size[2];
                    int rleCount;
                    if (mpStream->Read(&size[0], 4) != 4 || mpStream->Read(&size[1], 4) != 4 ||
                        mpStream->Read(&rleCount, 4) != 4)
                        goto fail;
                    U16Buffer data;
                    data.Resize(rleCount, &kind);
                    if (mpStream->Read(data.mpData, rleCount * 2) != rleCount * 2)
                        goto fail;
                    RLEHitMask* mask = new("UTFWin/RLEHitMask", 0, 0, 0, 0) RLEHitMask;
                    int dims[2] = { size[0], size[1] };
                    mask->BuildAssign(dims, &data);
                    AutoRefCount<IUnknown32> ref(mask);
                    objects->push_back(ref);
                    continue;
                }
                if (kind != 0)
                    continue;
            }
            // legacy / external hit mask: a resource key
            uint32_t key[3] = { 0, 0, 0 };
            if (mpStream->Read(key, 12) != 12)
                goto fail;
            IUnknown32* resource = 0;
            struct { uint32_t a; int pad; uint32_t c; } keyDesc;
            keyDesc.a = key[0];
            keyDesc.pad = 0x19AEF76;
            keyDesc.c = key[2];
            mgr->GetResource(key, &resource, 0, 0, 0, &keyDesc);
            objects->push_back_null();
            (objects->mpEnd - 1)->Set(resource);
        }
        // fourth group: objects created through the factory by id
        for (int i = 0; i < (int)countObjects; ++i) {
            uint32_t id;
            if (mpStream->Read(&id, 4) != 4)
                goto fail;
            IUnknown32* obj = factory->CreateById(id, 0, 0);
            if (obj)
                obj->AddRef();
            objects->push_back(*(AutoRefCount<IUnknown32>*)&obj);
            if (obj)
                obj->Release();
            if (objects->mpEnd[-1].mp == 0)
                goto fail;
        }

        // property blocks: <0x5FF5 marker><u16 object index><u16 flags><count x property>
        uint16_t marker;
        uint16_t index;
        int got = mpStream->Read(&marker, 2);
        while (got == 2 && mpStream->Read(&index, 2) == 2) {
            if (marker != 0x5FF5)
                goto fail;
            if (index == 0xFFFF) {
                uint32_t trailer;
                if (mpStream->Read(&trailer, 4) != 4 || trailer != 0x1C01C047)
                    goto fail;
                int n = (int)(objects->mpEnd - objects->mpBegin);
                for (int k = 0; k < n; ++k) {
                    IUnknown32* o = objects->mpBegin[k].mp;
                    if (o) {
                        ISerializable* ser = o->QueryInterface(0xEEC58382);
                        if (ser) {
                            SerDesc desc;
                            ser->GetDescriptor(&desc);
                            if (desc.mpType->mpFinish)
                                desc.mpType->mpFinish(desc.mpInstance);
                        }
                    }
                }
                scope.Release();
                return true;
            }
            if (index >= total)
                goto fail;
            uint16_t flags;
            if (mpStream->Read(&flags, 2) != 2)
                goto fail;
            if (flags & 0x8000)
                mpOutput->NotifyBound(objects->mpBegin[index].mp);
            int propCount = flags & 0x7FFF;
            if (propCount > 200)
                goto fail;
            if (propCount > 0) {
                ISerializable* ser = interface_cast_ISerializable(&objects->mpBegin[index]);
                if (ser == 0)
                    goto fail;
                SerDesc desc;
                ser->GetDescriptor(&desc);
                for (int k = 0; k < propCount; ++k) {
                    if (!ProcessProperty(&desc))
                        goto fail;
                }
            }
            got = mpStream->Read(&marker, 2);
        }
    }

endOfStream:
    pAlloc->PopBookmark();
    return false;

fail:
    scope.Release();
    return false;
}

// ---------------------------------------------------------------------------------------------
// cSPUIDeserializer::Read
// ---------------------------------------------------------------------------------------------
struct XmlDeserializer {
    virtual uint32_t Read(IStream* stream, int a1, void* output, int a3, int a4, int a5);   // @ 0x99BE60
};

struct cSPUIDeserializer : XmlDeserializer {
    virtual uint32_t Read(IStream* stream, int a1, void* output, int a3, int a4, int a5);
};

// @ 0x0082D9F0
uint32_t cSPUIDeserializer::Read(IStream* stream, int a1, void* output, int a3, int a4, int a5)
{
    int pos = stream->GetPosition(0);
    uint32_t magic = 0;
    if (stream->Read(&magic, 4) == 4 && magic == 0xE3FE3FB8) {
        stream->SetPosition(pos, 0);
        DeserializeHelper helper(stream, output);       // 0x274 bytes on the stack
        if (!helper.ProcessStream())
            return 0x2FC50006;
        return 0;
    }
    stream->SetPosition(pos, 0);
    return XmlDeserializer::Read(stream, a1, output, a3, a4, a5);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct PAUSerObject {
    void DoInsertValue(void**, int*&); // 0x006ec4a0
};
}
