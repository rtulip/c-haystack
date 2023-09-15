#include "{{TargetDir}}/Vec{{UpperTypeAlias}}.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

Vec{{UpperTypeAlias}} vec_{{LowerTypeAlias}}_new(void)
{
    return (Vec{{UpperTypeAlias}}) {
        .capacity = 0,
        .length = 0,
        .slice = NULL,
    };
}

void vec_{{LowerTypeAlias}}_destroy(Vec{{UpperTypeAlias}}* const self)
{
    assert(self != NULL);
    free(self->slice);
    *self = vec_{{LowerTypeAlias}}_new();
}

static bool _vec_{{LowerTypeAlias}}_at_capacity(const Vec{{UpperTypeAlias}}* const self)
{
    assert(self != NULL);
    return (self->capacity == self->length);
}

static void _vec_{{LowerTypeAlias}}_expand(Vec{{UpperTypeAlias}}* const self)
{
    /**
     * Increase the capacity of the vec.
     * 
     * If it's 0, then set it to 2.
     */
    self->capacity = self->capacity == 0 ?
        2 :
        self->capacity * 2;

    self->slice = realloc(self->slice, sizeof({{TypeName}}) * self->capacity);
    
    assert(self->slice != NULL);
}

void vec_{{LowerTypeAlias}}_push(Vec{{UpperTypeAlias}}* const self, {{TypeName}} item)
{
    assert(self != NULL);
    if (_vec_{{LowerTypeAlias}}_at_capacity(self))
    {
        _vec_{{LowerTypeAlias}}_expand(self);
    }

    assert(self->slice != NULL);
    self->slice[self->length] = item;
    self->length += 1;
}

const {{TypeName}}* vec_{{LowerTypeAlias}}_at(const Vec{{UpperTypeAlias}}* const self, size_t index)
{
    assert(self != NULL);
    assert(index < self->length);

    return &self->slice[index];
}

const {{TypeName}}* vec_{{LowerTypeAlias}}_last(const Vec{{UpperTypeAlias}}* const self)
{
    assert(self != NULL);

    if (self->length == 0)
    {
        return NULL;
    }
    else 
    {
        return &self->slice[self->length-1];
    }

}