#include "debugLog.h"

debugLog::debugLog()
{
}

debugLog::~debugLog()
{
	
}

debugLog* debugLog::get()
{
	static debugLog _debugLog;
	return &_debugLog;
}

void debugLog::addLog(std::string LogMessage)
{
	m_log_list.push_back(LogMessage);
}

void debugLog::clearLog()
{
	m_log_list.clear();
}
