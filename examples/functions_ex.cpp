
#include <iostream>
#include <optlib/Points/SetOfPoints/PointVals/Point/Point.h>

#include <optlib/Functions/Himmel.h>
#include <optlib/Functions/Rozenbrock.h>
#include <optlib/Functions/FuncAlongGradDirection.h>
#include <optlib/Functions/FunctionParam.h>
#include <optlib/Functions/Paraboloid.h>

using namespace OptLib;

int main() try
{
     // testing Function
    ConcreteFunc::Himmel Him{};
    double result1{Him(Point<2>{2.0, 1.0})};
    ConcreteFunc::Rozenbrok Roz{};
    double result2{Roz(Point<2>{2.0, 1.0})};

    ConcreteFunc::FuncAlongGradDirection<2> f{&Him, Point<2>{2.0, 1.0}};
    auto gr{f.grad(Point<1>{3.0})};

    // testing FunctionParam
    auto fp{ConcreteFuncParam::LinearFuncWithGrad{}};
    fp(Point<1>{1.0}, Point<1>{2.0});
    
    ConcreteFunc::Paraboloid<3> fpp{
        Hess<3>{
            Point<3>{1.0, 2.0, 3.0},
            Point<3>{1.0, 16.0, 3.0},
            Point<3>{1.0, 2.0, 7.0}}};
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
}