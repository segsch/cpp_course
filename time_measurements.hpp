#include <iostream>
#include <chrono>
#include <string> 

namespace cpp_course {
    using std::string;

    template<typename T> string time_type()                  { return "unknown"; }
    template<> string time_type<std::chrono::nanoseconds >() { return "ns";      }
    template<> string time_type<std::chrono::microseconds>() { return "us";      }
    template<> string time_type<std::chrono::milliseconds>() { return "ms";      }
    template<> string time_type<std::chrono::seconds     >() { return "s";       }
    template<> string time_type<std::chrono::minutes     >() { return "min";     }
    template<> string time_type<std::chrono::hours       >() { return "h";       }

    template<typename T> string time_str(T t) { return time_type<T>(); }

    template<typename Rep, typename Period>
    std::ostream& operator<<(std::ostream& out, std::chrono::duration<Rep, Period> d) {
        return out << d.count() << time_str(d);
    }

    template<typename MeasurementUnits = std::chrono::milliseconds, typename Clock = std::chrono::steady_clock>
    class time_measurement {
        std::chrono::time_point<Clock> start;
        std::string function_name;
    public:
        time_measurement(std::string func_name): start(Clock::now()), function_name(std::move(func_name)) {}
        ~time_measurement() {
            std::cout << "Time elapsed for " << function_name << ": " << std::chrono::duration_cast<MeasurementUnits>(Clock::now() - start) << std::endl;
        }
    };
}
