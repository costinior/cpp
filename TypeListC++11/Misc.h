#ifndef MISC_H
#define MISC_H

#include <type_traits>

//http://stackoverflow.com/questions/11251376/how-can-i-check-if-a-type-is-an-instantiation-of-a-given-class-template#comment14786989_11251408
template <template <typename...> class Template, typename T>
struct is_instantiation_of : public std::false_type
{};

template <template <typename...> class Template, typename... Args>
struct is_instantiation_of<Template, Template<Args...>> : public std::true_type
{};

#endif