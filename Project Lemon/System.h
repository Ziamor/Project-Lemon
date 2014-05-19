#pragma once
class System
{
public:
	virtual ~System();
	virtual bool execute() = 0;
};

