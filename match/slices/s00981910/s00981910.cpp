// Same shape as s009515e0's AnimationCurve::GetProperty (0x00951650): fills a
// PropertyRef with the curve descriptor, this, count 1 and the slot-5 vtable call.

// @ 0x0000981910
struct TypeDesc_00981910 { int x; };
extern const TypeDesc_00981910 kCurveDesc_00981910;   // 0x1444794

struct PropertyRef_00981910 {
    const TypeDesc_00981910* type;
    void* obj;
    int count;
    int value;
};

struct AnimCurve_00981910 {
    virtual void pv0();
    virtual void pv1();
    virtual void pv2();
    virtual int  pv3();
    virtual void pv4();
    virtual int  f5();                                // slot 5, offset 0x14
    void GetProperty(PropertyRef_00981910* out);
};

void AnimCurve_00981910::GetProperty(PropertyRef_00981910* out)
{
    out->type = &kCurveDesc_00981910;
    out->obj = this;
    out->count = 1;
    out->value = f5();
}
