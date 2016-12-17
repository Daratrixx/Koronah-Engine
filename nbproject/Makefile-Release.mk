#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Buff.o \
	${OBJECTDIR}/src/BuffInstance.o \
	${OBJECTDIR}/src/Camera.o \
	${OBJECTDIR}/src/Entity.o \
	${OBJECTDIR}/src/FrameBuffer.o \
	${OBJECTDIR}/src/FrameBuffer_Scan.o \
	${OBJECTDIR}/src/GUI.o \
	${OBJECTDIR}/src/GUI_Bar.o \
	${OBJECTDIR}/src/GUI_Button.o \
	${OBJECTDIR}/src/GUI_DynamicBar.o \
	${OBJECTDIR}/src/GUI_DynamicLabel.o \
	${OBJECTDIR}/src/GUI_Label.o \
	${OBJECTDIR}/src/GUI_OrderPanel.o \
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/GameEngine.o \
	${OBJECTDIR}/src/GameEngine_Building.o \
	${OBJECTDIR}/src/GameEngine_Collision.o \
	${OBJECTDIR}/src/GameEngine_Missile.o \
	${OBJECTDIR}/src/GameEngine_Player.o \
	${OBJECTDIR}/src/GameEngine_Unit.o \
	${OBJECTDIR}/src/GameObject.o \
	${OBJECTDIR}/src/GameState.o \
	${OBJECTDIR}/src/GameStateMenu.o \
	${OBJECTDIR}/src/GameStatePlayground.o \
	${OBJECTDIR}/src/GameStateSTR.o \
	${OBJECTDIR}/src/Geometry.o \
	${OBJECTDIR}/src/GraphicEngine.o \
	${OBJECTDIR}/src/GraphicEngine_Pass.o \
	${OBJECTDIR}/src/GraphicEngine_Render.o \
	${OBJECTDIR}/src/GraphicEngine_Scan.o \
	${OBJECTDIR}/src/HeightMapData.o \
	${OBJECTDIR}/src/Input.o \
	${OBJECTDIR}/src/Light.o \
	${OBJECTDIR}/src/LightEngine.o \
	${OBJECTDIR}/src/Missile.o \
	${OBJECTDIR}/src/Model.o \
	${OBJECTDIR}/src/ModelHeightMap.o \
	${OBJECTDIR}/src/ModelObj.o \
	${OBJECTDIR}/src/ParticleEngine.o \
	${OBJECTDIR}/src/Settings.o \
	${OBJECTDIR}/src/Shader.o \
	${OBJECTDIR}/src/Spell.o \
	${OBJECTDIR}/src/SpellInstance.o \
	${OBJECTDIR}/src/String.o \
	${OBJECTDIR}/src/TextEngine.o \
	${OBJECTDIR}/src/Texture.o \
	${OBJECTDIR}/src/Time.o \
	${OBJECTDIR}/src/Triggerable.o \
	${OBJECTDIR}/src/TriggerableInstance.o \
	${OBJECTDIR}/src/Unit.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglew32
CXXFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglew32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/koronah_engine.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/koronah_engine.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/koronah_engine ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Buff.o: src/Buff.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Buff.o src/Buff.cpp

${OBJECTDIR}/src/BuffInstance.o: src/BuffInstance.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/BuffInstance.o src/BuffInstance.cpp

${OBJECTDIR}/src/Camera.o: src/Camera.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Camera.o src/Camera.cpp

${OBJECTDIR}/src/Entity.o: src/Entity.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Entity.o src/Entity.cpp

${OBJECTDIR}/src/FrameBuffer.o: src/FrameBuffer.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FrameBuffer.o src/FrameBuffer.cpp

${OBJECTDIR}/src/FrameBuffer_Scan.o: src/FrameBuffer_Scan.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/FrameBuffer_Scan.o src/FrameBuffer_Scan.cpp

${OBJECTDIR}/src/GUI.o: src/GUI.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GUI.o src/GUI.cpp

${OBJECTDIR}/src/GUI_Bar.o: src/GUI_Bar.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GUI_Bar.o src/GUI_Bar.cpp

${OBJECTDIR}/src/GUI_Button.o: src/GUI_Button.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GUI_Button.o src/GUI_Button.cpp

${OBJECTDIR}/src/GUI_DynamicBar.o: src/GUI_DynamicBar.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GUI_DynamicBar.o src/GUI_DynamicBar.cpp

${OBJECTDIR}/src/GUI_DynamicLabel.o: src/GUI_DynamicLabel.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GUI_DynamicLabel.o src/GUI_DynamicLabel.cpp

${OBJECTDIR}/src/GUI_Label.o: src/GUI_Label.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GUI_Label.o src/GUI_Label.cpp

${OBJECTDIR}/src/GUI_OrderPanel.o: src/GUI_OrderPanel.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GUI_OrderPanel.o src/GUI_OrderPanel.cpp

${OBJECTDIR}/src/Game.o: src/Game.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/GameEngine.o: src/GameEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameEngine.o src/GameEngine.cpp

${OBJECTDIR}/src/GameEngine_Building.o: src/GameEngine_Building.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameEngine_Building.o src/GameEngine_Building.cpp

${OBJECTDIR}/src/GameEngine_Collision.o: src/GameEngine_Collision.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameEngine_Collision.o src/GameEngine_Collision.cpp

${OBJECTDIR}/src/GameEngine_Missile.o: src/GameEngine_Missile.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameEngine_Missile.o src/GameEngine_Missile.cpp

${OBJECTDIR}/src/GameEngine_Player.o: src/GameEngine_Player.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameEngine_Player.o src/GameEngine_Player.cpp

${OBJECTDIR}/src/GameEngine_Unit.o: src/GameEngine_Unit.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameEngine_Unit.o src/GameEngine_Unit.cpp

${OBJECTDIR}/src/GameObject.o: src/GameObject.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameObject.o src/GameObject.cpp

${OBJECTDIR}/src/GameState.o: src/GameState.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameState.o src/GameState.cpp

${OBJECTDIR}/src/GameStateMenu.o: src/GameStateMenu.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameStateMenu.o src/GameStateMenu.cpp

${OBJECTDIR}/src/GameStatePlayground.o: src/GameStatePlayground.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameStatePlayground.o src/GameStatePlayground.cpp

${OBJECTDIR}/src/GameStateSTR.o: src/GameStateSTR.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameStateSTR.o src/GameStateSTR.cpp

${OBJECTDIR}/src/Geometry.o: src/Geometry.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Geometry.o src/Geometry.cpp

${OBJECTDIR}/src/GraphicEngine.o: src/GraphicEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GraphicEngine.o src/GraphicEngine.cpp

${OBJECTDIR}/src/GraphicEngine_Pass.o: src/GraphicEngine_Pass.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GraphicEngine_Pass.o src/GraphicEngine_Pass.cpp

${OBJECTDIR}/src/GraphicEngine_Render.o: src/GraphicEngine_Render.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GraphicEngine_Render.o src/GraphicEngine_Render.cpp

${OBJECTDIR}/src/GraphicEngine_Scan.o: src/GraphicEngine_Scan.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GraphicEngine_Scan.o src/GraphicEngine_Scan.cpp

${OBJECTDIR}/src/HeightMapData.o: src/HeightMapData.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/HeightMapData.o src/HeightMapData.cpp

${OBJECTDIR}/src/Input.o: src/Input.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Input.o src/Input.cpp

${OBJECTDIR}/src/Light.o: src/Light.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Light.o src/Light.cpp

${OBJECTDIR}/src/LightEngine.o: src/LightEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LightEngine.o src/LightEngine.cpp

${OBJECTDIR}/src/Missile.o: src/Missile.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Missile.o src/Missile.cpp

${OBJECTDIR}/src/Model.o: src/Model.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Model.o src/Model.cpp

${OBJECTDIR}/src/ModelHeightMap.o: src/ModelHeightMap.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ModelHeightMap.o src/ModelHeightMap.cpp

${OBJECTDIR}/src/ModelObj.o: src/ModelObj.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ModelObj.o src/ModelObj.cpp

${OBJECTDIR}/src/ParticleEngine.o: src/ParticleEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ParticleEngine.o src/ParticleEngine.cpp

${OBJECTDIR}/src/Settings.o: src/Settings.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Settings.o src/Settings.cpp

${OBJECTDIR}/src/Shader.o: src/Shader.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Shader.o src/Shader.cpp

${OBJECTDIR}/src/Spell.o: src/Spell.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Spell.o src/Spell.cpp

${OBJECTDIR}/src/SpellInstance.o: src/SpellInstance.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SpellInstance.o src/SpellInstance.cpp

${OBJECTDIR}/src/String.o: src/String.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/String.o src/String.cpp

${OBJECTDIR}/src/TextEngine.o: src/TextEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TextEngine.o src/TextEngine.cpp

${OBJECTDIR}/src/Texture.o: src/Texture.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Texture.o src/Texture.cpp

${OBJECTDIR}/src/Time.o: src/Time.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Time.o src/Time.cpp

${OBJECTDIR}/src/Triggerable.o: src/Triggerable.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Triggerable.o src/Triggerable.cpp

${OBJECTDIR}/src/TriggerableInstance.o: src/TriggerableInstance.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TriggerableInstance.o src/TriggerableInstance.cpp

${OBJECTDIR}/src/Unit.o: src/Unit.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Unit.o src/Unit.cpp

${OBJECTDIR}/src/main.o: src/main.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
