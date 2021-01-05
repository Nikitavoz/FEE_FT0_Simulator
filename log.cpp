#include "log.h"

Log::Log(const bool createlogfile, const QString caller_name, const QString logFileName){
    this->callername = caller_name;
    if(createlogfile){
        if(!QDir("Logs").exists()) QDir().mkdir("Logs");
        logfile.setFileName(logFileName);
        if (!logfile.open(QFile::WriteOnly | QIODevice::Append | QFile::Text))
            this->sendMessage("Can't open log file: " + logFileName, console);
        else
            out.setDevice(&logfile);
    }
}

void Log::sendMessage(QString message, OutputDevice device){
    switch (device) {
    case console: {
        printf(qPrintable("[" + QTime::currentTime().toString("hh:mm:ss") + "] " + this->callername + " >> " + message + "\n"));
        break;}
    case file:    {
        if(message.contains("IPbus")) message = "\n" + message;
        if(saveToFile) out    << message << endl;
        emit LogMessage(message);
        break;}
    case both:    {
        sendMessage(message, console);
        sendMessage(message, file);
        break;}
    default: return;

    }
}



Log::~Log(){logfile.close();}