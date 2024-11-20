#include "common.hh"

namespace parser {
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;

	void print(double const& i) {
        std::cout << i << std::endl;
    }

	template <typename Iterator>
	bool parse(Iterator first, Iterator last)
	{
		using qi::double_;
		using qi::phrase_parse;
		using ascii::space;
		using boost::bind;
		using boost::placeholders::_1;

		bool r = phrase_parse(
			first,
			last,
			double_[&print] >> *(',' >> double_[bind(print,_1)]),
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
