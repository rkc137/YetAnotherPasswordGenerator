#include <array>
#include <cassert>
#include <cstdlib>
#include <ctime>

class PasswordGenerator
{
public:
	static std::string generate(std::size_t size = 10)
	{
		// assert(size); maybe you REALLY want to get 0 length password
		static auto init = [&](){
			std::srand(std::time({})); 
			return true;
		}();
		std::string password(size, '\1');
		for(auto &c : password)
			c = symbols[std::rand() % symbols.size()];
		return password;
	}
private:
	static constexpr std::array spec_symbols = {':', ';', '-', '_', '/', '?', '$', '#', '&'};
	static constexpr int count = 
		'9' - '0' + 1 + 
		(('z' - 'a') * 2) + 2 + 
		spec_symbols.size();
	static constexpr std::array<char, count> symbols = []() constexpr {
		std::array<char, count> s{};

		int j = 0;
		for(; j < 10; j++)
			s[j] = '0' + j;
		
		for(char c : {'a', 'A'})
			for (int i = 0; i < 26; i++)
				s[j++] = c + i;
			
		for(auto sc : spec_symbols)
			s[j++] = sc;
		
		return s;
	}();
};