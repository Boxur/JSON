#include "json/json.hpp"
#include <cstddef>
#include <initializer_list>
#include <string>
#include <utility>

namespace mc::json {
JSON::JSON() : type_(Type::Null) {}

JSON::JSON(const JSON &other) : type_(other.type_) {
  switch (type_) {
  case Type::Array:
    value_.array = new Array(*other.value_.array);
    break;
  case Type::Object:
    value_.object = new Object(*other.value_.object);
    break;
  case Type::String:
    value_.string = new std::string(*other.value_.string);
    break;
  case Type::Boolean:
  case Type::Null:
  case Type::NumFloat:
  case Type::NumInt:
    value_ = other.value_;
  }
}

JSON::JSON(JSON &&other) : type_(other.type_), value_(other.value_) {
  other.type_ = Type::Null;
  other.value_.null = {};
}

JSON::~JSON() {
  switch (type_) {
  case Type::Array:
    delete value_.array;
    break;
  case Type::Object:
    delete value_.object;
    break;
  case Type::String:
    delete value_.string;
    break;
  case Type::Boolean:
  case Type::Null:
  case Type::NumFloat:
  case Type::NumInt:
    break;
  }
  type_ = Type::Null;
}

JSON::JSON(Type type) : type_(type) {
  switch (type_) {
  case Type::Array:
    value_.array = new Array{};
    break;
  case Type::Object:
    value_.object = new Object{};
    break;
  case Type::String:
    value_.string = new std::string{};
    break;
  case Type::Boolean:
    value_.boolean = {};
    break;
  case Type::Null:
    value_.null = {};
  case Type::NumFloat:
    value_.num_float = {};
  case Type::NumInt:
    value_.num_int = {};
    break;
  }
}

JSON::JSON(const Object &object) : type_(Type::Object) {
  value_.object = new Object(object);
}

JSON::JSON(Object &&object) : type_(Type::Object) {
  value_.object = new Object(std::move(object));
}

JSON::JSON(const Array &array) : type_(Type::Array) {
  value_.array = new Array(array);
}

JSON::JSON(Array &&array) : type_(Type::Array) {
  value_.array = new Array(std::move(array));
}

const std::string &JSON::operator=(const char *str) {
  type_ = Type::String;
  value_.string = new std::string(str);
  return *value_.string;
}

JSON::JSON(const char *str) : type_(Type::String) {
  value_.string = new std::string(str);
}

const std::string &JSON::operator=(const std::string &string) {
  type_ = Type::String;
  value_.string = new std::string(string);
  return *value_.string;
}

const std::string &JSON::operator=(const std::string &&string) {
  type_ = Type::String;
  value_.string = new std::string(std::move(string));
  return *value_.string;
}

JSON::JSON(const std::string &string) : type_(Type::String) {
  value_.string = new std::string(string);
}

JSON::JSON(std::string &&string) : type_(Type::String) {
  value_.string = new std::string(std::move(string));
}

JSON::operator std::string *() {
  if (type_ != Type::String)
    return nullptr;
  return value_.string;
}

bool JSON::operator=(const bool &boolean) {
  type_ = Type::Boolean;
  value_.boolean = boolean;
  return value_.boolean;
}

JSON::JSON(const bool &boolean) : type_(Type::Boolean) {
  value_.boolean = boolean;
}

JSON::JSON(bool &&boolean) : type_(Type::Boolean) {
  value_.boolean = std::move(boolean);
}

JSON::operator bool *() {
  if (type_ != Type::Boolean)
    return nullptr;
  return &value_.boolean;
}

JSON::JSON(const Null &) : type_(Type::Null) { value_.null = {}; }

JSON::JSON(Null &&) : type_(Type::Null) { value_.null = {}; }

int JSON::operator=(const int &num_int) {
  type_ = Type::NumInt;
  value_.num_int = num_int;
  return value_.num_int;
}

JSON::JSON(const int &num_int) : type_(Type::NumInt) {
  value_.num_int = num_int;
}

JSON::JSON(int &&num_int) : type_(Type::NumInt) {
  value_.num_int = std::move(num_int);
}

JSON::operator int *() {
  if (type_ != Type::NumInt)
    return nullptr;
  return &value_.num_int;
}

float JSON::operator=(const float &num_float) {
  type_ = Type::NumFloat;
  value_.num_float = num_float;
  return value_.num_float;
}

JSON::JSON(const float &num_float) : type_(Type::NumFloat) {
  value_.num_float = num_float;
}

JSON::JSON(float &&num_float) : type_(Type::NumFloat) {
  value_.num_float = std::move(num_float);
}

JSON::operator float *() {
  if (type_ != Type::NumFloat)
    return nullptr;
  return &value_.num_float;
}

template <> JSON &JSON::operator[]<>(std::size_t index) {
  return *(*value_.array)[index];
}

template <> JSON &JSON::operator[]<>(std::string index) {
  return *(*value_.object)[index];
}

Array::Array() : data_{} {}

Array::Array(const Array &other) : data_(other.data_) {}

Array::Array(Array &&other) : data_(std::move(other.data_)) {}

Array::Array(std::initializer_list<JSON> data) : data_(std::move(data)) {}

JSON *Array::operator[](const std::size_t &index) {
  if (data_.size() <= index)
    return nullptr;
  return &data_[index];
}

Object::Object() : data_{} {}

Object::Object(const Object &other) : data_(other.data_) {}

Object::Object(Object &&other) : data_(std::move(other.data_)) {}

Object::Object(std::initializer_list<std::pair<const std::string, JSON>> data)
    : data_(std::move(data)) {}

JSON *Object::operator[](const std::string &index) {
  if (!data_.contains(index))
    return nullptr;
  return &data_[index];
}

} // namespace mc::json
