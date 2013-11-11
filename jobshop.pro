#-----------------------------------------------------------------------------
#
#    kSzereg - program szeregujący zadania w systemie wytwarzania gniazdowego
#    z wykorzystaniem heurystyk LIFO i FIFO, oraz wyznaczający parametry
#    strategii Just in Time. Praca inżynierska na wydziale Automatyki,
#    Elektroniki i Informatyki Politechniki Śląskiej w Gliwicach.
#    Copyright (C) 2012  Kamil 'konserw' Strzempowicz, konserw@gmail.com
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#----------------------------------------------------------------------------
TARGET = jobshop

QT += widgets svg

CONFIG += c++11 console

TEMPLATE = app
#QMAKE_CXXFLAGS += -Wall -Werror -Wextra

#OBJECTS_DIR =   temp
#UI_DIR =        temp
#MOC_DIR =       temp
#RCC_DIR =       temp

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    marszruta.cpp \
    maszyna.cpp \
    zadanie.cpp \
    wykres.cpp \
    grafZadanie.cpp \
    common.cpp \
    result.cpp \
    logger.cpp
HEADERS += \
    MainWindow.h \
    marszruta.h \
    maszyna.h \
    zadanie.h \
    common.h \
    wykres.h \
    grafZadanie.h \
    result.h \
    logger.h
FORMS += \
    MainWindow.ui \
    marszruta.ui \
    wykres.ui
OTHER_FILES += \
    license/LICENSE \
    license/gpl-3.0.txt \
    license/gpl-3.0.html

RESOURCES += \
    zasoby.qrc
