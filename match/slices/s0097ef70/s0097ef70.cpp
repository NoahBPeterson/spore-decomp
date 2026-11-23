// Same shape as s009515e0's AnimationCurve::GetProperty (0x00951650): fills a
// PropertyRef with the curve descriptor, this, count 1 and the slot-5 vtable call.

// @ 0x000097ef70
struct TypeDesc_0097ef70 { int x; };
extern const TypeDesc_0097ef70 kCurveDesc_0097ef70;   // 0x14438cc

struct PropertyRef_0097ef70 {
    const TypeDesc_0097ef70* type;
    void* obj;
    int count;
    int value;
};

struct AnimCurve_0097ef70 {
    virtual void pv0();
    virtual void pv1();
    virtual void pv2();
    virtual int  pv3();
    virtual void pv4();
    virtual int  f5();                                // slot 5, offset 0x14
    void GetProperty(PropertyRef_0097ef70* out);
};

void AnimCurve_0097ef70::GetProperty(PropertyRef_0097ef70* out)
{
    out->type = &kCurveDesc_0097ef70;
    out->obj = this;
    out->count = 1;
    out->value = f5();
}
