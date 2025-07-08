#pragma once
#include <cstdlib>

namespace viper {
	namespace random {

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline int getRadomInt() { return rand(); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="max"></param>
		/// <returns></returns>
		inline int getRandomInt(int max) { return rand() % max; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="max"></param>
		/// <param name="min"></param>
		/// <returns></returns>
		inline int getRandomInt(int max, int min) { return rand() % max; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline float getRandomFloat() { return (float)rand() / RAND_MAX; }
	}
}
