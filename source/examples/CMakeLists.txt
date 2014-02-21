
if(OPTION_BUILD_EXAMPLES)
	if(WIN32)
		install(FILES ${GLEW_INCLUDE_DIR}/../bin/glew32.dll DESTINATION ${INSTALL_BIN})
	endif()

	set(EXAMPLE_COMMON examplecommon)
	
	add_subdirectory("common")
	include_directories("common")

	add_subdirectory("camerapath")
	add_subdirectory("commandlineoutput")
	add_subdirectory("computeshader")
	add_subdirectory("gpu-particles")
	add_subdirectory("glraw-texture")
	add_subdirectory("multiple-contexts")
	add_subdirectory("mipmap-filtering")
	add_subdirectory("navigations")
	#add_subdirectory("deferred-lighting")
	add_subdirectory("post-processing")
	add_subdirectory("states")
	add_subdirectory("simple-texture")
	add_subdirectory("simple-transformfeedback")
	add_subdirectory("single-context")
	add_subdirectory("shaderincludes")
	add_subdirectory("ssbo")
	add_subdirectory("tessellation")
	add_subdirectory("vertexarrayattributes")
	add_subdirectory("wikiexample")
	add_subdirectory("transparency")
endif()