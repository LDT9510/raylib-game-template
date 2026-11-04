#[[ Prints a message with a custom formatting. ]]
function(announce message)
    message("=========================================================")
    message("${message}")
    message("=========================================================")
endfunction()

#[[ Same as set(${name} ${value} CACHE BOOL "" FORCE). ]]
macro(force_bool name value)
    set(${name} ${value} CACHE BOOL "" FORCE)
endmacro()

#[[ Same as set(${name} ${value} CACHE STRING "" FORCE). ]]
macro(force_string name value)
    set(${name} ${value} CACHE STRING "" FORCE)
endmacro()

#[[ Copies the compile_commands.json file to the source root, if it exists.]]
function(copy_compilation_database)
    if(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
        file(COPY_FILE
            "${CMAKE_BINARY_DIR}/compile_commands.json"
            "${CMAKE_SOURCE_DIR}/compile_commands.json" ONLY_IF_DIFFERENT)
    endif()
endfunction()
