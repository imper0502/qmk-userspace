# imper0502 userspace

共用程式碼,會被名稱為 `imper0502` 的 keymap 自動引入(見 `layouts/*/imper0502`)。

## Layout of this folder

| 路徑 | 內容 |
|---|---|
| `config.h` | 所有 `imper0502` keymap 共用的設定:retro tapping 與 neutralizer、one-shot 逾時、滑鼠鍵、LED。各 layout 的 `config.h` 只放功能開關與該 layout 自己的設定 |
| `imper0502.h` / `imper0502.c` | 層名稱、共用巨集(`LT_BTN3`),以及 `matrix_scan_user`、`keyboard_post_init_user`、`process_record_user` |
| `keymap.h` | 只給 `keymap.c` 引用:QMK 直接從 keymap 讀取的表(tap dance、key override、combo)與 keymap 用的巨集 |
| `features/<feature>/` | 一個資料夾對應一組有關聯的開關,內含程式碼與該組的 `switches.h`(預設值與相依檢查) |
| `features/switches.h` | 引入各資料夾的 `switches.h` |
| `features/tap_dance/` | tap dance 的共用部分:`tap_dance.h/.c`(狀態與 `current_dance()`)、`layer_dance.c`(空白鍵、Enter、grave、引號與反斜線鍵共用的邏輯)、`tap_dance_actions.h`(QMK 讀取的 action 表)、`idle_timer.c`、`tapping_term.c` |
| `features/tap_dance/keys/` | 一個鍵一個檔,放該鍵的 finished/reset 實作:`control.c`、`enter.c`、`space.c`、`shift.c`、`backspace.c`(五者共用 `IMPER0502_TD_THUMB`)、`grave.c`、`quote.c`、`backslash.c`、`insert_plus.c`、`table.c`、`alt_table.c`。每個檔案由對應的 `IMPER0502_TD_*` 開關控制。其中 `enter.c`、`space.c`、`grave.c`、`quote.c`、`backslash.c` 只定義各自的鍵碼與修飾鍵,邏輯共用 `layer_dance.c` |

## Feature switches

開關一律是 `1`(開)或 `0`(關)。預設值在各資料夾的 `switches.h`,要改就在 layout 的 `config.h` 用 `#define` 覆寫。程式裡一律用 `#if` 判斷,不要用 `#ifdef`,因為定義成 `0` 的開關仍然算「有定義」。

| 資料夾 | 開關 | 預設 | 控制 |
|---|---|---|---|
| `tap_dance/` | `IMPER0502_TD_THUMB` | 1 | `TD_LCTL`、`TD_ENT`、`TD_SPC`、`TD_SFT`、`TD_BSPC` |
| | `IMPER0502_TD_GRAVE` | 1 | `TD_GRV` |
| | `IMPER0502_TD_EDGE` | 0 | `TD_QUOT`、`TD_BSLS` |
| | `IMPER0502_TD_INSERT_PLUS` | 0 | `TD_INSP` |
| | `IMPER0502_TD_TABLE` | 0 | `TD_RTAB` |
| | `IMPER0502_TD_ALT_TABLE` | 0 | `TD_TABA` |
| | `IMPER0502_TD_COMMA_DOT` | 0 | `TD_COMM`、`TD_DOT` |
| `key_override/` | `IMPER0502_OVERRIDE_PUNCT` | 0 | Shift + `,` `.` |

下列 feature 沒有自訂開關,條件已經由 QMK 的旗標或硬體決定:

| 資料夾 | 條件 |
|---|---|
| `encoder/` | 鍵盤設定 `ENCODER_ENABLE`(`keyboard.json` 的 `encoder`) |
| `leader/` | `LEADER_ENABLE = yes` |
| `combo/` | `COMBO_ENABLE = yes` |
| `led/` | 鍵盤定義了 `LED_PIN_ON_STATE`、`TXLED`、`RXLED` 才會編進去 |
| `tap_dance/idle_timer.c` | 跟著 `IMPER0502_TD_THUMB`、`IMPER0502_TD_GRAVE` 或 `IMPER0502_TD_EDGE`:按住會開 `_FN` 層的 tap dance 會讀 `is_idle_timeout` |

`tap_dance/` 的開關需要 `TAP_DANCE_ENABLE = yes`,`IMPER0502_TD_THUMB` 另外需要 `CAPS_WORD_ENABLE = yes`(`TD_SFT` 用 Caps Word),`IMPER0502_OVERRIDE_PUNCT` 需要 `KEY_OVERRIDE_ENABLE = yes`,不符合時編譯會出現 `#error`。keymap 用到的 `TD_*` 所對應的開關必須是 1,否則會出現 `undeclared` 錯誤。

## License

Copyright 2024 Joey Wu yoj845@gmail.com @imper0502

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
