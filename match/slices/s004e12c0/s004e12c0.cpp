// w1g1 slice s004e12c0 -- /Od functional-match helpers around the species
// summarizer: the two property getter wrappers and the EASTL container
// instantiations that surround them.
//
// Flags: /Od /Ob1 /MD /Gy /TP (frame pointer, no C++ EH, x87 for float args).

typedef unsigned int uint32_t;

// A property-holder whose GetProperty virtual lives at vtable offset 0x24
// (index 9), called as bool GetProperty(int key, void* out).
struct PropertyHolder {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual bool GetProperty(int key, void* out); // +0x24
};

// Address resolvers (different element types).
void* __fastcall ResolveIntValue(int v);    // 0x004e41c0
void* __fastcall ResolveFloatValue(int v);  // 0x004e4230

// @ 0x004e1c30
// SP::cTribeTool::GetTutorialToolPrice: look up an int property, fall back to
// the caller-supplied default when the holder is null or the key is absent.
int GetTutorialToolPrice(PropertyHolder* pHolder, int key, int defaultValue)
{
    int value;
    int dummy;
    if (pHolder != 0 && pHolder->GetProperty(key, &value))
        return *(int*)ResolveIntValue(value);
    return defaultValue;
}

// @ 0x004e1c70
// SP::GetPropertyT<float>: same lookup for a float property (x87 return).
float GetPropertyFloat(PropertyHolder* pHolder, int key, float defaultValue)
{
    float value;
    int dummy;
    if (pHolder != 0 && pHolder->GetProperty(key, &value))
        return *(float*)ResolveFloatValue(*(int*)&value);
    return defaultValue;
}

// ---------------------------------------------------------------------------
// EASTL container instantiations and property helpers (skeletons).
// ---------------------------------------------------------------------------

// @ 0x004e12c0
// hashtable<ResourceKey,cSpeciesProfile*>::DoInsertValue node/slot insertion.
void* HashTableResourceKeyDoInsertValue(void* self, void* result, void* key)
{
    (void)self; (void)result; (void)key;
    return result;
}

// @ 0x004e14e0
// hashtable<ResourceKey,...>::find.
void* HashTableResourceKeyFind(void* self, void* result, void* key)
{
    (void)self; (void)result; (void)key;
    return result;
}

// @ 0x004e1780
// vector<FunctionalMatch::Constraint>::destroy-range (dtor loop).
void ConstraintVectorDestroy(void* self)
{
    (void)self;
}

// @ 0x004e17e0
// vector<FunctionalMatch::Constraint>::reserve.
void ConstraintVectorReserve(void* self, uint32_t n)
{
    (void)self; (void)n;
}

// @ 0x004e18e0
// vector<FunctionalMatch::Constraint>::push_back.
void ConstraintVectorPushBack(void* self, void* value)
{
    (void)self; (void)value;
}

// @ 0x004e1a20
// rbtree/hashtable iterator helper.
void* ContainerIteratorHelper(void* self)
{
    (void)self;
    return 0;
}

// @ 0x004e1a90
// rbtree insert-or-assign helper.
void* ContainerInsertHelper(void* self, void* value)
{
    (void)self; (void)value;
    return 0;
}
