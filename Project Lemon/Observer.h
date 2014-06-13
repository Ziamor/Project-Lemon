#pragma once
class Observer
{
public:
	enum event_type
	{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT
	};
	Observer(){}// Added definition in header file so we dont have too many pesky .cpp files
	virtual ~Observer(){}
	virtual void onNotify(const int entityID, event_type event) = 0;
};

