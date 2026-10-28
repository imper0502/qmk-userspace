# imper0502's 58-key keymap

## Keymap

```
LAYOUT_split_4x6_5
┌───┬───┬───┬───┬───┬───┐             ┌───┬───┬───┬───┬───┬───┐
│ « │ » │ @ │ # │ ( │ ) │             │ ^ │ & │ * │ $ │ins│del│
├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
│tab│ q │ w │ f │ p │ b │             │ j │ l │ u │ y │- _│= +│
├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
│esc│ a │ r │ s │ t │ g │             │ m │ n │ e │ i │ o │' "│
├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
│alt│ z │ x │ c │ d │ v │             │ k │ h │, <│. >│/ ?│\ |│
└───┴───┴───┴───┴───┴───┘             └───┴───┴───┴───┴───┴───┘
            ┌───┬───┬───┬───┐     ┌───┬───┬───┬───┐
            │a+t│ctl│sft│bs │     │ent│spc│` ~│   │
            └───┴───┴───┴───┘     └───┴───┴───┴───┘
                          ┌───┐ ┌───┐
                          │scr│ │   │
                          └───┘ └───┘
```

The thumb keys are the ones of the 56-key keymap, see [split_4x6_4](../../split_4x6_4/imper0502/readme.md), except that the outer left key is the Alt+Tab tap dance and the lower left key is Win+Shift+S (screenshot). The lower right key is unassigned (`XXXXXXX`, transparent on the `_QW` layer).

`esc` is a mod-tap (gui), `'` taps a quote and holds Win with the `_FN` layer, `bs` is the backspace tap dance (hold is Backspace, one tap then hold is Ctrl+Shift); `a+t` is the Alt+Tab tap dance (`IMPER0502_TD_ALT_TABLE` is 1 in this keymap) and `scr` is Win+Shift+S. Shared code and the feature switches live in `users/imper0502`, see its readme.

`temperance` lists `split_4x6_5` first among its community layouts, so `-km imper0502` builds this keymap there.

## Compile

```sh
qmk compile -kb temperance -km imper0502
```

編譯後的 hex 位於 `/qmk_firmware`。
