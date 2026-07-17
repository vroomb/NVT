find_package(SQLiteCpp CONFIG REQUIRED)

add_library(projectlib
	"project.hpp"
	"project.cpp"
)

set_target_properties(projectlib PROPERTIES CXX_STANDARD 23)
target_link_libraries(projectlib PRIVATE SQLiteCpp)
