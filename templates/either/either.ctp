#include "{{TargetDir}}/Either{{LeftTypeUpper}}Or{{RightTypeUpper}}.h"
#include <assert.h>
#include <stdio.h>

Either{{LeftTypeUpper}}Or{{RightTypeUpper}} either_{{LeftTypeLower}}_or_{{RightTypeLower}}_new_{{LeftTypeLower}}({{LeftTypeName}} {{LeftTypeIdentifier}})
{
    return (Either{{LeftTypeUpper}}Or{{RightTypeUpper}}) {
        .either.left = {{LeftTypeIdentifier}},
        .is_left = true,
    };
}

Either{{LeftTypeUpper}}Or{{RightTypeUpper}} either_{{LeftTypeLower}}_or_{{RightTypeLower}}_new_{{RightTypeLower}}({{RightTypeName}} {{RightTypeIdentifier}})
{
    return (Either{{LeftTypeUpper}}Or{{RightTypeUpper}}) {
        .either.right = {{RightTypeIdentifier}},
        .is_left = false,
    };   
}

bool either_{{LeftTypeLower}}_or_{{RightTypeLower}}_is_{{LeftTypeLower}}(const Either{{LeftTypeUpper}}Or{{RightTypeUpper}}* const either)
{
    assert(either != NULL);
    return either->is_left;
}

bool either_{{LeftTypeLower}}_or_{{RightTypeLower}}_is_{{RightTypeLower}}(const Either{{LeftTypeUpper}}Or{{RightTypeUpper}}* const either)
{
    assert(either != NULL);
    return !either->is_left;
}

{{LeftTypeName}} either_{{LeftTypeLower}}_or_{{RightTypeLower}}_unpack_{{LeftTypeLower}}_internal(
    const Either{{LeftTypeUpper}}Or{{RightTypeUpper}}* const either,
    const char* const file,
    const size_t line
)
{
    assert(either != NULL);

    if (!either->is_left)
    {
        printf("%s:%lu ERROR: Tried to unpack a {{LeftTypeName}} from an Either{{LeftTypeUpper}}Or{{RightTypeUpper}} which is a(n) {{RightTypeName}}", file, line);
        assert(0);
    }

    return either->either.left;
}

{{RightTypeName}} either_{{LeftTypeLower}}_or_{{RightTypeLower}}_unpack_{{RightTypeLower}}_internal(
    const Either{{LeftTypeUpper}}Or{{RightTypeUpper}}* const either,
    const char* const file,
    const size_t line
)
{
    assert(either != NULL);

    if (either->is_left)
    {
        printf("%s:%lu ERROR: Tried to unpack a {{RightTypeName}} from an Either{{LeftTypeUpper}}Or{{RightTypeUpper}} which is an {{LeftTypeName}}", file, line);
        assert(0);
    }

    return either->either.right;
}