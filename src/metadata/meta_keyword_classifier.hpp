#pragma once

#include <string>
#include <cstring>

#define META_KEYWORDS \
    MetaKeyword(Lua_Embed,"lua_embed") \
    MetaKeyword(Import,"import")\
    MetaKeyword(Export,"export")\

namespace MetaKeywordClassifier {
    enum class MetaKeyword {
        #define MetaKeyword(MetaKeywordValue,MetaKeywordString)\
            MetaKeywordValue,    
            META_KEYWORDS
        #undef MetaKeyword
        Unknown
    };

    MetaKeyword get_keyword_type(const char* keyword)
    {
        if (!keyword || !*keyword) return MetaKeyword::Unknown;

        #define MetaKeyword(MetaKeywordValue, MetaKeywordString) \
            else if (std::strcmp(keyword, MetaKeywordString) == 0) { \
                return MetaKeyword::MetaKeywordValue; \
            }
            META_KEYWORDS
        #undef MetaKeyword

        else return MetaKeyword::Unknown;
    };

    MetaKeyword get_keyword_type(std::string_view keyword)
    {
        if (keyword.length() == 0) return MetaKeyword::Unknown;

        #define MetaKeyword(MetaKeywordValue, MetaKeywordString) \
            else if (keyword == MetaKeywordString) { \
                return MetaKeyword::MetaKeywordValue; \
            }
            META_KEYWORDS
        #undef MetaKeyword

        else return MetaKeyword::Unknown;
    }

    const char* keyword_to_string(MetaKeyword kw)
    {
        switch (kw)
        {
        #define MetaKeyword(MetaKeywordValue, MetaKeywordString) \
            case MetaKeyword::MetaKeywordValue: return MetaKeywordString;
                META_KEYWORDS
        #undef MetaKeyword
                default: return "<Unknown>";
        }
    }

};

#undef META_KEYWORDS