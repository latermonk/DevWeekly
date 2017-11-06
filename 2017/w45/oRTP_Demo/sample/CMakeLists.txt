cmake_minimum_required(VERSION 3.8)
project (rtp)
include_directories(/home/www/src/ortp-0.25.0/include)
link_directories(/home/www/src/ortp-0.25.0/src/.libs)
add_library(debug ortp)


ADD_DEFINITIONS(
-g
)

add_executable(rtpsend rtpsend.c)
add_executable(rtprecv rtprecv.c)

target_link_libraries(ortp)
