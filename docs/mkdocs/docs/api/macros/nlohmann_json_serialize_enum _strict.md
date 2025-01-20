# NLOHMANN_JSON_SERIALIZE_ENUM_STRICT

```cpp
#define NLOHMANN_JSON_SERIALIZE_ENUM_STRICT(type, conversion...)
```

The `NLOHMANN_JSON_SERIALIZE_ENUM_STRICT` allows to define a user-defined serialization for every enumerator.

This macro declares strict serialization and deserialization functions (`to_json` and `from_json`) for an enum type. 
Unlike [`NLOHMANN_JSON_SERIALIZE_ENUM`](nlohmann_json_serialize_enum.md), this macro enforces strict validation and 
throws errors for unmapped values instead of defaulting to the first enum value.

## Parameters

`type` (in)
:   name of the enum to serialize/deserialize

`conversion` (in)
:   a pair of an enumerator and a JSON serialization; arbitrary pairs can be given as a comma-separated list

## Default definition

The macro adds two functions to the namespace which take care of the serialization and deserialization:

```cpp
template<typename BasicJsonType>
inline void to_json(BasicJsonType& j, const type& e);
template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, type& e);
```

## Notes

!!! info "Prerequisites"

    The macro must be used inside the namespace of the enum.

!!! important "Important notes"

    - If an enum value appears more than once in the mapping, only the first occurrence will be used for serialization, 
        subsequent mappings for the same enum value will be ignored.
    - If a JSON value appears more than once in the mapping, only the first occurrence will be used for deserialization, 
        subsequent mappings for the same JSON value will be ignored.
    - Unlike `NLOHMANN_JSON_SERIALIZE_ENUM`, this macro enforces strict validation:
        - Attempting to serialize an unmapped enum value will throw a `type_error.302` exception
        - Attempting to deserialize an unmapped JSON value will throw a `type_error.302` exception
        - There is no default value behavior - all values must be explicitly mapped

## Examples

??? example "Example 1: Strict serialization"

    The example shows how `NLOHMANN_JSON_SERIALIZE_ENUM_STRICT` enforces strict validation when serializing an enum value that is not in the mapping:

    ```cpp
    --8<-- "examples/nlohmann_json_serialize_enum_strict.cpp"
    ```

    Expected output:
    
    ```
    [json.exception.type_error.302] can't serialize - enum value 3 out of range
    ```

??? example "Example 2: Strict deserialization"

    The example shows how `NLOHMANN_JSON_SERIALIZE_ENUM_STRICT` enforces strict validation when deserializing a JSON value that is not in the mapping:

    ```cpp
    --8<-- "examples/nlohmann_json_deserialize_enum_strict.cpp"
    ```

    Expected output:
    
    ```
    [json.exception.type_error.302] can't deserialize - invalid json value : "yellow"
    ```

Both examples demonstrate:

- Proper error handling using try-catch blocks
- Clear error messages indicating the cause of failure
- No default value behavior - all values must be explicitly mapped
- Exception throwing for unmapped values

## See also

- [Specializing enum conversion](../../features/enum_conversion.md)
- [`JSON_DISABLE_ENUM_SERIALIZATION`](json_disable_enum_serialization.md)

## Version history

- Added in version 3.11.3.
