// Slice s007e27a0 -- container reset: clear the contents through
// 0x0093dc70(begin, end), zero the count, then release the heap buffer through
// operator delete (0x00f47380) when the capacity flag is above 1.  The callee
// gets ECX = the container (thiscall, ret 0), so this is a member function
// called with the object in ECX.

struct Container
{
    void*    m00;             // +0x00
    void*    mpBegin;         // +0x04
    unsigned mCapacityFlag;   // +0x08
    int      mCount;          // +0x0c

    void Reset();             // 0x007e27a0 (ECX = this, ret)
};

struct ContainerClearStub { void Clear(void* begin, void* end); };  // 0x0093dc70
void* operator_delete(void* p);                                     // 0x00f47380

// @ 0x007e27a0
void Container::Reset()
{
    ((ContainerClearStub*)this)->Clear(mpBegin, (void*)mCapacityFlag);
    mCount = 0;
    if (mCapacityFlag > 1u)
        operator_delete(mpBegin);
}
