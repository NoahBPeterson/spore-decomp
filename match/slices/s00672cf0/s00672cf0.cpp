// Slice s00672cf0: copy constructor of a record holding a fixed wide string (32 wchar_t of
// in-place storage, EASTL fixed_string layout) followed by one 32-bit field.

struct FixedPoolAllocator_s0067_2cf0 {
    int      mOverflow;    // +0x0c in the string
    wchar_t* mpPoolBegin;  // +0x10 in the string

    FixedPoolAllocator_s0067_2cf0(wchar_t* pool) : mpPoolBegin(pool) {}
};

struct FixedWString_s0067_2cf0 {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    FixedPoolAllocator_s0067_2cf0 mAllocator;  // +0x0c
    wchar_t  mBuffer[32];  // +0x14

    FixedWString_s0067_2cf0() : mAllocator(mBuffer)
    {
        mpCapacity = mAllocator.mpPoolBegin + 32;
        mpEnd = mAllocator.mpPoolBegin;
        mpBegin = mAllocator.mpPoolBegin;
        *mpBegin = 0;
    }

    void assign(const wchar_t* first, const wchar_t* last);  // 0x00672750
};

struct Record_s0067_2cf0 {
    FixedWString_s0067_2cf0 mName;  // +0x00
    int mValue;                     // +0x54

    Record_s0067_2cf0(const Record_s0067_2cf0& other);
};

// @ 0x00672cf0
Record_s0067_2cf0::Record_s0067_2cf0(const Record_s0067_2cf0& other)
{
    mName.assign(other.mName.mpBegin, other.mName.mpEnd);
    mValue = other.mValue;
}
