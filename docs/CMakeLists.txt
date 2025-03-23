find_package(Doxygen)

if(Doxygen_FOUND AND BUILD_DOC)
    message(STATUS "Documentation generation is enabled")

    message(STATUS "Downloading CSS stylesheets for documentation...")
    file(DOWNLOAD https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/v2.3.4/doxygen-awesome.css
        ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome.css)
    file(DOWNLOAD https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/v2.3.4/doxygen-awesome-sidebar-only.css
        ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome-sidebar-only.css)
    message(STATUS "CSS stylesheets was downloaded successfully")

    add_custom_target(DocsGeneration
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/doxygen.conf
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        BYPRODUCTS ${CMAKE_BINARY_DIR}/html/index.html
    )

    add_custom_command(TARGET DocsGeneration POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Documentation successfully generated. You can preview at: ${CMAKE_BINARY_DIR}/html/index.html"
    )
elseif(NOT BUILD_DOC)
    message(STATUS "Documentation build is disabled (BUILD_DOC=OFF)")
else()
    message(STATUS "Documentation build is disabled or Doxygen not found")
endif()