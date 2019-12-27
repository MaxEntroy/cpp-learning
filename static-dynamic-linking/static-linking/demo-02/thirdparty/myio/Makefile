# Makefile for installing myio

# Where to install.
INSTALL_TOP= /home/kang/workspace/myspace/git-personal/cpp-learning/static-dynamic-linking/static-linking/demo-02/thirdparty/myio
INSTALL_INC= $(INSTALL_TOP)/include/myio
INSTALL_LIB= $(INSTALL_TOP)/lib

# How to install.
INSTALL= install -p
INSTALL_EXEC= $(INSTALL) -m 755
INSTALL_DATA= $(INSTALL) -m 644

# Other utilities.
MKDIR= mkdir -p
RM= rm -f

# What to install.
TO_INC= numberio.h strio.h
TO_LIB= libmyio.a


# Targets start here.
install:
	cd src && $(MKDIR) $(INSTALL_INC) $(INSTALL_LIB)
	cd src && $(INSTALL_EXEC) $(TO_LIB) $(INSTALL_LIB)
	cd src && $(INSTALL_DATA) $(TO_INC) $(INSTALL_INC)

uninstall:
	cd src && cd $(INSTALL_LIB) && $(RM) $(TO_LIB)
	cd src && cd $(INSTALL_INC) && $(RM) $(TO_INC)

local:
	$(MAKE) install INSTALL_TOP=.

echo:
	@cd src && $(MAKE) -s echo
	@echo "INSTALL_TOP= $(INSTALL_TOP)"
	@echo "INSTALL_INC= $(INSTALL_INC)"
	@echo "INSTALL_LIB= $(INSTALL_LIB)"
	@echo "INSTALL= $(INSTALL)"
	@echo "INSTALL_EXEC= $(INSTALL_EXEC)"
	@echo "INSTALL_DATA= $(INSTALL_DATA)"
	@echo "MKDIR= $(MKDIR)"
	@echo "RM= $(RM)"
	@echo "TO_INC= $(TO_INC)"
	@echo "TO_LIB= $(TO_LIB)"

.PHONY: install uninstall local echo
