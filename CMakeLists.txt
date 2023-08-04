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
#								       #
#    It is recommended to use Clion to build a proct successfully      #
#	    		     					       #
#If the project is going under Linux/Unix/Mac OS:		       #
# 1. Install Qt5 						       #
# 2. Remove the line CMAKE_PREFIX_PATH from this file	               #
# 3. Change the data for the build directory (if necessary)            #
# 4. Open the terminal and go to the directory with the project        #
# 5. Write cmake.   		     				       #
# 6. make			     				       #
# 7. Congratulations! The project has been successfully assembled!     #
#			     					       #
#if the project is going under Windows:		      		       #
# 1. Install Qt5			     			       #
# 2. Specify the directory with Qt5 in the CMAKE_PREFIX_PATH field,    #
#    you can see an example below	 	     		       #
# 3. Change the data for the build directory (if necessary)            #
# 4. Open the terminal and go to the directory with the project        #
# 5. Write cmake . 		     				       #
# 6. make                 			     		       #
# 7. Congratulations! The project has been successfully assembled!     #
#			     					       #
########################################################################


cmake_minimum_required(VERSION 3.23)
project(TIP)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC_SEARCH_PATHS source/ui/)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH D:/ProgramFiles/Qt/5.14.2/mingw73_64/lib/cmake/Qt5) # path/to/Qt5

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build) # path/to/build_directory

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        PrintSupport
        REQUIRED
        )

add_executable(TIP
        WIN32
        source/main.cpp
        source/headers/mainwindow.h
        source/sources/mainwindow.cpp
        source/ui/mainwindow.ui
        source/headers/options.h
        source/sources/options.cpp
        source/ui/options.ui
        source/headers/fontchanger.h
        source/sources/fontchanger.cpp
        source/ui/fontchanger.ui
        source/sources/records_ammount.cpp
        source/headers/records_ammount.h
        source/ui/records_ammount.ui
        source/headers/logger.h
        source/sources/records_on_first_start.cpp
        source/headers/records_on_first_start.h
        source/ui/records_on_first_start.ui
        source/sources/progressbar.cpp
	  source/headers/progressbar.h
	  source/ui/progressbar.ui
	  )

target_link_libraries(TIP
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::PrintSupport
        )
