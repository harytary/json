#include <iostream>

# define JSON_DIAGNOSTICS 1
# define JSON_DIAGNOSTIC_POSITIONS 1
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string json_string = R"(
    {
        "address": {
            "street": "Fake Street",
            "housenumber": "12"
        }
    }
    )";
    json j = json::parse(json_string);

    try
    {
        int housenumber = j["address"]["housenumber"];
    }
    catch (const json::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}
