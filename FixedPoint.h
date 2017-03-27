#pragma once

#include "helper_fixed_point.h"

template <typename BaseType, int IntegerBits /* This number includes the sign bit, if any */>
class FixedPoint
{
public:
	static const int FractionalBits = sizeof(BaseType) * 8 - IntegerBits;

	FixedPoint() : _value(0) {}

	// TODO: template method for any integer arguments - possibly not doable on embedded systems due to lack of <type_traits> and std::enable_if
	FixedPoint(BaseType integerValue) : _value(integerValue << FractionalBits) {}
	FixedPoint(float fpValue) : _value(static_cast<BaseType>(fpValue * (1 << FractionalBits) /* 2^FractionalBits */) + 0.5f) {}

	FixedPoint operator+(const FixedPoint& other) const
	{
		FixedPoint result;
		result._value = _value + other._value;
		return result;
	}

	FixedPoint operator-(const FixedPoint& other) const
	{
		FixedPoint result;
		result._value = _value - other._value;
		return result;
	}

	FixedPoint& operator+=(const FixedPoint& other)
	{
		_value += other._value;
		return *this;
	}

	FixedPoint& operator-=(const FixedPoint& other)
	{
		_value -= other._value;
		return *this;
	}

	FixedPoint operator*(const FixedPoint& other) const
	{
		typename detail::expand_type<BaseType>::type intermediateResult = _value;
		intermediateResult *= other._value;

		FixedPoint result;
		result._value = (BaseType)(intermediateResult >> FractionalBits);
		return result;
	}

	BaseType toInt() const
	{
		return _value >> FractionalBits;
	}

	float toFloatingPoint() const
	{
		static const float fractMultiplier = 1.0f / (1 << FractionalBits);
		static const BaseType fractMask = (1 << FractionalBits) - 1;
		return (float)toInt() + (_value & fractMask) * fractMultiplier;
	}

private:
	BaseType _value;
};