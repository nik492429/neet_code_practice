#include <iostream>
using namespace std;


int16_t float_to_fixed(float value, int fractional_bits)
{
    float newValue = value * (1 << fractional_bits);
    return (int16_t)newValue;
}

float fixed_to_float(int16_t value, int fractional_bits)
{
    return (float)value / (1 << fractional_bits);
}

int main()
{
    float f = 3.14152;
    int16_t fixed = float_to_fixed(f, 8);
    float f_converted = fixed_to_float(fixed, 8);
    std::cout << "Fixed-point representation: " << fixed << std::endl;
    std::cout << "Converted back to float: " << f_converted << std::endl;

    std::cout << "Quantization error: " << f - f_converted << std::endl;
    return 0 ;
}