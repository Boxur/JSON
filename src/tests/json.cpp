#include "json/json.hpp"
#include <gtest/gtest.h>

TEST(JSON, string) {
  mc::json::JSON json("correct");
  {
    std::string *output = json;
    std::string correct{"correct"};
    ASSERT_EQ(*output, correct);
  }
}

TEST(JSON, number_int) {
  mc::json::JSON json(123);
  {
    int *output = json;
    int correct{123};
    ASSERT_EQ(*output, correct);
  }
}

TEST(JSON, number_float) {
  mc::json::JSON json(21.37f);
  {
    float *output = json;
    float correct{21.37};
    ASSERT_EQ(*output, correct);
  }
}

TEST(JSON, boolean) {
  mc::json::JSON json(true);
  {
    bool *output = json;
    bool correct{true};
    ASSERT_EQ(*output, correct);
  }
}

TEST(JSON, null) {
  mc::json::JSON json{};
  json = 4.0f;
  {
    float *output = json;
    float correct{4.0f};
    ASSERT_EQ(*output, correct);
  }
}

TEST(JSON, object) {
  using Object = mc::json::Object;

  mc::json::JSON json{Object{{"text", "hello"},
                             {"int", 12},
                             {"bool", true},
                             {"obj", Object{{"float", 1.2f}}}}};
  {
    std::string *output = json["text"];
    ASSERT_NE(output, nullptr);
    std::string correct{"hello"};
    ASSERT_EQ(*output, correct);
  }
  {
    int *output = json["int"];
    ASSERT_NE(output, nullptr);
    int correct{12};
    ASSERT_EQ(*output, correct);
  }
  {
    bool *output = json["bool"];
    ASSERT_NE(output, nullptr);
    bool correct{true};
    ASSERT_EQ(*output, correct);
  }
  {
    float *output = json["obj"]["float"];
    ASSERT_NE(output, nullptr);
    float correct{1.2f};
    ASSERT_EQ(*output, correct);
  }
  {
    float *output = json["obj", "float"];
    ASSERT_NE(output, nullptr);
    float correct{1.2f};
    ASSERT_EQ(*output, correct);
  }
}

TEST(JSON, array) {
  using Array = mc::json::Array;

  mc::json::JSON json{Array{"hello", 12, true, Array{1.2f}}};
  {
    std::string *output = json[0];
    ASSERT_NE(output, nullptr);
    std::string correct{"hello"};
    ASSERT_EQ(*output, correct);
  }
  {
    int *output = json[1];
    ASSERT_NE(output, nullptr);
    int correct{12};
    ASSERT_EQ(*output, correct);
  }
  {
    bool *output = json[2];
    ASSERT_NE(output, nullptr);
    bool correct{true};
    ASSERT_EQ(*output, correct);
  }
  {
    float *output = json[3][0];
    ASSERT_NE(output, nullptr);
    float correct{1.2f};
    ASSERT_EQ(*output, correct);
  }
  {
    float *output = json[3, 0];
    ASSERT_NE(output, nullptr);
    float correct{1.2f};
    ASSERT_EQ(*output, correct);
  }
}

TEST(JSON, object_and_array) {
  using Array = mc::json::Array;
  using Object = mc::json::Object;

  mc::json::JSON json{
      Array{Object{{"text", "hello"}, {"int", 12}},
            Object{{"bool", true}, {"array", Array{0.3f, 1.2f, 4.5f}}}}};
  {
    std::string *output = json[0]["text"];
    ASSERT_NE(output, nullptr);
    std::string correct{"hello"};
    ASSERT_EQ(*output, correct);
  }
  {
    int *output = json[0, "int"];
    ASSERT_NE(output, nullptr);
    int correct{12};
    ASSERT_EQ(*output, correct);
  }
  {
    bool *output = json[1]["bool"];
    ASSERT_NE(output, nullptr);
    bool correct{true};
    ASSERT_EQ(*output, correct);
  }
  {
    float *output = json[1]["array"][1];
    ASSERT_NE(output, nullptr);
    float correct{1.2f};
    ASSERT_EQ(*output, correct);
  }
  {
    float *output = json[1, "array", 2];
    ASSERT_NE(output, nullptr);
    float correct{4.5f};
    ASSERT_EQ(*output, correct);
  }
}
