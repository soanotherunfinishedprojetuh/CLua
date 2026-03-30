#pragma once
namespace ASTNodes {
    class CharLiteral {
        char* value;
    };

    class StringLiteral {
        const char* string;
    };

    class NumberLiteral {
        long double value;
    };

    class IntegerLiteral {
        unsigned long long value;
    };
}
