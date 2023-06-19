package faiss

// #cgo LDFLAGS: -L. -lfaiss_c_cuda
// #include <faiss/c_api/MetaIndexes_c.h>
import "C"
import (
	"errors"
)

func NewIndexIDMap(index Index) (Index, error) {
	var indexMapPointer *C.FaissIndexIDMap
	var pointerToIndexMapPointer **C.FaissIndexIDMap = &indexMapPointer

	if C.faiss_IndexIDMap_new(pointerToIndexMapPointer, index.cPtr()) != 0 {
		return nil, errors.New("error occurred while initializing IndexIDMapWrapper")
	}

	return &faissIndex{idx: indexMapPointer}, nil
}
