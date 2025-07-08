#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace viper {
	namespace math {
		constexpr float pi = 3.1415926535897932384626433832795f;
		constexpr float twoPi = 2 * pi;
		constexpr float halfPi = pi * 0.5f;

		/// <summary>
		///	Converts an angle from radians to degrees.
		/// </summary>
		/// <param name="rad">The angle in radians to convert.</param>
		/// <returns>The equivalent angle in degrees.</returns>
		constexpr float radToDeg(float rad) { return rad * 180 / pi; }

		/// <summary>
		/// Converts an angle from degrees to radians.
		/// </summary>
		/// <param name="deg">The angle in degrees to convert.</param>
		/// <returns>The angle in radians.</returns>
		constexpr float degToRad(float deg) { return deg * pi / 180; }

		using std::min;
		using std::max;
		//using std::clamp;
		using std::sqrt;
		using std::sqrtf;
		using std::sin;
		using std::sinf;
		using std::cos;
		using std::cosf;

	}
}
