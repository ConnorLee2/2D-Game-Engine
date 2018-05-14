#include "StateMachine.hpp"

namespace GameEngine
{
	void StateMachine::AddState(StateRef state, bool replacing)
	{
		// Adds a state onto the state and is the new state that will be running (other states will be paused)
		isAdding = true;
		isReplacing = replacing;

		newState = std::move(state);
	}

	void StateMachine::RemoveState()
	{
		// Manually remove the top state (state changes are handled in the next method)
		isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		// Runs at the start of each game loop
		// Remove the top level state if the stack isnt empty
		if (isRemoving && !states.empty())
		{
			states.pop();

			// if the stack isnt empty, set the new top state to be the running state
			if (!states.empty())
			{
				states.top()->Resume();
			}

			isRemoving = false;
		}

		// If adding a new state
		if (isAdding)
		{
			// If stack isn't empty
			if (!states.empty())
			{
				// Top state replaced by new state
				if (isReplacing)
				{
					states.pop();
				}

				// Pause top level state
				else
				{
					states.top()->Pause();
				}
			}

			// Push new state to top and initialise
			states.push(std::move(newState));
			states.top()->Init();
			isAdding = false;
		}
	}

	StateRef &StateMachine::GetActiveState()
	{
		// Returns the top level state (the state that is running in terms of drawing/game logic)
		return states.top();
	}
	void StateMachine::CleanUp()
	{
		if (states.empty())
		{
			// do nothing
		}

		// Remove all the states
		else
		{
			while (!states.empty())
			{
				states.pop();
			}
		}
	}
}