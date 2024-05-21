#ifndef solar_utils_hxx
#define solar_utils_hxx

#include <string>
#include <iostream>

#define WHEN(condition, dothis) if(condition) dothis;
#define MAKESURE(condition, ifnot) if(!condition) ifnot;

#define PRETTY_FUNCTION_MAXSIZE 80
inline std::string __PrettyFunctionLimiter(const std::string __pretty_function)
{
    return (__pretty_function.size() >= PRETTY_FUNCTION_MAXSIZE ? __pretty_function.substr(0, PRETTY_FUNCTION_MAXSIZE - 3) + "..." : __pretty_function);
}

/* GENERATORS() */
#define GENERROR(message) { \
    std::cout << "\033[1;31m[" << __FILE__ << ", " << __PrettyFunctionLimiter(__PRETTY_FUNCTION__) << \
    "]\033[0m: " << message << "\n"; std::exit(-1); }

#define GENDEBUG(message)   \
    std::cout << "\033[1;35m[" << __FILE__ << ", " << __PrettyFunctionLimiter(__PRETTY_FUNCTION__) << \
    "]\033[0m: " << message << "\n";

#define DEPREACTED(message) { \
    std::cout << "\033[1;33m[" << __FILE__ << ", " << __PrettyFunctionLimiter(__PRETTY_FUNCTION__) << \
    "]\033[0m (DEPREACTION WARNING): " << message << "\n"; }


#endif
// Solar/Utils.hxx