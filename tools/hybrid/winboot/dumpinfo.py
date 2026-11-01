"""dumpinfo.py DUMP: exception, registers and the code-range dwords on the faulting thread's stack (innermost first)
of a Windows Error Reporting minidump (LocalDumps). Map the addresses with the hybrid's .hooks.json (.hybx entries)."""
import struct, sys
from minidump.minidumpfile import MinidumpFile
m = MinidumpFile.parse(sys.argv[1])
exc = m.exception.exception_records[0]
rec = exc.ExceptionRecord
num = lambda x: x.value if hasattr(x, "value") else int(x)
print("exception %08x at %08x thread %d params %s" % (num(rec.ExceptionCode), num(rec.ExceptionAddress), exc.ThreadId,
      [hex(p) for p in rec.ExceptionInformation[:rec.NumberParameters]]))
# the faulting context (the exception stream's own x86 CONTEXT; the thread list holds the state when the dump was
# written, inside ntdll's exception dispatch)
loc = exc.ThreadContext
raw = open(sys.argv[1], "rb").read()[loc.Rva:loc.Rva + loc.DataSize]
off = {"Edi": 0x9c, "Esi": 0xa0, "Ebx": 0xa4, "Edx": 0xa8, "Ecx": 0xac, "Eax": 0xb0, "Ebp": 0xb4, "Eip": 0xb8, "Esp": 0xc4}
regs = {k: struct.unpack_from("<I", raw, o)[0] for k, o in off.items()} if len(raw) >= 0xc8 else {}
print(" ".join("%s=%08x" % (k.lower(), v) for k, v in regs.items()))
rd = m.get_reader().get_buffered_reader()
esp = regs.get("Esp")
if esp:
    rd.move(esp)
    data = rd.read(0x400)
    ws = struct.unpack("<%dI" % (len(data) // 4), data)
    hits = ["+%03x:%08x" % (4 * i, w) for i, w in enumerate(ws) if 0x401000 <= w < 0x1c00000]
    print("stack code dwords:", " ".join(hits[:40]))
