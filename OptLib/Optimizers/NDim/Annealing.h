#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		class Annealing {
			static PointVal<dim> Proceed(ConcreteState::StateStochastic<dim>& State, const FuncInterface::IFunc<dim>* f) 
			{
				double dp = exp((State.Guess().Val - State.currentGuess.Val) / t);
				if (dp > 1)
				{
					State.ChangeGuess();
				}
				else 
				{
					double p = (double)rand() / RAND_MAX;
					if (dp > p) 
					{
						State.ChangeGuess();
					}
				}
			}
		};
	}
	namespace StateParams
	{
		struct AnnealingParams
		{
		protected:
			using OptAlgo = OptLib::ConcreteOptimizer::Annealing;
			using StateType = OptLib::ConcreteState::StateStochastic;
			double h;
			double endTemperature;
			double initialTemperature;
			double (*TemperatureFunction) (double, int);
			Point<dim> currentPoint;
		public:
			AnnealingParams(Point<dim>&& sop, double step, double temperature_end) :
				h{ step }, endTemperature{ temperature_end }, currentPoint{ std::move(sop) } {}
			StateType CreateState(FuncInterface::IFunc<dim>* f)
			{
				state = new StateStochastic(SetOfPoints<dim + 1, Point<dim>> && State, f, initialTemperature, TemperatureFunction)
				return state;
			}
	}
}

//#include <iostream>
//double T(double t) {
//    return t -= 0.01;
//}
//double T(int i, int kmax) {
//    return 1 - (double)i / kmax;
//}
//double A(double x, double h) {
//    double r = ((double)rand() / RAND_MAX);
//    double res = 2 * r * h + x - h;
//    std::cout << r << " ";
//    std::cout << res << '\n';
//    return res;
//}
//double annealing(double x1, double h, double (*f)(double x), double (*T)(int, int), int k, double Tend = 0)
//{
//    double E1 = f(x1); //начальная энергия
//    double Ebest = E1; //лучшее состояние
//    double Xbest = x1; //x в лучшем состоянии
//    double E2;
//    int i = 0;
//    double t = T(i, k);
//    while (t > Tend)
//    {
//        double x2 = A(x1, h);
//        E2 = f(x2);
//        if (E2 < Ebest)
//        {
//            Xbest = x2;
//            Ebest = E2;
//        }
//        else {
//            double dp = exp((E1 - E2) / t);
//            if (dp > 1)
//            {
//                x1 = x2;
//                E1 = E2;
//            }
//            else
//            {
//                double p = (double)rand() / RAND_MAX;
//                if (dp > p)
//                {
//                    x1 = x2;
//                    E1 = E2;
//                }
//            }
//        }
//        i++;
//        t = T(i, k);
//    }
//    return Xbest;
//}
//double Fexample(double x) {
//    //return x*x - x * x * x+x;
//    return x * x;
//}
//int main()
//{
//    std::cout << annealing(10, 0.7, Fexample, T, 1000);
//}