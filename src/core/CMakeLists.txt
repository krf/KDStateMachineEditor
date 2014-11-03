set(LIB_SRCS
  export/abstractexporter.cpp
  export/qmlexporter.cpp
  export/scxmlexporter.cpp

  model/element.cpp
  model/elementfactory.cpp
  model/elementmodel.cpp
  model/elementutil.cpp
  import/scxmlparser.cpp

  util/objecthelper.cpp
  util/objecttreemodel.cpp
  util/settings.cpp
)

add_definitions(${GRAPHVIZ_COMPILE_FLAGS})
add_library(kdstatemachineeditor_core SHARED ${LIB_SRCS})
add_library(KDSME::Core ALIAS kdstatemachineeditor_core)
target_link_libraries(kdstatemachineeditor_core
  LINK_PRIVATE
  LINK_PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
)
set_target_properties(kdstatemachineeditor_core PROPERTIES SOVERSION ${KDSME_SOVERSION} VERSION ${KDSME_SOVERSION} EXPORT_NAME Core)
generate_export_header(kdstatemachineeditor_core EXPORT_FILE_NAME kdsme_core_export.h BASE_NAME KDSME_CORE)

set(build_iface_dirs
  ${CMAKE_CURRENT_SOURCE_DIR}/common
  ${CMAKE_CURRENT_SOURCE_DIR}/import
  ${CMAKE_CURRENT_SOURCE_DIR}/model
  ${CMAKE_CURRENT_SOURCE_DIR}/util
)
target_include_directories(kdstatemachineeditor_core
  PUBLIC
    "$<BUILD_INTERFACE:${build_iface_dirs}>"
    # FIXME: It is recommended to use a relative path here.
    # Doesn't work with CMake 2.8.11, though, probably needs 2.8.12(?)
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
  PRIVATE
    "${Qt5Qml_PRIVATE_INCLUDE_DIRS}" # qqmlcustomparser_p.h
    ${LIB_EXTRA_INCLUDES}
)

add_custom_command(TARGET kdstatemachineeditor_core POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/data" "${PROJECT_BINARY_DIR}/${XDG_DATA_INSTALL_DIR}/data"
)

install(TARGETS kdstatemachineeditor_core EXPORT KDSME_TARGETS ${INSTALL_TARGETS_DEFAULT_ARGS})
install(DIRECTORY data/ DESTINATION ${XDG_DATA_INSTALL_DIR}/data)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kdsme_core_export.h

  export/abstractexporter.h
  export/qmlexporter.h
  export/scxmlexporter.h
  model/element.h
  model/elementmodel.h
  model/elementutil.h
  util/objecttreemodel.h
  util/ringbuffer.h
  util/treewalker.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/core
)

add_subdirectory(tests)
