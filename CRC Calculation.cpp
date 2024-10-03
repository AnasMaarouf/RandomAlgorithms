#include <cstdint>
template<typename CRCBitSize> CRCBitSize CRC(uint8_t data[], unsigned int DataByteSize, CRCBitSize Polynomial, bool InOutReflect, CRCBitSize InitValue, CRCBitSize XorOutValue) {
    CRCBitSize crc = InitValue;

    //Perform modulo-2 division, a byte at a time.
    if (InOutReflect == false) {   // Unreflected
        for (int byte = 0; byte < DataByteSize; ++byte) {
            //Bring the next byte into the remainder.
            crc ^= (data[byte] << (8 * sizeof(CRCBitSize)) - 8);

            //Perform modulo-2 division, a bit at a time.
            for (uint8_t bit = 8; bit > 0; --bit) {
                //Try to divide the current data bit.
                if (crc & (1 << ((8 * sizeof(CRCBitSize)) - 1)))
                    crc = (crc << 1) ^ Polynomial;
                else
                    crc = (crc << 1);
            }
        }
    }
    else if (InOutReflect == true) { // Reflected
        // reverse the polynomial
        CRCBitSize revPolynomial = 0;
        unsigned int n = Polynomial;

        for (int i = 0; i < sizeof(CRCBitSize) * 8; i++) {
            revPolynomial = revPolynomial << 1;
            if ((n & 1) > 0) {
                revPolynomial = revPolynomial ^ 1;
            }
            n = n >> 1;
        }

        for (unsigned int byte = 0; byte < DataByteSize; byte++) {
            crc ^= data[byte];
            for (unsigned int k = 0; k < 8; k++)
                crc = crc & 1 ? (crc >> 1) ^ revPolynomial : crc >> 1;
        }
    }
    crc ^= XorOutValue;
    return crc;
}