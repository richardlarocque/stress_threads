package main

import (
	"fmt"
	"time"
	"flag"
	"bufio"
	"os"
)

const NumBurners int = 100

func burnerLoop(index int) {
	count := 0
	for { count += index }
}

func readerLoop(index int) {
	count := 0
	for {
		bio := bufio.NewReader(os.Stdin)
		bio.ReadLine()

		fmt.Printf(
			"Reader[%d] received input number %d\n",
			index, count);

		count++
	}
}

func main() {
	var numBurnersPtr = flag.Int("burners", 0,
		"number of busy-looping goroutines")
	var numReadersPtr = flag.Int("readers", 0,
		"number of goroutines blocking on STDIN")

	flag.Parse()

	// Spawn the burner threads.
	for i := 0; i < *numBurnersPtr; i++ {
		go burnerLoop(i)
	}

	// Spawn the reader threads.
	for i := 0; i < *numReadersPtr; i++ {
		go readerLoop(i)
	}

	// Spawn an active goroutine.
	go func() {
		count := 0
		for {
			fmt.Printf("Count: %v, %v\n", count, time.Now());
			time.Sleep(1000 * time.Millisecond)
			count++
		}
	}()


	// Block forever.
	x := make(chan struct{})
	<-x
}
