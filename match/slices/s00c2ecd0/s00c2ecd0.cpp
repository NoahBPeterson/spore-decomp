// Slice s00c2ecd0: reads a 32-bit property (id 0xe2da314e, type 10) from the owner's property
// list, or 0 when there is no list or no such property.

struct Property_s00c2_ecd0 {
    char pad00[0x12];
    unsigned short mType;  // +0x12

    unsigned int* GetValueUInt32();  // 0x0041ea00
};

struct PropertyList_s00c2_ecd0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(unsigned int id, Property_s00c2_ecd0*& out);  // slot 0x24
};

struct Owner_s00c2_ecd0 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    virtual PropertyList_s00c2_ecd0* GetLink();  // slot 0xc0

    unsigned int GetFlagsProperty();
};

// @ 0x00c2ecd0
unsigned int Owner_s00c2_ecd0::GetFlagsProperty()
{
    if (PropertyList_s00c2_ecd0* list = GetLink()) {
        Property_s00c2_ecd0* prop;
        unsigned int value = 0;
        if (list->GetProperty(0xe2da314e, prop) && prop->mType == 10)
            value = *prop->GetValueUInt32();
        return value;
    }
    return 0;
}
