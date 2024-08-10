purge.commands = rm -f *~ && rm -f */*~

CONFIG		+= qt release warn_on
DEFINES		+= QT_DEPRECATED_WARNINGS
LANGUAGE        = C++
QT		+= concurrent widgets
TEMPLATE        = app

QMAKE_CLEAN	+= DigitShuffle

android {
QMAKE_CXXFLAGS  += -Wall \
                   -Wcast-align \
                   -Wcast-qual \
                   -Wdouble-promotion \
                   -Werror \
                   -Werror=format-security \
                   -Wextra \
                   -Wformat=2 \
                   -Wold-style-cast \
                   -Woverloaded-virtual \
                   -Wpointer-arith \
                   -Wstack-protector \
                   -Wstrict-overflow=1 \
                   -Wundef \
                   -Wzero-as-null-pointer-constant \
                   -fPIE \
                   -fstack-protector-all \
                   -fwrapv \
                   -pedantic \
                   -std=c++11
} else {
QMAKE_CXXFLAGS  += -Wall \
                   -Wcast-align \
                   -Wcast-qual \
                   -Wdouble-promotion \
                   -Werror \
                   -Werror=format-security \
                   -Wextra \
                   -Wformat=2 \
                   -Wno-deprecated-copy \
                   -Wold-style-cast \
                   -Woverloaded-virtual \
                   -Wpointer-arith \
                   -Wstack-protector \
                   -Wstrict-overflow=1 \
                   -Wundef \
                   -Wzero-as-null-pointer-constant \
                   -fPIE \
                   -fstack-protector-all \
                   -fwrapv \
                   -pedantic \
                   -std=c++11

linux-* {
QMAKE_CXXFLAGS  += -Wformat-overflow=2 \
                   -pie
}
}

greaterThan(QT_MAJOR_VERSION, 5) {
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS -= -std=c++11
}

QMAKE_EXTRA_TARGETS = purge

FORMS		= digit-shuffle.ui

HEADERS		= digit-shuffle.h

RESOURCES       = icons.qrc

SOURCES		= digit-shuffle.cc

PROJECTNAME	= DigitShuffle
TARGET		= DigitShuffle

android {
DISTFILES += android/AndroidManifest.xml \
             android/build.gradle \
             android/gradle.properties \
             android/gradle/wrapper/gradle-wrapper.jar \
             android/gradle/wrapper/gradle-wrapper.properties \
             android/gradlew \
             android/gradlew.bat \
             android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
}
