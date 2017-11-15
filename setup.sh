#!/bin/bash
ROOT=`/bin/pwd`
EXERCISES_DIR=$ROOT/exercises
DEMOS_DIR=$ROOT/demos
CGAL_DIR=$ROOT/CGAL-3.8
MAKE_ARGS=$1


function barf {
	echo "Oops! Errors encountered."
	exit 1
}


function build {
	for proj in `ls $1`
	do
		cd $1/$proj
		qmake >/dev/null || continue
		make $MAKE_ARGS || barf
	done
}


echo "Setting up geoc viewer installation"

#echo "Compiling CGAL"
cd $CGAL_DIR
cmake .
make $1

echo "Generating Makefiles for the viewer library"
cd $ROOT
qmake CONFIG=debug
qmake CONFIG=release

echo "Making initial library build (release mode)"
make $MAKE_ARGS

echo "Compiling exercises"
build $EXERCISES_DIR

echo "Compiling demos"
build $DEMOS_DIR

echo "Compiling additional demos"
build $DEMOS_DIR/make_grid

cd $ROOT
echo "All done."
