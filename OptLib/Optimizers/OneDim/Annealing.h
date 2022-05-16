#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		class Annealing {
			static PointVal<dim> Proceed(ConcreteState::StateStochastic<dim>& State, const FuncInterface::IFunc<dim>* f) 
			{

			}
		};
	}
	namespace StateParams
	{
		struct AnnealingParams
		{
		public:
			using OptAlgo = OptLib::ConcreteOptimizer::Annealing;
			using StateType = OptLib::ConcreteState::StateStochastic;
		public:
			StateType CreateState(double initialTemperature, double (*TemperatureFunction) (double, int))
			{
				StateType state = StateType{initialTemperature, TemperatureFunction, 0};
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
//    double E1 = f(x1); //��������� �������
//    double Ebest = E1; //������ ���������
//    double Xbest = x1; //x � ������ ���������
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