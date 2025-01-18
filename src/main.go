package main

import (
	wrd "WrdEngine/src"
	sdl "github.com/veandco/go-sdl2/sdl"
	"os"
	"path/filepath"
)

var SCREEN = wrd.Screen{Width: 800, Height: 600}

const (
	_ = iota
	WindowErrorExit
	RendererErrorExit
	GameErrorExit
	ErrorExit
)

func main() {
	executable, err := os.Executable()
	execPath := filepath.Dir(executable)

	err = os.Chdir(execPath)
	os.Chdir("..")
	if err != nil {
		ShowError(ErrorExit, "An error occurred while starting game: %v", err)
	}
	w, err := wrd.NewWindow("Wordler", SCREEN.Width, SCREEN.Height, "assets/Images/background.bmp")
	if err != nil {
		ShowError(WindowErrorExit, "An error occurred while creating the window: ", err)
	}
	defer w.Destroy()

	player, err := wrd.NewPlayer(w.Renderer, "assets/Images/player.bmp", 0, SCREEN.Height-175)
	if err != nil {
		ShowError(GameErrorExit, "An error occurred while rendering objects: ", err)
	}

	floor, err := wrd.NewPhysicalBaseObj(w.Renderer, sdl.Color{R: 255, G: 255, B: 255, A: 255}, 0, SCREEN.Height-10, SCREEN.Width, 10)
	if err != nil {
		ShowError(GameErrorExit, "An error occurred while creating the floor: ", err)
	}
	floor.Lock()

	var run bool = true
	for run {
		for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
			switch e := event.(type) {
			case *sdl.QuitEvent:
				run = false
			default:
				player.Tick(e)
			}
		}
		err := w.Renderer.Clear()
		if err != nil {
			ShowError(RendererErrorExit, "An error occurred while clearing the renderer: ", err)
		}
		w.Render()
		floor.Render()
		player.Render()
		w.Renderer.Present()
	}
}
