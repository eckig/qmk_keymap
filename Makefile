QMK_REPO ?= zsa/qmk_firmware
QMK_BRANCH ?= firmware22

.PHONY: build
build: zsa_firmware/keyboards/voyager/keymaps/eckig  zsa_firmware/.build/voyager.bin

.PHONY: qmk_setup
qmk_setup:
	make -C zsa_firmware git-submodules
	cd zsa_firmware && qmk setup $(QMK_REPO) -b $(QMK_BRANCH) -y

zsa_firmware/keyboards/voyager/keymaps/eckig: eckig qmk_setup
	rm -rf "$@"
	cp -r "$<" "$@"

zsa_firmware/.build/voyager.bin: eckig qmk_setup
	make -C zsa_firmware voyager:eckig
