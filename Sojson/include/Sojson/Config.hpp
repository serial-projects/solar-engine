#ifndef SojsonConfig_hpp
#define SojsonConfig_hpp

/* THINGS YOU CAN CHANGE: */

/// SOJSON_FORCE_64BITS: While supporting more numbers, using Integer as 64-bit MIGHT use more
/// memory space and usually, not necessary, for example, on Solar Engine, levels barely go from
/// 0 - UINT8_MAX anyway, so, making it useless.
/// #define SOJSON_FORCE_64BITS

/// SOJSON_FORCE_64BITS_INTEGER: In case you want specifically the Integers to be 64 bit.
/// #define SOJSON_FORCE_64BITS_INTEGER

/// SOJSON_FORCE_64BITS_DECIMAL: In case you want specifically the Decimals to be 64 bit.
/// #define SOJSON_FORCE_64BITS_DECIMAL

/* THINGS THAT ARE MORE SPECIFIC TO THE VERSION: */

/// SOJSON_VERSION: The version the program is actually (1. <major> 0. <rev> 00 <minor> releases).
#define SOJSON_VERSION          1000

/// SOJSON_VERSION_STR: The version in format of string SOJSON_VERSION.
#define SOJSON_VERSION_STR      "1.0.00"

/// SOJSON_VERSION_NAME: The version name (usually an name given by me, LOL).
#define SOJSON_VERSION_NAME     "Sparkit"

/* DO NOT CHANGE: */

#ifdef SOJSON_FORCE_64BITS
    #define SOJSON_FORCE_64BITS_INTEGER     true
    #define SOJSON_FORCE_64BITS_DECIMAL     true
#endif

#endif