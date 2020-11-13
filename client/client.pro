TEMPLATE = app
TARGET = qmqtt_example
QT += network quick

SOURCES += \
    Publisher.cpp \
    Subscriber.cpp \
    main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/qmqtt/client
INSTALLS += target

RESOURCES += qml.qrc

android {
    include(androidOpenSsl/openssl.pri)
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    OTHER_FILES += \
        android/build.gradle \
        android/AndroidManifest.xml

    DISTFILES += \
        android/build.gradle \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat

    ANDROID_ABIS = armeabi-v7a
}

unix|win32: LIBS += -L$$OUT_PWD/../mqttLibrary/mqtt/ -lmqttLibrary

INCLUDEPATH += $$PWD/../mqttLibrary/mqtt
DEPENDPATH += $$PWD/../mqttLibrary/mqtt

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../mqttLibrary/mqtt/mqttLibrary.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../mqttLibrary/mqtt/libmqttLibrary.a

HEADERS += \
    Publisher.h \
    Subscriber.h


ios {

#    LIBS += -L$$PWD/openssl/lib/ -lssl -lcrypto

#    INCLUDEPATH += $$PWD/openssl/include
#    DEPENDPATH += $$PWD/openssl/include

#    PRE_TARGETDEPS += $$PWD/openssl/lib/libssl.a
#    PRE_TARGETDEPS += $$PWD/openssl/lib/libcrypto.a
}


