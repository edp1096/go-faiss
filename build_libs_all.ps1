mkdir -f dist


<# cpu #>
./clean.ps1
remove-item -r -force -ea 0 build
./build_lib.ps1

mkdir -f dist/cpu
move-item -force ./faiss.dll ./dist/cpu/
move-item -force ./libopenblas.exp.dll ./dist/cpu/
move-item -force ./faiss_c.dll ./dist/cpu/


<# gpu #>
./clean.ps1
remove-item -r -force -ea 0 build
./build_lib.ps1 cuda

mkdir -f dist/gpu
move-item -force ./faiss.dll ./dist/gpu/
move-item -force ./libopenblas.exp.dll ./dist/gpu/
move-item -force ./faiss_c_cuda.dll ./dist/gpu/
