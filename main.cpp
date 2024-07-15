#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <vector>

#define PROGRAM_NAME "rgba2hex"

typedef unsigned char channel; // color channel in decimal

struct Color {
	Color(channel red, channel green, channel blue, channel alpha)
	: red(red), green(green), blue(blue), alpha(alpha) { }

	std::string getHex() const;

	channel red;
	channel green;
	channel blue;
	channel alpha;
};

std::string decimal2hex(channel decimal) {
	std::string result;

	char symbols[16] = {'0','1','2','3',
						'4','5','6','7',
						'8','9','A','B',
						'C','D','E','F'};
	result.push_back(symbols[decimal/16]);
	result.push_back(symbols[decimal%16]);

	return result;
}

std::string Color::getHex() const {
	std::string result = "#";

	result += decimal2hex(this->red);
	result += decimal2hex(this->green);
	result += decimal2hex(this->blue);
	result += decimal2hex(this->alpha);

	return result;
}

channel string2channel(const std::string& str) {
	channel result;

	short digit = pow(10, str.length() - 1);

	for (char c : str) {
		if (c >= 48 && c <= 57) {
			result += (c-48) * digit;
			digit /= 10;
		} else {
			std::cout << "String to channel error!\n";
			exit(1);
		}
	}

	return result;
}

channel percent2decimal(short percentage) {
	return percentage*255/100;
}

void channelsFormat(std::vector<channel>& channels, const std::string& format) {
	for (short i = 0; i < format.length(); ++i) {
		channel& c = channels.at(i);
		switch (format.at(i)) {
			case 'd':
			break;
			case 'p':
				c = percent2decimal(c);
			break;
			default:
				std::cout << "Invalid format\n";
				exit(1);
			break;
		}
	}
}

void printHelp() {
	std::cout << "Usage:\n"
                 "cat <file> | " << PROGRAM_NAME << "\n"
                 "cat <file> | " << PROGRAM_NAME << " <format>\n"
                 "format: xxxx where x can be \'d\' or \'p\'\n"
                 "d = decimal (0-255)\n"
                 "p = percentage (0-100%)\n"
                 "default format is 'dddp' if <format> is omitted\n"
                 "Example:\n"
                 "cat file | " << PROGRAM_NAME << " dddp\n";
}

int main(int argc, char** argv) {

	std::string rgbaFormat = "dddp";

	if (argc == 2) {
		std::string arg = argv[1];

		if (arg == "-h" || arg == "--help") {
			printHelp();
			exit(0);
		}

		rgbaFormat = arg;
		std::regex formatRegex( R"((d|p){4})" );

		if ( !(std::regex_match(rgbaFormat, formatRegex)) ) {
			std::cout << "rgba format invalid!\n";
			printHelp();
			exit(1);
		}
	}

	std::string line;
	std::regex rgba_regex( R"(rgba\s*\(\s*\d+\s*\%?\s*,\s*\d+\s*\%?\s*,\s*\d+\s*\%?\s*,\s*\d+\s*\%?\s*\))" );
	std::smatch rgbaMatch;
	std::regex numbers_regex( R"(\d+)");

	while (std::getline(std::cin, line)) {

		if (!std::regex_search(line, rgbaMatch, rgba_regex)) {
			std::cout << line << '\n';
			continue;
		}

		std::vector<channel> channels;
		std::string subline = rgbaMatch.str();

		for (std::smatch number; std::regex_search(subline, number, numbers_regex);) {
			channels.push_back(string2channel(number.str()));
			subline = number.suffix();
		}

		channelsFormat(channels, rgbaFormat);

		Color color(channels.at(0), channels.at(1), channels.at(2), channels.at(3));

		std::cout << std::regex_replace(line, rgba_regex, color.getHex()) << '\n';
	}
}
