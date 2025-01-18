package main

import (
	wrd "Engine/src"
	"github.com/veandco/go-sdl2/sdl"
)

type PlayerController struct {
	Obj *wrd.BaseObject
}

var keyState = make(map[sdl.Keycode]bool)

func (self PlayerController) Tick(obj *wrd.BaseObject) {
	keys := sdl.GetKeyboardState()
	keyState[sdl.K_SPACE] = keys[sdl.SCANCODE_SPACE] != 0
	keyState[sdl.K_a] = keys[sdl.SCANCODE_A] != 0
	keyState[sdl.K_d] = keys[sdl.SCANCODE_D] != 0

}

func (self PlayerController) Start(obj *wrd.BaseObject) {
	// ...
}
