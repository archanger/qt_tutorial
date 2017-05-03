TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    desktop \
    mobile

desktop.depends = gallery-core
