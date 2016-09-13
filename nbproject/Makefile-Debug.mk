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
	${OBJECTDIR}/_ext/1021858732/Camera.o \
	${OBJECTDIR}/_ext/1021858732/Entity.o \
	${OBJECTDIR}/_ext/1021858732/FrameBuffer.o \
	${OBJECTDIR}/_ext/1021858732/GUI.o \
	${OBJECTDIR}/_ext/1021858732/GUI_Button.o \
	${OBJECTDIR}/_ext/1021858732/GUI_DynamicLabel.o \
	${OBJECTDIR}/_ext/1021858732/GUI_Label.o \
	${OBJECTDIR}/_ext/1021858732/Game.o \
	${OBJECTDIR}/_ext/1021858732/GameObject.o \
	${OBJECTDIR}/_ext/1021858732/GameState.o \
	${OBJECTDIR}/_ext/1021858732/GameStateMenu.o \
	${OBJECTDIR}/_ext/1021858732/GameStatePlayground.o \
	${OBJECTDIR}/_ext/1021858732/Geometry.o \
	${OBJECTDIR}/_ext/1021858732/GraphicEngine.o \
	${OBJECTDIR}/_ext/1021858732/HeightMapData.o \
	${OBJECTDIR}/_ext/1021858732/Input.o \
	${OBJECTDIR}/_ext/1021858732/Light.o \
	${OBJECTDIR}/_ext/1021858732/LightEngine.o \
	${OBJECTDIR}/_ext/1021858732/Model.o \
	${OBJECTDIR}/_ext/1021858732/ModelHeightMap.o \
	${OBJECTDIR}/_ext/1021858732/ModelObj.o \
	${OBJECTDIR}/_ext/1021858732/ParticleEngine.o \
	${OBJECTDIR}/_ext/1021858732/Shader.o \
	${OBJECTDIR}/_ext/1021858732/String.o \
	${OBJECTDIR}/_ext/1021858732/TextEngine.o \
	${OBJECTDIR}/_ext/1021858732/Texture.o \
	${OBJECTDIR}/_ext/1021858732/Time.o \
	${OBJECTDIR}/_ext/1021858732/Unit.o \
	${OBJECTDIR}/_ext/1021858732/Window.o \
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

${OBJECTDIR}/_ext/1021858732/Camera.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Camera.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Camera.cpp

${OBJECTDIR}/_ext/1021858732/Entity.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Entity.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Entity.cpp

${OBJECTDIR}/_ext/1021858732/FrameBuffer.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/FrameBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/FrameBuffer.o /C/Users/ANTOINE/Projets/Koronah\ Engine/FrameBuffer.cpp

${OBJECTDIR}/_ext/1021858732/GUI.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GUI.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI.cpp

${OBJECTDIR}/_ext/1021858732/GUI_Button.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Button.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GUI_Button.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Button.cpp

${OBJECTDIR}/_ext/1021858732/GUI_DynamicLabel.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_DynamicLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GUI_DynamicLabel.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_DynamicLabel.cpp

${OBJECTDIR}/_ext/1021858732/GUI_Label.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Label.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GUI_Label.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GUI_Label.cpp

${OBJECTDIR}/_ext/1021858732/Game.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Game.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Game.cpp

${OBJECTDIR}/_ext/1021858732/GameObject.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GameObject.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameObject.cpp

${OBJECTDIR}/_ext/1021858732/GameState.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GameState.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameState.cpp

${OBJECTDIR}/_ext/1021858732/GameStateMenu.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStateMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GameStateMenu.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStateMenu.cpp

${OBJECTDIR}/_ext/1021858732/GameStatePlayground.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStatePlayground.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GameStatePlayground.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GameStatePlayground.cpp

${OBJECTDIR}/_ext/1021858732/Geometry.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Geometry.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Geometry.cpp

${OBJECTDIR}/_ext/1021858732/GraphicEngine.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/GraphicEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/GraphicEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/GraphicEngine.cpp

${OBJECTDIR}/_ext/1021858732/HeightMapData.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/HeightMapData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/HeightMapData.o /C/Users/ANTOINE/Projets/Koronah\ Engine/HeightMapData.cpp

${OBJECTDIR}/_ext/1021858732/Input.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Input.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Input.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Input.cpp

${OBJECTDIR}/_ext/1021858732/Light.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Light.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Light.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Light.cpp

${OBJECTDIR}/_ext/1021858732/LightEngine.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/LightEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/LightEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/LightEngine.cpp

${OBJECTDIR}/_ext/1021858732/Model.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Model.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Model.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Model.cpp

${OBJECTDIR}/_ext/1021858732/ModelHeightMap.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelHeightMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/ModelHeightMap.o /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelHeightMap.cpp

${OBJECTDIR}/_ext/1021858732/ModelObj.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/ModelObj.o /C/Users/ANTOINE/Projets/Koronah\ Engine/ModelObj.cpp

${OBJECTDIR}/_ext/1021858732/ParticleEngine.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/ParticleEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/ParticleEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/ParticleEngine.cpp

${OBJECTDIR}/_ext/1021858732/Shader.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Shader.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Shader.cpp

${OBJECTDIR}/_ext/1021858732/String.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/String.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/String.o /C/Users/ANTOINE/Projets/Koronah\ Engine/String.cpp

${OBJECTDIR}/_ext/1021858732/TextEngine.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/TextEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/TextEngine.o /C/Users/ANTOINE/Projets/Koronah\ Engine/TextEngine.cpp

${OBJECTDIR}/_ext/1021858732/Texture.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Texture.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Texture.cpp

${OBJECTDIR}/_ext/1021858732/Time.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Time.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Time.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Time.cpp

${OBJECTDIR}/_ext/1021858732/Unit.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Unit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Unit.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Unit.cpp

${OBJECTDIR}/_ext/1021858732/Window.o: nbproject/Makefile-${CND_CONF}.mk /C/Users/ANTOINE/Projets/Koronah\ Engine/Window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1021858732
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1021858732/Window.o /C/Users/ANTOINE/Projets/Koronah\ Engine/Window.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I/C/MinGW/include -I/C/MinGW/SDL-2.0/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/koronah_engine.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
