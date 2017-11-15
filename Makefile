RELEASE_DIR = /tmp/viewer
ARCHIVE_DIR = .

release: Release.mk
	mkdir -p Release
	${MAKE} -f Release.mk $(args)
	
debug: Debug.mk
	mkdir -p Debug
	${MAKE} -f Debug.mk $(args)

clean:
	@rm -rf Release
	@rm -rf Debug
	
	@rm -f moc*.cpp
	
	@cd bin/ && rm -f exercise*-solution.txt
	
	${MAKE} clean -f Debug.mk $(args)
	${MAKE} clean -f Release.mk $(args)
	
	@cd exercises/exercise1 && ${MAKE} clean $(args)
	@cd exercises/exercise2 && ${MAKE} clean $(args)
	@cd exercises/exercise3 && ${MAKE} clean $(args)
	@cd exercises/exercises4-5 && ${MAKE} clean $(args)
	
	@cd demos/convex_hull_2 && ${MAKE} clean $(args)
	@cd demos/example && ${MAKE} clean $(args)
	@cd demos/polygon && ${MAKE} clean $(args)
	@cd demos/make_grid/make-grid && ${MAKE} clean $(args)
	@cd demos/make_grid/v1-triangulation && ${MAKE} clean $(args)
	@cd demos/make_grid/v2-alpha-shape && ${MAKE} clean $(args)
	@cd demos/make_grid/v3-boundary-components && ${MAKE} clean $(args)
	
distclean:
	${MAKE} distclean -f Debug.mk $(args)
	${MAKE} distclean -f Release.mk $(args)
	
	@rm -f Debug.mk
	@rm -f Release.mk
	@rm -rf Release
	@rm -rf Debug
	@rm -f moc*.cpp
	
	cd bin/ && rm -f exercise*-solution.txt
	
	@cd exercises/exercise1 && ${MAKE} distclean $(args)
	@cd exercises/exercise2 && ${MAKE} distclean $(args)
	@cd exercises/exercise3 && ${MAKE} distclean $(args)
	@cd exercises/exercises4-5 && ${MAKE} distclean $(args)
	
	@cd demos/convex_hull_2 && ${MAKE} distclean $(args)
	@cd demos/example && ${MAKE} distclean $(args)
	@cd demos/polygon && ${MAKE} distclean $(args)
	@cd demos/make_grid/make-grid && ${MAKE} distclean $(args)
	@cd demos/make_grid/v1-triangulation && ${MAKE} distclean $(args)
	@cd demos/make_grid/v2-alpha-shape && ${MAKE} distclean $(args)
	@cd demos/make_grid/v3-boundary-components && ${MAKE} distclean $(args)
	
export:
	@cd ..; tar cfj viewer-dist.tar.bz2 --exclude-vcs --exclude="*.o" \
		docs/* \
		manual/* \
		uml/* \
		viewer/demos/* \
		viewer/exercises/* \
		viewer/*pro \
		viewer/Makefile \
		viewer/*.sh \
		viewer/*.bat \
		viewer/src/* \
		viewer/bin/tests/*

archive:
	rm -f viewer.tar.bz2
	
	rm -rf $(RELEASE_DIR)
	mkdir $(RELEASE_DIR)
	
	cp -r ../docs/docs $(RELEASE_DIR)
	
	mkdir $(RELEASE_DIR)/manual
	cp ../manual/manual.pdf $(RELEASE_DIR)/manual
	cp ../manual/windows_install.pdf $(RELEASE_DIR)/manual
	
	mkdir $(RELEASE_DIR)/uml
	cp ../uml/framework.png $(RELEASE_DIR)/uml
	
	mkdir -p $(RELEASE_DIR)/viewer/bin
	cp -r bin/tests $(RELEASE_DIR)/viewer/bin
	cp -r bin/input $(RELEASE_DIR)/viewer/bin
	cp -r bin/debug $(RELEASE_DIR)/viewer/bin
	cp -r bin/grind $(RELEASE_DIR)/viewer/bin
	cp -r bin/run $(RELEASE_DIR)/viewer/bin
	
	cd CGAL-3.8; make clean
	rm -f CGAL-3.8/CMakeCache.txt
	cp -r CGAL-3.8 $(RELEASE_DIR)/viewer
	cp -r demos $(RELEASE_DIR)/viewer
	cp -r exercises $(RELEASE_DIR)/viewer
	cp -r src $(RELEASE_DIR)/viewer
	
	cp *.pro $(RELEASE_DIR)/viewer/
	cp *.sh $(RELEASE_DIR)/viewer/
	cp *.bat $(RELEASE_DIR)/viewer/
	cp Makefile $(RELEASE_DIR)/viewer/
	
	cd /tmp; tar jcf viewer.tar.bz2 --exclude-vcs --exclude="*.o" viewer/
	mv /tmp/viewer.tar.bz2 $(ARCHIVE_DIR)
	rm -rf $(RELEASE_DIR)
	