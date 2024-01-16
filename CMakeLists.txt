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
#								                                       #
#    It is recommended to use Clion to build a proct successfully      #
#	    		     					                               #
#If the project is going under Linux/Unix/Mac OS:		               #
# 1. Install Qt5 						                               #
# 2. Remove the line CMAKE_PREFIX_PATH from this file	               #
# 3. Change the data for the build directory (if necessary)            #
# 4. Open the terminal and go to the directory with the project        #
# 5. Write cmake.   		     				                       #
# 6. make			     				                               #
# 7. Congratulations! The project has been successfully assembled!     #
#			     					                                   #
#if the project is going under Windows:		      		               #
# 1. Install Qt5			     			                           #
# 2. Specify the directory with Qt5 in the CMAKE_PREFIX_PATH field,     #
#    you can see an example below	 	     		                   #
# 3. Change the data for the build directory (if necessary)            #
# 4. Open the terminal and go to the directory with the project        #
# 5. Write cmake . 		     				                           #
# 6. make                 			     		                       #
# 7. Congratulations! The project has been successfully assembled!     #
#			     					                                   #
########################################################################
cmake_minimum_required(VERSION 3.23)
project(TIP CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC_SEARCH_PATHS "source/ui/windows")

set(QT_PATH "E:/Development/CPP/Libraries/Qt/5.14.2/mingw73_64")
set(CMAKE_PREFIX_PATH "${QT_PATH}/lib/cmake/Qt5")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build) # path/to/build_directory

find_package(
        Qt5
        COMPONENTS
        Core
        Gui
        Widgets
        Sql
        PrintSupport
        REQUIRED
)

function(find_ui_files dir result)
    file(GLOB_RECURSE ui_files LIST_DIRECTORIES false "${dir}/**/*.ui")
    set(${result} ${ui_files} PARENT_SCOPE)
endfunction()

set(UI_FILES
        source/services/text-painter/text_painter.cpp
        source/services/text-painter/text_painter.h)
find_ui_files(source/ui UI_FILES)

add_executable(
        ${PROJECT_NAME}
        WIN32
        source/main.cpp
#        source/interfaces/fontchanger/fontchanger.cpp
#        source/interfaces/fontchanger/fontchanger.h
        source/interfaces/mainwindow/mainwindow.cpp
        source/interfaces/mainwindow/mainwindow.h
#        source/interfaces/options/options.cpp
#        source/interfaces/options/options.h
        source/services/settings/settings.cpp
        source/services/settings/settings.h
        source/services/text-painter/text_painter.cpp
        source/services/text-painter/text_painter.h
        ${UI_FILES}
)

target_link_libraries(
        ${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::PrintSupport
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)