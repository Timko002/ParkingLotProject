# ParkingLotProject

CS542 Parking Lot Project

Built with wxWidgets and VS2019

Daniel | Torsha | Mandar

This project requires a MYSQL server installed to run the project so it must be run on release/x64. The current wxWidets version we used is fully included in the project files

Step 1 create tables and inserts from the db create statements included with the project files

Step 2 In project properties in C/C++ -> General add the following files to your additional include directories for wxwidgets and mysql
	2.1 MySQL\Connector C++ 8.0\include\include 
	2.2 MySQL\MySQL Server 8.0\include
	2.3 ParkingLotProject\include
	2.4 ParkingLotProject\include\msvc

Step 3 include mysql and wxWidgets library directories in Linker -> Additional Library Directories.
	3.1 MySQL\Connector C++ 8.0\lib64\vs14
	3.2 MySQL\MySQL Server 8.0\lib
	3.3 ParkingLotProject\lib\vc142_x64_dll
Step 4 Preprocessor definitions set for the project under C/C++ -> Preprocessor
	4.1 WXUSINGDLL
	4.2 wxMSVC_VERSION_AUTO
	4.3 _CRT_SECURE_NO_WARNINGS
Step 5 Additional Dependencies in Linker -> Input were set
	5.1 mysqlcppconn.lib
	5.2 libmysql.lib