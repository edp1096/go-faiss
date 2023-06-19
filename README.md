Modification for windows

## Usage

* Example
```go
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
```

* Build
```powershell
go build # cpu
# or
go build -tags # gpu
```

----
# go-faiss

[![Go Reference](https://pkg.go.dev/badge/github.com/DataIntelligenceCrew/go-faiss.svg)](https://pkg.go.dev/github.com/DataIntelligenceCrew/go-faiss)

Go bindings for [Faiss](https://github.com/facebookresearch/faiss), a library for vector similarity search.

## Install

First you will need to build and install Faiss:

```
git clone https://github.com/facebookresearch/faiss.git
cd faiss
cmake -B build -DFAISS_ENABLE_GPU=OFF -DFAISS_ENABLE_C_API=ON -DBUILD_SHARED_LIBS=ON .
make -C build
sudo make -C build install
```

Building will produce the dynamic library `faiss_c`.
You will need to install it in a place where your system will find it (e.g. `/usr/lib` on Linux).
You can do this with:

    sudo cp build/c_api/libfaiss_c.so /usr/lib

Now you can install the Go module:

    go get github.com/DataIntelligenceCrew/go-faiss

## Usage

API documentation is available at <https://pkg.go.dev/github.com/DataIntelligenceCrew/go-faiss>.
See the [Faiss wiki](https://github.com/facebookresearch/faiss/wiki) for more information.

Examples can be found in the [_example](_example) directory.