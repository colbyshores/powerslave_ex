set(ANGELSCRIPT_SOURCE
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_atomic.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_builder.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_bytecode.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc_x86.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc_x64_gcc.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc_x64_msvc.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc_x64_mingw.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_compiler.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_configgroup.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_context.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_datatype.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_gc.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_generic.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_globalproperty.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_memory.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_module.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_objecttype.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_outputbuffer.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_parser.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_restore.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptcode.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptengine.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptfunction.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptnode.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptobject.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_string.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_string_util.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_thread.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_tokenizer.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_typeinfo.cpp
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_variablescope.cpp
)

if(MSVC AND CMAKE_CL_64)
            enable_language(ASM_MASM)
            if(CMAKE_ASM_MASM_COMPILER_WORKS)
                            set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc_x64_msvc_asm.asm)
            else()
                            message(FATAL ERROR "MSVC x86_64 target requires a working assembler")
            endif()
endif()

if(ANDROID)
        enable_language(ASM)
        if(CMAKE_ASM_COMPILER_WORKS)
                set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc_arm.cpp ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc_arm_gcc.S)
        else()
                message(FATAL ERROR "Android target requires a working assembler")
        endif(CMAKE_ASM_COMPILER_WORKS)
endif()

set(ANGELSCRIPT_HEADERS
        ${PROJECT_SOURCE_DIR}/lib/angelscript/include/angelscript.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_array.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_builder.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_bytecode.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_callfunc.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_compiler.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_config.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_configgroup.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_context.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_criticalsection.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_datatype.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_debug.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_generic.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_map.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_memory.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_module.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_objecttype.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_outputbuffer.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_parser.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_property.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_restore.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptcode.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptengine.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptfunction.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptnode.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_scriptobject.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_string.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_string_util.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_texts.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_thread.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_tokendef.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_tokenizer.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_typeinfo.h
        ${PROJECT_SOURCE_DIR}/lib/angelscript/source/as_variablescope.h
)

add_definitions("-D_CRT_SECURE_NO_WARNINGS -DANGELSCRIPT_EXPORT -D_LIB")

# Fix x64 issues on Linux
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND NOT APPLE)
        add_definitions(-fPIC)
endif()

add_library(angelscript STATIC ${ANGELSCRIPT_SOURCE} ${ANGELSCRIPT_HEADERS})
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/lib/angelscript/lib)

find_package(Threads)
target_link_libraries(angelscript ${CMAKE_THREAD_LIBS_INIT})

if(MSVC)
        set_target_properties(angelscript PROPERTIES COMPILE_FLAGS "/MP")
endif(MSVC)

set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/angelscript/bin)


