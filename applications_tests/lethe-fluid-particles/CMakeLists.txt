set(TEST_TARGET lethe-fluid-particles)

string(TOLOWER ${CMAKE_BUILD_TYPE} _build_type)

file(COPY particle_sedimentation_files/dem.particles DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/particle_sedimentation.${_build_type}")
file(COPY particle_sedimentation_files/dem.pvdhandler DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/particle_sedimentation.${_build_type}")
file(COPY particle_sedimentation_files/dem.simulationcontrol DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/particle_sedimentation.${_build_type}")
file(COPY particle_sedimentation_files/dem.triangulation DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/particle_sedimentation.${_build_type}")
file(COPY particle_sedimentation_files/dem.triangulation.info DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/particle_sedimentation.${_build_type}")
file(COPY particle_sedimentation_files/dem.triangulation_fixed.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/particle_sedimentation.${_build_type}")
file(COPY particle_sedimentation_files/dem.triangulation_variable.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/particle_sedimentation.${_build_type}")

file(COPY restart_particle_sedimentation_files/dem.particles DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/dem.pvdhandler DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/dem.simulationcontrol DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/dem.triangulation DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/dem.triangulation.info DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/dem.triangulation_fixed.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/dem.triangulation_variable.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case.particles DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case.pvdhandler DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case_particles.pvdhandler DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case.simulationcontrol DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case.triangulation DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case.triangulation.info DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case.triangulation_fixed.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")
file(COPY restart_particle_sedimentation_files/case.triangulation_variable.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/restart_particle_sedimentation.${_build_type}")

file(COPY dynamic_contact_search_files/dem.particles DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/dynamic_contact_search.${_build_type}")
file(COPY dynamic_contact_search_files/dem.pvdhandler DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/dynamic_contact_search.${_build_type}")
file(COPY dynamic_contact_search_files/dem.simulationcontrol DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/dynamic_contact_search.${_build_type}")
file(COPY dynamic_contact_search_files/dem.triangulation DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/dynamic_contact_search.${_build_type}")
file(COPY dynamic_contact_search_files/dem.triangulation.info DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/dynamic_contact_search.${_build_type}")
file(COPY dynamic_contact_search_files/dem.triangulation_fixed.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/dynamic_contact_search.${_build_type}")
file(COPY dynamic_contact_search_files/dem.triangulation_variable.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/dynamic_contact_search.${_build_type}")

file(COPY liquid_fluidized_bed_files/dem.particles DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/liquid_fluidized_bed.${_build_type}")
file(COPY liquid_fluidized_bed_files/dem.pvdhandler DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/liquid_fluidized_bed.${_build_type}")
file(COPY liquid_fluidized_bed_files/dem.simulationcontrol DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/liquid_fluidized_bed.${_build_type}")
file(COPY liquid_fluidized_bed_files/dem.triangulation DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/liquid_fluidized_bed.${_build_type}")
file(COPY liquid_fluidized_bed_files/dem.triangulation.info DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/liquid_fluidized_bed.${_build_type}")
file(COPY liquid_fluidized_bed_files/dem.triangulation_fixed.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/liquid_fluidized_bed.${_build_type}")
file(COPY liquid_fluidized_bed_files/dem.triangulation_variable.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/liquid_fluidized_bed.${_build_type}")

file(COPY periodic_particles_qcm_files/dem.particles DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/periodic_particles_qcm.${_build_type}")
file(COPY periodic_particles_qcm_files/dem.pvdhandler DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/periodic_particles_qcm.${_build_type}")
file(COPY periodic_particles_qcm_files/dem.simulationcontrol DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/periodic_particles_qcm.${_build_type}")
file(COPY periodic_particles_qcm_files/dem.triangulation DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/periodic_particles_qcm.${_build_type}")
file(COPY periodic_particles_qcm_files/dem.triangulation.info DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/periodic_particles_qcm.${_build_type}")
file(COPY periodic_particles_qcm_files/dem.triangulation_fixed.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/periodic_particles_qcm.${_build_type}")
file(COPY periodic_particles_qcm_files/dem.triangulation_variable.data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/periodic_particles_qcm.${_build_type}")

deal_ii_pickup_tests()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set_tests_properties(lethe-fluid-particles/particle_sedimentation.debug PROPERTIES TIMEOUT 1200)
  set_tests_properties(lethe-fluid-particles/restart_particle_sedimentation.debug PROPERTIES TIMEOUT 1200)
  set_tests_properties(lethe-fluid-particles/dynamic_contact_search.debug PROPERTIES TIMEOUT 1200)
  set_tests_properties(lethe-fluid-particles/liquid_fluidized_bed.debug PROPERTIES TIMEOUT 2400)
endif()
