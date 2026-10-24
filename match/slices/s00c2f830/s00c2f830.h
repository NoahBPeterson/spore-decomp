// Slice s00c2f830 — SP mission classes: constructors/destructors and the
// mission text getters.  All functions are __thiscall members of the SP
// mission hierarchy (ret 4 / ret 0 with ECX = this).
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#pragma once

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// Reference-counted object with the two leading vtable slots the whole engine
// uses: slot 0 = AddRef, slot 1 = Release.
// ---------------------------------------------------------------------------
struct RefObj {
    virtual int AddRef();        // +0x00
    virtual int Release();       // +0x04
};
// The AddRef/Release code paths in the original operate on the object's ref
// count at +0x08, so the derived objects place it there.
struct RefCounted {
    virtual int AddRef();        // +0x00
    virtual int Release();       // +0x04
    u32 mRefCount;               // +0x08
};

// ---------------------------------------------------------------------------
// EA::AutoRefCount<T> as used by the property system: the out-parameter form
// releases any current object before returning the raw slot.
// ---------------------------------------------------------------------------
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T*& AsOutParam()
    {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return mpObject;
    }
    operator T*() const { return mpObject; }
};

// ---------------------------------------------------------------------------
// SP::Property — a property value fetch returns a pointer into the variant.
// ---------------------------------------------------------------------------
struct Property {
    void*    mpData;     // +0x00
    u32      pad04[3];
    unsigned short mnFlags;  // +0x10
    unsigned short mnType;   // +0x12
    int* GetInt();           // 0x0041e990  Property::GetInt
    u32* GetUInt();          // 0x0041ea00  Property::GetUInt
    float* GetFloat();       // 0x0041ea70  SP::GetPropertyAsFloat
};

// A generic property container (property list / property object).
struct PropObj {
    virtual void v00();                            // +0x00
    virtual void Release();                        // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual bool GetProperty(u32 key, Property** out);  // +0x24
};

// ---------------------------------------------------------------------------
// SP::cString — the engine's localised-string wrapper (0x14 bytes).
// ---------------------------------------------------------------------------
struct cString {
    cString();                                                  // 0x006b5060
    cString(u32 table, u32 instance, const wchar_t* fallback);   // 0x006b5770
    ~cString();                                                 // 0x006b5240
    const wchar_t* GetText();                                   // 0x006b55c0
    u32 mTable; u32 mInstance; u32 pad08; u32 pad0c; u32 pad10;
};

// eastl wide-string assign (this in ECX), used for the ~Goal style texts.
void WString_Assign(void* s, const wchar_t* begin, const wchar_t* end);  // 0x00423650
void WString_Append(void* s, const wchar_t* text);                       // 0x005c3d90

// ---------------------------------------------------------------------------
// External entry points.
// ---------------------------------------------------------------------------
void* SP_PropertyManager();                       // 0x0067de30  SP::PropertyManager
void* EA_ResourceMan_GetManager();                // 0x0067dcd0  GetManager
