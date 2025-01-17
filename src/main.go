package main

import (
	wrd "WrdEngine/src"
	"fmt"
	sdl "github.com/veandco/go-sdl2/sdl"
	"os"
)

var SCREEN = wrd.Screen{800, 600}

const (
	_ = iota
	WindowError
	RendererError
	GameError
	Error
)

func ShowError(exitcode int, msgs ...any) {
	var msg string
	for _, msg_ := range msgs {
		msg += fmt.Sprintf("%v", msg_)
	}
	fmt.Fprintln(os.Stderr, msg)
	os.Exit(exitcode)
}

func main() {
	r, w := initAll()
	defer func() {
		w.Destroy()
		r.Destroy()
		sdl.Quit()
	}()
	player, err := wrd.NewPlayer(r, "assets/player.bmp", 0, 0)
	if err != nil {
		ShowError(GameError, "An error occurred while rendering objects: ", err)
	}
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
		r.Clear()
		player.Render()
		r.Present()
	}
}

func initAll() (r *sdl.Renderer, w *sdl.Window) {
	if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		ShowError(WindowError, "An error occurred while creating the window")
	}

	w, err := sdl.CreateWindow("Wordler", sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED, SCREEN.Width, SCREEN.Height, sdl.WINDOW_SHOWN)
	if err != nil {
		ShowError(WindowError, "An error occurred while creating the window")
	}

	r, err = sdl.CreateRenderer(w, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		ShowError(RendererError, "An error occurred while creating the window")
	}
	return
}
