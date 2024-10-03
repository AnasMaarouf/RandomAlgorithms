#include <iostream>
#include <stdint.h>
using namespace std;

/*
	The "stringSearch" function and "stringSearch" struct is c-language compatible.
	The name speaks for itself. Search for a specific string in a another string.
*/

struct stringSearchResult {
	uint64_t count;
	uint64_t stringPositions[64];
};

stringSearchResult StringSearch(char* input_Data, uint64_t inputDataSize, char* comparingDataString, uint64_t comparingDataSize);

int main()
{
	char data[41] = { '1','2','3','4','5','6','H','e','l','l','o',' ','W','o','r','l','d','!','1','2','3','4','5','6','H','e','l','l','o',' ','W','o','r','l','d','!','1','2','3','4','6' };

	char cmpString[5] = { 'W','o','r','l','d' };	// Search for "World" in the data array

	stringSearchResult r = StringSearch(data, 41, cmpString, 1);

	cout << "Number of strings found: " << r.count << endl;
	cout << "Position: " << endl;
	for(uint64_t i = 0; i < 64; i++)
		cout << i + 1 << ". " << r.stringPositions[i] << endl;

	return 0;
}



stringSearchResult StringSearch(char* input_Data, uint64_t inputDataSize, char* comparingDataString, uint64_t comparingDataSize) {
	// Initialize resulting struct.
	stringSearchResult result = { 0,{0} };

	// If input data and the comparing data is null return immediatly.
	if ((input_Data == NULL || input_Data == nullptr) || (comparingDataString == NULL || comparingDataString == nullptr))
		return result;

	uint64_t comparingDataStringIndex = 0;
	// Compare each character/byte of the comparing data variable with the input data.
	for (uint64_t inputDataIndex = 0; inputDataIndex < inputDataSize; inputDataIndex++) {
		char inputDataChar = input_Data[inputDataIndex];
		char comparingDataStringChar = comparingDataString[comparingDataStringIndex];

		// If both characters/bytes are equal.
		if (inputDataChar == comparingDataStringChar) {
			// Check if dataStringIndex is equal the size of the comparingDataString - 1;
			if (comparingDataStringIndex == comparingDataSize - 1) {
				// Increment resulting count.
				++result.count;

				// Store start position of the string, found in the input data.
				result.stringPositions[result.count -1] = inputDataIndex - (comparingDataSize - 1);

				// Reset/set the comparing-data-string-index to 0;
				comparingDataStringIndex = 0;
			}
			else {
				// Increment the comparing-data-string-index.
				comparingDataStringIndex++;
			}
		}
		else {
			// Reset the comparing-data-string-index.
			comparingDataStringIndex = 0;
		}
	}
	return result;
}