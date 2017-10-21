
#include "stdafx.h"
#include "Util.h"

namespace RJ {

	const int NOT_FOUND = -1;


	/**
	 * Returns index of character in word. -1 if not found.
	 * @param word
	 */
	int IndexOf(std::string word, char character)
	{
		size_t indexOfFoundWord = word.find(character);
		// find sets values to a really random huge value if not found.
		// we check for such values and return not found
		if (indexOfFoundWord < 0 || indexOfFoundWord > word.length())
		{
			return NOT_FOUND;
		}
		else
		{
			return indexOfFoundWord;
		}
	} // IndexOf

} // end of RJ namespace