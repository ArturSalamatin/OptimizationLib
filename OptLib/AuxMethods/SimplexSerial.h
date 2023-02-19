#pragma once
#include <functional>
#include <algorithm>
#include <array>

#include"SimplexOps.h"

namespace OptLib
{
	template<size_t dim>
	Point<dim> operator + (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result; // ����� ������ � ��� �� ���-��� ��������
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::plus<>{});
		return result;  // �� �� ������, ������������ �� ����� � ���������, ������
	}
	template<size_t dim>
	Point<dim> operator + (const Point<dim>& arr1, double consta)
	{
		Point<dim> result; 
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::plus<double>{consta });
		return result;  
	}
	template<size_t dim>
	Point<dim> operator + (double consta ,const Point<dim>& arr1)
	{
		return arr1 + consta
	}
	template<size_t dim>
	Point<dim> operator - (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result; 
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::minus<>{});
		return result;  
	}
	template<size_t dim>
	Point<dim> operator - (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::minus<double>{consta });
		return result;
	}
	template<size_t dim>
	Point<dim> operator -  (double consta, const Point<dim>& arr1)
	{
		return arr1 - consta;
	}
	template<size_t dim>
	double operator* (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps:multiplies<double>{consta });

		return result;
	}
	template<size_t dim>
	double abs(const Point<dim>& arr1)
	{
		Point<dim> result;
		double res = 0;
		std::transform(arr1.begin(), arr1.end(), arr1.begin(), result.begin(), std::multiplies<>{});
		for (auto& el : result)
			res += el;
		return sqrt(res);
	}
}

