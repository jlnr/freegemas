#include "log.h"

using namespace std;


string Log::ToString(TLogLevel T){
    switch(T){
    case logERROR:
        return "ERROR";
        break;
    case logWARNING:
        return "WARNING";
        break;
    case logINFO:
        return "INFO";
        break;
    case logDEBUG:
    default:
        return "DEBUG";
        break;
    }
}
string Log::cRed = "\033[31m";
string Log::cGreen =  "\033[32m";
string Log::cYellow = "\033[33m";
string Log::cBlue = "\033[34m";
string Log::cPurple = "\033[35m";

string Log::nRed = "\033[01;31m";
string Log::nGreen =  "\033[01;32m";
string Log::nYellow = "\033[01;33m";
string Log::nBlue = "\033[01;34m";
string Log::nPurple = "\033[01;35m";

string Log::bRed = "\033[1m\033[01;41m";
string Log::bGreen =  "\033[1m\033[01;42m";
string Log::bYellow = "\033[1m\033[01;43m";
string Log::bBlue = "\033[1m\033[01;44m";
string Log::bPurple = "\033[1m\033[01;45m";



string Log::cDef = "\033[00m";


string Log::CON(string s){
    return cGreen + "[++ Constructor] " + s + cDef;
}

string Log::DES(string s){
    return cRed + "[-- Destructor] " + s + cDef;
}

std::ostringstream& Log::Get(TLogLevel level)
{

    os << "[" << ToString(level) << "] ";
    return os;
}

Log::~Log(){
    os << Log::cDef << std::endl;
    if(output){
        fprintf(stderr, "%s", os.str().c_str());
        fflush(stderr);
    }
}

bool Log::output = true;
