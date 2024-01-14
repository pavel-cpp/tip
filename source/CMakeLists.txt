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

set(LIBRARYS "")

add_subdirectory(services)
add_subdirectory(interfaces)

add_executable(TIP WIN32 source/main.cpp)

target_link_libraries(TIP
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::PrintSupport
        )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)
