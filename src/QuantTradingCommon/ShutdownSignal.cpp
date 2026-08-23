#include "ShutdownSignal.h"

#ifdef WIN32
#include <windows.h>
#else
#include <signal.h>
#endif // WIN32

namespace quanttrading
{
#ifdef WIN32
// 控制台 Ctrl+C / Ctrl+Break / 关闭 / 注销 / 关机：置位退出标志，阻止默认终止，
// 交还主线程有序关停。处理器运行在独立线程，可安全调用。
static BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType)
{
    switch (ctrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        ShutdownSignal::Request();
        return TRUE;
    default:
        return FALSE;
    }
}
#else
// SIGINT / SIGTERM：处理器只做原子 store，保证 async-signal-safe。
static void SignalHandler(int /*signalNumber*/)
{
    ShutdownSignal::Request();
}
#endif // WIN32

void ShutdownSignal::InstallHandlers()
{
#ifdef WIN32
    ::SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
#else
    ::signal(SIGINT, SignalHandler);
    ::signal(SIGTERM, SignalHandler);
#endif // WIN32
}

void ShutdownSignal::Request()
{
    s_Requested.store(true);
}

bool ShutdownSignal::IsRequested()
{
    return s_Requested.load();
}
}
