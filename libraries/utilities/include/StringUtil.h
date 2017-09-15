#pragma once

#include <algorithm>
#include <cstdarg>
#include <memory>
#include <stdio.h>
#include <string>

namespace ell
{
namespace utilities
{
    static std::string ToLowercase(const std::string& s)
    {
        std::string lower = s;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

#ifndef _MSC_VER
    static int _vscprintf(const char* format, va_list pargs)
    {
        int retval;
        va_list argcopy;
        va_copy(argcopy, pargs);
        retval = vsnprintf(NULL, 0, format, argcopy);
        va_end(argcopy);
        return retval;
    }
#endif

    static std::string stringf(const char* format, ...)
    {
        va_list args;
        va_start(args, format);

        auto size = _vscprintf(format, args) + 1U;
        std::unique_ptr<char[]> buf(new char[size]);

#ifndef _MSC_VER
        vsnprintf(buf.get(), size, format, args);
#else
        vsnprintf_s(buf.get(), size, _TRUNCATE, format, args);
#endif

        va_end(args);

        return std::string(buf.get());
    }
}
}