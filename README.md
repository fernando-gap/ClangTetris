# c_tetris

I have always doubted how tetris was coded, I coded a so-called "clone" of tetris with my own algorithm that comes from the innards of my brain.
The result of that was this project.

Below are some TODOs you can try TO DO and open a PR to improve it!, I would be amazed, the most signifcant change I would recommend are the repetitive code,
which could be shrunk down in many lines, I did not have the time to do, so when I got time I may do it as well.

# TODO

- [ ] Move shape to the bottom when overlapping happens in the TOP border of a SHAPE
- [ ] L shape is moving to the LEFT, when it gets WIDER, it should be to the right when it has space
- [ ] Reuse function in ./src/shapes/ directory instead of creating one for each shape
- [ ] Implement random colors, rotations, and make the shape appear in the middle instead of the TOP LEFT CORNER in `GAME_CreateShape_X`
- [ ] Check for memory leaks, I have not the time to really check if there are memory leaks. All the functions inside

