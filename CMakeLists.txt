
cmake_minimum_required (VERSION 2.6)
project (Ebml)



include (TestBigEndian)
test_big_endian (BIG_ENDIAN)


configure_file (
	${PROJECT_SOURCE_DIR}/include/Ebml/Config.h.in
	${PROJECT_BINARY_DIR}/include/Ebml/Config.h)

configure_file (
	${PROJECT_SOURCE_DIR}/EbmlConfig.cmake.in
	${PROJECT_BINARY_DIR}/EbmlConfig.cmake
	@ONLY)



set (SOURCE_FILES
	src/Element.cpp
	src/FileStream.cpp
	src/Reader.cpp
	src/Stream.cpp
	src/VInt.cpp
	src/Writer.cpp)


set (HEADER_FILES
	include/Ebml/Ebml.h
	include/Ebml/Element.h
	include/Ebml/Endian.h
	include/Ebml/FileStream.h
	include/Ebml/Reader.h
	include/Ebml/Stream.h
	include/Ebml/Types.h
	include/Ebml/VInt.h
	include/Ebml/Writer.h
	${PROJECT_BINARY_DIR}/include/Ebml/Config.h)



include_directories (
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/Ebml
	${PROJECT_BINARY_DIR}/include
	${PROJECT_BINARY_DIR}/include/Ebml)



add_library (Ebml SHARED ${SOURCE_FILES} ${HEADER_FILES})


install (TARGETS Ebml EXPORT EbmlTargets DESTINATION lib)
install (EXPORT EbmlTargets DESTINATION lib/cmake/Ebml)
install (FILES ${PROJECT_BINARY_DIR}/EbmlConfig.cmake DESTINATION lib/cmake/Ebml)

install (FILES ${HEADER_FILES} DESTINATION include/Ebml)
