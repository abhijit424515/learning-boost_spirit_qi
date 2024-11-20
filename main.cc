#include "common.hh"

namespace parser {
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phoenix = boost::phoenix;

	template <typename Iterator>
	bool parse(Iterator first, Iterator last, std::vector<int>& v)
	{
		using ascii::space;
		using qi::double_;
		using qi::phrase_parse;
		using qi::_1;
		using phoenix::push_back;

		auto g = (
			double_[push_back(phoenix::ref(v), _1)] % ','
		);

		bool r = phrase_parse(
			first,
			last,
			g,
			space
		);

		if (first != last)
			return false;
		return r;
	}
}

int main() {
	while (1) {
		std::string input;
		std::getline(std::cin, input);
		std::string::iterator begin = input.begin(), end = input.end();
		
		std::vector<int> v;
		if (!parser::parse(begin, end, v)) {
			std::cout << "Parsing failed" << std::endl;
			return 1;
		}

		std::cout << "Parsed: " << std::endl;
		for (auto i : v)
			std::cout << i << ',';
		if (!v.empty())
			std::cout << '\b' << ' ';
		std::cout << std::endl;
	}
}