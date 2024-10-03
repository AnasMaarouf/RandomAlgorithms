/**********************************************
    Shifts each bit in an array of bytes, where
    the array is consideret as one single variable.
    An example is written and result is shown in
    console. Another example is an array of bytes
    consisting of:
    
                    10010001
                    01001000
                    00100100
                    00010010
    
        10010001010010000010010000010010
            

    Shifting the array by 10 to the left will
    result in the array being:

                    00100000
                    10010000
                    01001010
                    00000000
    
        00100000100100000100101000000000

**********************************************/
#include <cstdint>
#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

void shift_Array_of_bytes(uint8_t byte[], unsigned int arraySize, uint32_t nrOfBitShifts) {
    unsigned int bytesShifted = floor(nrOfBitShifts / 8);       // Calcute the number of bytes to shift.
    
    if (bytesShifted >= arraySize) {    // If more bytes are shifted than there is bytes in the array.
        // Change all values in array to 0.
        for (unsigned int index = 0; index < arraySize; index++)
            byte[index] = 0;

        return;     // Exit early
    }

    for (unsigned int index = 0; index < arraySize; index++) {
        // Go the number of bytes that needs to be shifted ahead, and shift the remainder of bits to the left, and logic-OR with the following byte shifted right with 8 minus the remainder of bits.
        byte[index] = (byte[index + bytesShifted] << (nrOfBitShifts - bytesShifted * 8)) | (byte[index + bytesShifted + 1] >> (8 - (nrOfBitShifts % 8)));
    }

    if (bytesShifted > 0) {     // Set the last bytes of the array to 0 (the number of bytes changed is the number og bytes shifted). 
        for (unsigned int index = 0; index < bytesShifted; index++) {
            byte[arraySize - 1 - index] = 0;
        }
    }
}


int main(void) {
    
    bitset<8> x;
    uint8_t data[] = { 5,1,6};
    int dataSize = 3;

    cout << "\n\n" << "<-- before bitshifting -->  ";
    for (unsigned int i = 0; i < dataSize; i++) {
        x = data[i];
        cout << x;
    }
    cout << endl;
    for (unsigned int i = 0; i < dataSize; i++) {
        x = data[i];
        cout << x << endl;
    }

    shift_Array_of_bytes(data, dataSize, 5);

    cout << "\n\n" << "<-- after bitshifting -->  ";
    for (unsigned int i = 0; i < dataSize; i++) {
        x = data[i];
        cout << x;
    }
    cout << endl;
    for (unsigned int i = 0; i < dataSize; i++) {
        x = data[i];
        cout << x << endl;
    }
    return 0;
}