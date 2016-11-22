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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/3ce853ac/Buff.o \
	${OBJECTDIR}/_ext/3ce853ac/BuffInstance.o \
	${OBJECTDIR}/_ext/3ce853ac/Camera.o \
	${OBJECTDIR}/_ext/3ce853ac/Entity.o \
	${OBJECTDIR}/_ext/3ce853ac/FrameBuffer.o \
	${OBJECTDIR}/_ext/3ce853ac/FrameBuffer_Scan.o \
	${OBJECTDIR}/_ext/3ce853ac/GUI.o \
	${OBJECTDIR}/_ext/3ce853ac/GUI_Bar.o \
	${OBJECTDIR}/_ext/3ce853ac/GUI_Button.o \
	${OBJECTDIR}/_ext/3ce853ac/GUI_DynamicBar.o \
	${OBJECTDIR}/_ext/3ce853ac/GUI_DynamicLabel.o \
	${OBJECTDIR}/_ext/3ce853ac/GUI_Label.o \
	${OBJECTDIR}/_ext/3ce853ac/GUI_OrderPanel.o \
	${OBJECTDIR}/_ext/3ce853ac/Game.o \
	${OBJECTDIR}/_ext/3ce853ac/GameEngine.o \
	${OBJECTDIR}/_ext/3ce853ac/GameEngine_Building.o \
	${OBJECTDIR}/_ext/3ce853ac/GameEngine_Collision.o \
	${OBJECTDIR}/_ext/3ce853ac/GameEngine_Missile.o \
	${OBJECTDIR}/_ext/3ce853ac/GameEngine_Player.o \
	${OBJECTDIR}/_ext/3ce853ac/GameEngine_Unit.o \
	${OBJECTDIR}/_ext/3ce853ac/GameObject.o \
	${OBJECTDIR}/_ext/3ce853ac/GameState.o \
	${OBJECTDIR}/_ext/3ce853ac/GameStateMenu.o \
	${OBJECTDIR}/_ext/3ce853ac/GameStatePlayground.o \
	${OBJECTDIR}/_ext/3ce853ac/GameStateSTR.o \
	${OBJECTDIR}/_ext/3ce853ac/Geometry.o \
	${OBJECTDIR}/_ext/3ce853ac/GraphicEngine.o \
	${OBJECTDIR}/_ext/3ce853ac/GraphicEngine_Scan.o \
	${OBJECTDIR}/_ext/3ce853ac/HeightMapData.o \
	${OBJECTDIR}/_ext/3ce853ac/Input.o \
	${OBJECTDIR}/_ext/3ce853ac/Light.o \
	${OBJECTDIR}/_ext/3ce853ac/LightEngine.o \
	${OBJECTDIR}/_ext/3ce853ac/Missile.o \
	${OBJECTDIR}/_ext/3ce853ac/Model.o \
	${OBJECTDIR}/_ext/3ce853ac/ModelHeightMap.o \
	${OBJECTDIR}/_ext/3ce853ac/ModelObj.o \
	${OBJECTDIR}/_ext/3ce853ac/ParticleEngine.o \
	${OBJECTDIR}/_ext/3ce853ac/Settings.o \
	${OBJECTDIR}/_ext/3ce853ac/Shader.o \
	${OBJECTDIR}/_ext/3ce853ac/Spell.o \
	${OBJECTDIR}/_ext/3ce853ac/SpellInstance.o \
	${OBJECTDIR}/_ext/3ce853ac/String.o \
	${OBJECTDIR}/_ext/3ce853ac/TextEngine.o \
	${OBJECTDIR}/_ext/3ce853ac/Texture.o \
	${OBJECTDIR}/_ext/3ce853ac/Time.o \
	${OBJECTDIR}/_ext/3ce853ac/Triggerable.o \
	${OBJECTDIR}/_ext/3ce853ac/TriggerableInstance.o \
	${OBJECTDIR}/_ext/3ce853ac/Unit.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/MinGW/SDL-2.0/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/koronah_engine.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/koronah_engine.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/koronah_engine ${OBJECTFILES} ${LDLIBSOPTIONS} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglew32 -lfreetype

${OBJECTDIR}/_ext/3ce853ac/Buff.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Buff.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Buff.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Buff.cpp

${OBJECTDIR}/_ext/3ce853ac/BuffInstance.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/BuffInstance.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/BuffInstance.o /C/Users/ANTOINE/Projets/Koronah\ Engine/BuffInstance.cpp

${OBJECTDIR}/_ext/3ce853ac/Camera.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Camera.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Camera.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Camera.cpp

${OBJECTDIR}/_ext/3ce853ac/Entity.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Entity.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Entity.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Entity.cpp

${OBJECTDIR}/_ext/3ce853ac/FrameBuffer.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/FrameBuffer.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/FrameBuffer.o /C/Users/ANTOINE/Projets/Koronah\ Engine/FrameBuffer.cpp

${OBJECTDIR}/_ext/3ce853ac/FrameBuffer_Scan.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/FrameBuffer_Scan.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/FrameBuffer_Scan.o /C/Users/ANTOINE/Projets/Koronah\ Engine/FrameBuffer_Scan.cpp

${OBJECTDIR}/_ext/3ce853ac/GUI.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GUI.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI.cpp

${OBJECTDIR}/_ext/3ce853ac/GUI_Bar.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Bar.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GUI_Bar.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Bar.cpp

${OBJECTDIR}/_ext/3ce853ac/GUI_Button.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Button.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GUI_Button.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Button.cpp

${OBJECTDIR}/_ext/3ce853ac/GUI_DynamicBar.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_DynamicBar.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GUI_DynamicBar.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_DynamicBar.cpp

${OBJECTDIR}/_ext/3ce853ac/GUI_DynamicLabel.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_DynamicLabel.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GUI_DynamicLabel.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_DynamicLabel.cpp

${OBJECTDIR}/_ext/3ce853ac/GUI_Label.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Label.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GUI_Label.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Label.cpp

${OBJECTDIR}/_ext/3ce853ac/GUI_OrderPanel.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_OrderPanel.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GUI_OrderPanel.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_OrderPanel.cpp

${OBJECTDIR}/_ext/3ce853ac/Game.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Game.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Game.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Game.cpp

${OBJECTDIR}/_ext/3ce853ac/GameEngine.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine.cpp

${OBJECTDIR}/_ext/3ce853ac/GameEngine_Building.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Building.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameEngine_Building.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Building.cpp

${OBJECTDIR}/_ext/3ce853ac/GameEngine_Collision.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Collision.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameEngine_Collision.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Collision.cpp

${OBJECTDIR}/_ext/3ce853ac/GameEngine_Missile.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Missile.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameEngine_Missile.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Missile.cpp

${OBJECTDIR}/_ext/3ce853ac/GameEngine_Player.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Player.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameEngine_Player.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Player.cpp

${OBJECTDIR}/_ext/3ce853ac/GameEngine_Unit.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Unit.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameEngine_Unit.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameEngine_Unit.cpp

${OBJECTDIR}/_ext/3ce853ac/GameObject.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameObject.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameObject.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameObject.cpp

${OBJECTDIR}/_ext/3ce853ac/GameState.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameState.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameState.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameState.cpp

${OBJECTDIR}/_ext/3ce853ac/GameStateMenu.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStateMenu.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameStateMenu.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStateMenu.cpp

${OBJECTDIR}/_ext/3ce853ac/GameStatePlayground.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStatePlayground.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameStatePlayground.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStatePlayground.cpp

${OBJECTDIR}/_ext/3ce853ac/GameStateSTR.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStateSTR.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GameStateSTR.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStateSTR.cpp

${OBJECTDIR}/_ext/3ce853ac/Geometry.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Geometry.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Geometry.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Geometry.cpp

${OBJECTDIR}/_ext/3ce853ac/GraphicEngine.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GraphicEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GraphicEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GraphicEngine.cpp

${OBJECTDIR}/_ext/3ce853ac/GraphicEngine_Scan.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/GraphicEngine_Scan.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/GraphicEngine_Scan.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GraphicEngine_Scan.cpp

${OBJECTDIR}/_ext/3ce853ac/HeightMapData.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/HeightMapData.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/HeightMapData.o /C/Users/ANTOINE/Projets/Koronah\ Engine/HeightMapData.cpp

${OBJECTDIR}/_ext/3ce853ac/Input.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Input.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Input.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Input.cpp

${OBJECTDIR}/_ext/3ce853ac/Light.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Light.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Light.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Light.cpp

${OBJECTDIR}/_ext/3ce853ac/LightEngine.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/LightEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/LightEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/LightEngine.cpp

${OBJECTDIR}/_ext/3ce853ac/Missile.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Missile.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Missile.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Missile.cpp

${OBJECTDIR}/_ext/3ce853ac/Model.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Model.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Model.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Model.cpp

${OBJECTDIR}/_ext/3ce853ac/ModelHeightMap.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelHeightMap.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/ModelHeightMap.o /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelHeightMap.cpp

${OBJECTDIR}/_ext/3ce853ac/ModelObj.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelObj.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/ModelObj.o /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelObj.cpp

${OBJECTDIR}/_ext/3ce853ac/ParticleEngine.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/ParticleEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/ParticleEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/ParticleEngine.cpp

${OBJECTDIR}/_ext/3ce853ac/Settings.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Settings.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Settings.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Settings.cpp

${OBJECTDIR}/_ext/3ce853ac/Shader.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Shader.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Shader.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Shader.cpp

${OBJECTDIR}/_ext/3ce853ac/Spell.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Spell.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Spell.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Spell.cpp

${OBJECTDIR}/_ext/3ce853ac/SpellInstance.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/SpellInstance.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/SpellInstance.o /C/Users/ANTOINE/Projets/Koronah\ Engine/SpellInstance.cpp

${OBJECTDIR}/_ext/3ce853ac/String.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/String.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/String.o /C/Users/ANTOINE/Projets/Koronah\ Engine/String.cpp

${OBJECTDIR}/_ext/3ce853ac/TextEngine.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/TextEngine.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/TextEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/TextEngine.cpp

${OBJECTDIR}/_ext/3ce853ac/Texture.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Texture.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Texture.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Texture.cpp

${OBJECTDIR}/_ext/3ce853ac/Time.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Time.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Time.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Time.cpp

${OBJECTDIR}/_ext/3ce853ac/Triggerable.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Triggerable.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Triggerable.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Triggerable.cpp

${OBJECTDIR}/_ext/3ce853ac/TriggerableInstance.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/TriggerableInstance.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/TriggerableInstance.o /C/Users/ANTOINE/Projets/Koronah\ Engine/TriggerableInstance.cpp

${OBJECTDIR}/_ext/3ce853ac/Unit.o: /C/Users/ANTOINE/Projets/Koronah\ Engine/Unit.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/3ce853ac
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ce853ac/Unit.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Unit.cpp

${OBJECTDIR}/main.o: main.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
