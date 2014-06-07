#pragma once
class System
{
public:
	enum event_type
	{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT
	};
	virtual ~System();
	virtual bool execute() = 0;
	virtual void onNotify(const int entityID, event_type event) = 0;
};

