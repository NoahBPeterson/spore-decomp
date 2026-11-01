"""threads.py PID [samples]: eip/esp and the top stack dwords of every thread of a 32-bit process (WOW64)."""
import ctypes, ctypes.wintypes as W, struct, sys, time
k = ctypes.WinDLL("kernel32", use_last_error=True)
pid = int(sys.argv[1]); samples = int(sys.argv[2]) if len(sys.argv) > 2 else 3

class TE(ctypes.Structure):
    _fields_ = [("dwSize", W.DWORD), ("cntUsage", W.DWORD), ("th32ThreadID", W.DWORD), ("th32OwnerProcessID", W.DWORD),
                ("tpBasePri", W.LONG), ("tpDeltaPri", W.LONG), ("dwFlags", W.DWORD)]
class CTX(ctypes.Structure):          # WOW64_CONTEXT
    _fields_ = [("ContextFlags", W.DWORD), ("Dr", W.DWORD * 6), ("Float", ctypes.c_byte * 112),
                ("SegGs", W.DWORD), ("SegFs", W.DWORD), ("SegEs", W.DWORD), ("SegDs", W.DWORD),
                ("Edi", W.DWORD), ("Esi", W.DWORD), ("Ebx", W.DWORD), ("Edx", W.DWORD), ("Ecx", W.DWORD), ("Eax", W.DWORD),
                ("Ebp", W.DWORD), ("Eip", W.DWORD), ("SegCs", W.DWORD), ("EFlags", W.DWORD), ("Esp", W.DWORD), ("SegSs", W.DWORD),
                ("Ext", ctypes.c_byte * 512)]
k.CreateToolhelp32Snapshot.restype = W.HANDLE
k.OpenThread.restype = W.HANDLE
k.OpenProcess.restype = W.HANDLE
proc = k.OpenProcess(0x0010 | 0x0400, False, pid)
def tids():
    snap = k.CreateToolhelp32Snapshot(4, 0); te = TE(); te.dwSize = ctypes.sizeof(TE); out = []
    ok = k.Thread32First(snap, ctypes.byref(te))
    while ok:
        if te.th32OwnerProcessID == pid: out.append(te.th32ThreadID)
        ok = k.Thread32Next(snap, ctypes.byref(te))
    k.CloseHandle(snap); return out
def rd(a, n):
    b = ctypes.create_string_buffer(n); got = ctypes.c_size_t()
    if not k.ReadProcessMemory(proc, ctypes.c_void_p(a), b, n, ctypes.byref(got)): return b""
    return b.raw[:got.value]
for s in range(samples):
    for t in tids():
        h = k.OpenThread(0x0002 | 0x0008 | 0x0040, False, t)   # suspend/resume, get context, query
        if not h: continue
        k.SuspendThread(h)
        c = CTX(); c.ContextFlags = 0x10007
        ok = k.Wow64GetThreadContext(h, ctypes.byref(c))
        k.ResumeThread(h); k.CloseHandle(h)
        if not ok: continue
        st = rd(c.Esp, 256)
        ws = struct.unpack("<%dI" % (len(st) // 4), st) if st else ()
        rets = [w for w in ws if 0x401000 <= w < 0x1a00000][:12]
        print("s%d tid %5d eip %08x esp %08x ebp %08x stack %s" % (s, t, c.Eip, c.Esp, c.Ebp, " ".join("%08x" % w for w in rets)))
    time.sleep(1)
