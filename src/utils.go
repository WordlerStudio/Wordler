package main

import (
	"fmt"
	"os"
)

func ShowError(exitcode int, msgs ...any) {
	var msg string
	for _, msg_ := range msgs {
		msg += fmt.Sprintf("%v", msg_)
	}
	fmt.Fprintln(os.Stderr, msg)
	os.Exit(exitcode)
}
