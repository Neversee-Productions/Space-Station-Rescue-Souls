#ifndef _MATH_H
#define _MATH_H

namespace app::math
{
	template<typename T> constexpr T pi() { return static_cast<T>(std::acos(-1.0)); }
	template<typename T> constexpr T toRadians(T const & rad) { return static_cast<T>(rad * (pi<T>() / static_cast<T>(180))); }
	template<typename T> constexpr T toDegrees(T const & deg) { return static_cast<T>(deg * (static_cast<T>(180) / pi<T>())); }
}

#endif // !_MATH_H
