set(SRC "HowToUse/main.cpp" "HowToUse/Adapter.cpp" "HowToUse/3rdParty.cpp")

add_executable(FastPIMPL ${SRC})
target_link_libraries(FastPIMPL ${LIBS})
