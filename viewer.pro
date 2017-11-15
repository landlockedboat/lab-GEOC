GEOC_BOOST_PATH	= $$[GEOC_BOOST_PATH]
GEOC_CGAL_PATH	= $$[GEOC_CGAL_PATH]


contains (CONFIG, debug) {
	CONFIG			+= debug
	OBJECTS_DIR		= ./Debug
	DEFINES			= _GEOC_DEBUG
	
	unix|macx {
		MAKEFILE	= Debug.mk
	}
}
else {
	CONFIG			+= release
	OBJECTS_DIR		= ./Release
	
	unix|macx {
		MAKEFILE	= Release.mk
	}
}


DESTDIR        = bin
TEMPLATE       = lib
CONFIG         += qt dll lex yacc uic resources warn_on precompile_header designer plugin
TARGET         = geoc


INCLUDEPATH += src
DEPENDPATH += src

!isEmpty (GEOC_BOOST_PATH) {
	INCLUDEPATH	+= "$${GEOC_BOOST_PATH}"
	DEPENDPATH	+= "$${GEOC_BOOST_PATH}"
}

!isEmpty (GEOC_CGAL_PATH) {
	INCLUDEPATH	+= "$${GEOC_CGAL_PATH}"/include
	DEPENDPATH	+= "$${GEOC_CGAL_PATH}"/include
}
else {
	INCLUDEPATH	+= CGAL-3.8/include
	DEPENDPATH	+= CGAL-3.8/include
}


unix|macx {
	QMAKE_CXXFLAGS_RELEASE	= -O2 -frounding-math
	QMAKE_CXXFLAGS_DEBUG	+= -g
	
	LIBS					+= -lGLU
	
	PRECOMPILED_HEADER		= \
							src/geoc/math/Vector.h \
                            src/geoc/higher_order_cpp.h \
							src/geoc/geoc.h
							
	QMAKE_CLEAN				+= bin/*.so*
}
else {
	DEFINES					+= WIN32 _SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS DLL_EXPORT
	QMAKE_CXXFLAGS_RELEASE	= /O2
	QMAKE_CXXFLAGS			= /EHsc /W1 /wd4251 /wd4305 /wd4244 /wd4244 /wd4100
	QMAKE_CLEAN				+= bin/*.dll
	
	!isEmpty (GEOC_BOOST_PATH) {
		LIBS	+= -L"$${GEOC_BOOST_PATH}/lib"
	}
	
	!isEmpty (GEOC_CGAL_PATH) {
		LIBS	+= -L"$${GEOC_CGAL_PATH}"/lib
	}
	else {
		LIBS	+= -L/CGAL-3.8/lib
	}
}


SOURCES     = \
             src/geoc/scene/cmd/Command.cc\
             src/geoc/scene/SceneManager.cc\
             src/geoc/scene/Point.cc\
             src/geoc/scene/LineSegmentEnt.cc\
             src/geoc/scene/CircleEnt.cc\
             src/geoc/scene/TriangleEnt.cc\
             src/geoc/scene/TriangulationEnt_helper.cc\
             src/geoc/scene/TriangulationEnt.cc\
             src/geoc/app/camera_control/CamCtrlState3D.cc\
             src/geoc/app/camera_control/CamCtrlContext.cc\
             src/geoc/app/camera_control/CamCtrlState2D.cc\
             src/geoc/app/GeocApplication.cc\
             src/geoc/app/GeocWidget.cc\
             src/geoc/app/input_translation.cc\
             src/geoc/app/designer.cc\
             src/geoc/io/input/Mouse.cc\
             src/geoc/io/input/Input.cc\
             src/geoc/io/loader/ObjectLoader.cc\
             src/geoc/io/loader/Loader.cc\
             src/geoc/io/screen/ScreenInput.cc\
             src/geoc/io/screen/CircleState.cc\
             src/geoc/io/screen/TriangleState.cc\
             src/geoc/io/screen/PointState.cc\
             src/geoc/io/screen/LineSegmentState.cc\
             src/geoc/io/output/FileOutput.cc\
             src/geoc/io/output/ScrollList.cc\
             src/geoc/io/output/OutputSystem.cc\
             src/geoc/io/output/ConsoleOutput.cc\
             src/geoc/io/Subject.cc\
             src/geoc/io/aux_functions.cc\
             src/geoc/io/File_utils.cc\
             src/geoc/io/Timer.cc\
             src/geoc/geometry/Triangle.cc\
             src/geoc/geometry/LineSegment.cc\
             src/geoc/geometry/Circle.cc\
             src/geoc/geometry/LineSegment_utils.cc\
             src/geoc/geometry/Triangle_utils.cc\
             src/geoc/geometry/Circle_utils.cc\
             src/geoc/geometry/Triangulation.cc\
             src/geoc/geometry/CgalTriangulation.cc\
             src/geoc/math/Vector.cc\
             src/geoc/math/Math.cc\
             src/geoc/math/Math_inline.cc\
             src/geoc/math/BoundingBox.cc\
             src/geoc/math/Orientation.cc\
             src/geoc/math/Spatial.cc\
             src/geoc/math/Vector_impl.cc\
             src/geoc/camera/Camera.cc\
             src/geoc/gfx/Graphics.cc\
             src/geoc/gfx/Font.cc\
             src/geoc/GeocException.cc\
             src/geoc/cgal/Vector_iterators.cc\
    src/geoc/math/Quaternion.cc

HEADERS     = \
             src/geoc/scene/cmd/Command.h\
             src/geoc/scene/SceneManager.h\
             src/geoc/scene/Entity.h\
             src/geoc/scene/Point.h\
             src/geoc/scene/LineSegmentEnt.h\
             src/geoc/scene/CircleEnt.h\
             src/geoc/scene/TriangleEnt.h\
             src/geoc/scene/TriangulationEnt.h\
             src/geoc/app/camera_control/CamCtrlState2D.h\
             src/geoc/app/camera_control/CamCtrlContext.h\
             src/geoc/app/camera_control/CamCtrlState.h\
             src/geoc/app/camera_control/CamCtrlState3D.h\
             src/geoc/app/update_requests.h\
             src/geoc/app/GeocApplication.h\
             src/geoc/app/GeocWidget.h\
             src/geoc/app/input_translation.h\
             src/geoc/app/designer.h\
             src/geoc/io/input/Mouse.h\
             src/geoc/io/input/Keyboard.h\
             src/geoc/io/input/Input.h\
             src/geoc/io/loader/ObjectLoader.h\
             src/geoc/io/loader/Loader.h\
             src/geoc/io/screen/IdleState.h\
             src/geoc/io/screen/ScreenState.h\
             src/geoc/io/screen/LineSegmentState.h\
             src/geoc/io/screen/CircleState.h\
             src/geoc/io/screen/TriangleState.h\
             src/geoc/io/screen/PointState.h\
             src/geoc/io/screen/IScreenState.h\
             src/geoc/io/screen/ScreenInput.h\
             src/geoc/io/output/FileOutput.h\
             src/geoc/io/output/ConsoleOutput.h\
             src/geoc/io/output/OutputSystem.h\
             src/geoc/io/output/OutputStream.h\
             src/geoc/io/output/ScrollList.h\
             src/geoc/io/Observer.h\
             src/geoc/io/Subject.h\
             src/geoc/io/aux_functions.h\
             src/geoc/io/File_utils.h\
             src/geoc/io/Timer.h\
             src/geoc/geometry/LineSegment.h\
             src/geoc/geometry/Circle.h\
             src/geoc/geometry/Triangle.h\
             src/geoc/geometry/Triangulation.h\
             src/geoc/geometry/CgalTriangulation.h\
             src/geoc/geometry/TriangulationBase.h\
             src/geoc/math/BoundingBox.h\
             src/geoc/math/Math.h\
             src/geoc/math/Vector_fwd_decl.h\
             src/geoc/math/Spatial.h\
             src/geoc/camera/Camera.h\
             src/geoc/gfx/Graphics.h\
             src/geoc/gfx/Font.h\
             src/geoc/gfx/alphabet.h\
             src/geoc/GeocException.h\
             src/geoc/algorithms.h\
             src/geoc/gl.h\
             src/geoc/glu.h\
             src/geoc/cgal/Kernel.h\
             src/geoc/cgal/Constructors.hpp\
             src/geoc/cgal/Vector_iterators.h\
    src/geoc/math/Quaternion.h
			 
win32 {
	HEADERS += \
			src/geoc/geoc.h \
			src/geoc/math/Vector.h \
            src/geoc/higher_order_cpp.h
}

FORMS       = \

YACCSOURCES = \

LEXSOURCES  = \

RESOURCES   = \

QT += opengl
