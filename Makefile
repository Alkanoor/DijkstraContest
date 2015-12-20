PERFORM_GRAPHICAL = performGraphical
PERFORM_TIMED = performTimed
GRAPHICAL_EXE = drawShortest
TIMER_EXE = timeShortest

RELEASE_DIR = bin
TEST_DIR = results


all :
	@(cd $(PERFORM_GRAPHICAL) && $(MAKE))
	@(cd $(PERFORM_TIMED) && $(MAKE))
	@mkdir -p $(RELEASE_DIR)
	@cp -a $(PERFORM_GRAPHICAL)/$(RELEASE_DIR)/. $(RELEASE_DIR)
	@cp -a $(PERFORM_TIMED)/$(RELEASE_DIR)/. $(RELEASE_DIR)
	@mkdir -p $(TEST_DIR)

clean :
	@rm -rf $(RELEASE_DIR)
	@rm $(TEST_DIR)/*
	@(cd $(PERFORM_GRAPHICAL) && $(MAKE) clean)
	@(cd $(PERFORM_TIMED) && $(MAKE) clean)

run-graphical :
	./startTest.sh $(RELEASE_DIR)/$(GRAPHICAL_EXE)

run-timed :
	./startTest.sh $(RELEASE_DIR)/$(TIMER_EXE) $(TEST_DIR)

configure :
	apt-get install libsfml-dev
