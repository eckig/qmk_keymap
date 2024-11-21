QMK_REPO ?= zsa/qmk_firmware
QMK_BRANCH ?= firmware24

.PHONY: build
build: qmk_setup
	rm -rf qmk_firmware/keyboards/zsa/voyager/keymaps/eckig
	cp -r eckig qmk_firmware/keyboards/zsa/voyager/keymaps/eckig
	make -C qmk_firmware zsa/voyager:eckig

.PHONY: qmk_setup
qmk_setup:
	make -C qmk_firmware git-submodules
	cd qmk_firmware && qmk setup $(QMK_REPO) -b $(QMK_BRANCH) -y
