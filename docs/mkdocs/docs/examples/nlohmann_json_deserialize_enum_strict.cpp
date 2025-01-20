#include <iostream>
#include <nlohmann/json.hpp>

#if !defined(JSON_NOEXCEPTION) && !defined(JSON_THROW_USER) && !defined(JSON_THROW)
    #define JSON_THROW(exception) throw exception
#else
    #include <cstdlib>
    #define JSON_THROW(exception) std::abort()
#endif

using json = nlohmann::json;

namespace ns
{
enum class Color
{
    red, green, blue
};

NLOHMANN_JSON_SERIALIZE_ENUM_STRICT(Color,
{
    { Color::red, "red" },
    { Color::green, "green" },
    { Color::blue, "blue" },
})
}

int main()
{

    // deserialization
    json j_yellow = "yellow";
    try
    {
        auto yellow = j_yellow.template get<ns::Color>();
        std::cout << j_yellow << " -> " << static_cast<int>(yellow) << std::endl;
    }
    catch (const nlohmann::json::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
