QMK_REPO ?= zsa/qmk_firmware
QMK_BRANCH ?= firmware22

.PHONY: build
build: qmk_firmware/keyboards/voyager/keymaps/eckig  qmk_firmware/.build/voyager.bin

.PHONY: qmk_setup
qmk_setup:
	make -C qmk_firmware git-submodules
	cd qmk_firmware && qmk setup $(QMK_REPO) -b $(QMK_BRANCH) -y

qmk_firmware/keyboards/voyager/keymaps/eckig: eckig qmk_setup
	rm -rf "$@"
	cp -r "$<" "$@"

qmk_firmware/.build/voyager.bin: eckig qmk_setup
	make -C qmk_firmware voyager:eckig
