#include "ui/mainwindow.h"

#include <signal.h>
#include <execinfo.h>
#include <iostream>
#include <QApplication>

#define ADDR_MAX_NUM 100

void SignalHandler(int sig)
{
    //    ara::log::Logger& logger_ctx = ara::log::CreateLogger("DB",
    //                                                   "Context for diag bridge collection");
    //logger_ctx.LogFatal() << "RECEIVED SIGNAL " << sig;
    std::cout << "RECEIVED SIGNAL " << sig << std::endl;

    if (sig == SIGTERM)
    {

    }
    else
    {
        void *pBuf[ADDR_MAX_NUM] = {0};
        int iAddrNum = backtrace(pBuf, ADDR_MAX_NUM);
        //logger_ctx.LogFatal() << "BACKTRACE: NUMBER OF ADDRESSES IS: " << iAddrNum;
        std::cout << "BACKTRACE: NUMBER OF ADDRESSES IS: " << iAddrNum << std::endl;
        char ** strSymbols = backtrace_symbols(pBuf, iAddrNum);
        if (strSymbols == NULL) {
            //logger_ctx.LogFatal() << "BACKTRACE: CANNOT GET BACKTRACE SYMBOLS";
            std::cout << "BACKTRACE: CANNOT GET BACKTRACE SYMBOLS" << std::endl;
            return;
        }
        int ii = 0;
        for (ii = 0; ii < iAddrNum; ii++) {
            //logger_ctx.LogFatal() << "[" << iAddrNum-ii << "] " << strSymbols[ii];
            std::cout << "[" << iAddrNum-ii << "] " << strSymbols[ii] << std::endl;
        }
        free(strSymbols);
        strSymbols = NULL;
        exit(1);
    }
}

void Initialize_Signalhandler(void)
{
    signal(SIGTERM, SignalHandler);
    signal(SIGSEGV, SignalHandler);
    signal(SIGILL, SignalHandler);
    signal(SIGABRT, SignalHandler);
}



int main(int argc, char *argv[])
{
    Initialize_Signalhandler();
    QApplication a(argc, argv);
    MainWindow w;
//    w.showFullScreen();
    w.show();
    return a.exec();
}
