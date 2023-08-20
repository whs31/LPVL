#pragma once

#include <utility>
#include <QtCore/QString>

namespace LPVL
{
  class INameable
  {
    public:
      INameable();
      explicit INameable(QString);

      [[nodiscard]] QString name() const;
      virtual void setName(const QString&);

    protected:
      QString m_name;
  };
} // LPVL

namespace LPVL
{
  inline INameable::INameable()
    : m_name(QString()) {}

  inline INameable::INameable(QString q)
    : m_name(std::move(q)) {}

  inline QString INameable::name() const { return m_name; }
  inline void INameable::setName(const QString& q) { m_name = q; }
} // LPVL