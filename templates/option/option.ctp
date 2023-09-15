#include "{{TargetDir}}/Option{{UpperTypeAlias}}.h"
#include <assert.h>
#include <stdio.h>

Option{{UpperTypeAlias}} option_{{LowerTypeAlias}}_some({{TypeName}} value)
{
    return (Option{{UpperTypeAlias}}) {
        .value = value,
        .is_some = true,
    };
}

Option{{UpperTypeAlias}} option_{{LowerTypeAlias}}_none(void)
{
    return (Option{{UpperTypeAlias}}) {
        .is_some = false,
    };
}

{{TypeName}} option_{{LowerTypeAlias}}_unwrap_internal(
    Option{{UpperTypeAlias}} option,
    const char* const file,
    const size_t line
)
{
    if (!option.is_some)
    {
        printf("%s:%ld: ERROR: Unwrapped a None Variant", file, line);
        assert(0);
    }

    return option.value;
}

bool option_{{LowerTypeAlias}}_is_some(const Option{{UpperTypeAlias}}* const option)
{
    assert(option != NULL);
    return option->is_some;
}