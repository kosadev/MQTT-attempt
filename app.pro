TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    mqttLibrary \
    client

client.depends = mqttLibrary