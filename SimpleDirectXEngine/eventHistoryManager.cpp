#include "eventHistoryManager.h"

eventHistoryManager::eventHistoryManager()
{
}

eventHistoryManager::~eventHistoryManager()
{
}

eventHistoryManager* eventHistoryManager::get()
{
	static eventHistoryManager _eventHistoryManager;
	return &_eventHistoryManager;
}

void eventHistoryManager::undo()
{
	if (!m_undoEventStack.empty())
	{
		m_redoEventStack.push(m_undoEventStack.top()->createCurrentState()); // create new redo event state from current undo event, then put into redo stack
		m_undoEventStack.top()->getState(); // set state to undo event state
		m_undoEventStack.pop(); // remove undo event from stack
	}
}

void eventHistoryManager::redo()
{
	if (!m_redoEventStack.empty())
	{
		m_undoEventStack.push(m_redoEventStack.top()->createCurrentState()); // create new undo event state from current redo event, then put into undo stack
		m_redoEventStack.top()->getState(); // set state to redo event state
		m_redoEventStack.pop(); // remove redo event from stack
	}
}

void eventHistoryManager::addToUndoStack(eventAbstract* _event)
{
	while(!m_redoEventStack.empty()) // empty redo stack
	{
		m_redoEventStack.pop();
	}

	m_undoEventStack.push(_event);
}
