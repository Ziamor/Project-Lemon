#pragma once
#include <vector>
#include "Observer.h"

class Subject
{
public:
	Subject();
	~Subject();
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notify(const int entityID, Observer::event_type event);
private:
	std::vector<Observer*> observers_;
};

