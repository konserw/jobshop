#-----------------------------------------------------------------------------
#
#    jobshop
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

CONFIG += c++11 #console

TEMPLATE = app
#QMAKE_CXXFLAGS += -Wall -Werror -Wextra

#OBJECTS_DIR =   temp
#UI_DIR =        temp
#MOC_DIR =       temp
#RCC_DIR =       temp

SOURCES += \
    main.cpp \
    MainWindow.cpp \
 #   maszyna.cpp \
    grafZadanie.cpp \
    common.cpp \
    result.cpp \
    logger.cpp \
    Operation.cpp \
    Job.cpp \
    ResultWindow.cpp \
    JobshopModel.cpp \
    OperationDelegate.cpp \
    Jobshop.cpp \
    OperationEditor.cpp

HEADERS += \
    MainWindow.h \
  #  maszyna.h \
    common.h \
    grafZadanie.h \
    result.h \
    logger.h \
    Operation.h \
    Job.h \
    ResultWindow.h \
    JobshopModel.h \
    OperationDelegate.h \
    Jobshop.h \
    OperationEditor.h

FORMS += \
    MainWindow.ui \
    ResultWindow.ui

OTHER_FILES += \
    license/LICENSE \
    license/gpl-3.0.txt \
    license/gpl-3.0.html

RESOURCES += \
    zasoby.qrc
