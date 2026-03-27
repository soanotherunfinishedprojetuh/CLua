#pragma once

#include <cstring>
#include <string>

#define KEYWORDS \
    MetaKeyword(Import, "import") \
    MetaKeyword(Export, "export")\
    MetaKeyword(LuaEmbed,"lua_embed")

namespace KeywordClassifier {
    enum class MetaKeyword {
        #define MetaKeyword(KeywordValue,KeywordString)\
            KeywordValue,    
            KEYWORDS
        #undef MetaKeyword
        Unknown
    };

    MetaKeyword get_metakeyword_type(const char* keyword)
    {
        if (!keyword || !*keyword) return MetaKeyword::Unknown;

        #define MetaKeyword(KeywordValue, KeywordString) \
            else if (std::strcmp(keyword, KeywordString) == 0) { \
                return MetaKeyword::KeywordValue; \
            }
            KEYWORDS
        #undef MetaKeyword

        else return MetaKeyword::Unknown;
    };

    MetaKeyword get_metakeyword_type(std::string_view keyword)
    {
        if (keyword.length() == 0) return MetaKeyword::Unknown;

        #define MetaKeyword(KeywordValue, KeywordString) \
            else if (keyword == KeywordString) { \
                return MetaKeyword::KeywordValue; \
            }
            KEYWORDS
        #undef MetaKeyword

        else return MetaKeyword::Unknown;
    }


    const char* metakeyword_to_string(MetaKeyword kw)
    {
        switch (kw)
        {
        #define MetaKeyword(KeywordValue, KeywordString) \
            case MetaKeyword::KeywordValue: return KeywordString;
                KEYWORDS
        #undef MetaKeyword
                default: return "<Unknown>";
        }
    }
  
};



#undef KEYWORDS