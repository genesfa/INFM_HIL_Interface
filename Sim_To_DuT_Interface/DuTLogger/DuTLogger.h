/**
 * DuT-Logger
 *
 * Contains the class DuTLogger and all necessary variables.
 * For better documentation see the class "DuTLogger" and it's functions.
 *
 * @author Marco Keul
 * @version 1.0
 */

#ifndef SIM_TO_DUT_INTERFACE_DUTLOGGER_H
#define SIM_TO_DUT_INTERFACE_DUTLOGGER_H

#include "DuTLoggerConfig.h"
#include "EventVisitor.h"
#include <string>
#include "quill/Quill.h"
#include "../Events/SimEvent.h"
#include <list>
#include <filesystem>
#include <fstream>

/**
 * This constant defines the mode how the logger will open the logfile of the console logging.
 * Mode "w" creates a new file or overwrite the existing file with the same name on every start of the application.
 * In mode "a" the logger tries to append it's content on an existing file with the same name.
 */
static const std::string FILE_MODE_CONSOLE = "w";

/**
 * This constant defines the mode how the logger will open the logfile of the data logging.
 * Mode "w" creates a new file or overwrite the existing file with the same name on every start of the application.
 * In mode "a" the logger tries to append it's content on an existing file with the same name.
 */
static const std::string FILE_MODE_DATA = "w";

/**
 * This constant contains the header of the csv files. This header will be printed in the first line of the files and
 * represents the order and meaning of the logged values.
 */
static const std::string CSV_HEADER = "Operation,Value,Origin,Timestamp";

/**
 * This enum collects all types of logger whose level can be changed.
 * So there is a log level for logging messages in the console and another one to log messages in a file.
 * Please notice that you can't change the level of the data logging, because all data objects will be logged with
 * the same level.
 */
enum LOG_TYPE {
    CONSOLE_LOG, FILE_LOG
};

/**
 * This logger is a tool with specialized functions to log and store messages for all elements of the
 * Sim_To_DuT_Interface. The logger and all of it's functions are static so it's not necessary to create instances
 * of the logger to write a message.
 *
 * With logger's functionality it's possible to log messages and events during the execution.
 *
 * The logger will create files if necessary in which the messages will be stored. The message provider can choose if the
 * message should be logged in the file or not. The logger notices old logfiles and will remove them if the real
 * number of logfiles is higher than the configured backup count.
 *
 * @author Marco Keul
 * @version 1.0
 */
class DuTLogger {

public:
    static void initializeLogger(LoggerConfig con);
    static void logMessage(std::string msg, LOG_LEVEL level);
    static void logMessage(std::string msg, LOG_LEVEL level, bool writeToFile);
    static void changeLogLevel(LOG_TYPE typ, LOG_LEVEL level);
    static void logEvent(sim_interface::SimEvent event);

private:
    // variable to remember if the logger has been initialized yet
    static bool initialized;

    // define all required loggers
    static quill::Logger* consoleLogger;
    static quill::Logger* consoleFileLogger;
    static quill::Logger* dataLogger;

    // handlers (important to change the log_level
    static quill::Handler* consoleHandler;
    static quill::Handler* consoleFileHandler;
    static quill::Handler* buildConsoleHandler(bool enableDebugMode);
    static quill::Handler* buildFileHandler(std::string logPath, bool enableDebugMode);

    // functions to create and manage loggers
    static quill::Logger* createConsoleLogger(const char* name, bool withFileHandler);
    static quill::Logger* createDataLogger(std::string logPath);

    // help functions
    static void logWithLevel(quill::Logger* log, std::string msg, LOG_LEVEL level);
    static quill::Handler* getHandlerType(LOG_TYPE type);
    static std::string getCurrentTimestamp();

    // file management
    static std::string getLoggingPath(std::string logPath);
    static std::string initializeLoggingPath(std::string logPath);
    static void removeOldLogfiles(std::string directory, int backupCount);
};

#endif //SIM_TO_DUT_INTERFACE_DUTLOGGER_H
