#include "Subject.h"

Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::addObserver(Observer* observer)
{
	for (size_t i = 0; i < observers_.size(); i++)
	{
		if (observer == observers_[i])
			return; // Observer already listening
	}

	for (size_t i = 0; i < observers_.size(); i++)
	{
		if (observers_[i] == nullptr)
		{
			observers_[i] = observer; //we found an empty slot, set it to point to new observer
			return;
		}
	}
	observers_.push_back(observer); // No empty spot was found so just add to the end
}

void Subject::removeObserver(Observer* observer)
{
	for (size_t i = 0; i < observers_.size(); i++)
	{
		if (observer == observers_[i])
			observers_[i] = nullptr;//we found the object to remove, set it to a nullptr
	}
}
void Subject::notify(const int entityID, Observer::event_type event)
{
	for (size_t i = 0; i < observers_.size(); i++)
	{
		observers_[i]->onNotify(entityID, event);
	}
}