AM_CPPFLAGS = --pedantic -Wall -O2 ${LIBXML2_CFLAGS} 
LIBS        = ${LIBXML2_LIBS}

bin_PROGRAMS = ray testmath

ray_SOURCES = src/Ray_Light.cpp src/Ray_Math.cpp src/Ray_Camera.cpp src/Ray_Image.cpp src/Ray_RenderableObject.cpp  src/Ray_Color.cpp src/Ray_Scene.cpp  src/ray.cpp

testmath_SOURCES = src/Ray_Color.cpp src/Ray_Math.cpp src/test_math.cpp

