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
	${OBJECTDIR}/Arma.o \
	${OBJECTDIR}/ArmaFactory.o \
	${OBJECTDIR}/Granada.o \
	${OBJECTDIR}/HUD.o \
	${OBJECTDIR}/Personaje.o \
	${OBJECTDIR}/PersonajeFactory.o \
	${OBJECTDIR}/Protagonista.o \
	${OBJECTDIR}/Proyectil.o \
	${OBJECTDIR}/RecursoHUD.o \
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
LDLIBSOPTIONS=-L../SFML-2.1/lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d -lsfml-main-d -lsfml-network-d

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fight_or_die.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fight_or_die.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fight_or_die ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Arma.o: Arma.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Arma.o Arma.cpp

${OBJECTDIR}/ArmaFactory.o: ArmaFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArmaFactory.o ArmaFactory.cpp

${OBJECTDIR}/Granada.o: Granada.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Granada.o Granada.cpp

${OBJECTDIR}/HUD.o: HUD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HUD.o HUD.cpp

${OBJECTDIR}/Personaje.o: Personaje.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Personaje.o Personaje.cpp

${OBJECTDIR}/PersonajeFactory.o: PersonajeFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PersonajeFactory.o PersonajeFactory.cpp

${OBJECTDIR}/Protagonista.o: Protagonista.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Protagonista.o Protagonista.cpp

${OBJECTDIR}/Proyectil.o: Proyectil.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Proyectil.o Proyectil.cpp

${OBJECTDIR}/RecursoHUD.o: RecursoHUD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RecursoHUD.o RecursoHUD.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fight_or_die.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
