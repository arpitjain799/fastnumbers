#pragma once

#include <charconv>
#include <cstdint>
#include <cstring>
#include <system_error>
#include <type_traits>

#include "fastnumbers/third_party/fast_float.h"

/// Table of what characters are classified as whitespace
constexpr bool WHITESPACE_TABLE[]
    = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/// Table of what characters are classified as digits
constexpr int DIGIT_TABLE[]
    = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

/**
 * \brief Check if a string could be converted to some numeric type
 *
 * Assumes no sign or whitespace.
 *
 * \param str The string to parse, assumed to be non-NULL
 * \param end The end of the string being checked
 * \param base The base to assume when checking an integer, set to 10
 *             unless you know it *must* be an integer.
 * \return 0 - invalid
 *         1 - integer
 *         2 - float
 *         3 - "intlike" float
 */
int string_contains_what(const char* str, const char* end, int base);

/**
 * \brief Remove underscores in a numeric-representing string
 *
 * Assumes the input can ba modified.
 *
 * In a generic number, valid underscores are between two digits.
 * A "based" number is necessarily an int, and in those cases the
 * definition of a valid underscore is a bit less well-defined.
 *
 * \param str The string from which to remove underscores
 * \param end Reference to the end of the string - after processing will
 *            point to the new end of the string
 * \param based Whether or not the string contains a non-base-10 integer
 */
void remove_valid_underscores(char* str, const char*& end, const bool based);

/**
 * \brief Lowercase a character - does no error checking
 */
constexpr inline char lowercase(const char c)
{
    // The ASCII standard was quite clever... upper- and lower-case
    // letters only differ from each other by the 32 bit, otherwise
    // they are identical. ORing the 32-bit forces lowercase.
    return static_cast<char>(c | 32);
}

/**
 * \brief Determine if a character is whitespace
 */
constexpr inline bool is_whitespace(const char c)
{
    // Using a table was determined through performance testing to be
    // many times faster than std::isspace, and twice as fast as using
    // a switch statement.
    return WHITESPACE_TABLE[static_cast<uint8_t>(c)];
}

/**
 * \brief Advance a string's pointer while whitespace is found
 */
constexpr inline void consume_whitespace(const char*& str, const char* end)
{
    while (str != end && is_whitespace(*str)) {
        str += 1;
    }
}

/**
 * \brief Convert a character to a digit, returns -1 on failure.
 */
template <typename T>
constexpr inline T to_digit(const char c)
{
    // Using a table was determined through performance testing to be
    // three times faster than c - '0' or a switch statement.
    return static_cast<T>(DIGIT_TABLE[static_cast<uint8_t>(c)]);
}

/**
 * \brief Determine if a character represents a digit
 */
constexpr inline bool is_valid_digit(const char c)
{
    // Using a table was determined through performance testing to be
    // faster than std::isdigit or a switch statement.
    return to_digit<int>(c) >= 0;
}

/**
 * \brief Advance a string's pointer while digits are found
 */
constexpr inline void consume_digits(const char*& str, const char* end)
{
    while (str != end && is_valid_digit(*str)) {
        str += 1;
    }
}

/**
 * \brief Advance a string's pointer while digits are found
 *        and attempt to read multiple digits at a time if possible
 */
inline void consume_digits(const char*& str, const std::size_t len)
{
    // Attempt to read eight characters at a time to determine
    // if they are digits. Loop over the character array in steps
    // of eight. Stop processing if not all eight characters are digits.
    const std::size_t number_of_eights = len / 8;
    for (std::size_t i = 0; i < number_of_eights; ++i) {
        if (fast_float::is_made_of_eight_digits_fast(str)) {
            str += 8;
        } else {
            break;
        }
    }

    // Read the remainder of digits one-at-a-time.
    consume_digits(str, str + len);
}

/**
 * \brief Determine if a character is '-' or '+'
 */
constexpr inline bool is_sign(const char c)
{
    return c == '-' || c == '+';
}

/**
 * \brief Determine if a character a prefix for base 2, 8, or 16
 */
constexpr inline bool is_base_prefix(const char c)
{
    // The ASCII standard was quite clever... upper- and lower-case
    // letters only differ from each other by the 32 bit, otherwise
    // they are identical.
    // So, we can OR the 32 bit to force the character to be
    // lowercase and then just check against the lowercase characters.
    const char lowered = lowercase(c);
    return (lowered == 'x') || (lowered == 'o') || (lowered == 'b');
}

/**
 * \brief Determine if a character a prefix for a specific base 2, 8, or 16
 */
constexpr inline bool is_base_prefix(const char c, const int base)
{
    const char lowered = lowercase(c);
    return (base == 16 && (lowered == 'x')) || (base == 8 && (lowered == 'o'))
        || (base == 2 && (lowered == 'b'));
}

/**
 * \brief Detect if a string contains infinity
 *
 * This is done without loops in the hope of being optimized
 * by the compiler
 *
 * \param str The string to check, assumed to be non-NULL
 * \param len The length of the string
 */
constexpr inline bool quick_detect_infinity(const char* str, const std::size_t len)
{
    // The ASCII standard was quite clever... upper- and lower-case
    // letters only differ from each other by the 32 bit, otherwise
    // they are identical. So, we can use the XOR operator against
    // lowercase "inf" and accumulate the results - if all bits are
    // zero or if only the 32 bit is one that means that the string
    // contained a case-insensitive INF.
    switch (len) {
    case 3: {
        const uint8_t accumulator = (str[0] ^ 'i') | (str[1] ^ 'n') | (str[2] ^ 'f');
        return accumulator == 0 || accumulator == 32;
    }
    case 8: {
        uint8_t accumulator = 0;
        accumulator |= (str[0] ^ 'i');
        accumulator |= (str[1] ^ 'n');
        accumulator |= (str[2] ^ 'f');
        accumulator |= (str[3] ^ 'i');
        accumulator |= (str[4] ^ 'n');
        accumulator |= (str[5] ^ 'i');
        accumulator |= (str[6] ^ 't');
        accumulator |= (str[7] ^ 'y');
        return accumulator == 0 || accumulator == 32;
    }
    default:
        return false;
    }
}

/**
 * \brief Detect if a string contains NaN
 *
 * This is done without loops in the hope of being optimized
 * by the compiler
 *
 * \param str The string to check, assumed to be non-NULL
 * \param len The length of the string
 */
constexpr inline bool quick_detect_nan(const char* str, const std::size_t len)
{
    if (len != 3) {
        return false;
    }
    // The ASCII standard was quite clever... upper- and lower-case
    // letters only differ from each other by the 32 bit, otherwise
    // they are identical. So, we can use the XOR operator against
    // lowercase "nan" and accumulate the results - if all bits are
    // zero or if only the 32 bit is one that means that the string
    // contained a case-insensitive NaN.
    const uint8_t accumulator = (str[0] ^ 'n') | (str[1] ^ 'a') | (str[2] ^ 'n');
    return accumulator == 0 || accumulator == 32;
}

/**
 * \brief Detect if a string probably contains an integer
 *
 * This is not a 100% assurance, but it is a gross check that
 * makes sure the first character is a digit.
 *
 * \param str The string to check, assumed to be non-NULL
 * \param len The length of the string
 */
constexpr inline bool is_likely_int(const char* str, std::size_t len)
{
    return len > 0 && is_valid_digit(*str);
}

/**
 * \brief Check the number of zeros at the end of a number
 *
 * \param str The string to check, assumed to be non-NULL
 * \param end The end of the string being checked
 * \return The number of zeros
 */
constexpr inline uint32_t number_trailing_zeros(const char* start, const char* end)
{
    uint32_t n = 0;
    for (end = end - 1; end >= start; --end) {
        if (*end == '0') {
            n += 1;
        } else {
            break;
        }
    }
    return n;
}

/**
 * \brief Auto-detect the base of the given integer string
 *
 * \param str The string to check, assumed to be non-NULL
 * \param end The end of the string being checked
 * \return The dectected base, possibly 2, 8, 10, 16, or -1 on error
 */
constexpr inline int detect_base(const char* str, const char* end)
{
    const std::size_t len = static_cast<std::size_t>(end - str);
    if (str[0] != '0' || len == 1) {
        return 10;
    }

    const char lowered = lowercase(str[1]);
    if (lowered == 'x') {
        return 16;
    } else if (lowered == 'o') {
        return 8;
    } else if (lowered == 'b') {
        return 2;
    } else {
        /* "old" (C-style) octal literal illegal in 3.x. */
        if (number_trailing_zeros(str, end) == len) {
            return 10;
        } else {
            return -1;
        }
    }
}

/**
 * \brief Return the number of digits an integer type can safely parse without overflow
 */
template <typename T, typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
constexpr inline T overflow_cutoff()
{
    // len('std::numeric_limits<T>::max()') - 1 == return value
    switch (static_cast<uint64_t>(std::numeric_limits<T>::max())) {
    case 9223372036854775807LL:
        return 18;
    case 18446744073709551615ULL:
        return 19;
    case 2147483647L:
    case 4294967295UL:
        return 9;
    case 32767:
    case 65535U:
        return 4;
    case 127:
    case 255U:
        return 2;
    default: // unknown, be safe
        return 0;
    }
}

/**
 * \brief Convert a string to an int type
 *
 * Assumes no sign or whitespace.
 *
 * \param str The string to parse, assumed to be non-NULL
 * \param end The end of the string being checked
 * \param base The base to assume when checking an integer, 0 is "guess".
 * \param error Flag to indicate if there was a parsing error
 * \param overflow Flag to indicate if the string was long enough to overflow
 * \param always_convert
 */
template <typename T, typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
T parse_int(
    const char* str,
    const char* end,
    int base,
    bool& error,
    bool& overflow,
    bool always_convert = false
)
{
    const std::size_t len = static_cast<std::size_t>(end - str);

    // If the base needs to be guessed, do so now and get it over with.
    if (base == 0) {
        base = detect_base(str, end);
    }

    // Negative bases are illegal. So is zero-length
    if (base < 0 || len == 0) {
        overflow = false;
        error = true;
        return -1;
    }

    // We use our own method for base-10 because we can omit some overflow
    // checking and get faster results.
    //
    // We just assume overflow if the length of the string is over a certain value.
    overflow = len > static_cast<std::size_t>(overflow_cutoff<T>());

    // Use std::from_chars for all but base-10.
    if (base != 10 || (overflow && always_convert)) {
        // Skip leading characters for non-base 10 ints.
        if (len > 1 && str[0] == '0' && is_base_prefix(str[1], base)) {
            str += 2;
        }

        // Use a very fast and accurate string to integer parser
        // that will report back if there was an overflow (which
        // we propagete back to the user).
        T value;
        const std::from_chars_result res = std::from_chars(str, end, value, base);
        error = res.ptr != end || res.ec == std::errc::invalid_argument;
        overflow = res.ec == std::errc::result_out_of_range;
        return value;
    }

    // If an overflow is going to happen, just evaluate that this looks like
    // an integer. Otherwise, actually calculate the value contained in the string.
    T value = static_cast<T>(0);
    if (overflow) {
        consume_digits(str, len);
    } else {
        // Attempt to read eight characters at a time and parse as digits.
        // Loop over the character array in steps of eight. Stop processing
        // if not all eight characters are digits.
        if constexpr (overflow_cutoff<T>() > 8) {
            const std::size_t number_of_eights = len / 8;
            for (std::size_t i = 0; i < number_of_eights; ++i) {
                if (fast_float::is_made_of_eight_digits_fast(str)) {
                    value = value * 100000000
                        + fast_float::parse_eight_digits_unrolled(str);
                    str += 8;
                } else {
                    break;
                }
            }
        }

        // Convert digits the remaining digits one-at-a-time.
        T this_char_as_digit = 0L;
        while (str != end && (this_char_as_digit = to_digit<T>(*str)) >= 0) {
            value = value * 10L + this_char_as_digit;
            str += 1;
        }
    }
    error = str != end;
    return value;
}

/**
 * \brief Convert a string to a double type
 *
 * Assumes no sign or whitespace. No overflow checking is performed.
 *
 * \param str The string to parse, assumed to be non-NULL
 * \param end The end of the string being checked
 * \param error Flag to indicate if there was a parsing error
 */
template <
    typename T,
    typename std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
T parse_float(const char* str, const char* end, bool& error)
{
    // parse_float is not supposed to accept signed values, but from_chars
    // will accept negative signs. To prevent accidental success on e.g. "+-3.14"
    // we short-cicuit on a leading negative sign.
    if (str != end && *str == '-') {
        error = true;
        return -1.0;
    }

    // Use a very fast and accurate string-to-floating point parser
    T value;
    const fast_float::from_chars_result res = fast_float::from_chars(str, end, value);
    error = !(res.ptr == end && res.ec == std::errc());
    return value;
}