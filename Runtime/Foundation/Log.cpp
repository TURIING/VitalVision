#include "Log.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

Log::Log() : _logFilePath("app.log") {
    _logLevelMask = eInfo | eDebug | eWarning | eError;
    _pattern = "[%H:%M:%S] %v";
}

Log::~Log() {
}

Log *Log::GetInstance() {
    static Log *pInstance = new Log;
    return pInstance;
}

void Log::OnCreate() {
    _pLogger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
    _pConsoleLogger = spdlog::stdout_color_mt("console");
    spdlog::set_pattern(_pattern.c_str());
    _pLogger ->set_level(spdlog::level::trace);
    _pConsoleLogger ->set_level(spdlog::level::trace);
}

void Log::OnDestroy() {
    _pLogger = nullptr;
    _pConsoleLogger = nullptr;
}

void Log::SetLogLevelMask(DebugLevel mask) {
    _logLevelMask = mask;
}

void Log::SetPattern(std::string_view pattern) {
    _pattern = pattern;
}

void Log::SetLogCallback(LogCallBack cb) {
    _logCallback = std::move(cb);
}

void Log::SetLogPath(const std::filesystem::path &path) {
    _logFilePath = path.string();
}

auto Log::GetLogPath() const -> std::filesystem::path {
    return _logFilePath;
}

auto Log::GetLogLevelMask() const -> DebugLevel {
    return _logLevelMask;
}

void Log::LogMessage(DebugLevel level, const std::source_location &location, const std::string &message) {
    std::string stringToWrite;
    const char *pFileName = location.file_name();
    const uint32_t line = location.line();
    const uint32_t column = location.column();
    std::string output;
    switch (level) {
    case eInfo:
        output = fmt::format("{}({},{}) [info ]: {}", pFileName, line, column, message);
        _pLogger->info("{}", output);
        _pConsoleLogger->info("{}", output);
        break;
    case eDebug:
        output = fmt::format("{}({},{}) [Debug]: {}", pFileName, line, column, message);
        _pLogger->debug("{}", output);
        _pConsoleLogger->debug("{}", output);
        break;
    case eWarning:
        output = fmt::format("{}({},{}) [Warn ]: {}", pFileName, line, column, message);
        _pLogger->warn("{}", output);
        _pConsoleLogger->warn("{}", output);
        break;
    case eError:
        output = fmt::format("{}({},{}) [Error]: {}", pFileName, line, column, message);
        _pLogger->error("{}", output);
        _pConsoleLogger->error("{}", output);
        break;
    case eNone:
    default:
        return;
    }

    if (_logCallback != nullptr) {
        _logCallback(level, output);
    }
}
