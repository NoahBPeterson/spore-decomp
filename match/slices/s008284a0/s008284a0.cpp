// Slice s008284a0: assignment operator of a record holding an id, a ref-counted pointer
// (intrusive_ptr semantics), a string and a trailing 32-bit field.

struct IRefObj_s0082_84a0 {
    virtual int AddRef();
    virtual int Release();
};

struct RefPtr_s0082_84a0 {
    IRefObj_s0082_84a0* mpObject;

    RefPtr_s0082_84a0& operator=(const RefPtr_s0082_84a0& ip) { return operator=(ip.mpObject); }

    RefPtr_s0082_84a0& operator=(IRefObj_s0082_84a0* pObject)
    {
        if (pObject != mpObject) {
            IRefObj_s0082_84a0* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct String_s0082_84a0 {
    char pad00[0x14];

    String_s0082_84a0& operator=(const String_s0082_84a0& x);  // 0x00542b80
};

struct Record_s0082_84a0 {
    int mId;                       // +0x00
    RefPtr_s0082_84a0 mpObject;    // +0x04
    String_s0082_84a0 mName;       // +0x08
    int mValue;                    // +0x1c

    Record_s0082_84a0& operator=(const Record_s0082_84a0& x);
};

// @ 0x008284a0
Record_s0082_84a0& Record_s0082_84a0::operator=(const Record_s0082_84a0& x)
{
    mId = x.mId;
    mpObject = x.mpObject;
    mName = x.mName;
    mValue = x.mValue;
    return *this;
}
