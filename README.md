# [Minigin](https://github.com/OleksandrHlebov/Bubble-Bobble)

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

This is an engine based on Minigin template made for programming 4 assignment at DAE.

The game I was assigned to implement is Bubble Bobble.

# Specifics
The engine contains all of the standard assignment requirements. Here are some specific design choices that I have made.

## Event dispatcher
The engine utilises event dispatching system that takes an EventHandler and allows for decoupled game event handling with a base GameEvent class that can be inherited from.

## Collision system
The engine provides the user with a collision system based on 2D AABB colliders. Those can be achieved by adding Collision2DComponent to an object 
and subscribing to OnOverlap event to react to collisions and resolve them as needed. The dynamic and static collisions are separated, allowing for checking the collisions only of moving objects and only after they moved.
In addition to that there are utility functions such as TraceSegment or TraceRect that can be useful for detecting a collision(s) at any given moment in any direction, of any object collision type.

## Animation 2D
The engine has implemented an Animation2DComponent which allows for easy utilisation of textures with multiple frames by providing the starting frame, last frame, total amount of frames in the animation and
 if it should loop for a certain amount of times.

## Custom keybind
The engine provides the user with own keybind struct, that can be used for input bindings for either gamepad(uses own implementation) or keyboard(uses sdl scancodes).