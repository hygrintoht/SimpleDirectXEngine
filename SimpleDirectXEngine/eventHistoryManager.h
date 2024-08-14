#pragma once
#include "stack"
#include "eventAbstract.h"

class eventHistoryManager
{
public:
	static eventHistoryManager* get();

	void undo();
	void redo();

	void addToUndoStack(eventAbstract* _event); // note: deletes all redo events

protected:

	std::stack<eventAbstract*> m_undoEventStack; // event history
	std::stack<eventAbstract*> m_redoEventStack; // undo history

private:
	eventHistoryManager();
	~eventHistoryManager();
	eventHistoryManager(eventHistoryManager const&) {}
	eventHistoryManager& operator = (eventHistoryManager) {}
};
