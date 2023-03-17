# c_tetris

I have always doubted how tetris was coded, then I did a so-called "clone" of tetris with my own algorithm that comes from the innards of my brain.
The result of that was this project.

Below are some TODOs you can try TO DO and open a PR to improve it!, I would be amazed, the most signifcant change I would recommend are the repetitive code,
which could be shrunk down in many lines, I did not have the time to do, so when I got time I may do it as well.

# ISSUES
Here are some sadly issues you will have if you want to really touch this game, as this game was a "one-week project"

1. I hardcoded the game in 400x200, so if you try to make the game look big, you will have thousands of problems:
   1. All the shapes SDL_Rect have a fixed length, that is (w/h) 400/200 = 20, so if you want to increase the size of the board, you will likely touch every file to change the 20 to the new board size... The screen resolution from (SDL) you can change without problems.
   2. I did not used textures in SDL, I used the pure SDL_Rect to render all shapes, so If you want to apply textures using images in the squares, you will need to change practically the entire rendering method. Though you can keep SDL_Rect, and only render the image in the texture using RenderCopy.

2. Portability, this game was meant to run in my machine, so if you try to run in windows, you will have problems, as all source files are using the POSIX file paths, so it will be probabily run in linux. I have no idea in how to make portable code as this was my first C project with +2K lines...


# TODO

- [ ] Move shape to the bottom when overlapping happens in the TOP border of a SHAPE
- [ ] L shape is moving to the LEFT, when it gets WIDER, it should be to the right when it has space
- [ ] Reuse function in ./src/shapes/ directory instead of creating one for each shape
- [ ] Implement random colors, rotations, and make the shape appear in the middle instead of the TOP LEFT CORNER in `GAME_CreateShape_X`
- [ ] Check for memory leaks, I have not the time to really check if there are memory leaks. All the functions inside

