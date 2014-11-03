add_executable(test_commands test_commands.cpp)
target_link_libraries(test_commands
  ${Qt5Test_LIBRARIES}
  kdstatemachineeditor_view
)
add_test(NAME test_commands COMMAND test_commands)

# if(Graphviz_FOUND)
#   add_executable(test_layouter test_layouter.cpp)
#   target_link_libraries(test_layouter
#     Qt5::Gui
#     kdstatemachineeditor_view
#   )
#   add_test(NAME test_layouter COMMAND test_layouter)
# endif()

add_executable(test_layoutinformation test_layoutinformation.cpp)
target_link_libraries(test_layoutinformation
  Qt5::Gui
  ${Qt5Test_LIBRARIES}
  kdstatemachineeditor_view
)
add_test(NAME test_layoutinformation COMMAND test_layoutinformation)

add_executable(test_layoutitem test_layoutitem.cpp)
target_link_libraries(test_layoutitem
  ${Qt5Test_LIBRARIES}
  kdstatemachineeditor_view
)
add_test(NAME test_layoutitem COMMAND test_layoutitem)
