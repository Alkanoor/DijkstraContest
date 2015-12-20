PERFORM_GRAPHICAL = performGraphical
PERFORM_TIMED = performTimed
GRAPHICAL_EXE = drawShortest
TIMER_EXE = timeShortest

SUBFOLDERS_MAKE = $(PERFORM_GRAPHICAL).make $(PERFORM_TIMED).make julienS.make
SUBFOLDERS_MAKE_CLEAN = $(PERFORM_GRAPHICAL).make_clean $(PERFORM_TIMED).make_clean julienS.make_clean

RELEASE_DIR = bin
TEST_DIR = results


all : $(SUBFOLDERS_MAKE)
	@mkdir -p $(TEST_DIR)
	@mkdir -p $(RELEASE_DIR)
	@cp -a $(PERFORM_GRAPHICAL)/$(RELEASE_DIR)/. $(RELEASE_DIR)
	@cp -a $(PERFORM_TIMED)/$(RELEASE_DIR)/. $(RELEASE_DIR)

clean : $(SUBFOLDERS_MAKE_CLEAN)
	@rm -rf $(RELEASE_DIR)
	@rm -rf $(TEST_DIR)/*

%.make :
	@(cd $(basename $@ .make) && $(MAKE))

%.make_clean :
	@(cd $(basename $@ .make_clean) && $(MAKE) clean)

run-graphical :
	./startTest.sh $(RELEASE_DIR)/$(GRAPHICAL_EXE)

run-timed :
	./startTest.sh $(RELEASE_DIR)/$(TIMER_EXE) $(TEST_DIR)

run-graphical-withEnvironment :
	@printf "$$NAME\n$$ALGO_PATH\n$$SITUATION_INDEX\n" | ./startTest.sh $(RELEASE_DIR)/$(GRAPHICAL_EXE)

run-timed-withEnvironment :
	@printf "$$NAME\n$$ALGO_PATH\n$$SITUATION_INDEX\n$$DELAY\n" | ./startTest.sh $(RELEASE_DIR)/$(TIMER_EXE) $(TEST_DIR)

configure :
	apt-get install libsfml-dev
