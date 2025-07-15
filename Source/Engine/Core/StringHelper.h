#pragma once
#include <string>

namespace viper {

	/// <summary>
	/// Converts all characters in a string to lowercase.
	/// </summary>
	/// <param name="str">The input string to convert.</param>
	/// <returns>A new string with all characters converted to lowercase.</returns>
	inline std::string toLower(const std::string str) {
		std::string result = str;

		// convert to lower
		for (char& c : result) {
			c = std::tolower(c);
		}

		return result;
	}
	
	/// <summary>
	/// Converts all characters in a string to uppercase.
	/// </summary>
	/// <param name="str">The input string to convert.</param>
	/// <returns>A new string with all characters converted to uppercase.</returns>
	inline std::string toUpper(const std::string str) {
		std::string result = str;

		// convert to upper
		for (char& c : result) {
			c = std::toupper(c);
		}

		return result;
	}
}