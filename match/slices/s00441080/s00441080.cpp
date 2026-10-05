// SP::cSPEditorBlock — list update + model creation (unoptimized /Od /Ob1).
#include "types.h"

namespace SP {

struct Elem { void* p; char pad[0x1C]; };   // 0x20-byte element

struct Property;      // property object (type field at +0x12)
struct PropertyList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8();
    virtual bool GetProperty(int id, Property** out);   // vtbl +0x24
};

struct cSPEditorBlock {
    char  pad0[0x4C8];
    Elem* begin48;     // +0x4C8
    Elem* end4cc;      // +0x4CC

    void F41080();                                     // 0441080
    void F40e60(void* p);                              // 0440E60
    void F410d0(int idx, int a3, int a4, int a5, int a6, int a7, int a8, int a9,
                int a10, int a11);                      // 04410D0
};

bool  GetBoolProperty(void* props, int id, uint8_t* out);     // 00407190
void  GetFloatProperty(void* props, int id, float* out);      // 0040CF10
void  GetPropertyAsKey(void* props, int id, void* out);       // 006A1250
void  GetPropertyAsKeyInstance(void* props, int id, void* out); // 006A12A0
uint8_t Property_GetBool(Property* p);                        // 0041E920
void* OperatorNewEditor(int size, const char* tag, int, int, int, int);  // 00F473A0
void* Sub_483D40(void* p);                                    // 00483D40
int   Sub_67DD80(void* a, int b, int c, int d, int e, int f, int g, int h, int i); // 0067DD80 (ModelManager)
void  Sub_4849E0(void* a, int b, int c, int d, int e, int f, int g, int h, int i); // 004849E0

// @ 0x00441080
void cSPEditorBlock::F41080()
{
    Elem* it = begin48;
    Elem* end = end4cc;
    for (; it != end; it++) {
        F40e60(it->p);
    }
}

// @ 0x004410D0
void cSPEditorBlock::F410d0(int idx, int a3, int a4, int a5, int a6, int a7, int a8,
                            int a9, int a10, int a11)
{
    PropertyList* props = *(PropertyList**)((char*)this + 0x0C);
    uint8_t hasProp = (uint8_t)(props->GetProperty(a5, 0) ? 1 : 0);
    uint8_t useDefault = 1;
    GetBoolProperty(props, a4, &useDefault);
    if (hasProp == 0 && useDefault == 0) return;

    float f0 = 0.0f, f1 = 0.0f, f2 = 1.0f;
    uint8_t flag = 0;
    uint8_t tag = 1;
    int key0 = (int)0xA659762B, key1 = 0x0C1EF506;
    GetPropertyAsKeyInstance(props, a11, &key1);
    if (hasProp != 0) {
        int k[3] = {0, 0, 0};
        GetPropertyAsKey(props, a5, k);
        if (k[0] != 0x2CA33BDB && k[0] != 0) {
            key1 = k[0];
            if (k[1] != 0) key0 = k[1];
            GetFloatProperty(props, a6, &f0);
            GetFloatProperty(props, a7, &f1);
            GetFloatProperty(props, a8, &f2);
            GetBoolProperty(props, a9, &flag);
            tag = 0;
            Property* prop = 0;
            if (props != 0 && props->GetProperty(a10, &prop) && *(short*)((char*)prop + 0x12) == 1) {
                tag = Property_GetBool(prop);
            }
        }
    }
    void* obj = OperatorNewEditor(0x9C, "Editor", 0, 0, 0, 0);
    void* model = obj ? Sub_483D40(obj) : 0;
    int* slot = (int*)((char*)this + 0x154 + idx * 4);
    if (model != (void*)*slot) {
        void* old = (void*)*slot;
        if (model != 0) { }
        *slot = (int)model;
        if (old != 0) { }
    }
    int mm = Sub_67DD80(this, key1, a3, key0, (int)f0, (int)f1, (int)f2, flag, 1);
    Sub_4849E0((void*)mm, (int)this, key1, a3, key0, (int)f0, (int)f1, (int)f2, flag);
    *(uint8_t*)(*(int*)((char*)this + 0x154 + idx * 4) + 0x92) = tag;
}

} // namespace SP
