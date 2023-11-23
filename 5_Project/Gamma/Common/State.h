#pragma once
#include <functional>

template<class T>
class State 
{
public:
	static State<T>* current;

public:
	State<T>() :
	{
		if (!current)
		{
			current = this;
		}
	}

public:
	void SetNext(State<T>*);
	void SetPrevious(State<T>*);
	void SetOnEnter(std::function<void()>);
	void SetOnExit(std::function<void()>);
	virtual void OnEnter();
	virtual void OnExit();
	static void Next();
	static void Previous();
	static void Change(State<T>*);
	std::function<void()> onExitCallback;
	std::function<void()> onEnterCallback;

private:
	State<T>* previous_= nullptr;
	State<T>* next_=nullptr;
};

template<class T>
void State<T>::SetNext(State<T>* next)
{
	next_ = next;
}

template<class T>
void State<T>::SetPrevious(State<T>* previous)
{
	previous_ = previous;
}

template<class T>
void State<T>::SetOnEnter(std::function<void()> enter)
{
	onEnter = enter;
}

template<class T>
void State<T>::SetOnExit(std::function<void()> exit)
{
	onExit = exit;
}

template<class T>
void State<T>::OnEnter()
{
	onEnterCallback();
}

template<class T>
void State<T>::OnExit()
{
	onExitCallback();
}

template<class T>
void State<T>::Next()
{
	Change(current->next_);
}

template<class T>
void State<T>::Previous()
{
	Change(current->previous_);
}

template<class T>
void State<T>::Change(State<T>* state_)
{
	current->OnExit();
	current = state_;
	current->OnEnter();
}