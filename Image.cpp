#include "Image.h"
#include <fstream>
#include <iostream>

bool Image::Load(const std::string& fileName, Uint8 alpha)
{
    std::ifstream stream(fileName, std::ios::binary);

    if (stream.fail())
    {
        std::cout << "Error: Cannot open file: " << fileName << std::endl;
        return false;
    }

    Uint8 header[54];
    stream.read((char*)header, 54);

    Uint16 type = *((Uint16*)(&header[0]));
    if (type != 'MB')
    {
        std::cout << "Error: Invalid File Format: " << type << std::endl;
        return false;
    }

    m_width = *(int*)(&header[18]);
    m_height = *(int*)(&header[22]);

    std::cout << m_width << std::endl << m_height << std::endl;

    int dataSize = m_width * m_height * 3;

    std::vector<Uint8> imageData(dataSize);
    stream.read((char*)imageData.data(), dataSize);

    for (int i = 0; i < dataSize; i += 3)
    {
        SDL_Color color;
        color.r = imageData[i + 2];
        color.g = imageData[i + 1];
        color.b = imageData[i];
        color.a = alpha; 

        m_buffer.push_back((color.r << 24 | color.g << 16 | color.b << 8 | color.a));
    }
    std::reverse(m_buffer.begin(), m_buffer.end());
    stream.close();

    return true;
}
