// Slice s0045c350: Collada export writers built on the string writer FUN_0045cd90,
// plus a date formatter.  /Od /Ob1 /MD /Gy /TP.
#include "types.h"

// ---- out-of-slice / masked callees ----
extern "C" int Sprintf8(char* buf, const char* fmt, ...);        // 0x938470
extern "C" void Sprintf8V(char* buf, unsigned int n, const char* fmt, void* args); // 0x938400 used by ResetAndFormat
extern "C" void WriterFmt(int out, const char* fmt, ...);        // 0x45cd90 (defined below)
void WriterStr(int out, const char* s);                          // 0x45cd40 (defined below)
void WriteVec3Array(int out, const char* name, const float* data, unsigned int count);   // 0x45ce80
void WriteVec2Array(int out, const char* name, const float* data, unsigned int count);   // 0x45cf40
void WriteNameArray(int out, const char* name, const int* data, unsigned int count);     // 0x45cfe0

// =====================================================================
// writer object: vtbl slot 0x38 = Write(ptr, len)
// =====================================================================
struct IByteSink {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual unsigned char Write(const char* p, int len);   // +0x38 (slot 14)
};

// =====================================================================
// @ 0x45cd40  write a NUL-terminated string through the sink
// =====================================================================
void WriterStr(int out, const char* s)
{
    const char* p = s;
    const char* start = p + 1;
    char c;
    do {
        c = *p++;
    } while (c != 0);
    int len = (int)(p - start);
    ((IByteSink*)out)->Write(s, len);
    return;
}

// =====================================================================
// BigStr: SSO string with inline buffer at +0x14 (used by WriterFmt)
// =====================================================================
struct BigStr {
    char* begin;
    char* end;
    char* cap;
    char  pad[8];
    char  buf[0x300];
    void  Ctor();                                   // 0x45d6f0
    void  ResetAndFormat(const char* fmt, void* args); // 0x45da50
    void  ReleaseHeap();                            // 0x429300
};

// =====================================================================
// @ 0x45cd90  formatted write through the sink (varargs)
// =====================================================================
int WriterFmtSink(int out, const char* fmt, ...)
{
    BigStr s;
    s.Ctor();
    void* args = (void*)(&fmt + 1);
    s.ResetAndFormat(fmt, args);
    unsigned char r = ((IByteSink*)out)->Write(s.begin, (int)(s.end - s.begin));
    s.ReleaseHeap();
    return r;
}

// =====================================================================
// @ 0x45ce20  format an EA::DateTime as an ISO-8601 UTC timestamp
// =====================================================================
struct DateTime {
    int GetParameter(int which);   // 0x92df80 thiscall
};

void FormatDate(char* out, DateTime* t)
{
    Sprintf8(out, "%04d-%02d-%02dT%02d:%02d:%02dZ",
             t->GetParameter(1), t->GetParameter(2), t->GetParameter(6),
             t->GetParameter(8), t->GetParameter(9), t->GetParameter(10));
    return;
}

// =====================================================================
// @ 0x45ce80  write a Vector3 float array source block
// =====================================================================
void WriteVec3Array(int out, const char* name, const float* data, unsigned int count)
{
    WriterFmt(out, "      <source id=\"%s\">\n        <float_array id=\"%s-array\" count=\"%d\">\n          ",
              name, name, count * 3);
    for (unsigned int i = 0; i < count; i = i + 1) {
        WriterFmt(out, "%f %f %f ", data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
    }
    WriterFmt(out,
        "\n        </float_array>\n        <technique_common>\n          <accessor source=\"#%s-array\" count=\"%d\" stride=\"3\">\n            <param name=\"X\" type=\"float\"/>\n            <param name=\"Y\" type=\"float\"/>\n            <param name=\"Z\" type=\"float\"/>\n          </accessor>\n        </technique_common>\n      </source>\n",
        name, count);
    return;
}

// =====================================================================
// @ 0x45cf40  write a Vector2 float array source block
// =====================================================================
void WriteVec2Array(int out, const char* name, const float* data, unsigned int count)
{
    WriterFmt(out, "      <source id=\"%s\">\n        <float_array id=\"%s-array\" count=\"%d\">\n          ",
              name, name, count << 1);
    for (unsigned int i = 0; i < count; i = i + 1) {
        WriterFmt(out, "%f %f ", data[i * 2], data[i * 2 + 1]);
    }
    WriterFmt(out,
        "\n        </float_array>\n        <technique_common>\n          <accessor source=\"#%s-array\" count=\"%d\" stride=\"2\">\n            <param name=\"S\" type=\"float\"/>\n            <param name=\"T\" type=\"float\"/>\n          </accessor>\n        </technique_common>\n      </source>\n",
        name, count);
    return;
}

// =====================================================================
// @ 0x45cfe0  write a bone-name (Name_array) source block
// =====================================================================
void WriteNameArray(int out, const char* name, const int* data, unsigned int count)
{
    WriterFmt(out, "    <source id=\"%s\">\n      <Name_array id=\"%s-array\" count=\"%d\">\n        ",
              name, name, count);
    for (unsigned int i = 0; i < count; i = i + 1) {
        WriterFmt(out, "%s%d ", data[i], i);
    }
    WriterFmt(out,
        "\n      </Name_array>\n      <technique_common>\n        <accessor source=\"#%s-array\" count=\"%d\" stride=\"1\">\n          <param name=\"JOINT\" type=\"Name\"/>\n        </accessor>\n      </technique_common>\n    </source>\n",
        name, count);
    return;
}

// =====================================================================
// @ 0x45d060  write the inverse-bind-pose matrix array  (PARTIAL)
// =====================================================================
void WriteInvBindPose(int out, const char* name, const void* mats, unsigned int count)
{
    (void)out; (void)name; (void)mats; (void)count;
    return;
}

// =====================================================================
// @ 0x45c350  top-level Collada scene writer  (PARTIAL)
// =====================================================================
int WriteColladaScene(int out, void* model)
{
    (void)out; (void)model;
    return 0;
}
