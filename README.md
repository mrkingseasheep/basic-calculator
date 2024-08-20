# basic-calculator

Hello this was a nice introduction to parsing and tokenizing equations.
Calculations can be parsed from our normal notation to reverse Polish notation using Dijkstra's shunting algorithm.
The equation can then be solved recursively, with a support for a variety of different operations.

## How to use it

`git clone https://github.com/mrkingseasheep/basic-calculator.git`

Then compile `main.cpp`

`make`

OR

`g++ main.cpp -o calculator.app`

Then run the binary: `./calculator.app`

### Running with Rofi

Ensure you have `rofi` installed.

Compile the binary.

Edit `calc.sh` and follow the instructions there.

Run `calc.sh`

Profit.

## List of supported operations

Remember to properly use (brackets) 👍

- [x] +-/\*
- [x] ^%!
- [x] sin cos tan
- [x] min max
- [x] lcm and gcd

For min, max, lcm and gcd, follow the following notation:

`lcm(2, 4)`

%, !, lcm and gcd will truncate (NOT ROUND) any floating point number.

## List of yet to be supported operations

- [ ] arctan and the other funny trigonometry operations (just a change to the regex)
- [ ] currency conversion
- [ ] support for constants
- [ ] unit conversion
