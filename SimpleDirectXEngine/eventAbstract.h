#pragma once

class eventAbstract
{
public:
	eventAbstract() {}
	virtual ~eventAbstract() {}

	virtual void getState() = 0; // get undo/redo state
	virtual eventAbstract* createCurrentState() = 0;// creates a new event where the current state is recorded and returns the event object pointer
};
