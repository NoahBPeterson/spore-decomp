// slice s006404f0: cSPPlayModeSubModePhoto helpers + small content-validation wrappers.
#include "../s00636320/s00636320.h"

int FUN_00552300(void* p);   // 0x00552300

struct cVBase {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
    virtual uint32_t GetType();               // +0x24 (index 9)
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35();
    virtual bool v36(uint32_t* out);          // +0x90 (index 36)
    virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(uint32_t a, int b);      // +0xA0 (index 40)
    virtual void v41(uint32_t a);             // +0xA4 (index 41)
    virtual void v42();                       // +0xA8 (index 42)
    virtual void v43(uint32_t a);             // +0xAC (index 43)
};

struct cXX : cVBase {
    uint32_t f4;   // +0x04
    uint32_t f8;   // +0x08
    uint32_t fc;   // +0x0C
    char pad10[0x26 - 0x10];
    uint8_t f26;   // +0x26

    void FUN_006412a0();
    void FUN_006412c0(uint32_t* src);
    void FUN_00641340(uint32_t a);
    void FUN_00641360(uint32_t a);
    void FUN_00641380(uint32_t* src, uint32_t a);
    void FUN_006413d0();
    char FUN_00641410();
    char FUN_00641470();
    char FUN_00641490();
    void FUN_006404f0();
    void FUN_00640ee0();
    void FUN_00640fa0();
    void FUN_006411b0();
};

// @ 0x006412C0
void cXX::FUN_006412c0(uint32_t* src)
{
    if (src[3] != 0) {
        f8 = ((uint32_t*)((uint32_t*)src[3])[3])[1];
        f4 = ((uint32_t*)((uint32_t*)src[3])[3])[2];
        fc = ((uint32_t*)((uint32_t*)src[3])[3])[3];
    } else {
        f4 = src[0];
        f8 = src[1];
        fc = src[2];
    }
}

// @ 0x00641340
void cXX::FUN_00641340(uint32_t a) { v40(a, 0); }

// @ 0x00641360
void cXX::FUN_00641360(uint32_t a) { v40(a, 1); }

// @ 0x00641380
void cXX::FUN_00641380(uint32_t* src, uint32_t a)
{
    f4 = src[0];
    f8 = src[1];
    fc = src[2];
    v41(a);
    v42();
    v43(a);
}

// @ 0x006413D0
void cXX::FUN_006413d0()
{
    v41(0);
    v42();
    v43(0);
}

// @ 0x00641410
char cXX::FUN_00641410()
{
    if (GetType() == 0xbcd73e89 || GetType() == 0xb8669ec9 ||
        GetType() == 0x37148141 || GetType() == 0x04f684a4)
        return 0;
    return f26;
}

// @ 0x00641470
char cXX::FUN_00641470()
{
    return FUN_00552300((char*)this + 4) != 0;
}

// @ 0x00641490
char cXX::FUN_00641490()
{
    if (FUN_00552300((char*)this + 4) == 2) {
        uint32_t local[2];
        if (v36(local) && (local[1] & local[0]) != 0xffffffff)
            return 1;
    }
    return 0;
}

// @ 0x006412A0  PARTIAL
void cXX::FUN_006412a0() {}
// @ 0x006404F0  PARTIAL
void cXX::FUN_006404f0() {}
// @ 0x00640EE0  PARTIAL
void cXX::FUN_00640ee0() {}
// @ 0x00640FA0  PARTIAL
void cXX::FUN_00640fa0() {}
// @ 0x006411B0  PARTIAL
void cXX::FUN_006411b0() {}
