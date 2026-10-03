// Startup module (continued from s00401000): constant vector/matrix initializers that
// return their output pointer, a packed 32-bit key builder, the /Od copies of the
// compiler's vector constructor/destructor iterators, and a routine that converts a
// block of object ids into a block of object indices.
//
// Built without optimization and without C++ EH: /Od /Ob1 /MD /Gy /TP /arch:SSE
// (frame pointer, movss float copies, no EH frame although locals have destructors).

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

// ---------------------------------------------------------------------------
// Math types
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    inline void Set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};

struct Vector4 {
    float x, y, z, w;
    inline void Set(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
};

struct Matrix3 { Vector3 m[3]; };
struct Matrix4 { Vector4 m[4]; };

// @ 0x00401200
Vector3* Vector3_SetUnitY(Vector3* v)
{
    v->x = 0.0f;
    v->y = 1.0f;
    v->z = 0.0f;
    return v;
}

// @ 0x00401240
Vector3* Vector3_SetUnitZ(Vector3* v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 1.0f;
    return v;
}

// @ 0x00401280
Vector3* Vector3_SetZero(Vector3* v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    return v;
}

// @ 0x004012C0
Vector3* Vector3_SetOne(Vector3* v)
{
    v->x = 1.0f;
    v->y = 1.0f;
    v->z = 1.0f;
    return v;
}

// @ 0x00401300
Vector4* Vector4_SetUnitX(Vector4* v)
{
    v->x = 1.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    v->w = 0.0f;
    return v;
}

// @ 0x00401350
Vector4* Vector4_SetUnitY(Vector4* v)
{
    v->x = 0.0f;
    v->y = 1.0f;
    v->z = 0.0f;
    v->w = 0.0f;
    return v;
}

// @ 0x004013A0
Vector4* Vector4_SetUnitZ(Vector4* v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 1.0f;
    v->w = 0.0f;
    return v;
}

// @ 0x004013F0
Vector4* Vector4_SetZero(Vector4* v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    v->w = 0.0f;
    return v;
}

// @ 0x00401440
Vector4* Vector4_SetOne(Vector4* v)
{
    v->x = 1.0f;
    v->y = 1.0f;
    v->z = 1.0f;
    v->w = 1.0f;
    return v;
}

// @ 0x00401490
Matrix3* Matrix3_SetIdentity(Matrix3* mat)
{
    mat->m[0].Set(1.0f, 0.0f, 0.0f);
    mat->m[1].Set(0.0f, 1.0f, 0.0f);
    mat->m[2].Set(0.0f, 0.0f, 1.0f);
    return mat;
}

// @ 0x00401540
Matrix3* Matrix3_SetZero(Matrix3* mat)
{
    mat->m[0].Set(0.0f, 0.0f, 0.0f);
    mat->m[1].Set(0.0f, 0.0f, 0.0f);
    mat->m[2].Set(0.0f, 0.0f, 0.0f);
    return mat;
}

// @ 0x004015F0
Matrix4* Matrix4_SetIdentity(Matrix4* mat)
{
    mat->m[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
    mat->m[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
    mat->m[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
    mat->m[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
    return mat;
}

// @ 0x00401720
Matrix4* Matrix4_SetZero(Matrix4* mat)
{
    mat->m[0].Set(0.0f, 0.0f, 0.0f, 0.0f);
    mat->m[1].Set(0.0f, 0.0f, 0.0f, 0.0f);
    mat->m[2].Set(0.0f, 0.0f, 0.0f, 0.0f);
    mat->m[3].Set(0.0f, 0.0f, 0.0f, 0.0f);
    return mat;
}

// @ 0x00401850
Vector4* Vector4_SetUnitW(Vector4* v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    v->w = 1.0f;
    return v;
}

// ---------------------------------------------------------------------------
// Packed 32-bit key: [31:30] kind (always 1 here), [28:24] b, [23:16] a, [15:8] c, [7:0] d
// ---------------------------------------------------------------------------
struct PackedKey {
    unsigned int d : 8;
    unsigned int c : 8;
    unsigned int a : 8;
    unsigned int b : 5;
    unsigned int reserved : 1;
    unsigned int kind : 2;
};

// @ 0x004018A0
PackedKey MakePackedKey(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    PackedKey key;
    *(unsigned int*)&key = 0;
    key.kind = 1;
    key.a = a;
    key.b = b;
    key.c = c;
    key.d = d;
    return key;
}

// ---------------------------------------------------------------------------
// Compiler-generated array helpers (`vector constructor iterator' ??_H and
// `vector destructor iterator' ??_I), written out by hand: the ctor/dtor is
// called through a __thiscall pointer, modeled as a pointer to member.
// ---------------------------------------------------------------------------
struct ArrayElement { };
typedef void (ArrayElement::*ElementCtorDtor)();

// @ 0x00401930
void __stdcall VectorConstructorIterator(void* p, unsigned int size, int count, ElementCtorDtor ctor)
{
    while (--count >= 0) {
        (((ArrayElement*)p)->*ctor)();
        p = (char*)p + size;
    }
}

// @ 0x00401960
void __stdcall VectorDestructorIterator(void* p, unsigned int size, int count, ElementCtorDtor dtor)
{
    p = (char*)p + size * count;
    while (--count >= 0) {
        p = (char*)p - size;
        (((ArrayElement*)p)->*dtor)();
    }
}

// ---------------------------------------------------------------------------
// Typed data blocks (count + strided element buffer + ref-counted owner)
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct RefPtr {
    IRefCounted* mpObject;
    RefPtr(IRefCounted* p);  // 0x0041CC20
    ~RefPtr() { if (mpObject) mpObject->Release(); }
};

struct DataBlock {
    int mnCount;
    char* mpData;
    uint16_t mnElementSize;
    uint16_t mnStride;
    RefPtr mpOwner;

    DataBlock(int count, uint16_t elementSize, uint16_t stride)
        : mnCount(count), mpData(0), mnElementSize(elementSize), mnStride(stride), mpOwner(0) {}
    DataBlock(const DataBlock& other);  // 0x00401B80

    uint32_t& At(int i) { return *(uint32_t*)(mpData + mnStride * i); }
};

struct TypedBlock : DataBlock {
    TypedBlock(const DataBlock& b) : DataBlock(b) {}
};

struct BlockKey {
    int mType;
    int mIndex;
    int mA;
    int mB;
    BlockKey(int type, int index, int a, int b) : mType(type), mIndex(index), mA(a), mB(b) {}
};

struct BlockEntry {  // 0x20 bytes
    BlockKey mKey;
    DataBlock mBlock;
    BlockEntry(int type, int index, int a, int b, const DataBlock& block)
        : mKey(type, index, a, b), mBlock(block)
    {
        int unused1;  // stand-ins for two dead stack slots in the original
        int unused2;
    }
};

struct BlockArray {
    BlockEntry* mpBegin;
    void push_back(const BlockEntry& e);  // 0x0041F7D0
};

struct BlockContainer {
    int mUnk0;
    int mUnk4;
    BlockArray mEntries;
};

int FindBlock(BlockContainer* c, int type, int index, int a, int b);  // 0x0071DDC0
void AllocateBlock(DataBlock* block);                                 // 0x00720070

// ---------------------------------------------------------------------------
// Objects looked up by id
// ---------------------------------------------------------------------------
struct Thing {
    uint32_t pad[2];
    uint32_t mFlags;
    void* Cast(uint32_t typeId);  // 0x011EDCF0
    int HasIndex() const { return (mFlags & 8) != 0; }
};

struct Object {
    uint32_t pad;
    Thing* mpThing;
};

struct IObjectManager {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24();
    virtual Object* GetObject(uint32_t id);  // slot 0x28
};
IObjectManager* GetObjectManager();  // 0x0067DD70

inline uint32_t* GetIndexComponent(Thing* t)
{
    if (t && t->HasIndex())
        return (uint32_t*)t->Cast(0x20f);
    return 0;
}

// Reads block (0x15,0,6,8) of object ids, maps every id to its object's index
// (0xFFFFFFFF if none) and appends the result as block (0x14,0,6,8).
// @ 0x00401990
void ConvertObjectIdsToIndices(BlockContainer* container)
{
    int i0 = FindBlock(container, 0x15, 0, 6, 8);
    if (i0 < 0)
        return;
    TypedBlock a(container->mEntries.mpBegin[i0].mBlock);
    DataBlock b(a.mnCount, 4, 4);
    AllocateBlock(&b);
    for (int i = 0, n = a.mnCount; i < n; ++i) {
        uint32_t handle = a.At(i);
        Object* object = GetObjectManager()->GetObject(handle);
        uint32_t* comp = GetIndexComponent(object->mpThing);
        uint32_t value = comp ? *comp : 0xffffffff;
        b.At(i) = value;
    }
    container->mEntries.push_back(BlockEntry(0x14, 0, 6, 8, b));
}
