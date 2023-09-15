#include "{{TargetDir}}/Option{{TypeAlias}}.h"
#include <assert.h>
#include <stdio.h>

Option{{TypeAlias}} option_{{TypeName}}_some({{TypeName}} value)
{
    return (Option{{TypeAlias}}) {
        .value = value,
        .is_some = true,
    };
}

Option{{TypeAlias}} option_{{TypeName}}_none(void)
{
    return (Option{{TypeAlias}}) {
        .is_some = true,
    };
}

{{TypeName}} option_{{TypeName}}_unwrap_internal(
    Option{{TypeAlias}} option,
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

bool option_{{TypeName}}_is_some(Option{{TypeAlias}}* option)
{
    assert(option != NULL);
    return option->is_some;
}