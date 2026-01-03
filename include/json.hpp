#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <variant>
#include <memory>

class JSON
{
	private:
		
		using Value = std::variant<std::shared_ptr<JSON>, std::unordered_map<std::string, std::shared_ptr<JSON>>, std::vector<std::shared_ptr<JSON>>, double, std::string, bool, std::monostate>;

		Value _value;

	public:
		void Parse(std::string);

		std::string ToString();

		Value operator[](std::variant<std::string,double> path);
};
