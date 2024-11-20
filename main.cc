#include "common.hh"

namespace parser {
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phoenix = boost::phoenix;

	void print(double const& i) {
        std::cout << i << std::endl;
    }

	template <typename Iterator>
	bool parse(Iterator first, Iterator last, std::complex<double>& c)
	{
		using ascii::space;
		using qi::double_;
		using qi::phrase_parse;
		using qi::_1;
		using phoenix::ref;

		double rN = 0.0, iN = 0.0, len = 0.0;

		auto g = (
			double_[ref(rN) = _1, ref(len) += _1*_1]
			| '(' >> double_[ref(rN) = _1, ref(len) += _1*_1] >> -(',' >> double_[ref(iN) = _1, ref(len) += _1*_1]) >> ')'
		);

		bool r = phrase_parse(
			first,
			last,
			g,
			space
		);

		if (first != last)
			return false;
		c = std::complex<double>(rN, iN);
		std::cout << "Length: " << std::sqrt(len) << std::endl;
		return r;
	}
}

int main() {
	while (1) {
		std::string input;
		std::getline(std::cin, input);
		std::string::iterator begin = input.begin(), end = input.end();
		
		std::complex<double> c;
		if (!parser::parse(begin, end, c)) {
			std::cout << "Parsing failed" << std::endl;
			return 1;
		}

		std::cout << "Real: " << c.real() << ", Imaginary: " << c.imag() << std::endl;
	}
}
