#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h> 

// castings
#define _bool(type) ((bool) type)
#define _uint8(type) ((uint8_t) type)
#define _uint16(type) ((uint16_t) type)
#define _uint32(type) ((uint32_t) type)
#define _uint64(type) ((uint64_t) type)
// Assuming uint128_t and int128_t are defined (compiler dependent)
#ifdef __SIZEOF_INT128__
#define _uint128(type) ((__uint128_t) type)
#define _int128(type) ((__int128_t) type)
#endif

#define _int8(type) ((int8_t) type)
#define _int16(type) ((int16_t) type)
#define _int32(type) ((int32_t) type)
#define _int64(type) ((int64_t) type)
#define _char(type) ((char) type)

// for strings
#define _string(type) ((char*) type)

// conversions
#define to_negative(number) (-(number))
#define to_negative_calc(number) (-1 *(number))

// conversion
#define to_positive(number) (abs(number)) // More robust for positive conversion
#define to_positive_calc(number) (+1 *(number)) // Unnecessary, just use the number directly

// conversion
#define to_ptr(variable) (&(variable)) // Corrected to take a variable, not just 'ptr'

// utility
#define isNULL(value) ((void*)value == NULL)
#define isTrue(value) ((void*)value == true)
#define isFalse(value) ((void*)value == false)
#define isNaN(value) ((void*)value == NaN)
// for falsy and truthty
#define  if_falsy(statement) if(!statement) 
#define  if_truthy(statement) if(statement) 
#define if_true(value) if isTrue(value)
#define if_false(value) if isFalse(value)
