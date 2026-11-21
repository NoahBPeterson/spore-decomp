// Slice s007fd9d0: fifteen UTFWin property accessors of the same shape as AnimationCurve::GetProperty
// (0x00951650, Animation.cpp): each fills a property reference with its class's property descriptor,
// the object, a count of one and the value its fifth virtual returns. The classes differ only in the
// descriptor; the descriptors are named by their own addresses.
// Flags: as AnimationCurve::GetProperty (/O2 /MD /Gy /TP /arch:SSE /fp:fast)

struct PropertyDesc;

struct PropertyRef {
    const PropertyDesc* type;  // +0x0
    void* obj;                 // +0x4
    int count;                 // +0x8
    int value;                 // +0xc
};

// A UTFWin object that exposes one property: its value comes from vtable slot 0x14.
template <const PropertyDesc* Desc>
struct SinglePropertyObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual int GetValue();  // slot 0x14
    virtual void GetProperty(PropertyRef* out);
};

template <const PropertyDesc* Desc>
void SinglePropertyObject<Desc>::GetProperty(PropertyRef* out)
{
    out->type = Desc;
    out->obj = this;
    out->count = 1;
    out->value = GetValue();
}

extern const PropertyDesc g_PropertyDesc_01415dd0;
extern const PropertyDesc g_PropertyDesc_01415df0;
extern const PropertyDesc g_PropertyDesc_01415e10;
extern const PropertyDesc g_PropertyDesc_01415f84;
extern const PropertyDesc g_PropertyDesc_01416480;
extern const PropertyDesc g_PropertyDesc_014164a0;
extern const PropertyDesc g_PropertyDesc_01416580;
extern const PropertyDesc g_PropertyDesc_014194b4;
extern const PropertyDesc g_PropertyDesc_01419b14;
extern const PropertyDesc g_PropertyDesc_0141ad20;
extern const PropertyDesc g_PropertyDesc_014405f4;
extern const PropertyDesc g_PropertyDesc_01440b08;
extern const PropertyDesc g_PropertyDesc_01440f88;
extern const PropertyDesc g_PropertyDesc_014415e4;
extern const PropertyDesc g_PropertyDesc_01441d3c;

// one instance per class (manifest rows name each)
template struct SinglePropertyObject<&g_PropertyDesc_01415dd0>;  // GetProperty at 0x007fd9d0
template struct SinglePropertyObject<&g_PropertyDesc_01415df0>;  // GetProperty at 0x007fda00
template struct SinglePropertyObject<&g_PropertyDesc_01415e10>;  // GetProperty at 0x007fda50
template struct SinglePropertyObject<&g_PropertyDesc_01415f84>;  // GetProperty at 0x007fe040
template struct SinglePropertyObject<&g_PropertyDesc_01416480>;  // GetProperty at 0x007ff740
template struct SinglePropertyObject<&g_PropertyDesc_014164a0>;  // GetProperty at 0x007ff770
template struct SinglePropertyObject<&g_PropertyDesc_01416580>;  // GetProperty at 0x007ff9c0
template struct SinglePropertyObject<&g_PropertyDesc_014194b4>;  // GetProperty at 0x0081ae60
template struct SinglePropertyObject<&g_PropertyDesc_01419b14>;  // GetProperty at 0x0081d4e0
template struct SinglePropertyObject<&g_PropertyDesc_0141ad20>;  // GetProperty at 0x008340d0
template struct SinglePropertyObject<&g_PropertyDesc_014405f4>;  // GetProperty at 0x009575b0
template struct SinglePropertyObject<&g_PropertyDesc_01440b08>;  // GetProperty at 0x00960520
template struct SinglePropertyObject<&g_PropertyDesc_01440f88>;  // GetProperty at 0x00964860
template struct SinglePropertyObject<&g_PropertyDesc_014415e4>;  // GetProperty at 0x009681e0
template struct SinglePropertyObject<&g_PropertyDesc_01441d3c>;  // GetProperty at 0x0096bcd0
