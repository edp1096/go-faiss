package main

import (
	"fmt"

	"github.com/edp1096/go-faiss"
)

func main() {
	/* Save index */
	dimension := 3

	items := []float32{
		0, 1.2, 3.4, 5.6,
		1, 2.1, 4.3, 6.5,
		2, 0.8, 1.5, 2.7,
		3, 3.2, 2.8, 1.4,
	}

	index, err := faiss.NewIndexFlatL2(dimension)
	if err != nil {
		panic(err)
	}

	index.Add(items)

	faiss.WriteIndex(index, "index_euc.faiss")

	/* Load index */
	numNearest := int64(2)
	query := []float32{0, 0.9, 2.3, 4.5}

	index2, err := faiss.ReadIndex("index_euc.faiss", faiss.IOFlagMmap)
	if err != nil {
		panic(err)
	}

	dists, labels, err := index2.Search(query, numNearest)
	if err != nil {
		panic(err)
	}

	fmt.Println("dists:", dists)
	fmt.Println("labels:", labels)
}
