########################################################################
#                                               .:^7^                  #
#                                         :^!?Y5PGGBG~77               #
#                                 .:~7JJ B#GGBBBGPYJ&#G#^              #
#                          .^. 5GGBBBB#&.!@GPB?   ?JPB5:               #
#                   .^!JPG##&#.#&#&#G#Y.  B&PPPGBBBBBG^                #
#              .5G#&&&&&&&#BP? .. ?@GB5   :@BPGBJ7~:.                  #
#              ^@@&&B#@#&P         #&GB!   Y&PG5                       #
#               ^^.  .&&##:        ^@BGB.   &#PG~                      #
#                     ?@##G         P&GBY   ~@PPG                      #
#                      #&#&!         &#GB~:~ G&PGJ                     #
#                      ^@###       .!G#GGBB#J.&#B?                     #
#                       P@##Y      Y@####BPY: ..                       #
#                       .&&#&:     .J7^.                               #
#                        7&B5.                                         #
#                                                                      #
#                                                                      #
########################################################################

cmake_minimum_required(VERSION 3.23)
project(TIP CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC_SEARCH_PATHS "source/ui")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build) # path/to/build_directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_EXE_LINKER_FLAGS}")

set(CMAKE_CXX_LINKER_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_CXX_LINKER_FLAGS}")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(QT_COMPONENTS Core Gui Widgets Sql PrintSupport Network)

find_package(
        Qt5
        COMPONENTS
        ${QT_COMPONENTS}
        REQUIRED
)

function(find_files dir type result)
    file(GLOB_RECURSE files LIST_DIRECTORIES false "${dir}/**/*.${type}")
    set(${result} ${files} PARENT_SCOPE)
endfunction()

set(UI_DIRECTORY "source/ui")
find_files(${UI_DIRECTORY} "ui" UI_FILES)

include_directories(source)

add_library(
        image_downloader SHARED
        source/services/image-downloader/image_downloader.cpp
)

set(CONSOLE_FLAG)
if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(CONSOLE_FLAG WIN32)
endif ()

add_executable(
        ${PROJECT_NAME}
        ${CONSOLE_FLAG}
        source/main.cpp
        source/interfaces/font-editor/font_editor.cpp
        source/interfaces/font-editor/font_editor.h
        source/interfaces/options/options.cpp
        source/interfaces/options/options.h
        source/interfaces/mainwindow/mainwindow.cpp
        source/interfaces/mainwindow/mainwindow.h
        source/interfaces/text-position-selector/text_position_selector.cpp
        source/interfaces/text-position-selector/text_position_selector.h
        source/interfaces/database-settings/database_settings.cpp
        source/interfaces/database-settings/database_settings.h
        source/interfaces/password-form/password_form.cpp
        source/interfaces/password-form/password_form.h
        source/interfaces/records-amount-form/records_amount_form.cpp
        source/interfaces/records-amount-form/records_amount_form.h
        ${UI_FILES}
        source/services/settings/settings_manager.cpp
        source/services/text-painter/text_painter.cpp
        source/services/theme-loader/theme_loader.cpp
        source/services/image-printer/image_printer.cpp
        source/resources/icon.rc
)

target_link_libraries(
        image_downloader
        PUBLIC
        Qt5::Network
)

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::PrintSupport
        image_downloader
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)

# Копирование содержимого папки reference в build
add_custom_command(
        TARGET ${PROJECT_NAME}  # Укажите вашу цель
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/build_folder_reference/
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Qt autoDLL
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/sqldrivers/qsqlpsql${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/sqldrivers/qsqlpsql${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${QT_INSTALL_PATH}/plugins/printsupport"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/printsupport")
    endif ()
    foreach (QT_LIB ${QT_COMPONENTS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
