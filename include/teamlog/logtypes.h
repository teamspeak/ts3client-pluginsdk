#ifndef TEAMLOG_LOGTYPES_H
#define TEAMLOG_LOGTYPES_H

enum LogTypes {
    LogType_NONE          = 0x0000, ///< Logging is disabled
    LogType_FILE          = 0x0001, ///< Log to regular log file
    LogType_CONSOLE       = 0x0002, ///< Log to standard output / error
    LogType_USERLOGGING   = 0x0004, ///< User defined logging. Will call the \ref ServerLibFunctions.onUserLoggingMessageEvent callback for every message to be logged
    LogType_NO_NETLOGGING = 0x0008, ///< Not used
    LogType_DATABASE      = 0x0010, ///< Log to database (deprecated, server only, no effect in SDK)
    LogType_SYSLOG        = 0x0020, ///< Log to syslog (only available on Linux)
};

enum LogLevel {
    LogLevel_CRITICAL = 0, ///< these messages stop the program
    LogLevel_ERROR,        ///< everything that is really bad, but not so bad we need to shut down
    LogLevel_WARNING,      ///< everything that *might* be bad
    LogLevel_DEBUG,        ///< output that might help find a problem
    LogLevel_INFO,         ///< informational output, like "starting database version x.y.z"
    LogLevel_DEVEL         ///< developer only output (will not be displayed in release mode)
};

#endif //TEAMLOG_LOGTYPES_H
