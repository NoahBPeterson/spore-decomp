// Slice s00946dc0 -- EA::Internet: multipart/form-data post-body stream + HTTP date parsing.
#ifndef S00946DC0_H
#define S00946DC0_H

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

extern "C" {
__declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);
__declspec(dllimport) int __cdecl atoi(const char*);
__declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
__declspec(dllimport) __int64 __cdecl _mktime64(struct tm*);
}

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
void  __cdecl operator delete(void*) throw();
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);

namespace eastl {

extern char gEmptyString[];                      // 0x01667bac
extern const char kEastlPathAddr[];              // 0x013ebb38

struct StrStub {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAlloc;

    StrStub() {}
    StrStub(const StrStub& other);               // 0x0057cb10
    StrStub(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first);
        char* p;
        if (n + 1 < 2) {
            p = (char*)0x1667bac;
            mpCapacity = p + 1;
        } else {
            p = (char*)operator new(n + 1, "EASTL", 0, 0, (int)kEastlPathAddr, 0xd1);
            mpCapacity = p + n + 1;
        }
        memcpy(p, first, n);
        mpBegin = p;
        mpEnd = p + n;
        *mpEnd = 0;
    }

    void assign(const char* first, const char* last);     // 0x00454cb0
    void append(const char* first, const char* last);     // 0x00455d60
    void RangeInitialize(unsigned n);                      // 0x00475ab0
    unsigned find(char c, unsigned pos) const;             // 0x00607580
};

struct StrDtor {
    void Destroy();                              // 0x00530670
};

inline void StrStubRelease(StrStub* s) {
    if (s->mpCapacity - s->mpBegin > 1 && s->mpBegin)
        operator delete(s->mpBegin);
}

}

struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
};

struct StreamNode : ListNode {
    void* mpStream;      // +8
};

struct ListBase {
    void DoClear();      // 0x0060c4a0
};

struct MemoryStream {
    void Construct(const char* name);            // 0x0093bd50
    void SetOption(int option, float value);     // 0x0093bb40
};

struct StreamChild {
    void Construct(void* stream, unsigned start, unsigned len);   // 0x0093b7d0
};

struct StrVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void PushEmpty();                            // 0x009473a0
    void DoInsertValue(char* pos, void* value);  // 0x00554820
};

struct AutoRefCountIStream {
    void* mpObject;
    AutoRefCountIStream(void* p);                // 0x00572620
};

class HTTPMultipartFormDataPostBodyStream {
public:
    void*      mpVtbl;        // +0x00
    void*      mpVtbl2;       // +0x04
    long       mnRefCount;    // +0x08
    ListNode   mListAnchor;   // +0x0c
    unsigned   mListSize;     // +0x14
    eastl::StrStub msBoundary;// +0x18
    ListNode*  mReadItr;      // +0x28
    long       mnPosition;    // +0x2c
    unsigned   mnSize;        // +0x30
    int        mnState;       // +0x34
    bool       mbFinal;       // +0x38
    int        mLastDataType; // +0x3c
    unsigned   mnTextStart;   // +0x40
    void*      mpMemStream;   // +0x44

    HTTPMultipartFormDataPostBodyStream();       // 0x00946dc0
    ~HTTPMultipartFormDataPostBodyStream();      // 0x00946f70
    bool Close();                                // 0x00946f10
    bool GetContentTypeString(eastl::StrStub* out);   // 0x00946fe0
    bool AddFormData(const char* name, void* stream, const char* contentType,
                     const char* fileName, const char* transferEncoding);  // 0x00947030
    bool CreateChildStream();                    // 0x00947270
};

extern const int kMonthDayOffset[13];            // 0x0143f578

int  GetDateTypeFromString(const eastl::StrStub* s);            // 0x00947540
int  WeekdayStringToInteger(const char* str, bool longNames);   // 0x00947480
int  MonthStringToInteger(const char* str);                     // 0x00947500
__int64 TimeToSeconds(int weekday, int day, int month, int year, int yday,
                      int hour, int minute, int second);        // 0x00947410
bool ParseDateTimeString(const eastl::StrStub* s, int* weekday, int* day, int* month,
                         int* year, int* yday, int* hour, int* min, int* sec);  // 0x00947700
int TimeStringToSeconds(const eastl::StrStub* s);                // 0x00947cd0

#endif
