/**
 * DICOM Encoder
 * dicomEncoder.hpp
 * Purpose: DICOM Encoder header file.
 * @author: Evangelos Mavropoulos
 * @date: 26/6/2018
 */

#ifndef DICOMENCODER_HPP_
#define DICOMENCODER_HPP_

#include <cstdint>
#include <string>
#include <vector>

namespace bioemtec {
/**
     * @brief A class that contains the implementation of the DICOM encoder.
     */

class dicomEncoder {
public:
    dicomEncoder();
    ~dicomEncoder();
    void encoder(std::string fileName, std::vector<std::string> stringInput, std::vector<
            float> decimalInput, uint16_t *inputImage);
};
}
#endif /* DICOMENCODER_HPP_ */
