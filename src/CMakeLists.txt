set(preview_SRCS
    previewbridge.cpp
    previewclient.cpp
    previewitem.cpp
    previewsettings.cpp
    main.cpp
)

add_executable(kdecorationviewer ${preview_SRCS})
target_link_libraries(kdecorationviewer
    KDecoration2::KDecoration
    KDecoration2::KDecoration2Private
    Qt5::Quick
    KF5::ConfigWidgets
    KF5::Declarative
    KF5::I18n
)

install(DIRECTORY qml DESTINATION ${DATA_INSTALL_DIR}/org.kde.kdecorationviewer)
install(TARGETS kdecorationviewer ${INSTALL_TARGETS_DEFAULT_ARGS} )
