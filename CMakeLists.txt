# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  
  ### Firelands ###
  
  #${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/Firelands/boss_alysrazar.cpp
  #${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/Firelands/boss_baloroc_the_doorkeeper.cpp
  #${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/Firelands/boss_beth'tilac.cpp
  #${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/Firelands/boss_majordomus.cpp
  #${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/Firelands/boss_ragnaros.cpp
  #${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/Firelands/boss_rhyolith.cpp
  ${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/boss_shannox.cpp
  ${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/firelands.h
  ${CMAKE_SOURCE_DIR}/../CataclysmScripts/src/Firelands/instance_firelands.cpp
)
message("  -> Prepared: Cataclysm Scripts")


