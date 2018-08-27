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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/WeightedTreeNode.o \
	${OBJECTDIR}/dataPoint.o \
	${OBJECTDIR}/heapp.o \
	${OBJECTDIR}/pqueue.o \
	${OBJECTDIR}/unionFind.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/pqueue_Test.o \
	${TESTDIR}/tests/unionFindtest.o

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdatastructures.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdatastructures.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdatastructures.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdatastructures.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdatastructures.a

${OBJECTDIR}/WeightedTreeNode.o: WeightedTreeNode.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WeightedTreeNode.o WeightedTreeNode.cpp

${OBJECTDIR}/dataPoint.o: dataPoint.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dataPoint.o dataPoint.cpp

${OBJECTDIR}/heapp.o: heapp.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/heapp.o heapp.cpp

${OBJECTDIR}/pqueue.o: pqueue.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pqueue.o pqueue.cpp

${OBJECTDIR}/unionFind.o: unionFind.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/unionFind.o unionFind.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/pqueue_Test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/unionFindtest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/pqueue_Test.o: tests/pqueue_Test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Graph -I. -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/pqueue_Test.o tests/pqueue_Test.cpp


${TESTDIR}/tests/unionFindtest.o: tests/unionFindtest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Graph -I. -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/unionFindtest.o tests/unionFindtest.cpp


${OBJECTDIR}/WeightedTreeNode_nomain.o: ${OBJECTDIR}/WeightedTreeNode.o WeightedTreeNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/WeightedTreeNode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WeightedTreeNode_nomain.o WeightedTreeNode.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/WeightedTreeNode.o ${OBJECTDIR}/WeightedTreeNode_nomain.o;\
	fi

${OBJECTDIR}/dataPoint_nomain.o: ${OBJECTDIR}/dataPoint.o dataPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/dataPoint.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dataPoint_nomain.o dataPoint.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/dataPoint.o ${OBJECTDIR}/dataPoint_nomain.o;\
	fi

${OBJECTDIR}/heapp_nomain.o: ${OBJECTDIR}/heapp.o heapp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/heapp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/heapp_nomain.o heapp.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/heapp.o ${OBJECTDIR}/heapp_nomain.o;\
	fi

${OBJECTDIR}/pqueue_nomain.o: ${OBJECTDIR}/pqueue.o pqueue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pqueue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pqueue_nomain.o pqueue.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/pqueue.o ${OBJECTDIR}/pqueue_nomain.o;\
	fi

${OBJECTDIR}/unionFind_nomain.o: ${OBJECTDIR}/unionFind.o unionFind.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/unionFind.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../Graph -include ../Graph/PrimEdge.h -include ../Graph/PrimNode.h -include ../Graph/UndirectedWeightedGraph.h -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/unionFind_nomain.o unionFind.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/unionFind.o ${OBJECTDIR}/unionFind_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
