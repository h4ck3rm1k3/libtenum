/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_SHORTCUT_HPP_
#define TENUM_SHORTCUT_HPP_

/**
 * @def TENUM_USE_SHORTCUTS
 * @brief If defined, will create shorter macros to access enum definition macros.
 */
#ifdef TENUM_USE_SHORTCUTS

#  define lte_enum_s            TENUM_SIMPLE_STATIC_ENUM
#  define lte_enum              TENUM_STATIC_ENUM
#  define lte_enum_decl         TENUM_STATIC_ENUM_DECLARATION
#  define lte_enum_defn         TENUM_STATIC_ENUM_DEFINITION
#  define lte_dynamic_enum_s    TENUM_SIMPLE_DYNAMIC_ENUM
#  define lte_dynamic_enum      TENUM_DYNAMIC_ENUM
#  define lte_dynamic_enum_decl TENUM_DYNAMIC_ENUM_DECLARATION
#  define lte_dynamic_enum_defn TENUM_DYNAMIC_ENUM_DEFINITION
#  define lte_bit_flag_s        TENUM_SIMPLE_BIT_FLAG
#  define lte_bit_flag          TENUM_BIT_FLAG
#  define lte_bit_flag_decl     TENUM_BIT_FLAG_DECLARATION
#  define lte_bit_flag_defn     TENUM_BIT_FLAG_DEFINITION

#  define lte_e   TENUM_ELEMENT
#  define lte_ev  TENUM_ELEMENT_VALUED
#  define lte_en  TENUM_ELEMENT_NAMED
#  define lte_evn TENUM_ELEMENT_VALUED_NAMED

#endif /* TENUM_USE_SHORTCUTS */

#endif /* TENUM_SHORTCUT_HPP_ */
