// Slice s00823e30 -- SP::cPropertyUI::ProcessSpinnerButtons (0x00823e30, 3566 bytes).
// A spinner up/down button was pressed (buttonID bit 0 set = decrement, clear = increment). Find the
// text edit mapped to the button, read its current text, add/subtract the configured increment
// according to the property's variant type, write the new text back, then re-run the matching
// Modify<Type> so the value goes into the PropertyList.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame)
// Notes preserved from the original: the decrement paths and the array ("0x8000000x") paths format
// integers with "%f", only the plain increment int/uint paths use "%d"; the array type compares are
// against 0x8000000x constants that a 16-bit type can never equal (dead code in the original too).
#include <stdlib.h>
#include <wchar.h>
#include "types.h"

extern char gEmptyString8[2];       // 0x01667bac (shared empty-string storage)
extern wchar_t gEmptyString16[2];   // 0x01667bac

struct EString8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    unsigned mAllocator;
    EString8() : mpBegin(gEmptyString8), mpEnd(gEmptyString8), mpCapacity(gEmptyString8 + 1) {}
    ~EString8() {
        if ((int)(mpCapacity - mpBegin) > 1 && mpBegin) operator delete[](mpBegin);
    }
    int sprintf(const char* fmt, ...);   // 0x00472fe0 (cdecl, this pushed first)
    int sprintf(const char* fmt, double v);   // same function, double argument
};

struct EString16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    unsigned mAllocator;
    EString16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    explicit EString16(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~EString16() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin) operator delete[](mpBegin);
    }
    const wchar_t* c_str() const { return mpBegin; }
    void RangeInitialize(const wchar_t* p);   // 0x00579a90
};

EString16 __cdecl ConvertToString16(const EString8& s);   // 0x0093c6d0
float __cdecl ParseFloatW(const wchar_t* s);              // 0x00671b80

struct IWindow {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual IWindow* GetParent();            // +0x10
    virtual void v5(); virtual void v6();
    virtual unsigned GetControlID();         // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20();
    virtual const wchar_t* GetText();        // +0x54
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void SetText(const wchar_t* text);   // +0x80
};

struct Variant {
    char pad[0x12];
    unsigned short mType;   // +0x12
};

struct PropertyList {
    virtual void v0();
    virtual int Release();   // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual Variant* GetProperty(unsigned id);   // +0x28
};

struct IPropManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void GetPropertyList(unsigned instanceID, unsigned groupID, PropertyList** out);   // +0x2c
};
namespace SP { IPropManager* PropertyManager(); }   // 0x0067de30

struct HashNode { unsigned first; IWindow* second; HashNode* next; };
struct HashIter { HashNode* mpNode; HashNode** mpBucket; };
struct HashMapU32 {
    unsigned pad0;
    HashNode** mpBucketArray;   // +4
    unsigned mnBucketCount;     // +8
    char pad1[0x20 - 0xc];
    HashIter find(const unsigned& key);   // 0x00645ed0
};

namespace SP {
class cPropertyUI {
public:
    char pad0[0xc];
    unsigned mCurrentGroupID;       // +0xc
    unsigned mCurrentInstanceID;    // +0x10
    char pad1[0x38 - 0x14];
    float mFloatIncrement;          // +0x38
    unsigned mIntIncrement;         // +0x3c
    char pad2[0x64 - 0x40];
    IWindow* mRootWindow;           // +0x64
    char pad3[0x150 - 0x68];
    HashMapU32 mSpinnerMap;         // +0x150
    void ModifyInt32(IWindow* w, bool bArray);    // 0x00820ec0
    void ModifyUInt32(IWindow* w, bool bArray);   // 0x00821260
    void ModifyFloat(IWindow* w, bool bArray);    // 0x00821600
    void ModifyVec2(IWindow* w, bool bArray);     // 0x0081f490
    void ModifyVec3(IWindow* w, bool bArray);     // 0x0081f900
    void ModifyVec4(IWindow* w, bool bArray);     // 0x0081fd70
    void ModifyRGB(IWindow* w, bool bArray);      // 0x00820210
    void ModifyRGBA(IWindow* w, bool bArray);     // 0x00820680
    void ProcessSpinnerButtons(unsigned buttonID);   // 0x00823e30
};
}

template <class T>
struct AutoRefCountT {
    T* mpObject;
    AutoRefCountT() : mpObject(0) {}
    ~AutoRefCountT() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam() {
        T* old = mpObject;
        if (old) { mpObject = 0; old->Release(); }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
};

// @ 0x00823e30
void SP::cPropertyUI::ProcessSpinnerButtons(unsigned buttonID) {
    HashIter it = mSpinnerMap.find(buttonID);
    if (it.mpNode == mSpinnerMap.mpBucketArray[mSpinnerMap.mnBucketCount]) return;
    IWindow* second = it.mpNode->second;
    IWindow* rowWindow = (second->GetParent()->GetParent() != mRootWindow)
        ? second->GetParent()->GetParent() : second->GetParent();
    unsigned id = rowWindow->GetControlID();
    AutoRefCountT<PropertyList> propList;
    PropertyManager()->GetPropertyList(mCurrentInstanceID, mCurrentGroupID, propList.AsPPTypeParam());
    Variant* variant = propList->GetProperty(id);
    EString16 text(second->GetText());
    unsigned short type = variant->mType;
    if ((buttonID & 1) == 0) {
        if (type == 0x9) {
            {
                EString8 s;
                s.sprintf("%d", mIntIncrement + (long)wcstol(text.mpBegin, 0, 0));
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyInt32(second->GetParent(), false);
            }
        } else if (type == 0xa) {
            {
                EString8 s;
                s.sprintf("%d", mIntIncrement + wcstoul(text.mpBegin, 0, 0));
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyUInt32(second->GetParent(), false);
            }
        } else if (type == 0xd) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyFloat(second->GetParent(), false);
            }
        } else if (type == 0x30) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec2(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x31) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec3(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x33) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec4(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x32) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGB(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x34) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGBA(second->GetParent()->GetParent(), false);
            }
        } else {
            unsigned t = type;
            if (t == 0x80000009) {
                {
                    EString8 s;
                    s.sprintf("%f", mIntIncrement + (long)wcstol(text.mpBegin, 0, 0));
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000a) {
                {
                    EString8 s;
                    s.sprintf("%f", mIntIncrement + wcstoul(text.mpBegin, 0, 0));
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyUInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000d) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyFloat(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000030) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec2(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000031) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec3(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000033) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec4(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000032) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGB(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000034) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) + mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGBA(second->GetParent()->GetParent(), true);
                }
            }
        }
    } else {
        if (type == 0x9) {
            {
                EString8 s;
                s.sprintf("%f", (long)wcstol(text.mpBegin, 0, 0) - mIntIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyInt32(second->GetParent(), false);
            }
        } else if (type == 0xa) {
            {
                EString8 s;
                s.sprintf("%f", wcstoul(text.mpBegin, 0, 0) - mIntIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyUInt32(second->GetParent(), false);
            }
        } else if (type == 0xd) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyFloat(second->GetParent(), false);
            }
        } else if (type == 0x30) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec2(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x31) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec3(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x33) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyVec4(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x32) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGB(second->GetParent()->GetParent(), false);
            }
        } else if (type == 0x34) {
            {
                EString8 s;
                s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                second->GetParent()->SetText(ConvertToString16(s).c_str());
                ModifyRGBA(second->GetParent()->GetParent(), false);
            }
        } else {
            unsigned t = type;
            if (t == 0x80000009) {
                {
                    EString8 s;
                    s.sprintf("%f", (long)wcstol(text.mpBegin, 0, 0) - mIntIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000a) {
                {
                    EString8 s;
                    s.sprintf("%f", wcstoul(text.mpBegin, 0, 0) - mIntIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyUInt32(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x8000000d) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyFloat(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000030) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec2(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000031) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec3(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000033) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyVec4(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000032) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGB(second->GetParent()->GetParent(), true);
                }
            } else if (t == 0x80000034) {
                {
                    EString8 s;
                    s.sprintf("%f", ParseFloatW(text.mpBegin) - mFloatIncrement);
                    second->GetParent()->SetText(ConvertToString16(s).c_str());
                    ModifyRGBA(second->GetParent()->GetParent(), true);
                }
            }
        }
    }
}
