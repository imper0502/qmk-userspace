image_name := qmkfm/qmk_cli
image_tag := latest
volume := qmk_firmware_dir
keyboard ?= pragmatic
keymap ?= imper0502

# External Userspace 的 overlay 只支援 keymaps/layouts/users，
# 自訂 keyboard 需要各自掛載到 qmk_firmware/keyboards 底下。
keyboard_mounts := $(foreach d,$(notdir $(wildcard keyboards/*)),-v "$(CURDIR)/keyboards/$(d)":/qmk_firmware/keyboards/$(d))
# community layout 的定義必須存在於 qmk_firmware/layouts/default（QMK 只在該處驗證 community_layouts）
layout_mounts := $(foreach d,$(notdir $(wildcard layouts/*)),-v "$(CURDIR)/layouts/$(d)":/qmk_firmware/layouts/default/$(d))

docker_run := docker run -it --rm \
	-v $(volume):/qmk_firmware \
	-v "$(CURDIR)":/userspace \
	$(keyboard_mounts) \
	$(layout_mounts) \
	$(image_name):$(image_tag)
overlay := qmk config user.overlay_dir=/userspace

.PHONY: install uninstall clean compile shell submodules

install: submodules
	docker pull $(image_name):$(image_tag)
	docker run -it --rm -v $(volume):/qmk_firmware $(image_name):$(image_tag) \
		sh -c "[ -d /qmk_firmware/.git ] || qmk setup -y"

submodules:
	git submodule update --init

# make compile keyboard=pragmatic keymap=imper0502   (hex 會輸出到 repo 根目錄)
compile: submodules
	$(docker_run) sh -c "$(overlay) && qmk compile -kb $(keyboard) -km $(keymap)"

shell: submodules
	$(docker_run) sh -c "$(overlay) && exec bash"

uninstall: clean
	docker volume rm $(volume)
	docker image rm $(image_name):$(image_tag)

clean:
	rm -f *.hex *.bin *.uf2
