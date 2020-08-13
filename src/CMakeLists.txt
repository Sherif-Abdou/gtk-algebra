find_package(PkgConfig REQUIRED)
pkg_search_module(PKG_GTK REQUIRED gtkmm-3.0)

include_directories(${PKG_GTK_INCLUDE_DIRS})

add_executable(gtk_algebra main.cpp HelloWorld.cpp HelloWorld.h)
target_link_libraries(gtk_algebra ${PKG_GTK_LDFLAGS})
