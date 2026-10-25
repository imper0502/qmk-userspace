# imper0502's 56-key keymap

## Keymap

```
LAYOUT_split_4x6_4
┌───┬───┬───┬───┬───┬───┐             ┌───┬───┬───┬───┬───┬───┐
│ « │ » │ @ │ # │ ( │ ) │             │ ^ │ & │ * │ $ │ins│del│
├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
│tab│ q │ w │ f │ p │ b │             │ j │ l │ u │ y │- _│= +│
├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
│esc│ a │ r │ s │ t │ g │             │ m │ n │ e │ i │ o │' "│
├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
│a&c│ z │ x │ c │ d │ v │             │ k │ h │, ;│. :│/ ?│\ |│
└───┴───┴───┴───┴───┴───┘             └───┴───┴───┴───┴───┴───┘
                ┌───┬───┬───┐     ┌───┬───┬───┐
            ┌───┤ctl│sft│bs │     │ent│spc│` ~├───┐
            │i+ ├───┴───┴───┘     └───┴───┴───┤   │
            └───┘                             └───┘
```

`esc` and `'` are mod-taps (gui and alt); `i+` is the insert/plus tap dance. Shared code and the feature switches live in `users/imper0502`, see its readme.

## Compile

```sh
qmk compile -kb pragmatic -km imper0502
qmk compile -kb temperance -km imper0502
```

編譯後的 hex 位於 `/qmk_firmware`。
