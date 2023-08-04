ALL = 

clean:
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} clean); \
	done

cleaner:
	-rm -f *~
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} cleaner); \
	done
