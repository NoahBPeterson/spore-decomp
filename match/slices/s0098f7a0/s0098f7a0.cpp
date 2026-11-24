// Same shape as s009515e0's AnimationCurve::GetProperty (0x00951650): fills a
// PropertyRef with the curve descriptor, this, count 1 and the slot-5 vtable call.

// @ 0x000098f7a0
struct TypeDesc_0098f7a0 { int x; };
extern const TypeDesc_0098f7a0 kCurveDesc_0098f7a0;   // 0x1445b0c

struct PropertyRef_0098f7a0 {
    const TypeDesc_0098f7a0* type;
    void* obj;
    int count;
    int value;
};

struct AnimCurve_0098f7a0 {
    virtual void pv0();
    virtual void pv1();
    virtual void pv2();
    virtual int  pv3();
    virtual void pv4();
    virtual int  f5();                                // slot 5, offset 0x14
    void GetProperty(PropertyRef_0098f7a0* out);
};

void AnimCurve_0098f7a0::GetProperty(PropertyRef_0098f7a0* out)
{
    out->type = &kCurveDesc_0098f7a0;
    out->obj = this;
    out->count = 1;
    out->value = f5();
}
