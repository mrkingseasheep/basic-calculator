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

- [x] +-/\*
- [x] ^%!
- [x] sin cos tan
- [x] min max

## List of yet to be supported operations

- [ ] arctan and the other funny trigonometry operations
- [ ] currency conversion
- [ ] lcm and gcf
- [ ] support for constants
- [ ] unit conversion
