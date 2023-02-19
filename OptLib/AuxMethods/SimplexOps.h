#pragma once
#include <functional>

namespace OptLib
{
	/// <summary>
	/// An alias for std::array. It is required for the ease of RawPoint construction.
	/// </summary>
	template<size_t dim>
	using Point = std::array<double, dim>;

	//template<size_t dim>  // переменная показывающая кол-во значений в массиве
	template<class Stream, size_t dim>
	Stream& operator << (Stream& o, const Point<dim>& p)
	{
		o << '(' << p[0];
		for (size_t i = 1; i < p.size(); ++i)
		{
			o << ", " << p[i];
		}
		return o << ')';
	}


	namespace SimplexOps
	{
		namespace UnaryOps
		{
			template <class Scalar>
			struct plus 
			{
				plus(Scalar value) : scalar{ value } {}

				template<class T>
				T operator() (const T& lhs)
				{
					return lhs + scalar;
				}

			protected:
				Scalar scalar;
			};

			template <class Scalar>
			struct minus
			{
				minus(Scalar value) : scalar{ value } {}

				template<class T>
				T operator() (const T& lhs)
				{
					return lhs - scalar;
				}

			protected:
				Scalar scalar;
			};
			
			template <class Scalar>
			struct mult
			{
				mult(Scalar value) : scalar{ value } {}

				template<class T>
				T operator() (const T& lhs)
				{
					return lhs * scalar;
				}

			protected:
				Scalar scalar;
			};
		}
		
		namespace BinaryOps
		{
			template <class T = void>
			using plus = std::plus<T>;

			template <class T = void>
			using minus = std::minus<T>;

			template <class T = void>
			using multiplies = std::multiplies<T>;
		}
	}
}

