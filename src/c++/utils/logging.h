/* ---------------------------------------------------------------------
 * LPVL - Linear Algebra, Plotting and Visualisation Library
 * Copyright (C) 2023 whs31.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 * http://www.gnu.org/licenses.
 *
 * github.com/whs31/lpvl
 * ---------------------------------------------------------------------- */

#pragma once

#include <string_view>
#include <QtCore/QtGlobal>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <CTRE/CTRE>

using std::u16string_view;

#define scope_info LPVL::Internal::parseScopeInfo(Q_FUNC_INFO)
#define lpvl_separator "."

namespace LPVL::Logging
{
  enum LoggingSeparator
  {
    Dot,
    DoubleSemicolon
  };

  inline bool setLoggingPattern() noexcept;
  inline bool setLoggingPattern(const QString& pattern) noexcept;
  inline void setSeparator(LoggingSeparator separator) noexcept;
} // LPVL::Logging

namespace LPVL::Internal
{
  inline auto toU16StringView(const QString& str) -> u16string_view;
  inline const char* parseScopeInfo(const char* x) noexcept;
} // LPVL::Internal

namespace LPVL::Logging
{
  inline bool setLoggingPattern() noexcept
  {
    #if !defined(CUSTOM_DEBUG_OUTPUT) && defined QT_CORE_LIB
    #define CUSTOM_DEBUG_OUTPUT
      qSetMessagePattern("[%{time process}] [%{category}] "
                         "%{if-debug}\033[01;38;05;15m%{endif}"
                         "%{if-info}\033[01;38;05;146m%{endif}"
                         "%{if-warning}\033[1;33m%{endif}"
                         "%{if-critical}\033[1;31m%{endif}"
                         "%{if-fatal}FATAL ERROR \033[1;31m%{endif}%{message}\033[0m");
      return true;
    #else
      return false;
    #endif
  }

  inline bool setLoggingPattern(const QString& pattern) noexcept
  {
    #if !defined(CUSTOM_DEBUG_OUTPUT) && defined QT_CORE_LIB
    #define CUSTOM_DEBUG_OUTPUT
      qSetMessagePattern(pattern);
      return true;
    #else
      return false;
    #endif
  }

  inline void setSeparator(LoggingSeparator separator) noexcept
  {
    #undef lpvl_separator
    switch(separator)
    {
      case DoubleSemicolon:
        #define lpvl_separator "::"
        break;
      case Dot:
      default:
        #define lpvl_separator "."
        break;
    }
  }
} // LPVL::Logging

namespace LPVL::Internal
{
  inline auto toU16StringView(const QString& str) -> u16string_view
  {
    return {reinterpret_cast<const char16_t*>(str.utf16()), static_cast<size_t>(str.size())};
  }

  inline const char* parseScopeInfo(const char* x) noexcept
  {
    QRegExp r(".* ([^\\s]*)\\(");
    r.lastIndexIn(x);
    return r.capturedTexts().back().replace("::", lpvl_separator).append(":").toLocal8Bit().data();
  }
} // LPVL::Internal