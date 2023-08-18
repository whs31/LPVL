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

#include "basicpalette.h"

/**
 * \class QQuickItem
 * \extends QObject
 */

/**
 * \brief Пространство имен библиотеки LPVL.
 */
namespace LPVL
{
  /**
   * \class BasicPalette
   * \brief Простейшая палитра цветов.
   * \details Класс предоставляет набор цветов с сеттерами, геттерами и сигналами.
   * Доступны следующие цвета:
   * - <span style="background:#000000">цвет заднего плана</span>
   * - <span style="background:#FFFFFF">цвет переднего плана</span>
   * - <span style="background:#666666">промежуточный цвет</span>
   * - <span style="background:#777777">второй промежуточный цвет</span>
   * - <span style="background:#00FF00">акцентный цвет</span>
   * - <span style="background:#FFFF00">цвет предупреждений</span>
   * - <span style="background:#FF0000">цвет ошибок</span>
   * - <span style="background:#0000FF">цвет оповещений</span>
   *
   * Класс зарегистрирован в мета-системе и доступен для встраивания в типы QML.
   */

  BasicPalette::BasicPalette()
    : m_background("black")
    , m_foreground("white")
    , m_overlay("gray")
    , m_overlay2("#777777")
    , m_accent("green")
    , m_warn("yellow")
    , m_error("red")
    , m_info("blue")
  {}

  /**
   * \property BasicPalette::background
   * \brief Цвет фона.
   * \details По умолчанию равен <span style="background:#000000">#000000</span>.
   */
  QColor BasicPalette::background() const { return m_background; }
  void BasicPalette::setBackground(const QColor& x) { m_background = x; }

  /**
   * \property BasicPalette::foreground
   * \brief Цвет, контрастный к фону.
   * \details По умолчанию равен <span style="background:#FFFFFF">#FFFFFF</span>.
   */
  QColor BasicPalette::foreground() const { return m_foreground; }
  void BasicPalette::setForeground(const QColor& x) { m_foreground = x; }

  /**
   * \property BasicPalette::overlay
   * \brief Цвет, промежуточный между #background и #foreground.
   * \details По умолчанию равен <span style="background:#666666">#666666</span>.
   */
  QColor BasicPalette::overlay() const { return m_overlay; }
  void BasicPalette::setOverlay(const QColor& x) { m_overlay = x; }

  /**
 * \property BasicPalette::overlay2
 * \brief Цвет, промежуточный между #background и #foreground.
 * \details По умолчанию равен <span style="background:#777777">#777777</span>.
 */
  QColor BasicPalette::overlay2() const { return m_overlay2; }
  void BasicPalette::setOverlay2(const QColor& x) { m_overlay2 = x; }

  /**
   * \property BasicPalette::accent
   * \brief Основной акцентный цвет.
   * \details По умолчанию равен <span style="background:#00FF00">#00FF00</span>.
   */
  QColor BasicPalette::accent() const { return m_accent; }
  void BasicPalette::setAccent(const QColor& x) { m_accent = x; }

  /**
   * \property BasicPalette::warn
   * \brief Цвет предупреждений.
   * \details По умолчанию равен <span style="background:#FFFF00">#FFFF00</span>.
   */
  QColor BasicPalette::warn() const { return m_warn; }
  void BasicPalette::setWarn(const QColor& x) { m_warn = x; }

  /**
   * \property BasicPalette::error
   * \brief Цвет ошибок.
   * \details По умолчанию равен <span style="background:#FF0000">#FF0000</span>.
   */
  QColor BasicPalette::error() const { return m_error; }
  void BasicPalette::setError(const QColor& x) { m_error = x; }

  /**
   * \property BasicPalette::info
   * \brief Цвет оповещений.
   * \details По умолчанию равен <span style="background:#0000FF">#0000FF</span>.
   */
  QColor BasicPalette::info() const { return m_info; }
  void BasicPalette::setInfo(const QColor& x) { m_info = x; }
}