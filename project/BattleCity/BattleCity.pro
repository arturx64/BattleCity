TEMPLATE = app

QT += qml quick
CONFIG += c++11

INCLUDEPATH +=   ../../src/includes/

SOURCES += \
    ../../src/src/main.cpp \
    ../../src/src/GameComponents/actor.cpp \
    ../../src/src/Phisics/phisical_engine.cpp \
    ../../src/src/game_play.cpp \
    ../../src/src/GameComponents/wall_actor.cpp \
    ../../src/src/Phisics/collider.cpp \
    ../../src/src/Map/map.cpp \
    ../../src/src/Map/pre_def_map_builder.cpp \
    ../../src/src/GameComponents/movable_actor.cpp \
    ../../src/src/GameComponents/tank.cpp \
    ../../src/src/GameComponents/unit.cpp \
    ../../src/src/GameComponents/wall_type.cpp \
    ../../src/src/Map/map_details.cpp \
    ../../src/src/GameComponents/projectile_actor.cpp \
    ../../src/src/direction.cpp \
    ../../src/src/GameComponents/player_tank.cpp \
    ../../src/src/GameComponents/enemy_tank.cpp \
    ../../src/src/Phisics/channel.cpp \
    ../../src/src/GameComponents/spawn_actor.cpp \
    ../../src/src/Phisics/rect_collider.cpp \
    ../../src/src/Phisics/tabular_collider.cpp \
    ../../src/src/Phisics/hit_visitor.cpp \
    ../../src/src/GameComponents/brick_wall.cpp \
    ../../src/src/GameComponents/metall_wall.cpp \
    ../../src/src/GameComponents/eagle.cpp \
    ../../src/src/game.cpp \
    ../../src/src/general_health.cpp

RESOURCES += \
    ../../qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    ../../src/includes/GameComponents/actor.h \
    ../../src/includes/Patterns/singleton.h \
    ../../src/includes/Phisics/phisical_engine.h \
    ../../src/includes/game_play.h \
    ../../src/includes/GameComponents/wall_actor.h \
    ../../src/includes/GameComponents/wall_type.h \
    ../../src/includes/Phisics/collider.h \
    ../../src/includes/Map/map.h \
    ../../src/includes/Map/map_builder_interface.h \
    ../../src/includes/Map/pre_def_map_builder.h \
    ../../src/includes/GameComponents/movable_actor.h \
    ../../src/includes/direction.h \
    ../../src/includes/GameComponents/tank.h \
    ../../src/includes/GameComponents/unit.h \
    ../../src/includes/Map/map_details.h \
    ../../src/includes/GameComponents/projectile_actor.h \
    ../../src/includes/GameComponents/player_tank.h \
    ../../src/includes/GameComponents/enemy_tank.h \
    ../../src/includes/Phisics/channel.h \
    ../../src/includes/GameComponents/spawn_actor.h \
    ../../src/includes/Phisics/collider_interface.h \
    ../../src/includes/Phisics/rect_collider.h \
    ../../src/includes/Phisics/tabular_collider.h \
    ../../src/includes/Phisics/hit_visitor.h \
    ../../src/includes/GameComponents/metall_wall.h \
    ../../src/includes/GameComponents/brick_wall.h \
    ../../src/includes/GameComponents/eagle.h \
    ../../src/includes/game.h \
    ../../src/includes/general_health.h
