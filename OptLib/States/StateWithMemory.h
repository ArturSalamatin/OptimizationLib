#ifndef STATEWITHMEMORY_H
#define STATEWITHMEMORY_H

#include <vector>
#include "../Points/SetOfPoints/PointVal/PointVal.h"
#include "../Points/Definitions.h"
#include "../Functions/Interface/FuncInterface.h"
#include "StateInterface.h"
#include "State.h"

namespace OptLib
{
	namespace StateWithMemory
	{
		template<size_t dim,  typename state = StateInterface::IStateSimplex<dim, SimplexValSort<dim>>>
		class StateSimplexMemory : public state
		{
			state* State;

		public:
			StateSimplexMemory(state* State, const FuncInterface::IFunc<dim>* f) : 
				state(State->GuessDomain().PointsNoVal(), f), 
				State{ State }
			{
				a_Memory.push_back(*State); // copies current state to a memory
			}
			const std::vector<state>& Memory() const { return a_Memory; }

			void SetDomain(SetOfPoints<dim + 1, PointVal<dim>>&& newDomain) override
			{
				(*State).SetDomain(std::move(newDomain));
				a_Memory.push_back(*State); // copies updated state to a memory
			}

		protected:
			mutable std::vector<state> a_Memory;
		};

		/// <summary>
		/// A State that memorizes all its previous states for StatePoint
		/// </summary>
		template<size_t dim>
		class StatePointImproved : public ConcreteState::StatePoint<dim>
		{
			ConcreteState::StatePoint<dim>* State;

		public:
			StatePointImproved(ConcreteState::StatePoint<dim>* State) : State{ State }
			{
				a_Memory.push_back(new ConcreteState::StatePoint<dim>(*State)); // copies current state to a memory
			}

			void UpdateState(const PointVal<dim>& v) override
			{
				(*State).UpdateState(v);
				a_Memory.push_back(new ConcreteState::StatePoint<dim>(*State)); // copies updated state to a memory
			}

			const std::vector<ConcreteState::StatePoint<dim>*>& Memory() { return a_Memory; }

		protected:
			std::vector<ConcreteState::StatePoint<dim>*> a_Memory;
		};


	} // StateWithMemory
} // OptLib

#endif