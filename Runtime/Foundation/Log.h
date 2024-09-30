#pragma once
#include <filesystem>
#include <spdlog/sinks/basic_file_sink.h>
#include <string_view>
#include <source_location>
#include <memory>
#include "PreprocessorDirectives.h"

struct FormatAndLocation {
    std::string_view fmt;
    std::source_location location;
public:
    template<size_t N>
    FormatAndLocation(const char (&arr)[N], const std::source_location &l = std::source_location::current())
        : fmt(arr), location(l) {
    }
    FormatAndLocation(const std::string_view &fmt, const std::source_location &l = std::source_location::current())
        : fmt(fmt), location(l) {
    }
    FormatAndLocation(const std::string &fmt, const std::source_location &l = std::source_location::current())
        : fmt(fmt.c_str(), fmt.length()), location(l) {
    }
    FormatAndLocation(const char *cString, const std::source_location &l = std::source_location::current())
        : fmt(cString, (cString != nullptr ? strlen(cString) : 0)), location(l) {
    }
};

class Log {
public:
    enum DebugLevel {
        // clang-format off
        eNone       = 0,
        eInfo       = 1 << 0,
        eDebug      = 1 << 1,
        eWarning    = 1 << 2,
        eError      = 1 << 3,
        eAll        = eInfo | eDebug | eWarning | eError,
        // clang-format on
    };
    ENUM_FLAGS_AS_MEMBER(DebugLevel)
    using LogCallBack = std::function<void(DebugLevel, const std::string &)>;
public:
    Log();
    ~Log();

    static Log *GetInstance();

    void OnCreate();
    void OnDestroy();

    void SetLogLevelMask(DebugLevel level);
    auto GetLogLevelMask() const -> DebugLevel;
    
    void SetPattern(std::string_view pattern);
    void SetLogCallback(LogCallBack cb);

    void SetLogPath(const std::filesystem::path &path);
    auto GetLogPath() const -> std::filesystem::path;

    template<typename... Args>
    static void Info(FormatAndLocation fmtAndLoc, Args &&...args);

    template<typename... Args>
    static void Debug(FormatAndLocation fmtAndLoc, Args &&...args);

    template<typename... Args>
    static void Warning(FormatAndLocation fmtAndLoc, Args &&...args);

    template<typename... Args>
    static void Error(FormatAndLocation fmtAndLoc, Args &&...args);


    template<typename... Args>
    static void InfoIf(bool cond, FormatAndLocation fmtAndLoc, Args &&...args) {
	    if (cond) {
		    Info(fmtAndLoc, std::forward<Args>(args)...);
	    }
    }

	template<typename... Args>
	static void DebugIf(bool cond, FormatAndLocation fmtAndLoc, Args &&...args) {
	    if (cond) {
		    Debug(fmtAndLoc, std::forward<Args>(args)...);
	    }
	}

	template<typename... Args>
	static void WarningIf(bool cond, FormatAndLocation fmtAndLoc, Args &&...args) {
	    if (cond) {
		    Warning(fmtAndLoc, std::forward<Args>(args)...);
	    }
	}

	template<typename... Args>
	static void ErrorIf(bool cond, FormatAndLocation fmtAndLoc, Args &&...args) {
	    if (cond) {
		    Error(fmtAndLoc, std::forward<Args>(args)...);
	    }
	}
private:
    void LogMessage(DebugLevel level, const std::source_location &location, const std::string &message);
private:
    // clang-format off
    DebugLevel                          _logLevelMask = eAll;
    std::string                         _pattern;
    std::string                         _logFilePath;
    LogCallBack                         _logCallback;
    std::shared_ptr<spdlog::logger>     _pLogger;
    std::shared_ptr<spdlog::logger>     _pConsoleLogger;
    // clang-format on
};


template<typename... Args>
void Log::Info(FormatAndLocation fmtAndLoc, Args &&...args) {
    if (GetInstance() == nullptr || !HasFlag(GetInstance()->GetLogLevelMask(), eInfo)) {
        return;
    }
    std::string message = fmt::vformat(fmtAndLoc.fmt, fmt::make_format_args(std::forward<Args>(args)...));
    GetInstance()->LogMessage(eInfo, fmtAndLoc.location, message);
}

template<typename... Args>
void Log::Debug(FormatAndLocation fmtAndLoc, Args &&...args) {
    if (GetInstance() == nullptr || !HasFlag(GetInstance()->GetLogLevelMask(), eDebug)) {
        return;
    }
    std::string message = fmt::vformat(fmtAndLoc.fmt, fmt::make_format_args(std::forward<Args>(args)...));
    GetInstance()->LogMessage(eDebug, fmtAndLoc.location, message);
}

template<typename... Args>
void Log::Warning(FormatAndLocation fmtAndLoc, Args &&...args) {
    if (GetInstance() == nullptr || !HasFlag(GetInstance()->GetLogLevelMask(), eWarning)) {
        return;
    }
    std::string message = fmt::vformat(fmtAndLoc.fmt, fmt::make_format_args(std::forward<Args>(args)...));
    GetInstance()->LogMessage(eWarning, fmtAndLoc.location, message);
}

template<typename... Args>
void Log::Error(FormatAndLocation fmtAndLoc, Args &&...args) {
    if (GetInstance() == nullptr || !HasFlag(GetInstance()->GetLogLevelMask(), eError)) {
        return;
    }
    std::string message = fmt::vformat(fmtAndLoc.fmt, fmt::make_format_args(std::forward<Args>(args)...));
    GetInstance()->LogMessage(eError, fmtAndLoc.location, message);
}