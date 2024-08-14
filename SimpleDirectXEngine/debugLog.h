#pragma once
#include <string>
#include <vector>

class debugLog
{
public:
	static debugLog* get();

	void addLog(std::string LogMessage);
	void clearLog();

protected:
	std::vector<std::string> m_log_list;

	friend class uiDebugConsole;
private:
	debugLog();
	~debugLog();
	debugLog(debugLog const&) {}
	debugLog& operator=(debugLog const&) {}
};