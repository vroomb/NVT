include("C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(nlohmann_json CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)

add_library(projectlib SHARED
	"project.hpp"
	"project.cpp"
)

set_target_properties(projectlib PROPERTIES CXX_STANDARD 23)
target_link_libraries(projectlib
PUBLIC
	SQLiteCpp
	nlohmann_json::nlohmann_json
)
