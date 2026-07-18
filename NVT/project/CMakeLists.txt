include("C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(SQLiteCpp CONFIG REQUIRED)

add_library(projectlib STATIC
	"project.hpp"
	"project.cpp"
)

set_target_properties(projectlib PROPERTIES CXX_STANDARD 23)
target_link_libraries(projectlib PUBLIC SQLiteCpp)
