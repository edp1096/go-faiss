#if defined(_WIN32) && !defined(__MINGW32__)
#define FAISS_C_API __declspec(dllexport)
#else
#define FAISS_C_API
#endif
