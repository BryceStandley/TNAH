#pragma once

namespace tnah
{
	/**
	* @class state
	* @brief An abstract class that provides a common interface to all state classes. It is templated so that class can be reused in any state machine.
	*
	* @author Dylan Blereau
	* @version 01
	* @date 25/04/2021 Dylan Blereau, Started
	*
	*
	**/
	template<class entity>
	class State
	{
	public:

		/**
		* @brief virtual destructor
		*
		*/
		virtual ~State() {}

		/**
		* @brief pure virtual function that represents the enter point of the state
		* @param entity* - a pointer to the entity class
		*/
		virtual void Enter(entity*) = 0;

		/**
		* @brief pure virtual function that represents the execute stage of the state
		* @param entity* - a pointer to the entity class
		*/
		virtual void Execute(entity*) = 0;

		/**
		* @brief pure virtual function that represents the exit stage of the state
		* @param entity* - a pointer to the entity class
		*/
		virtual void Exit(entity*) = 0;
	};
    	/**
	* @class stateMachine
	* @brief An templated stateMachine class that encapsulates all state related data and functions, allowing for a cleaner integration of an FSM thst can be used in the entity's class
	*
	* @author Dylan Blereau
	* @version 01
	* @date 27/04/2021 Dylan Blereau, Started
	*
	*
	**/
template<class entity>
class StateMachine
{
private:

		/// pointer to the owner of the FSM
	entity* owner;
		/// pointer to the previous state of the FSM
	State<entity>* previousState;
		/// pointer to the current state of the FSM
	State<entity>* currentState;
		/// pointer to the global state of the FSM
	State<entity>* globalState;

public:

		/*
		* @brief Constructor that assigns the state machine to an owner and initialises all states to nullptr
		* @param FSMowner - a pointer to the owner of the finite state machine
		*/
	StateMachine(entity* FSMowner)
	{
		owner = FSMowner;
		previousState = nullptr;
		currentState = nullptr;
		globalState = nullptr;
	}

		/*
		* @brief sets the previous state of the FSM to the state provided
		* @param st - a pointer to the state you want to set as the previous state
		*/
	void setPreviousState(State<entity>* st) { previousState = st; }

		/*
		* @brief sets the current state of the FSM to the state provided
		* @param st - a pointer to the state you want to set as the current state
		*/
	void setCurrentState(State<entity>* st) { currentState = st; }

		/*
		* @brief sets the global state of the FSM to the state provided
		* @param st - a pointer to the state you want to set as the global state
		*/
	void setGlobalState(State<entity>* st) { globalState = st; }

		/*
		* @brief updates and executes the FSM depending on which state its in
		*
		*/
	void update() const
	{
		if (globalState)
			globalState->Execute(owner);
		if (currentState)
			currentState->Execute(owner);
	}

		/*
		* @brief allows for the FSM to easily change states
		* @param newState - a pointer to the state the FSM will change to
		*/
	void changeState(State<entity>*newState)
	{
		if(currentState != nullptr)
		{
			previousState = currentState;
			///exit state
			currentState->Exit(owner);
			///change current state to new state
		}
		
		currentState = newState;
		///enter the new current state
		currentState->Enter(owner);	
	}

		/*
		* @brief reverts the current state back to the previous one
		*
		*/
	void revertToPreviousState()
	{
		currentState = previousState;
	}

		/*
		* @brief gets and returns the previousState of the state machine
		* @return State<entity>*
		*/
	State<entity>* getPreviousState() { return previousState; }

		/*
		* @brief gets and returns the currentState of the state machine
		* @return State<entity>*
		*/
	State<entity>* getCurrentState() { return currentState; }

		/*
		* @brief gets and returns the globalState of the state machine
		* @return State<entity>*
		*/
	State<entity>* getGlobalState() { return globalState; }

		/*
		* @brief checks if the current state is in the same state to the one passed as parameter. Returns true if so.
		* @return bool
		*/
	bool isInState(const State<entity>&st) const
	{
		return typeid(*currentState) == typeid(st);
	}

		/*
		* @brief virtual destructor
		*/
	~StateMachine() 
	{

	}

};
}
