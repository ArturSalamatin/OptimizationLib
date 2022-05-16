#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Direct methods require sorted simplex points with respect to f(x)
		/// </summary>
		template<size_t dim>
		using StateDirect =  StateInterface::IStateSimplex<dim, SimplexValSort<dim>>;

		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		class StateSegment : public StateInterface::IStateSimplex<1, SimplexValNoSort<1>>
		{
		public:
			StateSegment(const StateSegment&) = default;
			StateSegment(SetOfPoints<2, Point<1>>&& State, FuncInterface::IFunc<1>* f)
				:
				StateInterface::IStateSimplex<1, SimplexValNoSort<1>>(std::move(OrderPointsInSegment(State)), f)
			{}

		protected:
			SetOfPoints<2, Point<1>> OrderPointsInSegment(SetOfPoints<2, Point<1>>& setOfPoints)
			{
				if (setOfPoints[0][0] > setOfPoints[1][0])
					std::swap(setOfPoints[0], setOfPoints[1]);
				return setOfPoints;
			}
		};

		/// <summary>
		/// First and second order methods require only a point rather than entire simplex for optimization
		/// </summary>
		template<size_t dim>
		class StatePoint : public StateInterface::IState<dim>
		{
		protected:
			PointVal<dim> dx{};
		public:
			bool IsConverged(double abs_tol, double rel_tol) const override
			{
				auto& std = dx;
				auto var{ abs<dim>(dx / Guess()) };
				for (int i = 0; i < dim; i++)
				{
					bool f = (((std[i]) < abs_tol) || (var[i] < rel_tol)) && (((std.Val) < abs_tol) || (var.Val < rel_tol));
					if (!f) return false;
				}
				return true;
			}

			virtual void UpdateState(const PointVal<dim>& v)
			{
				dx = abs<dim>(v - Guess());
				ItsGuess = v;
			}

		};

		/// <summary>
		/// Stochastic methods require multiple initial points
		/// </summary>
		template<size_t dim>
		class StateStochastic : public StateInterface::IState<dim>
		{
		protected:
			double temperature;
			double(*Temperature) (double, int);
			int iteration;
			Point<dim> NextRandomState(Point<dim> x, double h) 
			{
				for (int i = 0; i < dim; i++) {
					double r = ((double)rand() / RAND_MAX);
					x[i] = 2 * r * h + x - h;
				}
				return x;
			}
		public:
			StateStochastic(SetOfPoints<dim + 1, Point<dim>>&& State, FuncInterface::IFunc<dim>* f, double initialTemperature, double (*TemperatureFunction) (double, int)) : 
				StateInterface::IState<dim>(State, f), 
				temperature{ initialTemperature }, Temperature{ TemperatureFunction }, iteration{ 0 } {}
			bool IsConverged(double endTemperature, double) const override
			{
				return temperature > endTemperature ? true : false;
			}

			void UpdateState(double h)
			{
				iteration++;
				temperature = Temperature(temperature, iteration);
				ItsGuess = NextRandomState(Guess().P, h);
			}
		};
	} // ConcreteState
} // OptLib