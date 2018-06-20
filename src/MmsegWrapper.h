#ifndef _MMSEG_WRAPPER_H
#define _MMSEG_WRAPPER_H

struct tagMMSeg;

#ifdef __cplusplus
extern "C" {
#endif

struct tagMMSeg * getInstance(void);
int loadDict(struct tagMMSeg * pInstance, const char * pDictPath);
char * copySegs(struct tagMMSeg * pInstance, const char * pOrigStr);
void releaseSegs(char * pSeg);
void unloadDict(struct tagMMSeg * pInstance);
void delInstance(tagMMSeg * pInstance);

#ifdef __cplusplus
};
#endif

#endif
