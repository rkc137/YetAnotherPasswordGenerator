#include <iostream>
#include <algorithm>
#include <limits>

#include "PasswordGenerator.hpp"

int main(int argc, char *argv[])
{
    std::string prog_name = [&](){
        const std::string path = argv[0];
        #ifdef _WIN32
            char slash = '\\';
        #elif __unix__
            char slash = '/';
        #endif
        auto const pos = path.find_last_of(slash);
        return path.substr(pos + 1);
    }();
    auto usage = std::string{"usage: "} + prog_name + " [length of password]\n";

    std::size_t length = 10;
    if(argc > 2)
    {
        std::cerr << "too many arguments\n" << usage;
        return 1;
    }

    auto max_length = std::string{}.max_size();
    if(argc != 1) try
    {
        long long i = std::stoll(argv[1]);
        if(i < 0) throw std::invalid_argument{""};
        if(i > max_length) throw std::out_of_range{""};
        length = static_cast<std::size_t>(i);
    }
    catch(std::invalid_argument const &ex)
    {
        std::cerr << "invalid argument\n" << usage;
        return 2;
    }
    catch(std::out_of_range const &ex)
    {
        std::cerr << "too big length\ntry lower than " << max_length << '\n';
        return 3;
    }
    
    try
    {
        std::cout << PasswordGenerator::generate(length) << '\n';
    }
    catch(std::bad_alloc const &ex)
    {
        std::cerr << "bad alloc (upgrade pc lol)\ntry shorter length\n";
        return 4;
    }
    
    return 0;
}