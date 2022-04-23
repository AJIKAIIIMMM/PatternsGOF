#pragma once

#include <stdint.h>
#include <string>

namespace MyTools {

    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

    class ScreenSingleton
    {
    public:

        static ScreenSingleton& getInstance()
        {
            static ScreenSingleton theInstance;
            return theInstance;
        }

        void ClrScr();
        void __fastcall GotoXY(double x, double y);
        uint16_t GetMaxX();
        uint16_t GetMaxY();
        void SetColor(ConsoleColor color);

    private:
        ScreenSingleton() { }
        ScreenSingleton(const ScreenSingleton& root) = delete;
        ScreenSingleton& operator=(const ScreenSingleton&) = delete;
    };

	//=============================================================================================

    class LogSingleton
    {
    protected:
        LogSingleton() { }
        LogSingleton(const LogSingleton&);
        LogSingleton& operator=(LogSingleton&);
    public:
        static LogSingleton& getInstance() {
            static LogSingleton instance;
            return instance;
        }

        void __fastcall OpenLogFile(const std::string& FN);
        void CloseLogFile();
        void __fastcall WriteToLog(const std::string& str);
        void __fastcall WriteToLog(const std::string& str, int n);
        void __fastcall WriteToLog(const std::string& str, double d);
    };

    class LoggerSingleton
    {
    protected:
        LoggerSingleton(LogSingleton& instance) : s1(instance) { }
        LoggerSingleton(const LoggerSingleton&);
        LoggerSingleton& operator=(LoggerSingleton&);
        LogSingleton& s1;
    public:
        mutable int d = 0;
        static LoggerSingleton& getInstance() {
            static LoggerSingleton instance(LogSingleton::getInstance());
            return instance;
        }
    };


    class Proxy {
    private:
        LoggerSingleton* log_singleton_;

        bool CheckAccess() const {
            std::cout << "Proxy: Checking access prior to firing a real request.\n";
            return true;
        }
        void LogCounting() const {
            std::cout << "¹ " << d++ << std::endl;
        }


    public:
        mutable int d = 0;
        Proxy(LoggerSingleton& log_singleton_ = LoggerSingleton::getInstance()) {
        }

        ~Proxy() {
            delete log_singleton_;
        }

    };
	//=============================================================================================

};