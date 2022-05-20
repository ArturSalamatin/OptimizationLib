#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		template<size_t dim,typename OneDimAlgoPrms>
		class StateGradientDescent : public StatePoint<dim>
		{
		public:
			OneDimAlgoPrms* argmin;
		public:
			StateGradientDescent(PointVal<dim>&& p0, FuncInterface::IFuncWithGrad<dim>* f,OneDimAlgoPrms* argmin_) 
				:argmin{argmin_}
			{
				ItsGuess = FuncInterface::CreateFromPoint<dim>(std::move(p0), f);
			}
		};
	} // ConcreteOptimizer

	namespace ConcreteOptimizer
	{
		template<size_t dim,typename OneDimAlgo,typename OneDimState,typename OneDimAlgoPrms>
		class GradientDescent
		{
		public:
			static PointVal<dim> Proceed(ConcreteState::StateGradientDescent<dim,OneDimAlgoPrms>& State, 
				const FuncInterface::IFuncWithGrad<dim>* f)
			{
				Point<dim> p = State.Guess().P;
				ConcreteFunc::FuncAlongGradDirection<dim> F(f, p);
				PointVal<1> lambda;
				auto OneDimAlgoState = State.argmin->CreateState(&F);
				for (int i = 0; i < 10; i++)
				{
					lambda = OptimizerInterface::OptimizerAlgorithm<1>::
						Proceed<OneDimAlgo,OneDimState, FuncInterface::IFuncWithGrad>(&OneDimAlgoState, &F);
				}
				PointVal<dim> res = State.Guess() - lambda * f->grad(State.Guess().P);
				res.Val = f->operator()(res.P);
				State.UpdateState(res);
				return res;
			}
		};
	}//ConcreteOptimizer

	namespace StateParams
	{
		template<size_t dim,typename OneDimAlgoPrms>
		struct GradientDescentParams
		{
		public:
			//using OptAlgo = OptLib::ConcreteOptimizer::GradientDescent<dim,OneDimAlgoPrms>;
			using StateType = ConcreteState::StateGradientDescent<dim,OneDimAlgoPrms>;

		public:
			PointVal<dim> p0;
			GradientDescentParams(PointVal<dim>&& p0_)
				:p0{ std::move(p0_) }{}
			StateType CreateState(FuncInterface::IFuncWithGrad<1>* f, OneDimAlgoPrms* argmin)
			{
				StateType state(std::move(p0), f, argmin);
				return state;
			}
		};
	} // StateParams
}//OptLib
