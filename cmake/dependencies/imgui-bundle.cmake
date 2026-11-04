include("Utils")

function(configure_external_imgui_bundle target)
    set(IMGUI_BUNDLE_LIB_NAME "imgui-bundle")

    add_external_subdirectory(${IMGUI_BUNDLE_LIB_NAME})
    # link to main target
    target_link_libraries(${target} PRIVATE imgui-bundle)

    copy_thirdparty_includes(${IMGUI_BUNDLE_LIB_NAME} "dcimgui.h")
endfunction()
