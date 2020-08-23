find_package(PkgConfig REQUIRED)
pkg_search_module(PKG_GTK REQUIRED gtkmm-3.0)

include_directories(${PKG_GTK_INCLUDE_DIRS})

add_executable(gtk_algebra main.cpp HelloWorld.cpp HelloWorld.h ui/TopBox.cpp ui/TopBox.h interfaces/TopBoxDelegate.cpp interfaces/TopBoxDelegate.h)
target_link_libraries(gtk_algebra gtk_algebra_lib ${PKG_GTK_LDFLAGS})
