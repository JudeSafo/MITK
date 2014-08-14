
macro(MITK_INSTALL_PYTHON _python_libs _python_dirs)

  set(_destination bin)
  if(APPLE)
    set(_destination MitkWorkbench.app/Contents/MacOS)
  endif()

  if(UNIX)
    # apple and linux only supports .so as loadable extension
    set(PYTHON_LIB_SUFFIX .so)
  else(WIN32)
    # windows only supports pyd as loadable extension
    set(PYTHON_LIB_SUFFIX .pyd)
  endif()

  # SimpleITK
  if(MITK_USE_SimpleITK)
    install(FILES "${SimpleITK_DIR}/Wrapping/SimpleITK.py"
                  DESTINATION ${_destination}/Python/SimpleITK )
    install(FILES "${SimpleITK_DIR}/Wrapping/__init__.py"
                  DESTINATION ${_destination}/Python/SimpleITK )
    install(FILES "${SimpleITK_DIR}/Wrapping/_SimpleITK${PYTHON_LIB_SUFFIX}"
                  DESTINATION ${_destination}/Python/SimpleITK )
    if(UNIX AND NOT APPLE)
        install(CODE "file(RPATH_REMOVE
                    FILE \"\${CMAKE_INSTALL_PREFIX}/bin/Python/SimpleITK/_SimpleITK${PYTHON_LIB_SUFFIX}\")")
    endif()

    list(APPEND _python_libs "Python/SimpleITK/_SimpleITK${PYTHON_LIB_SUFFIX}")
    list(APPEND _python_dirs "${SimpleITK_DIR}/lib")
  endif()

  # install OpenCV python wrapping
  if(MITK_USE_OpenCV)
    list(APPEND _python_libs "cv2${PYTHON_LIB_SUFFIX}")

    if(UNIX)
      install(FILES "${OpenCV_DIR}/lib/cv2${PYTHON_LIB_SUFFIX}" DESTINATION ${_destination})
    else()
      install(FILES "${OpenCV_DIR}/lib/Release/cv2${PYTHON_LIB_SUFFIX}" DESTINATION ${_destination})
    endif()

    if(UNIX AND NOT APPLE)
      install(CODE "file(RPATH_REMOVE
                         FILE \"\${CMAKE_INSTALL_PREFIX}/bin/cv2${CMAKE_SHARED_LIBRARY_SUFFIX}\")")
    endif()

    list(APPEND _python_dirs "${OpenCV_DIR}/lib")
  endif()

  # install VTK python wrapping
  find_package(VTK REQUIRED)

  set(_VTK_PYTHON_TARGETS )

  # find all vtk python wrapped targets
  foreach(_lib ${VTK_LIBRARIES})
    # exclude system libs
    if(${_lib} MATCHES "^vtk.+")
      # use only python wrapped modules ( targets end with PythonD )
      if(TARGET ${_lib}PythonD)
        list(APPEND _VTK_PYTHON_TARGETS ${_lib}Python)
      endif()
    endif()
  endforeach()

  # install the python modules and loaders
  foreach(_target ${_VTK_PYTHON_TARGETS})
    # get the properties of the python wrapped target
    if( CMAKE_BUILD_TYPE STREQUAL "Debug")
      get_target_property(_target_lib   "${_target}D" IMPORTED_LOCATION_DEBUG)
    else()
      get_target_property(_target_lib "${_target}D" IMPORTED_LOCATION_RELEASE)
    endif()
    get_filename_component(_filepath "${_target_lib}" PATH)

    install(FILES "${_filepath}/${_target}${PYTHON_LIB_SUFFIX}" DESTINATION ${_destination})

    if(UNIX AND NOT APPLE )
      install(CODE "file(RPATH_REMOVE
                    FILE \"\${CMAKE_INSTALL_PREFIX}/bin/${_target}${PYTHON_LIB_SUFFIX}\")")
    endif()
    list(APPEND _python_libs "${_target}${PYTHON_LIB_SUFFIX}")
  endforeach()

  # install vtk python. This folder contains all *.py files for VTK module loading.
  # glob through all files, NSIS can't use directories
  file(GLOB_RECURSE item RELATIVE "${VTK_DIR}/Wrapping/Python/vtk" "${VTK_DIR}/Wrapping/Python/vtk/*.py")
  foreach(f ${item})
    get_filename_component(_filepath "${f}" PATH)
    install(FILES "${VTK_DIR}/Wrapping/Python/vtk/${f}" DESTINATION ${_destination}/Python/vtk/${_filepath})
  endforeach()

  list(APPEND _python_dirs "${VTK_DIR}/lib")

  # install the python runtime from the superbuild
  if(NOT MITK_USE_SYSTEM_PYTHON)
    if(UNIX)
      set(_python_runtime_dir lib/python${PYTHON_MAJOR_VERSION}.${PYTHON_MINOR_VERSION})
      list(APPEND _python_dirs "${Python_DIR}/lib")
    else() #WIN32
      set(_python_runtime_dir Lib)
      list(APPEND _python_dirs "${Python_DIR}/libs")
      list(APPEND _python_dirs "${Python_DIR}/bin")
    endif()
      # install python stuff
      #install(DIRECTORY "${Python_DIR}/lib/python${PYTHON_MAJOR_VERSION}.${PYTHON_MINOR_VERSION}"
      #      DESTINATION ${_destination}/Python/lib
      #      USE_SOURCE_PERMISSIONS
      #      COMPONENT Runtime)

    file(GLOB_RECURSE item RELATIVE "${Python_DIR}/${_python_runtime_dir}" "${Python_DIR}/${_python_runtime_dir}/*")
    foreach(f ${item})
      get_filename_component(_filepath "${f}" PATH)
      install(FILES "${Python_DIR}/${_python_runtime_dir}/${f}" DESTINATION ${_destination}/Python/${_python_runtime_dir}/${_filepath})
    endforeach()

    file(GLOB_RECURSE item RELATIVE "${Python_DIR}/include" "${Python_DIR}/include/*")
    foreach(f ${item})
      get_filename_component(_filepath "${f}" PATH)
      install(FILES "${Python_DIR}/include/${f}" DESTINATION ${_destination}/Python/include/${_filepath})
    endforeach()
  endif()

  if(Numpy_DIR)
    # glob through all files, NSIS can't use directories
    file(GLOB_RECURSE item RELATIVE "${Numpy_DIR}/numpy" "${Numpy_DIR}/numpy/*")
    foreach(f ${item})
      get_filename_component(_filepath "${f}" PATH)
      install(FILES "${Numpy_DIR}/numpy/${f}" DESTINATION ${_destination}/Python/numpy/${_filepath})
    endforeach()
  endif()

  list(REMOVE_DUPLICATES _python_dirs)

endmacro()

