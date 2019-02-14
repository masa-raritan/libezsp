/**
 * @file ConsoleLogger.cpp
 *
 * @brief Concrete implementation of a logger using the stdout and stderr output streams on the text console
 */

#include "ConsoleLogger.h"
#include <cstdarg>
#include <cstdio>

ConsoleStderrLogger::ConsoleStderrLogger(const LOG_LEVEL logLevel) :
		ILoggerStream(logLevel) { /* Set the parent classes' logger's level to what has been provided as constructor's argument */
}

void ConsoleStderrLogger::log(const char *format, ...) {

	va_list args;
	va_start(args, format);
	fprintf(stderr, format, args);
	va_end(args);
}

int ConsoleStderrLogger::overflow(int c) {
	if (c != EOF) {
		if (putchar(c) == EOF) {
			return EOF;
		}
	}
	return c;
}

ConsoleStdoutLogger::ConsoleStdoutLogger(const LOG_LEVEL logLevel) :
		ILoggerStream(logLevel) { /* Set the parent classes' logger's level to what has been provided as constructor's argument */
}

void ConsoleStdoutLogger::log(const char *format, ...) {

	va_list args;
	va_start(args, format);
	printf(format, args);
	va_end(args);
}

int ConsoleStdoutLogger::overflow(int c) {
	if (c != EOF) {
		if (putchar(c) == EOF) {
			return EOF;
		}
	}
	return c;
}

static ConsoleErrorLogger consoleErrorLogger;	/* Create a unique instance of the ConsoleErrorLogger that will be used to handle error logs */
static ConsoleWarningLogger consoleWarningLogger;	/* Create a unique instance of the ConsoleWarningLogger that will be used to handle warning logs */
static ConsoleInfoLogger consoleInfoLogger;	/* Create a unique instance of the ConsoleInfoLogger that will be used to handle info logs */
static ConsoleDebugLogger consoleDebugLogger;	/* Create a unique instance of the ConsoleDebugLogger that will be used to handle debug logs */
static ConsoleTraceLogger consoleTraceLogger;	/* Create a unique instance of the ConsoleTraceLogger that will be used to handle trace logs */

ConsoleLogger::ConsoleLogger(ILoggerStream& errorLogger, ILoggerStream& warningLogger, ILoggerStream& infoLogger, ILoggerStream& debugLogger, ILoggerStream& traceLogger) :
		ILogger(errorLogger, warningLogger, infoLogger, debugLogger, traceLogger) {
}

ConsoleLogger& ConsoleLogger::getInstance() {
	static ConsoleLogger instance(consoleErrorLogger, consoleWarningLogger, consoleInfoLogger, consoleDebugLogger, consoleTraceLogger); /* Unique instance of the singleton */

	return instance;
}

/* Create unique (global) instances of each logger type, and store them inside the ILogger (singleton)'s class static attribute */
std::ostream ILogger::loggerErrorStream(&ConsoleLogger::getInstance().errorLogger);
std::ostream ILogger::loggerWarningStream(&ConsoleLogger::getInstance().warningLogger);
std::ostream ILogger::loggerInfoStream(&ConsoleLogger::getInstance().infoLogger);
std::ostream ILogger::loggerDebugStream(&ConsoleLogger::getInstance().debugLogger);
std::ostream ILogger::loggerTraceStream(&ConsoleLogger::getInstance().traceLogger);
