#include <CaveHook.h>
#include <ntstrsafe.h>

#define Log(format, ...) DbgPrintEx(0, 0, format, __VA_ARGS__)

PVOID original;

void __fastcall KeBugCheckExDetour(ULONG BugCheckCode, ULONG_PTR BugCheckParameter1, ULONG_PTR BugCheckParameter2, ULONG_PTR BugCheckParameter3, ULONG_PTR BugCheckParameter4) {
    Log("KeBugCheckEx called by pid: %ld, tid: %ld\n", PsGetCurrentProcessId(), PsGetCurrentThreadId());
    Log("CheckCode: %u 0x%lX, p1: %ld, p2: %ld, p3: %ld, p4: %ld\n", BugCheckCode, BugCheckCode, BugCheckParameter1, BugCheckParameter2, BugCheckParameter3, BugCheckParameter4);

    LARGE_INTEGER delay;
    delay.LowPart = 0;
    delay.HighPart = 0x80000000;
    KeDelayExecutionThread(KernelMode, FALSE, &delay);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
#pragma clang diagnostic ignored "-Wnull-dereference"
NTSTATUS DriverEntry(PDRIVER_OBJECT, PUNICODE_STRING) {
    HOOK_DATA hookData{};
    Log("Hook status: %d\n", CaveHookEx(reinterpret_cast<ULONGLONG>(KeBugCheckEx), &KeBugCheckExDetour, &original, &hookData));
    *reinterpret_cast<ULONGLONG*>(0) = 0; // Test bsod by reading and writing memory in 0

    return STATUS_SUCCESS;
}
#pragma clang diagnostic pop
