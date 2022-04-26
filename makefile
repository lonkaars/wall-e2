SUBDIRS := client robot

all clean format compile_commands: $(SUBDIRS) FORCE

$(SUBDIRS): FORCE
	$(MAKE) -C $@ $(MAKECMDGOALS)

FORCE: