#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace FuncInterface
	{
		template <size_t dim>
		class IFunc;

		template <size_t dim>
		static PointVal<dim> CreateFromPoint(Point<dim>&& p, const IFunc<dim>* f)
		{
			PointVal<dim> out;
			out.P = std::move(p);
			out.Val = f->operator()(out.P);
			return out;
		}

		template <size_t dim>
		class IFunc
		{ // direct methods only call the function calculation
		public:
			virtual double operator () (const Point<dim>& x) const = 0;
			template<size_t count>
			std::array<double, count> operator () (const SetOfPoints<count, Point<dim>>& x) const
			{
				std::array<Point<dim>::value_type, count> out;
				for (size_t i = 0; i < count; ++i)
					out[i] = this->operator()(x[i]);
				return out;
			}
		};

		template <size_t dim>
		class IGrad
		{
		public:
			virtual Grad<dim> grad(const Point<dim>& x) const = 0;
			template<size_t count>
			std::array<double, count> grad(const SetOfPoints<count, Point<dim>>& x) const
			{
				std::array<Point<dim>::value_type, count> out;
				for (size_t i = 0; i < count; ++i)
					out[i] = this->grad(x[i]);
				return out;
			}
		};

		template <size_t dim>
		class IHess
		{
		public:
			// each Point<dim> is a row of the Hessian matrix
			virtual Hess<dim> hess(const Point<dim>& x) const = 0;
		};

		template <size_t dim>
		class IFuncWithGrad :public IFunc<dim>, public IGrad<dim>
		{ }; // 1st order optimization methods require the function itself and the gradient

		template <size_t dim>
		class IFuncWithHess :public IFuncWithGrad<dim>, public IHess<dim>
		{ }; // 2nd order methods --- function, gradient, and hessian

	} // FuncInterface
} // OptLib