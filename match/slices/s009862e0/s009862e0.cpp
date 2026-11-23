// Same shape as s009515e0's AnimationCurve::GetProperty (0x00951650): fills a
// PropertyRef with the curve descriptor, this, count 1 and the slot-5 vtable call.

// @ 0x00009862e0
struct TypeDesc_009862e0 { int x; };
extern const TypeDesc_009862e0 kCurveDesc_009862e0;   // 0x1444e30

struct PropertyRef_009862e0 {
    const TypeDesc_009862e0* type;
    void* obj;
    int count;
    int value;
};

struct AnimCurve_009862e0 {
    virtual void pv0();
    virtual void pv1();
    virtual void pv2();
    virtual int  pv3();
    virtual void pv4();
    virtual int  f5();                                // slot 5, offset 0x14
    void GetProperty(PropertyRef_009862e0* out);
};

void AnimCurve_009862e0::GetProperty(PropertyRef_009862e0* out)
{
    out->type = &kCurveDesc_009862e0;
    out->obj = this;
    out->count = 1;
    out->value = f5();
}
