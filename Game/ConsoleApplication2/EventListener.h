#pragma once

/**Used as an interface for the event dispatcher*/
/*Objects wanting to receive events must inherit from this*/

class EventListener
{
public:
	enum class GenericEvent
	{
	};	

	enum class KeyDownEvent
	{
		UP = 1000,
		LEFT,
		DOWN,
		RIGHT
	};

	enum class KeyUpEvent
	{
		UP = 2000,
		LEFT,
		DOWN,
		RIGHT
	};


	void onEvent(KeyDownEvent evt)
	{
		onKeyDown(evt);
	}

	void onEvent(KeyUpEvent evt)
	{
		onKeyUp(evt);
	}

	void onEvent(GenericEvent evt)
	{
		onGenericEvent(evt);
	}


	virtual void onKeyDown(KeyDownEvent) {};
	virtual void onKeyUp(KeyUpEvent) {};
	virtual void onGenericEvent(GenericEvent) {};
};