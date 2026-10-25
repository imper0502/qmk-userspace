# imper0502's 54-key keymap

## Keymap

```
LAYOUT_split_4x6_3
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
                │ctl│sft│bs │     │ent│spc│` ~│
                └───┴───┴───┘     └───┴───┴───┘
```

`esc` and `'` are mod-taps (gui and alt). Shared code and the feature switches live in `users/imper0502`, see its readme.

## Compile

`pragmatic` and `temperance` list `split_4x6_4` before `split_4x6_3` in `community_layouts`, so they build the 56-key keymap. To build this one, put `split_4x6_3` first in a keyboard's `community_layouts`.

```sh
qmk compile -kb pragmatic -km imper0502
```

編譯後的 hex 位於 `/qmk_firmware`。
