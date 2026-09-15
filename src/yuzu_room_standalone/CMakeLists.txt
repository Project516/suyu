# SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
# SPDX-License-Identifier: GPL-3.0-or-later

add_executable(yuzu_room_standalone yuzu_room_standalone.cpp)

set_target_properties(yuzu_room_standalone PROPERTIES OUTPUT_NAME "suyu-room")

target_link_libraries(yuzu_room_standalone PRIVATE yuzu-room)
# OpenSSL's static libcrypto needs zlib symbols (compress/uncompress).
# Conan's static libcrypto requires zlib to be linked *after* crypto.
# Use LINK_GROUP to force correct order regardless of left-to-right pass,
# and fall back to plain -lz for systems where ZLIB target is missing.
find_package(ZLIB QUIET)
if (TARGET ZLIB::ZLIB)
    target_link_libraries(yuzu_room_standalone PRIVATE "$<LINK_GROUP:RESCAN,OpenSSL::SSL,OpenSSL::Crypto,ZLIB::ZLIB>" ZLIB::ZLIB)
elseif (TARGET zlibstatic)
    target_link_libraries(yuzu_room_standalone PRIVATE "$<LINK_GROUP:RESCAN,OpenSSL::SSL,OpenSSL::Crypto,zlibstatic>" zlibstatic)
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
