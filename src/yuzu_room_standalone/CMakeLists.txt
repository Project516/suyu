# SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
# SPDX-License-Identifier: GPL-3.0-or-later

add_executable(yuzu_room_standalone yuzu_room_standalone.cpp)

set_target_properties(yuzu_room_standalone PROPERTIES OUTPUT_NAME "suyu-room")

target_link_libraries(yuzu_room_standalone PRIVATE yuzu-room)
# OpenSSL's static libcrypto needs zlib symbols (compress/uncompress).
# Conan's static libcrypto requires zlib to be linked *after* crypto, so
# keep ZLIB last in left-to-right order. Do NOT use $<LINK_GROUP:RESCAN>
# here: it is unsupported by the MSVC and Apple linkers and fails CMake
# generation on Windows/macOS.
find_package(ZLIB QUIET)
if (TARGET ZLIB::ZLIB)
    target_link_libraries(yuzu_room_standalone PRIVATE OpenSSL::SSL OpenSSL::Crypto ZLIB::ZLIB)
elseif (TARGET zlibstatic)
    target_link_libraries(yuzu_room_standalone PRIVATE OpenSSL::SSL OpenSSL::Crypto zlibstatic)
else()
    target_link_libraries(yuzu_room_standalone PRIVATE z)
endif()

if(UNIX AND NOT APPLE)
    install(TARGETS yuzu_room_standalone RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()

if (YUZU_STATIC_ROOM)
    target_link_options(yuzu_room_standalone PRIVATE "-static")
endif()

create_target_directory_groups(yuzu_room_standalone)
