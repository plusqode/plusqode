/*
 * Copyright (C) 2026 - PlusQode - www.plusqode.com - plusqode@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



   #include "core/plogger.h"

   
   

PLogger::PLogger(const QString& fileName, const QString& level, const QString& type) {

    this->type = type;
    setLevel(level);

    file = new QFile(fileName);

    setType(type);   

    if(type.toLower() == "stdout")
        outStreamFile = new QTextStream(stdout);
    else
        outStreamFile = new QTextStream(file);

    (*outStreamFile) << "Start PLogger" << "\n";

}

PLogger::~PLogger() {

    outStreamFile->flush();
    file->close();

    delete outStreamFile;
    delete file;

}

void PLogger::setLevel(const QString& levelStr) {

    if(levelStr.toUpper() == "DEBUG") level = DEBUG;
    else if(levelStr.toUpper() == "INFO") level = INFO;
    else if(levelStr.toUpper() == "WARNING") level = WARNING;
    else if(levelStr.toUpper() == "SQL") level = SQL;
    else if(levelStr.toUpper() == "ERROR") level = ERROR;
    else if(levelStr.toUpper() == "FATAL") level = FATAL;
    else level = DEBUG;

}


void PLogger::setType(const QString& type) {

    if(type.toUpper() == "APPEND") {
        if (!file->open(QIODevice::Append | QIODevice::Text)) {
            std::cout << "Error in the method PLogger::setType(" << type.toStdString() << ")" << "\n";
            return;
        }
    }
    else if (type.toUpper() == "OVERWRITE")
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cout << "Error in the method PLogger::setType(" << type.toStdString() << ")" << "\n";
            return;
        }

}


void PLogger::write(Level _level, const QVariant& msg,
                     QString color, int bgc, int fgc,
                     QString levelStr) {

    if(level > _level)
        return;

    PString str = msg.toString();

    if(levelStr.isNull())
    switch (_level) {

        case DEBUG: levelStr = "DEBUG"; break;
        case INFO:  levelStr = "INFO"; break;
        case WARNING: levelStr = "WARNING"; break;
        case SQL: levelStr = "SQL"; break;
        case ERROR: levelStr = "ERROR"; break;
        case FATAL: levelStr = "FATAL"; break;
        default: break;

    }

#if defined (Q_OS_LINUX)
    if(type.toLower() == "stdout" && color.isNull() && fgc == -1 && bgc == -1) {
        switch (_level) {
            case DEBUG: color = "green"; break;
            case INFO:  color = "high_purple"; break;
            case WARNING: color = "high_cyan"; break;
            case SQL: color = "white"; break;
            case ERROR: color = "red"; break;
            case FATAL: color = "red"; break;
            default: color = "white";
        }
    }
    if(type.toLower() == "stdout") {
        if(bgc != -1 && fgc != -1)
            str = PString(msg.toString()).   colorize(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("bgc", bgc)->append("fgc", fgc)))));
        else
            str = PString(msg.toString()).color(color);
    }

#endif

    if(type.toLower() == "stdout")
        (*outStreamFile) << PString(QString("[PlusQode %1]$").arg(levelStr)) << str << "\n";
    else
        (*outStreamFile) << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << "] " + levelStr + ":" << str << "\n";

}

void PLogger::debug(const QVariant& msg) {

    write(DEBUG, msg);

}

void PLogger::info(const QVariant& msg) {

    write(INFO, msg);

}

void PLogger::warning(const QVariant& msg) {

    write(WARNING, msg);

}

void PLogger::sql(const QVariant& msg) {

    write(SQL, msg);

}

void PLogger::error(const QVariant& msg) {

    write(ERROR, msg);

}

void PLogger::fatal(const QVariant& msg) {

    write(FATAL, msg);

}







PLogManager::~PLogManager() {

    LogMap::Iterator it;
    for ( it = logMap.begin(); it != logMap.end(); ++it )
        delete *it;

}

void PLogManager::init(const QString& logName, const QString& fileName, const QString& level, const QString& type) {

    logMap[logName] = new PLogger(fileName, level, type);

}

void PLogManager::initByConfigFileName(const QString& logName, const QString& configFileName) {

    PConfigurationManager* config = PSinglConfigurationManager::instance();

    qDebug() << " - Logger ===>" << logName << configFileName;

    config->init(logName, configFileName);
    config->show(logName);

    QString level = config->value(logName, "logger.level").toString();
    QString basedir = config->value(logName, "logger.basedir").toString();
    QString logFileName = config->value(logName, "logger.filename").toString();
    QString type = config->value(logName, "logger.type").toString();

    logFileName = basedir + "/" + logFileName;

    init(logName, logFileName, level, type);

}

PLogger* PLogManager::log(const QString& logName) {

    if(logMap.find(logName) == logMap.end())
        return 0;

    return logMap[logName];

}


void PLogManager::debug(const QString& logName, const QVariant& msg) {

    log(logName)->debug(msg);

}


void PLogManager::info(const QString& logName, const QVariant& msg) {

    log(logName)->info(msg);

}

void PLogManager::warning(const QString& logName, const QVariant& msg) {

    log(logName)->warning(msg);

}

void PLogManager::sql(const QString& logName, const QVariant& msg) {

    log(logName)->sql(msg);

}

void PLogManager::error(const QString& logName, const QVariant& msg) {

    log(logName)->error(msg);

}

void PLogManager::fatal(const QString& logName, const QVariant& msg) {

    log(logName)->fatal(msg);

}


void PLogManager::initByPlusQodeFile() {

    PLogManager* logManager = PSinglLogManager::instance();
    logManager->initByConfigFileName("plusqode", PString(QString("%1/plusqode.cfg").arg(PGlobal::confFilePath())));

}


void PLogManager::demo() {

    PLogManager* logManager = PSinglLogManager::instance();
    logManager->init("curr-plusqode", "plusqode.log", "debug");
    PLogger* logger = logManager->log("curr-plusqode");
    logger->debug("Start PlusQode Logger");

}

void PLogManager::demoByConfigFileName() {

    PLogManager* logManager = PSinglLogManager::instance();
    logManager->initByConfigFileName("plusqode-log", PString(QString("%1/plusqode.cfg").arg(PGlobal::confFilePath())));
    PLogger* logger = logManager->log("plusqode-log");
    logger->debug("Start PlusQode Logger ");

    logManager->debug("plusqode-log", "log by log manager");

}











PLog:: PLog(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PLog:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString logName = source_args.value<PVariantMapPtr>()->include("logName") ? source_args.value<PVariantMapPtr>()->operator[]("logName").toString() : QVariant(QString("plusqode")).toString();args.removeByKey("logName");
QString color = source_args.value<PVariantMapPtr>()->include("color") ? source_args.value<PVariantMapPtr>()->operator[]("color").toString() : QVariant(  
                QString()).toString();args.removeByKey("color");
int bgc = source_args.value<PVariantMapPtr>()->include("bgc") ? source_args.value<PVariantMapPtr>()->operator[]("bgc").toInt() : QVariant(-1).toInt();args.removeByKey("bgc");
int fgc = source_args.value<PVariantMapPtr>()->include("fgc") ? source_args.value<PVariantMapPtr>()->operator[]("fgc").toInt() : QVariant(-1).toInt();args.removeByKey("fgc");
QString levelStr = source_args.value<PVariantMapPtr>()->include("levelStr") ? source_args.value<PVariantMapPtr>()->operator[]("levelStr").toString() : QVariant(  
                      
                QString()).toString();args.removeByKey("levelStr");


    this->logName = logName;
    this->color = color;
    this->bgc = bgc;
    this->fgc = fgc;
    this->levelStr = levelStr;

}

PLog::PLog(const QString& logName, PLogger::Level level) : logName(logName) {

    this->level = level;

}


PLog::~PLog() {

    PLogManager* logManager = PSinglLogManager::instance();
    logManager->log(logName)->write(level, buffer, color, bgc, fgc, levelStr);
    logManager->log(logName)->outStreamFile->flush();

}

PLog& PLog::debug(const QVariant& msg) {

    this->level = PLogger::DEBUG;

    if(!buffer.isNull())
        buffer += " ";

    buffer += msg.toString();
    return *this;

}

PLog& PLog::info(const QVariant& msg) {

    this->level = PLogger::INFO;

    if(!buffer.isNull())
        buffer += " ";
    buffer += msg.toString();

    return *this;

}

PLog& PLog::warning(const QVariant& msg) {

    this->level = PLogger::WARNING;

    if(!buffer.isNull())
        buffer += " ";
    buffer += msg.toString();

    return *this;

}

PLog& PLog::sql(const QVariant& msg) {

    this->level = PLogger::SQL;

    if(!buffer.isNull())
        buffer += " ";
    buffer += msg.toString();

    return *this;

}

PLog& PLog::error(const QVariant& msg) {

    this->level = PLogger::ERROR;

    if(!buffer.isNull())
        buffer += " ";
    buffer += msg.toString();

    return *this;

}

PLog& PLog::fatal(const QVariant& msg) {

    this->level = PLogger::FATAL;

    if(!buffer.isNull())
        buffer += " ";
    buffer += msg.toString();

    return *this;

}

PLog& PLog::operator<<(const QVariant& msg) {

    buffer += " " + msg.toString();
    return *this;

}

PLog& PLog:: setColor(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "setColor:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString color = source_args.value<PVariantMapPtr>()->include("color") ? source_args.value<PVariantMapPtr>()->operator[]("color").toString() : QVariant(  QString()).toString();args.removeByKey("color");
int bgc = source_args.value<PVariantMapPtr>()->include("bgc") ? source_args.value<PVariantMapPtr>()->operator[]("bgc").toInt() : QVariant(-1).toInt();args.removeByKey("bgc");
int fgc = source_args.value<PVariantMapPtr>()->include("fgc") ? source_args.value<PVariantMapPtr>()->operator[]("fgc").toInt() : QVariant(-1).toInt();args.removeByKey("fgc");


    this->color = color;
    this->bgc = bgc;
    this->fgc = fgc;
    return *this;

}

PLog& PLog::setLevelStr(QString levelStr) {

    this->levelStr = levelStr;
    return *this;

}


void PLog::demo() {

    PLogManager* logManager = PSinglLogManager::instance();
    logManager->init("plusqode", "plusqode.log", "debug");

    PLog("plusqode").debug() << "default message";
    PLog("plusqode").warning() << "warning message";

    PLog("plusqode").debug("default message");

}
