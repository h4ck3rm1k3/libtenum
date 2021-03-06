/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef TENUM_BIT_FIELD_HPP_
#define TENUM_BIT_FIELD_HPP_

#include <tenum/static_enum.hpp>

#define TENUM_SERIALIZE_BIT_FIELD_SIGNATURE(type_m,tuples_m) \
  template< > \
  template< > \
  inline ::std::string \
  enum_helper< TENUM_TYPE(type_m) >::serialize_impl< false, true >(TENUM_TYPE(type_m) const value_in, \
                                                                   ::boost::false_type const&, \
                                                                   ::boost::true_type const&)

#define TENUM_SERIALIZE_BIT_FIELD_DECLARATION(type_m,tuples_m) \
  TENUM_SERIALIZE_BIT_FIELD_SIGNATURE(type_m,tuples_m);

#define TENUM_SERIALIZE_BIT_FIELD_DEFINITION_EACH(_,type_m,tuple_m) \
  if (TENUM_CAST_UINT(value_in & TENUM_VALUE(type_m,TENUM_TUPLE_GET_VALUE(tuple_m))) != 0) { \
    stream << TENUM_DEFAULT_SEPARATOR_BIT_FIELD; \
    stream << serialize_impl< false, false >(TENUM_VALUE(type_m,TENUM_TUPLE_GET_VALUE(tuple_m)), \
                                             ::boost::false_type(), \
                                             ::boost::false_type()); \
  }

#define TENUM_SERIALIZE_BIT_FIELD_DEFINITION(type_m,tuples_m) \
  TENUM_SERIALIZE_BIT_FIELD_SIGNATURE(type_m,tuples_m) { \
    ::std::ostringstream stream; \
    BOOST_PP_SEQ_FOR_EACH(TENUM_SERIALIZE_BIT_FIELD_DEFINITION_EACH,type_m,tuples_m) \
    \
    ::std::string out = stream.str(); \
    return out.substr(::std::min(out.length(), \
                                 sizeof(TENUM_DEFAULT_SEPARATOR_BIT_FIELD) / sizeof(::std::string::value_type))); \
  }

#define TENUM_DESERIALIZE_BIT_FIELD_SIGNATURE(type_m,tuples_m) \
  template< > \
  template< > \
  inline TENUM_TYPE(type_m) \
  enum_helper< TENUM_TYPE(type_m) >::deserialize_impl< false, true >(::std::string const& value_in, \
                                                                     ::boost::false_type const&, \
                                                                     ::boost::true_type const&)

#define TENUM_DESERIALIZE_BIT_FIELD_DECLARATION(type_m,tuples_m) \
  TENUM_DESERIALIZE_BIT_FIELD_SIGNATURE(type_m,tuples_m);

#define TENUM_DESERIALIZE_BIT_FIELD_DEFINITION(type_m,tuples_m) \
  TENUM_DESERIALIZE_BIT_FIELD_SIGNATURE(type_m,tuples_m) { \
    ::std::size_t separator_pos = value_in.find(TENUM_DEFAULT_SEPARATOR_BIT_FIELD); \
    TENUM_TYPE(type_m) flag = deserialize_impl< false, false >(value_in.substr(0, separator_pos), \
                                                               ::boost::false_type(), \
                                                               ::boost::false_type()); \
    if (separator_pos != ::std::string::npos) { \
      TENUM_TYPE(type_m) trailing_flags = deserialize(value_in.substr(separator_pos + 1)); \
      return TENUM_CAST_ENUM(type_m, TENUM_CAST_UINT(flag) | TENUM_CAST_UINT(trailing_flags)); \
    } else { \
      return flag; \
    } \
  }

#define TENUM_BIT_FIELD_SERIALIZATION_DECLARATION(type_m,tuples_m) \
  namespace tenum { \
    template< > struct is_bit_field< TENUM_TYPE(type_m) > : ::boost::true_type {}; \
    TENUM_GET_BASE_OF_DECLARATION(type_m,tuples_m) \
    TENUM_SERIALIZE_DECLARATION(type_m,tuples_m) \
    TENUM_DESERIALIZE_DECLARATION(type_m,tuples_m) \
    TENUM_SERIALIZE_BIT_FIELD_DECLARATION(type_m,tuples_m) \
    TENUM_DESERIALIZE_BIT_FIELD_DECLARATION(type_m,tuples_m) \
  } \
  TENUM_STREAM_OPERATORS_DECLARATION(type_m)

#define TENUM_BIT_FIELD_SERIALIZATION_DEFINITION(type_m,tuples_m) \
  namespace tenum { \
    TENUM_GET_BASE_OF_DEFINITION(type_m,tuples_m) \
    TENUM_SERIALIZE_DEFINITION(type_m,tuples_m) \
    TENUM_DESERIALIZE_DEFINITION(type_m,tuples_m) \
    TENUM_SERIALIZE_BIT_FIELD_DEFINITION(type_m,tuples_m) \
    TENUM_DESERIALIZE_BIT_FIELD_DEFINITION(type_m,tuples_m) \
  } \
  TENUM_STREAM_OPERATORS_DEFINITION(type_m)

#define TENUM_BIT_FIELD_DECLARATION(type_m,tuples_m,underlying_m) \
  TENUM_ENUM_DEFINITION(type_m,BOOST_PP_SEQ_PUSH_FRONT(tuples_m,TENUM_TUPLE_VALUED(lte_unknown,0)),underlying_m) \
  TENUM_ENUM_OPERATORS_DECLARATION(type_m) \
  TENUM_BIT_FIELD_OPERATORS_DECLARATION(type_m) \
  TENUM_BIT_FIELD_SERIALIZATION_DECLARATION(type_m,tuples_m)

#define TENUM_BIT_FIELD_DEFINITION(type_m,tuples_m) \
  TENUM_ENUM_OPERATORS_DEFINITION(type_m) \
  TENUM_BIT_FIELD_OPERATORS_DEFINITION(type_m) \
  TENUM_BIT_FIELD_SERIALIZATION_DEFINITION(type_m,tuples_m)

#define TENUM_BIT_FIELD_I(type_m,tuples_m,underlying_m) \
  TENUM_BIT_FIELD_DECLARATION(type_m,tuples_m,underlying_m) \
  TENUM_BIT_FIELD_DEFINITION(type_m,tuples_m)

#define TENUM_BIT_FIELD(type_m,tuples_m,underlying_m) \
  TENUM_BIT_FIELD_I(type_m,tuples_m,:underlying_m)
#define TENUM_SIMPLE_BIT_FIELD(type_m,values_m) \
  TENUM_BIT_FIELD_I(type_m,TENUM_ENUM_VALUES_COMPLETE(values_m),BOOST_PP_EMPTY())

#endif /* TENUM_BIT_FIELD_HPP_ */
