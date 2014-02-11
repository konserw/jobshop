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

QT += widgets svg printsupport

CONFIG += c++11 #console

TEMPLATE = app
#QMAKE_CXXFLAGS += -Wall -Werror -Wextra

OBJECTS_DIR =   temp
UI_DIR =        temp
MOC_DIR =       temp
RCC_DIR =       temp

win32 {
    CONFIG(debug, release|debug) {
        QCPLIB = qcustomplotd1
    } else {
        QCPLIB = qcustomplot1
    }
} else {
    QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

    CONFIG(debug, release|debug) {
        QCPLIB = qcustomplotd
    } else {
        QCPLIB = qcustomplot
    }
}

DEFINES += QCUSTOMPLOT_USE_LIBRARY
LIBS += -L./qcustomplot/ -l$$QCPLIB

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    logger.cpp \
    Operation.cpp \
    Job.cpp \
    ResultWindow.cpp \
    JobshopModel.cpp \
    OperationDelegate.cpp \
    Jobshop.cpp \
    OperationEditor.cpp \
    Chromosome.cpp \
    EvolutionWindow.cpp \
    GanttMachine.cpp \
    GanttOperation.cpp \
    Result.cpp

HEADERS += \
    MainWindow.h \
    logger.h \
    Operation.h \
    Job.h \
    ResultWindow.h \
    JobshopModel.h \
    OperationDelegate.h \
    Jobshop.h \
    OperationEditor.h \
    Chromosome.h \
    EvolutionWindow.h \
    GanttMachine.h \
    GanttOperation.h \
    Result.h

FORMS += \
    MainWindow.ui \
    ResultWindow.ui

OTHER_FILES += \
    license/LICENSE \
    license/gpl-3.0.txt \
    license/gpl-3.0.html \
    snippets.txt

RESOURCES += \
    zasoby.qrc
