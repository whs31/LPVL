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

#include <QtCore/QtGlobal>

#if defined LPVL_LIBRARY && !defined LPVL_STATIC
    #define LPVL_EXPORT Q_DECL_EXPORT
#elif !defined LPVL_LIBRARY && !defined LPVL_STATIC
    #define LPVL_EXPORT Q_DECL_IMPORT
#else
    #define LPVL_EXPORT
#endif

#define LPVL_DECLARE_NO_COPY(name) private: name (const name&); name & operator=(const name &);
#define LPVL_DECLARE_SINGLETON(name) public: static name * get() { static name instance; return &instance; } private: LPVL_DECLARE_NO_COPY(name)

#define LPVL_REGISTER_QML(type, name, module) __attribute__((constructor)) static void register_qml() {qmlRegisterType<type>(module, 1, 0, name); qInfo() << "<LPVL> Registered type" << name << "in module" << module; }
#define LPVL_DESCRIBE_SELF(version) __attribute__((constructor)) static void describe() { qInfo() << "<LPVL> Library loaded. Version" << version; }

#define QML_EXPOSE_INSTANCE(type, import_module, name, instance) qmlRegisterSingletonInstance<type>(import_module, 1, 0, name, instance);
#define QML_EXPOSE_INSTANTIABLE(type, import_module, name) qmlRegisterType<type>(import_module, 1, 0, name);

#define LPVL_UNIMPLEMENTED
