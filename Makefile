.SILENT:

MAKEFLAGS += --no-print-directory

.PHONY: link test

link:
	for dir in $(QMK_USERSPACE)/keyboards/*/; do ln -sfnT "$${dir%/}" "$(QMK_HOME)/keyboards/$$(basename "$$dir")"; done
	for dir in $(QMK_USERSPACE)/layouts/*/; do ln -sfnT "$${dir%/}" "$(QMK_HOME)/layouts/default/$$(basename "$$dir")"; done
	ln -sfnT $(QMK_USERSPACE)/users/imper0502 $(QMK_HOME)/users/imper0502

test: link
	+$(MAKE) -C $(QMK_HOME) test:imper0502

Makefile: ;

%: link
	+$(MAKE) -C $(QMK_HOME) $(MAKECMDGOALS)
