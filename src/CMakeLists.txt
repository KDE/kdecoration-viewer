set(preview_SRCS
    previewbridge.cpp
    previewclient.cpp
    previewitem.cpp
    previewsettings.cpp
    main.cpp
)

add_definitions(-DSOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
add_executable(kdecorationviewer ${preview_SRCS})
target_link_libraries(kdecorationviewer
    KDecoration2::KDecoration
    KDecoration2::KDecoration2Private
    Qt5::Quick
    KF5::ConfigWidgets
    KF5::Service
    KF5::I18n
)
