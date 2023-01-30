TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

HEADERS += \
    libreria.h

INCLUDEPATH += / /home/adrian/Escritorio/dicom-classifier-main/DicomClassifier \ # Aqui es el path del proyecto con las cabeceras.

LIBS += -L/home/adrian/Escritorio/dicom-classifier-main/build \  # Directorio con los archivos compilados
        -ldcmdata \
        -ldcmimgle \
        -ldcmimage \
        -ldcmjpeg \
        -lpthread
