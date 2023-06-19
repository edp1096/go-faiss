git checkout -- faiss
git clean faiss -df

if ($args[0] -eq "all") {
    remove-item -force -ea 0 vendors/*.TMP
    remove-item -r -force -ea 0 vendors/openblas
    remove-item -force -ea 0 vendors/openblas.zip
    remove-item -r -force -ea 0 vendors/swig
    remove-item -force -ea 0 vendors/swig.zip
    remove-item -r -force -ea 0 build
}
