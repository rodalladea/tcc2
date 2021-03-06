if(BUILD_TBB)
  add_subdirectory("${OpenCV_SOURCE_DIR}/3rdparty/tbb")
  include_directories(SYSTEM ${TBB_INCLUDE_DIRS})
  set(OPENCV_LINKER_LIBS ${OPENCV_LINKER_LIBS} tbb)
  add_definitions(-DTBB_USE_GCC_BUILTINS=1 -D__TBB_GCC_BUILTIN_ATOMICS_PRESENT=1)
  if(tbb_need_GENERIC_DWORD_LOAD_STORE)
    add_definitions(-D__TBB_USE_GENERIC_DWORD_LOAD_STORE=1)
  endif()
  set(HAVE_TBB 1)
elseif(UNIX AND NOT APPLE)
  PKG_CHECK_MODULES(TBB tbb)

  if(TBB_FOUND)
    set(HAVE_TBB 1)
    if(NOT ${TBB_INCLUDE_DIRS} STREQUAL "")
      ocv_include_directories(${TBB_INCLUDE_DIRS})
    endif()
    link_directories(${TBB_LIBRARY_DIRS})
    set(OPENCV_LINKER_LIBS ${OPENCV_LINKER_LIBS} ${TBB_LIBRARIES})
  endif()
endif()

if(NOT HAVE_TBB)
  set(TBB_DEFAULT_INCLUDE_DIRS
    "/opt/intel/tbb/include" "/usr/local/include" "/usr/include"
    "C:/Program Files/Intel/TBB" "C:/Program Files (x86)/Intel/TBB"
    "C:/Program Files (x86)/tbb/include"
    "C:/Program Files (x86)/tbb/include"
    "${CMAKE_INSTALL_PREFIX}/include")

  find_path(TBB_INCLUDE_DIRS "tbb/tbb.h" PATHS ${TBB_INCLUDE_DIR} ${TBB_DEFAULT_INCLUDE_DIRS} DOC "The path to TBB headers")
  if(TBB_INCLUDE_DIRS)
    if(UNIX)
      set(TBB_LIB_DIR "${TBB_INCLUDE_DIRS}/../lib" CACHE PATH "Full path of TBB library directory")
      link_directories("${TBB_LIB_DIR}")
    endif()
    if(APPLE)
      set(OPENCV_LINKER_LIBS ${OPENCV_LINKER_LIBS} libtbb.dylib)
    elseif(ANDROID)
      set(OPENCV_LINKER_LIBS ${OPENCV_LINKER_LIBS}  tbb)
      add_definitions(-DTBB_USE_GCC_BUILTINS)
    elseif (UNIX)
      set(OPENCV_LINKER_LIBS ${OPENCV_LINKER_LIBS} tbb)
    elseif (WIN32)
      if(CMAKE_COMPILER_IS_GNUCXX)
        set(TBB_LIB_DIR "${TBB_INCLUDE_DIRS}/../lib" CACHE PATH "Full path of TBB library directory")
        link_directories("${TBB_LIB_DIR}")
        set(OPENCV_LINKER_LIBS ${OPENCV_LINKER_LIBS} tbb)
      else()
        get_filename_component(_TBB_LIB_PATH "${TBB_INCLUDE_DIRS}/../lib" ABSOLUTE)

        if(CMAKE_SYSTEM_PROCESSOR MATCHES amd64*|x86_64* OR MSVC64)
          set(_TBB_LIB_PATH "${_TBB_LIB_PATH}/intel64")
        else()
          set(_TBB_LIB_PATH "${_TBB_LIB_PATH}/ia32")
        endif()

        if(MSVC80)
          set(_TBB_LIB_PATH "${_TBB_LIB_PATH}/vc8")
        elseif(MSVC90)
          set(_TBB_LIB_PATH "${_TBB_LIB_PATH}/vc9")
        elseif(MSVC10)
          set(_TBB_LIB_PATH "${_TBB_LIB_PATH}/vc10")
        elseif(MSVC11)
          set(_TBB_LIB_PATH "${_TBB_LIB_PATH}/vc11")
        endif()
        set(TBB_LIB_DIR "${_TBB_LIB_PATH}" CACHE PATH "Full path of TBB library directory")
        link_directories("${TBB_LIB_DIR}")
      endif()
    endif()

    set(HAVE_TBB 1)
    if(NOT "${TBB_INCLUDE_DIRS}" STREQUAL "")
      ocv_include_directories("${TBB_INCLUDE_DIRS}")
    endif()
  endif(TBB_INCLUDE_DIRS)
endif(NOT HAVE_TBB)

# get TBB version
if(HAVE_TBB)
  find_file(TBB_STDDEF_PATH tbb/tbb_stddef.h "${TBB_INCLUDE_DIRS}")
  mark_as_advanced(TBB _STDDEF_PATH)
endif()
if(HAVE_TBB AND TBB_STDDEF_PATH)
  ocv_parse_header("${TBB_STDDEF_PATH}" TBB_VERSION_LINES TBB_VERSION_MAJOR TBB_VERSION_MINOR TBB_INTERFACE_VERSION)
else()
  unset(TBB_VERSION_MAJOR)
  unset(TBB_VERSION_MINOR)
  unset(TBB_INTERFACE_VERSION)
endif()
