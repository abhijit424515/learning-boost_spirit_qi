#include "common.hh"

namespace parser {
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;

	template <typename Iterator>
	bool parse(Iterator first, Iterator last)
	{
		using qi::double_;
		using qi::phrase_parse;
		using ascii::space;

		bool r = phrase_parse(
			first,
			last,
			double_ >> *(',' >> double_),
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
		
		if (!parser::parse(begin, end)) {
			std::cout << "Parsing failed" << std::endl;
			return 1;
		}
	}
}
