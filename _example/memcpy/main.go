package main

import (
	"fmt"

	"github.com/edp1096/go-faiss"
)

func main() {
	index, err := faiss.NewIndexFlatL2(16)
	if err != nil {
		panic(err)
	}

	gpuIndex, err := faiss.TransferToGpu(faiss.Index(index))
	if err != nil {
		panic(err)
	}

	fmt.Println(gpuIndex.Dim())

}
