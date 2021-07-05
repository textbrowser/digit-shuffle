purge.commands = rm -f *~ && rm -f */*~

CONFIG		+= qt release warn_on
DEFINES		+= QT_DEPRECATED_WARNINGS
LANGUAGE        = C++
QT		+=
TEMPLATE        = app

QMAKE_CLEAN	+= DigitShuffle
QMAKE_CXXFLAGS  += -Wall \
                   -Wcast-align \
                   -Wcast-qual \
                   -Wdouble-promotion \
                   -Werror \
                   -Werror=format-security \
                   -Wextra \
                   -Wfloat-equal \
                   -Wformat=2 \
                   -Wno-deprecated-copy \
                   -Woverloaded-virtual \
                   -Wpointer-arith \
                   -Wstack-protector \
                   -Wstrict-overflow=5 \
                   -Wundef \
                   -Wzero-as-null-pointer-constant \
                   -fPIE \
                   -fstack-protector-all \
                   -fwrapv \
                   -pedantic \
                   -std=c++11

linux-* {
QMAKE_CXXFLAGS  += -Wconversion \
                   -Wformat-overflow=2 \
                   -Wsign-conversion \
                   -pie
}

QMAKE_EXTRA_TARGETS = purge

FORMS		= digit-shuffle.ui

HEADERS		= digit-shuffle.h

SOURCES		= digit-shuffle.cc

PROJECTNAME	= DigitShuffle
TARGET		= DigitShuffle
