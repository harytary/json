#include <iostream>
#include <nlohmann/json.hpp>

#ifdef __cpp_exceptions
    #undef __cpp_exceptions
    #define __cpp_exceptions 1
#endif

#ifdef JSON_NOEXCEPTION
    #define JSON_NOEXCEPTION 0
#endif

#if (defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)) && !defined(JSON_NOEXCEPTION)
    #define JSON_THROW(exception) throw exception
    #define JSON_TRY try
    #define JSON_CATCH(exception) catch(exception)
    #define JSON_INTERNAL_CATCH(exception) catch(exception)
#else
    #include <cstdlib>
    #define JSON_THROW(exception) std::abort()
    #define JSON_TRY if(true)
    #define JSON_CATCH(exception) if(false)
    #define JSON_INTERNAL_CATCH(exception) if(false)
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
