$useGPU = "ON"
$threadCount = 8

$startTime = Get-Date

echo "Prepare vendors..."

cd vendors
import-module bitstransfer

if (-not (Test-Path -Path "openblas.zip")) {
    echo "Downloading OpenBLAS..."
    start-bitstransfer -destination openblas.zip -source https://github.com/xianyi/OpenBLAS/releases/download/v0.3.23/OpenBLAS-0.3.23-x64.zip

    mkdir -f openblas >$null
    remove-item -r -force -ea 0 openblas/*
    remove-item -force -ea 0 *.TMP
    tar -xf openblas.zip -C openblas
}

cd ..

$openblasROOT = ("$pwd/vendors/openblas/").Replace("\", "/")
$openblasLIB = "libopenblas"

copy-item -r -force mods/faiss/* faiss/


cd faiss

# nvcc --generate-code - https://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards
# Maxwell (CUDA >= 6 <= 11)
# 50 / Quadro 4000, Quadro 6000
# 52 / GTX970, GTX980, GTX Titan X
# 53 / Tegra X1, Jetson nano
# Pascal (CUDA >= 8)
# 60 / Quadro GP100, Tesla P100
# 61 / GTX1050, GTX1050Ti, GTX1060, GTX1070, GTX1080, GTX1080Ti, Titan Xp, Tesla P4, Tesla P40
# 62 / Tegra X2
# Turing (CUDA >= 9)
# 75 / GTX1660, RTX2060, RTX2070, RTX2080, RTX2080Ti, Titan RTX
# Ampere (CUDA >= 11.1)
# 80 / A100
# 86 / RTX3050, RTX3060, RTX3060Ti, RTX3070, RTX3080, RTX3090, RTX A4000, RTX A6000, RTX A40, RTX A10
# 87 / Jetson AGX
# Ada (CUDA >= 11.8)
# 89 / RTX 40 series
# Hopper (CUDA >= 12)
# 90 / H100
# 61-real;75-real;86-real ~= 320MB
cmake -B ../build . `
-DCMAKE_CXX_FLAGS="/std:c++17 /EHsc /wd4819" -DBUILD_TESTING=OFF `
-DBUILD_SHARED_LIBS="ON" `
-DFAISS_ENABLE_C_API="ON" -DFAISS_ENABLE_PYTHON="OFF" `
-DBLA_VENDOR=OpenBLAS     -DBLAS_LIBRARIES="$openblasLIB" -DLAPACK_LIBRARIES="$openblasLIB" `
-DFAISS_OPT_LEVEL="avx2"  -DFAISS_ENABLE_GPU="$useGPU" `
-DCMAKE_CUDA_ARCHITECTURES="86-real"

cd ../build
copy-item -force $openblasROOT/lib/libopenblas.lib faiss/

cmake --build . --config Release --target faiss_c -j $threadCount


cd ..


copy-item -force vendors/openblas/bin/libopenblas.dll ./libopenblas.exp.dll
copy-item -force build/faiss/Release/faiss.dll .
copy-item -force build/c_api/Release/faiss_c.dll ./faiss_c_cu.dll

gendef faiss_c_cu.dll
(Get-Content -Path "faiss_c_cu.def") -replace "faiss_c.dll", "faiss_c_cu.dll" | Set-Content -Path "faiss_c_cu.def"
dlltool -k -d ./faiss_c_cu.def -l ./libfaiss_c_cu.a
# ar src libfaiss_c_cu.a libfaiss_c_cu.a

$endTime = Get-Date
$elapsedTime = $endTime - $startTime
Write-Host "Elapsed Time: $elapsedTime"
