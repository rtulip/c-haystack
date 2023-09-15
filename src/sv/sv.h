#ifndef SV_H_
#define SV_H_


#include <stddef.h>
#include <stdbool.h>

typedef struct StringView {
    const char* slice;
    size_t length;
} StringView;

StringView sv_new(const char* string);
StringView sv_split_at_pattern(StringView* const  sv, const char* pattern);
StringView sv_read_from_file_alloc(const char* const filepath);
StringView sv_substring(const StringView* const sv, size_t start, size_t end);

bool sv_equals(const StringView* const sv, const char* string);
void sv_print(const StringView* const  sv);
void sv_println(const StringView* const sv);

void register_sv_printf(void);

#endif 