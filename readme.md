# IMPER0502's QMK Userspace

這個 repo 是 [QMK External Userspace](https://docs.qmk.fm/newbs_external_userspace)，qmk_firmware 本體放在 Docker named volume `qmk_firmware_dir`，透過環境變數 `QMK_USERSPACE`（image 預設為 `/qmk_userspace`）疊加本 repo 的內容。

```
qmk.json                         # build targets
keyboards/<keyboard>/            # 自訂鍵盤，各為獨立 repo 的 submodule（用符號連結放進 qmk_firmware/keyboards）
layouts/<layout>/<keymap>/       # 依 layout 共用的 keymap（layout 用符號連結放進 qmk_firmware/layouts/default/<layout>）
users/<keymap>/                  # 同名 keymap 自動引入的 userspace
```

## Keymaps

| layout | keymap | 說明 |
|---|---|---|
| `split_4x6_5` | `default`、`via`、`imper0502` | 58 鍵,temperance 使用:QWERTY、VIA 與 imper0502 keymap |
| `split_4x6_4` | `imper0502` | 56 鍵,pragmatic 使用 |
| `split_4x6_3` | `imper0502` | 54 鍵 |
| `split_4x6_2x3` | `imper0502` | 60 鍵,目前沒有鍵盤使用 |
| `split_6x6` | `default`、`imper0502`、`transposed`、`handdown`、`numpad` | pragmatic_classical 的 keymap |

`imper0502` keymap 共用 `users/imper0502`,功能開關的說明見 [users/imper0502/readme.md](users/imper0502/readme.md)。

## Clone
鍵盤是 git submodule：

```sh
git clone --recurse-submodules https://github.com/imper0502/qmk-userspace.git
# 已 clone 的話
git submodule update --init
```

| submodule | repo |
|---|---|
| `keyboards/pragmatic` | [qmk-kb-pragmatic](https://github.com/imper0502/qmk-kb-pragmatic) |
| `keyboards/pragmatic_classical` | [qmk-kb-pragmatic-classical](https://github.com/imper0502/qmk-kb-pragmatic-classical) |
| `keyboards/temperance` | [qmk-kb-temperance](https://github.com/imper0502/qmk-kb-temperance) |

## Dev Container (VS Code)
需要 Docker 與 VS Code 的 Dev Containers 擴充套件。

1. 用 VS Code 開啟此資料夾，執行 `Dev Containers: Reopen in Container`。
2. 第一次會自動把 qmk_firmware clone 到 named volume `qmk_firmware_dir`，並初始化鍵盤 submodule。repo 掛在這個 image 預設的 `/qmk_userspace`，所以不用設定 `user.overlay_dir`；每次啟動時 `make link` 會把 `keyboards/*`、`layouts/*` 與 `users/imper0502` 用符號連結放進 qmk_firmware。
3. 在容器內的 terminal 編譯與測試：

```sh
make temperance:imper0502      # 或 make pragmatic:imper0502；hex 會輸出到 repo 根目錄
make test                      # 只跑 tests/imper0502 的 QMK 單元測試
qmk userspace-compile          # 編譯 qmk.json 內所有 build targets
```

注意：需用本機資料夾開啟（不支援 "Clone Repository in Container Volume"）。

`Makefile` 是 QMK userspace 範本那份（把所有目標轉給 qmk_firmware 的 make），加上 `make link`；`make test` 只跑自己的測試，不是 QMK 全部的測試。

## Tests
`tests/imper0502/` 是 [QMK 單元測試](https://docs.qmk.fm/unit_testing)(googletest),只測 tap dance 的核心邏輯,不測鍵位:

- `current_dance()` 依 tap 次數、按住與被打斷回傳的狀態。
- 每個 tap dance(Control、Alt、Enter、Space、Backspace、Grave、引號、反斜線、Insert plus)在每種 tap 次數、點按或按住之後,都不會留下卡住的按鍵或修飾鍵。
- 左 Alt 鍵:按住是 Alt,點一下再按住是 Shift+Ctrl。
- 左 Control 鍵每種手勢送出什麼:點一、二、三下各送一、二、三次 Ctrl;按住維持 Ctrl;點一下再按住送 Alt+Shift;點兩下再按住切換 `_MK` 層且不送 Ctrl。
- 空白鍵、grave 與 Enter 鍵每種手勢:點 n 下送 n 個;按住開 `_FN` 層(grave 同時按住 Ctrl、Enter 同時按住 Shift);點一下再按住:空白鍵是 Ctrl+Shift、grave 是 Alt+Shift、Enter 是 Ctrl+Alt(都加上 `_FN` 層);點兩下以上再按住會重複送出;單擊被其他鍵打斷時,停頓後是層、打字中是該鍵本身。
- Shift 鍵(取代 `OSM`,沒有鎖定):點一下只讓下一個鍵加 Shift;點兩下以上開啟 Caps Word,Caps Word 開著時點任何下數都是關閉它;按住是 Shift,按住時按其他鍵,那個鍵也有 Shift;點一下以上再按住是 Ctrl+Alt。

QMK 只在 `qmk_firmware/tests/` 底下找測試,所以 devcontainer 會把 `tests/imper0502` 掛進去(要真實資料夾,符號連結找不到),`users/imper0502` 則由 `make link` 連進去,在容器內執行 `make test:imper0502`。

## License
本專案以 GPL-2.0-or-later 授權(全文見 `LICENSE`),各原始碼檔案以檔頭標示為準。`keyboards/pragmatic*` 衍生自 James Sa 的作品。
