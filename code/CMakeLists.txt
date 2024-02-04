#
# CMakeList.txt : CMake project for Compilers, include source and define project specific logic here.
#


cmake_minimum_required (VERSION 3.8)

project ("Compiler")


# Add source to this project's executable: check name and dependences
add_executable (Compiler
	"Compilers.h"	"Compilers.c"
	"Reader.h"		"Reader.c"		"MainReader.c"
	#"Scanner.h"		"Scanner.c"		"MainScanner.c"
	#"Parser.h"		"Parser.c"		"MainParser.c"
	# TO_DO: Add A22 (Scanner) and A32 (Parser)
)

set_property(TARGET Compiler PROPERTY C_STANDARD 90)

add_compile_options(-Wall -pedantic -Wno-trigraphs)
# TO_DO: Add tests and install targets if needed.
