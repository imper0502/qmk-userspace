# IMPER0502's QMK Userspace

這個 repo 是 [QMK External Userspace](https://docs.qmk.fm/newbs_external_userspace)，qmk_firmware 本體放在 Docker named volume `qmk_firmware_dir`，透過 `user.overlay_dir` 疊加本 repo 的內容。

```
qmk.json                         # build targets
keyboards/<keyboard>/            # 自訂鍵盤，各為獨立 repo 的 submodule（需各自掛載到 qmk_firmware/keyboards）
layouts/<layout>/<keymap>/       # 依 layout 共用的 keymap（layout 需另外掛載到 qmk_firmware/layouts/default/<layout>）
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
2. 第一次會自動把 qmk_firmware clone 到 `qmk_firmware_dir`（與 `make install` 共用），並執行 `qmk config user.overlay_dir=<workspace>`。
3. 在容器內的 terminal 直接編譯：

```sh
qmk compile -kb pragmatic -km imper0502
# 或編譯 qmk.json 內所有 build targets
qmk userspace-compile
# 編譯出的 hex 會自動複製到 repo 根目錄
```

注意：需用本機資料夾開啟（不支援 "Clone Repository in Container Volume"）。

## Make Targets
```sh
make install                                  # 取得 image 並 clone qmk_firmware 到 volume
make compile keyboard=pragmatic keymap=imper0502
make shell                                    # 進入已設定 overlay 的 bash
make test                                     # 執行 tests/imper0502 的 QMK 單元測試
make clean
make uninstall
```

## Tests
`tests/imper0502/` 是 [QMK 單元測試](https://docs.qmk.fm/unit_testing)(googletest),只測 tap dance 的核心邏輯,不測鍵位:

- `current_dance()` 依 tap 次數、按住與被打斷回傳的狀態。
- 每個 tap dance(Control、Enter、Space、Grave、Insert plus)在每種 tap 次數、點按或按住之後,都不會留下卡住的按鍵或修飾鍵。
- 左 Control 鍵每種手勢送出什麼:點一、二、三下各送一、二、三次 Ctrl;按住維持 Ctrl;點一下再按住送 Alt+Shift;點兩下再按住切換 `_MK` 層且不送 Ctrl。
- 空白鍵、grave 與 Enter 鍵每種手勢:點 n 下送 n 個;按住開 `_FN` 層(grave 同時按住 Ctrl、Enter 同時按住 Shift);點一下再按住:空白鍵是 Ctrl+Shift、grave 是 Alt+Shift、Enter 是 Ctrl+Alt(都加上 `_FN` 層);點兩下以上再按住會重複送出;單擊被其他鍵打斷時,停頓後是層、打字中是該鍵本身。
- Shift 鍵(取代 `OSM`,沒有鎖定):點一下只讓下一個鍵加 Shift;點兩下以上開啟 Caps Word,Caps Word 開著時點任何下數都是關閉它;按住是 Shift,按住時按其他鍵,那個鍵也有 Shift;點一下以上再按住是 Ctrl+Alt。

QMK 只在 `qmk_firmware/tests/` 底下找測試,所以 `make test` 與 devcontainer 會把 `tests/imper0502` 和 `users/imper0502` 掛進去,在容器內執行 `make test:imper0502`。

## License
本專案以 GPL-2.0-or-later 授權(全文見 `LICENSE`),各原始碼檔案以檔頭標示為準。`keyboards/pragmatic*` 衍生自 James Sa 的作品。
