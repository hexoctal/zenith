/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#ifndef ZEN_MATH_FUZZY_FLOOR_HPP
#define ZEN_MATH_FUZZY_FLOOR_HPP

#include "../const.hpp"

namespace Zen {
namespace Math {

/**
 * Calculate the fuzzy floor of the given value.
 *
 * @since 0.0.0
 *
 * @param value The value.
 * @param epsilon The epsilon.
 *
 * @return The fuzzy floor of the value.
 */
bool FuzzyFloor (double value, double epsilon = EPSILON);

}	// namespace Math
}	// namespace Zen

#endif
