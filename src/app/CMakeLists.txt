
set(WIN_PROJECT_SOURCES )
set(MAC_PROJECT_SOURCES )


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MAC_PROJECT_SOURCES
    # Todo: theme detection needed with new qt version?
            #ui/mac/themeDetection.mm
    )
endif()


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WIN_PROJECT_SOURCES
    # Todo: title bar theming needed with new qt version?
            #ui/windows/titleBar.h
    )
endif()


add_library(app STATIC
        ${PROJECT_ASSETS}

        ${WIN_PROJECT_SOURCES}
        ${MAC_PROJECT_SOURCES}

        init.h
        Settings.h
        Settings.cpp
        ApplicationManager.h

        ui/MainWindow.cpp
        ui/MainWindow.h

        ui/MainWidget.cpp
        ui/MainWidget.h

        ui/dialogs/info/InfoDialog.h
        ui/dialogs/info/InfoDialog.cpp

        ui/dialogs/settings/SettingsDialog.h
        ui/dialogs/settings/SettingsDialog.cpp
        ui/dialogs/settings/GeneralSettingsTab.cpp
        ui/dialogs/settings/GeneralSettingsTab.h
        ui/dialogs/settings/StyleSettingsTab.cpp
        ui/dialogs/settings/StyleSettingsTab.h

        utils/FilePathUtil.h
)

target_link_libraries(app PUBLIC
        Qt6::Widgets
        Qt6::Concurrent
)

#target_link_libraries(app PRIVATE
#        #OpenSSL::openssl
#        Libssh2::libssh2
#)