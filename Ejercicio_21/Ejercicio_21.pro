QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 # Puedes usar c++17 o c++20 si lo deseas

# Archivos fuente del proyecto
SOURCES += \
    main.cpp \
    htmlparsergui.cpp

# Archivos de cabecera del proyecto
HEADERS += \
    htmlparsergui.h

# Puedes añadir CONFIG -= app_bundle y CONFIG -= qt_debug si quieres una salida más limpia,
# pero no son estrictamente necesarios para que funcione.
# CONFIG -= app_bundle
# CONFIG -= qt_debug

# Reglas de implementación por defecto (puede que no las necesites en todos los OS)
unix:!macx: LIBS += -lresolv
