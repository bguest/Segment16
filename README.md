## WTF? How does this thing work?

Barely. Be gentle, its a work in progress. But in general the keyboard controls the 16 Segment Displays.

## Components

+ **Sign**: The Big 16 Segment Displays
+ **Keyboard**: Used for changing the sign, loosely based on VIM.
+ **Display**: 4 x 40 LCD Display attached to keyboard, it try's to be helpful.

## VIM

The way the sign is manipulated is loosely related to the VIM Text Editor. With VIM there are two
modes, Insert Mode and Normal Mode. **In thses instructions, unless otherwise stated, assume I'm
talking about pressing keys in normal mode**.

### Insert Mode

Insert mode is used to enter text into the sign. If you are in normal mode you can get to insert
mode by typing `i`.

**Example**: If you wanted to the sign to say `HI`, you would press `<esc>` then `>` until the
display says `Basic Typing` then press `i` followed by `H` and `I`.

### Normal Mode

In normal mode the keys are setup to edit the effects of the sign, color, tempo, different text
effects. To get to normal mode from Insert mode either press `<esc>` or type `kj` (`k` followed by
`j`).

**Example**: If you wanted to change the background to fade through the color spectrum. You would
type `<esc>`, then press `1` to edit the background, then press `h` until the display says `Solid
Fade`.

# Effects

It would be boring if all the sign did was show stationary text, so I made it needlessly more
complicated by adding effects.  The program is broken into to effects areas. Text Effects and
Color Effects. Text Effects control what segments are "on". Color Effects control what color the on
and off segments are.

Generally in normal mode typing `R` will reset the current effects to some default settings.

## Text Effects

Text Effects control what segments are "on".

+ `>`: Changes to the next text effect.
+ `<`: Changes to the previous text effect.

### Basic Typing

Like it sounds: In Insert mode, typing causes letters to be scrolled from right to
left.

### Random On

Randomly turns segments on.

+ `k`/`j`: Increases / Decrease the frequency
+ `]`/`[`: Increases / Decrease the number of random segments.

### Counter

Counts up or down some amount at some frequency

+ `k`/`j`: Increases / Decrease the frequency.
+ `]`/`[`: Increases / Decrease the amount that is added each step.

## Color Effects

Color Effects control what color the on and off segments are. There are two "Layers" that you can
manipulate. Pressing `1` sets you editing the Background Layer. Pressing `2` sets you
to editing the Letters layer.

+ `1`: Edit "Background" color layer
+ `2`: Edit "Letters" color layer

Once you have chosen a layer pressing the `h` and `l` keys cycles through the different color
effects

+ `h`/`l`: Next/Previous Color Effect

### Solid Color

Sets the selected color layer a solid non-changing color

+ `b`/`B`: (Brightness) Decrease / Increase color Value:
+ `c`/`C`: (Color) Decrease / Increase color Hue:
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation:

### Solid Fade

Fades the layer through the color spectrum.

+ `f`/`s`: (Faster/Slower) Increase / Decrease fade speed

+ `b`/`B`: (Brightness) Decrease / Increase color Value:
+ `c`/`C`: (Color) Decrease / Increase color Hue:
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation:

### Random Fade

This one if fun. Randomly Fades segments in the layer at a different rate. Typing letters will cause
the On segments to converge on a specific color after a certain amount of time has passed. Letters
and words will fade out of nothing and then fade away into chaos.

+ `f`/`s`: (Faster/Slower) Increase / Decrease maximum fade speed
+ `F`/`S`: (Faster/Slower) Decrease / Increase the time it takes to to converge.

To control the layer converge color:

+ `b`/`B`: (Brightness) Decrease / Increase color Value:
+ `c`/`C`: (Color) Decrease / Increase color Hue:
+ `v`/`V`: (Vibrancy) Decrease / Increase color Saturation:

<!--

# Q + A:

One of my "favorite" things about this project has been all the helpful suggestions that people
give, free of any effort on their end. If you really want to help. Make a pull request. I imagine
these questions in the tone of 1997 Valley Girl:

**Q**: Why are their only two letter. It would be way cooler if you had more letters so you could do
whole worlds.

**A**: No Shit. But cutting, grinding, welding, painting, soldering, wireing take time... And yes
I'd love help. I've actually got two more letters in the works, come find me at Burning Man and you'll be
able to spell naughty words to your hearts content.

**Q**: Why is it so complicated? Why not just use faders/dashpots to control things.

**A**: Things are as complicated as they can be, thats the nature of life. Adding faders/dashpots
makes things more complicated, not less. What you really want is a nicer user interface. In which
case I know its kind of cryptic, but I've only got limited bandwidth, but you can definitely help if
you want! I actually think it would be awesome to set up an old DJ Controller to change color
effects.

**Q**: You should make it sound reactive.

**A**: Yeah! This one is definetly on my list. I'd like to make the whole sign into one big Spectrum Analyser.

**Q**: Why not make an iPhone App.

**A**: Lets make it happen! I assume you know Objective-C / Swift ?
-->
