package main

import (
	wrd "Engine/src"
	"fmt"
	"github.com/veandco/go-sdl2/sdl"
	"log"
	"os"
	"path/filepath"
)

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

	window, err := wrd.NewWindow("Game")
	if err != nil {
		log.Fatalf("%v", err)
	}
	defer window.Destroy()

	player, err := wrd.NewObj(window.Renderer, "assets/Images/player.bmp", 100, 100)
	if err != nil {
		log.Fatalf("failed to create object: %v", err)
	}

	player.Connect(wrd.LeftClicked, func() {
		fmt.Println("Nacisnołeś mnie! (lewym przyciskiem myszy)")
	})

	player.Connect(wrd.MiddleClicked, func() {
		fmt.Println("Nacisnołeś mnie! (środkowym przyciskiem myszy)")
	})

	player.Attach(PlayerController{})

	//player.Connect(wrd.RightClicked, func() {
	//	fmt.Println("Nacisnołeś mnie! (prawym przyciskiem myszy)")
	//})

	background, err := wrd.ImagePathToTexture(window.Renderer, "assets/Images/background.bmp")
	mainScene, err := wrd.NewScene("MainScene", window.Renderer, background, *player)
	window.SetScene(mainScene)

	running := true
	for running {
		for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
			switch event.(type) {
			case *sdl.QuitEvent:
				running = false
			}
		}

		player.Tick()

		//if err := player.Render(); err != nil {
		//	log.Printf("render error: %v", err)
		//}

		window.RenderScene()
		window.Renderer.Present()
	}
}
