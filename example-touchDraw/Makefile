# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
	OF_ROOT=$(realpath ../../..)
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

ifeq ($(PLATFORM), linux64)

# libinput needs to run as root
RunRelease:
ifeq ($(PLATFORM_RUN_COMMAND),)
	@cd bin;sudo ./$(BIN_NAME)
else
	@$(PLATFORM_RUN_COMMAND)
endif

RunDebug:
ifeq ($(PLATFORM_RUN_COMMAND),)
	@cd bin;sudo ./$(BIN_NAME)
else
	@$(PLATFORM_RUN_COMMAND)
endif

endif #linux64