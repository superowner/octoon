INCLUDE_DIRECTORIES(${OCTOON_LIBRARY_OUTPUT_PATH})

IF(NOT OCTOON_BUILD_PLATFORM_EMSCRIPTEN)
    ADD_SUBDIRECTORY(glew)
    ADD_SUBDIRECTORY(glfw)
ENDIF()
ADD_SUBDIRECTORY(zlib)
ADD_SUBDIRECTORY(imgui)
ADD_SUBDIRECTORY(ImGuizmo)
ADD_SUBDIRECTORY(DirectX)
ADD_SUBDIRECTORY(HLSLCrossCompiler)
ADD_SUBDIRECTORY(unzip)
ADD_SUBDIRECTORY(zipper)
ADD_SUBDIRECTORY(freetype-2.9)
ADD_SUBDIRECTORY(libjpeg)
ADD_SUBDIRECTORY(libpng)
ADD_SUBDIRECTORY(gles)

IF(NOT OCTOON_BUILD_PLATFORM_EMSCRIPTEN)
    SET_TARGET_ATTRIBUTE(glew "contrib")
    SET_TARGET_ATTRIBUTE(glfw "contrib")
ENDIF()
SET_TARGET_ATTRIBUTE(zlib "contrib")
SET_TARGET_ATTRIBUTE(unzip "contrib")
SET_TARGET_ATTRIBUTE(zipper "contrib")
SET_TARGET_ATTRIBUTE(imgui "contrib")
SET_TARGET_ATTRIBUTE(libHLSLcc "contrib")
SET_TARGET_ATTRIBUTE(ImGuizmo "contrib")
SET_TARGET_ATTRIBUTE(libHLSLcc "contrib")
SET_TARGET_ATTRIBUTE(freetype "contrib")
SET_TARGET_ATTRIBUTE(dist "contrib")
SET_TARGET_ATTRIBUTE(libjpeg "contrib")
SET_TARGET_ATTRIBUTE(libpng "contrib")

IF(OCTOON_BUILD_PLATFORM_EMSCRIPTEN)
	ADD_SUBDIRECTORY(iGLU-1.0.0)
	SET_TARGET_ATTRIBUTE(iGLU "contrib")
ENDIF()