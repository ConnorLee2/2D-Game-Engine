#pragma once
#include <memory>
#include <stack>
#include "State.hpp"

/*
	Handles all of our states
*/


namespace GameEngine
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef state, bool replacing = true);
		void RemoveState();

		void ProcessStateChanges();

		StateRef &GetActiveState();
		void CleanUp();
	private:
		std::stack<StateRef> states;
		StateRef newState;

		bool isRemoving;
		bool isAdding;
		bool isReplacing;
	};
}