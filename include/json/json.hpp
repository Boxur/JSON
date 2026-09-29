#ifndef JSON_HPP_
#define JSON_HPP_
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace mc::json {
template <typename... O>
concept ValidKey = ((std::convertible_to<O, std::size_t> ||
                     std::convertible_to<O, std::string>) &&
                    ...);

struct Null {};
class Object;
class Array;
class JSON {
  union Value {
    Object *object;
    Array *array;
    std::string *string;
    bool boolean;
    Null null;
    int num_int;
    float num_float;
  } value_;

public:
  enum class Type {
    Object,
    Array,
    String,
    Boolean,
    Null,
    NumInt,
    NumFloat,
  };

private:
  Type type_;

public:
  JSON();
  JSON(const JSON &);
  JSON(JSON &&);
  ~JSON();

  JSON(Type);

  JSON(const Object &);
  JSON(Object &&);

  JSON(const Array &);
  JSON(Array &&);

  const std::string &operator=(const char *);
  const std::string &operator=(const char *&&);
  JSON(const char *);

  JSON(const std::string &);
  const std::string &operator=(const std::string &);
  const std::string &operator=(const std::string &&);
  JSON(std::string &&);
  operator std::string *();

  bool operator=(const bool &);
  JSON(const bool &);
  JSON(bool &&);
  operator bool *();

  JSON(const Null &);
  JSON(Null &&);

  int operator=(const int &);
  JSON(const int &);
  JSON(int &&);
  operator int *();

  float operator=(const float &);
  JSON(const float &);
  JSON(float &&);
  operator float *();

  template <typename... O>
    requires ValidKey<O...>
  JSON &operator[](std::size_t index, O...);
  template <typename... O>
    requires ValidKey<O...>
  JSON &operator[](std::string index, O...);

  template <typename T> T *value() {}
};

class Array {
  friend class JSON;

  std::vector<JSON> data_;

  Array();
  Array(const Array &);
  Array(Array &&);

public:
  Array(std::initializer_list<JSON>);
  JSON *operator[](const std::size_t &index);
};

class Object {
  friend class JSON;

  std::unordered_map<std::string, JSON> data_;

  Object();
  Object(const Object &);
  Object(Object &&);

public:
  Object(std::initializer_list<std::pair<const std::string, JSON>>);
  JSON *operator[](const std::string &index);
};

template <typename... O>
  requires ValidKey<O...>
JSON &JSON::operator[](std::size_t index, O... other) {
  JSON *found = (*value_.array)[index];
  return (*found)[other...];
}

template <> JSON &JSON::operator[]<>(std::size_t index);

template <typename... O>
  requires ValidKey<O...>
JSON &JSON::operator[](std::string index, O... other) {
  JSON *found = (*value_.object)[index];
  return (*found)[other...];
}

template <> JSON &JSON::operator[]<>(std::string index);

} // namespace mc::json
#endif
