// Slice s0084af40 (batch gold3).
// Two modules: EA::App::IMEServerWin32 (candidate-list bookkeeping over eastl wstring vectors)
// and the giflib GIF decoder's DGif* entry points (DGifCloseFile / DGifSetupDecompress /
// DGifGetPrefixChar / DGifGetCodeNext-style helpers).
// Built /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;
typedef uint8          GifByteType;
typedef __int64        int64;

void* __cdecl EAAllocate(uint32 n, const char* pName, int a, int b, const char* pFile, int line);
void  __cdecl PoolFree(void* p);
inline void operator delete(void* p) throw() { PoolFree(p); }

extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) int   __cdecl memcmp(const void*, const void*, unsigned int);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const wchar_t*);

// ---------------------------------------------------------------------------------------------
// giflib runtime I/O (GifFilePrivateType's callbacks)
// ---------------------------------------------------------------------------------------------
extern "C" int  __stdcall GifReadFile(void* hFile, void* pBuf, int nBytes);   // 0x0087d4e0 gread
extern "C" bool __stdcall GifFree(void* p);                                   // 0x0087d4c0 gfree
extern "C" int64 __stdcall GifTell(void* hFile);                              // 0x0087d570 gtell
extern "C" void __stdcall GifSeek(void* hFile, int lo, int hi);               // 0x0087d540 gseek

// ---------------------------------------------------------------------------------------------
// giflib file-private struct (retail offsets; the decoder state is the ancestor of DGifGetCode)
// ---------------------------------------------------------------------------------------------
struct GifFilePrivateType {
    void*   mFileHandle;      // +0x00
    unsigned char mPad[0x08 - 0x04];
    int     mRunningCode;     // +0x08
    int     mRunningBits;     // +0x0c
    int     mMaxCode1;        // +0x10
    int     mMaxCode;         // +0x14
    int     mLastCode;        // +0x18
    int     mStackPtr;        // +0x1c
    int     mCrntShiftDWord;  // +0x20
    int     mCrntShiftState;  // +0x24
    int     mEOFCode;         // +0x28
    int     mBadCode;         // +0x2c
    int     mLastCode2;       // +0x30
    void*   mUserData0;       // +0x34
    void*   mUserData1;       // +0x38
    void*   mpReadFn;         // +0x3c
    void*   mpWriteFn;        // +0x40
    void*   mBuffer;          // +0x48? (the +0x38 file handle the DGif helpers read through)
};

struct GifFileType {
    int        mUserData;     // +0x00
    int        mPad04;
    int        mPad08;
    int        mPad0c;
    int        mPad10;
    int        mPad14;
    int        mPad18;
    int        mPad1c;
    int        mPad20;
    int        mPad24;
    int        mPad28;
    int        mPad2c;
    int        mPad30;
    int        mPad34;
    int        mPad38;
    int        mPad3c;
    void*      mpPrivate;     // +0x40
    int        mPad44;
    void*      mpSaved;       // +0x48
    int        mError;        // +0x4c
    // ... image/colour-map fields follow
};

// The private+0x38 handle the DGif helpers read from.
struct GifPrivateHandle {
    unsigned char mPad[0x38];
    void*         mpFile;     // +0x38
};

// ---------------------------------------------------------------------------------------------
// IME types
// ---------------------------------------------------------------------------------------------
struct WString {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
};

// eastl::vector<WString, sp_vector_allocator>: 16-byte elements, 3 pointers.
struct WStringVec {
    WString* mpBegin;    // +0x00
    WString* mpEnd;      // +0x04
    WString* mpCapacity; // +0x08
};

struct CharPtrVec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
};

// ---------------------------------------------------------------------------------------------
// IMECompositionStringDataEx -- the composition string state at +0xc of the server
// ---------------------------------------------------------------------------------------------
struct IMECompositionStringDataEx {
    char       mHead[0x24];    // +0x00 .. +0x23 (owned by the base class)
    WStringVec mCandidates;    // +0x24 (wstring vector that FUN_0084af40 rebuilds)
    int        mPad30;
    int        mPad34;
    CharPtrVec mPtrs;          // +0x38 (pointer vector the candidate list feeds)
    char       mPad44[0x08];
    char       mFlag4c;        // +0x4c

    void RebuildCandidates();                                       // 0x0084af40
    void Reset();                                                   // 0x0084b1a0
    void Clear();                                                   // 0x0084b1f0
    void ResizeCandidates(unsigned nCount);                         // 0x0084b260
    void* InsertCandidates(WString* pWhere, unsigned nCount, const WString* pValue);  // 0x0084afc0
};

// The full object view starting at the IMEServerWin32 base (so +0xc lands on the IME data).
struct IMEServerWin32 {
    void*   mpVtbl0;          // +0x00
    char    mByte04;          // +0x04
    char    mByte05;          // +0x05
    int     mInt08;           // +0x08
    char    mCompData[0x60];  // +0x0c .. +0x6b
    char    mCandidateData[0x50];  // +0x6c .. +0xbb
    void*   mpHandlerVtbl;    // +0xbc
    int     mIntC0;           // +0xc0
    int     mIntC4;           // +0xc4
    int     mIntC8;           // +0xc8
    int     mIntCc;           // +0xcc
    int     mIntD0;           // +0xd0
    char    mByteD4;          // +0xd4
    void*   mHWnd;            // (not the retail offset; only used as a placeholder)

    void SetIMECandidateListData(unsigned nFlags);          // 0x0084b390
    long WinProc(void* hWnd, unsigned uMsg, unsigned wParam, long lParam);   // 0x0084b600
};

// ---------------------------------------------------------------------------------------------
// forward declarations for the retail helpers the IME code calls
// ---------------------------------------------------------------------------------------------
void  __cdecl eastl_VectorResize(void* pVec, unsigned nCount);            // 0x00999fb0
void  __cdecl eastl_DoFreeNodesTable(void* pTable, int nBucketCount);     // 0x0083cad0
void  __cdecl WStringPushBack(WString* pStr, wchar_t ch);                 // 0x004f6510
void* __cdecl CopyWStrings(void* pDst, const void* pFirst, const void* pLast);  // 0x0084ab40
void  __cdecl VectorWStringDoDestroyValues(void* pVec, void* pFirst, void* pLast); // 0x0084aad0
void  __cdecl CopyBytes(void* pDst, const void* pSrc, unsigned n);        // 0x011e0744
void  __cdecl IMECompositionStringDataExCtor(void* pThis);                // 0x0084a700

extern "C" __declspec(dllimport) void* __stdcall ImmGetContext(void* hWnd);                 // IMM32
extern "C" __declspec(dllimport) int   __stdcall ImmReleaseContext(void* hWnd, void* hIMC); // IMM32
extern "C" __declspec(dllimport) unsigned __stdcall ImmGetCandidateListW(void* hIMC, unsigned nIndex, void* pBuf, unsigned nBufLen);
extern "C" __declspec(dllimport) int   __stdcall ImmSetOpenStatus(void* hIMC, int bOpen);
extern "C" __declspec(dllimport) int   __stdcall ImmNotifyIME(void* hIMC, unsigned dwAction, unsigned dwIndex, unsigned dwValue);
extern "C" __declspec(dllimport) int   __stdcall ImmDisableTextFrameService(unsigned dwThreadId);
extern "C" __declspec(dllimport) long  __stdcall DefWindowProcA(void* hWnd, unsigned uMsg, unsigned wParam, long lParam);
extern "C" __declspec(dllimport) wchar_t* __cdecl wcsncpy(wchar_t*, const wchar_t*, unsigned);

// ---------------------------------------------------------------------------------------------
// DGifCloseFile -- giflib (0084bce0)
// ---------------------------------------------------------------------------------------------
// @ 0x0084bce0
int DGifCloseFile(GifFileType* pGifFile)
{
    if (pGifFile == 0)
        return 0;
    GifFilePrivateType* pPriv = (GifFilePrivateType*)pGifFile->mpPrivate;
    GifFilePrivateType* pSaved = (GifFilePrivateType*)pGifFile->mpSaved;
    if (pPriv->mpWriteFn) GifFree(pPriv->mpWriteFn);
    if (pPriv->mpReadFn) GifFree(pPriv->mpReadFn);
    if (pSaved) GifFree(pSaved);
    GifFree(pPriv);
    return 1;
}

// ---------------------------------------------------------------------------------------------
// DGifGetCodeNext -- read the next run-length code block (0084bc80)
// ---------------------------------------------------------------------------------------------
// @ 0x0084bc80
int DGifGetCodeNext(GifFileType* pGifFile, GifByteType** ppCodeBlock)
{
    GifFilePrivateType* pPriv = (GifFilePrivateType*)pGifFile->mpPrivate;
    void* pFile = ((GifPrivateHandle*)((char*)pPriv + 0x38))->mpFile;

    uint8 nSize;
    if (GifReadFile(pFile, &nSize, 1) == 0)
        return 0;
    if (nSize == 0) {
        *ppCodeBlock = 0;
    } else {
        *ppCodeBlock = (GifByteType*)((char*)pPriv + 0x70);
        *(uint8*)*ppCodeBlock = nSize;
        if (GifReadFile(pFile, (char*)*ppCodeBlock + 1, nSize) == 0)
            return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------------------------
// DGifSetupDecompress -- initialise the LZW decoder state (0084bd20)
// ---------------------------------------------------------------------------------------------
// @ 0x0084bd20
int DGifSetupDecompress(GifFileType* pGifFile)
{
    GifFilePrivateType* pPriv = (GifFilePrivateType*)pGifFile->mpPrivate;
    void* pFile = ((GifPrivateHandle*)((char*)pPriv + 0x38))->mpFile;

    uint8 nCodeSize;
    GifReadFile(pFile, &nCodeSize, 1);

    pPriv->mRunningCode = nCodeSize;
    pPriv->mRunningBits = 1 << nCodeSize;
    pPriv->mMaxCode1 = 1 + (1 << nCodeSize);
    pPriv->mMaxCode = 1 + (1 << nCodeSize);
    pPriv->mLastCode = (nCodeSize + 1);
    pPriv->mStackPtr = 0;
    int nBits = (1 << (nCodeSize + 1));
    pPriv->mCrntShiftDWord = 0;
    pPriv->mCrntShiftState = 0;
    pPriv->mEOFCode = nBits;
    pPriv->mBadCode = nBits + 1;
    for (int i = 0; i < 0x1002; ++i)
        ((int*)((char*)pPriv + 0x2170))[i] = 0x1002;
    return 1;
}

// ---------------------------------------------------------------------------------------------
// DGifGetPrefixChar -- walk the prefix table looking for a literal (0084bd90)
// retail passes the table in esi and the clear code in edx, so declare those registers live.
// ---------------------------------------------------------------------------------------------
// @ 0x0084bd90
int DGifGetPrefixChar(int* pPrefix, int nCode, int nClearCode)
{
    int i = 0;
    while (nCode > nClearCode) {
        if (i >= 0x1000) break;
        nCode = pPrefix[nCode];
        ++i;
    }
    return nCode;
}

// ---------------------------------------------------------------------------------------------
// DGifDecompressInput -- read one LZW code from the block stream (0084bdb0)
// ---------------------------------------------------------------------------------------------
// @ 0x0084bdb0
int DGifDecompressInput(GifFileType* pGifFile, int* pCode)
{
    GifFilePrivateType* pPriv = (GifFilePrivateType*)pGifFile->mpPrivate;
    for (;;) {
        uint8 nByte;
        if (GifReadFile(pPriv, &nByte, 1) == 0) {
            // skip: the real loop reads through the file handle
        }
        if (nByte == 0)
            break;
        int64 nPos = GifTell(pPriv);
        GifSeek(pPriv, (int)(nPos + nByte), (int)((nPos + nByte) >> 32));
    }
    *pCode = 0;
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x0084af40 IMECompositionStringDataEx::RebuildCandidates
// ---------------------------------------------------------------------------------------------
// @ 0x0084af40
void IMECompositionStringDataEx::RebuildCandidates()
{
    if (mCandidates.mpEnd == mCandidates.mpCapacity) {
        *(int*)((char*)this + 0x00) = 0;
        *(int*)((char*)this + 0x04) = 0;
        return;
    }
    unsigned nCount = (unsigned)(mCandidates.mpEnd - mCandidates.mpBegin);
    *(int*)((char*)this + 0x04) = (int)nCount;
    eastl_VectorResize(&mPtrs, nCount);

    for (unsigned i = 0; i < (unsigned)*(int*)((char*)this + 0x04); ++i) {
        WString* pStr = &mCandidates.mpBegin[i];
        if (pStr->mpEnd == pStr->mpBegin || pStr->mpBegin[(pStr->mpEnd - pStr->mpBegin) - 1] != 0)
            WStringPushBack(pStr, 0);
        mPtrs.mpBegin[i] = pStr->mpBegin;
    }
    *(int*)((char*)this + 0x00) = (int)(long)mPtrs.mpBegin;
}

// ---------------------------------------------------------------------------------------------
// 0x0084b1a0 IMECompositionStringDataEx::Reset
// ---------------------------------------------------------------------------------------------
// @ 0x0084b1a0
void IMECompositionStringDataEx::Reset()
{
    mCandidates.mpBegin = 0;
    mCandidates.mpEnd = 0;
    mCandidates.mpCapacity = 0;
    mPtrs.mpBegin = 0;
    mPtrs.mpEnd = 0;
    mPtrs.mpCapacity = 0;
    mFlag4c = 0;
    *(int*)((char*)this + 0x08) = 0;

    const wchar_t* pSrc = L"en-us";
    wchar_t* pDst = (wchar_t*)((char*)this + 0x0c);
    while ((*pDst++ = *pSrc++) != 0) {}

    RebuildCandidates();
}

// ---------------------------------------------------------------------------------------------
// 0x0084b1f0 IMECompositionStringDataEx::Clear
// ---------------------------------------------------------------------------------------------
// @ 0x0084b1f0
void IMECompositionStringDataEx::Clear()
{
    WString* pBegin = mCandidates.mpBegin;
    WString* pEnd = mCandidates.mpEnd;
    eastl_VectorResize(&mCandidates, 0);
    (void)pBegin; (void)pEnd;
    mCandidates.mpEnd = mCandidates.mpBegin;
    CopyBytes(mPtrs.mpEnd, mPtrs.mpEnd, 0);
    mPtrs.mpEnd = mPtrs.mpBegin;
    RebuildCandidates();
}

// ---------------------------------------------------------------------------------------------
// 0x0084b260 IMECompositionStringDataEx::ResizeCandidates
// ---------------------------------------------------------------------------------------------
// @ 0x0084b260
void IMECompositionStringDataEx::ResizeCandidates(unsigned nCount)
{
    unsigned nHave = (unsigned)(mCandidates.mpEnd - mCandidates.mpBegin);
    if (nCount > nHave) {
        WString empty;
        empty.mpBegin = (wchar_t*)0x01667bac;
        empty.mpEnd = (wchar_t*)0x01667bac;
        empty.mpCapacity = (wchar_t*)0x01667bae;
        InsertCandidates(mCandidates.mpEnd, nCount - nHave, &empty);
    } else {
        WString* pPos = mCandidates.mpBegin + nCount;
        WString* pNewEnd = (WString*)CopyWStrings(mCandidates.mpBegin, mCandidates.mpEnd, pPos);
        VectorWStringDoDestroyValues(&mCandidates, pNewEnd, mCandidates.mpEnd);
        mCandidates.mpEnd = mCandidates.mpEnd - (mCandidates.mpEnd - pNewEnd);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x0084b2e0 EA::App::IMEServerWin32::IMEServerWin32
// ---------------------------------------------------------------------------------------------
// @ 0x0084b2e0
void* IMEServerWin32Ctor(void* pThis)
{
    char* p = (char*)pThis;
    *(void**)p = (void*)0x0141cb28;
    p[4] = 0;
    p[5] = 1;
    *(int*)(p + 8) = 0;
    IMECompositionStringDataExCtor(p + 0xc);          // 0x0084a700
    ((IMECompositionStringDataEx*)(p + 0x6c))->Reset();
    *(void**)(p + 0xbc) = (void*)0x013eb394;
    *(int*)(p + 0xc0) = 0;
    *(int*)(p + 0xc4) = 0;
    *(int*)(p + 0xc8) = 0;
    *(int*)(p + 0xcc) = 0;
    *(int*)(p + 0xd0) = 0;
    p[0xd4] = 0;
    wcsncpy((wchar_t*)(p + 0x1c), L"en-us", 12);
    *(void**)p = (void*)0x0141cb78;
    *(void**)(p + 0xbc) = (void*)0x0141cb6c;
    *(wchar_t*)(p + 0x1c + 0x16) = 0;
    wcsncpy((wchar_t*)(p + 0x78), L"en-us", 12);
    *(wchar_t*)(p + 0x78 + 0x16) = 0;
    ImmDisableTextFrameService(0xffffffff);
    return p;
}

// ---------------------------------------------------------------------------------------------
// 0x0084afc0 IMECompositionStringDataEx::InsertCandidates -- grow the candidate vector
// ---------------------------------------------------------------------------------------------
// @ 0x0084afc0
void* IMECompositionStringDataEx::InsertCandidates(WString* pWhere, unsigned nCount, const WString* pValue)
{
    WString* pOldEnd = mCandidates.mpEnd;
    if (pWhere == pOldEnd) {
        for (unsigned i = 0; i < nCount; ++i) {
            mCandidates.mpEnd[i] = *pValue;
            ++mCandidates.mpEnd;
        }
    } else {
        WString* pPos = pWhere + nCount;
        CopyWStrings(pPos, pWhere, pOldEnd);
        mCandidates.mpEnd = pOldEnd + nCount;
        for (unsigned i = 0; i < nCount; ++i) pWhere[i] = *pValue;
    }
    return pWhere;
}

// ---------------------------------------------------------------------------------------------
// 0x0084b390 EA::App::IMEServerWin32::SetIMECandidateListData
// ---------------------------------------------------------------------------------------------
// @ 0x0084b390
void IMEServerWin32::SetIMECandidateListData(unsigned nFlags)
{
    void* hIMC = ImmGetContext(mHWnd);
    if (hIMC == 0)
        return;
    for (unsigned i = 0; i < 32; ++i) {
        if ((nFlags & (1u << i)) != 0) {
            unsigned nSize = ImmGetCandidateListW(hIMC, i, 0, 0);
            (void)nSize;
        }
    }
    ImmReleaseContext(mHWnd, hIMC);
}

// ---------------------------------------------------------------------------------------------
// 0x0084b600 EA::App::IMEServerWin32::WinProc
// ---------------------------------------------------------------------------------------------
// @ 0x0084b600
long IMEServerWin32::WinProc(void* hWnd, unsigned uMsg, unsigned wParam, long lParam)
{
    if (uMsg == 0x281)   // WM_IME_COMPOSITION
        return 0;
    if (uMsg == 0x286) { // WM_IME_CHAR
        ImmSetOpenStatus(hWnd, 1);
        return 0;
    }
    if (uMsg == 7)       // WM_SETFOCUS
        return 0;
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}
