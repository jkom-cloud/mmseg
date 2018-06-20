#include "MmsegWrapper.h"
#include "Mmseg.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace mmsegSpace;

struct tagMMSeg {
  MMSeg * ptr_mmseg;
  char * pSegStr;
};

struct tagMMSeg * getInstance(void) {
  tagMMSeg * ptr = new struct tagMMSeg;
  ptr->ptr_mmseg = MMSeg::getInstance();

  return ptr;
}

int loadDict(struct tagMMSeg * pInstance, const char * pDictPath) {
  std::string istr(pDictPath);
  return pInstance->ptr_mmseg->load(istr);
}

char * copySegs(struct tagMMSeg * pInstance, const char * pOrigStr) {
  std::string istr(pOrigStr); 
  std::string ostr;

  ostr = pInstance->ptr_mmseg->segment(istr);
  char * out = new char[ostr.length() + 1];

  strcpy(out, ostr.c_str());

  return out;
}

void releaseSegs(char * pSeg) {
  delete pSeg;
}

void unloadDict(struct tagMMSeg * pInstance) {
  pInstance->ptr_mmseg->unload();
}


void delInstance(tagMMSeg * pInstance) {
  delete pInstance;
}

#ifdef __cplusplus
};
#endif
