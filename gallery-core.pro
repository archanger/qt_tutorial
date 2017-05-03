TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    desktop

desktop.depends = gallery-core
