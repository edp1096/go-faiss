//go:build windows && cuda
// +build windows,cuda

package faiss

// #cgo LDFLAGS: -L. -lfaiss_c_cuda
/*
#include <faiss/c_api/Index_c.h>
#include <faiss/c_api/error_c.h>
*/
import "C"
import "errors"

func getLastError() error {
	return errors.New(C.GoString(C.faiss_get_last_error()))
}

// Metric type
const (
	MetricInnerProduct  = C.METRIC_INNER_PRODUCT
	MetricL2            = C.METRIC_L2
	MetricL1            = C.METRIC_L1
	MetricLinf          = C.METRIC_Linf
	MetricLp            = C.METRIC_Lp
	MetricCanberra      = C.METRIC_Canberra
	MetricBrayCurtis    = C.METRIC_BrayCurtis
	MetricJensenShannon = C.METRIC_JensenShannon
)
