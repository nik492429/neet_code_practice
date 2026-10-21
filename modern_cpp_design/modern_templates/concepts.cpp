#include <concepts>
#include <iostream>
#include <array>
using namespace std;

using Frame = std::array<int, 10>;

template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;


template<Integral T, FloatingPoint M>
void foo(T t, M u) {
    cout << t << " " << u << endl;
}

template <typename T>
concept Sensor = requires(T t) 
{
    t.setSettings();
    { t.getFrame() } -> std::same_as<Frame>;
};


class GMSLSensor
{
    public:
        Frame getFrame() {
            cout << "Getting frame from GMSL Sensor" << endl;
            return Frame{};
        }

        void setSettings() {
            cout << "Setting settings for GMSL Sensor" << endl;
        }


};

class V4L2Sensor
{
    public:
        Frame getFrame() {
            cout << "Getting frame from V4L2 Sensor" << endl;
            return Frame{};
        }

        void setSettings() {
            cout << "Setting settings for V4L2 Sensor" << endl;
        }
};


template<Sensor T>
void InitializeCamera(T& sensor) {
    (void)sensor.getFrame();
    sensor.setSettings();
}

int main()
{
    GMSLSensor gmslSensor;
    V4L2Sensor v4l2Sensor;

    InitializeCamera(gmslSensor);
    InitializeCamera(v4l2Sensor);

    foo(42, 3.14); // Works: 42 is Integral, 3.14 is FloatingPoint
    // foo(3.14, 42); // Error: 3.14 is not Integral
}


// int main() {
//     foo(42, 3.14); // Works: 42 is Integral, 3.14 is FloatingPoint
//     // foo(3.14, 42); // Error: 3.14 is not Integral
//     return 0;
// }