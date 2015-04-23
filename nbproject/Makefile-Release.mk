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
	${OBJECTDIR}/Arma.o \
	${OBJECTDIR}/ArmaFactory.o \
	${OBJECTDIR}/Granada.o \
	${OBJECTDIR}/HUD.o \
	${OBJECTDIR}/MapLoader.o \
	${OBJECTDIR}/Nivel.o \
	${OBJECTDIR}/Oleada.o \
	${OBJECTDIR}/Personaje.o \
	${OBJECTDIR}/PersonajeFactory.o \
	${OBJECTDIR}/Protagonista.o \
	${OBJECTDIR}/Proyectil.o \
	${OBJECTDIR}/Recurso.o \
	${OBJECTDIR}/RecursoHUD.o \
	${OBJECTDIR}/RecursosFactory.o \
	${OBJECTDIR}/lib/tinyxml/tinystr.o \
	${OBJECTDIR}/lib/tinyxml/tinyxml.o \
	${OBJECTDIR}/lib/tinyxml/tinyxmlerror.o \
	${OBJECTDIR}/lib/tinyxml/tinyxmlparser.o \
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
LDLIBSOPTIONS=-L../SFML-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -lsfml-network

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fight_or_die.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fight_or_die.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fight_or_die ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Arma.o: Arma.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Arma.o Arma.cpp

${OBJECTDIR}/ArmaFactory.o: ArmaFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArmaFactory.o ArmaFactory.cpp

${OBJECTDIR}/Granada.o: Granada.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Granada.o Granada.cpp

${OBJECTDIR}/HUD.o: HUD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HUD.o HUD.cpp

${OBJECTDIR}/MapLoader.o: MapLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MapLoader.o MapLoader.cpp

${OBJECTDIR}/Nivel.o: Nivel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Nivel.o Nivel.cpp

${OBJECTDIR}/Oleada.o: Oleada.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Oleada.o Oleada.cpp

${OBJECTDIR}/Personaje.o: Personaje.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Personaje.o Personaje.cpp

${OBJECTDIR}/PersonajeFactory.o: PersonajeFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PersonajeFactory.o PersonajeFactory.cpp

${OBJECTDIR}/Protagonista.o: Protagonista.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Protagonista.o Protagonista.cpp

${OBJECTDIR}/Proyectil.o: Proyectil.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Proyectil.o Proyectil.cpp

${OBJECTDIR}/Recurso.o: Recurso.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Recurso.o Recurso.cpp

${OBJECTDIR}/RecursoHUD.o: RecursoHUD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RecursoHUD.o RecursoHUD.cpp

${OBJECTDIR}/RecursosFactory.o: RecursosFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RecursosFactory.o RecursosFactory.cpp

${OBJECTDIR}/lib/tinyxml/tinystr.o: lib/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/tinyxml/tinystr.o lib/tinyxml/tinystr.cpp

${OBJECTDIR}/lib/tinyxml/tinyxml.o: lib/tinyxml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/tinyxml/tinyxml.o lib/tinyxml/tinyxml.cpp

${OBJECTDIR}/lib/tinyxml/tinyxmlerror.o: lib/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/tinyxml/tinyxmlerror.o lib/tinyxml/tinyxmlerror.cpp

${OBJECTDIR}/lib/tinyxml/tinyxmlparser.o: lib/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/tinyxml/tinyxmlparser.o lib/tinyxml/tinyxmlparser.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
